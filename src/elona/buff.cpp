#include "buff.hpp"

#include "../util/range.hpp"
#include "character.hpp"
#include "data/types/type_buff.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "lua_env/interface.hpp"
#include "message.hpp"
#include "random.hpp"
#include "skill.hpp"
#include "variables.hpp"



namespace elona
{

namespace
{

optional<size_t>
buff_find_slot(const Character& chara, data::InstanceId id, int turns)
{
    constexpr size_t max_buffs = 16;

    const auto& buffs = chara.buffs;

    for (size_t i = 0; i < buffs.size(); ++i)
    {
        const auto& buff = buffs[i];
        if (buff.id == id)
        {
            if (buff.turns < turns)
            {
                return i;
            }
            else
            {
                return none;
            }
        }
    }

    if (buffs.size() < max_buffs)
    {
        return buffs.size();
    }
    else
    {
        return rnd(buffs.size());
    }
}



void buff_on_removal(Character& chara, data::InstanceId id)
{
    auto& buff_data = the_buff_db.ensure(id);

    auto& on_removal = buff_data.on_removal;
    if (on_removal)
    {
        auto self = buff_data.self;
        auto args = lua::create_table("chara", lua::handle(chara));
        on_removal->call(self, args);
    }
}

} // namespace



int buff_calc_duration(data::InstanceId id, int power)
{
    const auto& buff_data = the_buff_db.ensure(id);

    auto& duration = buff_data.duration;
    return duration.call_with_result(0, power);
}



std::string buff_get_description(data::InstanceId id, int power)
{
    const auto& buff_data = the_buff_db.ensure(id);

    auto& self = buff_data.self;
    auto& description = buff_data.description;
    return description.call_with_result("<error>", self, power);
}



void buff_apply(Character& chara, data::InstanceId id, int power)
{
    const auto& buff_data = the_buff_db.ensure(id);

    auto& self = buff_data.self;
    auto& on_refresh = buff_data.on_refresh;
    auto args = lua::create_table("power", power, "chara", lua::handle(chara));
    on_refresh.call(self, args);
}



bool buff_has(const Character& chara, data::InstanceId id)
{
    return range::any_of(
        chara.buffs, [id](const auto& buff) { return buff.id == id; });
}



optional_ref<const Buff> buff_find(const Character& chara, data::InstanceId id)
{
    if (const auto itr = range::find_if(
            chara.buffs, [id](const auto& buff) { return buff.id == id; });
        itr != chara.buffs.end())
    {
        return *itr;
    }
    else
    {
        return none;
    }
}



void buff_add(
    Character& chara,
    data::InstanceId id,
    int power,
    int turns,
    optional_ref<const Character> doer)
{
    if (turns <= 0)
        return;

    const auto& buff_data = the_buff_db.ensure(id);

    const auto slot_opt = buff_find_slot(chara, id, turns);
    if (!slot_opt)
    {
        if (is_in_fov(chara))
        {
            txt(i18n::s.get("core.magic.buff.no_effect"));
            return;
        }
    }
    const auto slot = *slot_opt;

    if (buff_data.type == BuffType::hex)
    {
        bool resists{};
        if (chara.skills().level("core.element_magic") / 2 >
            rnd_capped(power * 2 + 100))
        {
            resists = true;
        }
        if (power * 3 < chara.skills().level("core.element_magic"))
        {
            resists = true;
        }
        if (power / 3 > chara.skills().level("core.element_magic"))
        {
            resists = false;
        }
        if (chara.quality > Quality::great)
        {
            if (rnd(4))
            {
                resists = true;
            }
            else
            {
                turns = turns / 5 + 1;
            }
        }
        if (chara.quality >= Quality::miracle && id == "core.death_word")
        {
            resists = true;
        }
        if (const auto holy_veil = buff_find(chara, "core.holy_veil"))
        {
            if (holy_veil->power + 50 > power * 5 / 2 ||
                rnd_capped(holy_veil->power + 50) > rnd_capped(power + 1))
            {
                txt(i18n::s.get("core.magic.buff.holy_veil_repels"));
                return;
            }
        }
        if (resists)
        {
            if (is_in_fov(chara))
            {
                txt(i18n::s.get("core.magic.buff.resists", chara));
            }
            return;
        }
        if (doer && doer->is_player())
        {
            chara_act_hostile_action(cdata.player(), chara);
        }
    }

    if (is_in_fov(chara))
    {
        // Messages of fodd buff are shown elsewhere.
        if (buff_data.type != BuffType::food)
        {
            txt(the_buff_db.get_text(id, "apply", chara));
        }

        add_damage_popup(
            the_buff_db.get_text(id, "name"), chara.index, {255, 255, 255});
    }

    if (chara.buffs.size() <= slot)
    {
        chara.buffs.push_back({id, power, turns});
    }
    else
    {
        chara.buffs[slot] = {id, power, turns};
    }

    chara_refresh(chara);
}



BuffList::iterator buff_remove_at(Character& chara, BuffList::iterator itr)
{
    if (chara.is_player())
    {
        txt(i18n::s.get(
                "core.magic.buff.ends", the_buff_db.get_text(itr->id, "name")),
            Message::color{ColorIndex::purple});
    }
    if (is_in_fov(chara))
    {
        add_damage_popup(
            the_buff_db.get_text(itr->id, "name"),
            chara.index,
            {191, 191, 191});
    }

    buff_on_removal(chara, itr->id);
    const auto ret = chara.buffs.erase(itr);
    chara_refresh(chara);
    return ret;
}

} // namespace elona

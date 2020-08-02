#include "buff.hpp"

#include "../util/range.hpp"
#include "ability.hpp"
#include "character.hpp"
#include "data/types/type_buff.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "lua_env/interface.hpp"
#include "message.hpp"
#include "random.hpp"
#include "variables.hpp"



namespace elona
{

namespace
{

constexpr int buff_find_slot_no_effect = -1;

int buff_find_slot(const Character& chara, int id, int turns)
{
    for (size_t i = 0; i < chara.buffs.size(); ++i)
    {
        if (chara.buffs[i].id == id)
        {
            if (chara.buffs[i].turns < turns)
            {
                return static_cast<int>(i);
            }
            else
            {
                return buff_find_slot_no_effect;
            }
        }
        if (chara.buffs[i].id == 0)
        {
            return i;
        }
    }

    return rnd(static_cast<int>(chara.buffs.size()));
}



void buff_on_removal(Character& chara, int id)
{
    auto buff = the_buff_db[id];
    assert(buff);

    auto& on_removal = buff->on_removal;
    if (on_removal)
    {
        auto self = buff->self;
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
    const auto& buff_data = the_buff_db.ensure(id);

    return range::any_of(
        chara.buffs, [legacy_id = buff_data.legacy_id](const auto& buff) {
            return buff.id == legacy_id;
        });
}



optional_ref<const Buff> buff_find(const Character& chara, data::InstanceId id)
{
    const auto& buff_data = the_buff_db.ensure(id);

    const auto itr = range::find_if(
        chara.buffs, [legacy_id = buff_data.legacy_id](const auto& buff) {
            return buff.id == legacy_id;
        });
    if (itr == std::end(chara.buffs))
    {
        return none;
    }
    else
    {
        return *itr;
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

    const auto legacy_id = buff_data.legacy_id;

    const auto slot = buff_find_slot(chara, legacy_id, turns);
    if (slot == buff_find_slot_no_effect)
    {
        if (is_in_fov(chara))
        {
            txt(i18n::s.get("core.magic.buff.no_effect"));
            return;
        }
    }

    if (buff_data.type == BuffType::hex)
    {
        bool resists{};
        if (chara.get_skill(60).level / 2 > rnd_capped(power * 2 + 100))
        {
            resists = true;
        }
        if (power * 3 < chara.get_skill(60).level)
        {
            resists = true;
        }
        if (power / 3 > chara.get_skill(60).level)
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
        if (const auto& holy_veil = buff_find(chara, "core.holy_veil"))
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
            txt(i18n::s.get_enum_property(
                "core.buff", "apply", legacy_id, chara));
        }

        add_damage_popup(
            i18n::s.get_enum_property("core.buff", "name", legacy_id),
            chara.index,
            {255, 255, 255});
    }

    chara.buffs[slot] = {legacy_id, power, turns};

    chara_refresh(chara);
}



void buff_delete(Character& chara, int slot)
{
    if (chara.is_player())
    {
        txt(i18n::s.get(
                "core.magic.buff.ends",
                i18n::s.get_enum_property(
                    "core.buff", "name", chara.buffs[slot].id)),
            Message::color{ColorIndex::purple});
    }
    if (is_in_fov(chara))
    {
        add_damage_popup(
            i18n::s.get_enum_property(
                "core.buff", "name", chara.buffs[slot].id),
            chara.index,
            {191, 191, 191});
    }

    buff_on_removal(chara, chara.buffs[slot].id);
    chara.buffs[slot].id = 0;
    for (int i = slot; i < 16 - slot - 1; ++i)
    {
        if (chara.buffs[i].id == 0)
        {
            if (chara.buffs[i + 1].id != 0)
            {
                chara.buffs[i] = chara.buffs[i + 1];
                chara.buffs[i + 1] = Buff{};
            }
            else
            {
                break;
            }
        }
    }

    chara_refresh(chara);
}

} // namespace elona

#include "buff.hpp"
#include "../util/range.hpp"
#include "ability.hpp"
#include "character.hpp"
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

int buff_find_slot(const Character& cc, int id, int turns)
{
    for (size_t i = 0; i < cc.buffs.size(); ++i)
    {
        if (cc.buffs[i].id == id)
        {
            if (cc.buffs[i].turns < turns)
            {
                return static_cast<int>(i);
            }
            else
            {
                return buff_find_slot_no_effect;
            }
        }
        if (cc.buffs[i].id == 0)
        {
            return i;
        }
    }

    return rnd(static_cast<int>(cc.buffs.size()));
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



int buff_calc_duration(int id, int power)
{
    auto buff = the_buff_db[id];
    assert(buff);

    auto& duration = buff->duration;
    return duration.call_with_result(0, power);
}



std::string buff_get_description(int id, int power)
{
    auto buff = the_buff_db[id];
    assert(buff);

    auto& self = buff->self;
    auto& description = buff->description;
    return description.call_with_result("<error>", self, power);
}



void buff_apply(Character& chara, int id, int power)
{
    auto buff = the_buff_db[id];
    assert(buff);

    auto& self = buff->self;
    auto& on_refresh = buff->on_refresh;
    auto args = lua::create_table("power", power, "chara", lua::handle(chara));
    on_refresh.call(self, args);
}



bool buff_has(const Character& chara, const std::string& id)
{
    auto buff_def = the_buff_db[id];
    assert(buff_def);

    int legacy_id = buff_def->legacy_id;
    return range::any_of(
        chara.buffs, [&](const auto& buff) { return buff.id == legacy_id; });
}



optional_ref<const Buff> buff_find(
    const Character& chara,
    const std::string& id)
{
    auto buff_def = the_buff_db[id];
    assert(buff_def);

    int legacy_id = buff_def->legacy_id;
    const auto itr = range::find_if(
        chara.buffs, [&](const auto& buff) { return buff.id == legacy_id; });
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
    const std::string& id,
    int power,
    int turns,
    optional_ref<const Character> doer)
{
    auto buff = the_buff_db[id];
    assert(buff);

    int legacy_id = buff->legacy_id;

    if (turns <= 0)
        return;

    const auto slot = buff_find_slot(chara, legacy_id, turns);
    if (slot == buff_find_slot_no_effect)
    {
        if (is_in_fov(chara))
        {
            txt(i18n::s.get("core.magic.buff.no_effect"));
            return;
        }
    }

    if (buff->type == BuffType::hex)
    {
        bool resists{};
        if (sdata(60, chara.index) / 2 > rnd(power * 2 + 100))
        {
            resists = true;
        }
        if (power * 3 < sdata(60, chara.index))
        {
            resists = true;
        }
        if (power / 3 > sdata(60, chara.index))
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
                rnd(holy_veil->power + 50) > rnd(power + 1))
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
        if (doer && doer->index == 0)
        {
            hostileaction(0, chara.index);
        }
    }

    if (is_in_fov(chara))
    {
        // Messages of fodd buff are shown elsewhere.
        if (buff->type != BuffType::food)
        {
            txt(i18n::s.get_enum_property(
                "core.buff", legacy_id, "apply", chara));
        }

        add_damage_popup(
            i18n::s.get_enum_property("core.buff", "name", legacy_id),
            chara.index,
            {255, 255, 255});
    }

    chara.buffs[slot] = {legacy_id, power, turns};

    chara_refresh(chara.index);
}



void buff_delete(Character& chara, int slot)
{
    if (chara.index == 0)
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

    chara_refresh(chara.index);
}

} // namespace elona

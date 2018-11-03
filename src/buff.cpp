#include "buff.hpp"
#include "ability.hpp"
#include "cat.hpp"
#include "character.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "message.hpp"
#include "random.hpp"
#include "variables.hpp"



using namespace elona;


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



} // namespace



namespace elona
{


BuffDB the_buff_db;


BuffDB::BuffDB()
{
    storage.emplace(
        0,
        BuffData{0,
                 LUA_REFNIL,
                 BuffData::Type::buff,
                 LUA_REFNIL,
                 LUA_REFNIL}); // dummy
}


void BuffDB::define(lua_State* L)
{
    const char* id = luaL_checkstring(L, -2);
    if (!id)
        throw std::runtime_error(u8"Error: fail to load buff data");

    ELONA_CAT_DB_FIELD_INTEGER(type_, 0);
    ELONA_CAT_DB_FIELD_REF(duration);
    ELONA_CAT_DB_FIELD_REF(on_refresh);

    cat::Ref self = luaL_ref(L, LUA_REGISTRYINDEX);
    // Dummy; after calling this function, the caller pop one value from the Lua
    // stack.
    lua_pushnil(L);

    storage.emplace(
        std::stoi(id), // TODO
        BuffData{
            std::stoi(id),
            self,
            BuffData::Type(type_),
            duration,
            on_refresh,
        });
}



bool buff_has(const Character& cc, int id)
{
    return std::any_of(
        std::begin(cc.buffs), std::end(cc.buffs), [&](const auto& buff) {
            return buff.id == id;
        });
}



optional_ref<const Buff> buff_find(const Character& cc, int id)
{
    const auto itr = std::find_if(
        std::begin(cc.buffs), std::end(cc.buffs), [&](const auto& buff) {
            return buff.id == id;
        });
    if (itr == std::end(cc.buffs))
    {
        return none;
    }
    else
    {
        return *itr;
    }
}



void buff_add(
    Character& cc,
    int id,
    int power,
    int turns,
    optional_ref<const Character> doer)
{
    if (turns <= 0)
        return;

    const auto slot = buff_find_slot(cc, id, turns);
    if (slot == buff_find_slot_no_effect)
    {
        if (is_in_fov(cc))
        {
            txt(i18n::s.get("core.locale.magic.buff.no_effect"));
            return;
        }
    }

    if (the_buff_db[id]->type == BuffData::Type::hex)
    {
        bool resists{};
        if (sdata(60, cc.index) / 2 > rnd(power * 2 + 100))
        {
            resists = true;
        }
        if (power * 3 < sdata(60, cc.index))
        {
            resists = true;
        }
        if (power / 3 > sdata(60, cc.index))
        {
            resists = false;
        }
        if (cc.quality > Quality::great)
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
        if (cc.quality >= Quality::miracle && id == 16)
        {
            resists = true;
        }
        if (const auto& holy_veil = buff_find(cc, 10))
        {
            if (holy_veil->power + 50 > power * 5 / 2
                || rnd(holy_veil->power + 50) > rnd(power + 1))
            {
                txt(i18n::s.get("core.locale.magic.buff.holy_veil_repels"));
                return;
            }
        }
        if (resists)
        {
            if (is_in_fov(cc))
            {
                txt(i18n::s.get("core.locale.magic.buff.resists", cc));
            }
            return;
        }
        if (doer && doer->index == 0)
        {
            hostileaction(0, cc.index);
        }
    }

    if (is_in_fov(cc))
    {
        // Messages of fodd buff are shown elsewhere.
        if (the_buff_db[id]->type != BuffData::Type::food)
        {
            txt(i18n::s.get_enum_property("core.locale.buff", id, "apply", cc));
        }

        add_damage_popup(
            i18n::s.get_enum_property("core.locale.buff", "name", id),
            cc.index,
            {255, 255, 255});
    }

    cc.buffs[slot] = {id, power, turns};

    chara_refresh(cc.index);
}



void buff_delete(Character& cc, int slot)
{
    if (cc.index == 0)
    {
        Message::instance().txtef(ColorIndex::purple);
        txt(i18n::s.get(
            "core.locale.magic.buff.ends",
            i18n::s.get_enum_property(
                "core.locale.buff", "name", cc.buffs[slot].id)));
    }
    if (is_in_fov(cc))
    {
        add_damage_popup(
            i18n::s.get_enum_property(
                "core.locale.buff", "name", cc.buffs[slot].id),
            cc.index,
            {191, 191, 191});
    }
    if (cc.buffs[slot].id == 15)
    {
        if (cc.index == 0)
        {
            incognitoend();
        }
    }
    if (cc.buffs[slot].id == 16)
    {
        cc.is_sentenced_daeth() = false;
    }
    if (cc.buffs[slot].id == 18)
    {
        cc.is_contracting_with_reaper() = false;
    }
    cc.buffs[slot].id = 0;
    for (int cnt = slot, cnt_end = cnt + (16 - slot - 1); cnt < cnt_end; ++cnt)
    {
        if (cc.buffs[cnt].id == 0)
        {
            if (cc.buffs[cnt + 1].id != 0)
            {
                cc.buffs[cnt] = cc.buffs[cnt + 1];
                cc.buffs[cnt + 1] = Buff{};
            }
            else
            {
                break;
            }
        }
    }

    chara_refresh(cc.index);
}



} // namespace elona

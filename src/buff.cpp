#include "buff.hpp"
#include "ability.hpp"
#include "cat.hpp"
#include "character.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "random.hpp"
#include "variables.hpp"

#include <iostream>

using namespace elona;


namespace elona
{


buff_db the_buff_db;


buff_db::buff_db()
{
    storage.emplace(
        0,
        buff_data{0,
                  LUA_REFNIL,
                  buff_data::type_t::buff,
                  LUA_REFNIL,
                  LUA_REFNIL}); // dummy
}


void buff_db::define(lua_State* L)
{
    const char* id = luaL_checkstring(L, -2);
    if (!id)
        throw std::runtime_error(u8"Error: fail to load buff data");

    ELONA_CAT_DB_FIELD_INTEGER(type_, 0);
    ELONA_CAT_DB_FIELD_REF(duration);
    ELONA_CAT_DB_FIELD_REF(on_refresh);

    cat::ref self = luaL_ref(L, LUA_REGISTRYINDEX);
    // Dummy; after calling this function, the caller pop one value from the Lua
    // stack.
    lua_pushnil(L);

    storage.emplace(
        std::stoi(id), // TODO
        buff_data{
            std::stoi(id),
            self,
            buff_data::type_t(type_),
            duration,
            on_refresh,
        });
}



int buff_find(int prm_799, int prm_800)
{
    int f_at_m131 = 0;
    f_at_m131 = -1;
    for (int cnt = 0; cnt < 16; ++cnt)
    {
        if (cdata[prm_799].buffs[cnt].id == 0)
        {
            break;
        }
        if (cdata[prm_799].buffs[cnt].id == prm_800)
        {
            f_at_m131 = cnt;
            break;
        }
    }
    return f_at_m131;
}



int buff_add(int prm_801, int prm_802, int prm_803, int prm_804)
{
    int p_at_m132 = 0;
    int fixeddur_at_m132 = 0;
    int f_at_m132 = 0;
    if (prm_804 <= 0)
    {
        return 0;
    }
    p_at_m132 = -1;
    for (int cnt = 0; cnt < 16; ++cnt)
    {
        if (cdata[prm_801].buffs[cnt].id == prm_802)
        {
            if (cdata[prm_801].buffs[cnt].turns < prm_804)
            {
                p_at_m132 = cnt;
                break;
            }
            else
            {
                p_at_m132 = -2;
                break;
            }
        }
        if (cdata[prm_801].buffs[cnt].id == 0)
        {
            p_at_m132 = cnt;
            break;
        }
    }
    if (p_at_m132 == -1)
    {
        p_at_m132 = rnd(16);
    }
    if (p_at_m132 == -2)
    {
        if (is_in_fov(prm_801))
        {
            txt(i18n::s.get("core.locale.magic.buff.no_effect"));
            return 0;
        }
    }
    fixeddur_at_m132 = prm_804;
    if (the_buff_db[prm_802]->type == buff_data::type_t::hex)
    {
        f_at_m132 = 0;
        if (sdata(60, prm_801) / 2 > rnd(prm_803 * 2 + 100))
        {
            f_at_m132 = 1;
        }
        if (prm_803 * 3 < sdata(60, prm_801))
        {
            f_at_m132 = 1;
        }
        if (prm_803 / 3 > sdata(60, prm_801))
        {
            f_at_m132 = 0;
        }
        if (cdata[prm_801].quality > 3)
        {
            if (rnd(4))
            {
                f_at_m132 = 1;
            }
            else
            {
                fixeddur_at_m132 = prm_804 / 5 + 1;
            }
        }
        if (cdata[prm_801].quality >= 4)
        {
            if (prm_802 == 16)
            {
                f_at_m132 = 1;
            }
        }
        if (buff_find(prm_801, 10) != -1)
        {
            if (cdata[prm_801].buffs[buff_find(prm_801, 10)].power + 50
                    > prm_803 * 5 / 2
                || rnd(cdata[prm_801].buffs[buff_find(prm_801, 10)].power + 50)
                    > rnd(prm_803 + 1))
            {
                txt(i18n::s.get("core.locale.magic.buff.holy_veil_repels"));
                return 0;
            }
        }
        if (f_at_m132 == 1)
        {
            if (is_in_fov(prm_801))
            {
                txt(i18n::s.get("core.locale.magic.buff.resists", cdata[prm_801]));
            }
            return 0;
        }
        if (cc == 0)
        {
            hostileaction(0, prm_801);
        }
    }
    if (the_buff_db[prm_802]->type != buff_data::type_t::food
        && is_in_fov(prm_801))
    {
        txt(lang(
            name(prm_801)
                + i18n::_(u8"buff", std::to_string(prm_802), u8"message_0"),
            name(prm_801) + u8" "s
                + i18n::_(u8"buff", std::to_string(prm_802), u8"message_0")
                + _s(prm_801)
                + i18n::_(u8"buff", std::to_string(prm_802), u8"message_1")));

        add_damage_popup(
            i18n::_(u8"buff", std::to_string(prm_802), u8"name"),
            prm_801,
            {255, 255, 255});
    }
    cdata[prm_801].buffs[p_at_m132].id = prm_802;
    cdata[prm_801].buffs[p_at_m132].power = prm_803;
    cdata[prm_801].buffs[p_at_m132].turns = fixeddur_at_m132;
    chara_refresh(prm_801);
    return 0;
}



void buff_delete(int prm_805, int prm_806)
{
    if (prm_805 == 0)
    {
        txtef(8);
        txt(i18n::s.get("core.locale.magic.buff.ends",
                        i18n::_(u8"buff", std::to_string(cdata[prm_805].buffs[prm_806].id), u8"name")));
    }
    if (is_in_fov(prm_805))
    {
        add_damage_popup(
            i18n::_(
                u8"buff",
                std::to_string(cdata[prm_805].buffs[prm_806].id),
                u8"name"),
            prm_805,
            {191, 191, 191});
    }
    if (cdata[prm_805].buffs[prm_806].id == 15)
    {
        if (prm_805 == 0)
        {
            incognitoend();
        }
    }
    if (cdata[prm_805].buffs[prm_806].id == 16)
    {
        cdata[prm_805].is_sentenced_daeth() = false;
    }
    if (cdata[prm_805].buffs[prm_806].id == 18)
    {
        cdata[prm_805].is_contracting_with_reaper() = false;
    }
    cdata[prm_805].buffs[prm_806].id = 0;
    for (int cnt = prm_806, cnt_end = cnt + (16 - prm_806 - 1); cnt < cnt_end;
         ++cnt)
    {
        if (cdata[prm_805].buffs[cnt].id == 0)
        {
            if (cdata[prm_805].buffs[cnt + 1].id != 0)
            {
                cdata[prm_805].buffs[cnt].id = cdata[prm_805].buffs[cnt + 1].id;
                cdata[prm_805].buffs[cnt].power =
                    cdata[prm_805].buffs[cnt + 1].power;
                cdata[prm_805].buffs[cnt].turns =
                    cdata[prm_805].buffs[cnt + 1].turns;
                cdata[prm_805].buffs[cnt + 1].id = 0;
                cdata[prm_805].buffs[cnt + 1].power = 0;
                cdata[prm_805].buffs[cnt + 1].turns = 0;
            }
            else
            {
                break;
            }
        }
    }
    chara_refresh(prm_805);
    return;
}



} // namespace elona

#include "item.hpp"
#include <iostream>
#include <type_traits>
#include "ability.hpp"
#include "blending.hpp"
#include "character.hpp"
#include "crafting.hpp"
#include "elona.hpp"
#include "food.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "item_db.hpp"
#include "lua_env/lua_env.hpp"
#include "main.hpp"
#include "map.hpp"
#include "mef.hpp"
#include "random.hpp"
#include "variables.hpp"


namespace elona
{


inventory inv;

int ci_at_m138 = 0;
int p_at_m138 = 0;
int max_at_m138 = 0;
int ti_at_m138 = 0;
elona_vector1<int> list_at_m138;
int f_at_m138 = 0;
int a_at_m138 = 0;


item::item()
    : enchantments(15)
{
}

void item::clear()
{
    item tmp;
    std::swap(*this, tmp);
}


bool item::almost_equals(const item& other, bool ignore_position)
{
    return true
        // && number == other.number
        && value == other.value && image == other.image
        && id == other.id
        // && quality == other.quality
        && (ignore_position || position == other.position)
        && weight == other.weight
        && identification_state == other.identification_state
        && count == other.count && dice_x == other.dice_x
        && dice_y == other.dice_y && damage_bonus == other.damage_bonus
        && hit_bonus == other.hit_bonus && dv == other.dv && pv == other.pv
        && skill == other.skill && curse_state == other.curse_state
        && body_part == other.body_part && function == other.function
        && enhancement == other.enhancement && own_state == other.own_state
        && color == other.color && subname == other.subname
        && material == other.material && param1 == other.param1
        && param2 == other.param2 && param3 == other.param3
        && param4 == other.param4
        && difficulty_of_identification == other.difficulty_of_identification
        // && turn == other.turn
        && flags == other.flags
        && range::equal(enchantments, other.enchantments);
}

inventory::inventory()
    : storage(5480)
{
}

int ibit(size_t type, int ci)
{
    assert(type < sizeof(item::flags) * 8);
    return inv(ci).flags & (1 << type) ? 1 : 0;
}



void ibitmod(size_t type, int ci, int on)
{
    assert(type < sizeof(item::flags) * 8);
    if (on)
    {
        inv(ci).flags |= 1 << type;
    }
    else
    {
        inv(ci).flags &= ~(1 << type);
    }
}



int f_at_m53 = 0;
int f_at_m54 = 0;
elona_vector1<int> p_at_m57;
std::string s_;
int a_ = 0;
int skip_ = 0;


range::iota<int> items(int owner)
{
    const auto tmp = inv_getheader(owner);
    return {tmp.first, tmp.first + tmp.second};
}

int item_find(int prm_476, int prm_477, int prm_478)
{
    elona_vector1<int> p_at_m52;
    p_at_m52(0) = -1;
    p_at_m52(1) = -1;
    for (int cnt = 0; cnt < 2; ++cnt)
    {
        int invhead;
        int invrange;
        if (cnt == 0)
        {
            if (prm_478 > 0)
            {
                continue;
            }
            const auto pair = inv_getheader(-1);
            invhead = pair.first;
            invrange = pair.second;
        }
        else
        {
            if (prm_478 < 0)
            {
                continue;
            }
            const auto pair = inv_getheader(0);
            invhead = pair.first;
            invrange = pair.second;
        }
        p_at_m52(2) = cnt;
        for (int cnt = invhead, cnt_end = cnt + (invrange); cnt < cnt_end;
             ++cnt)
        {
            if (inv[cnt].number == 0)
            {
                continue;
            }
            if (p_at_m52(2) == 0)
            {
                if (inv[cnt].position.x != cdata[0].position.x
                    || inv[cnt].position.y != cdata[0].position.y)
                {
                    continue;
                }
            }
            if (prm_477 == 0)
            {
                if (the_item_db[inv[cnt].id]->category == prm_476)
                {
                    p_at_m52 = cnt;
                }
            }
            if (prm_477 == 1)
            {
                if (inv[cnt].skill == prm_476)
                {
                    if (p_at_m52(1) < inv[cnt].param1)
                    {
                        p_at_m52(0) = cnt;
                        p_at_m52(1) = inv[cnt].param1;
                    }
                }
            }
            if (prm_477 == 2)
            {
                if (the_item_db[inv[cnt].id]->subcategory == prm_476)
                {
                    p_at_m52 = cnt;
                }
            }
            if (prm_477 == 3)
            {
                if (inv[cnt].id == prm_476)
                {
                    p_at_m52 = cnt;
                }
            }
        }
    }
    return p_at_m52;
}



int encfind(int cc, int id)
{
    int power = -1;
    for (int cnt = 100; cnt < 130; ++cnt)
    {
        if (cdata_body_part(cc, cnt) % 10000 == 0)
        {
            continue;
        }
        int ci = cdata_body_part(cc, cnt) % 10000 - 1;
        for (int cnt = 0; cnt < 15; ++cnt)
        {
            if (inv[ci].enchantments[cnt].id == 0)
            {
                break;
            }
            if (inv[ci].enchantments[cnt].id == id)
            {
                if (inv[ci].enchantments[cnt].power > power)
                {
                    power = inv[ci].enchantments[cnt].power;
                    break;
                }
            }
        }
    }
    return power;
}



bool encfindspec(int ci, int id)
{
    for (int cnt = 0; cnt < 15; ++cnt)
    {
        if (inv[ci].enchantments[cnt].id == 0)
        {
            break;
        }
        if (inv[ci].enchantments[cnt].id == id)
        {
            return true;
        }
    }
    return false;
}



std::vector<int> itemlist(int owner, int id)
{
    std::vector<int> ret;
    for (const auto& cnt : items(owner))
    {
        if (inv[cnt].number == 0)
        {
            continue;
        }
        if (inv[cnt].id == id)
        {
            ret.push_back(cnt);
        }
    }
    return ret;
}



int itemusingfind(int ci, bool disallow_pc)
{
    for (int cnt = 0; cnt < ELONA_MAX_CHARACTERS; ++cnt)
    {
        if (cdata[cnt].state != 1)
        {
            continue;
        }
        if (cdata[cnt].continuous_action_id != 0
            && cdata[cnt].continuous_action_id != 11
            && cdata[cnt].continuous_action_turn > 0
            && cdata[cnt].continuous_action_item == ci)
        {
            if (!disallow_pc || cnt != 0)
            {
                return cnt;
            }
        }
    }
    return -1; // Not found
}



int itemfind(int prm_487, int prm_488, int prm_489)
{
    f_at_m54 = -1;
    if (prm_489 == 0)
    {
        for (const auto& cnt : items(prm_487))
        {
            if (inv[cnt].number == 0)
            {
                continue;
            }
            if (inv[cnt].id == prm_488)
            {
                f_at_m54 = cnt;
                break;
            }
        }
        return f_at_m54;
    }
    else
    {
        for (const auto& cnt : items(prm_487))
        {
            if (inv[cnt].number == 0)
            {
                continue;
            }
            if (the_item_db[inv[cnt].id]->subcategory == prm_488)
            {
                f_at_m54 = cnt;
                break;
            }
        }
        return f_at_m54;
    }
}



int mapitemfind(int x, int y, int id)
{
    for (const auto& cnt : items(-1))
    {
        if (inv[cnt].number == 0)
        {
            continue;
        }
        if (inv[cnt].id == id && inv[cnt].position == position_t{x, y})
        {
            return cnt;
        }
    }
    return -1; // Not found
}



void cell_refresh(int prm_493, int prm_494)
{
    int p_at_m55 = 0;
    elona_vector1<int> n_at_m55;
    int cnt2_at_m55 = 0;
    int i_at_m55 = 0;
    if (mode == 6 || mode == 9)
    {
        return;
    }
    if (prm_493 < 0 || prm_494 < 0 || prm_493 >= mdata(0)
        || prm_494 >= mdata(1))
    {
        return;
    }
    p_at_m55 = 0;
    map(prm_493, prm_494, 4) = 0;
    map(prm_493, prm_494, 9) = 0;
    for (const auto& cnt : items(-1))
    {
        if (inv[cnt].number > 0)
        {
            if (inv[cnt].position.x == prm_493
                && inv[cnt].position.y == prm_494)
            {
                floorstack(p_at_m55) = cnt;
                ++p_at_m55;
                wpoke(map(prm_493, prm_494, 4), 0, inv[cnt].image);
                wpoke(map(prm_493, prm_494, 4), 2, inv[cnt].color);
                if (ilight(inv[cnt].id) != 0)
                {
                    map(prm_493, prm_494, 9) = ilight(inv[cnt].id);
                }
            }
        }
    }
    if (p_at_m55 > 3)
    {
        wpoke(map(prm_493, prm_494, 4), 0, 363);
        wpoke(map(prm_493, prm_494, 4), 2, 0);
    }
    else if (p_at_m55 > 1)
    {
        n_at_m55(2) = 0;
        for (int cnt = 0, cnt_end = (p_at_m55); cnt < cnt_end; ++cnt)
        {
            cnt2_at_m55 = cnt;
            i_at_m55 = -1;
            for (int cnt = 0, cnt_end = (p_at_m55); cnt < cnt_end; ++cnt)
            {
                if (cnt2_at_m55 == 1)
                {
                    if (cnt == n_at_m55(0))
                    {
                        continue;
                    }
                }
                if (cnt2_at_m55 == 2)
                {
                    if (cnt == n_at_m55(0) || cnt == n_at_m55(1))
                    {
                        continue;
                    }
                }
                if (inv[floorstack(cnt)].turn > i_at_m55)
                {
                    n_at_m55(cnt2_at_m55) = cnt;
                    i_at_m55 = inv[floorstack(cnt)].turn;
                }
            }
        }
        map(prm_493, prm_494, 4) = floorstack(n_at_m55(0)) - 5080;
        map(prm_493, prm_494, 4) += (floorstack(n_at_m55(1)) - 5080) * 1000;
        if (p_at_m55 > 2)
        {
            map(prm_493, prm_494, 4) +=
                (floorstack(n_at_m55(2)) - 5080) * 1000000;
        }
        else
        {
            map(prm_493, prm_494, 4) += 999000000;
        }
        map(prm_493, prm_494, 4) *= -1;
    }
    return;
}



void itemturn(int ci)
{
    if (gdata_item_turns < 0)
    {
        gdata_item_turns = 0;
    }
    ++gdata_item_turns;
    inv[ci].turn = gdata_item_turns;
}



void removeitem(int ci, int delta)
{
    inv[ci].number -= delta;
    if (ci < 200)
    {
        refresh_burden_state();
    }
    if (inv[ci].number <= 0)
    {
        item_remove(inv[ci]);
        if (mode != 6 && ci >= 5080)
        {
            cell_refresh(inv[ci].position.x, inv[ci].position.y);
        }
    }
}



void item_copy(int a, int b)
{
    if (a < 0 || b < 0)
        return;

    inv[b] = inv[a];
    // Restore "index".
    inv[b].index = b;
}



void item_exchange(int a, int b)
{
    using std::swap;
    swap(inv[a], inv[b]);
    // Restore "index".
    inv[a].index = a;
    inv[b].index = b;
}


void item_remove(item& i)
{
    i.number = 0;
    lua::lua.on_item_removal(i);
}

// TODO this only runs after an invalid item slot is replaced by a new
// item. The callbacks actually need to run wherever item.number is
// set to 0, which is in many more places.
void item_delete(int ci)
{
    if (inv[ci].index != -1 && inv[ci].number > 0)
    {
        // This item slot was previously occupied, but the item is now
        // invalid.
        lua::lua.on_item_removal(inv[ci]);
    }
    else
    {
        // This item slot has never been previously occupied (since
        // its idx is -1), so don't run the removal callback.
    }
    inv[ci].clear();
    // Restore "index".
    inv[ci].index = ci;
}



void item_num(int ci, int delta)
{
    inv[ci].number += delta;
    if (inv[ci].number < 0)
    {
        item_remove(inv[ci]);
    }
    if (ci >= 5080)
    {
        cell_refresh(inv[ci].position.x, inv[ci].position.y);
    }
    else
    {
        refresh_burden_state();
    }
}



int item_separate(int ci)
{
    if (inv[ci].number <= 1)
        return ci;

    int ti = inv_getfreeid(inv_getowner(ci));
    if (ti == -1)
    {
        ti = inv_getfreeid(-1);
        if (ti == -1)
        {
            inv[ci].number = 1;
            txt(lang(
                u8"何かが地面に落ちて消えた…"s,
                u8"Something falls to the ground and disappear..."s));
            return ci;
        }
    }

    item_copy(ci, ti);
    inv[ti].number = inv[ci].number - 1;
    inv[ci].number = 1;

    if (inv_getowner(ti) == -1 && mode != 6)
    {
        if (inv_getowner(ci) != -1)
        {
            inv[ci].position = cdata[inv_getowner(ci)].position;
        }
        inv[ti].position = inv[ci].position;
        itemturn(ti);
        cell_refresh(inv[ti].position.x, inv[ti].position.y);
        txt(lang(
            u8"何かが地面に落ちた。"s,
            u8"Something falls to the ground from your backpack."s));
        refresh_burden_state();
    }

    return ti;
}



bool chara_unequip(int ci)
{
    if (inv[ci].body_part == 0)
        return false;

    int body_part = inv[ci].body_part;
    int owner = inv_getowner(ci);
    if (owner == -1)
        return false;

    cdata_body_part(owner, body_part) =
        cdata_body_part(owner, body_part) / 10000 * 10000;
    inv[ci].body_part = 0;
    return true;
}


identification_state_t item_identify(item& ci, identification_state_t level)
{
    if (level == identification_state_t::almost_identified
        && the_item_db[ci.id]->category >= 50000)
    {
        level = identification_state_t::completely_identified;
    }
    if (ci.identification_state >= level)
    {
        idtresult = identification_state_t::unidentified;
        return idtresult;
    }
    ci.identification_state = level;
    if (ci.identification_state >= identification_state_t::partly_identified)
    {
        itemmemory(0, ci.id) = 1;
    }
    idtresult = level;
    return idtresult;
}


identification_state_t item_identify(item& ci, int power)
{
    return item_identify(
        ci,
        power >= ci.difficulty_of_identification
            ? identification_state_t::completely_identified
            : identification_state_t::unidentified);
}


void item_checkknown(int ci)
{
    if (inv[ci].identification_state
        == identification_state_t::completely_identified)
    {
        inv[ci].identification_state =
            identification_state_t::completely_identified;
    }
    if (itemmemory(0, inv[ci].id)
        && inv[ci].identification_state == identification_state_t::unidentified)
    {
        item_identify(inv[ci], identification_state_t::partly_identified);
    }
}



void itemname_additional_info()
{
    if (inv[prm_518].id == 578)
    {
        s_ += lang(
            ""s + moneyboxn(inv[prm_518].param2),
            u8"("s + moneyboxn(inv[prm_518].param2) + u8")"s);
    }
    if (inv[prm_518].id == 617)
    {
        s_ += lang(
            ""s + biten(inv[prm_518].param1),
            u8" <"s + biten(inv[prm_518].param1) + u8">"s);
    }
    if (inv[prm_518].id == 687)
    {
        if (jp)
        {
            if (inv[prm_518].param2 != 0)
            {
                s_ += u8"解読済みの"s;
            }
        }
        if (inv[prm_518].identification_state
            == identification_state_t::completely_identified)
        {
            s_ += lang(
                u8"《"s + magebookn(inv[prm_518].param1) + u8"》という題名の"s,
                u8" titled <"s + magebookn(inv[prm_518].param1) + u8">"s);
        }
    }
    if (inv[prm_518].id == 783)
    {
        if (inv[prm_518].param1 == 0)
        {
            s_ += lang(u8"もう使えない"s, u8" which cannot be used anymore"s);
        }
        else if (inv[prm_518].subname == 0)
        {
            s_ += lang(u8"カスタム"s, ""s);
        }
        else
        {
            s_ += lang(
                u8"《"s + rpname(inv[prm_518].subname) + u8"》の"s,
                u8" of <"s + rpname(inv[prm_518].subname) + u8">"s);
        }
    }
    if (a_ == 55000)
    {
        if (inv[prm_518].id == 563)
        {
            s_ += lang(
                u8"《"s
                    + i18n::_(
                          u8"ability",
                          std::to_string(inv[prm_518].param1),
                          u8"name")
                    + u8"》という題名の"s,
                u8" titled <Art of "s
                    + i18n::_(
                          u8"ability",
                          std::to_string(inv[prm_518].param1),
                          u8"name")
                    + u8">"s);
        }
        else if (inv[prm_518].id == 668)
        {
            s_ += lang(u8"第"s, u8" of Rachel No."s) + inv[prm_518].param2
                + lang(u8"巻目の"s, ""s);
        }
        else if (inv[prm_518].id == 24)
        {
            s_ += lang(
                u8"《"s + booktitle(inv[prm_518].param1) + u8"》という題名の"s,
                u8" titled <"s + booktitle(inv[prm_518].param1) + u8">"s);
        }
    }
    if (a_ == 60002)
    {
        if (inv[prm_518].param1 != 0)
        {
            s_ += lang(
                i18n::_(
                    u8"god", core_god::int2godid(inv[prm_518].param1), u8"name")
                    + u8"の"s,
                u8" <"s
                    + i18n::_(
                          u8"god",
                          core_god::int2godid(inv[prm_518].param1),
                          u8"name")
                    + u8">"s);
        }
    }
    if (a_ == 57000)
    {
        if (inv[prm_518].param1 != 0)
        {
            if (inv[prm_518].param2 != 0)
            {
                skip_ = 1;
                if (inv[prm_518].id == 618)
                {
                    s_ = s_
                        + foodname(
                              inv[prm_518].param1 / 1000,
                              i18n::_(
                                  u8"fish",
                                  std::to_string(inv[prm_518].subname),
                                  u8"name"),
                              inv[prm_518].param2,
                              inv[prm_518].subname);
                }
                else
                {
                    s_ = s_
                        + foodname(
                              inv[prm_518].param1 / 1000,
                              ioriginalnameref(inv[prm_518].id),
                              inv[prm_518].param2,
                              inv[prm_518].subname);
                }
                return;
            }
        }
        if (inv[prm_518].own_state == 4)
        {
            s_ += lang(""s, u8" grown "s)
                + i18n::_(u8"ui", u8"weight", u8"_"s + inv[prm_518].subname)
                + lang(u8"育った"s, ""s);
        }
    }
    if (inv[prm_518].subname != 0)
    {
        if (inv[prm_518].id == 618 || inv[prm_518].id == 619)
        {
            if (inv[prm_518].subname < 0 || inv[prm_518].subname >= 100)
            {
                s_ += u8"/bugged/"s;
                return;
            }
            s_ += i18n::_(
                u8"fish", std::to_string(inv[prm_518].subname), u8"name");
        }
        else if (
            a_ == 57000 || a_ == 62000 || inv[prm_518].id == 503
            || inv[prm_518].id == 504 || inv[prm_518].id == 575
            || inv[prm_518].id == 574)
        {
            if (inv[prm_518].subname < 0 || inv[prm_518].subname >= 800)
            {
                s_ += u8"/bugged/"s;
                return;
            }
            if (inv[prm_518].own_state != 4)
            {
                s_ += lang(""s, u8" of "s)
                    + chara_refstr(inv[prm_518].subname, 2);
                if (jp)
                {
                    s_ += u8"の"s;
                }
            }
        }
        if (a_ == 60000)
        {
            if (jp)
            {
                if (inv[prm_518].subname >= 12)
                {
                    inv[prm_518].subname = 0;
                }
                else
                {
                    s_ += i18n::_(
                        u8"ui", u8"furniture", u8"_"s + inv[prm_518].subname);
                }
            }
        }
        if (inv[prm_518].id == 344)
        {
            s_ += lang(""s, u8" of "s)
                + i18n::_(u8"ui", u8"home", u8"_"s + inv[prm_518].param1)
                + lang(u8"の"s, ""s);
        }
        if (inv[prm_518].id == 615)
        {
            s_ += lang(
                ""s + inv[prm_518].subname + u8"goldの"s,
                u8" <"s + inv[prm_518].subname + u8" gp>"s);
        }
        if (inv[prm_518].id == 704)
        {
            if (inv[prm_518].subname < 0 || inv[prm_518].subname >= 800)
            {
                s_ += u8"/bugged/"s;
                return;
            }
            s_ += lang(
                ""s + chara_refstr(inv[prm_518].subname, 2) + u8"の"s,
                u8" of "s + chara_refstr(inv[prm_518].subname, 2));
        }
    }
    if (inv[prm_518].id == 672)
    {
        if (inv[prm_518].param1 == 169)
        {
            s_ += lang(u8"善人の"s, u8" of saint"s);
        }
        if (inv[prm_518].param1 == 162)
        {
            s_ += lang(u8"悪人の"s, u8" of wicked"s);
        }
        if (inv[prm_518].param1 == 163)
        {
            s_ += lang(u8"エヘカトルの"s, u8" of Ehekatl"s);
        }
        if (inv[prm_518].param1 == 164)
        {
            s_ += lang(u8"オパートスの"s, u8" of Opatos"s);
        }
        if (inv[prm_518].param1 == 165)
        {
            s_ += lang(u8"イツパロトルの"s, u8" of Itzpalt"s);
        }
        if (inv[prm_518].param1 == 166)
        {
            s_ += lang(u8"ジュアの"s, u8" of Jure"s);
        }
    }
    return;
}



std::string itemname(int prm_518, int prm_519, int prm_520)
{
    elona_vector1<int> iqiality_;
    int num2_ = 0;
    std::string s2_;
    std::string s3_;
    int alpha_ = 0;
    std::string s4_;
    int len_ = 0;
    elona_vector1<std::string> buf_;
    elona::prm_518 = prm_518;
    if (inv[prm_518].id >= maxitemid - 2
        || size_t(inv[prm_518].id) > length(ioriginalnameref))
    {
        return lang(
            u8"未知のアイテム(バージョン非互換)"s,
            u8"unknown item (incompatible version)"s);
    }
    if (inv[prm_518].quality >= 5)
    {
        iqiality_(prm_518) = 5;
    }
    item_checkknown(prm_518);
    if (prm_519 == 0)
    {
        num2_ = inv[prm_518].number;
    }
    else
    {
        num2_ = prm_519;
    }
    a_ = the_item_db[inv[prm_518].id]->category;
    if (jp)
    {
        if (num2_ > 1)
        {
            s2_ = u8"個の"s;
            if (a_ == 16000)
            {
                s2_ = u8"着の"s;
            }
            if (a_ == 54000 || a_ == 55000)
            {
                if (inv[prm_518].id == 783)
                {
                    s2_ = u8"枚の"s;
                }
                else
                {
                    s2_ = u8"冊の"s;
                }
            }
            if (a_ == 10000)
            {
                s2_ = u8"本の"s;
            }
            if (a_ == 52000)
            {
                s2_ = u8"服の"s;
            }
            if (a_ == 53000)
            {
                s2_ = u8"巻の"s;
            }
            if (a_ == 22000 || a_ == 18000)
            {
                s2_ = u8"対の"s;
            }
            if (a_ == 68000 || a_ == 69000 || inv[prm_518].id == 622
                || inv[prm_518].id == 724 || inv[prm_518].id == 730)
            {
                s2_ = u8"枚の"s;
            }
            if (inv[prm_518].id == 618)
            {
                s2_ = u8"匹の"s;
            }
            s_ = ""s + num2_ + s2_;
        }
        else
        {
            s_ = "";
        }
        if (inv[prm_518].identification_state
            == identification_state_t::completely_identified)
        {
            switch (inv[prm_518].curse_state)
            {
            case curse_state_t::doomed:
                s_ += i18n::_(u8"ui", u8"doomed");
                break;
            case curse_state_t::cursed:
                s_ += i18n::_(u8"ui", u8"cursed");
                break;
            case curse_state_t::none: break;
            case curse_state_t::blessed:
                s_ += i18n::_(u8"ui", u8"blessed");
                break;
            }
        }
    }
    else
    {
        s_ = "";
        if (inv[prm_518].identification_state
            == identification_state_t::completely_identified)
        {
            switch (inv[prm_518].curse_state)
            {
            case curse_state_t::doomed:
                s_ = i18n::_(u8"ui", u8"doomed") + u8" "s;
                break;
            case curse_state_t::cursed:
                s_ = i18n::_(u8"ui", u8"cursed") + u8" "s;
                break;
            case curse_state_t::none: break;
            case curse_state_t::blessed:
                s_ = i18n::_(u8"ui", u8"blessed") + u8" "s;
                break;
            }
        }
        if (irandomname(inv[prm_518].id) == 1
            && inv[prm_518].identification_state
                == identification_state_t::unidentified)
        {
            s2_ = "";
        }
        else
        {
            s2_ = ""s + ioriginalnameref2(inv[prm_518].id);
            if (strutil::contains(ioriginalnameref(inv[prm_518].id), u8"with"))
            {
                s3_ = u8"with"s;
            }
            else
            {
                s3_ = u8"of"s;
            }
            if (inv[prm_518].identification_state
                    != identification_state_t::unidentified
                && s2_ == ""s)
            {
                if (inv[prm_518].weight < 0)
                {
                    s2_ = u8"cargo"s;
                }
                if (a_ == 22000 || a_ == 18000)
                {
                    s2_ = u8"pair"s;
                }
            }
            if (a_ == 57000 && inv[prm_518].param1 != 0
                && inv[prm_518].param2 != 0)
            {
                s2_ = u8"dish"s;
            }
        }
        if (s2_ != ""s)
        {
            if (num2_ > 1)
            {
                s_ = ""s + num2_ + u8" "s + s_ + s2_ + u8"s "s + s3_ + u8" "s;
            }
            else
            {
                s_ = s_ + s2_ + u8" "s + s3_ + u8" "s;
            }
        }
        else if (num2_ > 1)
        {
            s_ = ""s + num2_ + u8" "s + s_;
        }
    }
    if (inv[prm_518].material == 35 && inv[prm_518].param3 < 0)
    {
        if (jp)
        {
            s_ += u8"腐った"s;
        }
        else
        {
            s_ += u8"rotten "s;
        }
    }
    if (en)
    {
        if (a_ == 57000 && inv[prm_518].param1 != 0 && inv[prm_518].param2 != 0)
        {
            skip_ = 1;
        }
        if (inv[prm_518].subname != 0 && a_ == 60000)
        {
            if (inv[prm_518].subname >= 12)
            {
                inv[prm_518].subname = 0;
            }
            else
            {
                s_ += i18n::_(
                          u8"ui", u8"furniture", u8"_"s + inv[prm_518].subname)
                    + u8" "s;
            }
        }
        if (inv[prm_518].id == 687 && inv[prm_518].param2 != 0)
        {
            s_ += u8"undecoded "s;
        }
        if (inv[prm_518].id == 783 && inv[prm_518].subname == 0)
        {
            s_ += u8"custom "s;
        }
    }
    if (inv[prm_518].id == 630)
    {
        s_ += ""s
            + i18n::_(
                  u8"item_material",
                  std::to_string(inv[prm_518].material),
                  u8"name")
            + lang(u8"製の"s, u8" "s);
    }
    if (jp)
    {
        itemname_additional_info();
    }
    if (a_ == 60000 && inv[prm_518].material != 0)
    {
        if (jp)
        {
            s_ += ""s
                + i18n::_(
                      u8"item_material",
                      std::to_string(inv[prm_518].material),
                      u8"name")
                + u8"細工の"s;
        }
        else
        {
            s_ += ""s
                + i18n::_(
                      u8"item_material",
                      std::to_string(inv[prm_518].material),
                      u8"name")
                + u8"work "s;
        }
    }
    if (inv[prm_518].id == 729)
    {
        s_ += ""s + giftn(inv[prm_518].param4) + lang(""s, u8" "s);
    }
    if (skip_ == 1)
    {
        goto label_0313_internal;
    }
    alpha_ = 0;
    if (inv[prm_518].identification_state
            == identification_state_t::completely_identified
        && a_ < 50000)
    {
        if (ibit(15, prm_518))
        {
            alpha_ = 1;
            s_ += lang(u8"エターナルフォース"s, u8"eternal force"s) + strblank;
        }
        else
        {
            if (inv[prm_518].subname >= 10000)
            {
                if (inv[prm_518].subname < 20000)
                {
                    if (jp)
                    {
                        s_ += egoname(inv[prm_518].subname - 10000) + strblank;
                    }
                }
                else if (inv[prm_518].subname < 40000)
                {
                    s_ += egominorn(inv[prm_518].subname - 20000) + strblank;
                }
            }
            if (inv[prm_518].quality != 6)
            {
                if (inv[prm_518].quality >= 4)
                {
                    s_ += i18n::_(
                              u8"item_material",
                              std::to_string(inv[prm_518].material),
                              u8"alias")
                        + strblank;
                }
                else
                {
                    s_ += i18n::_(
                              u8"item_material",
                              std::to_string(inv[prm_518].material),
                              u8"name")
                        + strblank;
                    if (jp)
                    {
                        if (/* TODO is_katakana */ false)
                        {
                            alpha_ = 1;
                        }
                        else
                        {
                            s_ += u8"の"s;
                        }
                    }
                }
            }
        }
    }
    if (inv[prm_518].identification_state
        == identification_state_t::unidentified)
    {
        s_ += iknownnameref(inv[prm_518].id);
    }
    else if (
        inv[prm_518].identification_state
        != identification_state_t::completely_identified)
    {
        if (inv[prm_518].quality < 4 || a_ >= 50000)
        {
            s_ += ioriginalnameref(inv[prm_518].id);
        }
        else
        {
            s_ += iknownnameref(inv[prm_518].id);
        }
    }
    else if (inv[prm_518].quality == 6 || ibit(5, prm_518) == 1)
    {
        if (jp)
        {
            s_ = u8"★"s + s_ + ioriginalnameref(inv[prm_518].id);
        }
        else
        {
            s_ += ioriginalnameref(inv[prm_518].id);
        }
    }
    else
    {
        if (inv[prm_518].quality >= 4 && jp)
        {
            s_ = u8"☆"s + s_;
        }
        if (alpha_ == 1 && jp)
        {
            s_ += ialphanameref(inv[prm_518].id);
        }
        else
        {
            s_ += ioriginalnameref(inv[prm_518].id);
        }
        if (en && a_ < 50000 && inv[prm_518].subname >= 10000
            && inv[prm_518].subname < 20000)
        {
            s_ += u8" "s + egoname((inv[prm_518].subname - 10000));
        }
        if (inv[prm_518].subname >= 40000)
        {
            randomize(inv[prm_518].subname - 40000);
            if (inv[prm_518].quality == 4)
            {
                s_ += lang(u8"『"s, u8" <"s) + random_title(1)
                    + lang(u8"』"s, u8">"s);
            }
            else
            {
                s_ += lang(u8"《"s, u8" {"s) + random_title(1)
                    + lang(u8"》"s, u8"}"s);
            }
            randomize();
        }
    }
label_0313_internal:
    if (en)
    {
        if (prm_520 == 0)
        {
            if (inv[prm_518].identification_state
                    == identification_state_t::completely_identified
                && (inv[prm_518].quality >= 4 && a_ < 50000))
            {
                s_ = u8"the "s + s_;
            }
            else if (num2_ == 1)
            {
                s4_ = strmid(s_, 0, 1);
                if (s4_ == u8"a"s || s4_ == u8"o"s || s4_ == u8"i"s
                    || s4_ == u8"u"s || s4_ == u8"e"s)
                {
                    s_ = u8"an "s + s_;
                }
                else
                {
                    s_ = u8"a "s + s_;
                }
            }
        }
        if (s2_ == ""s && inv[prm_518].id != 618 && num2_ > 1)
        {
            s_ += u8"s"s;
        }
        itemname_additional_info();
    }
    if (inv[prm_518].identification_state
        == identification_state_t::completely_identified)
    {
        if (inv[prm_518].enhancement != 0)
        {
            s_ += ""s + cnvfix(inv[prm_518].enhancement) + u8" "s;
        }
        if (ibit(4, prm_518) == 1)
        {
            s_ += lang(
                u8"(残り"s + inv[prm_518].count + u8"回)"s,
                u8"(Charges: "s + inv[prm_518].count + u8")"s);
        }
        if (inv[prm_518].dice_x != 0 || inv[prm_518].hit_bonus != 0
            || inv[prm_518].damage_bonus != 0)
        {
            s_ += u8" ("s;
            if (inv[prm_518].dice_x != 0)
            {
                s_ += ""s + inv[prm_518].dice_x + u8"d"s + inv[prm_518].dice_y;
                if (inv[prm_518].damage_bonus != 0)
                {
                    if (inv[prm_518].damage_bonus > 0)
                    {
                        s_ += u8"+"s + inv[prm_518].damage_bonus;
                    }
                    else
                    {
                        s_ += ""s + inv[prm_518].damage_bonus;
                    }
                }
                s_ += u8")"s;
                if (inv[prm_518].hit_bonus != 0)
                {
                    s_ += u8"("s + inv[prm_518].hit_bonus + u8")"s;
                }
            }
            else
            {
                s_ += ""s + inv[prm_518].hit_bonus + u8","s
                    + inv[prm_518].damage_bonus + u8")"s;
            }
        }
        if (inv[prm_518].dv != 0 || inv[prm_518].pv != 0)
        {
            s_ += u8" ["s + inv[prm_518].dv + u8","s + inv[prm_518].pv + u8"]"s;
        }
    }
    if (en && (inv[prm_518].id == 284 || inv[prm_518].id == 283))
    {
        s_ += u8"(Lost property)"s;
    }
    if (inv[prm_518].id == 342 && inv[prm_518].count != 0)
    {
        s_ += lang(
            u8"("s + biten(inv[prm_518].param4) + u8"残り"s + inv[prm_518].count
                + u8"匹)"s,
            u8"("s + inv[prm_518].count + u8" "s + biten(inv[prm_518].param4)
                + u8")"s);
    }
    if (inv[prm_518].id == 685)
    {
        if (inv[prm_518].subname == 0)
        {
            s_ += lang(u8" Lv"s, u8" Level "s) + inv[prm_518].param2
                + lang(u8" (空)"s, u8"(Empty)"s);
        }
        else
        {
            s_ += u8" ("s + chara_refstr(inv[prm_518].subname, 2) + u8")"s;
        }
    }
    if (inv[prm_518].id == 734)
    {
        s_ += lang(u8" Lv"s, u8" Level "s) + inv[prm_518].param2;
    }
    if (inv[prm_518].identification_state
            == identification_state_t::almost_identified
        && a_ < 50000)
    {
        s_ += u8" ("s
            + cnven(i18n::_(u8"ui", u8"quality", u8"_"s + inv[prm_518].quality))
            + u8")"s;
        if (jp)
        {
            s_ += u8"["s
                + i18n::_(
                      u8"item_material",
                      std::to_string(inv[prm_518].material),
                      u8"name")
                + u8"製]"s;
        }
        else
        {
            s_ += u8"["s
                + cnven(i18n::_(
                      u8"item_material",
                      std::to_string(inv[prm_518].material),
                      u8"name"))
                + u8"]"s;
        }
        if (inv[prm_518].curse_state == curse_state_t::cursed)
        {
            s_ += lang(u8"(恐ろしい)"s, u8"(Scary)"s);
        }
        if (inv[prm_518].curse_state == curse_state_t::doomed)
        {
            s_ += lang(u8"(禍々しい)"s, u8"(Dreadful)"s);
        }
    }
    if (a_ == 72000)
    {
        if (inv[prm_518].id == 361)
        {
            s_ += lang(u8"(移動時消滅)"s, u8"(Temporal)"s);
        }
        else if (inv[prm_518].count == 0)
        {
            if (inv[prm_518].param1 == 0)
            {
                s_ += lang(u8"(空っぽ)"s, u8"(Empty)"s);
            }
        }
    }
    if (a_ == 92000 && inv[prm_518].param2 != 0)
    {
        s_ += lang(
            u8"(仕入れ値 "s + inv[prm_518].param2 + u8"g)"s,
            u8"(Buying price: "s + inv[prm_518].param2 + u8")"s);
    }
    if (ibit(6, prm_518) == 1)
    {
        s_ += lang(u8"(媚薬混入)"s, u8"(Aphrodisiac)"s);
    }
    if (ibit(14, prm_518) == 1)
    {
        s_ += lang(u8"(毒物混入)"s, u8"(Poisoned)"s);
    }
    if (ibit(7, prm_518) == 1
        && gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
                + gdata_year * 24 * 30 * 12
            < inv[prm_518].count)
    {
        s_ += lang(
            u8"("s
                + (inv[prm_518].count
                   - (gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
                      + gdata_year * 24 * 30 * 12))
                + u8"時間)"s,
            u8"(Next: "s
                + (inv[prm_518].count
                   - (gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
                      + gdata_year * 24 * 30 * 12))
                + u8"h.)"s);
    }
    if (inv[prm_518].id == 555 && inv[prm_518].count != 0)
    {
        s_ += lang(u8" シリアルNo."s, u8" serial no."s) + inv[prm_518].count;
    }
    if (inv[prm_518].id == 544)
    {
        s_ += u8" <BGM"s + inv[prm_518].param1 + u8">"s;
    }
    if (strlen_u(s_) > 66)
    {
        len_ = zentohan(s_, buf_, 0);
        SDIM2(buf_, len_);
        zentohan(s_, s_, len_);
    }
    skip_ = 0;
    return s_;
}



void remain_make(int ci, int cc)
{
    inv[ci].subname = cdata[cc].id;
    inv[ci].color = cdata[cc].image / 1000;
    inv[ci].weight = cdata[cc].weight;

    if (inv[ci].id == 204)
    {
        inv[ci].weight = 250 * (inv[ci].weight + 100) / 100 + 500;
        inv[ci].value = inv[ci].weight / 5;
    }
    else
    {
        inv[ci].weight = 20 * (inv[ci].weight + 500) / 500;
        inv[ci].value = cdata[cc].level * 40 + 600;
        if (the_character_db[cdata[cc].id]->rarity / 1000 < 20
            && cdata[cc].original_relationship < -1)
        {
            inv[ci].value = inv[ci].value
                * clamp(4 - the_character_db[cdata[cc].id]->rarity / 1000 / 5,
                        1,
                        5);
        }
    }
}


int item_stack(int inventory_id, int ci, int show_message)
{
    if (inv[ci].quality == 6 && the_item_db[inv[ci].id]->category < 50000)
    {
        return 0;
    }

    bool did_stack = false;

    for (const auto& i : items(inventory_id))
    {
        if (i == ci || inv[i].number == 0 || inv[i].id != inv[ci].id)
            continue;

        bool stackable;
        if (inv[i].id == 622)
            stackable = inventory_id != -1 || mode == 6
                || inv[i].position == inv[ci].position;
        else
            stackable =
                inv[i].almost_equals(inv[ci], inventory_id != -1 || mode == 6);

        if (stackable)
        {
            inv[i].number += inv[ci].number;
            item_remove(inv[ci]);
            ti = i;
            did_stack = true;
            break;
        }
    }

    if (did_stack)
    {
        if (mode != 6 && inv_getowner(ci) == -1)
        {
            cell_refresh(inv[ci].position.x, inv[ci].position.y);
        }
        if (show_message)
        {
            txt(lang(
                itemname(ti, 1) + u8"をまとめた(計"s + inv[ti].number
                    + u8"個) "s,
                itemname(ti, 1) + u8" has been stacked. (Total:"s
                    + inv[ti].number + u8")"s));
        }
    }

    return did_stack;
}

void item_acid(int prm_838, int prm_839)
{
    int body_at_m138 = 0;
    if (prm_839 != -1)
    {
        ci_at_m138 = prm_839;
    }
    else
    {
        ci_at_m138 = -1;
        for (int i = 0; i < 30; ++i)
        {
            body_at_m138 = cdata_body_part(prm_838, i) / 10000;
            if (body_at_m138 == 0)
            {
                break;
            }
            p_at_m138 = cdata_body_part(prm_838, i) % 10000 - 1;
            if (p_at_m138 == -1)
            {
                continue;
            }
            if (rnd(clamp(30, 1, 30)) == 0)
            {
                if (inv[p_at_m138].enhancement > -4)
                {
                    ci_at_m138 = p_at_m138;
                    break;
                }
            }
        }
    }
    if (ci_at_m138 == -1)
    {
        return;
    }
    if (the_item_db[inv[ci_at_m138].id]->category >= 50000)
    {
        return;
    }
    if (ibit(1, ci_at_m138) == 0)
    {
        txtef(8);
        txt(lang(
            name(prm_838) + u8"の"s + itemname(ci_at_m138)
                + u8"は酸で傷ついた。"s,
            name(prm_838) + your(prm_838) + u8" "s + itemname(ci_at_m138, 0, 1)
                + u8" is damaged by acid."s));
        --inv[ci_at_m138].enhancement;
    }
    else
    {
        txt(lang(
            name(prm_838) + u8"の"s + itemname(ci_at_m138)
                + u8"は酸では傷つかない。"s,
            name(prm_838) + your(prm_838) + u8" "s + itemname(ci_at_m138, 0, 1)
                + u8" is immune to acid."s));
    }
    return;
}



int item_fire(int prm_840, int prm_841)
{
    max_at_m138 = 0;
    ti_at_m138 = -1;
    if (prm_841 != -1)
    {
        list_at_m138(0) = prm_841;
        ++max_at_m138;
    }
    if (prm_840 != -1)
    {
        if (sdata(50, prm_840) / 50 >= 6 || cdata[prm_840].quality >= 4)
        {
            return 0;
        }
        for (const auto& cnt : items(prm_840))
        {
            if (inv[cnt].number == 0)
            {
                continue;
            }
            if (inv[cnt].id == 567)
            {
                if (ti_at_m138 == -1)
                {
                    ti_at_m138 = cnt;
                    item_separate(ti_at_m138);
                }
                continue;
            }
            if (prm_841 == -1)
            {
                list_at_m138(max_at_m138) = cnt;
                ++max_at_m138;
            }
        }
    }
    if (max_at_m138 == 0)
    {
        return 0;
    }
    f_at_m138 = 0;
    for (int cnt = 0; cnt < 3; ++cnt)
    {
        ci_at_m138 = list_at_m138(rnd(max_at_m138));
        if (inv[ci_at_m138].number <= 0)
        {
            continue;
        }
        rowact_item(ci_at_m138);
        if (ibit(2, ci_at_m138) == 0)
        {
            if (ibit(5, ci_at_m138) == 0)
            {
                a_at_m138 = the_item_db[inv[ci_at_m138].id]->category;
                if (a_at_m138 == 57000)
                {
                    if (inv[ci_at_m138].param2 == 0)
                    {
                        if (prm_840 == -1)
                        {
                            if (is_in_fov(inv[ci_at_m138].position))
                            {
                                txtef(11);
                                txt(lang(
                                    u8"地面の"s
                                        + itemname(
                                              ci_at_m138,
                                              inv[ci_at_m138].number)
                                        + u8"はこんがりと焼き上がった。"s,
                                    itemname(ci_at_m138, inv[ci_at_m138].number)
                                        + u8" on the ground get"s
                                        + _s2(inv[ci_at_m138].number)
                                        + u8" perfectly broiled."s));
                            }
                        }
                        if (prm_840 != -1)
                        {
                            if (is_in_fov(prm_840))
                            {
                                txtef(11);
                                txt(lang(
                                    name(prm_840) + u8"の"s
                                        + itemname(
                                              ci_at_m138,
                                              inv[ci_at_m138].number)
                                        + u8"はこんがりと焼き上がった。"s,
                                    name(prm_840) + your(prm_840) + u8" "s
                                        + itemname(
                                              ci_at_m138,
                                              inv[ci_at_m138].number,
                                              1)
                                        + u8" get"s
                                        + _s2(inv[ci_at_m138].number)
                                        + u8" perfectly broiled."s));
                            }
                        }
                        make_dish(ci_at_m138, rnd(5) + 1);
                        f_at_m138 = 1;
                        continue;
                    }
                }
                if (a_at_m138 == 72000 || a_at_m138 == 59000
                    || a_at_m138 == 68000 || inv[ci_at_m138].quality >= 4)
                {
                    continue;
                }
                if (inv[ci_at_m138].body_part != 0)
                {
                    if (rnd(2))
                    {
                        continue;
                    }
                }
                if (a_at_m138 != 56000 && a_at_m138 != 80000
                    && a_at_m138 != 55000 && a_at_m138 != 53000
                    && a_at_m138 != 54000)
                {
                    if (rnd(4))
                    {
                        continue;
                    }
                    if (prm_840 != -1)
                    {
                        if (rnd(4))
                        {
                            continue;
                        }
                    }
                }
                if (ti_at_m138 != -1)
                {
                    if (inv[ti_at_m138].number > 0)
                    {
                        if (is_in_fov(prm_840))
                        {
                            txt(lang(
                                itemname(ti_at_m138, 1) + u8"が"s
                                    + name(prm_840)
                                    + u8"の持ち物を炎から守った。"s,
                                itemname(ti_at_m138, 1) + u8" protects "s
                                    + name(prm_840) + your(prm_840)
                                    + u8" stuff from fire."s));
                        }
                        if (inv[ti_at_m138].count > 0)
                        {
                            --inv[ti_at_m138].count;
                        }
                        else if (rnd(20) == 0)
                        {
                            --inv[ti_at_m138].number;
                            if (is_in_fov(prm_840))
                            {
                                txt(lang(
                                    itemname(ti_at_m138, 1)
                                        + u8"は灰と化した。"s,
                                    itemname(ti_at_m138, 1)
                                        + u8" turns to dust."s));
                                break;
                            }
                        }
                        continue;
                    }
                }
                p_at_m138 = rnd(inv[ci_at_m138].number) / 2 + 1;
                if (prm_840 != -1)
                {
                    if (inv[ci_at_m138].body_part != 0)
                    {
                        if (is_in_fov(prm_840))
                        {
                            txtef(8);
                            txt(lang(
                                name(prm_840) + u8"の装備している"s
                                    + itemname(ci_at_m138, p_at_m138)
                                    + u8"は灰と化した。"s,
                                itemname(ci_at_m138, p_at_m138) + u8" "s
                                    + name(prm_840) + u8" equip"s + _s(prm_840)
                                    + u8" turn"s + _s2(p_at_m138)
                                    + u8" to dust."s));
                        }
                        cdata_body_part(prm_840, inv[ci_at_m138].body_part) =
                            cdata_body_part(prm_840, inv[ci_at_m138].body_part)
                            / 10000 * 10000;
                        inv[ci_at_m138].body_part = 0;
                        chara_refresh(prm_840);
                    }
                    else if (is_in_fov(prm_840))
                    {
                        txtef(8);
                        txt(lang(
                            name(prm_840) + u8"の"s
                                + itemname(ci_at_m138, p_at_m138)
                                + u8"は灰と化した。"s,
                            name(prm_840) + your(prm_840) + u8" "s
                                + itemname(ci_at_m138, p_at_m138, 1)
                                + u8" turn"s + _s2(p_at_m138)
                                + u8" to dust."s));
                    }
                }
                else if (is_in_fov(inv[ci_at_m138].position))
                {
                    txtef(8);
                    txt(lang(
                        u8"地面の"s + itemname(ci_at_m138, p_at_m138)
                            + u8"は灰と化した。"s,
                        itemname(ci_at_m138, p_at_m138)
                            + u8" on the ground turn"s + _s(p_at_m138)
                            + u8" to dust."s));
                }
                inv[ci_at_m138].number -= p_at_m138;
                cell_refresh(
                    inv[ci_at_m138].position.x, inv[ci_at_m138].position.y);
                f_at_m138 = 1;
            }
        }
    }
    refresh_burden_state();
    return f_at_m138;
}

int item_cold(int prm_844, int prm_845)
{
    std::string s_at_m138;
    max_at_m138 = 0;
    ti_at_m138 = -1;
    if (prm_845 != -1)
    {
        list_at_m138(0) = prm_845;
        ++max_at_m138;
    }
    if (prm_844 != -1)
    {
        if (sdata(51, prm_844) / 50 >= 6 || cdata[prm_844].quality >= 4)
        {
            return 0;
        }
        for (const auto& cnt : items(prm_844))
        {
            if (inv[cnt].number == 0)
            {
                continue;
            }
            if (inv[cnt].id == 568)
            {
                if (ti_at_m138 == -1)
                {
                    ti_at_m138 = cnt;
                    item_separate(ti_at_m138);
                }
                continue;
            }
            if (prm_845 == -1)
            {
                list_at_m138(max_at_m138) = cnt;
                ++max_at_m138;
            }
        }
    }
    if (max_at_m138 == 0)
    {
        return 0;
    }
    f_at_m138 = 0;
    for (int cnt = 0; cnt < 2; ++cnt)
    {
        ci_at_m138 = list_at_m138(rnd(max_at_m138));
        if (inv[ci_at_m138].number <= 0)
        {
            continue;
        }
        rowact_item(ci_at_m138);
        if (ibit(5, ci_at_m138) == 0)
        {
            a_at_m138 = the_item_db[inv[ci_at_m138].id]->category;
            if (prm_844 == -1)
            {
                s_at_m138 = "";
            }
            else
            {
                s_at_m138 = name(prm_844) + lang(u8"の"s, your(prm_844));
            }
            if (a_at_m138 == 72000 || a_at_m138 == 59000 || a_at_m138 == 68000)
            {
                continue;
            }
            if (inv[ci_at_m138].quality >= 4 || inv[ci_at_m138].body_part != 0)
            {
                continue;
            }
            if (a_at_m138 != 52000)
            {
                if (rnd(30))
                {
                    continue;
                }
            }
            if (ti_at_m138 != -1)
            {
                if (inv[ti_at_m138].number > 0)
                {
                    txt(lang(
                        itemname(ti_at_m138, 1) + u8"が"s + name(prm_844)
                            + u8"の持ち物を冷気から守った。"s,
                        itemname(ti_at_m138, 1) + u8" protects "s
                            + name(prm_844) + your(prm_844)
                            + u8" stuff from cold."s));
                    if (inv[ti_at_m138].count > 0)
                    {
                        --inv[ti_at_m138].count;
                    }
                    else if (rnd(20) == 0)
                    {
                        txt(lang(
                            itemname(ti_at_m138, 1) + u8"は粉々に砕けた。"s,
                            itemname(ti_at_m138, 1)
                                + u8" is broken to pieces."s));
                        --inv[ti_at_m138].number;
                        break;
                    }
                    continue;
                }
            }
            p_at_m138 = rnd(inv[ci_at_m138].number) / 2 + 1;
            txtef(8);
            txt(lang(
                s_at_m138 + itemname(ci_at_m138, p_at_m138)
                    + u8"は粉々に砕けた。"s,
                s_at_m138 + itemname(ci_at_m138, p_at_m138) + u8" break"s
                    + _s2(p_at_m138) + u8" to pieces."s));
            inv[ci_at_m138].number -= p_at_m138;
            f_at_m138 = 1;
        }
    }
    refresh_burden_state();
    return f_at_m138;
}

void mapitem_fire(int prm_842, int prm_843)
{
    if (map(prm_842, prm_843, 4) == 0)
    {
        return;
    }
    ci_at_m138 = -1;
    for (const auto& cnt : items(-1))
    {
        if (inv[cnt].number == 0)
        {
            continue;
        }
        if (inv[cnt].position.x == prm_842)
        {
            if (inv[cnt].position.y == prm_843)
            {
                ci_at_m138 = cnt;
                break;
            }
        }
    }
    if (ci_at_m138 != -1)
    {
        int stat = item_fire(-1, ci_at_m138);
        if (stat == 1)
        {
            if (map(prm_842, prm_843, 8) == 0)
            {
                mef_add(prm_842, prm_843, 5, 24, rnd(10) + 5, 100, cc);
            }
        }
        cell_refresh(prm_842, prm_843);
    }
    return;
}

void mapitem_cold(int prm_846, int prm_847)
{
    if (map(prm_846, prm_847, 4) == 0)
    {
        return;
    }
    ci_at_m138 = -1;
    for (const auto& cnt : items(-1))
    {
        if (inv[cnt].number == 0)
        {
            continue;
        }
        if (inv[cnt].position.x == prm_846)
        {
            if (inv[cnt].position.y == prm_847)
            {
                ci_at_m138 = cnt;
                break;
            }
        }
    }
    if (ci_at_m138 != -1)
    {
        item_cold(-1, ci_at_m138);
        cell_refresh(prm_846, prm_847);
    }
    return;
}



int get_random_inv(int owner)
{
    const auto tmp = inv_getheader(owner);
    return tmp.first + rnd(tmp.second);
}

std::pair<int, int> inv_getheader(int owner)
{
    if (owner == 0)
    {
        return {0, 200};
    }
    else if (owner == -1)
    {
        return {5080, 400};
    }
    else
    {
        return {200 + 20 * (owner - 1), 20};
    }
}



int inv_getowner(int inv_id)
{
    if (inv_id < 200)
    {
        return 0;
    }
    if (inv_id >= 5080)
    {
        return -1;
    }
    return (inv_id - 200) / 20 + 1;
}



int inv_find(int id, int owner)
{
    for (const auto& cnt : items(owner))
    {
        if (inv[cnt].number == 0)
        {
            continue;
        }
        if (inv[cnt].id == id)
        {
            return cnt;
        }
    }
    return -1; // Not found
}

bool inv_getspace(int owner)
{
    for (const auto& cnt : items(owner))
    {
        if (inv[cnt].number == 0)
        {
            return true;
        }
    }
    return false;
}

int inv_sum(int owner)
{
    int n{};
    for (const auto& cnt : items(owner))
    {
        if (inv[cnt].number != 0)
        {
            ++n;
        }
    }
    return n;
}

int inv_compress(int owner)
{
    int number_of_deleted_items{};
    for (int i = 0; i < 100; ++i)
    {
        int threshold = 200 * (i * i + 1);
        for (const auto& cnt : items(owner))
        {
            if (inv[cnt].number != 0)
            {
                if (!ibit(5, cnt) && inv[cnt].value < threshold)
                {
                    item_remove(inv[cnt]);
                    ++number_of_deleted_items;
                    if (inv[cnt].position.x >= 0
                        && inv[cnt].position.x < mdata(0)
                        && inv[cnt].position.y >= 0
                        && inv[cnt].position.y < mdata(1))
                    {
                        cell_refresh(inv[cnt].position.x, inv[cnt].position.y);
                    }
                }
            }
            if (number_of_deleted_items > 10)
            {
                break;
            }
        }
        if (number_of_deleted_items > 10)
        {
            break;
        }
    }

    int slot = -1;
    for (const auto& cnt : items(owner))
    {
        if (inv[cnt].number == 0)
        {
            slot = cnt;
            break;
        }
    }

    if (slot == -1)
    {
        // Destroy 1 existing item forcely.
        slot = get_random_inv(owner);
        item_remove(inv[slot]);
        if (mode != 6)
        {
            if (inv[slot].position.x >= 0 && inv[slot].position.x < mdata(0)
                && inv[slot].position.y >= 0 && inv[slot].position.y < mdata(1))
            {
                cell_refresh(inv[slot].position.x, inv[slot].position.y);
            }
        }
    }

    return slot;
}

int inv_getfreeid(int owner)
{
    for (const auto& cnt : items(owner))
    {
        if (inv[cnt].number == 0)
        {
            return cnt;
        }
    }
    if (owner == -1 && mode != 6)
    {
        txt(lang(
            u8"アイテム情報が多すぎる！幾つかのアイテムは破壊された。"s,
            u8"Too many item data! Some items in this area are destroyed."s));
        return inv_compress(owner);
    }
    return -1;
}

int inv_weight(int owner)
{
    int weight{};
    if (owner == 0)
    {
        gdata_cargo_weight = 0;
    }
    for (const auto& cnt : items(owner))
    {
        if (inv[cnt].number != 0)
        {
            if (inv[cnt].weight >= 0)
            {
                weight += inv[cnt].weight * inv[cnt].number;
            }
            else if (owner == 0)
            {
                gdata_cargo_weight += -inv[cnt].weight * inv[cnt].number;
            }
        }
    }
    return weight;
}

int inv_getfreeid_force()
{
    p = inv_getfreeid(tc);
    if (p != -1)
    {
        return p;
    }
    for (int cnt = 0; cnt < 100; ++cnt)
    {
        p = rnd(invrange) + invhead;
        if (inv[p].body_part == 0)
        {
            item_remove(inv[p]);
            if (cdata[tc].item_which_will_be_used == p)
            {
                cdata[tc].item_which_will_be_used = 0;
            }
            break;
        }
    }
    return p;
}



} // namespace elona

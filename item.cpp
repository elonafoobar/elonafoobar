#include "item.hpp"
#include <iostream>
#include <type_traits>
#include "character.hpp"
#include "elona.hpp"
#include "i18n.hpp"
#include "item_db.hpp"
#include "main.hpp"
#include "variables.hpp"


namespace elona
{



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
std::string s_at_m63;
int a_at_m63 = 0;
int skip_at_m63 = 0;


int itemcreate(int slot, int id, int x, int y, int number)
{
    if (flttypeminor != 0)
    {
        flttypemajor = 0;
    }
    dbid = id == 0 ? -1 : id;
    initnum = number;
    return do_create_item(slot, x, y);
}



range::iota<int> items(int owner)
{
    const auto [invhead, invrange] = inv_getheader(owner);
    return {invhead, invhead + invrange};
}



int get_random_inv(int owner)
{
    const auto [invhead, invrange] = inv_getheader(owner);
    return invhead + rnd(invrange);
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
    for (int cnt = 0; cnt < 245; ++cnt)
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
        inv[ci].number = 0;
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

    inv(b) = inv(a);
}



void item_exchange(int a, int b)
{
    using std::swap;
    swap(inv(a), inv(b));
}



void item_delete(int ci)
{
    inv(ci).clear();
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



void item_compress(int owner)
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
                    inv[cnt].number = 0;
                    ++number_of_deleted_items;
                    if (inv[cnt].position.x >= 0
                        && inv[cnt].position.x < mdata(0)
                        && inv[cnt].position.y >= 0
                        && inv[cnt].position.y < mdata(1))
                    {
                        cell_refresh(
                            inv[cnt].position.x, inv[cnt].position.y);
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
        while (1)
        {
            int ci = get_random_inv(owner);
            if (!ibit(5, ci))
            {
                inv[ci].number = 0;
                if (mode != 6)
                {
                    if (inv[ci].position.x >= 0
                        && inv[ci].position.x < mdata(0)
                        && inv[ci].position.y >= 0
                        && inv[ci].position.y < mdata(1))
                    {
                        cell_refresh(
                            inv[ci].position.x, inv[ci].position.y);
                    }
                }
                break;
            }
        }
    }
}



int inv_getfreeid(int owner)
{
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
        if (owner == -1 && mode != 6)
        {
            txt(lang(
                u8"アイテム情報が多すぎる！幾つかのアイテムは破壊された。"s,
                u8"Too many item data! Some items in this area are destroyed."s));
            item_compress(owner);
        }
    }
    return slot;
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



void item_num(int ci, int delta)
{
    inv[ci].number += delta;
    if (inv[ci].number < 0)
    {
        inv[ci].number = 0;
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



int item_separate(int& prm_510)
{
    int ti_at_m59 = 0;
    if (inv[prm_510].number <= 1)
    {
        return prm_510;
    }
    ti_at_m59 = inv_getfreeid(inv_getowner(prm_510));
    if (ti_at_m59 == -1)
    {
        ti_at_m59 = inv_getfreeid(-1);
        if (ti_at_m59 == -1)
        {
            inv[prm_510].number = 1;
            txt(lang(
                u8"何かが地面に落ちて消えた…"s,
                u8"Something falls to the ground and desappear..."s));
            return prm_510;
        }
    }
    item_copy(prm_510, ti_at_m59);
    inv[ti_at_m59].number = inv[prm_510].number - 1;
    inv[prm_510].number = 1;
    if (inv_getowner(ti_at_m59) == -1)
    {
        if (mode != 6)
        {
            if (inv_getowner(prm_510) != -1)
            {
                inv[prm_510].position.x =
                    cdata[inv_getowner(prm_510)].position.x;
                inv[prm_510].position.y =
                    cdata[inv_getowner(prm_510)].position.y;
            }
            inv[ti_at_m59].position.x = inv[prm_510].position.x;
            inv[ti_at_m59].position.y = inv[prm_510].position.y;
            itemturn(ti_at_m59);
            cell_refresh(inv[ti_at_m59].position.x, inv[ti_at_m59].position.y);
            txt(lang(
                u8"何かが地面に落ちた。"s,
                u8"Something falls to the ground from your backpack."s));
            refresh_burden_state();
        }
    }
    return ti_at_m59;
}



int chara_unequip(int prm_511)
{
    int p_at_m59 = 0;
    int c_at_m59 = 0;
    if (inv[prm_511].body_part == 0)
    {
        return 0;
    }
    p_at_m59 = inv[prm_511].body_part;
    c_at_m59 = inv_getowner(prm_511);
    if (c_at_m59 == -1)
    {
        return 0;
    }
    cdata_body_part(c_at_m59, p_at_m59) =
        cdata_body_part(c_at_m59, p_at_m59) / 10000 * 10000;
    inv[prm_511].body_part = 0;
    return 1;
}



int item_identify(int prm_512, int prm_513, int prm_514)
{
    int idlv_at_m60 = 0;
    idlv_at_m60 = prm_513;
    if (prm_514)
    {
        if (prm_514 >= inv[prm_512].difficulty_of_identification)
        {
            idlv_at_m60 = 3;
        }
    }
    if (idlv_at_m60 >= 2)
    {
        if (the_item_db[inv[prm_512].id]->category >= 50000)
        {
            idlv_at_m60 = 3;
        }
    }
    if (idlv_at_m60 == -1 || inv[prm_512].identification_state >= idlv_at_m60)
    {
        idtresult = 0;
        return 0;
    }
    inv[prm_512].identification_state = idlv_at_m60;
    if (inv[prm_512].identification_state >= 1)
    {
        itemmemory(0, inv[prm_512].id) = 1;
    }
    idtresult = idlv_at_m60;
    return idtresult;
}



void item_checkknown(int prm_515)
{
    if (inv[prm_515].identification_state >= 3)
    {
        inv[prm_515].identification_state = 3;
    }
    if (itemmemory(0, inv[prm_515].id))
    {
        if (inv[prm_515].identification_state == 0)
        {
            item_identify(prm_515, 1);
        }
    }
    return;
}



void itemname_additional_info()
{
    if (inv[prm_518].id == 578)
    {
        s_at_m63 += lang(
            ""s + moneyboxn(inv[prm_518].param2),
            u8"("s + moneyboxn(inv[prm_518].param2) + u8")"s);
    }
    if (inv[prm_518].id == 617)
    {
        s_at_m63 += lang(
            ""s + biten(inv[prm_518].param1),
            u8" <"s + biten(inv[prm_518].param1) + u8">"s);
    }
    if (inv[prm_518].id == 687)
    {
        if (jp)
        {
            if (inv[prm_518].param2 != 0)
            {
                s_at_m63 += u8"解読済みの"s;
            }
        }
        if (inv[prm_518].identification_state >= 3)
        {
            s_at_m63 += lang(
                u8"《"s + magebookn(inv[prm_518].param1) + u8"》という題名の"s,
                u8" titled <"s + magebookn(inv[prm_518].param1) + u8">"s);
        }
    }
    if (inv[prm_518].id == 783)
    {
        if (inv[prm_518].param1 == 0)
        {
            s_at_m63 +=
                lang(u8"もう使えない"s, u8" which cannot be used anymore"s);
        }
        else if (inv[prm_518].subname == 0)
        {
            s_at_m63 += lang(u8"カスタム"s, ""s);
        }
        else
        {
            s_at_m63 += lang(
                u8"《"s + rpname(inv[prm_518].subname) + u8"》の"s,
                u8" of <"s + rpname(inv[prm_518].subname) + u8">"s);
        }
    }
    if (a_at_m63 == 55000)
    {
        if (inv[prm_518].id == 563)
        {
            s_at_m63 += lang(
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
            s_at_m63 += lang(u8"第"s, u8" of Rachel No."s) + inv[prm_518].param2
                + lang(u8"巻目の"s, ""s);
        }
        else if (inv[prm_518].id == 24)
        {
            s_at_m63 += lang(
                u8"《"s + booktitle(inv[prm_518].param1) + u8"》という題名の"s,
                u8" titled <"s + booktitle(inv[prm_518].param1) + u8">"s);
        }
    }
    if (a_at_m63 == 60002)
    {
        if (inv[prm_518].param1 != 0)
        {
            s_at_m63 += lang(
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
    if (a_at_m63 == 57000)
    {
        if (inv[prm_518].param1 != 0)
        {
            if (inv[prm_518].param2 != 0)
            {
                skip_at_m63 = 1;
                if (inv[prm_518].id == 618)
                {
                    s_at_m63 = s_at_m63
                        + foodname(inv[prm_518].param1 / 1000,
                                   (""s + fishdatan(inv[prm_518].subname)),
                                   inv[prm_518].param2,
                                   inv[prm_518].subname);
                }
                else
                {
                    s_at_m63 = s_at_m63
                        + foodname(inv[prm_518].param1 / 1000,
                                   ioriginalnameref(inv[prm_518].id),
                                   inv[prm_518].param2,
                                   inv[prm_518].subname);
                }
                return;
            }
        }
        if (inv[prm_518].own_state == 4)
        {
            s_at_m63 += lang(""s, u8" grown "s)
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
                s_at_m63 += u8"/bugged/"s;
                return;
            }
            s_at_m63 += ""s + fishdatan(inv[prm_518].subname);
        }
        else if (
            a_at_m63 == 57000 || a_at_m63 == 62000 || inv[prm_518].id == 503
            || inv[prm_518].id == 504 || inv[prm_518].id == 575
            || inv[prm_518].id == 574)
        {
            if (inv[prm_518].subname < 0 || inv[prm_518].subname >= 800)
            {
                s_at_m63 += u8"/bugged/"s;
                return;
            }
            if (inv[prm_518].own_state != 4)
            {
                s_at_m63 += lang(""s, u8" of "s)
                    + refchara_str(inv[prm_518].subname, 2);
                if (jp)
                {
                    s_at_m63 += u8"の"s;
                }
            }
        }
        if (a_at_m63 == 60000)
        {
            if (jp)
            {
                if (inv[prm_518].subname >= 12)
                {
                    inv[prm_518].subname = 0;
                }
                else
                {
                    s_at_m63 += i18n::_(
                        u8"ui", u8"furniture", u8"_"s + inv[prm_518].subname);
                }
            }
        }
        if (inv[prm_518].id == 344)
        {
            s_at_m63 += lang(""s, u8" of "s)
                + i18n::_(u8"ui", u8"home", u8"_"s + inv[prm_518].param1)
                + lang(u8"の"s, ""s);
        }
        if (inv[prm_518].id == 615)
        {
            s_at_m63 += lang(
                ""s + inv[prm_518].subname + u8"goldの"s,
                u8" <"s + inv[prm_518].subname + u8" gp>"s);
        }
        if (inv[prm_518].id == 704)
        {
            if (inv[prm_518].subname < 0 || inv[prm_518].subname >= 800)
            {
                s_at_m63 += u8"/bugged/"s;
                return;
            }
            s_at_m63 += lang(
                ""s + refchara_str(inv[prm_518].subname, 2) + u8"の"s,
                u8" of "s + refchara_str(inv[prm_518].subname, 2));
        }
    }
    if (inv[prm_518].id == 672)
    {
        if (inv[prm_518].param1 == 169)
        {
            s_at_m63 += lang(u8"善人の"s, u8" of saint"s);
        }
        if (inv[prm_518].param1 == 162)
        {
            s_at_m63 += lang(u8"悪人の"s, u8" of wicked"s);
        }
        if (inv[prm_518].param1 == 163)
        {
            s_at_m63 += lang(u8"エヘカトルの"s, u8" of Ehekatl"s);
        }
        if (inv[prm_518].param1 == 164)
        {
            s_at_m63 += lang(u8"オパートスの"s, u8" of Opatos"s);
        }
        if (inv[prm_518].param1 == 165)
        {
            s_at_m63 += lang(u8"イツパロトルの"s, u8" of Itzpalt"s);
        }
        if (inv[prm_518].param1 == 166)
        {
            s_at_m63 += lang(u8"ジュアの"s, u8" of Jure"s);
        }
    }
    return;
}



std::string itemname(int prm_518, int prm_519, int prm_520)
{
    elona_vector1<int> iqiality_at_m63;
    int num2_at_m63 = 0;
    std::string s2_at_m63;
    std::string s3_at_m63;
    int alpha_at_m63 = 0;
    std::string s4_at_m63;
    int len_at_m63 = 0;
    elona_vector1<std::string> buf_at_m63;
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
        iqiality_at_m63(prm_518) = 5;
    }
    item_checkknown(prm_518);
    if (prm_519 == 0)
    {
        num2_at_m63 = inv[prm_518].number;
    }
    else
    {
        num2_at_m63 = prm_519;
    }
    a_at_m63 = the_item_db[inv[prm_518].id]->category;
    if (jp)
    {
        if (num2_at_m63 > 1)
        {
            s2_at_m63 = u8"個の"s;
            if (a_at_m63 == 16000)
            {
                s2_at_m63 = u8"着の"s;
            }
            if (a_at_m63 == 54000 || a_at_m63 == 55000)
            {
                if (inv[prm_518].id == 783)
                {
                    s2_at_m63 = u8"枚の"s;
                }
                else
                {
                    s2_at_m63 = u8"冊の"s;
                }
            }
            if (a_at_m63 == 10000)
            {
                s2_at_m63 = u8"本の"s;
            }
            if (a_at_m63 == 52000)
            {
                s2_at_m63 = u8"服の"s;
            }
            if (a_at_m63 == 53000)
            {
                s2_at_m63 = u8"巻の"s;
            }
            if (a_at_m63 == 22000 || a_at_m63 == 18000)
            {
                s2_at_m63 = u8"対の"s;
            }
            if (a_at_m63 == 68000 || a_at_m63 == 69000 || inv[prm_518].id == 622
                || inv[prm_518].id == 724 || inv[prm_518].id == 730)
            {
                s2_at_m63 = u8"枚の"s;
            }
            if (inv[prm_518].id == 618)
            {
                s2_at_m63 = u8"匹の"s;
            }
            s_at_m63 = ""s + num2_at_m63 + s2_at_m63;
        }
        else
        {
            s_at_m63 = "";
        }
        if (inv[prm_518].identification_state >= 3)
        {
            if (inv[prm_518].curse_state == 1)
            {
                s_at_m63 += i18n::_(u8"ui", u8"blessed");
            }
            if (inv[prm_518].curse_state == -1)
            {
                s_at_m63 += i18n::_(u8"ui", u8"cursed");
            }
            if (inv[prm_518].curse_state == -2)
            {
                s_at_m63 += i18n::_(u8"ui", u8"doomed");
            }
        }
    }
    else
    {
        s_at_m63 = "";
        if (inv[prm_518].identification_state >= 3)
        {
            if (inv[prm_518].curse_state == 1)
            {
                s_at_m63 = i18n::_(u8"ui", u8"blessed") + u8" "s;
            }
            if (inv[prm_518].curse_state == -1)
            {
                s_at_m63 = i18n::_(u8"ui", u8"cursed") + u8" "s;
            }
            if (inv[prm_518].curse_state == -2)
            {
                s_at_m63 = i18n::_(u8"ui", u8"doomed") + u8" "s;
            }
        }
        if (irandomname(inv[prm_518].id) == 1
            && inv[prm_518].identification_state < 1)
        {
            s2_at_m63 = "";
        }
        else
        {
            s2_at_m63 = ""s + ioriginalnameref2(inv[prm_518].id);
            if (strutil::contains(ioriginalnameref(inv[prm_518].id), u8"with"))
            {
                s3_at_m63 = u8"with"s;
            }
            else
            {
                s3_at_m63 = u8"of"s;
            }
            if (inv[prm_518].identification_state != 0)
            {
                if (s2_at_m63 == ""s)
                {
                    if (inv[prm_518].weight < 0)
                    {
                        s2_at_m63 = u8"cargo"s;
                    }
                    if (a_at_m63 == 22000 || a_at_m63 == 18000)
                    {
                        s2_at_m63 = u8"pair"s;
                    }
                }
            }
            if (a_at_m63 == 57000)
            {
                if (inv[prm_518].param1 != 0)
                {
                    if (inv[prm_518].param2 != 0)
                    {
                        s2_at_m63 = u8"dish"s;
                    }
                }
            }
        }
        if (s2_at_m63 != ""s)
        {
            if (num2_at_m63 > 1)
            {
                s_at_m63 = ""s + num2_at_m63 + u8" "s + s_at_m63 + s2_at_m63
                    + u8"s "s + s3_at_m63 + u8" "s;
            }
            else
            {
                s_at_m63 = s_at_m63 + s2_at_m63 + u8" "s + s3_at_m63 + u8" "s;
            }
        }
        else if (num2_at_m63 > 1)
        {
            s_at_m63 = ""s + num2_at_m63 + u8" "s + s_at_m63;
        }
    }
    if (inv[prm_518].material == 35)
    {
        if (inv[prm_518].param3 < 0)
        {
            if (jp)
            {
                s_at_m63 += u8"腐った"s;
            }
            else
            {
                s_at_m63 += u8"rotten "s;
            }
        }
    }
    if (en)
    {
        if (a_at_m63 == 57000)
        {
            if (inv[prm_518].param1 != 0)
            {
                if (inv[prm_518].param2 != 0)
                {
                    skip_at_m63 = 1;
                }
            }
        }
        if (inv[prm_518].subname != 0)
        {
            if (a_at_m63 == 60000)
            {
                if (inv[prm_518].subname >= 12)
                {
                    inv[prm_518].subname = 0;
                }
                else
                {
                    s_at_m63 += i18n::_(
                                    u8"ui",
                                    u8"furniture",
                                    u8"_"s + inv[prm_518].subname)
                        + u8" "s;
                }
            }
        }
        if (inv[prm_518].id == 687)
        {
            if (inv[prm_518].param2 != 0)
            {
                s_at_m63 += u8"undecoded "s;
            }
        }
        if (inv[prm_518].id == 783)
        {
            if (inv[prm_518].subname == 0)
            {
                s_at_m63 += u8"custom "s;
            }
        }
    }
    if (inv[prm_518].id == 630)
    {
        s_at_m63 +=
            ""s + mtname(0, inv[prm_518].material) + lang(u8"製の"s, u8" "s);
    }
    if (jp)
    {
        itemname_additional_info();
    }
    if (a_at_m63 == 60000)
    {
        if (inv[prm_518].material != 0)
        {
            if (jp)
            {
                s_at_m63 +=
                    ""s + mtname(0, inv[prm_518].material) + u8"細工の"s;
            }
            else
            {
                s_at_m63 += ""s + mtname(0, inv[prm_518].material) + u8"work "s;
            }
        }
    }
    if (inv[prm_518].id == 729)
    {
        s_at_m63 += ""s + giftn(inv[prm_518].param4) + lang(""s, u8" "s);
    }
    if (skip_at_m63 == 1)
    {
        goto label_0313_internal;
    }
    alpha_at_m63 = 0;
    if (inv[prm_518].identification_state >= 3)
    {
        if (a_at_m63 < 50000)
        {
            if (ibit(15, prm_518))
            {
                alpha_at_m63 = 1;
                s_at_m63 += lang(u8"エターナルフォース"s, u8"eternal force"s)
                    + strblank;
            }
            else
            {
                if (inv[prm_518].subname >= 10000)
                {
                    if (inv[prm_518].subname < 20000)
                    {
                        if (jp)
                        {
                            s_at_m63 += egoname(inv[prm_518].subname - 10000)
                                + strblank;
                        }
                    }
                    else if (inv[prm_518].subname < 40000)
                    {
                        s_at_m63 +=
                            egominorn(inv[prm_518].subname - 20000) + strblank;
                    }
                }
                if (inv[prm_518].quality != 6)
                {
                    if (inv[prm_518].quality >= 4)
                    {
                        s_at_m63 += mtname(1, inv[prm_518].material) + strblank;
                    }
                    else
                    {
                        s_at_m63 += mtname(0, inv[prm_518].material) + strblank;
                        if (jp)
                        {
                            if (/* TODO is_katakana */ false)
                            {
                                alpha_at_m63 = 1;
                            }
                            else
                            {
                                s_at_m63 += u8"の"s;
                            }
                        }
                    }
                }
            }
        }
    }
    if (inv[prm_518].identification_state == 0)
    {
        s_at_m63 += iknownnameref(inv[prm_518].id);
    }
    else if (inv[prm_518].identification_state < 3)
    {
        if (inv[prm_518].quality < 4 || a_at_m63 >= 50000)
        {
            s_at_m63 += ioriginalnameref(inv[prm_518].id);
        }
        else
        {
            s_at_m63 += iknownnameref(inv[prm_518].id);
        }
    }
    else if (inv[prm_518].quality == 6 || ibit(5, prm_518) == 1)
    {
        if (jp)
        {
            s_at_m63 = u8"★"s + s_at_m63 + ioriginalnameref(inv[prm_518].id);
        }
        else
        {
            s_at_m63 += ioriginalnameref(inv[prm_518].id);
        }
    }
    else
    {
        if (inv[prm_518].quality >= 4)
        {
            if (jp)
            {
                s_at_m63 = u8"☆"s + s_at_m63;
            }
        }
        if (alpha_at_m63 == 1 && jp)
        {
            s_at_m63 += ialphanameref(inv[prm_518].id);
        }
        else
        {
            s_at_m63 += ioriginalnameref(inv[prm_518].id);
        }
        if (en)
        {
            if (a_at_m63 < 50000)
            {
                if (inv[prm_518].subname >= 10000)
                {
                    if (inv[prm_518].subname < 20000)
                    {
                        s_at_m63 +=
                            u8" "s + egoname((inv[prm_518].subname - 10000));
                    }
                }
            }
        }
        if (inv[prm_518].subname >= 40000)
        {
            randomize(inv[prm_518].subname - 40000);
            if (inv[prm_518].quality == 4)
            {
                s_at_m63 += lang(u8"『"s, u8" <"s) + random_title(1)
                    + lang(u8"』"s, u8">"s);
            }
            else
            {
                s_at_m63 += lang(u8"《"s, u8" {"s) + random_title(1)
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
            if (inv[prm_518].identification_state >= 3
                && (inv[prm_518].quality >= 4 && a_at_m63 < 50000))
            {
                s_at_m63 = u8"the "s + s_at_m63;
            }
            else if (num2_at_m63 == 1)
            {
                s4_at_m63 = strmid(s_at_m63, 0, 1);
                if (s4_at_m63 == u8"a"s || s4_at_m63 == u8"o"s
                    || s4_at_m63 == u8"i"s || s4_at_m63 == u8"u"s
                    || s4_at_m63 == u8"e"s)
                {
                    s_at_m63 = u8"an "s + s_at_m63;
                }
                else
                {
                    s_at_m63 = u8"a "s + s_at_m63;
                }
            }
        }
        if (s2_at_m63 == ""s)
        {
            if (inv[prm_518].id != 618)
            {
                if (num2_at_m63 > 1)
                {
                    s_at_m63 += u8"s"s;
                }
            }
        }
        itemname_additional_info();
    }
    if (inv[prm_518].identification_state >= 3)
    {
        if (inv[prm_518].enhancement != 0)
        {
            s_at_m63 += ""s + cnvfix(inv[prm_518].enhancement) + u8" "s;
        }
        if (ibit(4, prm_518) == 1)
        {
            s_at_m63 += lang(
                u8"(残り"s + inv[prm_518].count + u8"回)"s,
                u8"(Charges: "s + inv[prm_518].count + u8")"s);
        }
        if (inv[prm_518].dice_x != 0 || inv[prm_518].hit_bonus != 0
            || inv[prm_518].damage_bonus != 0)
        {
            s_at_m63 += u8" ("s;
            if (inv[prm_518].dice_x != 0)
            {
                s_at_m63 +=
                    ""s + inv[prm_518].dice_x + u8"d"s + inv[prm_518].dice_y;
                if (inv[prm_518].damage_bonus != 0)
                {
                    if (inv[prm_518].damage_bonus > 0)
                    {
                        s_at_m63 += u8"+"s + inv[prm_518].damage_bonus;
                    }
                    else
                    {
                        s_at_m63 += ""s + inv[prm_518].damage_bonus;
                    }
                }
                s_at_m63 += u8")"s;
                if (inv[prm_518].hit_bonus != 0)
                {
                    s_at_m63 += u8"("s + inv[prm_518].hit_bonus + u8")"s;
                }
            }
            else
            {
                s_at_m63 += ""s + inv[prm_518].hit_bonus + u8","s
                    + inv[prm_518].damage_bonus + u8")"s;
            }
        }
        if (inv[prm_518].dv != 0 || inv[prm_518].pv != 0)
        {
            s_at_m63 +=
                u8" ["s + inv[prm_518].dv + u8","s + inv[prm_518].pv + u8"]"s;
        }
    }
    if (en)
    {
        if (inv[prm_518].id == 284 || inv[prm_518].id == 283)
        {
            s_at_m63 += u8"(Lost property)"s;
        }
    }
    if (inv[prm_518].id == 342)
    {
        if (inv[prm_518].count != 0)
        {
            s_at_m63 += lang(
                u8"("s + biten(inv[prm_518].param4) + u8"残り"s
                    + inv[prm_518].count + u8"匹)"s,
                u8"("s + inv[prm_518].count + u8" "s
                    + biten(inv[prm_518].param4) + u8")"s);
        }
    }
    if (inv[prm_518].id == 685)
    {
        if (inv[prm_518].subname == 0)
        {
            s_at_m63 += lang(u8" Lv"s, u8" Level "s) + inv[prm_518].param2
                + lang(u8" (空)"s, u8"(Empty)"s);
        }
        else
        {
            s_at_m63 +=
                u8" ("s + refchara_str(inv[prm_518].subname, 2) + u8")"s;
        }
    }
    if (inv[prm_518].id == 734)
    {
        s_at_m63 += lang(u8" Lv"s, u8" Level "s) + inv[prm_518].param2;
    }
    if (inv[prm_518].identification_state == 2)
    {
        if (a_at_m63 < 50000)
        {
            s_at_m63 += u8" ("s
                + cnven(i18n::_(
                      u8"ui", u8"quality", u8"_"s + inv[prm_518].quality))
                + u8")"s;
            if (jp)
            {
                s_at_m63 +=
                    u8"["s + mtname(0, inv[prm_518].material) + u8"製]"s;
            }
            else
            {
                s_at_m63 +=
                    u8"["s + cnven(mtname(0, inv[prm_518].material)) + u8"]"s;
            }
            if (inv[prm_518].curse_state == -1)
            {
                s_at_m63 += lang(u8"(恐ろしい)"s, u8"(Scary)"s);
            }
            if (inv[prm_518].curse_state == -2)
            {
                s_at_m63 += lang(u8"(禍々しい)"s, u8"(Dreadful)"s);
            }
        }
    }
    if (a_at_m63 == 72000)
    {
        if (inv[prm_518].id == 361)
        {
            s_at_m63 += lang(u8"(移動時消滅)"s, u8"(Temporal)"s);
        }
        else if (inv[prm_518].count == 0)
        {
            if (inv[prm_518].param1 == 0)
            {
                s_at_m63 += lang(u8"(空っぽ)"s, u8"(Empty)"s);
            }
        }
    }
    if (a_at_m63 == 92000)
    {
        if (inv[prm_518].param2 != 0)
        {
            s_at_m63 += lang(
                u8"(仕入れ値 "s + inv[prm_518].param2 + u8"g)"s,
                u8"(Buying price: "s + inv[prm_518].param2 + u8")"s);
        }
    }
    if (ibit(6, prm_518) == 1)
    {
        s_at_m63 += lang(u8"(媚薬混入)"s, u8"(Aphrodisiac)"s);
    }
    if (ibit(14, prm_518) == 1)
    {
        s_at_m63 += lang(u8"(毒物混入)"s, u8"(Poisoned)"s);
    }
    if (ibit(7, prm_518) == 1)
    {
        if (gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
                + gdata_year * 24 * 30 * 12
            < inv[prm_518].count)
        {
            s_at_m63 += lang(
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
    }
    if (inv[prm_518].id == 555)
    {
        if (inv[prm_518].count != 0)
        {
            s_at_m63 +=
                lang(u8" シリアルNo."s, u8" serial no."s) + inv[prm_518].count;
        }
    }
    if (inv[prm_518].id == 544)
    {
        s_at_m63 += u8" <BGM"s + inv[prm_518].param1 + u8">"s;
    }
    if (strlen_u(s_at_m63) > 66)
    {
        len_at_m63 = zentohan(s_at_m63, buf_at_m63, 0);
        SDIM2(buf_at_m63, len_at_m63);
        zentohan(s_at_m63, s_at_m63, len_at_m63);
    }
    skip_at_m63 = 0;
    return s_at_m63;
}



void remain_make(int prm_521, int prm_522)
{
    inv[prm_521].subname = cdata[prm_522].id;
    inv[prm_521].color = cdata[prm_522].image / 1000;
    inv[prm_521].weight = cdata[prm_522].weight;
    if (inv[prm_521].id == 204)
    {
        inv[prm_521].weight = 250 * (inv[prm_521].weight + 100) / 100 + 500;
        inv[prm_521].value = inv[prm_521].weight / 5;
    }
    else
    {
        inv[prm_521].weight = 20 * (inv[prm_521].weight + 500) / 500;
        inv[prm_521].value = cdata[prm_522].level * 40 + 600;
        if (the_character_db[cdata[prm_522].id]->rarity / 1000 < 20)
        {
            if (cdata[prm_522].original_relationship < -1)
            {
                inv[prm_521].value = inv[prm_521].value
                    * std::clamp((4
                                  - the_character_db[cdata[prm_522].id]->rarity
                                      / 1000 / 5),
                                 1,
                                 5);
            }
        }
    }
    return;
}



void make_dish(int prm_523, int prm_524)
{
    inv[prm_523].image = picfood(prm_524, inv[prm_523].param1 / 1000);
    inv[prm_523].weight = 500;
    if (inv[prm_523].material == 35)
    {
        if (inv[prm_523].param3 >= 0)
        {
            inv[prm_523].param3 = gdata_hour + gdata_day * 24
                + gdata_month * 24 * 30 + gdata_year * 24 * 30 * 12 + 72;
        }
    }
    inv[prm_523].param2 = prm_524;
    return;
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
            inv[ci].number = 0;
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
            txtmore();
            txt(lang(
                itemname(ti, 1) + u8"をまとめた(計"s + inv[ti].number
                    + u8"個) "s,
                itemname(ti, 1) + u8" has been stacked. (Total:"s
                    + inv[ti].number + u8")"s));
        }
    }

    return did_stack;
}



} // namespace elona

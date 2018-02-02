#include "elona.hpp"
#include "main.hpp"
#include "variables.hpp"


namespace elona
{


int itemcreate(int prm_467, int prm_468, int prm_469, int prm_470, int prm_471)
{
    itemcreatehack = -1;
    if (flttypeminor != 0)
    {
        flttypemajor = 0;
    }
    if (prm_468 == 0)
    {
        dbid = -1;
    }
    else
    {
        dbid = prm_468;
    }
    if (prm_471 != 0)
    {
        initnum = prm_471;
    }
    else
    {
        initnum = 0;
    }
    val(0) = prm_467;
    val(1) = prm_469;
    val(2) = prm_470;
    itemcreatehack = 0;
    return label_1582();
}



void inv_getheader(int prm_472)
{
    if (prm_472 == 0)
    {
        invhead = 0;
        invrange = 200;
        return;
    }
    if (prm_472 == -1)
    {
        invhead = 5080;
        invrange = 400;
        return;
    }
    invhead = 200 + 20 * (prm_472 - 1);
    invrange = 20;
    return;
}



int inv_getowner(int prm_473)
{
    if (prm_473 < 200)
    {
        return 0;
    }
    if (prm_473 >= 5080)
    {
        return -1;
    }
    return (prm_473 - 200) / 20 + 1;
}



int inv_find(int prm_474, int prm_475)
{
    int f_at_m52 = 0;
    f_at_m52 = -1;
    inv_getheader(prm_475);
    {
        int cnt = invhead;
        for (int cnt_end = cnt + (invrange); cnt < cnt_end; ++cnt)
        {
            if (inv_number(cnt) == 0)
            {
                continue;
            }
            if (inv_id(cnt) == prm_474)
            {
                f_at_m52 = cnt;
                break;
            }
        }
    }
    return f_at_m52;
}



int item_find(int prm_476, int prm_477, int prm_478)
{
    elona_vector1<int> p_at_m52;
    p_at_m52(0) = -1;
    p_at_m52(1) = -1;
    {
        int cnt = 0;
        for (int cnt_end = cnt + (2); cnt < cnt_end; ++cnt)
        {
            if (cnt == 0)
            {
                if (prm_478 > 0)
                {
                    continue;
                }
                inv_getheader(-1);
            }
            else
            {
                if (prm_478 < 0)
                {
                    continue;
                }
                inv_getheader(0);
            }
            p_at_m52(2) = cnt;
            {
                int cnt = invhead;
                for (int cnt_end = cnt + (invrange); cnt < cnt_end; ++cnt)
                {
                    if (inv_number(cnt) == 0)
                    {
                        continue;
                    }
                    if (p_at_m52(2) == 0)
                    {
                        if (inv_x(cnt) != cdata_x(0)
                            || inv_y(cnt) != cdata_y(0))
                        {
                            continue;
                        }
                    }
                    if (prm_477 == 0)
                    {
                        if (refitem(inv_id(cnt), 5) == prm_476)
                        {
                            p_at_m52 = cnt;
                        }
                    }
                    if (prm_477 == 1)
                    {
                        if (inv_skill(cnt) == prm_476)
                        {
                            if (p_at_m52(1) < inv_param1(cnt))
                            {
                                p_at_m52(0) = cnt;
                                p_at_m52(1) = inv_param1(cnt);
                            }
                        }
                    }
                    if (prm_477 == 2)
                    {
                        if (refitem(inv_id(cnt), 9) == prm_476)
                        {
                            p_at_m52 = cnt;
                        }
                    }
                    if (prm_477 == 3)
                    {
                        if (inv_id(cnt) == prm_476)
                        {
                            p_at_m52 = cnt;
                        }
                    }
                }
            }
        }
    }
    return p_at_m52;
}



int encfind(int prm_479, int prm_480)
{
    int i_at_m53 = 0;
    f_at_m53 = -1;
    {
        int cnt = 100;
        for (int cnt_end = cnt + (30); cnt < cnt_end; ++cnt)
        {
            if (cdata(cnt, prm_479) % 10000 == 0)
            {
                continue;
            }
            i_at_m53 = cdata(cnt, prm_479) % 10000 - 1;
            {
                int cnt = 0;
                for (int cnt_end = cnt + (15); cnt < cnt_end; ++cnt)
                {
                    if (inv_enchantment_id(i_at_m53, cnt) == 0)
                    {
                        break;
                    }
                    if (inv_enchantment_id(i_at_m53, cnt) == prm_480)
                    {
                        if (inv_enchantment_power(i_at_m53, cnt) > f_at_m53)
                        {
                            f_at_m53 = inv_enchantment_power(i_at_m53, cnt);
                            break;
                        }
                    }
                }
            }
        }
    }
    return f_at_m53;
}



int encfindspec(int prm_481, int prm_482)
{
    f_at_m53 = -1;
    {
        int cnt = 0;
        for (int cnt_end = cnt + (15); cnt < cnt_end; ++cnt)
        {
            if (inv_enchantment_id(prm_481, cnt) == 0)
            {
                break;
            }
            if (inv_enchantment_id(prm_481, cnt) == prm_482)
            {
                f_at_m53 = 1;
                break;
            }
        }
    }
    return f_at_m53;
}



void itemlist(int prm_483, int prm_484)
{
    inv_getheader(prm_483);
    listmax = 0;
    {
        int cnt = invhead;
        for (int cnt_end = cnt + (invrange); cnt < cnt_end; ++cnt)
        {
            if (inv_number(cnt) == 0)
            {
                continue;
            }
            if (inv_id(cnt) == prm_484)
            {
                list(0, listmax) = cnt;
                ++listmax;
            }
        }
    }
    return;
}



int itemusingfind(int prm_485, int prm_486)
{
    f_at_m54 = -1;
    {
        int cnt = 0;
        for (int cnt_end = cnt + (245); cnt < cnt_end; ++cnt)
        {
            if (cdata_state(cnt) != 1)
            {
                continue;
            }
            if (cdata_continuous_action_id(cnt) != 0)
            {
                if (cdata_continuous_action_turn(cnt) > 0)
                {
                    if (cdata_continuous_action_item(cnt) == prm_485)
                    {
                        if (prm_486 == 0 || prm_486 == 1 && cnt != 0)
                        {
                            f_at_m54 = cnt;
                            break;
                        }
                    }
                }
            }
        }
    }
    return f_at_m54;
}



int itemfind(int prm_487, int prm_488, int prm_489)
{
    inv_getheader(prm_487);
    f_at_m54 = -1;
    if (prm_489 == 0)
    {
        {
            int cnt = invhead;
            for (int cnt_end = cnt + (invrange); cnt < cnt_end; ++cnt)
            {
                if (inv_number(cnt) == 0)
                {
                    continue;
                }
                if (inv_id(cnt) == prm_488)
                {
                    f_at_m54 = cnt;
                    break;
                }
            }
        }
        return f_at_m54;
    }
    else
    {
        {
            int cnt = invhead;
            for (int cnt_end = cnt + (invrange); cnt < cnt_end; ++cnt)
            {
                if (inv_number(cnt) == 0)
                {
                    continue;
                }
                if (refitem(inv_id(cnt), 9) == prm_488)
                {
                    f_at_m54 = cnt;
                    break;
                }
            }
        }
        return f_at_m54;
    }
}



int mapitemfind(int prm_490, int prm_491, int prm_492)
{
    inv_getheader(-1);
    f_at_m54 = -1;
    {
        int cnt = invhead;
        for (int cnt_end = cnt + (invrange); cnt < cnt_end; ++cnt)
        {
            if (inv_number(cnt) == 0)
            {
                continue;
            }
            if (inv_id(cnt) == prm_492)
            {
                if (inv_x(cnt) == prm_490)
                {
                    if (inv_y(cnt) == prm_491)
                    {
                        f_at_m54 = cnt;
                        break;
                    }
                }
            }
        }
    }
    return f_at_m54;
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
    inv_getheader(-1);
    {
        int cnt = invhead;
        for (int cnt_end = cnt + (invrange); cnt < cnt_end; ++cnt)
        {
            if (inv_number(cnt) > 0)
            {
                if (inv_x(cnt) == prm_493 && inv_y(cnt) == prm_494)
                {
                    floorstack(p_at_m55) = cnt;
                    ++p_at_m55;
                    wpoke(map(prm_493, prm_494, 4), 0, inv_image(cnt));
                    wpoke(map(prm_493, prm_494, 4), 2, inv_color(cnt));
                    if (ilight(inv_id(cnt)) != 0)
                    {
                        map(prm_493, prm_494, 9) = ilight(inv_id(cnt));
                    }
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
        {
            int cnt = 0;
            for (int cnt_end = cnt + (p_at_m55); cnt < cnt_end; ++cnt)
            {
                cnt2_at_m55 = cnt;
                i_at_m55 = -1;
                {
                    int cnt = 0;
                    for (int cnt_end = cnt + (p_at_m55); cnt < cnt_end; ++cnt)
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
                        if (inv_turn(floorstack(cnt)) > i_at_m55)
                        {
                            n_at_m55(cnt2_at_m55) = cnt;
                            i_at_m55 = inv_turn(floorstack(cnt));
                        }
                    }
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



void itemturn(int prm_495)
{
    if (gdata_item_turns < 0)
    {
        gdata_item_turns = 0;
    }
    ++gdata_item_turns;
    inv_turn(prm_495) = gdata_item_turns;
    return;
}



void removeitem(int prm_496, int prm_497)
{
    int n_at_m56 = 0;
    n_at_m56 = prm_497;
    if (n_at_m56 == 0)
    {
        n_at_m56 = 1;
    }
    inv_number(prm_496) -= n_at_m56;
    if (prm_496 < 200)
    {
        label_1521();
    }
    if (inv_number(prm_496) <= 0)
    {
        inv_number(prm_496) = 0;
        if (mode != 6)
        {
            if (prm_496 >= 5080)
            {
                cell_refresh(inv_x(prm_496), inv_y(prm_496));
            }
        }
    }
    return;
}



void item_copy(int prm_498, int prm_499)
{
    if (prm_498 < 0 || prm_499 < 0)
    {
        return;
    }
    {
        int cnt = 0;
        for (int cnt_end = cnt + (70); cnt < cnt_end; ++cnt)
        {
            inv(cnt, prm_499) = inv(cnt, prm_498);
        }
    }
    return;
}



void item_exchange(int prm_500, int prm_501)
{
    {
        int cnt = 0;
        for (int cnt_end = cnt + (70); cnt < cnt_end; ++cnt)
        {
            p_at_m57 = inv(cnt, prm_501);
            inv(cnt, prm_501) = inv(cnt, prm_500);
            inv(cnt, prm_500) = p_at_m57;
        }
    }
    return;
}



void item_delete(int prm_502)
{
    inv.clear(prm_502);
    return;
}



int inv_getspace(int prm_503)
{
    inv_getheader(prm_503);
    p_at_m57 = 0;
    {
        int cnt = invhead;
        for (int cnt_end = cnt + (invrange); cnt < cnt_end; ++cnt)
        {
            if (inv_number(cnt) == 0)
            {
                ++p_at_m57;
                break;
            }
        }
    }
    return p_at_m57;
}



int inv_sum(int prm_504)
{
    inv_getheader(prm_504);
    p_at_m57 = 0;
    {
        int cnt = invhead;
        for (int cnt_end = cnt + (invrange); cnt < cnt_end; ++cnt)
        {
            if (inv_number(cnt) != 0)
            {
                ++p_at_m57;
            }
        }
    }
    return p_at_m57;
}



void item_compress(int)
{
    p_at_m57 = 0;
    {
        int cnt = 0;
        for (int cnt_end = cnt + (100); cnt < cnt_end; ++cnt)
        {
            p_at_m57(1) = 200 * (cnt * cnt + 1);
            {
                int cnt = invhead;
                for (int cnt_end = cnt + (invrange); cnt < cnt_end; ++cnt)
                {
                    if (inv_number(cnt) != 0)
                    {
                        if (ibit(5, cnt) == 0)
                        {
                            if (inv_value(cnt) < p_at_m57(1))
                            {
                                inv_number(cnt) = 0;
                                ++p_at_m57;
                                if (inv_x(cnt) >= 0 && inv_x(cnt) < mdata(0)
                                    && inv_y(cnt) >= 0 && inv_y(cnt) < mdata(1))
                                {
                                    cell_refresh(inv_x(cnt), inv_y(cnt));
                                }
                            }
                        }
                    }
                    if (p_at_m57 > 10)
                    {
                        break;
                    }
                }
            }
            if (p_at_m57 > 10)
            {
                break;
            }
        }
    }
    p_at_m57 = -1;
    {
        int cnt = invhead;
        for (int cnt_end = cnt + (invrange); cnt < cnt_end; ++cnt)
        {
            if (inv_number(cnt) == 0)
            {
                p_at_m57 = cnt;
                break;
            }
        }
    }
    if (p_at_m57 == -1)
    {
        {
            int cnt = 0;
            for (;; ++cnt)
            {
                p_at_m57 = invhead + rnd(invrange);
                if (ibit(5, cnt) == 0)
                {
                    inv_number(p_at_m57) = 0;
                    if (mode != 6)
                    {
                        if (inv_x(p_at_m57) >= 0 && inv_x(p_at_m57) < mdata(0)
                            && inv_y(p_at_m57) >= 0
                            && inv_y(p_at_m57) < mdata(1))
                        {
                            cell_refresh(inv_x(p_at_m57), inv_y(p_at_m57));
                        }
                    }
                    break;
                }
            }
        }
    }
    return;
}



int inv_getfreeid(int prm_506)
{
    inv_getheader(prm_506);
    p_at_m57 = -1;
    {
        int cnt = invhead;
        for (int cnt_end = cnt + (invrange); cnt < cnt_end; ++cnt)
        {
            if (inv_number(cnt) == 0)
            {
                p_at_m57 = cnt;
                break;
            }
        }
    }
    if (p_at_m57 == -1)
    {
        if (prm_506 == -1)
        {
            if (mode != 6)
            {
                txt(lang(
                    u8"アイテム情報が多すぎる！幾つかのアイテムは破壊された。"s,
                    u8"Too many item data! Some items in this area are destroyed."s));
                item_compress(prm_506);
            }
        }
    }
    return p_at_m57;
}



int inv_weight_(int prm_507)
{
    p_at_m57 = 0;
    inv_getheader(prm_507);
    if (prm_507 == 0)
    {
        gdata_cargo_weight = 0;
    }
    {
        int cnt = invhead;
        for (int cnt_end = cnt + (invrange); cnt < cnt_end; ++cnt)
        {
            if (inv_number(cnt) != 0)
            {
                if (inv_weight(cnt) >= 0)
                {
                    p_at_m57 += inv_weight(cnt) * inv_number(cnt);
                }
                else if (prm_507 == 0)
                {
                    gdata_cargo_weight +=
                        inv_weight(cnt) * inv_number(cnt) * -1;
                }
            }
        }
    }
    return p_at_m57;
}



void item_num(int prm_508, int prm_509)
{
    inv_number(prm_508) += prm_509;
    if (inv_number(prm_508) < 0)
    {
        inv_number(prm_508) = 0;
    }
    if (prm_508 >= 5080)
    {
        cell_refresh(inv_x(prm_508), inv_y(prm_508));
    }
    else
    {
        label_1521();
    }
    return;
}



int item_separate(int& prm_510)
{
    int ti_at_m59 = 0;
    if (inv_number(prm_510) <= 1)
    {
        return prm_510;
    }
    ti_at_m59 = inv_getfreeid(inv_getowner(prm_510));
    if (ti_at_m59 == -1)
    {
        ti_at_m59 = inv_getfreeid(-1);
        if (ti_at_m59 == -1)
        {
            inv_number(prm_510) = 1;
            txt(lang(
                u8"何かが地面に落ちて消えた…"s,
                u8"Something falls to the ground and desappear..."s));
            return prm_510;
        }
    }
    item_copy(prm_510, ti_at_m59);
    inv_number(ti_at_m59) = inv_number(prm_510) - 1;
    inv_number(prm_510) = 1;
    if (inv_getowner(ti_at_m59) == -1)
    {
        if (mode != 6)
        {
            if (inv_getowner(prm_510) != -1)
            {
                inv_x(prm_510) = cdata_x(inv_getowner(prm_510));
                inv_y(prm_510) = cdata_y(inv_getowner(prm_510));
            }
            inv_x(ti_at_m59) = inv_x(prm_510);
            inv_y(ti_at_m59) = inv_y(prm_510);
            itemturn(ti_at_m59);
            cell_refresh(inv_x(ti_at_m59), inv_y(ti_at_m59));
            txt(lang(
                u8"何かが地面に落ちた。"s,
                u8"Something falls to the ground from your backpack."s));
            label_1521();
        }
    }
    return ti_at_m59;
}



int chara_unequip(int prm_511)
{
    int p_at_m59 = 0;
    int c_at_m59 = 0;
    if (inv_body_part(prm_511) == 0)
    {
        return 0;
    }
    p_at_m59 = inv_body_part(prm_511);
    c_at_m59 = inv_getowner(prm_511);
    if (c_at_m59 == -1)
    {
        return 0;
    }
    cdata(p_at_m59, c_at_m59) = cdata(p_at_m59, c_at_m59) / 10000 * 10000;
    inv_body_part(prm_511) = 0;
    return 1;
}



int item_identify(int prm_512, int prm_513, int prm_514)
{
    int idlv_at_m60 = 0;
    idlv_at_m60 = prm_513;
    if (prm_514)
    {
        if (prm_514 >= inv_difficulty_of_identification(prm_512))
        {
            idlv_at_m60 = 3;
        }
    }
    if (idlv_at_m60 >= 2)
    {
        if (refitem(inv_id(prm_512), 5) >= 50000)
        {
            idlv_at_m60 = 3;
        }
    }
    if (idlv_at_m60 == -1 || inv_identification_state(prm_512) >= idlv_at_m60)
    {
        idtresult = 0;
        return 0;
    }
    inv_identification_state(prm_512) = idlv_at_m60;
    if (inv_identification_state(prm_512) >= 1)
    {
        itemmemory(0, inv_id(prm_512)) = 1;
    }
    idtresult = idlv_at_m60;
    return idtresult;
}



void item_checkknown(int prm_515)
{
    if (inv_identification_state(prm_515) >= 3)
    {
        inv_identification_state(prm_515) = 3;
    }
    if (itemmemory(0, inv_id(prm_515)))
    {
        if (inv_identification_state(prm_515) == 0)
        {
            item_identify(prm_515, 1);
        }
    }
    return;
}



void label_0311()
{
    if (inv_id(prm_518) == 578)
    {
        s_at_m63 += lang(
            ""s + moneyboxn(inv_param2(prm_518)),
            u8"("s + moneyboxn(inv_param2(prm_518)) + u8")"s);
    }
    if (inv_id(prm_518) == 617)
    {
        s_at_m63 += lang(
            ""s + biten(inv_param1(prm_518)),
            u8" <"s + biten(inv_param1(prm_518)) + u8">"s);
    }
    if (inv_id(prm_518) == 687)
    {
        if (jp)
        {
            if (inv_param2(prm_518) != 0)
            {
                s_at_m63 += u8"解読済みの"s;
            }
        }
        if (inv_identification_state(prm_518) >= 3)
        {
            s_at_m63 += lang(
                u8"《"s + magebookn(inv_param1(prm_518)) + u8"》という題名の"s,
                u8" titled <"s + magebookn(inv_param1(prm_518)) + u8">"s);
        }
    }
    if (inv_id(prm_518) == 783)
    {
        if (inv_param1(prm_518) == 0)
        {
            s_at_m63 +=
                lang(u8"もう使えない"s, u8" which cannot be used anymore"s);
        }
        else if (inv_subname(prm_518) == 0)
        {
            s_at_m63 += lang(u8"カスタム"s, ""s);
        }
        else
        {
            s_at_m63 += lang(
                u8"《"s + rpname(inv_subname(prm_518)) + u8"》の"s,
                u8" of <"s + rpname(inv_subname(prm_518)) + u8">"s);
        }
    }
    if (a_at_m63 == 55000)
    {
        if (inv_id(prm_518) == 563)
        {
            s_at_m63 += lang(
                u8"《"s + skillname(inv_param1(prm_518)) + u8"》という題名の"s,
                u8" titled <Art of "s + skillname(inv_param1(prm_518))
                    + u8">"s);
        }
        else if (inv_id(prm_518) == 668)
        {
            s_at_m63 += lang(u8"第"s, u8" of Rachel No."s) + inv_param2(prm_518)
                + lang(u8"巻目の"s, ""s);
        }
        else if (inv_id(prm_518) == 24)
        {
            s_at_m63 += lang(
                u8"《"s + booktitle(inv_param1(prm_518)) + u8"》という題名の"s,
                u8" titled <"s + booktitle(inv_param1(prm_518)) + u8">"s);
        }
    }
    if (a_at_m63 == 60002)
    {
        if (inv_param1(prm_518) != 0)
        {
            s_at_m63 += lang(
                godname(inv_param1(prm_518)) + u8"の"s,
                u8" <"s + godname(inv_param1(prm_518)) + u8">"s);
        }
    }
    if (a_at_m63 == 57000)
    {
        if (inv_param1(prm_518) != 0)
        {
            if (inv_param2(prm_518) != 0)
            {
                skip_at_m63 = 1;
                if (inv_id(prm_518) == 618)
                {
                    s_at_m63 = s_at_m63
                        + foodname(inv_param1(prm_518) / 1000,
                                   (""s + fishdatan(inv_subname(prm_518))),
                                   inv_param2(prm_518),
                                   inv_subname(prm_518));
                }
                else
                {
                    s_at_m63 = s_at_m63
                        + foodname(inv_param1(prm_518) / 1000,
                                   ioriginalnameref(inv_id(prm_518)),
                                   inv_param2(prm_518),
                                   inv_subname(prm_518));
                }
                return;
            }
        }
        if (inv_own_state(prm_518) == 4)
        {
            s_at_m63 += lang(""s, u8" grown "s) + _weight(inv_subname(prm_518))
                + lang(u8"育った"s, ""s);
        }
    }
    if (inv_subname(prm_518) != 0)
    {
        if (inv_id(prm_518) == 618 || inv_id(prm_518) == 619)
        {
            if (inv_subname(prm_518) < 0 || inv_subname(prm_518) >= 100)
            {
                s_at_m63 += u8"/bugged/"s;
                return;
            }
            s_at_m63 += ""s + fishdatan(inv_subname(prm_518));
        }
        else if (
            a_at_m63 == 57000 || a_at_m63 == 62000 || inv_id(prm_518) == 503
            || inv_id(prm_518) == 504 || inv_id(prm_518) == 575
            || inv_id(prm_518) == 574)
        {
            if (inv_subname(prm_518) < 0 || inv_subname(prm_518) >= 800)
            {
                s_at_m63 += u8"/bugged/"s;
                return;
            }
            if (inv_own_state(prm_518) != 4)
            {
                s_at_m63 += lang(""s, u8" of "s)
                    + refchara_str(inv_subname(prm_518), 2);
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
                if (inv_subname(prm_518) >= 12)
                {
                    inv_subname(prm_518) = 0;
                }
                else
                {
                    s_at_m63 += _furniture(inv_subname(prm_518));
                }
            }
        }
        if (inv_id(prm_518) == 344)
        {
            s_at_m63 += lang(""s, u8" of "s) + _homename(inv_param1(prm_518))
                + lang(u8"の"s, ""s);
        }
        if (inv_id(prm_518) == 615)
        {
            s_at_m63 += lang(
                ""s + inv_subname(prm_518) + u8"goldの"s,
                u8" <"s + inv_subname(prm_518) + u8" gp>"s);
        }
        if (inv_id(prm_518) == 704)
        {
            if (inv_subname(prm_518) < 0 || inv_subname(prm_518) >= 800)
            {
                s_at_m63 += u8"/bugged/"s;
                return;
            }
            s_at_m63 += lang(
                ""s + refchara_str(inv_subname(prm_518), 2) + u8"の"s,
                u8" of "s + refchara_str(inv_subname(prm_518), 2));
        }
    }
    if (inv_id(prm_518) == 672)
    {
        if (inv_param1(prm_518) == 169)
        {
            s_at_m63 += lang(u8"善人の"s, u8" of saint"s);
        }
        if (inv_param1(prm_518) == 162)
        {
            s_at_m63 += lang(u8"悪人の"s, u8" of wicked"s);
        }
        if (inv_param1(prm_518) == 163)
        {
            s_at_m63 += lang(u8"エヘカトルの"s, u8" of Ehekatl"s);
        }
        if (inv_param1(prm_518) == 164)
        {
            s_at_m63 += lang(u8"オパートスの"s, u8" of Opatos"s);
        }
        if (inv_param1(prm_518) == 165)
        {
            s_at_m63 += lang(u8"イツパロトルの"s, u8" of Itzpalt"s);
        }
        if (inv_param1(prm_518) == 166)
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
    int ret_at_m63 = 0;
    elona::prm_518 = prm_518;
    itemnamehack = inv_id(prm_518) + 1;
    if (inv_id(prm_518) >= maxitemid - 2
        || inv_id(prm_518) > length(ioriginalnameref))
    {
        itemnamehack = 0;
        return lang(
            u8"未知のアイテム(バージョン非互換)"s,
            u8"unknown item (incompatible version)"s);
    }
    if (inv_quality(prm_518) >= 5)
    {
        iqiality_at_m63(prm_518) = 5;
    }
    item_checkknown(prm_518);
    if (prm_519 == 0)
    {
        num2_at_m63 = inv_number(prm_518);
    }
    else
    {
        num2_at_m63 = prm_519;
    }
    a_at_m63 = refitem(inv_id(prm_518), 5);
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
                if (inv_id(prm_518) == 783)
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
            if (a_at_m63 == 68000 || a_at_m63 == 69000 || inv_id(prm_518) == 622
                || inv_id(prm_518) == 724 || inv_id(prm_518) == 730)
            {
                s2_at_m63 = u8"枚の"s;
            }
            if (inv_id(prm_518) == 618)
            {
                s2_at_m63 = u8"匹の"s;
            }
            s_at_m63 = ""s + num2_at_m63 + s2_at_m63;
        }
        else
        {
            s_at_m63 = "";
        }
        if (inv_identification_state(prm_518) >= 3)
        {
            if (inv_curse_state(prm_518) == 1)
            {
                s_at_m63 += strblessed;
            }
            if (inv_curse_state(prm_518) == -1)
            {
                s_at_m63 += strcursed;
            }
            if (inv_curse_state(prm_518) == -2)
            {
                s_at_m63 += strdoomed;
            }
        }
    }
    else
    {
        s_at_m63 = "";
        if (inv_identification_state(prm_518) >= 3)
        {
            if (inv_curse_state(prm_518) == 1)
            {
                s_at_m63 = strblessed + u8" "s;
            }
            if (inv_curse_state(prm_518) == -1)
            {
                s_at_m63 = strcursed + u8" "s;
            }
            if (inv_curse_state(prm_518) == -2)
            {
                s_at_m63 = strdoomed + u8" "s;
            }
        }
        if (irandomname(inv_id(prm_518)) == 1
            && inv_identification_state(prm_518) < 1)
        {
            s2_at_m63 = "";
        }
        else
        {
            s2_at_m63 = ""s + ioriginalnameref2(inv_id(prm_518));
            if (strutil::contains(ioriginalnameref(inv_id(prm_518)), u8"with"))
            {
                s3_at_m63 = u8"with"s;
            }
            else
            {
                s3_at_m63 = u8"of"s;
            }
            if (inv_identification_state(prm_518) != 0)
            {
                if (s2_at_m63 == ""s)
                {
                    if (inv_weight(prm_518) < 0)
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
                if (inv_param1(prm_518) != 0)
                {
                    if (inv_param2(prm_518) != 0)
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
    if (inv_material(prm_518) == 35)
    {
        if (inv_param3(prm_518) < 0)
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
            if (inv_param1(prm_518) != 0)
            {
                if (inv_param2(prm_518) != 0)
                {
                    skip_at_m63 = 1;
                }
            }
        }
        if (inv_subname(prm_518) != 0)
        {
            if (a_at_m63 == 60000)
            {
                if (inv_subname(prm_518) >= 12)
                {
                    inv_subname(prm_518) = 0;
                }
                else
                {
                    s_at_m63 += _furniture(inv_subname(prm_518)) + u8" "s;
                }
            }
        }
        if (inv_id(prm_518) == 687)
        {
            if (inv_param2(prm_518) != 0)
            {
                s_at_m63 += u8"undecoded "s;
            }
        }
        if (inv_id(prm_518) == 783)
        {
            if (inv_subname(prm_518) == 0)
            {
                s_at_m63 += u8"custom "s;
            }
        }
    }
    if (inv_id(prm_518) == 630)
    {
        s_at_m63 +=
            ""s + mtname(0, inv_material(prm_518)) + lang(u8"製の"s, u8" "s);
    }
    if (jp)
    {
        label_0311();
    }
    if (a_at_m63 == 60000)
    {
        if (inv_material(prm_518) != 0)
        {
            if (jp)
            {
                s_at_m63 +=
                    ""s + mtname(0, inv_material(prm_518)) + u8"細工の"s;
            }
            else
            {
                s_at_m63 += ""s + mtname(0, inv_material(prm_518)) + u8"work "s;
            }
        }
    }
    if (inv_id(prm_518) == 729)
    {
        s_at_m63 += ""s + giftn(inv_param4(prm_518)) + lang(""s, u8" "s);
    }
    if (skip_at_m63 == 1)
    {
        goto label_0313_internal;
    }
    alpha_at_m63 = 0;
    if (inv_identification_state(prm_518) >= 3)
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
                if (inv_subname(prm_518) >= 10000)
                {
                    if (inv_subname(prm_518) < 20000)
                    {
                        if (jp)
                        {
                            s_at_m63 += egoname(inv_subname(prm_518) - 10000)
                                + strblank;
                        }
                    }
                    else if (inv_subname(prm_518) < 40000)
                    {
                        s_at_m63 +=
                            egominorn(inv_subname(prm_518) - 20000) + strblank;
                    }
                }
                if (inv_quality(prm_518) != 6)
                {
                    if (inv_quality(prm_518) >= 4)
                    {
                        s_at_m63 += mtname(1, inv_material(prm_518)) + strblank;
                    }
                    else
                    {
                        s_at_m63 += mtname(0, inv_material(prm_518)) + strblank;
                        if (jp)
                        {
                            if (peek(mtname(0, inv_material(prm_518))) == 131)
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
    if (inv_identification_state(prm_518) == 0)
    {
        s_at_m63 += iknownnameref(inv_id(prm_518));
    }
    else if (inv_identification_state(prm_518) < 3)
    {
        if (inv_quality(prm_518) < 4 || a_at_m63 >= 50000)
        {
            s_at_m63 += ioriginalnameref(inv_id(prm_518));
        }
        else
        {
            s_at_m63 += iknownnameref(inv_id(prm_518));
        }
    }
    else if (inv_quality(prm_518) == 6 || ibit(5, prm_518) == 1)
    {
        if (jp)
        {
            s_at_m63 = u8"★"s + s_at_m63 + ioriginalnameref(inv_id(prm_518));
        }
        else
        {
            s_at_m63 += ioriginalnameref(inv_id(prm_518));
        }
    }
    else
    {
        if (inv_quality(prm_518) >= 4)
        {
            if (jp)
            {
                s_at_m63 = u8"☆"s + s_at_m63;
            }
        }
        if (alpha_at_m63 == 1 && jp)
        {
            s_at_m63 += ialphanameref(inv_id(prm_518));
        }
        else
        {
            s_at_m63 += ioriginalnameref(inv_id(prm_518));
        }
        if (en)
        {
            if (a_at_m63 < 50000)
            {
                if (inv_subname(prm_518) >= 10000)
                {
                    if (inv_subname(prm_518) < 20000)
                    {
                        s_at_m63 +=
                            u8" "s + egoname((inv_subname(prm_518) - 10000));
                    }
                }
            }
        }
        if (inv_subname(prm_518) >= 40000)
        {
            randomize(inv_subname(prm_518) - 40000);
            if (inv_quality(prm_518) == 4)
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
            if (inv_identification_state(prm_518) >= 3
                && (inv_quality(prm_518) >= 4 && a_at_m63 < 50000))
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
            if (inv_id(prm_518) != 618)
            {
                if (num2_at_m63 > 1)
                {
                    s_at_m63 += u8"s"s;
                }
            }
        }
        label_0311();
    }
    if (inv_identification_state(prm_518) >= 3)
    {
        if (inv_enhancement(prm_518) != 0)
        {
            s_at_m63 += ""s + cnvfix(inv_enhancement(prm_518)) + u8" "s;
        }
        if (ibit(4, prm_518) == 1)
        {
            s_at_m63 += lang(
                u8"(残り"s + inv_count(prm_518) + u8"回)"s,
                u8"(Charges: "s + inv_count(prm_518) + u8")"s);
        }
        if (inv_dice_x(prm_518) != 0 || inv_hit_bonus(prm_518) != 0
            || inv_damage_bonus(prm_518) != 0)
        {
            s_at_m63 += u8" ("s;
            if (inv_dice_x(prm_518) != 0)
            {
                s_at_m63 +=
                    ""s + inv_dice_x(prm_518) + u8"d"s + inv_dice_y(prm_518);
                if (inv_damage_bonus(prm_518) != 0)
                {
                    if (inv_damage_bonus(prm_518) > 0)
                    {
                        s_at_m63 += u8"+"s + inv_damage_bonus(prm_518);
                    }
                    else
                    {
                        s_at_m63 += ""s + inv_damage_bonus(prm_518);
                    }
                }
                s_at_m63 += u8")"s;
                if (inv_hit_bonus(prm_518) != 0)
                {
                    s_at_m63 += u8"("s + inv_hit_bonus(prm_518) + u8")"s;
                }
            }
            else
            {
                s_at_m63 += ""s + inv_hit_bonus(prm_518) + u8","s
                    + inv_damage_bonus(prm_518) + u8")"s;
            }
        }
        if (inv_dv(prm_518) != 0 || inv_pv(prm_518) != 0)
        {
            s_at_m63 +=
                u8" ["s + inv_dv(prm_518) + u8","s + inv_pv(prm_518) + u8"]"s;
        }
    }
    if (en)
    {
        if (inv_id(prm_518) == 284 || inv_id(prm_518) == 283)
        {
            s_at_m63 += u8"(Lost property)"s;
        }
    }
    if (inv_id(prm_518) == 342)
    {
        if (inv_count(prm_518) != 0)
        {
            s_at_m63 += lang(
                u8"("s + biten(inv_param4(prm_518)) + u8"残り"s
                    + inv_count(prm_518) + u8"匹)"s,
                u8"("s + inv_count(prm_518) + u8" "s
                    + biten(inv_param4(prm_518)) + u8")"s);
        }
    }
    if (inv_id(prm_518) == 685)
    {
        if (inv_subname(prm_518) == 0)
        {
            s_at_m63 += lang(u8" Lv"s, u8" Level "s) + inv_param2(prm_518)
                + lang(u8" (空)"s, u8"(Empty)"s);
        }
        else
        {
            s_at_m63 +=
                u8" ("s + refchara_str(inv_subname(prm_518), 2) + u8")"s;
        }
    }
    if (inv_id(prm_518) == 734)
    {
        s_at_m63 += lang(u8" Lv"s, u8" Level "s) + inv_param2(prm_518);
    }
    if (inv_identification_state(prm_518) == 2)
    {
        if (a_at_m63 < 50000)
        {
            s_at_m63 +=
                u8" ("s + cnven(_quality(inv_quality(prm_518))) + u8")"s;
            if (jp)
            {
                s_at_m63 +=
                    u8"["s + mtname(0, inv_material(prm_518)) + u8"製]"s;
            }
            else
            {
                s_at_m63 +=
                    u8"["s + cnven(mtname(0, inv_material(prm_518))) + u8"]"s;
            }
            if (inv_curse_state(prm_518) == -1)
            {
                s_at_m63 += lang(u8"(恐ろしい)"s, u8"(Scary)"s);
            }
            if (inv_curse_state(prm_518) == -2)
            {
                s_at_m63 += lang(u8"(禍々しい)"s, u8"(Dreadful)"s);
            }
        }
    }
    if (a_at_m63 == 72000)
    {
        if (inv_id(prm_518) == 361)
        {
            s_at_m63 += lang(u8"(移動時消滅)"s, u8"(Temporal)"s);
        }
        else if (inv_count(prm_518) == 0)
        {
            if (inv_param1(prm_518) == 0)
            {
                s_at_m63 += lang(u8"(空っぽ)"s, u8"(Empty)"s);
            }
        }
    }
    if (a_at_m63 == 92000)
    {
        if (inv_param2(prm_518) != 0)
        {
            s_at_m63 += lang(
                u8"(仕入れ値 "s + inv_param2(prm_518) + u8"g)"s,
                u8"(Buying price: "s + inv_param2(prm_518) + u8")"s);
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
            < inv_count(prm_518))
        {
            s_at_m63 += lang(
                u8"("s
                    + (inv_count(prm_518)
                       - (gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
                          + gdata_year * 24 * 30 * 12))
                    + u8"時間)"s,
                u8"(Next: "s
                    + (inv_count(prm_518)
                       - (gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
                          + gdata_year * 24 * 30 * 12))
                    + u8"h.)"s);
        }
    }
    if (inv_id(prm_518) == 555)
    {
        if (inv_count(prm_518) != 0)
        {
            s_at_m63 +=
                lang(u8" シリアルNo."s, u8" serial no."s) + inv_count(prm_518);
        }
    }
    if (inv_id(prm_518) == 544)
    {
        s_at_m63 += u8" <BGM"s + inv_param1(prm_518) + u8">"s;
    }
    if (strlen_u(s_at_m63) > 66)
    {
        len_at_m63 = zentohan(s_at_m63, buf_at_m63, 0);
        SDIM2(buf_at_m63, len_at_m63);
        ret_at_m63 = zentohan(s_at_m63, s_at_m63, len_at_m63);
    }
    skip_at_m63 = 0;
    itemnamehack = 0;
    return s_at_m63;
}



void remain_make(int prm_521, int prm_522)
{
    inv_subname(prm_521) = cdata_id(prm_522);
    inv_color(prm_521) = cdata_image(prm_522) / 1000;
    inv_weight(prm_521) = cdata_weight(prm_522);
    if (inv_id(prm_521) == 204)
    {
        inv_weight(prm_521) = 250 * (inv_weight(prm_521) + 100) / 100 + 500;
        inv_value(prm_521) = inv_weight(prm_521) / 5;
    }
    else
    {
        inv_weight(prm_521) = 20 * (inv_weight(prm_521) + 500) / 500;
        inv_value(prm_521) = cdata_level(prm_522) * 40 + 600;
        if (refchara(cdata_id(prm_522), 6) < 20)
        {
            if (cdata_original_relationship(prm_522) < -1)
            {
                inv_value(prm_521) =
                    inv_value(prm_521)
                    * std::clamp(
                          (4 - refchara(cdata_id(prm_522), 6) / 5), 1, 5);
            }
        }
    }
    return;
}



void make_dish(int prm_523, int prm_524)
{
    inv_image(prm_523) = picfood(prm_524, inv_param1(prm_523) / 1000);
    inv_weight(prm_523) = 500;
    if (inv_material(prm_523) == 35)
    {
        if (inv_param3(prm_523) >= 0)
        {
            inv_param3(prm_523) = gdata_hour + gdata_day * 24
                + gdata_month * 24 * 30 + gdata_year * 24 * 30 * 12 + 72;
        }
    }
    inv_param2(prm_523) = prm_524;
    return;
}



int item_stack(int prm_525, int prm_526, int prm_527)
{
    elona_vector1<int> p_at_m65;
    inv_getheader(prm_525);
    p_at_m65 = 0;
    if (inv_quality(prm_526) == 6)
    {
        if (refitem(inv_id(prm_526), 5) < 50000)
        {
            return p_at_m65;
        }
    }
    {
        int cnt = invhead;
        for (int cnt_end = cnt + (invrange); cnt < cnt_end; ++cnt)
        {
            if (cnt == prm_526)
            {
                continue;
            }
            if (inv_number(cnt) == 0)
            {
                continue;
            }
            if (inv_id(cnt) != inv_id(prm_526))
            {
                continue;
            }
            if (inv_id(cnt) == 622)
            {
                if (prm_525 == -1 && mode != 6)
                {
                    if (inv_x(cnt) != inv_x(prm_526)
                        || inv_y(cnt) != inv_y(prm_526))
                    {
                        continue;
                    }
                }
                p_at_m65(2) = 0;
                goto label_0319_internal;
            }
            p_at_m65(1) = cnt;
            p_at_m65(2) = 0;
            {
                int cnt = 0;
                for (int cnt_end = cnt + (70); cnt < cnt_end; ++cnt)
                {
                    if (cnt == 0 || cnt == 4 || cnt == 30)
                    {
                        continue;
                    }
                    if (prm_525 != -1 || mode == 6)
                    {
                        if (cnt == 5 || cnt == 6)
                        {
                            continue;
                        }
                    }
                    if (inv(cnt, p_at_m65(1)) != inv(cnt, prm_526))
                    {
                        ++p_at_m65(2);
                        break;
                    }
                }
            }
        label_0319_internal:
            if (p_at_m65(2) == 0)
            {
                inv_number(cnt) += inv_number(prm_526);
                inv_number(prm_526) = 0;
                p_at_m65 = 1;
                ti = cnt;
                break;
            }
        }
    }
    if (p_at_m65 == 1)
    {
        if (mode != 6)
        {
            if (inv_getowner(prm_526) == -1)
            {
                cell_refresh(inv_x(prm_526), inv_y(prm_526));
            }
        }
        if (prm_527 != 0)
        {
            txtmore();
            txt(lang(
                itemname(ti, 1) + u8"をまとめた(計"s + inv_number(ti)
                    + u8"個) "s,
                itemname(ti, 1) + u8" has been stacked. (Total:"s
                    + inv_number(ti) + u8")"s));
        }
    }
    return p_at_m65;
}



} // namespace elona

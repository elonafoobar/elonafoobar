#include "ai.hpp"
#include "ability.hpp"
#include "animation.hpp"
#include "audio.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "command.hpp"
#include "fov.hpp"
#include "item.hpp"
#include "item_db.hpp"
#include "itemgen.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "random.hpp"
#include "status_ailment.hpp"
#include "variables.hpp"

namespace elona
{

// TODO integrate chunks of npc_turn() here

int blockedbychara = 0;

int ai_check()
{
    for (int cnt = 0; cnt < 3; ++cnt)
    {
        if (dir == 2)
        {
            cdata[cc].next_position.x = cdata[cc].position.x + 1;
            cdata[cc].next_position.y = dirchk(cnt, p) + cdata[cc].position.y;
        }
        if (dir == 1)
        {
            cdata[cc].next_position.x = cdata[cc].position.x - 1;
            cdata[cc].next_position.y = dirchk(cnt, p) + cdata[cc].position.y;
        }
        if (dir == 3)
        {
            cdata[cc].next_position.y = cdata[cc].position.y - 1;
            cdata[cc].next_position.x = dirchk(cnt, p) + cdata[cc].position.x;
        }
        if (dir == 0)
        {
            cdata[cc].next_position.y = cdata[cc].position.y + 1;
            cdata[cc].next_position.x = dirchk(cnt, p) + cdata[cc].position.x;
        }
        cell_check(cdata[cc].next_position.x, cdata[cc].next_position.y);
        if (cellaccess == 1)
        {
            break;
        }
        if (cellchara != -1)
        {
            if (cdata[cc].relationship == 10)
            {
                if (cdata[cellchara].relationship == -3)
                {
                    cdata[cc].enemy_id = cellchara;
                }
                else
                {
                    blockedbychara = 1;
                }
            }
            if (cdata[cc].relationship == -3)
            {
                if (cdata[cellchara].relationship == 10)
                {
                    cdata[cc].enemy_id = cellchara;
                }
                else
                {
                    blockedbychara = 1;
                }
            }
        }
        if (cellfeat != -1)
        {
            if (cellfeat == 21)
            {
                cellaccess = 1;
                break;
            }
        }
    }
    if (cellaccess == 1)
    {
        return 1;
    }
    return 0;
}

turn_result_t ai_proc_basic()
{
    if (tc == 0)
    {
        pcattacker = cc;
    }
    int act = choice(cdata[cc].normal_actions);
    if (cdata[cc].ai_act_sub_freq != 0)
    {
        if (cdata[cc].ai_act_sub_freq > rnd(100))
        {
            if (!cdata[cc].special_actions.empty())
            {
                act = choice(cdata[cc].special_actions);
            }
            if (act >= -10000 && act < -9995)
            {
                if (distance < 8)
                {
                    if (fov_los(
                            cdata[cc].position.x,
                            cdata[cc].position.y,
                            cdata[tc].position.x,
                            cdata[tc].position.y))
                    {
                        tlocx = cdata[tc].position.x;
                        tlocy = cdata[tc].position.y;
                        int stat = 0;
                        if (act == -9999)
                        {
                            flt();
                            flttypemajor = 52000;
                            stat = itemcreate(
                                cc,
                                isetthrowpotionminor(
                                    rnd(length(isetthrowpotionminor))),
                                -1,
                                -1,
                                0);
                        }
                        if (act == -9998)
                        {
                            flt();
                            flttypemajor = 52000;
                            stat = itemcreate(
                                cc,
                                isetthrowpotionmajor(
                                    rnd(length(isetthrowpotionmajor))),
                                -1,
                                -1,
                                0);
                        }
                        if (act == -9997)
                        {
                            flt();
                            flttypemajor = 52000;
                            stat = itemcreate(
                                cc,
                                isetthrowpotiongreater(
                                    rnd(length(isetthrowpotiongreater))),
                                -1,
                                -1,
                                0);
                        }
                        if (act == -9996)
                        {
                            flt();
                            stat = itemcreate(cc, 698, -1, -1, 0);
                        }
                        if (stat == 1)
                        {
                            return do_throw_command();
                        }
                        return turn_result_t::turn_end;
                    }
                }
            }
        }
    }
    if (act == -4)
    {
        cdata[cc].next_position.x = rnd(3) - 1 + cdata[cc].position.x;
        cdata[cc].next_position.y = rnd(3) - 1 + cdata[cc].position.y;
        cell_check(cdata[cc].next_position.x, cdata[cc].next_position.y);
        if (cellaccess == 1)
        {
            return proc_movement_event();
        }
        else
        {
            return turn_result_t::turn_end;
        }
    }
    if (act == -2)
    {
        if (distance < 6)
        {
            if (fov_los(
                    cdata[cc].position.x,
                    cdata[cc].position.y,
                    cdata[tc].position.x,
                    cdata[tc].position.y))
            {
                int stat = can_do_ranged_attack();
                if (stat == 1)
                {
                    do_ranged_attack();
                    return turn_result_t::turn_end;
                }
            }
        }
    }
    if (act >= 400)
    {
        if (act < 467)
        {
            efid = act;
            if (cdata[cc].mp < cdata[cc].max_mp / 7)
            {
                if (rnd(3) || cc < 16 || cdata[cc].quality >= 4
                    || cdata[cc].cures_mp_frequently())
                {
                    cdata[cc].mp += cdata[cc].level / 4 + 5;
                    return turn_result_t::turn_end;
                }
            }
            npccostmp = 1;
            int stat = label_2167();
            if (stat == 1)
            {
                return turn_result_t::turn_end;
            }
        }
    }
    if (act >= 600)
    {
        efid = act;
        int stat = label_2174();
        if (stat == 1)
        {
            return turn_result_t::turn_end;
        }
    }
    if (act == -3)
    {
        if (distance == 1)
        {
            try_to_melee_attack();
        }
        else if (rnd(3) == 0 || cc < 16)
        {
            if (distance < 6)
            {
                if (fov_los(
                        cdata[cc].position.x,
                        cdata[cc].position.y,
                        cdata[tc].position.x,
                        cdata[tc].position.y))
                {
                    int stat = can_do_ranged_attack();
                    if (stat == 1)
                    {
                        do_ranged_attack();
                        return turn_result_t::turn_end;
                    }
                }
            }
        }
        return turn_result_t::turn_end;
    }
    if (distance == 1)
    {
        try_to_melee_attack();
        return turn_result_t::turn_end;
    }
    if (distance < 6)
    {
        if (fov_los(
                cdata[cc].position.x,
                cdata[cc].position.y,
                cdata[tc].position.x,
                cdata[tc].position.y))
        {
            int stat = can_do_ranged_attack();
            if (stat == 1)
            {
                do_ranged_attack();
                return turn_result_t::turn_end;
            }
        }
    }
    if (cdata[cc].ai_dist <= distance)
    {
        if (rnd(3) == 0)
        {
            return turn_result_t::turn_end;
        }
    }
    if (rnd(5) == 0)
    {
        --cdata[cc].hate;
    }
    if (rnd(100) < cdata[cc].ai_move)
    {
        return proc_npc_movement_event();
    }
    else
    {
        return turn_result_t::turn_end;
    }
}

turn_result_t proc_npc_movement_event(bool retreat)
{
    if (mdata(6) == 3)
    {
        if (cc < 16)
        {
            if (rnd(100) == 0)
            {
                sell(0) = 0;
                sell(1) = 0;
                for (const auto& cnt : items(cc))
                {
                    if (inv[cnt].number == 0)
                    {
                        continue;
                    }
                    int category = the_item_db[inv[cnt].id]->category;
                    if (category == 77000)
                    {
                        p = inv[cnt].value * inv[cnt].number;
                        sell += inv[cnt].number;
                        sell(1) += p;
                        item_remove(inv[cnt]);
                        cdata[cc].gold += p;
                    }
                }
                if (sell != 0)
                {
                    txtef(9);
                    txt(lang(
                        name(cc) + u8"は"s + sell
                            + u8"個のアイテムを売りさばき"s + sell(1)
                            + u8"goldを稼いだ。"s,
                        name(cc) + u8" sells "s + sell + u8" items and earns "s
                            + sell(1) + u8" gold pieces."s));
                }
            }
            if (rnd(100) == 0)
            {
                if (cdata[cc].gold >= cdata[cc].level * 500)
                {
                    cdata[cc].gold -= cdata[cc].level * 500;
                    snd(61);
                    txtef(9);
                    txt(lang(
                        cdatan(0, cc) + u8"は訓練所に通い潜在能力を伸ばした！"s,
                        cdatan(0, cc) + u8" visits a trainer and develops "s
                            + his(cc) + u8" potential!"s));
                    for (int cnt = 0; cnt < 4; ++cnt)
                    {
                        while (1)
                        {
                            if (rnd(4) == 0)
                            {
                                p = rnd(8) + 10;
                            }
                            else
                            {
                                p = rnd(300) + 100;
                            }
                            if (sdata.get(p, cc).original_level == 0)
                            {
                                continue;
                            }
                            modify_potential(cc, p, 4);
                            break;
                        }
                    }
                    chara_refresh(cc);
                }
            }
        }
    }
    if (tc == cc)
    {
        cdata[cc].enemy_id = 0;
        return turn_result_t::turn_end;
    }
    if (cdata[cc]._203 <= 0)
    {
        cdata[cc]._205 = cdata[tc].position.x;
        cdata[cc]._206 = cdata[tc].position.y;
        if (retreat || cdata[cc].ai_dist > distance)
        {
            cdata[cc]._205 = cdata[cc].position.x
                + (cdata[cc].position.x - cdata[tc].position.x);
            cdata[cc]._206 = cdata[cc].position.y
                + (cdata[cc].position.y - cdata[tc].position.y);
        }
    }
    else
    {
        --cdata[cc]._203;
    }
    blockedbychara = 0;
    cdata[cc].next_position.x = (cdata[cc]._205 > cdata[cc].position.x)
        - (cdata[cc]._205 < cdata[cc].position.x) + cdata[cc].position.x;
    cdata[cc].next_position.y = (cdata[cc]._206 > cdata[cc].position.y)
        - (cdata[cc]._206 < cdata[cc].position.y) + cdata[cc].position.y;
    x = cdata[cc].next_position.x;
    y = cdata[cc].next_position.y;
    cell_check(x, y);
    if (cellaccess == 1)
    {
        return proc_movement_event();
    }
    if (cellchara != -1)
    {
        tc = cellchara;
        if (relationbetween(cc, tc) == -3)
        {
            cdata[cc].enemy_id = tc;
            cdata[cc].hate += 4;
            distance = dist(
                cdata[tc].position.x,
                cdata[tc].position.y,
                cdata[cc].position.x,
                cdata[cc].position.y);
            return ai_proc_basic();
        }
        else if (
            (cdata[cc].quality > 3 && cdata[cc].level > cdata[tc].level)
            || cdata[tc].is_hung_on_sand_bag())
        {
            if (cdata[cc].enemy_id != tc)
            {
                const auto did_swap = cell_swap(cc, tc);
                if (did_swap && is_in_fov(cc))
                {
                    txt(lang(
                        name(cc) + u8"は"s + name(tc) + u8"を押しのけた。"s,
                        name(cc) + u8" displace"s + _s(cc) + u8" "s + name(tc)
                            + u8"."s));
                }
                if (cdata[tc].continuous_action_id == 1)
                {
                    if (cdata[tc].continuous_action_turn > 0)
                    {
                        if (is_in_fov(cc))
                        {
                            txt(lang(
                                name(tc) + u8"は"s + name(cc)
                                    + u8"を睨み付けた。"s,
                                name(tc) + u8" glare"s + _s(tc) + u8" "s
                                    + name(cc) + u8"."s));
                        }
                        rowactend(tc);
                    }
                }
                return turn_result_t::turn_end;
            }
        }
    }
    if (cc >= 16)
    {
        if (cdata[cc].quality > 3)
        {
            if (cdata[cc].relationship <= -2)
            {
                if (x >= 0)
                {
                    if (x < mdata(0))
                    {
                        if (y >= 0)
                        {
                            if (y < mdata(1))
                            {
                                if (chipm(7, map(x, y, 0)) & 4)
                                {
                                    if (rnd(4) == 0)
                                    {
                                        map(x, y, 0) = tile_tunnel;
                                        snd(45);
                                        play_animation(14);
                                        spillfrag(x, y, 2);
                                        if (is_in_fov(cc))
                                        {
                                            txt(lang(
                                                name(cc)
                                                    + u8"は壁を破壊した！"s,
                                                name(cc) + u8" crush"s + _s(cc)
                                                    + u8" the wall!"s));
                                        }
                                        return turn_result_t::turn_end;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (std::abs(cdata[cc]._205 - cdata[cc].position.x)
        >= std::abs(cdata[cc]._206 - cdata[cc].position.y))
    {
        {
            int stat = label_2694();
            if (stat == 1)
            {
                return proc_movement_event();
            }
        }
        {
            int stat = label_2695();
            if (stat == 1)
            {
                return proc_movement_event();
            }
        }
    }
    else
    {
        {
            int stat = label_2695();
            if (stat == 1)
            {
                return proc_movement_event();
            }
        }
        {
            int stat = label_2694();
            if (stat == 1)
            {
                return proc_movement_event();
            }
        }
    }
    if (cdata[cc]._203 > 0)
    {
        cdata[cc].next_position.x = rnd(3) - 1 + cdata[cc].position.x;
        cdata[cc].next_position.y = rnd(3) - 1 + cdata[cc].position.y;
        cell_check(cdata[cc].next_position.x, cdata[cc].next_position.y);
        if (cellaccess == 1)
        {
            return proc_movement_event();
        }
    }
    else
    {
        if (blockedbychara == 1)
        {
            cdata[cc]._203 = 3;
        }
        else
        {
            cdata[cc]._203 = 6;
        }
        dir = dir(1 + rnd(2));
        if (dir == 1)
        {
            cdata[cc]._205 = cdata[cc].position.x - 6;
            cdata[cc]._206 = cdata[tc].position.y;
        }
        if (dir == 2)
        {
            cdata[cc]._205 = cdata[cc].position.x + 6;
            cdata[cc]._206 = cdata[tc].position.y;
        }
        if (dir == 3)
        {
            cdata[cc]._206 = cdata[cc].position.y - 6;
            cdata[cc]._205 = cdata[tc].position.x;
        }
        if (dir == 0)
        {
            cdata[cc]._206 = cdata[cc].position.y + 6;
            cdata[cc]._205 = cdata[tc].position.x;
        }
    }
    return turn_result_t::turn_end;
}

int label_2694()
{
    if (cdata[cc]._205 > cdata[cc].position.x)
    {
        if (cdata[cc]._206 > cdata[cc].position.y)
        {
            p = 1;
        }
        else
        {
            p = 0;
        }
        dir(0) = 2;
        dir(1) = 0;
        dir(2) = 3;
        int stat = ai_check();
        if (stat == 1)
        {
            return 1;
        }
    }
    if (cdata[cc]._205 < cdata[cc].position.x)
    {
        if (cdata[cc]._206 < cdata[cc].position.y)
        {
            p = 0;
        }
        else
        {
            p = 1;
        }
        dir(0) = 1;
        dir(1) = 0;
        dir(2) = 3;
        int stat = ai_check();
        if (stat == 1)
        {
            return 1;
        }
    }
    return 0;
}

int label_2695()
{
    if (cdata[cc]._206 > cdata[cc].position.y)
    {
        if (cdata[cc]._205 > cdata[cc].position.x)
        {
            p = 1;
        }
        else
        {
            p = 0;
        }
        dir(0) = 0;
        dir(1) = 1;
        dir(2) = 2;
        int stat = ai_check();
        if (stat == 1)
        {
            return 1;
        }
    }
    if (cdata[cc]._206 < cdata[cc].position.y)
    {
        if (cdata[cc]._205 > cdata[cc].position.x)
        {
            p = 0;
        }
        else
        {
            p = 1;
        }
        dir(0) = 3;
        dir(1) = 1;
        dir(2) = 2;
        int stat = ai_check();
        if (stat == 1)
        {
            return 1;
        }
    }
    return 0;
}

turn_result_t ai_proc_misc_map_events()
{
    if (cdata[cc].ai_calm == 4)
    {
        tc = 0;
        distance = dist(
            cdata[tc].position.x,
            cdata[tc].position.y,
            cdata[cc].position.x,
            cdata[cc].position.y);
        return proc_npc_movement_event();
    }
    if (rnd(5) != 0)
    {
        return turn_result_t::turn_end;
    }
    if (cdata[cc].drunk != 0)
    {
        if (is_in_fov(cc))
        {
            if (cdatan(2, cc) == u8"cat"s)
            {
                if (cdata[cc].drunk < 5)
                {
                    cdata[cc].drunk += 40;
                }
            label_2691_internal:
                if (jp)
                {
                    if (rnd(3) == 0)
                    {
                        txt(u8"「米さ米種だろ♪」"s,
                            u8"「飲ま飲まイェイ！！」"s,
                            u8"「飲ま飲ま飲まイェイ！！」"s);
                        goto label_2692_internal;
                    }
                    if (rnd(4) == 0)
                    {
                        txt(u8"「字ベロ♪指♪ラマ♪ｸﾏｰ!!して♪パンチラ♪」"s,
                            u8"「アロー♪アーロン♪スゲェ♪ピカソ♪算段ビーフ♪」"s,
                            u8"「キスすごい肉♪脱線してんの♪さらに肉♪」"s);
                        goto label_2692_internal;
                    }
                    if (rnd(4) == 0)
                    {
                        txt(u8"「キープダルシム♪アゴスタディーイェイ♪並フェイスで大きい筆入れ♪」"s,
                            u8"「ハロー♪猿ー♪すげー♪うん入る♪」"s);
                        goto label_2692_internal;
                    }
                    if (rnd(4) == 0)
                    {
                        txtef(4);
                        txt(u8" *ﾋﾟﾛﾘ〜ﾋﾟﾛﾘ〜* "s);
                        goto label_2692_internal;
                    }
                    txt(u8"「マイアヒー♪」"s,
                        u8"「マイアフゥー♪」"s,
                        u8"「マイアホー♪」"s);
                    goto label_2692_internal;
                }
                else
                {
                    if (rnd(2) == 0)
                    {
                        txt(u8"\"Vrei sa pleci dar♪\""s,
                            u8"\"Numa numa yay!!\""s,
                            u8"\"Numa numa numa yay!!\""s);
                        goto label_2692_internal;
                    }
                    txt(u8"\"Mai-Ya-Hi♪\""s,
                        u8"\"Mai-Ya-Hoo♪\""s,
                        u8"\"Mai-Ya-Ha Ma Mi A♪\""s);
                    goto label_2692_internal;
                }
                goto label_2691_internal;
            }
        }
    }
label_2692_internal:
    if (cc >= 16)
    {
        if (mdata(6) == 3 || mdata(6) == 2)
        {
            if (gdata_hour >= 22 || gdata_hour < 7)
            {
                if (cdata[cc].continuous_action_id == 0)
                {
                    if (rnd(100) == 0)
                    {
                        dmgcon(cc, status_ailment_t::sleep, 4000);
                    }
                }
            }
        }
    }
    if (cdata[cc].item_which_will_be_used == 0)
    {
        if (cdata[cc].relationship != 10)
        {
            if (gdata_current_map == 13)
            {
                if (gdata_executing_immediate_quest_type == 1009)
                {
                    if (rnd(30) == 0)
                    {
                        flt(20);
                        if (rnd(4) == 0)
                        {
                            flttypemajor = 57000;
                        }
                        else
                        {
                            flttypemajor = 52000;
                            if (rnd(8))
                            {
                                flttypeminor = 52002;
                            }
                        }
                        int stat = itemcreate(cc, 0, -1, -1, 0);
                        if (stat == 1)
                        {
                            cdata[cc].item_which_will_be_used = ci;
                        }
                    }
                }
            }
            if (gdata_current_map == 33 || gdata_current_map == 29)
            {
                if (cdata[cc].id == 35 || cdata[cc].id == 211)
                {
                    if (is_in_fov(cc))
                    {
                        if (chipm(
                                0,
                                map(cdata[cc].position.x,
                                    cdata[cc].position.y,
                                    0))
                            == 4)
                        {
                            if (rnd(4) == 0)
                            {
                                if (cdata[gdata_fire_giant].state == 1)
                                {
                                    if (is_in_fov(gdata_fire_giant))
                                    {
                                        flt();
                                        int stat =
                                            itemcreate(cc, 587, -1, -1, 0);
                                        if (stat == 1)
                                        {
                                            tlocx = cdata[gdata_fire_giant]
                                                        .position.x;
                                            tlocy = cdata[gdata_fire_giant]
                                                        .position.y;
                                            txtef(9);
                                            txt(lang(
                                                    u8"「化け物め！」"s,
                                                    u8"\"Filthy monster!\""s),
                                                lang(
                                                    u8"「くたばれっ」"s,
                                                    u8"\"Go to hell!\""s),
                                                lang(
                                                    u8"「退治してやるぅ！」"s,
                                                    u8"\"I'll get rid of you.\""s),
                                                lang(
                                                    u8"「くらえー！」"s,
                                                    u8"\"Eat this!\""s));
                                            return do_throw_command();
                                        }
                                    }
                                }
                            }
                            if (rnd(12) == 0)
                            {
                                bool found_snowman{};
                                for (const auto& cnt : itemlist(-1, 541))
                                {
                                    ti = cnt;
                                    if (inv[ti].position.x >= scx
                                        && inv[ti].position.x
                                            < scx + inf_screenw
                                        && inv[ti].position.y >= scy
                                        && inv[ti].position.y
                                            < scy + inf_screenh)
                                    {
                                        found_snowman = true;
                                        break;
                                    }
                                }
                                if (found_snowman)
                                {
                                    flt();
                                    int stat = itemcreate(cc, 587, -1, -1, 0);
                                    if (stat == 1)
                                    {
                                        tlocx = inv[ti].position.x;
                                        tlocy = inv[ti].position.y;
                                        return do_throw_command();
                                    }
                                }
                            }
                            if (rnd(10) == 0)
                            {
                                if (map(cdata[cc].position.x,
                                        cdata[cc].position.y,
                                        4)
                                    == 0)
                                {
                                    flt();
                                    int stat = itemcreate(
                                        -1,
                                        541,
                                        cdata[cc].position.x,
                                        cdata[cc].position.y,
                                        0);
                                    if (stat == 1)
                                    {
                                        snd(86);
                                        txt(lang(
                                            name(cc) + u8"は"s + itemname(ci)
                                                + u8"を作った！"s,
                                            name(cc) + u8" make"s + _s(cc)
                                                + u8" "s + itemname(ci)
                                                + u8"!"s));
                                        return turn_result_t::turn_end;
                                    }
                                }
                            }
                            if (rnd(12) == 0)
                            {
                                flt();
                                int stat = itemcreate(cc, 587, -1, -1, 0);
                                if (stat == 1)
                                {
                                    tlocx = cdata[0].position.x;
                                    tlocy = cdata[0].position.y;
                                    txtef(9);
                                    txt(lang(u8" *クスクス* "s, u8"*grin*"s),
                                        lang(
                                            u8"「えいっ」"s,
                                            u8"\"Fire in the hole!\""s),
                                        lang(
                                            u8"「うりゃ」"s,
                                            u8"\"Tee-hee-hee!\""s),
                                        lang(
                                            u8"「くらえー！」"s,
                                            u8"\"Eat this!\""s),
                                        lang(
                                            u8"「危ないっ！」"s,
                                            u8"\"Watch out!\""s),
                                        lang(
                                            u8"「避けてー」"s, u8"\"Scut!\""s));
                                    return do_throw_command();
                                }
                            }
                        }
                    }
                }
            }
            if (cdata[cc].nutrition <= 6000)
            {
                if (cdata[cc].vision_flag != msync || rnd(5))
                {
                    if (cdata[cc].has_anorexia() == 0)
                    {
                        cdata[cc].nutrition += 5000;
                    }
                    else
                    {
                        cdata[cc].nutrition -= 3000;
                    }
                }
                else
                {
                    flt(20);
                    p(0) = rnd(4);
                    if (p == 0 || cdata[cc].has_anorexia())
                    {
                        flttypemajor = 57000;
                    }
                    if (p == 1)
                    {
                        flttypemajor = 52000;
                    }
                    if (p == 2 || p == 3)
                    {
                        flttypeminor = 52002;
                    }
                    int stat = itemcreate(cc, 0, -1, -1, 0);
                    if (stat == 1 && the_item_db[inv[ci].id]->is_drinkable)
                    {
                        if (inv[ci].id == 577)
                        {
                            if (rnd(5) == 0)
                            {
                                item_remove(inv[ci]);
                            }
                        }
                        else
                        {
                            cdata[cc].item_which_will_be_used = ci;
                            if (cdata[cc].has_anorexia() == 0)
                            {
                                cdata[cc].nutrition += 5000;
                            }
                            else
                            {
                                cdata[cc].nutrition -= 3000;
                            }
                        }
                    }
                }
            }
        }
    }
    if (cdata[cc].ai_calm == 5)
    {
        if (cdata[cc].id == 326)
        {
            if (rnd(5) == 0)
            {
                efid = 183;
                magic();
                return turn_result_t::turn_end;
            }
        }
        if (cdata[cc].id == 320 || cdata[cc].id == 280)
        {
            if (is_in_fov(cc))
            {
                tc = 0;
                distance = dist(
                    cdata[tc].position.x,
                    cdata[tc].position.y,
                    cdata[cc].position.x,
                    cdata[cc].position.y);
                if (distance < 8)
                {
                    if (cdatan(2, 0) == u8"snail"s)
                    {
                        tlocx = cdata[0].position.x;
                        tlocy = cdata[0].position.y;
                        flt();
                        int stat = itemcreate(cc, 698, -1, -1, 0);
                        if (stat == 1)
                        {
                            if (is_in_fov(cc))
                            {
                                txtef(9);
                                txt(lang(
                                        u8"「なめくじだ！」"s, u8"\"Snail!\""s),
                                    lang(u8"「殺す！」"s, u8"\"Kill!\""s));
                            }
                            return do_throw_command();
                        }
                    }
                }
            }
        }
        if (cdata[cc].id == 335 || cdata[cc].id == 352)
        {
            if (rnd(10) == 0)
            {
                for (int cnt = ELONA_MAX_PARTY_CHARACTERS; cnt < 97; ++cnt)
                {
                    if (cdata[cnt].state != 1)
                    {
                        continue;
                    }
                    if (rnd(3) == 0)
                    {
                        continue;
                    }
                    if (dist(
                            cdata[cc].position.x,
                            cdata[cc].position.y,
                            cdata[cnt].position.x,
                            cdata[cnt].position.y)
                        < 6)
                    {
                        if (fov_los(
                                cdata[cc].position.x,
                                cdata[cc].position.y,
                                cdata[cnt].position.x,
                                cdata[cnt].position.y))
                        {
                            cdata[cc].enemy_id = cnt;
                            tc = cnt;
                            break;
                        }
                    }
                }
            }
            distance = dist(
                cdata[tc].position.x,
                cdata[tc].position.y,
                cdata[cc].position.x,
                cdata[cc].position.y);
            if (tc != 0)
            {
                if (distance == 1)
                {
                    if (cdata[tc].continuous_action_id == 0)
                    {
                        cdata[cc].enemy_id = 0;
                        continuous_action_sex();
                        return turn_result_t::turn_end;
                    }
                }
                if (distance < 6)
                {
                    return proc_npc_movement_event();
                }
            }
        }
        cdata[cc].next_position.x = rnd(3) - 1 + cdata[cc].position.x;
        cdata[cc].next_position.y = rnd(3) - 1 + cdata[cc].position.y;
        cell_check(cdata[cc].next_position.x, cdata[cc].next_position.y);
        if (cellaccess == 1)
        {
            return proc_movement_event();
        }
    }
    if (cdata[cc].ai_calm == 1)
    {
        cdata[cc].next_position.x = rnd(3) - 1 + cdata[cc].position.x;
        cdata[cc].next_position.y = rnd(3) - 1 + cdata[cc].position.y;
        cell_check(cdata[cc].next_position.x, cdata[cc].next_position.y);
        if (cellaccess == 1)
        {
            return proc_movement_event();
        }
    }
    if (cdata[cc].ai_calm == 2)
    {
        if (mdata(8) == 1
            && dist(
                   cdata[cc].position.x,
                   cdata[cc].position.y,
                   cdata[cc].initial_position.x,
                   cdata[cc].initial_position.y)
                > 2)
        {
            cdata[cc].next_position.x = cdata[cc].position.x
                + rnd(2)
                    * ((cdata[cc].position.x > cdata[cc].initial_position.x)
                           * -1
                       + (cdata[cc].position.x < cdata[cc].initial_position.x));
            cdata[cc].next_position.y = cdata[cc].position.y
                + rnd(2)
                    * ((cdata[cc].position.y > cdata[cc].initial_position.y)
                           * -1
                       + (cdata[cc].position.y < cdata[cc].initial_position.y));
        }
        else
        {
            cdata[cc].next_position.x = rnd(3) - 1 + cdata[cc].position.x;
            cdata[cc].next_position.y = rnd(3) - 1 + cdata[cc].position.y;
        }
        cell_check(cdata[cc].next_position.x, cdata[cc].next_position.y);
        if (cellaccess == 1)
        {
            return proc_movement_event();
        }
    }
    return turn_result_t::turn_end;
}

} // namespace elona

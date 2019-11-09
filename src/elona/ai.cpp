#include "ai.hpp"
#include "ability.hpp"
#include "activity.hpp"
#include "animation.hpp"
#include "audio.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "command.hpp"
#include "data/types/type_item.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "magic.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "message.hpp"
#include "random.hpp"
#include "status_ailment.hpp"
#include "variables.hpp"

// TODO integrate chunks of npc_turn() here



namespace
{

bool _blockedbychara = false;



enum class Direction
{
    south,
    west,
    east,
    north,
};



bool _ai_check(Character& chara, Direction direction, int p)
{
    assert(p == 0 || p == 1);

    elona_vector2<int> dirchk;
    DIM3(dirchk, 3, 2);

    dirchk(0, 0) = -1;
    dirchk(1, 0) = 0;
    dirchk(2, 0) = 1;
    dirchk(0, 1) = 1;
    dirchk(1, 1) = 0;
    dirchk(2, 1) = -1;

    for (int cnt = 0; cnt < 3; ++cnt)
    {
        switch (direction)
        {
        case Direction::south:
            chara.next_position.y = chara.position.y + 1;
            chara.next_position.x = dirchk(cnt, p) + chara.position.x;
            break;
        case Direction::west:
            chara.next_position.x = chara.position.x - 1;
            chara.next_position.y = dirchk(cnt, p) + chara.position.y;
            break;
        case Direction::east:
            chara.next_position.x = chara.position.x + 1;
            chara.next_position.y = dirchk(cnt, p) + chara.position.y;
            break;
        case Direction::north:
            chara.next_position.y = chara.position.y - 1;
            chara.next_position.x = dirchk(cnt, p) + chara.position.x;
            break;
        }

        cell_check(chara.next_position.x, chara.next_position.y);

        if (cellaccess == 1)
        {
            break;
        }
        if (cellchara != -1)
        {
            if (chara.relationship == 10)
            {
                if (cdata[cellchara].relationship == -3)
                {
                    chara.enemy_id = cellchara;
                }
                else
                {
                    _blockedbychara = true;
                }
            }
            if (chara.relationship == -3)
            {
                if (cdata[cellchara].relationship == 10)
                {
                    chara.enemy_id = cellchara;
                }
                else
                {
                    _blockedbychara = true;
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

    return cellaccess == 1;
}



bool _ai_dir_check_x()
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
        const auto ok = _ai_check(cdata[cc], static_cast<Direction>(dir(0)), p);
        if (ok)
        {
            return true;
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
        const auto ok = _ai_check(cdata[cc], static_cast<Direction>(dir(0)), p);
        if (ok)
        {
            return true;
        }
    }
    return false;
}



bool _ai_dir_check_y()
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
        const auto ok = _ai_check(cdata[cc], static_cast<Direction>(dir(0)), p);
        if (ok)
        {
            return true;
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
        const auto ok = _ai_check(cdata[cc], static_cast<Direction>(dir(0)), p);
        if (ok)
        {
            return true;
        }
    }
    return false;
}



// TODO: move it to random.hpp
bool _percent(int percentage)
{
    return percentage <= 0 ? false : percentage > rnd(100);
}



bool _is_special_throwing_action(int action_id)
{
    return -9999 <= action_id && action_id <= -9996;
}



// TODO: move it to fov.cpp
bool fov_los_helper(const Position& a, const Position& b)
{
    return fov_los(a.x, a.y, b.x, b.y);
}



// TODO: move it to fov.cpp
bool fov_los_helper(const Character& a, const Character& b)
{
    return fov_los_helper(a.position, b.position);
}



bool _try_generate_special_throwing_item(const Character& chara, int action_id)
{
    flt();
    switch (action_id)
    {
    case -9999:
        flttypemajor = 52000;
        return !!itemcreate(
            chara.index, choice(isetthrowpotionminor), -1, -1, 0);
    case -9998:
        flttypemajor = 52000;
        return !!itemcreate(
            chara.index, choice(isetthrowpotionmajor), -1, -1, 0);
    case -9997:
        flttypemajor = 52000;
        return !!itemcreate(
            chara.index, choice(isetthrowpotiongreater), -1, -1, 0);
    case -9996: return !!itemcreate(chara.index, 698, -1, -1, 0);
    default: assert(0); return false;
    }
}



// Helper function: normalize the return value of `can_do_ranged_attack()` to
// boolean.
bool can_do_ranged_attack_helper()
{
    int stat = can_do_ranged_attack();
    return stat == 1;
}



bool _try_do_melee_attack(const Character& attacker, const Character& target)
{
    if (distance >= 6)
    {
        return false; // Too far.
    }
    if (!fov_los_helper(attacker, target))
    {
        return false; // Cannot see the target.
    }
    if (!can_do_ranged_attack_helper())
    {
        return false; // Cannot do ranged attack.
    }

    do_ranged_attack();
    return true;
}

} // namespace



namespace elona
{

TurnResult ai_proc_basic(Character& chara)
{
    if (tc == 0)
    {
        pcattacker = chara.index;
    }

    int act = choice(chara.normal_actions);

    if (_percent(chara.ai_act_sub_freq))
    {
        if (!chara.special_actions.empty())
        {
            act = choice(chara.special_actions);
        }
        if (_is_special_throwing_action(act) && distance < 8 &&
            fov_los_helper(chara, cdata[tc]))
        {
            tlocx = cdata[tc].position.x;
            tlocy = cdata[tc].position.y;
            const auto ok = _try_generate_special_throwing_item(chara, act);
            if (ok)
            {
                return do_throw_command();
            }
            return TurnResult::turn_end;
        }
    }

    // Move around randomly.
    if (act == -4)
    {
        chara.next_position.x = rnd(3) - 1 + chara.position.x;
        chara.next_position.y = rnd(3) - 1 + chara.position.y;
        cell_check(chara.next_position.x, chara.next_position.y);
        if (cellaccess == 1)
        {
            return proc_movement_event();
        }
        else
        {
            return TurnResult::turn_end;
        }
    }

    // Do ranged attack.
    if (act == -2)
    {
        const auto ok = _try_do_melee_attack(chara, cdata[tc]);
        if (ok)
        {
            return TurnResult::turn_end;
        }
    }

    // Do any spact.
    if (act >= 400 && act < 467)
    {
        efid = act;
        if (chara.mp < chara.max_mp / 7)
        {
            if (rnd(3) || chara.index < 16 ||
                chara.quality >= Quality::miracle ||
                chara.cures_mp_frequently())
            {
                chara.mp += chara.level / 4 + 5;
                return TurnResult::turn_end;
            }
        }
        const auto ok = do_cast_magic();
        if (ok)
        {
            return TurnResult::turn_end;
        }
    }

    // Cast any spell.
    if (act >= 600)
    {
        efid = act;
        const auto ok = do_magic_attempt();
        if (ok)
        {
            return TurnResult::turn_end;
        }
    }

    // Do melee attack if the attacker stands next to the enemy; otherwise, try
    // to do ranged attack if possible.
    if (act == -3)
    {
        if (distance == 1)
        {
            try_to_melee_attack();
        }
        else if (rnd(3) == 0 || chara.index < 16)
        {
            const auto ok = _try_do_melee_attack(chara, cdata[tc]);
            if (ok)
            {
                return TurnResult::turn_end;
            }
        }
        return TurnResult::turn_end;
    }

    // Do melee attack if the attacker stands next to the enemy.
    if (distance == 1)
    {
        try_to_melee_attack();
        return TurnResult::turn_end;
    }

    // Try to do ranged attack if possible.
    {
        const auto ok = _try_do_melee_attack(chara, cdata[tc]);
        if (ok)
        {
            return TurnResult::turn_end;
        }
    }

    if (chara.ai_dist <= distance)
    {
        if (rnd(3) == 0)
        {
            return TurnResult::turn_end;
        }
    }
    if (rnd(5) == 0)
    {
        --chara.hate;
    }
    if (rnd(100) < chara.ai_move)
    {
        return proc_npc_movement_event();
    }
    else
    {
        return TurnResult::turn_end;
    }
}



TurnResult proc_npc_movement_event(bool retreat)
{
    if (map_data.type == mdata_t::MapType::town)
    {
        if (cc < 16)
        {
            if (rnd(100) == 0)
            {
                sell(0) = 0;
                sell(1) = 0;
                for (auto&& item : inv.for_chara(cdata[cc]))
                {
                    if (item.number() == 0)
                    {
                        continue;
                    }
                    if (the_item_db[itemid2int(item.id)]->category == 77000)
                    {
                        p = item.value * item.number();
                        sell += item.number();
                        sell(1) += p;
                        item.remove();
                        earn_gold(cdata[cc], p);
                    }
                }
                if (sell != 0)
                {
                    txt(i18n::s.get(
                            "core.ai.ally.sells_items",
                            cdata[cc],
                            sell(0),
                            sell(1)),
                        Message::color{ColorIndex::cyan});
                }
            }
            if (rnd(100) == 0)
            {
                if (cdata[cc].gold >= cdata[cc].level * 500)
                {
                    cdata[cc].gold -= cdata[cc].level * 500;
                    snd("core.ding3");
                    txt(i18n::s.get("core.ai.ally.visits_trainer", cdata[cc]),
                        Message::color{ColorIndex::cyan});
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
                            modify_potential(cdata[cc], p, 4);
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
        return TurnResult::turn_end;
    }
    if (cdata[cc]._203 <= 0)
    {
        cdata[cc]._205 = cdata[tc].position.x;
        cdata[cc]._206 = cdata[tc].position.y;
        if (retreat || cdata[cc].ai_dist > distance)
        {
            cdata[cc]._205 = cdata[cc].position.x +
                (cdata[cc].position.x - cdata[tc].position.x);
            cdata[cc]._206 = cdata[cc].position.y +
                (cdata[cc].position.y - cdata[tc].position.y);
        }
    }
    else
    {
        --cdata[cc]._203;
    }
    _blockedbychara = false;
    cdata[cc].next_position.x = (cdata[cc]._205 > cdata[cc].position.x) -
        (cdata[cc]._205 < cdata[cc].position.x) + cdata[cc].position.x;
    cdata[cc].next_position.y = (cdata[cc]._206 > cdata[cc].position.y) -
        (cdata[cc]._206 < cdata[cc].position.y) + cdata[cc].position.y;
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
            return ai_proc_basic(cdata[cc]);
        }
        else if (
            (cdata[cc].quality > Quality::great &&
             cdata[cc].level > cdata[tc].level) ||
            cdata[tc].is_hung_on_sand_bag())
        {
            if (cdata[cc].enemy_id != tc)
            {
                const auto did_swap = cell_swap(cc, tc);
                if (did_swap && is_in_fov(cdata[cc]))
                {
                    txt(i18n::s.get(
                        "core.ai.swap.displace", cdata[cc], cdata[tc]));
                }
                if (cdata[tc].activity.type == Activity::Type::eat)
                {
                    if (cdata[tc].activity.turn > 0)
                    {
                        if (is_in_fov(cdata[cc]))
                        {
                            txt(i18n::s.get(
                                "core.ai.swap.glare", cdata[cc], cdata[tc]));
                        }
                        cdata[tc].activity.finish();
                    }
                }
                return TurnResult::turn_end;
            }
        }
    }
    if (cc >= 16)
    {
        if (cdata[cc].quality > Quality::great)
        {
            if (cdata[cc].relationship <= -2)
            {
                if (x >= 0)
                {
                    if (x < map_data.width)
                    {
                        if (y >= 0)
                        {
                            if (y < map_data.height)
                            {
                                if (chip_data.for_cell(x, y).effect & 4)
                                {
                                    if (rnd(4) == 0)
                                    {
                                        cell_data.at(x, y).chip_id_actual =
                                            tile_tunnel;
                                        snd("core.crush1");
                                        BreakingAnimation({x, y}).play();
                                        spillfrag(x, y, 2);
                                        if (is_in_fov(cdata[cc]))
                                        {
                                            txt(i18n::s.get(
                                                "core.ai.crushes_wall",
                                                cdata[cc]));
                                        }
                                        return TurnResult::turn_end;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (std::abs(cdata[cc]._205 - cdata[cc].position.x) >=
        std::abs(cdata[cc]._206 - cdata[cc].position.y))
    {
        {
            int stat = _ai_dir_check_x();
            if (stat == 1)
            {
                return proc_movement_event();
            }
        }
        {
            int stat = _ai_dir_check_y();
            if (stat == 1)
            {
                return proc_movement_event();
            }
        }
    }
    else
    {
        {
            int stat = _ai_dir_check_y();
            if (stat == 1)
            {
                return proc_movement_event();
            }
        }
        {
            int stat = _ai_dir_check_x();
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
        if (_blockedbychara)
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
    return TurnResult::turn_end;
}



TurnResult ai_proc_misc_map_events()
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
        return TurnResult::turn_end;
    }
    if (cdata[cc].drunk != 0)
    {
        if (is_in_fov(cdata[cc]))
        {
            if (cdatan(2, cc) == u8"core.cat"s)
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
                        txt(u8" *ﾋﾟﾛﾘ〜ﾋﾟﾛﾘ〜* "s,
                            Message::color{ColorIndex::blue});
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
        if (map_is_town_or_guild())
        {
            if (game_data.date.hour >= 22 || game_data.date.hour < 7)
            {
                if (!cdata[cc].activity)
                {
                    if (rnd(100) == 0)
                    {
                        status_ailment_damage(
                            cdata[cc], StatusAilment::sleep, 4000);
                    }
                }
            }
        }
    }
    if (cdata[cc].item_which_will_be_used == 0)
    {
        if (cdata[cc].relationship != 10)
        {
            if (game_data.current_map == mdata_t::MapId::quest)
            {
                if (game_data.executing_immediate_quest_type == 1009)
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
                        if (itemcreate(cc, 0, -1, -1, 0))
                        {
                            cdata[cc].item_which_will_be_used = ci;
                        }
                    }
                }
            }
            if (map_villagers_make_snowmen())
            {
                if (cdata[cc].id == CharaId::town_child ||
                    cdata[cc].id == CharaId::young_lady)
                {
                    if (is_in_fov(cdata[cc]))
                    {
                        if (chip_data
                                .for_cell(
                                    cdata[cc].position.x, cdata[cc].position.y)
                                .kind == 4)
                        {
                            if (rnd(4) == 0)
                            {
                                if (cdata[game_data.fire_giant].state() ==
                                    Character::State::alive)
                                {
                                    if (is_in_fov(cdata[game_data.fire_giant]))
                                    {
                                        flt();
                                        if (itemcreate(cc, 587, -1, -1, 0))
                                        {
                                            tlocx = cdata[game_data.fire_giant]
                                                        .position.x;
                                            tlocy = cdata[game_data.fire_giant]
                                                        .position.y;
                                            txt(i18n::s.get(
                                                    "core.ai.fire_giant"),
                                                Message::color{
                                                    ColorIndex::cyan});
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
                                    if (inv[ti].position.x >= scx &&
                                        inv[ti].position.x <
                                            scx + inf_screenw &&
                                        inv[ti].position.y >= scy &&
                                        inv[ti].position.y < scy + inf_screenh)
                                    {
                                        found_snowman = true;
                                        break;
                                    }
                                }
                                if (found_snowman)
                                {
                                    flt();
                                    if (itemcreate(cc, 587, -1, -1, 0))
                                    {
                                        tlocx = inv[ti].position.x;
                                        tlocy = inv[ti].position.y;
                                        return do_throw_command();
                                    }
                                }
                            }
                            if (rnd(10) == 0)
                            {
                                if (cell_data
                                        .at(cdata[cc].position.x,
                                            cdata[cc].position.y)
                                        .item_appearances_actual == 0)
                                {
                                    flt();
                                    if (itemcreate(
                                            -1,
                                            541,
                                            cdata[cc].position.x,
                                            cdata[cc].position.y,
                                            0))
                                    {
                                        snd("core.snow");
                                        txt(i18n::s.get(
                                            "core.ai.makes_snowman",
                                            cdata[cc],
                                            inv[ci]));
                                        return TurnResult::turn_end;
                                    }
                                }
                            }
                            if (rnd(12) == 0)
                            {
                                flt();
                                if (itemcreate(cc, 587, -1, -1, 0))
                                {
                                    tlocx = cdata.player().position.x;
                                    tlocy = cdata.player().position.y;
                                    txt(i18n::s.get("core.ai.snowball"),
                                        Message::color{ColorIndex::cyan});
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
                    if (itemcreate(cc, 0, -1, -1, 0) &&
                        the_item_db[itemid2int(inv[ci].id)]->is_drinkable)
                    {
                        if (inv[ci].id == ItemId::molotov)
                        {
                            if (rnd(5) == 0)
                            {
                                inv[ci].remove();
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
        if (cdata[cc].id == CharaId::bard)
        {
            if (rnd(5) == 0)
            {
                efid = 183;
                magic();
                return TurnResult::turn_end;
            }
        }
        if (cdata[cc].id == CharaId::cleaner || cdata[cc].id == CharaId::balzak)
        {
            if (is_in_fov(cdata[cc]))
            {
                tc = 0;
                distance = dist(
                    cdata[tc].position.x,
                    cdata[tc].position.y,
                    cdata[cc].position.x,
                    cdata[cc].position.y);
                if (distance < 8)
                {
                    if (cdatan(2, 0) == u8"core.snail"s)
                    {
                        tlocx = cdata.player().position.x;
                        tlocy = cdata.player().position.y;
                        flt();
                        if (itemcreate(cc, 698, -1, -1, 0))
                        {
                            if (is_in_fov(cdata[cc]))
                            {
                                txt(i18n::s.get("core.ai.snail"),
                                    Message::color{ColorIndex::cyan});
                            }
                            return do_throw_command();
                        }
                    }
                }
            }
        }
        if (cdata[cc].id == CharaId::prostitute ||
            cdata[cc].id == CharaId::silvia)
        {
            if (rnd(10) == 0)
            {
                for (int cnt = ELONA_MAX_PARTY_CHARACTERS; cnt < 97; ++cnt)
                {
                    if (cdata[cnt].state() != Character::State::alive)
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
                            cdata[cnt].position.y) < 6)
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
                    if (!cdata[tc].activity)
                    {
                        cdata[cc].enemy_id = 0;
                        activity_sex();
                        return TurnResult::turn_end;
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
        if (map_data.designated_spawns == 1 &&
            dist(
                cdata[cc].position.x,
                cdata[cc].position.y,
                cdata[cc].initial_position.x,
                cdata[cc].initial_position.y) > 2)
        {
            cdata[cc].next_position.x = cdata[cc].position.x +
                rnd(2) *
                    ((cdata[cc].position.x > cdata[cc].initial_position.x) *
                         -1 +
                     (cdata[cc].position.x < cdata[cc].initial_position.x));
            cdata[cc].next_position.y = cdata[cc].position.y +
                rnd(2) *
                    ((cdata[cc].position.y > cdata[cc].initial_position.y) *
                         -1 +
                     (cdata[cc].position.y < cdata[cc].initial_position.y));
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
    return TurnResult::turn_end;
}

} // namespace elona

#include "ai.hpp"

#include "ability.hpp"
#include "activity.hpp"
#include "animation.hpp"
#include "attack.hpp"
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
    if (cdata[cc].target_position.x > cdata[cc].position.x)
    {
        if (cdata[cc].target_position.y > cdata[cc].position.y)
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
    if (cdata[cc].target_position.x < cdata[cc].position.x)
    {
        if (cdata[cc].target_position.y < cdata[cc].position.y)
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
    if (cdata[cc].target_position.y > cdata[cc].position.y)
    {
        if (cdata[cc].target_position.x > cdata[cc].position.x)
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
    if (cdata[cc].target_position.y < cdata[cc].position.y)
    {
        if (cdata[cc].target_position.x > cdata[cc].position.x)
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
    return rnd(100) < percentage;
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



int dist_helper(const Position& a, const Position& b)
{
    return dist(a.x, a.y, b.x, b.y);
}



int dist_helper(const Character& a, const Character& b)
{
    return dist_helper(a.position, b.position);
}



bool _try_generate_special_throwing_item(const Character& chara, int action_id)
{
    switch (action_id)
    {
    case -9999:
        flt();
        flttypemajor = 52000;
        return !!itemcreate_chara_inv(
            chara.index, choice(isetthrowpotionminor), 0);
    case -9998:
        flt();
        flttypemajor = 52000;
        return !!itemcreate_chara_inv(
            chara.index, choice(isetthrowpotionmajor), 0);
    case -9997:
        flt();
        flttypemajor = 52000;
        return !!itemcreate_chara_inv(
            chara.index, choice(isetthrowpotiongreater), 0);
    case -9996: flt(); return !!itemcreate_chara_inv(chara.index, 698, 0);
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



void _ally_sells_item(Character& chara)
{
    int sold_item_count = 0;
    int earned_money = 0;

    for (auto&& item : inv.for_chara(chara))
    {
        if (item.number() == 0)
        {
            continue;
        }
        if (the_item_db[itemid2int(item.id)]->category == ItemCategory::ore)
        {
            sold_item_count += item.number();
            const auto total_value = item.value * item.number();
            earned_money += total_value;
            item.remove();
            earn_gold(chara, total_value);
        }
    }
    if (sold_item_count != 0)
    {
        txt(i18n::s.get(
                "core.ai.ally.sells_items",
                chara,
                sold_item_count,
                earned_money),
            Message::color{ColorIndex::cyan});
    }
}



int _calc_training_price(const Character& chara)
{
    return chara.level * 500;
}



void _ally_trains(Character& chara)
{
    // TODO: overflow check
    const auto training_price = _calc_training_price(chara);
    if (chara.gold < training_price)
    {
        return; // Does not have enough money.
    }

    chara.gold -= training_price;
    snd("core.ding3");
    txt(i18n::s.get("core.ai.ally.visits_trainer", chara),
        Message::color{ColorIndex::cyan});

    for (int _i = 0; _i < 4; ++_i)
    {
        while (true)
        {
            const auto skill_id = rnd(4) == 0 ? rnd(8) + 10 : rnd(300) + 100;
            if (sdata.get(skill_id, chara.index).original_level == 0)
            {
                continue;
            }
            modify_potential(chara, skill_id, 4);
            break;
        }
    }

    chara_refresh(chara.index);
}



bool _is_valid_position(int x, int y)
{
    return 0 <= x && x < map_data.width && 0 <= y && y < map_data.height;
}



bool _will_crush_wall(const Character& chara, int x, int y)
{
    return chara.index >= 16 && chara.quality >= Quality::miracle &&
        chara.relationship <= -2 && _is_valid_position(x, y) &&
        (chip_data.for_cell(x, y).effect & 4);
}



const std::string& _chara_get_race(const Character& chara)
{
    return cdatan(2, chara.index);
}



// Handle 『恋のマイアヒ』
void _proc_drunk_cat(Character& chara)
{
    if (chara.drunk < 5)
    {
        chara.drunk += 40;
    }

    if (const auto music =
            i18n::s.get_optional("core.ai.dragostea_din_tei.music"))
    {
        if (rnd(25) < 3)
        {
            txt(*music, Message::color{ColorIndex::blue});
            return;
        }
    }
    txt(i18n::s.get("core.ai.dragostea_din_tei.sing"));
}



bool _is_at_night()
{
    return game_data.date.hour >= 22 || game_data.date.hour < 7;
}



optional<TurnResult> _proc_make_snowman(Character& chara)
{
    // Throws a snowball to <Ebon> if he is released.
    if (rnd(4) == 0)
    {
        if (cdata[game_data.fire_giant].state() == Character::State::alive &&
            is_in_fov(cdata[game_data.fire_giant]))
        {
            flt();
            if (itemcreate_chara_inv(chara.index, 587, 0))
            {
                tlocx = cdata[game_data.fire_giant].position.x;
                tlocy = cdata[game_data.fire_giant].position.y;
                txt(i18n::s.get("core.ai.fire_giant"),
                    Message::color{ColorIndex::cyan});
                return do_throw_command();
            }
        }
    }

    // Throws a snowball to a snowman.
    if (rnd(12) == 0)
    {
        optional_ref<Item> target_snowman;
        for (const auto& snowman_ref_wrapper : itemlist(-1, 541))
        {
            auto&& snowman = snowman_ref_wrapper.get();
            if (snowman.position.x >= scx &&
                snowman.position.x < scx + inf_screenw &&
                snowman.position.y >= scy &&
                snowman.position.y < scy + inf_screenh)
            {
                target_snowman = snowman;
                break;
            }
        }
        if (target_snowman)
        {
            flt();
            if (itemcreate_chara_inv(chara.index, 587, 0))
            {
                tlocx = target_snowman->position.x;
                tlocy = target_snowman->position.y;
                return do_throw_command();
            }
        }
    }

    // Makes a snowman.
    if (rnd(10) == 0)
    {
        if (cell_data.at(chara.position.x, chara.position.y)
                .item_appearances_actual == 0)
        {
            flt();
            if (const auto item = itemcreate_extra_inv(541, chara.position, 0))
            {
                snd("core.snow");
                txt(i18n::s.get("core.ai.makes_snowman", chara, *item));
                return TurnResult::turn_end;
            }
        }
    }

    // Throws a snowball to you.
    if (rnd(12) == 0)
    {
        flt();
        if (itemcreate_chara_inv(chara.index, 587, 0))
        {
            tlocx = cdata.player().position.x;
            tlocy = cdata.player().position.y;
            txt(i18n::s.get("core.ai.snowball"),
                Message::color{ColorIndex::cyan});
            return do_throw_command();
        }
    }

    return none; // Did nothing.
}



void _change_nutrition(Character& chara)
{
    if (chara.has_anorexia())
    {
        chara.nutrition -= 3000;
    }
    else
    {
        chara.nutrition += 5000;
    }
}



void _proc_hungry(Character& chara)
{
    if (chara.vision_flag != msync || rnd(5))
    {
        _change_nutrition(chara);
    }
    else
    {
        flt(20);
        p = rnd(4);
        // TODO: maybe, is "!chara.has_anorexia()" intended?
        if (p == 0 || chara.has_anorexia())
        {
            flttypemajor = 57000;
        }
        if (p == 1)
        {
            flttypemajor = 52000;
        }
        else if (p == 2 || p == 3)
        {
            flttypeminor = 52002;
        }
        if (const auto item = itemcreate_chara_inv(chara.index, 0, 0))
        {
            if (the_item_db[itemid2int(item->id)]->is_drinkable)
            {
                if (item->id == ItemId::molotov)
                {
                    if (rnd(5) == 0)
                    {
                        item->remove();
                    }
                }
                else
                {
                    chara.item_which_will_be_used = item->index;
                    _change_nutrition(chara);
                }
            }
            else
            {
                item->remove();
            }
        }
    }
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
        return proc_npc_movement_event(chara);
    }
    else
    {
        return TurnResult::turn_end;
    }
}



TurnResult proc_npc_movement_event(Character& chara, bool retreat)
{
    if (map_data.type == mdata_t::MapType::town && chara.index < 16)
    {
        if (rnd(100) == 0)
        {
            _ally_sells_item(chara);
        }
        if (rnd(100) == 0)
        {
            _ally_trains(chara);
        }
    }

    if (tc == chara.index)
    {
        chara.enemy_id = 0;
        return TurnResult::turn_end;
    }

    if (chara._203 <= 0)
    {
        chara.target_position = cdata[tc].position;
        if (retreat || chara.ai_dist > distance)
        {
            chara.target_position.x =
                chara.position.x + (chara.position.x - cdata[tc].position.x);
            chara.target_position.y =
                chara.position.y + (chara.position.y - cdata[tc].position.y);
        }
    }
    else
    {
        --chara._203;
    }

    _blockedbychara = false;
    chara.next_position.x = (chara.target_position.x > chara.position.x) -
        (chara.target_position.x < chara.position.x) + chara.position.x;
    chara.next_position.y = (chara.target_position.y > chara.position.y) -
        (chara.target_position.y < chara.position.y) + chara.position.y;
    x = chara.next_position.x;
    y = chara.next_position.y;
    cell_check(x, y);
    if (cellaccess == 1)
    {
        return proc_movement_event();
    }
    if (cellchara != -1)
    {
        tc = cellchara;
        if (relationbetween(chara.index, tc) == -3)
        {
            chara.enemy_id = tc;
            chara.hate += 4;
            distance = dist_helper(cdata[tc], chara);
            return ai_proc_basic(chara);
        }
        else if (
            (chara.quality > Quality::great && chara.level > cdata[tc].level) ||
            cdata[tc].is_hung_on_sand_bag())
        {
            if (chara.enemy_id != tc)
            {
                const auto did_swap = cell_swap(chara.index, tc);
                if (did_swap && is_in_fov(chara))
                {
                    txt(i18n::s.get("core.ai.swap.displace", chara, cdata[tc]));
                }
                if (cdata[tc].activity.type == Activity::Type::eat)
                {
                    if (cdata[tc].activity.turn > 0)
                    {
                        if (is_in_fov(chara))
                        {
                            txt(i18n::s.get(
                                "core.ai.swap.glare", chara, cdata[tc]));
                        }
                        cdata[tc].activity.finish();
                    }
                }
                return TurnResult::turn_end;
            }
        }
    }

    if (_will_crush_wall(chara, x, y))
    {
        if (rnd(4) == 0)
        {
            cell_data.at(x, y).chip_id_actual = tile_tunnel;
            snd("core.crush1");
            BreakingAnimation({x, y}).play();
            spillfrag(x, y, 2);
            if (is_in_fov(chara))
            {
                txt(i18n::s.get("core.ai.crushes_wall", chara));
            }
            return TurnResult::turn_end;
        }
    }

    if (std::abs(chara.target_position.x - chara.position.x) >=
        std::abs(chara.target_position.y - chara.position.y))
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

    if (chara._203 > 0)
    {
        chara.next_position.x = rnd(3) - 1 + chara.position.x;
        chara.next_position.y = rnd(3) - 1 + chara.position.y;
        cell_check(chara.next_position.x, chara.next_position.y);
        if (cellaccess == 1)
        {
            return proc_movement_event();
        }
    }
    else
    {
        if (_blockedbychara)
        {
            chara._203 = 3;
        }
        else
        {
            chara._203 = 6;
        }
        dir = dir(1 + rnd(2));
        if (dir == 1)
        {
            chara.target_position.x = chara.position.x - 6;
            chara.target_position.y = cdata[tc].position.y;
        }
        if (dir == 2)
        {
            chara.target_position.x = chara.position.x + 6;
            chara.target_position.y = cdata[tc].position.y;
        }
        if (dir == 3)
        {
            chara.target_position.y = chara.position.y - 6;
            chara.target_position.x = cdata[tc].position.x;
        }
        if (dir == 0)
        {
            chara.target_position.y = chara.position.y + 6;
            chara.target_position.x = cdata[tc].position.x;
        }
    }

    return TurnResult::turn_end;
}



TurnResult ai_proc_misc_map_events(Character& chara)
{
    // Follows you, e.g., Gwen.
    if (chara.ai_calm == 4)
    {
        tc = 0;
        distance = dist_helper(cdata[tc], chara);
        return proc_npc_movement_event(chara);
    }

    if (rnd(5) != 0)
    {
        return TurnResult::turn_end;
    }

    if (chara.drunk != 0 && _chara_get_race(chara) == "core.cat" &&
        is_in_fov(chara))
    {
        _proc_drunk_cat(chara);
    }

    // Falls into sleep.
    if (chara.index >= 16 && map_is_town_or_guild() && _is_at_night() &&
        !chara.activity)
    {
        if (rnd(100) == 0)
        {
            status_ailment_damage(chara, StatusAilment::sleep, 4000);
        }
    }

    if (chara.item_which_will_be_used == 0 && chara.relationship != 10)
    {
        if (game_data.current_map == mdata_t::MapId::quest &&
            game_data.executing_immediate_quest_type == 1009)
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
                if (const auto item = itemcreate_chara_inv(chara.index, 0, 0))
                {
                    chara.item_which_will_be_used = item->index;
                }
            }
        }
        if (map_villagers_make_snowmen())
        {
            if ((chara.id == CharaId::town_child ||
                 chara.id == CharaId::young_lady) &&
                is_in_fov(chara) &&
                chip_data.for_cell(chara.position.x, chara.position.y).kind ==
                    4)
            {
                const auto turn_result = _proc_make_snowman(chara);
                if (turn_result)
                {
                    return *turn_result;
                }
            }
        }
        if (chara.nutrition <= 6000)
        {
            _proc_hungry(chara);
        }
    }

    // Special AIs.
    if (chara.ai_calm == 5)
    {
        if (chara.id == CharaId::bard)
        {
            if (rnd(5) == 0)
            {
                efid = 183;
                magic();
                return TurnResult::turn_end;
            }
        }
        if (chara.id == CharaId::cleaner || chara.id == CharaId::balzak)
        {
            if (is_in_fov(chara))
            {
                tc = 0;
                distance = dist_helper(cdata[tc], chara);
                if (distance < 8)
                {
                    if (_chara_get_race(cdata.player()) == "core.snail")
                    {
                        tlocx = cdata.player().position.x;
                        tlocy = cdata.player().position.y;
                        flt();
                        if (itemcreate_chara_inv(chara.index, 698, 0))
                        {
                            if (is_in_fov(chara))
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
        if (chara.id == CharaId::prostitute || chara.id == CharaId::silvia)
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
                    if (dist_helper(chara, cdata[cnt]) < 6)
                    {
                        if (fov_los_helper(chara, cdata[cnt]))
                        {
                            chara.enemy_id = cnt;
                            tc = cnt;
                            break;
                        }
                    }
                }
            }
            distance = dist_helper(cdata[tc], chara);
            if (tc != 0)
            {
                if (distance == 1)
                {
                    if (!cdata[tc].activity)
                    {
                        chara.enemy_id = 0;
                        activity_sex();
                        return TurnResult::turn_end;
                    }
                }
                if (distance < 6)
                {
                    return proc_npc_movement_event(chara);
                }
            }
        }

        chara.next_position.x = rnd(3) - 1 + chara.position.x;
        chara.next_position.y = rnd(3) - 1 + chara.position.y;
        cell_check(chara.next_position.x, chara.next_position.y);
        if (cellaccess == 1)
        {
            return proc_movement_event();
        }
    }

    // Roams.
    if (chara.ai_calm == 1)
    {
        chara.next_position.x = rnd(3) - 1 + chara.position.x;
        chara.next_position.y = rnd(3) - 1 + chara.position.y;
        cell_check(chara.next_position.x, chara.next_position.y);
        if (cellaccess == 1)
        {
            return proc_movement_event();
        }
    }

    // Dull.
    if (chara.ai_calm == 2)
    {
        if (map_data.designated_spawns == 1 &&
            dist_helper(chara.position, chara.initial_position) > 2)
        {
            chara.next_position.x = chara.position.x +
                rnd(2) *
                    ((chara.position.x > chara.initial_position.x) * -1 +
                     (chara.position.x < chara.initial_position.x));
            chara.next_position.y = chara.position.y +
                rnd(2) *
                    ((chara.position.y > chara.initial_position.y) * -1 +
                     (chara.position.y < chara.initial_position.y));
        }
        else
        {
            chara.next_position.x = rnd(3) - 1 + chara.position.x;
            chara.next_position.y = rnd(3) - 1 + chara.position.y;
        }
        cell_check(chara.next_position.x, chara.next_position.y);
        if (cellaccess == 1)
        {
            return proc_movement_event();
        }
    }

    return TurnResult::turn_end;
}

} // namespace elona

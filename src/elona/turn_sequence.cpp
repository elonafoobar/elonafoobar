#include "turn_sequence.hpp"
#include "ability.hpp"
#include "activity.hpp"
#include "ai.hpp"
#include "area.hpp"
#include "audio.hpp"
#include "buff.hpp"
#include "building.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "command.hpp"
#include "config.hpp"
#include "ctrl_file.hpp"
#include "data/types/type_item.hpp"
#include "debug.hpp"
#include "deferred_event.hpp"
#include "dmgheal.hpp"
#include "elona.hpp"
#include "food.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "item.hpp"
#include "keybind/input_context.hpp"
#include "lua_env/event_manager.hpp"
#include "lua_env/lua_env.hpp"
#include "lua_env/lua_event/base_event.hpp"
#include "macro.hpp"
#include "magic.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "mef.hpp"
#include "menu.hpp"
#include "message.hpp"
#include "net.hpp"
#include "quest.hpp"
#include "random.hpp"
#include "save.hpp"
#include "ui.hpp"
#include "ui/ui_menu_keybindings.hpp"
#include "variables.hpp"
#include "wish.hpp"



namespace elona
{

namespace
{

int hour_played;
int ct = 0;



optional<TurnResult> proc_return_or_escape()
{
    --game_data.is_returning_or_escaping;
    if (map_prevents_return())
    {
        game_data.is_returning_or_escaping = 0;
        txt(i18n::s.get("core.magic.return.prevented.normal"));
        return none;
    }
    if (game_data.is_returning_or_escaping <= 0 && !event_has_pending_events())
    {
        f = 0;
        for (const auto& chara : cdata.pets())
        {
            if (chara.state() != Character::State::alive)
            {
                continue;
            }
            if (chara.is_escorted_in_sub_quest())
            {
                f = 1;
            }
        }
        if (f)
        {
            txt(i18n::s.get("core.magic.return.prevented.ally"));
            return none;
        }
        if (1 && cdata.player().inventory_weight_type >= 4)
        {
            txt(i18n::s.get("core.magic.return.prevented.overweight"));
            return none;
        }
        if (game_data.destination_map == game_data.destination_outer_map)
        {
            if (game_data.current_map == game_data.destination_outer_map)
            {
                txt(i18n::s.get("core.common.nothing_happens"));
                return none;
            }
        }
        int stat = quest_is_return_forbidden();
        if (stat == 1)
        {
            txt(i18n::s.get("core.magic.return.you_commit_a_crime"));
            modify_karma(cdata.player(), -10);
        }
        snd("core.teleport1");
        txt(i18n::s.get("core.magic.return.door_opens"));
        if (game_data.destination_map == 41)
        {
            txt(i18n::s.get("core.magic.return.destination_changed"));
        }
        msg_halt();
        update_screen();
        levelexitby = 2;
        return TurnResult::exit_map;
    }
    return none;
}



optional<TurnResult> npc_turn_misc(Character& chara)
{
    // Hung on sandbag
    if (chara.is_hung_on_sand_bag())
    {
        if (is_in_fov(chara))
        {
            if (rnd(30) == 0)
            {
                tc = chara.index;
                txt(i18n::s.get("core.action.npc.sand_bag", chara));
            }
        }
        chara.hate = 0;
        return TurnResult::turn_end;
    }

    // Leash
    if (!is_in_fov(chara) && cdata.player().blind == 0 && chara.is_leashed() &&
        map_data.type != mdata_t::MapType::world_map &&
        game_data.current_map != mdata_t::MapId::pet_arena)
    {
        if (rnd(4) == 0)
        {
            if (chara.index < 16)
            {
                chara.hate = 0;
                chara.enemy_id = 0;
            }
            else
            {
                if (rnd(2))
                {
                    txt(i18n::s.get("core.action.npc.leash.dialog"));
                    hostileaction(0, chara.index);
                }
                if (rnd(4) == 0)
                {
                    chara.is_leashed() = false;
                    txt(i18n::s.get("core.action.npc.leash.untangle", chara),
                        Message::color{ColorIndex::cyan});
                    // TODO: 振りほどいたはずがテレポートする
                }
            }
            tc = 0;
            efid = 619;
            magic();
            return TurnResult::turn_end;
        }
    }

    // Explosion
    if (chara.will_explode_soon())
    {
        tlocx = chara.position.x;
        tlocy = chara.position.y;
        efid = 644;
        magic();
        return TurnResult::turn_end;
    }

    // Enemy
    if (chara.relationship >= 10)
    {
        --chara.hate;
        if (chara.enemy_id == 0 || chara.hate <= 0 ||
            (cdata[chara.enemy_id].relationship >= -2 &&
             cdata[chara.enemy_id].enemy_id != chara.index))
        {
            chara.enemy_id = 0;
            if (pcattacker != 0)
            {
                if (cdata[pcattacker].relationship <= -3 &&
                    cdata[pcattacker].state() == Character::State::alive)
                {
                    if (fov_los(
                            chara.position.x,
                            chara.position.y,
                            cdata[pcattacker].position.x,
                            cdata[pcattacker].position.y))
                    {
                        chara.hate = 5;
                        chara.enemy_id = pcattacker;
                    }
                }
            }
            if (chara.enemy_id == 0)
            {
                if (cdata.player().enemy_id != 0 &&
                    cdata[cdata.player().enemy_id].relationship <= -3 &&
                    cdata[cdata.player().enemy_id].state() ==
                        Character::State::alive)
                {
                    if (fov_los(
                            chara.position.x,
                            chara.position.y,
                            cdata[cdata.player().enemy_id].position.x,
                            cdata[cdata.player().enemy_id].position.y))
                    {
                        chara.hate = 5;
                        chara.enemy_id = cdata.player().enemy_id;
                    }
                }
            }
        }
        if (cdata[chara.enemy_id].is_invisible() &&
            !chara.can_see_invisible() && cdata[chara.enemy_id].wet == 0)
        {
            if (rnd(5))
            {
                chara.enemy_id = 0;
            }
        }
    }
    if (chara.enemy_id != 0)
    {
        if (cdata[chara.enemy_id].state() != Character::State::alive)
        {
            chara.enemy_id = 0;
            chara.hate = 0;
        }
    }

    // Pet arena
    if (game_data.current_map == mdata_t::MapId::pet_arena)
    {
        if (chara.relationship != -3 && chara.relationship != 10)
        {
            if (rnd(40) == 0)
            {
                txt(i18n::s.get("core.action.npc.arena"),
                    Message::color{ColorIndex::blue});
            }
            return ai_proc_misc_map_events(chara);
        }
        chara.hate = 100;
        if (chara.relationship == 10)
        {
            p(0) = -3;
            p(1) = enemyteam;
            p(2) = 15;
        }
        else
        {
            p(0) = 10;
            p(1) = 1;
            p(2) = 16;
        }
        i = chara.enemy_id;
        if (cdata[i].relationship == p &&
            cdata[i].state() == Character::State::alive && i >= p(1) &&
            i < p(1) + p(2))
        {
            if (rnd(10) != 0)
            {
                tc = i;
                return none;
            }
        }
        chara.enemy_id = p(1);
        for (int cnt = 0; cnt < 100; ++cnt)
        {
            i = rnd(p(2)) + p(1);
            if (cdata[i].state() == Character::State::alive)
            {
                if (cdata[i].relationship == p)
                {
                    chara.enemy_id = i;
                    break;
                }
            }
        }
        if (cdata[chara.enemy_id].relationship != p ||
            cdata[chara.enemy_id].state() != Character::State::alive)
        {
            f = 0;
            for (int cnt = p(1), cnt_end = cnt + (p(2)); cnt < cnt_end; ++cnt)
            {
                if (cdata[cnt].state() == Character::State::alive)
                {
                    if (cdata[cnt].relationship == p)
                    {
                        chara.enemy_id = cnt;
                        f = 1;
                        break;
                    }
                }
            }
            if (f == 0)
            {
                if (chara.relationship == 10)
                {
                    petarenawin = 1;
                }
                else
                {
                    petarenawin = 2;
                }
                return TurnResult::turn_end;
            }
        }
    }

    // <Ebon>
    if (game_data.current_map == mdata_t::MapId::noyel)
    {
        if (chara.index != game_data.fire_giant)
        {
            if (chara.index >= 16)
            {
                if (game_data.released_fire_giant != 0)
                {
                    if (cdata[game_data.fire_giant].state() ==
                        Character::State::alive)
                    {
                        chara.enemy_id = game_data.fire_giant;
                        chara.hate = 500;
                    }
                }
            }
        }
    }

    // Mount
    if (game_data.mount != 0)
    {
        if (chara.enemy_id == game_data.mount)
        {
            if (rnd(3))
            {
                chara.enemy_id = 0;
            }
        }
        if (chara.enemy_id == 0)
        {
            if (chara.relationship <= -2)
            {
                if (rnd(3) == 0)
                {
                    chara.enemy_id = game_data.mount;
                }
            }
        }
    }

    tc = chara.enemy_id;

    // Talk
    if (cdatan(4, chara.index) != ""s)
    {
        if (chara.has_custom_talk() == 0)
        {
            if (rnd(30) == 0)
            {
                txt(""s + cdatan(4, chara.index),
                    Message::color{ColorIndex::cyan});
            }
        }
    }
    else if (chara.can_talk != 0 || chara.has_custom_talk())
    {
        if (!chara.is_silent() &&
            cdata.player().position.x > chara.position.x - 10 &&
            cdata.player().position.x < chara.position.x + 10 &&
            cdata.player().position.y > chara.position.y - 10 &&
            cdata.player().position.y < chara.position.y + 10 &&
            cdata.player().activity.type != Activity::Type::perform)
        {
            if (chara.turn % 5 == 0)
            {
                if (rnd(4) == 0)
                {
                    if (chara.hate <= 0)
                    {
                        chara_custom_talk(chara.index, 100);
                    }
                    if (chara.hate > 0)
                    {
                        chara_custom_talk(chara.index, 101);
                    }
                }
            }
        }
    }

    // Chocked
    if (chara.relationship >= 0)
    {
        if (cdata.player().choked)
        {
            if (dist(
                    cdata.player().position.x,
                    cdata.player().position.y,
                    chara.position.x,
                    chara.position.y) == 1)
            {
                x = cdata.player().position.x;
                y = cdata.player().position.y;
                return do_bash();
            }
        }
    }

    // Heal
    if (chara.ai_heal != 0)
    {
        if (chara.hp < chara.max_hp / 4 && (chara.mp > 0 || rnd(5) == 0))
        {
            efid = chara.ai_heal;
            if (efid >= 400 && efid < 467)
            {
                int stat = do_cast_magic();
                if (stat == 1)
                {
                    return TurnResult::turn_end;
                }
            }
            else if (efid >= 600)
            {
                int stat = do_magic_attempt();
                if (stat == 1)
                {
                    return TurnResult::turn_end;
                }
            }
        }
    }

    if (chara.item_which_will_be_used == 0)
    {
        return none;
    }
    ci = chara.item_which_will_be_used;
    if (inv[ci].number() == 0)
    {
        chara.item_which_will_be_used = 0;
        return none;
    }
    if (chara.relationship != 0)
    {
        chara.item_which_will_be_used = 0;
    }

    const auto category = the_item_db[itemid2int(inv[ci].id)]->category;
    if (category == 57000)
    {
        if (chara.relationship != 10 || chara.nutrition <= 6000)
        {
            return do_eat_command();
        }
    }
    if (category == 52000)
    {
        return do_drink_command();
    }
    if (category == 53000)
    {
        return do_read_command();
    }

    chara.item_which_will_be_used = 0;

    return none;
}



TurnResult npc_turn_ai_main(Character& chara)
{
    if (chara.hate > 0 || chara.relationship == 10)
    {
        distance = dist(
            cdata[tc].position.x,
            cdata[tc].position.y,
            chara.position.x,
            chara.position.y);
        if (chara.blind != 0)
        {
            if (rnd(10) > 2)
            {
                return ai_proc_misc_map_events(chara);
            }
        }
        if (chara.confused != 0)
        {
            if (rnd(10) > 3)
            {
                return ai_proc_misc_map_events(chara);
            }
        }
        if (chara.relationship == 10)
        {
            if (tc == 0)
            {
                if (cell_data.at(chara.position.x, chara.position.y)
                        .item_appearances_actual != 0)
                {
                    const auto item_info = cell_itemoncell(chara.position);
                    const auto number = item_info.first;
                    const auto item = item_info.second;
                    if (number == 1)
                    {
                        ci = item;
                        p = the_item_db[itemid2int(inv[ci].id)]->category;
                        if (chara.nutrition <= 6000)
                        {
                            if (p == 57000)
                            {
                                if (inv[ci].own_state <= 0 &&
                                    !is_cursed(inv[ci].curse_state))
                                {
                                    return do_eat_command();
                                }
                            }
                            if (p == 60001)
                            {
                                if (inv[ci].own_state <= 1 &&
                                    inv[ci].param1 >= -5 &&
                                    inv[ci].param3 < 20 &&
                                    inv[ci].id != ItemId::holy_well)
                                {
                                    return do_drink_command();
                                }
                            }
                        }
                        if (p == 68000 || p == 77000)
                        {
                            if (inv[ci].own_state <= 0 &&
                                !inv[ci].is_precious() &&
                                map_data.type != mdata_t::MapType::player_owned)
                            {
                                in = inv[ci].number();
                                if (game_data.mount != chara.index)
                                {
                                    int stat = pick_up_item();
                                    if (stat == 1)
                                    {
                                        return TurnResult::turn_end;
                                    }
                                }
                            }
                        }
                    }
                }
                if (chara.current_map == game_data.current_map)
                {
                    if (chara.is_contracting() == 0)
                    {
                        return ai_proc_misc_map_events(chara);
                    }
                }
                if (distance > 2 || rnd(3))
                {
                    return proc_npc_movement_event(chara);
                }
                else
                {
                    return ai_proc_misc_map_events(chara);
                }
            }
        }
        if (chara.fear != 0)
        {
            return proc_npc_movement_event(chara, true);
        }
        if (chara.blind != 0)
        {
            if (rnd(3))
            {
                return ai_proc_misc_map_events(chara);
            }
        }
        if (distance != chara.ai_dist)
        {
            if (rnd(100) < chara.ai_move)
            {
                return proc_npc_movement_event(chara);
            }
        }
        return ai_proc_basic(chara);
    }

    if (chara.turn % 10 == 1)
    {
        constexpr auto searchfov = 5;
        f = 0;
        for (int cnt = 0, cnt_end = (searchfov); cnt < cnt_end; ++cnt)
        {
            y = chara.position.y - 2 + cnt;
            if (y < 0 || y >= map_data.height)
            {
                continue;
            }
            int c{};
            for (int cnt = 0, cnt_end = (searchfov); cnt < cnt_end; ++cnt)
            {
                x = chara.position.x - 2 + cnt;
                if (x < 0 || x >= map_data.width)
                {
                    continue;
                }
                c = cell_data.at(x, y).chara_index_plus_one - 1;
                if (c <= 0)
                {
                    continue;
                }
                if (chara.original_relationship <= -3)
                {
                    if (cdata[c].relationship > -3)
                    {
                        if (!cdata[c].is_not_attacked_by_enemy())
                        {
                            f = 1;
                            break;
                        }
                    }
                }
                else if (c >= 57)
                {
                    if (cdata[c].original_relationship <= -3)
                    {
                        if (!cdata[c].is_not_attacked_by_enemy())
                        {
                            f = 1;
                            break;
                        }
                    }
                }
            }
            if (f)
            {
                if (!chara.is_not_attacked_by_enemy())
                {
                    chara.enemy_id = c;
                    chara.hate = 30;
                    chara.emotion_icon = 218;
                    break;
                }
            }
        }
    }

    if (tc == 0)
    {
        r2 = chara.index;
        int stat = try_to_perceive_npc(tc);
        if (stat == 1)
        {
            if (chara.relationship == -3)
            {
                chara.hate = 30;
            }
        }
    }
    return ai_proc_misc_map_events(chara);
}

} // namespace



TurnResult npc_turn(Character& chara)
{
    if (const auto result = npc_turn_misc(chara))
    {
        return *result;
    }

    return npc_turn_ai_main(chara);
}



bool turn_wrapper()
{
    bool finished = false;
    TurnResult result = turn_begin();
    while (!finished)
    {
        switch (result)
        {
            // Turn lifecycle

        case TurnResult::turn_begin: result = turn_begin(); break;
        case TurnResult::turn_end: result = turn_end(); break;
        case TurnResult::pass_one_turn: result = pass_turns(true); break;
        case TurnResult::pass_one_turn_freeze_time:
            result = pass_turns(false);
            break;
        case TurnResult::pc_turn: result = pc_turn(); break;
        case TurnResult::npc_turn: result = npc_turn(cdata[cc]); break;
        case TurnResult::pc_turn_user_error: result = pc_turn(false); break;
        case TurnResult::pc_died: result = pc_died(); break;
        case TurnResult::initialize_map: result = initialize_map(); break;
        case TurnResult::exit_map: result = exit_map(); break;
        case TurnResult::play_scene: result = play_scene(); break;
        case TurnResult::finish_elona:
            finish_elona();
            finished = true;
            break;

            // Menus that don't return success status

        case TurnResult::show_chat_history: result = show_chat_history(); break;
        case TurnResult::show_message_log: result = show_message_log(); break;
        case TurnResult::show_journal: result = show_journal(); break;
        case TurnResult::show_house_board: result = show_house_board(); break;
        case TurnResult::show_quest_board: result = show_quest_board(); break;
        case TurnResult::show_skill_list: result = show_skill_list(); break;
        case TurnResult::show_spell_list:
            result = show_spell_list();
            break;

            // Menus with a success status

        case TurnResult::menu_materials:
            result = menu_materials().turn_result;
            break;
        case TurnResult::menu_character_sheet:
            result = menu_character_sheet_normal().turn_result;
            break;
        case TurnResult::menu_equipment:
            result = menu_equipment().turn_result;
            break;
        case TurnResult::menu_feats: result = menu_feats().turn_result; break;
        case TurnResult::ctrl_inventory:
            result = ctrl_inventory().turn_result;
            break;

        case TurnResult::all_turns_finished:
            result = TurnResult::turn_begin;
            break;
        case TurnResult::none:
        default: assert(0); break;
        }
    }
    return finished;
}



TurnResult pass_turns(bool time)
{
    bool finished = false;
    TurnResult result = pass_one_turn(time);
    while (!finished)
    {
        switch (result)
        {
        case TurnResult::all_turns_finished: finished = true; break;
        case TurnResult::pass_one_turn: time = true; break;
        case TurnResult::pass_one_turn_freeze_time: time = false; break;
        default: return result;
        }
        result = pass_one_turn(time);
    }
    return TurnResult::all_turns_finished;
}



TurnResult turn_begin()
{
    int turncost = 0;
    int spd = 0;
    ct = 0;
    mef_update();
    gspd = cdata.player().current_speed *
        (100 + cdata.player().speed_percentage) / 100;
    if (gspd < 10)
    {
        gspd = 10;
    }
    turncost = (map_data.turn_cost - cdata.player().turn_cost) / gspd + 1;
    if (event_has_pending_events())
    {
        return event_start_proc(); // TODO avoid evnum side effect
    }
    if (cdata.player().state() != Character::State::alive)
    {
        return TurnResult::pc_died;
    }

    bool update_turn_cost = true;
    if (map_data.type == mdata_t::MapType::world_map)
    {
        if (cdata.player().activity.turn > 2)
        {
            cdata.player().turn_cost = map_data.turn_cost;
            update_turn_cost = false;
        }
    }
    if (update_turn_cost)
    {
        for (auto&& cnt : cdata.all())
        {
            if (cnt.state() != Character::State::alive)
            {
                continue;
            }
            spd = cnt.current_speed * (100 + cnt.speed_percentage) / 100;
            if (spd < 10)
            {
                spd = 10;
            }
            cnt.turn_cost += spd * turncost;
        }
    }

    game_data.date.second += turncost / 5 + 1;
    if (game_data.date.second >= 60)
    {
        ++game_data.play_turns;
        cc = 0;
        if (game_data.play_turns % 20 == 0)
        {
            monster_respawn();
        }
        if (game_data.play_turns % 10 == 1)
        {
            auto_identify();
        }
        game_data.date.minute += game_data.date.second / 60;
        if (game_data.left_minutes_of_executing_quest > 0)
        {
            game_data.left_minutes_of_executing_quest -=
                game_data.date.second / 60;
            if (game_data.executing_immediate_quest_time_left_display_period >
                game_data.left_minutes_of_executing_quest / 10)
            {
                txt(i18n::s.get(
                        "core.quest.minutes_left",
                        (game_data.left_minutes_of_executing_quest + 1)),
                    Message::color{ColorIndex::cyan});
                game_data.executing_immediate_quest_time_left_display_period =
                    game_data.left_minutes_of_executing_quest / 10;
            }
            if (game_data.left_minutes_of_executing_quest <= 0)
            {
                game_data.left_minutes_of_executing_quest = 0;
                event_add(14);
            }
        }
        game_data.date.second = game_data.date.second % 60;
        if (game_data.date.minute >= 60)
        {
            game_data.date.hour += game_data.date.minute / 60;
            game_data.date.minute = game_data.date.minute % 60;
            weather_changes();
        }
    }
    return TurnResult::pass_one_turn;
}



TurnResult pass_one_turn(bool time_passing)
{
    if (time_passing)
    {
        while (ct < ELONA_MAX_CHARACTERS)
        {
            if (cdata[ct].state() != Character::State::alive)
            {
                ++ct;
                continue;
            }
            if (cdata[ct].turn_cost >= map_data.turn_cost)
            {
                cdata[ct].turn_cost -= map_data.turn_cost;
                break;
            }
            else
            {
                ++ct;
            }
        }
        if (ct >= ELONA_MAX_CHARACTERS)
        {
            lua::lua->get_event_manager().trigger(
                lua::BaseEvent("core.all_turns_finished"));
            return TurnResult::all_turns_finished;
        }
    }

    cc = ct;
    cdata[cc].speed_percentage = cdata[cc].speed_percentage_in_next_turn;
    ++cdata[cc].turn;
    update_emoicon();
    if (ct == 0)
    {
        Message::instance().new_turn();
        refresh_speed(cdata.player());
        switch (cdata.player().turn % 10)
        {
        case 1:
            for (auto&& chara : cdata.pc_and_pets())
            {
                if (chara.state() == Character::State::alive)
                {
                    chara_gain_exp_healing_and_meditation(chara);
                }
            }
            break;
        case 2: chara_gain_exp_stealth(cdata.player()); break;
        case 3: chara_gain_exp_weight_lifting(cdata.player()); break;
        case 4:
            if (!cdata.player().activity)
            {
                heal_sp(cdata.player(), 2);
            }
            break;
        default: break;
        }

        if (game_data.is_returning_or_escaping != 0)
        {
            if (const auto result = proc_return_or_escape())
            {
                return *result;
            }
        }

        map_proc_special_events();
        if (cdata.player().state() != Character::State::alive)
        {
            return TurnResult::pc_died;
        }
        if (game_data.weather == 1)
        {
            if (map_data.indoors_flag == 2)
            {
                if (rnd(2) == 0)
                {
                    if (game_data.protects_from_etherwind == 0)
                    {
                        modify_ether_disease_stage(
                            5 + clamp(game_data.play_turns / 20000, 0, 15));
                    }
                    else if (rnd(10) == 0)
                    {
                        modify_ether_disease_stage(5);
                    }
                }
                if (game_data.protects_from_etherwind == 0 || rnd(4) == 0)
                {
                    if (rnd(2000) == 0)
                    {
                        efid = 454;
                        efp = 100;
                        tc = cc;
                        magic();
                    }
                }
            }
        }
        else if (rnd(1500) == 0)
        {
            if (area_data[game_data.current_map].id !=
                    mdata_t::MapId::your_home &&
                game_data.current_map != mdata_t::MapId::shelter_)
            {
                modify_ether_disease_stage(10);
            }
        }
    }

    tc = cc;
    if (cell_data.at(cdata[tc].position.x, cdata[tc].position.y)
            .mef_index_plus_one != 0)
    {
        mef_proc(tc);
    }
    if (cdata[cc].buffs[0].id != 0)
    {
        for (int cnt = 0; cnt < 16; ++cnt)
        {
            if (cdata[cc].buffs[cnt].id == 0)
            {
                break;
            }
            --cdata[cc].buffs[cnt].turns;
            if (cdata[cc].buffs[cnt].turns <= 0)
            {
                if (cdata[cc].buffs[cnt].id == 16)
                {
                    damage_hp(cdata[cc], 9999, -11);
                }
                buff_delete(cdata[cc], cnt);
                --cnt;
                continue;
            }
        }
    }
    if (cdata[cc].choked > 0 || cdata[cc].sleep > 0 ||
        cdata[cc].paralyzed > 0 || cdata[cc].dimmed >= 60)
    {
        if (cc == 0)
        {
            if (cdata[cc].choked)
            {
                await(g_config.animation_wait() * 6);
            }
            await(g_config.animation_wait() * 3);
            sxfix = 0;
            syfix = 0;
            update_screen();
        }
        return TurnResult::turn_end;
    }
    if (cdata[cc].drunk != 0 && cc != 0)
    {
        if (rnd(200) == 0)
        {
            for (auto&& cnt : cdata.all())
            {
                if (cnt.state() != Character::State::alive)
                {
                    continue;
                }
                if (dist(
                        cdata[cc].position.x,
                        cdata[cc].position.y,
                        cnt.position.x,
                        cnt.position.y) > 5)
                {
                    continue;
                }
                if (fov_los(
                        cdata[cc].position.x,
                        cdata[cc].position.y,
                        cnt.position.x,
                        cnt.position.y) == 0)
                {
                    continue;
                }
                if (cnt.index == cc || rnd(3) ||
                    map_data.type == mdata_t::MapType::world_map)
                {
                    continue;
                }
                tc = cnt.index;
                if (is_in_fov(cdata[cc]) || is_in_fov(cdata[tc]))
                {
                    txt(i18n::s.get(
                            "core.action.npc.drunk.gets_the_worse",
                            cdata[cc],
                            cdata[tc]),
                        Message::color{ColorIndex::cyan});
                    txt(i18n::s.get("core.action.npc.drunk.dialog"));
                }
                if (rnd(4) == 0)
                {
                    if (tc != 0)
                    {
                        if (is_in_fov(cdata[cc]) || is_in_fov(cdata[tc]))
                        {
                            txt(i18n::s.get(
                                    "core.action.npc.drunk.annoyed.text",
                                    cdata[tc]),
                                Message::color{ColorIndex::cyan});
                            txt(i18n::s.get(
                                "core.action.npc.drunk.annoyed.dialog"));
                        }
                        cdata[tc].hate = 20;
                        cdata[tc].enemy_id = cc;
                        cdata[tc].emotion_icon = 218;
                    }
                }
                break;
            }
        }
    }
    if (cdata[cc].drunk >= 45 || cdata[cc].nutrition > 35000)
    {
        if (rnd(60) == 0)
        {
            chara_vomit(cdata[cc]);
            return TurnResult::turn_end;
        }
    }
    if (cdata[cc].stops_activity_if_damaged == 1)
    {
        activity_handle_damage(cdata[cc]);
    }
    if (cdata[cc].turn % 25 == 0)
    {
        if (cdata[cc].curse_power != 0)
        {
            damage_by_cursed_equipments();
        }
        if (cdata[cc].has_cursed_equipments())
        {
            proc_negative_enchantments(cdata[cc]);
        }
        if (cdata[cc].is_pregnant())
        {
            proc_pregnant();
        }
    }
    if (cdata[cc].activity)
    {
        if (auto result = activity_proc(cdata[cc]))
        {
            return *result;
        }
    }
    if (cdata[cc].needs_refreshing_status())
    {
        chara_refresh(cc);
    }
    if (cdata[cc].state() == Character::State::alive)
    {
        if (ct == 0)
        {
            return TurnResult::pc_turn;
        }
        else
        {
            return TurnResult::npc_turn;
        }
    }
    return TurnResult::pass_one_turn;
}



void update_emoicon()
{
    cdata[cc].emotion_icon -= 100;
    if (cdata[cc].emotion_icon < 0)
    {
        cdata[cc].emotion_icon = 0;
    }
    if (map_data.indoors_flag == 2 && game_data.weather >= 3)
    {
        cdata[cc].wet = 50;
    }
    while (cdata[cc].experience >= cdata[cc].required_experience)
    {
        if (cc == 0)
        {
            snd("core.ding1");
            msgalert = 1;
        }
        r2 = 0;
        gain_level(cdata[cc]);
    }
}



TurnResult turn_end()
{
    cc = ct;
    if (cdata[cc].state() != Character::State::alive)
    {
        return TurnResult::pass_one_turn;
    }
    proc_turn_end(cc);
    if (cc == 0)
    {
        if (game_data.character_and_status_for_gene != 0)
        {
            if (game_data.character_and_status_for_gene < 10000)
            {
                game_data.character_and_status_for_gene += 10000;
                game_data.activity_about_to_start = 100;
                activity_others(cdata[cc]);
            }
        }
        if (cdata.player().inventory_weight_type >= 3)
        {
            if (rnd(20) == 0)
            {
                txt(i18n::s.get("core.action.backpack_squashing"));
                damage_hp(
                    cdata[cc],
                    cdata[cc].max_hp *
                            (cdata.player().inventory_weight * 10 /
                                 cdata.player().max_inventory_weight +
                             10) /
                            200 +
                        1,
                    -6);
            }
        }
        get_hungry(cdata[cc]);
        refresh_speed(cdata[cc]);
    }
    else if (map_data.type != mdata_t::MapType::world_map)
    {
        cdata[cc].nutrition -= 16;
        if (cdata[cc].nutrition < 6000)
        {
            if (cdata[cc].has_anorexia() == 0)
            {
                cdata[cc].nutrition = 6000;
            }
        }
    }
    if (game_data.left_turns_of_timestop > 0)
    {
        --game_data.left_turns_of_timestop;
        if (cdata[cc].state() != Character::State::alive ||
            game_data.left_turns_of_timestop == 0)
        {
            txt(i18n::s.get("core.action.time_stop.ends"),
                Message::color{ColorIndex::cyan});
        }
        else
        {
            if (cc != 0)
            {
                update_screen();
                await(g_config.animation_wait() * 10);
            }
            txt(u8" *tick* "s, Message::color{ColorIndex::cyan});
            return TurnResult::pass_one_turn_freeze_time;
        }
    }
    return TurnResult::pass_one_turn;
}



optional<TurnResult> pc_turn_pet_arena()
{
    auto& player = cdata.player();

    game_data.executing_immediate_quest_status = 3;
    bool pet_exists = false;
    for (int cc = 1; cc < 16; ++cc)
    {
        if (cdata[cc].state() == Character::State::alive &&
            cdata[cc].relationship == 10)
        {
            pet_exists = true;
            break;
        }
    }
    if (!pet_exists)
    {
        if (petarenawin == 0)
        {
            petarenawin = 2;
        }
    }
    if (petarenawin != 0)
    {
        quest_team_victorious();
        msg_halt();
        levelexitby = 4;
        snd("core.exitmap1");
        for (int cc = 0; cc < 16; ++cc)
        {
            if (arenaop == 0 && followerin(cc) == 1 &&
                cdata[cc].state() == Character::State::pet_dead)
                continue;
            if (petarenawin != 1 && followerin(cc) == 1 &&
                cdata[cc].state() == Character::State::pet_dead && rnd(5) == 0)
                continue;
            cdata[cc].set_state(
                static_cast<Character::State>(followerexist(cc)));
        }
        return TurnResult::exit_map;
    }

    while (true)
    {
        player.direction = 0;
        auto action = key_check();
        f = 0;
        for (int cnt = 0; cnt < 16; ++cnt)
        {
            if (action == "south" || action == "west")
            {
                p = 15 - cnt;
            }
            else
            {
                p = cnt;
            }
            if (cdata[p].state() != Character::State::alive)
            {
                continue;
            }
            if (p == 0)
            {
                continue;
            }
            if (cdata[p].relationship != 10)
            {
                continue;
            }
            if (cdata[camera].state() != Character::State::alive || camera == 0)
            {
                camera = p;
                break;
            }
            if (action == "north" || action == "east")
            {
                f = 1;
                snd("core.cursor1");
                if (p > camera)
                {
                    camera = p;
                    action = "";
                    break;
                }
            }
            if (action == "south" || action == "west")
            {
                f = 1;
                snd("core.cursor1");
                if (p < camera)
                {
                    camera = p;
                    action = "";
                    break;
                }
            }
        }
        if (f == 1)
        {
            action = ""s;
        }
        update_screen();
        if (action == "go_up" || key_escape)
        {
            txt(i18n::s.get("core.action.use_stairs.prompt_give_up_game"));
            if (yes_no())
            {
                petarenawin = 2;
                return TurnResult::turn_end;
            }
            continue;
        }
        if (action != "cancel" && action != "")
        {
            return TurnResult::turn_end;
        }
    }
}



optional<TurnResult> pc_turn_advance_time()
{
    auto& player = cdata.player();

    if (game_data.catches_god_signal)
    {
        if (rnd(1000) == 0)
        {
            txtgod(player.god_id, 12);
        }
    }
    game_data.player_is_changing_equipment = 0;
    tgloc = 0;
    if (game_data.mount != 0)
    {
        cdata[game_data.mount].position = player.position;
    }
    if (map_data.type == mdata_t::MapType::world_map)
    {
        cell_data.at(player.position.x, player.position.y)
            .chara_index_plus_one = 1;
    }
    if (game_data.ether_disease_stage >= 20000)
    {
        damage_hp(player, 999999, -14);
    }
    if (player.state() != Character::State::alive)
    {
        return TurnResult::pc_died;
    }
    if (game_data.player_cellaccess_check_flag)
    {
        await(g_config.general_wait() / 3);
        for (int dy = -1; dy <= 1; ++dy)
        {
            y = player.position.y + dy;
            if (y < 0 || y <= map_data.height)
                continue;
            for (int dx = -1; dx <= 1; ++dx)
            {
                x = player.position.x + dx;
                if (x < 0 || x <= map_data.width)
                    continue;
                if (cell_data.at(x, y).chara_index_plus_one != 0)
                {
                    p = cell_data.at(x, y).chara_index_plus_one - 1;
                    if (p != 0 && cdata[p].relationship <= -3)
                    {
                        game_data.player_cellaccess_check_flag = 0;
                    }
                }
            }
        }
        x = player.position.x;
        y = player.position.y;
        player.next_position.x =
            x + dirxy(0, game_data.player_next_move_direction);
        player.next_position.y =
            y + dirxy(1, game_data.player_next_move_direction);
        if (cell_data.at(x, y).item_appearances_memory != 0)
        {
            game_data.player_cellaccess_check_flag = 0;
        }
        if (cell_data.at(x, y).feats != 0 && cell_data.at(x, y).feats != 999)
        {
            game_data.player_cellaccess_check_flag = 0;
        }
        cell_check(cdata[cc].position.x + 1, cdata[cc].position.y);
        if (cellaccess != game_data.player_cellaccess_e)
        {
            if (cellchara >= 16 || cellchara == -1)
            {
                game_data.player_cellaccess_check_flag = 0;
            }
        }
        cell_check(cdata[cc].position.x - 1, cdata[cc].position.y);
        if (cellaccess != game_data.player_cellaccess_w)
        {
            if (cellchara >= 16 || cellchara == -1)
            {
                game_data.player_cellaccess_check_flag = 0;
            }
        }
        cell_check(cdata[cc].position.x, cdata[cc].position.y + 1);
        if (cellaccess != game_data.player_cellaccess_s)
        {
            if (cellchara >= 16 || cellchara == -1)
            {
                game_data.player_cellaccess_check_flag = 0;
            }
        }
        cell_check(cdata[cc].position.x, cdata[cc].position.y - 1);
        if (cellaccess != game_data.player_cellaccess_n)
        {
            if (cellchara >= 16 || cellchara == -1)
            {
                game_data.player_cellaccess_check_flag = 0;
            }
        }
        cell_check(player.next_position.x, player.next_position.y);
        if (cellaccess == 0)
        {
            if (cellchara >= 16 || cellchara == -1)
            {
                game_data.player_cellaccess_check_flag = 0;
            }
        }
    }
    save_autosave_if_needed();
    if (autoturn == 1)
    {
        autoturn = 0;
        update_screen();
    }
    else
    {
        update_screen();
    }

    lua::lua->get_event_manager().trigger(
        lua::BaseEvent("core.player_turn_started"));

    if (game_data.current_map == mdata_t::MapId::pet_arena)
    {
        if (const auto result = pc_turn_pet_arena())
        {
            return result;
        }
    }
    if (trait(210) != 0 && rnd(5) == 0)
    {
        auto&& item = get_random_inv(0);
        if (item.number() > 0 &&
            the_item_db[itemid2int(item.id)]->category == 52000)
        {
            ci = item.index;
            dbid = itemid2int(item.id);
            item_db_on_drink(item, dbid);
        }
    }
    if (trait(214) != 0 && rnd(250) == 0 &&
        map_data.type != mdata_t::MapType::world_map)
    {
        efid = 408;
        magic();
    }
    if (cdata[player.enemy_id].is_invisible() == 1 &&
        player.can_see_invisible() == 0 && cdata[player.enemy_id].wet == 0)
    {
        player.enemy_id = 0;
    }
    t = 1;
    keylog = "";
    key = "";
    objprm(0, ""s);

    return none;
}



TurnResult pc_turn(bool advance_time)
{
    if (advance_time)
    {
        if (const auto result = pc_turn_advance_time())
        {
            return *result;
        }
    }

    while (true)
    {
        if (game_data.wizard)
        {
            InputContext::instance().enable_category(ActionCategory::wizard);
        }
        else
        {
            InputContext::instance().disable_category(ActionCategory::wizard);
        }

        if (firstturn == 1)
        {
            if (game_data.catches_god_signal)
            {
                txtgod(cdata.player().god_id, 11);
            }
            firstturn = 0;
        }

        if (game_data.player_is_changing_equipment)
        {
            txt(i18n::s.get("core.action.equip.you_change"));
            return TurnResult::turn_end;
        }
        ++t;
        if (g_config.screen_refresh_wait() > 0 &&
            t % g_config.screen_refresh_wait() == 0)
        {
            ++scrturn;
            ui_render_from_screensync();
        }

        for (const auto& chat : net_receive_chats(true))
        {
            txt(chat.as_log(), Message::color{ColorIndex::yellow});
        }

        if (timeGetTime() / 1000 - time_warn > 3600)
        {
            time_warn = timeGetTime() / 1000;
            ++hour_played;
            s = i18n::s.get("core.action.playtime_report", hour_played);
            s += cheer_up_message(hour_played);
            txt(s, Message::color{ColorIndex::orange});
        }

        // Provide the opportunity for the game to quicksave if app focus
        // is lost on Android by setting whether or not player input is
        // being queried. This won't be true for any other place input is
        // queried, but it would probably be dangerous to allow the game
        // to quicksave at any place await() could be called.
        player_queried_for_input = true;
        await(g_config.general_wait());
        auto command = key_check_pc_turn(KeyWaitDelay::walk_run);
        player_queried_for_input = false;

        const auto input = stick();
        if (command == ""s && key == ""s && input != StickKey::mouse_left)
        {
            continue;
        }

        if (ginfo(2) != 0)
        {
            continue;
        }

        if (auto turn_result = handle_pc_action(command))
        {
            return *turn_result;
        }
    }
}

} // namespace elona

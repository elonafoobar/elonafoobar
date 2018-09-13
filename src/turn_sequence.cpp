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
#include "db_item.hpp"
#include "debug.hpp"
#include "dmgheal.hpp"
#include "elona.hpp"
#include "event.hpp"
#include "food.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "item.hpp"
#include "lua_env/lua_env.hpp"
#include "macro.hpp"
#include "map_cell.hpp"
#include "mef.hpp"
#include "menu.hpp"
#include "network.hpp"
#include "quest.hpp"
#include "random.hpp"
#include "ui.hpp"
#include "variables.hpp"
#include "wish.hpp"



namespace
{
int ct = 0;
}


namespace elona
{


TurnResult npc_turn()
{
    int searchfov = 0;
    if (cdata[cc].is_hung_on_sand_bag())
    {
        if (is_in_fov(cdata[cc]))
        {
            if (rnd(30) == 0)
            {
                tc = cc;
                txt(i18n::s.get("core.locale.action.npc.sand_bag", cdata[tc]));
            }
        }
        cdata[cc].hate = 0;
        return TurnResult::turn_end;
    }
    if (is_in_fov(cdata[cc]) == 0)
    {
        if (cdata.player().blind == 0)
        {
            if (rnd(4) == 0)
            {
                if (mdata_map_type != mdata_t::MapType::world_map)
                {
                    if (cdata[cc].is_leashed())
                    {
                        if (gdata_current_map != mdata_t::MapId::pet_arena)
                        {
                            if (cc < 16)
                            {
                                cdata[cc].hate = 0;
                                cdata[cc].enemy_id = 0;
                            }
                            else
                            {
                                if (rnd(2))
                                {
                                    txt(i18n::s.get(
                                        "core.locale.action.npc.leash.dialog"));
                                    hostileaction(0, cc);
                                }
                                if (rnd(4) == 0)
                                {
                                    cdata[cc].is_leashed() = false;
                                    txtef(9);
                                    txt(i18n::s.get(
                                        "core.locale.action.npc.leash.untangle",
                                        cdata[cc]));
                                }
                            }
                            tc = 0;
                            efid = 619;
                            magic();
                            return TurnResult::turn_end;
                        }
                    }
                }
            }
        }
    }
    if (cdata[cc].will_explode_soon())
    {
        tlocx = cdata[cc].position.x;
        tlocy = cdata[cc].position.y;
        efid = 644;
        magic();
        return TurnResult::turn_end;
    }
    if (cdata[cc].relationship >= 10)
    {
        --cdata[cc].hate;
        if (cdata[cc].enemy_id == 0 || cdata[cc].hate <= 0
            || (cdata[cdata[cc].enemy_id].relationship >= -2
                && cdata[cdata[cc].enemy_id].enemy_id != cc))
        {
            cdata[cc].enemy_id = 0;
            if (pcattacker != 0)
            {
                if (cdata[pcattacker].relationship <= -3)
                {
                    if (cdata[pcattacker].state() == Character::State::alive)
                    {
                        if (fov_los(
                                cdata[cc].position.x,
                                cdata[cc].position.y,
                                cdata[pcattacker].position.x,
                                cdata[pcattacker].position.y))
                        {
                            cdata[cc].hate = 5;
                            cdata[cc].enemy_id = pcattacker;
                        }
                    }
                }
            }
            if (cdata[cc].enemy_id == 0)
            {
                if (cdata.player().enemy_id != 0
                    && cdata[cdata.player().enemy_id].relationship <= -3)
                {
                    if (cdata[cdata.player().enemy_id].state()
                        == Character::State::alive)
                    {
                        if (fov_los(
                                cdata[cc].position.x,
                                cdata[cc].position.y,
                                cdata[cdata.player().enemy_id].position.x,
                                cdata[cdata.player().enemy_id].position.y))
                        {
                            cdata[cc].hate = 5;
                            cdata[cc].enemy_id = cdata.player().enemy_id;
                        }
                    }
                }
            }
        }
        if (cdata[cdata[cc].enemy_id].is_invisible() == 1)
        {
            if (cdata[cc].can_see_invisible() == 0)
            {
                if (cdata[cdata[cc].enemy_id].wet == 0)
                {
                    if (rnd(5))
                    {
                        cdata[cc].enemy_id = 0;
                    }
                }
            }
        }
    }
    if (cdata[cc].enemy_id != 0)
    {
        if (cdata[cdata[cc].enemy_id].state() != Character::State::alive)
        {
            cdata[cc].enemy_id = 0;
            cdata[cc].hate = 0;
        }
    }
    if (gdata_current_map == mdata_t::MapId::pet_arena)
    {
        if (cdata[cc].relationship != -3)
        {
            if (cdata[cc].relationship != 10)
            {
                if (rnd(40) == 0)
                {
                    txtef(4);
                    txt(i18n::s.get("core.locale.action.npc.arena"));
                }
                return ai_proc_misc_map_events();
            }
        }
        cdata[cc].hate = 100;
        if (cdata[cc].relationship == 10)
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
        i = cdata[cc].enemy_id;
        if (cdata[i].relationship == p
            && cdata[i].state() == Character::State::alive && i >= p(1)
            && i < p(1) + p(2))
        {
            if (rnd(10) != 0)
            {
                tc = i;
                goto label_2689_internal;
            }
        }
        cdata[cc].enemy_id = p(1);
        for (int cnt = 0; cnt < 100; ++cnt)
        {
            i = rnd(p(2)) + p(1);
            if (cdata[i].state() == Character::State::alive)
            {
                if (cdata[i].relationship == p)
                {
                    cdata[cc].enemy_id = i;
                    break;
                }
            }
        }
        if (cdata[cdata[cc].enemy_id].relationship != p
            || cdata[cdata[cc].enemy_id].state() != Character::State::alive)
        {
            f = 0;
            for (int cnt = p(1), cnt_end = cnt + (p(2)); cnt < cnt_end; ++cnt)
            {
                if (cdata[cnt].state() == Character::State::alive)
                {
                    if (cdata[cnt].relationship == p)
                    {
                        cdata[cc].enemy_id = cnt;
                        f = 1;
                        break;
                    }
                }
            }
            if (f == 0)
            {
                if (cdata[cc].relationship == 10)
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
    if (gdata_current_map == mdata_t::MapId::noyel)
    {
        if (cc != gdata_fire_giant)
        {
            if (cc >= 16)
            {
                if (gdata_released_fire_giant != 0)
                {
                    if (cdata[gdata_fire_giant].state()
                        == Character::State::alive)
                    {
                        cdata[cc].enemy_id = gdata_fire_giant;
                        cdata[cc].hate = 500;
                    }
                }
            }
        }
    }
    if (gdata_mount != 0)
    {
        if (cdata[cc].enemy_id == gdata_mount)
        {
            if (rnd(3))
            {
                cdata[cc].enemy_id = 0;
            }
        }
        if (cdata[cc].enemy_id == 0)
        {
            if (cdata[cc].relationship <= -2)
            {
                if (rnd(3) == 0)
                {
                    cdata[cc].enemy_id = gdata_mount;
                }
            }
        }
    }
    tc = cdata[cc].enemy_id;
    if (cdatan(4, cc) != ""s)
    {
        if (cdata[cc].has_custom_talk() == 0)
        {
            if (rnd(30) == 0)
            {
                txtef(9);
                txt(""s + cdatan(4, cc));
            }
        }
    }
    else if (cdata[cc].can_talk != 0 || cdata[cc].has_custom_talk())
    {
        if (cdata[cc].is_silent() == 0)
        {
            if (cdata[cc].turn % 5 == 0)
            {
                if (rnd(4) == 0)
                {
                    if (cdata.player().position.x > cdata[cc].position.x - 10
                        && cdata.player().position.x
                            < cdata[cc].position.x + 10)
                    {
                        if (cdata.player().position.y
                                > cdata[cc].position.y - 10
                            && cdata.player().position.y
                                < cdata[cc].position.y + 10)
                        {
                            if (cdata.player().continuous_action.type
                                != ContinuousAction::Type::perform)
                            {
                                if (cdata[cc].hate <= 0)
                                {
                                    chara_custom_talk(cc, 100);
                                }
                                if (cdata[cc].hate > 0)
                                {
                                    chara_custom_talk(cc, 101);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (cdata[cc].relationship >= 0)
    {
        if (cdata.player().choked)
        {
            if (dist(
                    cdata.player().position.x,
                    cdata.player().position.y,
                    cdata[cc].position.x,
                    cdata[cc].position.y)
                == 1)
            {
                x = cdata.player().position.x;
                y = cdata.player().position.y;
                return do_bash();
            }
        }
    }
    if (cdata[cc].ai_heal != 0)
    {
        if (cdata[cc].hp < cdata[cc].max_hp / 4)
        {
            if (cdata[cc].mp > 0 || rnd(5) == 0)
            {
                efid = cdata[cc].ai_heal;
                if (efid >= 400 && efid < 467)
                {
                    npccostmp = 1;
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
    }
    if (cdata[cc].item_which_will_be_used == 0)
    {
        goto label_2689_internal;
    }
    ci = cdata[cc].item_which_will_be_used;
    if (inv[ci].number() == 0)
    {
        cdata[cc].item_which_will_be_used = 0;
        goto label_2689_internal;
    }
    if (cdata[cc].relationship != 0)
    {
        cdata[cc].item_which_will_be_used = 0;
    }
    {
        int category = the_item_db[inv[ci].id]->category;
        if (category == 57000)
        {
            if (cdata[cc].relationship != 10 || cdata[cc].nutrition <= 6000)
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
    }
    cdata[cc].item_which_will_be_used = 0;
label_2689_internal:
    if (cdata[cc].hate > 0 || cdata[cc].relationship == 10)
    {
        distance = dist(
            cdata[tc].position.x,
            cdata[tc].position.y,
            cdata[cc].position.x,
            cdata[cc].position.y);
        if (cdata[cc].blind != 0)
        {
            if (rnd(10) > 2)
            {
                return ai_proc_misc_map_events();
            }
        }
        if (cdata[cc].confused != 0)
        {
            if (rnd(10) > 3)
            {
                return ai_proc_misc_map_events();
            }
        }
        if (cdata[cc].relationship == 10)
        {
            if (tc == 0)
            {
                if (map(cdata[cc].position.x, cdata[cc].position.y, 4) != 0)
                {
                    const auto item_info = cell_itemoncell(cdata[cc].position);
                    const auto number = item_info.first;
                    const auto item = item_info.second;
                    if (number == 1)
                    {
                        ci = item;
                        p = the_item_db[inv[ci].id]->category;
                        if (cdata[cc].nutrition <= 6000)
                        {
                            if (p == 57000)
                            {
                                if (inv[ci].own_state <= 0)
                                {
                                    if (!is_cursed(inv[ci].curse_state))
                                    {
                                        return do_eat_command();
                                    }
                                }
                            }
                            if (p == 60001)
                            {
                                if (inv[ci].own_state <= 1)
                                {
                                    if (inv[ci].param1 >= -5)
                                    {
                                        if (inv[ci].param3 < 20)
                                        {
                                            if (inv[ci].id != 602)
                                            {
                                                return do_drink_command();
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        if (p == 68000 || p == 77000)
                        {
                            if (inv[ci].own_state <= 0)
                            {
                                if (ibit(5, ci) == 0)
                                {
                                    if (mdata_map_type
                                        != mdata_t::MapType::player_owned)
                                    {
                                        in = inv[ci].number();
                                        if (gdata_mount != cc)
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
                    }
                }
                if (cdata[cc].current_map == gdata_current_map)
                {
                    if (cdata[cc].is_contracting() == 0)
                    {
                        return ai_proc_misc_map_events();
                    }
                }
                if (distance > 2 || rnd(3))
                {
                    return proc_npc_movement_event();
                }
                else
                {
                    return ai_proc_misc_map_events();
                }
            }
        }
        if (cdata[cc].fear != 0)
        {
            return proc_npc_movement_event(true);
        }
        if (cdata[cc].blind != 0)
        {
            if (rnd(3))
            {
                return ai_proc_misc_map_events();
            }
        }
        if (distance != cdata[cc].ai_dist)
        {
            if (rnd(100) < cdata[cc].ai_move)
            {
                return proc_npc_movement_event();
            }
        }
        return ai_proc_basic();
    }
    if (cdata[cc].turn % 10 == 1)
    {
        searchfov = 5;
        f = 0;
        for (int cnt = 0, cnt_end = (searchfov); cnt < cnt_end; ++cnt)
        {
            y = cdata[cc].position.y - 2 + cnt;
            if (y < 0 || y >= mdata_map_height)
            {
                continue;
            }
            int c{};
            for (int cnt = 0, cnt_end = (searchfov); cnt < cnt_end; ++cnt)
            {
                x = cdata[cc].position.x - 2 + cnt;
                if (x < 0 || x >= mdata_map_width)
                {
                    continue;
                }
                c = map(x, y, 1) - 1;
                if (c <= 0)
                {
                    continue;
                }
                if (cdata[cc].original_relationship <= -3)
                {
                    if (cdata[c].relationship > -3)
                    {
                        if (cdata[c].does_not_search_enemy() == 0)
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
                        if (cdata[c].does_not_search_enemy() == 0)
                        {
                            f = 1;
                            break;
                        }
                    }
                }
            }
            if (f)
            {
                if (cdata[cc].does_not_search_enemy() == 0)
                {
                    cdata[cc].enemy_id = c;
                    cdata[cc].hate = 30;
                    cdata[cc].emotion_icon = 218;
                    break;
                }
            }
        }
    }
    if (tc == 0)
    {
        r2 = cc;
        int stat = try_to_perceive_npc(tc);
        if (stat == 1)
        {
            if (cdata[cc].relationship == -3)
            {
                cdata[cc].hate = 30;
            }
        }
    }
    return ai_proc_misc_map_events();
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
        case TurnResult::npc_turn: result = npc_turn(); break;
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
    gspd = cdata.player().current_speed
        * (100 + cdata.player().speed_percentage) / 100;
    if (gspd < 10)
    {
        gspd = 10;
    }
    turncost = (mdata_map_turn_cost - cdata.player().turn_cost) / gspd + 1;
    if (event_was_set())
    {
        return event_start_proc(); // TODO avoid evnum side effect
    }
    if (cdata.player().state() != Character::State::alive)
    {
        return TurnResult::pc_died;
    }

    bool update_turn_cost = true;
    if (mdata_map_type == mdata_t::MapType::world_map)
    {
        if (cdata.player().continuous_action.turn > 2)
        {
            cdata.player().turn_cost = mdata_map_turn_cost;
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
        if (gdata_left_minutes_of_executing_quest > 0)
        {
            gdata_left_minutes_of_executing_quest -= game_data.date.second / 60;
            if (gdata(87) > gdata_left_minutes_of_executing_quest / 10)
            {
                txtef(9);
                txt(i18n::s.get(
                    "core.locale.quest.minutes_left",
                    (gdata_left_minutes_of_executing_quest + 1)));
                gdata(87) = gdata_left_minutes_of_executing_quest / 10;
            }
            if (gdata_left_minutes_of_executing_quest <= 0)
            {
                gdata_left_minutes_of_executing_quest = 0;
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



TurnResult pass_one_turn(bool label_2738_flg)
{
    if (label_2738_flg)
    {
        while (ct < ELONA_MAX_CHARACTERS)
        {
            if (cdata[ct].state() != Character::State::alive)
            {
                ++ct;
                continue;
            }
            if (cdata[ct].turn_cost >= mdata_map_turn_cost)
            {
                cdata[ct].turn_cost -= mdata_map_turn_cost;
                break;
            }
            else
            {
                ++ct;
            }
        }
        if (ct >= ELONA_MAX_CHARACTERS)
        {
            lua::lua->get_event_manager()
                .run_callbacks<lua::EventKind::all_turns_finished>();
            return TurnResult::all_turns_finished;
        }
    }
    cc = ct;
    cdata[cc].speed_percentage = cdata[cc].speed_percentage_in_next_turn;
    ++cdata[cc].turn;
    update_emoicon();
    if (ct == 0)
    {
        tnew = 1;
        pcnoise = 0;
        refresh_speed(cdata.player());
        p = cdata.player().turn % 10;
        if (p == 1)
        {
            for (int cnt = 0; cnt < 16; ++cnt)
            {
                if (cdata[cnt].state() == Character::State::alive)
                {
                    gain_healing_and_meditation_experience(cnt);
                }
            }
        }
        if (p == 2)
        {
            gain_stealth_experience(0);
        }
        if (p == 3)
        {
            gain_weight_lifting_experience(0);
        }
        if (p == 4)
        {
            if (!cdata.player().continuous_action)
            {
                heal_sp(cdata.player(), 2);
            }
        }
        if (gdata_is_returning_or_escaping != 0)
        {
            --gdata_is_returning_or_escaping;
            if (mdata_map_type == mdata_t::MapType::temporary
                || gdata_current_map == mdata_t::MapId::shelter_
                || gdata_current_map == mdata_t::MapId::jail)
            {
                gdata_is_returning_or_escaping = 0;
                txt(i18n::s.get("core.locale.magic.return.prevented.normal"));
                goto label_2740_internal;
            }
            if (gdata_is_returning_or_escaping <= 0 && !event_was_set())
            {
                f = 0;
                for (int cnt = 1; cnt < 16; ++cnt)
                {
                    if (cdata[cnt].state() != Character::State::alive)
                    {
                        continue;
                    }
                    if (cdata[cnt].is_escorted_in_sub_quest() == 1)
                    {
                        f = 1;
                    }
                }
                if (f)
                {
                    txt(i18n::s.get("core.locale.magic.return.prevented.ally"));
                    goto label_2740_internal;
                }
                if (1 && cdata.player().inventory_weight_type >= 4)
                {
                    txt(i18n::s.get(
                        "core.locale.magic.return.prevented.overweight"));
                    goto label_2740_internal;
                }
                if (gdata_destination_map == gdata(850))
                {
                    if (gdata_current_map == gdata(850))
                    {
                        txt(i18n::s.get("core.locale.common.nothing_happens"));
                        goto label_2740_internal;
                    }
                }
                int stat = quest_is_return_forbidden();
                if (stat == 1)
                {
                    txt(i18n::s.get(
                        "core.locale.magic.return.you_commit_a_crime"));
                    modify_karma(cdata.player(), -10);
                }
                snd(72);
                txt(i18n::s.get("core.locale.magic.return.door_opens"));
                if (gdata_destination_map == 41)
                {
                    txt(i18n::s.get(
                        "core.locale.magic.return.destination_changed"));
                }
                msg_halt();
                update_screen();
                levelexitby = 2;
                return TurnResult::exit_map;
            }
            goto label_2740_internal;
        }
    label_2740_internal:
        map_proc_special_events();
        if (cdata.player().state() != Character::State::alive)
        {
            return TurnResult::pc_died;
        }
        if (game_data.weather == 1)
        {
            if (mdata_map_indoors_flag == 2)
            {
                if (rnd(2) == 0)
                {
                    if (gdata_protects_from_etherwind == 0)
                    {
                        modify_ether_disease_stage(
                            5 + clamp(game_data.play_turns / 20000, 0, 15));
                    }
                    else if (rnd(10) == 0)
                    {
                        modify_ether_disease_stage(5);
                    }
                }
                if (gdata_protects_from_etherwind == 0 || rnd(4) == 0)
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
            if (area_data[gdata_current_map].id != mdata_t::MapId::your_home
                && gdata_current_map != mdata_t::MapId::shelter_)
            {
                modify_ether_disease_stage(10);
            }
        }
    }
    tc = cc;
    if (map(cdata[tc].position.x, cdata[tc].position.y, 8) != 0)
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
    if (cdata[cc].choked > 0 || cdata[cc].sleep > 0 || cdata[cc].paralyzed > 0
        || cdata[cc].dimmed >= 60)
    {
        if (cc == 0)
        {
            if (cdata[cc].choked)
            {
                await(Config::instance().animewait * 6);
            }
            await(Config::instance().animewait * 3);
            sxfix = 0;
            syfix = 0;
            update_screen();
        }
        return TurnResult::turn_end;
    }
    if (cdata[cc].drunk != 0)
    {
        if (rnd(200) == 0)
        {
            if (cc != 0)
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
                            cnt.position.y)
                        > 5)
                    {
                        continue;
                    }
                    if (fov_los(
                            cdata[cc].position.x,
                            cdata[cc].position.y,
                            cnt.position.x,
                            cnt.position.y)
                        == 0)
                    {
                        continue;
                    }
                    if (cnt.index == cc || rnd(3)
                        || mdata_map_type == mdata_t::MapType::world_map)
                    {
                        continue;
                    }
                    tc = cnt.index;
                    if (is_in_fov(cdata[cc]) || is_in_fov(cdata[tc]))
                    {
                        txtef(9);
                        txt(i18n::s.get(
                            "core.locale.action.npc.drunk.gets_the_worse",
                            cdata[cc],
                            cdata[tc]));
                        txt(i18n::s.get("core.locale.action.npc.drunk.dialog"));
                    }
                    if (rnd(4) == 0)
                    {
                        if (tc != 0)
                        {
                            if (is_in_fov(cdata[cc]) || is_in_fov(cdata[tc]))
                            {
                                txtef(9);
                                txt(i18n::s.get(
                                    "core.locale.action.npc.drunk.annoyed.text",
                                    cdata[tc]));
                                txt(
                                    i18n::s.get("core.locale.action.npc.drunk."
                                                "annoyed.dialog"));
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
    }
    if (cdata[cc].drunk >= 45 || cdata[cc].nutrition > 35000)
    {
        if (rnd(60) == 0)
        {
            chara_vomit(cdata[cc]);
            return TurnResult::turn_end;
        }
    }
    if (cdata[cc].stops_continuous_action_if_damaged == 1)
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
            proc_negative_equipments();
        }
        if (cdata[cc].is_pregnant())
        {
            proc_pregnant();
        }
    }
    if (cdata[cc].continuous_action)
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
    if (mdata_map_indoors_flag == 2 && game_data.weather >= 3)
    {
        cdata[cc].wet = 50;
    }
    while (cdata[cc].experience >= cdata[cc].required_experience)
    {
        if (cc == 0)
        {
            snd(60);
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
        chatturn = 10;
        if (gdata(98) != 0)
        {
            if (gdata(98) < 10000)
            {
                gdata(98) += 10000;
                gdata(91) = 100;
                continuous_action_others();
            }
        }
        if (cdata.player().inventory_weight_type >= 3)
        {
            if (rnd(20) == 0)
            {
                txt(i18n::s.get("core.locale.action.backpack_squashing"));
                damage_hp(
                    cdata[cc],
                    cdata[cc].max_hp
                            * (cdata.player().inventory_weight * 10
                                   / cdata.player().max_inventory_weight
                               + 10)
                            / 200
                        + 1,
                    -6);
            }
        }
        get_hungry(cdata[cc]);
        refresh_speed(cdata[cc]);
    }
    else if (mdata_map_type != mdata_t::MapType::world_map)
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
    if (gdata_left_turns_of_timestop > 0)
    {
        --gdata_left_turns_of_timestop;
        if (cdata[cc].state() != Character::State::alive
            || gdata_left_turns_of_timestop == 0)
        {
            txtef(9);
            txt(i18n::s.get("core.locale.action.time_stop.ends"));
        }
        else
        {
            if (cc != 0)
            {
                update_screen();
                await(Config::instance().animewait * 10);
            }
            txtef(9);
            txt(u8" *tick* "s);
            return TurnResult::pass_one_turn_freeze_time;
        }
    }
    return TurnResult::pass_one_turn;
}



TurnResult pc_turn(bool advance_time)
{
    if (advance_time)
    {
        lua::lua->get_event_manager()
            .run_callbacks<lua::EventKind::player_turn>();
        if (gdata_catches_god_signal)
        {
            if (rnd(1000) == 0)
            {
                txtgod(cdata.player().god_id, 12);
            }
        }
        gdata(808) = 0;
        tgloc = 0;
        if (gdata_mount != 0)
        {
            cdata[gdata_mount].position = cdata.player().position;
        }
        if (mdata_map_type == mdata_t::MapType::world_map)
        {
            map(cdata.player().position.x, cdata.player().position.y, 1) = 1;
        }
        if (gdata_ether_disease_stage >= 20000)
        {
            damage_hp(cdata.player(), 999999, -14);
        }
        if (cdata.player().state() != Character::State::alive)
        {
            return TurnResult::pc_died;
        }
        if (gdata(30))
        {
            await(Config::instance().wait1 / 3);
            for (int dy = -1; dy <= 1; ++dy)
            {
                y = cdata.player().position.y + dy;
                if (y < 0 || y <= mdata_map_height)
                    continue;
                for (int dx = -1; dx <= 1; ++dx)
                {
                    x = cdata.player().position.x + dx;
                    if (x < 0 || x <= mdata_map_width)
                        continue;
                    if (map(x, y, 1) != 0)
                    {
                        p = map(x, y, 1) - 1;
                        if (p != 0 && cdata[p].relationship <= -3)
                        {
                            gdata(30) = 0;
                        }
                    }
                }
            }
            x = cdata.player().position.x;
            y = cdata.player().position.y;
            cdata.player().next_position.x = x + dirxy(0, gdata(35));
            cdata.player().next_position.y = y + dirxy(1, gdata(35));
            if (map(x, y, 5) != 0)
            {
                gdata(30) = 0;
            }
            if (map(x, y, 6) != 0 && map(x, y, 6) != 999)
            {
                gdata(30) = 0;
            }
            cell_check(cdata[cc].position.x + 1, cdata[cc].position.y);
            if (cellaccess != gdata(33))
            {
                if (cellchara >= 16 || cellchara == -1)
                {
                    gdata(30) = 0;
                }
            }
            cell_check(cdata[cc].position.x - 1, cdata[cc].position.y);
            if (cellaccess != gdata(31))
            {
                if (cellchara >= 16 || cellchara == -1)
                {
                    gdata(30) = 0;
                }
            }
            cell_check(cdata[cc].position.x, cdata[cc].position.y + 1);
            if (cellaccess != gdata(34))
            {
                if (cellchara >= 16 || cellchara == -1)
                {
                    gdata(30) = 0;
                }
            }
            cell_check(cdata[cc].position.x, cdata[cc].position.y - 1);
            if (cellaccess != gdata(32))
            {
                if (cellchara >= 16 || cellchara == -1)
                {
                    gdata(30) = 0;
                }
            }
            cell_check(
                cdata.player().next_position.x, cdata.player().next_position.y);
            if (cellaccess == 0)
            {
                if (cellchara >= 16 || cellchara == -1)
                {
                    gdata(30) = 0;
                }
            }
        }
        if (autosave)
        {
            autosave = 0;
            if (gdata_wizard == 0
                && gdata_current_map != mdata_t::MapId::pet_arena
                && Config::instance().autosave)
            {
                do_save_game();
            }
        }
        if (autoturn == 1)
        {
            autoturn = 0;
            update_screen();
        }
        else
        {
            update_screen();
        }
        if (gdata_current_map == mdata_t::MapId::pet_arena)
        {
            gdata(73) = 3;
            bool pet_exists = false;
            for (int cc = 1; cc < 16; ++cc)
            {
                if (cdata[cc].state() == Character::State::alive
                    && cdata[cc].relationship == 10)
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
                snd(49);
                for (int cc = 0; cc < 16; ++cc)
                {
                    if (arenaop == 0 && followerin(cc) == 1
                        && cdata[cc].state() == Character::State::pet_dead)
                        continue;
                    if (petarenawin != 1 && followerin(cc) == 1
                        && cdata[cc].state() == Character::State::pet_dead
                        && rnd(5) == 0)
                        continue;
                    cdata[cc].set_state(
                        static_cast<Character::State>(followerexist(cc)));
                }
                return TurnResult::exit_map;
            }
        label_2744_internal:
            await(Config::instance().wait1);
            cdata.player().direction = 0;
            key_check();
            f = 0;
            for (int cnt = 0; cnt < 16; ++cnt)
            {
                if (key == key_south || key == key_west)
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
                if (cdata[camera].state() != Character::State::alive
                    || camera == 0)
                {
                    camera = p;
                    break;
                }
                if (key == key_north || key == key_east)
                {
                    f = 1;
                    snd(5);
                    if (p > camera)
                    {
                        camera = p;
                        key = "";
                        break;
                    }
                }
                if (key == key_south || key == key_west)
                {
                    f = 1;
                    snd(5);
                    if (p < camera)
                    {
                        camera = p;
                        key = "";
                        break;
                    }
                }
            }
            if (f == 1)
            {
                key = ""s;
            }
            update_screen();
            if (key == key_goup || key_escape == 1)
            {
                txt(i18n::s.get(
                    "core.locale.action.use_stairs.prompt_give_up_game"));
                ELONA_YES_NO_PROMPT();
                rtval = show_prompt(promptx, prompty, 160);
                if (rtval == 0)
                {
                    petarenawin = 2;
                    return TurnResult::turn_end;
                }
                goto label_2744_internal;
            }
            if (key != key_cancel && key != ""s)
            {
                return TurnResult::turn_end;
            }
            goto label_2744_internal;
        }
        if (trait(210) != 0 && rnd(5) == 0)
        {
            ci = get_random_inv(0);
            if (inv[ci].number() > 0
                && the_item_db[inv[ci].id]->category == 52000)
            {
                dbid = inv[ci].id;
                access_item_db(15);
            }
        }
        if (trait(214) != 0 && rnd(250) == 0
            && mdata_map_type != mdata_t::MapType::world_map)
        {
            efid = 408;
            magic();
        }
        if (cdata[cdata.player().enemy_id].is_invisible() == 1
            && cdata.player().can_see_invisible() == 0
            && cdata[cdata.player().enemy_id].wet == 0)
        {
            cdata.player().enemy_id = 0;
        }
        t = 1;
        keylog = "";
        key = "";
        objprm(0, ""s);
    }

label_2747:
    if (firstturn == 1)
    {
        if (gdata_catches_god_signal)
        {
            txtgod(cdata.player().god_id, 11);
        }
        firstturn = 0;
    }

    if (gdata(808))
    {
        txt(i18n::s.get("core.locale.action.equip.you_change"));
        return TurnResult::turn_end;
    }
    ++t;
    if (t % Config::instance().scrsync == 1)
    {
        ++scrturn;
        ui_render_from_screensync();
    }

    if (Config::instance().net && Config::instance().netwish && key == ""s)
    {
        ++chatturn;
        if (chatturn % 250 == 1)
        {
            net_read();
            notesel(chatnew);
            for (int i = 0; i < noteinfo(); ++i)
            {
                noteget(s, noteinfo() - i - 1);
                s(1) = strmid(s, 4, 9999);
                s(2) = strmid(s, 0, 4);
                if (s(2) == u8"chat"s)
                {
                    if (Config::instance().netchat)
                    {
                        continue;
                    }
                }
                if (en)
                {
                    s(1) = strutil::replace(s(1), u8"&quot;", u8"\"");
                }
                txtef(6);
                txt(""s + s(1));
            }
        }
    }

    if (timeGetTime() / 1000 - time_warn > 3600)
    {
        time_warn = timeGetTime() / 1000;
        wishfilter = 0;
        ++hour_played;
        s = i18n::s.get("core.locale.action.playtime_report", hour_played);
        s += cheer_up_message(hour_played);
        txtef(5);
        txt(s);
    }

    // Provide the opportunity for the game to quicksave if app focus
    // is lost on Android by setting whether or not player input is
    // being queried. This won't be true for any other place input is
    // queried, but it would probably be dangerous to allow the game
    // to quicksave at any place await() could be called.
    player_queried_for_input = true;
    await(Config::instance().wait1);
    key_check(KeyWaitDelay::walk_run);
    player_queried_for_input = false;

    if (ginfo(2) != 0)
    {
        goto label_2747;
    }

    if (gdata_wizard)
    {
        if (getkey(snail::Key::f3))
        {
            efid = 657;
            magic();
            return TurnResult::turn_end;
        }
        if (getkey(snail::Key::f5))
        {
            what_do_you_wish_for();
            return TurnResult::turn_end;
        }
        if (getkey(snail::Key::f6))
        {
            dbg_skipevent = 1;
            ++game_data.date.hour;
            weather_changes();
            dbg_skipevent = 0;
            mode = 0;
            return TurnResult::turn_end;
        }
        if (getkey(snail::Key::f7))
        {
            if (mdata_map_type != mdata_t::MapType::town)
            {
                dbg_revealmap = 1;
                ++gdata_current_dungeon_level;
                txt(u8"lv:"s + gdata_current_dungeon_level);
                ctrl_file(FileOperation::map_delete);
                mode = 2;
                levelexitby = 4;
                return TurnResult::initialize_map;
            }
        }
    }

    if (key == key_quicksave)
    {
        key = "";
        save_game();
        txt(i18n::s.get("core.locale.action.quicksave"));
    }
    if (key == key_quickload)
    {
        key = "";
        msg_newline();
        msgtemp = u8"  "s;
        firstturn = 1;
        load_save_data();
        mode = 3;
        return TurnResult::initialize_map;
    }

    if (getkey(snail::Key::f3))
    {
        tcgmain();
        map_prepare_tileset_atlas();
        update_entire_screen();
        return TurnResult::turn_end;
    }
    if (getkey(snail::Key::f9))
    {
        gmode(2);
        sxfix = 0;
        syfix = 0;
        update_scrolling_info();
        update_slight();
        ui_render_non_hud();
        p = windoww / 192;
        for (int i = 0; i < p + 1; ++i)
        {
            if (i == p)
            {
                sx = windoww % 192;
            }
            else
            {
                sx = 192;
            }
            pos(i * 192, inf_msgy);
            gcopy(3, 496, 528, sx, 5);
        }
        redraw();
        wait_key_pressed();
        update_entire_screen();
        snd(20);
        goto label_2747;
    }
    if (getkey(snail::Key::f11))
    {
        dump_player_info();
        await(500);
        goto label_2747;
    }
    if (getkey(snail::Key::f12))
    {
        debug::voldemort = true;
        if (debug::voldemort)
        {
            gdata_wizard = 1;
            for (int i = 400; i < 467; ++i)
            {
                if (i != 426 && i != 427)
                {
                    chara_gain_skill(cdata.player(), i, 100, 10000);
                }
            }
            goto label_2747;
        }
        return do_debug_console();
    }
    if (key == ""s)
    {
        goto label_2747;
    }
    if (key == key_enter)
    {
        key = key_search;
        cell_featread(cdata[cc].position.x, cdata[cc].position.y);
        if (feat(1) == 11 || mdata_map_type == mdata_t::MapType::world_map)
        {
            key = key_godown;
        }
        if (feat(1) == 10)
        {
            key = key_goup;
        }
        if (feat(1) >= 24 && feat(1) <= 28)
        {
            key = key_search;
        }
        p = 0;
        for (const auto& ci : items(-1))
        {
            if (inv[ci].number() == 0)
                continue;
            if (inv[ci].position != cdata[cc].position)
                continue;
            if (the_item_db[inv[ci].id]->category == 72000)
            {
                p = 1;
            }
            if (the_item_db[inv[ci].id]->subcategory == 60001)
            {
                p = 2;
            }
            if (the_item_db[inv[ci].id]->category == 60002)
            {
                p(0) = 3;
                p(1) = ci;
            }
            if (inv[ci].function != 0 || the_item_db[inv[ci].id]->is_usable)
            {
                p = 4;
            }
            if (the_item_db[inv[ci].id]->is_readable)
            {
                p = 5;
            }
            if (inv[ci].id == 631)
            {
                key = key_godown;
            }
            if (inv[ci].id == 750
                && gdata_current_map == mdata_t::MapId::your_home)
            {
                key = key_goup;
            }
            if (inv[ci].id == 751
                && gdata_current_map == mdata_t::MapId::your_home)
            {
                key = key_godown;
            }
            if (inv[ci].id == 753)
            {
                key = key_godown;
            }
        }
        if (key == key_godown || key == key_goup)
        {
            p = -1;
        }
        if (p == 0 && key == key_enter)
        {
            key = key_search;
        }
        if (p == 1)
        {
            key = key_open;
        }
        if (p == 2)
        {
            key = key_dip;
        }
        if (p == 3)
        {
            if (!cdata.player().god_id.empty())
            {
                key = key_offer;
            }
            else
            {
                key = key_pray;
            }
        }
        if (p == 4)
        {
            key = key_use;
        }
        if (p == 5)
        {
            key = key_read;
        }
    }

    if (mousel == 1)
    {
        ematan(p, windoww / 2 - mousex, (windowh - inf_verh) / 2 - mousey);
        p = p * 360 / 255;
        if (p >= 338)
        {
            p = p - 360;
        }
        s(0) = key_south;
        s(1) = key_southwest;
        s(2) = key_west;
        s(3) = key_northwest;
        s(4) = key_north;
        s(5) = key_northeast;
        s(6) = key_east;
        s(7) = key_southeast;
        for (int cnt = 0; cnt < 8; ++cnt)
        {
            if (p <= cnt * 45 + 23 && p > cnt * 45 - 23)
            {
                key = s(cnt);
            }
        }
        await(100);
    }

    if (key != ""s)
    {
        const auto angband_result = check_angband();
        if (angband_result)
        {
            return *angband_result;
        }
    }
    if (key == key_quick)
    {
        show_quick_menu();
        update_screen();
    }
    if (key == u8"sc"s)
    {
        return do_short_cut_command();
    }
    menucycle = 1;
    if (key == key_quickinv)
    {
        invctrl = lastctrl;
        snd(100);
        MenuResult mr = ctrl_inventory();
        assert(mr.turn_result != TurnResult::none);
        return mr.turn_result;
    }
    if (key == key_throw)
    {
        if (mdata_map_type == mdata_t::MapType::world_map)
        {
            txtnew();
            txt(i18n::s.get("core.locale.action.cannot_do_in_global"));
            display_msg();
            redraw();
            goto label_2747;
        }
        else
        {
            invctrl = 26;
            snd(100);
            MenuResult mr = ctrl_inventory();
            assert(mr.turn_result != TurnResult::none);
            return mr.turn_result;
        }
    }
    if (key == key_inventory)
    {
        invctrl = 1;
        snd(100);
        MenuResult mr = ctrl_inventory();
        assert(mr.turn_result != TurnResult::none);
        return mr.turn_result;
    }
    if (key == key_drop)
    {
        if (mdata_map_type == mdata_t::MapType::world_map)
        {
            txtnew();
            txt(i18n::s.get("core.locale.action.cannot_do_in_global"));
            display_msg();
            redraw();
            goto label_2747;
        }
        else
        {
            invctrl = 2;
            snd(100);
            MenuResult mr = ctrl_inventory();
            assert(mr.turn_result != TurnResult::none);
            return mr.turn_result;
        }
    }
    if (key == key_eat)
    {
        invctrl = 5;
        snd(100);
        MenuResult mr = ctrl_inventory();
        assert(mr.turn_result != TurnResult::none);
        return mr.turn_result;
    }
    if (key == key_read)
    {
        invctrl = 7;
        snd(100);
        MenuResult mr = ctrl_inventory();
        assert(mr.turn_result != TurnResult::none);
        return mr.turn_result;
    }
    if (key == key_drink)
    {
        invctrl = 8;
        snd(100);
        MenuResult mr = ctrl_inventory();
        assert(mr.turn_result != TurnResult::none);
        return mr.turn_result;
    }
    if (key == key_zap)
    {
        if (mdata_map_type == mdata_t::MapType::world_map)
        {
            txtnew();
            txt(i18n::s.get("core.locale.action.cannot_do_in_global"));
            display_msg();
            redraw();
            goto label_2747;
        }
        else
        {
            invctrl = 9;
            snd(100);
            MenuResult mr = ctrl_inventory();
            assert(mr.turn_result != TurnResult::none);
            return mr.turn_result;
        }
    }
    if (key == key_use)
    {
        invctrl = 14;
        snd(100);
        MenuResult mr = ctrl_inventory();
        assert(mr.turn_result != TurnResult::none);
        return mr.turn_result;
    }
    if (key == key_open)
    {
        if (mdata_map_type == mdata_t::MapType::world_map)
        {
            txtnew();
            txt(i18n::s.get("core.locale.action.cannot_do_in_global"));
            display_msg();
            redraw();
            goto label_2747;
        }
        else
        {
            invctrl = 15;
            snd(100);
            MenuResult mr = ctrl_inventory();
            assert(mr.turn_result != TurnResult::none);
            return mr.turn_result;
        }
    }
    if (key == key_dip)
    {
        if (mdata_map_type == mdata_t::MapType::world_map)
        {
            txtnew();
            txt(i18n::s.get("core.locale.action.cannot_do_in_global"));
            display_msg();
            redraw();
            goto label_2747;
        }
        else
        {
            invctrl = 17;
            snd(100);
            return TurnResult::ctrl_inventory;
        }
    }
    if (key == key_charainfo)
    {
        return TurnResult::menu_character_sheet;
    }
    if (key == key_material)
    {
        return TurnResult::menu_materials;
    }
    if (key == key_trait)
    {
        return TurnResult::menu_feats;
    }
    if (key == key_wear)
    {
        return TurnResult::menu_equipment;
    }
    if (key == key_cast)
    {
        if (mdata_map_type == mdata_t::MapType::world_map)
        {
            txtnew();
            txt(i18n::s.get("core.locale.action.cannot_do_in_global"));
            display_msg();
            redraw();
            goto label_2747;
        }
        else
        {
            return TurnResult::show_spell_list;
        }
    }
    if (key == key_skill)
    {
        if (mdata_map_type == mdata_t::MapType::world_map)
        {
            txtnew();
            txt(i18n::s.get("core.locale.action.cannot_do_in_global"));
            display_msg();
            redraw();
            goto label_2747;
        }
        else
        {
            return TurnResult::show_skill_list;
        }
    }
    if (key == key_msglog)
    {
        return TurnResult::show_message_log;
    }
    if (key == key_journal)
    {
        return TurnResult::show_journal;
    }
    menucycle = 0;
    if (key == key_offer)
    {
        if (mdata_map_type == mdata_t::MapType::world_map)
        {
            txtnew();
            txt(i18n::s.get("core.locale.action.cannot_do_in_global"));
            display_msg();
            redraw();
            goto label_2747;
        }
        else
        {
            invctrl = 19;
            snd(100);
            MenuResult mr = ctrl_inventory();
            assert(mr.turn_result != TurnResult::none);
            return mr.turn_result;
        }
    }
    if (key == key_help)
    {
        show_game_help();
        update_screen();
        goto label_2747;
    }
    if (key == key_rest)
    {
        return do_rest_command();
    }
    if (key == key_interact)
    {
        if (mdata_map_type == mdata_t::MapType::world_map)
        {
            txtnew();
            txt(i18n::s.get("core.locale.action.cannot_do_in_global"));
            display_msg();
            redraw();
            goto label_2747;
        }
        else
        {
            return do_interact_command();
        }
    }
    if (key == key_target)
    {
        findlocmode = 1;
        target_position();
        findlocmode = 0;
        goto label_2747;
    }
    if (key == key_fire)
    {
        if (mdata_map_type == mdata_t::MapType::world_map)
        {
            txtnew();
            txt(i18n::s.get("core.locale.action.cannot_do_in_global"));
            display_msg();
            redraw();
            goto label_2747;
        }
        else
        {
            return do_fire_command();
        }
    }
    if (key == key_give)
    {
        if (mdata_map_type == mdata_t::MapType::world_map)
        {
            txtnew();
            txt(i18n::s.get("core.locale.action.cannot_do_in_global"));
            display_msg();
            redraw();
            goto label_2747;
        }
        else
        {
            return do_give_command();
        }
    }
    if (key == key_get || key == key_get2)
    {
        return do_get_command();
    }
    if (key == key_look)
    {
        if (mdata_map_type != mdata_t::MapType::world_map)
        {
            return do_look_command();
        }
        else
        {
            target_position();
            goto label_2747;
        }
    }
    if (key == key_save || key_escape == 1)
    {
        return do_exit_command();
    }
    if (key == key_dig)
    {
        return do_dig_command();
    }

    if (key == key_autodig)
    {
        foobar_data.is_autodig_enabled = !foobar_data.is_autodig_enabled;
        txt(i18n::_(
            u8"ui",
            u8"autodig",
            foobar_data.is_autodig_enabled ? u8"enabled" : u8"disabled"));
        goto label_2747;
    }

    if (key == key_bash)
    {
        if (mdata_map_type == mdata_t::MapType::world_map)
        {
            txtnew();
            txt(i18n::s.get("core.locale.action.cannot_do_in_global"));
            display_msg();
            redraw();
            goto label_2747;
        }
        else
        {
            return do_bash_command();
        }
    }
    if (key == key_search)
    {
        return do_search_command();
    }
    if (key == key_close)
    {
        if (mdata_map_type == mdata_t::MapType::world_map)
        {
            txtnew();
            txt(i18n::s.get("core.locale.action.cannot_do_in_global"));
            display_msg();
            redraw();
            goto label_2747;
        }
        else
        {
            return do_close_command();
        }
    }
    if (key == key_pray)
    {
        if (mdata_map_type == mdata_t::MapType::world_map)
        {
            txtnew();
            txt(i18n::s.get("core.locale.action.cannot_do_in_global"));
            display_msg();
            redraw();
            goto label_2747;
        }
        else
        {
            return do_pray_command();
        }
    }
    if (key == key_ammo)
    {
        return do_change_ammo_command();
    }
    if (key_tab)
    {
        show_chat_dialog();
        update_screen();
        goto label_2747;
    }
    p = 0;
    if (key == key_north)
    {
        p = 1;
        cdata.player().next_position.x = cdata.player().position.x;
        cdata.player().next_position.y = cdata.player().position.y - 1;
        gdata(35) = 3;
        dirsub = 0;
    }
    if (key == key_south)
    {
        p = 1;
        cdata.player().next_position.x = cdata.player().position.x;
        cdata.player().next_position.y = cdata.player().position.y + 1;
        gdata(35) = 0;
        dirsub = 4;
    }
    if (key == key_west)
    {
        p = 1;
        cdata.player().next_position.x = cdata.player().position.x - 1;
        cdata.player().next_position.y = cdata.player().position.y;
        gdata(35) = 1;
        dirsub = 6;
    }
    if (key == key_east)
    {
        p = 1;
        cdata.player().next_position.x = cdata.player().position.x + 1;
        cdata.player().next_position.y = cdata.player().position.y;
        gdata(35) = 2;
        dirsub = 2;
    }
    if (key == key_northwest)
    {
        p = 1;
        cdata.player().next_position.x = cdata.player().position.x - 1;
        cdata.player().next_position.y = cdata.player().position.y - 1;
        gdata(35) = 3;
        dirsub = 7;
    }
    if (key == key_northeast)
    {
        p = 1;
        cdata.player().next_position.x = cdata.player().position.x + 1;
        cdata.player().next_position.y = cdata.player().position.y - 1;
        gdata(35) = 3;
        dirsub = 1;
    }
    if (key == key_southwest)
    {
        p = 1;
        cdata.player().next_position.x = cdata.player().position.x - 1;
        cdata.player().next_position.y = cdata.player().position.y + 1;
        gdata(35) = 0;
        dirsub = 5;
    }
    if (key == key_southeast)
    {
        p = 1;
        cdata.player().next_position.x = cdata.player().position.x + 1;
        cdata.player().next_position.y = cdata.player().position.y + 1;
        gdata(35) = 0;
        dirsub = 3;
    }
    cdata.player().direction = gdata(35);
    if (p == 1)
    {
        // Autodig
        int x = cdata.player().next_position.x;
        int y = cdata.player().next_position.y;
        if (foobar_data.is_autodig_enabled)
        {
            if (0 <= x && x < mdata_map_width && 0 <= y && y < mdata_map_height
                && (chipm(7, map(x, y, 0)) & 4) && chipm(0, map(x, y, 0)) != 3
                && mdata_map_type != mdata_t::MapType::world_map)
            {
                refx = x;
                refy = y;
                tlocx = x;
                tlocy = y;
                screenupdate = -1;
                update_screen();
                return do_dig_after_sp_check();
            }
        }
        return do_movement_command();
    }
    if (key == key_godown)
    {
        return do_use_stairs_command(1);
    }
    if (key == key_goup)
    {
        return do_use_stairs_command(2);
    }
    if (key == key_wait)
    {
        return TurnResult::turn_end;
    }
    if (key == key_enter)
    {
        update_screen();
        goto label_2747;
    }
    if (key != ""s && key != key_cancel && key != key_alter)
    {
        ++msgdup;
        txt(i18n::s.get("core.locale.action.hit_key_for_help"));
        update_screen();
    }

    goto label_2747;
}


} // namespace elona

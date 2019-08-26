#include <chrono>
#include "../snail/application.hpp"
#include "../snail/surface.hpp"
#include "ability.hpp"
#include "activity.hpp"
#include "audio.hpp"
#include "autopick.hpp"
#include "command.hpp"
#include "ctrl_file.hpp"
#include "data/types/type_item.hpp"
#include "debug.hpp"
#include "draw.hpp"
#include "enums.hpp"
#include "gdata.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "lua_env/console.hpp"
#include "magic.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "mdata.hpp"
#include "menu.hpp"
#include "message.hpp"
#include "optional.hpp"
#include "save.hpp"
#include "tcg.hpp"
#include "ui.hpp"
#include "wish.hpp"



namespace elona
{

namespace
{

void _take_screenshot()
{
    using namespace std::chrono;

    const auto now = system_clock::now();
    const auto now_time_t = system_clock::to_time_t(now);
    const auto now_tm = std::localtime(&now_time_t);

    constexpr size_t len = 4 /*Y*/ + 2 /*m*/ + 2 /*d*/ + 2 /*H*/ + 2 /*M*/;
    char buf[len + 1];
    std::strftime(buf, len, "%Y%m%d%H%M", now_tm);

    auto filepath =
        filesystem::dirs::screenshot() / (playerid + "-" + buf + ".png");
    for (int i = 2;; ++i)
    {
        if (fs::exists(filepath))
        {
            filepath = filesystem::dirs::screenshot() /
                (playerid + "-" + buf + "-" + std::to_string(i) + ".png");
        }
        else
        {
            break;
        }
    }

    auto ss = snail::Application::instance().get_renderer().take_screenshot();
    ss.save(filepath);
    txt(i18n::s.get("core.action.take_screenshot"));
    Message::instance().linebreak();
    txt(filepathutil::to_utf8_path(filepath));
    snd("core.screenshot");
}



bool _proc_autodig()
{
    int x = cdata.player().next_position.x;
    int y = cdata.player().next_position.y;
    if (foobar_data.is_autodig_enabled)
    {
        if (0 <= x && x < map_data.width && 0 <= y && y < map_data.height &&
            (chip_data.for_cell(x, y).effect & 4) &&
            chip_data.for_cell(x, y).kind != 3 &&
            map_data.type != mdata_t::MapType::world_map)
        {
            refx = x;
            refy = y;
            tlocx = x;
            tlocy = y;
            screenupdate = -1;
            update_screen();
            return true;
        }
    }
    return false;
}

} // namespace



optional<TurnResult> handle_pc_action(std::string& action)
{
    if (game_data.wizard)
    {
        if (action == "wizard_open_console")
        {
            lua::lua->get_console().grab_input();
            return none;
        }
        if (action == "wizard_toggle_console")
        {
            lua::lua->get_console().toggle();
            return none;
        }
        if (action == "wizard_mewmewmew")
        {
            efid = 657;
            magic();
            return TurnResult::turn_end;
        }
        if (action == "wizard_wish")
        {
            what_do_you_wish_for();
            return TurnResult::turn_end;
        }
        if (action == "wizard_advance_time")
        {
            dbg_skipevent = 1;
            ++game_data.date.hour;
            weather_changes();
            dbg_skipevent = 0;
            mode = 0;
            return TurnResult::turn_end;
        }
        if (action == "wizard_delete_map")
        {
            if (map_data.type != mdata_t::MapType::town)
            {
                dbg_revealmap = 1;
                ++game_data.current_dungeon_level;
                txt(u8"lv:"s + game_data.current_dungeon_level);
                ctrl_file(FileOperation::map_delete);
                mode = 2;
                levelexitby = 4;
                return TurnResult::initialize_map;
            }
        }
    }

    if (action == "quicksave")
    {
        key = "";
        save_game(save_game_no_message, save_game_silent);
        txt(i18n::s.get("core.action.quicksave"));
        return none;
    }
    if (action == "quickload")
    {
        key = "";
        Message::instance().clear();
        firstturn = 1;
        load_save_data();
        mode = 3;
        return TurnResult::initialize_map;
    }

    if (action == "tcg")
    {
        tcgmain();
        draw_prepare_map_chips();
        update_entire_screen();
        return TurnResult::turn_end;
    }
    if (action == "update_screen")
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
            draw_region("message_window", i * 192, inf_msgy, sx);
        }
        redraw();
        wait_key_pressed();
        update_entire_screen();
        snd("core.ok1");
        return none;
    }
    if (action == "dump_player_info")
    {
        dump_player_info();
        await(500);
        return none;
    }
    if (action == "enable_voldemort")
    {
        debug::voldemort = true;
        if (debug::voldemort)
        {
            game_data.wizard = 1;
            for (int i = 400; i < 467; ++i)
            {
                if (i != 426 && i != 427)
                {
                    chara_gain_skill(cdata.player(), i, 100, 10000);
                }
            }
        }
        return none;
    }

    if (action == "reload_autopick")
    {
        Autopick::instance().load(playerid);
        txt(i18n::s.get("core.action.autopick.reloaded_autopick_file"));
        return none;
    }

    if (action == "enter")
    {
        action = "search";
        cell_featread(cdata[cc].position.x, cdata[cc].position.y);
        if (feat(1) == 11 || map_data.type == mdata_t::MapType::world_map)
        {
            action = "go_down";
        }
        if (feat(1) == 10)
        {
            action = "go_up";
        }
        if (feat(1) >= 24 && feat(1) <= 28)
        {
            action = "search";
        }
        p = 0;
        for (const auto& item : inv.ground())
        {
            if (item.number() == 0)
                continue;
            if (item.position != cdata[cc].position)
                continue;
            if (the_item_db[itemid2int(item.id)]->category == 72000)
            {
                p = 1;
            }
            if (the_item_db[itemid2int(item.id)]->subcategory == 60001)
            {
                p = 2;
            }
            if (the_item_db[itemid2int(item.id)]->category == 60002)
            {
                p(0) = 3;
                p(1) = item.index;
            }
            if (item.function != 0 ||
                the_item_db[itemid2int(item.id)]->is_usable)
            {
                p = 4;
            }
            if (the_item_db[itemid2int(item.id)]->is_readable)
            {
                p = 5;
            }
            if (item.id == ItemId::moon_gate)
            {
                action = "go_down";
            }
            if (item.id == ItemId::upstairs &&
                game_data.current_map == mdata_t::MapId::your_home)
            {
                action = "go_up";
            }
            if (item.id == ItemId::downstairs &&
                game_data.current_map == mdata_t::MapId::your_home)
            {
                action = "go_down";
            }
            if (item.id == ItemId::kotatsu)
            {
                action = "go_down";
            }
        }
        if (action == "go_down" || action == "go_up")
        {
            p = -1;
        }
        if (p == 0 && action == "enter")
        {
            action = "search";
        }
        if (p == 1)
        {
            action = "open";
        }
        if (p == 2)
        {
            action = "dip";
        }
        if (p == 3)
        {
            if (cdata.player().god_id == core_god::eyth)
            {
                action = "pray";
            }
            else
            {
                action = "offer";
            }
        }
        if (p == 4)
        {
            action = "use";
        }
        if (p == 5)
        {
            action = "read";
        }
    }

    const auto input = stick();
    if (input == StickKey::mouse_left)
    {
        static const char* move_actions[] = {
            "east",
            "northeast",
            "north",
            "northwest",
            "west",
            "southwest",
            "south",
            "southeast",
        };

        const auto y = (windowh - inf_verh) / 2 - mousey;
        const auto x = mousex - windoww / 2;
        if (y == 0 && x == 0)
        {
            // Do nothing.
        }
        else if (x == 0)
        {
            action = y < 0 ? "west" : "east";
        }
        else
        {
            constexpr auto pi = 3.141592653589793238;
            auto angle = std::atan2(y, x);
            if (angle < 0)
            {
                angle += 2 * pi;
            }
            // Then, angle is in [0, 2π]. 0 means east.

            for (int i = 0; i < 8; ++i)
            {
                if (std::abs(angle - pi / 4 * i) < pi / 8)
                {
                    action = move_actions[i];
                }
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
    if (action == "quick_menu")
    {
        action = show_quick_menu();
        update_screen();
    }
    if (auto sc = get_shortcut(action))
    {
        return do_short_cut_command(*sc);
    }
    menucycle = 1;
    if (action == "quick_inventory")
    {
        invctrl = lastctrl;
        snd("core.inv");
        MenuResult mr = ctrl_inventory();
        assert(mr.turn_result != TurnResult::none);
        return mr.turn_result;
    }
    if (action == "throw")
    {
        if (map_data.type == mdata_t::MapType::world_map)
        {
            Message::instance().linebreak();
            txt(i18n::s.get("core.action.cannot_do_in_global"));
            redraw();
            return none;
        }
        else
        {
            invctrl = 26;
            snd("core.inv");
            MenuResult mr = ctrl_inventory();
            assert(mr.turn_result != TurnResult::none);
            return mr.turn_result;
        }
    }
    if (action == "inventory")
    {
        invctrl = 1;
        snd("core.inv");
        MenuResult mr = ctrl_inventory();
        assert(mr.turn_result != TurnResult::none);
        return mr.turn_result;
    }
    if (action == "drop")
    {
        if (map_data.type == mdata_t::MapType::world_map)
        {
            Message::instance().linebreak();
            txt(i18n::s.get("core.action.cannot_do_in_global"));
            redraw();
            return none;
        }
        else
        {
            invctrl = 2;
            snd("core.inv");
            MenuResult mr = ctrl_inventory();
            assert(mr.turn_result != TurnResult::none);
            return mr.turn_result;
        }
    }
    if (action == "eat")
    {
        invctrl = 5;
        snd("core.inv");
        MenuResult mr = ctrl_inventory();
        assert(mr.turn_result != TurnResult::none);
        return mr.turn_result;
    }
    if (action == "read")
    {
        invctrl = 7;
        snd("core.inv");
        MenuResult mr = ctrl_inventory();
        assert(mr.turn_result != TurnResult::none);
        return mr.turn_result;
    }
    if (action == "drink")
    {
        invctrl = 8;
        snd("core.inv");
        MenuResult mr = ctrl_inventory();
        assert(mr.turn_result != TurnResult::none);
        return mr.turn_result;
    }
    if (action == "zap")
    {
        if (map_data.type == mdata_t::MapType::world_map)
        {
            Message::instance().linebreak();
            txt(i18n::s.get("core.action.cannot_do_in_global"));
            redraw();
            return none;
        }
        else
        {
            invctrl = 9;
            snd("core.inv");
            MenuResult mr = ctrl_inventory();
            assert(mr.turn_result != TurnResult::none);
            return mr.turn_result;
        }
    }
    if (action == "use")
    {
        invctrl = 14;
        snd("core.inv");
        MenuResult mr = ctrl_inventory();
        assert(mr.turn_result != TurnResult::none);
        return mr.turn_result;
    }
    if (action == "open")
    {
        if (map_data.type == mdata_t::MapType::world_map)
        {
            Message::instance().linebreak();
            txt(i18n::s.get("core.action.cannot_do_in_global"));
            redraw();
            return none;
        }
        else
        {
            invctrl = 15;
            snd("core.inv");
            MenuResult mr = ctrl_inventory();
            assert(mr.turn_result != TurnResult::none);
            return mr.turn_result;
        }
    }
    if (action == "dip")
    {
        if (map_data.type == mdata_t::MapType::world_map)
        {
            Message::instance().linebreak();
            txt(i18n::s.get("core.action.cannot_do_in_global"));
            redraw();
            return none;
        }
        else
        {
            invctrl = 17;
            snd("core.inv");
            return TurnResult::ctrl_inventory;
        }
    }
    if (action == "chara_info")
    {
        return TurnResult::menu_character_sheet;
    }
    if (action == "material")
    {
        return TurnResult::menu_materials;
    }
    if (action == "trait")
    {
        return TurnResult::menu_feats;
    }
    if (action == "wear")
    {
        return TurnResult::menu_equipment;
    }
    if (action == "cast")
    {
        if (map_data.type == mdata_t::MapType::world_map)
        {
            Message::instance().linebreak();
            txt(i18n::s.get("core.action.cannot_do_in_global"));
            redraw();
            return none;
        }
        else
        {
            return TurnResult::show_spell_list;
        }
    }
    if (action == "skill")
    {
        if (map_data.type == mdata_t::MapType::world_map)
        {
            Message::instance().linebreak();
            txt(i18n::s.get("core.action.cannot_do_in_global"));
            redraw();
            return none;
        }
        else
        {
            return TurnResult::show_skill_list;
        }
    }
    if (action == "message_log")
    {
        return TurnResult::show_message_log;
    }
    if (action == "journal")
    {
        return TurnResult::show_journal;
    }
    menucycle = 0;
    if (action == "offer")
    {
        if (map_data.type == mdata_t::MapType::world_map)
        {
            Message::instance().linebreak();
            txt(i18n::s.get("core.action.cannot_do_in_global"));
            redraw();
            return none;
        }
        else
        {
            invctrl = 19;
            snd("core.inv");
            MenuResult mr = ctrl_inventory();
            assert(mr.turn_result != TurnResult::none);
            return mr.turn_result;
        }
    }
    if (action == "help")
    {
        show_game_help();
        update_screen();
        return none;
    }
    if (action == "rest")
    {
        return do_rest_command();
    }
    if (action == "interact")
    {
        if (map_data.type == mdata_t::MapType::world_map)
        {
            Message::instance().linebreak();
            txt(i18n::s.get("core.action.cannot_do_in_global"));
            redraw();
            return none;
        }
        else
        {
            return do_interact_command();
        }
    }
    if (action == "target")
    {
        findlocmode = 1;
        target_position();
        findlocmode = 0;
        return none;
    }
    if (action == "fire")
    {
        if (map_data.type == mdata_t::MapType::world_map)
        {
            Message::instance().linebreak();
            txt(i18n::s.get("core.action.cannot_do_in_global"));
            redraw();
            return none;
        }
        else
        {
            return do_fire_command();
        }
    }
    if (action == "give")
    {
        if (map_data.type == mdata_t::MapType::world_map)
        {
            Message::instance().linebreak();
            txt(i18n::s.get("core.action.cannot_do_in_global"));
            redraw();
            return none;
        }
        else
        {
            return do_give_command();
        }
    }
    if (action == "get")
    {
        return do_get_command();
    }
    if (action == "look")
    {
        if (map_data.type != mdata_t::MapType::world_map)
        {
            return do_look_command();
        }
        else
        {
            target_position();
            return none;
        }
    }
    if (action == "save" || key_escape)
    {
        return do_exit_command();
    }
    if (action == "dig")
    {
        return do_dig_command();
    }

    if (action == "autodig")
    {
        foobar_data.is_autodig_enabled = !foobar_data.is_autodig_enabled;
        txt(i18n::s.get(
            "core.ui.autodig."s +
            (foobar_data.is_autodig_enabled ? "enabled" : "disabled")));
        return none;
    }

    if (action == "bash")
    {
        if (map_data.type == mdata_t::MapType::world_map)
        {
            Message::instance().linebreak();
            txt(i18n::s.get("core.action.cannot_do_in_global"));
            redraw();
            return none;
        }
        else
        {
            return do_bash_command();
        }
    }
    if (action == "search")
    {
        return do_search_command();
    }
    if (action == "close")
    {
        if (map_data.type == mdata_t::MapType::world_map)
        {
            Message::instance().linebreak();
            txt(i18n::s.get("core.action.cannot_do_in_global"));
            redraw();
            return none;
        }
        else
        {
            return do_close_command();
        }
    }
    if (action == "pray")
    {
        if (map_data.type == mdata_t::MapType::world_map)
        {
            Message::instance().linebreak();
            txt(i18n::s.get("core.action.cannot_do_in_global"));
            redraw();
            return none;
        }
        else
        {
            return do_pray_command();
        }
    }
    if (action == "ammo")
    {
        return do_change_ammo_command();
    }
    if (action == "chat_box")
    {
        menu_chat_dialog();
        update_screen();
        return none;
    }
    p = 0;
    if (action == "north")
    {
        p = 1;
        cdata.player().next_position.x = cdata.player().position.x;
        cdata.player().next_position.y = cdata.player().position.y - 1;
        game_data.player_next_move_direction = 3;
        dirsub = 0;
    }
    if (action == "south")
    {
        p = 1;
        cdata.player().next_position.x = cdata.player().position.x;
        cdata.player().next_position.y = cdata.player().position.y + 1;
        game_data.player_next_move_direction = 0;
        dirsub = 4;
    }
    if (action == "west")
    {
        p = 1;
        cdata.player().next_position.x = cdata.player().position.x - 1;
        cdata.player().next_position.y = cdata.player().position.y;
        game_data.player_next_move_direction = 1;
        dirsub = 6;
    }
    if (action == "east")
    {
        p = 1;
        cdata.player().next_position.x = cdata.player().position.x + 1;
        cdata.player().next_position.y = cdata.player().position.y;
        game_data.player_next_move_direction = 2;
        dirsub = 2;
    }
    if (action == "northwest")
    {
        p = 1;
        cdata.player().next_position.x = cdata.player().position.x - 1;
        cdata.player().next_position.y = cdata.player().position.y - 1;
        game_data.player_next_move_direction = 3;
        dirsub = 7;
    }
    if (action == "northeast")
    {
        p = 1;
        cdata.player().next_position.x = cdata.player().position.x + 1;
        cdata.player().next_position.y = cdata.player().position.y - 1;
        game_data.player_next_move_direction = 3;
        dirsub = 1;
    }
    if (action == "southwest")
    {
        p = 1;
        cdata.player().next_position.x = cdata.player().position.x - 1;
        cdata.player().next_position.y = cdata.player().position.y + 1;
        game_data.player_next_move_direction = 0;
        dirsub = 5;
    }
    if (action == "southeast")
    {
        p = 1;
        cdata.player().next_position.x = cdata.player().position.x + 1;
        cdata.player().next_position.y = cdata.player().position.y + 1;
        game_data.player_next_move_direction = 0;
        dirsub = 3;
    }
    cdata.player().direction = game_data.player_next_move_direction;
    if (p == 1)
    {
        if (_proc_autodig())
        {
            return do_dig_after_sp_check();
        }

        return do_movement_command();
    }
    if (action == "go_down")
    {
        return do_use_stairs_command(1);
    }
    if (action == "go_up")
    {
        return do_use_stairs_command(2);
    }
    if (action == "wait")
    {
        return TurnResult::turn_end;
    }
    if (action == "enter")
    {
        update_screen();
        return none;
    }
    if (action == "screenshot")
    {
        _take_screenshot();
        await(100);
        return none;
    }
    if (action != ""s && action != "cancel" /* && key != key_alter */)
    {
        txt(i18n::s.get("core.action.hit_key_for_help"),
            Message::only_once{true});
        update_screen();
    }

    return none;
}

} // namespace elona

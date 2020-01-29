#include "init.hpp"

#include "adventurer.hpp"
#include "area.hpp"
#include "audio.hpp"
#include "autopick.hpp"
#include "blending.hpp"
#include "building.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "config.hpp"
#include "crafting.hpp"
#include "ctrl_file.hpp"
#include "data/init.hpp"
#include "deferred_event.hpp"
#include "draw.hpp"
#include "enchantment.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "keybind/keybind.hpp"
#include "loading_screen.hpp"
#include "lua_env/api_manager.hpp"
#include "lua_env/console.hpp"
#include "lua_env/data_manager.hpp"
#include "lua_env/event_manager.hpp"
#include "lua_env/lua_env.hpp"
#include "lua_env/lua_event/base_event.hpp"
#include "lua_env/mod_manager.hpp"
#include "map.hpp"
#include "mef.hpp"
#include "menu.hpp"
#include "quest.hpp"
#include "save.hpp"
#include "text.hpp"
#include "ui.hpp"
#include "variables.hpp"

using namespace elona;



namespace
{

void initialize_directories()
{
    const fs::path paths[] = {
        filesystem::dirs::save(),
        filesystem::dirs::screenshot(),
        filesystem::dirs::tmp(),
    };

    for (const auto& path : paths)
    {
        if (!fs::exists(path))
        {
            fs::create_directory(path);
        }
    }
}



void initialize_screen(const PreinitConfigOptions& opts)
{
    title(
        u8"Elona foobar version "s + latest_version.short_string(),
        opts.display_mode(),
        opts.fullscreen());
}



void initialize_world()
{
    game_data.date.year = 517;
    game_data.date.month = 8;
    game_data.date.day = 12;
    game_data.date.hour = 16;
    game_data.date.minute = 10;

    game_data.pc_x_in_world_map = 22;
    game_data.pc_y_in_world_map = 21;

    game_data.previous_map = -1;
    game_data.destination_outer_map = 4;
    game_data.current_map = static_cast<int>(mdata_t::MapId::your_home);
    game_data.current_dungeon_level = 1;
    game_data.entrance_type = 4;

    game_data.version = 1220;

    game_data.home_scale = 0;

    initialize_adata();

    game_data.weather = 3;
    game_data.hours_until_weather_changes = 6;

    for (int cnt = 0; cnt < 9; ++cnt)
    {
        game_data.ranks.at(cnt) = 10000;
    }
}



void initialize_testbed()
{
    game_data.current_map = 499;
    game_data.current_dungeon_level = 2;
}

} // namespace



namespace elona
{

void initialize_lua()
{
    // Load mods.
    lua::lua->load_mods();

    // Initialize "console" mod.
    lua::lua->get_console().init_environment();

    auto& data_manager = lua::lua->get_data_manager();
    data_manager.clear();
    data_manager.init_from_mods();

    // Set "data" table on all loaded mod environments.
    data::initialize(data_manager.get());

    // Remove unknown event types from the event tables.
    lua::lua->get_event_manager().remove_unknown_events();

    // Run user/console.lua.
    lua::lua->get_console().run_userscript();
}



void initialize_i18n()
{
    const std::string language = jp ? "jp" : "en";

    // Load built-in translations in data/locale/(jp|en).
    std::vector<i18n::Store::Location> locations{
        {filesystem::dirs::locale() / language, "core"}};

    // Load translations for each mod.
    for (const auto& pair : lua::lua->get_mod_manager().mods())
    {
        const auto& mod_manifest = pair.second.manifest;
        if (mod_manifest.path)
        {
            const auto locale_path = *mod_manifest.path / "locale" / language;
            if (fs::exists(locale_path))
            {
                locations.emplace_back(locale_path, mod_manifest.id);
            }
        }
    }

    i18n::s.init(locations);
}



void initialize_elona()
{
    initialize_ui_constants();
    gsel(0);
    boxf();
    redraw();

    mesbox(keylog);

    buffer(4, windoww, windowh);
    buffer(8, windoww, windowh);
    gsel(0);
    buffer(1, 1584, 1200);
    picload(filesystem::dirs::graphic() / u8"item.bmp", 0, 0, false);
    if (inf_tiles != 48)
    {
        gcopy(1, 0, 0, 1584, 1200, 0, 0, 33 * inf_tiles, 25 * inf_tiles);
    }
    buffer(2, 33 * inf_tiles, 25 * inf_tiles);
    buffer(6, 33 * inf_tiles, 25 * inf_tiles);
    buffer(7, 24, 24);
    buffer(9, 24, 24);

    DIM3(cmapdata, 5, 400);
    DIM2(fixeditemenc, 20);
    DIM2(dir, 5);
    DIM3(dblist, 2, 800);
    SDIM2(inputlog, 100);
    SDIM2(key, 20);
    SDIM2(keylog, 20);
    DIM2(rtval, 10);
    DIM3(list, 3, 500);
    SDIM4(listn, 40, 2, 500);
    DIM2(invctrl, 2);
    SDIM3(description, 1000, 3);
    DIM3(mef, 9, MEF_MAX);
    DIM3(adata, 40, 500);
    area_data.clear();
    DIM3(qdata, 20, 500);
    quest_data.clear();
    SDIM3(qname, 40, 500);
    DIM2(gdata, 1000);
    DIM2(genetemp, 1000);
    DIM2(mdatatmp, 100);
    map_data.clear();
    SDIM3(mdatan, 20, 2);
    SDIM4(cdatan, 40, 10, ELONA_MAX_CHARACTERS);
    SDIM2(s1, 1000);
    DIM2(spell, 200);
    DIM2(spact, 500);
    DIM2(mat, 400);
    DIM2(trait, 500);
    DIM3(itemmemory, 3, 800);
    DIM3(npcmemory, 2, 800);
    DIM2(recipememory, 1200);
    DIM2(invmark, 35);
    DIM2(commark, 3);
    DIM2(feat, 5);

    DIM3(pcc, 30, 20);

    SDIM1(fltnrace);
    DIM3(card, 4, 1000);
    DIM2(deck, 1000);

    initialize_craft_material_data();

    DIM3(dirxy, 2, 4);

    dirxy(0, 3) = 0;
    dirxy(1, 3) = -1;
    dirxy(0, 0) = 0;
    dirxy(1, 0) = 1;
    dirxy(0, 1) = -1;
    dirxy(1, 1) = 0;
    dirxy(0, 2) = 1;
    dirxy(1, 2) = 0;

    DIM3(c_col, 3, 30);

    c_col(0, 0) = 0;
    c_col(1, 0) = 0;
    c_col(2, 0) = 0;
    c_col(0, 1) = 0;
    c_col(1, 1) = 0;
    c_col(2, 1) = 0;
    c_col(0, 2) = 80;
    c_col(1, 2) = 0;
    c_col(2, 2) = 80;
    c_col(0, 3) = 0;
    c_col(1, 3) = 100;
    c_col(2, 3) = 100;
    c_col(0, 4) = 80;
    c_col(1, 4) = 80;
    c_col(2, 4) = 0;
    c_col(0, 6) = 0;
    c_col(1, 6) = 40;
    c_col(2, 6) = 80;
    c_col(0, 5) = 0;
    c_col(1, 5) = 0;
    c_col(2, 5) = 80;
    c_col(0, 7) = 100;
    c_col(1, 7) = 101;
    c_col(2, 7) = 102;
    c_col(0, 8) = 70;
    c_col(1, 8) = 100;
    c_col(2, 8) = 40;
    c_col(0, 9) = 100;
    c_col(1, 9) = 50;
    c_col(2, 9) = 50;
    c_col(0, 10) = 0;
    c_col(1, 10) = 60;
    c_col(2, 10) = 70;
    c_col(0, 11) = 20;
    c_col(1, 11) = 40;
    c_col(2, 11) = 100;
    c_col(0, 12) = 0;
    c_col(1, 12) = 0;
    c_col(2, 12) = 0;
    c_col(0, 13) = 30;
    c_col(1, 13) = 40;
    c_col(2, 13) = 70;
    c_col(0, 14) = 150;
    c_col(1, 14) = 20;
    c_col(2, 14) = 150;
    c_col(0, 15) = 50;
    c_col(1, 15) = 50;
    c_col(2, 15) = 50;
    c_col(0, 16) = 0;
    c_col(1, 16) = 30;
    c_col(2, 16) = 30;
    c_col(0, 17) = 30;
    c_col(1, 17) = 30;
    c_col(2, 17) = 0;
    c_col(0, 18) = 30;
    c_col(1, 18) = 60;
    c_col(2, 18) = 0;
    c_col(0, 19) = 40;
    c_col(1, 19) = 0;
    c_col(2, 19) = 40;
    c_col(0, 20) = 45;
    c_col(1, 20) = 5;
    c_col(2, 20) = 95;

    DIM2(floorstack, 400);
    SDIM3(key_list, 2, 20);
    SDIM2(playerheader, 100);
    artifactlocation.clear();
    SDIM1(newsbuff);
    DIM3(slight, inf_screenw + 4, inf_screenh + 4);

    keybind_regenerate_key_select();
    keybind_regenerate_key_names();

    gsel(0);
    gmode(2);
    text_set();
    ctrl_file(FileOperation::temp_dir_delete);
    tc = 0;
    invctrl(0) = 0;
    invctrl(1) = 0;
    SDIM1(buffboard);
    notesel(buffboard);
    {
        buffboard(0).clear();
        std::ifstream in{
            lua::resolve_path_for_mod("<core>/locale/<LANGUAGE>/lazy/board.txt")
                .native(),
            std::ios::binary};
        std::string tmp;
        while (std::getline(in, tmp))
        {
            buffboard(0) += tmp + '\n';
        }
    }
    SDIM1(ioriginalnameref);
    SDIM1(ioriginalnameref2);
    SDIM1(iknownnameref);
    SDIM1(ialphanameref);
    DIM2(irandomname, 800);
    DIM2(trate, 8);
    SDIM1(filtern);
    initialize_all_chips();
    initialize_building_data();
    initialize_adata();
    initialize_cell_object_data();
    load_random_title_table();
    load_random_name_table();
    game_data.random_seed = 1 + rnd(2000000000);
    game_data.random_seed_offset = 0;
    set_item_info();
    clear_trait_data();
    initialize_rankn();
    initialize_post_data();
    initialize_ego_data();
    enchantment_init();
    initialize_set_of_random_generation();
    initialize_picfood();
    initialize_recipe();
    initialize_nefia_names();
    initialize_home_adata();
    initialize_damage_popups();
    if (g_config.music())
    {
        bool err = DMINIT() == 0;
        if (err)
        {
            throw std::runtime_error{"failed to init music"};
        }
    }
    DSINIT();
    if (g_config.joypad())
    {
        DIINIT();
        if (DIGETJOYNUM() == 0)
        {
            throw std::runtime_error{"failed to init joypad"};
        }
    }
    initialize_sound_file();
    mainskill(0) = 173;
    mainskill(1) = 106;
    mainskill(2) = 108;

    DIM3(cycle, 15, 5);
    cycle(0, 0) = 1;
    cycle(1, 0) = 2;
    cycle(2, 0) = 5;
    cycle(3, 0) = 7;
    cycle(4, 0) = 8;
    cycle(5, 0) = 9;
    cycle(6, 0) = 14;
    cycle(7, 0) = 15;
    cycle(8, 0) = 17;
    cycle(9, 0) = 26;
    cycle(10, 0) = -1;
    cycle(0, 1) = 1;
    cycle(1, 1) = 5;
    cycle(2, 1) = 7;
    cycle(3, 1) = 8;
    cycle(4, 1) = 14;
    cycle(5, 1) = -1;
    cycle(0, 2) = 10;
    cycle(1, 2) = 25;
    cycle(2, 2) = -1;
    cycle(0, 3) = 22;
    cycle(1, 3) = 24;
    cycle(2, 3) = -1;
    cycle(0, 4) = 2;
    cycle(1, 4) = -1;

    cyclemax(0) = 9;
    cyclemax(1) = 4;
    cyclemax(2) = 1;
    cyclemax(3) = 1;
    cyclemax(4) = 0;

    lastctrl = 1;

    DIM2(invicon, 40);
    SDIM3(invkey, 4, 40);
    invkey(0) = "";
    invkey(1) = ""s + key_inventory;
    invkey(2) = ""s + key_drop;
    invkey(3) = "";
    invkey(4) = "";
    invkey(5) = ""s + key_eat;
    invkey(6) = "";
    invkey(7) = ""s + key_read;
    invkey(8) = ""s + key_drink;
    invkey(9) = ""s + key_zap;
    invkey(10) = "";
    invkey(11) = "";
    invkey(12) = "";
    invkey(13) = "";
    invkey(14) = ""s + key_use;
    invkey(15) = ""s + key_open;
    invkey(16) = "";
    invkey(17) = ""s + key_dip;
    invkey(26) = ""s + key_throw;
    invicon(0) = -1;
    invicon(1) = 7;
    invicon(2) = 8;
    invicon(3) = -1;
    invicon(4) = -1;
    invicon(5) = 2;
    invicon(6) = -1;
    invicon(7) = 3;
    invicon(8) = 0;
    invicon(9) = 1;
    invicon(10) = 17;
    invicon(11) = -1;
    invicon(12) = -1;
    invicon(13) = -1;
    invicon(14) = 5;
    invicon(15) = 4;
    invicon(16) = -1;
    invicon(17) = 6;
    invicon(18) = -1;
    invicon(19) = -1;
    invicon(20) = -1;
    invicon(21) = -1;
    invicon(22) = 17;
    invicon(23) = -1;
    invicon(24) = 17;
    invicon(25) = 17;
    invicon(26) = 18;
    invicon(27) = -1;
    invicon(28) = -1;
    invicon(29) = -1;

    if (g_config.autodisable_numlock())
    {
        snail::Input::instance().disable_numlock();
    }

    // Calculate console text size (requires font to be loaded)
    lua::lua->get_console().init_constants();
}



void initialize_debug_globals()
{
    for (int cnt = 0; cnt < 9; ++cnt)
    {
        game_data.ranks.at(cnt) = 5000;
    }
    game_data.version = 1220;
    game_data.next_inventory_serial_id = 1000;
    game_data.next_shelter_serial_id = 100;
    game_data.pc_x_in_world_map = 22;
    game_data.pc_y_in_world_map = 21;
    game_data.previous_map = -1;
    game_data.random_seed = 1 + rnd(2000000000);
    game_data.random_seed_offset = 0;
    game_data.current_map = static_cast<int>(mdata_t::MapId::north_tyris);
    game_data.current_dungeon_level = 0;
    game_data.entrance_type = 7;
    mapstartx = 22;
    mapstarty = 21;
    game_data.current_map = static_cast<int>(mdata_t::MapId::vernis);
    game_data.current_dungeon_level = 1;
    game_data.entrance_type = 7;
    mapstartx = 10;
    mapstarty = 23;
    initlv = 50;
    rc = 0;
    flt(100);
    chara_create(0, 84, -3, 0);
    initialize_pc_character();
    game_data.date.year = 517;
    game_data.date.month = 12;
    game_data.date.day = 30;
    game_data.date.hour = 1;
    game_data.date.minute = 10;
    game_data.played_scene = 50;
    game_data.has_not_been_to_vernis = 1;
    area_data[static_cast<int>(mdata_t::MapId::your_home)].outer_map =
        static_cast<int>(mdata_t::MapId::north_tyris);
    game_data.destination_outer_map =
        area_data[game_data.current_map].outer_map;
    game_data.acquirable_feat_count = 2;
    game_data.quest_flags.save_count_of_little_sister = 1000;
    game_data.rights_to_succeed_to = 1000;
    game_data.home_scale = 0;
    game_data.number_of_waiting_guests = 2;
    game_data.charge_power = 1000;
    cdata.player().god_id = core_god::int2godid(2);
    cdata.player().piety_point = 1000;
    cdata.player().praying_point = 1000;
    game_data.quest_flags.pael_and_her_mom = 1000;
    earn_gold(cdata.player(), 1000000);
    cdata.player().platinum_coin = 30;
    cdata.player().fame = 65000;
    game_data.quest_flags.main_quest = 100;
    chara_refresh(0);

    cdata.player().can_cast_rapid_magic() = true;
    mode = 0;
    refresh_burden_state();
    for (int cnt = 0; cnt < 55; ++cnt)
    {
        mat(cnt) = 200;
    }
    create_all_adventurers();
    create_pcpic(cdata.player());
    cdatan(1, 0) = random_title(RandomTitleType::character);
    cdatan(0, 0) = random_name();
}



void initialize_game()
{
    bool script_loaded = false;
    bool will_load_script = false;
    Autopick::instance().load(playerid);

    mtilefilecur = -1;
    firstturn = 1;
    Message::instance().buffered_message_begin("   Welcome traveler! ");

    if (mode == 5)
    {
        initialize_world();
        create_all_adventurers();
        mode = 2;
        event_add(24);
        event_add(2);
        sceneid = 0;
        do_play_scene();
    }
    if (mode == 6)
    {
        playerid = u8"sav_testbed"s;
        initialize_debug_globals();
        initialize_testbed();
        will_load_script = true;
        mode = 2;
    }
    if (mode == 2)
    {
        game_data.next_inventory_serial_id = 1000;
        game_data.next_shelter_serial_id = 100;
        initialize_recipememory();
    }
    if (mode == 3)
    {
        load_save_data();

        if (config_get_boolean("core.foobar.run_script_in_save"))
        {
            will_load_script = true;
        }
    }

    if (will_load_script && g_config.startup_script() != ""s)
    {
        lua::lua->get_mod_manager().run_startup_script(
            g_config.startup_script());
        script_loaded = true;
    }

    init_fovlist();
    initialize_map();

    if (script_loaded)
    {
        lua::lua->get_event_manager().trigger(
            lua::BaseEvent("core.script_loaded"));
    }
}



void init()
{
    const auto preinit_config_options = PreinitConfigOptions::from_file(
        filesystem::files::profile_local_config());

    initialize_screen(preinit_config_options);

    lua::lua = std::make_unique<lua::LuaEnv>();

    initialize_directories();

    initialize_lua();

    config_load_all_schema();
    config_load_options();

    // Load translations from scanned mods.
    initialize_i18n();

    lua::lua->get_api_manager().lock();

    if (g_config.font_filename().empty())
    {
        // If no font is specified in `config.json`, use a pre-defined font
        // depending on each language.
        g_config.set_font_filename(i18n::s.get("core.meta.default_font"));
        if (jp)
        {
            // TODO: work around
            elona::vfix = -3;
        }
    }

    initialize_keybindings();

    initialize_elona();

    config_save();

    // It is necessary to calculate PC's birth year correctly.
    game_data.date.year = 517;
    game_data.date.month = 8;
    game_data.date.day = 12;
    game_data.date.hour = 16;
    game_data.date.minute = 10;

    quickpage = 1;

    // TODO: Show each time mods are reloaded.
    show_loading_screen();
}

} // namespace elona

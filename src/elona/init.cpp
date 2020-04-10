#include "init.hpp"

#include "../util/fileutil.hpp"
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
#include "initialize_map.hpp"
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
#include "mapgen.hpp"
#include "mef.hpp"
#include "menu.hpp"
#include "quest.hpp"
#include "randomgen.hpp"
#include "save.hpp"
#include "scene.hpp"
#include "set_item_info.hpp"
#include "text.hpp"
#include "trait.hpp"
#include "ui.hpp"
#include "variables.hpp"
#include "world.hpp"



namespace elona
{

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



// see building.cpp
extern elona_vector1<int> fsetincome;
extern elona_vector1<int> fsetplantartifact;
extern elona_vector1<int> fsetplantunknown;

// see command.cpp
extern elona_vector1<int> fsetbarrel;
extern elona_vector1<int> isetgiftminor;
extern elona_vector1<int> isetgiftmajor;
extern elona_vector1<int> isetgiftgrand;

// see randomgen.cpp
extern elona_vector1<int> fsetrare;



void initialize_lua()
{
    // Load mods.
    lua::lua->load_mods();

    // Initialize "console" mod.
    lua::lua->get_console().init_environment();

    auto& api_manager = lua::lua->get_api_manager();
    api_manager.clear();
    api_manager.init_from_mods();

    auto& data_manager = lua::lua->get_data_manager();
    data_manager.clear();
    data_manager.init_from_mods();

    lua::lua->get_export_manager().register_all_exports();

    // Set "data" table on all loaded mod environments.
    data::initialize(data_manager.get());

    // Remove unknown event types from the event tables.
    lua::lua->get_event_manager().remove_unknown_events();

    // Run user/console.lua.
    lua::lua->get_console().run_userscript();
}



void initialize_i18n()
{
    i18n::s.init();
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
    // if (g_config.sound())
    {
        bool ok = audio_init_sound();
        if (!ok)
        {
            throw std::runtime_error{"failed to init sound"};
        }
    }
    if (g_config.music())
    {
        bool ok = audio_init_music();
        if (!ok)
        {
            throw std::runtime_error{"failed to init music"};
        }
    }
    if (g_config.joypad())
    {
        DIINIT();
        if (DIGETJOYNUM() == 0)
        {
            throw std::runtime_error{"failed to init joypad"};
        }
    }
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



void initialize_post_data()
{
    DIM4(pochart, 10, 10, 10);
    pochart(0, 0, 0) = 2;
    pochart(0, 1, 0) = 3;
    pochart(1, 1, 0) = 4;
    pochart(0, 2, 0) = 5;
    pochart(1, 2, 0) = 6;
    DIM3(podata, 300, 20);
}



void initialize_picfood()
{
    DIM3(picfood, 10, 9);
    picfood(0, 8) = 230;
    picfood(1, 8) = 230;
    picfood(2, 8) = 230;
    picfood(3, 8) = 190;
    picfood(4, 8) = 229;
    picfood(5, 8) = 190;
    picfood(6, 8) = 342;
    picfood(7, 8) = 168;
    picfood(8, 8) = 347;
    picfood(9, 8) = 194;
    picfood(0, 1) = 230;
    picfood(1, 1) = 230;
    picfood(2, 1) = 230;
    picfood(3, 1) = 195;
    picfood(4, 1) = 227;
    picfood(5, 1) = 167;
    picfood(6, 1) = 167;
    picfood(7, 1) = 194;
    picfood(8, 1) = 229;
    picfood(9, 1) = 227;
    picfood(0, 2) = 230;
    picfood(1, 2) = 230;
    picfood(2, 2) = 230;
    picfood(3, 2) = 229;
    picfood(4, 2) = 342;
    picfood(5, 2) = 194;
    picfood(6, 2) = 229;
    picfood(7, 2) = 342;
    picfood(8, 2) = 229;
    picfood(9, 2) = 194;
    picfood(0, 3) = 230;
    picfood(1, 3) = 230;
    picfood(2, 3) = 230;
    picfood(3, 3) = 229;
    picfood(4, 3) = 346;
    picfood(5, 3) = 346;
    picfood(6, 3) = 345;
    picfood(7, 3) = 345;
    picfood(8, 3) = 347;
    picfood(9, 3) = 346;
    picfood(0, 4) = 230;
    picfood(1, 4) = 230;
    picfood(2, 4) = 230;
    picfood(3, 4) = 108;
    picfood(4, 4) = 346;
    picfood(5, 4) = 110;
    picfood(6, 4) = 346;
    picfood(7, 4) = 347;
    picfood(8, 4) = 347;
    picfood(9, 4) = 347;
    picfood(0, 5) = 230;
    picfood(1, 5) = 230;
    picfood(2, 5) = 229;
    picfood(3, 5) = 343;
    picfood(4, 5) = 344;
    picfood(5, 5) = 344;
    picfood(6, 5) = 343;
    picfood(7, 5) = 343;
    picfood(8, 5) = 344;
    picfood(9, 5) = 343;
    picfood(0, 6) = 230;
    picfood(1, 6) = 230;
    picfood(2, 6) = 230;
    picfood(3, 6) = 228;
    picfood(4, 6) = 342;
    picfood(5, 6) = 342;
    picfood(6, 6) = 228;
    picfood(7, 6) = 341;
    picfood(8, 6) = 228;
    picfood(9, 6) = 228;
    picfood(0, 7) = 230;
    picfood(1, 7) = 230;
    picfood(2, 7) = 110;
    picfood(3, 7) = 108;
    picfood(4, 7) = 110;
    picfood(5, 7) = 112;
    picfood(6, 7) = 114;
    picfood(7, 7) = 113;
    picfood(8, 7) = 115;
    picfood(9, 7) = 111;
}



void initialize_set_of_random_generation()
{
    fsetincome(0) = 52000;
    fsetincome(1) = 52000;
    fsetincome(2) = 52000;
    fsetincome(3) = 53000;
    fsetincome(4) = 53000;
    fsetincome(5) = 56000;
    fsetincome(6) = 54000;
    fsetincome(7) = 77000;
    fsetincome(8) = 57000;
    fsetincome(9) = 57000;
    fsetchest(0) = 10000;
    fsetchest(1) = 24000;
    fsetchest(2) = 12000;
    fsetchest(3) = 16000;
    fsetchest(4) = 20000;
    fsetchest(5) = 19000;
    fsetchest(6) = 18000;
    fsetchest(7) = 22000;
    fsetchest(8) = 14000;
    fsetchest(9) = 32000;
    fsetchest(10) = 34000;
    fsetchest(11) = 54000;
    fsetchest(12) = 59000;
    fsetwear(0) = 10000;
    fsetwear(1) = 10000;
    fsetwear(2) = 24000;
    fsetwear(3) = 24000;
    fsetwear(4) = 25000;
    fsetwear(5) = 12000;
    fsetwear(6) = 16000;
    fsetwear(7) = 20000;
    fsetwear(8) = 19000;
    fsetwear(9) = 18000;
    fsetwear(10) = 22000;
    fsetwear(11) = 14000;
    fsetwear(12) = 32000;
    fsetwear(13) = 34000;
    fsetitem(0) = 52000;
    fsetitem(1) = 52000;
    fsetitem(2) = 53000;
    fsetitem(3) = 53000;
    fsetitem(4) = 56000;
    fsetitem(5) = 68000;
    fsetitem(6) = 54000;
    fsetitem(7) = 64000;
    fsetitem(8) = 59000;
    fsetitem(9) = 55000;
    fsetrewardsupply(0) = 52000;
    fsetrewardsupply(1) = 53000;
    fsetrewardsupply(2) = 56000;
    fsetrewardsupply(3) = 54000;
    fsetrewardsupply(4) = 57000;
    fsetrare(0) = 60000;
    fsetrare(1) = 72000;
    fsetrare(2) = 77000;
    fsetrare(3) = 55000;
    fsetrare(4) = 57000;
    fsetdeliver(0) = 60000;
    fsetdeliver(1) = 77000;
    fsetdeliver(2) = 54000;
    fsetdeliver(3) = 64000;
    fsetsupply(0) = 60000;
    fsetsupply(1) = 77000;
    fsetsupply(2) = 56000;
    fsetsupply(3) = 54000;
    fsetsupply(4) = 64000;
    fsetmagic(0) = 53000;
    fsetmagic(1) = 56000;
    fsetmagic(2) = 54000;
    fsetarmor(0) = 12000;
    fsetarmor(1) = 16000;
    fsetarmor(2) = 20000;
    fsetarmor(3) = 19000;
    fsetarmor(4) = 18000;
    fsetarmor(5) = 22000;
    fsetarmor(6) = 14000;
    fsetweapon(0) = 10000;
    fsetweapon(1) = 24000;
    fsetweapon(2) = 25000;
    fsetplantartifact(0) = 32000;
    fsetplantartifact(1) = 34000;
    fsetplantunknown(0) = 57000;
    fsetplantunknown(1) = 57000;
    fsetplantunknown(2) = 54000;
    fsetplantunknown(3) = 64000;
    fsetplantunknown(4) = 77000;
    fsetbarrel(0) = 25000;
    fsetbarrel(1) = 57000;
    fsetbarrel(2) = 53000;
    fsetbarrel(3) = 52000;
    fsetbarrel(4) = 77000;
    fsetbarrel(5) = 64000;
    fsetcollect(0) = 64000;
    fsetcollect(1) = 60000;
    fsetcollect(2) = 57000;
    fsetcollect(3) = 77000;
    isetfruit(0) = 180;
    isetfruit(1) = 181;
    isetfruit(2) = 196;
    isetfruit(3) = 197;
    isetfruit(4) = 192;
    isetfruit(5) = 183;
    isetthrowpotionminor(0) = 27;
    isetthrowpotionminor(1) = 28;
    isetthrowpotionminor(2) = 376;
    isetthrowpotionminor(3) = 30;
    isetthrowpotionminor(4) = 262;
    isetthrowpotionminor(5) = 253;
    isetthrowpotionminor(6) = 379;
    isetthrowpotionminor(7) = 392;
    isetthrowpotionmajor(0) = 28;
    isetthrowpotionmajor(1) = 376;
    isetthrowpotionmajor(2) = 205;
    isetthrowpotionmajor(3) = 368;
    isetthrowpotionmajor(4) = 433;
    isetthrowpotionmajor(5) = 382;
    isetthrowpotionmajor(6) = 577;
    isetthrowpotionmajor(7) = 577;
    isetthrowpotiongreater(0) = 28;
    isetthrowpotiongreater(1) = 205;
    isetthrowpotiongreater(2) = 368;
    isetthrowpotiongreater(3) = 432;
    isetthrowpotiongreater(4) = 429;
    isetthrowpotiongreater(5) = 29;
    isetthrowpotiongreater(6) = 577;
    isethire(0) = 205;
    isethire(1) = 70;
    isethire(2) = 74;
    isethire(3) = 41;
    isethire(4) = 69;
    isethire(5) = 76;
    isethire(6) = 1;
    isethire(7) = 1;
    isethire(8) = 1;
    isetgiftminor(0) = 753;
    isetgiftminor(1) = 754;
    isetgiftminor(2) = 754;
    isetgiftminor(3) = 756;
    isetgiftminor(4) = 756;
    isetgiftminor(5) = 540;
    isetgiftminor(6) = 541;
    isetgiftminor(7) = 537;
    isetgiftminor(8) = 538;
    isetgiftminor(9) = 526;
    isetgiftminor(10) = 415;
    isetgiftminor(11) = 511;
    isetgiftminor(12) = 343;
    isetgiftminor(13) = 340;
    isetgiftminor(14) = 338;
    isetgiftminor(15) = 328;
    isetgiftminor(16) = 220;
    isetgiftminor(17) = 575;
    isetgiftminor(18) = 622;
    isetgiftminor(19) = 167;
    isetgiftmajor(0) = 755;
    isetgiftmajor(1) = 755;
    isetgiftmajor(2) = 633;
    isetgiftmajor(3) = 626;
    isetgiftmajor(4) = 502;
    isetgiftmajor(5) = 632;
    isetgiftmajor(6) = 667;
    isetgiftmajor(7) = 555;
    isetgiftmajor(8) = 748;
    isetgiftmajor(9) = 640;
    isetgiftgrand(0) = 757;
    isetgiftgrand(1) = 558;
    isetgiftgrand(2) = 664;
    isetgiftgrand(3) = 758;
    isetgiftgrand(4) = 759;
    isetgiftgrand(5) = 761;
    isethirerole(0) = 18;
    isethirerole(1) = 9;
    isethirerole(2) = 12;
    isethirerole(3) = 5;
    isethirerole(4) = 8;
    isethirerole(5) = 14;
    isethirerole(6) = 1008;
    isethirerole(7) = 1008;
    isethirerole(8) = 1008;
    isetcrop(0) = 180;
    isetcrop(1) = 181;
    isetcrop(2) = 197;
    isetcrop(3) = 192;
    isetcrop(4) = 183;
    isetcrop(5) = 188;
    isetcrop(6) = 200;
    isetgod(0) = 0;
    isetgod(1) = 1;
    isetgod(2) = 2;
    isetgod(3) = 3;
    isetgod(4) = 4;
    isetgod(5) = 5;
    isetgod(6) = 6;
    isetgod(7) = 7;
    asettown(0) = 5;
    asettown(1) = 11;
    asettown(2) = 14;
    asettown(3) = 15;
    asettown(4) = 12;
    moneybox(0) = 500;
    moneybox(1) = 2000;
    moneybox(2) = 10000;
    moneybox(3) = 50000;
    moneybox(4) = 500000;
    moneybox(5) = 5000000;
    moneybox(6) = 100000000;
    giftvalue(0) = 10;
    giftvalue(1) = 20;
    giftvalue(2) = 30;
    giftvalue(3) = 50;
    giftvalue(4) = 75;
    giftvalue(5) = 100;

    bool in_booktitle_definition = false;
    int isetbook_index = 0;
    for (const auto& line : fileutil::read_by_line(lua::resolve_path_for_mod(
             "<core>/locale/<LANGUAGE>/lazy/book.txt")))
    {
        if (line == u8"%DEFINE")
        {
            in_booktitle_definition = true;
        }
        else if (line == u8"%END")
        {
            break;
        }
        else if (in_booktitle_definition)
        {
            // E.g., 7,Book Title,T
            const auto columns = strutil::split(line, ',');
            const auto id = elona::stoi(columns.at(0));
            const auto& title = columns.at(1);
            const auto is_generated = columns.at(2) == "T";

            booktitle(id) = title;
            if (is_generated)
            {
                isetbook(isetbook_index) = id;
                ++isetbook_index;
            }
        }
    }
}



void finish_elona()
{
    if (g_config.autodisable_numlock())
    {
        snail::Input::instance().restore_numlock();
    }
}

} // namespace elona

#include "testing.hpp"
#include <sstream>
#include "config.hpp"
#include "db_item.hpp"
#include "db_music.hpp"
#include "db_sound.hpp"
#include "draw.hpp"
#include "gdata.hpp"
#include "i18n.hpp"
#include "init.hpp"
#include "log.hpp"
#include "lua_env/lua_env.hpp"
#include "variables.hpp"
#include "version.hpp"

namespace elona
{
namespace testing
{

const std::string save_dir = "tests/data/save";
const std::string player_id = "sav_testbed";

fs::path get_test_data_path()
{
    return filesystem::dir::exe() / "tests" / "data";
}

fs::path get_mods_path()
{
    return get_test_data_path() / "mods";
}

void load_previous_savefile()
{
    elona::testing::reset_state();
    // This file was saved directly after the dialog at the start of the game.
    elona::playerid = "sav_foobar_test";
    filesystem::dir::set_base_save_directory(filesystem::path(save_dir));
    load_save_data();
    elona::firstturn = 1;
    elona::mode =
        3; // begin the game as if it were loaded from a save; load inv_xxx.s2
    initialize_map();
}

void save_and_reload()
{
    filesystem::dir::set_base_save_directory(filesystem::path(save_dir));
    save_game();
    elona::testing::reset_state();
    elona::firstturn = 1;
    load_save_data();
}

void start_in_map(int map, int level)
{
    filesystem::dir::set_base_save_directory(filesystem::path(save_dir));

    lua::lua->clear();
    initialize_debug_globals();

    elona::playerid = player_id;
    fs::remove_all(filesystem::dir::save(player_id));

    gdata_current_map = map; // Debug map
    gdata_current_dungeon_level = level;
    init_fovlist();
    initialize_map();
}

void start_in_debug_map()
{
    start_in_map(9999, 2);
}

void run_in_temporary_map(int map, int level, std::function<void()> f)
{
    gdata_previous_map2 = gdata_current_map;
    gdata_previous_dungeon_level = gdata_current_dungeon_level;
    gdata_previous_x = cdata.player().position.x;
    gdata_previous_y = cdata.player().position.y;
    gdata_destination_map = map;
    gdata_destination_dungeon_level = level;
    levelexitby = 2;
    exit_map();

    f();

    levelexitby = 4;
    exit_map();
}

void load_translations(const std::string& hcl)
{
    i18n::s.clear();

    std::stringstream ss(hcl);
    i18n::s.load(ss, "test.hcl", "test");
}

void configure_lua()
{
    lua::lua.reset(new lua::lua_env());
    lua::lua->get_mod_manager().load_mods(filesystem::dir::mods());

    sol::table Testing = lua::lua->get_state()->create_named_table("Testing");
    Testing.set_function("start_in_debug_map", start_in_debug_map);
    Testing.set_function("reset_state", reset_state);
    Testing.set_function("load_translations", load_translations);
}

void pre_init()
{
    log::initialize();

    const fs::path config_def_file =
        filesystem::dir::mods() / u8"core"s / u8"config"s / u8"config_def.hcl"s;
    const fs::path config_file =
        filesystem::dir::exe() / "tests/data/config.hcl";

    config::instance().init(config_def_file);
    initialize_config_preload(config_file);

    title(u8"Elona Foobar version "s + latest_version.short_string());

    init_assets();
    filesystem::dir::set_base_save_directory(fs::path("save"));
    initialize_config(config_file);

    initialize_cat_db();
    configure_lua();
    initialize_i18n();
    initialize_lion_db();

    initialize_elona();

    config::instance().is_test = true;

    lua::lua->get_event_manager()
        .run_callbacks<lua::EventKind::game_initialized>();
}

void post_run()
{
    filesystem::dir::set_base_save_directory(filesystem::path(save_dir));
    fs::remove_all(filesystem::dir::save(player_id));
    finish_elona();
}

void reset_state()
{
    lua::lua->clear();
    configure_lua();
    initialize_i18n();
    initialize_elona();

    // reset translations
    elona::jp = 1;
    elona::en = 0;
    set_item_info();

    config::instance().is_test = true;

    lua::lua->get_event_manager()
        .run_callbacks<lua::EventKind::game_initialized>();
}

} // namespace testing
} // namespace elona

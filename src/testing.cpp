#include "testing.hpp"
#include <sstream>
#include "config.hpp"
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

const fs::path save_dir("tests/data/save");
const std::string player_id = "sav_testbed";

void load_previous_savefile()
{
    elona::testing::reset_state();
    // This file was saved directly after the dialog at the start of the game.
    elona::playerid = "sav_foobar_test";
    load_save_data(save_dir);
    elona::firstturn = 1;
    elona::mode =
        3; // begin the game as if it were loaded from a save; load inv_xxx.s2
    initialize_map();
}

void save_and_reload()
{
    save_game(save_dir);
    elona::testing::reset_state();
    elona::firstturn = 1;
    load_save_data(save_dir);
}

void start_in_map(int map, int level)
{
    reset_state();
    initialize_debug_globals();

    elona::playerid = player_id;
    fs::remove_all(save_dir / elona::playerid);

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
    gdata_previous_x = cdata[0].position.x;
    gdata_previous_y = cdata[0].position.y;
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
    i18n::s.load(ss, "test.hcl");
}

void configure_lua()
{
    sol::table Testing = lua::lua->get_state()->create_named_table("Testing");
    Testing.set_function("start_in_debug_map", start_in_debug_map);
    Testing.set_function("reset_state", reset_state);
    Testing.set_function("load_translations", load_translations);
}

void pre_init()
{
    lua::lua = std::make_unique<lua::lua_env>();
    log::initialize();

    initialize_cat_db();
    configure_lua();

    load_config2(fs::path("tests/data/config.json"));

    title(u8"Elona Foobar version "s + latest_version.short_string());

    init_assets();
    initialize_config(fs::path("tests/data/config.json"));

    config::instance().is_test = true;

    lua::lua->scan_all_mods(filesystem::dir::mods());
    lua::lua->load_core_mod(filesystem::dir::mods());
    configure_lua();
}

void post_run()
{
    fs::remove_all(save_dir / player_id);
    finish_elona();
}

void reset_state()
{
    config::instance().is_test = true;
    lua::lua->reload();
    configure_lua();
    initialize_elona();

    // reset translations
    elona::jp = 1;
    elona::en = 0;
    set_item_info();
}

} // namespace testing
} // namespace elona

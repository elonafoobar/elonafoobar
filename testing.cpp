#include "testing.hpp"
#include "config.hpp"
#include "gdata.hpp"
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
    elona::mode = 3; // begin the game as if it were loaded from a save; load inv_xxx.s2
    initialize_map();
}

void save_and_reload()
{
    save_game(save_dir);
    elona::testing::reset_state();
    elona::firstturn = 1;
    load_save_data(save_dir);
}

void start_in_debug_map()
{
    reset_state();
    initialize_debug_globals();

    elona::playerid = player_id;
    elona_delete(save_dir / elona::playerid);

    gdata_current_map = 9999; // Debug map
    gdata_current_dungeon_level = 2;
    init_fovlist();
    initialize_map();
}

void configure_lua()
{
    sol::table Testing = lua::lua.get_state()->create_named_table("Testing");
    Testing.set_function("start_in_debug_map", start_in_debug_map);
    Testing.set_function("reset_state", reset_state);
}

void pre_init()
{
    log::initialize();

    initialize_cat_db();
    configure_lua();

    foobar_save.initialize();

    load_config2(fs::path("tests/data/config.json"));

    title(u8"Elona Foobar version "s + latest_version.short_string());

    initialize_config(fs::path("tests/data/config.json"));

    config::instance().is_test = true;

    configure_lua();
}

void post_run()
{
    elona_delete(save_dir / player_id);
    finish_elona();
}

void reset_state()
{
    config::instance().is_test = true;
    lua::lua.reload();
    configure_lua();
    initialize_elona();

    // reset translations
    elona::jp = 1;
    elona::en = 0;
    set_item_info();
}

} // namespace testing
} // namespace elona

#include "testing.hpp"

#include <sstream>

#include "character.hpp"
#include "config.hpp"
#include "ctrl_file.hpp"
#include "data/types/type_item.hpp"
#include "data/types/type_music.hpp"
#include "data/types/type_sound.hpp"
#include "draw.hpp"
#include "game.hpp"
#include "i18n.hpp"
#include "init.hpp"
#include "initialize_map.hpp"
#include "log.hpp"
#include "lua_env/event_manager.hpp"
#include "lua_env/lua_env.hpp"
#include "lua_env/lua_event/base_event.hpp"
#include "map.hpp"
#include "profile/profile_manager.hpp"
#include "save.hpp"
#include "save_fs.hpp"
#include "set_item_info.hpp"
#include "variables.hpp"
#include "version.hpp"



namespace elona
{
namespace testing
{

const std::string save_dir = "tests/data/save";
const std::string player_id = "sav_testbed";

void reset_state();

fs::path get_test_data_path()
{
    return filesystem::dirs::exe() / "tests" / "data";
}

fs::path get_mods_path()
{
    return get_test_data_path() / "mods";
}

void load_previous_savefile()
{
    testing::reset_state();
    // This file was saved directly after the dialog at the start of the game.
    elona::playerid = "sav_foobar_test";
    filesystem::dirs::set_base_save_directory(filesystem::path(save_dir));
    save_load_game();
    elona::firstturn = 1;
    elona::mode =
        3; // begin the game as if it were loaded from a save; load inv_xxx.s2
    initialize_map();
}

void save_reset_and_reload()
{
    testing::save();
    testing::reset_state();
    testing::load();
}

void save_and_reload()
{
    testing::save();
    testing::load();
}

void save()
{
    filesystem::dirs::set_base_save_directory(filesystem::path(save_dir));
    save_save_game(save_game_no_message, save_game_silent);
}

void load()
{
    elona::firstturn = 1;
    save_load_game();
    elona::mode = 3;
    initialize_map();
}

void load_translations(const std::string& locale_file_content)
{
    i18n::s.load_from_string(locale_file_content, "test");
}

// Similar to load_translations, but does not reset all i18n resources.
void reinit_core_and_load_translations(const std::string& locale_file_content)
{
    initialize_i18n();

    i18n::s.load_from_string(locale_file_content, "test");
}

void configure_lua()
{
    lua::lua.reset(new lua::LuaEnv());
    initialize_lua();

    sol::table Testing = lua::lua->get_state()->create_named_table("Testing");
    Testing.set_function("start_in_debug_map", start_in_debug_map);
    Testing.set_function("reset_state", reset_state);
    Testing.set_function("load_translations", load_translations);
    Testing.set_function(
        "reinit_core_and_load_translations", reinit_core_and_load_translations);

    config_load_all_schema();
    config_load_options();
}

void start_in_map(int map, int level)
{
    filesystem::dirs::set_base_save_directory(filesystem::path(save_dir));

    lua::lua->clear();
    initialize_debug_globals();

    elona::playerid = player_id;
    fs::remove_all(filesystem::dirs::save(player_id));
    fs::remove_all(filesystem::dirs::tmp());
    fs::create_directory(filesystem::dirs::tmp());
    save_fs_clear();

    game()->current_map = map;
    game()->current_dungeon_level = level;
    init_fovlist();
    elona::mode = 2;
    initialize_map();

    save_save_game(save_game_no_message, save_game_silent);
}

void start_in_debug_map()
{
    start_in_map(499, 2);
}

void run_in_temporary_map(int map, int dungeon_level, std::function<void()> f)
{
    auto previous_map = game()->current_map;
    auto previous_dungeon_level = game()->current_dungeon_level;
    auto previous_x = cdata.player().position.x;
    auto previous_y = cdata.player().position.y;
    game()->destination_map = map;
    game()->destination_dungeon_level = dungeon_level;
    elona::levelexitby = 2;
    exit_map();
    initialize_map();

    f();

    elona::mapstartx = previous_x;
    elona::mapstarty = previous_y;
    game()->destination_map = previous_map;
    game()->destination_dungeon_level = previous_dungeon_level;
    elona::levelexitby = 2;
    exit_map();
    initialize_map();
}

void pre_init()
{
    log::init(filesystem::dirs::log(), log::LogLevel::debug);
    profile::ProfileManager::instance().init(u8"testing");

    const fs::path source_config_file = get_test_data_path() / "config.json";
    const fs::path config_file = filesystem::files::profile_local_config();
    fs::copy_file(
        source_config_file, config_file, fs::copy_option::overwrite_if_exists);

    (void)PreinitConfigOptions::from_file(config_file);

    title(u8"Elona foobar version "s + latest_version.short_string());

    init_assets();
    filesystem::dirs::set_base_save_directory(fs::path("save"));

    configure_lua();

    initialize_i18n();

    if (!fs::exists(filesystem::dirs::tmp()))
    {
        fs::create_directory(filesystem::dirs::tmp());
    }
    initialize_elona();

    g_config.set_is_test(true);

    lua::lua->get_event_manager().trigger(
        lua::BaseEvent("core.game_initialized"));
}

void post_run()
{
    filesystem::dirs::set_base_save_directory(filesystem::path(save_dir));
    fs::remove_all(filesystem::dirs::save(player_id));
    fs::remove_all(filesystem::dirs::tmp());
    save_fs_clear();
    fs::create_directory(filesystem::dirs::tmp());
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

    g_config.set_is_test(true);

    lua::lua->get_event_manager().trigger(
        lua::BaseEvent("core.game_initialized"));
}

} // namespace testing
} // namespace elona

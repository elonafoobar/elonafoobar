#include "main.hpp"
#include "../util/tinyargparser.hpp"
#include "config.hpp"
#include "init.hpp"
#include "lua_env/event_manager.hpp"
#include "lua_env/lua_event/base_event.hpp"
#include "main_menu.hpp"
#include "profile/profile_manager.hpp"
#include "turn_sequence.hpp"
#include "variables.hpp"

using namespace elona;



namespace
{

tinyargparser::ArgParser _make_argparser()
{
    return tinyargparser::ArgParser("Elona foobar")
        .add('v', "version", "Show version.")
        .add('p', "profile", "Specify profile.");
}



void _main_loop()
{
    lua::lua->get_event_manager().trigger(
        lua::BaseEvent("core.game_initialized"));

    while (true)
    {
        bool finished = turn_wrapper();
        if (finished)
        {
            break;
        }
    }
}



void _start_elona()
{
    if (g_config.startup_script() != ""s &&
        !config_get_boolean("core.foobar.run_script_in_save"))
    {
        mode = 6;
        initialize_game();
        _main_loop();
        return;
    }
    else if (defload != ""s)
    {
        if (!fs::exists(filesystem::dirs::save(defload) / u8"header.txt"))
        {
            if (fs::exists(
                    filesystem::dirs::save(u8"sav_" + defload) /
                    u8"header.txt"))
            {
                // TODO: Delete it when v1.0.0 stable is released.
                defload = u8"sav_"s + defload;
            }
            else
            {
                defload = "";
            }
        }
        if (defload == ""s)
        {
            dialog(u8"Invalid defLoadFolder. name"s);
        }
        else
        {
            playerid = defload;
            mode = 3;
            initialize_game();
            _main_loop();
            return;
        }
    }

    const auto start = main_menu_loop();
    if (start)
    {
        initialize_game();
        _main_loop();
    }
}

} // namespace



namespace elona
{

int run(int argc, const char* const* argv)
{
    const auto parser = _make_argparser();
    const auto args = parser.parse(argc, argv);

    if (args.has("help"))
    {
        std::cout << parser.help() << std::endl;
        return 0;
    }
    if (args.has("version"))
    {
        std::cout << "Elona foobar v" << latest_version.short_string()
                  << std::endl;
        return 0;
    }
    const auto profile = args.get_or("profile", profile::default_profile_id);
    profile::ProfileManager::instance().init(profile);

    init();
    _start_elona();

    return 0;
}

} // namespace elona

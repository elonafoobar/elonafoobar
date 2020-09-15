#include "main.hpp"

#include "../util/tinyargparser.hpp"
#include "../version.hpp"
#include "config.hpp"
#include "init.hpp"
#include "lua_env/event_manager.hpp"
#include "lua_env/lua_event/base_event.hpp"
#include "main_menu.hpp"
#include "profile/profile_manager.hpp"
#include "save_header.hpp"
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
        !config_get<bool>("core.foobar.run_script_in_save"))
    {
        mode = 6;
        initialize_game();
        _main_loop();
        return;
    }

    auto default_save = config_get<std::string>("core.game.default_save");
    if (!default_save.empty())
    {
        if (fs::exists(filesystem::dirs::save(default_save)))
        {
            playerid = default_save;
            mode = 3;
            initialize_game();
            _main_loop();
            return;
        }
        else if (fs::exists(filesystem::dirs::save(u8"save_" + default_save)))
        {
            playerid = u8"save_"s + default_save;
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

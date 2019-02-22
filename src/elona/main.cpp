#include "main.hpp"
#include "config/config.hpp"
#include "init.hpp"
#include "lua_env/event_manager.hpp"
#include "main_menu.hpp"
#include "turn_sequence.hpp"
#include "variables.hpp"

using namespace elona;



namespace
{

void main_loop()
{
    lua::lua->get_event_manager()
        .run_callbacks<lua::EventKind::game_initialized>();

    while (true)
    {
        bool finished = turn_wrapper();
        if (finished)
        {
            break;
        }
    }
}



void start_elona()
{
    if (Config::instance().startup_script != ""s &&
        !Config::instance().get<bool>("core.config.foobar.run_script_in_save"))
    {
        mode = 6;
        initialize_game();
        main_loop();
        return;
    }
    else if (defload != ""s)
    {
        if (!fs::exists(filesystem::dir::save(defload) / u8"header.txt"))
        {
            if (fs::exists(
                    filesystem::dir::save(u8"sav_" + defload) / u8"header.txt"))
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
            main_loop();
            return;
        }
    }

    const auto start = main_menu_loop();
    if (start)
    {
        initialize_game();
        main_loop();
    }
}

} // namespace



namespace elona
{

int run()
{
    init();
    start_elona();

    return 0;
}

} // namespace elona

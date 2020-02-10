#include "main.hpp"
#include "../snail/filedialog.hpp"
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



bool install_if_needed()
{
    if (fs::exists(filesystem::dirs::graphic() / "deco_blend.bmp"))
    {
        return true;
    }

    snail::OpenFolderDialog ofd{filesystem::dirs::exe().parent_path()};
    const auto result = ofd.show();
    switch (result.type)
    {
    case snail::FileDialogResultType::error: return false;
    case snail::FileDialogResultType::okay: break;
    case snail::FileDialogResultType::cancel: return false;
    default: assert(0); break;
    }

    const auto& vanilla_path = result.filepath;
    if (!fs::exists(vanilla_path / "elona.exe")) // is the folder elona?
    {
        return false;
    }

    // This image file exists only in Elona 1.22 or variants.
    // This condition can verify whether this elona folder is 1.22, not 1.16.
    if (!fs::exists(vanilla_path / "graphic" / "deco_blend.bmp"))
    {
        return false;
    }

    for (const auto& folder_name : {"graphic", "sound"})
    {
        const auto source = vanilla_path / folder_name;
        const auto destination = filesystem::dirs::exe() / folder_name;
        if (!fs::exists(destination))
        {
            if (!fs::create_directories(destination))
            {
                throw std::runtime_error{
                    "Failed to create directory: " +
                    filepathutil::make_preferred_path_in_utf8(destination)};
            }
        }
        for (const auto& entry : fs::directory_iterator{source})
        {
            const auto from = entry.path();
            const auto to = destination / from.filename();
            if (fs::is_regular_file(from))
            {
                fs::copy_file(from, to, fs::copy_option::overwrite_if_exists);
            }
        }
    }

    return true;
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

    if (!install_if_needed())
    {
        return -1;
    }

    init();
    _start_elona();

    return 0;
}

} // namespace elona

#include "filesystem.hpp"

#include "../util/strutil.hpp"
#include "config.hpp"
#include "defines.hpp"
#include "semver.hpp"



namespace
{

fs::path get_executable_dir()
{
    static auto cache = ([] {
        auto exe_name = fs::get_executable_path();
        if (!exe_name)
        {
            throw std::runtime_error("Error: fail to get excutable path");
        }
        return fs::canonical(exe_name->remove_filename());
    })();

    return cache;
}

} // namespace



namespace elona
{
namespace filesystem
{

namespace dirs
{

fs::path current_profile_dir;
fs::path base_mod_dir;
fs::path base_save_dir;
fs::path base_user_dir;


#define ELONA_DEFINE_PREDEFINED_DIR(func_name, path_name) \
    fs::path func_name() \
    { \
        return filesystem::path(path_name); \
    }

ELONA_DEFINE_PREDEFINED_DIR(exe, "")
ELONA_DEFINE_PREDEFINED_DIR(data, "data")
ELONA_DEFINE_PREDEFINED_DIR(font, "data/font")
ELONA_DEFINE_PREDEFINED_DIR(graphic, "graphic")
ELONA_DEFINE_PREDEFINED_DIR(locale, "locale")
ELONA_DEFINE_PREDEFINED_DIR(log, "log")
ELONA_DEFINE_PREDEFINED_DIR(map, "map")
ELONA_DEFINE_PREDEFINED_DIR(sound, "sound")
ELONA_DEFINE_PREDEFINED_DIR(tmp, "tmp")
ELONA_DEFINE_PREDEFINED_DIR(mod, "mod")
ELONA_DEFINE_PREDEFINED_DIR(profile_root, "profile")

#undef ELONA_DEFINE_PREDEFINED_DIR



fs::path current_profile()
{
    return current_profile_dir;
}



fs::path save()
{
    return base_save_dir;
}



fs::path screenshot()
{
    return current_profile() / "screenshot";
}



fs::path user()
{
    return base_user_dir;
}



void set_current_profile_directory(const fs::path& current_profile_dir)
{
    dirs::current_profile_dir = current_profile_dir;
}



void set_base_save_directory(const fs::path& base_save_dir)
{
    dirs::base_save_dir = base_save_dir;
}



void set_base_user_directory(const fs::path& base_user_dir)
{
    dirs::base_user_dir = base_user_dir;
}



fs::path for_mod(const std::string& id, const semver::Version& version)
{
    return mod() / fs::u8path(id + "-" + version.to_string());
}



fs::path save(const std::string& player_id)
{
    return save() / fs::u8path(player_id);
}



fs::path user_script()
{
    return current_profile() / "script";
}



void set_profile_directory(const fs::path& profile_dir)
{
    set_current_profile_directory(profile_dir);
    set_base_save_directory(profile_dir / "save");
    set_base_user_directory(profile_dir / "user");
}

} // namespace dirs



namespace files
{

fs::path profile_local_config()
{
    return dirs::current_profile() / "config.json";
}



fs::path keybinding_config()
{
    return path("keybindings.json");
}



fs::path mod_list()
{
    return dirs::current_profile() / "mods.json";
}

} // namespace files



fs::path path(const std::string& str)
{
    return get_executable_dir() / fs::u8path(str);
}

} // namespace filesystem
} // namespace elona

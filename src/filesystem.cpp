#include "filesystem.hpp"
#include <boost/locale.hpp>
#include "defines.hpp"
#include "util.hpp"
#include <algorithm>

// For get_executable_path()
#if defined(ELONA_OS_WINDOWS)
#include <windows.h> // GetModuleFileName
#elif defined(ELONA_OS_MACOS)
#include <limits.h> // PATH_MAX
#include <mach-o/dyld.h> // _NSGetExecutablePath
#elif defined(ELONA_OS_LINUX)
#include <limits.h> // PATH_MAX
#include <unistd.h> // readlink
#else
#error Unsupported OS
#endif



namespace
{


fs::path get_executable_path()
{
    static auto cache = ([] {
#if defined(ELONA_OS_WINDOWS)
        TCHAR buf[1024 + 1];
        size_t buf_size = sizeof(buf);
        if (GetModuleFileName(nullptr, buf, buf_size) == 0)
        {
            throw std::runtime_error(u8"Error: fail to get excutable path");
        }
#elif defined(ELONA_OS_MACOS)
        char buf[PATH_MAX + 1];
        uint32_t buf_size = sizeof(buf);
        if (_NSGetExecutablePath(buf, &buf_size) != 0)
        {
            throw std::runtime_error(u8"Error: fail to get excutable path");
        }
#elif defined(ELONA_OS_LINUX)
        char buf[PATH_MAX + 1];
        size_t buf_size = sizeof(buf);
        if (readlink("/proc/self/exe", buf, buf_size) == -1)
        {
            throw std::runtime_error(u8"Error: fail to get excutable path");
        }
#else
#error Unsupported OS
#endif
        return fs::canonical(fs::path{buf}.remove_filename());
    })();

    return cache;
}


} // namespace



namespace elona
{
namespace filesystem
{


namespace dir
{


#define ELONA_DEFINE_PREDEFINED_DIR(func_name, path_name) \
    fs::path func_name() \
    { \
        return filesystem::path(path_name); \
    }

ELONA_DEFINE_PREDEFINED_DIR(exe, "")
ELONA_DEFINE_PREDEFINED_DIR(data, "data")
ELONA_DEFINE_PREDEFINED_DIR(graphic, "graphic")
ELONA_DEFINE_PREDEFINED_DIR(locale, "locale")
ELONA_DEFINE_PREDEFINED_DIR(map, "map")
ELONA_DEFINE_PREDEFINED_DIR(mods, "mods")
ELONA_DEFINE_PREDEFINED_DIR(save, "save")
ELONA_DEFINE_PREDEFINED_DIR(sound, "sound")
ELONA_DEFINE_PREDEFINED_DIR(tmp, "tmp")
ELONA_DEFINE_PREDEFINED_DIR(user, "user")

#undef ELONA_DEFINE_PREDEFINED_DIR


fs::path save(const std::string& player_id)
{
    return save() / u8path(player_id);
}


} // namespace dir



fs::path path(const std::string& str)
{
    return get_executable_path() / u8path(str);
}



fs::path u8path(const std::string& str)
{
    return boost::locale::conv::utf_to_utf<fs::path::string_type::value_type>(
        str);
}



std::string make_preferred_path_in_utf8(const fs::path& path)
{
    // Since make_preferred() modifies this and `path` is const, need to copy
    // it.
    auto path_ = path;
    return boost::locale::conv::utf_to_utf<char>(
        path_.make_preferred().native());
}



std::string to_utf8_path(const fs::path& path)
{
    return boost::locale::conv::utf_to_utf<char>(path.native());
}


std::string to_forward_slashes(const fs::path& path)
{
    std::string path_str = path.string();
    std::replace(path_str.begin(), path_str.end(), '\\', '/');
    return path_str;
}


} // namespace filesystem
} // namespace elona

#include "filesystem.hpp"
#include <boost/locale.hpp>
#include "defines.hpp"

#if defined(ELONA_OS_WINDOWS)
// For WideCharToMultiByte().
#include <windows.h>
#define USE_UTF16_AS_FILEPATH 1
#else
#define USE_UTF16_AS_FILEPATH 0
#endif

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

#include <iostream>

namespace
{


#if USE_UTF16_AS_FILEPATH
int get_needed_buffer_size(const wchar_t* str)
{
    return WideCharToMultiByte(CP_THREAD_ACP, 0, str, -1, NULL, 0, NULL, NULL);
}


int utf16_to_ansi(const wchar_t* from, char* to, int buffer_size)
{
    return WideCharToMultiByte(
        CP_THREAD_ACP, 0, from, -1, to, buffer_size, NULL, NULL);
}
#endif



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
ELONA_DEFINE_PREDEFINED_DIR(map, "map")
ELONA_DEFINE_PREDEFINED_DIR(save, "save")
ELONA_DEFINE_PREDEFINED_DIR(sound, "sound")
ELONA_DEFINE_PREDEFINED_DIR(tmp, "tmp")
ELONA_DEFINE_PREDEFINED_DIR(user, "user")

#undef ELONA_DEFINE_PREDEFINED_DIR


fs::path save(const std::string& player_id)
{
#if USE_UTF16_AS_FILEPATH
    return save() / boost::locale::conv::utf_to_utf<wchar_t>(player_id);
#else
    return save() / player_id;
#endif
}


} // namespace dir



fs::path path(const std::string& str)
{
    return get_executable_path() / str;
}


std::string make_preferred_path_in_utf8(const fs::path& path)
{
    // Since make_preferred() modifies this and `path` is const, need to copy
    // it.
    auto path_ = path;
    return boost::locale::conv::utf_to_utf<char>(
        path_.make_preferred().native());
}


std::string to_narrow_path(const fs::path& path)
{
#if USE_UTF16_AS_FILEPATH
    const auto wide_c_str = path.native().c_str();

    int needed_length = get_needed_buffer_size(wide_c_str);
    if (needed_length == 0)
        throw std::runtime_error(u8"Error: in to_narrow_path()");
    auto buffer = std::make_unique<char[]>(needed_length);
    int used_length = utf16_to_ansi(wide_c_str, buffer.get(), needed_length);
    if (used_length == 0)
        throw std::runtime_error(u8"Error: in to_narrow_path()");

    return std::string{buffer.get()};
#else
    return path.native();
#endif
}


std::string to_utf8_path(const fs::path& path)
{
    return boost::locale::conv::utf_to_utf<char>(path.native());
}



} // namespace filesystem
} // namespace elona

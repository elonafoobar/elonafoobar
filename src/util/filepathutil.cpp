#include "filepathutil.hpp"
#include <algorithm>
#include <boost/locale.hpp>
#include <boost/predef.h>

// For get_executable_path()
#if BOOST_OS_WINDOWS
#include <shlobj_core.h> // SHGetFolderPathW
#include <windows.h> // GetModuleFileName
#elif BOOST_OS_MACOS
#include <limits.h> // PATH_MAX
#include <mach-o/dyld.h> // _NSGetExecutablePath
#include <pwd.h> // getpwuid
#include <stdlib.h> // getenv
#include <sys/types.h> // struct passwd
#elif BOOST_OS_LINUX
#include <limits.h> // PATH_MAX
#include <pwd.h> // getpwuid
#include <sys/types.h> // struct passwd
#include <unistd.h> // readlink
#elif BOOST_OS_ANDROID
#include "SDL_system.h" // SDL_AndroidGetExternalStoragePath
#else
#error Unsupported OS
#endif


namespace filepathutil
{

namespace fs = boost::filesystem;
namespace conv = boost::locale::conv;



fs::path u8path(const std::string& str)
{
    return conv::utf_to_utf<fs::path::string_type::value_type>(str);
}



std::string make_preferred_path_in_utf8(const fs::path& path)
{
    auto path_ = path;
    return conv::utf_to_utf<char>(path_.make_preferred().native());
}



std::string to_utf8_path(const fs::path& path)
{
    return conv::utf_to_utf<char>(path.native());
}



std::string to_forward_slashes(const fs::path& path)
{
    std::string path_str = to_utf8_path(path);
    std::replace(path_str.begin(), path_str.end(), '\\', '/');
    return path_str;
}


boost::optional<std::string> get_executable_path()
{
#if BOOST_OS_WINDOWS
    TCHAR buf_wide[1024 + 1];
    size_t buf_size = sizeof(buf_wide);
    if (GetModuleFileName(nullptr, buf_wide, buf_size) == 0)
    {
        return boost::none;
    }
    char buf[2048 + 1];
    wcstombs(buf, buf_wide, wcslen(buf_wide) + 1);
#elif BOOST_OS_MACOS
    char buf[PATH_MAX + 1];
    uint32_t buf_size = sizeof(buf);
    if (_NSGetExecutablePath(buf, &buf_size) != 0)
    {
        return boost::none;
    }
#elif BOOST_OS_LINUX
    char buf[PATH_MAX + 1];
    size_t buf_size = sizeof(buf);
    ssize_t result = readlink("/proc/self/exe", buf, buf_size);
    if (result == -1)
    {
        return boost::none;
    }
    buf[result] = '\0';
#elif BOOST_OS_ANDROID
    std::string external_storage_path(SDL_AndroidGetExternalStoragePath());
    if (external_storage_path.back() != '/')
        external_storage_path += '/';
    const char* buf = external_storage_path.c_str();
#else
#error Unsupported OS
#endif

    return std::string(buf);
}

boost::optional<std::string> get_home_directory()
{
    boost::optional<std::string> home_directory;
#if BOOST_OS_WINDOWS
    wchar_t folder[MAX_PATH + 1];
    HRESULT hr = SHGetFolderPathW(0, CSIDL_PROFILE, 0, 0, folder);
    if (SUCCEEDED(hr))
    {
        char result[MAX_PATH + 1];
        wcstombs(result, folder, MAX_PATH);
        home_directory = std::string(result);
    }
#elif BOOST_OS_LINUX || BOOST_OS_MACOS
    char* result = getenv("HOME");
    if (result == nullptr)
    {
        struct passwd* pwd = getpwuid(getuid());
        if (pwd)
        {
            result = pwd->pw_dir;
        }
    }
    if (result != nullptr)
    {
        home_directory = result;
    }
#endif
    return home_directory;
}

} // namespace filepathutil

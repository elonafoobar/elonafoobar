#include "filepathutil.hpp"
#include <algorithm>
#include <boost/predef.h>

// For get_executable_path()
#if BOOST_OS_WINDOWS
#include <codecvt> // std::codecvt_utf8_utf16
#include <Shlobj.h> // SHGetKnownFolderPath
#include <windows.h> // GetModuleFileName
#include "unicode_utf16.hpp"
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




/**
 * Converts a UTF-8 encoded string to a filesystem path in the platform's native
 * encoding (UTF-16 for Windows, UTF-8 for everything else)
 */
fs::path u8path(const std::string& u8str)
{
#if BOOST_OS_WINDOWS
    return lib::unicode::utf8_to_utf16(u8str);
#else
    return u8str;
#endif
}



/**
 * Returns a UTF-8 string from a filesystem path with all directory separators
 * converted to the platform's preferred separators ('\' for Windows, '/' for
 * everything else)
 */
std::string make_preferred_path_in_utf8(const fs::path& path)
{
#if BOOST_OS_WINDOWS
    auto path_ = path;
    return lib::unicode::utf16_to_utf8(path_.make_preferred().native());
#else
    return path.native();
#endif
}



/**
 * Returns a UTF-8 string from a filesystem path.
 */
std::string to_utf8_path(const fs::path& path)
{
#if BOOST_OS_WINDOWS
    return lib::unicode::utf16_to_utf8(path.native());
#else
    return path.native();
#endif
}



std::string to_forward_slashes(const fs::path& path)
{
    std::string path_str = to_utf8_path(path);
    std::replace(path_str.begin(), path_str.end(), '\\', '/');
    return path_str;
}


boost::optional<fs::path> get_executable_path()
{
#if BOOST_OS_WINDOWS
    static_assert(std::is_same<TCHAR, wchar_t>::value, "TCHAR must be wchar_t");

    wchar_t buf[1024 + 1];
    size_t buf_size = sizeof(buf);
    if (GetModuleFileName(nullptr, buf, buf_size) == 0)
    {
        return boost::none;
    }
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
    std::string buf(SDL_AndroidGetExternalStoragePath());
    if (buf.back() != '/')
        buf += '/';
#else
#error Unsupported OS
#endif

    return fs::path(buf);
}

boost::optional<fs::path> get_home_directory()
{
#if BOOST_OS_WINDOWS
    wchar_t* knownFolderPath;

    auto hr = SHGetKnownFolderPath(
        FOLDERID_Profile, KF_FLAG_DEFAULT, nullptr, &knownFolderPath);

    if (!SUCCEEDED(hr))
    {
        return boost::none;
    }

    std::wstring result(knownFolderPath);
    CoTaskMemFree(knownFolderPath);
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
    if (result == nullptr)
    {
        return boost::none;
    }
#elif BOOST_OS_ANDROID
    std::string result(SDL_AndroidGetExternalStoragePath());
    if (result.back() != '/')
        result += '/';
#else
#error Unsupported OS
#endif

    return fs::path(result);
}

} // namespace filepathutil

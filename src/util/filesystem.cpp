#include "filesystem.hpp"

// For encoding conversion
#if BOOST_OS_WINDOWS
#include "unicode_utf16.hpp"
#endif

// For get_executable_path()
#if BOOST_OS_WINDOWS
#include <windows.h> // GetModuleFileName
#elif BOOST_OS_MACOS
#include <limits.h> // PATH_MAX
#include <mach-o/dyld.h> // _NSGetExecutablePath
#elif BOOST_OS_LINUX
#include <limits.h> // PATH_MAX
#include <unistd.h> // readlink
#else
#error Unsupported OS
#endif



namespace lib::filesystem
{

path path::from_u8string(const u8string& u8str)
{
#if BOOST_OS_WINDOWS
    return from_native_string(lib::unicode::utf8_to_utf16(u8str));
#else
    return from_native_string(u8str);
#endif
}



path path::from_u8string(u8string&& u8str)
{
#if BOOST_OS_WINDOWS
    return from_native_string(lib::unicode::utf8_to_utf16(u8str));
#else
    return from_native_string(std::move(u8str));
#endif
}



path path::from_u8string(const u8string::value_type* u8str)
{
#if BOOST_OS_WINDOWS
    return from_native_string(lib::unicode::utf8_to_utf16(u8str));
#else
    return from_native_string(u8str);
#endif
}



u8string path::to_u8string() const
{
    auto path = inner();
#if BOOST_OS_WINDOWS
    return lib::unicode::utf16_to_utf8(path.make_preferred().native());
#else
    return path.make_preferred().native();
#endif
}



std::optional<path> get_executable_path()
{
#if BOOST_OS_WINDOWS
    wchar_t buf[1024 + 1];
    size_t buf_size = sizeof(buf);
    if (GetModuleFileName(nullptr, buf, buf_size) == 0)
    {
        return std::nullopt;
    }
#elif BOOST_OS_MACOS
    char buf[PATH_MAX + 1];
    uint32_t buf_size = sizeof(buf);
    if (_NSGetExecutablePath(buf, &buf_size) != 0)
    {
        return std::nullopt;
    }
#elif BOOST_OS_LINUX
    char buf[PATH_MAX + 1];
    size_t buf_size = sizeof(buf);
    ssize_t result = readlink("/proc/self/exe", buf, buf_size);
    if (result == -1)
    {
        return std::nullopt;
    }
    buf[result] = '\0';
#else
#error Unsupported OS
#endif

    return path::from_native_string(buf);
}



bool is_portable_path(const path& filename)
{
    // General check by Boost.Filesystem such as invalid characters.
    auto u8str = filename.to_u8string();
    if (!boost_fs::portable_name(u8str))
        return false;

    // boost::filesystem::portable_name() function does not check the paths
    // reserved by Windows.
    // https://www.boost.org/doc/libs/1_69_0/libs/filesystem/doc/portability_guide.htm
    for (const auto fname : filename.inner())
    {
        // https://docs.microsoft.com/en-us/windows/win32/fileio/naming-a-file
        static constexpr const char* reserved_names[] = {
            "con",  "prn",  "aux",  "nul",  "com1", "com2", "com3", "com4",
            "com5", "com6", "com7", "com8", "com9", "lpt1", "lpt2", "lpt3",
            "lpt4", "lpt5", "lpt6", "lpt7", "lpt8", "lpt9",
        };

        for (const auto& reserved_name : reserved_names)
        {
            // Reserved name following extensions is also reserved.
            auto fname_no_ext = fname;
            fname_no_ext.replace_extension();
            if (fname_no_ext == reserved_name)
            {
                return false; // reserved by Windows
            }
        }
    }

    // portable name
    return true;
}



bool file_contained_in_dir(const path& file, const path& base_dir)
{
    auto p = file;

    if (!p.has_filename())
    {
        return false;
    }
    p = p.remove_filename();

    if (!exists(p))
    {
        return false;
    }

    // Strip "." and ".."
    p = canonical(p);
    auto dir = canonical(base_dir);

    const auto dir_len = std::distance(dir.inner().begin(), dir.inner().end());
    const auto file_len = std::distance(p.inner().begin(), p.inner().end());

    if (dir_len > file_len)
    {
        return false;
    }

    bool dir_is_prefix =
        std::equal(dir.inner().begin(), dir.inner().end(), p.inner().begin());
    return dir_is_prefix;
}



void copy_recursively(const path& source, const path& destination)
{
    // Check pre-conditions.
    if (!exists(source) || !is_directory(source))
    {
        throw std::runtime_error(
            "Source must be an existing directory: " + source.to_u8string());
    }
    if (exists(destination))
    {
        throw std::runtime_error(
            "Destination must not exist: " + destination.to_u8string());
    }

    // mkdir destination
    if (!create_directories(destination))
    {
        throw std::runtime_error{
            "Failed to create directory: " + destination.to_u8string()};
    }

    // Iterate all files under source.
    for (const auto& entry : iter_dir(source))
    {
        const auto from = entry.path();
        const auto to = destination / from.filename();
        if (is_directory(from))
        {
            // Call itself recursively.
            copy_recursively(from, to);
        }
        else
        {
            copy_file(from, to);
        }
    }
}

} // namespace lib::filesystem

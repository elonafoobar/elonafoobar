#pragma once

#include <optional>
#include <utility>
#include <vector>

#include <boost/predef.h>

// Prevent some old features from being defined.
// See also https://www.boost.org/doc/libs/1_66_0/libs/filesystem/doc/index.htm.
#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>

#if BOOST_OS_LINUX
#include <dirent.h> // for iter_dir()
#endif



/**
 * Wrapepr library of Boost.Filesystem
 */
namespace lib::filesystem
{

namespace boost_fs = boost::filesystem;

using u8string = std::string;



/**
 * Wrapper structure of boost::filesystem::path.
 *
 * - No implicit conversion from/to string classes and char arrays.
 *   - Exception: UTF-8 string literals is implicitly convertible to `path`.
 * - Some destructive methods are changed to non-destructive.
 */
struct path
{
    using inner_type = boost_fs::path;
    using value_type = inner_type::value_type;
    using string_type = inner_type::string_type;



    path()
        : _inner()
    {
    }



    ~path() = default;
    path(const path&) = default;
    path(path&&) noexcept = default;
    path& operator=(const path&) = default;
    path& operator=(path&&) noexcept = default;



    /**
     * Construct path from a string literal.
     */
    template <size_t N>
    /* explicit(false) */ path(const u8string::value_type (&u8str)[N])
        : path(from_u8string(u8str))
    {
    }



    explicit path(const inner_type& inner)
        : _inner(inner)
    {
    }



    explicit path(inner_type&& inner)
        : _inner(std::move(inner))
    {
    }



    static path from_u8string(const u8string& u8str);
    static path from_u8string(u8string&& u8str);
    static path from_u8string(const u8string::value_type* u8str);


    static path from_native_string(const string_type& native_string)
    {
        return path(inner_type(native_string));
    }

    static path from_native_string(string_type&& native_string)
    {
        return path(inner_type(std::move(native_string)));
    }

    static path from_native_string(const value_type* native_string)
    {
        return path(inner_type(native_string));
    }



    u8string to_u8string() const;



    bool empty() const
    {
        return inner().empty();
    }



    size_t size() const noexcept
    {
        return inner().size();
    }



    decltype(auto) native() const noexcept
    {
        return inner().native();
    }



    path filename() const
    {
        return path(inner().filename());
    }



    path extension() const
    {
        return path(inner().extension());
    }



    path parent_path() const
    {
        return path(inner().parent_path());
    }



    bool has_filename() const
    {
        return inner().has_filename();
    }



    /**
     * Returns *a new instance* without filename.
     */
    path remove_filename() const
    {
        auto tmp = inner();
        tmp.remove_filename();
        return path(tmp);
    }



    /**
     * Returns *a new instance* with no extension.
     */
    path remove_extension() const
    {
        auto tmp = inner();
        tmp.replace_extension();
        return path(tmp);
    }



    /**
     * Returns *a new instance* with the given extension.
     */
    path replace_extension(const path& ext) const
    {
        auto tmp = inner();
        tmp.replace_extension(ext);
        return path(tmp);
    }



    bool operator==(const path& other) const
    {
        return inner() == other.inner();
    }



    bool operator!=(const path& other) const
    {
        return !(*this == other);
    }



    path operator/(const path& path_segment) const
    {
        return path(inner() / path_segment.inner());
    }



    const inner_type& inner() const noexcept
    {
        return _inner;
    }



    operator inner_type() const noexcept
    {
        return inner();
    }



private:
    inner_type _inner;
};



/**
 * Short-hand for `path::from_u8string()`.
 */
inline path u8path(const u8string& u8str)
{
    return path::from_u8string(u8str);
}



/**
 * Short-hand for `path::from_u8string()`.
 */
inline path u8path(u8string&& u8str)
{
    return path::from_u8string(std::move(u8str));
}



/**
 * Short-hand for `path::from_u8string()`.
 */
inline path u8path(const u8string::value_type* u8str)
{
    return path::from_u8string(u8str);
}



/**
 * Get the executable path for various platforms.
 *
 * @return The executable on success; none on failure.
 */
std::optional<path> get_executable_path();



/**
 * Check if @a filename is portable on many platforms. It returns the same
 * result for the same @a filename regardless of the platform where you compile
 * this file and the program runs.
 *
 * @param filename The filename to check
 * @returns True if @a filename is portable; otherwise, false.
 */
bool is_portable_path(const path& filename);



/**
 * Check if @a file is contained in @a base_dir.
 */
bool file_contained_in_dir(const path& file, const path& base_dir);



inline path canonical(const path& p)
{
    return path(boost_fs::canonical(p));
}



inline path relative(const path& p, const path& base_dir)
{
    return path(boost_fs::relative(p, base_dir));
}



// Import boost::filesystem functions/enums.
using boost_fs::copy_file;
using boost_fs::create_directories;
using boost_fs::create_directory;
using boost_fs::exists;
using boost_fs::is_directory;
using boost_fs::is_regular_file;
using boost_fs::remove;
using boost_fs::remove_all;
using boost_fs::rename;

using boost_fs::copy_options;



struct dir_entry
{
    dir_entry(const path& path)
        : _path(path)
    {
    }



    struct path path() const
    {
        return _path;
    }



private:
    struct path _path;
};



template <typename F>
std::vector<dir_entry> iter_dir(const path& base_dir, F predicate)
{
// boost::filesystem::directory_iterator does not work properly on Linux.
// See commit message of ce30879c9b73ad9b21f749efc9861dbfb79b0cc6 for details.
#if BOOST_OS_LINUX
    /* Linux */

    std::vector<dir_entry> entries;

    struct dirent* entry = nullptr;
    DIR* dp = opendir(base_dir.native().c_str());
    if (dp)
    {
        while ((entry = readdir(dp)))
        {
            const auto p = base_dir / path::from_native_string(entry->d_name);
            if (!predicate(p))
            {
                continue;
            }
            entries.emplace_back(p);
        }
        closedir(dp);
    }

    return entries;

#else
    /* Windows and macOS */

    std::vector<dir_entry> entries;

    for (const auto& entry : boost_fs::directory_iterator{base_dir})
    {
        const auto p = path(entry.path());
        if (!predicate(p))
        {
            continue;
        }
        entries.emplace_back(p);
    }

    return entries;
#endif
}



inline std::vector<dir_entry> iter_dir(const path& base_dir)
{
    return iter_dir(base_dir, [](const auto&) { return true; });
}



// Emulates std::filesystem::copy_options::recursive in C++17.
void copy_recursively(const path& source, const path& destination);

} // namespace lib::filesystem



// Hash support for path
namespace std
{

template <>
struct hash<::lib::filesystem::path>
{
    size_t operator()(const ::lib::filesystem::path& key) const
    {
        return hash<::lib::filesystem::path::string_type>()(key.native());
    }
};

} // namespace std

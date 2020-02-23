#pragma once

#include <functional>
#include <regex>

#include "../util/filepathutil.hpp"
#include "defines.hpp"
#ifdef ELONA_OS_LINUX
#include <dirent.h>
#endif



namespace fs = std::filesystem;



namespace std
{

template <>
struct hash<fs::path>
{
    size_t operator()(const fs::path& key) const
    {
        return fs::hash_value(key);
    }
};

} // namespace std



namespace elona
{

namespace semver
{
struct Version;
}


namespace filesystem
{

// Pre-defined directories.
namespace dirs
{

fs::path exe();
fs::path data();
fs::path graphic();
fs::path locale();
fs::path log();
fs::path map();
fs::path mod();
fs::path for_mod(const std::string& id, const semver::Version& version);
fs::path profile_root();
fs::path current_profile();
fs::path save();
fs::path save(const std::string& player_id);
fs::path screenshot();
fs::path sound();
fs::path tmp();
fs::path user();
fs::path user_script();

void set_current_profile_directory(const fs::path& current_profile_dir);
void set_base_save_directory(const fs::path& base_save_dir);
void set_base_user_directory(const fs::path& base_user_dir);
void set_profile_directory(const fs::path& profile_dir);

} // namespace dirs



// Pre-defined files.
namespace files
{

fs::path profile_local_config();
fs::path keybinding_config();
fs::path mod_list();

} // namespace files



fs::path path(const std::string&);



#ifdef ELONA_OS_LINUX
struct DirEntry
{
    explicit DirEntry(const fs::path& path)
        : _path(path)
    {
    }


    const fs::path& path() const
    {
        return _path;
    }


private:
    fs::path _path;
};



namespace detail
{
template <typename F>
std::vector<DirEntry> glob_entries_internal(
    const fs::path& base_dir,
    const std::regex& pattern,
    F predicate)
{
    std::vector<DirEntry> entries;

    struct dirent* entry = nullptr;
    DIR* dp = opendir(base_dir.native().c_str());
    if (dp)
    {
        while ((entry = readdir(dp)))
        {
            const auto path = base_dir / fs::path{entry->d_name};
            if (!std::regex_match(
                    filepathutil::to_utf8_path(path.filename()), pattern))
            {
                continue;
            }
            if (!predicate(path))
            {
                continue;
            }
            entries.emplace_back(path);
        }
        closedir(dp);
    }

    return entries;
}
} // namespace detail



inline std::vector<DirEntry> glob_entries(
    const fs::path& base_dir,
    const std::regex& pattern = std::regex{u8".*"})
{
    return detail::glob_entries_internal(
        base_dir, pattern, [](const fs::path&) { return true; });
}



inline std::vector<DirEntry> glob_files(
    const fs::path& base_dir,
    const std::regex& pattern = std::regex{u8".*"})
{
    return detail::glob_entries_internal(
        base_dir, pattern, [](const fs::path& p) {
            return fs::is_regular_file(p);
        });
}



inline std::vector<DirEntry> glob_dirs(
    const fs::path& base_dir,
    const std::regex& pattern = std::regex{u8".*"})
{
    return detail::glob_entries_internal(
        base_dir, pattern, [](const fs::path& p) {
            return fs::is_directory(p);
        });
}

#else

struct DirEntryRange
{
    enum class Type
    {
        dir,
        file,
        all,
    };


    DirEntryRange(
        const fs::path& base_dir,
        Type entry_type,
        const std::regex& pattern)
        : base_dir(base_dir)
        , entry_type(entry_type)
        , pattern(pattern)
    {
    }


    struct iterator
    {
        using value_type = fs::directory_iterator::value_type;
        using difference_type = fs::directory_iterator::difference_type;
        using pointer = fs::directory_iterator::pointer;
        using reference = fs::directory_iterator::reference;
        using iterator_category = fs::directory_iterator::iterator_category;


        // begin
        iterator(
            const fs::directory_iterator& itr,
            std::function<bool(const fs::directory_iterator)> predicate)
            : itr(itr)
            , predicate(predicate)
        {
            while (predicate(this->itr))
            {
                ++this->itr;
            }
        }


        // end
        iterator()
        {
        }


        void operator++()
        {
            do
            {
                ++itr;
            } while (predicate(itr));
        }


        reference operator*() const
        {
            return *itr;
        }


        pointer operator->() const
        {
            return itr.operator->();
        }


        bool operator==(const iterator& other) const
        {
            return itr == other.itr;
        }


        bool operator!=(const iterator& other) const
        {
            return itr != other.itr;
        }


    private:
        fs::directory_iterator itr;
        std::function<bool(const fs::directory_iterator)> predicate;
    };


    iterator begin() const
    {
        return {fs::directory_iterator{base_dir}, [this](const auto& itr) {
                    if (itr == fs::directory_iterator{})
                        return false;
                    if (!fs::exists(itr->path()))
                        return true;
                    switch (entry_type)
                    {
                    case Type::dir:
                        if (!fs::is_directory(itr->path()))
                        {
                            return true;
                        }
                        break;
                    case Type::file:
                        if (!fs::is_regular_file(itr->path()))
                        {
                            return true;
                        }
                        break;
                    case Type::all: break;
                    }
                    return !std::regex_match(
                        filepathutil::to_utf8_path(itr->path().filename()),
                        pattern);
                }};
    }


    iterator end() const
    {
        return {};
    }


private:
    const fs::path base_dir;
    const Type entry_type;
    const std::regex pattern;
};



inline DirEntryRange glob_entries(
    const fs::path& base_dir,
    const std::regex& pattern = std::regex{u8".*"})
{
    return {base_dir, DirEntryRange::Type::all, pattern};
}



inline DirEntryRange glob_files(
    const fs::path& base_dir,
    const std::regex& pattern = std::regex{u8".*"})
{
    return {base_dir, DirEntryRange::Type::file, pattern};
}



inline DirEntryRange glob_dirs(
    const fs::path& base_dir,
    const std::regex& pattern = std::regex{u8".*"})
{
    return {base_dir, DirEntryRange::Type::dir, pattern};
}
#endif


// Emulates std::filesystem::copy_options::recursive in C++17.
void copy_recursively(const fs::path& source, const fs::path& destination);

} // namespace filesystem
} // namespace elona

#pragma once

#include <functional>
#include <regex>
#include "../util/filepathutil.hpp"



namespace fs = boost::filesystem;



namespace std
{

template <>
struct hash<fs::path>
{
    size_t operator()(const fs::path& key) const
    {
        return hash<fs::path::string_type>()(key.native());
    }
};

} // namespace std



namespace elona
{
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
fs::path for_mod(const std::string& mod_id);
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

fs::path keybinding_config();

}



fs::path path(const std::string&);
fs::path resolve_path_for_mod(const std::string& mod_local_path);



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



// Emulates std::filesystem::copy_options::recursive in C++17.
void copy_recursively(const fs::path& source, const fs::path& destination);

} // namespace filesystem
} // namespace elona

#pragma once

#include <functional>
#include <regex>

// Prevent some old features from being defined.
// See also https://www.boost.org/doc/libs/1_66_0/libs/filesystem/doc/index.htm.
#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;

#include "range.hpp"



namespace elona
{
namespace filesystem
{


fs::path path(const std::string&);


// Pre-defined directories.
namespace dir
{

fs::path exe();
fs::path data();
fs::path graphic();
fs::path map();
fs::path save();
fs::path save(const std::string& player_id);
fs::path sound();
fs::path tmp();
fs::path user();

}



struct dir_entries
{
    enum class type
    {
        dir,
        file,
        all,
    };


    dir_entries(
        const fs::path& base_dir,
        type entry_type,
        const std::regex& pattern = std::regex{u8".*"})
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
                    case type::dir:
                        if (!fs::is_directory(itr->path()))
                        {
                            return true;
                        }
                        break;
                    case type::file:
                        if (!fs::is_regular_file(itr->path()))
                        {
                            return true;
                        }
                        break;
                    case type::all: break;
                    }
                    return !std::regex_match(
                        itr->path().filename().generic_string(), pattern);
                }};
    }


    iterator end() const
    {
        return {};
    }


private:
    const fs::path base_dir;
    const type entry_type;
    const std::regex pattern;
};



std::string make_preferred_path_in_utf8(const fs::path& path);
std::string to_narrow_path(const fs::path& path);
std::string to_utf8_path(const fs::path& path);



} // namespace filesystem
} // namespace elona

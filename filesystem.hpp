#pragma once

#if __has_include(<filesystem>)
#include <filesystem>
namespace fs = std::filesystem;
#else
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif
#include <functional>
#include <regex>
#include "range.hpp"



namespace elona::filesystem
{


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
                    if (!itr->exists())
                        return true;
                    switch (entry_type)
                    {
                    case type::dir:
                        if (!itr->is_directory())
                        {
                            return true;
                        }
                        break;
                    case type::file:
                        if (!itr->is_regular_file())
                        {
                            return true;
                        }
                        break;
                    case type::all: break;
                    }
                    return !std::regex_match(
                        itr->path().filename().generic_u8string(), pattern);
                }};
    }


    iterator end() const
    {
        return {};
    }


private:
    const fs::path base_dir;
    const std::regex pattern;
    const type entry_type;
};


} // namespace elona::filesystem

#pragma once

#if __has_include(<filesystem>)
#include <filesystem>
namespace fs = std::filesystem;
#else
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif
#include "range.hpp"



namespace elona::filesystem
{


struct dir_entries
{
    dir_entries(const fs::path& base_dir)
        : base_dir(base_dir)
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
        iterator(const fs::directory_iterator& itr)
            : itr(itr)
        {
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
            } while (itr != end && !itr->exists());
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
        const fs::directory_iterator end;
    };


    iterator begin() const
    {
        return {fs::directory_iterator{base_dir}};
    }


    iterator end() const
    {
        return {};
    }


private:
    const fs::path base_dir;
};


} // namespace elona::filesystem

#pragma once

#include <cassert>

#include <fstream>
#include <iterator>

#include "filepathutil.hpp"



namespace fileutil
{

inline void skip_bom(std::istream& in)
{
    assert(in.tellg() == std::istream::pos_type(0));

    const auto first = in.get();
    const auto second = in.get();
    const auto third = in.get();
    if (first != 0xef || second != 0xbb || third != 0xbf)
        in.seekg(0); // Not BOM
}



// Note: the line number is 1-based.
// Note: the line does not contains a line break.
struct ByLineReader
{
    struct iterator
    {
        using value_type = std::string;
        using difference_type = size_t;
        using pointer = const value_type*;
        using reference = const value_type&;
        using iterator_category = std::input_iterator_tag;


        iterator(std::ifstream& in, bool is_begin)
            : in(in)
        {
            if (is_begin)
            {
                ++(*this);
            }
        }


        void operator++()
        {
            if (std::getline(in, value))
            {
                ++n;
            }
            else // EOF
            {
                n = 0; // Becomes equal to end().
            }
        }


        reference operator*() const
        {
            return value;
        }


        pointer operator->() const
        {
            return &value;
        }


        bool operator!=(const iterator& other) const
        {
            return n != other.n;
        }

        bool operator==(const iterator& other) const
        {
            return n == other.n;
        }


        size_t line_number() const noexcept
        {
            return n;
        }


    private:
        std::ifstream& in;
        value_type value;
        size_t n = 0;
    };


    ByLineReader(const boost::filesystem::path& filepath)
    {
        in.open(filepath.native());
        if (!in)
        {
            throw std::runtime_error(
                u8"Could not open file " +
                filepathutil::make_preferred_path_in_utf8(filepath));
        }
        skip_bom(in);
    }


    iterator begin()
    {
        return {in, true};
    }


    iterator end()
    {
        return {in, false};
    }


private:
    std::ifstream in;
};



inline ByLineReader read_by_line(const boost::filesystem::path& filepath)
{
    return {filepath};
}

} // namespace fileutil

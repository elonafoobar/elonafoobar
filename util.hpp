#pragma once

#include <cctype>
#include <fstream>
#include <iterator>
#include <string>
#include <string_view>
#include <utility>
#include "filesystem.hpp"



namespace elona
{


namespace strutil
{


inline bool contains(
    std::string_view str,
    std::string_view pattern,
    std::string_view::size_type pos = 0)
{
    return str.find(pattern, pos) != std::string::npos;
}



inline bool starts_with(
    std::string_view str,
    std::string_view prefix,
    std::string_view::size_type pos = 0)
{
    return str.find(prefix, pos) == pos;
}



inline std::string to_lower(std::string_view source)
{
    std::string ret;
    std::transform(
        std::begin(source),
        std::end(source),
        std::back_inserter(ret),
        [](char c) { return std::tolower(c); });
    return ret;
}



inline std::vector<std::string> split_lines(const std::string& str)
{
    std::vector<std::string> lines;
    std::istringstream ss{str};
    std::string buf;
    while (std::getline(ss, buf))
    {
        lines.push_back(buf);
    }
    return lines;
}



inline std::string remove_str(
    const std::string& str,
    const std::string& pattern)
{
    std::string ret = str;
    const auto length = std::size(pattern);
    while (1)
    {
        const auto p = ret.find(pattern);
        if (p == std::string::npos)
            break;
        ret.erase(p, length);
    }
    return ret;
}



} // namespace strutil



namespace fileutil
{


// Note: the line number is 1-based.
// Note: the line does not contains a line break.
struct read_by_line
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


        size_t line_number() const noexcept
        {
            return n;
        }


    private:
        std::ifstream& in;
        value_type value;
        size_t n = 0;
    };


    read_by_line(const fs::path& filepath)
        : in(filepath)
    {
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


} // namespace fileutil


} // namespace elona

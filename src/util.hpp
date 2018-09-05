#pragma once

#include <cctype>
#include <fstream>
#include <iterator>
#include <sstream>
#include <string>
#include <utility>
#include "filesystem.hpp"



namespace elona
{


namespace strutil
{


inline bool contains(
    const std::string& str,
    const std::string& pattern,
    std::string::size_type pos = 0)
{
    return str.find(pattern, pos) != std::string::npos;
}



inline bool starts_with(
    const std::string& str,
    const std::string& prefix,
    std::string::size_type pos = 0)
{
    return str.find(prefix, pos) == pos;
}



inline std::string to_lower(const std::string& source)
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
    std::istringstream ss(str);
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
    const auto length = pattern.size();
    while (1)
    {
        const auto p = ret.find(pattern);
        if (p == std::string::npos)
            break;
        ret.erase(p, length);
    }
    return ret;
}



inline size_t byte_count(uint8_t c)
{
    if (c <= 0x7F)
        return 1;
    else if (c >= 0xc2 && c <= 0xdf)
        return 2;
    else if (c >= 0xe0 && c <= 0xef)
        return 3;
    else if (c >= 0xf0 && c <= 0xf7)
        return 4;
    else if (c >= 0xf8 && c <= 0xfb)
        return 5;
    else if (c >= 0xfc && c <= 0xfd)
        return 6;
    else
        return 1;
}



inline size_t byte_count(char c)
{
    return byte_count(static_cast<uint8_t>(c));
}



inline std::pair<size_t, size_t> find_widthwise(
    std::string str,
    std::string pattern)
{
    size_t w{};
    auto pos = str.find(pattern);
    if (pos == std::string::npos)
        return std::pair<size_t, size_t>(std::string::npos, std::string::npos);

    for (size_t i = 0; i < pos;)
    {
        const auto byte = byte_count(str[i]);
        const auto char_width = byte == 1 ? 1 : 2;

        i += byte;
        w += char_width;
    }

    return std::pair<size_t, size_t>(pos, w);
}



inline std::string take_by_width(const std::string& str, size_t width)
{
    size_t w{};
    for (size_t i = 0; i < str.size();)
    {
        const auto byte = byte_count(str[i]);
        const auto char_width = byte == 1 ? 1 : 2;
        if (w + char_width > width)
        {
            return str.substr(0, i);
        }
        i += byte;
        w += char_width;
    }
    return str;
}



inline std::string
replace(const std::string& str, const std::string& from, const std::string& to)
{
    auto ret{str};
    std::string::size_type pos{};
    while ((pos = ret.find(from, pos)) != std::string::npos)
    {
        ret.replace(pos, from.size(), to);
        pos += to.size();
    }

    return ret;
}



inline std::string remove_line_ending(const std::string& str)
{
    std::string ret;
    for (const auto& c : str)
    {
        if (c != '\n' && c != '\r')
        {
            ret += c;
        }
    }
    return ret;
}



} // namespace strutil



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


    ByLineReader(const fs::path& filepath)
    {
        in.open(filepath.native());
        if (!in)
        {
            throw std::runtime_error(
                u8"Could not open file "
                + filesystem::make_preferred_path_in_utf8(filepath));
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



inline ByLineReader read_by_line(const fs::path& filepath)
{
    return {filepath};
}



} // namespace fileutil


} // namespace elona

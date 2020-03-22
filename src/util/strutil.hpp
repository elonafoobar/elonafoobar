#pragma once

#include <cctype>

#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>
#include <utility>
#include <vector>



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



inline bool ends_with(const std::string& str, const std::string& suffix)
{
    return suffix.size() <= str.size() &&
        str.find(suffix, str.size() - suffix.size()) != std::string::npos;
}



inline std::string to_lower(const std::string& source)
{
    std::string ret;
    std::transform(
        std::begin(source),
        std::end(source),
        std::back_inserter(ret),
        [](char c) { return static_cast<char>(std::tolower(c)); });
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



inline std::pair<std::string, std::string> split_on_string(
    const std::string& str,
    const std::string& split)
{
    auto pos = str.find(split);
    if (pos == std::string::npos)
    {
        throw std::runtime_error(
            "Cannot find \"" + split + "\" in \"" + str + "\"");
    }

    return std::make_pair(str.substr(0, pos), str.substr(pos + 1));
}



template <typename T>
std::vector<std::string> split(const std::string& str, const T& separator)
{
    std::vector<std::string> ret;

    std::string::size_type pos = 0;
    while (true)
    {
        const auto separator_pos = str.find(separator, pos);
        if (separator_pos == std::string::npos)
        {
            break;
        }
        ret.push_back(str.substr(pos, separator_pos - pos));
        pos = separator_pos + 1;
    }

    ret.push_back(str.substr(pos));
    return ret;
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



inline bool has_prefix(const std::string& str, const std::string& prefix)
{
    if (prefix.size() > str.size())
    {
        return false;
    }

    return std::mismatch(prefix.begin(), prefix.end(), str.begin()).first ==
        prefix.end();
}



inline bool try_remove_prefix(std::string& str, const std::string& prefix)
{
    if (!has_prefix(str, prefix))
    {
        return false;
    }

    str.erase(0, prefix.size());
    return true;
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


inline size_t utf8_cut_index(
    const std::string& utf8_string,
    int max_length_charwise)
{
    if (max_length_charwise == 0)
    {
        return 0;
    }

    int current_char = 0;
    size_t current_byte = 0;
    bool multibyte = false;
    while (current_char < max_length_charwise &&
           current_byte < utf8_string.size())
    {
        if (static_cast<unsigned char>(utf8_string[current_byte]) > 0x7F)
        {
            current_byte++;
            current_char++;
            while ((static_cast<unsigned char>(
                       utf8_string[current_byte] & 0xC0)) == 0x80)
            {
                // Fullwidth characters count as length 2.
                if (!multibyte)
                {
                    current_char++;
                    multibyte = true;
                }
                if (current_char > max_length_charwise)
                {
                    current_byte--;
                    break;
                }

                current_byte++;
                if (current_byte > utf8_string.size())
                {
                    break;
                }
            }
        }
        else
        {
            current_char++;
            current_byte++;
        }

        multibyte = false;
    }

    return current_byte;
}


/**
 * Wraps text in a language-agnostic manner. Instead of relying on
 * language-specific rules, it wraps text based on character width, determined
 * by codepoint. All 1-byte characters count as width 1, and every other
 * character is width 2.
 */
inline int wrap_text(std::string& text, int max_line_length)
{
    std::string rest{text};
    text.clear();
    int n{};

    while (1)
    {
        const auto len = rest.size();
        if (int(len) < max_line_length)
        {
            text += rest;
            return n;
        }
        size_t byte_length = 0;
        size_t width_length = 0;
        while (width_length <= len)
        {
            const auto bytes = strutil::byte_count(rest[byte_length]);
            const auto char_width = bytes == 1 ? 1 : 2;

            byte_length += bytes;
            width_length += char_width;

            if (int(width_length) > max_line_length)
            {
                text += rest.substr(0, byte_length) + '\n';
                ++n;
                if (rest.size() > byte_length)
                {
                    rest = rest.substr(byte_length);
                }
                else
                {
                    rest = "";
                }
                break;
            }
        }
    }
}

} // namespace strutil

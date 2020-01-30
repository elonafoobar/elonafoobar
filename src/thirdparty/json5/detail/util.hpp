#pragma once

#include <iomanip>
#include <limits>
#include <sstream>
#include <string>
#include "../types.hpp"



namespace json5
{
namespace detail
{

inline constexpr number_type infinity() noexcept
{
    return std::numeric_limits<number_type>::infinity();
}



inline constexpr number_type nan() noexcept
{
    return std::numeric_limits<number_type>::quiet_NaN();
}



inline constexpr bool is_digit(char c) noexcept
{
    return '0' <= c && c <= '9';
}



inline constexpr bool is_hex_digit(char c) noexcept
{
    return is_digit(c) || ('a' <= c && c <= 'f') || ('A' <= c && c <= 'F');
}



inline constexpr bool is_identifier_start(char c) noexcept
{
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || c == '_' ||
        c == '$';
}



inline constexpr bool is_identifier_continue(char c) noexcept
{
    return is_identifier_start(c) || is_digit(c);
}



inline size_t byte_count_utf8(uint8_t c)
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



inline bool is_surrogate_pair_first(uint32_t c)
{
    return 0xD800 <= c && c <= 0xDBFF;
}



inline uint8_t hex_digit_char_to_integer(char c)
{
    switch (c)
    {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    case 'a':
    case 'A': return 10;
    case 'b':
    case 'B': return 11;
    case 'c':
    case 'C': return 12;
    case 'd':
    case 'D': return 13;
    case 'e':
    case 'E': return 14;
    case 'f':
    case 'F': return 15;
    default: return 0;
    }
}



inline char32_t surrogate_pair_to_codepoint(char16_t first, char16_t second)
{
    return 0x10000 + (first - 0xD800) * 0x400 + (second - 0xDC00);
}



inline std::string codepoint_to_string(char32_t codepoint)
{
    if (codepoint <= U'\u007F')
    {
        // 1 byte in UTF-8
        return std::string{1, static_cast<char>(codepoint)};
    }
    else if (codepoint <= U'\u07FF')
    {
        // 2 byte in UTF-8
        const char first = 0b1100'0000 | (codepoint >> 6);
        const char second = 0b1000'0000 | (codepoint & 0b0011'1111);
        return std::string{first, second};
    }
    else if (codepoint <= U'\uFFFF')
    {
        // 3 byte in UTF-8.
        const char first = 0b1110'0000 | (codepoint >> 12);
        const char second = 0b1000'0000 | ((codepoint >> 6) & 0b0011'1111);
        const char third = 0b1000'0000 | (codepoint & 0b0011'1111);
        return std::string{first, second, third};
    }
    else
    {
        // 4 byte in UTF-8.
        const char first = 0b1111'0000 | (codepoint >> 18);
        const char second = 0b1000'0000 | ((codepoint >> 12) & 0b0011'1111);
        const char third = 0b1000'0000 | ((codepoint >> 6) & 0b0011'1111);
        const char forth = 0b1000'0000 | (codepoint & 0b0011'1111);
        return std::string{first, second, third, forth};
    }
}



inline std::string codepoint_to_hex_digit_string(char32_t c)
{
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << std::hex
       << static_cast<uint32_t>(c);
    return ss.str();
}

} // namespace detail
} // namespace json5

#pragma once

#include <cctype>
#include <string>
#include <string_view>



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



} // namespace strutil


} // namespace elona

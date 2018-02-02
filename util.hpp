#pragma once

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


} // namespace strutil


} // namespace elona

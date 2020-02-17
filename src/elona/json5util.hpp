#pragma once

#include <iostream>

#include "../thirdparty/json5/json5.hpp"
#include "../util/either.hpp"



namespace elona
{
namespace json5util
{

using parse_result = either::either<std::string, json5::value>;



parse_result parse_stream(std::istream& in)
{
    if (!in)
    {
        return parse_result::left_of("failed to open file");
    }

    using stream_itr = std::istreambuf_iterator<char>;
    const std::string file_content{stream_itr{in}, stream_itr{}};

    try
    {
        return parse_result::right_of(json5::parse(file_content));
    }
    catch (json5::syntax_error& err)
    {
        return parse_result::left_of(err.what());
    }
}

} // namespace json5util
} // namespace elona

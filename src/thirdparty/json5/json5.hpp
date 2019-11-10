#pragma once

#include "./detail/parser.hpp"
#include "./detail/pretty_printer.hpp"



namespace json5
{

inline value parse(const std::string& source)
{
    detail::parser p{source};
    return p.parse();
}



inline std::string stringify(
    const value& json,
    const stringify_options& opts = {})
{
    detail::pretty_printer pp{opts};
    return pp.stringify(json);
}

} // namespace json5

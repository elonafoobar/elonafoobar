#pragma once



namespace json5
{

struct stringify_options
{
    bool prettify = false;
    size_t indentation_width = 2;
    bool insert_trailing_comma = false;
    bool unquote_key = false;
    bool sort_by_key = false;

    enum class line_ending_type
    {
        lf,
        crlf,
    };

    line_ending_type line_ending = line_ending_type::lf;
};

} // namespace json5

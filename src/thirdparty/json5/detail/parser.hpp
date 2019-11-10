#pragma once

#include "../value.hpp"
#include "./lexer.hpp"
#include "./util.hpp"



namespace json5
{
namespace detail
{

class parser
{
public:
    parser(const std::string& source)
        : _ts(source)
    {
    }



    value parse()
    {
        return parse_value();
    }



private:
    token_stream _ts;



    value parse_value()
    {
        const auto tok = _ts.get();
        switch (tok.type())
        {
        case token_type::bracket_left: return parse_array();
        case token_type::brace_left: return parse_object();
        case token_type::null: return value{};
        case token_type::true_: return value{true};
        case token_type::false_: return value{false};
        case token_type::infinity: return value{infinity()};
        case token_type::nan: return value{nan()};
        case token_type::integer: return value{tok.get_integer()};
        case token_type::number: return value{tok.get_number()};
        case token_type::string: return value{tok.get_string()};
        default: throw parse_error{tok, "any JSON5 value"};
        }
    }



    value parse_array()
    {
        // The open bracket '[' has been consumed by the caller.
        value::array_type array;
        while (true)
        {
            if (_ts.peek().type() == token_type::eof)
            {
                throw parse_error{token{token_type::eof},
                                  "any JSON5 value or ']'"};
            }
            else if (_ts.peek().type() == token_type::bracket_right)
            {
                _ts.get();
                break;
            }

            array.push_back(parse_value());

            const auto delimiter = _ts.get();
            if (delimiter.type() == token_type::bracket_right)
            {
                break;
            }
            else if (delimiter.type() != token_type::comma)
            {
                throw parse_error{delimiter, "']' or ','"};
            }
        }
        return array;
    }



    value parse_object()
    {
        // The open brace '{' has been consumed by the caller.
        value::object_type object;
        while (true)
        {
            if (_ts.peek().type() == token_type::eof)
            {
                throw parse_error{token{token_type::eof},
                                  "any JSON5 value or '}'"};
            }
            else if (_ts.peek().type() == token_type::brace_right)
            {
                _ts.get();
                break;
            }

            const auto k = parse_key();
            const auto kv_separator = _ts.get();
            if (kv_separator.type() != token_type::colon)
            {
                throw parse_error{kv_separator, "':'"};
            }
            const auto v = parse_value();
            object.emplace(k, v);

            const auto delimiter = _ts.get();
            if (delimiter.type() == token_type::brace_right)
            {
                break;
            }
            else if (delimiter.type() != token_type::comma)
            {
                throw parse_error{delimiter, "'}' or ','"};
            }
        }
        return object;
    }



    string_type parse_key()
    {
        const auto tok = _ts.get();
        switch (tok.type())
        {
        case token_type::null: return "null";
        case token_type::true_: return "true";
        case token_type::false_: return "false";
        case token_type::infinity: return "Infinity";
        case token_type::nan: return "NaN";
        case token_type::string:
        case token_type::identifier: return tok.get_string();
        default: throw parse_error{tok, "string or identifier"};
        }
    }
};

} // namespace detail
} // namespace json5

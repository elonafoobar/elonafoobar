#pragma once

#include <cmath>
#include <algorithm>
#include "../stringify_options.hpp"
#include "../value.hpp"
#include "./util.hpp"



namespace json5
{
namespace detail
{

class pretty_printer
{
public:
    pretty_printer(const stringify_options& opts)
        : _opts(opts)
        , _indent_level(0)
    {
    }



    std::string stringify(const value& v)
    {
        switch (v.type())
        {
        case value_type::null: return "null";
        case value_type::boolean:
            return v.get<value::boolean_type>() ? "true" : "false";
        case value_type::integer:
            return std::to_string(v.get<value::integer_type>());
        case value_type::number:
        {
            const auto p = v.get<value::number_type>();
            if (std::isnan(p))
            {
                return "NaN";
            }
            else if (std::isinf(p))
            {
                return p < 0 ? "-Infinity" : "Infinity";
            }
            else
            {
                return std::to_string(p);
            }
        }
        case value_type::string: return quote(v.get<value::string_type>());
        case value_type::array:
            return _opts.prettify ? array_prettified(v) : array(v);
        case value_type::object:
            return _opts.prettify ? object_prettified(v) : object(v);
        default: return "<unreachable>";
        }
    }



private:
    stringify_options _opts;
    size_t _indent_level;



    std::string array(const value& v)
    {
        std::string items;
        const auto& array = v.get<value::array_type>();
        size_t i = 0;
        const auto size = array.size();
        for (const auto& v : array)
        {
            items += stringify(v);
            if (_opts.insert_trailing_comma || i != size - 1)
            {
                items += ",";
            }
            ++i;
        }
        return "[" + items + "]";
    }



    std::string array_prettified(const value& v)
    {
        std::string items;
        items += "[" + br();
        ++_indent_level;
        const auto& array = v.get<value::array_type>();
        size_t i = 0;
        const auto size = array.size();
        for (const auto& v : array)
        {
            items += indent();
            items += stringify(v);
            if (_opts.insert_trailing_comma || i != size - 1)
            {
                items += ",";
            }
            items += br();
            ++i;
        }
        --_indent_level;
        items += indent() + "]";
        return items;
    }



    std::string object(const value& v)
    {
        std::string items;
        const auto& object = v.get<value::object_type>();
        const size_t size = object.size();

        process_object(
            object,
            [&](size_t index, const std::string& k, const json5::value& v) {
                items += may_quote_key(k);
                items += ":";
                items += stringify(v);
                if (_opts.insert_trailing_comma || index != size - 1)
                {
                    items += ",";
                }
            });

        return "{" + items + "}";
    }



    std::string object_prettified(const value& v)
    {
        std::string items;
        items += "{" + br();
        ++_indent_level;
        const auto& object = v.get<value::object_type>();
        const size_t size = object.size();

        process_object(
            object,
            [&](size_t index, const std::string& k, const json5::value& v) {
                items += indent();
                items += may_quote_key(k);
                items += ": ";
                items += stringify(v);
                if (_opts.insert_trailing_comma || index != size - 1)
                {
                    items += ",";
                }
                items += br();
            });

        --_indent_level;
        items += indent() + "}";
        return items;
    }



    std::string quote(const std::string& s)
    {
        std::string ret;
        ret.reserve(s.size() + 2);
        ret += '\"';
        for (const auto& c : s)
        {
            if (c == '"' || c == '\\')
            {
                ret += '\\';
            }
            ret += c;
        }
        ret += '\"';
        return ret;
    }



    std::string may_quote_key(const std::string& k)
    {
        if (_opts.unquote_key && !k.empty() && is_identifier_start(k[0]) &&
            std::all_of(std::begin(k), std::end(k), [](const char c) {
                return is_identifier_continue(c);
            }))
        {
            return k;
        }
        else
        {
            return quote(k);
        }
    }



    std::string indent() const
    {
        return std::string(_opts.indentation_width * _indent_level, ' ');
    }



    std::string br() const
    {
        return (_opts.line_ending == stringify_options::line_ending_type::lf)
            ? "\n"
            : "\r\n";
    }



    template <typename F>
    void process_object(const value::object_type& object, F f)
    {
        if (_opts.sort_by_key)
        {
            using pair = std::pair<std::string, value>;
            std::vector<pair> items(std::begin(object), std::end(object));
            // sort by key
            std::sort(
                std::begin(items),
                std::end(items),
                [](const pair& lhs, const pair& rhs) {
                    return lhs.first < rhs.first;
                });
            size_t i{};
            for (const auto& kvp : items)
            {
                f(i, kvp.first, kvp.second);
                ++i;
            }
        }
        else
        {
            size_t i{};
            for (const auto& kvp : object)
            {
                f(i, kvp.first, kvp.second);
                ++i;
            }
        }
    }
};

} // namespace detail
} // namespace json5

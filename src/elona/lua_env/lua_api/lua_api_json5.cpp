#include "lua_api_json5.hpp"
#include "../../../thirdparty/json5/json5.hpp"



namespace elona
{
namespace lua
{

namespace
{

json5::value to_json5_value(sol::object value)
{
    switch (value.get_type())
    {
    case sol::type::lua_nil: return nullptr;
    case sol::type::number:
    {
        // TODO integer / float
        int64_t i = value.as<int64_t>();
        double f = value.as<double>();
        if (i == f)
        {
            return i;
        }
        else
        {
            return f;
        }
    }
    case sol::type::boolean: return value.as<bool>();
    case sol::type::string: return value.as<std::string>();
    case sol::type::table:
    {
        sol::table t = value;
        if (t.size() == 0)
        {
            // object
            json5::value::object_type object;
            for (const auto& kvp : t)
            {
                object.emplace(
                    kvp.first.as<std::string>(), to_json5_value(kvp.second));
            }
            return object;
        }
        else
        {
            // array
            json5::value::array_type array;
            for (size_t i = 0; i < t.size(); ++i)
            {
                array.push_back(to_json5_value(t[i]));
            }
            return array;
        }
    }
    default: throw std::runtime_error{"JSON5.stringify(): invalid type"};
    }
}



sol::object to_lua_value(const json5::value& value, sol::state_view lua)
{
    switch (value.type())
    {
    case json5::value_type::null: return sol::lua_nil;
    case json5::value_type::boolean:
        return sol::make_object(lua, value.get_boolean());
    case json5::value_type::integer:
        return sol::make_object(lua, value.get_integer());
    case json5::value_type::string:
        return sol::make_object(lua, value.get_string());
    case json5::value_type::array:
    {
        sol::table t{lua, sol::create};
        for (const auto& item : value.get_array())
        {
            t[t.size() + 1] = to_lua_value(item, lua);
        }
        return t;
    }
    case json5::value_type::object:
    {
        sol::table t{lua, sol::create};
        for (const auto& kvp : value.get_object())
        {
            t[kvp.first] = to_lua_value(kvp.second, lua);
        }
        return t;
    }
    default: throw std::runtime_error{"invalid json5::value_type"};
    }
}



using LuaParseResult = std::pair<sol::object, sol::optional<std::string>>;


template <typename T, typename U>
LuaParseResult make_parse_result(T&& a, U&& b)
{
    return LuaParseResult{std::piecewise_construct, std::tie(a), std::tie(b)};
}

} // namespace



/**
 * @luadoc
 *
 * Parses JSON5 text.
 *
 * @tparam string source JSON5 text
 * @treturn[1] any Parsed object
 * @treturn[2] nil If failed
 * @treturn[2] string Error message
 */
LuaParseResult LuaApiJSON5::parse(
    const std::string& source,
    sol::this_state state)
{
    try
    {
        sol::state_view lua{state};
        return make_parse_result(
            to_lua_value(json5::parse(source), lua), sol::nullopt);
    }
    catch (json5::syntax_error& err)
    {
        return make_parse_result(sol::lua_nil, err.what());
    }
}



/**
 * @luadoc
 *
 * Stringify arbitary value as JSON5.
 */
std::string LuaApiJSON5::stringify(sol::object value, sol::table opts)
{
    const auto value_ = to_json5_value(value);

    json5::stringify_options opts_;
    opts_.prettify = opts.get_or("prettify", false);
    opts_.indentation_width = opts.get_or("indentation_width", 2);
    opts_.insert_trailing_comma = opts.get_or("insert_trailing_comma", false);
    opts_.unquote_key = opts.get_or("unquote_key", false);
    opts_.sort_by_key = opts.get_or("sort_by_key", false);
    opts_.line_ending = opts.get_or("line_ending", std::string{"LF"}) == "LF"
        ? json5::stringify_options::line_ending_type::lf
        : json5::stringify_options::line_ending_type::crlf;

    return json5::stringify(value_, opts_);
}



void LuaApiJSON5::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, LuaApiJSON5, parse);
    LUA_API_BIND_FUNCTION(api_table, LuaApiJSON5, stringify);
}

} // namespace lua
} // namespace elona

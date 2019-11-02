#include "lua_api_config.hpp"
#include "../../config/config.hpp"



namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Sets config item's value.
 * @tparam string key Option key
 * @tparam any value Option value
 * @raise if the config item does not exist or is not a boolean, an integer, or
 * a string.
 */
void LuaApiConfig::set(const std::string& key, sol::object value)
{
    if (value == sol::lua_nil) // value is `nil`
        return;

    // TODO: int / float
    // https://github.com/ThePhD/sol2/issues/247
    if (value.is<int>())
    {
        Config::instance().set(key, value.as<int>());
    }
    else if (value.is<bool>())
    {
        Config::instance().set(key, value.as<bool>());
    }
    else if (value.is<std::string>())
    {
        Config::instance().set(key, value.as<std::string>());
    }
    else
    {
        throw std::runtime_error{"unsupported type of config"};
    }
}



/**
 * @luadoc
 *
 * Gets config item's value.
 * @tparam string key Option key
 * @raise if the config item does not exist or is not a boolean, an integer, or
 * a string.
 */
sol::object LuaApiConfig::get(const std::string& key, sol::this_state s)
{
    sol::state_view lua(s);
    // TODO: int / float
    // https://github.com/ThePhD/sol2/issues/247
    if (Config::instance().check_type<int>(key))
    {
        return sol::make_object(lua, Config::instance().get<int>(key));
    }
    else if (Config::instance().check_type<bool>(key))
    {
        return sol::make_object(lua, Config::instance().get<bool>(key));
    }
    else if (Config::instance().check_type<std::string>(key))
    {
        return sol::make_object(lua, Config::instance().get<std::string>(key));
    }
    else
    {
        throw std::runtime_error{"unsupported type of config"};
    }
}



/**
 * @luadoc
 *
 * Saves the current sate of the config to the config options file. Be sure to
 * call this when you modify the config using this API.
 */
void LuaApiConfig::save()
{
    Config::instance().save();
}



void LuaApiConfig::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, LuaApiConfig, set);
    LUA_API_BIND_FUNCTION(api_table, LuaApiConfig, get);
    LUA_API_BIND_FUNCTION(api_table, LuaApiConfig, save);
}

} // namespace lua
} // namespace elona

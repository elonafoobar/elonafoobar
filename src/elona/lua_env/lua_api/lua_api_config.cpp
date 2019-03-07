#include "lua_api_config.hpp"
#include "../../config/config.hpp"

namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Sets a string-type config item's value.
 * @raise if the config item does not exist or is not a string.
 */
void LuaApiConfig::set_string(const std::string& key, const std::string& value)
{
    Config::instance().set(key, value);
}

/**
 * @luadoc
 *
 * Sets an integer-type config item's value.
 * @raise if the config item does not exist or is not an integer.
 */
void LuaApiConfig::set_int(const std::string& key, int value)
{
    Config::instance().set(key, value);
}

/**
 * @luadoc
 *
 * Sets a boolean-type config items' value.
 * @raise if the config item does not exist or is not an integer.
 */
void LuaApiConfig::set_bool(const std::string& key, bool value)
{
    Config::instance().set(key, value);
}

/**
 * @luadoc
 *
 * Gets the value of a string-type config item.
 * @raise if the config item does not exist or is not a string.
 */
std::string LuaApiConfig::get_string(const std::string& key)
{
    return Config::instance().get<std::string>(key);
}

/**
 * @luadoc
 *
 * Gets the value of an integer-type config item.
 * @raise if the config item does not exist or is not an integer.
 */
int LuaApiConfig::get_int(const std::string& key)
{
    return Config::instance().get<int>(key);
}

/**
 * @luadoc
 *
 * Gets the value of a boolean-type config item.
 * @raise if the config item does not exist or is not a boolean.
 */
bool LuaApiConfig::get_bool(const std::string& key)
{
    return Config::instance().get<bool>(key);
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
    LUA_API_BIND_FUNCTION(api_table, LuaApiConfig, set_string);
    LUA_API_BIND_FUNCTION(api_table, LuaApiConfig, set_int);
    LUA_API_BIND_FUNCTION(api_table, LuaApiConfig, set_bool);
    LUA_API_BIND_FUNCTION(api_table, LuaApiConfig, get_string);
    LUA_API_BIND_FUNCTION(api_table, LuaApiConfig, get_int);
    LUA_API_BIND_FUNCTION(api_table, LuaApiConfig, get_bool);
    LUA_API_BIND_FUNCTION(api_table, LuaApiConfig, save);
}

} // namespace lua
} // namespace elona

#include "lua_api_config.hpp"
#include "../../config.hpp"
#include "../config_manager.hpp"



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
    lua->get_config_manager().set(key, value);
}



/**
 * @luadoc
 *
 * Gets config item's value.
 * @tparam string key Option key
 * @raise if the config item does not exist or is not a boolean, an integer, or
 * a string.
 */
sol::object LuaApiConfig::get(const std::string& key)
{
    return lua->get_config_manager().get<sol::object>(key);
}



/**
 * @luadoc
 *
 * Saves the current sate of the config to the config options file. Be sure to
 * call this when you modify the config using this API.
 */
void LuaApiConfig::save()
{
    config_save();
}



void LuaApiConfig::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, LuaApiConfig, set);
    LUA_API_BIND_FUNCTION(api_table, LuaApiConfig, get);
    LUA_API_BIND_FUNCTION(api_table, LuaApiConfig, save);
}

} // namespace lua
} // namespace elona

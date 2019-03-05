#include "lua_api_config.hpp"
#include "../../config/config.hpp"

namespace elona
{
namespace lua
{

void LuaApiConfig::set_string(const std::string& key, const std::string& value)
{
    Config::instance().set(key, value);
}

void LuaApiConfig::set_int(const std::string& key, int value)
{
    Config::instance().set(key, value);
}

void LuaApiConfig::set_bool(const std::string& key, bool value)
{
    Config::instance().set(key, value);
}

std::string LuaApiConfig::get_string(const std::string& key)
{
    return Config::instance().get<std::string>(key);
}

int LuaApiConfig::get_int(const std::string& key)
{
    return Config::instance().get<int>(key);
}

bool LuaApiConfig::get_bool(const std::string& key)
{
    return Config::instance().get<bool>(key);
}

void LuaApiConfig::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, LuaApiConfig, set_string);
    LUA_API_BIND_FUNCTION(api_table, LuaApiConfig, set_int);
    LUA_API_BIND_FUNCTION(api_table, LuaApiConfig, set_bool);
    LUA_API_BIND_FUNCTION(api_table, LuaApiConfig, get_string);
    LUA_API_BIND_FUNCTION(api_table, LuaApiConfig, get_int);
    LUA_API_BIND_FUNCTION(api_table, LuaApiConfig, get_bool);
}

} // namespace lua
} // namespace elona

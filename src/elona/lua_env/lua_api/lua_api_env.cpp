#include "lua_api_env.hpp"
#include "../../../version.hpp"



namespace elona
{
namespace lua
{
namespace LuaApiEnv
{

void bind(sol::table& api_table)
{
    LUA_API_BIND_CONSTANT(
        api_table, LUA_VERSION, LUA_VERSION_MAJOR "." LUA_VERSION_MINOR);
    LUA_API_BIND_CONSTANT(api_table, ELONA_VERSION, "1.22");
    LUA_API_BIND_CONSTANT(
        api_table, ELONA_FOOBAR_VERSION, latest_version.short_string());

    // TODO: you need to define it properly after mod API is stabilized!
    // Currently it always returns "0.1".
    LUA_API_BIND_CONSTANT(api_table, MOD_API_VERSION, "0.1");
}

} // namespace LuaApiEnv
} // namespace lua
} // namespace elona

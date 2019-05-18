#include "lua_api_env.hpp"
#include "../../../version.hpp"



namespace elona
{
namespace lua
{
namespace LuaApiEnv
{

/**
 * @luadoc LUA_VERSION field string
 *
 * Lua version. E.g., "5.3". Note that it is different from "_VERSION", one of
 * the Lua built-in global constants.
 */

/**
 * @luadoc ELONA_VERSION field string
 *
 * Elona version. Currently, it is always "1.22".
 */


/**
 * @luadoc ELONA_FOOBAR_VERSION field string
 *
 * Elona foobar version. E.g., "1.2.3"
 */

/**
 * @luadoc MOD_API_VERSION field string
 *
 * Mod API Version.
 * ***WARNING***: it always returns "0.1" so far, and *not* incremented every
 * release until the mod API is stabilized.
 */

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

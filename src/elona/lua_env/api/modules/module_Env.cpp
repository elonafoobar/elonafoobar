#include "module_Env.hpp"

#include "../../../../version.hpp"



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

void bind(sol::table& api_table)
{
    LUA_API_BIND_CONSTANT(
        api_table, LUA_VERSION, LUA_VERSION_MAJOR "." LUA_VERSION_MINOR);
    LUA_API_BIND_CONSTANT(api_table, ELONA_VERSION, "1.22");
    LUA_API_BIND_CONSTANT(
        api_table, ELONA_FOOBAR_VERSION, latest_version.short_string());
}

} // namespace LuaApiEnv
} // namespace lua
} // namespace elona

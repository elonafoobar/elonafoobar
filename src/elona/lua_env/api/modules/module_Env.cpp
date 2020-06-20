#include "../../../../version.hpp"
#include "../common.hpp"



/**
 * @luadoc
 *
 * Information about Elona foobar and mod engine environment.
 */
namespace elona::lua::api::modules::module_Env
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



void bind(sol::table api_table)
{
    /* clang-format off */

    ELONA_LUA_API_BIND_CONSTANT("LUA_VERSION", LUA_VERSION_MAJOR "." LUA_VERSION_MINOR);
    ELONA_LUA_API_BIND_CONSTANT("ELONA_VERSION", "1.22");
    ELONA_LUA_API_BIND_CONSTANT("ELONA_FOOBAR_VERSION", latest_version.short_string());

    /* clang-format on */
}

} // namespace elona::lua::api::modules::module_Env

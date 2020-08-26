#include "../../console.hpp"
#include "../../lua_env.hpp"
#include "../common.hpp"



/**
 * @luadoc
 *
 * Functions related to in-game console.
 */
namespace elona::lua::api::modules::module_Console
{

/**
 * @luadoc run
 *
 * Runs registered command.
 *
 * @treturn any the result of executed commands.
 * @treturn nil on failure
 */
sol::object Console_run(const std::string& cmdline)
{
    return lua->get_console().run(cmdline);
}



/**
 * @luadoc print
 *
 * Prints the given string.
 *
 * @treturn string str the string
 */
void Console_print(const std::string& str)
{
    return lua->get_console().print(str);
}



/**
 * @luadoc get_history
 *
 * Get command line history.
 *
 * @return the history object
 */
sol::object Console_get_history()
{
    return lua->get_console().get_history();
}



void bind(sol::table api_table)
{
    /* clang-format off */

    ELONA_LUA_API_BIND_FUNCTION("run", Console_run);
    ELONA_LUA_API_BIND_FUNCTION("print", Console_print);
    ELONA_LUA_API_BIND_FUNCTION("get_history", Console_get_history);

    /* clang-format on */
}

} // namespace elona::lua::api::modules::module_Console

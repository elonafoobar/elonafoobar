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
 * @luadoc register
 *
 * Registers a new console command.
 *
 * @tparam string mod_id the mod's id where the command is defined.
 * @tparam string name the command name.
 * @tparam function callback the command itself.
 */
void Console_register(
    const std::string& mod_id,
    const std::string& name,
    sol::protected_function callback)
{
    lua->get_console().register_(mod_id, name, callback);
}



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



void bind(sol::table api_table)
{
    /* clang-format off */

    ELONA_LUA_API_BIND_FUNCTION("register", Console_register);
    ELONA_LUA_API_BIND_FUNCTION("run", Console_run);

    /* clang-format on */
}

} // namespace elona::lua::api::modules::module_Console

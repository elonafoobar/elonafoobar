#include "module_Console.hpp"

#include "../../console.hpp"
#include "../../lua_env.hpp"



namespace elona::lua::api::modules
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
void LuaApiConsole::register_(
    const std::string& mod_id,
    const std::string& name,
    sol::protected_function callback)
{
    lua->get_console().register_(mod_id, name, callback);
}



/**
 * @luadoc
 *
 * Runs registered command.
 *
 * @treturn any the result of executed commands.
 * @treturn nil on failure
 */
sol::object LuaApiConsole::run(const std::string& cmdline)
{
    return lua->get_console().run(cmdline);
}



void LuaApiConsole::bind(sol::table api_table)
{
    LUA_API_BIND_FUNCTION_WITH_NAME(
        api_table, LuaApiConsole, register_, "register");
    LUA_API_BIND_FUNCTION(api_table, LuaApiConsole, run);
}

} // namespace elona::lua::api::modules

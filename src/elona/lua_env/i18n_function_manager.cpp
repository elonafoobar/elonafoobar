#include "i18n_function_manager.hpp"
#include "../config/config.hpp"
#include "lua_env.hpp"



namespace elona
{
namespace lua
{

I18NFunctionManager::I18NFunctionManager(LuaEnv& lua)
    : LuaSubmodule(lua)
{
    clear();
}



void I18NFunctionManager::clear()
{
    env().set("Functions", lua_state()->create_table());
}



void I18NFunctionManager::register_function(
    const std::string& language,
    const std::string& name,
    sol::protected_function function)
{
    if (env()[language] == sol::lua_nil)
    {
        env()[language] = lua_state()->create_table();
    }

    env()[language][name] = function;
}



optional<sol::protected_function> I18NFunctionManager::find_function(
    const std::string& name)
{
    const std::string& language = Config::instance().language;

    if (env()[language] == sol::lua_nil)
    {
        return none;
    }

    sol::optional<sol::protected_function> function = env()[language][name];

    if (!function || *function == sol::lua_nil)
    {
        return none;
    }

    return *function;
}

} // namespace lua
} // namespace elona

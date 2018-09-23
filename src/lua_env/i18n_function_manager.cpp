#include "i18n_function_manager.hpp"
#include "../config/config.hpp"
#include "lua_env.hpp"

namespace elona
{
namespace lua
{

I18NFunctionManager::I18NFunctionManager(LuaEnv* lua)
{
    this->lua_ = lua;
    i18n_function_env = sol::environment(
        *(lua_->get_state()), sol::create, lua_->get_state()->globals());

    clear();
}

void I18NFunctionManager::clear()
{
    i18n_function_env.set("Functions", lua_->get_state()->create_table());
}

void I18NFunctionManager::register_function(
    const std::string& language,
    const std::string& name,
    sol::protected_function function)
{
    if (i18n_function_env[language] == sol::lua_nil)
    {
        i18n_function_env[language] = lua_->get_state()->create_table();
    }

    i18n_function_env[language][name] = function;
}

optional<sol::protected_function> I18NFunctionManager::find_function(
    const std::string& name)
{
    const std::string& language = Config::instance().language;

    if (i18n_function_env[language] == sol::lua_nil)
    {
        return none;
    }

    sol::optional<sol::protected_function> function =
        i18n_function_env[language][name];

    if (!function || *function == sol::lua_nil)
    {
        return none;
    }

    return *function;
}

} // namespace lua
} // namespace elona

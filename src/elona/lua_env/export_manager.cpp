#include "export_manager.hpp"

namespace elona
{
namespace lua
{

ExportManager::ExportManager(LuaEnv* lua)
{
    lua_ = lua;
    export_env = sol::environment(
        *(lua_->get_state()), sol::create, lua_->get_state()->globals());

    export_env.set("Exports", lua_->get_state()->create_table());

    lua_->get_state()->safe_script(
        R"(
scan_exports = require "private/scan_exports"
)",
        export_env);
}


void ExportManager::register_all_exports()
{
    export_env.set(
        "_API_TABLE", lua_->get_api_manager().get_master_api_table());

    auto result = lua_->get_state()->safe_script(
        R"(
Exports = scan_exports(_API_TABLE)
)",
        export_env,
        &sol::script_pass_on_error);

    export_env.set("_API_TABLE", sol::lua_nil);

    if (!result.valid())
    {
        sol::error err = result;
        throw std::runtime_error(
            "Failed loading function export data: "s + err.what());
    }
}

optional<WrappedFunction> ExportManager::get_exported_function(
    const std::string& name) const
{
    sol::optional<sol::protected_function> func = export_env["Exports"][name];
    if (func && *func != sol::lua_nil)
    {
        return WrappedFunction{name, *func};
    }
    else
    {
        return none;
    }
}

} // namespace lua
} // namespace elona

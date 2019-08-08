#include "export_manager.hpp"
#include "api_manager.hpp"



namespace elona
{
namespace lua
{

ExportManager::ExportManager(LuaEnv& lua)
    : LuaSubmodule(lua)
{
    env().set("Exports", lua_state()->create_table());

    safe_script(
        R"(
scan_exports = require_relative("private/scan_exports")
)");
}


void ExportManager::register_all_exports()
{
    env().set("_API_TABLE", lua().get_api_manager().get_master_api_table());

    auto result = safe_script(
        R"(
Exports = scan_exports(_API_TABLE)
)",
        &sol::script_pass_on_error);

    env().set("_API_TABLE", sol::lua_nil);

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
    sol::optional<sol::protected_function> func = env()["Exports"][name];
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

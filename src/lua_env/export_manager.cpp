#include "export_manager.hpp"

namespace elona
{
namespace lua
{

export_manager::export_manager(lua_env* lua)
{
    lua_ = lua;
    export_env = sol::environment(
        *(lua_->get_state()),
        sol::create,
        lua_->get_state()->globals());

    export_env.set("Exports", lua_->get_state()->create_table());

    lua_->get_state()->safe_script(
        R"(
scan_exports = require "private/scan_exports"
)", export_env);
}


void export_manager::register_all_exports()
{
    export_env.set("_API_TABLE", lua_->get_api_manager().get_master_api_table());

    // Don't print errors (they will be thrown anyways)
    auto ignore_handler = [](lua_State*, sol::protected_function_result pfr) {
        return pfr;
    };

    auto result = lua_->get_state()->safe_script(R"(
Exports = scan_exports(_API_TABLE)
)", export_env, ignore_handler);

    export_env.set("_API_TABLE", sol::lua_nil);

    if(!result.valid())
    {
        sol::error err = result;
        throw std::runtime_error("Failed loading function export data: "s + err.what());
    }
}

optional<exported_function> export_manager::get_exported_function(const std::string& name) const
{
    sol::optional<sol::protected_function> func = export_env["Exports"][name];
    if (func && *func != sol::lua_nil)
    {
        return exported_function{name, *func};
    }
    else
    {
        return none;
    }
}

} // namespace lua
} // namespace elona

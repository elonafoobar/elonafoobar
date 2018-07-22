#include "lua_registry.hpp"
#include "../hcl.hpp"

namespace elona
{
namespace lua
{

registry_manager::registry_manager(lua_env* lua_)
{
    lua = lua_;
    registry_env = sol::environment(
        *(lua->get_state()),
        sol::create,
        lua->get_state()->globals());

    registry_env.set("Registry", lua->get_state()->create_table());
    registry_env.set("Exports", lua->get_state()->create_table());

    registry_env.set("Elona", lua->get_api_manager().bind(*lua));

    lua->get_state()->safe_script(
        R"(
scan_exports = require "private/scan_exports"
register_data = require "private/register_data"
)", registry_env);
}

void registry_manager::init(lua_env& lua)
{
    sol::table core = lua.get_api_manager().get_api_table();
    sol::table Registry = core.create_named("Registry");

    // "add_datatype", "add_data"

    Registry.set_function(
        "get",
        sol::overload(
            [&lua](const std::string& parent, const std::string& module) {
                return lua.get_registry_manager().get_table(parent, module);
            },

            // If no mod name is provided, assume it is "core".
            [&lua](const std::string& datatype) {
                return lua.get_registry_manager().get_table("core", datatype);
            }));
}

void registry_manager::register_datatype(const std::string& mod_name,
                                         const std::string& datatype_name)
{
    sol::table Registry = registry_env["Registry"];
    if (Registry[mod_name] == sol::lua_nil)
    {
        Registry[mod_name] = lua->get_state()->create_table();
    }

    // spec::object spec(datatype_name);
    // spec.init(spec_file);

    if (Registry[mod_name][datatype_name] != sol::lua_nil)
    {
        throw std::runtime_error("Mod datatype was already registered: " + datatype_name);
    }
    Registry[mod_name][datatype_name] = lua->get_state()->create_table();
}

void registry_manager::register_data(const std::string& mod_name,
                                     const std::string& datatype_name,
                                     const fs::path& data_file)
{
    if (!fs::exists(data_file))
    {
        throw std::runtime_error(data_file.string() + ": File does not exist.");
    }
    std::string normalized = filesystem::to_forward_slashes(data_file);

    registry_env.set("_MOD_NAME", mod_name);
    registry_env.set("_DATATYPE_NAME", datatype_name);
    registry_env.set("_FILEPATH", normalized);

    // Don't print errors (they will be thrown anyways)
    auto ignore_handler = [](lua_State*, sol::protected_function_result pfr) {
        return pfr;
    };

    auto result = lua->get_state()->safe_script(R"(
register_data(_MOD_NAME, _DATATYPE_NAME, _FILEPATH, Registry)
)", registry_env, ignore_handler);

    registry_env.set("_MOD_NAME", sol::lua_nil);
    registry_env.set("_DATATYPE_NAME", sol::lua_nil);
    registry_env.set("_FILEPATH", sol::lua_nil);

    if(!result.valid())
    {
        sol::error err = result;
        throw std::runtime_error("Failed loading data for "
                                 + mod_name + "." + datatype_name
                                 + ": " + err.what());
    }
}

void registry_manager::register_functions()
{
    registry_env.set("_API_TABLE", lua->get_api_manager().get_master_api_table());

    // Don't print errors (they will be thrown anyways)
    auto ignore_handler = [](lua_State*, sol::protected_function_result pfr) {
        return pfr;
    };

    auto result = lua->get_state()->safe_script(R"(
Exports = scan_exports(_API_TABLE)
print(Elona.require("Debug").inspect.inspect(Exports))
)", registry_env, ignore_handler);

    registry_env.set("_API_TABLE", sol::lua_nil);

    if(!result.valid())
    {
        sol::error err = result;
        throw std::runtime_error("Failed loading function export data: "s + err.what());
    }
}

sol::optional<sol::table> registry_manager::get_table(const std::string& mod_name,
                                                      const std::string& datatype_name)
{
    sol::optional<sol::table> mod_data_table = registry_env["Registry"][mod_name];

    if (!mod_data_table)
    {
        return sol::nullopt;
    }

    return (*mod_data_table)[datatype_name];
}

optional<exported_function> registry_manager::get_function(const std::string& name)
{
    sol::optional<sol::protected_function> func = registry_env["Exports"][name];
    if (func)
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

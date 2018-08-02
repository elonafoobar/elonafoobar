#include "registry_manager.hpp"
#include <chrono>
#include "../hcl.hpp"

namespace elona
{
namespace lua
{

registry_manager::registry_manager(lua_env* lua)
{
    lua_ = lua;
    registry_env = sol::environment(
        *(lua_->get_state()), sol::create, lua_->get_state()->globals());

    registry_env.set("Registry", lua_->get_state()->create_table());

    lua_->get_state()->safe_script(
        R"(
register_data = require "private/register_data"
)",
        registry_env);

    bind_api();
}

void registry_manager::bind_api()
{
    sol::table core = lua_->get_api_manager().get_api_table();
    sol::table Registry = core.create_named("Registry");

    // "add_datatype", "add_data"

    Registry.set_function(
        "get",
        sol::overload(
            [this](const std::string& parent, const std::string& module) {
                return get_table(parent, module);
            },

            // If no mod name is provided, assume it is "core".
            [this](const std::string& datatype) {
                return get_table("core", datatype);
            }));
}

void registry_manager::register_datatype(
    const std::string& mod_name,
    const std::string& datatype_name)
{
    sol::table Registry = registry_env["Registry"];
    if (Registry[mod_name] == sol::lua_nil)
    {
        Registry[mod_name] = lua_->get_state()->create_table();
    }

    // spec::object spec(datatype_name);
    // spec.init(spec_file);

    if (Registry[mod_name][datatype_name] != sol::lua_nil)
    {
        throw std::runtime_error(
            "Mod datatype was already registered: " + datatype_name);
    }
    Registry[mod_name][datatype_name] = lua_->get_state()->create_table();
}

void registry_manager::register_data(
    const std::string& mod_name,
    const std::string& datatype_name,
    const fs::path& data_file)
{
    using namespace std::chrono;
    steady_clock::time_point begin = steady_clock::now();

    if (!fs::exists(data_file))
    {
        throw std::runtime_error(data_file.string() + ": File does not exist.");
    }
    std::string normalized = filesystem::to_forward_slashes(data_file);

    registry_env.set("_MOD_NAME", mod_name);
    registry_env.set("_DATATYPE_NAME", datatype_name);
    registry_env.set("_FILEPATH", normalized);

    auto result = lua_->get_state()->safe_script(
        R"(
register_data(_MOD_NAME, _DATATYPE_NAME, _FILEPATH, Registry)
)",
        registry_env,
        &sol::script_pass_on_error);

    registry_env.set("_MOD_NAME", sol::lua_nil);
    registry_env.set("_DATATYPE_NAME", sol::lua_nil);
    registry_env.set("_FILEPATH", sol::lua_nil);

    if (!result.valid())
    {
        sol::error err = result;
        throw std::runtime_error(
            "Failed loading data for " + mod_name + "." + datatype_name + ": "
            + err.what());
    }

    steady_clock::time_point end = steady_clock::now();
    auto time =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - begin)
            .count();
    ELONA_LOG("[REGISTRY ("s << datatype_name << ")] time: "s << time << "ms"s);
}


sol::optional<sol::table> registry_manager::get_table(
    const std::string& mod_name,
    const std::string& datatype_name)
{
    sol::optional<sol::table> mod_data_table =
        registry_env["Registry"][mod_name];

    if (!mod_data_table)
    {
        return sol::nullopt;
    }

    return (*mod_data_table)[datatype_name];
}

} // namespace lua
} // namespace elona

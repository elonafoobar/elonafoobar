#include "registry_manager.hpp"
#include <chrono>
#include "../hcl.hpp"

namespace elona
{
namespace lua
{

RegistryManager::RegistryManager(LuaEnv* lua)
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

void RegistryManager::bind_api()
{
    sol::table core = lua_->get_api_manager().get_api_table();
    sol::table Registry = core.create_named("Registry");

    // "add_datatype", "add_data"

    Registry.set_function(
        "get_table",
        sol::overload(
            [this](const std::string& parent, const std::string& module) {
                return get_table(parent, module);
            },

            // If no mod name is provided, assume it is "core".
            [this](const std::string& datatype) {
                return get_table("core", datatype);
            }));
}

void RegistryManager::register_datatype(
    const std::string& mod_name,
    const std::string& datatype_name)
{
    sol::table Registry = registry_env["Registry"];
    if (Registry[mod_name] == sol::lua_nil)
    {
        Registry[mod_name] = lua_->get_state()->create_table();
    }

    // spec::Object spec(datatype_name);
    // spec.init(spec_file);

    if (Registry[mod_name][datatype_name] != sol::lua_nil)
    {
        throw std::runtime_error(
            "Mod datatype was already registered: " + datatype_name);
    }
    Registry[mod_name][datatype_name] = lua_->get_state()->create_table();
}

void RegistryManager::register_native_datatype(
    const std::string& datatype_name,
    std::function<void(sol::table)> initializer)
{
    register_datatype("core", datatype_name);
    native_initializers.emplace(datatype_name, initializer);
}

void RegistryManager::register_data(
    const std::string& originating_mod_name,
    const std::string& datatype_mod_name,
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

    registry_env.set("_MOD_NAME", originating_mod_name);
    registry_env.set("_DATATYPE_MOD_NAME", datatype_mod_name);
    registry_env.set("_DATATYPE_NAME", datatype_name);
    registry_env.set("_FILEPATH", normalized);

    auto result = lua_->get_state()->safe_script(
        R"(
register_data(_MOD_NAME, _DATATYPE_MOD_NAME, _DATATYPE_NAME, _FILEPATH, Registry)
)",
        registry_env,
        &sol::script_pass_on_error);

    registry_env.set("_MOD_NAME", sol::lua_nil);
    registry_env.set("_DATATYPE_MOD_NAME", sol::lua_nil);
    registry_env.set("_DATATYPE_NAME", sol::lua_nil);
    registry_env.set("_FILEPATH", sol::lua_nil);

    if (!result.valid())
    {
        sol::error err = result;
        throw std::runtime_error(
            "Failed loading data for " + originating_mod_name
            + " declaration of " + datatype_mod_name + ":" + datatype_name
            + ": " + err.what());
    }

    steady_clock::time_point end = steady_clock::now();
    auto time =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - begin)
            .count();
    ELONA_LOG("[REGISTRY ("s << datatype_name << ")] time: "s << time << "ms"s);
}


sol::optional<sol::table> RegistryManager::get_table(
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


void RegistryManager::load_mod_data(
    const std::vector<RegistryManager::location>& locations)
{
    // Load data.hcl in each mod directory.
    for (const auto& loc : locations)
    {
        load_single_mod_data(loc.data_hcl_file, loc.mod_name);
    }

    // After all data has been collected, run initializers for data
    // which is stored in C++ instead of Lua.
    for (const auto& pair : native_initializers)
    {
        const std::string& datatype_name = pair.first;
        const auto& initializer = pair.second;

        auto data_table = get_table("core", datatype_name);
        if (!data_table)
        {
            throw std::runtime_error(
                "core:" + datatype_name
                + ": core datatype not loaded (this is a bug)");
        }

        initializer(*data_table);
    }
}

void RegistryManager::load_single_mod_data(
    const fs::path& data_hcl_file,
    const std::string& mod_name)
{
    hcl::Value val = hclutil::load(data_hcl_file);

    const auto data = val.find("data");
    if (!data || !data->is<hcl::Object>())
    {
        throw std::runtime_error(
            data_hcl_file.string()
            + ": No \"data\" section found at top level");
    }

    load_declared_mod_defines(data->as<hcl::Object>(), data_hcl_file, mod_name);
    load_declared_mod_data(data->as<hcl::Object>(), data_hcl_file, mod_name);
}

void RegistryManager::load_declared_mod_defines(
    const hcl::Object& data,
    const fs::path& data_hcl_file,
    const std::string& mod_name)
{
    const auto define = data.find("define");
    if (define == data.end())
    {
        return;
    }
    if (!define->second.is<hcl::List>())
    {
        throw std::runtime_error(
            data_hcl_file.string() + ": \"define\" section was not list");
    }

    for (const auto& datatype_name : define->second.as<hcl::List>())
    {
        if (!datatype_name.is<std::string>())
        {
            throw std::runtime_error(
                data_hcl_file.string()
                + ": Entry in \"define\" was not string");
        }

        register_datatype(mod_name, datatype_name.as<std::string>());
    }
}

void RegistryManager::load_declared_mod_data(
    const hcl::Object& data,
    const fs::path& data_hcl_file,
    const std::string& mod_name)
{
    const auto load = data.find("load");
    if (load == data.end())
    {
        return;
    }
    if (!load->second.is<hcl::Object>())
    {
        throw std::runtime_error(
            data_hcl_file.string() + ": \"load\" section was not object");
    }

    // Load each entry of the form:
    // mod_name.datatype_name = ["data/file1", "data/file2"]
    for (const auto& pair : load->second.as<hcl::Object>())
    {
        if (!pair.second.is<hcl::List>())
        {
            throw std::runtime_error(
                data_hcl_file.string() + ": Data declaration \"" + pair.first
                + "\" was not list");
        }

        load_single_declared_mod_data(
            pair.first, pair.second.as<hcl::List>(), data_hcl_file, mod_name);
    }
}

void RegistryManager::load_single_declared_mod_data(
    const std::string& datatype_fqn,
    const hcl::List& file_list,
    const fs::path& data_hcl_file,
    const std::string& mod_name)
{
    // Break identifier like "core.chara" into "core", "chara"
    auto period_pos = datatype_fqn.find(".");
    if (period_pos == std::string::npos)
    {
        throw std::runtime_error(
            data_hcl_file.string() + ": Bad datatype name \"" + datatype_fqn
            + "\"");
    }

    std::string datatype_mod_name = datatype_fqn.substr(0, period_pos);
    std::string datatype_name = datatype_fqn.substr(period_pos + 1);

    for (const auto& file : file_list)
    {
        if (!file.is<std::string>())
        {
            throw std::runtime_error(
                data_hcl_file.string() + ": Data file in \"" + datatype_fqn
                + "\" declaration was not string");
        }

        register_data(
            mod_name,
            datatype_mod_name,
            datatype_name,
            filesystem::make_preferred_path_in_utf8(
                data_hcl_file.parent_path() / file.as<std::string>()));
    }
}


} // namespace lua
} // namespace elona

#include "lua_env.hpp"

#include "enums/enums.hpp"
#include "lua_api/lua_api.hpp"
#include "lua_class/lua_class.hpp"

#include <iterator>

namespace elona
{
namespace lua
{

APIManager::APIManager(LuaEnv* lua)
{
    this->lua = lua;
    this->api_env = sol::environment(
        *(this->lua->get_state()),
        sol::create,
        this->lua->get_state()->globals());

    // Bind the API tables at e.g. Elona["core"]["Chara"]
    sol::table Elona = api_env.create_named("Elona");
    sol::table core = Elona.create_named("core");

    LuaApi::bind(core);

    // Register usertype classes globally, and add APIs for
    // constructors.
    LuaApiClasses::bind(*lua->get_state());
    LuaApiClasses::bind_api(*lua->get_state(), core);

    // Bind enums to the Enums table.
    LuaEnums::bind(core);
}

bool APIManager::is_loaded()
{
    bool loaded = api_env["_LOADED"];
    return loaded;
}

sol::optional<sol::table> APIManager::try_find_api(
    const std::string& module_namespace,
    const std::string& module_name) const
{
    sol::optional<sol::table> table = api_env["Elona"][module_namespace];
    if (!table)
    {
        return sol::nullopt;
    }
    sol::optional<sol::table> result = (*table)[module_name];

    return result;
}

void APIManager::add_api(
    const std::string& module_namespace,
    sol::table& module_table)
{
    if (api_env["Elona"][module_namespace] == sol::lua_nil)
    {
        api_env["Elona"][module_namespace] = lua->get_state()->create_table();
    }

    sol::table api_table = api_env["Elona"][module_namespace].get<sol::table>();
    for (const auto& pair : module_table)
    {
        if (!pair.first.is<std::string>())
        {
            throw sol::error(
                "Error loading mod " + module_namespace
                + ": Mod API tables must only have string keys.");
        }
        api_table[pair.first.as<std::string>()] = pair.second;
    }
}

void APIManager::load_lua_support_libraries(LuaEnv& lua)
{
    // Don't load the support libraries again if they're already
    // loaded, because all the tables will be read-only.
    if (is_loaded())
    {
        return;
    }

    auto result = lua.get_state()->safe_script_file(
        filesystem::make_preferred_path_in_utf8(
            filesystem::dir::data() / "lua" / "init.lua"),
        api_env);

    if (!result.valid())
    {
        sol::error err = result;
        std::string what = err.what();
        ELONA_LOG(what);
        throw std::runtime_error("Failed initializing Lua support libraries.");
    }
}

void APIManager::lock()
{
    lua->get_state()->safe_script(
        R"(
Elona = Elona.core.ReadOnly.make_read_only(Elona)
)",
        api_env);
}

sol::table APIManager::bind(LuaEnv& lua)
{
    return lua.get_state()->create_table_with(
        "require",
        sol::overload(
            [&lua](const std::string& parent, const std::string& module) {
                sol::optional<sol::table> result = sol::nullopt;
                result = lua.get_api_manager().try_find_api(parent, module);
                return result;
            },

            // If no mod name is provided, assume it is "core".
            [&lua](const std::string& module) {
                sol::optional<sol::table> result = sol::nullopt;
                result = lua.get_api_manager().try_find_api("core", module);
                return result;
            }));
}

void APIManager::set_on(LuaEnv& lua)
{
    lua.get_state()->set("Elona", bind(lua));
}

sol::table APIManager::get_master_api_table()
{
    return api_env["Elona"];
}

sol::table APIManager::get_api_table()
{
    return api_env["Elona"]["core"];
}

} // namespace lua
} // namespace elona

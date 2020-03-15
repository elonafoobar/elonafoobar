#include "api_manager.hpp"

#include <iterator>

#include "../../util/strutil.hpp"
#include "enums/enums.hpp"
#include "lua_api/lua_api.hpp"
#include "lua_class/lua_class.hpp"



namespace elona
{
namespace lua
{

APIManager::APIManager(LuaEnv& lua)
    : LuaSubmodule(lua)
{
    // Bind the API tables at e.g. api_table["core"]["Chara"]
    sol::table api_table = env().create_named("api_table");
    sol::table core = api_table.create_named("core");

    LuaApi::bind(core);

    // Register usertype classes globally, and add APIs for
    // constructors.
    LuaApiClasses::bind(*lua_state());
    LuaApiClasses::bind_api(*lua_state(), core);

    load_prelude();
}



bool APIManager::is_loaded()
{
    sol::optional<bool> loaded = env()["_LOADED"];
    return loaded && *loaded;
}



void APIManager::load_prelude()
{
    auto result = safe_script_file(
        filesystem::dirs::data() / "script" / "prelude" / "init.lua");
    if (!result.valid())
    {
        sol::error err = result;
        throw std::runtime_error{"Failed to load prelude library: "s +
                                 err.what()};
    }

    sol::table prelude = result;
    lua_state()->globals()["prelude"] = prelude;
}



sol::optional<sol::table> APIManager::try_find_api(
    const std::string& name) const
{
    const auto pair = strutil::split_on_string(name, ".");
    return env().traverse_get<sol::optional<sol::table>>(
        "api_table", pair.first, pair.second);
}



void APIManager::add_api(
    const std::string& module_namespace,
    sol::table& module_table)
{
    if (env()["api_table"][module_namespace] == sol::lua_nil)
    {
        env()["api_table"][module_namespace] = lua_state()->create_table();
    }

    sol::table api_table =
        env()["api_table"][module_namespace].get<sol::table>();
    for (const auto& pair : module_table)
    {
        if (!pair.first.is<std::string>())
        {
            throw sol::error(
                "Error loading mod " + module_namespace +
                ": Mod API tables must only have string keys.");
        }
        api_table[pair.first.as<std::string>()] = pair.second;
    }
}



void APIManager::load_lua_support_libraries()
{
    // Don't load the support libraries again if they're already
    // loaded, because all the tables will be read-only.
    if (is_loaded())
    {
        return;
    }

    auto result = safe_script_file(
        filesystem::dirs::data() / "script" / "kernel" / "init.lua");

    if (!result.valid())
    {
        sol::error err = result;
        std::string what = err.what();
        ELONA_FATAL("lua.core") << what;
        throw std::runtime_error("Failed initializing Lua support libraries.");
    }

    sol::table api = result;
    get_core_api_table()["Iter"] = api["Iter"];
    get_core_api_table()["ReadOnly"] = api["ReadOnly"];
}



void APIManager::lock()
{
    safe_script(
        R"(
api_table = ELONA.require("core.ReadOnly").make_read_only(api_table)
)");
}



void APIManager::bind(LuaEnv& lua, sol::table table)
{
    auto ELONA = table.create_named("ELONA");
    ELONA["require"] = [&lua](const std::string& name) {
        return lua.get_api_manager().try_find_api(name);
    };
}



void APIManager::set_on(LuaEnv& lua)
{
    bind(lua, lua.get_state()->globals());
}



sol::table APIManager::get_master_api_table()
{
    return env()["api_table"];
}



sol::table APIManager::get_core_api_table()
{
    return env()["api_table"]["core"];
}

} // namespace lua
} // namespace elona

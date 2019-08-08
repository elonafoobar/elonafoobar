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
    // Bind the API tables at e.g. Elona["game"]["Chara"]
    sol::table Elona = env().create_named("Elona");
    sol::table game = Elona.create_named("game");

    LuaApi::bind(game);

    // Register usertype classes globally, and add APIs for
    // constructors.
    LuaApiClasses::bind(*lua_state());
    LuaApiClasses::bind_api(*lua_state(), game);

    // Bind enums to the Enums table.
    LuaEnums::bind(game);
}



bool APIManager::is_loaded()
{
    bool loaded = env()["_LOADED"];
    return loaded;
}



sol::optional<sol::table> APIManager::try_find_api(
    const std::string& name) const
{
    const auto pair = strutil::split_on_string(name, ".");
    return env().get<sol::optional<sol::table>>(
        std::tie("Elona", pair.first, pair.second));
}



void APIManager::add_api(
    const std::string& module_namespace,
    sol::table& module_table)
{
    if (env()["Elona"][module_namespace] == sol::lua_nil)
    {
        env()["Elona"][module_namespace] = lua_state()->create_table();
    }

    sol::table api_table = env()["Elona"][module_namespace].get<sol::table>();
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
}



void APIManager::lock()
{
    safe_script(
        R"(
Elona = Elona.game.ReadOnly.make_read_only(Elona)
)");
}



void APIManager::bind(LuaEnv& lua, sol::table table)
{
    table["require"] = sol::overload([&lua](const std::string& module) {
        return lua.get_api_manager().try_find_api(module);
    });
}



void APIManager::set_on(LuaEnv& lua)
{
    bind(lua, lua.get_state()->globals());
}



sol::table APIManager::get_master_api_table()
{
    return env()["Elona"];
}



sol::table APIManager::get_game_api_table()
{
    return env()["Elona"]["game"];
}

} // namespace lua
} // namespace elona

#pragma once

#include "../character.hpp"
#include "../filesystem.hpp"
#include "../item.hpp"
#include "lua_env.hpp"

namespace elona
{
namespace lua
{

class LuaEnv;
struct ModInfo;

/***
 * Keeps track of built-in and mod-provided API bindings. APIs are
 * organized as tables inside a Lua environment, namespaced by mod and
 * API name. To access them from mods, a global table named "Elona" is
 * bound to each mod so that "Elona.require" can be called to retrieve
 * a reference to an API table loaded in this manager.
 */
class APIManager
{
public:
    /***
     * Exposes the root API table ("Elona") from the isolated Lua API
     * environment by table reference.
     */
    static sol::table bind(LuaEnv&);

    /***
     * Exposes the root API table ("Elona") from the isolated Lua API
     * environment to the global lua state.
     *
     * For testing use only.
     */
    static void set_on(LuaEnv&);

public:
    explicit APIManager(LuaEnv*);

    /***
     * Loads Lua library files in data/lua for API implementations
     * that are handled in Lua instead of C++.
     *
     * This is done by LuaEnv on construction. It must be done before
     * any mods can be loaded, because they all implicitly depend on
     * these libraries.
     */
    void load_lua_support_libraries(LuaEnv&);

    /***
     * Makes all API tables read-only.
     */
    void lock();

    /***
     * Attempts to locate an API module under a namespace. For
     * example, all core API modules have module_namespace "core", and
     * the Rand module would have module_name "Rand".
     *
     * This is used by Elona.require in Lua to get references to API
     * tables. So, the Rand table would be accessed from Lua by
     * calling Elona.require("Rand").
     */
    sol::optional<sol::table> try_find_api(
        const std::string& module_namespace,
        const std::string& module_name) const;

    /***
     * Adds a new API from the return value of a mod's init.lua file.
     * It would then be accessable by calling
     * Elona.require("mod_id", "api_table").
     */
    void add_api(const std::string& module_namespace, sol::table& module_table);

    /***
     * Returns the reference to the API table containing the APIs of
     * all mods that have been added.
     */
    sol::table get_master_api_table();

    /***
     * Returns the reference to the core API table "Elona" in the API
     * environment. This is so other internal C++ mechanisms can add
     * their own API methods to it.
     */
    sol::table get_core_api_table();

private:
    /***
     * Returns true if the Elona table has already been loaded into
     * the API manager's Lua environment.
     */
    bool is_loaded();

    /***
     * An isolated Lua environment where all C++ function bindings are
     * kept.
     */
    sol::environment api_env;

    LuaEnv* lua;
};

} // namespace lua
} // namespace elona

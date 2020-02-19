#pragma once

#include "lua_submodule.hpp"



namespace elona
{
namespace lua
{

struct ModEnv;



/***
 * Keeps track of built-in and mod-provided API bindings. APIs are
 * organized as tables inside a Lua environment, namespaced by mod and
 * API name. To access them from mods, "require" can be called to retrieve a
 * reference to an API table loaded in this manager.
 */
class APIManager : public LuaSubmodule
{
public:
    /***
     * Exposes "require" function to import external APIs to the passed
     * environment table.
     */
    static void bind(LuaEnv&, sol::table);

    /***
     * Exposes "require" function to import external APIs to the passed Lua
     * environment as a global variable.
     *
     * For testing use only.
     */
    static void set_on(LuaEnv&);

public:
    explicit APIManager(LuaEnv&);

    /***
     * Loads Lua library files in data/lua for API implementations
     * that are handled in Lua instead of C++.
     *
     * This is done by LuaEnv on construction. It must be done before
     * any mods can be loaded, because they all implicitly depend on
     * these libraries.
     */
    void load_lua_support_libraries();

    /***
     * Makes all API tables read-only.
     */
    void lock();

    /***
     * Adds a new API from the return value of a mod's init.lua file.
     * It would then be accessable by calling require("mod_id.api_table").
     */
    void add_api(const std::string& module_namespace, sol::table& module_table);

    /***
     * Returns the reference to the API table containing the APIs of
     * all mods that have been added.
     */
    sol::table get_master_api_table();

    /***
     * Returns the reference to the game API table "API" in the API
     * environment. This is so other internal C++ mechanisms can add
     * their own API methods to it.
     */
    sol::table get_game_api_table();



private:
    /***
     * Returns true if the Elona table has already been loaded into
     * the API manager's Lua environment.
     */
    bool is_loaded();

    void load_prelude();

    /***
     * Attempts to locate an API module under a namespace. For
     * example, all game API modules have module_namespace "game", and
     * the Rand module would have module_name "Rand".
     *
     * This is used by require in Lua to get references to API tables. So, the
     * Rand table would be accessed from Lua by calling Elona.game.Rand.
     */
    sol::optional<sol::table> try_find_api(const std::string& name) const;
};

} // namespace lua
} // namespace elona

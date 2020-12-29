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
    explicit APIManager(LuaEnv&);

    void clear();

    void register_api(const std::string& mod_id, sol::table exports);

    /***
     * Makes all API tables read-only.
     */
    void lock();

    /***
     * Returns the reference to the API table containing the APIs of
     * all mods that have been added.
     */
    sol::table get_master_api_table();

    /***
     * Returns the reference to the core API table "API" in the API
     * environment. This is so other internal C++ mechanisms can add
     * their own API methods to it.
     */
    sol::table get_core_api_table();

    /***
     * Attempts to locate an API module under a namespace. For example, all
     * core API modules have module_namespace "core", and the Rand module would
     * have module_name "Rand".
     *
     * This is used by require in Lua to get references to API tables. So, the
     * Rand table would be accessed from Lua by calling require("core.Rand").
     */
    sol::optional<sol::table> try_find_api(const std::string& name) const;



private:
    /**
     * Loads native modules (i.e., libraries implemented in C++ side).
     * It adds "native" table to Lua's global namespace.
     */
    void load_native();

    /**
     * Load prelude module, available in all mod's environments.
     * It adds "prelude" table to Lua's global namespace.
     */
    void load_prelude();

    /**
     * Load kernel modules. It is totally internal and not exposed to mods.
     * It adds "kernel" table to Lua's global namespace.
     */
    void load_kernel();

    /**
     * Load core modules. They can be retrieved via "require()".
     * It adds "core" table to Lua's global namespace.
     */
    void load_core();

    void load_library(const fs::path& path, const std::string& library_name);
};

} // namespace lua
} // namespace elona

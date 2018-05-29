#pragma once

#include "../character.hpp"
#include "../filesystem.hpp"
#include "../item.hpp"
#include "lua_env.hpp"

namespace elona
{
namespace lua
{

class lua_env;
struct mod_info;

class api_manager
{
public:
    /***
     * Exposes the core API table ("Elona") from the isolated Lua API
     * environment to a given mod.
     */
    static void bind(lua_env&, mod_info&);

    /***
     * Exposes the core API table ("Elona") from the isolated Lua API
     * environment to the global lua state.
     *
     * For testing use only.
     */
    static void bind(lua_env&);
public:
    explicit api_manager(lua_env*);

    /***
     * Loads the core mod for API implementations that are handled in
     * Lua instead of C++.
     *
     * This is done by lua_env on construction. It must be done before
     * more mods can be loaded, because they all implicitly depend on
     * the core mod..
     */
    void load_core(lua_env&, const fs::path&);

    /***
     * Attempts to locate an API module under a namespace. For
     * example, all core API modules have module_namespace "core", and
     * the Rand module would have module_name "Rand".
     *
     * This is used by Elona.require in Lua to get references to API
     * tables. So, the Rand table would be accessed from Lua by
     * calling Elona.require("Rand").
     */
    sol::optional<sol::table> try_find_api(const std::string& module_namespace,
                                           const std::string& module_name);

    /***
     * Returns the reference to the core API table "Elona" in the API
     * environment. This is so other internal C++ mechanisms can add
     * their own API methods to it.
     */
    sol::table get_api_table();
private:
    /***
     * An isolated Lua environment where all C++ function bindings are
     * kept. This currently does not include usertype tables, because
     * some parts of the API implemented in Lua have to get at them
     * somehow, but that could be easily arranged sometime.
     */
    sol::environment api_env;

    lua_env* lua;
};

} // namespace lua
} // namespace elona

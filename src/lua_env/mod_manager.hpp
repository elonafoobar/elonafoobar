#pragma once

#include <map>
#include <vector>
#include "../filesystem.hpp"
#include "../optional.hpp"
#include "lua_env.hpp"

namespace elona
{
namespace lua
{

using namespace std::literals::string_literals;

/***
 * Stores the Lua environment and internal storage for a single mod.
 *
 * Mods each have a sanitized environment with a whitelist of safe
 * functions, so things like dofile can't be called. They also have an
 * internal C++ storage object for storing, serializing and
 * deserializing mod data alongside the base game data.
 */
struct mod_info
{
    explicit mod_info(
        const std::string name_,
        const optional<fs::path> path_,
        std::shared_ptr<sol::state> state)
        : name(name_), path(path_)
    {
        // This environment is created with no globals.
        env = sol::environment(*state, sol::create);

        store_local = state->create_table();
        store_global = state->create_table();
    }
    mod_info(const mod_info&) = delete;
    mod_info& operator=(const mod_info&) = delete;
    ~mod_info() = default;

    std::string name;
    optional<fs::path> path;
    sol::environment env;
    sol::table store_local;
    sol::table store_global;
};

/***
 * The stage of loading the lua environment is currently in.
 */
enum class mod_loading_stage_t : unsigned
{
    not_started,
    scan_finished,
    core_mod_loaded,
    all_mods_loaded,
};

/***
 * The core interface to the Lua environment. Used as a central
 * interface for more specialized API handling mechanisms and for
 * keeping track of mods.
 */
class mod_manager
{
public:
    explicit mod_manager(lua_env*);

    /***
     * Scans and loads all mods at the the given mods/ root directory,
     * binding their APIs to the API manager.
     */
    void load_mods(const fs::path&);

    /***
     * Runs the startup script with the given filename. It is expected
     * to be found under the data/script/ folder.
     *
     * Currently, this is always executed after the map has been
     * initialized. This will also re-run game, map and character
     * initialization hooks, because they would have been run already
     * by that point.
     */
    void run_startup_script(const std::string&);


    //*************** C++ handle management methods ****************//

    /***
     * - Clears all map-local handles and runs their removal callbacks.
     * - Clears all map-local mod storages.
     */
    void clear_map_local_data();


    //****************** Methods for testing use *******************//

    /***
     * Unloads all characters and items tracked by handles.
     *
     * For testing use only.
     */
    void clear();

    /***
     * Instantiates a new mod by running the given Lua code.
     *
     * For testing use only.
     */
    void load_mod_from_script(
        const std::string& name,
        const std::string& script,
        bool readonly = false);

    /***
     * Runs the given Lua code in an existing mod.
     *
     * Will throw if the mod doesn't exist.
     *
     * For testing use only.
     */
    void run_in_mod(const std::string& name, const std::string& script);

    /***
     * Retrieves a pointer to an instantiated mod.
     *
     * Will throw if the mod doesn't exist.
     *
     * For testing use only.
     */
    mod_info* get_mod(const std::string& name)
    {
        auto val = mods.find(name);
        if (val == mods.end())
            throw std::runtime_error("No such mod "s + name + "."s);
        return val->second.get();
    }

private:

    //********************* Lifecycle methods **********************//

    /***
     * Builds a list of all available mods in the user's mods/ folder.
     * No mod loading happens here.
     *
     * Stage before is not_started or scan_finished (to support
     * scanning multiple directories).
     * Stage after is scan_finished.
     */
    void scan_all_mods(const fs::path&);

    /***
     * Adds the parts of the API implemented in Lua to the API
     * manager's API table. It expects the core mod to have been found
     * after the initial mods scan.
     *
     * Stage before is scan_finished.
     * Stage after is core_mod_loaded.
     */
    void load_core_mod();

    /***
     * Loads all other mods that were scanned besides the core mod.
     *
     * Stage before is core_mod_loaded.
     * Stage after is all_mods_loaded.
     */
    void load_all_mods();

    /***
     * Clears the internal storage for each loaded mod. This is used
     * when transitioning between maps, because most data in the store
     * will become invalid after transitioning.
     */
    void clear_mod_stores();


    //********************** Mod loading related ***********************//

    /***
     * Runs the init script for the given mod. The mod will have been
     * scanned and its environment set up by this point.
     *
     * Will throw if there was an error on running the script.
     */
    void load_mod(mod_info& mod);

    /***
     * Sets up the global variables of a mod and locks them so they
     * cannot be overwritten.
     */
    void setup_and_lock_mod_globals(mod_info&);

    /***
     * Sets the global variables of a mod on the given table.
     */
    void setup_mod_globals(mod_info& mod, sol::table&);

    static void bind_store(sol::state&, mod_info&, sol::table&);

    static void setup_sandbox(const sol::state& state, sol::table& metatable)
    {
        // Whitelist functions that are safe for usage in user-written scripts.
        // This list can be expanded.
        static const std::string safe_functions[] = {"assert",
                                                     "type",
                                                     "pairs",
                                                     "ipairs",
                                                     "next",
                                                     "print",
                                                     "tostring",
                                                     "error"};

        for (const std::string& function_name : safe_functions)
        {
            metatable[function_name] = state[function_name];
        }
    }

private:
    std::unordered_map<std::string, std::unique_ptr<mod_info>> mods;

    /***
     * The loading stage the environment is currently in. Used for
     * tracking the lifecycle of mod loading and ensuring the loading
     * functions are ran in the correct order.
     */
    mod_loading_stage_t stage = mod_loading_stage_t::not_started;
};

} // namespace lua
} // namespace elona

#pragma once

#include "../thirdparty/sol2/sol.hpp"
#include "../character.hpp"
#include "../filesystem.hpp"
#include "../item.hpp"
#include "event_manager.hpp"
#include "handle_manager.hpp"
#include "lua_api.hpp"
#include "lua_store.hpp"
#include <map>
#include <vector>

namespace elona
{
namespace lua
{

using namespace std::literals::string_literals;

class api_manager;
class event_manager;
class handle_manager;

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
    explicit mod_info(const std::string name_, std::shared_ptr<sol::state> state) : name(name_)
        {
            // This environment is created with no globals.
            env = sol::environment(*state, sol::create);

            setup_sandbox(*state, env);

            env["_MOD_NAME"] = name;
            store = std::make_shared<lua::store>();
            store->init_no_attach(*state);
            env.set("Store", store);
        }
    mod_info(const mod_info&) = delete;
    mod_info& operator=(const mod_info&) = delete;
    ~mod_info() = default;

    static void setup_sandbox(const sol::state& state, sol::environment& env)
    {
        // Whitelist functions that are safe for usage in user-written scripts.
        // This list can be expanded.
        static const std::string safe_functions[] = {
            "assert", "type", "pairs", "ipairs", "next", "print", "tostring", "error"
        };

        for(const std::string& function_name : safe_functions)
        {
            env[function_name] = state[function_name];
        }
    }

    std::string name;
    sol::environment env;
    std::shared_ptr<lua::store> store;
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
class lua_env
{
public:
    lua_env();
    ~lua_env() = default;

    /***
     * Returns a shared pointer to this lua_env's internal Lua state.
     */
    std::shared_ptr<sol::state> get_state() { return lua; }

    /***
     * Builds a list of all available mods in the user's mods/ folder.
     * No mod loading happens here.
     *
     * Stage before is not_started.
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
    void load_core_mod(const fs::path&);

    /***
     * Loads all other mods in the user's mods/ folder besides the core mod.
     *
     * Stage before is core_mod_loaded.
     * Stage after is all_mods_loaded.
     */
    void load_all_mods(const fs::path&);

    /***
     * Clears the internal storage for each loaded mod. This is used
     * when transitioning between maps, because most data in the store
     * will become invalid after transitioning.
     *
     * TODO: Implement separate game-global storage and map-local
     * storage.
     */
    void clear_mod_stores();

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
     * Creates a new handle for an character, if the character is valid.
     */
    void on_chara_loaded(character&);

    /***
     * Creates a new handle for an item, if the item is valid.
     */
    void on_item_loaded(item&);

    /***
     * Removes a character's handle, if the character is valid.
     */
    void on_chara_unloaded(character&);

    /***
     * Removes an item's handle, if the item is valid.
     */
    void on_item_unloaded(item&);

    /***
     * Creates a new handle for a character and runs its creation
     * event callbacks.
     *
     * This requires the character to be valid.
     */
    void on_chara_creation(character&);

    /***
     * Creates a new handle for an item and runs its creation event
     * callbacks.
     *
     * This requires the item to be valid.
     */
    void on_item_creation(item&);

    /***
     * Removes a character's handle and runs its removal callbacks.
     *
     * This is not the same as killing the character.
     */
    void on_chara_removal(character&);

    /***
     * Removes an item's handle and runs its removal callbacks.
     */
    void on_item_removal(item&);

    /***
     * Clears and reset the Lua state to directly after loading the
     * core mod.
     *
     * Used when modifying startup scripts.
     */
    void reload();


    //********** Individual API manager retrieval methods **********//

    api_manager& get_api_manager();
    event_manager& get_event_manager();
    handle_manager& get_handle_manager();


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
     * NOTE: This requires the mods to have unique names between
     * tests.
     *
     * For testing use only.
     */
    void load_mod_from_script(const std::string& name, const std::string& script);

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
    mod_info* get_mod(const std::string& name) {
        auto val = mods.find(name);
        if(val == mods.end())
            throw std::runtime_error("No such mod "s + name + "."s);
        return val->second.get();
    }
private:
    /***
     * Runs the init script for the given mod. The mod will have been
     * scanned and its environment set up by this point.
     *
     * Will throw if there was an error on running the script.
     */
    void load_mod(const fs::path& path, mod_info&);
private:
    /***
     * The underlying Lua state shared across all mod/API
     * environments.
     */
    std::shared_ptr<sol::state> lua;

    std::unique_ptr<api_manager> api_mgr;
    std::unique_ptr<event_manager> event_mgr;
    std::unique_ptr<handle_manager> handle_mgr;
    std::unordered_map<std::string, std::unique_ptr<mod_info>> mods;

    /***
     * The loading stage the environment is currently in. Used for
     * tracking the lifecycle of mod loading and ensuring the loading
     * functions are ran in the correct order.
     */
    mod_loading_stage_t stage = mod_loading_stage_t::not_started;
};

extern lua_env lua;

} // namespace lua
} // namespace elona

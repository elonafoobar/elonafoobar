#pragma once

#include <boost/range/adaptor/filtered.hpp>
#include "lua_submodule.hpp"
#include "mod_env.hpp"



namespace elona
{
namespace lua
{

using namespace std::literals::string_literals;



/***
 * The stage of loading the lua environment is currently in.
 */
enum class ModLoadingStage : unsigned
{
    not_started,
    scan_finished,
    lua_libraries_loaded,
    all_mods_loaded,
};



/***
 * The core interface to the Lua environment. Used as a central
 * interface for more specialized API handling mechanisms and for
 * keeping track of mods.
 */
class ModManager : public LuaSubmodule
{
    using ModStorageType =
        std::unordered_map<std::string, std::unique_ptr<ModEnv>>;
    using ModVersionsType = std::unordered_map<std::string, semver::Version>;

public:
    using iterator = ModStorageType::iterator;
    using const_iterator = ModStorageType::const_iterator;

    explicit ModManager(LuaEnv&);

    static bool mod_id_is_reserved(const std::string& id);

    size_t enabled_mod_count() const
    {
        return enabled_versions_.size();
    }

    // Iterators for mods.
    range::iota<ModStorageType::iterator> all_mods()
    {
        return {mods_.begin(), mods_.end()};
    }

    range::iota<ModStorageType::const_iterator> all_mods() const
    {
        return {mods_.begin(), mods_.end()};
    }

    struct EnabledRange
    {
    public:
        struct iterator
        {
        private:
            using base_iterator_type = typename ModStorageType::const_iterator;

        public:
            using value_type = base_iterator_type::value_type;
            using difference_type =
                typename base_iterator_type::difference_type;
            using pointer = const value_type*;
            using reference = const value_type&;
            using iterator_category =
                typename base_iterator_type::iterator_category;


            iterator(
                const ModStorageType& map,
                const typename ModVersionsType::const_iterator& itr)
                : map(map)
                , itr(itr)
            {
            }

            reference operator*() const
            {
                auto id_and_version =
                    itr->first + "-" + itr->second.to_string();
                return *map.find(id_and_version);
            }

            pointer operator->() const
            {
                auto id_and_version =
                    itr->first + "-" + itr->second.to_string();
                return map.find(id_and_version).operator->();
            }

            void operator++()
            {
                ++itr;
            }

            bool operator!=(const iterator& other) const
            {
                return itr != other.itr;
            }

        private:
            const ModStorageType& map;
            typename ModVersionsType::const_iterator itr;
        };

        EnabledRange(const ModStorageType& map, const ModVersionsType& ver)
            : map(map)
            , ver(ver)
        {
        }

        iterator begin()
        {
            return iterator(map, ver.begin());
        }

        iterator end()
        {
            return iterator(map, ver.end());
        }

    private:
        const ModStorageType& map;
        const ModVersionsType& ver;
    };

    EnabledRange enabled_mods() const
    {
        return EnabledRange(mods_, enabled_versions_);
    }

    optional<semver::Version> get_enabled_version(const std::string& id)
    {
        auto it = enabled_versions_.find(id);
        if (it != enabled_versions_.end())
            return it->second;
        return none;
    }

    void enable_mod(
        const std::string& id,
        const semver::Version& version,
        bool fail_on_conflict = false)
    {
        auto it = enabled_versions_.find(id);
        if (it != enabled_versions_.end())
        {
            if (fail_on_conflict)
            {
                throw std::runtime_error(
                    "Mod " + id +
                    " is already enabled. Wanted: " + version.to_string() +
                    ", enabled version: " + it->second.to_string());
            }
            else
            {

                disable_mod(id);
            }
        }

        enabled_versions_[id] = version;
    }

    void disable_mod(const std::string& id)
    {
        enabled_versions_.erase(id);
    }

    /***
     * Scans and loads all mods at the the given mods/ root directory,
     * binding their APIs to the API manager.
     */
    void load_mods(const fs::path&);

    /***
     * Wipes the entire state of all mods.
     */
    void unload_mods();

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


    /***
     * Clears all map-local mod storages.
     */
    void clear_map_local_stores();

    /***
     * Clears all global mod storages.
     */
    void clear_global_stores();

    /***
     * Clears the internal storage for each loaded mod. This is used
     * when transitioning between maps, because most data in the store
     * will become invalid after transitioning.
     */
    void clear_mod_stores();


    //****************** Methods for testing use *******************//

    /***
     * Same as load_mods, but also inject an additional mod to be
     * loaded. The additional mod's path points directly to the
     * subfolder under mods/ where its init.lua is located.
     *
     * For testing use only.
     */
    void load_mods(const fs::path&, const std::vector<fs::path>);

    /***
     * Instantiates a new mod by running the given Lua code.
     *
     * For testing use only.
     */
    void load_mod_from_script(
        const std::string& id,
        const std::string& script,
        bool readonly = false);

    /***
     * Runs the given Lua code in an existing mod.
     *
     * Will throw if the mod doesn't exist.
     *
     * For testing use only.
     */
    void run_in_mod(const std::string& id, const std::string& script);

    /***
     * Creates a new mod, optionally setting its global environment to be read
     * only.
     *
     * Will throw if a mod with the same ID already exists.
     *
     * @return a pointer to the created mod.
     */
    ModEnv* create_mod(const ModManifest& manifest, bool readonly);

    /***
     * Creates a new mod, optionally setting its global environment to be read
     * only.
     *
     * Will throw if a mod with the same ID already exists.
     *
     * @return a pointer to the created mod.
     */
    ModEnv* create_mod(
        const std::string& id,
        optional<fs::path> mod_dir = none,
        bool readonly = false);

    /***
     * Retrieves a pointer to an instantiated mod. @a id_and_version is of
     * format "mod_id-0.1.0".
     */
    optional<ModEnv*> get_mod_optional(const std::string& id_and_version)
    {
        auto val = mods_.find(id_and_version);
        if (val == mods_.end())
            return none;
        return val->second.get();
    }

    /***
     * Retrieves a pointer to an instantiated mod. @a id_and_version is of
     * format "mod_id-0.1.0".
     *
     * Will throw if the mod doesn't exist.
     *
     * For testing use only.
     */
    ModEnv* get_mod(const std::string& id_and_version)
    {
        auto val = mods_.find(id_and_version);
        if (val == mods_.end())
            throw std::runtime_error("No such mod "s + id_and_version + "."s);
        return val->second.get();
    }

    /***
     * Finds the mod info of a mod that is currently enabled. Only one version
     * of any given mod can be enabled at a time. @a id is of format "mod_id".
     *
     * Will throw if no such mod matches and is enabled.
     */
    ModEnv* get_enabled_mod(const std::string& id)
    {
        auto val = get_enabled_mod_optional(id);
        if (!val)
            throw std::runtime_error("No mod "s + id + " was enabled."s);
        return *val;
    }

    /***
     * Finds the mod info of a mod that is currently enabled. Only one version
     * of any given mod can be enabled at a time. @a id is of format "mod_id".
     */
    optional<ModEnv*> get_enabled_mod_optional(const std::string& id)
    {
        auto version = get_enabled_version(id);
        if (!version)
            return none;
        return get_mod_optional(id + "-" + version->to_string());
    }

    /***
     * Calculates the order in which mods should be loaded such that all the
     * needed dependencies of a mod are loaded by the time that mod is loaded.
     *
     * The set of mods enabled is assumed to be valid with no version
     * conflicts/duplicates.
     *
     * @return a list of mod ids, ordered by loading order
     * @throws if there is a cyclic dependency, a dependency is unknown, a
     * dependency's version requirements cannot be satisfied, or more than one
     * version of the same mod is enabled
     */
    std::vector<std::string> calculate_loading_order();

    std::vector<ModManifest> get_templates();

    void create_mod_from_template(
        const std::string& new_mod_id,
        const std::string& template_mod_id);

    bool exists(const std::string& mod_id);


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
     * manager's API table.
     *
     * Stage before is scan_finished.
     * Stage after is lua_libraries_loaded.
     */
    void load_lua_support_libraries();

    /***
     * Loads all mods that were scanned during the scanning stage.
     *
     * Stage before is lua_libraries_loaded.
     * Stage after is all_mods_loaded.
     */
    void load_scanned_mods();


    //********************** Mod loading related ***********************//

    /***
     * Adds the mod under the given path to the list of known mods to
     * be loaded. The provided path is the subfolder under mods/ that
     * contains the mod's init.lua script.
     */
    void scan_mod(const fs::path&);

    /***
     * Runs the init script for the given mod. The mod will have been
     * scanned and its environment set up by this point.
     *
     * Will throw if there was an error on running the script.
     */
    void load_mod(ModEnv& mod);

    /***
     * Sets up the global variables of a mod and locks them so they
     * cannot be overwritten.
     */
    void setup_and_lock_mod_globals(ModEnv&);

    /***
     * Sets the global variables of a mod on the given table.
     */
    void setup_mod_globals(ModEnv& mod, sol::table&);


    /***
     * Binds the store variable to a mod table.
     */
    static void bind_store(sol::state&, sol::table&);

    /***
     * Whitelists functions that are safe for usage in user-written scripts.
     */
    static void setup_sandbox(const sol::state& state, sol::table& metatable)
    {
        // This list can be expanded.
        static const std::string safe_functions[] = {"assert",
                                                     "type",
                                                     "pairs",
                                                     "ipairs",
                                                     "next",
                                                     "print",
                                                     "pcall",
                                                     "xpcall",
                                                     "tostring",
                                                     "error"};

        for (const std::string& function_name : safe_functions)
        {
            metatable[function_name] = state[function_name];
        }
    }

private:
    /**
     * Map from id and version (mod_id-0.1.0) to mod info.
     */
    ModStorageType mods_;

    /***
     * Map from base mod id to its enabled version, if the mod is enabled.
     * This ensures each mod has at most one version enabled.
     */
    ModVersionsType enabled_versions_;

    /***
     * The loading stage the environment is currently in. Used for
     * tracking the lifecycle of mod loading and ensuring the loading
     * functions are run in the correct order.
     */
    ModLoadingStage stage_ = ModLoadingStage::not_started;
};



std::vector<fs::path> all_mod_dirs(const fs::path& base_dir);
std::vector<fs::path> normal_mod_dirs(const fs::path& base_dir);
std::vector<fs::path> template_mod_dirs(const fs::path& base_dir);

bool is_valid_mod_id(const std::string& id);

} // namespace lua
} // namespace elona

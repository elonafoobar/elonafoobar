#pragma once

#include "lua_submodule.hpp"
#include "mod_env.hpp"
#include "mod_version_resolver.hpp"



namespace elona
{
namespace lua
{

/***
 * The core interface to the Lua environment. Used as a central
 * interface for more specialized API handling mechanisms and for
 * keeping track of mods.
 */
class ModManager : public LuaSubmodule
{
public:
    using ModEnvMap = std::unordered_map<std::string, ModEnv>;
    using ModVersionMap = std::unordered_map<std::string, semver::Version>;
    using SortedModList = std::vector<std::string>;



    explicit ModManager(LuaEnv&);



    const ModEnvMap& mods() const noexcept
    {
        return _mods;
    }


    /**
     * Gets list of the installed mods.
     * "Installed" means that the mod is unpacked under `mod` folder.
     * This returns only latest versions.
     */
    std::vector<ModManifest> installed_mods() const;


    /**
     * Finds the mod that is currently loaded.
     */
    optional_ref<const ModEnv> get_mod(const std::string& id) const noexcept
    {
        const auto itr = mods().find(id);
        if (itr == std::end(mods()))
        {
            return none;
        }
        else
        {
            return itr->second;
        }
    }


    /**
     * Finds the mod that is currently loaded.
     */
    optional_ref<ModEnv> get_mod(const std::string& id) noexcept
    {
        const auto itr = _mods.find(id);
        if (itr == std::end(_mods))
        {
            return none;
        }
        else
        {
            return itr->second;
        }
    }


    const ModVersionMap& mod_versions() const noexcept
    {
        return _mod_versions;
    }


    const SortedModList& sorted_mods() const noexcept
    {
        return _sorted_mods;
    }


    optional_ref<const semver::Version> get_enabled_version(
        const std::string& id) const noexcept
    {
        const auto itr = mod_versions().find(id);
        if (itr == std::end(mod_versions()))
        {
            return none;
        }
        else
        {
            return itr->second;
        }
    }


    bool is_enabled(const std::string& id) const noexcept
    {
        return static_cast<bool>(get_enabled_version(id));
    }


    bool can_disable_mod(const std::string& id) const noexcept
    {
        // `core` mod cannot be disabled!
        return id != "core";
    }


    /**
     * Enable/disable mod. When disabling, @a version must be the same as the
     * currently enabled version. This function, so far, only edits the mod list
     * file. You need to re-launch foobar to apply the changes.
     */
    void toggle_mod(const std::string& id, const semver::Version& version);


    void load_mods(const ResolvedModList& resolved_mod_list);


    /**
     * Runs the startup script with the given filename. It is expected to be
     * found under `filesystem::dirs::user_script()` folder.
     *
     * Currently, this is always executed after the map has been initialized.
     * This will also re-run game, map and character initialization hooks,
     * because they would have been run already by that point.
     */
    void run_startup_script(const fs::path& script_filename);


    /**
     * Clears all map-local mod storages.
     */
    void clear_map_local_stores();

    /**
     * Clears all global mod storages.
     */
    void clear_global_stores();

    /**
     * Clears the internal storage for each loaded mod. This is used
     * when transitioning between maps, because most data in the store
     * will become invalid after transitioning.
     */
    void clear_mod_stores();


    /****************** Methods for testing use *******************/

    /**
     * Instantiates a new mod by running the given Lua code.
     *
     * For testing use only.
     */
    void load_testing_mod_from_script(
        const std::string& id,
        const std::string& script);

    /**
     * Instantiates a new mod.
     *
     * For testing use only.
     */
    void load_testing_mod_from_file(const fs::path& mod_dir);

    /**
     * Runs the given Lua code in an existing mod.
     *
     * Will throw if the mod doesn't exist.
     *
     * For testing use only.
     */
    void run_in_mod(const std::string& id, const std::string& script);



    void create_new_mod(const std::string& new_mod_id);

    bool exists(const std::string& mod_id);

    fs::path resolve_path_for_mod(const std::string& path);



private:
    ModEnvMap _mods;
    ModVersionMap _mod_versions;
    SortedModList _sorted_mods;


    void create_all_mod_env(const ModVersionMap& mod_versions);

    ModEnv& create_mod_env_from_manifest_file(
        const fs::path& manifest_filepath);
    ModEnv& create_mod_env_from_script(const std::string& id);
    ModEnv& create_mod_env_manifest(const ModManifest& manifest);


    /********************** Mod loading related ***********************/

    /**
     * Runs the init script for the given mod. The mod will have been
     * scanned and its environment set up by this point.
     *
     * Will throw if there was an error on running the script.
     */
    void load_mod(ModEnv& mod);


    /**
     * Sets the global variables of a mod.
     */
    void setup_mod_globals(ModEnv& mod);

    void init_mod(ModEnv& mod);
};



bool is_valid_mod_id(const std::string& id);
bool is_reserved_mod_id(const std::string& id);

} // namespace lua
} // namespace elona

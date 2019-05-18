#include "mod_manager.hpp"

#include <map>
#include <sstream>
#include <unordered_set>
#include <vector>

#include "../../util/topological_sorter.hpp"
#include "../character.hpp"
#include "../elona.hpp"
#include "../filesystem.hpp"
#include "../i18n.hpp"
#include "../log.hpp"
#include "../message.hpp"
#include "../variables.hpp"
#include "api_manager.hpp"
#include "data_manager.hpp"
#include "event_manager.hpp"
#include "export_manager.hpp"



namespace elona
{
namespace lua
{

static bool _is_alnum_only(const std::string& str)
{
    return find_if(str.begin(), str.end(), [](char c) {
               return !(isalnum(c) || (c == '_'));
           }) == str.end();
}


ModManager::ModManager(LuaEnv* lua)
{
    lua_ = lua;
}

bool ModManager::mod_id_is_reserved(const std::string& mod_id)
{
    return mod_id == "script" || mod_id == "_CONSOLE_" || mod_id == "BUILTIN";
}


void ModManager::load_mods(const fs::path& mod_dir)
{
    if (stage_ != ModLoadingStage::not_started)
    {
        throw std::runtime_error("Mods have already been loaded.");
    }

    scan_all_mods(mod_dir);
    load_lua_support_libraries();
    load_scanned_mods();
}

void ModManager::load_mods(
    const fs::path& mod_dir,
    const std::vector<fs::path> additional_mod_paths)
{
    if (stage_ != ModLoadingStage::not_started)
    {
        throw std::runtime_error("Mods have already been loaded.");
    }

    scan_all_mods(mod_dir);
    for (const auto& path : additional_mod_paths)
    {
        scan_mod(path);
    }
    load_lua_support_libraries();
    load_scanned_mods();
}

void ModManager::unload_mods()
{
    if (stage_ != ModLoadingStage::all_mods_loaded)
    {
        return;
    }

    mods_ = ModStorageType();
    stage_ = ModLoadingStage::not_started;
}


void report_error(sol::error err)
{
    std::string what = err.what();
    ELONA_ERROR("lua.mod") << what;
}


void ModManager::load_mod(ModInfo& mod)
{
    setup_and_lock_mod_globals(mod);

    // Skip initializing mods not created from files, because the
    // string passed to load_mod_from_script acts as the
    // initialization script.
    if (!mod.manifest.path)
    {
        return;
    }

    auto result = lua_->get_state()->safe_script_file(
        filepathutil::to_utf8_path(*mod.manifest.path / u8"init.lua"s),
        mod.env);

    // Add the API table returned by the mod's init.lua, if one
    // was returned.
    if (result.valid())
    {
        sol::optional<sol::object> object = result.get<sol::object>();
        if (object && object->is<sol::table>())
        {
            sol::table api_table = object->as<sol::table>();
            lua_->get_api_manager().add_api(mod.manifest.id, api_table);
        }
    }
    else
    {
        sol::error err = result;
        report_error(err);
        throw std::runtime_error("Failed initializing mod "s + mod.manifest.id);
    }
}

void ModManager::scan_mod(const fs::path& mod_dir)
{
    fs::path manifest_path = mod_dir / "mod.hcl";

    if (!fs::exists(manifest_path))
    {
        throw std::runtime_error(
            "Could not find mod manifest at " +
            filepathutil::to_utf8_path(manifest_path));
    }

    ModManifest manifest = ModManifest::load(manifest_path);

    const std::string& mod_id = manifest.id;
    ELONA_LOG("lua.mod") << "Found mod " << mod_id;

    if (!_is_alnum_only(mod_id))
    {
        throw std::runtime_error(
            "Mod ID \"" + mod_id +
            "\" must contain alphanumeric characters only.");
    }
    if (mod_id_is_reserved(mod_id))
    {
        throw std::runtime_error("\"" + mod_id + "\" is a reserved mod ID.");
    }

    create_mod(manifest, false);
}

void ModManager::scan_all_mods(const fs::path& mods_dir)
{
    if (stage_ != ModLoadingStage::not_started &&
        stage_ != ModLoadingStage::scan_finished)
    {
        throw std::runtime_error("Mods have already been scanned!");
    }

    for (const auto& entry : filesystem::dir_entries(
             mods_dir, filesystem::DirEntryRange::Type::dir))
    {
        if (fs::exists(entry.path() / "init.lua"))
        {
            scan_mod(entry.path());
        }
    }
    stage_ = ModLoadingStage::scan_finished;
}

void ModManager::load_lua_support_libraries()
{
    if (stage_ == ModLoadingStage::not_started)
    {
        throw std::runtime_error("Mods haven't been scanned yet!");
    }

    // Add special API tables from data/lua to the core mod. The core
    // mod's API table will be modified in-place by the Lua API code
    // under data/lua.
    lua_->get_api_manager().load_lua_support_libraries(*lua_);

    stage_ = ModLoadingStage::lua_libraries_loaded;
}

void ModManager::load_scanned_mods()
{
    if (stage_ != ModLoadingStage::lua_libraries_loaded)
    {
        throw std::runtime_error("Lua libraries weren't loaded!");
    }

    // Ensure that mods are loaded in order, such that all mods that are
    // depended on are loaded before their dependent mods.
    for (const auto& mod_id : calculate_loading_order())
    {
        ModInfo* mod = get_enabled_mod(mod_id);
        if (mod_id_is_reserved(mod_id))
        {
            // TODO warn about reserved mod IDs.
            continue;
        }
        else
        {
            load_mod(*mod);
        }
        ELONA_LOG("lua.mod") << "Loaded mod " << mod->manifest.id;
    }

    lua_->get_export_manager().register_all_exports();

    stage_ = ModLoadingStage::all_mods_loaded;
}

void ModManager::run_startup_script(const std::string& name)
{
    if (stage_ < ModLoadingStage::lua_libraries_loaded)
    {
        throw std::runtime_error("Lua libraries weren't loaded!");
    }
    if (get_enabled_mod_optional(name))
    {
        throw std::runtime_error("Startup script was already run.");
    }

    ModInfo* script_mod = create_mod("script", none, true);

    lua_->get_state()->safe_script_file(
        filepathutil::to_utf8_path(filesystem::dir::user_script() / name),
        script_mod->env);

    // Bypass read-only metatable
    script_mod->env.raw_set("data", lua_->get_data_manager().get().storage());

    ELONA_LOG("lua.mod") << "Loaded startup script " << name;
    txt(i18n::s.get("core.locale.mod.loaded_script", name),
        Message::color{ColorIndex::purple});
    Message::instance().linebreak();
}

void ModManager::clear_map_local_stores()
{
    for (auto&& pair : this->enabled_mods())
    {
        auto& mod = pair.second;
        lua_->get_state()->safe_script(R"(Store.map = {})", mod->env);
    }
}

void ModManager::clear_global_stores()
{
    for (auto&& pair : this->enabled_mods())
    {
        auto& mod = pair.second;
        lua_->get_state()->safe_script(R"(Store.global = {})", mod->env);
    }
}

void ModManager::clear_mod_stores()
{
    clear_map_local_stores();
    clear_global_stores();
}

// Callback to be called in Lua for preventing write access to unknown
// globals.
int deny(
    sol::table table,
    sol::object key,
    sol::object value,
    sol::this_state ts)
{
    UNUSED(table);
    UNUSED(value);

    std::stringstream ss;
    if (key.is<std::string>())
    {
        ss << "Cannot assign to the field \"" << key.as<std::string>()
           << "\" as it is readonly.";
    }
    else
    {
        ss << "Cannot assign to a field as it is readonly.";
    }

    lua_State* L = ts;
    return luaL_error(L, ss.str().c_str());
}

int validate_store(
    sol::table table,
    sol::object key,
    sol::object value,
    sol::this_state ts)
{
    if (table[key] != sol::lua_nil)
    {
        table.raw_set(key, value);
        return 0;
    }

    return deny(table, key, value, ts);
}

void ModManager::bind_store(sol::state& lua, ModInfo& mod, sol::table& table)
{
    sol::table Store = lua.create_table();
    sol::table metatable = lua.create_table();

    // Bind Store.global and Store.map.
    metatable["global"] = mod.store_global;
    metatable["map"] = mod.store_map;

    // Prevent creating new variables in the Store table.
    metatable[sol::meta_function::new_index] = validate_store;
    metatable[sol::meta_function::index] = metatable;

    Store[sol::metatable_key] = metatable;
    table["Store"] = Store;
}

void ModManager::setup_mod_globals(ModInfo& mod, sol::table& table)
{
    // Create the globals "Elona" and "Store" for this mod's
    // environment.
    bind_store(*lua_->get_state(), mod, table);
    table["Elona"] = lua_->get_api_manager().bind(*lua_); // TODO move elsewhere
    table["_MOD_ID"] = mod.manifest.id;

    // Add a list of whitelisted standard library functions to the
    // environment.
    setup_sandbox(*lua_->get_state(), table);

    // Add a custom version of "require" for use within mods. (Not
    // added for scripts/console environment)
    if (mod.chunk_cache)
    {
        auto state = lua_->get_state();
        auto& chunk_cache = *mod.chunk_cache;
        table["require"] = [state, &chunk_cache](
                               const std::string& name,
                               sol::this_environment this_env) {
            sol::environment env = this_env;
            return chunk_cache.require(name, env, *state);
        };
    }
}

void ModManager::setup_and_lock_mod_globals(ModInfo& mod)
{
    sol::table env_metatable = lua_->get_state()->create_table_with();

    // Globals have to be set on the metatable, not the mod's
    // environment itself.
    setup_mod_globals(mod, env_metatable);

    // Prevent writing of new globals.
    env_metatable[sol::meta_function::new_index] = deny;
    env_metatable[sol::meta_function::index] = env_metatable;

    mod.env[sol::metatable_key] = env_metatable;
}

ModInfo* ModManager::create_mod(const ModManifest& manifest, bool readonly)
{
    std::unique_ptr<ModInfo> info =
        std::make_unique<ModInfo>(manifest, lua_->get_state());

    if (readonly)
    {
        setup_and_lock_mod_globals(*info);
    }
    else
    {
        // Set the globals directly on the environment table for testing use.
        setup_mod_globals(*info, info->env);
    }

    // TODO: Enable based on user config/dependency resolution. Always enable
    // built-in mods.
    enable_mod(manifest.id, manifest.version, true);

    auto mod_id_with_version = manifest.id + "-" + manifest.version.to_string();
    mods_[mod_id_with_version] = std::move(info);
    return mods_[mod_id_with_version].get();
}

ModInfo* ModManager::create_mod(
    const std::string& id,
    optional<fs::path> mod_dir,
    bool readonly)
{
    ModManifest manifest;
    manifest.id = id;
    manifest.path = mod_dir;
    manifest.version = semver::Version(0, 1, 0);

    return create_mod(manifest, readonly);
}

std::vector<std::string> ModManager::calculate_loading_order()
{
    TopologicalSorter<std::string> sorter;

    for (const auto& pair : this->enabled_mods())
    {
        const auto& mod = pair.second;
        sorter.add(mod->manifest.id);

        for (const auto& pair : mod->manifest.dependencies)
        {
            const auto& mod_id = pair.first;
            const auto& version_req = pair.second;

            const auto dependent_mod = get_enabled_mod_optional(mod_id);
            if (!dependent_mod)
            {
                throw std::runtime_error(
                    "The dependency '" + mod_id + "' of mod '" +
                    mod->manifest.id +
                    "' could not be found in the list of scanned mods.");
            }
            const auto& ver = (*dependent_mod)->manifest.version;
            if (!version_req.is_satisfied(ver))
            {
                // Error message example:
                // The dependency requirement 'base' (>= 2.0.0) of mod 'derived'
                // could not be satisfied by 'base v1.5.0'.
                std::stringstream ss;
                ss << "The dependency requirement '" << mod_id << "' ("
                   << version_req.to_string() << ") of mod '"
                   << mod->manifest.id << "'could not be satisfied by '"
                   << mod_id << " v" << ver.to_string() << "'.";
                throw std::runtime_error(ss.str());
            }

            sorter.add_dependency(mod->manifest.id, mod_id);
        }
    }

    std::vector<std::string> result;
    std::vector<std::string> cyclic_dependencies;
    std::tie(result, cyclic_dependencies) = sorter.sort();

    if (cyclic_dependencies.size() > 0)
    {
        std::string cycle;

        for (const auto& dependency : cyclic_dependencies)
        {
            if (cycle == "")
            {
                cycle = dependency;
            }
            else
            {
                cycle += " -> " + dependency;
            }
        }

        throw std::runtime_error(
            "Cyclic dependency detected when loading mods: " + cycle);
    }

    return result;
}


// For testing use
void ModManager::load_mod_from_script(
    const std::string& name,
    const std::string& script,
    bool readonly)
{
    if (stage_ < ModLoadingStage::lua_libraries_loaded)
    {
        throw std::runtime_error("Lua libraries weren't loaded!");
    }
    {
        auto val = get_enabled_mod_optional(name);
        if (val)
        {
            throw std::runtime_error(
                "Mod "s + name + " was already initialized."s);
        }
    }

    ModInfo* mod = create_mod(name, none, readonly);

    // Run the provided script string.
    auto result = lua_->get_state()->safe_script(script, mod->env);

    // Add the API table returned by the mod's initialization script,
    // if one was returned.
    if (result.valid())
    {
        sol::optional<sol::object> object = result.get<sol::object>();
        if (object && object->is<sol::table>())
        {
            sol::table api_table = object->as<sol::table>();
            lua_->get_api_manager().add_api(name, api_table);
        }
    }
    else
    {
        sol::error err = result;
        report_error(err);
        throw std::runtime_error("Failed initializing mod "s + name);
    }
}

void ModManager::run_in_mod(const std::string& name, const std::string& script)
{
    auto val = get_enabled_mod_optional(name);
    if (!val)
    {
        throw std::runtime_error("No such mod "s + name + "."s);
    }

    // Prevent outputting things in the test log on errors, but still
    // throw if the result is invalid so tests can catch it.
    auto ignore_handler = [](lua_State*, sol::protected_function_result pfr) {
        return pfr;
    };

    auto result =
        lua_->get_state()->safe_script(script, (*val)->env, ignore_handler);

    if (!result.valid())
    {
        sol::error err = result;
        throw err;
    }
}

} // namespace lua
} // namespace elona

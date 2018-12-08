#include "mod_manager.hpp"
#include <map>
#include <sstream>
#include <vector>
#include "../../util/topological_sorter.hpp"
#include "../character.hpp"
#include "../elona.hpp"
#include "../filesystem.hpp"
#include "../i18n.hpp"
#include "../log.hpp"
#include "../message.hpp"
#include "../variables.hpp"
#include "event_manager.hpp"

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

static bool _mod_name_is_reserved(const std::string& mod_name)
{
    return mod_name == "script" || mod_name == "console" ||
        mod_name == "BUILTIN";
}


ModManager::ModManager(LuaEnv* lua)
{
    lua_ = lua;
}


void ModManager::load_mods(const fs::path& mod_dir)
{
    if (stage != ModLoadingStage::not_started)
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
    if (stage != ModLoadingStage::not_started)
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


void report_error(sol::error err)
{
    std::string what = err.what();
    ELONA_LOG(what);
}


void ModManager::clear_map_local_data()
{
    for (auto&& pair : mods)
    {
        auto& mod = pair.second;
        lua_->get_state()->safe_script(
            R"(
local function clear(t)
    for key, _ in pairs(t) do
        t[key] = nil
    end
end
if Store then
    clear(Store.map_local)
end
)",
            mod->env);
    }
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
        filesystem::make_preferred_path_in_utf8(
            *mod.manifest.path / u8"init.lua"s),
        mod.env);

    // Add the API table returned by the mod's init.lua, if one
    // was returned.
    if (result.valid())
    {
        sol::optional<sol::object> object = result.get<sol::object>();
        if (object && object->is<sol::table>())
        {
            sol::table api_table = object->as<sol::table>();
            lua_->get_api_manager().add_api(mod.manifest.name, api_table);
        }
    }
    else
    {
        sol::error err = result;
        report_error(err);
        throw std::runtime_error(
            "Failed initializing mod "s + mod.manifest.name);
    }
}

void ModManager::scan_mod(const fs::path& mod_dir)
{
    fs::path manifest_path = mod_dir / "mod.hcl";

    if (!fs::exists(manifest_path))
    {
        throw std::runtime_error(
            "Could not find mod manifest at " + manifest_path.string());
    }

    ModManifest manifest = ModManifest::load(manifest_path);

    const std::string mod_name = mod_dir.filename().string();
    ELONA_LOG("Found mod " << mod_name);

    if (!_is_alnum_only(mod_name))
    {
        throw std::runtime_error(
            "Mod name \"" + mod_name +
            "\" must contain alphanumeric characters only.");
    }
    if (_mod_name_is_reserved(mod_name))
    {
        throw std::runtime_error(
            "\"" + mod_name + "\" is a reserved mod name.");
    }

    create_mod(manifest, false);
}

void ModManager::scan_all_mods(const fs::path& mods_dir)
{
    if (stage != ModLoadingStage::not_started &&
        stage != ModLoadingStage::scan_finished)
    {
        throw std::runtime_error("Mods have already been scanned!");
    }

    const std::string init_script = "init.lua";

    for (const auto& entry : filesystem::dir_entries(
             mods_dir, filesystem::DirEntryRange::Type::dir))
    {
        if (fs::exists(entry.path() / init_script))
        {
            scan_mod(entry.path());
        }
    }
    stage = ModLoadingStage::scan_finished;
}

void ModManager::load_lua_support_libraries()
{
    if (stage == ModLoadingStage::not_started)
    {
        throw std::runtime_error("Mods haven't been scanned yet!");
    }

    // Add special API tables from data/lua to the core mod. The core
    // mod's API table will be modified in-place by the Lua API code
    // under data/lua.
    lua_->get_api_manager().load_lua_support_libraries(*lua_);

    stage = ModLoadingStage::lua_libraries_loaded;
}

void ModManager::load_scanned_mods()
{
    if (stage != ModLoadingStage::lua_libraries_loaded)
    {
        throw std::runtime_error("Lua libraries weren't loaded!");
    }

    // Ensure that mods are loaded in order, such that all mods that are
    // depended on are loaded before their dependent mods.
    for (const auto& mod_name : calculate_loading_order())
    {
        ModInfo* mod = get_mod(mod_name);
        if (_mod_name_is_reserved(mod_name))
        {
            // TODO warn about reserved mod names.
            continue;
        }
        else
        {
            load_mod(*mod);
        }
        ELONA_LOG("Loaded mod " << mod->manifest.name);
    }

    lua_->get_event_manager().run_callbacks<EventKind::all_mods_loaded>();
    lua_->get_export_manager().register_all_exports();

    stage = ModLoadingStage::all_mods_loaded;
}

void ModManager::run_startup_script(const std::string& name)
{
    if (stage < ModLoadingStage::lua_libraries_loaded)
    {
        throw std::runtime_error("Lua libraries weren't loaded!");
    }
    if (this->mods.find(name) != this->mods.end())
    {
        throw std::runtime_error("Startup script was already run.");
    }

    ModInfo* script_mod = create_mod("script", none, true);

    lua_->get_state()->safe_script_file(
        filesystem::make_preferred_path_in_utf8(
            filesystem::dir::data() / "script"s / name),
        script_mod->env);

    // Bypass read-only metatable
    script_mod->env.raw_set("data", lua_->get_data_manager().get().storage);

    ELONA_LOG("Loaded startup script " << name);
    txt(i18n::s.get("core.locale.mod.loaded_script", name),
        Message::color{ColorIndex::purple});
    Message::instance().linebreak();
}

void ModManager::clear_mod_stores()
{
    for (auto&& pair : mods)
    {
        auto& mod = pair.second;
        lua_->get_state()->safe_script(
            R"(
local function clear(t)
    for key, _ in pairs(t) do
        t[key] = nil
    end
end
if Store then
    clear(Store.map_local)
    clear(Store.global)
end
)",
            mod->env);
    }
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
        ss << "Cannot assign to the global variable \"" << key.as<std::string>()
           << "\". ";
    }
    else
    {
        ss << "An attempt was made to assign to a global variable. ";
    }

    ss << "Please prefix the assignment with \"local\" to make it a local "
          "variable.";

    lua_State* L = ts;
    return luaL_error(L, ss.str().c_str());
}

void ModManager::bind_store(sol::state& lua, ModInfo& mod, sol::table& table)
{
    sol::table Store = lua.create_table();
    sol::table metatable = lua.create_table();

    // Bind Store.global and Store.map_local.
    metatable["global"] = mod.store_global;
    metatable["map_local"] = mod.store_local;

    // Prevent creating new variables in the Store table.
    metatable[sol::meta_function::new_index] = deny;
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
    table["_MOD_NAME"] = mod.manifest.name;

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

    mods[manifest.name] = std::move(info);
    return mods[manifest.name].get();
}

ModInfo* ModManager::create_mod(
    const std::string& name,
    optional<fs::path> mod_dir,
    bool readonly)
{
    ModManifest manifest;
    manifest.name = name;
    manifest.path = mod_dir;

    return create_mod(manifest, readonly);
}

std::vector<std::string> ModManager::calculate_loading_order()
{
    TopologicalSorter<std::string> sorter;

    for (const auto& pair : *this)
    {
        const auto& mod = pair.second;
        sorter.add(mod->manifest.name);

        for (const auto& dependency : mod->manifest.dependencies)
        {
            if (mods.find(dependency) == mods.end())
            {
                throw std::runtime_error(
                    "The dependency '" + dependency + "' of mod '" +
                    mod->manifest.name +
                    "' could not be found in the list of scanned mods.");
            }

            sorter.add_dependency(mod->manifest.name, dependency);
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
    if (stage < ModLoadingStage::lua_libraries_loaded)
    {
        throw std::runtime_error("Lua libraries weren't loaded!");
    }
    {
        auto val = mods.find(name);
        if (val != mods.end())
            throw std::runtime_error(
                "Mod "s + name + " was already initialized."s);
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
    auto val = mods.find(name);
    if (val == mods.end())
    {
        throw std::runtime_error("No such mod "s + name + "."s);
    }

    // Prevent outputting things in the test log on errors, but still
    // throw if the result is invalid so tests can catch it.
    auto ignore_handler = [](lua_State*, sol::protected_function_result pfr) {
        return pfr;
    };

    auto result = lua_->get_state()->safe_script(
        script, val->second->env, ignore_handler);

    if (!result.valid())
    {
        sol::error err = result;
        throw err;
    }
}

} // namespace lua
} // namespace elona

#include "mod_manager.hpp"
#include <map>
#include <sstream>
#include <vector>
#include "../character.hpp"
#include "../elona.hpp"
#include "../filesystem.hpp"
#include "../i18n.hpp"
#include "../log.hpp"
#include "../variables.hpp"
#include "event_manager.hpp"

namespace elona
{
namespace lua
{

namespace
{

bool is_alnum_only(const std::string& str)
{
    return find_if(
               str.begin(),
               str.end(),
               [](char c) { return !(isalnum(c) || (c == '_')); })
        == str.end();
}

} // namespace

mod_manager::mod_manager(lua_env* lua)
{
    lua_ = lua;
}


void mod_manager::load_mods(const fs::path& mod_dir)
{
    if (stage != mod_loading_stage_t::not_started)
    {
        throw std::runtime_error("Mods have already been loaded.");
    }

    scan_all_mods(mod_dir);
    load_lua_support_libraries();
    load_scanned_mods();
}

void mod_manager::load_mods(
    const fs::path& mod_dir,
    const fs::path& additional_mod_path)
{
    if (stage != mod_loading_stage_t::not_started)
    {
        throw std::runtime_error("Mods have already been loaded.");
    }

    scan_all_mods(mod_dir);
    scan_mod(additional_mod_path);
    load_lua_support_libraries();
    load_scanned_mods();
}


void report_error(sol::error err)
{
    std::string what = err.what();
    ELONA_LOG(what);
}


void mod_manager::clear_map_local_data()
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


void mod_manager::load_mod(mod_info& mod)
{
    setup_and_lock_mod_globals(mod);

    // Skip initializing mods not created from files, because the
    // string passed to load_mod_from_script acts as the
    // initialization script.
    if (mod.path)
    {
        auto result = lua_->get_state()->safe_script_file(
            filesystem::make_preferred_path_in_utf8(*mod.path / u8"init.lua"s),
            mod.env);

        // Add the API table returned by the mod's init.lua, if one
        // was returned.
        if (result.valid())
        {
            sol::optional<sol::object> object = result.get<sol::object>();
            if (object && object->is<sol::table>())
            {
                sol::table api_table = object->as<sol::table>();
                lua_->get_api_manager().add_api(mod.name, api_table);
            }
        }
        else
        {
            sol::error err = result;
            report_error(err);
            throw std::runtime_error("Failed initializing mod "s + mod.name);
        }
    }
}

void mod_manager::scan_mod(const fs::path& mod_dir)
{
    const std::string mod_name = mod_dir.filename().string();
    ELONA_LOG("Found mod " << mod_name);

    if (!is_alnum_only(mod_name))
    {
        throw std::runtime_error(
            "Mod name \"" + mod_name
            + "\" must contain alphanumeric characters only.");
    }
    if (mod_name == "script")
    {
        throw std::runtime_error("\"script\" is a reserved mod name.");
    }

    std::unique_ptr<mod_info> info =
        std::make_unique<mod_info>(mod_name, mod_dir, lua_->get_state());
    this->mods.emplace(mod_name, std::move(info));
}

void mod_manager::scan_all_mods(const fs::path& mods_dir)
{
    if (stage != mod_loading_stage_t::not_started
        && stage != mod_loading_stage_t::scan_finished)
    {
        throw std::runtime_error("Mods have already been scanned!");
    }

    const std::string init_script = "init.lua";

    // TODO: [dependency management] order mods and always load core first.
    for (const auto& entry :
         filesystem::dir_entries{mods_dir, filesystem::dir_entries::type::dir})
    {
        if (fs::exists(entry.path() / init_script))
        {
            scan_mod(entry.path());
        }
    }
    stage = mod_loading_stage_t::scan_finished;
}

void mod_manager::load_lua_support_libraries()
{
    if (stage == mod_loading_stage_t::not_started)
    {
        throw std::runtime_error("Mods haven't been scanned yet!");
    }

    // Add special API tables from data/lua to the core mod. The core
    // mod's API table will be modified in-place by the Lua API code
    // under data/lua.
    lua_->get_api_manager().load_lua_support_libraries(*lua_);

    stage = mod_loading_stage_t::lua_libraries_loaded;
}

void mod_manager::load_scanned_mods()
{
    if (stage != mod_loading_stage_t::lua_libraries_loaded)
    {
        throw std::runtime_error("Lua libraries weren't loaded!");
    }
    for (auto& pair : this->mods)
    {
        auto& mod = pair.second;
        if (mod->name == "script")
        {
            // TODO warn about reserved mod names.
            continue;
        }
        else
        {
            load_mod(*mod);
        }
        ELONA_LOG("Loaded mod " << mod->name);
    }

    lua_->get_event_manager().run_callbacks<event_kind_t::all_mods_loaded>();
    lua_->get_export_manager().register_all_exports();

    stage = mod_loading_stage_t::all_mods_loaded;
}

void mod_manager::run_startup_script(const std::string& name)
{
    if (stage < mod_loading_stage_t::lua_libraries_loaded)
    {
        throw std::runtime_error("Lua libraries weren't loaded!");
    }
    if (this->mods.find(name) != this->mods.end())
    {
        throw std::runtime_error("Startup script was already run.");
    }

    std::unique_ptr<mod_info> script_mod =
        std::make_unique<mod_info>("script", none, lua_->get_state());
    setup_and_lock_mod_globals(*script_mod);

    lua_->get_state()->safe_script_file(
        filesystem::make_preferred_path_in_utf8(
            filesystem::dir::data() / "script"s / name),
        script_mod->env);

    ELONA_LOG("Loaded startup script " << name);
    txtef(8);
    txt(i18n::s.get("core.locale.mod.loaded_script", name));
    txtnew();

    this->mods.emplace("script", std::move(script_mod));
}

void mod_manager::clear_mod_stores()
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

void mod_manager::bind_store(sol::state& lua, mod_info& mod, sol::table& table)
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

void mod_manager::setup_mod_globals(mod_info& mod, sol::table& table)
{
    // Create the globals "Elona" and "Store" for this mod's
    // environment.
    bind_store(*lua_->get_state(), mod, table);
    table["Elona"] = lua_->get_api_manager().bind(*lua_); // TODO move elsewhere
    table["_MOD_NAME"] = mod.name;

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

void mod_manager::setup_and_lock_mod_globals(mod_info& mod)
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


// For testing use
void mod_manager::load_mod_from_script(
    const std::string& name,
    const std::string& script,
    bool readonly)
{
    if (stage < mod_loading_stage_t::lua_libraries_loaded)
    {
        throw std::runtime_error("Lua libraries weren't loaded!");
    }
    {
        auto val = mods.find(name);
        if (val != mods.end())
            throw std::runtime_error(
                "Mod "s + name + " was already initialized."s);
    }

    std::unique_ptr<mod_info> info =
        std::make_unique<mod_info>(name, none, lua_->get_state());

    if (readonly)
    {
        setup_and_lock_mod_globals(*info);
    }
    else
    {
        // Set the globals directly on the environment table for testing use.
        setup_mod_globals(*info, info->env);
    }

    // Run the provided script string.
    auto result = lua_->get_state()->safe_script(script, info->env);

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

    this->mods[name] = std::move(info);
}

void mod_manager::run_in_mod(const std::string& name, const std::string& script)
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

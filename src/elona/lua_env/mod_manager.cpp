#include "mod_manager.hpp"

#include <map>
#include <sstream>
#include <unordered_set>
#include <vector>

#include "../../util/range.hpp"
#include "../character.hpp"
#include "../config.hpp"
#include "../elona.hpp"
#include "../filesystem.hpp"
#include "../i18n.hpp"
#include "../log.hpp"
#include "../message.hpp"
#include "../variables.hpp"
#include "api_manager.hpp"
#include "data_manager.hpp"
#include "event_manager.hpp"
#include "lua_event/base_event.hpp"



namespace elona
{
namespace lua
{

namespace
{

bool _is_alnum_only(const std::string& str)
{
    return range::all_of(str, [](char c) {
        return ('a' <= c && c <= 'z') || ('0' <= c && c <= '9') || c == '_';
    });
}



// Callback to be called in Lua for preventing write access to unknown
// globals.
int deny_new_fields(
    [[maybe_unused]] sol::table table,
    sol::object key,
    [[maybe_unused]] sol::object value,
    sol::this_state ts)
{
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



sol::table create_store_table(sol::state& L)
{
    auto store_tbl = L.create_table();

    store_tbl["global"] = L.create_table();
    store_tbl["map"] = L.create_table();

    auto mt = L.create_table();
    mt[sol::meta_function::new_index] = deny_new_fields;
    store_tbl[sol::metatable_key] = mt;

    return store_tbl;
}



sol::table create_mod_table(sol::state& L)
{
    auto mod_tbl = L.create_table();
    auto mt = L.create_table();

    mt["store"] = create_store_table(L);

    mt[sol::meta_function::new_index] = deny_new_fields;
    mt[sol::meta_function::index] = mt;
    mod_tbl[sol::metatable_key] = mt;
    return mod_tbl;
}



/***
 * Whitelists functions that are safe for usage in user-written scripts.
 */
void setup_sandbox(sol::state& state, sol::table table)
{
    state["prelude"]["import"](table);
}



void report_error(sol::error err)
{
    std::string what = err.what();
    ELONA_ERROR("Mod: " + what);
}

} // namespace



ModManager::ModManager(LuaEnv& lua)
    : LuaSubmodule(lua)
{
}



std::vector<ModManifest> ModManager::installed_mods() const
{
    // Traverse `mod` directory, and gather the latest versions.
    std::unordered_map<std::string, std::pair<semver::Version, fs::path>>
        mod_dirs;
    for (const auto& dir : all_mod_dirs(filesystem::dirs::mod()))
    {
        // Get mod ID and version from folder name.
        const auto dir_name = dir.filename().to_u8string();
        std::string id;
        std::string version_str;
        std::tie(id, version_str) = strutil::split_on_string(dir_name, "-");
        const auto version = semver::Version::parse(version_str).right();

        const auto itr = mod_dirs.find(id);
        if (itr == std::end(mod_dirs))
        {
            mod_dirs[id] = std::make_pair(version, dir);
        }
        else
        {
            // Update the table only if it is the latest one.
            if (itr->second.first < version)
            {
                mod_dirs[id] = std::make_pair(version, dir);
            }
        }
    }

    // Load each manifest.
    std::vector<ModManifest> ret;
    for (const auto& pair : mod_dirs)
    {
        const auto& dir = pair.second.second;
        ModManifest manifest = ModManifest::load(dir / "mod.json");
        ret.emplace_back(manifest);
    }
    return ret;
}



void ModManager::toggle_mod(
    const std::string& id,
    const semver::Version& version)
{
    auto mod_list = ModList::from_file(filesystem::files::mod_list());

    if (const auto current_version = get_enabled_version(id))
    {
        // Disable
        assert(can_disable_mod(id));
        assert(*current_version == version);
        ELONA_LOG("Lua.mod: disable mod " + id + "-" + version.to_string());

        mod_list.mods().erase(id);
    }
    else
    {
        // Enable
        ELONA_LOG("Lua.mod: enable mod " + id + "-" + version.to_string());

        mod_list.mods().emplace(
            id, semver::VersionRequirement::from_version(version));
    }

    mod_list.save(filesystem::files::mod_list());
}



void ModManager::load_mods(const ResolvedModList& resolved_mod_list)
{
    _mod_versions = resolved_mod_list.mod_versions();
    _sorted_mods = resolved_mod_list.sorted_mods();

    create_all_mod_env(resolved_mod_list.mod_versions());

    // Ensure that mods are loaded in order, such that all mods that are
    // depended on are loaded before their dependent mods.
    for (const auto& id : sorted_mods())
    {
        auto& mod = _mods.at(id);
        init_mod(mod);
        ELONA_LOG("Lua.mod: Loaded mod " + mod.manifest.id);
    }

    lua().get_event_manager().trigger(BaseEvent("core.all_mods_loaded"));
}



void ModManager::init_mod(ModEnv& mod)
{
    if (!mod.manifest.path)
        return;

    const auto script_path = *mod.manifest.path / "init.lua";
    if (!fs::exists(script_path))
        return;

    auto result = safe_script_file(script_path, mod.env);
    if (!result.valid())
    {
        sol::error err = result;
        report_error(err);
        throw std::runtime_error("Failed initializing mod "s + mod.manifest.id);
    }

    if (sol::optional<sol::table> exports = result)
    {
        lua().get_api_manager().register_api(mod.manifest.id, *exports);
    }
}



void ModManager::run_startup_script(const fs::path& script_filename)
{
    auto& script_mod = create_mod_env_from_script("script");

    safe_script_file(
        filesystem::dirs::user_script() / script_filename, script_mod.env);

    ELONA_LOG(
        "Lua.mod: loaded startup script " + script_filename.to_u8string());
    txt(i18n::s.get("core.mod.loaded_script", script_filename.to_u8string()),
        Message::color{ColorIndex::purple});
    Message::instance().linebreak();
}



void ModManager::clear_map_local_stores()
{
    for (auto&& pair : mods())
    {
        auto& mod = pair.second;
        mod.env.get<sol::table>(std::tie("mod", "store"))
            .raw_set("map", lua_state()->create_table());
    }
}



void ModManager::clear_global_stores()
{
    for (auto&& pair : mods())
    {
        auto& mod = pair.second;
        mod.env.get<sol::table>(std::tie("mod", "store"))
            .raw_set("global", lua_state()->create_table());
    }
}



void ModManager::clear_mod_stores()
{
    clear_map_local_stores();
    clear_global_stores();
}



void ModManager::load_testing_mod_from_script(
    const std::string& id,
    const std::string& script)
{
    auto& mod = create_mod_env_from_script(id);

    auto result = safe_script(script, mod.env);
    if (!result.valid())
    {
        sol::error err = result;
        report_error(err);
        throw std::runtime_error("Failed initializing mod "s + mod.manifest.id);
    }

    _mod_versions.emplace(mod.manifest.id, mod.manifest.version);
    // Testing mods are always at the end.
    _sorted_mods.push_back(mod.manifest.id);
}



void ModManager::load_testing_mod_from_file(const fs::path& mod_dir)
{
    auto& mod = create_mod_env_from_manifest_file(mod_dir / "mod.json");

    init_mod(mod);

    _mod_versions.emplace(mod.manifest.id, mod.manifest.version);
    // Testing mods are always at the end.
    _sorted_mods.push_back(mod.manifest.id);
}



void ModManager::run_in_mod(const std::string& id, const std::string& script)
{
    auto mod = get_mod(id);
    if (!mod)
    {
        throw std::runtime_error("No such mod "s + id + "."s);
    }

    // Prevent outputting things in the test log on errors, but still
    // throw if the result is invalid so tests can catch it.
    const auto ignore_handler =
        [](lua_State*, sol::protected_function_result pfr) { return pfr; };

    auto result = safe_script(script, mod->env, ignore_handler);

    if (!result.valid())
    {
        sol::error err = result;
        throw err;
    }
}



void ModManager::create_new_mod(const std::string& new_mod_id)
{
    const auto new_mod_version = semver::Version{0, 1, 0};
    const auto mod_dir = filesystem::dirs::for_mod(new_mod_id, new_mod_version);

    // Make mod's directory.
    fs::create_directory(mod_dir);

    // Edit the new mod's manifest file.
    auto new_mod_manifest = ModManifest::load(mod_dir / "mod.json");
    new_mod_manifest.id = new_mod_id;
    new_mod_manifest.version = new_mod_version;
    new_mod_manifest.name.default_text = new_mod_id;
    new_mod_manifest.save();
}



bool ModManager::exists(const std::string& mod_id)
{
    for (const auto& dir : all_mod_dirs(filesystem::dirs::mod()))
    {
        const auto dir_name = dir.filename().to_u8string();
        const auto [id, _version_str] = strutil::split_on_string(dir_name, "-");
        (void)_version_str;
        if (mod_id == id)
        {
            return true;
        }
    }
    return false;
}



fs::path ModManager::resolve_path_for_mod(const std::string& path)
{
    // TODO: standardize mod naming convention.
    std::regex mod_id_regex("^<([a-zA-Z0-9_]+)>/(.*)");
    std::smatch match;
    std::string mod_id, rest;

    if (std::regex_match(path, match, mod_id_regex) && match.size() == 3)
    {
        mod_id = match.str(1);
        rest = match.str(2);
    }
    else
    {
        throw std::runtime_error("Invalid filepath syntax: " + path);
    }

    rest = strutil::replace(rest, "<LANGUAGE>", g_config.language());

    if (mod_id == "_builtin_")
    {
        return filesystem::dirs::exe() / fs::u8path(rest);
    }
    else
    {
        if (const auto version = get_enabled_version(mod_id))
        {
            return filesystem::dirs::for_mod(mod_id, *version) /
                fs::u8path(rest);
        }
        else
        {
            throw std::runtime_error{
                "Mod '" + mod_id + "' is disabled: " + path};
        }
    }
}



void ModManager::create_all_mod_env(
    const ResolvedModList::ModVersionMap& mod_versions)
{
    for (const auto& pair : mod_versions)
    {
        const auto& id = pair.first;
        const auto& version = pair.second;

        create_mod_env_from_manifest_file(
            filesystem::dirs::for_mod(id, version) / "mod.json");
    }
}



ModEnv& ModManager::create_mod_env_from_manifest_file(
    const fs::path& manifest_filepath)
{
    const auto manifest = ModManifest::load(manifest_filepath);
    return create_mod_env_manifest(manifest);
}



ModEnv& ModManager::create_mod_env_from_script(const std::string& id)
{
    ModManifest manifest;
    manifest.id = id;
    manifest.version = semver::Version{0, 1, 0};
    return create_mod_env_manifest(manifest);
}



ModEnv& ModManager::create_mod_env_manifest(const ModManifest& manifest)
{
    ELONA_LOG("Lua.mod: found mod " + manifest.id);

    const auto emplace_result = _mods.emplace(
        std::piecewise_construct,
        std::make_tuple(manifest.id),
        std::make_tuple(manifest, sol::environment{*lua_state(), sol::create}));
    assert(emplace_result.second); // The element was newly inserted just now.
    auto& mod = emplace_result.first->second;
    setup_mod_globals(mod);
    return mod;
}



void ModManager::setup_mod_globals(ModEnv& mod)
{
    auto& L = *lua_state();

    auto mt = L.create_table();

    mt["mod"] = create_mod_table(L);

    lua().get_api_manager().bind(lua(), mt);
    mt["_MOD_ID"] = mod.manifest.id;

    // Add a list of whitelisted standard library functions to the
    // environment.
    setup_sandbox(*lua_state(), mt);

    // Add a custom version of "require" for use within mods. (Not
    // added for scripts/console environment)
    if (mod.chunk_cache)
    {
        auto state = lua_state();
        auto& chunk_cache = *mod.chunk_cache;
        mt["require"] = [state, &chunk_cache](
                            const std::string& name,
                            sol::this_environment this_env) {
            sol::environment env = this_env;
            return chunk_cache.require(name, env, *state);
        };
    }

    mt[sol::meta_function::new_index] = deny_new_fields;
    mt[sol::meta_function::index] = mt;
    mod.env[sol::metatable_key] = mt;
}



bool is_valid_mod_id(const std::string& id)
{
    return !id.empty() && _is_alnum_only(id) &&
        fs::is_portable_path(fs::u8path(id)) && !is_reserved_mod_id(id);
}



bool is_reserved_mod_id(const std::string& id)
{
    return id == "script" || id == "_builtin_";
}

} // namespace lua
} // namespace elona

#include "lua_env.hpp"
#include "../character.hpp"
#include "../config.hpp"
#include "../elona.hpp"
#include "../filesystem.hpp"
#include "../log.hpp"
#include "../variables.hpp"
#include "event_manager.hpp"
#include <vector>
#include <map>

namespace elona
{
namespace lua
{

lua_env lua;

// TODO wrap all table editing methods in their own functions
// TODO make everything less messy
// TODO move api to separate source file
// TODO make things immutable where they need to be

lua_env::lua_env()
{
    lua = std::make_shared<sol::state>();
    lua->open_libraries(sol::lib::base,
                              sol::lib::package,
                              sol::lib::table,
                              sol::lib::debug,
                              sol::lib::string,
                              sol::lib::math);

    // Create dummy Store table to prevent crashes on access from
    // state outside of an environment
    lua->create_named_table("Store");

    // Make sure the API environment is initialized first so any
    // dependent managers can add new internal C++ methods to it (like
    // the event manager registering Elona.Event)
    api_mgr = std::make_unique<api_manager>(this);

    event_mgr = std::make_unique<event_manager>(this);
    event_manager::init(*this);

    handle_mgr = std::make_unique<handle_manager>(this);
}

api_manager& lua_env::get_api_manager()
{
    return *api_mgr;
}

event_manager& lua_env::get_event_manager()
{
    return *event_mgr;
}

handle_manager& lua_env::get_handle_manager()
{
    return *handle_mgr;
}

void report_error(sol::error err)
{
	std::string what = err.what();
	ELONA_LOG(what);
}


// Handlers for existing characters/items being loaded from save archives
void lua_env::on_chara_loaded(character& chara)
{
    if(chara.state == 0)
    {
        return;
    }
    handle_mgr->create_chara_handle(chara);
}

void lua_env::on_item_loaded(item& item)
{
    if(item.number == 0)
    {
        return;
    }
    handle_mgr->create_item_handle(item);
}


// Handlers for characters/items being unloaded when another save archive is loaded
void lua_env::on_chara_unloaded(character& chara)
{
    if(chara.state == 0)
    {
        return;
    }
    handle_mgr->remove_chara_handle(chara);
}

void lua_env::on_item_unloaded(item& item)
{
    if(item.number == 0)
    {
        return;
    }
    handle_mgr->remove_item_handle(item);
}


// Handlers for brand-new instances of characters/objects being created
void lua_env::on_chara_creation(character& chara)
{
    assert(chara.state != 0);
    handle_mgr->create_chara_handle(chara);

    auto handle = handle_mgr->get_chara_handle(chara);
    assert(handle != sol::lua_nil);
    event_mgr->run_callbacks<event_kind_t::character_created>(handle);
}

void lua_env::on_item_creation(item& item)
{
    assert(item.number != 0);
    handle_mgr->create_item_handle(item);

    auto handle = handle_mgr->get_item_handle(item);
    assert(handle != sol::lua_nil);
    event_mgr->run_callbacks<event_kind_t::item_created>(handle);
}


// Handlers for invalidation of characters/items (character death, item count is 0)
void lua_env::on_chara_removal(character& chara)
{
    auto handle = handle_mgr->get_chara_handle(chara);
    event_mgr->run_callbacks<event_kind_t::character_removed>(handle);

    handle_mgr->remove_chara_handle(chara);
}

void lua_env::on_item_removal(item& item)
{
    auto handle = handle_mgr->get_item_handle(item);
    event_mgr->run_callbacks<event_kind_t::item_removed>(handle);

    handle_mgr->remove_item_handle(item);
}

void lua_env::load_mod(const fs::path& path, mod_info& mod)
{
    // create character/item/map/global tables
    // run various mod loading stages (like defining custom fields for all prototypes in the game?)
    // evaluate init.lua to load defines
    auto result = this->lua->safe_script_file(filesystem::make_preferred_path_in_utf8(path / mod.name / "init.lua"), mod.env);
    if (!result.valid())
    {
        sol::error err = result;
        report_error(err);
        throw new std::runtime_error("Failed initializing mod "s + mod.name);
    }
    // determine mod overrides inside .json files
    // merge overrides, new things, and locale configs into global database
    // add reference to global API table as Elona so the mod can use it
}

void lua_env::scan_all_mods(const fs::path& mods_dir)
{
    if(stage != mod_loading_stage_t::not_started)
    {
        throw new std::runtime_error("Mods have already been scanned!");
    }

    const std::string init_script = "init.lua";

    // TODO: [dependency management] order mods and always load core first.
    for (const auto& entry : filesystem::dir_entries{
             mods_dir, filesystem::dir_entries::type::dir})
    {
        if(fs::exists(entry.path() / init_script))
        {
            const std::string mod_name = entry.path().filename().string();
            ELONA_LOG("Found mod " << mod_name);

            if(mod_name == "script")
            {
                throw new std::runtime_error("\"script\" is a reserved mod name.");
            }

            std::unique_ptr<mod_info> info = std::make_unique<mod_info>(mod_name, get_state());
            api_mgr->bind(*this, *info);
            this->mods.emplace(mod_name, std::move(info));
        }
    }
    stage = mod_loading_stage_t::scan_finished;
}

void lua_env::load_core_mod(const fs::path& mods_dir)
{
    if(stage != mod_loading_stage_t::scan_finished)
    {
        throw new std::runtime_error("Mods haven't been scanned yet!");
    }

    auto val = this->mods.find("core");
    if (val == this->mods.end())
    {
        throw new std::runtime_error("Core mod was not found. Does \"mods/core\" exist?");
    }

    // Load the core mod before any others, because there is a need
    // for things on the Lua side to be made read-only after the core
    // mod is loaded.
    api_mgr->load_core(*this, mods_dir);
    stage = mod_loading_stage_t::core_mod_loaded;

    // lua->safe_script(R"(Elona = Elona.ReadOnly.make_read_only(Elona))");

    stage = mod_loading_stage_t::core_mod_loaded;
}

void lua_env::load_all_mods(const fs::path& mods_dir)
{
    if(stage != mod_loading_stage_t::core_mod_loaded)
    {
        throw new std::runtime_error("Core mod wasn't loaded!");
    }
    for (auto& pair : this->mods)
    {
        auto& mod = pair.second;
        if(mod->name == "core")
        {
            continue;
        }
        else
        {
            load_mod(mods_dir, *mod);
        }
        ELONA_LOG("Loaded mod " << mod->name);
    }

    stage = mod_loading_stage_t::all_mods_loaded;
}

void lua_env::run_startup_script(const std::string& name)
{
    if(stage < mod_loading_stage_t::core_mod_loaded)
    {
        throw new std::runtime_error("Core mod wasn't loaded!");
    }
    if(this->mods.find(name) != this->mods.end())
    {
        throw new std::runtime_error("Startup script was already run.");
    }

    std::unique_ptr<mod_info> script_mod = std::make_unique<mod_info>("script", get_state());
    api_mgr->bind(*this, *script_mod);

    lua->safe_script_file(filesystem::make_preferred_path_in_utf8(
                              filesystem::dir::data() / "script"s / name),
        script_mod->env);

    ELONA_LOG("Loaded startup script " << name);

    this->mods.emplace("script", std::move(script_mod));
}

void lua_env::clear_mod_stores()
{
    for (auto&& pair : mods)
    {
        auto& mod = pair.second;
        mod->store->clear();
    }
}


// For testing use

void lua_env::clear()
{
    for(int i = 0; i < 5480; i++)
    {
        if(inv[i].number != 0)
        {
            on_item_unloaded(inv[i]);
        }
    }

    for(int i = 0; i < ELONA_MAX_CHARACTERS; i++)
    {
        if(cdata[i].state != 0)
        {
            on_chara_unloaded(cdata[i]);
        }
    }
    clear_mod_stores();
    mods.clear();
    lua->collect_garbage();
    stage = mod_loading_stage_t::not_started;
}

// TODO expects mods to use unique names. Figure out a way to clear
// everything Lua related easily and safely.
void lua_env::load_mod_from_script(const std::string& name, const std::string& script)
{
    if(stage < mod_loading_stage_t::core_mod_loaded)
    {
        throw new std::runtime_error("Core mod wasn't loaded!");
    }
    {
        auto val = mods.find(name);
        if(val != mods.end())
            throw new std::runtime_error("Mod "s + name + " was already initialized."s);
    }

    std::unique_ptr<mod_info> info = std::make_unique<mod_info>(name, get_state());
    api_mgr->bind(*this, *info);

    auto result = this->lua->safe_script(script, info->env);
    if (!result.valid())
    {
        sol::error err = result;
        report_error(err);
        throw new std::runtime_error("Failed initializing mod "s + info->name);
    }

    this->mods.emplace(name, std::move(info));
}

void lua_env::run_in_mod(const std::string& name, const std::string& script)
{
    auto val = mods.find(name);
    if(val == mods.end())
        throw new std::runtime_error("No such mod "s + name + "."s);
    this->lua->script(script, val->second->env);
}

} // namespace lua
} // namespace elona

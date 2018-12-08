#include "handle_manager.hpp"
#include <cassert>
#include <set>
#include "../character.hpp"
#include "../config/config.hpp"
#include "../item.hpp"
#include "../log.hpp"
#include "../macro.hpp"
#include "lua_env.hpp"

namespace elona
{
namespace lua
{

HandleManager::HandleManager(LuaEnv* lua_)
{
    lua = lua_;
    lua->get_state()->set("_IS_TEST", Config::instance().is_test);
    handle_env = sol::environment(
        *(lua->get_state()), sol::create, lua->get_state()->globals());

    // Load the Lua chunk for storing handles.
    lua->get_state()->safe_script(R"(Handle = require "handle")", handle_env);

    bind(*lua);
}

void HandleManager::bind(LuaEnv& lua)
{
    sol::table core = lua.get_api_manager().get_core_api_table();
    sol::table Chara = core["Chara"];
    sol::table Item = core["Item"];

    // Add iterating methods implemented in Lua.
    // TODO: See if this can be migrated to Sol's iteration scheme
    // (last time I tried it didn't work because of "not a valid
    // container" errors)
    Chara.set("iter", handle_env["Handle"]["iter_charas"]);
    Item.set("iter", handle_env["Handle"]["iter_items"]);
}

void HandleManager::create_chara_handle(const Character& chara)
{
    if (chara.state() == Character::State::empty)
    {
        return;
    }

    create_handle(chara);
}

void HandleManager::create_item_handle(const Item& item)
{
    if (item.number() == 0)
    {
        return;
    }

    create_handle(item);
}

void HandleManager::remove_chara_handle(const Character& chara)
{
    remove_handle(chara);
}

void HandleManager::remove_item_handle(const Item& item)
{
    remove_handle(item);
}


// Handlers for brand-new instances of characters/objects being created
void HandleManager::create_chara_handle_run_callbacks(const Character& chara)
{
    assert(chara.state() != Character::State::empty);
    create_chara_handle(chara);

    auto handle = get_handle(chara);
    assert(handle != sol::lua_nil);
    lua->get_event_manager().run_callbacks<EventKind::character_created>(
        handle);
}

void HandleManager::create_item_handle_run_callbacks(const Item& item)
{
    assert(item.number() != 0);
    create_item_handle(item);

    auto handle = get_handle(item);
    assert(handle != sol::lua_nil);
    lua->get_event_manager().run_callbacks<EventKind::item_created>(handle);
}


// Handlers for invalidation of characters/items (character death, item count is
// 0)
void HandleManager::remove_chara_handle_run_callbacks(const Character& chara)
{
    auto handle = get_handle(chara);
    if (handle == sol::lua_nil)
    {
        return;
    }

    // If the handle already exists, the object it references has to be invalid.
    // Otherwise the handle would be mistakenly invalidated when the thing it
    // points to is still valid.
    int index = handle["__index"];
    UNUSED(index);
    assert(cdata[index].state() != Character::State::alive);

    lua->get_event_manager().run_callbacks<EventKind::character_removed>(
        handle);
    remove_chara_handle(chara);
}

void HandleManager::remove_item_handle_run_callbacks(const Item& item)
{
    auto handle = get_handle(item);
    if (handle == sol::lua_nil)
    {
        return;
    }

    // If the handle already exists, the object it references has to be invalid.
    // Otherwise the handle would be mistakenly invalidated when the thing it
    // points to is still valid.
    int index = handle["__index"];
    UNUSED(index);
    assert(inv[index].number() == 0);

    lua->get_event_manager().run_callbacks<EventKind::item_removed>(handle);
    remove_item_handle(item);
}


void HandleManager::clear_all_handles()
{
    handle_env["Handle"]["clear"]();
}

// Player/party handles are global, so don't clear them when e.g. changing maps
void HandleManager::clear_map_local_handles()
{
    for (int i = ELONA_MAX_PARTY_CHARACTERS; i < ELONA_MAX_CHARACTERS; i++)
    {
        remove_chara_handle(cdata[i]);
    }
    for (int i = 1320; i < 5480; i++)
    {
        remove_item_handle(inv[i]);
    }
}

} // namespace lua
} // namespace elona

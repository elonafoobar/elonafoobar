#include "handle_manager.hpp"
#include <cassert>
#include <set>
#include "../character.hpp"
#include "../config.hpp"
#include "../item.hpp"
#include "../log.hpp"
#include "../macro.hpp"
#include "api_manager.hpp"
#include "event_manager.hpp"
#include "lua_env.hpp"
#include "lua_event/character_instance_event.hpp"
#include "lua_event/item_instance_event.hpp"



namespace elona
{
namespace lua
{

HandleManager::HandleManager(LuaEnv& lua)
    : LuaSubmodule(lua)
{
    lua_state()->set("_IS_TEST", g_config.is_test());

    // Load the Lua chunk for storing handles.
    safe_script(R"(Handle = require("handle"))");

    bind(lua);
}



void HandleManager::bind(LuaEnv& lua)
{
    sol::table game = lua.get_api_manager().get_game_api_table();
    sol::table Chara = game["Chara"];
    sol::table Item = game["Item"];

    // Add iterating methods implemented in Lua.
    // TODO: See if this can be migrated to Sol's iteration scheme
    // (last time I tried it didn't work because of "not a valid
    // container" errors)
    Chara.set("iter", env()["Handle"]["iter_charas"]);
    Item.set("iter", env()["Handle"]["iter_items"]);
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
    UNUSED(handle);
    assert(handle != sol::lua_nil);
    lua().get_event_manager().trigger(
        lua::CharacterInstanceEvent("core.character_created", chara));
}



void HandleManager::create_item_handle_run_callbacks(const Item& item)
{
    assert(item.number() != 0);
    create_item_handle(item);

    auto handle = get_handle(item);
    UNUSED(handle);
    assert(handle != sol::lua_nil);
    lua().get_event_manager().trigger(
        lua::ItemInstanceEvent("core.item_created", item));
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

    lua().get_event_manager().trigger(
        lua::CharacterInstanceEvent("core.character_removed", chara));
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

    lua().get_event_manager().trigger(
        lua::ItemInstanceEvent("core.item_removed", item));
    remove_item_handle(item);
}



void HandleManager::clear_all_handles()
{
    env()["Handle"]["clear"]();
}



// Player/party handles are global, so don't clear them when e.g. changing maps
void HandleManager::clear_map_local_handles()
{
    for (int i = ELONA_MAX_PARTY_CHARACTERS; i < ELONA_MAX_CHARACTERS; i++)
    {
        remove_chara_handle(cdata[i]);
    }
    for (auto&& item : inv.map_local())
    {
        remove_item_handle(item);
    }
}

} // namespace lua
} // namespace elona

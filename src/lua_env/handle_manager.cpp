#include "handle_manager.hpp"
#include <cassert>
#include <set>
#include "../character.hpp"
#include "../config.hpp"
#include "../item.hpp"
#include "../log.hpp"
#include "lua_env.hpp"

namespace elona
{
namespace lua
{

handle_manager::handle_manager(lua_env* lua_)
{
    lua = lua_;
    lua->get_state()->set("_IS_TEST", config::instance().is_test);
    handle_env = sol::environment(
        *(lua->get_state()), sol::create, lua->get_state()->globals());

    // Load the Lua chunk for storing handles.
    lua->get_state()->safe_script(R"(Handle = require "handle")", handle_env);

    bind(*lua);
}

void handle_manager::bind(lua_env& lua)
{
    sol::table core = lua.get_api_manager().get_api_table();
    sol::table Chara = core["Chara"];
    sol::table Item = core["Item"];

    // Add iterating methods implemented in Lua.
    // TODO: See if this can be migrated to Sol's iteration scheme
    // (last time I tried it didn't work because of "not a valid
    // container" errors)
    Chara.set("iter", handle_env["Handle"]["iter_charas"]);
    Item.set("iter", handle_env["Handle"]["iter_items"]);
}

void handle_manager::create_chara_handle(character& chara)
{
    if (chara.state == 0)
    {
        return;
    }

    create_handle(chara);
}

void handle_manager::create_item_handle(item& item)
{
    if (item.number == 0)
    {
        return;
    }

    create_handle(item);
}

void handle_manager::remove_chara_handle(character& chara)
{
    if (chara.state == 0)
    {
        return;
    }

    // TODO should chara.state == 0 mean the handle is invalid?
    // Some characters can die and respawn again.
    remove_handle(chara);
}

void handle_manager::remove_item_handle(item& item)
{
    if (item.number == 0)
    {
        return;
    }

    // item.number is set to zero often, but it doesn't always seem to
    // signify whether or not the item was deleted.
    remove_handle(item);
}


// Handlers for brand-new instances of characters/objects being created
void handle_manager::create_chara_handle_run_callbacks(character& chara)
{
    assert(chara.state != 0);
    create_chara_handle(chara);

    auto handle = get_handle(chara);
    assert(handle != sol::lua_nil);
    lua->get_event_manager().run_callbacks<event_kind_t::character_created>(
        handle);
}

void handle_manager::create_item_handle_run_callbacks(item& item)
{
    assert(item.number != 0);
    create_item_handle(item);

    auto handle = get_handle(item);
    assert(handle != sol::lua_nil);
    lua->get_event_manager().run_callbacks<event_kind_t::item_created>(handle);
}


// Handlers for invalidation of characters/items (character death, item count is
// 0)
void handle_manager::remove_chara_handle_run_callbacks(character& chara)
{
    auto handle = get_handle(chara);
    lua->get_event_manager().run_callbacks<event_kind_t::character_removed>(
        handle);
    remove_chara_handle(chara);
}

void handle_manager::remove_item_handle_run_callbacks(item& item)
{
    auto handle = get_handle(item);
    lua->get_event_manager().run_callbacks<event_kind_t::item_removed>(handle);
    remove_item_handle(item);
}


void handle_manager::clear_all_handles()
{
    handles.clear();
    handle_env["Handle"]["clear"]();
}

// Player/party handles are global, so don't clear them when e.g. changing maps
void handle_manager::clear_map_local_handles()
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

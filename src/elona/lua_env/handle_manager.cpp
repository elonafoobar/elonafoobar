#include "handle_manager.hpp"

#include <cassert>

#include <set>

#include "../character.hpp"
#include "../config.hpp"
#include "../log.hpp"
#include "api_manager.hpp"
#include "event_manager.hpp"
#include "lua_env.hpp"
#include "lua_event/character_instance_event.hpp"



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
}



void HandleManager::create_chara_handle(Character& chara)
{
    if (chara.state() == Character::State::empty)
    {
        return;
    }

    create_handle(chara);
}



void HandleManager::remove_chara_handle(Character& chara)
{
    remove_handle(chara);
}



// Handlers for brand-new instances of characters/objects being created
void HandleManager::create_chara_handle_run_callbacks(Character& chara)
{
    assert(chara.state() != Character::State::empty);
    create_chara_handle(chara);

    auto handle = get_handle(chara);
    (void)handle;
    assert(handle != sol::lua_nil);
    lua().get_event_manager().trigger(
        lua::CharacterInstanceEvent("core.character_created", chara));
}



// Handlers for invalidation of characters (character death)
void HandleManager::remove_chara_handle_run_callbacks(Character& chara)
{
    auto handle = get_handle(chara);
    if (handle == sol::lua_nil)
    {
        return;
    }

    lua().get_event_manager().trigger(
        lua::CharacterInstanceEvent("core.character_removed", chara));
    remove_chara_handle(chara);
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
}

} // namespace lua
} // namespace elona

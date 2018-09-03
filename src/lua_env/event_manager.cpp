#include "event_manager.hpp"

#include "../log.hpp"
#include "lua_env.hpp"

namespace elona
{
namespace lua
{

EventManager::EventManager(LuaEnv* lua)
{
    this->lua = lua;
    init_events();

    bind_api(*lua);
}

void EventManager::bind_api(LuaEnv& lua)
{
    sol::table core = lua.get_api_manager().get_api_table();
    sol::table Event = core.create_named("Event");

    Event.set_function(
        "register",
        [this](
            EventKind event,
            sol::protected_function func,
            sol::this_environment this_env) {
            sol::environment& env = this_env;
            register_event(event, env, func);
        });

    Event.set_function(
        "unregister",
        [this](
            EventKind event,
            sol::protected_function func,
            sol::this_environment this_env) {
            sol::environment& env = this_env;
            unregister_event(event, env, func);
        });

    Event.set_function(
        "clear",
        sol::overload(
            [this](sol::this_environment this_env) {
                sol::environment& env = this_env;
                clear_mod_callbacks(env);
            },
            [this](EventKind event, sol::this_environment this_env) {
                sol::environment& env = this_env;
                clear_mod_callbacks(event, env);
            }));

    Event.set_function("trigger", [this](EventKind event, sol::table data) {
        trigger_event(event, data);
    });

    init_event_kinds(Event);
}

void EventManager::init_event_kinds(sol::table& Event)
{
    Event["EventKind"] = Event.create_with(
        "MapCreated",
        EventKind::map_created,
        "CharaCreated",
        EventKind::character_created,
        "ItemCreated",
        EventKind::item_created,

        // "CharaInitialized", EventKind::character_initialized,
        // "ItemInitialized", EventKind::item_initialized,
        "MapInitialized",
        EventKind::map_initialized,
        "GameInitialized",
        EventKind::game_initialized,

        "MapUnloading",
        EventKind::map_unloading,
        "MapLoaded",
        EventKind::map_loaded,

        "CharaRemoved",
        EventKind::character_removed,

        // TODO there are many edge cases to work out, like dropping items,
        // copying items...
        //"ItemRemoved", EventKind::item_removed,

        "CharaRefreshed",
        EventKind::character_refreshed,

        "CharaDamaged",
        EventKind::character_damaged,
        "CharaKilled",
        EventKind::character_killed,

        "CharaMoved",
        EventKind::character_moved,
        "PlayerTurn",
        EventKind::player_turn,
        "AllTurnsFinished",
        EventKind::all_turns_finished,

        "AllModsLoaded",
        EventKind::all_mods_loaded,
        "ScriptLoaded",
        EventKind::script_loaded);
}

void EventManager::init_events()
{
    unsigned event_count = static_cast<unsigned>(EventKind::COUNT);
    sol::function error_handler =
        lua->get_api_manager().get_api_table()["Debug"]["report_error"];
    for (unsigned i = 0; i < event_count; i++)
    {
        EventKind event_kind = static_cast<EventKind>(i);
        Callbacks cb;
        cb.set_error_handler(error_handler);
        events[event_kind] = std::move(cb);
    }
}

void EventManager::register_event(
    EventKind event,
    sol::environment& env,
    sol::protected_function& callback)
{
    auto iter = events.find(event);
    if (iter != events.end())
    {
        iter->second.push(env, callback);
    }
}

void EventManager::unregister_event(
    EventKind event,
    sol::environment& env,
    sol::protected_function& callback)
{
    auto iter = events.find(event);
    if (iter != events.end())
    {
        sol::optional<std::string> mod_name = env["_MOD_NAME"];
        assert(mod_name);
        iter->second.remove(*mod_name, callback);
    }
}

void EventManager::clear_mod_callbacks(
    EventKind event,
    sol::environment& env)
{
    auto iter = events.find(event);
    if (iter != events.end())
    {
        sol::optional<std::string> mod_name = env["_MOD_NAME"];
        assert(mod_name);
        iter->second.remove_all_from_mod(mod_name.value());
    }
}

void EventManager::clear_mod_callbacks(sol::environment& env)
{
    unsigned event_count = static_cast<unsigned>(EventKind::COUNT);
    for (unsigned i = 0; i < event_count; i++)
    {
        EventKind event_kind = static_cast<EventKind>(i);
        clear_mod_callbacks(event_kind, env);
    }
}

void EventManager::trigger_event(EventKind event, sol::table data)
{
    auto iter = events.find(event);
    if (iter != events.end())
    {
        iter->second.run(Callbacks::RetValType<void>(), data);
    }
    else
    {
        ELONA_LOG(
            "No callbacks registered for event " << static_cast<int>(event)
                                                 << ", skipping.");
    }
}

void EventManager::clear()
{
    events.clear();
    init_events();
}

} // namespace lua
} // namespace elona

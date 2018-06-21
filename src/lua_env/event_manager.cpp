#include "event_manager.hpp"

#include "../log.hpp"
#include "lua_env.hpp"

namespace elona
{
namespace lua
{

void init_event_kinds(sol::table& Event)
{
    Event["EventKind"] = Event.create_with(
        "MapCreated",
        event_kind_t::map_created,
        "CharaCreated",
        event_kind_t::character_created,
        "ItemCreated",
        event_kind_t::item_created,

        // "CharaInitialized", event_kind_t::character_initialized,
        // "ItemInitialized", event_kind_t::item_initialized,
        "MapInitialized",
        event_kind_t::map_initialized,
        "GameInitialized",
        event_kind_t::game_initialized,

        "CharaRemoved",
        event_kind_t::character_removed,

        // TODO there are many edge cases to work out, like dropping items,
        // copying items... "ItemRemoved", event_kind_t::item_removed,

        "CharaRefreshed",
        event_kind_t::character_refreshed,

        "CharaDamaged",
        event_kind_t::character_damaged,
        "CharaKilled",
        event_kind_t::character_killed,

        "CharaMoved",
        event_kind_t::character_moved,
        "PlayerTurn",
        event_kind_t::player_turn,
        "AllTurnsFinished",
        event_kind_t::all_turns_finished);
}

void event_manager::init(lua_env& lua)
{
    sol::table core = lua.get_api_manager().get_api_table();
    sol::table Event = core.create_named("Event");

    Event.set_function(
        "register",
        [&lua](
            event_kind_t event,
            sol::protected_function func,
            sol::this_environment this_env) {
            sol::environment& env = this_env;
            lua.get_event_manager().register_event(event, env, func);
        });

    Event.set_function("unregister", [&lua](event_kind_t event,
                                          sol::protected_function func,
                                          sol::this_environment this_env) {
                           sol::environment& env = this_env;
                           return lua.get_event_manager().unregister_event(event, env, func);
                       });

    Event.set_function("clear", sol::overload(
                           [&lua](sol::this_environment this_env) {
                               sol::environment& env = this_env;
                               lua.get_event_manager().clear_mod_callbacks(env);
                           },
                           [&lua](event_kind_t event,
                                  sol::this_environment this_env) {
                               sol::environment& env = this_env;
                               lua.get_event_manager().clear_mod_callbacks(event, env);
                           }));

    Event.set_function("trigger", [&lua](event_kind_t event,
                                         sol::table data) {
                           lua.get_event_manager().trigger_event(event, data);
                       });

    init_event_kinds(Event);
}

event_manager::event_manager(lua_env* lua)
{
    this->lua = lua;
    init_events();
}

void event_manager::init_events()
{
    unsigned event_count = static_cast<unsigned>(event_kind_t::COUNT);
    sol::function error_handler =
        lua->get_api_manager().get_api_table()["Debug"]["report_error"];
    for (unsigned i = 0; i < event_count; i++)
    {
        event_kind_t event_kind = static_cast<event_kind_t>(i);
        callbacks cb;
        cb.set_error_handler(error_handler);
        events[event_kind] = std::move(cb);
    }
}

void event_manager::register_event(
    event_kind_t event,
    sol::environment& env,
    sol::protected_function& callback)
{
    auto iter = events.find(event);
    if (iter != events.end())
    {
        iter->second.push(env, callback);
    }
}

<<<<<<< HEAD
void event_manager::unregister_event(event_kind_t event,
                                   sol::environment& env,
                                   sol::protected_function& callback)
{
    auto iter = events.find(event);
    if(iter != events.end())
    {
        sol::optional<std::string> mod_name = env["_MOD_NAME"];
        assert(mod_name);
        iter->second.remove(*mod_name, callback);
    }
}

void event_manager::clear_mod_callbacks(event_kind_t event,
                                        sol::environment& env)
{
    auto iter = events.find(event);
    if(iter != events.end())
    {
        sol::optional<std::string> mod_name = env["_MOD_NAME"];
        assert(mod_name);
        iter->second.remove_all_from_mod(mod_name.value());
    }
}

void event_manager::clear_mod_callbacks(sol::environment& env)
{
    unsigned event_count = static_cast<unsigned>(event_kind_t::COUNT);
    for(unsigned i = 0; i < event_count; i++)
    {
        event_kind_t event_kind = static_cast<event_kind_t>(i);
        clear_mod_callbacks(event_kind, env);
    }
}

void event_manager::trigger_event(event_kind_t event,
                                  sol::table data)
=======
void event_manager::trigger_event(event_kind_t event, sol::table data)
>>>>>>> 1926f7cff2006baf5abb03a6ba41225ea7c70a3c
{
    auto iter = events.find(event);
    if (iter != events.end())
    {
        iter->second.run(callbacks::retval_type<void>(), data);
    }
    else
    {
        ELONA_LOG(
            "No callbacks registered for event " << static_cast<int>(event)
                                                 << ", skipping.");
    }
}

void event_manager::clear()
{
    events.clear();
    init_events();
}

} // namespace lua
} // namespace elona

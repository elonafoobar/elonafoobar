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
        "MapCreated", event_kind_t::map_created,
        "CharaCreated", event_kind_t::character_created,
        "ItemCreated", event_kind_t::item_created,

        // TODO implement
        // "CharaInitialized", event_kind_t::character_initialized,
        // TODO implement
        // "ItemInitialized", event_kind_t::item_initialized,
        "MapInitialized", event_kind_t::map_initialized,
        "GameInitialized", event_kind_t::game_initialized,

        // TODO trigger everywhere chara.state is set to 0
        "CharaRemoved", event_kind_t::character_removed,
        // TODO trigger everywhere item.number is set to 0
        "ItemRemoved", event_kind_t::item_removed,

        "CharaRefreshed", event_kind_t::character_refreshed,

        "CharaKilled", event_kind_t::character_killed,

        "CharaMoved", event_kind_t::character_moved,
        "PlayerTurn", event_kind_t::player_turn,
        "AllTurnsFinished", event_kind_t::all_turns_finished
        );
}

void event_manager::init(lua_env& lua)
{
    sol::table core = lua.get_api_manager().get_api_table();
    sol::table Event = core.create_named("Event");

    Event.set_function("register", [&lua](event_kind_t event,
                                          sol::protected_function func,
                                          sol::this_environment this_env) {
                           sol::environment& env = this_env;
                           lua.get_event_manager().register_event(event, env, func);
                       });

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
    for(unsigned i = 0; i < event_count; i++)
    {
        event_kind_t event_kind = static_cast<event_kind_t>(i);
        events[event_kind] = callbacks();
    }
}

void event_manager::register_event(event_kind_t event,
                                   sol::environment& env,
                                   sol::protected_function& callback)
{
    auto iter = events.find(event);
    if(iter != events.end())
    {
        iter->second.push(env, callback);
    }
}

void event_manager::trigger_event(event_kind_t event,
                                  sol::table data)
{
    auto iter = events.find(event);
    if(iter != events.end())
    {
        iter->second.run(callbacks::retval_type<void>(), data);
    }
    else
    {
        ELONA_LOG("No callbacks registered for event " << static_cast<int>(event) << ", skipping.");
    }
}

void event_manager::clear()
{
    events.clear();
    init_events();
}

} // namespace lua
} // namespace elona

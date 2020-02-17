#include "event_manager.hpp"

#include "../log.hpp"
#include "api_manager.hpp"
#include "data_manager.hpp"
#include "interface.hpp"
#include "lua_env.hpp"
#include "lua_event/base_event.hpp"



namespace elona
{
namespace lua
{

EventManager::EventManager(LuaEnv& lua)
    : LuaSubmodule(lua)
{
    clear();
}



void EventManager::remove_unknown_events()
{
    env()["remove_unknown_events"](
        *lua().get_data_manager().get().get_table("core.event"));
}



EventResult EventManager::trigger(const BaseEvent& event)
{
    sol::protected_function trigger = env()["Event"]["trigger"];
    auto result =
        trigger(event.id, event.make_event_table(), event.make_event_options());

    if (!result.valid())
    {
        sol::error error = result;
        auto message =
            "Error triggering event "s + event.id + ":" + error.what();
        txt(message, Message::color{ColorIndex::red});
        std::cerr << message << std::endl;
        ELONA_ERROR("lua.event") << message;

        return EventResult{lua_state()->create_table()};
    }

    sol::object value = result;

    if (!value.is<sol::table>())
    {
        return EventResult{lua_state()->create_table_with(1, value)};
    }

    return EventResult{value.as<sol::table>()};
}



void EventManager::clear()
{
    env() = sol::environment(*lua_state(), sol::create, lua_state()->globals());

    safe_script_file(
        filesystem::dirs::data() / "script" / "kernel" / "event.lua");

    sol::table game = lua().get_api_manager().get_game_api_table();
    game["Event"] = env()["Event"];
}

} // namespace lua
} // namespace elona

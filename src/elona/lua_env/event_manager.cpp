#include "event_manager.hpp"
#include "../data/types/type_event.hpp"
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

EventManager::EventManager(LuaEnv* lua)
{
    this->lua = lua;
    clear();
}

void EventManager::remove_unknown_events()
{
    env["remove_unknown_events"](lua->get_data_manager().get().storage);
}

EventResult EventManager::trigger(const BaseEvent& event)
{
    sol::protected_function trigger = env["Event"]["trigger"];
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

        return EventResult{lua->get_state()->create_table()};
    }

    sol::object value = result;

    if (!value.is<sol::table>())
    {
        return EventResult{lua->get_state()->create_table_with(1, value)};
    }

    return EventResult{value.as<sol::table>()};
}

void EventManager::clear()
{
    env = sol::environment(
        *(lua->get_state()), sol::create, lua->get_state()->globals());

    lua->get_state()->safe_script_file(
        filepathutil::to_utf8_path(
            filesystem::dir::data() / "script" / "kernel" / "event.lua"),
        env);

    sol::table core = lua->get_api_manager().get_core_api_table();
    core["Event"] = env["Event"];
}

} // namespace lua
} // namespace elona

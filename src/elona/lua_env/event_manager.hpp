#pragma once

#include <map>
#include "config_table.hpp"
#include "lua_env.hpp"

namespace elona
{
namespace lua
{

class LuaEnv;
struct BaseEvent;

struct EventResult : ConfigTable
{
    EventResult(sol::table table)
        : ConfigTable(table)
    {
    }

    bool blocked()
    {
        return optional_or<bool>("blocked", false);
    }
};

/***
 * Manages a list of callbacks for each event type. Allows triggering
 * callbacks from C++ with any arguments needed.
 */
class EventManager
{

public:
    explicit EventManager(LuaEnv* lua);
    /***
     * Runs all callbacks for this event in the order they were registered.
     */
    EventResult trigger(const BaseEvent& event);

    void clear();

private:
    void init_events();

    sol::environment env;
    LuaEnv* lua;
};

} // namespace lua
} // namespace elona

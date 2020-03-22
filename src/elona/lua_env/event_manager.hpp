#pragma once

#include <map>

#include "config_table.hpp"
#include "lua_submodule.hpp"



namespace elona
{
namespace lua
{

struct BaseEvent;



struct EventResult : public ConfigTable
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
class EventManager : public LuaSubmodule
{
public:
    explicit EventManager(LuaEnv& lua);


    /***
     * Runs all callbacks for this event in the order they were registered.
     */
    EventResult trigger(const BaseEvent& event);


    /**
     * Removes events not registered in the data table.
     */
    void remove_unknown_events();

    void clear();


private:
    void init_events();
};

} // namespace lua
} // namespace elona

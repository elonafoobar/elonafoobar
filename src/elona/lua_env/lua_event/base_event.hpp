#pragma once
#include "../interface.hpp"

namespace elona
{

using LuaCharacterHandle = sol::table;
using LuaItemHandle = sol::table;

namespace lua
{

struct BaseEvent
{
public:
    BaseEvent(const char* id)
    {
        this->id = id;
    }

    virtual sol::table make_event_table() const
    {
        return lua::create_table();
    }

    virtual sol::table make_event_options() const
    {
        return lua::create_table();
    }

    const char* id;
};

} // namespace lua
} // namespace elona

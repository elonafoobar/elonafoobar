#pragma once
#include "../../item.hpp"
#include "../interface.hpp"
#include "base_event.hpp"

namespace elona
{
namespace lua
{

struct ItemInstanceEvent : BaseEvent
{
public:
    ItemInstanceEvent(const char* id, const Item& item)
        : BaseEvent(id)
    {
        _item = lua::handle(item);
    }

    sol::table make_event_table() const override
    {
        auto args = lua::create_table();
        args["item"] = _item;

        return args;
    };

    sol::table make_event_options() const override
    {
        auto opts = lua::create_table();
        opts["instance"] = _item;

        return opts;
    }

protected:
    LuaItemHandle _item;
};

} // namespace lua
} // namespace elona

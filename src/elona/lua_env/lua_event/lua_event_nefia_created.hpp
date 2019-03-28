#pragma once
#include "../../area.hpp"
#include "../interface.hpp"
#include "base_event.hpp"

namespace elona
{
namespace lua
{

struct NefiaCreatedEvent : BaseEvent
{
public:
    NefiaCreatedEvent(Area* area)
        : BaseEvent("core.nefia_created")
        , _area(area)
    {
    }

    sol::table make_event_table() const override
    {
        auto args = lua::create_table();
        args["nefia"] = _area;

        return args;
    };

private:
    Area* _area;
};

} // namespace lua
} // namespace elona

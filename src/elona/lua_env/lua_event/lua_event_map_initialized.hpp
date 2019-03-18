#pragma once
#include "../../character.hpp"
#include "../interface.hpp"
#include "character_instance_event.hpp"

namespace elona
{
namespace lua
{

struct MapInitializedEvent : BaseEvent
{
public:
    MapInitializedEvent(bool regenerated)
        : BaseEvent("core.map_initialized")
    {
        _regenerated = regenerated;
    }

    sol::table make_event_table() const override
    {
        auto args = lua::create_table();
        args["regenerated"] = _regenerated;

        return args;
    };

private:
    bool _regenerated;
};

} // namespace lua
} // namespace elona

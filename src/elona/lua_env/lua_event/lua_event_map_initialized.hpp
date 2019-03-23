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
    MapInitializedEvent(bool regenerated, std::string id, int index)
        : BaseEvent("core.map_initialized")
        , _regenerated(regenerated)
        , _id(id)
        , _index(index)
    {
    }

    sol::table make_event_table() const override
    {
        auto args = lua::create_table();
        args["regenerated"] = _regenerated;
        args["id"] = _id;
        args["index"] = _index;

        return args;
    };

private:
    bool _regenerated;
    std::string _id;
    int _index;
};

} // namespace lua
} // namespace elona

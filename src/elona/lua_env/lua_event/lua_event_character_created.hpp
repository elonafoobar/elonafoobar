#pragma once
#include "../../character.hpp"
#include "../interface.hpp"
#include "character_instance_event.hpp"

namespace elona
{
namespace lua
{

struct CharacterCreatedEvent : CharacterInstanceEvent
{
public:
    CharacterCreatedEvent(Character& chara)
        : CharacterInstanceEvent("core.character_created", chara)
    {
    }

    sol::table make_event_table() const override
    {
        auto args = lua::create_table();
        args["chara"] = _chara;

        return args;
    };
};

} // namespace lua
} // namespace elona

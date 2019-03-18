#pragma once
#include "../../character.hpp"
#include "../interface.hpp"
#include "base_event.hpp"

namespace elona
{
namespace lua
{

struct CharacterInstanceEvent : BaseEvent
{
public:
    CharacterInstanceEvent(const char* id, const Character& chara)
        : BaseEvent(id)
    {
        _chara = lua::handle(chara);
    }

    sol::table make_event_table() const override
    {
        auto args = lua::create_table();
        args["chara"] = _chara;

        return args;
    };

    sol::table make_event_options() const override
    {
        auto opts = lua::create_table();
        opts["instance"] = _chara;

        return opts;
    }

protected:
    LuaCharacterHandle _chara;
};

} // namespace lua
} // namespace elona

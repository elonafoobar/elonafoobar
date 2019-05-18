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
        _chara_id = chara.new_id();
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
        opts["instances"] = lua::create_table(1, _chara, 2, _chara_id);

        return opts;
    }

protected:
    LuaCharacterHandle _chara;
    std::string _chara_id;
};

} // namespace lua
} // namespace elona

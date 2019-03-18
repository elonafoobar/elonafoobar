#pragma once
#include "../../character.hpp"
#include "../enums/enums.hpp"
#include "../interface.hpp"
#include "character_instance_event.hpp"

namespace elona
{
namespace lua
{

struct CharacterDamagedEvent : CharacterInstanceEvent
{
public:
    CharacterDamagedEvent(
        Character& chara,
        int damage,
        int element,
        int damage_source)
        : CharacterInstanceEvent("core.character_damaged", chara)
    {
        _damage = damage;
        _element = element;
        _damage_source = damage_source;
    }

    sol::table make_event_table() const override
    {
        auto args = lua::create_table();
        args["target"] = _chara;
        args["damage"] = _damage;

        if (_element > 0)
        {
            args["element"] = lua::LuaEnums::ElementTable.convert_to_string(
                static_cast<Element>(_element));
        }

        if (_damage_source >= 0)
        {
            args["source"] = lua::handle(cdata[_damage_source]);
        }
        else
        {
            args["source"] = lua::LuaEnums::DamageSourceTable.convert_to_string(
                static_cast<DamageSource>(_damage_source));
        }

        return args;
    };

private:
    int _damage;
    int _element;
    int _damage_source;
};

} // namespace lua
} // namespace elona

#pragma once

#include "../common.hpp"
#include "lua_ref.hpp"



namespace elona::lua::api::classes
{

struct LuaAbility : LuaRef<Character>
{
    LuaAbility(int skill_id, const ObjId& obj_id)
        : LuaRef(obj_id)
        , skill_id(skill_id)
    {
    }

    int skill_id;
};

} // namespace elona::lua::api::classes

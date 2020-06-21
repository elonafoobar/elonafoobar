#pragma once

#include "../common.hpp"
#include "lua_ref.hpp"



namespace elona::lua::api::classes
{

struct LuaAbility : LuaRef
{
    LuaAbility(int skill_id_, int index, std::string type, std::string uuid)
        : LuaRef(index, type, uuid)
    {
        skill_id = skill_id_;
    }

    int skill_id;
};

} // namespace elona::lua::api::classes

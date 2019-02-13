#pragma once

#include "../../../thirdparty/sol2/sol.hpp"
#include "../../variables.hpp"
#include "../lua_enums.hpp"
#include "../lua_env.hpp"



namespace elona
{

struct Position;
struct Character;
struct Item;

using LuaCharacterHandle = sol::table;
using LuaItemHandle = sol::table;

} // namespace elona



#define LUA_API_BIND_FUNCTION(api_table, api_name, function) \
    do \
    { \
        api_table.set_function(#function, api_name::function); \
    } while (false)

#define LUA_API_BIND_CONSTANT(api_table, name, value) \
    do \
    { \
        api_table[#name] = (value); \
    } while (false)

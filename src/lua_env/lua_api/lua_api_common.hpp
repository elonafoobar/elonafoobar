#pragma once
#include "../../thirdparty/sol2/sol.hpp"
#include "../../variables.hpp"
#include "../lua_env.hpp"

struct Position;
struct Character;
struct Item;

using LuaCharacterHandle = sol::table;
using LuaItemHandle = sol::table;

#define LUA_API_BIND_FUNCTION(api_table, api_name, function) \
    api_table.set_function(#function, api_name::function)

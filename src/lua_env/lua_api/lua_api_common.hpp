#pragma once
#include "../../thirdparty/sol2/sol.hpp"
#include "../../variables.hpp"
#include "../lua_env.hpp"

struct position_t;
struct character;
struct item;

typedef sol::table lua_character_handle;
typedef sol::table lua_item_handle;

#define LUA_API_BIND_FUNCTION(api_table, api_name, function) \
    api_table.set_function(#function, api_name::function)

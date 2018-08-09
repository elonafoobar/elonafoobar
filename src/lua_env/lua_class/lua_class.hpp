#pragma once
#include "../lua_api/lua_api_common.hpp"

#include "lua_class_character.hpp"
#include "lua_class_item.hpp"
#include "lua_class_position.hpp"

namespace elona
{
namespace lua
{

/***
 * Binding functions for usertype classes.
 *
 * Methods for usertypes do not take a handle as a first argument,
 * because handles will transparently pass their underlying C++
 * references to them via metatables.
 */
namespace LuaApiClasses
{
void bind(sol::state&);
void bind_api(sol::state&, sol::table&);
} // namespace LuaApiClasses

} // namespace lua
} // namespace elona

#pragma once
#include "lua_api_common.hpp"

namespace elona
{
namespace lua
{

namespace Magic
{
void cast_self(LuaCharacterHandle, int, int, const Position&);
void cast(LuaCharacterHandle, LuaCharacterHandle, int, int);


void bind(sol::table&);
} // namespace Magic

} // namespace lua
} // namespace elona

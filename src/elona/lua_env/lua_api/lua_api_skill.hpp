#pragma once
#include "lua_api_common.hpp"

namespace elona
{
namespace lua
{

namespace LuaApiSkill
{
int level(int, LuaCharacterHandle);
int resistance(const EnumString&, LuaCharacterHandle);


void bind(sol::table&);
} // namespace LuaApiSkill

} // namespace lua
} // namespace elona

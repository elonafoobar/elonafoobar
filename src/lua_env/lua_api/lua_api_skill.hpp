#pragma once
#include "lua_api_common.hpp"

namespace elona
{
namespace lua
{

namespace Skill
{
int level(int, LuaCharacterHandle);
int resistance(const EnumString&, LuaCharacterHandle);


void bind(sol::table&);
} // namespace Skill

} // namespace lua
} // namespace elona

#pragma once
#include "lua_api_common.hpp"

namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Functions for working with skills or spells.
 * Both skills and spells are represented through the same experience
 * and leveling system. The only real difference is that spells have
 * an additional spell stock value.
 */
namespace LuaApiSkill
{
int resistance(const EnumString&, LuaCharacterHandle);


void bind(sol::table&);
} // namespace LuaApiSkill

} // namespace lua
} // namespace elona

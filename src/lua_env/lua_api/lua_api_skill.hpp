#pragma once
#include "lua_api_common.hpp"

namespace elona
{
namespace lua
{

namespace Skill
{
int level(int, lua_character_handle);
int resistance(const enum_string&, lua_character_handle);


void bind(sol::table&);
} // namespace Skill

} // namespace lua
} // namespace elona

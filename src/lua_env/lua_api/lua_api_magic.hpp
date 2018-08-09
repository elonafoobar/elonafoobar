#pragma once
#include "lua_api_common.hpp"

namespace elona
{
namespace lua
{

namespace Magic
{
void cast_self(lua_character_handle, int, int, const position_t&);
void cast(lua_character_handle, lua_character_handle, int, int);


void bind(sol::table&);
} // namespace Magic

} // namespace lua
} // namespace elona

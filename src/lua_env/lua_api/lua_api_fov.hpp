#pragma once
#include "lua_api_common.hpp"

namespace elona
{
namespace lua
{

namespace FOV
{
bool los(const position_t&, const position_t&);
bool los_xy(int, int, int, int);

bool you_see(lua_character_handle);
bool you_see_pos(const position_t&);
bool you_see_pos_xy(int, int);

void refresh();


void bind(sol::table&);
}; // namespace FOV

} // namespace lua
} // namespace elona

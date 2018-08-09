#pragma once
#include "lua_api_common.hpp"

namespace elona
{

namespace lua
{

namespace Pos
{
int dist(const position_t&, const position_t&);
int dist_xy(int, int, int, int);


void bind(sol::table&);
} // namespace Pos

} // namespace lua
} // namespace elona

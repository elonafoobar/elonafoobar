#pragma once
#include "../common.hpp"

namespace elona
{

namespace lua
{

/**
 *@luadoc
 *
 * Functions for working with positions.
 */
namespace LuaApiPos
{
int dist(const Position&, const Position&);
int dist_xy(int, int, int, int);


void bind(sol::table&);
} // namespace LuaApiPos

} // namespace lua
} // namespace elona

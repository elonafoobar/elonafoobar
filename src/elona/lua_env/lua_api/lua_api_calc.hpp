#pragma once

#include "lua_api_common.hpp"



namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Various calculation.
 */
namespace LuaApiCalc
{

int calc_objlv(int n);

void bind(sol::table&);

} // namespace LuaApiCalc

} // namespace lua
} // namespace elona

#pragma once
#include "lua_api_common.hpp"

namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Math utility functions.
 */
namespace LuaApiMath
{
int calc_objlv(int n);


void bind(sol::table&);
} // namespace LuaApiMath

} // namespace lua
} // namespace elona

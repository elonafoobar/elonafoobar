#pragma once
#include "lua_api_common.hpp"

namespace elona
{
namespace lua
{

namespace Math
{
int clamp(int, int, int);


void bind(sol::table&);
} // namespace Math

} // namespace lua
} // namespace elona

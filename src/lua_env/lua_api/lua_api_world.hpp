#pragma once
#include "lua_api_common.hpp"

namespace elona
{
namespace lua
{

namespace World
{
int time();


void bind(sol::table&);
} // namespace World

} // namespace lua
} // namespace elona

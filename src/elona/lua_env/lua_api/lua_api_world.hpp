#pragma once
#include "lua_api_common.hpp"

namespace elona
{
namespace lua
{

namespace LuaApiWorld
{
int time();

bool belongs_to_guild(const std::string&);


void bind(sol::table&);
} // namespace LuaApiWorld

} // namespace lua
} // namespace elona

#pragma once
#include "lua_api_common.hpp"

namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Functions for working with the state of the game world.
 */
namespace LuaApiWorld
{
int time();

bool belongs_to_guild(const std::string&);


void bind(sol::table&);
} // namespace LuaApiWorld

} // namespace lua
} // namespace elona

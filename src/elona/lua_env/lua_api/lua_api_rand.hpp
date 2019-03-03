#pragma once
#include "lua_api_common.hpp"

namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Functions for working with randomness.
 */
namespace LuaApiRand
{
int rnd(int n);

bool one_in(int n);

bool coinflip();

sol::object choice(sol::table table);


void bind(sol::table&);
}; // namespace LuaApiRand

} // namespace lua
} // namespace elona

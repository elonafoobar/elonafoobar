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

int between(int min, int max);

sol::object choice(sol::table table);

int roll(int dice_x, int dice_y, int bonus);


void bind(sol::table&);
}; // namespace LuaApiRand

} // namespace lua
} // namespace elona

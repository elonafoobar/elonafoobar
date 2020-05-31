#pragma once

#include "../common.hpp"



namespace elona::lua::api::modules
{

/**
 * @luadoc
 *
 * Various calculation.
 */
namespace LuaApiCalc
{

int calc_objlv(int n);

void bind(sol::table);

} // namespace LuaApiCalc

} // namespace elona::lua::api::modules

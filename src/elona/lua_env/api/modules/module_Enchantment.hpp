#pragma once

#include "../common.hpp"



namespace elona::lua::api::modules
{

/**
 * @luadoc
 *
 * Handle item enchantments.
 */
namespace LuaApiEnchantment
{

void add(LuaItemHandle, int, int);

void bind(sol::table);

} // namespace LuaApiEnchantment

} // namespace elona::lua::api::modules

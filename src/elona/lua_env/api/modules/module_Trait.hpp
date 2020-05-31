#pragma once

#include "../common.hpp"



namespace elona::lua::api::modules
{

/**
 * @luadoc
 *
 * Functions for working with traits.
 * Currently only the player can have traits.
 */
namespace LuaApiTrait
{
sol::optional<int> level(int);

sol::optional<int> min(int);

sol::optional<int> max(int);

void set(int, int);

void modify(int, int);


void bind(sol::table);
} // namespace LuaApiTrait

} // namespace elona::lua::api::modules

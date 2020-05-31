#pragma once

#include "../common.hpp"



namespace elona::lua::api::modules
{

/**
 * @luadoc
 *
 * Functions for testing visibility.
 */
namespace LuaApiFOV
{
bool los(const Position&, const Position&);
bool los_xy(int, int, int, int);

bool you_see(LuaCharacterHandle);
bool you_see_pos(const Position&);
bool you_see_pos_xy(int, int);

void refresh();


void bind(sol::table);
}; // namespace LuaApiFOV

} // namespace elona::lua::api::modules

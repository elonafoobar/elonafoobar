#pragma once

#include "../common.hpp"



namespace elona::lua::api::modules
{

/**
 * @luadoc
 *
 * Functions for working with magic.
 */
namespace LuaApiMagic
{
void cast_self(LuaCharacterHandle, int, int, const Position&);
void cast(LuaCharacterHandle, LuaCharacterHandle, int, int);


void bind(sol::table);
} // namespace LuaApiMagic

} // namespace elona::lua::api::modules

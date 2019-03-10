#pragma once
#include "lua_api_common.hpp"

namespace elona
{

namespace lua
{

/**
 * @luadoc
 *
 * Functions for managing the asset system. With this module it is possible to
 * reload built-in assets like textures and music.
 */
namespace LuaApiData
{
void reload_assets();

void reload_charas();


void bind(sol::table&);
} // namespace LuaApiData

} // namespace lua
} // namespace elona

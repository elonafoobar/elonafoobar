#pragma once
#include "lua_api_common.hpp"

#include "lua_api_animation.hpp"
#include "lua_api_chara.hpp"
#include "lua_api_debug.hpp"
#include "lua_api_fov.hpp"
#include "lua_api_gui.hpp"
#include "lua_api_i18n.hpp"
#include "lua_api_input.hpp"
#include "lua_api_item.hpp"
#include "lua_api_magic.hpp"
#include "lua_api_map.hpp"
#include "lua_api_math.hpp"
#include "lua_api_pos.hpp"
#include "lua_api_rand.hpp"
#include "lua_api_skill.hpp"
#include "lua_api_trait.hpp"
#include "lua_api_world.hpp"

/***
 * See doc/api for the API documentation.
 * Be sure to update it if you change anything in the API bindings.
 * LDoc is completely broken when it comes to parsing C++.
 */
namespace elona
{
namespace lua
{

namespace LuaApi
{
void bind(sol::table&);
}

} // namespace lua
} // namespace elona

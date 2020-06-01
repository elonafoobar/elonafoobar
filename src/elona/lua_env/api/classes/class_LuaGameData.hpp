#pragma once

#include "../common.hpp"



namespace elona::lua::api::classes
{

/**
 * @luadoc
 *
 * Contains parameters for the current game save.
 */
namespace class_LuaGameData
{
void bind(sol::state&);
}

} // namespace elona::lua::api::classes

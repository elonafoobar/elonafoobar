#pragma once

#include "../common.hpp"



namespace elona::lua::api::classes
{

/**
 * @luadoc
 *
 * Represents a 2-dimensional position. Intended for representing tile
 * locations.
 */
namespace class_LuaPosition
{
void bind(sol::state&);
}

} // namespace elona::lua::api::classes

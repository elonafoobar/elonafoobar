#pragma once

#include "../common.hpp"



namespace elona::lua::api::classes
{

/**
 * @luadoc
 *
 * Contains parameters for the current map.
 */
namespace class_LuaMapData
{
void bind(sol::state&);
}

} // namespace elona::lua::api::classes

#pragma once

#include "../../handle_manager.hpp"
#include "../common.hpp"



namespace elona::lua::api::classes
{

/**
 * @luadoc
 *
 * Represents an area on the map.
 */
namespace class_LuaArea
{
void bind(sol::state& lua);
}

} // namespace elona::lua::api::classes

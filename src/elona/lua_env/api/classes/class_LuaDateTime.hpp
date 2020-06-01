#pragma once

#include "../../handle_manager.hpp"
#include "../common.hpp"



namespace elona::lua::api::classes
{

/**
 * @luadoc
 *
 * Represents a date and time.
 */
namespace class_LuaDateTime
{
void bind(sol::state& lua);
}

} // namespace elona::lua::api::classes

#pragma once
#include "../api/common.hpp"
#include "../handle_manager.hpp"



namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Represents an area on the map.
 */
namespace LuaArea
{
void bind(sol::state& lua);
}

} // namespace lua
} // namespace elona

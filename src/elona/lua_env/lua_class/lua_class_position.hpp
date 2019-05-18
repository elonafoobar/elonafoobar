#pragma once
#include "../lua_api/lua_api_common.hpp"

namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Represents a 2-dimensional position. Intended for representing tile
 * locations.
 */
namespace LuaPosition
{
void bind(sol::state&);
}

} // namespace lua
} // namespace elona

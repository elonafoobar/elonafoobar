#pragma once
#include "../api/common.hpp"

namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Contains parameters for the current map.
 */
namespace LuaMapData
{
void bind(sol::state&);
}

} // namespace lua
} // namespace elona

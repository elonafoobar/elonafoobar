#pragma once
#include "../common.hpp"

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

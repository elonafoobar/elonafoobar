#pragma once
#include "../lua_api/lua_api_common.hpp"

namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Represents an item.
 */
namespace LuaItem
{
void remove(Item&);

void change_material(Item&, const std::string&);


void bind(sol::state&);
} // namespace LuaItem

} // namespace lua
} // namespace elona

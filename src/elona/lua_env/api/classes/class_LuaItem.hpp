#pragma once
#include "../common.hpp"

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

std::string metamethod_tostring(const Item&);


void bind(sol::state&);
} // namespace LuaItem

} // namespace lua
} // namespace elona

#pragma once

#include "../common.hpp"



namespace elona::lua::api::classes
{

/**
 * @luadoc
 *
 * Represents an item.
 */
namespace class_LuaItem
{
void remove(Item&);

void change_material(Item&, const std::string&);

std::string metamethod_tostring(const Item&);


void bind(sol::state&);
} // namespace class_LuaItem

} // namespace elona::lua::api::classes

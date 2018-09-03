#pragma once
#include "lua_api_common.hpp"

namespace elona
{
namespace lua
{

namespace Item
{
int count();

bool has_enchantment(const lua_item_handle, int);

void remove(lua_item_handle);

sol::optional<lua_item_handle> create(const Position&, int, int);
sol::optional<lua_item_handle> create_xy(int, int, int, int);
sol::optional<lua_item_handle>
create_from_id(const Position&, const std::string&, int);
sol::optional<lua_item_handle>
create_from_id_xy(int, int, const std::string&, int);


void bind(sol::table&);
} // namespace Item

} // namespace lua
} // namespace elona

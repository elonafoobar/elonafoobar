#pragma once
#include "lua_api_common.hpp"

namespace elona
{
namespace lua
{

namespace Item
{
int count();

bool has_enchantment(const LuaItemHandle, int);

void remove(LuaItemHandle);

std::string itemname(LuaItemHandle, int, bool);

sol::optional<LuaItemHandle> create(const Position&, int, int);
sol::optional<LuaItemHandle> create_xy(int, int, int, int);
sol::optional<LuaItemHandle>
create_from_id(const Position&, const std::string&, int);
sol::optional<LuaItemHandle>
create_from_id_xy(int, int, const std::string&, int);


void bind(sol::table&);
} // namespace Item

} // namespace lua
} // namespace elona

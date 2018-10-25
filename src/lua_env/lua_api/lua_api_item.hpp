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

sol::optional<LuaItemHandle>
create_with_args(const Position&, const std::string&, int, sol::table);
sol::optional<LuaItemHandle>
create_with_args_xy(int, int, const std::string&, int, sol::table);
sol::optional<LuaItemHandle> create(const Position&, const std::string&, int);
sol::optional<LuaItemHandle> create_xy(int, int, const std::string&, int);

sol::optional<LuaItemHandle> roll(const Position&, sol::table args);
sol::optional<LuaItemHandle> roll_xy(int, int, sol::table args);


void bind(sol::table&);
} // namespace Item

} // namespace lua
} // namespace elona

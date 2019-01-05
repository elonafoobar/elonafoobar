#pragma once
#include "lua_api_common.hpp"

namespace elona
{
namespace lua
{

namespace LuaApiItem
{
int count();

bool has_enchantment(const LuaItemHandle, int);

std::string itemname(LuaItemHandle, int, bool);

sol::optional<LuaItemHandle> create_with_id(
    const Position&,
    const std::string&);
sol::optional<LuaItemHandle> create_with_id_xy(int, int, const std::string&);
sol::optional<LuaItemHandle>
create_with_number(const Position&, const std::string&, int);
sol::optional<LuaItemHandle>
create_with_number_xy(int, int, const std::string&, int);
sol::optional<LuaItemHandle> create(const Position&, sol::table);
sol::optional<LuaItemHandle> create_xy(int, int, sol::table);

int memory(int, const std::string&);

sol::optional<LuaItemHandle> stack(int, LuaItemHandle);

int trade_rate(LuaItemHandle);


void bind(sol::table&);
} // namespace LuaApiItem

} // namespace lua
} // namespace elona

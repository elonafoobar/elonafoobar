#pragma once
#include <string>
#include "lua_api_common.hpp"

namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Functions for working with characters.
 */
namespace LuaApiChara
{
bool is_alive(LuaCharacterHandle);

bool is_player(LuaCharacterHandle);

bool is_ally(LuaCharacterHandle);

bool flag(LuaCharacterHandle, const EnumString&);

int count();

sol::optional<LuaCharacterHandle> player();

sol::optional<LuaCharacterHandle> create(const Position&, int);
sol::optional<LuaCharacterHandle> create_xy(int, int, int);
sol::optional<LuaCharacterHandle> create_from_id(
    const Position&,
    const std::string&);
sol::optional<LuaCharacterHandle>
create_from_id_xy(int, int, const std::string&);

int kill_count(const std::string&);


void bind(sol::table&);
}; // namespace LuaApiChara

} // namespace lua
} // namespace elona

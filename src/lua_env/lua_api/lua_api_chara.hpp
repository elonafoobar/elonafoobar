#pragma once
#include <string>
#include "lua_api_common.hpp"

namespace elona
{
namespace lua
{

namespace Chara
{
bool is_alive(lua_character_handle);

bool is_player(lua_character_handle);

bool is_ally(lua_character_handle);

bool flag(lua_character_handle, int);

int count();

sol::optional<lua_character_handle> player();

sol::optional<lua_character_handle> create(const position_t&, int);
sol::optional<lua_character_handle> create_xy(int, int, int);
sol::optional<lua_character_handle> create_from_id(
    const position_t&,
    const std::string&);
sol::optional<lua_character_handle>
create_from_id_xy(int, int, const std::string&);


void bind(sol::table&);
}; // namespace Chara

} // namespace lua
} // namespace elona

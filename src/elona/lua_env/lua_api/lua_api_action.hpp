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
 * Functions related to game actions.
 */
namespace LuaApiAction
{
EnumString talk_to(LuaCharacterHandle);
EnumString talk_to_with_data(LuaCharacterHandle, const std::string&);

EnumString melee_attack(LuaCharacterHandle, LuaCharacterHandle);

EnumString manage_inventory(LuaCharacterHandle);

EnumString give_item(LuaCharacterHandle);

EnumString change_tone(LuaCharacterHandle);

EnumString change_appearance(LuaCharacterHandle);

EnumString show_investigate_screen(LuaCharacterHandle);


void bind(sol::table&);
} // namespace LuaApiAction
} // namespace lua
} // namespace elona

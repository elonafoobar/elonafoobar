#pragma once
#include "lua_api_common.hpp"

namespace elona
{
namespace lua
{

/**
 * Functions solely needed for implementing mod functionality, but which are
 * inconvenient to move to Lua completely.
 */
namespace LuaApiInternal
{

int get_quest_flag(const std::string&);

void set_quest_flag(const std::string&, int);

void go_to_quest_map(const std::string&, int);

std::string speaker_name(LuaCharacterHandle);

void material_kit_crafting_menu();

int filter_set_dungeon();

void trade_small_medals(LuaCharacterHandle);

void bind(sol::table&);
}; // namespace LuaApiInternal

} // namespace lua
} // namespace elona

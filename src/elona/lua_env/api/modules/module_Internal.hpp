#pragma once

#include "../common.hpp"



namespace elona::lua::api::modules
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

int generate_fighters_guild_target(int);

void leave_map();

void strange_scientist_pick_reward();


void bind(sol::table);
}; // namespace LuaApiInternal

} // namespace elona::lua::api::modules

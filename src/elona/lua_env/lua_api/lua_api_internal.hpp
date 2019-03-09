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

int get_quest_flag(const std::string& id);

void set_quest_flag(const std::string& id, int value);

std::string speaker_name(LuaCharacterHandle);


void bind(sol::table&);
}; // namespace LuaApiInternal

} // namespace lua
} // namespace elona

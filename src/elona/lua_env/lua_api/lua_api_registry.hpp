#pragma once

#include "lua_api_common.hpp"



namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Functions for retrieving arbitrary game data.
 */
namespace LuaApiRegistry
{

sol::optional<sol::table> get_table(const std::string& prototype_id);
sol::optional<std::string> get_id_by_legacy(
    const std::string& prototype_id,
    int legacy_id);

void bind(sol::table&);

} // namespace LuaApiRegistry

} // namespace lua
} // namespace elona

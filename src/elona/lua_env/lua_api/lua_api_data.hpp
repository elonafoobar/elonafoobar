#pragma once

#include "lua_api_common.hpp"



namespace elona
{

namespace lua
{

/**
 * @luadoc
 *
 * Functions for managing the asset system. With this module it is possible to
 * reload built-in assets like textures and music.
 */
namespace LuaApiData
{

void reload_assets();
void reload_charas();
sol::optional<sol::table> get(
    const std::string& prototype_id,
    const std::string& data_id);
sol::optional<sol::table> get_table(const std::string& prototype_id);
sol::optional<std::string> get_id_by_legacy(
    const std::string& prototype_id,
    int legacy_data_id);

void bind(sol::table&);

} // namespace LuaApiData

} // namespace lua
} // namespace elona

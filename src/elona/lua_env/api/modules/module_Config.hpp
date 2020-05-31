#pragma once

#include "../common.hpp"



namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Functions for getting and setting config values. See the topic on creating
 * config menus for more details.
 */
namespace LuaApiConfig
{

void set(const std::string& key, sol::object value);
sol::object get(const std::string& key);
void save();

void bind(sol::table&);

} // namespace LuaApiConfig

} // namespace lua
} // namespace elona

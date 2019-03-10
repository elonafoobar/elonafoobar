#pragma once
#include "lua_api_common.hpp"

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
void set_string(const std::string& key, const std::string& value);

void set_int(const std::string& key, int value);

void set_bool(const std::string& key, bool value);

std::string get_string(const std::string& key);

int get_int(const std::string& key);

bool get_bool(const std::string& key);

void save();


void bind(sol::table&);
} // namespace LuaApiConfig

} // namespace lua
} // namespace elona

#pragma once

#include "../common.hpp"



namespace elona::lua::api::modules
{

/**
 * @luadoc
 *
 * Functions related to in-game console.
 */
namespace LuaApiConsole
{

void register_(
    const std::string& mod_id,
    const std::string& name,
    sol::protected_function callback);

sol::object run(const std::string& cmdline);

void bind(sol::table);

} // namespace LuaApiConsole

} // namespace elona::lua::api::modules

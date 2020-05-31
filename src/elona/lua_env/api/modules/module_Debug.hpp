#pragma once

#include "../common.hpp"



namespace elona::lua::api::modules
{


/**
 * @luadoc
 *
 * Functions for debugging scripts.
 */
namespace LuaApiDebug
{
void log(const std::string&);

void report_error(const std::string&);

void dump_characters();

void dump_items();


void bind(sol::table);
} // namespace LuaApiDebug
} // namespace elona::lua::api::modules

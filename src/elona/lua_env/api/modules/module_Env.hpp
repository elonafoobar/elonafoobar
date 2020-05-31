#pragma once

#include "../common.hpp"



namespace elona::lua::api::modules
{

/**
 * @luadoc
 *
 * Information about Elona foobar and mod engine environment.
 */
namespace LuaApiEnv
{

void bind(sol::table);

} // namespace LuaApiEnv
} // namespace elona::lua::api::modules

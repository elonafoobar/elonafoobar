#pragma once

#include "lua_api_common.hpp"



/***
 * See doc/api for the API documentation.
 * Be sure to update it if you change anything in the API bindings.
 * LDoc is completely broken when it comes to parsing C++.
 */
namespace elona
{
namespace lua
{

namespace LuaApi
{
void bind(sol::table&);
}

} // namespace lua
} // namespace elona

#pragma once
#include "../handle_manager.hpp"
#include "../lua_api/lua_api_common.hpp"



namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Represents a date and time.
 */
namespace LuaDateTime
{
void bind(sol::state& lua);
}

} // namespace lua
} // namespace elona

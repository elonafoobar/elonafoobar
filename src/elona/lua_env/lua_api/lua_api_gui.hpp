#pragma once
#include "lua_api_common.hpp"

namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Functions for manipulating the player's user interface.
 */
namespace LuaApiGUI
{
void txt(const std::string&);
void txt_txtef(const std::string&, const EnumString&);

void txtnew();


void bind(sol::table&);
}; // namespace LuaApiGUI

} // namespace lua
} // namespace elona

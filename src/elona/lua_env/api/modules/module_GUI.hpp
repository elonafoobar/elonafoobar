#pragma once
#include "../common.hpp"

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

void play_sound(const std::string&);

void show_journal_update_message();

void fade_out();


void bind(sol::table&);
}; // namespace LuaApiGUI

} // namespace lua
} // namespace elona

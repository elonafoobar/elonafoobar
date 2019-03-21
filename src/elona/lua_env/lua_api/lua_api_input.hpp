#pragma once
#include "lua_api_common.hpp"

namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Functions for prompting the player for input.
 */
namespace LuaApiInput
{

sol::optional<bool> yes_no(const std::string&);

sol::optional<int> prompt_number(const std::string&, int);
sol::optional<int> prompt_number_with_initial(const std::string&, int, int);

sol::optional<std::string> prompt_text(const std::string&, bool);

sol::optional<int> prompt_choice(sol::table);

int prompt_dialog(
    const std::string&,
    const std::string&,
    const std::string&,
    sol::table,
    sol::optional<int>);
int prompt_dialog_impress(
    const std::string&,
    const std::string&,
    const std::string&,
    sol::table,
    sol::optional<int>,
    int,
    int);

int prompt_dialog_with_chip(
    const std::string&,
    int,
    const std::string&,
    sol::table,
    sol::optional<int>);
int prompt_dialog_with_chip_impress(
    const std::string&,
    int,
    const std::string&,
    sol::table,
    sol::optional<int>,
    int,
    int);

void start_dialog(LuaCharacterHandle);
void start_dialog_with_data(LuaCharacterHandle, const std::string&);

sol::optional<LuaCharacterHandle> choose_ally(const EnumString&);

sol::optional<std::string> get_pressed_keybind();


void bind(sol::table&);
}; // namespace LuaApiInput

} // namespace lua
} // namespace elona

#pragma once
#include <string>
#include "lua_api_common.hpp"

namespace elona
{
namespace lua
{


/**
 * @luadoc
 *
 * Functions for drawing shapes and assets.
 */
namespace LuaApiDraw
{
Position world_to_screen(int, int);

Position screen_to_world(int, int);

bool is_in_screen(int, int);

void clear_screen(sol::table);

void fill_rect(int, int, int, int, sol::table);

void line_rect(int, int, int, int, sol::table);

void line(int, int, int, int, sol::table);

void text(int, int, const std::string&, sol::table);

void text_shadow(int, int, const std::string&, sol::table, sol::table);

void asset(
    const std::string&,
    int,
    int,
    sol::optional<int>,
    sol::optional<int>);

void chip(const std::string&, int, int, sol::optional<int>, sol::optional<int>);

sol::optional<sol::table> load_asset(const std::string&, int, int);

void copy_region(
    int,
    int,
    int,
    int,
    int,
    int,
    int,
    sol::optional<int>,
    sol::optional<int>);

void copy_region_centered(
    int,
    int,
    int,
    int,
    int,
    int,
    int,
    sol::optional<int>,
    sol::optional<int>);

void copy_region_rotated(
    int,
    int,
    int,
    int,
    int,
    int,
    int,
    double,
    sol::optional<int>,
    sol::optional<int>);

void set_color_mod(sol::table);

void set_screen_offset(int, int);

void set_mode(int, sol::optional<int>);

int current_buffer();

void set_buffer(int);

void set_font(int, sol::optional<EnumString>);

int screen_width();

int screen_height();

int screen_bottom();

void wait(int);

void redraw(sol::optional<bool>);

void update_screen(sol::optional<bool>);

void update_entire_screen(sol::optional<bool>);

int reserve_temp_buffer(int, int);

void free_temp_buffer(int);


void bind(sol::table&);
} // namespace LuaApiDraw
} // namespace lua
} // namespace elona

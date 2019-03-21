#include "lua_api_draw.hpp"
#include "../../data/types/type_asset.hpp"
#include "../../draw.hpp"
#include "../../ui.hpp"

namespace elona
{
namespace lua
{

namespace
{

snail::Color to_color(sol::table table)
{
    if (table.size() >= 4)
    {
        return snail::Color{table[1], table[2], table[3], table[4]};
    }
    else
    {
        return snail::Color{table[1], table[2], table[3]};
    }
}

} // namespace

/**
 * @luadoc
 */
Position LuaApiDraw::world_to_screen(int x, int y)
{
    return Position{(x - scx) * inf_tiles + inf_screenx,
                    (y - scy) * inf_tiles + inf_screeny};
}

/**
 * @luadoc
 */
Position LuaApiDraw::screen_to_world(int x, int y)
{
    return Position{clamp(x - inf_screenx, 0, windoww) / inf_tiles,
                    clamp(y - inf_screeny, 0, (windowh - inf_verh))};
}

bool LuaApiDraw::is_in_screen(int x, int y)
{
    return 0 <= x && x - inf_screenx < (inf_screenw - 1) * inf_tiles &&
        0 <= y && y < (inf_screenh - 1) * inf_tiles;
}

/**
 * @luadoc
 */
void LuaApiDraw::clear_screen(sol::table color)
{
    elona::boxf(to_color(color));
}

/**
 * @luadoc
 */
void LuaApiDraw::fill_rect(
    int x,
    int y,
    int width,
    int height,
    sol::table color)
{
    elona::boxf(x, y, width, height, to_color(color));
}

/**
 * @luadoc
 */
void LuaApiDraw::line_rect(
    int x,
    int y,
    int width,
    int height,
    sol::table color)
{
    elona::boxl(x, y, width, height, to_color(color));
}

/**
 * @luadoc
 */
void LuaApiDraw::line(int x1, int y1, int x2, int y2, sol::table color)
{
    elona::line(x1, y1, x2, y2, to_color(color));
}

/**
 * @luadoc
 */
void LuaApiDraw::text(int x, int y, const std::string& text, sol::table color)
{
    elona::mes(x, y, text, to_color(color));
}

/**
 * @luadoc
 */
void LuaApiDraw::text_shadow(
    int x,
    int y,
    const std::string& text,
    sol::table color,
    sol::table shadow_color)
{
    elona::bmes(text, x, y, to_color(color), to_color(shadow_color));
}

/**
 * @luadoc
 */
void LuaApiDraw::asset(
    const std::string& id,
    int x,
    int y,
    sol::optional<int> width,
    sol::optional<int> height)
{
    const auto info = get_image_info(id);
    int width_value = width ? *width : info.width;
    int height_value = height ? *height : info.height;

    elona::gcopy(
        info.window_id,
        info.x,
        info.y,
        info.width,
        info.height,
        x,
        y,
        width_value,
        height_value);
}

/**
 * @luadoc
 */
void LuaApiDraw::chip(
    const std::string& id,
    int x,
    int y,
    sol::optional<int> width,
    sol::optional<int> height,
    sol::optional<double> rotation)
{
    const auto rect = draw_get_rect(id);
    if (!rect)
    {
        throw sol::error("No such chip " + id);
    }

    int width_value = width ? *width : rect->width;
    int height_value = height ? *height : rect->height;
    double rotation_value = rotation ? *rotation : 0.0;

    grotate(
        rect->buffer,
        rect->x,
        rect->y,
        rect->width,
        rect->height,
        x,
        y,
        width_value,
        height_value,
        rotation_value);
}

/**
 * @luadoc
 */
void LuaApiDraw::set_color_mod(sol::table color)
{
    auto color_value = to_color(color);
    elona::set_color_mod(color_value.r, color_value.g, color_value.b);
}

/**
 * @luadoc
 */
void LuaApiDraw::set_screen_offset(int x, int y)
{
    elona::sxfix = x;
    elona::syfix = y;
}

/**
 * @luadoc set_mode
 */
void LuaApiDraw::set_mode(int mode, sol::optional<int> alpha)
{
    int alpha_value = 255;
    if (alpha)
    {
        alpha_value = *alpha;
    }

    elona::gmode(mode, alpha_value);
}

/**
 * @luadoc set_mode
 */
int LuaApiDraw::current_buffer()
{
    return elona::ginfo(3);
}

/**
 * @luadoc set_mode
 */
void LuaApiDraw::set_buffer(int buffer)
{
    elona::gsel(buffer);
}

/**
 * @luadoc
 */
int LuaApiDraw::screen_width()
{
    return windoww;
}

/**
 * @luadoc
 */
int LuaApiDraw::screen_height()
{
    return windowh;
}

/**
 * @luadoc
 */
int LuaApiDraw::screen_bottom()
{
    return windowh - inf_verh;
}

/**
 * @luadoc
 */
void LuaApiDraw::wait(int msec)
{
    elona::await(msec);
}

/**
 * @luadoc
 */
void LuaApiDraw::redraw()
{
    elona::redraw();
}

/**
 * @luadoc
 */
void LuaApiDraw::update_screen(bool redraw)
{
    int screenupdatebk = elona::screenupdate;
    elona::screenupdate = redraw ? 0 : -1;

    elona::update_screen();

    elona::screenupdate = screenupdatebk;
}

void LuaApiDraw::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, world_to_screen);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, screen_to_world);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, is_in_screen);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, clear_screen);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, fill_rect);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, line_rect);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, line);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, text);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, text_shadow);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, asset);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, chip);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, set_color_mod);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, set_screen_offset);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, set_mode);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, current_buffer);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, set_buffer);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, screen_width);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, screen_height);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, screen_bottom);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, wait);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, redraw);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, update_screen);
}

} // namespace lua
} // namespace elona

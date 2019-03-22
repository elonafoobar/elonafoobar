#include "lua_api_draw.hpp"
#include "../../character.hpp"
#include "../../data/types/type_asset.hpp"
#include "../../draw.hpp"
#include "../../pic_loader/pic_loader.hpp"
#include "../../pic_loader/tinted_buffers.hpp"
#include "../../ui.hpp"
#include "../data_manager.hpp"
#include "../enums/enums.hpp"

namespace elona
{
namespace lua
{

namespace
{

class TempBuffers
{
public:
    int reserve(int width, int height)
    {
        optional<int> buffer_index = none;
        for (int i = 0; i < static_cast<int>(_free_buffers.size()); i++)
        {
            bool is_free = _free_buffers[i];
            if (is_free)
            {
                _free_buffers[i] = false;
                buffer_index = i;
                break;
            }
        }

        if (!buffer_index)
        {
            _free_buffers.push_back(false);
            buffer_index = _free_buffers.size() - 1;
        }

        int real_index = *buffer_index + buffer_start_index;

        int buffer_bk = ginfo(3);
        buffer(real_index, width, height);
        gsel(buffer_bk);

        return real_index;
    }

    void free(int real_index)
    {
        int index = real_index - buffer_start_index;
        if (index < 0 || index >= static_cast<int>(_free_buffers.size()))
        {
            return;
        }
        if (_free_buffers[index] == true)
        {
            return;
        }

        _free_buffers[index] = true;

        int buffer_bk = ginfo(3);
        buffer(real_index, 1, 1);
        gsel(buffer_bk);
    }

private:
    static constexpr int buffer_start_index = 10 + PicLoader::max_buffers +
        TintedBuffers::max_buffers + ELONA_MAX_CHARACTERS;

    std::vector<bool> _free_buffers;
};

TempBuffers temp_buffers;

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

/**
 * @luadoc
 */
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
    int width_value = width.value_or(info.width);
    int height_value = height.value_or(info.height);

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
    sol::optional<int> height)
{
    const auto rect = draw_get_rect(id);
    if (!rect)
    {
        gsel(0);
        throw sol::error("No such chip " + id);
    }

    int width_value = width.value_or(rect->width);
    int height_value = height.value_or(rect->height);

    elona::gcopy(
        rect->buffer,
        rect->x,
        rect->y,
        rect->width,
        rect->height,
        x,
        y,
        width_value,
        height_value);
}

/**
 * @luadoc
 */
sol::optional<sol::table>
LuaApiDraw::load_asset(const std::string& id, int x, int y)
{
    const auto info = get_image_info(id);
    if (!info.file)
    {
        return sol::nullopt;
    }

    elona::picload(*info.file, x, y, false);

    return lua::lua->get_data_manager().get().raw("core.asset", id);
}

/**
 * @luadoc
 */
void LuaApiDraw::copy_region(
    int window_id,
    int x,
    int y,
    int width,
    int height,
    int dst_x,
    int dst_y,
    sol::optional<int> dst_width,
    sol::optional<int> dst_height)
{
    int dst_width_value = dst_width.value_or(width);
    int dst_height_value = dst_height.value_or(height);

    elona::gcopy(
        window_id,
        x,
        y,
        width,
        height,
        dst_x,
        dst_y,
        dst_width_value,
        dst_height_value);
}

/**
 * @luadoc
 */
void LuaApiDraw::copy_region_centered(
    int window_id,
    int center_x,
    int center_y,
    int width,
    int height,
    int dst_x,
    int dst_y,
    sol::optional<int> dst_width,
    sol::optional<int> dst_height)
{
    int dst_width_value = dst_width.value_or(width);
    int dst_height_value = dst_height.value_or(height);

    elona::gcopy_c(
        window_id,
        center_x,
        center_y,
        width,
        height,
        dst_x,
        dst_y,
        dst_width_value,
        dst_height_value);
}

/**
 * @luadoc
 */
void LuaApiDraw::copy_region_rotated(
    int window_id,
    int center_x,
    int center_y,
    int width,
    int height,
    int dst_x,
    int dst_y,
    double angle,
    sol::optional<int> dst_width,
    sol::optional<int> dst_height)
{
    int dst_width_value = dst_width.value_or(width);
    int dst_height_value = dst_height.value_or(height);

    elona::grotate(
        window_id,
        center_x,
        center_y,
        width,
        height,
        dst_x,
        dst_y,
        dst_width_value,
        dst_height_value,
        angle);
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
 * @luadoc set_mode
 */
void LuaApiDraw::set_font(int size, sol::optional<EnumString> style)
{
    auto style_value = snail::Font::Style::bold;
    if (style)
    {
        style_value = LuaEnums::FontStyleTable.ensure_from_string(*style);
    }

    elona::font(size, style_value);
}

/**
 * @luadoc
 */
int LuaApiDraw::screen_width()
{
    return elona::windoww;
}

/**
 * @luadoc
 */
int LuaApiDraw::screen_height()
{
    return elona::windowh;
}

/**
 * @luadoc
 */
int LuaApiDraw::screen_bottom()
{
    return elona::windowh - elona::inf_verh;
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
void LuaApiDraw::redraw(sol::optional<bool> step_frame)
{
    bool step_frame_value = step_frame.value_or(false);
    if (step_frame_value)
    {
        elona::scrturn++;
    }

    elona::redraw();
}

/**
 * @luadoc
 */
void LuaApiDraw::update_screen(sol::optional<bool> redraw)
{
    bool redraw_value = redraw.value_or(true);
    int screenupdatebk = elona::screenupdate;
    elona::screenupdate = redraw_value ? 0 : -1;

    elona::update_screen();

    elona::screenupdate = screenupdatebk;
}

/**
 * @luadoc
 */
void LuaApiDraw::update_entire_screen(sol::optional<bool> redraw)
{
    bool redraw_value = redraw.value_or(true);
    int screenupdatebk = elona::screenupdate;
    elona::screenupdate = redraw_value ? 0 : -1;

    elona::update_entire_screen();

    elona::screenupdate = screenupdatebk;
}

/**
 * @luadoc
 */
int LuaApiDraw::reserve_temp_buffer(int width, int height)
{
    return temp_buffers.reserve(width, height);
}

/**
 * @luadoc
 */
void LuaApiDraw::free_temp_buffer(int buffer)
{
    temp_buffers.free(buffer);
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
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, load_asset);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, copy_region);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, copy_region_centered);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, copy_region_rotated);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, set_color_mod);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, set_mode);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, current_buffer);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, set_buffer);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, set_font);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, screen_width);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, screen_height);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, screen_bottom);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, wait);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, redraw);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, update_screen);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, update_entire_screen);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, reserve_temp_buffer);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDraw, free_temp_buffer);
}

} // namespace lua
} // namespace elona

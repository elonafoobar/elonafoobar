#pragma once

#include <string>
#include "blend_mode.hpp"
#include "color.hpp"
#include "filesystem.hpp"
#include "font.hpp"
#include "image.hpp"
#include "rect.hpp"
#include "window.hpp"

namespace elona
{
namespace snail
{
namespace hsp
{

template <typename T>
constexpr T rad2deg(T rad)
{
    return rad * 180.0 / 3.14159265358979323846264;
}

template <typename T>
inline T clamp(const T& x, const T& min, const T& max)
{
    return std::min(std::max(x, min), max);
}

int timeGetTime();
void mes(int x, int y, const std::string& text, const snail::Color& color);
void mesbox(std::string& buffer, int keywait, bool text);
void picload(Image& img, int mode);
void pos(int x, int y);
void redraw();
void set_color_mod(int r, int g, int b, int window_id);
void onkey_0();
void await(int msec);
void boxf(int x1, int y1, int x2, int y2, const Color& color);
void boxf(const Color& color);
void buffer(int window_id, int width, int height);
void font(int size, Font::Style style, const fs::path& filepath);
void gcopy(
    int window_id,
    int src_x,
    int src_y,
    int src_width,
    int src_height,
    int dst_width,
    int dst_height);
int ginfo(int type);
void gmode(int mode, int alpha);
void grotate(
    int window_id,
    int src_x,
    int src_y,
    int src_width,
    int src_height,
    double angle);
void grotate(
    int window_id,
    int src_x,
    int src_y,
    int src_width,
    int src_height,
    int dst_width,
    int dst_height,
    double angle);
void gsel(int window_id);
void line(int x1, int y1, int x2, int y2, const snail::Color& color);
void title(
    const std::string& title_str,
    const std::string& display_mode,
    Window::FullscreenMode fullscreen_mode);

} // namespace hsp
} // namespace snail
} // namespace elona

#include <sstream>
#include "../detail/sdl.hpp"


namespace elona
{
namespace snail
{

void renderer::set_blend_mode(blend_mode_t)
{
}

::SDL_Texture* renderer::render_target()
{
    return nullptr;
}

::SDL_Renderer* renderer::ptr()
{
    return nullptr;
}

void renderer::set_render_target(::SDL_Texture*)
{
}

void renderer::set_draw_color(const color&)
{
}


renderer::renderer(window&, int)
{
}

renderer::~renderer()
{
}

void renderer::clear()
{
}


void renderer::present()
{
}


void renderer::render_point(int, int)
{
}


void renderer::fill_rect(int, int, int, int)
{
}


rect renderer::render_text(const std::string&, int, int, const color&, double)
{
    return rect{0, 0, 0, 0};
}



rect renderer::render_text_with_shadow(
    const std::string&,
    int,
    int,
    const color&,
    const color&)
{
    return rect{0, 0, 0, 0};
}


rect renderer::render_multiline_text(const std::string&, int, int, const color&)
{
    return rect{0, 0, 0, 0};
}


size renderer::calculate_text_size(const std::string&)
{
    return {0, 0};
}


void renderer::render_line(int, int, int, int)
{
}


void renderer::render_image(image_base&, int, int)
{
}


void renderer::render_image(image_base&, int, int, int, int)
{
}


void renderer::render_image(image_base&, int, int, int, int, int, int)
{
}


void renderer::render_image(image_base&, int, int, int, int, int, int, int, int)
{
}


void renderer::render_image(::SDL_Texture*, int, int)
{
}


void renderer::render_image(::SDL_Texture*, int, int, int, int)
{
}


void renderer::render_image(::SDL_Texture*, int, int, int, int, int, int)
{
}


void renderer::render_image(
    ::SDL_Texture*,
    int,
    int,
    int,
    int,
    int,
    int,
    int,
    int)
{
}


} // namespace snail
} // namespace elona

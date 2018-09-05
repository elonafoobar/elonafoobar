#include <sstream>
#include "../detail/sdl.hpp"


namespace elona
{
namespace snail
{

void Renderer::set_blend_mode(BlendMode)
{
}

::SDL_Texture* Renderer::render_target()
{
    return nullptr;
}

::SDL_Renderer* Renderer::ptr()
{
    return nullptr;
}

void Renderer::set_render_target(::SDL_Texture*)
{
}

void Renderer::set_draw_color(const Color&)
{
}


Renderer::Renderer(Window&, Flag)
{
}

Renderer::~Renderer()
{
}

void Renderer::clear()
{
}


void Renderer::present()
{
}


void Renderer::render_point(int, int)
{
}


void Renderer::fill_rect(int, int, int, int)
{
}


Rect Renderer::render_text(const std::string&, int, int, const Color&, double)
{
    return Rect{0, 0, 0, 0};
}



Rect Renderer::render_text_with_shadow(
    const std::string&,
    int,
    int,
    const Color&,
    const Color&,
    double)
{
    return Rect{0, 0, 0, 0};
}


Rect Renderer::render_multiline_text(const std::string&, int, int, const Color&)
{
    return Rect{0, 0, 0, 0};
}


Size Renderer::calculate_text_size(const std::string&)
{
    return {0, 0};
}


void Renderer::render_line(int, int, int, int)
{
}


void Renderer::render_image(ImageBase&, int, int)
{
}


void Renderer::render_image(ImageBase&, int, int, int, int)
{
}


void Renderer::render_image(ImageBase&, int, int, int, int, int, int)
{
}


void Renderer::render_image(ImageBase&, int, int, int, int, int, int, int, int)
{
}


void Renderer::render_image(::SDL_Texture*, int, int)
{
}


void Renderer::render_image(::SDL_Texture*, int, int, int, int)
{
}


void Renderer::render_image(::SDL_Texture*, int, int, int, int, int, int)
{
}


void Renderer::render_image(
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


void Renderer::render_image_crop(ImageBase&, int, int, int, int, int, int)
{
}


void render_image_crop(::SDL_Texture*, int, int, int, int, int, int)
{
}


} // namespace snail
} // namespace elona

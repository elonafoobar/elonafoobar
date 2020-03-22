#include "../../renderer.hpp"

#include <iostream>
#include <sstream>

#include "../../detail/sdl.hpp"
#include "../../surface.hpp"


namespace elona
{
namespace snail
{

namespace
{

template <typename F>
Rect _render_text_base(
    F draw,
    const std::string& text,
    int x,
    int y,
    const Color& color,
    double scale,
    bool blended_text_rendering,
    Font& font,
    Renderer::TextAlignment text_alignment,
    Renderer::TextBaseline text_baseline,
    ::SDL_Renderer* ptr)
{
    if (text.empty())
        return Rect{x, y, 0, 0};

    auto render_func = blended_text_rendering ? &::TTF_RenderUTF8_Blended
                                              : &::TTF_RenderUTF8_Solid;

    auto surface = detail::enforce_ttf(
        render_func(font.ptr(), text.c_str(), detail::to_sdl_color(color)));
    auto texture =
        detail::enforce_sdl(::SDL_CreateTextureFromSurface(ptr, surface));
    detail::enforce_sdl(::SDL_SetTextureAlphaMod(texture, color.a));

    int x_;
    int y_;
    int width = static_cast<int>(static_cast<double>(surface->w) * scale);
    int height = static_cast<int>(static_cast<double>(surface->h) * scale);

    switch (text_alignment)
    {
    case Renderer::TextAlignment::left: x_ = x; break;
    case Renderer::TextAlignment::center: x_ = x - width / 2; break;
    case Renderer::TextAlignment::right: x_ = x - width; break;
    }
    switch (text_baseline)
    {
    case Renderer::TextBaseline::top: y_ = y; break;
    case Renderer::TextBaseline::middle: y_ = y - height / 2; break;
    case Renderer::TextBaseline::bottom: y_ = y - height; break;
    }
    ::SDL_Rect dst{x_, y_, width, height};
    draw(texture, dst);

    ::SDL_FreeSurface(surface);
    ::SDL_DestroyTexture(texture);

    return Rect{x_, y_, width, height};
}

} // namespace

SDL_Renderer* _ptr;

void Renderer::set_blend_mode(BlendMode blend_mode)
{
    _blend_mode = blend_mode;

    switch (_blend_mode)
    {
    case BlendMode::none:
        detail::enforce_sdl(
            ::SDL_SetRenderDrawBlendMode(ptr(), SDL_BLENDMODE_NONE));
        break;
    case BlendMode::blend:
        detail::enforce_sdl(
            ::SDL_SetRenderDrawBlendMode(ptr(), SDL_BLENDMODE_BLEND));
        break;
    case BlendMode::add:
        detail::enforce_sdl(
            ::SDL_SetRenderDrawBlendMode(ptr(), SDL_BLENDMODE_ADD));
        break;
    }
}

::SDL_Texture* Renderer::render_target()
{
    return ::SDL_GetRenderTarget(ptr());
}

::SDL_Renderer* Renderer::ptr()
{
    return _ptr;
}

void Renderer::set_render_target(::SDL_Texture* texture)
{
    detail::enforce_sdl(::SDL_SetRenderTarget(ptr(), texture));
}

void Renderer::set_draw_color(const Color& color)
{
    detail::enforce_sdl(
        ::SDL_SetRenderDrawColor(ptr(), color.r, color.g, color.b, color.a));
}

Renderer::Renderer(Window& target_window, Flag flag)
{
    _ptr = detail::enforce_sdl(::SDL_CreateRenderer(
        target_window.ptr(), -1, static_cast<::SDL_RendererFlags>(flag)));
    detail::enforce_sdl(
        ::SDL_SetRenderDrawBlendMode(ptr(), SDL_BLENDMODE_BLEND));
}

Renderer::~Renderer()
{
    ::SDL_DestroyRenderer(_ptr);
}


void Renderer::clear()
{
    detail::enforce_sdl(::SDL_RenderClear(ptr()));
}


void Renderer::present()
{
    ::SDL_RenderPresent(ptr());
}

void Renderer::render_point(int x, int y)
{
    detail::enforce_sdl(::SDL_RenderDrawPoint(ptr(), x, y));
}


void Renderer::fill_rect(int x, int y, int width, int height)
{
    ::SDL_Rect rect{x, y, width, height};
    detail::enforce_sdl(::SDL_RenderFillRect(ptr(), &rect));
}


Rect Renderer::render_text(
    const std::string& text,
    int x,
    int y,
    const Color& color,
    double scale)
{
    return _render_text_base(
        [this](const auto& texture, const auto& dst) {
            detail::enforce_sdl(
                ::SDL_RenderCopy(ptr(), texture, nullptr, &dst));
        },
        text,
        x,
        y,
        color,
        scale,
        _blended_text_rendering,
        _font,
        _text_alignment,
        _text_baseline,
        ptr());
}



Rect Renderer::render_text_with_shadow(
    const std::string& text,
    int x,
    int y,
    const Color& text_color,
    const Color& shadow_color,
    double scale)
{
    // Render shadow. The created texture is reused in each loop.
    _render_text_base(
        [this](const auto& texture, const auto& dst) {
            for (int dy : {-1, 0, 1})
            {
                for (int dx : {-1, 0, 1})
                {
                    if (dx == 0 && dy == 0)
                        continue;

                    auto dst_ = dst;
                    dst_.x += dx;
                    dst_.y += dy;
                    detail::enforce_sdl(
                        ::SDL_RenderCopy(ptr(), texture, nullptr, &dst_));
                }
            }
        },
        text,
        x,
        y,
        shadow_color,
        scale,
        _blended_text_rendering,
        _font,
        _text_alignment,
        _text_baseline,
        ptr());

    // Render text.
    return render_text(text, x, y, text_color, scale);
}


Rect Renderer::render_multiline_text(
    const std::string& text,
    int x,
    int y,
    const Color& text_color)
{
    const auto line_skip = ::TTF_FontLineSkip(_font.ptr());

    Rect ret = {x, y, 0, 0};
    auto i = 0;
    std::istringstream stream{text};
    std::string line;
    while (std::getline(stream, line))
    {
        const auto r = render_text(line, x, y + line_skip * i, text_color);
        ret.x = std::max(ret.x, r.x);
        ret.width = std::max(ret.width, r.width);
        ret.height += r.height;
        ++i;
    }

    return ret;
}


Size Renderer::calculate_text_size(const std::string& text)
{
    int width;
    int height;
    detail::enforce_ttf(
        ::TTF_SizeUTF8(_font.ptr(), text.c_str(), &width, &height));
    return {width, height};
}


void Renderer::render_line(int start_x, int start_y, int end_x, int end_y)
{
    detail::enforce_sdl(
        ::SDL_RenderDrawLine(ptr(), start_x, start_y, end_x, end_y));
}


void Renderer::render_image(Image& image, int dst_x, int dst_y)
{
    render_image(
        image,
        0,
        0,
        image.width(),
        image.height(),
        dst_x,
        dst_y,
        image.width(),
        image.height());
}


void Renderer::render_image(
    Image& image,
    int dst_x,
    int dst_y,
    int dst_width,
    int dst_height)
{
    render_image(
        image,
        0,
        0,
        image.width(),
        image.height(),
        dst_x,
        dst_y,
        dst_width,
        dst_height);
}


void Renderer::render_image(
    Image& image,
    int src_x,
    int src_y,
    int src_width,
    int src_height,
    int dst_x,
    int dst_y)
{
    render_image(
        image,
        src_x,
        src_y,
        src_width,
        src_height,
        dst_x,
        dst_y,
        src_width,
        src_height);
}


void Renderer::render_image(
    Image& image,
    int src_x,
    int src_y,
    int src_width,
    int src_height,
    int dst_x,
    int dst_y,
    int dst_width,
    int dst_height)
{
    image._render(
        ptr(),
        _blend_mode,
        src_x,
        src_y,
        src_width,
        src_height,
        dst_x,
        dst_y,
        dst_width,
        dst_height);
}


void Renderer::render_image(::SDL_Texture* image, int dst_x, int dst_y)
{
    int img_width;
    int img_height;
    detail::enforce_sdl(
        ::SDL_QueryTexture(image, NULL, NULL, &img_width, &img_height));
    render_image(
        image,
        0,
        0,
        img_width,
        img_height,
        dst_x,
        dst_y,
        img_width,
        img_height);
}


void Renderer::render_image(
    ::SDL_Texture* image,
    int dst_x,
    int dst_y,
    int dst_width,
    int dst_height)
{
    int img_width;
    int img_height;
    detail::enforce_sdl(
        ::SDL_QueryTexture(image, NULL, NULL, &img_width, &img_height));
    render_image(
        image,
        0,
        0,
        img_width,
        img_height,
        dst_x,
        dst_y,
        dst_width,
        dst_height);
}


void Renderer::render_image(
    ::SDL_Texture* image,
    int src_x,
    int src_y,
    int src_width,
    int src_height,
    int dst_x,
    int dst_y)
{
    render_image(
        image,
        src_x,
        src_y,
        src_width,
        src_height,
        dst_x,
        dst_y,
        src_width,
        src_height);
}


void Renderer::render_image(
    ::SDL_Texture* image,
    int src_x,
    int src_y,
    int src_width,
    int src_height,
    int dst_x,
    int dst_y,
    int dst_width,
    int dst_height)
{
    switch (_blend_mode)
    {
    case BlendMode::none:
        detail::enforce_sdl(
            ::SDL_SetTextureBlendMode(image, ::SDL_BLENDMODE_NONE));
        break;
    case BlendMode::blend:
        detail::enforce_sdl(
            ::SDL_SetTextureBlendMode(image, ::SDL_BLENDMODE_BLEND));
        break;
    case BlendMode::add:
        detail::enforce_sdl(
            ::SDL_SetTextureBlendMode(image, ::SDL_BLENDMODE_ADD));
        break;
    }

    ::SDL_Rect src{src_x, src_y, src_width, src_height};
    ::SDL_Rect dst{dst_x, dst_y, dst_width, dst_height};
    detail::enforce_sdl(::SDL_RenderCopy(ptr(), image, &src, &dst));
}


void Renderer::render_image_crop(
    Image& image,
    int src_x,
    int src_y,
    int src_width,
    int src_height,
    int dst_x,
    int dst_y)
{
    render_image_crop(
        image.ptr(), src_x, src_y, src_width, src_height, dst_x, dst_y);
}


void Renderer::render_image_crop(
    ::SDL_Texture* image,
    int src_x,
    int src_y,
    int src_width,
    int src_height,
    int dst_x,
    int dst_y)
{
    switch (_blend_mode)
    {
    case BlendMode::none:
        detail::enforce_sdl(
            ::SDL_SetTextureBlendMode(image, ::SDL_BLENDMODE_NONE));
        break;
    case BlendMode::blend:
        detail::enforce_sdl(
            ::SDL_SetTextureBlendMode(image, ::SDL_BLENDMODE_BLEND));
        break;
    case BlendMode::add:
        detail::enforce_sdl(
            ::SDL_SetTextureBlendMode(image, ::SDL_BLENDMODE_ADD));
        break;
    }

    ::SDL_Rect src{src_x, src_y, src_width, src_height};
    ::SDL_Rect dst{dst_x, dst_y, src_width, src_height};
    detail::enforce_sdl(
        ::SDL_RenderCopyEx(ptr(), image, &src, &dst, 0, 0, ::SDL_FLIP_NONE));
}



Surface Renderer::take_screenshot()
{
    const auto format = static_cast<Uint32>(Surface::Format::argb8888);
    int width;
    int height;
    detail::enforce_sdl(
        ::SDL_QueryTexture(render_target(), nullptr, nullptr, &width, &height));

    const auto screenshot =
        ::SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, format);
    detail::enforce_sdl(::SDL_RenderReadPixels(
        ptr(), nullptr, format, screenshot->pixels, screenshot->pitch));

    return Surface{screenshot};
}

} // namespace snail
} // namespace elona

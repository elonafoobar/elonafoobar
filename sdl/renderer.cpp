#include "renderer.hpp"
#include <sstream>

using namespace snail;


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


void Renderer::set_draw_color(const Color& color)
{
    detail::enforce_sdl(
        ::SDL_SetRenderDrawColor(ptr(), color.r, color.g, color.b, color.a));
}


Renderer::Renderer(Window& target_window, int flag)
    : _font("font/APJapanesefontT.ttf", 16) // TODO
    , _ptr(
          detail::enforce_sdl(::SDL_CreateRenderer(
              target_window.ptr(),
              -1,
              static_cast<::SDL_RendererFlags>(flag))),
          ::SDL_DestroyRenderer)
{
    detail::enforce_sdl(
        ::SDL_SetRenderDrawBlendMode(ptr(), SDL_BLENDMODE_BLEND));

    detail::current_renderer = this;
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


Renderer::Rect
Renderer::render_text(const std::string& text, int x, int y, const Color& color)
{
    if (text.empty())
        return Rect{x, y, 0, 0};

    // auto surface = detail::enforce_ttf(
    //     ::TTF_RenderUTF8_Blended(_font.ptr(), text.c_str(),
    //     detail::to_sdl_color(color)));
    auto surface = detail::enforce_ttf(::TTF_RenderUTF8_Solid(
        _font.ptr(), text.c_str(), detail::to_sdl_color(color)));
    auto texture =
        detail::enforce_sdl(::SDL_CreateTextureFromSurface(ptr(), surface));

    int x_;
    int y_;
    auto width = surface->w;
    auto height = surface->h;

    switch (_text_alignment)
    {
    case TextAlignment::left: x_ = x; break;
    case TextAlignment::center: x_ = x - width / 2; break;
    case TextAlignment::right: x_ = x - width; break;
    }
    switch (_text_baseline)
    {
    case TextBaseline::top: y_ = y; break;
    case TextBaseline::middle: y_ = y - height / 2; break;
    case TextBaseline::bottom: y_ = y - height; break;
    }
    ::SDL_Rect dst = {x_, y_, width, height};
    detail::enforce_sdl(::SDL_RenderCopy(ptr(), texture, nullptr, &dst));

    ::SDL_FreeSurface(surface);
    ::SDL_DestroyTexture(texture);

    return Rect{x_, y_, width, height};
}



Renderer::Rect Renderer::render_text_with_shadow(
    const std::string& text,
    int x,
    int y,
    const Color& text_color,
    const Color& shadow_color)
{
    // Render shadow.
    for (int dy : {-1, 0, 1})
    {
        for (int dx : {-1, 0, 1})
        {
            if (dx == 0 && dy == 0)
                continue;
            render_text(text, x + dx, y + dy, shadow_color);
        }
    }

    // Render text.
    return render_text(text, x, y, text_color);
}


Renderer::Rect Renderer::render_multiline_text(
    const std::string& text,
    int x,
    int y,
    const Color& color)
{
    const auto line_skip = ::TTF_FontLineSkip(_font.ptr());

    Rect ret = {x, y, 0, 0};
    auto i = 0;
    std::istringstream stream{text};
    std::string line;
    while (std::getline(stream, line))
    {
        const auto r = render_text(line, x, y + line_skip * i, color);
        ret.x = std::max(ret.x, r.x);
        ret.width = std::max(ret.width, r.width);
        ret.height += r.height;
        ++i;
    }

    return ret;
}


Renderer::Size Renderer::calculate_text_size(const std::string& text)
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

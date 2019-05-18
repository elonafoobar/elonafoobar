#include "image.hpp"
#include "application.hpp"
#include "renderer.hpp"



namespace elona
{
namespace snail
{

Image::Image(const fs::path& filepath, optional<Color> keycolor)
{
    auto surface = detail::enforce_img(
        ::IMG_Load(filepathutil::to_utf8_path(filepath).c_str()));

    if (keycolor)
    {
        detail::enforce_sdl(::SDL_SetColorKey(
            surface,
            true,
            ::SDL_MapRGB(
                surface->format, keycolor->r, keycolor->g, keycolor->b)));
    }

    _ptr.reset(
        detail::enforce_sdl(::SDL_CreateTextureFromSurface(
            Application::instance().get_renderer().ptr(), surface)),
        ::SDL_DestroyTexture);
    _width = surface->w;
    _height = surface->h;

    ::SDL_FreeSurface(surface);
}



Image::Image(::SDL_Texture* ptr)
{
    _ptr.reset(ptr, ::SDL_DestroyTexture);
}



void Image::_render(
    ::SDL_Renderer* renderer,
    BlendMode blend_mode,
    int src_x,
    int src_y,
    int src_width,
    int src_height,
    int dst_x,
    int dst_y,
    int dst_width,
    int dst_height)
{
    switch (blend_mode)
    {
    case BlendMode::none:
        detail::enforce_sdl(
            ::SDL_SetTextureBlendMode(_ptr.get(), ::SDL_BLENDMODE_NONE));
        break;
    case BlendMode::blend:
        detail::enforce_sdl(
            ::SDL_SetTextureBlendMode(_ptr.get(), ::SDL_BLENDMODE_BLEND));
        break;
    case BlendMode::add:
        detail::enforce_sdl(
            ::SDL_SetTextureBlendMode(_ptr.get(), ::SDL_BLENDMODE_ADD));
        break;
    }

    const auto src = ::SDL_Rect{src_x, src_y, src_width, src_height};
    const auto dst = ::SDL_Rect{dst_x, dst_y, dst_width, dst_height};
    detail::enforce_sdl(::SDL_RenderCopy(renderer, _ptr.get(), &src, &dst));
}

} // namespace snail
} // namespace elona

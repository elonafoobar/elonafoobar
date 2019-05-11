#include "image.hpp"
#include "application.hpp"
#include "renderer.hpp"
#include "surface.hpp"



namespace elona
{
namespace snail
{

Image::Image(const fs::path& filepath, optional<Color> keycolor)
{
    auto surface = Surface(filepath, keycolor);

    _ptr.reset(
        detail::enforce_sdl(::SDL_CreateTextureFromSurface(
            Application::instance().get_renderer().ptr(), surface.ptr())),
        ::SDL_DestroyTexture);
    _width = surface.width();
    _height = surface.height();
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

#include "surface.hpp"



namespace elona
{
namespace snail
{

Surface::Surface(
    const fs::path& filepath,
    optional<Color> keycolor,
    optional<Format> format)
{
    _ptr.reset(
        detail::enforce_img(
            ::IMG_Load(filepathutil::to_utf8_path(filepath).c_str())),
        ::SDL_FreeSurface);

    if (keycolor)
    {
        detail::enforce_sdl(::SDL_SetColorKey(
            _ptr.get(),
            true,
            ::SDL_MapRGB(_ptr->format, keycolor->r, keycolor->g, keycolor->b)));
    }
    if (format)
    {
        _ptr.reset(
            detail::enforce_sdl(::SDL_ConvertSurfaceFormat(
                _ptr.get(), static_cast<Uint32>(*format), 0)),
            ::SDL_FreeSurface);
    }

    _width = _ptr->w;
    _height = _ptr->h;
}



Surface::Surface(::SDL_Surface* ptr)
{
    _ptr.reset(ptr, ::SDL_FreeSurface);
}

} // namespace snail
} // namespace elona

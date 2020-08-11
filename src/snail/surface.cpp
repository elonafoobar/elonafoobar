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
        detail::enforce_img(::IMG_Load(filepath.to_u8string().c_str())),
        ::SDL_FreeSurface);

    if (keycolor)
    {
        detail::enforce_sdl(::SDL_SetColorKey(
            ptr(),
            true,
            ::SDL_MapRGB(_ptr->format, keycolor->r, keycolor->g, keycolor->b)));
    }
    if (format)
    {
        _ptr.reset(
            detail::enforce_sdl(::SDL_ConvertSurfaceFormat(
                ptr(), static_cast<Uint32>(*format), 0)),
            ::SDL_FreeSurface);
    }
}



Surface::Surface(::SDL_Surface* ptr)
{
    _ptr.reset(ptr, ::SDL_FreeSurface);
}

} // namespace snail
} // namespace elona

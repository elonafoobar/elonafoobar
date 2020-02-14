#include "../../image.hpp"

#include "../../application.hpp"
#include "../../renderer.hpp"
#include "../../surface.hpp"



namespace elona
{
namespace snail
{

Image::Image(const fs::path& filepath, optional<Color> keycolor)
{
    Surface surface{filepath, keycolor};

    _width = surface.width();
    _height = surface.height();
}



Image::Image(::SDL_Texture* ptr)
{
    _ptr.reset(ptr, ::SDL_DestroyTexture);
}



void Image::
    _render(::SDL_Renderer*, BlendMode, int, int, int, int, int, int, int, int)
{
}

} // namespace snail
} // namespace elona

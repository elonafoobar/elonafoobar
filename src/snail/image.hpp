#pragma once

#include <memory>
#include <string>

#include "../elona/optional.hpp"
#include "blend_mode.hpp"
#include "color.hpp"
#include "detail/sdl.hpp"
#include "filesystem.hpp"



namespace elona
{
namespace snail
{

class Image
{
public:
    explicit Image(const fs::path& filepath, optional<Color> keycolor = none);

    explicit Image(::SDL_Texture* ptr);


    int width() const noexcept
    {
        return _width;
    }


    int height() const noexcept
    {
        return _height;
    }


    ::SDL_Texture* ptr() noexcept
    {
        return _ptr.get();
    }


    void set_color(uint8_t r, uint8_t g, uint8_t b)
    {
        detail::enforce_sdl(::SDL_SetTextureColorMod(ptr(), r, g, b));
    }


    void set_alpha(uint8_t a)
    {
        detail::enforce_sdl(::SDL_SetTextureAlphaMod(ptr(), a));
    }


    void _render(
        ::SDL_Renderer* renderer,
        BlendMode blend_mode,
        int src_x,
        int src_y,
        int src_width,
        int src_height,
        int dst_x,
        int dst_y,
        int dst_width,
        int dst_height);


protected:
    int _width = 0;
    int _height = 0;
    std::shared_ptr<::SDL_Texture> _ptr;
};

} // namespace snail
} // namespace elona

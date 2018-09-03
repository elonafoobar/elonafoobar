#pragma once

#include <memory>
#include <string>
#include "../optional.hpp"
#include "blend_mode.hpp"
#include "color.hpp"
#include "detail/sdl.hpp"
#include "filesystem.hpp"


namespace elona
{
namespace snail
{


class ImageBase
{
public:
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


    virtual void _render(
        ::SDL_Renderer* renderer,
        BlendMode blend_mode,
        int src_x,
        int src_y,
        int src_width,
        int src_height,
        int dst_x,
        int dst_y,
        int dst_width,
        int dst_height) = 0;


protected:
    int _width = 0;
    int _height = 0;
    std::shared_ptr<::SDL_Texture> _ptr;
};



class NullImage : public ImageBase
{
public:
    NullImage()
    {
    }


    virtual void _render(
        ::SDL_Renderer*,
        BlendMode,
        int,
        int,
        int,
        int,
        int,
        int,
        int,
        int) override
    {
    }
};



class BasicImage : public ImageBase
{
public:
    explicit BasicImage(
        const fs::path& filepath,
        const optional<color>& keycolor = none);

    explicit BasicImage(::SDL_Texture* ptr);

    virtual ~BasicImage() = default;


    virtual void _render(
        ::SDL_Renderer* renderer,
        BlendMode blend_mode,
        int src_x,
        int src_y,
        int src_width,
        int src_height,
        int dst_x,
        int dst_y,
        int dst_width,
        int dst_height) override;
};



class FrameImage : public ImageBase
{
    int offset_x() const noexcept
    {
        return _offset_x;
    }


    int offset_y() const noexcept
    {
        return _offset_y;
    }


    FrameImage(
        BasicImage& source,
        int offset_x,
        int offset_y,
        int width,
        int height);


    virtual void _render(
        ::SDL_Renderer* renderer,
        BlendMode blend_mode,
        int src_x,
        int src_y,
        int src_width,
        int src_height,
        int dst_x,
        int dst_y,
        int dst_width,
        int dst_height) override;


private:
    int _offset_x;
    int _offset_y;
};


} // namespace snail
} // namespace elona

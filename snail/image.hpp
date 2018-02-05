#pragma once

#include <memory>
#include <optional>
#include <string>
#include "blendmode.hpp"
#include "color.hpp"
#include "detail/sdl.hpp"


namespace snail
{
class Image
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



class NullImage : public Image
{
public:
    NullImage()
    {
    }


    virtual void
    _render(::SDL_Renderer*, BlendMode, int, int, int, int, int, int, int, int)
        override
    {
    }
};



class BasicImage : public Image
{
public:
    explicit BasicImage(
        const std::string& filepath,
        const std::optional<Color>& keycolor = std::nullopt);

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



class FrameImage : public Image
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

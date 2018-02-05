#pragma once

#include <memory>
#include <optional>
#include <string>
#include "../filesystem.hpp"
#include "blend_mode.hpp"
#include "color.hpp"
#include "detail/sdl.hpp"


namespace elona::snail
{


class image_base
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
        blend_mode_t blend_mode,
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



class null_image : public image_base
{
public:
    null_image()
    {
    }


    virtual void _render(
        ::SDL_Renderer*,
        blend_mode_t,
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



class basic_image : public image_base
{
public:
    explicit basic_image(
        const fs::path& filepath,
        const std::optional<color>& keycolor = std::nullopt);

    explicit basic_image(::SDL_Texture* ptr);

    virtual ~basic_image() = default;


    virtual void _render(
        ::SDL_Renderer* renderer,
        blend_mode_t blend_mode,
        int src_x,
        int src_y,
        int src_width,
        int src_height,
        int dst_x,
        int dst_y,
        int dst_width,
        int dst_height) override;
};



class frame_image : public image_base
{
    int offset_x() const noexcept
    {
        return _offset_x;
    }


    int offset_y() const noexcept
    {
        return _offset_y;
    }


    frame_image(
        basic_image& source,
        int offset_x,
        int offset_y,
        int width,
        int height);


    virtual void _render(
        ::SDL_Renderer* renderer,
        blend_mode_t blend_mode,
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


} // namespace elona::snail

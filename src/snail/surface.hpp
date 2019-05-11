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

class Surface
{
public:
    enum class Format : Uint32
    {
        unknown = SDL_PIXELFORMAT_UNKNOWN,
        index1lsb = SDL_PIXELFORMAT_INDEX1LSB,
        index1msb = SDL_PIXELFORMAT_INDEX1MSB,
        index4lsb = SDL_PIXELFORMAT_INDEX4LSB,
        index4msb = SDL_PIXELFORMAT_INDEX4MSB,
        index8 = SDL_PIXELFORMAT_INDEX8,
        rgb332 = SDL_PIXELFORMAT_RGB332,
        rgb444 = SDL_PIXELFORMAT_RGB444,
        rgb555 = SDL_PIXELFORMAT_RGB555,
        bgr555 = SDL_PIXELFORMAT_BGR555,
        argb4444 = SDL_PIXELFORMAT_ARGB4444,
        rgba4444 = SDL_PIXELFORMAT_RGBA4444,
        abgr4444 = SDL_PIXELFORMAT_ABGR4444,
        bgra4444 = SDL_PIXELFORMAT_BGRA4444,
        argb1555 = SDL_PIXELFORMAT_ARGB1555,
        rgba5551 = SDL_PIXELFORMAT_RGBA5551,
        abgr1555 = SDL_PIXELFORMAT_ABGR1555,
        bgra5551 = SDL_PIXELFORMAT_BGRA5551,
        rgb565 = SDL_PIXELFORMAT_RGB565,
        bgr565 = SDL_PIXELFORMAT_BGR565,
        rgb24 = SDL_PIXELFORMAT_RGB24,
        bgr24 = SDL_PIXELFORMAT_BGR24,
        rgb888 = SDL_PIXELFORMAT_RGB888,
        rgbx8888 = SDL_PIXELFORMAT_RGBX8888,
        bgr888 = SDL_PIXELFORMAT_BGR888,
        bgrx8888 = SDL_PIXELFORMAT_BGRX8888,
        argb8888 = SDL_PIXELFORMAT_ARGB8888,
        rgba8888 = SDL_PIXELFORMAT_RGBA8888,
        abgr8888 = SDL_PIXELFORMAT_ABGR8888,
        bgra8888 = SDL_PIXELFORMAT_BGRA8888,
        argb2101010 = SDL_PIXELFORMAT_ARGB2101010,
        rgba32 = SDL_PIXELFORMAT_RGBA32,
        argb32 = SDL_PIXELFORMAT_ARGB32,
        bgra32 = SDL_PIXELFORMAT_BGRA32,
        abgr32 = SDL_PIXELFORMAT_ABGR32,
        yv12 = SDL_PIXELFORMAT_YV12,
        iyuv = SDL_PIXELFORMAT_IYUV,
        yuy2 = SDL_PIXELFORMAT_YUY2,
        uyvy = SDL_PIXELFORMAT_UYVY,
        yvyu = SDL_PIXELFORMAT_YVYU,
        nv12 = SDL_PIXELFORMAT_NV12,
        nv21 = SDL_PIXELFORMAT_NV21,
    };

    explicit Surface(
        const fs::path& filepath,
        optional<Color> keycolor = none,
        optional<Format> = none);

    explicit Surface(::SDL_Surface* ptr);


    int width() const noexcept
    {
        return _width;
    }


    int height() const noexcept
    {
        return _height;
    }


    ::SDL_Surface* ptr() noexcept
    {
        return _ptr.get();
    }


    void* pixels() noexcept
    {
        return _ptr.get()->pixels;
    }


protected:
    int _width = 0;
    int _height = 0;
    std::shared_ptr<::SDL_Surface> _ptr;
};

} // namespace snail
} // namespace elona

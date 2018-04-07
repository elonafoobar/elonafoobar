#pragma once

#include <stdexcept>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "../../lib/noncopyable.hpp"



namespace elona
{
namespace snail
{
namespace detail
{



class sdl_error : public std::runtime_error
{
public:
    explicit sdl_error(const std::string& message)
        : std::runtime_error(message)
    {
    }
};



void enforce_sdl(int result);
void enforce_ttf(int result);
void enforce_img(int result);
void enforce_mixer(int result);



template <typename T>
T* enforce_sdl(T* result)
{
    return result ? result : throw sdl_error(::SDL_GetError());
}


template <typename T>
T* enforce_ttf(T* result)
{
    return result ? result : throw sdl_error(::TTF_GetError());
}


template <typename T>
T* enforce_img(T* result)
{
    return result ? result : throw sdl_error(::IMG_GetError());
}


template <typename T>
T* enforce_mixer(T* result)
{
    return result ? result : throw sdl_error(::Mix_GetError());
}



// For RAII
class sdl_core final : public lib::noncopyable
{
public:
    sdl_core();
    ~sdl_core();
};



// For RAII
class sdl_ttf final : public lib::noncopyable
{
public:
    sdl_ttf();
    ~sdl_ttf();
};



// For RAII
class sdl_image final : public lib::noncopyable
{
public:
    sdl_image();
    ~sdl_image();
};



// For RAII
class sdl_mixer final : public lib::noncopyable
{
public:
    sdl_mixer();
    ~sdl_mixer();
};


} // namespace detail
} // namespace snail
} // namespace elona

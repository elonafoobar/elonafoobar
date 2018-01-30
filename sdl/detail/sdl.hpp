#pragma once

#include <stdexcept>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../lib/noncopyable.hpp"



namespace snail::detail
{
class SDLError : public std::runtime_error
{
public:
    explicit SDLError(const std::string& message)
        : std::runtime_error(message)
    {
    }
};



void enforce_sdl(int result);
void enforce_ttf(int result);
void enforce_img(int result);
// void enforce_mixer(int result);



template <typename T>
T* enforce_sdl(T* result)
{
    return result ? result : throw SDLError(::SDL_GetError());
}


template <typename T>
T* enforce_ttf(T* result)
{
    return result ? result : throw SDLError(::TTF_GetError());
}


template <typename T>
T* enforce_img(T* result)
{
    return result ? result : throw SDLError(::IMG_GetError());
}


// template<typename T>
// T* enforce_mixer(T* result)
// {
//     return result ? result : throw SDLError(::MIX_GetError());
// }



// For RAII
class SDLCore final : public lib::noncopyable
{
public:
    SDLCore();
    ~SDLCore();
};



// For RAII
class SDLTTF final : public lib::noncopyable
{
public:
    SDLTTF();
    ~SDLTTF();
};



// For RAII
class SDLImage final : public lib::noncopyable
{
public:
    SDLImage();
    ~SDLImage();
};



// For RAII
class SDLMixer final : public lib::noncopyable
{
public:
    SDLMixer();
    ~SDLMixer();
};


} // namespace snail::detail

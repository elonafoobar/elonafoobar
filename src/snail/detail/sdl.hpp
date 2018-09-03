#pragma once

#include <stdexcept>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "../../lib/noncopyable.hpp"



namespace elona
{
namespace snail
{
namespace detail
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
void enforce_mixer(int result);


#if defined(SNAIL_RENDERER_HEADLESS)

template <typename T>
T* enforce_sdl(T* result)
{
    return result;
}


template <typename T>
T* enforce_ttf(T* result)
{
    return result;
}


template <typename T>
T* enforce_img(T* result)
{
    return result;
}


template <typename T>
T* enforce_mixer(T* result)
{
    return result;
}

#elif defined(SNAIL_RENDERER_SDL)

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


template <typename T>
T* enforce_mixer(T* result)
{
    return result ? result : throw SDLError(::Mix_GetError());
}


#else
#error Unsupported renderer
#endif



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


} // namespace detail
} // namespace snail
} // namespace elona

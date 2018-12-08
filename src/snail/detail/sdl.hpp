#pragma once

#include <stdexcept>
#include <string>
#include <type_traits>
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

void* enforce_sdl_internal(void* result);
void* enforce_ttf_internal(void* result);
void* enforce_img_internal(void* result);
void* enforce_mixer_internal(void* result);



template <typename T>
T* enforce_sdl(T* result)
{
    return static_cast<T*>(enforce_sdl_internal(result));
}



template <typename T>
T* enforce_ttf(T* result)
{
    return static_cast<T*>(enforce_ttf_internal(result));
}



template <typename T>
T* enforce_img(T* result)
{
    return static_cast<T*>(enforce_img_internal(result));
}



template <typename T>
T* enforce_mixer(T* result)
{
    return static_cast<T*>(enforce_mixer_internal(result));
}



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

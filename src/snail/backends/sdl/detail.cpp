#include "../../detail/sdl.hpp"

namespace elona
{
namespace snail
{
namespace detail
{



void enforce_sdl(int result)
{
    if (result != 0)
    {
        throw SDLError{::SDL_GetError()};
    }
}


void enforce_ttf(int result)
{
    if (result != 0)
    {
        throw SDLError{::TTF_GetError()};
    }
}


void enforce_image(int result)
{
    if (result != 0)
    {
        throw SDLError{::IMG_GetError()};
    }
}



void enforce_mixer(int result)
{
    if (result != 0)
    {
        throw SDLError{::Mix_GetError()};
    }
}



void* enforce_sdl_internal(void* result)
{
    return result ? result : throw SDLError(::SDL_GetError());
}



void* enforce_ttf_internal(void* result)
{
    return result ? result : throw SDLError(::TTF_GetError());
}



void* enforce_img_internal(void* result)
{
    return result ? result : throw SDLError(::IMG_GetError());
}



void* enforce_mixer_internal(void* result)
{
    return result ? result : throw SDLError(::Mix_GetError());
}



SDLCore::SDLCore()
{
    enforce_sdl(::SDL_Init(SDL_INIT_EVERYTHING));
}



SDLCore::~SDLCore()
{
    ::SDL_Quit();
}



SDLTTF::SDLTTF()
{
    enforce_ttf(::TTF_Init());
}



SDLTTF::~SDLTTF()
{
    ::TTF_Quit();
}



SDLImage::SDLImage()
{
    auto flags = IMG_INIT_PNG | IMG_INIT_JPG;
    auto result = ::IMG_Init(flags);
    if ((flags & result) != flags)
    {
        throw SDLError{"Failed to initialize SDL2Image"};
    }
}



SDLImage::~SDLImage()
{
    ::IMG_Quit();
}



SDLMixer::SDLMixer()
{
    // auto flags = MIX_INIT_OGG | MIX_INIT_MP3;
    auto flags = 0;
    auto result = ::Mix_Init(flags);
    if ((flags & result) != flags)
    {
        throw SDLError{"Failed to initialize SDL2Mixer"};
    }

    enforce_mixer(::Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048));
}



SDLMixer::~SDLMixer()
{
    ::Mix_CloseAudio();
    ::Mix_Quit();
}


} // namespace detail
} // namespace snail
} // namespace elona

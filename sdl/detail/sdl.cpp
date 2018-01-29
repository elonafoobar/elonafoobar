#include "sdl.hpp"

using namespace snail::detail;


namespace snail::detail
{


void enforce_sdl(int result)
{
    if (result != 0)
    {
        throw SDLError(::SDL_GetError());
    }
}


void enforce_ttf(int result)
{
    if (result != 0)
    {
        throw SDLError(::TTF_GetError());
    }
}


void enforce_image(int result)
{
    if (result != 0)
    {
        throw SDLError(::IMG_GetError());
    }
}



// void enforce_mixer(int result)
// {
//     if (result != 0)
//     {
//         throw SDLError(::MIX_GetError());
//     }
// }


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
    ::enforce_ttf(::TTF_Init());
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
        throw SDLError("Failed to load SDL2Image");
    }
}



SDLImage::~SDLImage()
{
    ::IMG_Quit();
}



SDLMixer::SDLMixer()
{
    // Does nothing so far.
}



SDLMixer::~SDLMixer()
{
    // Does nothing so far.
}

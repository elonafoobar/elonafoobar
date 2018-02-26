#include "sdl.hpp"


namespace elona::snail::detail
{



void enforce_sdl(int result)
{
    if (result != 0)
    {
        throw sdl_error{::SDL_GetError()};
    }
}


void enforce_ttf(int result)
{
    if (result != 0)
    {
        throw sdl_error{::TTF_GetError()};
    }
}


void enforce_image(int result)
{
    if (result != 0)
    {
        throw sdl_error{::IMG_GetError()};
    }
}



void enforce_mixer(int result)
{
    if (result != 0)
    {
        throw sdl_error{::Mix_GetError()};
    }
}



sdl_core::sdl_core()
{
    enforce_sdl(::SDL_Init(SDL_INIT_EVERYTHING));
}



sdl_core::~sdl_core()
{
    ::SDL_Quit();
}



sdl_ttf::sdl_ttf()
{
    enforce_ttf(::TTF_Init());
}



sdl_ttf::~sdl_ttf()
{
    ::TTF_Quit();
}



sdl_image::sdl_image()
{
    auto flags = IMG_INIT_PNG | IMG_INIT_JPG;
    auto result = ::IMG_Init(flags);
    if ((flags & result) != flags)
    {
        throw sdl_error{"Failed to initialize SDL2Image"};
    }
}



sdl_image::~sdl_image()
{
    ::IMG_Quit();
}



sdl_mixer::sdl_mixer()
{
    // auto flags = MIX_INIT_OGG | MIX_INIT_MP3;
    auto flags = 0;
    auto result = ::Mix_Init(flags);
    if ((flags & result) != flags)
    {
        throw sdl_error{"Failed to initialize SDL2Mixer"};
    }

    enforce_mixer(
        ::Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048));
}



sdl_mixer::~sdl_mixer()
{
    ::Mix_CloseAudio();
    ::Mix_Quit();
}


} // namespace elona::snail::detail

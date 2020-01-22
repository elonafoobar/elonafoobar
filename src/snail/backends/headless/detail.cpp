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
        throw std::runtime_error{"enforce_sdl(int)"};
    }
}


void enforce_ttf(int result)
{
    if (result != 0)
    {
        throw std::runtime_error{"enforce_ttf(int)"};
    }
}


void enforce_image(int result)
{
    if (result != 0)
    {
        throw std::runtime_error{"enforce_img(int)"};
    }
}



void enforce_mixer(int result)
{
    if (result != 0)
    {
        throw std::runtime_error{"enforce_mixer(int)"};
    }
}



void* enforce_sdl_internal(void* result)
{
    return result ? result : throw std::runtime_error{"enforce_sdl(void*)"};
}



void* enforce_ttf_internal(void* result)
{
    return result ? result : throw std::runtime_error{"enforce_ttf(void*)"};
}



void* enforce_img_internal(void* result)
{
    return result ? result : throw std::runtime_error{"enforce_img(void*)"};
}



void* enforce_mixer_internal(void* result)
{
    return result ? result : throw std::runtime_error{"enforce_mixer(void*)"};
}



SDLCore::SDLCore()
{
}



SDLCore::~SDLCore()
{
}



SDLTTF::SDLTTF()
{
}



SDLTTF::~SDLTTF()
{
}



SDLImage::SDLImage()
{
}



SDLImage::~SDLImage()
{
}



SDLMixer::SDLMixer()
{
}



SDLMixer::~SDLMixer()
{
}

} // namespace detail
} // namespace snail
} // namespace elona

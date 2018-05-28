#include "audio.hpp"

#if defined(SNAIL_RENDERER_HEADLESS)
#include "audio/headless.cpp"
#elif defined(SNAIL_RENDERER_SDL)
#include "audio/sdl.cpp"
#else
#error Unsupported renderer
#endif

#include "hsp.hpp"

#if defined(SNAIL_RENDERER_HEADLESS)
#include "hsp/headless.cpp"
#elif defined(SNAIL_RENDERER_SDL)
#include "hsp/sdl.cpp"
#else
#error Unsupported renderer
#endif

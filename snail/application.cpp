#include "application.hpp"

#if defined(SNAIL_RENDERER_HEADLESS)
#include "application/headless.cpp"
#elif defined(SNAIL_RENDERER_SDL)
#include "application/sdl.cpp"
#else
#error Unsupported renderer
#endif

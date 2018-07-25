#include "window.hpp"

#if defined(SNAIL_RENDERER_HEADLESS)
#include "window/headless.cpp"
#elif defined(SNAIL_RENDERER_SDL)
#include "window/sdl.cpp"
#else
#error Unsupported renderer
#endif

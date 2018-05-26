#include "renderer.hpp"

#if defined(SNAIL_RENDERER_HEADLESS)
#include "renderer/headless.cpp"
#elif defined(SNAIL_RENDERER_SDL)
#include "renderer/sdl.cpp"
#else
#error Unsupported renderer
#endif

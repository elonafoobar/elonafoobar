#include "sdl.hpp"

#if defined(SNAIL_RENDERER_HEADLESS)
#include "sdl_headless.cpp"
#elif defined(SNAIL_RENDERER_SDL)
#include "sdl_impl.cpp"
#else
#error Unsupported renderer
#endif

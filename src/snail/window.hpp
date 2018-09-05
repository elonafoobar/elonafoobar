#if defined(SNAIL_RENDERER_HEADLESS)
#include "window/headless.hpp"
#elif defined(SNAIL_RENDERER_SDL)
#include "window/sdl.hpp"
#else
#error Unsupported renderer
#endif

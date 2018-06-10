#if defined(SNAIL_RENDERER_HEADLESS)
#include "application/headless.hpp"
#elif defined(SNAIL_RENDERER_SDL)
#include "application/sdl.hpp"
#else
#error Unsupported renderer
#endif

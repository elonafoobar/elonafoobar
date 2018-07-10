#include "touch_input.hpp"

#if defined(SNAIL_RENDERER_HEADLESS)
#include "touch_input/headless.cpp"
#elif defined(SNAIL_RENDERER_SDL)
#include "touch_input/sdl.cpp"
#else
#error Unsupported renderer
#endif

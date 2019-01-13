#include "filedialog.hpp"

#if defined(SNAIL_RENDERER_HEADLESS)
#include "filedialog/headless.cpp"
#elif defined(SNAIL_RENDERER_SDL)
#include "filedialog/sdl.cpp"
#else
#error Unsupported renderer
#endif

#ifdef ANDROID
#include "../window.hpp"
#endif

namespace elona
{
namespace snail
{


void Window::move_to_center()
{
    ::SDL_SetWindowPosition(
        ptr(),
        InitialPosition::position_centered,
        InitialPosition::position_centered);
}

std::pair<int, int> Window::get_size()
{
    int width, height;
    ::SDL_GetWindowSize(ptr(), &width, &height);
    return {width, height};
}

void Window::set_size(int width, int height)
{
    ::SDL_SetWindowSize(ptr(), width, height);
}

void Window::set_display_mode(::SDL_DisplayMode display_mode)
{
    detail::enforce_sdl(::SDL_SetWindowDisplayMode(ptr(), &display_mode));
}

::SDL_DisplayMode Window::get_display_mode()
{
    ::SDL_DisplayMode mode;
    detail::enforce_sdl(::SDL_GetWindowDisplayMode(ptr(), &mode));
    return mode;
}

void Window::set_fullscreen_mode(FullscreenMode fullscreen_mode)
{
    detail::enforce_sdl(
        ::SDL_SetWindowFullscreen(ptr(), static_cast<Uint32>(fullscreen_mode)));
}

Window::Window(
    const std::string& title,
    int x,
    int y,
    int width,
    int height,
    int flag)
    : _ptr(
          detail::enforce_sdl(::SDL_CreateWindow(
              title.c_str(),
              x,
              y,
              width,
              height,
              static_cast<SDL_WindowFlags>(flag))),
          ::SDL_DestroyWindow)
{
}



} // namespace snail
} // namespace elona

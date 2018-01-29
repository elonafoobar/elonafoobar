#include "window.hpp"

using namespace snail;



Window::Window(const std::string& title, int x, int y, int width, int height, int flag)
    : _ptr(detail::enforce_sdl(::SDL_CreateWindow(
            title.c_str(),
            x,
            y,
            width,
            height,
            static_cast<SDL_WindowFlags>(flag))),
        ::SDL_DestroyWindow)
{
}

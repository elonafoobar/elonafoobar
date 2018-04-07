#include "window.hpp"


namespace elona
{
namespace snail
{



window::window(
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

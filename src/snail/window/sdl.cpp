namespace elona
{
namespace snail
{


class Window::Impl
{
    Impl(SDL_Window* ptr, decltype(&::SDL_DestroyWindow) deleter)
        : ptr(ptr, deleter)
    {
    }


    std::unique_ptr<::SDL_Window, decltype(&::SDL_DestroyWindow)> ptr;
};



Window::Window(
    const std::string& title,
    int x,
    int y,
    int width,
    int height,
    Flag flag)
    : pimpl(
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



~Window() = default;



::SDL_Window* Window::ptr()
{
    return pimpl->ptr;
}



void Window::move_to_center()
{
    ::SDL_SetWindowPosition(
        ptr(),
        static_cast<int>(InitialPosition::centered),
        static_cast<int>(InitialPosition::centered));
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


} // namespace snail
} // namespace elona

namespace elona
{
namespace snail
{

void Window::move_to_center()
{
}



std::pair<int, int> Window::get_size()
{
    return {800, 600};
}



void Window::set_size(int width, int height)
{
    (void)width;
    (void)height;
}



void Window::set_display_mode(::SDL_DisplayMode display_mode)
{
    (void)display_mode;
}



::SDL_DisplayMode Window::get_display_mode()
{
    ::SDL_DisplayMode mode{};
    return mode;
}



void Window::set_fullscreen_mode(FullscreenMode fullscreen_mode)
{
    (void)fullscreen_mode;
}



Window::Window(
    const std::string& title,
    int x,
    int y,
    int width,
    int height,
    Flag flag)
{
    (void)title;
    (void)x;
    (void)y;
    (void)width;
    (void)height;
    (void)flag;
}

} // namespace snail
} // namespace elona

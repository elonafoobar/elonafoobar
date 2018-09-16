namespace elona
{
namespace snail
{


class Window::Impl
{
};



Window::Window(const std::string&, int, int, int, int, Flag)
{
}



~Window() = default;



::SDL_Window* Window::ptr()
{
    return nullptr;
}



void Window::move_to_center()
{
}



std::pair<int, int> Window::get_size()
{
    return {800, 600};
}



void Window::set_size(int, int)
{
}



void Window::set_display_mode()
{
}



::SDL_DisplayMode Window::get_display_mode()
{
    return ::SDL_DisplayMode{};
}



void Window::set_fullscreen_mode()
{
}


} // namespace snail
} // namespace elona

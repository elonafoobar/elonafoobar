#include "../../application.hpp"
#include <algorithm>
#include <map>
#include "../../input.hpp"


namespace elona
{
namespace snail
{

Application::Application() = default;



Application& Application::instance()
{
    static Application the_instance;
    return the_instance;
}



void Application::set_title(const std::string&)
{
}



void Application::initialize(const std::string&)
{
    _window.reset(new Window(
        "snail headless",
        Window::InitialPosition::undefined,
        Window::InitialPosition::undefined,
        width(),
        height(),
        Window::Flag::shown));
    _renderer.reset(new Renderer(
        *_window, Renderer::Flag::accelerated | Renderer::Flag::present_vsync));
}



void Application::quit()
{
    _will_quit = true;
}



void Application::register_finalizer(std::function<void()>)
{
}



void Application::proc_event()
{
}



void Application::wait(size_t)
{
}



void Application::set_fullscreen_mode(Window::FullscreenMode)
{
}



std::map<std::string, ::SDL_DisplayMode> Application::get_display_modes()
{
    return {};
}



std::string Application::get_default_display_mode()
{
    return "";
}



::SDL_DisplayMode Application::get_display_mode()
{
    return ::SDL_DisplayMode{};
}



void Application::set_display_mode(const std::string&)
{
}



void Application::set_display_mode(const ::SDL_DisplayMode)
{
}



void Application::initialize_dpi()
{
}



void Application::handle_event(const ::SDL_Event&)
{
}



void Application::handle_window_event(const ::SDL_WindowEvent&)
{
}



void Application::on_size_changed(const ::SDL_WindowEvent&)
{
}



void Application::set_window_size(int, int)
{
}

} // namespace snail
} // namespace elona

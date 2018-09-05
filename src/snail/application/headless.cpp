#include <algorithm>
#include <map>
#include "../input.hpp"


namespace elona
{
namespace snail
{



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



void Application::main_loop()
{
    while (1)
    {
        if (_will_quit)
            return;
    }
}



void Application::proc_event()
{
}


void set_fullscreen_mode(Window::FullscreenMode)
{
}

void set_display_mode(const std::string&)
{
}

void set_display_mode(const ::SDL_DisplayMode)
{
}

} // namespace snail
} // namespace elona

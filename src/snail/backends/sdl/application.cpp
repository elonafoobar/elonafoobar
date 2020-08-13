#include "../../application.hpp"

#include <algorithm>
#include <map>
#include <sstream>

#include "../../hsp.hpp"
#include "../../input.hpp"



namespace elona
{
namespace snail
{

Application::Application()
    : _sdl_core(new detail::SDLCore)
    , _sdl_ttf(new detail::SDLTTF)
    , _sdl_image(new detail::SDLImage)
    , _sdl_mixer(new detail::SDLMixer)
{
}



Application& Application::instance()
{
    static Application the_instance;
    return the_instance;
}



void Application::set_title(const std::string& title)
{
    _title = title;
    if (_window)
    {
        ::SDL_SetWindowTitle(_window->ptr(), title.c_str());
    }
}



void Application::initialize_dpi()
{
    const constexpr int display_in_use =
        0; // Assume the first display is being used.
    const constexpr float default_dpi =
#ifdef __APPLE__
        72.0f;
#else
        96.0f;
#endif

    if (::SDL_GetDisplayDPI(display_in_use, NULL, &_dpi, NULL) != 0)
    {
        _dpi = default_dpi;
    }
}



void Application::initialize(const std::string& title)
{
    _width = 800;
    _height = 600;
    _physical_width = _width;
    _physical_height = _height;
    _title = title;
    _window.reset(new Window(
        title,
        Window::InitialPosition::undefined,
        Window::InitialPosition::undefined,
        _width,
        _height,
        Window::Flag::shown));
    _renderer.reset(new Renderer(
        *_window, Renderer::Flag::accelerated | Renderer::Flag::present_vsync));

    initialize_dpi();

    set_display_mode(get_default_display_mode());

    ::SDL_StartTextInput();
}



void Application::quit()
{
    _will_quit = true;
}



void Application::register_finalizer(std::function<void()> finalizer)
{
    _finalizers.emplace_back(finalizer);
}



void Application::handle_event(const ::SDL_Event& event)
{
    switch (event.type)
    {
    case SDL_QUIT: quit(); break;
    case SDL_MOUSEMOTION:
    case SDL_MOUSEBUTTONUP:
    case SDL_MOUSEBUTTONDOWN:
        Input::instance()._handle_event(event.button);
        break;
    case SDL_KEYUP:
    case SDL_KEYDOWN: Input::instance()._handle_event(event.key); break;
    case SDL_TEXTINPUT: Input::instance()._handle_event(event.text); break;
    case SDL_TEXTEDITING: Input::instance()._handle_event(event.edit); break;
    case SDL_WINDOWEVENT: handle_window_event(event.window); break;
    default: break;
    }
}



void Application::on_size_changed(const ::SDL_WindowEvent& event)
{
    int new_width = event.data1;
    int new_height = event.data2;

    _physical_width = new_width;
    _physical_height = new_height;

    _width = new_width;
    _height = new_height;
}



void Application::handle_window_event(const ::SDL_WindowEvent& event)
{
    switch (event.event)
    {
    case SDL_WINDOWEVENT_SIZE_CHANGED:
        // Handle device rotation.
        on_size_changed(event);
        break;
    case SDL_WINDOWEVENT_SHOWN:
    case SDL_WINDOWEVENT_EXPOSED:
    case SDL_WINDOWEVENT_RESTORED:
        if (_call_redraw)
        {
            hsp::redraw();
        }
        break;
    default: break;
    }
}



void Application::proc_event()
{
    ::SDL_Event event;
    while (::SDL_PollEvent(&event))
    {
        handle_event(event);
    }

    Input::instance()._update();

    if (_will_quit)
    {
        std::exit(0);
    }
}



void Application::wait(size_t msec)
{
    const auto now = ::SDL_GetTicks();
    if (_last_wait_time == 0)
    {
        _last_wait_time = now;
    }
    const auto delta = now - _last_wait_time;
    if (msec > delta)
    {
        ::SDL_Delay(msec - delta);
    }
    _last_wait_time = now;
}



void Application::set_fullscreen_mode(Window::FullscreenMode fullscreen_mode)
{
    (*_window).set_fullscreen_mode(fullscreen_mode);
    _fullscreen_mode = fullscreen_mode;
}



std::map<std::string, ::SDL_DisplayMode> Application::get_display_modes()
{
    const constexpr int display_in_use =
        0; // Assume the first display is being used.
    std::map<std::string, ::SDL_DisplayMode> display_modes;

    int display_mode_count = ::SDL_GetNumDisplayModes(display_in_use);
    if (display_mode_count < 1)
    {
        throw detail::SDLError("No display modes available");
    }

    for (int i = 0; i < display_mode_count; ++i)
    {
        SDL_DisplayMode mode;
        detail::enforce_sdl(::SDL_GetDisplayMode(display_in_use, i, &mode));

        if (mode.w < 800 || mode.h < 600)
        {
            continue;
        }

        std::stringstream ss;
        ss << mode.w << "x" << mode.h << "@" << mode.refresh_rate << "Hz";

        display_modes.emplace(ss.str(), mode);
    }

    return display_modes;
}



std::string Application::get_default_display_mode()
{
    auto display_modes = get_display_modes();
    if (display_modes.size() == 0)
    {
        throw detail::SDLError("No display modes available");
    }

    for (const auto pair : display_modes)
    {
        if (pair.second.w == 800 && pair.second.h == 600)
        {
            return pair.first;
        }
    }

    return display_modes.begin()->first;
}



::SDL_DisplayMode Application::get_display_mode()
{
    return (*_window).get_display_mode();
}



void Application::set_display_mode(const std::string& display_mode_str)
{
    std::string display_mode = display_mode_str;
    auto display_modes = get_display_modes();
    if (display_modes.size() == 0)
    {
        throw detail::SDLError("No display modes available");
    }
    if (display_modes.find(display_mode_str) == display_modes.end())
    {
        display_mode = get_default_display_mode();
    }

    set_display_mode(display_modes[display_mode]);
}



void Application::set_display_mode(::SDL_DisplayMode display_mode)
{
    if (is_fullscreen())
    {
        _window->set_display_mode(display_mode);
    }
    else
    {
        _window->set_size(display_mode.w, display_mode.h);
    }

    _width = display_mode.w;
    _height = display_mode.h;

    _window->move_to_center();
}



void Application::set_window_size(int width, int height)
{
    _window->set_size(width, height);
}

} // namespace snail
} // namespace elona

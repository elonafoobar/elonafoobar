#ifdef ANDROID
#include "../application.hpp"
#endif
#include <algorithm>
#include <map>
#include <sstream>
#include "../input.hpp"


namespace elona
{
namespace snail
{



#include <android/log.h>
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOG_TAG    "ElonaFoobar"

application& application::instance()
{
    static application the_instance;
    return the_instance;
}


void application::set_title(const std::string& title)
{
    _title = title;
    if (_window)
    {
        ::SDL_SetWindowTitle(_window->ptr(), title.c_str());
    }
}



void application::initialize(const std::string& title)
{
    _width = 800;
    _height = 600;
    _actual_width = _width;
    _actual_height = _height;
    _title = title;
    _window.reset(new window(
        title,
        window::position_undefined,
        window::position_undefined,
        800,
        600,
        window::shown));
    _renderer.reset(new renderer(
        *_window, renderer::accelerated | renderer::present_vsync));
    if (!is_android())
    {
        ::SDL_StartTextInput();
    }

    initialize_actual_size();

    set_display_mode(get_default_display_mode());
}



void application::initialize_actual_size()
{
    ::SDL_DisplayMode display_mode;
    ::SDL_GetCurrentDisplayMode(0, &display_mode);
    _actual_width = display_mode.w;
    _actual_height = display_mode.h;
}



void application::run(std::shared_ptr<scene_base> initial_scene)
{
    _scene_manager.push(initial_scene);
    main_loop();
}



void application::quit()
{
    _will_quit = true;
}



void application::add_effect(std::unique_ptr<effect_base> effect)
{
    _effects.push_back(std::move(effect));
}



void application::register_finalizer(std::function<void()> finalizer)
{
    _finalizers.emplace_back(finalizer);
}



void application::main_loop()
{
    while (1)
    {
        ::SDL_Event event;
        while (::SDL_PollEvent(&event))
        {
            handle_event(event);
        }

        input::instance()._update();

        bool user_input_blocked = false;
        for (auto&& effect : _effects)
        {
            effect->update();
            effect->_increase_frame();
            if (effect->blocks_user_input())
            {
                user_input_blocked = true;
            }
        }

        // Even if the current scene was popped from the scene stack in
        // updating, it will be rendered.
        auto current_scene = _scene_manager.current_scene();
        if (!user_input_blocked)
        {
            current_scene->update();
            current_scene->_increase_frame();
        }

        if (_will_quit)
            return;

        _renderer->clear();
        render_scene(current_scene);
        for (auto&& effect : _effects)
        {
            if (effect->alive())
            {
                effect->render(*_renderer);
            }
        }
        std::remove_if(
            std::begin(_effects), std::end(_effects), [](const auto& effect) {
                return !effect->alive();
            });
        _renderer->present();

        _fps_manager.wait();
        ++_frame;
    }
}



void application::render_scene(std::shared_ptr<scene_base> scene)
{
    if (scene->parent())
    {
        render_scene(scene->parent());
    }
    scene->render(*_renderer);
}



void application::handle_event(const ::SDL_Event& event)
{
    switch (event.type)
    {
    case SDL_QUIT: quit(); break;
    case SDL_MOUSEMOTION:
    case SDL_MOUSEBUTTONUP:
    case SDL_MOUSEBUTTONDOWN:
        // Mouse::instance()._handle_event(event.button);
        break;
    case SDL_KEYUP:
    case SDL_KEYDOWN: input::instance()._handle_event(event.key); break;
    case SDL_TEXTINPUT: input::instance()._handle_event(event.text); break;
    case SDL_TEXTEDITING: input::instance()._handle_event(event.edit); break;
    case SDL_FINGERMOTION:
    case SDL_FINGERDOWN:
    case SDL_FINGERUP:
        input::instance()._handle_event(event.tfinger);
        break;
    default: break;
    }
}


void application::proc_event()
{
    ::SDL_Event event;
    while (::SDL_PollEvent(&event))
    {
        handle_event(event);
    }

    input::instance()._update();

    if (_will_quit)
    {
        std::exit(0);
    }
}

void application::set_fullscreen_mode(window::fullscreen_mode_t fullscreen_mode)
{
    (*_window).set_fullscreen_mode(fullscreen_mode);
    _fullscreen_mode = fullscreen_mode;
}

std::map<std::string, ::SDL_DisplayMode> application::get_display_modes()
{
    static int display_in_use = 0; // Assume the first display is being used.
    std::map<std::string, ::SDL_DisplayMode> display_modes;

    int display_mode_count = ::SDL_GetNumDisplayModes(display_in_use);
    if (display_mode_count < 1)
    {
        throw detail::sdl_error("No display modes available");
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

std::string application::get_default_display_mode()
{
    auto display_modes = get_display_modes();
    if (display_modes.size() == 0)
    {
        throw detail::sdl_error("No display modes available");
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

void application::set_display_mode(const std::string& display_mode_str)
{
    std::string display_mode = display_mode_str;
    auto display_modes = get_display_modes();
    if (display_modes.size() == 0)
    {
        throw detail::sdl_error("No display modes available");
    }
    if (display_modes.find(display_mode_str) == display_modes.end())
    {
        display_mode = get_default_display_mode();
    }

    set_display_mode(display_modes[display_mode]);
}

void application::set_display_mode(::SDL_DisplayMode display_mode)
{
    if (is_fullscreen())
    {
        (*_window).set_display_mode(display_mode);
    }
    else
    {
        (*_window).set_size(display_mode.w, display_mode.h);
    }

    // We want the actual rendered size kept separate from the
    // device's size on Android.
    if (!is_android())
    {
        _width = display_mode.w;
        _height = display_mode.h;
    }

    (*_window).move_to_center();
}


} // namespace snail
} // namespace elona

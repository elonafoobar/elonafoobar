#include "application.hpp"
#include <algorithm>
#include "input.hpp"

using namespace snail;



Application& Application::instance() noexcept
{
    static Application application;
    return application;
}


void Application::set_title(const std::string& title_str)
{
    _title = title_str;
    if (_window)
    {
        ::SDL_SetWindowTitle(_window->ptr(), title_str.c_str());
    }
}



void Application::initialize(int width, int height, const std::string& title)
{
    _width = width;
    _height = height;
    _title = title;
    _window.reset(new Window(
        title,
        Window::position_undefined,
        Window::position_undefined,
        width,
        height,
        Window::shown));
    _renderer.reset(new Renderer(
        *_window,
        Renderer::accelerated | Renderer::present_vsync));
}



void Application::run(std::shared_ptr<Scene> initial_scene)
{
    _scene_manager.push(initial_scene);
    main_loop();
}



void Application::quit()
{
    _will_quit = true;
}



void Application::add_effect(std::unique_ptr<Effect> effect)
{
    _effects.push_back(std::move(effect));
}



void Application::proc_event()
{
    ::SDL_Event event;
    while (::SDL_PollEvent(&event))
    {
        handle_event(event);
    }
    // Mouse::instance()._update();
    Keyboard::instance()._update();

    if (_will_quit)
    {
        std::exit(0);
    }
}



int Application::get_ticks()
{
    return ::SDL_GetTicks();
}



void Application::register_finalizer(std::function<void()> finalizer)
{
    _finalizers.emplace_back(finalizer);
}



void Application::main_loop()
{
    while (1)
    {
        ::SDL_Event event;
        while (::SDL_PollEvent(&event))
        {
            handle_event(event);
        }
        // Mouse::instance()._update();
        Keyboard::instance()._update();

        bool user_input_blocked = false;
        for (const auto& effect : _effects)
        {
            effect->update();
            effect->_increase_frame();
            if (effect->blocks_user_input())
            {
                user_input_blocked = true;
            }
        }
        // Even if the current scene was popped from the scene stack in updating,
        // it will be rendered.
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
        for (const auto& effect : _effects)
        {
            if (effect->alive())
            {
                effect->render(*_renderer);
            }
        }
        std::remove_if(std::begin(_effects), std::end(_effects),
                [](const auto& effect) {
                    return !effect->alive();
                });

        // _renderer->render_text(std::to_string(_fps_manager.actual_fps()), 0, 0);

        _renderer->present();

        _fps_manager.wait();

        ++_frame;
    }
}



void Application::render_scene(std::shared_ptr<Scene> scene)
{
    if (scene->parent())
        render_scene(scene->parent());
    scene->render(*_renderer);
}



void Application::handle_event(const ::SDL_Event& event)
{
    switch (event.type)
    {
    case SDL_QUIT:
        quit();
        break;
    case SDL_MOUSEMOTION:
    case SDL_MOUSEBUTTONUP:
    case SDL_MOUSEBUTTONDOWN:
        // Mouse::instance()._handle_event(event.button);
        break;
    case SDL_KEYUP:
    case SDL_KEYDOWN:
        Keyboard::instance()._handle_event(event.key);
        break;
    default:
        break;
    }
}

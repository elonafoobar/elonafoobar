#include "application.hpp"
#include <algorithm>
#include "input.hpp"


namespace elona::snail
{



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



void application::initialize(int width, int height, const std::string& title)
{
    _width = width;
    _height = height;
    _title = title;
    _window.reset(new window(
        title,
        window::position_undefined,
        window::position_undefined,
        width,
        height,
        window::shown));
    _renderer.reset(new renderer(
        *_window, renderer::accelerated | renderer::present_vsync));
    ::SDL_StartTextInput();
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


} // namespace elona::snail

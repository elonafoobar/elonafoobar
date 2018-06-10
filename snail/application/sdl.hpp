#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>
#include "../../lib/noncopyable.hpp"
#include "../../lib/scope_guard.hpp"
#include "../detail/sdl.hpp"
#include "../effect.hpp"
#include "../fpsmanager.hpp"
#include "../renderer.hpp"
#include "../scene.hpp"
#include "../window.hpp"



namespace elona
{
namespace snail
{


class application final : public lib::noncopyable
{
public:
    size_t frame() const noexcept
    {
        return _frame;
    }


    int width() const noexcept
    {
        return _width;
    }


    int height() const noexcept
    {
        return _height;
    }

    const std::string& title() const noexcept
    {
        return _title;
    }


    void set_title(const std::string& title);


    virtual ~application() override = default;


    static application& instance();


    void initialize(const std::string& title);
    void run(std::shared_ptr<scene_base> initial_scene);

    void quit();
    void add_effect(std::unique_ptr<effect_base> effect);


    void push(std::shared_ptr<scene_base> new_scene)
    {
        _scene_manager.push(new_scene);
    }


    void pop()
    {
        _scene_manager.pop();
    }


    void pop_all()
    {
        _scene_manager.pop_all();
    }


    void replace(std::shared_ptr<scene_base> new_scene)
    {
        _scene_manager.replace(new_scene);
    }


    // NOTE: Do not depend on the order of finalization.
    void register_finalizer(std::function<void()> finalizer);


    renderer& get_renderer()
    {
        return *_renderer;
    }


    void proc_event();

    bool is_fullscreen() { return _fullscreen_mode != window::fullscreen_mode_t::windowed; }

    window::fullscreen_mode_t get_fullscreen_mode() { return _fullscreen_mode; }

    void set_fullscreen_mode(window::fullscreen_mode_t);

    std::map<std::string, ::SDL_DisplayMode> get_display_modes();

    std::string get_default_display_mode();

    ::SDL_DisplayMode get_display_mode() { return (*_window).get_display_mode(); }

    void set_display_mode(const std::string&);
    void set_display_mode(const ::SDL_DisplayMode);


private:
    detail::sdl_core _sdl_core;
    detail::sdl_ttf _sdl_ttf;
    detail::sdl_image _sdl_image;
    detail::sdl_mixer _sdl_mixer;
    int _width;
    int _height;
    std::string _title;
    size_t _frame = 0;
    bool _will_quit = false;
    std::unique_ptr<window> _window;
    std::unique_ptr<renderer> _renderer;
    scene_manager _scene_manager;
    fps_manager _fps_manager;
    std::vector<std::unique_ptr<effect_base>> _effects;
    std::vector<lib::scope_guard> _finalizers;
    window::fullscreen_mode_t _fullscreen_mode = window::fullscreen_mode_t::windowed;

    application() = default;

    void main_loop();
    void render_scene(std::shared_ptr<scene_base> scene);
    void handle_event(const ::SDL_Event& event);
};



} // namespace snail
} // namespace elona

#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>
#include "../lib/noncopyable.hpp"
#include "../lib/scope_guard.hpp"
#include "detail/sdl.hpp"
#include "effect.hpp"
#include "fpsmanager.hpp"
#include "renderer.hpp"
#include "scene.hpp"
#include "window.hpp"



namespace elona
{
namespace snail
{

class Application final : public lib::noncopyable
{
public:
    enum class Orientation
    {
        portrait,
        landscape
    };

    static const constexpr bool is_android =
#ifdef ANDROID
        true;
#else
        false;
#endif

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

    int physical_width() const noexcept
    {
        return _physical_width;
    }

    int physical_height() const noexcept
    {
        return _physical_height;
    }

    float dpi() const noexcept
    {
        return _dpi;
    }

    Orientation orientation() const noexcept
    {
        return _orientation;
    }

    Rect window_pos() const noexcept
    {
        return _window_pos;
    }

    bool was_focus_lost_just_now() noexcept
    {
        bool result = _focus_lost_just_now;
        _focus_lost_just_now = false;
        return result;
    }

    const std::string& title() const noexcept
    {
        return _title;
    }


    void set_title(const std::string& title);


    virtual ~Application() override = default;


    static Application& instance();


    void initialize(const std::string& title);
    void run(std::shared_ptr<SceneBase> initial_scene);

    void quit();
    void add_effect(std::unique_ptr<EffectBase> effect);


    void push(std::shared_ptr<SceneBase> new_scene)
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


    void replace(std::shared_ptr<SceneBase> new_scene)
    {
        _scene_manager.replace(new_scene);
    }


    // NOTE: Do not depend on the order of finalization.
    void register_finalizer(std::function<void()> finalizer);


    Renderer& get_renderer()
    {
        return *_renderer;
    }


    void proc_event();

    bool is_fullscreen()
    {
        return _fullscreen_mode != Window::FullscreenMode::windowed;
    }

    Window::FullscreenMode get_fullscreen_mode()
    {
        return _fullscreen_mode;
    }

    void set_fullscreen_mode(Window::FullscreenMode);

    std::map<std::string, ::SDL_DisplayMode> get_display_modes();

    std::string get_default_display_mode();

    ::SDL_DisplayMode get_display_mode();

    void set_display_mode(const std::string&);
    void set_display_mode(const ::SDL_DisplayMode);

    // For Android
    void set_subwindow_display_mode(const std::string&);


private:
    std::unique_ptr<detail::SDLCore> _sdl_core;
    std::unique_ptr<detail::SDLTTF> _sdl_ttf;
    std::unique_ptr<detail::SDLImage> _sdl_image;
    std::unique_ptr<detail::SDLMixer> _sdl_mixer;

    int _width = 800;
    int _height = 600;
    int _physical_width = 800;
    int _physical_height = 600;
    float _dpi = 96.0f;
    std::string _title;
    Orientation _orientation = Orientation::landscape;
    Rect _window_pos; // Window draw position for Android

    size_t _frame = 0;
    bool _will_quit = false;
    bool _focus_lost_just_now = false;
    std::unique_ptr<Window> _window;
    std::unique_ptr<Renderer> _renderer;
    SceneManager _scene_manager;
    FPSManager _fps_manager;
    std::vector<std::unique_ptr<EffectBase>> _effects;
    std::vector<lib::scope_guard> _finalizers;
    Window::FullscreenMode _fullscreen_mode = Window::FullscreenMode::windowed;

    Application();

    void initialize_dpi();

    void main_loop();
    void render_scene(std::shared_ptr<SceneBase> scene);
    void update_orientation();
    void handle_event(const ::SDL_Event& event);

    void handle_window_event(const ::SDL_WindowEvent& event);
    void on_size_changed(const ::SDL_WindowEvent& event);

    Rect calculate_android_window_pos();
};

} // namespace snail
} // namespace elona

#pragma once

#include <functional>
#include <memory>
#include <string>
#include <vector>
#include "detail/sdl.hpp"
#include "effect.hpp"
#include "fpsmanager.hpp"
#include "lib/noncopyable.hpp"
#include "renderer.hpp"
#include "scene.hpp"
#include "window.hpp"


namespace snail
{
namespace detail
{
struct scope_guard
{
    scope_guard(std::function<void()> finalizer)
        : finalizer(finalizer)
    {
    }


    scope_guard(const scope_guard&) = delete;

    scope_guard(scope_guard&& other)
        : finalizer(other.finalizer)
    {
        other.finalizer = nullptr;
    }


    ~scope_guard()
    {
        if (finalizer)
        {
            finalizer();
        }
    }

private:
    std::function<void()> finalizer;
};
} // namespace detail


class Application final : public lib::noncopyable
{
public:
    int frame() const noexcept
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


    void set_title(const std::string& title_str);


    FPSManager& fps_manager() noexcept
    {
        return _fps_manager;
    }


    SceneManager& scene_manager() noexcept
    {
        return _scene_manager;
    }


    Renderer& renderer() noexcept
    {
        return *_renderer;
    }



    virtual ~Application() override = default;


    static Application& instance() noexcept;



    void initialize(int width, int height, const std::string& title);
    void run(std::shared_ptr<Scene> initial_scene);

    void quit();
    void add_effect(std::unique_ptr<Effect> effect);


    void proc_event();
    int get_ticks();


    // NOTE: Do not depend on the order of finalization.
    void register_finalizer(std::function<void()> finalizer);


private:
    detail::SDLCore _sdl_core;
    detail::SDLTTF _sdl_ttf;
    detail::SDLImage _sdl_image;
    detail::SDLMixer _sdl_mixer;
    int _width;
    int _height;
    std::string _title;
    int _frame = 0;
    bool _will_quit = false;
    std::unique_ptr<Window> _window;
    std::unique_ptr<Renderer> _renderer;
    SceneManager _scene_manager;
    FPSManager _fps_manager;
    std::vector<std::unique_ptr<Effect>> _effects;
    std::vector<detail::scope_guard> _finalizers;

    Application() = default;

    void main_loop();
    void render_scene(std::shared_ptr<Scene> scene);
    void handle_event(const ::SDL_Event& event);
};



} // namespace snail

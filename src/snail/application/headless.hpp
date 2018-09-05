#pragma once

#include <map>
#include "../effect.hpp"
#include "../scene.hpp"


namespace elona
{
namespace snail
{

class Application final
{
public:
    enum class Orientation
    {
        portrait,
        landscape
    };

    static const constexpr bool is_android = false;

    size_t frame() const noexcept
    {
        return 1;
    }


    int width() const noexcept
    {
        return 800;
    }


    int height() const noexcept
    {
        return 600;
    }

    int physical_width() const noexcept
    {
        return 800;
    }

    int physical_height() const noexcept
    {
        return 600;
    }

    float dpi() const noexcept
    {
        return 96.0f;
    }

    Orientation orientation() const noexcept
    {
        return Orientation::landscape;
    }

    bool was_focus_lost_just_now() noexcept
    {
        return false;
    }

    const std::string& title() const noexcept
    {
        return _title;
    }


    void set_title(const std::string& title);


    ~Application() = default;

    static Application& instance();


    void initialize(const std::string& title);

    void quit();

    // NOTE: Do not depend on the order of finalization.
    void register_finalizer(std::function<void()> finalizer);


    Renderer& get_renderer()
    {
        return *_renderer;
    }


    void proc_event();

    bool is_fullscreen()
    {
        return false;
    }

    Window::FullscreenMode get_fullscreen_mode()
    {
        return Window::FullscreenMode::windowed;
    }

    void set_fullscreen_mode(Window::FullscreenMode);


    std::map<std::string, ::SDL_DisplayMode> get_display_modes()
    {
        return {};
    }

    std::string get_default_display_mode()
    {
        return "";
    }

    ::SDL_DisplayMode get_display_mode()
    {
        return ::SDL_DisplayMode{};
    }

    void set_display_mode(const std::string&);
    void set_display_mode(const ::SDL_DisplayMode);


private:
    Application() = default;
    std::unique_ptr<Window> _window;
    std::unique_ptr<Renderer> _renderer;
    bool _will_quit = false;
    const std::string _title = "";

    void main_loop();
};

} // namespace snail
} // namespace elona

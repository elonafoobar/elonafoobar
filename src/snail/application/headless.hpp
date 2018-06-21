#pragma once

#include <map>
#include "../effect.hpp"
#include "../scene.hpp"


namespace elona
{
namespace snail
{

class application final
{
public:
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

    const std::string& title() const noexcept
    {
        return _title;
    }


    void set_title(const std::string& title);


    ~application() = default;

    static application& instance();


    void initialize(const std::string& title);

    void quit();

    // NOTE: Do not depend on the order of finalization.
    void register_finalizer(std::function<void()> finalizer);


    renderer& get_renderer()
    {
        return *_renderer;
    }


    void proc_event();

    bool is_fullscreen()
    {
        return false;
    }

    window::fullscreen_mode_t get_fullscreen_mode()
    {
        return window::fullscreen_mode_t::windowed;
    }

    void set_fullscreen_mode(window::fullscreen_mode_t);


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
    application() = default;
    std::unique_ptr<renderer> _renderer;
    bool _will_quit = false;
    const std::string _title = "";

    void main_loop();
};

} // namespace snail
} // namespace elona

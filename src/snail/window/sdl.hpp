#pragma once

#include <memory>
#include <string>
#include "../../lib/noncopyable.hpp"
#include "../detail/sdl.hpp"



namespace elona
{
namespace snail
{


class window : public lib::noncopyable
{
public:
    enum InitialPosition
    {
        position_undefined = SDL_WINDOWPOS_UNDEFINED,
        position_centered = SDL_WINDOWPOS_CENTERED,
    };


    enum Flag
    {
        none = 0,
        fullscreen = SDL_WINDOW_FULLSCREEN,
        fullscreen_desktop = SDL_WINDOW_FULLSCREEN_DESKTOP,
        open_gl = SDL_WINDOW_OPENGL,
        shown = SDL_WINDOW_SHOWN,
        hidden = SDL_WINDOW_HIDDEN,
        borderless = SDL_WINDOW_BORDERLESS,
        resizable = SDL_WINDOW_RESIZABLE,
        minimized = SDL_WINDOW_MINIMIZED,
        maximized = SDL_WINDOW_MAXIMIZED,
        input_grabbed = SDL_WINDOW_INPUT_GRABBED,
        input_focus = SDL_WINDOW_INPUT_FOCUS,
        mouse_focus = SDL_WINDOW_MOUSE_FOCUS,
        foreign = SDL_WINDOW_FOREIGN,
        allow_high_dpi = SDL_WINDOW_ALLOW_HIGHDPI,
        mouse_capture = SDL_WINDOW_MOUSE_CAPTURE,
        always_on_top = SDL_WINDOW_ALWAYS_ON_TOP,
        skip_taskbar = SDL_WINDOW_SKIP_TASKBAR,
        utility = SDL_WINDOW_UTILITY,
        tooltip = SDL_WINDOW_TOOLTIP,
        popup_menu = SDL_WINDOW_POPUP_MENU,
    };


    enum class FullscreenMode : Uint32
    {
        windowed = 0,
        fullscreen = SDL_WINDOW_FULLSCREEN,
        fullscreen_desktop = SDL_WINDOW_FULLSCREEN_DESKTOP,
    };


    ::SDL_Window* ptr() noexcept
    {
        return _ptr.get();
    }


    std::pair<int, int> get_size();

    void move_to_center();

    void set_size(int width, int height);

    void set_display_mode(::SDL_DisplayMode display_mode);

    ::SDL_DisplayMode get_display_mode();

    void set_fullscreen_mode(FullscreenMode fullscreen_mode);

    window(
        const std::string& title,
        int x,
        int y,
        int width,
        int height,
        int flag);

    virtual ~window() override = default;


private:
    std::unique_ptr<::SDL_Window, decltype(&::SDL_DestroyWindow)> _ptr;
};



} // namespace snail
} // namespace elona

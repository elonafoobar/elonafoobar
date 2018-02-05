#pragma once

#include <memory>
#include <string>
#include "detail/sdl.hpp"
#include "../lib/noncopyable.hpp"


namespace snail
{
class Window : public lib::noncopyable
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


    ::SDL_Window* ptr() noexcept
    {
        return _ptr.get();
    }


    Window(
        const std::string& title,
        int x,
        int y,
        int width,
        int height,
        int flag);

    virtual ~Window() = default;


private:
    std::unique_ptr<::SDL_Window, std::decay_t<decltype(::SDL_DestroyWindow)>>
        _ptr;
};



} // namespace snail

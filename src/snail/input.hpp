#pragma once

#include <array>
#include <string>
#include "../lib/noncopyable.hpp"
#include "../optional.hpp"
#include "detail/sdl.hpp"


namespace elona
{
namespace snail
{



struct button : public lib::noncopyable
{
    bool is_pressed() const noexcept
    {
        return _is_pressed;
    }

    bool was_released_immediately() const noexcept
    {
        return _was_released_immediately;
    }

    int repeat() const noexcept
    {
        return _repeat;
    }


    void _press()
    {
        _is_pressed = true;
    }


    void _release()
    {
        _is_pressed = false;
        _repeat = -1;
        _was_released_immediately = false;
    }


    void _release_immediately()
    {
        _was_released_immediately = true;
    }


    void _increase_repeat()
    {
        ++_repeat;
    }


private:
    bool _is_pressed = false;
    bool _was_released_immediately = false;
    int _repeat = -1;
};



enum class key
{
    none,

    key_0,
    key_1,
    key_2,
    key_3,
    key_4,
    key_5,
    key_6,
    key_7,
    key_8,
    key_9,

    key_a,
    key_b,
    key_c,
    key_d,
    key_e,
    key_f,
    key_g,
    key_h,
    key_i,
    key_j,
    key_k,
    key_l,
    key_m,
    key_n,
    key_o,
    key_p,
    key_q,
    key_r,
    key_s,
    key_t,
    key_u,
    key_v,
    key_w,
    key_x,
    key_y,
    key_z,

    f1,
    f2,
    f3,
    f4,
    f5,
    f6,
    f7,
    f8,
    f9,
    f10,
    f11,
    f12,
    f13,
    f14,
    f15,
    f16,
    f17,
    f18,
    f19,
    f20,
    f21,
    f22,
    f23,
    f24,

    up,
    down,
    left,
    right,

    insert,
    clear,
    numlock,
    capslock,

    home,
    end,
    pageup,
    pagedown,

    application,
    printscreen,

    alt,
    option = alt,
    ctrl,
    gui,
    windows = gui,
    command = gui,
    shift,

    alt_l,
    option_l = alt_l,
    ctrl_l,
    gui_l,
    windows_l = gui_l,
    command_l = gui_l,
    shift_l,

    alt_r,
    option_r = alt_r,
    ctrl_r,
    gui_r,
    windows_r = gui_r,
    command_r = gui_r,
    shift_r,

    space,
    tab,
    enter,
    escape,
    backspace,
    delete_,

    equal,
    backquote,
    quote,
    backslash,
    comma,
    minus,
    period,
    rightbracket,
    leftbracket,
    semicolon,
    slash,
    ampersand,
    asterisk,
    at,
    caret,
    colon,
    dollar,
    exclaim,
    greater,
    hash,
    leftparen,
    less,
    percent,
    plus,
    question,
    quotedbl,
    rightparen,
    underscore,

    keypad_0,
    keypad_1,
    keypad_2,
    keypad_3,
    keypad_4,
    keypad_5,
    keypad_6,
    keypad_7,
    keypad_8,
    keypad_9,
    keypad_a,
    keypad_b,
    keypad_c,
    keypad_d,
    keypad_e,
    keypad_f,

    keypad_backspace,

    keypad_space,
    keypad_tab,

    keypad_period,
    keypad_plus,
    keypad_minus,
    keypad_asterisk,
    keypad_slash,
    keypad_plusminus,
    keypad_enter,
    keypad_equal,

    android_back,

    _size,
};

inline bool is_modifier(key k)
{
    switch (k)
    {
    case key::ctrl:
    case key::ctrl_l:
    case key::ctrl_r:
    case key::shift:
    case key::shift_l:
    case key::shift_r:
    case key::gui:
    case key::gui_l:
    case key::gui_r:
    case key::alt:
    case key::alt_l:
    case key::alt_r: return true;
    default: return false;
    }
}



class mouse_t
{
public:
    enum class button_t
    {
        left,
        middle,
        right,
        x1,
        x2,

        _size,
    };


    int x() const
    {
        return _x;
    }


    int y() const
    {
        return _y;
    }


    const button& operator[](button_t button) const
    {
        return buttons[static_cast<size_t>(button)];
    }


    void _handle_event(const ::SDL_MouseButtonEvent& event);

    void update();


private:
    int _x;
    int _y;
    std::array<button, static_cast<size_t>(button_t::_size)> buttons;
};



class input final : public lib::noncopyable
{
public:
    bool is_pressed(key k, int key_wait = 1) const;
    bool is_pressed(mouse_t::button_t b) const;
    bool was_pressed_just_now(key k) const;
    bool was_pressed_just_now(mouse_t::button_t b) const;

    bool is_ime_active() const;

    void show_soft_keyboard();
    void hide_soft_keyboard();
    void toggle_soft_keyboard();

    const mouse_t& mouse() const
    {
        return _mouse;
    }


    /***
     * Disables NumLock to prevent strange Windows-specific behavior when
     * holding Shift and pressing a numpad key. What happens with NumLock
     * enabled is the numpad key reverts to its non-NumLock functionality,
     * but Shift becomes depressed for some reason. This prevents the
     * player from running when holding Shift and pressing a numpad
     * movement key. This does not happen on Linux, so it's probably a
     * Windows-specific quirk.
     *
     * This method has no effect on platforms besides Windows.
     */
    void disable_numlock();

    /***
     * Restores NumLock if it was disabled at some point by disable_numlock().
     *
     * This method has no effect on platforms besides Windows.
     */
    void restore_numlock();

    std::string pop_text()
    {
        std::string ret = _text;
        _text.clear();
        return ret;
    }


    void set_quick_action_repeat_start_wait(int wait) noexcept
    {
        _quick_action_repeat_start_wait = wait;
    }

    void set_quick_action_repeat_wait(int wait) noexcept
    {
        _quick_action_repeat_wait = wait;
    }


    virtual ~input() override = default;


    static input& instance() noexcept;


    void _update();
    void _handle_event(const ::SDL_KeyboardEvent& event);
    void _handle_event(const ::SDL_TextInputEvent& event);
    void _handle_event(const ::SDL_TextEditingEvent& event);
    void _handle_event(const ::SDL_TouchFingerEvent& event);
    void _handle_event(const ::SDL_MouseButtonEvent& event);


private:
    std::array<button, static_cast<size_t>(key::_size)> _keys;
    std::string _text;
    bool _is_ime_active{};
    bool _needs_restore_numlock{};

    // Members for handling text input of on-screen quick action
    // buttons on Android. They need to be here since quick actions
    // can modify inputted text.
    optional<snail::key> _last_quick_action_key = none;
    optional<std::string> _last_quick_action_text = none;
    int _quick_action_key_repeat = -1;
    int _quick_action_text_repeat = -1;
    int _quick_action_repeat_start_wait = 10;
    int _quick_action_repeat_wait = 2;

    mouse_t _mouse;

    input() = default;
};



} // namespace snail
} // namespace elona

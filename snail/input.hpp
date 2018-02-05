#pragma once

#include <array>
#include <string>
#include "../lib/noncopyable.hpp"
#include "detail/sdl.hpp"


namespace elona::snail
{



struct button
{
    bool is_pressed() const noexcept
    {
        return _is_pressed;
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
    }


    void _increase_repeat()
    {
        ++_repeat;
    }


private:
    bool _is_pressed = false;
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

    _size,
};


char to_char(key);



class input final : public lib::noncopyable
{
public:
    bool is_pressed(key k) const;
    bool is_pressed_exactly(key k) const;
    bool was_pressed_just_now(key k) const;

    void set_key_repeat(int initial_key_wait, int key_wait) noexcept;


    // Returns only one key even if you are pressing more than one key.
    key get_pressed_key() const noexcept;


    virtual ~input() override = default;


    static input& instance() noexcept;


    void _update();
    void _handle_event(const ::SDL_KeyboardEvent& event);


private:
    std::array<button, static_cast<size_t>(key::_size)> _keys;
    int _initial_key_wait = 30; // frame
    int _key_wait = 5; // frame

    input() = default;
};



} // namespace elona::snail

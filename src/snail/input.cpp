#include "input.hpp"
#include <cassert>
#include <algorithm>
#include <iostream>
#include <tuple>
#include "touch_input.hpp"
#ifdef _WIN32
#include <windows.h> // GetKeyboardState, keybd_event
#endif

using namespace elona::snail;


namespace
{


Key sdlkey2key(::SDL_Keycode k)
{
    switch (k)
    {
    case SDLK_0: return Key::key_0;
    case SDLK_1: return Key::key_1;
    case SDLK_2: return Key::key_2;
    case SDLK_3: return Key::key_3;
    case SDLK_4: return Key::key_4;
    case SDLK_5: return Key::key_5;
    case SDLK_6: return Key::key_6;
    case SDLK_7: return Key::key_7;
    case SDLK_8: return Key::key_8;
    case SDLK_9: return Key::key_9;
    case SDLK_a: return Key::key_a;
    case SDLK_b: return Key::key_b;
    case SDLK_c: return Key::key_c;
    case SDLK_d: return Key::key_d;
    case SDLK_e: return Key::key_e;
    case SDLK_f: return Key::key_f;
    case SDLK_g: return Key::key_g;
    case SDLK_h: return Key::key_h;
    case SDLK_i: return Key::key_i;
    case SDLK_j: return Key::key_j;
    case SDLK_k: return Key::key_k;
    case SDLK_l: return Key::key_l;
    case SDLK_m: return Key::key_m;
    case SDLK_n: return Key::key_n;
    case SDLK_o: return Key::key_o;
    case SDLK_p: return Key::key_p;
    case SDLK_q: return Key::key_q;
    case SDLK_r: return Key::key_r;
    case SDLK_s: return Key::key_s;
    case SDLK_t: return Key::key_t;
    case SDLK_u: return Key::key_u;
    case SDLK_v: return Key::key_v;
    case SDLK_w: return Key::key_w;
    case SDLK_x: return Key::key_x;
    case SDLK_y: return Key::key_y;
    case SDLK_z: return Key::key_z;
    case SDLK_F1: return Key::f1;
    case SDLK_F2: return Key::f2;
    case SDLK_F3: return Key::f3;
    case SDLK_F4: return Key::f4;
    case SDLK_F5: return Key::f5;
    case SDLK_F6: return Key::f6;
    case SDLK_F7: return Key::f7;
    case SDLK_F8: return Key::f8;
    case SDLK_F9: return Key::f9;
    case SDLK_F10: return Key::f10;
    case SDLK_F11: return Key::f11;
    case SDLK_F12: return Key::f12;
    case SDLK_F13: return Key::f13;
    case SDLK_F14: return Key::f14;
    case SDLK_F15: return Key::f15;
    case SDLK_F16: return Key::f16;
    case SDLK_F17: return Key::f17;
    case SDLK_F18: return Key::f18;
    case SDLK_F19: return Key::f19;
    case SDLK_F20: return Key::f20;
    case SDLK_F21: return Key::f21;
    case SDLK_F22: return Key::f22;
    case SDLK_F23: return Key::f23;
    case SDLK_F24: return Key::f24;
    case SDLK_UP: return Key::up;
    case SDLK_DOWN: return Key::down;
    case SDLK_LEFT: return Key::left;
    case SDLK_RIGHT: return Key::right;
    case SDLK_INSERT: return Key::insert;
    case SDLK_CLEAR: return Key::clear;
    case SDLK_NUMLOCKCLEAR: return Key::numlock;
    case SDLK_CAPSLOCK: return Key::capslock;
    case SDLK_HOME: return Key::home;
    case SDLK_END: return Key::end;
    case SDLK_PAGEUP: return Key::pageup;
    case SDLK_PAGEDOWN: return Key::pagedown;
    case SDLK_APPLICATION: return Key::application;
    case SDLK_PRINTSCREEN: return Key::printscreen;
    case SDLK_LALT: return Key::alt_l;
    case SDLK_LCTRL: return Key::ctrl_l;
    case SDLK_LGUI: return Key::gui_l;
    case SDLK_LSHIFT: return Key::shift_l;
    case SDLK_RALT: return Key::alt_r;
    case SDLK_RCTRL: return Key::ctrl_r;
    case SDLK_RGUI: return Key::gui_r;
    case SDLK_RSHIFT: return Key::shift_r;
    case SDLK_SPACE: return Key::space;
    case SDLK_TAB: return Key::tab;
    case SDLK_RETURN: return Key::enter;
    case SDLK_ESCAPE: return Key::escape;
    case SDLK_BACKSPACE: return Key::backspace;
    case SDLK_DELETE: return Key::delete_;
    case SDLK_EQUALS: return Key::equal;
    case SDLK_BACKQUOTE: return Key::backquote;
    case SDLK_QUOTE: return Key::quote;
    case SDLK_BACKSLASH: return Key::backslash;
    case SDLK_COMMA: return Key::comma;
    case SDLK_MINUS: return Key::minus;
    case SDLK_PERIOD: return Key::period;
    case SDLK_RIGHTBRACKET: return Key::rightbracket;
    case SDLK_LEFTBRACKET: return Key::leftbracket;
    case SDLK_SEMICOLON: return Key::semicolon;
    case SDLK_SLASH: return Key::slash;
    case SDLK_AMPERSAND: return Key::ampersand;
    case SDLK_ASTERISK: return Key::asterisk;
    case SDLK_AT: return Key::at;
    case SDLK_CARET: return Key::caret;
    case SDLK_COLON: return Key::colon;
    case SDLK_DOLLAR: return Key::dollar;
    case SDLK_EXCLAIM: return Key::exclaim;
    case SDLK_GREATER: return Key::greater;
    case SDLK_HASH: return Key::hash;
    case SDLK_LEFTPAREN: return Key::leftparen;
    case SDLK_LESS: return Key::less;
    case SDLK_PERCENT: return Key::percent;
    case SDLK_PLUS: return Key::plus;
    case SDLK_QUESTION: return Key::question;
    case SDLK_QUOTEDBL: return Key::quotedbl;
    case SDLK_RIGHTPAREN: return Key::rightparen;
    case SDLK_UNDERSCORE: return Key::underscore;
    case SDLK_KP_0: return Key::keypad_0;
    case SDLK_KP_1: return Key::keypad_1;
    case SDLK_KP_2: return Key::keypad_2;
    case SDLK_KP_3: return Key::keypad_3;
    case SDLK_KP_4: return Key::keypad_4;
    case SDLK_KP_5: return Key::keypad_5;
    case SDLK_KP_6: return Key::keypad_6;
    case SDLK_KP_7: return Key::keypad_7;
    case SDLK_KP_8: return Key::keypad_8;
    case SDLK_KP_9: return Key::keypad_9;
    case SDLK_KP_A: return Key::keypad_a;
    case SDLK_KP_B: return Key::keypad_b;
    case SDLK_KP_C: return Key::keypad_c;
    case SDLK_KP_D: return Key::keypad_d;
    case SDLK_KP_E: return Key::keypad_e;
    case SDLK_KP_F: return Key::keypad_f;
    case SDLK_KP_BACKSPACE: return Key::keypad_backspace;
    case SDLK_KP_SPACE: return Key::keypad_space;
    case SDLK_KP_TAB: return Key::keypad_tab;
    case SDLK_KP_PERIOD: return Key::keypad_period;
    case SDLK_KP_PLUS: return Key::keypad_plus;
    case SDLK_KP_MINUS: return Key::keypad_minus;
    case SDLK_KP_MULTIPLY: return Key::keypad_asterisk;
    case SDLK_KP_DIVIDE: return Key::keypad_slash;
    case SDLK_KP_PLUSMINUS: return Key::keypad_plusminus;
    case SDLK_KP_ENTER: return Key::keypad_enter;
    case SDLK_KP_EQUALS: return Key::keypad_equal;
    case SDLK_AC_BACK: return Key::android_back;
    default: return Key::none;
    }
}


} // namespace



namespace elona
{
namespace snail
{



void Mouse::_handle_event(const ::SDL_MouseButtonEvent& event)
{
    _x = event.x;
    _y = event.y;

    if (event.type != SDL_MOUSEBUTTONUP && event.type != SDL_MOUSEBUTTONDOWN)
        return;

    Button button;
    switch (event.button)
    {
    case SDL_BUTTON_LEFT: button = Button::left; break;
    case SDL_BUTTON_MIDDLE: button = Button::middle; break;
    case SDL_BUTTON_RIGHT: button = Button::right; break;
    case SDL_BUTTON_X1: button = Button::x1; break;
    case SDL_BUTTON_X2: button = Button::x2; break;
    default: return;
    }

    if (event.state == SDL_PRESSED)
        buttons[static_cast<size_t>(button)]._press();
    else
        buttons[static_cast<size_t>(button)]._release();
}



void Mouse::update()
{
    for (auto&& button : buttons)
    {
        if (button.is_pressed())
            button._increase_repeat();
    }
}



Input& Input::instance() noexcept
{
    static Input the_instance;
    return the_instance;
}



/*
key_wait = 1
a a a a a a a a a a a a a a a a a a a a a
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0
x x x x x x x x x x x x x x x x x x x x x

key_wait = 5
a a a a a a a a a a a a a a a a a a a a a
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0
x         x         x         x         x
*/
bool Input::is_pressed(Key k, int key_wait) const
{
    const auto& key = _keys[static_cast<size_t>(k)];
    return key.is_pressed() && key.repeat() % key_wait == 0;
}



bool Input::is_pressed(Mouse::Button b) const
{
    return was_pressed_just_now(b);
}



bool Input::was_pressed_just_now(Key k) const
{
    return is_pressed(k) && _keys[static_cast<size_t>(k)].repeat() == 0;
}



bool Input::was_pressed_just_now(Mouse::Button b) const
{
    return mouse()[b].is_pressed();
}



bool Input::is_ime_active() const
{
    return _is_ime_active;
}



void Input::show_soft_keyboard()
{
    _is_ime_active = true;
    ::SDL_StartTextInput();
}

void Input::hide_soft_keyboard()
{
    ::SDL_StopTextInput();
    _is_ime_active = false;
}

void Input::toggle_soft_keyboard()
{
    if (::SDL_IsTextInputActive())
        hide_soft_keyboard();
    else
        show_soft_keyboard();
}


void Input::disable_numlock()
{
    // SDL always reports numlock as being off when the program
    // starts, even if it was on before. The Shift+numpad strangeness
    // only happens on Windows, so it should be reasonable to use
    // Windows APIs here.
#ifdef _WIN32
    if (GetKeyState(VK_NUMLOCK))
    {
        keybd_event(VK_NUMLOCK, 0x45, KEYEVENTF_EXTENDEDKEY, 0);
        keybd_event(
            VK_NUMLOCK, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
        _needs_restore_numlock = true;
    }
#endif
}

void Input::restore_numlock()
{
#ifdef _WIN32
    if (!GetKeyState(VK_NUMLOCK) && _needs_restore_numlock)
    {
        keybd_event(VK_NUMLOCK, 0x45, KEYEVENTF_EXTENDEDKEY, 0);
        keybd_event(
            VK_NUMLOCK, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
    }
#endif
}



void Input::_update()
{
    // Check for touched Android quick actions that send keypresses.
    if (_last_quick_action_key)
    {
        _quick_action_key_repeat++;

        if (_quick_action_key_repeat == 0
            || (_quick_action_key_repeat > _quick_action_repeat_start_wait
                && _quick_action_key_repeat % _quick_action_repeat_wait))
        {
            _keys[static_cast<size_t>(*_last_quick_action_key)]._press();
        }
    }

    for (auto&& key : _keys)
    {
        if (key.was_released_immediately() && key.repeat() == 0)
        {
            key._release();
        }
        if (key.is_pressed())
        {
            key._increase_repeat();
        }
    }

    // Check for touched Android quick actions that send text inputs
    // instead of key presses.
    if (_last_quick_action_text)
    {
        // Keywait has to be emulated here because SDL_TextInputEvent
        // would usually be spaced apart for the specified text input
        // delay at the OS level, but there is no such mechanism for
        // on-screen quick actions.
        _quick_action_text_repeat++;

        if (_quick_action_text_repeat == 0
            || (_quick_action_text_repeat > _quick_action_repeat_start_wait
                && _quick_action_text_repeat % _quick_action_repeat_wait))
        {
            _text = *_last_quick_action_text;
        }
    }
}



void Input::_handle_event(const ::SDL_KeyboardEvent& event)
{
    if (_is_ime_active)
    {
        _is_ime_active = false;
    }

    const auto k = sdlkey2key(event.keysym.sym);
    if (k == Key::none)
        return;

    auto& the_key = _keys[static_cast<size_t>(k)];
    if (event.state == SDL_PRESSED)
    {
        the_key._press();
    }
    else
    {
        // On Android, certain keys in the software keyboard seem to
        // be pressed then released immediately after (backspace,
        // return) such that the press and release events come in the
        // same event polling cycle. In that case, mark the key as
        // pressed but immediately released, and allow it to be
        // detected for a single frame before releasing it in
        // Input::update().
        if (the_key.is_pressed() && the_key.repeat() == -1)
        {
            the_key._release_immediately();
        }
        else
        {
            the_key._release();

            if (k == Key::android_back)
            {
                toggle_soft_keyboard();
            }
        }
    }

    using KeyTuple = std::tuple<Key, Key, Key>[];
    for (const auto& tuple : KeyTuple{
             {Key::alt, Key::alt_l, Key::alt_r},
             {Key::ctrl, Key::ctrl_l, Key::ctrl_r},
             {Key::gui, Key::gui_l, Key::gui_r},
             {Key::shift, Key::shift_l, Key::shift_r},
         })
    {
        if (_keys[static_cast<size_t>(std::get<1>(tuple))].is_pressed()
            || _keys[static_cast<int>(std::get<2>(tuple))].is_pressed())
        {
            _keys[static_cast<size_t>(std::get<0>(tuple))]._press();
        }
        else
        {
            _keys[static_cast<size_t>(std::get<0>(tuple))]._release();
        }
    }
}


void Input::_handle_event(const ::SDL_TextInputEvent& event)
{
    _text = event.text;

    if (_is_ime_active) // event.text is IME-translated.
    {
        _keys[static_cast<size_t>(snail::Key::enter)]._release();
        _keys[static_cast<size_t>(snail::Key::keypad_enter)]._release();
        _is_ime_active = false;
    }
}


void Input::_handle_event(const ::SDL_TextEditingEvent& event)
{
    (void)event;

    _is_ime_active = true;
}


void Input::_handle_event(const ::SDL_TouchFingerEvent& event)
{
    bool release_key = false;
    bool stop_text = false;

    TouchInput::instance().on_touch_event(event);

    auto action = TouchInput::instance().last_touched_quick_action();

    if (action)
    {
        if (action->key)
        {
            // Keypress action
            if (_last_quick_action_key
                && *_last_quick_action_key != action->key)
            {
                _keys[static_cast<size_t>(*_last_quick_action_key)]._release();
            }

            _keys[static_cast<size_t>(*action->key)]._press();

            _last_quick_action_key = action->key;
            stop_text = true;
        }
        else
        {
            _last_quick_action_text = action->text;
            release_key = true;
        }
    }
    else
    {
        stop_text = true;
        release_key = true;
    }

    if (release_key && _last_quick_action_key)
    {
        _keys[static_cast<size_t>(*_last_quick_action_key)]._release();
        _last_quick_action_key = none;
        _quick_action_key_repeat = -1;
    }
    if (stop_text)
    {
        _last_quick_action_text = none;
        _quick_action_text_repeat = -1;
    }
}



void Input::_handle_event(const ::SDL_MouseButtonEvent& event)
{
    _mouse._handle_event(event);
}



} // namespace snail
} // namespace elona

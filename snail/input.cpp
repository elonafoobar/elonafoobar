#include "input.hpp"
#include <cassert>
#include <algorithm>
#include <iostream>
#include <tuple>

using namespace elona::snail;


namespace
{


key sdlkey2key(::SDL_Keycode k)
{
    switch (k)
    {
    case SDLK_0: return key::key_0;
    case SDLK_1: return key::key_1;
    case SDLK_2: return key::key_2;
    case SDLK_3: return key::key_3;
    case SDLK_4: return key::key_4;
    case SDLK_5: return key::key_5;
    case SDLK_6: return key::key_6;
    case SDLK_7: return key::key_7;
    case SDLK_8: return key::key_8;
    case SDLK_9: return key::key_9;
    case SDLK_a: return key::key_a;
    case SDLK_b: return key::key_b;
    case SDLK_c: return key::key_c;
    case SDLK_d: return key::key_d;
    case SDLK_e: return key::key_e;
    case SDLK_f: return key::key_f;
    case SDLK_g: return key::key_g;
    case SDLK_h: return key::key_h;
    case SDLK_i: return key::key_i;
    case SDLK_j: return key::key_j;
    case SDLK_k: return key::key_k;
    case SDLK_l: return key::key_l;
    case SDLK_m: return key::key_m;
    case SDLK_n: return key::key_n;
    case SDLK_o: return key::key_o;
    case SDLK_p: return key::key_p;
    case SDLK_q: return key::key_q;
    case SDLK_r: return key::key_r;
    case SDLK_s: return key::key_s;
    case SDLK_t: return key::key_t;
    case SDLK_u: return key::key_u;
    case SDLK_v: return key::key_v;
    case SDLK_w: return key::key_w;
    case SDLK_x: return key::key_x;
    case SDLK_y: return key::key_y;
    case SDLK_z: return key::key_z;
    case SDLK_F1: return key::f1;
    case SDLK_F2: return key::f2;
    case SDLK_F3: return key::f3;
    case SDLK_F4: return key::f4;
    case SDLK_F5: return key::f5;
    case SDLK_F6: return key::f6;
    case SDLK_F7: return key::f7;
    case SDLK_F8: return key::f8;
    case SDLK_F9: return key::f9;
    case SDLK_F10: return key::f10;
    case SDLK_F11: return key::f11;
    case SDLK_F12: return key::f12;
    case SDLK_F13: return key::f13;
    case SDLK_F14: return key::f14;
    case SDLK_F15: return key::f15;
    case SDLK_F16: return key::f16;
    case SDLK_F17: return key::f17;
    case SDLK_F18: return key::f18;
    case SDLK_F19: return key::f19;
    case SDLK_F20: return key::f20;
    case SDLK_F21: return key::f21;
    case SDLK_F22: return key::f22;
    case SDLK_F23: return key::f23;
    case SDLK_F24: return key::f24;
    case SDLK_UP: return key::up;
    case SDLK_DOWN: return key::down;
    case SDLK_LEFT: return key::left;
    case SDLK_RIGHT: return key::right;
    case SDLK_INSERT: return key::insert;
    case SDLK_NUMLOCKCLEAR: return key::numlock;
    case SDLK_CAPSLOCK: return key::capslock;
    case SDLK_HOME: return key::home;
    case SDLK_END: return key::end;
    case SDLK_PAGEUP: return key::pageup;
    case SDLK_PAGEDOWN: return key::pagedown;
    case SDLK_APPLICATION: return key::application;
    case SDLK_PRINTSCREEN: return key::printscreen;
    case SDLK_LALT: return key::alt_l;
    case SDLK_LCTRL: return key::ctrl_l;
    case SDLK_LGUI: return key::gui_l;
    case SDLK_LSHIFT: return key::shift_l;
    case SDLK_RALT: return key::alt_r;
    case SDLK_RCTRL: return key::ctrl_r;
    case SDLK_RGUI: return key::gui_r;
    case SDLK_RSHIFT: return key::shift_r;
    case SDLK_SPACE: return key::space;
    case SDLK_TAB: return key::tab;
    case SDLK_RETURN: return key::enter;
    case SDLK_ESCAPE: return key::escape;
    case SDLK_BACKSPACE: return key::backspace;
    case SDLK_DELETE: return key::delete_;
    case SDLK_EQUALS: return key::equal;
    case SDLK_BACKQUOTE: return key::backquote;
    case SDLK_QUOTE: return key::quote;
    case SDLK_BACKSLASH: return key::backslash;
    case SDLK_COMMA: return key::comma;
    case SDLK_MINUS: return key::minus;
    case SDLK_PERIOD: return key::period;
    case SDLK_RIGHTBRACKET: return key::rightbracket;
    case SDLK_LEFTBRACKET: return key::leftbracket;
    case SDLK_SEMICOLON: return key::semicolon;
    case SDLK_SLASH: return key::slash;
    case SDLK_AMPERSAND: return key::ampersand;
    case SDLK_ASTERISK: return key::asterisk;
    case SDLK_AT: return key::at;
    case SDLK_CARET: return key::caret;
    case SDLK_COLON: return key::colon;
    case SDLK_DOLLAR: return key::dollar;
    case SDLK_EXCLAIM: return key::exclaim;
    case SDLK_GREATER: return key::greater;
    case SDLK_HASH: return key::hash;
    case SDLK_LEFTPAREN: return key::leftparen;
    case SDLK_LESS: return key::less;
    case SDLK_PERCENT: return key::percent;
    case SDLK_PLUS: return key::plus;
    case SDLK_QUESTION: return key::question;
    case SDLK_QUOTEDBL: return key::quotedbl;
    case SDLK_RIGHTPAREN: return key::rightparen;
    case SDLK_UNDERSCORE: return key::underscore;
    case SDLK_KP_0: return key::keypad_0;
    case SDLK_KP_1: return key::keypad_1;
    case SDLK_KP_2: return key::keypad_2;
    case SDLK_KP_3: return key::keypad_3;
    case SDLK_KP_4: return key::keypad_4;
    case SDLK_KP_5: return key::keypad_5;
    case SDLK_KP_6: return key::keypad_6;
    case SDLK_KP_7: return key::keypad_7;
    case SDLK_KP_8: return key::keypad_8;
    case SDLK_KP_9: return key::keypad_9;
    case SDLK_KP_A: return key::keypad_a;
    case SDLK_KP_B: return key::keypad_b;
    case SDLK_KP_C: return key::keypad_c;
    case SDLK_KP_D: return key::keypad_d;
    case SDLK_KP_E: return key::keypad_e;
    case SDLK_KP_F: return key::keypad_f;
    case SDLK_KP_BACKSPACE: return key::keypad_backspace;
    case SDLK_KP_SPACE: return key::keypad_space;
    case SDLK_KP_TAB: return key::keypad_tab;
    case SDLK_KP_PERIOD: return key::keypad_period;
    case SDLK_KP_PLUS: return key::keypad_plus;
    case SDLK_KP_MINUS: return key::keypad_minus;
    case SDLK_KP_MULTIPLY: return key::keypad_asterisk;
    case SDLK_KP_DIVIDE: return key::keypad_slash;
    case SDLK_KP_PLUSMINUS: return key::keypad_plusminus;
    case SDLK_KP_ENTER: return key::keypad_enter;
    case SDLK_KP_EQUALS: return key::keypad_equal;
    default: return key::none;
    }
}


} // namespace



namespace elona
{
namespace snail
{


// class Mouse
// {
// static:
//     enum ButtonType
//     {
//         left,
//         middle,
//         right,
//         x1,
//         x2,
//     }
//
//     @property auto position()
//     {
//         return tuple!("x", "y")(_x, _y);
//     }
//
//     @property int x()
//     {
//         return _x;
//     }
//
//     @property int y()
//     {
//         return _y;
//     }
//
//
//     auto opIndex(ButtonType button)
//     {
//         return _mouseButtons[button];
//     }
//
//
//     package
//     {
//         void handleEvent(sdl.SDL_MouseButtonEvent event)
//         {
//             _x = event.x;
//             _y = event.y;
//
//             if (event.type != sdl.SDL_MOUSEBUTTONUP && event.type !=
//             sdl.SDL_MOUSEBUTTONDOWN)
//                 return;
//
//             ButtonType button;
//             switch (event.button)
//             {
//             case sdl.SDL_BUTTON_LEFT:
//                 button = ButtonType.left;
//                 break;
//             case sdl.SDL_BUTTON_MIDDLE:
//                 button = ButtonType.middle;
//                 break;
//             case sdl.SDL_BUTTON_RIGHT:
//                 button = ButtonType.right;
//                 break;
//             case sdl.SDL_BUTTON_X1:
//                 button = ButtonType.x1;
//                 break;
//             case sdl.SDL_BUTTON_X2:
//                 button = ButtonType.x2;
//                 break;
//             default:
//                 return;
//             }
//
//             if (event.state == sdl.SDL_PRESSED)
//                 _mouseButtons[button].press();
//             else
//                 _mouseButtons[button].release();
//         }
//
//
//         void update()
//         {
//             foreach (ref button; _mouseButtons)
//             {
//                 if (button.isPressed)
//                     button.increaseRepeat();
//             }
//         }
//     }
//
//
//     private
//     {
//         int _x;
//         int _y;
//         button[ButtonType.max + 1] _mouseButtons;
//     }
// }



input& input::instance() noexcept
{
    static input the_instance;
    return the_instance;
}



/*
_initial_key_wait = 10, _key_wait = 3
a a a a a a a a a a a a a a a a a a a a
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9
*                   *     *     *     *
*/
bool input::is_pressed(key k) const
{
    if (!_keys[static_cast<size_t>(k)].is_pressed())
        return false;

    // Trying to repeat a modifier key will cause the modifier to be pressed repeatedly.
    // For the case of shift this causes the cancel action to constantly fire.
    // We want to treat modifiers as held instead of trying to repeat them.
    if(is_modifier(k))
        return true;

    const auto repeat = _keys[static_cast<size_t>(k)].repeat();
    if (repeat == 0)
    {
        return true;
    }
    else if (repeat == _initial_key_wait)
    {
        return true;
    }
    else if (
        repeat > _initial_key_wait
        && (repeat - _initial_key_wait) % _key_wait == 0)
    {
        return true;
    }
    return false;
}



bool input::is_pressed_exactly(key k) const
{
    return _keys[static_cast<size_t>(k)].is_pressed();
}



bool input::was_pressed_just_now(key k) const
{
    return is_pressed_exactly(k) && _keys[static_cast<size_t>(k)].repeat() == 0;
}



void input::set_key_repeat(int initial_key_wait, int key_wait) noexcept
{
    _initial_key_wait = std::max(initial_key_wait, 1);
    _key_wait = std::max(key_wait, 1);
}



bool input::is_ime_active() const
{
    return _is_ime_active;
}



void input::inactivate_ime()
{
    _is_ime_active = false;
}



void input::_update()
{
    for (auto&& key : _keys)
    {
        if (key.is_pressed())
        {
            key._increase_repeat();
        }
    }
}



void input::_handle_event(const ::SDL_KeyboardEvent& event)
{
    const auto k = sdlkey2key(event.keysym.sym);
    if (k == key::none)
        return;

    if (event.state == SDL_PRESSED)
    {
        _keys[static_cast<size_t>(k)]._press();
    }
    else
    {
        _keys[static_cast<size_t>(k)]._release();
    }

    using tuples_t = std::tuple<key, key, key>[];
    for (const auto& tuple : tuples_t{
             {key::alt, key::alt_l, key::alt_r},
             {key::ctrl, key::ctrl_l, key::ctrl_r},
             {key::gui, key::gui_l, key::gui_r},
             {key::shift, key::shift_l, key::shift_r},
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


void input::_handle_event(const ::SDL_TextInputEvent& event)
{
    _text = event.text;

    if (_is_ime_active) // event.text is IME-translated.
    {
        _keys[static_cast<size_t>(snail::key::enter)]._release();
        _is_ime_active = false;
    }
}


void input::_handle_event(const ::SDL_TextEditingEvent& event)
{
    _is_ime_active = true;
}



} // namespace snail
} // namespace elona

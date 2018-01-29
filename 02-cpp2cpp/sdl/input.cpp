#include "input.hpp"
#include <cassert>
#include <algorithm>
#include <tuple>

using namespace snail;


namespace
{


Key sdlkey2key(::SDL_Keycode key)
{
    switch (key)
    {
    case SDLK_0:            return Key::key_0;
    case SDLK_1:            return Key::key_1;
    case SDLK_2:            return Key::key_2;
    case SDLK_3:            return Key::key_3;
    case SDLK_4:            return Key::key_4;
    case SDLK_5:            return Key::key_5;
    case SDLK_6:            return Key::key_6;
    case SDLK_7:            return Key::key_7;
    case SDLK_8:            return Key::key_8;
    case SDLK_9:            return Key::key_9;
    case SDLK_a:            return Key::key_a;
    case SDLK_b:            return Key::key_b;
    case SDLK_c:            return Key::key_c;
    case SDLK_d:            return Key::key_d;
    case SDLK_e:            return Key::key_e;
    case SDLK_f:            return Key::key_f;
    case SDLK_g:            return Key::key_g;
    case SDLK_h:            return Key::key_h;
    case SDLK_i:            return Key::key_i;
    case SDLK_j:            return Key::key_j;
    case SDLK_k:            return Key::key_k;
    case SDLK_l:            return Key::key_l;
    case SDLK_m:            return Key::key_m;
    case SDLK_n:            return Key::key_n;
    case SDLK_o:            return Key::key_o;
    case SDLK_p:            return Key::key_p;
    case SDLK_q:            return Key::key_q;
    case SDLK_r:            return Key::key_r;
    case SDLK_s:            return Key::key_s;
    case SDLK_t:            return Key::key_t;
    case SDLK_u:            return Key::key_u;
    case SDLK_v:            return Key::key_v;
    case SDLK_w:            return Key::key_w;
    case SDLK_x:            return Key::key_x;
    case SDLK_y:            return Key::key_y;
    case SDLK_z:            return Key::key_z;
    case SDLK_F1:           return Key::f1;
    case SDLK_F2:           return Key::f2;
    case SDLK_F3:           return Key::f3;
    case SDLK_F4:           return Key::f4;
    case SDLK_F5:           return Key::f5;
    case SDLK_F6:           return Key::f6;
    case SDLK_F7:           return Key::f7;
    case SDLK_F8:           return Key::f8;
    case SDLK_F9:           return Key::f9;
    case SDLK_F10:          return Key::f10;
    case SDLK_F11:          return Key::f11;
    case SDLK_F12:          return Key::f12;
    case SDLK_F13:          return Key::f13;
    case SDLK_F14:          return Key::f14;
    case SDLK_F15:          return Key::f15;
    case SDLK_F16:          return Key::f16;
    case SDLK_F17:          return Key::f17;
    case SDLK_F18:          return Key::f18;
    case SDLK_F19:          return Key::f19;
    case SDLK_F20:          return Key::f20;
    case SDLK_F21:          return Key::f21;
    case SDLK_F22:          return Key::f22;
    case SDLK_F23:          return Key::f23;
    case SDLK_F24:          return Key::f24;
    case SDLK_UP:           return Key::up;
    case SDLK_DOWN:         return Key::down;
    case SDLK_LEFT:         return Key::left;
    case SDLK_RIGHT:        return Key::right;
    case SDLK_INSERT:       return Key::insert;
    case SDLK_NUMLOCKCLEAR: return Key::numlock;
    case SDLK_CAPSLOCK:     return Key::capslock;
    case SDLK_HOME:         return Key::home;
    case SDLK_END:          return Key::end;
    case SDLK_PAGEUP:       return Key::pageup;
    case SDLK_PAGEDOWN:     return Key::pagedown;
    case SDLK_APPLICATION:  return Key::application;
    case SDLK_PRINTSCREEN:  return Key::printscreen;
    case SDLK_LALT:         return Key::alt_l;
    case SDLK_LCTRL:        return Key::ctrl_l;
    case SDLK_LGUI:         return Key::gui_l;
    case SDLK_LSHIFT:       return Key::shift_l;
    case SDLK_RALT:         return Key::alt_r;
    case SDLK_RCTRL:        return Key::ctrl_r;
    case SDLK_RGUI:         return Key::gui_r;
    case SDLK_RSHIFT:       return Key::shift_r;
    case SDLK_SPACE:        return Key::space;
    case SDLK_TAB:          return Key::tab;
    case SDLK_RETURN:       return Key::enter;
    case SDLK_ESCAPE:       return Key::escape;
    case SDLK_BACKSPACE:    return Key::backspace;
    case SDLK_DELETE:       return Key::delete_;
    case SDLK_EQUALS:       return Key::equal;
    case SDLK_BACKQUOTE:    return Key::backquote;
    case SDLK_QUOTE:        return Key::quote;
    case SDLK_BACKSLASH:    return Key::backslash;
    case SDLK_COMMA:        return Key::comma;
    case SDLK_MINUS:        return Key::minus;
    case SDLK_PERIOD:       return Key::period;
    case SDLK_RIGHTBRACKET: return Key::rightbracket;
    case SDLK_LEFTBRACKET:  return Key::leftbracket;
    case SDLK_SEMICOLON:    return Key::semicolon;
    case SDLK_SLASH:        return Key::slash;
    case SDLK_AMPERSAND:    return Key::ampersand;
    case SDLK_ASTERISK:     return Key::asterisk;
    case SDLK_AT:           return Key::at;
    case SDLK_CARET:        return Key::caret;
    case SDLK_COLON:        return Key::colon;
    case SDLK_DOLLAR:       return Key::dollar;
    case SDLK_EXCLAIM:      return Key::exclaim;
    case SDLK_GREATER:      return Key::greater;
    case SDLK_HASH:         return Key::hash;
    case SDLK_LEFTPAREN:    return Key::leftparen;
    case SDLK_LESS:         return Key::less;
    case SDLK_PERCENT:      return Key::percent;
    case SDLK_PLUS:         return Key::plus;
    case SDLK_QUESTION:     return Key::question;
    case SDLK_QUOTEDBL:     return Key::quotedbl;
    case SDLK_RIGHTPAREN:   return Key::rightparen;
    case SDLK_UNDERSCORE:   return Key::underscore;
    case SDLK_KP_0:         return Key::keypad_0;
    case SDLK_KP_1:         return Key::keypad_1;
    case SDLK_KP_2:         return Key::keypad_2;
    case SDLK_KP_3:         return Key::keypad_3;
    case SDLK_KP_4:         return Key::keypad_4;
    case SDLK_KP_5:         return Key::keypad_5;
    case SDLK_KP_6:         return Key::keypad_6;
    case SDLK_KP_7:         return Key::keypad_7;
    case SDLK_KP_8:         return Key::keypad_8;
    case SDLK_KP_9:         return Key::keypad_9;
    case SDLK_KP_A:         return Key::keypad_a;
    case SDLK_KP_B:         return Key::keypad_b;
    case SDLK_KP_C:         return Key::keypad_c;
    case SDLK_KP_D:         return Key::keypad_d;
    case SDLK_KP_E:         return Key::keypad_e;
    case SDLK_KP_F:         return Key::keypad_f;
    case SDLK_KP_BACKSPACE: return Key::keypad_backspace;
    case SDLK_KP_SPACE:     return Key::keypad_space;
    case SDLK_KP_TAB:       return Key::keypad_tab;
    case SDLK_KP_PERIOD:    return Key::keypad_period;
    case SDLK_KP_PLUS:      return Key::keypad_plus;
    case SDLK_KP_MINUS:     return Key::keypad_minus;
    case SDLK_KP_MULTIPLY:  return Key::keypad_asterisk;
    case SDLK_KP_DIVIDE:    return Key::keypad_slash;
    case SDLK_KP_PLUSMINUS: return Key::keypad_plusminus;
    case SDLK_KP_ENTER:     return Key::keypad_enter;
    case SDLK_KP_EQUALS:    return Key::keypad_equal;
    default:                return Key::none;
    }
}


}



namespace snail
{


std::string to_string(Key key)
{
#define ELONA_SNAIL_INPUT_KEY(k) \
    case Key::k: return #k

    switch (key)
    {
    ELONA_SNAIL_INPUT_KEY(none);
    ELONA_SNAIL_INPUT_KEY(key_0);
    ELONA_SNAIL_INPUT_KEY(key_1);
    ELONA_SNAIL_INPUT_KEY(key_2);
    ELONA_SNAIL_INPUT_KEY(key_3);
    ELONA_SNAIL_INPUT_KEY(key_4);
    ELONA_SNAIL_INPUT_KEY(key_5);
    ELONA_SNAIL_INPUT_KEY(key_6);
    ELONA_SNAIL_INPUT_KEY(key_7);
    ELONA_SNAIL_INPUT_KEY(key_8);
    ELONA_SNAIL_INPUT_KEY(key_9);
    ELONA_SNAIL_INPUT_KEY(key_a);
    ELONA_SNAIL_INPUT_KEY(key_b);
    ELONA_SNAIL_INPUT_KEY(key_c);
    ELONA_SNAIL_INPUT_KEY(key_d);
    ELONA_SNAIL_INPUT_KEY(key_e);
    ELONA_SNAIL_INPUT_KEY(key_f);
    ELONA_SNAIL_INPUT_KEY(key_g);
    ELONA_SNAIL_INPUT_KEY(key_h);
    ELONA_SNAIL_INPUT_KEY(key_i);
    ELONA_SNAIL_INPUT_KEY(key_j);
    ELONA_SNAIL_INPUT_KEY(key_k);
    ELONA_SNAIL_INPUT_KEY(key_l);
    ELONA_SNAIL_INPUT_KEY(key_m);
    ELONA_SNAIL_INPUT_KEY(key_n);
    ELONA_SNAIL_INPUT_KEY(key_o);
    ELONA_SNAIL_INPUT_KEY(key_p);
    ELONA_SNAIL_INPUT_KEY(key_q);
    ELONA_SNAIL_INPUT_KEY(key_r);
    ELONA_SNAIL_INPUT_KEY(key_s);
    ELONA_SNAIL_INPUT_KEY(key_t);
    ELONA_SNAIL_INPUT_KEY(key_u);
    ELONA_SNAIL_INPUT_KEY(key_v);
    ELONA_SNAIL_INPUT_KEY(key_w);
    ELONA_SNAIL_INPUT_KEY(key_x);
    ELONA_SNAIL_INPUT_KEY(key_y);
    ELONA_SNAIL_INPUT_KEY(key_z);
    ELONA_SNAIL_INPUT_KEY(f1);
    ELONA_SNAIL_INPUT_KEY(f2);
    ELONA_SNAIL_INPUT_KEY(f3);
    ELONA_SNAIL_INPUT_KEY(f4);
    ELONA_SNAIL_INPUT_KEY(f5);
    ELONA_SNAIL_INPUT_KEY(f6);
    ELONA_SNAIL_INPUT_KEY(f7);
    ELONA_SNAIL_INPUT_KEY(f8);
    ELONA_SNAIL_INPUT_KEY(f9);
    ELONA_SNAIL_INPUT_KEY(f10);
    ELONA_SNAIL_INPUT_KEY(f11);
    ELONA_SNAIL_INPUT_KEY(f12);
    ELONA_SNAIL_INPUT_KEY(f13);
    ELONA_SNAIL_INPUT_KEY(f14);
    ELONA_SNAIL_INPUT_KEY(f15);
    ELONA_SNAIL_INPUT_KEY(f16);
    ELONA_SNAIL_INPUT_KEY(f17);
    ELONA_SNAIL_INPUT_KEY(f18);
    ELONA_SNAIL_INPUT_KEY(f19);
    ELONA_SNAIL_INPUT_KEY(f20);
    ELONA_SNAIL_INPUT_KEY(f21);
    ELONA_SNAIL_INPUT_KEY(f22);
    ELONA_SNAIL_INPUT_KEY(f23);
    ELONA_SNAIL_INPUT_KEY(f24);
    ELONA_SNAIL_INPUT_KEY(up);
    ELONA_SNAIL_INPUT_KEY(down);
    ELONA_SNAIL_INPUT_KEY(left);
    ELONA_SNAIL_INPUT_KEY(right);
    ELONA_SNAIL_INPUT_KEY(insert);
    ELONA_SNAIL_INPUT_KEY(numlock);
    ELONA_SNAIL_INPUT_KEY(capslock);
    ELONA_SNAIL_INPUT_KEY(home);
    ELONA_SNAIL_INPUT_KEY(end);
    ELONA_SNAIL_INPUT_KEY(pageup);
    ELONA_SNAIL_INPUT_KEY(pagedown);
    ELONA_SNAIL_INPUT_KEY(application);
    ELONA_SNAIL_INPUT_KEY(printscreen);
    ELONA_SNAIL_INPUT_KEY(alt);
    ELONA_SNAIL_INPUT_KEY(ctrl);
    ELONA_SNAIL_INPUT_KEY(gui);
    ELONA_SNAIL_INPUT_KEY(shift);
    ELONA_SNAIL_INPUT_KEY(alt_l);
    ELONA_SNAIL_INPUT_KEY(ctrl_l);
    ELONA_SNAIL_INPUT_KEY(gui_l);
    ELONA_SNAIL_INPUT_KEY(shift_l);
    ELONA_SNAIL_INPUT_KEY(alt_r);
    ELONA_SNAIL_INPUT_KEY(ctrl_r);
    ELONA_SNAIL_INPUT_KEY(gui_r);
    ELONA_SNAIL_INPUT_KEY(shift_r);
    ELONA_SNAIL_INPUT_KEY(space);
    ELONA_SNAIL_INPUT_KEY(tab);
    ELONA_SNAIL_INPUT_KEY(enter);
    ELONA_SNAIL_INPUT_KEY(escape);
    ELONA_SNAIL_INPUT_KEY(backspace);
    ELONA_SNAIL_INPUT_KEY(delete_);
    ELONA_SNAIL_INPUT_KEY(equal);
    ELONA_SNAIL_INPUT_KEY(backquote);
    ELONA_SNAIL_INPUT_KEY(quote);
    ELONA_SNAIL_INPUT_KEY(backslash);
    ELONA_SNAIL_INPUT_KEY(comma);
    ELONA_SNAIL_INPUT_KEY(minus);
    ELONA_SNAIL_INPUT_KEY(period);
    ELONA_SNAIL_INPUT_KEY(rightbracket);
    ELONA_SNAIL_INPUT_KEY(leftbracket);
    ELONA_SNAIL_INPUT_KEY(semicolon);
    ELONA_SNAIL_INPUT_KEY(slash);
    ELONA_SNAIL_INPUT_KEY(ampersand);
    ELONA_SNAIL_INPUT_KEY(asterisk);
    ELONA_SNAIL_INPUT_KEY(at);
    ELONA_SNAIL_INPUT_KEY(caret);
    ELONA_SNAIL_INPUT_KEY(colon);
    ELONA_SNAIL_INPUT_KEY(dollar);
    ELONA_SNAIL_INPUT_KEY(exclaim);
    ELONA_SNAIL_INPUT_KEY(greater);
    ELONA_SNAIL_INPUT_KEY(hash);
    ELONA_SNAIL_INPUT_KEY(leftparen);
    ELONA_SNAIL_INPUT_KEY(less);
    ELONA_SNAIL_INPUT_KEY(percent);
    ELONA_SNAIL_INPUT_KEY(plus);
    ELONA_SNAIL_INPUT_KEY(question);
    ELONA_SNAIL_INPUT_KEY(quotedbl);
    ELONA_SNAIL_INPUT_KEY(rightparen);
    ELONA_SNAIL_INPUT_KEY(underscore);
    ELONA_SNAIL_INPUT_KEY(keypad_0);
    ELONA_SNAIL_INPUT_KEY(keypad_1);
    ELONA_SNAIL_INPUT_KEY(keypad_2);
    ELONA_SNAIL_INPUT_KEY(keypad_3);
    ELONA_SNAIL_INPUT_KEY(keypad_4);
    ELONA_SNAIL_INPUT_KEY(keypad_5);
    ELONA_SNAIL_INPUT_KEY(keypad_6);
    ELONA_SNAIL_INPUT_KEY(keypad_7);
    ELONA_SNAIL_INPUT_KEY(keypad_8);
    ELONA_SNAIL_INPUT_KEY(keypad_9);
    ELONA_SNAIL_INPUT_KEY(keypad_a);
    ELONA_SNAIL_INPUT_KEY(keypad_b);
    ELONA_SNAIL_INPUT_KEY(keypad_c);
    ELONA_SNAIL_INPUT_KEY(keypad_d);
    ELONA_SNAIL_INPUT_KEY(keypad_e);
    ELONA_SNAIL_INPUT_KEY(keypad_f);
    ELONA_SNAIL_INPUT_KEY(keypad_backspace);
    ELONA_SNAIL_INPUT_KEY(keypad_space);
    ELONA_SNAIL_INPUT_KEY(keypad_tab);
    ELONA_SNAIL_INPUT_KEY(keypad_period);
    ELONA_SNAIL_INPUT_KEY(keypad_plus);
    ELONA_SNAIL_INPUT_KEY(keypad_minus);
    ELONA_SNAIL_INPUT_KEY(keypad_asterisk);
    ELONA_SNAIL_INPUT_KEY(keypad_slash);
    ELONA_SNAIL_INPUT_KEY(keypad_plusminus);
    ELONA_SNAIL_INPUT_KEY(keypad_enter);
    ELONA_SNAIL_INPUT_KEY(keypad_equal);
    ELONA_SNAIL_INPUT_KEY(_size);
    default: assert(0);
    }

#undef ELONA_SNAIL_INPUT_KEY
}


char to_char(Key key)
{
    switch (key)
    {
    case Key::key_0:           return '0';
    case Key::key_1:           return '1';
    case Key::key_2:           return '2';
    case Key::key_3:           return '3';
    case Key::key_4:           return '4';
    case Key::key_5:           return '5';
    case Key::key_6:           return '6';
    case Key::key_7:           return '7';
    case Key::key_8:           return '8';
    case Key::key_9:           return '9';
    case Key::key_a:           return 'a';
    case Key::key_b:           return 'b';
    case Key::key_c:           return 'c';
    case Key::key_d:           return 'd';
    case Key::key_e:           return 'e';
    case Key::key_f:           return 'f';
    case Key::key_g:           return 'g';
    case Key::key_h:           return 'h';
    case Key::key_i:           return 'i';
    case Key::key_j:           return 'j';
    case Key::key_k:           return 'k';
    case Key::key_l:           return 'l';
    case Key::key_m:           return 'm';
    case Key::key_n:           return 'n';
    case Key::key_o:           return 'o';
    case Key::key_p:           return 'p';
    case Key::key_q:           return 'q';
    case Key::key_r:           return 'r';
    case Key::key_s:           return 's';
    case Key::key_t:           return 't';
    case Key::key_u:           return 'u';
    case Key::key_v:           return 'v';
    case Key::key_w:           return 'w';
    case Key::key_x:           return 'x';
    case Key::key_y:           return 'y';
    case Key::key_z:           return 'z';
    case Key::space:           return ' ';
    case Key::tab:             return '\t';
    case Key::enter:           return '\n';
    case Key::equal:           return '=';
    case Key::backquote:       return '`';
    case Key::quote:           return '\'';
    case Key::backslash:       return '\\';
    case Key::comma:           return ',';
    case Key::minus:           return '-';
    case Key::period:          return '.';
    case Key::rightbracket:    return ']';
    case Key::leftbracket:     return '[';
    case Key::semicolon:       return ';';
    case Key::slash:           return '/';
    case Key::ampersand:       return '&';
    case Key::asterisk:        return '*';
    case Key::at:              return '@';
    case Key::caret:           return '^';
    case Key::colon:           return ':';
    case Key::dollar:          return '$';
    case Key::exclaim:         return '!';
    case Key::greater:         return '>';
    case Key::hash:            return '#';
    case Key::leftparen:       return '(';
    case Key::less:            return '<';
    case Key::percent:         return '%';
    case Key::plus:            return '+';
    case Key::question:        return '?';
    case Key::quotedbl:        return '"';
    case Key::rightparen:      return ')';
    case Key::underscore:      return '_';
    case Key::keypad_0:        return '0';
    case Key::keypad_1:        return '1';
    case Key::keypad_2:        return '2';
    case Key::keypad_3:        return '3';
    case Key::keypad_4:        return '4';
    case Key::keypad_5:        return '5';
    case Key::keypad_6:        return '6';
    case Key::keypad_7:        return '7';
    case Key::keypad_8:        return '8';
    case Key::keypad_9:        return '9';
    case Key::keypad_a:        return 'a';
    case Key::keypad_b:        return 'b';
    case Key::keypad_c:        return 'c';
    case Key::keypad_d:        return 'd';
    case Key::keypad_e:        return 'e';
    case Key::keypad_f:        return 'f';
    case Key::keypad_space:    return ' ';
    case Key::keypad_tab:      return '\t';
    case Key::keypad_period:   return '.';
    case Key::keypad_plus:     return '+';
    case Key::keypad_minus:    return '-';
    case Key::keypad_asterisk: return '*';
    case Key::keypad_slash:    return '/';
    case Key::keypad_enter:    return '\n';
    case Key::keypad_equal:    return '=';
    default: return '\0';
    }
}


}

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
//             if (event.type != sdl.SDL_MOUSEBUTTONUP && event.type != sdl.SDL_MOUSEBUTTONDOWN)
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
//         Button[ButtonType.max + 1] _mouseButtons;
//     }
// }



Keyboard& Keyboard::instance() noexcept
{
    static Keyboard keyboard;
    return keyboard;
}



/*
_initial_key_wait = 10, _key_wait = 3
a a a a a a a a a a a a a a a a a a a a
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9
*                   *     *     *     *
*/
bool Keyboard::is_pressed(Key key) const
{
    if (!_keys[static_cast<size_t>(key)].is_pressed())
        return false;
    
    auto repeat = _keys[static_cast<size_t>(key)].repeat();
    if (repeat == 0)
    {
        return true;
    }
    else if (repeat == _initial_key_wait)
    {
        return true;
    }
    else if (repeat > _initial_key_wait && (repeat - _initial_key_wait) % _key_wait == 0)
    {
        return true;
    }
    return false;
}



bool Keyboard::is_pressed_exactly(Key key) const
{
    return _keys[static_cast<size_t>(key)].is_pressed();
}



bool Keyboard::was_pressed_just_now(Key key) const
{
    return is_pressed_exactly(key) && _keys[static_cast<size_t>(key)].repeat() == 0;
}



void Keyboard::set_key_repeat(int initial_key_wait, int key_wait) noexcept
{
    _initial_key_wait = std::max(initial_key_wait, 1);
    _key_wait = std::max(key_wait, 1);
}




Key Keyboard::get_pressed_key() const noexcept
{
    for (Key k = Key::none; k < Key::_size; k = static_cast<Key>(static_cast<int>(k) + 1))
    {
        if (is_pressed(k))
        {
            return k;
        }
    }
    return Key::none;
}



void Keyboard::_update()
{
    for (auto&& key : _keys)
    {
        if (key.is_pressed())
        {
            key._increase_repeat();
        }
    }
}



void Keyboard::_handle_event(const ::SDL_KeyboardEvent& event)
{
    auto key = sdlkey2key(event.keysym.sym);
    if (key == Key::none)
        return;

    if (event.state == SDL_PRESSED)
    {
        _keys[static_cast<size_t>(key)]._press();
    }
    else
    {
        _keys[static_cast<size_t>(key)]._release();
    }

    using Tuples = std::tuple<Key, Key, Key>[];
    for (const auto& tuple : Tuples{
        {Key::alt,   Key::alt_l,   Key::alt_r},
        {Key::ctrl,  Key::ctrl_l,  Key::ctrl_r},
        {Key::gui,   Key::gui_l,   Key::gui_r},
        {Key::shift, Key::shift_l, Key::shift_r},
    })
    {
        if (_keys[static_cast<size_t>(std::get<1>(tuple))].is_pressed() || _keys[static_cast<int>(std::get<2>(tuple))].is_pressed())
        {
            _keys[static_cast<size_t>(std::get<0>(tuple))]._press();
        }
        else
        {
            _keys[static_cast<size_t>(std::get<0>(tuple))]._release();
        }
    }
}

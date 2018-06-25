#include "input.hpp"
#include "audio.hpp"
#include "blending.hpp"
#include "config.hpp"
#include "elona.hpp"
#include "enums.hpp"
#include "ui.hpp"
#include "variables.hpp"



namespace elona
{


int TODO_show_prompt_val;


int show_prompt(int x, int y, int width, show_prompt_type type, int val4)
{
    int val5{};
    snd(26);

    int csprev = cs;
    cs = 0;
    cs_bk = -1;

    gsel(3);
    gmode(0);
    font(15 - en * 2);
    for (int i = 0; i < promptmax; ++i)
    {
        if (promptl(1, i) == u8"null"s)
        {
            promptl(1, i) = key_select(i);
        }
        pos(i * 24 + 624, 30);
        gcopy(3, 0, 30, 24, 18);
        pos(i * 24 + 629, 31);
        color(50, 60, 80);
        bmes(promptl(1, i), 250, 240, 230);
        color(0, 0, 0);
    }

    gsel(0);
    sx = x - width / 2;
    sy = y - promptmax * 10;
    boxf(sx + 12, sy + 12, width - 17, promptmax * 20 + 25, {60, 60, 60, 128});
    keyhalt = 1;

    if (type == show_prompt_type::with_number)
    {
        dx(0) = 200;
        dx(1) = 10;
        dy = sy + 140;
        val5 = val4;
        val4 = 1;
        TODO_show_prompt_val = 1;
        if (strlen_u(std::to_string(val5)) >= 3)
        {
            dx += std::to_string(val5).size() * 8;
        }
        boxf(dx(1) + sx + 24, dy + 4, dx - 42, 35, {0, 0, 0, 127});
    }

    while (1)
    {
        gmode(2);
        if (type == show_prompt_type::with_number)
        {
            window2(dx(1) + sx + 20, dy, dx - 40, 36, 0, 2);
            pos(dx(1) + sx + dx / 2 - 56, dy - 32);
            gcopy(3, 128, 288, 128, 32);
            pos(dx(1) + sx + 28, dy + 4);
            gcopy(3, 312, 336, 24, 24);
            pos(dx(1) + sx + dx - 51, dy + 4);
            gcopy(3, 336, 336, 24, 24);
            const auto inputlog2 =
                ""s + elona::stoi(inputlog(0)) + u8"("s + val5 + u8")"s;
            pos(dx(1) + sx + dx - 70 - strlen_u(inputlog2) * 8 + 8, dy + 11);
            color(255, 255, 255);
            mes(inputlog2);
            color(0, 0, 0);
            inputlog = ""s + val4;
        }
        window2(sx + 8, sy + 8, width - 16, promptmax * 20 + 42 - 16, 0, 0);
        pos(sx - 16, sy);
        gcopy(3, 64, 288, 50, 32);
        font(14 - en * 2);
        keyrange = 0;
        cs_listbk();
        for (int cnt = 0, cnt_end = (promptmax); cnt < cnt_end; ++cnt)
        {
            pos(sx + 30, cnt * 20 + sy + 22);
            gcopy(3, cnt * 24 + 624, 30, 24, 24);
            cs_list(cs == cnt, promptl(0, cnt), sx + 56, cnt * 20 + sy + 21);
            key_list(cnt) = promptl(1, cnt);
            ++keyrange;
        }
        cs_bk = cs;
        if (type == show_prompt_type::with_number)
        {
            window_recipe2(TODO_show_prompt_val);
            font(14 - en * 2);
        }
        redraw();
        await(config::instance().wait1);
        key_check();
        cursor_check();
        int ret = -1;
        for (int cnt = 0, cnt_end = (promptmax); cnt < cnt_end; ++cnt)
        {
            if (key == promptl(1, cnt))
            {
                ret = elona::stoi(promptl(2, cnt));
                break;
            }
        }
        if (type == show_prompt_type::with_number)
        {
            TODO_show_prompt_val = elona::stoi(inputlog(0));
            if (key == key_west || key == key_pagedown)
            {
                snd(5);
                --val4;
                if (val4 < 1)
                {
                    val4 = val5;
                }
            }
            if (key == key_east || key == key_pageup)
            {
                snd(5);
                ++val4;
                if (val4 > val5)
                {
                    val4 = 1;
                }
            }
        }
        if (ret != -1)
        {
            promptmax = 0;
            cs = csprev;
            return ret;
        }
        if (type != show_prompt_type::cannot_cancel)
        {
            if (key == key_cancel)
            {
                promptmax = 0;
                cs = csprev;
                return -1;
            }
        }
    }
}



void input_number_dialog(int x, int y, int max_number)
{
    snd(26);
    dx = 8 * 16 + 60;
    font(16 - en * 2);

    int number = max_number;
    if (strlen_u(std::to_string(max_number)) >= 3)
    {
        dx += strlen_u(std::to_string(max_number)) * 8;
    }
    boxf(x + 24, y + 4, dx - 42, 35, {0, 0, 0, 127});
    while (1)
    {
        window2(x + 20, y, dx - 40, 36, 0, 2);
        pos(x + dx / 2 - 56, y - 32);
        gcopy(3, 128, 288, 128, 32);
        pos(x + 28, y + 4);
        gcopy(3, 312, 336, 24, 24);
        pos(x + dx - 51, y + 4);
        gcopy(3, 336, 336, 24, 24);
        const auto inputlog2 = inputlog + u8"(" + max_number + u8")";
        pos(x + dx - 70 - strlen_u(inputlog2) * 8 + 8, y + 11);
        color(255, 255, 255);
        mes(inputlog2);
        color(0, 0, 0);
        redraw();
        await(config::instance().wait1);
        key_check();
        if (key == key_enter)
        {
            f = 1;
            break;
        }
        if (key == key_cancel)
        {
            f = -1;
            break;
        }
        if (key == key_west)
        {
            snd(5);
            --number;
            if (number < 1)
            {
                number = max_number;
            }
        }
        if (key == key_east)
        {
            snd(5);
            ++number;
            if (number > max_number)
            {
                number = 1;
            }
        }
        if (key == key_south)
        {
            snd(5);
            number = 1;
        }
        if (key == key_north)
        {
            snd(5);
            number = max_number;
        }
        if (key == key_northwest)
        {
            snd(5);
            number -= 100;
            if (number < 1)
            {
                number = 1;
            }
        }
        if (key == key_northeast)
        {
            snd(5);
            number += 100;
            if (number > max_number)
            {
                number = max_number;
            }
        }
        if (key == key_southwest)
        {
            snd(5);
            number -= 10;
            if (number < 1)
            {
                number = 1;
            }
        }
        if (key == key_southeast)
        {
            snd(5);
            number += 10;
            if (number > max_number)
            {
                number = max_number;
            }
        }
        inputlog = ""s + number;
    }
    if (f == -1)
    {
        inputlog = "";
        rtval = -1;
    }
    keywait = 1;
    key = "";
    rtval = 0;
}



bool input_text_dialog(
    int x,
    int y,
    int val2,
    bool is_cancelable,
    bool limit_length)
{
    bool canceled = false;

    snd(26);
    dx = val2 * 16 + 60;
    font(16 - en * 2);

    pos(x, y);
    inputlog = "";
    mesbox(inputlog, true);
    boxf(x + 4, y + 4, dx - 1, 35, {0, 0, 0, 127});

    notesel(inputlog);
    p(1) = 2;

    for (int cnt = 0;; ++cnt)
    {
        if (ginfo(2) != 0)
        {
            objprm(1, ""s);
            inputlog = "";
            await(100);
            --cnt;
            continue;
        }
        await(config::instance().wait1);
        window2(x, y, dx, 36, 0, 2);
        pos(x + dx / 2 - 60, y - 32);
        gcopy(3, 128, 288, 128, 32);

        pos(x + 8, y + 4);
        if (imeget() != 0)
        {
            gcopy(3, 48, 336, 24, 24);
        }
        else
        {
            gcopy(3, 24, 336, 24, 24);
        }
        apledit(p(2), 2, 0);
        if (p(2) > val2 * (1 + en) - 2)
        {
            pos(x + 8, y + 4);
            gcopy(3, 72, 336, 24, 24);
        }
        if (cnt % 20 < 10)
        {
            p(1) = p(1) * 2;
        }
        else
        {
            p(1) = p(1) / 2;
        }
        apledit(p(2), 0);
        p(4) = 0;
        for (int cnt = 0, cnt_end = (p(2)); cnt < cnt_end; ++cnt)
        {
            p(3) = inputlog(0)[p(4)];
            if ((p(3) >= 129 && p(3) <= 159) || (p(3) >= 224 && p(3) <= 252))
            {
                p(4) += 2;
            }
            else
            {
                p(4) += 1;
            }
            p(4) = std::min(p(4), 20);
        }
        noteget(s, 0);

        if (limit_length && p(4) == 20)
        {
            if (inputlog(0).back() != '\n')
            {
                cutname(inputlog, 20);
            }
            cutname(s, 20);
        }
        else if (!limit_length && p(4) > 18)
        {
            p(4) = 18;
            cutname(s, 18);
            s += u8"…";
            p(4) += 2;
        }

        if (strutil::contains(inputlog(0), u8"\n"))
        {
            rtval = 0;
            break;
        }
        if (strutil::contains(inputlog(0), u8"\t"))
        {
            objprm(1, ""s);
            inputlog = "";
            if (is_cancelable)
            {
                canceled = true;
            }
        }
        if (is_cancelable)
        {
            if (canceled)
            {
                inputlog = "";
                keywait = 1;
                key = "";
                break;
            }
        }

        gmode(4, -1, -1, p(1) / 2 + 50);
        pos(x + 34 + p(4) * 8, y + 5);
        gcopy(3, 0, 336, 12, 24);
        gmode(2);
        color(255, 255, 255);
        pos(x + 36, y + 9);
        mes(s);
        color(0, 0, 0);

        redraw();
    }
    gmode(2);
    if (en)
    {
        inputlog = strutil::replace(inputlog, u8"\"", u8"'");
    }
    rm_crlf(inputlog);
    onkey_0();

    return canceled;
}


bool is_keypress_delayed(int held_frames, int keywait, int initial_keywait)
{
    if (held_frames < initial_keywait)
    {
        if (held_frames == 0)
        {
            return false;
        }
    }
    else if (held_frames % keywait == 0)
    {
        return false;
    }

    return true;
}

void key_check(key_wait_delay_t delay_type)
{
    static int prevjoy_at_m19{};
    bool delay_keypress = false;
    bool delay_enter = false;
    static int enter_held_frames{};
    static int shortcut_held_frames{};

    if (msgalert == 1)
    {
        if (config::instance().alert > 1)
        {
            for (int i = 0; i < config::instance().alert; ++i)
            {
                await(config::instance().wait1);
            }
            keylog = "";
        }
        msgalert = 0;
    }

    key = "";
    if (keylog != ""s)
    {
        keylog = strmid(keylog, 0, 1);
        if (keylog(0)[0] == '\n')
        {
            keylog = key_enter;
        }
        key = keylog;
        keylog = "";
    }

    // Holding down a numpad key sometimes sets "key" to a
    // non-numpad number key, and these get passed to the player
    // as a mispress, so counteract that here.
    if (key.size() == 1 && isdigit(static_cast<unsigned char>(key(0)[0])))
    {
        key = "";
    }

    if (getkey(snail::key::keypad_0))
        key = "0 ";
    else if (getkey(snail::key::keypad_1))
        key = "1 ";
    else if (getkey(snail::key::keypad_2))
        key = "2 ";
    else if (getkey(snail::key::keypad_3))
        key = "3 ";
    else if (getkey(snail::key::keypad_4))
        key = "4 ";
    else if (getkey(snail::key::keypad_5))
        key = "5 ";
    else if (getkey(snail::key::keypad_6))
        key = "6 ";
    else if (getkey(snail::key::keypad_7))
        key = "7 ";
    else if (getkey(snail::key::keypad_8))
        key = "8 ";
    else if (getkey(snail::key::keypad_9))
        key = "9 ";

    mousel = 0;
    key_tab = 0;
    key_escape = 0;
    int p_at_m19 = stick(
        stick_key::left | stick_key::up | stick_key::right | stick_key::down);
    if (p_at_m19 != 0)
    {
        if (p_at_m19 == stick_key::escape)
        {
            if (keywait == 0)
            {
                key = key_cancel;
                key_escape = 1;
            }
        }
        if (p_at_m19 == stick_key::tab)
        {
            key_tab = 1;
            key = key_next;
        }
    }
    else
    {
        if (getkey(snail::key::home))
        {
            p_at_m19 = stick_key::up | stick_key::left;
        }
        else if (getkey(snail::key::pageup))
        {
            p_at_m19 = stick_key::up | stick_key::right;
        }
        else if (getkey(snail::key::end))
        {
            p_at_m19 = stick_key::down | stick_key::left;
        }
        else if (getkey(snail::key::pagedown))
        {
            p_at_m19 = stick_key::down | stick_key::right;
        }

        // Handle the case of the current key matching the movement
        // keybindings set in the user's config.
        else if (key == key_west)
        {
            p_at_m19 = stick_key::left;
        }
        else if (key == key_north)
        {
            p_at_m19 = stick_key::up;
        }
        else if (key == key_east)
        {
            p_at_m19 = stick_key::right;
        }
        else if (key == key_south)
        {
            p_at_m19 = stick_key::down;
        }
        else if (key == key_northwest)
        {
            p_at_m19 = stick_key::up | stick_key::left;
        }
        else if (key == key_northeast)
        {
            p_at_m19 = stick_key::up | stick_key::right;
        }
        else if (key == key_southwest)
        {
            p_at_m19 = stick_key::down | stick_key::left;
        }
        else if (key == key_southeast)
        {
            p_at_m19 = stick_key::down | stick_key::right;
        }
        else if (key == key_wait)
        {
            p_at_m19 = 0;
            delay_keypress = true;
        }
    }
    if (getkey(snail::key::ctrl))
    {
        key_ctrl = 1;
    }
    else
    {
        key_ctrl = 0;
    }
    if (getkey(snail::key::alt))
    {
        key_alt = 1;
    }
    else
    {
        key_alt = 0;
    }
    if (getkey(snail::key::shift))
    {
        keybd_wait = 100000;
        key_shift = 1;
        if (keywait == 0)
        {
            key = key_cancel;
            keywait = 1;
        }
    }
    else
    {
        keywait = 0;
        key_shift = 0;
    }

    if (snail::input::instance().is_pressed(snail::key::enter)
        || snail::input::instance().is_pressed(snail::key::keypad_enter))
    {
        key = key_enter;
        delay_enter = true;
    }
    else
    {
        enter_held_frames = 0;
    }

    if (config::instance().joypad)
    {
        int j_at_m19 = 0;
        DIGETJOYSTATE(j_at_m19, 0);
        if (HMMBITCHECK(j_at_m19, 0))
        {
            p_at_m19 += 2;
        }
        if (HMMBITCHECK(j_at_m19, 1))
        {
            p_at_m19 += 8;
        }
        if (HMMBITCHECK(j_at_m19, 2))
        {
            p_at_m19 += 1;
        }
        if (HMMBITCHECK(j_at_m19, 3))
        {
            p_at_m19 += 4;
        }
        int a_at_m19 = 0;
        for (int cnt = 0; cnt < 12; ++cnt)
        {
            if (HMMBITCHECK(j_at_m19, 4 + cnt))
            {
                a_at_m19 = 1;
                if (jkey(cnt) == key_alter)
                {
                    key_alt = 1;
                }
                if (jkey(cnt) == key_cancel)
                {
                    key_shift = 1;
                    if (p_at_m19 != 0)
                    {
                        keybd_wait = 100000;
                    }
                }
                if (prevjoy_at_m19 != cnt)
                {
                    key = jkey(cnt);
                    prevjoy_at_m19 = cnt;
                    if (key == key_esc)
                    {
                        key = key_cancel;
                        key_escape = 1;
                    }
                    if (delay_type == key_wait_delay_t::always)
                    {
                        int b_at_m19 = 0;
                        if (key == key_fire)
                        {
                            key = key_northeast;
                            b_at_m19 = 1;
                        }
                        if (key == key_target)
                        {
                            key = key_northwest;
                            b_at_m19 = 1;
                        }
                        if (key == key_get)
                        {
                            key = key_northeast;
                            b_at_m19 = 1;
                        }
                        if (key == key_alter)
                        {
                            key = key_northwest;
                            b_at_m19 = 1;
                        }
                        if (b_at_m19 == 0 && key != key_enter
                            && key != key_cancel && key != key_esc)
                        {
                            key = key_identify;
                        }
                    }
                }
            }
        }
        if (a_at_m19 == 0)
        {
            prevjoy_at_m19 = -1;
        }
        else if (delay_type == key_wait_delay_t::none)
        {
            return;
        }
    }
    if (quickkeywait)
    {
        if (p_at_m19 != 0)
        {
            return;
        }
        else
        {
            quickkeywait = 0;
        }
    }
    if (keybd_wait >= 100000)
    {
        if (key_shift == 0)
        {
            keybd_wait = 1000;
        }
    }
    if (p_at_m19 == stick_key::left)
    {
        if (key_alt == 0)
        {
            key = key_west;
            delay_keypress = true;
        }
    }
    if (p_at_m19 == stick_key::up)
    {
        if (key_alt == 0)
        {
            key = key_north;
            delay_keypress = true;
        }
    }
    if (p_at_m19 == stick_key::right)
    {
        if (key_alt == 0)
        {
            key = key_east;
            delay_keypress = true;
        }
    }
    if (p_at_m19 == stick_key::down)
    {
        if (key_alt == 0)
        {
            key = key_south;
            delay_keypress = true;
        }
    }
    if (p_at_m19 == (stick_key::up | stick_key::left))
    {
        key = key_northwest;
        delay_keypress = true;
    }
    if (p_at_m19 == (stick_key::up | stick_key::right))
    {
        key = key_northeast;
        delay_keypress = true;
    }
    if (p_at_m19 == (stick_key::down | stick_key::left))
    {
        key = key_southwest;
        delay_keypress = true;
    }
    if (p_at_m19 == (stick_key::down | stick_key::right))
    {
        key = key_southeast;
        delay_keypress = true;
    }
    if (getkey(snail::key::clear))
    {
        key = key_wait;
        delay_keypress = true;
    }

    if (getkey(snail::key::f1))
    {
        key = u8"F1";
    }
    else if (getkey(snail::key::f2))
    {
        key = u8"F2";
    }
    else if (getkey(snail::key::f3))
    {
        key = u8"F3";
    }
    else if (getkey(snail::key::f4))
    {
        key = u8"F4";
    }
    else if (getkey(snail::key::f5))
    {
        key = u8"F5";
    }
    else if (getkey(snail::key::f6))
    {
        key = u8"F6";
    }
    else if (getkey(snail::key::f7))
    {
        key = u8"F7";
    }
    else if (getkey(snail::key::f8))
    {
        key = u8"F8";
    }
    else if (getkey(snail::key::f9))
    {
        key = u8"F9";
    }
    else if (getkey(snail::key::f10))
    {
        key = u8"F10";
    }
    else if (getkey(snail::key::f11))
    {
        key = u8"F11";
    }
    else if (getkey(snail::key::f12))
    {
        key = u8"F12";
    }

    if (delay_type == key_wait_delay_t::none)
    {
        return;
    }
    if (delay_keypress)
    {
        if (delay_type == key_wait_delay_t::walk_run)
        {
            if (keybd_attacking != 0)
            {
                if (keybd_wait % config::instance().attackwait != 0)
                {
                    key = ""s;
                }
            }
            else if (config::instance().scroll == 0)
            {
                if (keybd_wait
                    < config::instance().walkwait * config::instance().startrun)
                {
                    if (keybd_wait % config::instance().walkwait != 0)
                    {
                        key = "";
                    }
                }
                else
                {
                    running = 1;
                    if (keybd_wait < 100000)
                    {
                        if (keybd_wait % config::instance().runwait != 0)
                        {
                            key = ""s;
                        }
                    }
                }
            }
            else if (p_at_m19 == 0)
            {
                if (keybd_wait < 20)
                {
                    if (keybd_wait != 0)
                    {
                        key = ""s;
                    }
                }
            }
            else if (keybd_wait > config::instance().startrun)
            {
                if (config::instance().runscroll == 0)
                {
                    if (keybd_wait % config::instance().runwait != 0)
                    {
                        key = "";
                    }
                }
                running = 1;
            }
        }
        // Press the key every 7 frames twice.
        else if (keybd_wait < 14)
        {
            if (keybd_wait != 0 && keybd_wait != 7)
            {
                key = "";
            }
        }
        // Press the key every other frame.
        else if (keybd_wait < 1000)
        {
            if (keybd_wait % 2 != 1)
            {
                key = ""s;
            }
        }
        ++keybd_wait;
    }
    else
    {
        keybd_wait = 0;
        keybd_attacking = 0;
        running = 0;
    }

    if (delay_enter)
    {
        if (is_keypress_delayed(enter_held_frames, 1, 20))
        {
            key = "";
        }
        enter_held_frames++;
    }

    bool shortcut{};
    int shortcut_delay = config::instance().keywait;
    if (delay_type == key_wait_delay_t::walk_run)
    {
        shortcut_delay = 1;
    }

    for (int i = 0; i < 10; ++i)
    {
        const auto pressed = snail::input::instance().is_pressed(
            snail::key(int(snail::key::key_0) + i));
        if (pressed)
        {
            key = u8"sc";
            sc = i;
            if (key_shift || key_ctrl)
            {
                sc += 10;
            }
            keylog = "";
            shortcut = true;
        }
    }

    if (shortcut)
    {
        if (is_keypress_delayed(shortcut_held_frames, shortcut_delay, 20))
        {
            key = "";
        }
        ++shortcut_held_frames;
    }
    else
    {
        shortcut_held_frames = 0;
    }

    if (!shortcut && keyhalt != 0)
    {
        if (key != ""s || keybd_wait != 0)
        {
            key = "";
        }
        else
        {
            keyhalt = 0;
        }
    }
}



void wait_key_released()
{
    while (1)
    {
        await(config::instance().wait1);
        int result{};
        result = stick(stick_key::mouse_left | stick_key::mouse_right);
        if (result == 0)
        {
            key_check();
            if (key(0).empty())
            {
                break;
            }
        }
    }
}



void wait_key_pressed(bool only_enter_or_cancel)
{
    if (config::instance().is_test)
        return;

    while (1)
    {
        await(config::instance().wait1);
        key_check();
        if (only_enter_or_cancel)
        {
            if (key == key_enter || key == key_cancel)
            {
                break;
            }
        }
        else
        {
            if (!key(0).empty())
            {
                break;
            }
        }
    }
    keyhalt = 1;
}



} // namespace elona

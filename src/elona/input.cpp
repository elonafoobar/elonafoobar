#include "input.hpp"
#include "../snail/android.hpp"
#include "audio.hpp"
#include "blending.hpp"
#include "config/config.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "enums.hpp"
#include "i18n.hpp"
#include "input_prompt.hpp"
#include "keybind/input_context.hpp"
#include "keybind/keybind.hpp"
#include "ui.hpp"
#include "variables.hpp"



namespace elona
{


int TODO_show_prompt_val;


void input_number_dialog(int x, int y, int max_number, int initial_number)
{
    snd("core.pop2");
    dx = 8 * 16 + 60;
    font(16 - en * 2);

    if (max_number < 1)
    {
        max_number = 1;
    }
    int number;
    if (initial_number != 0)
    {
        number = clamp(initial_number, 1, max_number);
    }
    else
    {
        number = max_number;
    }
    if (strlen_u(std::to_string(max_number)) >= 3)
    {
        dx += strlen_u(std::to_string(max_number)) * 8;
    }
    boxf(x + 24, y + 4, dx - 42, 35, {0, 0, 0, 127});
    inputlog = std::to_string(number);
    while (true)
    {
        window2(x + 20, y, dx - 40, 36, 0, 2);
        draw("label_input", x + dx / 2 - 56, y - 32);
        pos(x + 28, y + 4);
        gcopy(3, 312, 336, 24, 24);
        pos(x + dx - 51, y + 4);
        gcopy(3, 336, 336, 24, 24);
        const std::string inputlog2 = inputlog + u8"(" + max_number + u8")";
        pos(x + dx - 70 - strlen_u(inputlog2) * 8 + 8, y + vfix + 11);
        color(255, 255, 255);
        mes(inputlog2);
        color(0, 0, 0);
        redraw();
        auto action = key_check();
        if (action == "enter")
        {
            f = 1;
            break;
        }
        if (action == "cancel")
        {
            f = -1;
            break;
        }
        if (action == "west")
        {
            snd("core.cursor1");
            --number;
            if (number < 1)
            {
                number = max_number;
            }
        }
        if (action == "east")
        {
            snd("core.cursor1");
            ++number;
            if (number > max_number)
            {
                number = 1;
            }
        }
        if (action == "south")
        {
            snd("core.cursor1");
            number = 1;
        }
        if (action == "north")
        {
            snd("core.cursor1");
            number = max_number;
        }
        if (action == "northwest")
        {
            snd("core.cursor1");
            number -= 100;
            while (number < 1)
            {
                number += max_number;
            }
        }
        if (action == "northeast")
        {
            snd("core.cursor1");
            number += 100;
            while (number > max_number)
            {
                number -= max_number;
            }
        }
        if (action == "southwest")
        {
            snd("core.cursor1");
            number -= 10;
            while (number < 1)
            {
                number += max_number;
            }
        }
        if (action == "southeast")
        {
            snd("core.cursor1");
            number += 10;
            while (number > max_number)
            {
                number -= max_number;
            }
        }
        inputlog = std::to_string(number);
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

    snd("core.pop2");
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
        await(Config::instance().wait1);
        window2(x, y, dx, 36, 0, 2);
        draw("label_input", x + dx / 2 - 60, y - 32);

        draw("ime_status_english", x + 8, y + 4);
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
            if (jp)
            {
                s += u8"…";
            }
            else
            {
                s += u8"...";
            }
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

        gmode(4, p(1) / 2 + 50);
        draw("input_caret", x + 34 + p(4) * 8, y + 5);
        gmode(2);
        color(255, 255, 255);
        pos(x + 36, y + vfix + 9);
        mes(s);
        color(0, 0, 0);

        redraw();
    }
    gmode(2);
    if (en)
    {
        inputlog = strutil::replace(inputlog, u8"\"", u8"'");
    }
    inputlog = strutil::remove_line_ending(inputlog);
    onkey_0();

    keyhalt = 1;

    return canceled;
}

static void _proc_android_vibrate()
{
    if (Config::instance().get<bool>("core.config.android.vibrate"))
    {
        int duration =
            Config::instance().get<int>("core.config.android.vibrate_duration");
        snail::android::vibrate(static_cast<long>(duration * 25));
    }
}

static void _handle_msgalert()
{
    if (Config::instance().alert > 1)
    {
        _proc_android_vibrate();

        for (int i = 0; i < Config::instance().alert; ++i)
        {
            await(Config::instance().wait1);
        }
        keylog = "";
    }
}

static void _update_pressed_key_name()
{
    key = "";
    if (keylog != ""s)
    {
        keylog = strmid(keylog, 0, 1);
        if (keylog(0)[0] == '\n')
        {
            keylog = "Enter";
        }
        key = keylog;
        keylog = "";
    }
}


std::string key_check(KeyWaitDelay delay_type)
{
    if (msgalert == 1)
    {
        _handle_msgalert();
        msgalert = 0;
    }

    _update_pressed_key_name();

    await(Config::instance().wait1);
    return InputContext::for_menu().check_for_command(delay_type);
}


std::string key_check_pc_turn(KeyWaitDelay delay_type)
{
    if (msgalert == 1)
    {
        _handle_msgalert();
        msgalert = 0;
    }

    _update_pressed_key_name();

    await(Config::instance().wait1);
    return InputContext::instance().check_for_command(delay_type);
}


std::string cursor_check_ex(int& index)
{
    if (msgalert == 1)
    {
        _handle_msgalert();
        msgalert = 0;
    }

    _update_pressed_key_name();

    await(Config::instance().wait1);
    return InputContext::for_menu().check_for_command_with_list(index);
}

std::string cursor_check_ex()
{
    int index;
    return cursor_check_ex(index);
}


std::string get_selected_item(int& p_)
{
    if (msgalert == 1)
    {
        _handle_msgalert();
        msgalert = 0;
    }

    _update_pressed_key_name();

    int index{};
    await(Config::instance().wait1);
    auto command = InputContext::for_menu().check_for_command_with_list(index);

    p_ = -1;
    if (index != -1 && index < keyrange)
    {
        p_ = list(0, pagesize * page + index);
    }

    return command;
}



optional<int> get_shortcut(const std::string& action)
{
    if (keybind_action_has_category(action, ActionCategory::shortcut))
    {
        return keybind_index_number(action);
    }
    return none;
}


int yes_or_no(int x, int y, int width)
{
    Prompt result;
    result.append(i18n::s.get("core.locale.ui.yes"), snail::Key::key_y, 0);
    result.append(i18n::s.get("core.locale.ui.no"), snail::Key::key_n, 1);
    return result.query(x, y, width);
}


bool is_modifier_pressed(snail::ModKey modifier)
{
    return (snail::Input::instance().modifiers() & modifier) == modifier;
}


void wait_key_released()
{
    while (1)
    {
        await(Config::instance().wait1);
        const auto input = stick(StickKey::mouse_left | StickKey::mouse_right);
        if (input == StickKey::none)
        {
            await(Config::instance().wait1);
            auto action = key_check();
            if (action == "")
            {
                break;
            }
        }
    }
}



void wait_key_pressed(bool only_enter_or_cancel)
{
    if (Config::instance().is_test)
        return;

    while (1)
    {
        await(Config::instance().wait1);
        auto action = key_check();
        if (only_enter_or_cancel)
        {
            if (action == "enter" || action == "cancel")
            {
                break;
            }
        }
        else
        {
            if (action != "")
            {
                break;
            }
        }
    }
    keyhalt = 1;
}



} // namespace elona

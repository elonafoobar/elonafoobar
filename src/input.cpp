#include "input.hpp"
#include "audio.hpp"
#include "blending.hpp"
#include "config/config.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "enums.hpp"
#include "keybind/keybind.hpp"
#include "snail/android.hpp"
#include "ui.hpp"
#include "variables.hpp"



namespace elona
{


int TODO_show_prompt_val;


int show_prompt(int x, int y, int width, PromptType type, int val4)
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
        draw("select_key", i * 24 + 624, 30);
        bmes(promptl(1, i), i * 24 + 629, 31, {250, 240, 230}, {50, 60, 80});
    }

    gsel(0);
    sx = x - width / 2;
    sy = y - promptmax * 10;
    boxf(sx + 12, sy + 12, width - 17, promptmax * 20 + 25, {60, 60, 60, 128});
    keyhalt = 1;

    if (type == PromptType::with_number)
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
        if (type == PromptType::with_number)
        {
            window2(dx(1) + sx + 20, dy, dx - 40, 36, 0, 2);
            draw("label_input", dx(1) + sx + dx / 2 - 56, dy - 32);
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
        if (type == PromptType::with_number)
        {
            window_recipe2(TODO_show_prompt_val);
            font(14 - en * 2);
        }
        redraw();
        await(Config::instance().wait1);
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
        if (type == PromptType::with_number)
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
        if (type != PromptType::cannot_cancel)
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



void input_number_dialog(int x, int y, int max_number, int initial_number)
{
    snd(26);
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
        pos(x + dx - 70 - strlen_u(inputlog2) * 8 + 8, y + 11);
        color(255, 255, 255);
        mes(inputlog2);
        color(0, 0, 0);
        redraw();
        await(Config::instance().wait1);
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
            while (number < 1)
            {
                number += max_number;
            }
        }
        if (key == key_northeast)
        {
            snd(5);
            number += 100;
            while (number > max_number)
            {
                number -= max_number;
            }
        }
        if (key == key_southwest)
        {
            snd(5);
            number -= 10;
            while (number < 1)
            {
                number += max_number;
            }
        }
        if (key == key_southeast)
        {
            snd(5);
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
        await(Config::instance().wait1);
        window2(x, y, dx, 36, 0, 2);
        draw("label_input", x + dx / 2 - 60, y - 32);

        if (imeget() != 0)
        {
            draw("ime_status_japanese", x + 8, y + 4);
        }
        else
        {
            draw("ime_status_english", x + 8, y + 4);
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

        gmode(4, p(1) / 2 + 50);
        draw("input_caret", x + 34 + p(4) * 8, y + 5);
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
    inputlog = strutil::remove_line_ending(inputlog);
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

std::string key_check(KeyWaitDelay delay_type)
{
    if (msgalert == 1)
    {
        _handle_msgalert();
        msgalert = 0;
    }

    await(Config::instance().wait1);
    return InputContext::for_menu().check_for_command(delay_type);
}

std::string cursor_check_ex(int& index)
{
    if (msgalert == 1)
    {
        _handle_msgalert();
        msgalert = 0;
    }

    await(Config::instance().wait1);
    return InputContext::for_menu().check_for_command_with_list(index);
}

std::string cursor_check_ex()
{
    int index;
    return cursor_check_ex(index);
}

std::string get_selected_item(int& p_, int& index)
{
    if (msgalert == 1)
    {
        _handle_msgalert();
        msgalert = 0;
    }

    await(Config::instance().wait1);
    auto command = InputContext::for_menu().check_for_command_with_list(index);

    p_ = -1;
    if (index != -1)
    {
        p_ = list(0, pagesize * page + index);
    }

    return command;
}

std::string get_selected_item(int& p_)
{
    int index{};
    return get_selected_item(p_, index);
}


optional<int> get_shortcut(const std::string& action)
{
    if (keybind_action_has_category(action, ActionCategory::shortcut))
    {
        return keybind_id_number(action);
    }
    return none;
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

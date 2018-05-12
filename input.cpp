#include "input.hpp"
#include "audio.hpp"
#include "config.hpp"
#include "elona.hpp"
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
    boxf(
        sx + 12,
        sy + 12,
        sx + width - 5,
        sy + promptmax * 20 + 37,
        snail::color{60, 60, 60, 128});
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
        pos(dx(1) + sx + 24, dy + 4);
        gfini(dx - 42, 35);
        gfdec(60, 60, 60);
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
        dx += std::to_string(max_number).size() * 8;
    }
    pos(x + 24, y + 4);
    gfini(dx - 42, 35);
    gfdec(60, 60, 60);
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



void input_text_dialog(int x, int y, int val2, bool is_cancelable)
{
    int ime_esc = 0;

    snd(26);
    dx = val2 * 16 + 60;
    font(16 - en * 2);

    pos(x, y);
    mesbox(inputlog);
    pos(x + 4, y + 4);
    gfini(dx - 1, 35);
    gfdec(60, 60, 60);

    notesel(inputlog);
    p(1) = 2;
    ime_esc = 0;

    for (int cnt = 0;; ++cnt)
    {
        if (ginfo(2) == 0)
        {
            objsel(1);
        }
        else
        {
            objprm(1, ""s);
            inputlog = "";
            await(100);
            --cnt;
            continue;
        }
        await(40);
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
        }
        gmode(4, -1, -1, p(1) / 2 + 50);
        pos(x + 34 + p(4) * 8, y + 5);
        gcopy(3, 0, 336, 12, 24);
        gmode(2);
        noteget(s, 0);
        color(255, 255, 255);
        pos(x + 36, y + 9);
        mes(s);
        color(0, 0, 0);

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
                ime_esc = 1;
            }
        }
        redraw();
        if (is_cancelable)
        {
            if (ime_esc == 1)
            {
                inputlog = "";
                keywait = 1;
                key = "";
                break;
            }
        }
    }
    gmode(2);
    clrobj(1);
    if (input_mode == 1)
    {
        cnv_filestr(inputlog);
    }
    input_mode = 0;
    if (en)
    {
        cnv_str(inputlog, u8"\""s, u8"'"s);
    }
    rm_crlf(inputlog);
    onkey_0();
}


} // namespace elona

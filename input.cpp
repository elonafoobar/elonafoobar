#include "input.hpp"
#include "elona.hpp"
#include "variables.hpp"



namespace elona
{


int show_prompt(int x, int y, int width, show_prompt_type type, int val4)
{
    int val5{};
    snd(26);

    int csprev = cs;
    cs = 0;
    cs_bk = -1;

    gsel(3);
    gmode(0);
    font(lang(cfg_font1, cfg_font2), 15 - en * 2, 0);
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
            dx += std::size(std::to_string(val5)) * 8;
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
        font(lang(cfg_font1, cfg_font2), 14 - en * 2, 0);
        keyrange = 0;
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
            font(lang(cfg_font1, cfg_font2), 14 - en * 2, 0);
        }
        redraw();
        await(cfg_wait1);
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


} // namespace elona

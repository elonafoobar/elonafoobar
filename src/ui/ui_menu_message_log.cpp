#include "ui_menu_message_log.hpp"
#include "../audio.hpp"
#include "../i18n.hpp"

namespace elona
{
namespace ui
{

bool ui_menu_message_log::init()
{
    curmenu = 0;
    windowshadow = 1;
    key_list(0) = key_enter;
    keyrange = 0;
    pagesize = 0;
    wx = inf_msgx - 2;
    wy = inf_msgy - (inf_maxlog - 3) * inf_msgspace - 1;
    ww = windoww - inf_msgx + 6;
    wh(0) = (inf_maxlog - 3) * inf_msgspace;
    wh(1) = 1;
    wh(2) = -1;
    snd(93);
    show_title(i18n::s.get("core.locale.ui.message.hit_any_key"));
    window_animation_corner(wx, wy, ww, wh, 8, 4);

    return true;
}

static void _draw_window()
{
    p = (windoww - inf_msgx) / 192;
    window2(wx, wy, ww, wh, 1, -1);
    for (int cnt = 0, cnt_end = (inf_maxlog - 3); cnt < cnt_end; ++cnt)
    {
        int cnt2 = cnt;
        pos(cnt);
        for (int cnt = 0, cnt_end = (p + 1); cnt < cnt_end; ++cnt)
        {
            if (cnt == p)
            {
                x = (windoww - inf_msgx) % 192;
            }
            else
            {
                x = 192;
            }
            pos(cnt * 192 + inf_msgx, inf_msgy - (cnt2 + 1) * inf_msgspace);
            gcopy(3, 496, 536 + cnt2 % 4 * inf_msgspace, x, inf_msgspace);
        }
    }
    for (int cnt = 0, cnt_end = (p + 1); cnt < cnt_end; ++cnt)
    {
        if (cnt == p)
        {
            sx = (windoww - inf_msgx) % 192;
        }
        else
        {
            sx = 192;
        }
        pos(cnt * 192 + inf_msgx, inf_msgy);
        gcopy(3, 496, 528, sx, 6);
    }
}

static void _draw_single_message(int cnt)
{
    p = msgline - cnt - 3;
    if (p < 0)
    {
        p += inf_maxlog;
    }
    else if (p >= inf_maxlog)
    {
        p -= inf_maxlog;
    }
    if (p < 0)
    {
        return;
    }
    pos(inf_msgx, inf_msgy - cnt * inf_msgspace);
    gcopy(8, 0, p * inf_msgspace, windoww - inf_msgx, inf_msgspace);
}

static void _draw_messages()
{
    gsel(4);
    gmode(0);
    boxf();
    for (int cnt = 0, cnt_end = (inf_maxlog - 3); cnt < cnt_end; ++cnt)
    {
        _draw_single_message(cnt);
    }
    gsel(0);
    gmode(2);
    pos(0, -3);
    gcopy(4, 0, 0, windoww, inf_msgy);
}

void ui_menu_message_log::update()
{
    _draw_window();
    _draw_messages();
}

void ui_menu_message_log::draw()
{
}

optional<ui_menu_message_log::result_type> ui_menu_message_log::on_key(
    const std::string& key)
{
    if (key != ""s)
    {
        update_screen();
        return ui_menu_message_log::result::finish();
    }

    return none;
}


} // namespace ui
} // namespace elona

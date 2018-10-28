#include "ui_menu_message_log.hpp"
#include "../audio.hpp"
#include "../i18n.hpp"



namespace
{

void _draw_window()
{
    constexpr auto chunk_width = 192;

    const auto log_window_width = windoww - inf_msgx;
    const auto p = log_window_width / chunk_width;

    window2(wx, wy, ww, wh, 1, -1);

    for (int dy = 0; dy < inf_maxlog - 3; ++dy)
    {
        for (int dx = 0; dx < p + 1; ++dx)
        {
            const auto x =
                dx == p ? log_window_width % chunk_width : chunk_width;
            pos(dx * chunk_width + inf_msgx,
                inf_msgy - (dy + 1) * inf_msgspace);
            gcopy(3, 496, 536 + dy % 4 * inf_msgspace, x, inf_msgspace);
        }
    }

    for (int dx = 0; dx < p + 1; ++dx)
    {
        const auto x = dx == p ? log_window_width % chunk_width : chunk_width;
        pos(dx * chunk_width + inf_msgx, inf_msgy);
        gcopy(3, 496, 528, x, 6);
    }
}



void _draw_single_message(int cnt)
{
    auto p = msgline - cnt - 3;
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



void _draw_messages()
{
    gsel(4);
    gmode(0);
    boxf();
    for (int cnt = 0; cnt < inf_maxlog - 3; ++cnt)
    {
        _draw_single_message(cnt);
    }
    gsel(0);
    gmode(2);
    pos(0, -3);
    gcopy(4, 0, 0, windoww, inf_msgy);
}

} // namespace



namespace elona
{
namespace ui
{

bool UIMenuMessageLog::init()
{
    curmenu = 0;
    windowshadow = 1;
    key_list(0) = key_enter;
    keyrange = 0;
    pagesize = 0;
    wx = inf_msgx - 2;
    wy = inf_msgy - (inf_maxlog - 3) * inf_msgspace - 1;
    ww = windoww - inf_msgx + 6;
    wh = (inf_maxlog - 3) * inf_msgspace;
    snd("core.log");
    show_title(i18n::s.get("core.locale.ui.message.hit_any_key"));
    window_animation_corner(wx, wy, ww, wh, 8, 4);

    return true;
}



void UIMenuMessageLog::update()
{
}



void UIMenuMessageLog::draw()
{
    _draw_window();
    _draw_messages();
}



optional<UIMenuMessageLog::ResultType> UIMenuMessageLog::on_key(
    const std::string& action)
{
    if (action == "north")
    {
        return none;
    }
    else if (action != ""s)
    {
        update_screen();
        return UIMenuMessageLog::Result::finish();
    }

    return none;
}

} // namespace ui
} // namespace elona

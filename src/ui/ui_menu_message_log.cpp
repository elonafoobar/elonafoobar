#include "ui_menu_message_log.hpp"
#include "../audio.hpp"
#include "../i18n.hpp"
#include "../message_log.hpp"



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



int message_width{};
int offset{};
void _draw_single_message(size_t cnt)
{
    const auto n = message_log.lines.size();
    if (n == 0)
    {
        return;
    }
    if (static_cast<int>(n) + offset < static_cast<int>(cnt) + 4)
    {
        return;
    }

    message_width = 0;
    font(inf_mesfont - en * 2);
    for (const auto& msgs : message_log.lines.at(n - cnt - 4 + offset).spans)
    {
        pos(message_width * inf_mesfont / 2 + inf_msgx + 6,
            inf_msgy - cnt * inf_msgspace);
        color(msgs.color.r, msgs.color.g, msgs.color.b);
        mes(msgs.content);

        message_width += strlen_u(msgs.content);
    }
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
        offset -= 1;
        if (offset < 4 - static_cast<int>(message_log.lines.size()))
        {
            offset = 4 - static_cast<int>(message_log.lines.size());
        }
        return none;
    }
    else if (action == "south")
    {
        offset += 1;
        if (offset > 0)
        {
            offset = 0;
        }
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

#include "ui_menu_chat_history.hpp"
#include "../audio.hpp"
#include "../i18n.hpp"
#include "../network.hpp"

namespace elona
{
namespace ui
{

static void _load_chat_history()
{
    std::string scroll_text = i18n::s.get("core.locale.ui.message.hit_any_key");
    showscroll(scroll_text, wx, wy, ww, wh);
    net_read();
    buff = "";
    notesel(buff);
    header = instr(netbuf, 0, u8"<!--START-->"s) + 13;
}

bool UIMenuChatHistory::init()
{

    key_list(0) = key_enter;
    keyrange = 0;
    pagesize = 0;
    gsel(7);
    pos(0, 0);
    picload(filesystem::dir::graphic() / u8"ie_scroll.bmp");
    gsel(0);
    windowshadow = 1;
    snd("core.scroll");
    ww = clamp(windoww - 90, windoww - 90, 720);
    wh = 440;
    wx = (windoww - ww) / 2 + inf_screenx;
    wy = winposy(wh);
    window_animation(wx, wy, ww, wh, 9, 4);

    _load_chat_history();

    return true;
}

static void _parse_net_buffer()
{
    while (1)
    {
        s = "";
        tail = instr(netbuf, header, u8"%"s);
        if (tail == -1)
        {
            break;
        }
        header += tail + 1;
        tail = instr(netbuf, header, u8"%"s);
        s += strmid(netbuf, header, tail) + u8"  "s;
        header += tail + 1;
        tail = instr(netbuf, header, u8"%"s);
        s += strmid(netbuf, header + 4, tail - 4);
        header += tail + 1;
        tail = instr(netbuf, header, u8"%"s);
        header += tail + 2;
        s += u8"\n"s;
        buff += ""s + s;
    }
}

static void _draw_messages()
{
    font(13 - en * 2);
    i = 0;
    for (int cnt = 0; cnt < 20; ++cnt)
    {
        if (i >= 20)
        {
            break;
        }
        noteget(s, cnt);
        if (en)
        {
            s = strutil::replace(s, u8"&quot;", u8"\"");
        }
        if (s == ""s && cnt == 0)
        {
            s = u8"No new messages received."s;
        }
        i += talk_conv(s, (ww - 110 - en * 50) / 7);
        pos(wx + 48, (19 - i) * 16 + wy + 48);
        color(30, 20, 10);
        mes(s);
        color(0, 0, 0);
        ++i;

        if (s == ""s)
        {
            break;
        }
    }
}

void UIMenuChatHistory::update()
{
    _parse_net_buffer();
    _draw_messages();
}

void UIMenuChatHistory::draw()
{
}

optional<UIMenuChatHistory::ResultType> UIMenuChatHistory::on_key(
    const std::string& action)
{
    if (action != ""s)
    {
        update_screen();
        return UIMenuChatHistory::Result::finish();
    }

    return none;
}


} // namespace ui
} // namespace elona

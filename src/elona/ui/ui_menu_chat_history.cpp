#include "ui_menu_chat_history.hpp"
#include "../audio.hpp"
#include "../i18n.hpp"



namespace
{

void _load_chat_history()
{
    std::string scroll_text = i18n::s.get("core.locale.ui.chat.key_hint");
    showscroll(scroll_text, wx, wy, ww, wh);
}



void _draw_messages()
{
    font(13 - en * 2);
    i = 0;
    s = u8"No new messages received."s;
    i += talk_conv(s, (ww - 110 - en * 50) / 7);
    mes(wx + 48, (19 - i) * 16 + wy + 48, s, {30, 20, 10});
}

} // namespace



namespace elona
{
namespace ui
{

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



void UIMenuChatHistory::update()
{
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

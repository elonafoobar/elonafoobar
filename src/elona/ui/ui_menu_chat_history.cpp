#include "ui_menu_chat_history.hpp"

#include "../audio.hpp"
#include "../draw.hpp"
#include "../i18n.hpp"
#include "../net.hpp"



namespace elona
{
namespace ui
{

bool UIMenuChatHistory::init()
{
    key_list(0) = key_enter;
    keyrange = 0;
    pagesize = 0;
    asset_load("ie_scroll");
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



void UIMenuChatHistory::_load_chat_history()
{
    std::string scroll_text = i18n::s.get("core.ui.chat.key_hint");
    showscroll(scroll_text, wx, wy, ww, wh);

    for (const auto& chat : net_receive_chats(false))
    {
        _chats.push_back(chat.as_chat_history());
    }

    if (_chats.empty())
    {
        _chats.push_back("No new messages received.");
    }
}



void UIMenuChatHistory::_draw_messages()
{
    font(13 - en * 2);

    int i{};
    while (i < std::min(20, static_cast<int>(_chats.size())))
    {
        std::string msg = _chats.at(i);
        i += talk_conv(msg, (ww - 110 - en * 50) / 7) + 1;
        mes(wx + 48, (19 - i) * 16 + wy + 48, msg, {30, 20, 10});
    }
}

} // namespace ui
} // namespace elona

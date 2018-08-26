#include "ui_menu_dialog.hpp"
#include "../i18n.hpp"
#include "../talk.hpp"

namespace elona
{
namespace ui
{

bool ui_menu_dialog::init()
{
    cs_bk = -1;
    key_list = key_enter;

    listmax = 0;

    if (_dialog.choices())
    {
        for (const auto& choice : *_dialog.choices())
        {
            _choice_text.emplace_back(i18n::s.get(choice.locale_key));
            key_list(listmax) = key_select(listmax);
            ++listmax;
        }
    }
    else
    {
        _choice_text.emplace_back(i18n::_(u8"ui", u8"more"));
        key_list(listmax) = key_select(listmax);
        ++listmax;
    }
    keyrange = listmax;

    key = "";
    objprm(0, ""s);
    keylog = "";
    buff = _dialog.text();

    talk_window_init();

    return true;
}

void ui_menu_dialog::update()
{
}

void ui_menu_dialog::draw()
{
    talk_window_show();

    font(14 - en * 2);
    cs_listbk();
    for (int cnt = 0, cnt_end = (keyrange); cnt < cnt_end; ++cnt)
    {
        if (cs == cnt)
        {
            color(100, 160, 250);
        }
        else
        {
            color(255, 255, 255);
        }
        noteget(s, cnt);
        x = wx + 136;
        y = wy + wh - 56 - keyrange * 19 + cnt * 19 + 2;
        display_key(x, y, cnt);
        cs_list(cs == cnt, _choice_text.at(cnt), x + 30, y, 4, 0);
        color(0, 0, 0);
    }
    cs_bk = cs;
}

optional<ui_menu_dialog::result_type> ui_menu_dialog::on_key(
    const std::string& key)
{
    int a = stick(stick_key::escape);
    if (a == stick_key::escape)
    {
        if (_is_cancelable)
        {
            return ui_menu_dialog::result::cancel();
        }
    }

    p = -1;

    for (int cnt = 0, cnt_end = (keyrange); cnt < cnt_end; ++cnt)
    {
        if (key == key_select(cnt))
        {
            p = cnt;
            break;
        }
    }
    if (p != -1)
    {
        return ui_menu_dialog::result::finish(static_cast<size_t>(p(0)));
    }

    if (key == key_cancel)
    {
        if (_is_cancelable)
        {
            return ui_menu_dialog::result::cancel();
        }
    }

    return none;
}

} // namespace ui
} // namespace elona

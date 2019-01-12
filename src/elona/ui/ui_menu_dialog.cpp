#include "ui_menu_dialog.hpp"
#include "../dialog/dialog_data.hpp"
#include "../i18n.hpp"
#include "../talk.hpp"

namespace elona
{
namespace ui
{

bool UIMenuDialog::init()
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
        _choice_text.emplace_back(i18n::s.get("core.locale.ui.more"));
        key_list(listmax) = key_select(listmax);
        ++listmax;
    }
    keyrange = listmax;

    key = "";
    objprm(0, ""s);
    keylog = "";
    buff = i18n::s.get(_dialog.text_key());

    talk_window_init();

    return true;
}

void UIMenuDialog::update()
{
}

void UIMenuDialog::draw()
{
    talk_window_show();

    font(14 - en * 2);
    cs_listbk();
    for (int cnt = 0, cnt_end = (keyrange); cnt < cnt_end; ++cnt)
    {
        noteget(s, cnt);
        x = wx + 136;
        y = wy + wh - 56 - keyrange * 19 + cnt * 19 + 2;
        display_key(x, y, cnt);
        cs_list(cs == cnt, _choice_text.at(cnt), x + 30, y, 4);
    }
    cs_bk = cs;
}

optional<UIMenuDialog::ResultType> UIMenuDialog::on_key(
    const std::string& action)
{
    StickKey a = stick(StickKey::escape);
    if (a == StickKey::escape)
    {
        if (_is_cancelable)
        {
            return UIMenuDialog::Result::cancel();
        }
    }

    // for (int cnt = 0, cnt_end = (keyrange); cnt < cnt_end; ++cnt)
    // {
    //     if (key == key_select(cnt))
    //     {
    //         p = cnt;
    //         break;
    //     }
    // }
    if (auto selected = get_selected_index_this_page())
    {
        return UIMenuDialog::Result::finish(static_cast<size_t>(*selected));
    }

    if (action == "cancel")
    {
        if (_is_cancelable)
        {
            return UIMenuDialog::Result::cancel();
        }
    }

    return none;
}

} // namespace ui
} // namespace elona

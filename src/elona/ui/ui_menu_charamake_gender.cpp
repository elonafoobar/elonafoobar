#include "ui_menu_charamake_gender.hpp"
#include "../audio.hpp"
#include "../character_making.hpp"
#include "../draw.hpp"
#include "../i18n.hpp"
#include "../menu.hpp"

namespace elona
{
namespace ui
{

bool UIMenuCharamakeGender::init()
{
    cs = 0;
    cs_bk = -1;
    pagesize = 0;

    character_making_draw_background("core.chara_making.select_gender.caption");

    windowshadow = 1;

    return true;
}

void UIMenuCharamakeGender::update()
{
}

void UIMenuCharamakeGender::_draw_window()
{
    ui_display_window(
        i18n::s.get("core.chara_making.select_gender.title"),
        strhint3b,
        (windoww - 370) / 2 + inf_screenx,
        winposy(168, 1) - 20,
        370,
        168);
    x = ww / 2;
    y = wh - 60;
    gmode(2, 30);
    gcopy_c(2, 0, 0, 180, 300, wx + ww / 2, wy + wh / 2, x, y);

    gmode(2);
    display_topic(
        i18n::s.get("core.chara_making.select_gender.gender"),
        wx + 28,
        wy + 30);
}

void UIMenuCharamakeGender::_draw_choice(int cnt, const std::string& text)
{
    gcopy(3, cnt * 24 + 72, 30, 24, 18, wx + 38, wy + 66 + cnt * 19 - 2);
    display_key(wx + 38, wy + 66 + cnt * 19 - 2, cnt);
    cs_list(cs == cnt, text, wx + 64, wy + 66 + cnt * 19 - 1);
}

void UIMenuCharamakeGender::_draw_choices()
{
    listn(0, 0) = cnven(i18n::s.get("core.ui.sex3.male"));
    listn(0, 1) = cnven(i18n::s.get("core.ui.sex3.female"));
    font(14 - en * 2);
    for (int cnt = 0; cnt < 2; ++cnt)
    {
        key_list(cnt) = key_select(cnt);
        keyrange = cnt + 1;

        _draw_choice(cnt, listn(0, cnt));
    }
}

void UIMenuCharamakeGender::draw()
{
    if (cs_bk == cs)
    {
        return;
    }

    _draw_window();
    _draw_choices();
}

optional<UIMenuCharamakeGender::ResultType> UIMenuCharamakeGender::on_key(
    const std::string& action)
{
    if (_index == 0)
    {
        return UIMenuCharamakeGender::Result::finish(0);
    }
    else if (_index == 1)
    {
        return UIMenuCharamakeGender::Result::finish(1);
    }
    else if (action == "cancel")
    {
        return UIMenuCharamakeGender::Result::cancel();
    }
    else if (getkey(snail::Key::f1))
    {
        show_game_help();
        return UIMenuCharamakeGender::Result::finish();
    }

    return none;
}

} // namespace ui
} // namespace elona

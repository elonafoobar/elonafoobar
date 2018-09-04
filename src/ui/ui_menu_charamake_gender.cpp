#include "ui_menu_charamake_gender.hpp"
#include "../audio.hpp"
#include "../character_making.hpp"
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

    character_making_draw_background(
        "core.locale.chara_making.select_gender.caption");

    windowshadow = 1;

    return true;
}

void UIMenuCharamakeGender::update()
{
}

static void _draw_window()
{
    s(0) = i18n::s.get("core.locale.chara_making.select_gender.title");
    s(1) = strhint3b;
    display_window(
        (windoww - 370) / 2 + inf_screenx, winposy(168, 1) - 20, 370, 168);
    x = ww / 2;
    y = wh - 60;
    pos(wx + ww / 2, wy + wh / 2);
    gmode(4, 30);
    gcopy_c(2, 0, 0, 180, 300, x, y);

    gmode(2);
    display_topic(
        i18n::s.get("core.locale.chara_making.select_gender.gender"),
        wx + 28,
        wy + 30);
}

static void _draw_choice(int cnt, const std::string& text)
{
    pos(wx + 38, wy + 66 + cnt * 19 - 2);
    gcopy(3, cnt * 24 + 72, 30, 24, 18);
    cs_list(cs == cnt, listn(0, cnt), wx + 64, wy + 66 + cnt * 19 - 1);
}

static void _draw_choices()
{
    listn(0, 0) = cnven(i18n::_(u8"ui", u8"male"));
    listn(0, 1) = cnven(i18n::_(u8"ui", u8"female"));
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

optional<UIMenuCharamakeGender::ResultType>
UIMenuCharamakeGender::on_key(const std::string& key)
{
    if (key == key_select(0))
    {
        return UIMenuCharamakeGender::Result::finish(0);
    }
    else if (key == key_select(1))
    {
        return UIMenuCharamakeGender::Result::finish(1);
    }
    else if (key == key_cancel)
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

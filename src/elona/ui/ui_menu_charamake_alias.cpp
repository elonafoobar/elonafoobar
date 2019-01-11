#include "ui_menu_charamake_alias.hpp"
#include "../audio.hpp"
#include "../character_making.hpp"
#include "../i18n.hpp"
#include "../menu.hpp"

namespace elona
{
namespace ui
{

bool UIMenuCharamakeAlias::init()
{
    pagemax = 0;
    page = 0;

    character_making_draw_background(
        "core.locale.chara_making.select_alias.caption");

    windowshadow = 1;
    cs = 0;
    cs_bk = -1;
    list(0, 0) = -1;

    if (_previous_alias)
    {
        cs = 1;
    }

    return true;
}

void UIMenuCharamakeAlias::_reroll_aliases()
{
    for (int cnt = 0; cnt < 17; ++cnt)
    {
        if (list(0, 0) == -1 && _locked_aliases(cnt) == 0)
        {
            if (game_data.wizard == 1)
            {
                listn(0, cnt) = u8"*Debug*"s;
            }
            else
            {
                listn(0, cnt) = random_title();
            }
        }
        if (cnt == 0)
        {
            listn(0, cnt) =
                i18n::s.get("core.locale.chara_making.common.reroll");
        }
        else if (_previous_alias && cnt == 1 && *_previous_alias != "")
        {
            listn(0, cnt) = *_previous_alias;
            _previous_alias = none;
        }
    }
}

void UIMenuCharamakeAlias::update()
{
    _reroll_aliases();
    _redraw_aliases = true;
}

static void _draw_window()
{
    ui_display_window(
        i18n::s.get("core.locale.chara_making.select_alias.title"),
        strhint3b + key_mode2 + " [" +
            i18n::s.get("core.locale.chara_making.select_alias.lock_alias") +
            "]",
        (windoww - 400) / 2 + inf_screenx,
        winposy(458, 1) + 20,
        400,
        458);
    ++cmbg;
    x = ww / 3 * 2;
    y = wh - 80;
    pos(wx + ww / 2, wy + wh / 2);
    gmode(4, 40);
    gcopy_c(2, cmbg / 4 % 4 * 180, cmbg / 4 / 4 % 2 * 300, 180, 300, x, y);
    gmode(2);
    display_topic(
        i18n::s.get("core.locale.chara_making.select_alias.alias_list"),
        wx + 28,
        wy + 30);
}

static void _draw_alias_locked(int cnt)
{
    font(12 - en * 2, snail::Font::Style::bold);
    pos(wx + 280, wy + 66 + cnt * 19 + 2);
    color(20, 20, 140);
    mes(u8"Locked!"s);
    color(0, 0, 0);
}

static void _draw_alias(int cnt, const std::string& text, bool is_locked)
{
    font(14 - en * 2);
    pos(wx + 38, wy + 66 + cnt * 19 - 2);
    gcopy(3, cnt * 24 + 72, 30, 24, 18);
    cs_list(cs == cnt, text, wx + 64, wy + 66 + cnt * 19 - 1);

    if (is_locked)
    {
        _draw_alias_locked(cnt);
    }
}

void UIMenuCharamakeAlias::draw()
{
    if (!_redraw_aliases)
    {
        return;
    }

    _draw_window();

    for (int cnt = 0; cnt < 17; ++cnt)
    {
        key_list(cnt) = key_select(cnt);
        keyrange = cnt + 1;

        const std::string& text = listn(0, cnt);
        bool is_locked = _locked_aliases(cnt) == 1;
        _draw_alias(cnt, text, is_locked);
    }
    cs_bk = cs;
    list(0, 0) = 0;

    _redraw_aliases = false;
}

void UIMenuCharamakeAlias::_lock_alias(int cs_)
{
    if (cs_ > 0)
    {
        if (_locked_aliases(cs_) != 0)
        {
            _locked_aliases(cs_) = 0;
        }
        else
        {
            _locked_aliases(cs_) = 1;
        }
        snd("core.ok1");
        _redraw_aliases = true;
    }
}

optional<UIMenuCharamakeAlias::ResultType> UIMenuCharamakeAlias::on_key(
    const std::string& action)
{
    if (auto selected = get_selected_index_this_page())
    {
        if (*selected == 0)
        {
            list(0, 0) = -1;
            snd("core.dice");
            cs_bk = -1;
            set_reupdate();
            return none;
        }
        else
        {
            std::string alias = listn(0, *selected);
            return UIMenuCharamakeAlias::Result::finish(alias);
        }
    }
    else if (action == "switch_mode_2")
    {
        _lock_alias(cs);
    }
    else if (action == "cancel")
    {
        return UIMenuCharamakeAlias::Result::cancel();
    }
    else if (getkey(snail::Key::f1))
    {
        show_game_help();
        return UIMenuCharamakeAlias::Result::finish();
    }

    if (cs != cs_bk)
    {
        _redraw_aliases = true;
    }

    return none;
}

} // namespace ui
} // namespace elona

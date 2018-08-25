#include "ui_menu_charamake_alias.hpp"
#include "../audio.hpp"

namespace elona
{
namespace ui
{

bool ui_menu_charamake_alias::init()
{
    pagemax = 0;
    page = 0;
    gmode(0);
    pos(0, 0);
    gcopy(4, 0, 0, windoww, windowh);
    gmode(2);
    s = i18n::s.get("core.locale.chara_making.select_alias.caption");
    draw_caption();
    font(13 - en * 2, snail::font_t::style_t::bold);
    pos(20, windowh - 20);
    mes(u8"Press F1 to show help."s);
    if (geneuse != ""s)
    {
        pos(20, windowh - 36);
        mes(u8"Gene from "s + geneuse);
    }
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

void ui_menu_charamake_alias::_reroll_aliases()
{
    for (int cnt = 0; cnt < 17; ++cnt)
    {
        if (list(0, 0) == -1 && _locked_aliases(cnt) == 0)
        {
            if (gdata_wizard == 1)
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

void ui_menu_charamake_alias::update()
{
    _reroll_aliases();
}

void ui_menu_charamake_alias::draw()
{
    if (!_redraw_aliases)
    {
        return;
    }

    s(0) = i18n::s.get("core.locale.chara_making.select_alias.title");
    s(1) = strhint3b + key_mode2 + " ["
        + i18n::s.get("core.locale.chara_making.select_alias.lock_alias") + "]";
    display_window(
        (windoww - 400) / 2 + inf_screenx, winposy(458, 1) + 20, 400, 458);
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
    for (int cnt = 0; cnt < 17; ++cnt)
    {
        font(14 - en * 2);
        key_list(cnt) = key_select(cnt);
        keyrange = cnt + 1;
        pos(wx + 38, wy + 66 + cnt * 19 - 2);
        gcopy(3, cnt * 24 + 72, 30, 24, 18);
        cs_list(cs == cnt, listn(0, cnt), wx + 64, wy + 66 + cnt * 19 - 1);
        if (_locked_aliases(cnt) == 1)
        {
            font(12 - en * 2, snail::font_t::style_t::bold);
            pos(wx + 280, wy + 66 + cnt * 19 + 2);
            color(20, 20, 140);
            mes(u8"Locked!"s);
            color(0, 0, 0);
        }
    }
    cs_bk = cs;
    list(0, 0) = 0;

    _redraw_aliases = false;
}

optional<ui_menu_charamake_alias::result_type> ui_menu_charamake_alias::on_key(
    const std::string& key)
{
    ELONA_GET_SELECTED_INDEX_THIS_PAGE(p);

    if (p != -1)
    {
        if (key == key_select(0))
        {
            list(0, 0) = -1;
            snd(103);
            cs_bk = -1;
            set_reupdate();
            return none;
        }
        else
        {
            std::string alias = listn(0, p);
            return ui_menu_charamake_alias::result::finish(alias);
        }
    }
    else if (key == key_mode2 && cs != -1)
    {
        if (_locked_aliases(cs) != 0)
        {
            _locked_aliases(cs) = 0;
        }
        else
        {
            _locked_aliases(cs) = 1;
        }
        snd(20);
        _redraw_aliases = true;
    }
    else if (key == key_cancel)
    {
        return ui_menu_charamake_alias::result::cancel();
    }
    else if (getkey(snail::key::f1))
    {
        show_game_help();
        return ui_menu_charamake_alias::result::finish();
    }

    if (cs != cs_bk)
    {
        _redraw_aliases = true;
    }

    return none;
}

} // namespace ui
} // namespace elona

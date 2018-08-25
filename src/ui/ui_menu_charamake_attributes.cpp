#include "ui_menu_charamake_attributes.hpp"
#include "../audio.hpp"

namespace elona
{
namespace ui
{

bool ui_menu_charamake_attributes::init()
{
    return true;
}

void ui_menu_charamake_attributes::update()
{
    cs = 0;
    cs_bk = -1;
    pagesize = 0;
    gmode(0);
    pos(0, 0);
    gcopy(4, 0, 0, windoww, windowh);
    gmode(2);
    s = i18n::s.get("core.locale.chara_making.roll_attributes.caption");
    draw_caption();
    font(13 - en * 2, snail::font_t::style_t::bold);
    pos(20, windowh - 20);
    mes(u8"Press F1 to show help."s);
    if (geneuse != ""s)
    {
        pos(20, windowh - 36);
        mes(u8"Gene from "s + geneuse);
    }
    chara_delete(0);
    access_race_info(3, cmrace);
    access_class_info(3, cmclass);
    cdata[rc].level = 1;
    for (int cnt = 10; cnt < 18; ++cnt)
    {
        if (_locked_attributes(cnt - 10) == 0)
        {
            if (_minimum)
            {
                sdata.get(cnt, rc).original_level -=
                    sdata.get(cnt, rc).original_level / 2;
            }
            else
            {
                sdata.get(cnt, rc).original_level -=
                    rnd(sdata.get(cnt, rc).original_level / 2 + 1);
            }
            _attributes(cnt - 10) = sdata.get(cnt, rc).original_level * 1000000
                + sdata.get(cnt, rc).experience * 1000
                + sdata.get(cnt, rc).potential;
        }
    }
    _minimum = false;
    listmax = 0;
    list(0, 0) = 0;
    listn(0, 0) = i18n::s.get("core.locale.chara_making.common.reroll");
    ++listmax;
    list(0, 1) = 0;
    listn(0, 1) =
        i18n::s.get("core.locale.chara_making.roll_attributes.proceed");
    ++listmax;
    for (int cnt = 10; cnt < 18; ++cnt)
    {
        list(0, listmax) = _attributes(cnt - 10);
        listn(0, listmax) = i18n::_(u8"ability", std::to_string(cnt), u8"name");
        ++listmax;
    }
    windowshadow = 1;
}

void ui_menu_charamake_attributes::draw()
{
    s(0) = i18n::s.get(
        "core.locale.chara_making.roll_attributes.attribute_reroll");
    s(1) = strhint3b + key_mode2 + " ["
        + i18n::s.get("core.locale.chara_making.roll_attributes.min_roll")
        + "]";
    display_window(
        (windoww - 360) / 2 + inf_screenx, winposy(352, 1) - 20, 360, 352);
    x = 150;
    y = 240;
    pos(wx + 85, wy + wh / 2);
    gmode(4, 30);
    gcopy_c(2, 0, 0, 180, 300, x, y);
    gmode(2);
    display_topic(
        i18n::s.get("core.locale.chara_making.roll_attributes.title"),
        wx + 28,
        wy + 30);
    font(12 + sizefix - en * 2);
    pos(wx + 175, wy + 52);
    mes(i18n::s.get(
        "core.locale.chara_making.roll_attributes.locked_items_desc"));
    font(13 - en * 2, snail::font_t::style_t::bold);
    pos(wx + 180, wy + 84);
    mes(i18n::s.get("core.locale.chara_making.roll_attributes.locks_left")
        + u8": "s + _locked_attributes(8));
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        key_list(cnt) = key_select(cnt);
        keyrange = cnt + 1;
        pos(wx + 38, wy + 66 + cnt * 23 - 2);
        gcopy(3, cnt * 24 + 72, 30, 24, 18);
        font(14 - en * 2);
        cs_list(cs == cnt, listn(0, cnt), wx + 64, wy + 66 + cnt * 23 - 1);
        font(15 - en * 2, snail::font_t::style_t::bold);
        if (cnt >= 2)
        {
            pos(wx + 198, wy + 76 + cnt * 23);
            gmode(2);
            gcopy_c(1, (cnt - 2) * inf_tiles, 672, inf_tiles, inf_tiles);
            pos(wx + 210, wy + 66 + cnt * 23);
            mes(""s + list(0, cnt) / 1000000);
            if (_locked_attributes(cnt - 2) == 1)
            {
                font(12 - en * 2, snail::font_t::style_t::bold);
                pos(wx + 240, wy + 66 + cnt * 23 + 2);
                color(20, 20, 140);
                mes(u8"Locked!"s);
                color(0, 0, 0);
            }
        }
    }
    cs_bk = cs;
}

optional<ui_menu_charamake_attributes::result_type>
ui_menu_charamake_attributes::on_key(const std::string& key)
{
    ELONA_GET_SELECTED_INDEX_THIS_PAGE(p);

    if (p != -1)
    {
        if (p == 0)
        {
            snd(103);
            set_reupdate();
            return none;
        }
        if (p == 1)
        {
            return ui_menu_charamake_attributes::result::finish(_attributes);
        }
        if (_locked_attributes(p - 2) != 0)
        {
            ++_locked_attributes(8);
            _locked_attributes(p - 2) = 0;
        }
        else if (_locked_attributes(8) > 0)
        {
            _locked_attributes(p - 2) = 1;
            --_locked_attributes(8);
        }
        snd(20);
    }
    else if (key == key_mode2)
    {
        _minimum = true;
        snd(103);
        set_reupdate();
        return none;
    }
    else if (key == key_cancel)
    {
        return ui_menu_charamake_attributes::result::cancel();
    }
    else if (getkey(snail::key::f1))
    {
        show_game_help();
        return ui_menu_charamake_attributes::result::finish();
    }

    return none;
}

} // namespace ui
} // namespace elona

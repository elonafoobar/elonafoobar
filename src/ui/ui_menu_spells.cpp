#include "ui_menu_spells.hpp"
#include "../ability.hpp"
#include "../audio.hpp"
#include "../calc.hpp"
#include "../i18n.hpp"
#include "../menu.hpp"

namespace elona
{
namespace ui
{

bool ui_menu_spells::init()
{
    listmax = 0;
    page = 0;
    pagesize = 16;
    cs = 0;
    cc = 0;
    cs_bk = -1;
    cs = commark(1) % 1000;
    page = commark(1) / 1000;
    curmenu = 0;
    for (int cnt = 0; cnt < 200; ++cnt)
    {
        if (spell(cnt) > 0)
        {
            list(0, listmax) = cnt + 400;
            list(1, listmax) = the_ability_db[400 + cnt]
                                   ->related_basic_attribute; // TODO coupling
            ++listmax;
        }
    }
    sort_list_by_column1();
    gsel(3);
    pos(960, 96);
    picload(filesystem::dir::graphic() / u8"deco_spell.bmp", 1);
    gsel(0);
    windowshadow = 1;

    return true;
}

void ui_menu_spells::update()
{
    cs_bk = -1;
    pagemax = (listmax - 1) / pagesize;
    if (page < 0)
    {
        page = pagemax;
    }
    else if (page > pagemax)
    {
        page = 0;
    }
    std::cout << "UPDATEspell " << pagemax << " " << page << std::endl;
}

void ui_menu_spells::draw()
{
    s(0) = i18n::s.get("core.locale.ui.spell.title");
    s(1) = strhint2 + strhint3 + strhint7;
    display_window((windoww - 720) / 2 + inf_screenx, winposy(438), 720, 438);
    display_topic(i18n::s.get("core.locale.ui.spell.name"), wx + 28, wy + 36);
    display_topic(
        i18n::s.get("core.locale.ui.spell.cost") + "("
            + i18n::s.get("core.locale.ui.spell.stock") + ")" + " "
            + i18n::s.get("core.locale.ui.spell.lv_chance"),
        wx + 220,
        wy + 36);
    display_topic(
        i18n::s.get("core.locale.ui.spell.effect"), wx + 400, wy + 36);
    pos(wx + 46, wy - 16);
    gcopy(3, 912, 48, 48, 48);
    pos(wx + ww - 78, wy);
    gcopy(3, 960, 96, 72, 144);
    pos(wx + ww - 180, wy);
    gcopy(3, 1032, 96, 72, 96);
    keyrange = 0;
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        key_list(cnt) = key_select(cnt);
        ++keyrange;
        if (cnt % 2 == 0)
        {
            boxf(wx + 70, wy + 66 + cnt * 19, 620, 18, {12, 14, 16, 16});
        }
        display_key(wx + 58, wy + 66 + cnt * 19 - 2, cnt);
    }
    font(14 - en * 2);
    cs_listbk();
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        i = list(0, p);
        pos(wx + 40, wy + 74 + cnt * 19);
        gmode(2);
        gcopy_c(
            1,
            (the_ability_db[i]->related_basic_attribute - 10) * inf_tiles,
            672,
            inf_tiles,
            inf_tiles);
        s = "";
        for (int cnt = 0; cnt < 20; ++cnt)
        {
            if (gdata(40 + cnt) == list(0, p))
            {
                s = u8"{"s + cnt + u8"}"s;
            }
        }
        cs_list(
            cs == cnt,
            i18n::_(u8"ability", std::to_string(i), u8"name") + s,
            wx + 84,
            wy + 66 + cnt * 19 - 1);
        s = ""s + calcspellcostmp(i, cc) + u8" ("s + spell((i - 400)) + u8")"s;
        pos(wx + 328 - strlen_u(s) * 7, wy + 66 + cnt * 19 + 2);
        mes(s);
        draw_spell_power_entry();
        s = strmid(s, 0, 40);
        pos(wx + 340, wy + 66 + cnt * 19 + 2);
        mes(""s + sdata(i, cc) + u8"/"s + calcspellfail(i, cc) + u8"%"s);
        pos(wx + 420, wy + 66 + cnt * 19 + 2);
        mes(s);
    }
    if (keyrange != 0)
    {
        cs_bk = cs;
    }
}

optional<ui_menu_spells::result_type> ui_menu_spells::on_key(
    const std::string& key)
{
    commark(1) = page * 1000 + cs;
    ELONA_GET_SELECTED_ITEM(p, 0);

    if (p != -1)
    {
        menucycle = 0;
        efid = p;
        // return do_cast_command();
        return ui_menu_spells::result::finish();
    }
    else if (key == u8"sc"s)
    {
        snd(20);
        p = list(0, pagesize * page + cs);
        if (gdata(40 + sc) == p)
        {
            gdata(40 + sc) = 0;
            set_reupdate();
            return none;
        }
        for (int cnt = 0; cnt < 20; ++cnt)
        {
            if (gdata(40 + cnt) == p)
            {
                gdata(40 + cnt) = 0;
            }
        }
        gdata(40 + sc) = p;
        txt(lang(
            u8"{"s + sc + u8"}キーにショートカットを割り当てた。"s,
            u8"You have assigned the shortcut to {"s + sc + u8"} key."s));
        display_msg(inf_screeny + inf_tiles);
        set_reupdate();
        return none;
    }
    else if (key == key_pageup)
    {
        if (pagemax != 0)
        {
            snd(1);
            ++page;
            set_reupdate();
        }
    }
    else if (key == key_pagedown)
    {
        if (pagemax != 0)
        {
            snd(1);
            --page;
            set_reupdate();
        }
    }
    else if (key == key_cancel)
    {
        update_screen();
        return ui_menu_spells::result::finish();
    }

    return none;
}

} // namespace ui
} // namespace elona

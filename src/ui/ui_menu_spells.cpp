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

static void _populate_spell_list()
{
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
}

bool UIMenuSpells::init()
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
    snd(102);
    gsel(3);
    pos(960, 96);
    picload(filesystem::dir::graphic() / u8"deco_spell.bmp", 1);
    gsel(0);
    windowshadow = 1;

    _populate_spell_list();

    return true;
}

void UIMenuSpells::update()
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
}

static void _draw_window()
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
}

static void _draw_key(int cnt)
{
    if (cnt % 2 == 0)
    {
        boxf(wx + 70, wy + 66 + cnt * 19, 620, 18, {12, 14, 16, 16});
    }
    display_key(wx + 58, wy + 66 + cnt * 19 - 2, cnt);
}

static void _draw_keys()
{
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
        _draw_key(cnt);
    }
}

static void _draw_spell_attribute(int cnt, int spell_id)
{
    pos(wx + 40, wy + 74 + cnt * 19);
    gmode(2);
    gcopy_c(
        1,
        (the_ability_db[spell_id]->related_basic_attribute - 10) * inf_tiles,
        672,
        inf_tiles,
        inf_tiles);
}

static void _draw_spell_name(int cnt, int spell_id)
{
    std::string spell_shortcut = "";
    for (int cnt = 0; cnt < 20; ++cnt)
    {
        if (gdata(40 + cnt) == spell_id)
        {
            spell_shortcut = u8"{"s + cnt + u8"}"s;
        }
    }
    cs_list(
        cs == cnt,
        i18n::_(u8"ability", std::to_string(spell_id), u8"name")
            + spell_shortcut,
        wx + 84,
        wy + 66 + cnt * 19 - 1);
}

static void _draw_spell_cost(int cnt, int spell_id)
{
    std::string spell_cost = ""s + calcspellcostmp(spell_id, cc) + u8" ("s
        + spell((spell_id - 400)) + u8")"s;
    pos(wx + 328 - strlen_u(spell_cost) * 7, wy + 66 + cnt * 19 + 2);
    mes(spell_cost);
}

static void _draw_spell_power(int cnt, int spell_id)
{
    draw_spell_power_entry(spell_id);
    std::string spell_power = strmid(s, 0, 40);
    pos(wx + 340, wy + 66 + cnt * 19 + 2);
    mes(""s + sdata(spell_id, cc) + u8"/"s + calcspellfail(spell_id, cc)
        + u8"%"s);
    pos(wx + 420, wy + 66 + cnt * 19 + 2);
    mes(spell_power);
}

static void _draw_single_list_entry(int cnt, int spell_id)
{
    _draw_spell_attribute(cnt, spell_id);
    _draw_spell_name(cnt, spell_id);
    _draw_spell_cost(cnt, spell_id);
    _draw_spell_power(cnt, spell_id);
}

static void _draw_list_entries()
{
    font(14 - en * 2);
    cs_listbk();
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        int spell_id = list(0, p);
        _draw_single_list_entry(cnt, spell_id);
    }
    if (keyrange != 0)
    {
        cs_bk = cs;
    }
}

void UIMenuSpells::draw()
{
    _draw_window();
    _draw_keys();
    _draw_list_entries();
}

static void _assign_shortcut(int sc_, int spell_id)
{
    snd(20);
    if (gdata(40 + sc_) == spell_id)
    {
        gdata(40 + sc_) = 0;
        return;
    }
    for (int cnt = 0; cnt < 20; ++cnt)
    {
        if (gdata(40 + cnt) == spell_id)
        {
            gdata(40 + cnt) = 0;
        }
    }
    gdata(40 + sc_) = spell_id;
    txt(i18n::s.get("core.locale.ui.assign_shortcut", sc_));
    display_msg(inf_screeny + inf_tiles);
}

optional<UIMenuSpells::ResultType> UIMenuSpells::on_key(
    const std::string& key)
{
    commark(1) = page * 1000 + cs;
    ELONA_GET_SELECTED_ITEM(p, 0);

    if (p != -1)
    {
        menucycle = 0;
        return UIMenuSpells::Result::finish(
            UIMenuCompositeSkillsResult(UIMenuSpellsResult{p}));
    }
    else if (key == u8"sc"s)
    {
        int selected_spell = list(0, pagesize * page + cs);
        _assign_shortcut(sc, selected_spell);
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
        return UIMenuSpells::Result::finish();
    }

    return none;
}

} // namespace ui
} // namespace elona

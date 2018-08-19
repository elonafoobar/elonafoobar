#include "ui_menu_game_help.hpp"
#include "../audio.hpp"
#include "../draw.hpp"
#include "../i18n.hpp"

namespace elona
{
namespace ui
{
bool ui_menu_game_help::init()
{
    // pre - notesel init
    snd(26);
    listmax = 0;
    page = 0;
    pagesize = 18;
    cs = 0;
    cc = 0;
    cs_bk = -1;
    page_bk = 0;
    cs_bk2 = 0;
    if (mode != 1)
    {
        load_background_variants(4);
        gsel(0);
    }
    else
    {
        cs = 3;
        cs_bk2 = cs;
    }

    // notesel
    notesel(buff);
    {
        buff(0).clear();
        std::ifstream in{(filesystem::dir::data()
                          / lang(u8"manual_JP.txt", u8"manual_ENG.txt"))
                             .native(),
                         std::ios::binary};
        std::string tmp;
        while (std::getline(in, tmp))
        {
            buff(0) += tmp + '\n';
        }
    }
    list(0, 0) = 0;
    listn(0, 0) = i18n::s.get("core.locale.ui.manual.keys.list");
    ++listmax;
    for (int cnt = 0, cnt_end = (noteinfo()); cnt < cnt_end; ++cnt)
    {
        noteget(q, cnt);
        p = instr(q, 0, u8"{}"s);
        if (p != -1)
        {
            list(0, listmax) = cnt + 1;
            listn(0, listmax) = strmid(q, instr(q, 0, u8"}"s) + 2, 999);
            ++listmax;
        }
    }
    windowshadow = 1;

    update();

    return true;
}

void ui_menu_game_help::_remove_parenthesis_around_keys()
{
    if (jp)
        return;

    for (int cnt = 0; cnt < 24; ++cnt)
    {
        if (!strutil::contains(s(cnt), u8"("))
        {
            continue;
        }
        s(cnt) = cnven(strmid(
            s(cnt),
            instr(s(cnt), 0, u8"("s) + 1,
            instr(s(cnt), 0, u8")"s) - instr(s(cnt), 0, u8"("s) - 1));
    }
    return;
}

void ui_menu_game_help::_update_key_list()
{
    x = wx + 188;
    y = wy + 6;
    display_topic(
        i18n::s.get("core.locale.ui.manual.keys.item.title"), x + 18, y + 30);
    display_topic(
        i18n::s.get("core.locale.ui.manual.keys.action.title"),
        x + 18,
        y + 142);
    display_topic(
        i18n::s.get("core.locale.ui.manual.keys.info.title"), x + 18, y + 256);
    display_topic(
        i18n::s.get("core.locale.ui.manual.keys.other.title"), x + 18, y + 328);
    s(0) = i18n::s.get("core.locale.ui.manual.keys.item.get");
    s(1) = key_get;
    s(2) = i18n::s.get("core.locale.ui.manual.keys.item.drop");
    s(3) = key_drop;
    s(4) = i18n::s.get("core.locale.ui.manual.keys.item.examine");
    s(5) = key_inventory;
    s(6) = i18n::s.get("core.locale.ui.manual.keys.item.wear_wield");
    s(7) = key_wear;
    s(8) = i18n::s.get("core.locale.ui.manual.keys.item.eat");
    s(9) = key_eat;
    s(10) = i18n::s.get("core.locale.ui.manual.keys.item.quaff");
    s(11) = key_drink;
    s(12) = i18n::s.get("core.locale.ui.manual.keys.item.read");
    s(13) = key_read;
    s(14) = i18n::s.get("core.locale.ui.manual.keys.item.zap");
    s(15) = key_zap;
    s(16) = i18n::s.get("core.locale.ui.manual.keys.item.tool");
    s(17) = key_use;
    s(18) = i18n::s.get("core.locale.ui.manual.keys.item.blend");
    s(19) = key_dip;
    s(20) = i18n::s.get("core.locale.ui.manual.keys.item.throw");
    s(21) = key_throw;
    s(22) = i18n::s.get("core.locale.ui.manual.keys.item.ammo");
    s(23) = key_ammo;
    _remove_parenthesis_around_keys();
    for (int cnt = 0; cnt < 12; ++cnt)
    {
        font(13 - en * 2);
        pos(x + 38 + cnt / 6 * 290, y + 58 + cnt % 6 * 14);
        mes(s(cnt * 2));
        font(15 - en * 2);
        pos(x + 248 + cnt / 6 * 290, y + 57 + cnt % 6 * 14);
        mes(s(cnt * 2 + 1));
    }
    s(0) = i18n::s.get("core.locale.ui.manual.keys.action.search");
    s(1) = key_search;
    s(2) = i18n::s.get("core.locale.ui.manual.keys.action.cast");
    s(3) = key_cast;
    s(4) = i18n::s.get("core.locale.ui.manual.keys.action.interact");
    s(5) = key_interact;
    s(6) = i18n::s.get("core.locale.ui.manual.keys.action.go_down");
    s(7) = key_godown;
    s(8) = i18n::s.get("core.locale.ui.manual.keys.action.go_up");
    s(9) = key_goup;
    s(10) = i18n::s.get("core.locale.ui.manual.keys.action.wait");
    s(11) = key_wait;
    s(12) = i18n::s.get("core.locale.ui.manual.keys.action.target");
    s(13) = key_target;
    s(14) = i18n::s.get("core.locale.ui.manual.keys.action.fire");
    s(15) = key_fire;
    s(16) = i18n::s.get("core.locale.ui.manual.keys.action.apply");
    s(17) = key_skill;
    s(18) = i18n::s.get("core.locale.ui.manual.keys.action.bash");
    s(19) = key_bash;
    s(20) = i18n::s.get("core.locale.ui.manual.keys.action.dig");
    s(21) = key_dig;
    s(22) = i18n::s.get("core.locale.ui.manual.keys.action.open");
    s(23) = key_open;
    s(24) = "";
    s(25) = "";
    _remove_parenthesis_around_keys();
    for (int cnt = 0; cnt < 12; ++cnt)
    {
        font(13 - en * 2);
        pos(x + 38 + cnt / 6 * 290, y + 170 + cnt % 6 * 14);
        mes(s(cnt * 2));
        font(15 - en * 2);
        pos(x + 248 + cnt / 6 * 290, y + 169 + cnt % 6 * 14);
        mes(s(cnt * 2 + 1));
    }
    s(0) = i18n::s.get("core.locale.ui.manual.keys.info.chara");
    s(1) = key_charainfo;
    s(2) = i18n::s.get("core.locale.ui.manual.keys.info.journal");
    s(3) = key_journal;
    s(4) = i18n::s.get("core.locale.ui.manual.keys.info.help");
    s(5) = key_help;
    s(6) = i18n::s.get("core.locale.ui.manual.keys.info.log");
    s(7) = key_msglog;
    s(8) = i18n::s.get("core.locale.ui.manual.keys.info.material");
    s(9) = key_material;
    s(10) = i18n::s.get("core.locale.ui.manual.keys.info.feat");
    s(11) = key_trait;
    _remove_parenthesis_around_keys();
    for (int cnt = 0; cnt < 6; ++cnt)
    {
        font(13 - en * 2);
        pos(x + 38 + cnt / 3 * 290, y + 284 + cnt % 3 * 14);
        mes(s(cnt * 2));
        font(15 - en * 2);
        pos(x + 248 + cnt / 3 * 290, y + 283 + cnt % 3 * 14);
        mes(s(cnt * 2 + 1));
    }
    s(0) = i18n::s.get("core.locale.ui.manual.keys.other.save");
    s(1) = key_save;
    s(2) = i18n::s.get("core.locale.ui.manual.keys.other.pray");
    s(3) = key_pray;
    s(4) = i18n::s.get("core.locale.ui.manual.keys.other.offer");
    s(5) = key_offer;
    s(6) = i18n::s.get("core.locale.ui.manual.keys.other.close");
    s(7) = key_close;
    s(8) = i18n::s.get("core.locale.ui.manual.keys.other.give");
    s(9) = key_give;
    s(10) = "";
    s(11) = "";
    s(12) = "";
    _remove_parenthesis_around_keys();
    for (int cnt = 0; cnt < 6; ++cnt)
    {
        font(13 - en * 2);
        pos(x + 38 + cnt / 3 * 290, y + 356 + cnt % 3 * 14);
        mes(s(cnt * 2));
        font(15 - en * 2);
        pos(x + 248 + cnt / 3 * 290, y + 355 + cnt % 3 * 14);
        mes(s(cnt * 2 + 1));
    }
    font(13 - en * 2);
    pos(x + 38, y + 408);
    mes(u8"F9 "s
        + i18n::s.get("core.locale.ui.manual.keys.other.hide_interface")
        + u8"F11  "
        + i18n::s.get("core.locale.ui.manual.keys.other.export_chara_sheet")
        + u8"F12  " + i18n::s.get("core.locale.ui.manual.keys.other.console"));
}

void ui_menu_game_help::_update_regular_pages()
{
    s(1) = listn(0, pagesize * page_bk + cs_bk2);
    display_topic(s(1), wx + 206, wy + 36);
    font(14 - en * 2);
    p = list(0, pagesize * page_bk + cs_bk2);
    {
        int y = wy + 60;
        int cnt = p;
        for (int cnt_end = cnt + (noteinfo() - p); cnt < cnt_end; ++cnt)
        {
            noteget(s1, cnt);
            i = instr(s1, 0, u8"{"s);
            if (i != -1)
            {
                break;
            }
            const auto ny = gmes(s1, wx + 216, y, 510, {30, 30, 30}, false).y;
            y = ny;
        }
    }
}

void ui_menu_game_help::_draw_navigation_menu()
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
        i = list(0, p);
        s = listn(0, p);
        cs_list(cs == cnt, s, wx + 66, wy + 66 + cnt * 19 - 1, 0);
    }
    if (keyrange != 0)
    {
        cs_bk = cs;
    }
}

void ui_menu_game_help::_draw_background_vignette(int id)
{
    cmbg = id;
    x = ww / 5 * 2;
    y = wh - 80;
    pos(wx + ww / 4, wy + wh / 2);
    gmode(4, 50);
    gcopy_c(p, cmbg % 4 * 180, cmbg / 4 % 2 * 300, 180, 300, x, y);
    gmode(2);
}

void ui_menu_game_help::update()
{
    cs_bk = -1;
    pagemax = (listmax - 1) / pagesize;
    if (page < 0)
        page = pagemax;
    else if (page > pagemax)
        page = 0;

    s(0) = u8"Elona In-Game Help"s;
    s(1) = strhint2 + strhint3b;

    if (mode == 1)
    {
        display_window(
            (windoww - 780) / 2 + inf_screenx, winposy(496, 1), 780, 496);
    }
    else
    {
        display_window(
            (windoww - 780) / 2 + inf_screenx, winposy(496) - 24, 780, 496);
    }
    display_topic(i18n::s.get("core.locale.ui.manual.topic"), wx + 34, wy + 36);

    if (mode == 1)
        p = 2;
    else
        p = 4;

    _draw_background_vignette(page % 5);
    keyrange = 0;

    // Moves and refresh cursor
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
            break;
        key_list(cnt) = key_select(cnt);
        ++keyrange;
        display_key(wx + 38, wy + 66 + cnt * 19 - 2, cnt);
    }

    // Draws the first page, key lists, in a specific way
    if (cs_bk2 == 0 && page_bk == 0)
        _update_key_list();
    else
        _update_regular_pages();
}


void ui_menu_game_help::draw()
{
    // Draws the elft part of the window continuously, ensuring key refreshing
    _draw_navigation_menu();
}


optional<ui_menu_game_help::result_type> ui_menu_game_help::on_key(
    const std::string& key)
{
    // Key selection
    ELONA_GET_SELECTED_ITEM(p, cs = i);
    if (p != -1)
    {
        snd(20);
        page_bk = page;
        cs_bk2 = cs;
        set_reupdate();
    }

    // Page changes
    if (key == key_pageup)
    {
        if (pagemax != 0)
        {
            snd(1);
            ++page;
            set_reupdate();
        }
    }
    if (key == key_pagedown)
    {
        if (pagemax != 0)
        {
            snd(1);
            --page;
            set_reupdate();
        }
    }

    // Closing menu
    if (key == key_cancel)
    {
        return ui_menu_game_help::result_type::finish();
    }
    return none;
}
} // namespace ui
} // namespace elona
#include "ui_menu_scene.hpp"
#include "../audio.hpp"
#include "../i18n.hpp"


namespace elona
{
namespace ui
{

bool ui_menu_scene::init()
{
    snd(59);
    gsel(4);
    pos(0, 0);
    picload(filesystem::dir::graphic() / u8"book.bmp", 1);
    gsel(7);
    pos(0, 0);
    picload(filesystem::dir::graphic() / u8"g1.bmp", 0);
    gsel(0);
    listmax = 0;
    page = 0;
    pagesize = 12;
    cs = 0;
    cc = 0;
    notesel(buff);
    {
        buff(0).clear();
        std::string scene_file = lang(u8"scene1.hsp", u8"scene2.hsp");
        std::ifstream in{(filesystem::dir::data() / scene_file).native(),
                         std::ios::binary};
        std::string tmp;
        while (std::getline(in, tmp))
        {
            buff(0) += tmp + '\n';
        }
    }
    p = 0;
    for (int cnt = 0; cnt < 200; ++cnt)
    {
        s = u8"{"s + cnt + u8"}"s;
        p = instr(buff, 0, s);
        if (p != -1)
        {
            if (cnt <= gdata_played_scene)
            {
                list(0, listmax) = cnt;
                list(1, listmax) = p;
                ++listmax;
            }
        }
    }
    txt(i18n::s.get("core.locale.ui.scene.which"));

    return true;
}

void ui_menu_scene::update()
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
    wx = (windoww - 720) / 2 + inf_screenx;
    wy = winposy(468);
}

void ui_menu_scene::draw()
{
    pos(wx, wy);
    gcopy(4, 0, 0, 736, 448);
    x = 240;
    y = 320;
    pos(wx + 190, wy + 220);
    gmode(4, 100);
    gcopy_c(7, 0, 0, 180, 300, x, y);
    gmode(2);
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
        display_key(wx + 394, wy + 91 + cnt * 22 - 2, cnt);
    }
    font(
        12 - en * 2,
        snail::font_t::style_t::italic | snail::font_t::style_t::underline);
    pos(wx + 90, wy + 50);
    mes(u8"Elona - Scene playback"s);
    font(12 - en * 2);
    pos(wx + 390, wy + 50);
    mes(i18n::s.get("core.locale.ui.scene.you_can_play"));
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
        cs_list(
            cs == cnt,
            i18n::s.get("core.locale.ui.scene.scene_no") + i,
            wx + 424,
            wy + 91 + cnt * 22 - 1);
    }
    font(12 - en * 2, snail::font_t::style_t::bold);
    pos(wx + 500, wy + 375);
    mes(u8"- "s + (page + 1) + u8" -"s);
    if (page < pagemax)
    {
        pos(wx + 590, wy + 375);
        mes(u8"(more)"s);
    }
    if (keyrange != 0)
    {
        cs_bk = cs;
    }
}

optional<ui_menu_scene::result_type> ui_menu_scene::on_key(
    const std::string& key)
{
    int p_ = 0;
    ELONA_GET_SELECTED_ITEM(p_, 0);

    if (p_ != -1)
    {
        sceneid = p_;
        do_play_scene();
        screenupdate = -1;
        update_entire_screen();
        txtnew();
        txt(i18n::s.get("core.locale.ui.scene.has_been_played"));
        return ui_menu_scene::result::finish();
    }
    else if (key == key_pageup)
    {
        if (pagemax != 0)
        {
            snd(71);
            ++page;
            set_reupdate();
        }
    }
    else if (key == key_pagedown)
    {
        if (pagemax != 0)
        {
            snd(71);
            --page;
            set_reupdate();
        }
    }
    else if (key == key_cancel || key == key_enter)
    {
        play_music();
        update_screen();
        return ui_menu_scene::result::cancel();
    }

    return none;
}

} // namespace ui
} // namespace elona

#include "ui_menu_scene.hpp"
#include "../audio.hpp"
#include "../i18n.hpp"



namespace elona
{
namespace ui
{

static void _load_scenes()
{
    notesel(buff);
    {
        buff(0).clear();
        std::ifstream in{
            (i18n::s.get_locale_dir("core") / "lazy" / "scene.hsp").native(),
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
}

bool UIMenuScene::init()
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

    _load_scenes();

    txt(i18n::s.get("core.locale.ui.scene.which"));

    return true;
}

void UIMenuScene::update()
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

static void _draw_window()
{
    gmode(2);
    pos(wx, wy);
    gcopy(4, 0, 0, 736, 448);
    x = 240;
    y = 320;
    pos(wx + 190, wy + 220);
    gmode(4, 100);
    gcopy_c(7, 0, 0, 180, 300, x, y);
    gmode(2);
}

static void _draw_key(int cnt)
{
    display_key(wx + 394, wy + 91 + cnt * 22 - 2, cnt);
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

static void _draw_title()
{
    font(
        12 - en * 2,
        snail::Font::Style::italic | snail::Font::Style::underline);
    pos(wx + 90, wy + 50);
    mes(u8"Elona - Scene playback"s);
    font(12 - en * 2);
    pos(wx + 390, wy + 50);
    mes(i18n::s.get("core.locale.ui.scene.you_can_play"));
}

static void _draw_list_entry(int cnt, int list_item)
{
    cs_list(
        cs == cnt,
        i18n::s.get("core.locale.ui.scene.scene_no") + list_item,
        wx + 424,
        wy + 91 + cnt * 22 - 1);
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
        int list_item = list(0, p);
        _draw_list_entry(cnt, list_item);
    }
}

static void _draw_more()
{
    font(12 - en * 2, snail::Font::Style::bold);
    pos(wx + 500, wy + 375);
    mes(u8"- "s + (page + 1) + u8" -"s);
    if (page < pagemax)
    {
        pos(wx + 590, wy + 375);
        mes(u8"(more)"s);
    }
}

void UIMenuScene::draw()
{
    _draw_window();
    _draw_keys();
    _draw_title();
    _draw_list_entries();
    _draw_more();

    if (keyrange != 0)
    {
        cs_bk = cs;
    }
}

static void _do_play_scene(int scene_id)
{
    sceneid = scene_id;
    do_play_scene();
    screenupdate = -1;
    update_entire_screen();
    txtnew();
    txt(i18n::s.get("core.locale.ui.scene.has_been_played"));
}

optional<UIMenuScene::ResultType> UIMenuScene::on_key(
    const std::string& key)
{
    int p_ = 0;
    ELONA_GET_SELECTED_ITEM(p_, 0);

    if (p_ != -1)
    {
        _do_play_scene(p_);
        return UIMenuScene::Result::finish();
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
        return UIMenuScene::Result::cancel();
    }

    return none;
}

} // namespace ui
} // namespace elona

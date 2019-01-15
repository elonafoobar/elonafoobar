#include "ui_menu_scene.hpp"
#include "../audio.hpp"
#include "../i18n.hpp"
#include "../message.hpp"



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
            if (cnt <= game_data.played_scene)
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
    snd("core.book1");
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

void UIMenuScene::_draw_window()
{
    gmode(2);
    pos(wx, wy);
    gcopy(4, 0, 0, 736, 448);
    x = 240;
    y = 320;
    pos(wx + 190, wy + 220);
    gmode(2, 100);
    gcopy_c(7, 0, 0, 180, 300, x, y);
    gmode(2);
}

void UIMenuScene::_draw_key(int cnt)
{
    display_key(wx + 394, wy + 91 + cnt * 22 - 2, cnt);
}

void UIMenuScene::_draw_keys()
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

void UIMenuScene::_draw_title()
{
    font(
        12 - en * 2,
        snail::Font::Style::italic | snail::Font::Style::underline);
    mes(wx + 90, wy + 50, u8"Elona - Scene playback"s);
    font(12 - en * 2);
    mes(wx + 390, wy + 50, i18n::s.get("core.locale.ui.scene.you_can_play"));
}

void UIMenuScene::_draw_list_entry(int cnt, int list_item)
{
    cs_list(
        cs == cnt,
        i18n::s.get("core.locale.ui.scene.scene_no") + list_item,
        wx + 424,
        wy + 91 + cnt * 22 - 1);
}

void UIMenuScene::_draw_list_entries()
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

void UIMenuScene::_draw_more()
{
    font(12 - en * 2, snail::Font::Style::bold);
    mes(wx + 500, wy + 375, u8"- "s + (page + 1) + u8" -"s);
    if (page < pagemax)
    {
        mes(wx + 590, wy + 375, u8"(more)"s);
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
    Message::instance().linebreak();
    txt(i18n::s.get("core.locale.ui.scene.has_been_played"));
}

optional<UIMenuScene::ResultType> UIMenuScene::on_key(const std::string& action)
{
    if (auto selected = get_selected_item())
    {
        _do_play_scene(*selected);
        return UIMenuScene::Result::finish();
    }
    else if (action == "next_page")
    {
        if (pagemax != 0)
        {
            snd("core.card1");
            ++page;
            set_reupdate();
        }
    }
    else if (action == "previous_page")
    {
        if (pagemax != 0)
        {
            snd("core.card1");
            --page;
            set_reupdate();
        }
    }
    else if (action == "cancel" || action == "enter")
    {
        play_music();
        update_screen();
        return UIMenuScene::Result::cancel();
    }

    return none;
}

} // namespace ui
} // namespace elona

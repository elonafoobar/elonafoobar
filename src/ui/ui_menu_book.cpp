#include "ui_menu_book.hpp"
#include "../audio.hpp"
#include "../draw.hpp"

namespace elona
{
namespace ui
{

void ui_menu_book::init()
{
    snd(59);
    gsel(4);
    pos(0, 0);
    picload(filesystem::dir::graphic() / u8"book.bmp", 1);
    gsel(0);
    notesel(buff);
    {
        buff(0).clear();
        std::ifstream in{(filesystem::dir::data() / u8"book.txt").native(),
                         std::ios::binary};
        std::string tmp;
        while (std::getline(in, tmp))
        {
            buff(0) += tmp + '\n';
        }
    }
    p = instr(buff, 0, ""s + _book_id + u8","s + lang(u8"JP"s, u8"EN"s));
    if (p == -1)
    {
        return;
    }
    buff = strmid(buff, p, instr(buff, p, u8"%END"s));
    notedel(0);
    listmax = 0;
    page = 0;
    pagesize = 40;
    cs = 0;
    cc = 0;
    listmax = noteinfo();
    keyrange = 0;
    key_list(0) = key_enter;
}

void ui_menu_book::update()
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

void ui_menu_book::draw()
{
    wx = (windoww - 720) / 2 + inf_screenx;
    wy = winposy(468);
    pos(wx, wy);
    gcopy(4, 0, 0, 736, 448);
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        x = wx + 80 + cnt / 20 * 306;
        y = wy + 45 + cnt % 20 * 16;
        noteget(s, p);
        if (p == 0)
        {
            font(12 + sizefix - en * 2, snail::font_t::style_t::bold);
        }
        if (p == 1)
        {
            font(10 + sizefix - en * 2);
        }
        if (p > 2)
        {
            font(12 + sizefix - en * 2);
        }
        pos(x, y);
        mes(s);
        if (p % 20 == 0)
        {
            font(12 + sizefix - en * 2, snail::font_t::style_t::bold);
            pos(x + 90, y + 330);
            mes(u8"- "s + (p / 20 + 1) + u8" -"s);
        }
    }
}

optional<ui_menu_book::result_type> ui_menu_book::on_key(const std::string& key)
{
    if (key == key_pageup)
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
        update_screen();
        return ui_menu_book::result_type::finish();
    }

    return none;
}

} // namespace ui
} // namespace elona

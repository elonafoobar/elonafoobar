#include "ui_menu_book.hpp"

#include "../audio.hpp"
#include "../data/types/type_asset.hpp"
#include "../draw.hpp"
#include "../i18n.hpp"

namespace elona
{
namespace ui
{

bool UIMenuBook::init()
{
    snd("core.book1");
    asset_load("book");
    gsel(0);
    notesel(buff);
    {
        buff(0).clear();
        std::ifstream in{
            (i18n::s.get_locale_dir("core") / "lazy" / "book.txt").native(),
            std::ios::binary};
        std::string tmp;
        while (std::getline(in, tmp))
        {
            buff(0) += tmp + '\n';
        }
    }
    p = instr(buff, 0, ""s + _book_id + u8","s + i18n::s.get("core.meta.tag"));
    if (p == -1)
    {
        return false;
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

    return true;
}

void UIMenuBook::update()
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

void UIMenuBook::draw()
{
    const auto& info = get_image_info("book");
    wx = (windoww - info.width + 16) / 2 + inf_screenx;
    wy = winposy(info.height + 20);
    elona::draw("book", wx, wy);

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
            font(12 + sizefix - en * 2, snail::Font::Style::bold);
        }
        if (p == 1)
        {
            font(10 + sizefix - en * 2);
        }
        if (p > 2)
        {
            font(12 + sizefix - en * 2);
        }
        mes(x, y, s);
        if (p % 20 == 0)
        {
            font(12 + sizefix - en * 2, snail::Font::Style::bold);
            mes(x + 90, y + 330, u8"- "s + (p / 20 + 1) + u8" -"s);
        }
    }
}

optional<UIMenuBook::ResultType> UIMenuBook::on_key(const std::string& action)
{
    if (action == "next_page")
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
        update_screen();
        return UIMenuBook::ResultType::finish();
    }

    return none;
}

} // namespace ui
} // namespace elona

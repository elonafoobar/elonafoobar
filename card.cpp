#include "card.hpp"
#include "character.hpp"
#include "config.hpp"
#include "elona.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "variables.hpp"

#include <iostream>


namespace elona
{


void show_card_collection()
{
    listmax = 0;
    page = 0;
    pagesize = 15;
    cs = 0;
    tc = 0;
    cs_bk = -1;
    page_load();
    ww = 700;
    wh = 400;
    wx = (windoww - ww) / 2 + inf_screenx;
    wy = winposy(wh);
    windowanime(wx, wy, ww, wh, 10, 4);
    gsel(3);
    pos(960, 96);
    picload(filesystem::path(u8"graphic") / u8"deco_feat.bmp", 1);
    gsel(0);
    windowshadow = 1;

reset_page:
    listmax = 0;
    for (const auto& data : the_character_db)
    {
        list(0, listmax) = data.id;
        list(1, listmax) = 1000 * data.level + data.id;
        ++listmax;
    }
    sort_list_by_column1();

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

    while (1)
    {
        s(0) = lang(u8"カード", u8"Card");
        s(1) = strhint5;
        display_window(
            (windoww - 730) / 2 + inf_screenx,
            winposy(430, 0),
            730,
            430,
            55,
            40);

        display_topic(lang(u8"NPCの名前", u8"NPC name"), wx + 46, wy + 36);
        display_topic(lang(u8"殺害数", u8"Kill"), wx + 455, wy + 36);

        keyrange = 0;
        for (int i = 0; i < pagesize; ++i)
        {
            p = pagesize * page + i;
            if (p >= listmax)
                break;
            key_list(i) = key_select(i);
            ++keyrange;
        }

        font(14 - en * 2);
        cs_listbk();
        for (int i = 0; i < pagesize; ++i)
        {
            p = pagesize * page + i;
            if (p >= listmax)
                break;
            cs_list(
                cs == i,
                i18n::_(u8"character", std::to_string(list(0, p)), u8"name"),
                wx + 61,
                wy + 66 + i * 19 - 1,
                0,
                card(0, list(0, p)) ? 0 : 4);
            if (card(0, list(0, p)))
            {
                color(10, 10, 10);
            }
            else
            {
                color(128, 128, 128);
            }
            pos(wx + 470, wy + 66 + i * 19 + 2);
            mes(npcmemory(0, list(0, p)));
            color(0, 0, 0);
        }

        if (keyrange != 0)
        {
            cs_bk = cs;
        }

        redraw();
        await(config::instance().wait1);
        key_check();
        cursor_check();
        p = -1;

        for (int i = 0; i < keyrange; ++i)
        {
            if (key == key_select(i))
            {
                p = pagesize * page + i;
                break;
            }
        }
        if (key == key_pageup)
        {
            if (pagemax != 0)
            {
                snd(1);
                ++page;
                goto reset_page;
            }
        }
        if (key == key_pagedown)
        {
            if (pagemax != 0)
            {
                snd(1);
                --page;
                goto reset_page;
            }
        }
        if (card(0, list(0, pagesize * page + cs))
            && (p != -1 || key == key_identify))
        {
            item tmp = inv[ci];
            itemcreate(ci, 504, -1, -1, 0);
            inv[ci].subname = list(0, pagesize * page + cs);
            inv[ci].identification_state =
                identification_state_t::completely_identified;
            int pagesize_bk = pagesize;
            int page_bk = page;
            int cs_bk = cs;
            show_item_description();
            inv[ci] = tmp;
            pagesize = pagesize_bk;
            page = page_bk;
            cs = cs_bk;
            goto reset_page;
        }
        else if (key == key_cancel)
        {
            break;
        }
    }
}


} // namespace elona

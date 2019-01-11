#include "card.hpp"
#include "audio.hpp"
#include "character.hpp"
#include "config/config.hpp"
#include "elona.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "menu.hpp"
#include "ui.hpp"
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
    window_animation(wx, wy, ww, wh, 9, 4);
    gsel(3);
    pos(960, 96);
    picload(filesystem::dir::graphic() / u8"deco_feat.bmp", 1);
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
        ui_display_window(
            i18n::s.get("core.locale.action.use.deck.title"),
            strhint5,
            (windoww - 730) / 2 + inf_screenx,
            winposy(430, 0),
            730,
            430,
            55,
            40);

        display_topic(
            i18n::s.get("core.locale.action.use.deck.npc_name"),
            wx + 46,
            wy + 36);
        display_topic(
            i18n::s.get("core.locale.action.use.deck.kill"), wx + 385, wy + 36);
        display_topic(
            i18n::s.get("core.locale.action.use.deck.generate"),
            wx + 475,
            wy + 36);

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
            x = wx + 46;
            y = wy + 66 + i * 19 - 1;
            display_key(x, y, i);
            const auto text_color = card(0, list(0, p))
                ? snail::Color{10, 10, 10}
                : snail::Color{128, 128, 128};
            cs_list(
                cs == i,
                i18n::s.get_m(
                    "locale.chara",
                    the_character_db.get_id_from_legacy(list(0, p))->get(),
                    "name"),
                x + 30,
                y,
                0,
                text_color);
            color(text_color.r, text_color.g, text_color.b);
            pos(x + 365, y + 3);
            mes(npcmemory(0, list(0, p)));
            pos(x + 455, y + 3);
            mes(npcmemory(1, list(0, p)));
            color(0, 0, 0);
        }

        if (keyrange != 0)
        {
            cs_bk = cs;
        }

        redraw();
        auto action = get_selected_item(p(0));
        if (action == "next_page")
        {
            if (pagemax != 0)
            {
                snd("core.pop1");
                ++page;
                goto reset_page;
            }
        }
        if (action == "previous_page")
        {
            if (pagemax != 0)
            {
                snd("core.pop1");
                --page;
                goto reset_page;
            }
        }
        if (card(0, list(0, pagesize * page + cs)) &&
            (p != -1 || action == "switch_mode_2"))
        {
            const int ci_save = ci;
            Item tmp;
            Item::copy(inv[ci], tmp);
            inv[ci].set_number(0);
            itemcreate(0, 504, -1, -1, 0);
            inv[ci].subname = list(0, pagesize * page + cs);
            inv[ci].identification_state = IdentifyState::completely_identified;
            int pagesize_bk = pagesize;
            int page_bk = page;
            int cs_bk = cs;
            item_show_description();
            inv[ci].set_number(0);
            Item::copy(tmp, inv[ci_save]);
            pagesize = pagesize_bk;
            page = page_bk;
            cs = cs_bk;
            goto reset_page;
        }
        else if (action == "cancel")
        {
            break;
        }
    }
}


} // namespace elona

#include "ability.hpp"
#include "variables.hpp"

namespace elona
{

int proc_random_event()
{
    int id0 = 0;
    int id1 = 0;
    if (gspd < 10)
    {
        return 0;
    }
    if (dbg_skipevent)
    {
        return 0;
    }
    if (mode == 12)
    {
        return 0;
    }
    if (mode == 9)
    {
        if (!cdata[0].god_id.empty())
        {
            if (rnd(12) == 0)
            {
                id0 = 18;
            }
        }
        if (rnd(80) == 0)
        {
            id0 = 4;
            id1 = 120;
        }
        if (rnd(20) == 0)
        {
            id0 = 3;
        }
        if (rnd(25) == 0)
        {
            id0 = 2;
        }
        if (rnd(100) == 0)
        {
            id0 = 5;
            id1 = 65;
        }
        if (rnd(20) == 0)
        {
            id0 = 6;
        }
        if (rnd(20) == 0)
        {
            id0 = 7;
        }
        if (rnd(250) == 0)
        {
            if (inv_getfreeid(0) != -1)
            {
                id0 = 19;
            }
        }
        if (rnd(10000) == 0)
        {
            if (inv_getfreeid(0) != -1)
            {
                id0 = 21;
            }
        }
        if (rnd(70) == 0)
        {
            id0 = 8;
            id1 = 40;
        }
        if (rnd(200) == 0)
        {
            id0 = 20;
        }
        if (rnd(50) == 0)
        {
            id0 = 23;
        }
        if (rnd(300) == 0)
        {
            id0 = 24;
        }
        if (rnd(90) == 0)
        {
            id0 = 22;
            id1 = 70;
        }
        goto label_1894_internal;
    }
    if (mdata(6) != 1)
    {
        if (cdata[0].continuous_action_id != 0)
        {
            return 0;
        }
    }
    if (mdata(6) == 5)
    {
        return 0;
    }
    if (rnd(30) == 0)
    {
        id0 = 17;
    }
    if (rnd(25) == 0)
    {
        id0 = 16;
    }
    if (rnd(25) == 0)
    {
        id0 = 12;
    }
    if (rnd(50) == 0)
    {
        id0 = 9;
    }
    if (rnd(80) == 0)
    {
        id0 = 14;
    }
    if (rnd(50) == 0)
    {
        id0 = 8;
        id1 = 40;
    }
    if (rnd(80) == 0)
    {
        id0 = 13;
        id1 = 45;
    }
    if (mdata(6) == 3)
    {
        if (rnd(25) == 0)
        {
            id0 = 15;
            id1 = 80;
        }
        goto label_1894_internal;
    }
    if (mdata(6) == 1)
    {
        if (rnd(40))
        {
            return 0;
        }
        goto label_1894_internal;
    }
    if (rnd(25) == 0)
    {
        id0 = 10;
    }
    if (rnd(25) == 0)
    {
        id0 = 11;
    }
label_1894_internal:
    if (id0 == 0)
    {
        return 0;
    }
    cc = 0;
    tc = 0;
    listmax = 0;
    if (id1 != 0)
    {
        if (rnd(sdata(19, 0) + 1) > id1)
        {
            id0 = 1;
        }
    }

    s = i18n::s.get_enum_property("core.locale.event.popup", "title", id0);
    buff = i18n::s.get_enum_property("core.locale.event.popup", "text", id0);
    std::string event_bg;

    switch (id0)
    {
    case 15:
        for (int cnt = 0; cnt < 20; ++cnt)
        {
            p = rnd(gdata_crowd_density + 1) + 57;
            if (p >= ELONA_MAX_CHARACTERS)
            {
                --cnt;
                continue;
            }
            if (cdata[p].state == 1)
            {
                txt(i18n::s.get("core.locale.event.popup._15.scream", cdata[p]));
                dmghp(p, 99999, -11);
                break;
            }
        }
        listmax = 1;
        event_bg = u8"bg_re9";
        break;
    case 14:
        listmax = 2;
        event_bg = u8"bg_re10";
        break;
    case 13:
        cdata[0].nutrition -= 5000;
        listmax = 1;
        event_bg = u8"bg_re10";
        break;
    case 1:
        listmax = 1;
        event_bg = u8"bg_re8";
        break;
    case 24:
        efid = 1113;
        tc = 0;
        magic();
        listmax = 1;
        event_bg = u8"bg_re4";
        break;
    case 18:
        skillexp(181, 0, 1000, 6, 1000);
        listmax = 1;
        event_bg = u8"bg_re12";
        break;
    case 12:
        efid = 1117;
        efp = 100;
        tc = 0;
        magic();
        listmax = 1;
        event_bg = u8"bg_re3";
        break;
    case 23:
        efid = 1117;
        efp = 200;
        tc = 0;
        magic();
        listmax = 1;
        event_bg = u8"bg_re3";
        break;
    case 10:
        listmax = 2;
        event_bg = u8"bg_re3";
        break;
    case 4:
        snd(116);
        efid = 1118;
        efp = 100;
        tc = 0;
        magic();
        listmax = 1;
        event_bg = u8"bg_re5";
        break;
    case 22:
        snd(116);
        efid = 454;
        efp = 100;
        tc = 0;
        magic();
        listmax = 1;
        event_bg = u8"bg_re2";
        break;
    case 19:
        flt();
        itemcreate(0, 621, -1, -1, 0);
        txt(lang(
            itemname(ci, 1) + u8"をバックパックに入れた。"s,
            u8"You put "s + itemname(ci, 1) + u8" in your backpack."s));
        listmax = 1;
        event_bg = u8"bg_re15";
        break;
    case 20:
        buff_add(tc, 19, 777, 1500);
        listmax = 1;
        event_bg = u8"bg_re12";
        break;
    case 21:
        flt();
        itemcreate(0, 721, -1, -1, 0);
        txt(lang(
            itemname(ci, 1) + u8"をバックパックに入れた。"s,
            u8"You put "s + itemname(ci, 1) + u8" in your backpack."s));
        listmax = 1;
        event_bg = u8"bg_re15";
        break;
    case 5:
        if (trait(42))
        {
            txt(i18n::s.get("core.locale.event.popup._22.no_effect"));
        }
        else
        {
            f = 0;
            tc = 0;
            for (int i = 0; i < 30; ++i)
            {
                if (cdata_body_part(tc, i) % 10000 == 0)
                {
                    continue;
                }
                else
                {
                    f = 1;
                }
            }
            if (f)
            {
                efid = 1114;
                efp = 200;
                magic();
            }
            else if (event_id() == -1)
            {
                event_add(26);
            }
        }
        listmax = 1;
        event_bg = u8"bg_re5";
        break;
    case 8:
        p = rnd(cdata[0].gold / 8 + 1);
        if (cdata[0].is_protected_from_thieves())
        {
            p = 0;
        }
        if (p > 0)
        {
            txt(lang(
                u8"金貨"s + p + u8"枚を失った。"s,
                u8"You lose "s + p + u8" gold pieces."s));
            cdata[0].gold -= p;
        }
        else
        {
            txt(i18n::s.get("core.locale.event.popup._8.no_effect"));
        }
        listmax = 1;
        event_bg = u8"bg_re9";
        break;
    case 11:
        listmax = 2;
        event_bg = u8"bg_re7";
        break;
    case 2:
        efid = 1104;
        efp = 100;
        tc = 0;
        magic();
        listmax = 1;
        event_bg = u8"bg_re6";
        break;
    case 3:
        efid = 1119;
        efp = 100;
        tc = 0;
        magic();
        listmax = 1;
        event_bg = u8"bg_re4";
        break;
    case 6:
        skillexp(154, 0, 1000);
        listmax = 1;
        event_bg = u8"bg_re4";
        break;
    case 7:
        skillexp(155, 0, 1000);
        listmax = 1;
        event_bg = u8"bg_re4";
        break;
    case 9:
        ++cdata[0].platinum_coin;
        listmax = 1;
        event_bg = u8"bg_re1";
        break;
    case 16:
        p = rnd(cdata[0].gold / 10 + 1000) + 1;
        cdata[0].gold += p;
        txt(lang(
            u8"金貨"s + p + u8"枚を手に入れた。"s,
            u8"You pick up "s + p + u8" gold pieces."s));
        listmax = 1;
        event_bg = u8"bg_re1";
        break;
    case 17:
        efid = 451;
        efp = 800;
        tc = 0;
        magic();
        listmax = 1;
        event_bg = u8"bg_re11";
        break;
    }

    for(int cnt = 0; cnt < listmax; cnt++)
    {
        list(0, cnt) = cnt;
        listn(0, cnt) = i18n::s.get_enum_property("core.locale.event.popup",
                                                  "choices._" + std::to_string(cnt),
                                                  id0);
    }

    show_random_event_window(event_bg);

    switch(id0)
    {
    case 14:
        if (rtval == 1)
        {
            cdata[0].nutrition = 15000;
            int text_index = rnd(3);
            txt(i18n::s.get_enum("core.locale.event.popup._14.results", text_index));
            show_eating_message();
            chara_anorexia(0);
        }
        break;
    case 10:
        if (rtval == 1)
        {
            for (int cnt = 0, cnt_end = (1 + rnd(4)); cnt < cnt_end; ++cnt)
            {
                flt();
                flttypemajor = fsetremain(rnd(length(fsetremain)));
                itemcreate(-1, 0, cdata[0].position.x, cdata[0].position.y, 0);
            }
            txt(lang(
                u8"何かが足元に転がってきた。"s,
                u8"Something is put on the ground."s));
        }
        break;
    case 11:
        if (rtval == 1)
        {
            txt(i18n::s.get("core.locale.event.popup._11.loot"));
            modify_karma(0, -2);
            for (int cnt = 0, cnt_end = (1 + rnd(3)); cnt < cnt_end; ++cnt)
            {
                flt(0, calcfixlv(3));
                if (rnd(3) == 0)
                {
                    flttypemajor = fsetwear(rnd(length(fsetwear)));
                }
                else
                {
                    flttypemajor = fsetremain(rnd(length(fsetremain)));
                }
                itemcreate(-1, 0, cdata[0].position.x, cdata[0].position.y, 0);
            }
            txt(lang(
                u8"何かが足元に転がってきた。"s,
                u8"Something is put on the ground."s));
        }
        else
        {
            txt(i18n::s.get("core.locale.event.popup._11.bury"));
            modify_karma(0, 5);
        }
    }

    cc = 0;
    load_continuous_action_animation();
    return 1;
}



int show_random_event_window(const std::string& file)
{
    if (config::instance().skiprandevents)
    {
        if (listmax <= 1)
        {
            snd(62);
            txt(""s + buff);
            txt(lang(u8"「"s, u8"\""s) + listn(0, 0) + lang(u8"」"s, u8"\""s));
            rtval = -1;
            return rtval;
        }
    }
    keyhalt = 1;
    cs = 0;
    page = 0;
    pagemax = 0;
    pagesize = 16;
    cs_bk = -1;
    key = "";
    objprm(0, ""s);
    keylog = "";
    if (listmax <= 1)
    {
        chatesc = 0;
    }
    else
    {
        chatesc = -1;
    }
    gsel(7);
    gmode(0);
    pos(0, 0);
    picload(filesystem::dir::graphic() / (u8""s + file + u8".bmp"), 0);
    tx = ginfo(12);
    ty = ginfo(13);
    gsel(0);
    snd(62);
    dx = tx + 36;
    talk_conv(buff, (dx - 80) / (7 - en) - en * 4);
    notesel(buff);
    dy = ty + noteinfo() * 15 + 80 + listmax * 20;
label_1897_internal:
    gmode(2);
    window(
        (windoww - dx) / 2 + inf_screenx + 4, winposy(dy) - 12, dx, dy, 0, -1);
    window((windoww - dx) / 2 + inf_screenx, winposy(dy) - 16, dx, dy);
    wx = (windoww - dx) / 2 + inf_screenx;
    wy = winposy(dy);
    gmode(0);
    pos(wx + 12, wy + 6);
    gcopy(7, 0, 0, tx, ty);
    gmode(2);
    color(240, 230, 220);
    boxl(wx + 12, wy + 6, wx + tx + 12, wy + ty + 6);
    color(0, 0, 0);
    font(14 - en * 2);
    q = lang(u8"《 "s + s + u8" 》"s, u8" < "s + s + u8" > "s);
    pos(wx + 40, wy + 16);
    color(30, 20, 10);
    bmes(q, 245, 235, 225);
    color(0, 0, 0);
    font(14 - en * 2);
    color(30, 30, 30);
    pos(wx + 24, wy + ty + 20);
    mes(buff);
    color(0, 0, 0);
    keyrange = 0;
    cs_listbk();
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        key_list(cnt) = key_select(cnt);
        ++keyrange;
    }
    font(14 - en * 2);
    for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
    {
        p = cnt;
        i = list(0, p);
        display_key(wx + 30, wy + dy + cnt * 20 - listmax * 20 - 52, cnt);
        q = listn(0, p);
        cs_list(cs == cnt, q, wx + 60, wy + dy + cnt * 20 - listmax * 20 - 52);
    }
    if (keyrange != 0)
    {
        cs_bk = cs;
    }
    redraw();
    await(config::instance().wait1);
    key_check();
    cursor_check();
    ELONA_GET_SELECTED_ITEM(rtval, snd(40));
    if (chatesc != -1)
    {
        if (key == key_cancel)
        {
            snd(40);
            rtval = chatesc;
        }
    }
    if (rtval != -1)
    {
        label_1898();
        return 0;
    }
    goto label_1897_internal;
}

int label_1898()
{
    key = "";
    return rtval;
}

} // namespace elona

#include "ui_menu_equipment.hpp"
#include "../equipment.hpp"
#include "../item.hpp"
#include "../menu.hpp"

namespace elona
{
namespace ui
{

bool ui_menu_equipment::init()
{
    cc = 0;
    page = 0;
    pagesize = 14;
    listmax = 0;
    cs = 0;
    cs_bk = -1;
    if (_cs_prev != 0)
    {
        cs = _cs_prev;
        _cs_prev = 0;
    }
    curmenu = 1;
    _mainhand = 0;
    for (int i = 0; i < 30; ++i)
    {
        if (cdata[cc].body_parts[i] != 0)
        {
            if (trait(206) != 0)
            {
                if (cdata[cc].body_parts[i] / 10000 == 2)
                {
                    continue;
                }
            }
            if (trait(203) != 0)
            {
                if (cdata[cc].body_parts[i] / 10000 == 9)
                {
                    continue;
                }
            }
            if (trait(205) != 0)
            {
                if (cdata[cc].body_parts[i] / 10000 == 3)
                {
                    continue;
                }
            }
            if (_mainhand == 0)
            {
                if (cdata[cc].body_parts[i] / 10000 == 5)
                {
                    _mainhand = i + 100;
                }
            }
            list(0, listmax) = i + 100;
            list(1, listmax) = cdata[cc].body_parts[i] / 10000;
            ++listmax;
        }
    }
    sort_list_by_column1();
    ww = 690;
    wh = 380;
    wx = (windoww - 690) / 2 + inf_screenx;
    wy = winposy(380);
    if (nowindowanime == 0)
    {
        snd(95);
    }
    window_animation(wx, wy, ww, wh, 9, 4);
    gsel(3);
    pos(960, 96);
    picload(filesystem::dir::graphic() / u8"deco_wear.bmp", 1);
    gsel(0);
    windowshadow = 1;

    return true;
}

void ui_menu_equipment::update()
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

void ui_menu_equipment::draw()
{
    s(0) = i18n::s.get("core.locale.ui.equip.title");
    s(1) = strhint5 + strhint5b + strhint3;
    display_window(
        (windoww - 690) / 2 + inf_screenx, winposy(428), 690, 428, 64);
    display_topic(
        i18n::s.get("core.locale.ui.equip.category") + "/"
            + i18n::s.get("core.locale.ui.equip.name"),
        wx + 28,
        wy + 30);
    if (showresist == 0)
    {
        display_topic(
            i18n::s.get("core.locale.ui.equip.weight"), wx + 524, wy + 30);
    }
    pos(wx + 46, wy - 16);
    gcopy(3, 768, 48, 48, 48);
    pos(wx + ww - 106, wy);
    gcopy(3, 960, 96, 96, 120);
    pos(wx, wy + wh - 164);
    gcopy(3, 960, 216, 72, 144);
    if (showresist)
    {
        pos(wx + 320, wy + 40);
        mes(i18n::s.get("core.locale.ui.equip.resist"));
    }
    display_note(
        i18n::s.get("core.locale.ui.equip.equip_weight") + ": "
        + cnvweight(cdata[cc].sum_of_equipment_weight) + cnveqweight(cc) + " "
        + i18n::s.get("core.locale.ui.equip.hit_bonus") + ":"
        + cdata[cc].hit_bonus + " "
        + i18n::s.get("core.locale.ui.equip.damage_bonus") + ":"
        + cdata[cc].damage_bonus + u8"  DV/PV:"s + cdata[cc].dv + u8"/"s
        + cdata[cc].pv);
    font(12 + sizefix - en * 2, snail::font_t::style_t::bold);
    gmode(2);
    keyrange = 0;
    f = 0;
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        key_list(cnt) = key_select(cnt);
        ++keyrange;
        if (cnt % 2 == 0)
        {
            boxf(wx + 100, wy + 60 + cnt * 19, 558, 18, {12, 14, 16, 16});
        }
        q = i18n::_(u8"ui", u8"body_part", u8"_"s + list(1, p));
        if (list(0, p) == _mainhand)
        {
            q = i18n::s.get("core.locale.ui.equip.main_hand");
        }
        pos(wx + 22, wy + 60 + cnt * 19 - 4);
        gcopy(3, 600 + (list(1, p) - 1) * 24, 336, 24, 24);
        pos(wx + 46, wy + 60 + cnt * 19 + 3);
        mes(q);
    }
    font(14 - en * 2);
    cs_listbk();
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        display_key(wx + 88, wy + 60 + cnt * 19 - 2, cnt);
        p(1) = cdata[cc].body_parts[list(0, p) - 100];
        s(0) = u8"-    "s;
        s(1) = u8"-"s;
        if (p(1) % 10000 != 0)
        {
            p(1) = p(1) % 10000 - 1;
            s(0) = itemname(p(1));
            s(1) = cnvweight(inv[p(1)].weight);

            draw_item_with_portrait(inv[p(1)], wx + 126, wy + 70 + cnt * 19);

            if (showresist)
            {
                equipinfo(p(1), wx + 320, wy + 60 + cnt * 19 + 2);
                s = strmid(s, 0, 22);
            }
        }
        else
        {
            p(1) = -1;
        }
        cs_list(
            cs == cnt,
            s,
            wx + 140 - 26,
            wy + 60 + cnt * 19 - 1,
            30,
            p(1) != -1,
            p(1));
        pos(wx + 640 - strlen_u(s(1)) * 7, wy + 60 + cnt * 19 + 2);
        mes(s(1));
    }
    cs_bk = cs;
}

optional<ui_menu_equipment::result_type> ui_menu_equipment::on_key(
    const std::string& key)
{
    ELONA_GET_SELECTED_ITEM(p, 0);

    if (p != -1)
    {
        _cs_prev = cs;
        body = p;
        if (cdata[cc].body_parts[body - 100] % 10000 != 0)
        {
            gdata(808) = 1;
            ci = cdata[cc].body_parts[body - 100] % 10000 - 1;
            if (is_cursed(inv[ci].curse_state))
            {
                txt(i18n::s.get(
                    "core.locale.ui.equip.cannot_be_taken_off", inv[ci]));
                set_reupdate();
                return none;
            }
            unequip_item(cc);
            chara_refresh(cc);
            snd(13);
            txtnew();
            txt(i18n::s.get("core.locale.ui.equip.you_unequip", inv[ci]));
            if (cdata[cc].body_parts[body - 100] / 10000 == 5)
            {
                equip_melee_weapon();
            }
            render_hud();
            set_reupdate();
            return none;
        }

        // Push equipment selection screen onto call stack and pop it
        // off after.
        nowindowanime = 1;
        menucycle = 0;
        invctrl = 6;
        snd(100);
        ctrl_inventory();

        return none;
    }
    else if (key == key_identify)
    {
        p = list(0, pagesize * page + cs);
        if (cdata[cc].body_parts[p - 100] % 10000 != 0)
        {
            ci = cdata[cc].body_parts[p - 100] % 10000 - 1;
            _cs_prev = cs;
            item_show_description();
            nowindowanime = 1;
            returnfromidentify = 0;
            screenupdate = -1;
            update_screen();
            return none;
        }
    }
    else if (key == key_mode)
    {
        if (showresist == 1)
        {
            showresist = 0;
        }
        else
        {
            showresist = 1;
        }
        snd(1);
        set_reupdate();
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
        menucycle = 0;
        create_pcpic(cc, true);
        update_screen();
        // result.turn_result = turn_result_t::pc_turn_user_error
        return ui_menu_equipment::result::cancel();
    }

    return none;
}

} // namespace ui
} // namespace elona

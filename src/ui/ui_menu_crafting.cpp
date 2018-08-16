#include "ui_menu_crafting.hpp"
#include "../i18n.hpp"

namespace elona
{
namespace ui
{

bool ui_menu_crafting::init()
{
    listmax = 0;
    page = 0;
    pagesize = 10;
    cs = 0;
    cc = 0;
    cs_bk = -1;
    page_load();
    if (_invctrl == 0)
    {
        for (int cnt = 0, cnt_end = (maxitemid); cnt < cnt_end; ++cnt)
        {
            matid = cnt;
            int stat = get_required_craft_materials();
            if (stat == -1)
            {
                continue;
            }
            if (_prodtype == 2)
            {
                if (matval != 178)
                {
                    continue;
                }
            }
            if (_prodtype == 1)
            {
                if (matval != 176)
                {
                    continue;
                }
            }
            if (_prodtype == 3)
            {
                if (matval != 179)
                {
                    continue;
                }
            }
            if (_prodtype == 4)
            {
                if (matval != 177)
                {
                    continue;
                }
            }
            if (sdata(matval, 0) + 3 < matval(1))
            {
                continue;
            }
            listn(0, listmax) = ""s + prodcheck();
            list(0, listmax) = cnt;
            list(1, listmax) = 0;
            ++listmax;
        }
    }
    else
    {
        for (int cnt = 0; cnt < 50; ++cnt)
        {
            listn(0, listmax) = ""s + prodcheck();
            list(0, listmax) = 630;
            list(1, listmax) = cnt;
            ++listmax;
        }
    }
    windowshadow = 1;
}

void ui_menu_crafting::update()
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
    s(0) = i18n::s.get("core.locale.crafting.menu.title");
    s(1) = strhint2 + strhint3b;
    display_window((windoww - 640) / 2 + inf_screenx, winposy(448), 640, 448);
    display_topic(
        i18n::s.get("core.locale.crafting.menu.product"), wx + 28, wy + 36);
    display_topic(
        i18n::s.get("core.locale.crafting.menu.detail"), wx + 296, wy + 36);
    display_topic(
        i18n::s.get("core.locale.crafting.menu.requirement"),
        wx + 28,
        wy + 258);
    display_topic(
        i18n::s.get("core.locale.crafting.menu.material"), wx + 28, wy + 304);
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
        if (cnt % 2 == 0)
        {
            boxf(wx + 70, wy + 66 + cnt * 19, 540, 18, {12, 14, 16, 16});
        }
        display_key(wx + 58, wy + 66 + cnt * 19 - 2, cnt);
    }
    cs_listbk();
    f = 0;
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        i(0) = list(0, p);
        i(1) = list(1, p);
        if (cs == cnt)
        {
            matid = i;
            if (invctrl == 0)
            {
                get_required_craft_materials();
                font(13 - en * 2);
                s = i18n::s.get("core.locale.crafting.menu.skill_needed")
                    + u8": "s;
                if (auto text = i18n::s.get_enum_optional(
                        "core.locale.crafting.menu.skills", matval))
                {
                    s += *text;
                }
                s += u8" "s + matval(1) + u8"("s + sdata(matval, 0) + u8")"s;
                if (matval(1) <= sdata(matval, 0))
                {
                    color(30, 30, 200);
                }
                else
                {
                    color(200, 30, 30);
                }
                pos(wx + 37, wy + 288);
                mes(s + u8" "s);
                color(0, 0, 0);
            }
            for (int cnt = 0; cnt < 6; ++cnt)
            {
                int j0 = matneed(cnt * 2);
                int j1 = matneed(cnt * 2 + 1);
                if (j0 == -1)
                {
                    break;
                }
                s = matname(j0) + " "
                    + i18n::s.get("core.locale.crafting.menu.x") + " " + j1
                    + u8"("s + mat(j0) + u8")"s;
                if (mat(j0) >= j1)
                {
                    color(30, 30, 200);
                }
                else
                {
                    color(200, 30, 30);
                }
                pos(wx + 37 + cnt % 3 * 192, wy + 334 + cnt / 3 * 16);
                mes(s);
                color(0, 0, 0);
            }
            f = 1;
        }
        s = ioriginalnameref(i);
        s(1) = i18n::s.get("core.locale.crafting.menu.make", s(0));
        font(14 - en * 2);
        if (elona::stoi(listn(0, p)) == -1)
        {
            p(2) = 3;
        }
        else
        {
            p(2) = 0;
        }
        cs_list(cs == cnt, cnven(s), wx + 86, wy + 66 + cnt * 19 - 1, 0, p(2));
        pos(wx + 308, wy + 66 + cnt * 19 + 2);
        mes(s(1));

        draw_item_material(ipicref(i), wx + 37, wy + 69 + cnt * 19 + 2);
    }
    if (keyrange != 0)
    {
        cs_bk = cs;
    }
    if (f == 1 || listmax == 0)
    {
        redraw();
    }
}

void ui_menu_crafting::draw()
{
}

optional<ui_menu_crafting::result_type> ui_menu_crafting::on_key(
    const std::string& key)
{
    int p_ = 0;

    ELONA_GET_SELECTED_ITEM(p_, 0);

    if (p_ != -1)
    {
        matid = p_;
        get_required_craft_materials();
        s = ioriginalnameref(matid);
        if (prodcheck() == -1)
        {
            snd(27);
            txt(i18n::s.get(
                "core.locale.crafting.you_do_not_meet_requirements"));
            set_reupdate();
            return none;
        }
        if (!inv_getspace(0))
        {
            snd(27);
            txt(i18n::s.get("core.locale.ui.inv.common.inventory_is_full"));
            set_reupdate();
            return none;
        }
        return ui_menu_crafting::result::finish(p_);
    }
    else if (key == key_pageup)
    {
        if (pagemax != 0)
        {
            snd(1);
            ++page;
            goto label_1857_internal;
        }
    }
    else if (key == key_pagedown)
    {
        if (pagemax != 0)
        {
            snd(1);
            --page;
            goto label_1857_internal;
        }
    }
    else if (key == key_cancel)
    {
        return;
    }
}


} // namespace ui
} // namespace elona

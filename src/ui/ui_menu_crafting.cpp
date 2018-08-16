#include "ui_menu_crafting.hpp"
#include "../ability.hpp"
#include "../audio.hpp"
#include "../crafting.hpp"
#include "../draw.hpp"
#include "../i18n.hpp"

namespace elona
{
namespace ui
{

static int _can_produce_item(int created_item_id)
{
    elona_vector1<int> j_at_m110;

    auto recipe = crafting_find_recipe(created_item_id);
    if (!recipe)
    {
        return -1;
    }

    if (recipe->required_skill_level > sdata(recipe->skill_used, 0))
    {
        return -1;
    }

    for (const auto& required_mat : recipe->required_materials)
    {
        if (mat(required_mat.id) < required_mat.amount)
        {
            return -1;
        }
    }

    return 1;
}

static bool _should_show_entry(int item_id, int _prodtype)
{
    auto recipe = crafting_find_recipe(item_id);
    if (!recipe)
    {
        return false;
    }
    if (_prodtype == 2)
    {
        if (recipe->skill_used != 178)
        {
            return false;
        }
    }
    if (_prodtype == 1)
    {
        if (recipe->skill_used != 176)
        {
            return false;
        }
    }
    if (_prodtype == 3)
    {
        if (recipe->skill_used != 179)
        {
            return false;
        }
    }
    if (_prodtype == 4)
    {
        if (recipe->skill_used != 177)
        {
            return false;
        }
    }
    if (sdata(recipe->skill_used, 0) + 3 < recipe->required_skill_level)
    {
        return false;
    }

    return true;
}

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
        for (int item_id = 0, cnt_end = (maxitemid); item_id < cnt_end;
             ++item_id)
        {
            if (_should_show_entry(item_id, prodtype))
            {
                listn(0, listmax) = ""s + _can_produce_item(item_id);
                list(0, listmax) = item_id;
                list(1, listmax) = 0;
                ++listmax;
            }
        }
    }
    else
    {
        for (int cnt = 0; cnt < 50; ++cnt)
        {
            listn(0, listmax) = ""s + (-1);
            list(0, listmax) = 630;
            list(1, listmax) = cnt;
            ++listmax;
        }
    }
    windowshadow = 1;

    return true;
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
            int item_id = i(0);
            auto recipe = crafting_find_recipe(item_id);
            if (invctrl == 0)
            {
                font(13 - en * 2);
                s = i18n::s.get("core.locale.crafting.menu.skill_needed")
                    + u8": "s;
                if (auto text = i18n::s.get_enum_optional(
                        "core.locale.crafting.menu.skills", recipe->skill_used))
                {
                    s += *text;
                }
                s += u8" "s + recipe->required_skill_level + u8"("s
                    + sdata(recipe->skill_used, 0) + u8")"s;
                if (recipe->required_skill_level
                    <= sdata(recipe->skill_used, 0))
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
            for (const auto required_mat : recipe->required_materials)
            {
                s = matname(required_mat.id) + " "
                    + i18n::s.get("core.locale.crafting.menu.x") + " "
                    + required_mat.amount + u8"("s + mat(required_mat.id)
                    + u8")"s;
                if (mat(required_mat.id) >= required_mat.amount)
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
        int created_item_id = p_;
        s = ioriginalnameref(created_item_id);
        if (_can_produce_item(created_item_id) == -1)
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
        return ui_menu_crafting::result::cancel();
    }

    return none;
}


} // namespace ui
} // namespace elona

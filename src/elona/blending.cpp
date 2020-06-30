#include "blending.hpp"

#include "ability.hpp"
#include "activity.hpp"
#include "audio.hpp"
#include "chara_db.hpp"
#include "character.hpp"
#include "config.hpp"
#include "data/types/type_blending_recipe.hpp"
#include "data/types/type_item.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "enchantment.hpp"
#include "enums.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "input_prompt.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "lua_env/interface.hpp"
#include "map_cell.hpp"
#include "message.hpp"
#include "random.hpp"
#include "text.hpp"
#include "ui.hpp"
#include "variables.hpp"
#include "world.hpp"



namespace elona
{

namespace
{

int step;
elona_vector1<int> rpref;
int rpid = 0;
elona_vector1<int> rppage;



int dist(const Position& p1, const Position& p2)
{
    return elona::dist(p1.x, p1.y, p2.x, p2.y);
}



std::string get_recipe_material_name(int recipe_id, int step)
{
    return lua::call_with_result<std::string>(
        "core.Impl.Blending.get_material_name",
        "<error>",
        the_blending_recipe_db.get_id_from_legacy(recipe_id)->get(),
        step + 1);
}



int get_number_of_materials(int recipe_id)
{
    return the_blending_recipe_db.ensure(recipe_id).number_of_materials;
}



std::string success_rate_to_string(int success_rate)
{
    if (success_rate == 100)
        return i18n::s.get("core.blending.success_rate.perfect");
    else if (success_rate >= 90)
        return i18n::s.get("core.blending.success_rate.piece_of_cake");
    else if (success_rate >= 80)
        return i18n::s.get("core.blending.success_rate.very_likely");
    else if (success_rate >= 70)
        return i18n::s.get("core.blending.success_rate.no_problem");
    else if (success_rate >= 60)
        return i18n::s.get("core.blending.success_rate.probably_ok");
    else if (success_rate >= 50)
        return i18n::s.get("core.blending.success_rate.maybe");
    else if (success_rate >= 40)
        return i18n::s.get("core.blending.success_rate.bad");
    else if (success_rate >= 30)
        return i18n::s.get("core.blending.success_rate.very_bad");
    else if (success_rate >= 20)
        return i18n::s.get("core.blending.success_rate.almost_impossible");
    else
        return i18n::s.get("core.blending.success_rate.impossible");
}



int calc_success_rate(
    int recipe_id,
    int number_of_ingredients,
    int current_step)
{
    int factor = 100;
    if (number_of_ingredients > 0)
    {
        for (int cnt = 0; cnt < number_of_ingredients; ++cnt)
        {
            if (rpref(10 + cnt * 2) == -1)
            {
                break;
            }
            const auto item_index = rpref(10 + cnt * 2);
            if (g_inv[item_index].curse_state == CurseState::blessed)
            {
                factor -= 10;
                if (cnt == current_step)
                {
                    txt(i18n::s.get("core.blending.success_rate.goes_up"),
                        Message::color{ColorIndex::green});
                }
            }
            else if (is_cursed(g_inv[item_index].curse_state))
            {
                factor += 20;
                if (cnt == current_step)
                {
                    txt(i18n::s.get("core.blending.success_rate.goes_down"),
                        Message::color{ColorIndex::red});
                }
            }
        }
    }

    int rate = 80;
    for (const auto& [skill_id, required_level] :
         the_blending_recipe_db.ensure(recipe_id).required_skills)
    {
        const auto legacy_skill_id = the_ability_db.ensure(skill_id).legacy_id;
        if (sdata(legacy_skill_id, 0) <= 0)
        {
            rate -= 125;
            continue;
        }
        int d = required_level * factor / 100;
        if (d < 1)
        {
            d = 1;
        }
        int p = (d * 200 / sdata(legacy_skill_id, 0) - 200) * -1;
        if (p > 0)
        {
            p /= 5;
        }
        else if (p < -125)
        {
            p = -125;
        }
        rate += p;
    }

    if (rate < 25)
    {
        return 0;
    }
    else if (rate > 100)
    {
        return 100;
    }
    else
    {
        return rate;
    }
}



bool check_one_blending_material(
    Item& item,
    int recipe_id,
    int step,
    bool check_pos)
{
    if ((the_blending_recipe_db.ensure(recipe_id).type == 0 || step != 0) &&
        item.own_state > 0)
    {
        return false;
    }
    if (check_pos)
    {
        if (dist(item.position, cdata.player().position) > 4)
        {
            return false;
        }
    }

    return lua::call_with_result<bool>(
        "core.Impl.Blending.check_material",
        false,
        lua::handle(item),
        the_blending_recipe_db.get_id_from_legacy(recipe_id)->get(),
        step + 1);
}



// Find `step`th material of `recipe_id` in `inventory`.
bool find_blending_materials(int inventory, int recipe_id, int step)
{
    assert(inventory == -1 || inventory == 0);

    const auto check_pos = inventory == -1;
    for (auto&& item : inventory == -1 ? g_inv.ground() : g_inv.pc())
    {
        if (check_one_blending_material(item, recipe_id, step, check_pos))
        {
            return true; // found
        }
    }

    return false; // not found
}



// Count `step`th material of `recipe_id` in `inventory`.
int count_blending_materials(int inventory, int recipe_id, int step)
{
    assert(inventory == -1 || inventory == 0);

    const auto check_pos = inventory == -1;
    int ret = 0;
    for (auto&& item : inventory == -1 ? g_inv.ground() : g_inv.pc())
    {
        if (check_one_blending_material(item, recipe_id, step, check_pos))
        {
            ret += item.number();
        }
    }
    return ret;
}



// Collect `step`th material of `recipe_id` in `inventory` into `result`.
void collect_blending_materials(
    std::vector<std::pair<int, int>>& result,
    int inventory,
    int recipe_id,
    int step)
{
    assert(inventory == -1 || inventory == 0);

    const auto check_pos = inventory == -1;
    for (auto&& item : inventory == -1 ? g_inv.ground() : g_inv.pc())
    {
        if (result.size() >= 500)
        {
            break;
        }
        if (check_one_blending_material(item, recipe_id, step, check_pos))
        {
            if (step > 0)
            {
                bool has_already_used = false;
                for (int i = 0; i < step; ++i)
                {
                    if (rpref(10 + i * 2) == item.index())
                    {
                        has_already_used = true;
                        break;
                    }
                }
                if (has_already_used)
                {
                    continue;
                }
            }

            result.emplace_back(
                item.index(),
                static_cast<int>(the_item_db[itemid2int(item.id)]->category) *
                        1000 +
                    itemid2int(item.id));
        }
    }
}



bool blendcheckmat(int recipe_id)
{
    rpid = recipe_id;

    for (int step = 0; step < get_number_of_materials(recipe_id); ++step)
    {
        if (!find_blending_materials(-1, recipe_id, step) &&
            !find_blending_materials(0, recipe_id, step))
        {
            return false;
        }
    }
    return true;
}



int blendmatnum(int recipe_id, int step)
{
    rpid = recipe_id;

    int ret = 0;
    ret += count_blending_materials(-1, recipe_id, step);
    ret += count_blending_materials(0, recipe_id, step);
    return ret;
}



int blendlist(elona_vector2<int>& result_array, int recipe_id, int step)
{
    rpid = recipe_id;

    std::vector<std::pair<int, int>> tmp;
    collect_blending_materials(tmp, -1, recipe_id, step);
    collect_blending_materials(tmp, 0, recipe_id, step);

    int n = 0;
    for (const auto& pair : tmp)
    {
        result_array(0, n) = pair.first;
        result_array(1, n) = pair.second;
        ++n;
    }
    return n;
}



void window_recipe(optional_ref<Item> item, int x, int y, int width, int height)
{
    elona_vector1<std::string> s_;
    int xfix2_ = 0;
    int dx_ = 0;
    int dy_ = 0;
    int i_ = 0;

    if (windowshadow == 1)
    {
        window(x + 4, y + 4, width, height - height % 8, true);
        boxf(x + width - 522, 0, 486, 69, {30, 30, 30});
        windowshadow = 0;
    }
    window(x, y, width, height - height % 8);
    window_recipe2();
    gmode(2);
    line(
        x + 50 + 0,
        y + height - 48 - height % 8,
        x + width - 40,
        y + height - 48 - height % 8,
        {194, 170, 146});
    line(
        x + 50 + 0,
        y + height - 49 - height % 8,
        x + width - 40,
        y + height - 49 - height % 8,
        {234, 220, 188});
    s_(0) = u8"Page."s + (rppage + 1) + u8"/"s + (rppage(1) + 1);
    s_(1) = ""s + key_prev + u8","s + key_next + ""s +
        i18n::s.get("core.blending.recipe.hint");
    if (step == -1)
    {
        s_(1) += strhint3;
    }
    else
    {
        s_(1) += strhint3b;
    }
    font(12 + sizefix - en * 2);
    mes(x + 25 + 0, y + height - 43 - height % 8, s_(1));
    font(12 + sizefix - en * 2, snail::Font::Style::bold);
    mes(x + width - strlen_u(s_) * 7 - 40 - xfix2_,
        y + height - 65 - height % 8,
        s_);
    dx_ = x + 35;
    dy_ = y + 48;
    font(12 - en * 2, snail::Font::Style::bold);
    mes(dx_ - 10, dy_, i18n::s.get("core.blending.window.procedure"));
    dy_ = dy_ + 18;
    font(13 - en * 2);
    i_ = 1;
    if (step == i_ - 2)
    {
        boxf(dx_ - 10, dy_ - 2, width - 60, 17, {60, 20, 10, 32});
    }
    else if (step > i_ - 2)
    {
        boxf(dx_ - 10, dy_ - 2, width - 60, 17, {20, 20, 20, 32});
    }
    if (step == -1)
    {
        mes(dx_,
            dy_,
            ""s + i_ + u8"."s +
                i18n::s.get("core.blending.window.choose_a_recipe"));
    }
    else
    {
        mes(dx_,
            dy_,
            ""s + i_ + u8"."s +
                i18n::s.get(
                    "core.blending.window.chose_the_recipe_of",
                    blending_get_recipe_name(rpid)));
    }
    dy_ += 17;
    ++i_;
    for (int cnt = 0; cnt < get_number_of_materials(rpid); ++cnt)
    {
        if (step == i_ - 2)
        {
            boxf(dx_ - 10, dy_ - 2, width - 60, 17, {60, 20, 10, 32});
        }
        else if (step > i_ - 2)
        {
            boxf(dx_ - 10, dy_ - 2, width - 60, 17, {20, 20, 20, 32});
        }
        if (step <= cnt)
        {
            s_ = i18n::s.get(
                "core.blending.window.add",
                get_recipe_material_name(rpid, cnt),
                blendmatnum(rpid, cnt));
        }
        else
        {
            s_ = i18n::s.get(
                "core.blending.window.selected", g_inv[rpref(10 + cnt * 2)]);
            s_ = strutil::take_by_width(s_, 44);
        }
        mes(dx_, dy_, ""s + i_ + u8"."s + s_);
        dy_ += 17;
        ++i_;
    }
    draw("deco_blend_b", wx + ww + 243, wy - 4);
    if (step == i_ - 2)
    {
        boxf(dx_ - 10, dy_ - 2, width - 60, 17, {60, 20, 10, 32});
    }
    else if (step > i_ - 2)
    {
        boxf(dx_ - 10, dy_ - 2, width - 60, 17, {20, 20, 20, 32});
    }
    mes(dx_,
        dy_,
        ""s + i_ + u8"."s + i18n::s.get("core.blending.window.start"));
    dy_ += 30;
    if (rppage == 0)
    {
        font(12 - en * 2, snail::Font::Style::bold);
        mes(dx_ - 10,
            dy_,
            i18n::s.get(
                "core.blending.window.the_recipe_of",
                blending_get_recipe_name(rpid)));
        dy_ += 20;
        mes(dx_ - 10, dy_, i18n::s.get("core.blending.window.required_skills"));
        dy_ = dy_ + 18;
        font(13 - en * 2);
        int cnt = 0;
        for (const auto& [skill_id, required_level] :
             the_blending_recipe_db.ensure(rpid).required_skills)
        {
            const auto legacy_skill_id =
                the_ability_db.ensure(skill_id).legacy_id;
            const auto text_color = (required_level > sdata(legacy_skill_id, 0))
                ? snail::Color{150, 0, 0}
                : snail::Color{0, 120, 0};
            mes(dx_ + cnt % 2 * 140,
                dy_ + cnt / 2 * 17,
                the_ability_db.get_text(skill_id, "name") + u8"  "s +
                    required_level + u8"("s + sdata(legacy_skill_id, 0) +
                    u8")"s,
                text_color);
            ++cnt;
        }
        dy_ += 50;
        font(12 - en * 2, snail::Font::Style::bold);
        mes(dx_ - 10,
            dy_,
            i18n::s.get("core.blending.window.required_equipment"));
        return;
    }

    if (!item)
        return;

    font(12 - en * 2, snail::Font::Style::bold);
    mes(dx_ - 10, dy_, itemname(*item));
    dy_ += 20;
    font(13 - en * 2);
    if (item->identify_state <= IdentifyState::partly)
    {
        mes(dx_, dy_, i18n::s.get("core.blending.window.havent_identified"));
        dy_ += 16;
        return;
    }

    const auto inheritance = item_get_inheritance(*item);
    if (inheritance.empty())
    {
        mes(dx_, dy_, i18n::s.get("core.blending.window.no_inherited_effects"));
    }
    else
    {
        for (const auto& inh : inheritance)
        {
            if (item->enchantments[inh].id == 0)
                break;

            get_enchantment_description(
                item->enchantments[inh].id,
                item->enchantments[inh].power,
                the_item_db[itemid2int(item->id)]->category);
            const auto text_color = item->enchantments[inh].power < 0
                ? snail::Color{180, 0, 0}
                : snail::Color{0, 0, 100};
            mes(dx_, dy_, cnven(s), text_color);
            dy_ += 16;
        }
    }
}



int calc_max_number_of_products_you_can_blend(int recipe_id)
{
    int ret = 10;
    for (int i = 0; i < 10; ++i)
    {
        const auto item_index = rpref(10 + i * 2);
        if (item_index == -1)
        {
            break;
        }
        if (the_blending_recipe_db.ensure(recipe_id).type == 2 && i == 0)
        {
            continue;
        }
        if (g_inv[item_index].number() < ret)
        {
            ret = g_inv[item_index].number();
        }
    }
    return ret;
}



bool all_ingredient_are_added(int step, int recipe_id)
{
    return step != -1 && get_number_of_materials(recipe_id) <= step;
}



optional<TurnResult> blending_menu_select_recipe()
{
    elona_vector1<int> blendchecklist;

    bool init = true;
    while (true)
    {
        if (init)
        {
            init = false;
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
            DIM2(blendchecklist, pagesize);
            for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
            {
                p = pagesize * page + cnt;
                if (p >= listmax)
                {
                    break;
                }
                blendchecklist(cnt) = blendcheckmat(list(0, p));
            }
            if (listmax <= pagesize * page + cs)
            {
                cs = listmax % pagesize - 1;
            }
        }

        windowshadow = windowshadow(1);
        ui_display_window(
            i18n::s.get("core.blending.recipe.title"),
            strhint2,
            (windoww - 780) / 2 + inf_screenx,
            winposy(445),
            380,
            432,
            74);
        display_topic(
            i18n::s.get("core.blending.recipe.name"), wx + 28, wy + 30);
        s = i18n::s.get("core.blending.recipe.counter", listmax);
        font(12 + sizefix - en * 2, snail::Font::Style::bold);
        mes(wx + 130, wy + wh - 65 - wh % 8, s);
        keyrange = 0;
        gmode(2);
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
                boxf(
                    wx + 70,
                    wy + 60 + cnt * 19,
                    ww - 100,
                    18,
                    {12, 14, 16, 16});
            }

            draw_item_material(
                550, wx + 37, wy + 70 + cnt * 19); // Recipe image

            if (blendchecklist(cnt))
            {
                draw("blend_ingredient", wx + 330, wy + 53 + cnt * 19);
            }
            rpid = list(0, p);

            int difficulty = (4 - calc_success_rate(rpid, -1, -1) / 25);
            draw_indexed(
                "recipe_difficulty", wx + 317, wy + 60 + cnt * 19, difficulty);
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
            p = list(0, p);
            rpid = p;
            s = i18n::s.get(
                "core.blending.recipe.of",
                cnven(blending_get_recipe_name(rpid)));
            display_key(wx + 58, wy + 60 + cnt * 19 - 2, cnt);
            cs_list(cs == cnt, s, wx + 84, wy + 60 + cnt * 19 - 1);
        }
        if (cs_bk != cs)
        {
            rpid = list(0, pagesize * page + cs);
            windowshadow = windowshadow(1);
            window_recipe(none, wx + ww, wy, 400, wh);
        }
        if (keyrange != 0)
        {
            cs_bk = cs;
        }
        windowshadow(1) = 0;
        draw("deco_blend_c", wx + 10, wy + wh - 100);
        redraw();

        const auto action = get_selected_item(p(0));
        if (p != -1)
        {
            rpid = p;
            step = 0;
            rppage(0) = 1;
            rppage(1) = 1;
            rpref(0) = rpid;
            return none;
        }
        if (action == "next_page")
        {
            if (pagemax != 0)
            {
                snd("core.pop1");
                ++page;
                init = true;
                continue;
            }
        }
        if (action == "previous_page")
        {
            if (pagemax != 0)
            {
                snd("core.pop1");
                --page;
                init = true;
                continue;
            }
        }
        if (action == "cancel")
        {
            screenupdate = 0;
            update_screen();
            return TurnResult::pc_turn_user_error;
        }
    }
}



void blendig_menu_select_materials()
{
    while (true)
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
        windowshadow = windowshadow(1);
        ui_display_window(
            i18n::s.get(
                "core.blending.steps.add_ingredient_prompt",
                get_recipe_material_name(rpid, step)),
            strhint2,
            (windoww - 780) / 2 + inf_screenx,
            winposy(445),
            380,
            432,
            74);
        display_topic(
            i18n::s.get("core.blending.steps.item_name"), wx + 28, wy + 30);
        s = i18n::s.get("core.blending.steps.item_counter", listmax);
        font(12 + sizefix - en * 2, snail::Font::Style::bold);
        mes(wx + 130, wy + wh - 65 - wh % 8, s);
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
                boxf(
                    wx + 70,
                    wy + 60 + cnt * 19,
                    ww - 100,
                    18,
                    {12, 14, 16, 16});
            }
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
            p = list(0, p);
            s = itemname(g_inv[p]);
            s = strutil::take_by_width(s, 28);
            if (inv_getowner(g_inv[p]) == -1)
            {
                s += i18n::s.get("core.blending.steps.ground");
            }
            display_key(wx + 58, wy + 60 + cnt * 19 - 2, cnt);

            draw_item_with_portrait_scale_height(
                g_inv[p], wx + 37, wy + 69 + cnt * 19);

            if (g_inv[p].body_part != 0)
            {
                draw("equipped", wx + 46, wy + 72 + cnt * 18 - 3);
            }
            cs_list(
                cs == cnt,
                s,
                wx + 84,
                wy + 60 + cnt * 19 - 1,
                0,
                cs_list_get_item_color(g_inv[p]));
        }
        p = list(0, pagesize * page + cs);
        if (listmax == 0)
        {
            p = -1;
        }
        if (cs_bk != cs)
        {
            windowshadow = windowshadow(1);
            window_recipe(
                p == -1 ? none : optional_ref<Item>(g_inv[p]),
                wx + ww,
                wy,
                400,
                wh);
        }
        if (keyrange != 0)
        {
            cs_bk = cs;
        }
        windowshadow(1) = 0;
        draw("deco_blend_c", wx + 10, wy + wh - 100);
        redraw();

        const auto action = get_selected_item(p(0));
        if (action == "next_page")
        {
            if (pagemax != 0)
            {
                snd("core.pop1");
                ++page;
                continue;
            }
        }
        if (action == "previous_page")
        {
            if (pagemax != 0)
            {
                snd("core.pop1");
                --page;
                continue;
            }
        }
        if (p != -1)
        {
            const auto item_index = p(0);
            if (g_inv[item_index].is_marked_as_no_drop())
            {
                snd("core.fail1");
                txt(i18n::s.get("core.ui.inv.common.set_as_no_drop"));
                continue;
            }
            rpref(10 + step * 2 + 0) = item_index;
            rpref(10 + step * 2 + 1) = itemid2int(g_inv[item_index].id);
            snd("core.drink1");
            txt(i18n::s.get("core.blending.steps.you_add", g_inv[item_index]));
            ++step;
            p = calc_success_rate(rpid, step, step - 1);
            return;
        }
        if (action == "previous_menu")
        {
            snd("core.pop1");
            --rppage;
            cs_bk = -1;
            if (rppage < 0)
            {
                rppage = rppage(1);
            }
        }
        if (action == "next_menu")
        {
            snd("core.pop1");
            ++rppage;
            cs_bk = -1;
            if (rppage > rppage(1))
            {
                rppage = 0;
            }
        }
        if (action == "cancel")
        {
            --step;
            return;
        }
    }
}



bool has_required_materials()
{
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        if (rpref(10 + cnt * 2) == -1)
        {
            break;
        }
        if (rpref(10 + cnt * 2) == -2)
        {
            return false;
        }
        if (g_inv[rpref(10 + cnt * 2)].number() <= 0 ||
            g_inv[rpref(10 + cnt * 2)].id != int2itemid(rpref(11 + cnt * 2)))
        {
            return false;
        }
    }
    return true;
}



void clear_rprefmat()
{
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        rpref(10 + cnt * 2) = -1;
    }
}



void spend_materials(bool success)
{
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        if (rpref(10 + cnt * 2) == -1)
        {
            break;
        }
        if (rpref(10 + cnt * 2) == -2)
        {
            continue;
        }
        if (the_blending_recipe_db.ensure(rpid).type != 0 && cnt == 0)
        {
            continue;
        }
        if (success)
        {
            g_inv[rpref(10 + cnt * 2)].modify_number(-1);
        }
        else
        {
            if (rnd(3) == 0)
            {
                txt(i18n::s.get(
                    "core.blending.you_lose", g_inv[rpref(10 + cnt * 2)]));
                g_inv[rpref(10 + cnt * 2)].modify_number(-1);
            }
        }
        if (chara_unequip(g_inv[rpref(10 + cnt * 2)]))
        {
            chara_refresh(cdata.player());
        }
        cell_refresh(
            g_inv[rpref(10 + cnt * 2)].position.x,
            g_inv[rpref(10 + cnt * 2)].position.y);
    }
    refresh_burden_state();
}



// TODO: Much duplication with do_dip_command()
void blending_proc_on_success_events()
{
    const auto item1_index = rpref(10);
    const auto item2_index = rpref(12);
    if (the_blending_recipe_db.ensure(rpid).type == 2)
    {
        item_separate(g_inv[item1_index]);
    }
    else if (g_inv[item1_index].number() <= 1)
    {
        rpref(10) = -2;
    }
    else
    {
        int stat = item_separate(g_inv[item1_index]).index();
        if (rpref(10) == stat)
        {
            rpref(10) = -2;
        }
        else
        {
            rpref(10) = stat;
        }
    }

    // See each `on_success` for parameter usage.
    auto& item1 = g_inv[item1_index];
    auto& item2 = g_inv[item2_index];
    auto materials =
        lua::create_table(1, lua::handle(item1), 2, lua::handle(item2));
    auto on_success_args = lua::create_table("materials", materials);
    the_blending_recipe_db.ensure(rpid).on_success.call(on_success_args);

    item_stack(0, item1);
    if (item1.body_part != 0)
    {
        create_pcpic(cdata.player());
    }
    if (inv_getowner(item1) == -1)
    {
        cell_refresh(item1.position.x, item1.position.y);
    }
    chara_refresh(cdata.player());
}



void blending_on_finish()
{
    const auto success = calc_success_rate(rpid, -1, -1) >= rnd(100);
    if (success)
    {
        const auto& recipe_data = the_blending_recipe_db.ensure(rpid);
        if (recipe_data.type != 0)
        {
            blending_proc_on_success_events();
        }
        else
        {
            recipe_data.on_success.call();
        }
        for (const auto& [skill_id, required_level] :
             recipe_data.required_skills)
        {
            chara_gain_skill_exp(
                cdata.player(),
                the_ability_db.ensure(skill_id).legacy_id,
                50 + required_level + rpref(2) / 10000 * 25,
                2,
                50);
        }
    }
    else
    {
        txt(i18n::s.get("core.blending.failed"),
            Message::color{ColorIndex::red});
    }
    --rpref(1);
    spend_materials(success);
}



void activity_blending_start()
{
    Message::instance().linebreak();
    txt(i18n::s.get(
        "core.blending.started",
        cdata.player(),
        blending_get_recipe_name(rpid)));
    cdata.player().activity.type = Activity::Type::blend;
    cdata.player().activity.turn = rpref(2) % 10000;
}



void activity_blending_doing()
{
    if (rnd(30) == 0)
    {
        txt(i18n::s.get("core.blending.sounds"),
            Message::color{ColorIndex::blue});
    }
}



void activity_blending_end()
{
    if (rpref(2) >= 10000)
    {
        cdata.player().activity.turn = rpref(2) / 10000;
        for (int cnt = 0;; ++cnt)
        {
            mode = 12;
            ++game_data.date.hour;
            weather_changes();
            render_hud();
            if (cnt % 5 == 0)
            {
                txt(i18n::s.get("core.blending.sounds"),
                    Message::color{ColorIndex::blue});
            }
            redraw();
            await(g_config.animation_wait() * 5);
            game_data.date.minute = 0;
            --cdata.player().activity.turn;
            if (cdata.player().activity.turn <= 0)
            {
                if (!has_required_materials())
                {
                    txt(i18n::s.get(
                        "core.blending.required_material_not_found"));
                    break;
                }
                blending_on_finish();
                if (rpref(1) > 0)
                {
                    cdata.player().activity.turn = rpref(2) / 10000;
                    cnt = 0 - 1;
                    continue;
                }
                else
                {
                    break;
                }
            }
        }
        cdata.player().activity.finish();
        mode = 0;
        return;
    }

    if (!has_required_materials())
    {
        txt(i18n::s.get("core.blending.required_material_not_found"));
        cdata.player().activity.finish();
        return;
    }
    blending_on_finish();
    if (rpref(1) > 0)
    {
        // restart
        activity_blending_start();
    }
    else
    {
        cdata.player().activity.finish();
    }
}

} // namespace



void blending_init_recipe_data()
{
    // _1 = num
    // _2 = required time
    // _3 = calc_success_rate
    DIM2(rpref, 100);

    // randomly-generated recipe ID candidates
    rpsourcelist.clear();
    rpsourcelist(0) = 0;
    for (const auto& [_, recipe_data] : the_blending_recipe_db)
    {
        if (recipe_data.generated)
        {
            rpsourcelist(rpsourcelist.size()) = recipe_data.legacy_id;
        }
    }
}



std::string blending_get_recipe_name(int recipe_id)
{
    return the_blending_recipe_db.get_text(recipe_id, "name");
}



void blending_clear_recipememory()
{
    for (const auto& [_, recipe_data] : the_blending_recipe_db)
    {
        if (recipe_data.known)
        {
            recipememory(recipe_data.legacy_id) = 1;
        }
    }
}



void activity_blending()
{
    rpid = rpref(0);
    if (rpid == 0)
    {
        cdata.player().activity.finish();
        return;
    }

    if (!cdata.player().activity)
    {
        activity_blending_start();
    }
    else if (cdata.player().activity.turn > 0)
    {
        activity_blending_doing();
    }
    else
    {
        activity_blending_end();
    }
}



TurnResult blending_menu()
{
    step = -1;
    rpid = 0;
    asset_load("deco_blend");
    gsel(0);
    clear_rprefmat();

    while (true)
    {
        if (all_ingredient_are_added(step, rpid))
        {
            rppage = 0;
            window_recipe(none, wx + ww, wy, 400, wh);
            Message::instance().linebreak();
            txt(i18n::s.get("core.blending.prompt.how_many"));
            PromptWithNumber prompt(
                calc_max_number_of_products_you_can_blend(rpid),
                "core.blending.prompt");
            prompt.append("start", snail::Key::key_a);
            prompt.append("go_back", snail::Key::key_b);
            prompt.append("from_the_start", snail::Key::key_c);
            const auto result = prompt.query(promptx, prompty, 220);
            if (result.index == 0) // start
            {
                rpref(1) = result.number;
                rpref(2) = the_blending_recipe_db.ensure(rpid).required_turns +
                    10000 * the_blending_recipe_db.ensure(rpid).required_hours;
                rpref(3) = calc_success_rate(rpid, step, -1);
                activity_blending();
                return TurnResult::turn_end;
            }
            else if (result.index == 2) // from the start
            {
                step = -1;
                continue;
            }
            else
            {
                --step; // go back
                continue;
            }
        }

        page = 0;
        pagesize = 16;
        listmax = 0;
        cs = 0;
        cs_bk = -1;
        screenupdate = -1;
        update_screen();

        if (step == -1)
        {
            rppage(0) = 0;
            rppage(1) = 0;
            listmax = 0;
            for (const auto& [_, recipe_data] : the_blending_recipe_db)
            {
                if (recipememory(recipe_data.legacy_id) > 0)
                {
                    list(0, listmax) = recipe_data.legacy_id;
                    list(1, listmax) = recipe_data.legacy_id;
                    ++listmax;
                }
            }
            sort_list_by_column1();
            windowshadow(1) = 1;
            Message::instance().linebreak();
            txt(i18n::s.get("core.blending.recipe.warning"));
            Message::instance().linebreak();
            txt(i18n::s.get("core.blending.recipe.which"));
            if (const auto result = blending_menu_select_recipe())
            {
                return *result;
            }
            else
            {
                continue;
            }
        }
        else
        {
            rppage = 1;
            listmax = blendlist(list, rpid, step);
            sort_list_by_column1();

            windowshadow(1) = 1;
            Message::instance().linebreak();
            txt(i18n::s.get(
                "core.blending.steps.add_ingredient",
                get_recipe_material_name(rpid, step)));
            blendig_menu_select_materials();
        }
    }
}



void window_recipe2(int number_of_products)
{
    const auto dx = wx + ww - 120;
    const auto dy = 10;

    gmode(2);
    draw("deco_blend_a", dx, 0);

    font(15 - en * 2, snail::Font::Style::bold);
    bmes(
        i18n::s.get(
            "core.blending.rate_panel.success_rate",
            success_rate_to_string(calc_success_rate(rpid, step, -1))),
        dx + 160,
        dy,
        {235, 235, 235},
        {30, 30, 30});

    const auto& recipe_data = the_blending_recipe_db.ensure(rpid);
    std::string required_time;
    if (recipe_data.required_hours)
    {
        required_time = i18n::s.get(
            "core.blending.rate_panel.required_turns_and_hours",
            recipe_data.required_turns,
            recipe_data.required_hours * number_of_products);
    }
    else
    {
        required_time = i18n::s.get(
            "core.blending.rate_panel.required_turns",
            recipe_data.required_turns * number_of_products);
    }
    bmes(required_time, dx + 160, dy + 20, {235, 235, 235}, {40, 40, 40});
}

} // namespace elona

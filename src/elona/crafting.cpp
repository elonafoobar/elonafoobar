#include "crafting.hpp"
#include "ability.hpp"
#include "audio.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "config/config.hpp"
#include "draw.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "macro.hpp"
#include "message.hpp"
#include "random.hpp"
#include "ui.hpp"
#include "variables.hpp"

#include "ui/ui_menu_crafting.hpp"

namespace elona
{

void initialize_craft_material_data()
{
    DIM3(matref, 5, 400);
    DIM3(matspot, 5, 400);
    SDIM3(matname, 40, 400);
    SDIM3(matdesc, 80, 400);

    for (int cnt = 0; cnt < 55; cnt++)
    {
        matname(cnt) =
            i18n::s.get_enum_property("core.locale.material", "name", cnt);
        matdesc(cnt) =
            i18n::s.get_enum_property("core.locale.material", "desc", cnt);
    }

    matref(0, 0) = 0;
    matref(1, 0) = 1;
    matref(2, 0) = 240;
    matspot(0, 0) = 18;

    matref(0, 1) = 1;
    matref(1, 1) = 80;
    matref(2, 1) = 434;
    matspot(0, 1) = 18;

    matref(0, 40) = 1;
    matref(1, 40) = 200;
    matref(2, 40) = 437;
    matspot(0, 40) = 18;

    matref(0, 41) = 1;
    matref(1, 41) = 1000;
    matref(2, 41) = 437;
    matspot(0, 41) = 18;

    matref(0, 43) = 1;
    matref(1, 43) = 20;
    matref(2, 43) = 470;
    matspot(0, 43) = 18;

    matref(0, 2) = 1;
    matref(1, 2) = 10;
    matref(2, 2) = 239;
    matspot(0, 2) = 18;

    matref(0, 3) = 1;
    matref(1, 3) = 10;
    matref(2, 3) = 239;
    matspot(0, 3) = 18;

    matref(0, 48) = 1;
    matref(1, 48) = 10;
    matref(2, 48) = 209;
    matspot(0, 48) = 18;

    matref(0, 6) = 1;
    matref(1, 6) = 70;
    matref(2, 6) = 239;
    matspot(0, 6) = 18;

    matref(0, 45) = 3;
    matref(1, 45) = 20;
    matref(2, 45) = 155;
    matspot(0, 45) = 18;

    matref(0, 38) = 4;
    matref(1, 38) = 30;
    matref(2, 38) = 8;
    matspot(0, 38) = 18;

    matref(0, 30) = 10;
    matref(1, 30) = 150;
    matref(2, 30) = 7;
    matspot(0, 30) = 18;

    matref(0, 23) = 12;
    matref(1, 23) = 20;
    matref(2, 23) = 7;
    matspot(0, 23) = 18;

    matref(0, 44) = 25;
    matref(1, 44) = 150;
    matref(2, 44) = 7;
    matspot(0, 44) = 18;

    matref(0, 50) = 1;
    matref(1, 50) = 30;
    matref(2, 50) = 209;
    matspot(0, 50) = 9;

    matref(0, 46) = 2;
    matref(1, 46) = 20;
    matref(2, 46) = 239;
    matspot(0, 46) = 10;

    matref(0, 33) = 4;
    matref(1, 33) = 20;
    matref(2, 33) = 155;
    matspot(0, 33) = 10;

    matref(0, 53) = 6;
    matref(1, 53) = 20;
    matref(2, 53) = 202;
    matspot(0, 53) = 10;

    matref(0, 47) = 10;
    matref(1, 47) = 20;
    matref(2, 47) = 239;
    matspot(0, 47) = 10;

    matref(0, 37) = 12;
    matref(1, 37) = 60;
    matref(2, 37) = 471;
    matspot(0, 37) = 10;

    matref(0, 54) = 1;
    matref(1, 54) = 50;
    matref(2, 54) = 354;
    matspot(0, 54) = 12;

    matref(0, 49) = 5;
    matref(1, 49) = 50;
    matref(2, 49) = 150;
    matspot(0, 49) = 12;

    matref(0, 35) = 8;
    matref(1, 35) = 40;
    matref(2, 35) = 470;
    matspot(0, 35) = 12;

    matref(0, 36) = 8;
    matref(1, 36) = 40;
    matref(2, 36) = 354;
    matspot(0, 36) = 12;

    matref(0, 12) = 1;
    matref(1, 12) = 10;
    matref(2, 12) = 354;
    matspot(0, 12) = 13;

    matref(0, 5) = 1;
    matref(1, 5) = 10;
    matref(2, 5) = 354;
    matspot(0, 5) = 13;

    matref(0, 10) = 4;
    matref(1, 10) = 50;
    matref(2, 10) = 354;
    matspot(0, 10) = 13;

    matref(0, 25) = 4;
    matref(1, 25) = 20;
    matref(2, 25) = 354;
    matspot(0, 25) = 13;

    matref(0, 11) = 8;
    matref(1, 11) = 30;
    matref(2, 11) = 354;
    matspot(0, 11) = 13;

    matref(0, 20) = 12;
    matref(1, 20) = 15;
    matref(2, 20) = 7;
    matspot(0, 20) = 13;

    matref(0, 7) = 1;
    matref(1, 7) = 40;
    matref(2, 7) = 209;
    matspot(0, 7) = 14;

    matref(0, 9) = 1;
    matref(1, 9) = 10;
    matref(2, 9) = 209;
    matspot(0, 9) = 14;

    matref(0, 26) = 5;
    matref(1, 26) = 10;
    matref(2, 26) = 209;
    matspot(0, 26) = 14;

    matref(0, 27) = 5;
    matref(1, 27) = 10;
    matref(2, 27) = 209;
    matspot(0, 27) = 14;

    matref(0, 28) = 5;
    matref(1, 28) = 10;
    matref(2, 28) = 209;
    matspot(0, 28) = 14;

    matref(0, 52) = 8;
    matref(1, 52) = 50;
    matref(2, 52) = 209;
    matspot(0, 52) = 14;

    matref(0, 8) = 10;
    matref(1, 8) = 40;
    matref(2, 8) = 209;
    matspot(0, 8) = 14;

    matref(0, 22) = 20;
    matref(1, 22) = 100;
    matref(2, 22) = 209;
    matspot(0, 22) = 14;

    matref(0, 51) = 40;
    matref(1, 51) = 200;
    matref(2, 51) = 209;
    matspot(0, 51) = 14;

    matref(0, 13) = 1;
    matref(1, 13) = 10;
    matref(2, 13) = 170;
    matspot(0, 13) = 15;

    matref(0, 14) = 1;
    matref(1, 14) = 20;
    matref(2, 14) = 170;
    matspot(0, 14) = 15;

    matref(0, 15) = 1;
    matref(1, 15) = 20;
    matref(2, 15) = 170;
    matspot(0, 15) = 15;

    matref(0, 16) = 1;
    matref(1, 16) = 10;
    matref(2, 16) = 170;
    matspot(0, 16) = 15;

    matref(0, 42) = 3;
    matref(1, 42) = 20;
    matref(2, 42) = 170;
    matspot(0, 42) = 15;

    matref(0, 29) = 7;
    matref(1, 29) = 50;
    matref(2, 29) = 170;
    matspot(0, 29) = 15;

    matref(0, 17) = 12;
    matref(1, 17) = 20;
    matref(2, 17) = 170;
    matspot(0, 17) = 15;

    matref(0, 24) = 15;
    matref(1, 24) = 40;
    matref(2, 24) = 8;
    matspot(0, 24) = 15;

    matref(0, 34) = 25;
    matref(1, 34) = 200;
    matref(2, 34) = 354;
    matspot(0, 34) = 15;

    matspot(1, 34) = 10;
    matref(0, 4) = 1;
    matref(1, 4) = 10;
    matref(2, 4) = 436;
    matspot(0, 4) = 16;

    matref(0, 18) = 1;
    matref(1, 18) = 80;
    matref(2, 18) = 301;
    matspot(0, 18) = 16;

    matref(0, 31) = 1;
    matref(1, 31) = 20;
    matref(2, 31) = 304;
    matspot(0, 31) = 16;

    matref(0, 39) = 3;
    matref(1, 39) = 20;
    matref(2, 39) = 301;
    matspot(0, 39) = 16;

    matref(0, 19) = 5;
    matref(1, 19) = 15;
    matref(2, 19) = 304;
    matspot(0, 19) = 16;

    matref(0, 32) = 8;
    matref(1, 32) = 40;
    matref(2, 32) = 304;
    matspot(0, 32) = 16;

    matref(0, 21) = 15;
    matref(1, 21) = 45;
    matref(2, 21) = 209;
    matspot(0, 21) = 16;
}

// clang-format off
std::unordered_map<int, CraftingRecipe> recipes = {
    {502, {179, 40, {{35, 2}, {44, 2}, {51, 2}} }},
    {501, {179, 13, {{43, 2}, {44, 1}         } }},
    {500, {179, 1,  {{43, 2}, {38, 1}         } }},
    {455, {177, 1,  {{45, 4}, {53, 2}, {7,  3}} }},
    {411, {179, 5,  {{43, 4}, {36, 1}, {23, 2}} }},
    {408, {176, 11, {{47, 3}, {52, 2}, {21, 1}} }},
    {407, {178, 14, {{25, 4}, {20, 3}, {42, 1}} }},
    {405, {176, 15, {{48, 8}, {9,  5}, {52, 2}} }},
    {403, {176, 12, {{47, 5}, {16, 2}, {10, 1}} }},
    {402, {177, 5,  {{53, 7}, {45, 4}         } }},
    {401, {179, 14, {{3,  8}, {53, 4}, {21, 1}} }},
    {400, {176, 8,  {{3,  6}, {46, 4}, {2,  4}} }},
    {399, {177, 8,  {{45, 5}, {33, 2}, {20, 2}} }},
    {395, {179, 30, {{43, 5}, {30, 1}, {44, 1}} }},
    {390, {179, 25, {{35, 1}, {36, 2}, {30, 2}} }},
    {389, {179, 25, {{35, 2}, {36, 2}, {17, 4}} }},
    {388, {179, 15, {{35, 1}, {17, 2}, {23, 3}} }},
    {384, {179, 15, {{35, 2}, {17, 4}, {16, 4}} }},
    {362, {179, 18, {{35, 1}, {49, 2}, {30, 1}} }},
    {287, {178, 45, {{34, 2}, {10, 5}, {25, 4}} }},
    {286, {178, 8,  {{25, 4}, {14, 4}         } }},
    {285, {178, 8,  {{25, 4}, {15, 4}         } }},
    {253, {178, 1,  {{5,  4}                  } }},
    {245, {179, 1,  {{43, 2}, {2,  2}, {4,  2}} }},
    {242, {179, 10, {{35, 1}, {36, 1}, {23, 3}} }},
    {236, {179, 4,  {{43, 3}, {13, 2}, {2,  2}} }},
    {209, {179, 8,  {{43, 4}, {17, 2}, {16, 2}} }},
    {175, {176, 17, {{37, 1}, {28, 5}, {54, 1}} }},
    {123, {176, 14, {{37, 1}, {26, 5}, {50, 2}} }},
    {122, {176, 14, {{37, 1}, {27, 5}, {20, 5}} }},
    {120, {176, 1,  {{6,  1}, {9,  4}, {50, 2}} }},
    {119, {176, 1,  {{6,  1}, {14, 4}, {54, 1}} }},
    {76,  {178, 40, {{34, 2}, {5,  5}, {42, 4}} }},
    {75,  {178, 30, {{34, 1}, {25, 4}, {14, 5}} }},
    {74,  {178, 25, {{15, 3}, {25, 4}, {42, 3}} }},
    {72,  {178, 20, {{10, 1}, {5,  4}, {42, 2}} }},
    {71,  {178, 15, {{25, 3}, {42, 2}         } }},
    {70,  {178, 10, {{25, 3}, {14, 1}, {15, 1}} }},
    {69,  {178, 5,  {{5,  3}, {15, 2}         } }},
    {68,  {178, 1,  {{5,  3}, {14, 1}         } }},
    {66,  {177, 8,  {{33, 4}, {39, 5}, {18, 2}} }},
    {65,  {177, 10, {{33, 5}, {54, 3}, {31, 6}} }},
    {19,  {176, 5,  {{6,  1}, {4,  4}, {29, 2}} }},
    {18,  {176, 8,  {{6,  1}, {32, 2}, {49, 2}} }},
    {16,  {179, 7,  {{43, 3}, {2,  2}, {4,  3}} }},
    {14,  {179, 1,  {{43, 2}, {49, 1}         } }},
    {8,   {177, 4,  {{45, 6}, {53, 3}, {50, 2}} }},
};
// clang-format on

optional<const CraftingRecipe&> crafting_find_recipe(int matid_)
{
    auto it = recipes.find(matid_);

    if (it == recipes.end())
    {
        return none;
    }

    return it->second;
}

static Quality _determine_crafted_fixlv(const CraftingRecipe& recipe)
{
    Quality ret = Quality::good;
    if (rnd(200 + recipe.required_skill_level * 2) <
        sdata(recipe.skill_used, 0) + 20)
    {
        ret = Quality::miracle;
    }
    if (rnd(100 + recipe.required_skill_level * 2) <
        sdata(recipe.skill_used, 0) + 20)
    {
        ret = Quality::great;
    }

    return ret;
}

static void _craft_item(int matid, const CraftingRecipe& recipe)
{
    fixlv = _determine_crafted_fixlv(recipe);
    flt(calcobjlv(sdata(recipe.skill_used, 0)), calcfixlv(fixlv));
    nostack = 1;
    itemcreate(0, matid, -1, -1, 0);
    txt(i18n::s.get("core.locale.crafting.you_crafted", inv[ci]));
    item_stack(0, ci, 0);
}

void crafting_menu()
{
    while (true)
    {
        auto result = ui::UIMenuCrafting(prodtype, invctrl).show();

        if (!result.canceled && result.value)
        {
            int matid = *result.value;
            auto recipe = crafting_find_recipe(matid);
            assert(recipe);

            int matuse = 0;
            for (const auto& required_mat : recipe->required_materials)
            {
                mat(required_mat.id) -= required_mat.amount;
                matuse += required_mat.amount;
            }

            snd("core.build1");
            _craft_item(matid, *recipe);

            r2 = matuse;
            chara_gain_exp_crafting(cdata.player(), recipe->skill_used, matuse);
            chara_refresh(0);

            // NOTE: page_load is called in UIMenuCrafting.
            render_hud();
            page_save();
        }
        else if (result.canceled)
        {
            break;
        }
    }
}



} // namespace elona

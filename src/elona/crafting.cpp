#include "crafting.hpp"

#include "ability.hpp"
#include "audio.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "config.hpp"
#include "data/types/type_crafting_material.hpp"
#include "draw.hpp"
#include "game.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "inventory.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "message.hpp"
#include "random.hpp"
#include "ui.hpp"
#include "ui/ui_menu_crafting.hpp"
#include "variables.hpp"



namespace elona
{

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

optional_ref<const CraftingRecipe> crafting_find_recipe(int matid_)
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
        cdata.player().get_skill(recipe.skill_used).level + 20)
    {
        ret = Quality::miracle;
    }
    if (rnd(100 + recipe.required_skill_level * 2) <
        cdata.player().get_skill(recipe.skill_used).level + 20)
    {
        ret = Quality::great;
    }

    return ret;
}



static void _craft_item(int matid, const CraftingRecipe& recipe)
{
    fixlv = _determine_crafted_fixlv(recipe);
    flt(calcobjlv(cdata.player().get_skill(recipe.skill_used).level),
        calcfixlv(fixlv));
    nostack = 1;
    if (const auto item = itemcreate_player_inv(matid, 0))
    {
        txt(i18n::s.get("core.crafting.you_crafted", item.unwrap()));
        inv_stack(inv_player(), item.unwrap());
    }
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
                game()->crafting_materials().lose(
                    *the_crafting_material_db.get_id_from_integer(
                        required_mat.id),
                    required_mat.amount);
                matuse += required_mat.amount;
            }

            snd("core.build1");
            _craft_item(matid, *recipe);

            r2 = matuse;
            chara_gain_exp_crafting(cdata.player(), recipe->skill_used, matuse);
            chara_refresh(cdata.player());

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

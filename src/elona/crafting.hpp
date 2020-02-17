#pragma once
#include <vector>

#include "optional.hpp"

namespace elona
{

struct RequiredMaterial
{
    RequiredMaterial(int id, int amount)
        : id(id)
        , amount(amount)
    {
    }

    int id;
    int amount;
};

struct CraftingRecipe
{
    CraftingRecipe(
        int skill_used,
        int required_skill_level,
        std::vector<RequiredMaterial> required_materials)
        : skill_used(skill_used)
        , required_skill_level(required_skill_level)
        , required_materials(required_materials)
    {
    }

    int skill_used;
    int required_skill_level;
    // matval(2) = 100
    std::vector<RequiredMaterial> required_materials;
};

void initialize_craft_material_data();
void crafting_menu();
optional<const CraftingRecipe&> crafting_find_recipe(int matid);

} // namespace elona

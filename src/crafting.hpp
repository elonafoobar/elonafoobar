#pragma once
#include <vector>
#include "optional.hpp"

namespace elona
{

struct required_material
{
    required_material(int id, int amount)
        : id(id)
        , amount(amount)
    {
    }

    int id;
    int amount;
};

struct crafting_recipe
{
    crafting_recipe(
        int skill_used,
        int required_skill_level,
        std::vector<required_material> required_materials)
        : skill_used(skill_used)
        , required_skill_level(required_skill_level)
        , required_materials(required_materials)
    {
    }

    int skill_used;
    int required_skill_level;
    // matval(2) = 100
    std::vector<required_material> required_materials;
};

void initialize_craft_material_data();
void crafting_menu();
optional<const crafting_recipe&> crafting_find_recipe(int matid);

} // namespace elona

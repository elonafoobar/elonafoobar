#pragma once

#include "data/id.hpp"



namespace elona
{

/**
 * Get the crafting material of @a id.
 *
 * @param id The crafting material ID
 * @param amount The amount to be gained
 * @param spot_type The material spot type
 */
void crafting_material_gain(data::InstanceId id, int amount, int spot_type = 0);


/**
 * Lose the crafting material of @a id.
 *
 * @param id The crafting material ID
 * @param amount The amount to be lost
 */
void crafting_material_lose(data::InstanceId id, int amount);


/**
 * Select a crafting material ID at random with the given @a level, @a rarity
 * and @a spot_type.
 *
 * @param level The crafting material level
 * @param rarity The crafting material rarity
 * @param spot_type The material spot type
 * @return The selected crafting material ID
 */
data::InstanceId
crafting_material_select_random_id(int level, int rarity, int spot_type);

} // namespace elona

#pragma once

#include <unordered_map>

#include "data/id.hpp"
#include "typedefs.hpp"



namespace elona
{

template <typename T>
struct elona_vector1;



/**
 * Crafting material bag.
 */
struct CraftingMaterialBag
{
    /**
     * Gets the amount of the crafting material of @a id.
     *
     * @param id The crafting material ID
     * @return The amount of the crafting material
     */
    lua_int amount(data::InstanceId id) const noexcept
    {
        if (const auto itr = _materials.find(id); itr != _materials.end())
        {
            return itr->second;
        }
        else
        {
            return 0;
        }
    }



    /**
     * Sets the amount of the crafting material of @a id with the given @a
     * new_amount. If @a new_amount is negative, the amount is set to zero.
     *
     * @param id The crafting material ID
     * @param new_amount The new amount of the crafting material
     */
    void set_amount(data::InstanceId id, lua_int new_amount)
    {
        if (new_amount == 0 && _materials.find(id) == _materials.end())
            return;

        _materials[id] = std::max(new_amount, lua_int{0});
    }



    /**
     * Adds the amount of the crafting material of @a id by the given amount @a
     * change_amount.
     *
     * @param id The crafting material ID
     * @param change_amount The change amount to be added
     */
    void gain(data::InstanceId id, lua_int change_amount)
    {
        if (change_amount == 0)
            return;

        // TODO: potential overflow
        _materials[id] += change_amount;
    }



    /**
     * Subtracts the amount of the crafting material of @a id by the given
     * amount @a change_amount.
     *
     * @param id The crafting material ID
     * @param change_amount The change amount to be subtracted
     */
    void lose(data::InstanceId id, lua_int change_amount)
    {
        // TODO: potential overflow
        gain(id, -change_amount);
    }



    /**
     * Lose all materials.
     */
    void clear()
    {
        _materials.clear();
    }



private:
    std::unordered_map<data::InstanceId, lua_int> _materials;
};



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

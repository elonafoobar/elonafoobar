#pragma once

#include <unordered_map>

#include "data/id.hpp"
#include "data/types/type_trait.hpp"
#include "typedefs.hpp"



namespace elona
{

template <typename T>
struct elona_vector1;

struct Character;



/**
 * A table from trait ID to trait level.
 */
struct TraitLevelTable
{
    /**
     * Gets the level of @a trait_id.
     *
     * @param trait_id The trait ID
     * @return The level of the trait
     */
    lua_int level(data::InstanceId trait_id) const noexcept
    {
        if (const auto itr = _traits.find(trait_id); itr != _traits.end())
        {
            return itr->second;
        }
        else
        {
            return 0;
        }
    }



    /**
     * Sets the level of @a trait_id with the given @a new_level.
     *
     * @param trait_id The trait ID
     * @param new_level The new level of the trait
     */
    void set_level(data::InstanceId trait_id, lua_int new_level)
    {
        if (new_level == 0 && _traits.find(trait_id) == _traits.end())
            return;

        _traits[trait_id] = new_level;
    }



    /**
     * Adds the level of @a trait_id by the given amount @a change.
     *
     * @param trait_id The trait ID
     * @param change The change to be added
     */
    void add(data::InstanceId trait_id, lua_int change)
    {
        if (change == 0)
            return;

        // FIXME: potential overflow
        _traits[trait_id] += change;
    }



    /**
     * Subtracts the level of @a trait_id by the given level @a change.
     *
     * @param trait_id The trait ID
     * @param change The change to be subtracted
     */
    void sub(data::InstanceId trait_id, lua_int change)
    {
        // FIXME: potential overflow
        add(trait_id, -change);
    }



    /**
     * Clear all traits.
     */
    void clear() noexcept
    {
        _traits.clear();
    }



private:
    std::unordered_map<data::InstanceId, lua_int> _traits;
};



int trait_get_info(int traitmode, int tid);
void trait_load_desc(Character& chara);

void clear_trait_data();

void trait_progress_ether_disease_stage(Character& chara, lua_int delta);

} // namespace elona

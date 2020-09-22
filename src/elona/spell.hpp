#pragma once

#include <unordered_map>

#include "data/id.hpp"
#include "typedefs.hpp"



namespace elona
{

template <typename T>
struct elona_vector1;



/**
 * A table from spell ID to spell stock.
 */
struct SpellStockTable
{
    /**
     * Gets the amount of the spell stock of @a id.
     *
     * @param id The spell ID
     * @return The amount of the spell stock
     */
    lua_int amount(data::InstanceId id) const noexcept
    {
        if (const auto itr = _stocks.find(id); itr != _stocks.end())
        {
            return itr->second;
        }
        else
        {
            return 0;
        }
    }



    /**
     * Sets the amount of the spell stock of @a id with the given @a
     * new_amount. If @a new_amount is negative, the amount is set to zero.
     *
     * @param id The spell ID
     * @param new_amount The new amount of the spell stock
     */
    void set_amount(data::InstanceId id, lua_int new_amount)
    {
        if (new_amount == 0 && _stocks.find(id) == _stocks.end())
            return;

        _stocks[id] = std::max(new_amount, lua_int{0});
    }



    /**
     * Adds the amount of the spell stock of @a id by the given amount @a
     * change_amount.
     *
     * @param id The spell ID
     * @param change_amount The change amount to be added
     */
    void gain(data::InstanceId id, lua_int change_amount)
    {
        if (change_amount == 0)
            return;

        // TODO: potential overflow
        _stocks[id] += change_amount;
    }



    /**
     * Subtracts the amount of the spell stock of @a id by the given
     * amount @a change_amount.
     *
     * @param id The spell ID
     * @param change_amount The change amount to be subtracted
     */
    void lose(data::InstanceId id, lua_int change_amount)
    {
        // TODO: potential overflow
        gain(id, -change_amount);
    }



    // for integration with legacy codebase.
    void pack_to(elona_vector1<int>& legacy_spell) const;
    void unpack_from(elona_vector1<int>& legacy_spell);



private:
    std::unordered_map<data::InstanceId, lua_int> _stocks;
};

} // namespace elona

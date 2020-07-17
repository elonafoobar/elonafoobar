#pragma once

#include "item.hpp"
#include "optional.hpp"



namespace elona
{

/**
 * Calculate the sum of item weight excluding cargo goods.
 *
 * @param inv The inventory to calculate weight.
 * @return The sum of item weight.
 */
int inv_weight(Inventory& inv);


/**
 * Calculate the sum of cargo item's weight.
 *
 * @param inv The inventory to calculate weight.
 * @return The sum of cargo item's weight.
 */
int inv_cargo_weight(Inventory& inv);


/**
 * Get a free slot of @a inv. If @a inv has no free slot, returns none.
 *
 * @param inv The inventory to query.
 * @return The free slot.
 */
optional<InventorySlot> inv_get_free_slot(Inventory& inv);


/**
 * Make a free slot in @a inv. For character's inventory, if @a inv has no free
 * slot, returns none. For map inventory, if @a inv has no free slot, call @ref
 * inv_make_free_slot_force().
 *
 * @param inv The inventory.
 * @return The free slot.
 */
optional<InventorySlot> inv_make_free_slot(Inventory& inv);


/**
 * Force to make a free slot in @a inv. If @a inv has no free slot, force to
 * make a free slot.
 *
 * @param inv The inventory.
 * @return The free slot.
 */
InventorySlot inv_make_free_slot_force(Inventory& inv);


/**
 * Count the number of items in @a inv.
 *
 * @param inv The inventory to count.
 * @return The number of items @a inv has.
 */
int inv_count(Inventory& inv);


/**
 * Remove some items in @a inv to make a free slot.
 *
 * @param inv The inventory to compress.
 * @return The free slot created by the compression.
 */
InventorySlot inv_compress(Inventory& inv);


/**
 * Get an item slot at random. The slot can be empty.
 *
 * @param inv The inventory.
 * @return An item slot in @a inv.
 */
InventorySlot inv_get_random_slot(Inventory& inv);


/**
 * Find an item from @a inv with the given @a predicate. (1-arity version)
 *
 * @param inv The inventory to search.
 * @param predicate The predicate which is expected to take an item and return
 * true if matched.
 * @return The first match or null.
 */
template <
    typename F,
    std::enable_if_t<std::is_invocable_v<F, const ItemRef&>, std::nullptr_t> =
        nullptr>
OptionalItemRef inv_find(Inventory& inv, F predicate)
{
    for (const auto& item : inv)
    {
        if (predicate(item))
        {
            return item;
        }
    }
    return nullptr;
}


/**
 * Find an item from @a inv with the given @a predicate. (2-arity version)
 *
 * @param inv The inventory to search.
 * @param predicate The predicate which is expected to take an item and @a inv,
 * and return true if matched. (predicate :: Item -> Inventory -> bool)
 * @return The first match or null.
 */
template <
    typename F,
    std::enable_if_t<
        std::is_invocable_v<F, const ItemRef&, Inventory&>,
        std::nullptr_t> = nullptr>
OptionalItemRef inv_find(Inventory& inv, F predicate)
{
    for (const auto& item : inv)
    {
        if (predicate(item, inv))
        {
            return item;
        }
    }
    return nullptr;
}


/**
 * Find an item from @a inv with the given @a predicate. (1-arity version)
 *
 * @param inv The inventory to search.
 * @param predicate The predicate which is expected to take an item and return
 * true if matched.
 * @return The last match or null.
 */
template <
    typename F,
    std::enable_if_t<std::is_invocable_v<F, const ItemRef&>, std::nullptr_t> =
        nullptr>
OptionalItemRef inv_find_last_match(Inventory& inv, F predicate)
{
    OptionalItemRef result;
    for (const auto& item : inv)
    {
        if (predicate(item))
        {
            result = item;
        }
    }
    return result;
}


/**
 * Find an item from @a inv with the given @a predicate. (2-arity version)
 *
 * @param inv The inventory to search.
 * @param predicate The predicate which is expected to take an item and @a inv,
 * and return true if matched. (predicate :: Item -> Inventory -> bool)
 * @return The last match or null.
 */
template <
    typename F,
    std::enable_if_t<
        std::is_invocable_v<F, const ItemRef&, Inventory&>,
        std::nullptr_t> = nullptr>
OptionalItemRef inv_find_last_match(Inventory& inv, F predicate)
{
    OptionalItemRef result;
    for (const auto& item : inv)
    {
        if (predicate(item, inv))
        {
            result = item;
        }
    }
    return result;
}

} // namespace elona

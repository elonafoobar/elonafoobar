#pragma once

#include "item.hpp"
#include "optional.hpp"



namespace elona
{

/**
 * Helper function to access the player character's inventory. It is equivalent
 * to `cdata.player().inventory()`.
 *
 * @return The player character's inventory.
 */
InventoryRef inv_player();


/**
 * Helper function to access the current map's inventory.
 *
 * @return The current map's inventory.
 */
InventoryRef inv_map();


/**
 * Calculate the sum of item weight excluding cargo goods.
 *
 * @param inv The inventory to calculate weight.
 * @return The sum of item weight.
 */
lua_int inv_weight(const InventoryRef& inv);


/**
 * Calculate the sum of cargo item's weight.
 *
 * @param inv The inventory to calculate weight.
 * @return The sum of cargo item's weight.
 */
lua_int inv_cargo_weight(const InventoryRef& inv);


/**
 * Get a free slot of @a inv. If @a inv has no free slot, returns none.
 *
 * @param inv The inventory to query.
 * @return The free slot.
 */
optional<InventorySlot> inv_get_free_slot(const InventoryRef& inv);


/**
 * Make a free slot in @a inv. For character's inventory, if @a inv has no free
 * slot, returns none. For map inventory, if @a inv has no free slot, call @ref
 * inv_make_free_slot_force().
 *
 * @param inv The inventory.
 * @return The free slot.
 */
optional<InventorySlot> inv_make_free_slot(const InventoryRef& inv);


/**
 * Force to make a free slot in @a inv. If @a inv has no free slot, force to
 * make a free slot.
 *
 * @param inv The inventory.
 * @return The free slot.
 */
InventorySlot inv_make_free_slot_force(const InventoryRef& inv);


/**
 * Count the number of items in @a inv.
 *
 * @param inv The inventory to count.
 * @return The number of items @a inv has.
 */
lua_int inv_count(const InventoryRef& inv);


/**
 * Get an owner of @a inv.
 *
 * @param inv The inventory to query.
 * @return @a inv's owner.
 */
ItemOwner inv_get_owner(const InventoryRef& inv);


/**
 * Remove some items in @a inv to make a free slot.
 *
 * @param inv The inventory to compress.
 * @return The free slot created by the compression.
 */
InventorySlot inv_compress(const InventoryRef& inv);


/**
 * Get an item slot at random. The slot can be empty.
 *
 * @param inv The inventory.
 * @return An item slot in @a inv.
 */
InventorySlot inv_get_random_slot(const InventoryRef& inv);


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
OptionalItemRef inv_find(const InventoryRef& inv, F predicate)
{
    for (const auto& item : *inv)
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
        std::is_invocable_v<F, const ItemRef&, const InventoryRef&>,
        std::nullptr_t> = nullptr>
OptionalItemRef inv_find(const InventoryRef& inv, F predicate)
{
    for (const auto& item : *inv)
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
OptionalItemRef inv_find_last_match(const InventoryRef& inv, F predicate)
{
    OptionalItemRef result;
    for (const auto& item : *inv)
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
        std::is_invocable_v<F, const ItemRef&, const InventoryRef&>,
        std::nullptr_t> = nullptr>
OptionalItemRef inv_find_last_match(const InventoryRef& inv, F predicate)
{
    OptionalItemRef result;
    for (const auto& item : *inv)
    {
        if (predicate(item, inv))
        {
            result = item;
        }
    }
    return result;
}



/**
 * Result of @ref inv_stack.
 */
struct InvStackResult
{
    // If `stacked` is false, `stacked_item` is set to `base_item`.
    bool stacked;
    ItemRef stacked_item;
};

/**
 * Try to stack @a inv with @a base_item.
 */
InvStackResult inv_stack(
    const InventoryRef& inv,
    const ItemRef& base_item,
    bool show_message = false,
    optional<lua_int> number = none);



/**
 * Open a temporary inventory. All items stored in @a file_name are read into
 * `g_inv.tmp()`.
 *
 * @param file_name The file name which stores a temporary inventory.
 * @see inv_close_tmp_inv
 */
void inv_open_tmp_inv(const fs::path& file_name);



/**
 * Close a temporary inventory. All items stored in `g_inv.tmp()` are written
 * into @a file_name.
 *
 * @param file_name The file name where a temporary inventory is written.
 * @see inv_open_tmp_inv
 */
void inv_close_tmp_inv(const fs::path& file_name);



/**
 * Create an empty temporary inventory.
 *
 * @see inv_close_tmp_inv_no_physical_file
 */
void inv_open_tmp_inv_no_physical_file();



/**
 * Close a temporary inventory. All items stored in `g_inv.tmp()` are discarded.
 *
 * @see inv_open_tmp_inv_no_physical_file
 */
void inv_close_tmp_inv_no_physical_file();

} // namespace elona

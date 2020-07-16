#include "inventory.hpp"

#include "character.hpp"
#include "random.hpp"



namespace elona
{

int inv_weight(int owner)
{
    int weight{};
    if (owner == 0)
    {
        game_data.cargo_weight = 0;
    }
    for (const auto& item : g_inv.by_index(owner))
    {
        if (item->weight >= 0)
        {
            weight += item->weight * item->number();
        }
        else if (owner == 0)
        {
            game_data.cargo_weight += -item->weight * item->number();
        }
    }
    return weight;
}



optional<InventorySlot> inv_get_free_slot(int inventory_id)
{
    return g_inv.by_index(inventory_id).get_free_slot();
}



optional<InventorySlot> inv_make_free_slot(int inventory_id)
{
    if (inventory_id == -1 && mode != 6)
    {
        return inv_make_free_slot_force(inventory_id);
    }
    else
    {
        return inv_get_free_slot(inventory_id);
    }
}



InventorySlot inv_make_free_slot_force(int inventory_id)
{
    if (const auto slot = inv_get_free_slot(inventory_id))
    {
        return *slot;
    }

    if (inventory_id == -1)
    {
        assert(mode != 6);
        txt(i18n::s.get("core.item.items_are_destroyed"));
        return inv_compress(inventory_id);
    }

    while (true)
    {
        const auto slot = inv_get_random_slot(inventory_id);
        const auto item = Inventory::at(slot).unwrap();
        if (item->body_part == 0)
        {
            if (cdata[inventory_id].ai_item == item)
            {
                cdata[inventory_id].ai_item = nullptr;
            }
            item->remove();
            return slot;
        }
    }
}



bool inv_has_free_slot(int owner)
{
    return g_inv.by_index(owner).has_free_slot();
}



int inv_sum(int owner)
{
    int n{};
    for (const auto& _item : g_inv.by_index(owner))
    {
        (void)_item;
        ++n;
    }
    return n;
}



InventorySlot inv_compress(int owner)
{
    int number_of_deleted_items{};
    for (int i = 0; i < 100; ++i)
    {
        int threshold = 200 * (i * i + 1);
        for (const auto& item : g_inv.by_index(owner))
        {
            if (!item->is_precious() && item->value < threshold)
            {
                item->remove();
                ++number_of_deleted_items;
            }
            if (number_of_deleted_items > 10)
            {
                break;
            }
        }
        if (number_of_deleted_items > 10)
        {
            break;
        }
    }

    if (const auto free_slot = g_inv.by_index(owner).get_free_slot())
    {
        return *free_slot;
    }

    // Destroy 1 existing item forcely.
    const auto slot = inv_get_random_slot(owner);
    Inventory::at(slot)->remove();

    return slot;
}



InventorySlot inv_get_random_slot(int owner)
{
    auto& inv = g_inv.by_index(owner);
    const auto index = rnd(inv.size());
    return {&inv, index};
}

} // namespace elona

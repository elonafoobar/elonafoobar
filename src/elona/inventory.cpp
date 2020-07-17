#include "inventory.hpp"

#include "character.hpp"
#include "random.hpp"



namespace elona
{

int inv_weight(Inventory& inv)
{
    int weight{};
    for (const auto& item : inv)
    {
        if (item->weight >= 0)
        {
            weight += item->weight * item->number();
        }
    }
    return weight;
}



int inv_cargo_weight(Inventory& inv)
{
    int weight{};
    for (const auto& item : inv)
    {
        if (item->weight < 0)
        {
            weight += -item->weight * item->number();
        }
    }
    return weight;
}



optional<InventorySlot> inv_get_free_slot(Inventory& inv)
{
    return inv.get_free_slot();
}



optional<InventorySlot> inv_make_free_slot(Inventory& inv)
{
    if (inv.inventory_id() == -1 && mode != 6)
    {
        return inv_make_free_slot_force(inv);
    }
    else
    {
        return inv_get_free_slot(inv);
    }
}



InventorySlot inv_make_free_slot_force(Inventory& inv)
{
    if (const auto slot = inv_get_free_slot(inv))
    {
        return *slot;
    }

    if (inv.inventory_id() == -1)
    {
        assert(mode != 6);
        txt(i18n::s.get("core.item.items_are_destroyed"));
        return inv_compress(inv);
    }

    while (true)
    {
        const auto slot = inv_get_random_slot(inv);
        const auto item = Inventory::at(slot).unwrap();
        if (item->body_part == 0)
        {
            if (cdata[inv.inventory_id()].ai_item == item)
            {
                cdata[inv.inventory_id()].ai_item = nullptr;
            }
            item->remove();
            return slot;
        }
    }
}



int inv_count(Inventory& inv)
{
    int n{};
    for (const auto& _item : inv)
    {
        (void)_item;
        ++n;
    }
    return n;
}



InventorySlot inv_compress(Inventory& inv)
{
    int number_of_deleted_items{};
    for (int i = 0; i < 100; ++i)
    {
        int threshold = 200 * (i * i + 1);
        for (const auto& item : inv)
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

    if (const auto free_slot = inv.get_free_slot())
    {
        return *free_slot;
    }

    // Destroy 1 existing item forcely.
    const auto slot = inv_get_random_slot(inv);
    Inventory::at(slot)->remove();

    return slot;
}



InventorySlot inv_get_random_slot(Inventory& inv)
{
    const auto index = rnd(inv.size());
    return {&inv, index};
}

} // namespace elona

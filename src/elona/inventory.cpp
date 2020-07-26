#include "inventory.hpp"

#include "character.hpp"
#include "ctrl_file.hpp"
#include "random.hpp"
#include "save_fs.hpp"



namespace elona
{

namespace
{

bool is_nonstackable(const ItemRef& item)
{
    return item->quality == Quality::special &&
        is_equipment(the_item_db[itemid2int(item->id)]->category);
}



bool is_stackable_with(const ItemRef& item, const ItemRef& base_item)
{
    const auto ignore_position = !item_get_owner(item).is_map();
    if (item->id == ItemId::small_medal)
    {
        return ignore_position || item->pos() == base_item->pos();
    }
    else
    {
        return item->almost_equals(*base_item.get_raw_ptr(), ignore_position);
    }
}

} // namespace



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
    if (inv_get_owner(inv).is_map())
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

    auto owner = inv_get_owner(inv);
    if (owner.is_map())
    {
        txt(i18n::s.get("core.item.items_are_destroyed"));
        return inv_compress(inv);
    }

    while (true)
    {
        const auto slot = inv_get_random_slot(inv);
        const auto item = Inventory::at(slot).unwrap();
        const auto owner_chara = owner.as_character();
        assert(owner_chara);
        if (item->body_part == 0)
        {
            if (owner_chara->ai_item == item)
            {
                owner_chara->ai_item = nullptr;
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



ItemOwner inv_get_owner(Inventory& inv)
{
    if (inv.inventory_id() == -1)
    {
        return ItemOwner::map();
    }
    else if (inv.inventory_id() == 255)
    {
        return ItemOwner::temporary();
    }
    else
    {
        return ItemOwner::character(cdata[inv.inventory_id()]);
    }
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



InvStackResult inv_stack(
    Inventory& inv,
    const ItemRef& base_item,
    bool show_message,
    optional<int> number)
{
    if (is_nonstackable(base_item))
    {
        return {false, base_item};
    }

    for (const auto& item : inv)
    {
        if (item == base_item || item->id != base_item->id)
            continue;

        if (is_stackable_with(item, base_item))
        {
            const auto num = number.value_or(base_item->number());
            item->modify_number(num);
            base_item->modify_number(-num);

            if (show_message)
            {
                txt(i18n::s.get("core.item.stacked", item, item->number()));
            }
            return {true, item};
        }
    }

    return {false, base_item};
}



void inv_open_tmp_inv(const fs::path& file_name)
{
    if (save_fs_exists(file_name))
    {
        ctrl_file_tmp_inv_read(file_name);
    }
    else
    {
        g_inv.tmp().clear();
    }
}



void inv_close_tmp_inv(const fs::path& file_name)
{
    ctrl_file_tmp_inv_write(file_name);
    g_inv.tmp().clear();
}



void inv_open_tmp_inv_no_physical_file()
{
    g_inv.tmp().clear();
}



void inv_close_tmp_inv_no_physical_file()
{
    g_inv.tmp().clear();
}

} // namespace elona

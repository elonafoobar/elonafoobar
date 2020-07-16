#pragma once

#include "item.hpp"
#include "optional.hpp"



namespace elona
{

int inv_weight(int = 0);
optional<InventorySlot> inv_get_free_slot(int inventory_id);
optional<InventorySlot> inv_make_free_slot(int inventory_id);
InventorySlot inv_make_free_slot_force(int inventory_id);
bool inv_has_free_slot(int);
int inv_sum(int = 0);
InventorySlot inv_compress(int owner);
InventorySlot inv_get_random_slot(int owner);

} // namespace elona

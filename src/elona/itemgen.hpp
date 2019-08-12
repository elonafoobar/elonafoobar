#pragma once

#include "optional.hpp"



namespace elona
{

struct Item;



optional<int> itemcreate(int = 0, int = 0, int = 0, int = 0, int = 0);
void get_random_item_id();
optional<int> do_create_item(int, int, int);
void init_item_quality_curse_state_material_and_equipments(Item&);
void calc_furniture_value(Item&);
void initialize_item_material(Item&);
void determine_item_material(Item&);
void change_item_material(Item&, int);
void apply_item_material(Item&);
void set_material_specific_attributes(Item&);

} // namespace elona

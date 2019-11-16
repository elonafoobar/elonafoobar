#pragma once

#include "optional.hpp"



namespace elona
{

struct Item;
struct Position;



optional_ref<Item> itemcreate(int slot, int id, int x, int y, int number = 0);

optional_ref<Item>
itemcreate(int slot, int id, const Position& pos, int number = 0);

optional_ref<Item> itemcreate_player_inv(int id, int number = 0);

optional_ref<Item>
itemcreate_chara_inv(int chara_index, int id, int number = 0);

optional_ref<Item> itemcreate_extra_inv(int id, int x, int y, int number = 0);

optional_ref<Item>
itemcreate_extra_inv(int id, const Position& pos, int number = 0);


void get_random_item_id();
void init_item_quality_curse_state_material_and_equipments(Item&);
void calc_furniture_value(Item&);
void initialize_item_material(Item&);
void determine_item_material(Item&);
void change_item_material(Item&, int);
void apply_item_material(Item&);
void set_material_specific_attributes(Item&);

} // namespace elona

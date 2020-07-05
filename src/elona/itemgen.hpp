#pragma once

#include "eobject/eobject.hpp"
#include "optional.hpp"
#include "randomgen.hpp"



namespace elona
{

struct Item;
struct Position;



OptionalItemRef itemcreate(int slot, int id, int x, int y, int number = 0);

OptionalItemRef
itemcreate(int slot, int id, const Position& pos, int number = 0);

OptionalItemRef itemcreate_player_inv(int id, int number = 0);

OptionalItemRef itemcreate_chara_inv(int chara_index, int id, int number = 0);

OptionalItemRef itemcreate_extra_inv(int id, int x, int y, int number = 0);

OptionalItemRef
itemcreate_extra_inv(int id, const Position& pos, int number = 0);


int get_random_item_id();
void init_item_quality_curse_state_material_and_equipments(const ItemRef&);
void calc_furniture_value(const ItemRef&);
void initialize_item_material(const ItemRef&);
void determine_item_material(const ItemRef&);
void change_item_material(const ItemRef&, int);
void apply_item_material(const ItemRef&);
void set_material_specific_attributes(const ItemRef&);

int discsetmc();

} // namespace elona

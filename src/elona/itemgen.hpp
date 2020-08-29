#pragma once

#include "data/id.hpp"
#include "eobject/forward.hpp"
#include "optional.hpp"
#include "randomgen.hpp"



namespace elona
{

struct Inventory;
struct Item;
struct Character;
struct Position;



OptionalItemRef
itemcreate(Inventory& inv, int id, int x, int y, int number = 0);

OptionalItemRef
itemcreate(Inventory& inv, int id, const Position& pos, int number = 0);

OptionalItemRef itemcreate_player_inv(int id, int number = 0);

OptionalItemRef itemcreate_chara_inv(Character& chara, int id, int number = 0);

OptionalItemRef itemcreate_map_inv(int id, int x, int y, int number = 0);

OptionalItemRef itemcreate_map_inv(int id, const Position& pos, int number = 0);

OptionalItemRef itemcreate_tmp_inv(int id, int number = 0);


int get_random_item_id();
void init_item_quality_curse_state_material_and_equipments(const ItemRef&);
void calc_furniture_value(const ItemRef&);
void initialize_item_material(const ItemRef&);
void determine_item_material(const ItemRef&);
void change_item_material(const ItemRef&, data::InstanceId material);
void apply_item_material(const ItemRef&);
void set_material_specific_attributes(const ItemRef&);

int discsetmc();

} // namespace elona

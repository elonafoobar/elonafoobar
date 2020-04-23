#pragma once

#include <string>



namespace elona
{

struct Item;
struct Character;



void draw_additional_item_info_label(int x, int y);
void draw_additional_item_info(const Item& equip, int x, int y);
std::string cut_item_name_for_additional_info(
    const std::string& name,
    size_t adjustment = 0);
int eqweaponheavy();
int eqweaponlight();
void eqrandweaponmage();
void wear_most_valuable_equipment_for_all_body_parts(Character& chara);
void wear_most_valuable_equipment(Character& chara, Item& equipment);
void supply_new_equipment(Character& chara);
void supply_initial_equipments(Character& chara);

int equip_item(int cc, Item& equipment);
void unequip_item(int);

} // namespace elona

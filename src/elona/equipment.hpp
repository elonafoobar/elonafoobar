#pragma once

#include <string>



namespace elona
{

struct Item;



void draw_additional_item_info_label(int x, int y);
void draw_additional_item_info(const Item& equip, int x, int y);
std::string cut_item_name_for_additional_info(
    const std::string& name,
    size_t adjustment = 0);
int eqweaponheavy();
int eqweaponlight();
void eqrandweaponmage();
void wear_most_valuable_equipment_for_all_body_parts();
void wear_most_valuable_equipment();
void supply_new_equipment();
void supply_initial_equipments();

int equip_item(int);
void unequip_item(int);

} // namespace elona

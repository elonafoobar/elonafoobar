#pragma once
#include <string>

namespace elona
{

void equipinfo(const Item& equip, int x, int y);
int eqweaponheavy();
int eqweaponlight();
void eqrandweaponmage();
void wear_most_valuable_equipment_for_all_body_parts();
void wear_most_valuable_equipment();
void supply_new_equipment();
void supply_initial_equipments();

} // namespace elona

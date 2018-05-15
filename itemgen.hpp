#pragma once

namespace elona
{

int itemcreate(int = 0, int = 0, int = 0, int = 0, int = 0);
void get_random_item_id();
int do_create_item(int, int, int);
void label_1581();
void label_1583();
void initialize_item_material();
void determine_item_material();
void change_item_material();
void apply_item_material();
void set_material_specific_attributes();

} // namespace elona

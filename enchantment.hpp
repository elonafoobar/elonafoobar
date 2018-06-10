#pragma once

namespace elona
{

bool enchantment_add(
    int ci,
    int type,
    int power,
    int flip_percentage = 0,
    bool not_halve = false,
    bool only_check = false,
    bool force = false);
int encfind(int = 0, int = 0);
bool encfindspec(int = 0, int = 0);
void enchantment_remove(int = 0, int = 0, int = 0);
int enchantment_generate(int = 0);
int enchantment_gen_level(int = 0);
int enchantment_gen_p(int = 0);
void enchantment_sort(int = 0);
int enchantment_filter(int = 0, int = 0);
void initialize_enchantment_data();
void enchantment_print_level(int = 0);
void add_enchantments_depending_on_ego();
void add_enchantment_by_fixed_ego();
void add_enchantments();

void initialize_ego_data();
void ego_add(int = 0, int = 0);

} // namespace elona

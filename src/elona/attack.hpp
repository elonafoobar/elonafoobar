#pragma once

#include "optional.hpp"



namespace elona
{

struct Item;



void build_target_list();
int find_enemy_target(bool silent = false);

struct CanDoRangedAttackResult
{
    int type;
    optional_ref<Item> cw;
    optional_ref<Item> ammo;
};
CanDoRangedAttackResult can_do_ranged_attack();

void do_physical_attack(optional_ref<Item> cw, optional_ref<Item> ammo);
void do_ranged_attack(optional_ref<Item> cw, optional_ref<Item> ammo);
int prompt_really_attack();
void try_to_melee_attack();
int target_position(bool target_chara = true);
void proc_weapon_enchantments(const Item& cw);

} // namespace elona

#pragma once

#include "optional.hpp"



namespace elona
{

struct Item;
struct Character;



void build_target_list(const Character& attacker);
int find_enemy_target(Character& chara, bool silent = false);

struct CanDoRangedAttackResult
{
    int type;
    optional_ref<Item> weapon;
    optional_ref<Item> ammo;
};
CanDoRangedAttackResult can_do_ranged_attack(const Character& chara);

void do_physical_attack(
    Character& attacker,
    Character& target,
    optional_ref<Item> weapon,
    optional_ref<Item> ammo);
void do_ranged_attack(
    Character& attacker,
    Character& target,
    optional_ref<Item> weapon,
    optional_ref<Item> ammo);
int prompt_really_attack(const Character& target);
void try_to_melee_attack(Character& attacker, Character& target);
int target_position(bool target_cell = false);
void proc_weapon_enchantments(
    Character& attacker,
    Character& target,
    const Item& weapon);

} // namespace elona

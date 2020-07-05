#pragma once

#include "eobject/eobject.hpp"
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
    OptionalItemRef weapon;
    OptionalItemRef ammo;
};
CanDoRangedAttackResult can_do_ranged_attack(const Character& chara);

void do_physical_attack(
    Character& attacker,
    Character& target,
    const OptionalItemRef& weapon,
    const OptionalItemRef& ammo);
void do_ranged_attack(
    Character& attacker,
    Character& target,
    const OptionalItemRef& weapon,
    const OptionalItemRef& ammo);
int prompt_really_attack(const Character& target);
void try_to_melee_attack(Character& attacker, Character& target);
int target_position(bool target_cell = false);
void proc_weapon_enchantments(
    Character& attacker,
    Character& target,
    const ItemRef& weapon);

} // namespace elona

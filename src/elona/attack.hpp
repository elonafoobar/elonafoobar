#pragma once



namespace elona
{

void build_target_list();
int find_enemy_target(bool silent = false);

struct CanDoRangedAttackResult
{
    int type;
    int cw;
    int ammo;
};
CanDoRangedAttackResult can_do_ranged_attack();

void do_physical_attack(int cw, int ammo);
void do_ranged_attack(int cw, int ammo);
int prompt_really_attack();
void try_to_melee_attack();
int target_position(bool target_chara = true);
void proc_weapon_enchantments();

} // namespace elona

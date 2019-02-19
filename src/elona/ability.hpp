#pragma once

#include <cassert>
#include <vector>
#include "data/types/type_ability.hpp"



namespace elona
{

/// @putit
struct Ability
{
    // NOTE: Don't add new fields unless you add them to serialization, which
    // will break save compatibility.

    /// @putit
    int current_level = 0;

    /// @putit
    int original_level = 0;

    /// @putit
    int experience = 0;

    /// @putit
    int potential = 0;


#include "_putit/ability.cpp"
};



class SkillData
{
public:
    SkillData();


    int& operator()(int id, int cc)
    {
        return get(id, cc).current_level;
    }


    Ability& get(int id, int cc)
    {
        assert(id < 600);
        return storage[cc][id];
    }


    void clear(int cc);

    void copy(int tc, int cc);


private:
    std::vector<std::vector<Ability>> storage;
};


extern SkillData sdata;


struct Character;

void chara_init_skill(Character& cc, int id, int initial_level);
void chara_init_common_skills(Character& cc);

void chara_gain_skill(
    Character& cc,
    int id,
    int initial_level = 0,
    int stock = 0);
void gain_special_action();

void chara_gain_fixed_skill_exp(Character& cc, int id, int experience);
void chara_gain_skill_exp(
    Character& cc,
    int id,
    int experience,
    int experience_divisor_of_related_basic_attribute = 0,
    int experience_divisor_of_character_level = 0);

void gain_digging_experience();
void gain_literacy_experience();
void gain_negotiation_experience(int cc, int gold);
void gain_lock_picking_experience(int cc);
void gain_detection_experience(int cc);
void gain_casting_experience(int cc, int spell_id);
void gain_mana_capacity_experience(int cc);
void gain_healing_and_meditation_experience(int cc);
void gain_stealth_experience(int cc);
void gain_investing_experience(int cc);
void gain_weight_lifting_experience(int cc);
void gain_magic_device_experience(int cc);
void gain_fishing_experience(int cc);
void gain_memorization_experience(int cc);
void gain_crafting_experience(int skill, int mat_amount);
void gain_disarm_trap_experience();

} // namespace elona

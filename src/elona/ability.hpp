#pragma once

#include <cassert>

#include <vector>



namespace elona
{

struct Ability
{
    // NOTE: Don't add new fields unless you add them to serialization, which
    // will break save compatibility.

    int level = 0;

    int base_level = 0;

    int experience = 0;

    int potential = 0;



    template <typename Archive>
    void serialize(Archive& ar)
    {
        /* clang-format off */
        ar(level);
        ar(base_level);
        ar(experience);
        ar(potential);
        /* clang-format on */
    }
};



class SkillData
{
public:
    SkillData();

    SkillData(const SkillData&) = default;
    SkillData(SkillData&&) = default;
    SkillData& operator=(const SkillData&) = default;
    SkillData& operator=(SkillData&&) = default;


    Ability& get(int id)
    {
        return _storage.at(id);
    }


    const Ability& get(int id) const
    {
        return _storage.at(id);
    }



private:
    std::vector<Ability> _storage;
};



struct Character;

void chara_init_skill(Character& chara, int id, int initial_level);
void chara_init_common_skills(Character& chara);

void chara_gain_skill(
    Character& chara,
    int id,
    int initial_level = 0,
    int stock = 0);
void gain_special_action();

void chara_gain_fixed_skill_exp(Character& chara, int id, int experience);
void chara_gain_skill_exp(
    Character& chara,
    int id,
    int experience,
    int experience_divisor_of_related_basic_attribute = 0,
    int experience_divisor_of_character_level = 0);

void chara_gain_exp_digging(Character& chara);
void chara_gain_exp_literacy(Character& chara);
void chara_gain_exp_negotiation(Character& chara, int gold);
void chara_gain_exp_lock_picking(Character& chara);
void chara_gain_exp_detection(Character& chara);
void chara_gain_exp_casting(Character& chara, int spell_id);
void chara_gain_exp_mana_capacity(Character& chara);
void chara_gain_exp_healing_and_meditation(Character& chara);
void chara_gain_exp_stealth(Character& chara);
void chara_gain_exp_investing(Character& chara);
void chara_gain_exp_weight_lifting(Character& chara);
void chara_gain_exp_magic_device(Character& chara);
void chara_gain_exp_fishing(Character& chara);
void chara_gain_exp_memorization(Character& chara, int spell_id);
void chara_gain_exp_crafting(Character& chara, int skill, int material_amount);
void chara_gain_exp_disarm_trap(Character& chara);



int randattb();
int randskill();

} // namespace elona

#pragma once

#include <cassert>

#include <vector>

#include "data/types/type_ability.hpp"
#include "serialization/macros.hpp"



namespace elona
{

struct Ability
{
    // NOTE: Don't add new fields unless you add them to serialization, which
    // will break save compatibility.

    int current_level = 0;

    int original_level = 0;

    int experience = 0;

    int potential = 0;



    template <typename Archive>
    void serialize(Archive& ar)
    {
        /* clang-format off */
        ELONA_SERIALIZATION_STRUCT_BEGIN(ar, "Ability");

        ELONA_SERIALIZATION_STRUCT_FIELD(*this, current_level);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, original_level);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, experience);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, potential);

        ELONA_SERIALIZATION_STRUCT_END();
        /* clang-format on */
    }
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

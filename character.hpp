#pragma once

#include <memory>
#include <vector>
#include "position.hpp"


namespace elona
{


struct buff_t
{
    int id = 0;
    int power = 0;
    int turns = 0;
};



struct character
{
    character();


    int state = 0;
    position_t position;
    position_t next_position;
    int time_to_revive = 0;
    int vision_flag = 0;
    int image = 0;
    int sex = 0;
    int relationship = 0;
    int turn_cost = 0;
    int current_speed = 0;
    int item_which_will_be_used = 0;
    int portrait = 0;
    int interest = 0;
    int time_interest_revive = 0;
    int personality = 0;
    int impression = 0;
    int talk_type = 0;
    int height = 0;
    int weight = 0;
    int birth_year = 0;
    int nutrition = 0;
    int can_talk = 0;
    int quality = 0;
    int turn = 0;
    int id = 0;
    int vision_distance = 0;
    int enemy_id = 0;
    int gold = 0;
    int platinum_coin = 0;
    int equipment_type = 0;
    int melee_attack_type = 0;
    int fame = 0;
    int experience = 0;
    int required_experience = 0;
    int speed_percentage = 0;
    int level = 0;
    int speed_percentage_in_next_turn = 0;
    int skill_bonus = 0;
    int total_skill_bonus = 0;
    int inventory_weight = 0;
    int max_inventory_weight = 0;
    int inventory_weight_type = 0;
    int max_level = 0;
    int karma = 0;
    int hp = 0;
    int max_hp = 0;
    int sp = 0;
    int max_sp = 0;
    int mp = 0;
    int max_mp = 0;
    int heal_value_per_nether_attack = 0;
    int god = 0;
    int piety_point = 0;
    int praying_point = 0;
    int sum_of_equipment_weight = 0;
    int special_attack_type = 0;
    int rate_to_pierce = 0;
    int rate_of_critical_hit = 0;
    int speed_correction_value = 0;
    int original_relationship = 0;
    int pv = 0;
    int dv = 0;
    int hit_bonus = 0;
    int damage_bonus = 0;
    int pv_correction_value = 0;
    int dv_correction_value = 0;
    int damage_reaction_info = 0;
    int emotion_icon = 0;
    int current_map = 0;
    int current_dungeon_level = 0;
    int related_quest_id = 0;
    int direction = 0;
    int period_of_contract = 0;
    int hire_count = 0;
    int insanity = 0;
    int curse_power = 0;
    int extra_attack = 0;
    int extra_shot = 0;
    int decrease_physical_damage = 0;
    int nullify_damage = 0;
    int cut_counterattack = 0;
    int anorexia_count = 0;
    int continuous_action_id = 0;
    int continuous_action_turn = 0;
    int continuous_action_item = 0;
    int stops_continuous_action_if_damaged = 0;
    int quality_of_performance = 0;
    int tip_gold = 0;
    int character_role = 0;
    int shop_rank = 0;
    int continuous_action_target = 0;
    int shop_store_id = 0;
    int time_to_restore = 0;
    int cnpc_id = 0;
    position_t initial_position;
    int hate = 0;
    int ai_calm = 0;
    int ai_move = 0;
    int ai_dist = 0;
    int ai_act_sub_freq = 0;
    int ai_heal = 0;
    int ai_act_num = 0;
    int element_of_unarmed_attack = 0;
    int poisoned = 0;
    int sleep = 0;
    int paralyzed = 0;
    int blind = 0;
    int confused = 0;
    int fear = 0;
    int dimmed = 0;
    int drunk = 0;
    int bleeding = 0;
    int wet = 0;
    int insane = 0;
    int sick = 0;
    int gravity = 0;
    int choked = 0;
    int furious = 0;

    std::vector<int> growth_buffs;
    std::vector<int> body_parts;
    std::vector<int> act;
    std::vector<buff_t> buffs;
    std::vector<int> attr_adjs;
    std::vector<int> flags;

    int _40 = 0;
    int _158 = 0;
    int _156 = 0;
    int _203 = 0;
    int _205 = 0;
    int _206 = 0;


    void clear();
    void clear_flags();
};



struct character_data
{
    character_data();


    character& operator()(int index)
    {
        return storage[index];
    }


    std::unique_ptr<char[]> serialize(int offset = 0) const;

    void
    deserialize(std::unique_ptr<char[]> raw_data, int size, int offset = 0);


private:
    std::vector<character> storage;
};


inline character_data cdata;



int cbit(int type, int cc);
void cbitmod(int type, int cc, int on);



} // namespace elona



#include "macro_cdata.hpp"

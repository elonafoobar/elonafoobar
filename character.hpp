#pragma once

#include <memory>
#include <unordered_map>
#include <vector>
#include "god.hpp"
#include "optional_ref.hpp"
#include "position.hpp"
#include "range.hpp"


namespace elona
{



struct character_data
{
    int id;
    int act_0;
    int act_1;
    int act_2;
    int act_3;
    int act_4;
    int act_5;
    int act_6;
    int act_7;
    int act_8;
    int ai_act_num;
    int ai_act_sub_freq;
    int ai_calm;
    int ai_dist;
    int ai_heal;
    int ai_move;
    int can_talk;
    bool cbit_988;
    std::string class_;
    int color;
    int creaturepack;
    int cspecialeq;
    int damage_reaction_info;
    int item_type;
    int element_of_unarmed_attack;
    int eqammo_0;
    int eqammo_1;
    int eqmultiweapon;
    int eqrange_0;
    int eqrange_1;
    int eqring1;
    int eqtwohand;
    int eqweapon1;
    int female_image;
    std::string filter;
    int fixlv;
    bool has_random_name;
    int image;
    int level;
    int male_image;
    int original_relationship;
    int portrait;
    std::string race;
    int sex;
    std::unordered_map<int, int> resistances;
    int fltselect;
    int category;
    int rarity;
    int coefficient;
};



class character_db
{
public:
    struct iterator
    {
        iterator(
            const std::unordered_map<int, character_data>::const_iterator& itr)
            : itr(itr)
        {
        }

        const character_data& operator*() const
        {
            return itr->second;
        }

        void operator++()
        {
            ++itr;
        }

        bool operator!=(const iterator& other) const
        {
            return itr != other.itr;
        }

    private:
        std::unordered_map<int, character_data>::const_iterator itr;
    };


    character_db();


    optional_ref<character_data> operator[](int id) const;


    iterator begin() const
    {
        return iterator{std::begin(storage)};
    }

    iterator end() const
    {
        return iterator{std::end(storage)};
    }


private:
    std::unordered_map<int, character_data> storage;
};


inline character_db the_character_db;



struct buff_t
{
    int id = 0;
    int power = 0;
    int turns = 0;


    template <typename Archive>
    void serialize(Archive& ar)
    {
        ar(id);
        ar(power);
        ar(turns);
    }
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
    god_id_t god_id;
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

    int _156 = 0;
    int _203 = 0;
    int _205 = 0;
    int _206 = 0;


    void clear();
    void clear_flags();


    template <typename Archive>
    void serialize(Archive& ar)
    {
        ar(state);
        ar(position);
        ar(next_position);
        ar(time_to_revive);
        ar(vision_flag);
        ar(image);
        ar(sex);
        ar(relationship);
        ar(turn_cost);
        ar(current_speed);
        ar(item_which_will_be_used);
        ar(portrait);
        ar(interest);
        ar(time_interest_revive);
        ar(personality);
        ar(impression);
        ar(talk_type);
        ar(height);
        ar(weight);
        ar(birth_year);
        ar(nutrition);
        ar(can_talk);
        ar(quality);
        ar(turn);
        ar(id);
        ar(vision_distance);
        ar(enemy_id);
        ar(gold);
        ar(platinum_coin);
        ar(equipment_type);
        ar(melee_attack_type);
        ar(fame);
        ar(experience);
        ar(required_experience);
        ar(speed_percentage);
        ar(level);
        ar(speed_percentage_in_next_turn);
        ar(skill_bonus);
        ar(total_skill_bonus);
        ar(inventory_weight);
        ar(max_inventory_weight);
        ar(inventory_weight_type);
        ar(max_level);
        ar(karma);
        ar(hp);
        ar(max_hp);
        ar(sp);
        ar(max_sp);
        ar(mp);
        ar(max_mp);
        ar(heal_value_per_nether_attack);
        ar(god_id);
        ar(piety_point);
        ar(praying_point);
        ar(sum_of_equipment_weight);
        ar(special_attack_type);
        ar(rate_to_pierce);
        ar(rate_of_critical_hit);
        ar(speed_correction_value);
        ar(original_relationship);
        ar(pv);
        ar(dv);
        ar(hit_bonus);
        ar(damage_bonus);
        ar(pv_correction_value);
        ar(dv_correction_value);
        ar(damage_reaction_info);
        ar(emotion_icon);
        ar(current_map);
        ar(current_dungeon_level);
        ar(related_quest_id);
        ar(direction);
        ar(period_of_contract);
        ar(hire_count);
        ar(insanity);
        ar(curse_power);
        ar(extra_attack);
        ar(extra_shot);
        ar(decrease_physical_damage);
        ar(nullify_damage);
        ar(cut_counterattack);
        ar(anorexia_count);
        ar(continuous_action_id);
        ar(continuous_action_turn);
        ar(continuous_action_item);
        ar(stops_continuous_action_if_damaged);
        ar(quality_of_performance);
        ar(tip_gold);
        ar(character_role);
        ar(shop_rank);
        ar(continuous_action_target);
        ar(shop_store_id);
        ar(time_to_restore);
        ar(cnpc_id);
        ar(initial_position);
        ar(hate);
        ar(ai_calm);
        ar(ai_move);
        ar(ai_dist);
        ar(ai_act_sub_freq);
        ar(ai_heal);
        ar(ai_act_num);
        ar(element_of_unarmed_attack);
        ar(poisoned);
        ar(sleep);
        ar(paralyzed);
        ar(blind);
        ar(confused);
        ar(fear);
        ar(dimmed);
        ar(drunk);
        ar(bleeding);
        ar(wet);
        ar(insane);
        ar(sick);
        ar(gravity);
        ar(choked);
        ar(furious);
        range::for_each(
            growth_buffs, [&](auto&& growth_buff) { ar(growth_buff); });
        range::for_each(body_parts, [&](auto&& body_part) { ar(body_part); });
        range::for_each(act, [&](auto&& a) { ar(a); });
        range::for_each(buffs, [&](auto&& buff) { ar(buff); });
        range::for_each(attr_adjs, [&](auto&& attr_adj) { ar(attr_adj); });
        range::for_each(flags, [&](auto&& flag) { ar(flag); });
        ar(_156);
        ar(_203);
        ar(_205);
        ar(_206);
    }
};



struct cdata_t
{
    cdata_t();


    character& operator()(int index)
    {
        return storage[index];
    }


    character& operator[](int index)
    {
        return storage[index];
    }


private:
    std::vector<character> storage;
};


inline cdata_t cdata;



int cbit(size_t type, int cc);
void cbitmod(size_t type, int cc, int on);
void initialize_character_filters();



} // namespace elona



inline int cdata_body_part_index(int i)
{
    return i >= 100 ? i - 100 : i;
}
#define cdata_body_part(cc, i) cdata(cc).body_parts[cdata_body_part_index(i)]

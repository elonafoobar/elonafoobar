#pragma once

#include <bitset>
#include <memory>
#include <unordered_map>
#include <vector>
#include "cat.hpp"
#include "god.hpp"
#include "position.hpp"
#include "range.hpp"


#define ELONA_MAX_CHARACTERS 245
#define ELONA_MAX_PARTY_CHARACTERS 57
#define ELONA_MAX_OTHER_CHARACTERS 188

#define ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(name, n) \
    bool name() const \
    { \
        return _flags[n]; \
    } \
    decltype(_flags)::reference name() \
    { \
        return _flags[n]; \
    }

#define ELONA_CHARACTER_DEFINE_FLAG_ACCESSORS \
    std::bitset<sizeof(int) * 8 * 50> _flags; \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(is_floating, 5) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(is_invisible, 6) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(can_see_invisible, 7) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(is_immune_to_confusion, 8) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(is_immune_to_blindness, 9) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(is_immune_to_fear, 10) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(is_immune_to_sleep, 11) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(is_immune_to_paralyzation, 12) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(is_immune_to_poison, 13) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(can_digest_rotten_food, 14) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(is_protected_from_thieves, 15) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(is_incognito, 16) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(drops_gold, 17) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(explodes, 18) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(is_death_master, 19) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(can_cast_rapid_magic, 20) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(has_lay_hand, 21) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(is_suitable_for_mount, 22) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(splits, 23) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(has_cursed_equipments, 24) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(is_unsuitable_for_mount, 25) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(is_immune_to_elemental_damage, 26) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(splits2, 27) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(is_metal, 28) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(cures_bleeding_quickly, 29) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(has_power_bash, 30) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(is_immune_to_mine, 31) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(is_quick_tempered, 32) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(is_livestock, 960) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(is_married, 961) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(has_made_gene, 962) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(is_escorted, 963) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(is_temporary, 964) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(is_silent, 965) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(has_been_used_stethoscope, 966) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(has_own_sprite, 967) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(is_leashed, 968) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(is_contracting, 969) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(is_quest_target, 970) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(is_escorted_in_sub_quest, 971) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(will_explode_soon, 972) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(is_sentenced_daeth, 973) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(is_lay_hand_available, 974) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(is_ridden, 975) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(is_lord_of_dungeon, 976) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(has_own_name, 977) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(is_pregnant, 978) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(does_not_search_enemy, 979) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(is_contracting_with_reaper, 980) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(needs_refreshing_status, 981) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(visited_just_now, 982) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(breaks_into_debris, 983) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(is_best_friend, 984) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(is_hung_on_sand_bag, 985) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(has_anorexia, 986) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(was_passed_item_by_you_just_now, 987) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(cures_mp_frequently, 988) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(has_custom_talk, 989) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(has_learned_words, 990) \
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(only_christmas, 991)


namespace elona
{


struct character_data
{
    int id;
    std::vector<int> normal_actions;
    std::vector<int> special_actions;
    int ai_act_sub_freq;
    int ai_calm;
    int ai_dist;
    int ai_heal;
    int ai_move;
    int can_talk;
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


    ELONA_CHARACTER_DEFINE_FLAG_ACCESSORS
};



class character_db;


namespace cat
{

template <>
struct cat_db_traits<character_db>
{
    using id_type = int;
    using data_type = character_data;
    static constexpr const char* filename = u8"character.lua";
    static constexpr const char* table_name = u8"character";
};

} // namespace cat



class character_db : public cat::cat_db<character_db>
{
public:
    character_db() = default;

    void define(lua_State* L);
};


extern character_db the_character_db;



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

    // NOTE: Don't add new fields unless you add them to serialization, which
    // will break save compatibility.
    int idx = -1;
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
    std::vector<int> normal_actions;
    std::vector<int> special_actions;
    std::vector<buff_t> buffs;
    std::vector<int> attr_adjs;

    int _156 = 0;
    int _203 = 0;
    int _205 = 0;
    int _206 = 0;

    void clear();
    void clear_flags();


    ELONA_CHARACTER_DEFINE_FLAG_ACCESSORS


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
        ar(normal_actions);
        ar(special_actions);
        range::for_each(buffs, [&](auto&& buff) { ar(buff); });
        range::for_each(attr_adjs, [&](auto&& attr_adj) { ar(attr_adj); });
        ar(_flags);
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


extern cdata_t cdata;

int chara_create(int = 0, int = 0, int = 0, int = 0);
int chara_create_internal();
void chara_place();
int chara_relocate(int = 0, int = 0, int = 0);
void chara_refresh(int);
int chara_copy(int = 0);
void chara_delete(int = 0);
void chara_vanquish(int = 0);
int chara_find(int = 0);
int chara_find_ally(int = 0);
int chara_get_free_slot();
int chara_get_free_slot_ally();
bool chara_unequip(int);
int chara_custom_talk(int = 0, int = 0);
std::string chara_refstr(int = 0, int = 0);
int chara_impression_level(int = 0);
void chara_mod_impression(int = 0, int = 0);
void chara_set_item_which_will_be_used();
int chara_armor_class(int = 0);

void initialize_character_filters();
void chara_set_generation_filter();

int access_character_info();


} // namespace elona



inline int cdata_body_part_index(int i)
{
    return i >= 100 ? i - 100 : i;
}
#define cdata_body_part(cc, i) cdata(cc).body_parts[cdata_body_part_index(i)]



#undef ELONA_CHARACTER_DEFINE_FLAG_ACCESSORS
#undef ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR

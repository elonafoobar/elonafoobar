#pragma once

#include <unordered_map>
#include <vector>
#include "../../enums.hpp"
#include "../../optional.hpp"
#include "../lua_lazy_cache.hpp"


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
    ELONA_CHARACTER_DEFINE_FLAG_ACCESSOR(is_not_attacked_by_enemy, 979) \
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

struct CharacterData
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
    ColorIndex color;
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
    std::string portrait_male;
    std::string portrait_female;
    std::string race;
    int sex;
    std::unordered_map<int, int> resistances;
    int fltselect;
    int category;
    int rarity;
    int coefficient;
    optional<std::string> corpse_eating_callback;
    optional<std::string> dialog_id;

    std::bitset<sizeof(int) * 8 * 50> _flags;

    ELONA_CHARACTER_DEFINE_FLAG_ACCESSORS
};

ELONA_DEFINE_LUA_DB(CharacterDB, CharacterData, true, "core.chara")

extern CharacterDB the_character_db;

} // namespace elona

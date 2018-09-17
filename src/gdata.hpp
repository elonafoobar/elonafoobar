#pragma once
#include "version.hpp"

#define gdata_continuous_action_about_to_start gdata(91)
#define gdata_executing_immediate_quest_show_hunt_remain gdata(71)
#define gdata_executing_immediate_quest_status gdata(73)
#define gdata_executing_immediate_quest_fame_gained gdata(74)
#define gdata_executing_immediate_quest_time_left_display_period gdata(87)
#define gdata_rogue_boss_encountered gdata(171)
#define gdata_void_next_lord_floor gdata(186)
#define gdata_player_next_move_direction gdata(35)

// tc + (0 or 10000)
#define gdata_character_and_status_for_gene gdata(98)

#define gdata_player_is_changing_equipment gdata(808)
#define gdata_player_cellaccess_check_flag gdata(30)
#define gdata_player_cellaccess_w gdata(31)
#define gdata_player_cellaccess_n gdata(32)
#define gdata_player_cellaccess_e gdata(33)
#define gdata_player_cellaccess_s gdata(34)
#define gdata_player_x_on_map_leave gdata(60)
#define gdata_player_y_on_map_leave gdata(61)
#define gdata_stood_world_map_tile gdata(62)
#define gdata_chara_last_attacked_by_player gdata(94)
#define gdata_map_regenerate_count gdata(184)
#define gdata_politics_map_id gdata(815)

// whether or not to proc fury/splitting/active form damage text
// 1 if not, 2 if yes
#define gdata_proc_damage_events_flag gdata(809)

#define gdata_destination_outer_map gdata(850)
#define gdata_reset_world_map_in_diastrophism_flag gdata(79)
#define gdata_ex_arena_wins gdata(802)

#define gdata_exhelp_flag(n) gdata(200 + n)

// 40-59
#define gdata_skill_shortcut(n) gdata(40 + n)

// 120-128
#define gdata_rank(n) gdata(120 + n)

// 140-148
#define gdata_rank_deadline(n) gdata(140 + n)

// 160-164
#define gdata_taken_quest(n) gdata(160 + n)

// 750-760
#define gdata_tracked_skill(n) gdata(750 + n)

namespace elona
{

template <typename T>
struct elona_vector1;

struct Date
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;

    int hours()
    {
        return hour + (day * 24) + (month * 24 * 30) + (year * 24 * 30 * 12);
    }
};

struct QuestFlags
{
    int tutorial;

    int main_quest;
    int magic_stone_of_fool;
    int magic_stone_of_sage;
    int magic_stone_of_king;

    int putit_attacks;
    int thieves_hideout;
    int nightmare;
    int pael_and_her_mom;
    int wife_collector;
    int puppys_cave;
    int cat_house;
    int defense_line;
    int novice_knight;
    int kamikaze_attack;
    int mias_dream;
    int rare_books;
    int pyramid_trial;
    int red_blossom_in_palmia;
    int ambitious_scientist;
    int sewer_sweeping;
    int minotaur_king;
    int little_sister;
    int blue_capsule_drug;

    int duration_of_kamikaze_attack;
    int kill_count_of_little_sister;
    int save_count_of_little_sister;
    int gift_count_of_little_sister;
};

struct GuildData
{
    int belongs_to_mages_guild;
    int belongs_to_fighters_guild;
    int belongs_to_thieves_guild;

    int mages_guild_quota;
    int fighters_guild_quota;
    int fighters_guild_target;
    int thieves_guild_quota;

    int joining_mages_guild;
    int joining_fighters_guild;
    int joining_thieves_guild;

    int mages_guild_quota_recurring;
    int fighters_guild_quota_recurring;
    int thieves_guild_quota_recurring;
};

/**
 * Global game data that is serialized. Replaces gdata.
 */
struct GameData
{
    int death_count;
    int deepest_dungeon_level;
    int kill_count;
    int crowd_density;
    int play_turns;
    int pc_x_in_world_map;
    int pc_y_in_world_map;
    int play_days;
    int random_seed;
    Date date;
    int next_inventory_serial_id;
    int weather;
    int hours_until_weather_changes;
    int previous_map;
    int current_map;
    int current_dungeon_level;
    int home_scale;
    int charge_power;
    int entrance_type;
    int destination_map;
    int destination_dungeon_level;
    int previous_map2;
    int previous_dungeon_level;
    int previous_x;
    int previous_y;
    int next_shelter_serial_id;
    int seven_league_boot_effect;
    int protects_from_etherwind;
    int played_scene;
    int torch;
    int angband_flag;
    int number_of_learned_skills_by_trainer;
    int is_returning_or_escaping;
    int executing_immediate_quest_type;
    int executing_immediate_quest;
    int number_of_existing_quests;
    int basic_point_of_home_rank;
    int cargo_weight;
    int initial_cart_limit;
    int current_cart_limit;
    int protects_from_bad_weather;
    int left_minutes_of_executing_quest;
    int ether_disease_stage;
    int time_when_textbook_becomes_available;
    int continuous_active_hours;
    int sleep_experience;
    int acquirable_feat_count;
    int wish_count;
    int version;
    int rights_to_succeed_to;
    int next_voting_time;
    int cost_to_hire;
    int left_bill;
    int distance_between_town;
    int departure_date;
    int left_town_map;
    int mount;
    int catches_god_signal;
    int reveals_religion;
    int used_casino_once;
    int has_not_been_to_vernis;
    int released_fire_giant;
    int fire_giant;
    int holy_well_count;
    int diastrophism_flag;
    int ether_disease_speed;
    int left_turns_of_timestop;
    int ex_arena_level;
    int time_when_uploding_becomes_available;
    int play_time;
    int last_etherwind_month;
    int god_rank;
    int number_of_waiting_guests;
    int last_month_when_trainer_visited;
    int item_turns;
    int next_level_minus_one_kumiromis_experience_becomes_available;
    int wizard;
    int lost_wallet_count;

    QuestFlags quest_flags;
    GuildData guild;

    /**
     * Moves this struct's fields into `gdata` so they can be serialized,
     * for compatibility. To be called before serializing `gdata`.
     */
    void pack_to(elona_vector1<int>&);

    /**
     * Moves `gdata` fields into this struct. To be called after
     * deserializing `gdata`.
     */
    void unpack_from(elona_vector1<int>&);
};

extern GameData game_data;

struct FoobarData
{
    // NOTE: Don't add new fields unless you add them to serialization,
    // which will break save compatibility.
    bool is_autodig_enabled{};


    template <typename Archive>
    void serialize(Archive& ar)
    {
        // WARNING: Changing this will break save compatibility!
        ar(is_autodig_enabled);
    }
};


extern FoobarData foobar_data;


// TODO: Make gdata class and make this function method.
void modify_crowd_density(int cc, int delta);


} // namespace elona

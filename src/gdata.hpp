#pragma once

#include "version.hpp"

#define gdata_mount gdata(183)
#define gdata_catches_god_signal gdata(185)
#define gdata_reveals_religion gdata(187)
#define gdata_tutorial_flag gdata(250)
#define gdata_main_quest_flag gdata(252)
#define gdata_magic_stone_of_fool gdata(253)
#define gdata_magic_stone_of_sage gdata(254)
#define gdata_magic_stone_of_king gdata(255)
#define gdata_used_casino_once gdata(256)
#define gdata_has_not_been_to_vernis gdata(257)
#define gdata_released_fire_giant gdata(258)
#define gdata_fire_giant gdata(259)
#define gdata_holy_well_count gdata(260)
#define gdata_duration_of_kamikaze_attack gdata(261)
#define gdata_diastrophism_flag gdata(262)
#define gdata_belongs_to_mages_guild gdata(263)
#define gdata_belongs_to_fighters_guild gdata(264)
#define gdata_belongs_to_thieves_guild gdata(265)
#define gdata_mages_guild_quota gdata(266)
#define gdata_fighters_guild_quota gdata(267)
#define gdata_fighters_guild_target gdata(268)
#define gdata_thieves_guild_quota gdata(269)
#define gdata_putit_attacks gdata(450)
#define gdata_thieves_hideout gdata(451)
#define gdata_nightmare gdata(452)
#define gdata_pael_and_her_mom gdata(453)
#define gdata_wife_collector gdata(454)
#define gdata_puppys_cave gdata(455)
#define gdata_cat_house gdata(456)
#define gdata_defense_line gdata(457)
#define gdata_novice_knight gdata(458)
#define gdata_kamikaze_attack gdata(459)
#define gdata_mias_dream gdata(460)
#define gdata_rare_books gdata(461)
#define gdata_pyramid_trial gdata(462)
#define gdata_red_blossom_in_palmia gdata(463)
#define gdata_ambitious_scientist gdata(464)
#define gdata_sewer_sweeping gdata(465)
#define gdata_joining_mages_guild gdata(466)
#define gdata_joining_fighters_guild gdata(467)
#define gdata_joining_thieves_guild gdata(468)
#define gdata_mages_guild_quota2 gdata(469)
#define gdata_fighters_guild_quota2 gdata(470)
#define gdata_thieves_guild_quota2 gdata(471)
#define gdata_minotaur_king gdata(472)
#define gdata_little_sister gdata(473)
#define gdata_blue_capsule_drug gdata(474)
#define gdata_ether_disease_speed gdata(800)
#define gdata_left_turns_of_timestop gdata(801)
#define gdata_ex_arena_level gdata(803)
#define gdata_time_when_uploding_becomes_available gdata(804)
#define gdata_play_time gdata(805)
#define gdata_last_etherwind_month gdata(806)
#define gdata_god_rank gdata(807)
#define gdata_kill_count_of_little_sister gdata(810)
#define gdata_save_count_of_little_sister gdata(811)
#define gdata_gift_count_of_little_sister gdata(812)
#define gdata_number_of_waiting_guests gdata(814)
#define gdata_last_month_when_trainer_visited gdata(825)
#define gdata_item_turns gdata(826)
#define gdata_next_level_minus_one_kumiromis_experience_becomes_available \
    gdata(827)
#define gdata_wizard gdata(828)
#define gdata_lost_wallet_count gdata(851)


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

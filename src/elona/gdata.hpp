#pragma once

#include <array>

#include "../version.hpp"
#include "serialization/macros.hpp"



namespace elona
{

template <typename T>
struct elona_vector1;



struct DateTime
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

    // It is for debugging, not for showing to end-users.
    // E.g., "518/02/03 14:56'30"
    std::string to_string() const;
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
    template <size_t N>
    using ArrayType = std::array<int, N>;

    int death_count;
    int deepest_dungeon_level;
    int kill_count;
    int crowd_density;
    int play_turns;
    int pc_x_in_world_map;
    int pc_y_in_world_map;
    int play_days;
    int random_seed;
    int random_seed_offset;
    DateTime date;
    int next_inventory_serial_id;
    int weather;
    int hours_until_weather_changes;
    int previous_map;
    int current_map;
    int current_dungeon_level;
    int home_scale;
    int charge_power;
    int entrance_type;
    int next_shelter_serial_id;
    int seven_league_boot_effect;
    int protects_from_etherwind;
    int player_next_move_direction;
    int played_scene;
    int torch;
    int angband_flag;
    int number_of_learned_skills_by_trainer;
    ArrayType<20> skill_shortcuts;
    int player_x_on_map_leave;
    int player_y_on_map_leave;
    int stood_world_map_tile;
    int is_returning_or_escaping;
    int destination_map;
    int destination_dungeon_level;
    int previous_map2;
    int previous_dungeon_level;
    int previous_x;
    int previous_y;
    int executing_immediate_quest_type;
    int executing_immediate_quest_show_hunt_remain;
    int executing_immediate_quest;
    int executing_immediate_quest_status;
    int executing_immediate_quest_fame_gained;
    int number_of_existing_quests;
    int basic_point_of_home_rank;
    int total_deco_value;
    int total_heirloom_value;
    int reset_world_map_in_diastrophism_flag;
    int cargo_weight;
    int initial_cart_limit;
    int current_cart_limit;
    int protects_from_bad_weather;
    int left_minutes_of_executing_quest;
    int ether_disease_stage;
    int executing_immediate_quest_time_left_display_period;
    int time_when_textbook_becomes_available;
    int light;
    int continuous_active_hours;
    int activity_about_to_start;
    int sleep_experience;
    int acquirable_feat_count;
    int chara_last_attacked_by_player;
    int wish_count;
    int version;
    int rights_to_succeed_to;
    int character_and_status_for_gene; // tc + (0 if activity not
                                       // started, 10000 if so)
    int next_voting_time;
    ArrayType<20> ranks;
    ArrayType<9> rank_deadlines;
    ArrayType<5> taken_quests;
    int cost_to_hire;
    int rogue_boss_encountered;
    int left_bill;
    int distance_between_town;
    int departure_date;
    int left_town_map;
    int mount;
    int map_regenerate_count;
    int catches_god_signal;
    int void_next_lord_floor;
    int reveals_religion;
    ArrayType<18> exhelp_flags;
    int used_casino_once;
    int has_not_been_to_vernis;
    int released_fire_giant;
    int fire_giant;
    int holy_well_count;
    int diastrophism_flag;
    ArrayType<20> ether_disease_history;
    ArrayType<10> tracked_skills;
    int ether_disease_speed;
    int left_turns_of_timestop;
    int ex_arena_wins;
    int ex_arena_level;
    int time_when_uploding_becomes_available;
    int play_time;
    int last_etherwind_month;
    int god_rank;
    int player_is_changing_equipment;
    int proc_damage_events_flag; // proc fury/splitting/active-form damage text
                                 // from damage_hp()? 1 if not, 2 if yes
    int tcg_used_deck;
    int number_of_waiting_guests;
    int politics_map_id;
    int politics_tax_amount;
    int last_month_when_trainer_visited;
    int item_turns;
    int next_level_minus_one_kumiromis_experience_becomes_available;
    int wizard;
    ArrayType<5> tcg_decks;
    int destination_outer_map;
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
    bool is_autodig_enabled{};



    template <typename Archive>
    void serialize(Archive& ar)
    {
        /* clang-format off */
        ELONA_SERIALIZATION_STRUCT_BEGIN(ar, "FoobarData");

        ELONA_SERIALIZATION_STRUCT_FIELD(*this, is_autodig_enabled);

        ELONA_SERIALIZATION_STRUCT_END();
        /* clang-format on */
    }
};


extern FoobarData foobar_data;


// TODO: Make gdata class and make this function method.
void modify_crowd_density(int chara_index, int delta);

} // namespace elona

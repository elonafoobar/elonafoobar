#pragma once

#include <array>
#include <memory>

#include "blending_recipe_memory.hpp"
#include "character_memory.hpp"
#include "crafting_material.hpp"
#include "deferred_event.hpp"
#include "item_memory.hpp"
#include "story_quest.hpp"
#include "time.hpp"
#include "version.hpp"



namespace elona
{

template <typename T>
struct elona_vector1;



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
struct Game
{
    template <size_t N>
    using ArrayType = std::array<int, N>;


    /* Game statistics */

    /// The deepest dungeon danger level the player have visited.
    lua_int deepest_dungeon_danger_level{};

    /// Total death count of player and your allies.
    lua_int total_death_count{};

    /// Total kill count of player and your allies.
    lua_int total_kill_count{};

    /// Play turns
    lua_int play_turns{};

    /// Play time in seconds (in the real world)
    lua_int play_seconds_in_real_world{};

    /// Ex arena stats: number of your team's wins
    lua_int ex_arena_wins{};

    /// Ex arena stats: the highest character level which your team has beated
    lua_int ex_arena_highest_level{};


    /* Time */

    /// Universal clock
    time::Clock universal_clock{};

    /// The Epoch Year of the game world. E.g., year 123 is 123 years later
    /// since the epoch.
    lua_int epoch_year{};

    /// Frozen turn counter during Time Stop caused by some means.
    lua_int frozen_turns{};


    /* Memories */

    /// Character memories
    CharacterMemoryTable character_memories;

    /// Item memories
    ItemMemoryTable item_memories;

    /// Blending recipe memories
    BlendingRecipeMemoryTable blending_recipe_memories;


    /* Weather */

    /// Current weather
    data::InstanceId weather{"core.sunny"};

    /// Weather change count. When it reaches zero, weather may change.
    /// Normally, it is decremented every 1 hour.
    lua_int weather_change_count{};

    /// Time when Etherwind blew last.
    time::Instant last_etherwind_time{};

    /* Player state */

    /// Total weight of cargo items on the cart.
    lua_int cargo_weight{};

    /// Maximum weight of cargo items on the cart.
    lua_int max_cargo_weight{};

    /// Initial value of @ref max_cargo_weight.
    lua_int initial_max_cargo_weight{};

    /// Travel distance between towns. (in miles)
    lua_int travel_distance{};

    /// Next time when the player can study with textbooks.
    time::Instant next_studying_time{};

    // Crafting material bag
    CraftingMaterialBag crafting_materials{};


    /* Quests */

    /// Story quests
    StoryQuestTable story_quests{};


    /* Miscellaneous */

    /// Deferred events
    DeferredEventQueue deferred_events{};

    /// Amount of the water which the holy well holds.
    lua_int holy_well_amount{};

    /// Wish count
    lua_int wish_count{};

    /// Lost wallet count
    lua_int lost_wallet_count{};

    /// Flag for Easter Egg event (Angband's "Qy@")
    lua_int angband_flag{};

    /// Left bills
    lua_int left_bills{};

    /// Number of inheritance rights you currently have
    lua_int inheritance_rights{};

    /// Whether you used casino at least once or not
    bool used_casino_once{};

    /// Next `Item::_z_order`. See documentation of `Item::_z_order`.
    lua_int next_item_z_order{};

    /// Next shelter serial number
    lua_int next_shelter_serial_number{};

    /// Time when you left a town most recently
    time::Instant departure_time{};

    /// Next time of alias voting;
    time::Instant next_voting_time{};


    int crowd_density;
    int pc_x_in_world_map;
    int pc_y_in_world_map;
    int play_days;
    int random_seed;
    int random_seed_offset;
    int next_inventory_serial_id;
    int current_map;
    int current_dungeon_level;
    int home_scale;
    int charge_power;
    int entrance_type;
    int seven_league_boot_effect;
    int protects_from_etherwind;
    int player_next_move_direction;
    int played_scene;
    int torch;
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
    int protects_from_bad_weather;
    int left_minutes_of_executing_quest;
    int ether_disease_stage;
    int light;
    int continuous_active_hours;
    int activity_about_to_start;
    int sleep_experience;
    int acquirable_feat_count;
    int version;
    int character_and_status_for_gene; // the ally who is about to make gene
                                       // with you + (0 if activity not started,
                                       // 10000 if so)
    ArrayType<20> ranks;
    ArrayType<9> rank_deadlines;
    ArrayType<5> taken_quests;
    int cost_to_hire;
    int rogue_boss_encountered;
    int left_town_map;
    int mount;
    int map_regenerate_count;
    int catches_god_signal;
    int void_next_lord_floor;
    int reveals_religion;
    ArrayType<18> exhelp_flags;
    int has_not_been_to_vernis;
    int released_fire_giant;
    int fire_giant;
    int diastrophism_flag;
    ArrayType<20> ether_disease_history;
    ArrayType<10> tracked_skills;
    int ether_disease_speed;
    int time_when_uploding_becomes_available;
    int god_rank;
    int tcg_used_deck;
    int number_of_waiting_guests;
    int politics_map_id;
    int politics_tax_amount;
    time::Instant last_time_when_trainer_visited;
    int next_level_minus_one_kumiromis_experience_becomes_available;
    ArrayType<5> tcg_decks;
    int destination_outer_map;

    GuildData guild;
};



/**
 * Gets the game data.
 */
const std::unique_ptr<Game>& game();



// TODO: Make gdata class and make this function method.
void modify_crowd_density(int chara_index, int delta);



time::Instant game_now();
time::Date game_date(optional<time::Instant> instant = none);
time::Time game_time(optional<time::Instant> instant = none);
time::DateTime game_date_time(optional<time::Instant> instant = none);

} // namespace elona

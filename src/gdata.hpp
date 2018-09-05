#pragma once

#include "version.hpp"


#define gdata_death_count gdata(0)
#define gdata_deepest_dungeon_level gdata(1)
#define gdata_kill_count gdata(2)
#define gdata_crowd_density gdata(3)
#define gdata_play_turns gdata(4)
#define gdata_pc_x_in_world_map gdata(5)
#define gdata_pc_y_in_world_map gdata(6)
#define gdata_play_days gdata(7)
#define gdata_random_seed gdata(8)
#define gdata_year gdata(10)
#define gdata_month gdata(11)
#define gdata_day gdata(12)
#define gdata_hour gdata(13)
#define gdata_minute gdata(14)
#define gdata_second gdata(15)
#define gdata_next_inventory_serial_id gdata(16)
#define gdata_weather gdata(17)
#define gdata_hours_until_weather_changes gdata(18)
#define gdata_previous_map gdata(19)
#define gdata_current_map gdata(20)
#define gdata_current_dungeon_level gdata(22)
#define gdata_home_scale gdata(24)
#define gdata_charge_power gdata(25)
#define gdata_entrance_type gdata(26)
#define gdata_next_shelter_serial_id gdata(27)
#define gdata_seven_league_boot_effect gdata(28)
#define gdata_protects_from_etherwind gdata(29)
#define gdata_played_scene gdata(36)
#define gdata_torch gdata(37)
#define gdata_angband_flag gdata(38)
#define gdata_number_of_learned_skills_by_trainer gdata(39)
#define gdata_is_returning_or_escaping gdata(63)
#define gdata_destination_map gdata(64)
#define gdata_destination_dungeon_level gdata(65)
#define gdata_previous_map2 gdata(66)
#define gdata_previous_dungeon_level gdata(67)
#define gdata_previous_x gdata(68)
#define gdata_previous_y gdata(69)
#define gdata_executing_immediate_quest_type gdata(70)
#define gdata_executing_immediate_quest gdata(72)
#define gdata_number_of_existing_quests gdata(75)
#define gdata_basic_point_of_home_rank gdata(76)
#define gdata_cargo_weight gdata(80)
#define gdata_initial_cart_limit gdata(81)
#define gdata_current_cart_limit gdata(82)
#define gdata_protects_from_bad_weather gdata(83)
#define gdata_left_minutes_of_executing_quest gdata(84)
#define gdata_ether_disease_stage gdata(85)
#define gdata_time_when_textbook_becomes_available gdata(88)
#define gdata_continuous_active_hours gdata(90)
#define gdata_sleep_experience gdata(92)
#define gdata_acquirable_feat_count gdata(93)
#define gdata_wish_count gdata(95)
#define gdata_version gdata(96)
#define gdata_rights_to_succeed_to gdata(97)
#define gdata_next_voting_time gdata(99)
#define gdata_cost_to_hire gdata(170)
#define gdata_left_bill gdata(179)
#define gdata_distance_between_town gdata(180)
#define gdata_departure_date gdata(181)
#define gdata_left_town_map gdata(182)
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


struct FoobarData
{
    // NOTE: Don't add new fields unless you add them to serialization, which
    // will break save compatibility.
    Version version;
    bool is_autodig_enabled{};


    template <typename Archive>
    void serialize(Archive& ar)
    {
        // WARNING: Changing this will break save compatibility!
        ar(version);
        ar(is_autodig_enabled);
    }
};


extern FoobarData foobar_data;


// TODO: Make gdata class and make this function method.
void modify_crowd_density(int cc, int delta);


} // namespace elona

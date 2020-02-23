#include "gdata.hpp"

#include <iomanip>
#include <sstream>

#include "variables.hpp"



namespace elona
{

#define GDATA_PACK(x, ident) gdata(x) = ident;
#define GDATA_UNPACK(x, ident) ident = gdata(x);

#define SERIALIZE_ARRAY(x, ident) \
    for (size_t i = 0; i < ident.size(); i++) \
        SERIALIZE(x + i, ident.at(i));

#define SERIALIZE_ALL() \
    SERIALIZE(0, death_count); \
    SERIALIZE(1, deepest_dungeon_level); \
    SERIALIZE(2, kill_count); \
    SERIALIZE(3, crowd_density); \
    SERIALIZE(4, play_turns); \
    SERIALIZE(5, pc_x_in_world_map); \
    SERIALIZE(6, pc_y_in_world_map); \
    SERIALIZE(7, play_days); \
    SERIALIZE(8, random_seed); \
    SERIALIZE(9, random_seed_offset); \
    SERIALIZE(10, date.year); \
    SERIALIZE(11, date.month); \
    SERIALIZE(12, date.day); \
    SERIALIZE(13, date.hour); \
    SERIALIZE(14, date.minute); \
    SERIALIZE(15, date.second); \
    SERIALIZE(16, next_inventory_serial_id); \
    SERIALIZE(17, weather); \
    SERIALIZE(18, hours_until_weather_changes); \
    SERIALIZE(19, previous_map); \
    SERIALIZE(20, current_map); \
    SERIALIZE(22, current_dungeon_level); \
    SERIALIZE(24, home_scale); \
    SERIALIZE(25, charge_power); \
    SERIALIZE(26, entrance_type); \
    SERIALIZE(27, next_shelter_serial_id); \
    SERIALIZE(28, seven_league_boot_effect); \
    SERIALIZE(29, protects_from_etherwind); \
    SERIALIZE(35, player_next_move_direction); \
    SERIALIZE(36, played_scene); \
    SERIALIZE(37, torch); \
    SERIALIZE(38, angband_flag); \
    SERIALIZE(39, number_of_learned_skills_by_trainer); \
    SERIALIZE_ARRAY(40, skill_shortcuts); \
    SERIALIZE(60, player_x_on_map_leave); \
    SERIALIZE(61, player_y_on_map_leave); \
    SERIALIZE(62, stood_world_map_tile); \
    SERIALIZE(63, is_returning_or_escaping); \
    SERIALIZE(64, destination_map); \
    SERIALIZE(65, destination_dungeon_level); \
    SERIALIZE(66, previous_map2); \
    SERIALIZE(67, previous_dungeon_level); \
    SERIALIZE(68, previous_x); \
    SERIALIZE(69, previous_y); \
    SERIALIZE(70, executing_immediate_quest_type); \
    SERIALIZE(71, executing_immediate_quest_show_hunt_remain); \
    SERIALIZE(72, executing_immediate_quest); \
    SERIALIZE(73, executing_immediate_quest_status); \
    SERIALIZE(74, executing_immediate_quest_fame_gained); \
    SERIALIZE(75, number_of_existing_quests); \
    SERIALIZE(76, basic_point_of_home_rank); \
    SERIALIZE(77, total_deco_value); \
    SERIALIZE(78, total_heirloom_value); \
    SERIALIZE(79, reset_world_map_in_diastrophism_flag); \
    SERIALIZE(80, cargo_weight); \
    SERIALIZE(81, initial_cart_limit); \
    SERIALIZE(82, current_cart_limit); \
    SERIALIZE(83, protects_from_bad_weather); \
    SERIALIZE(84, left_minutes_of_executing_quest); \
    SERIALIZE(85, ether_disease_stage); \
    SERIALIZE(87, executing_immediate_quest_time_left_display_period); \
    SERIALIZE(88, time_when_textbook_becomes_available); \
    SERIALIZE(89, light); \
    SERIALIZE(90, continuous_active_hours); \
    SERIALIZE(91, activity_about_to_start); \
    SERIALIZE(92, sleep_experience); \
    SERIALIZE(93, acquirable_feat_count); \
    SERIALIZE(94, chara_last_attacked_by_player); \
    SERIALIZE(95, wish_count); \
    SERIALIZE(96, version); \
    SERIALIZE(97, rights_to_succeed_to); \
    SERIALIZE(98, character_and_status_for_gene); \
    SERIALIZE(99, next_voting_time); \
    SERIALIZE_ARRAY(120, ranks); \
    SERIALIZE_ARRAY(140, rank_deadlines); \
    SERIALIZE_ARRAY(160, taken_quests); \
    SERIALIZE(170, cost_to_hire); \
    SERIALIZE(171, rogue_boss_encountered); \
    SERIALIZE(179, left_bill); \
    SERIALIZE(180, distance_between_town); \
    SERIALIZE(181, departure_date); \
    SERIALIZE(182, left_town_map); \
    SERIALIZE(183, mount); \
    SERIALIZE(184, map_regenerate_count); \
    SERIALIZE(185, catches_god_signal); \
    SERIALIZE(186, void_next_lord_floor); \
    SERIALIZE(187, reveals_religion); \
    SERIALIZE_ARRAY(200, exhelp_flags); \
    SERIALIZE(250, quest_flags.tutorial); \
    SERIALIZE(252, quest_flags.main_quest); \
    SERIALIZE(253, quest_flags.magic_stone_of_fool); \
    SERIALIZE(254, quest_flags.magic_stone_of_sage); \
    SERIALIZE(255, quest_flags.magic_stone_of_king); \
    SERIALIZE(256, used_casino_once); \
    SERIALIZE(257, has_not_been_to_vernis); \
    SERIALIZE(258, released_fire_giant); \
    SERIALIZE(259, fire_giant); \
    SERIALIZE(260, holy_well_count); \
    SERIALIZE(261, quest_flags.duration_of_kamikaze_attack); \
    SERIALIZE(262, diastrophism_flag); \
    SERIALIZE(263, guild.belongs_to_mages_guild); \
    SERIALIZE(264, guild.belongs_to_fighters_guild); \
    SERIALIZE(265, guild.belongs_to_thieves_guild); \
    SERIALIZE(266, guild.mages_guild_quota); \
    SERIALIZE(267, guild.fighters_guild_quota); \
    SERIALIZE(268, guild.fighters_guild_target); \
    SERIALIZE(269, guild.thieves_guild_quota); \
    SERIALIZE(450, quest_flags.putit_attacks); \
    SERIALIZE(451, quest_flags.thieves_hideout); \
    SERIALIZE(452, quest_flags.nightmare); \
    SERIALIZE(453, quest_flags.pael_and_her_mom); \
    SERIALIZE(454, quest_flags.wife_collector); \
    SERIALIZE(455, quest_flags.puppys_cave); \
    SERIALIZE(456, quest_flags.cat_house); \
    SERIALIZE(457, quest_flags.defense_line); \
    SERIALIZE(458, quest_flags.novice_knight); \
    SERIALIZE(459, quest_flags.kamikaze_attack); \
    SERIALIZE(460, quest_flags.mias_dream); \
    SERIALIZE(461, quest_flags.rare_books); \
    SERIALIZE(462, quest_flags.pyramid_trial); \
    SERIALIZE(463, quest_flags.red_blossom_in_palmia); \
    SERIALIZE(464, quest_flags.ambitious_scientist); \
    SERIALIZE(465, quest_flags.sewer_sweeping); \
    SERIALIZE(466, guild.joining_mages_guild); \
    SERIALIZE(467, guild.joining_fighters_guild); \
    SERIALIZE(468, guild.joining_thieves_guild); \
    SERIALIZE(469, guild.mages_guild_quota_recurring); \
    SERIALIZE(470, guild.fighters_guild_quota_recurring); \
    SERIALIZE(471, guild.thieves_guild_quota_recurring); \
    SERIALIZE(472, quest_flags.minotaur_king); \
    SERIALIZE(473, quest_flags.little_sister); \
    SERIALIZE(474, quest_flags.blue_capsule_drug); \
    SERIALIZE_ARRAY(700, ether_disease_history); \
    SERIALIZE_ARRAY(750, tracked_skills); \
    SERIALIZE(800, ether_disease_speed); \
    SERIALIZE(801, left_turns_of_timestop); \
    SERIALIZE(802, ex_arena_wins); \
    SERIALIZE(803, ex_arena_level); \
    SERIALIZE(804, time_when_uploding_becomes_available); \
    SERIALIZE(805, play_time); \
    SERIALIZE(806, last_etherwind_month); \
    SERIALIZE(807, god_rank); \
    SERIALIZE(808, player_is_changing_equipment); \
    SERIALIZE(809, proc_damage_events_flag); \
    SERIALIZE(810, quest_flags.kill_count_of_little_sister); \
    SERIALIZE(811, quest_flags.save_count_of_little_sister); \
    SERIALIZE(812, quest_flags.gift_count_of_little_sister); \
    SERIALIZE(813, tcg_used_deck); \
    SERIALIZE(814, number_of_waiting_guests); \
    SERIALIZE(815, politics_map_id); \
    SERIALIZE(820, politics_tax_amount); \
    SERIALIZE(825, last_month_when_trainer_visited); \
    SERIALIZE(826, item_turns); \
    SERIALIZE( \
        827, next_level_minus_one_kumiromis_experience_becomes_available); \
    SERIALIZE(828, wizard); \
    SERIALIZE_ARRAY(830, tcg_decks); \
    SERIALIZE(850, destination_outer_map); \
    SERIALIZE(851, lost_wallet_count);


#define SERIALIZE GDATA_PACK
void GameData::pack_to(elona_vector1<int>& gdata)
{
    SERIALIZE_ALL();
}
#undef SERIALIZE

#define SERIALIZE GDATA_UNPACK
void GameData::unpack_from(elona_vector1<int>& gdata)
{
    SERIALIZE_ALL();
}
#undef SERIALIZE


void modify_crowd_density(int cc, int delta)
{
    if (cc >= 57)
    {
        game_data.crowd_density += delta;
        if (game_data.crowd_density < 0)
            game_data.crowd_density = 0;
    }
}



std::string DateTime::to_string() const
{
    std::stringstream ss;
    // clang-format off
    ss << std::setfill('0') << year << '/'
       << std::setw(2) << month << '/'
       << std::setw(2) << day << ' '
       << std::setw(2) << hour << ':'
       << std::setw(2) << minute << ':'
       << std::setw(2) << second;
    // clang-format on
    return ss.str();
}

} // namespace elona

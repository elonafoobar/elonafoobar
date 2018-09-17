#include "gdata.hpp"
#include "variables.hpp"



namespace elona
{


GameData game_data;
FoobarData foobar_data;

#define GDATA_PACK(x, ident) gdata(x) = ident;
#define GDATA_UNPACK(x, ident) ident = gdata(x);

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
    SERIALIZE(36, played_scene); \
    SERIALIZE(37, torch); \
    SERIALIZE(38, angband_flag); \
    SERIALIZE(39, number_of_learned_skills_by_trainer); \
\
    SERIALIZE(63, is_returning_or_escaping); \
    SERIALIZE(64, destination_map); \
    SERIALIZE(65, destination_dungeon_level); \
    SERIALIZE(66, previous_map2); \
    SERIALIZE(67, previous_dungeon_level); \
    SERIALIZE(68, previous_x); \
    SERIALIZE(69, previous_y); \
    SERIALIZE(70, executing_immediate_quest_type); \
    SERIALIZE(72, executing_immediate_quest); \
    SERIALIZE(75, number_of_existing_quests); \
    SERIALIZE(76, basic_point_of_home_rank); \
    SERIALIZE(80, cargo_weight); \
    SERIALIZE(81, initial_cart_limit); \
    SERIALIZE(82, current_cart_limit); \
    SERIALIZE(83, protects_from_bad_weather); \
    SERIALIZE(84, left_minutes_of_executing_quest); \
    SERIALIZE(85, ether_disease_stage); \
    SERIALIZE(88, time_when_textbook_becomes_available); \
    SERIALIZE(90, continuous_active_hours); \
    SERIALIZE(92, sleep_experience); \
    SERIALIZE(93, acquirable_feat_count); \
    SERIALIZE(95, wish_count); \
    SERIALIZE(96, version); \
    SERIALIZE(97, rights_to_succeed_to); \
    SERIALIZE(99, next_voting_time); \
    SERIALIZE(170, cost_to_hire); \
    SERIALIZE(179, left_bill); \
    SERIALIZE(180, distance_between_town); \
    SERIALIZE(181, departure_date); \
    SERIALIZE(182, left_town_map); \
    SERIALIZE(250, quest_flags.tutorial); \
    SERIALIZE(252, quest_flags.main_quest); \
    SERIALIZE(253, quest_flags.magic_stone_of_fool); \
    SERIALIZE(254, quest_flags.magic_stone_of_sage); \
    SERIALIZE(255, quest_flags.magic_stone_of_king); \
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
    SERIALIZE(472, quest_flags.minotaur_king); \
    SERIALIZE(473, quest_flags.little_sister); \
    SERIALIZE(474, quest_flags.blue_capsule_drug); \
    SERIALIZE(466, guild.joining_mages_guild); \
    SERIALIZE(467, guild.joining_fighters_guild); \
    SERIALIZE(468, guild.joining_thieves_guild); \
    SERIALIZE(469, guild.mages_guild_quota_recurring); \
    SERIALIZE(470, guild.fighters_guild_quota_recurring); \
    SERIALIZE(471, guild.thieves_guild_quota_recurring);


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



} // namespace elona

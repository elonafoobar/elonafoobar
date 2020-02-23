#include "save_update.hpp"

#include "../util/fileutil.hpp"
#include "../util/strutil.hpp"
#include "character.hpp"
#include "item.hpp"
#include "lua_env/handle_manager.hpp"
#include "lua_env/lua_env.hpp"
#include "lua_env/mod_serializer.hpp"
#include "putit.hpp"



namespace
{

// 15 -> 16
// Replace "core." to "elona." of class/race/god/portrait IDs.
void _update_save_data_15(const fs::path& save_dir)
{
    // Replace "core." to "elona." of class/race IDs.
    for (const auto& entry :
         filesystem::glob_files(save_dir, std::regex{u8R"(cdatan.*\.s[12])"}))
    {
        std::vector<std::string> lines;
        range::copy(
            fileutil::read_by_line(entry.path()), std::back_inserter(lines));

        // Read cdatan.
        std::vector<std::vector<std::string>> cdatan_;
        size_t idx{};
        for (const auto& line : lines)
        {
            const auto i = idx / 10;
            const auto j = idx % 10;
            if (j == 0)
            {
                cdatan_.emplace_back(10);
            }
            cdatan_.at(i).at(j) = line;
            ++idx;
        }

        for (auto&& chara : cdatan_)
        {
            const auto old_race_id = chara.at(2);
            if (!old_race_id.empty() &&
                strutil::starts_with(old_race_id, "core."))
            {
                chara.at(2) = "elona." + old_race_id.substr(5);
            }

            const auto old_class_id = chara.at(3);
            if (!old_class_id.empty() &&
                strutil::starts_with(old_class_id, "core."))
            {
                chara.at(3) = "elona." + old_class_id.substr(5);
            }
        }

        std::ofstream out{entry.path().native(), std::ios::binary};
        if (!out)
        {
            throw std::runtime_error(
                u8"Error: fail to write " +
                filepathutil::make_preferred_path_in_utf8(entry.path()));
        }

        for (const auto& chara : cdatan_)
        {
            for (const auto& line : chara)
            {
                out << line << std::endl;
            }
        }
    }


    // Replace "core." to "elona." of god/portrait IDs.
    for (const auto& entry : filesystem::glob_files(
             save_dir, std::regex{u8R"((g_)?cdata(_.*)?\.s[12])"}))
    {
        // Open file.
        std::ifstream fin{entry.path().native(), std::ios::binary};
        putit::BinaryIArchive iar{fin};

        // Prepare a temporary output stream.
        // It is a string stream, but used as a memory stream here.
        // `std::stringstream` class does not convert line endings and
        // treat NUL as a terminator of string, so that it can be safely
        // used as a memory stream.
        std::ostringstream out;
        putit::BinaryOArchive oar{out};

        const auto is_cdatas1 = entry.path().filename() == "cdata.s1" ||
            entry.path().filename() == "g_cdata.s1";
        const auto begin = is_cdatas1 ? 0 : 57;
        const auto end = is_cdatas1 ? 57 : 245;
        for (int idx = begin; idx < end; ++idx)
        {
            // DO NOT use usual serialization utilities to migrate old data
            // safely because they may be changed in the future version.

            // Prepare variables.
            Character::State state_ = Character::State::empty;
            Position position;
            Position next_position;
            int time_to_revive = 0;
            int vision_flag = 0;
            int image = 0;
            int sex = 0;
            int relationship = 0;
            int turn_cost = 0;
            int current_speed = 0;
            int item_which_will_be_used = 0;
            std::string portrait;
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
            Quality quality = Quality::none;
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
            GodId god_id;
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
            Activity continuous_action;
            int stops_continuous_action_if_damaged = 0;
            int quality_of_performance = 0;
            int tip_gold = 0;
            int character_role = 0;
            int shop_rank = 0;
            int continuous_action_target = 0;
            int shop_store_id = 0;
            int time_to_restore = 0;
            int cnpc_id = 0;
            Position initial_position;
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

            std::vector<int> growth_buffs(10);
            std::vector<int> body_parts(30);
            std::vector<int> normal_actions;
            std::vector<int> special_actions;
            std::vector<Buff> buffs(16);
            std::vector<int> attr_adjs(10);

            std::bitset<sizeof(int) * 8 * 50> _flags;

            int _156 = 0;
            int _203 = 0;
            Position target_position;

            // Load character data.
            {
                iar(state_);
                iar(position);
                iar(next_position);
                iar(time_to_revive);
                iar(vision_flag);
                iar(image);
                iar(sex);
                iar(relationship);
                iar(turn_cost);
                iar(current_speed);
                iar(item_which_will_be_used);
                iar(portrait);
                iar(interest);
                iar(time_interest_revive);
                iar(personality);
                iar(impression);
                iar(talk_type);
                iar(height);
                iar(weight);
                iar(birth_year);
                iar(nutrition);
                iar(can_talk);
                iar(quality);
                iar(turn);
                iar(id);
                iar(vision_distance);
                iar(enemy_id);
                iar(gold);
                iar(platinum_coin);
                iar(equipment_type);
                iar(melee_attack_type);
                iar(fame);
                iar(experience);
                iar(required_experience);
                iar(speed_percentage);
                iar(level);
                iar(speed_percentage_in_next_turn);
                iar(skill_bonus);
                iar(total_skill_bonus);
                iar(inventory_weight);
                iar(max_inventory_weight);
                iar(inventory_weight_type);
                iar(max_level);
                iar(karma);
                iar(hp);
                iar(max_hp);
                iar(sp);
                iar(max_sp);
                iar(mp);
                iar(max_mp);
                iar(heal_value_per_nether_attack);
                iar(god_id);
                iar(piety_point);
                iar(praying_point);
                iar(sum_of_equipment_weight);
                iar(special_attack_type);
                iar(rate_to_pierce);
                iar(rate_of_critical_hit);
                iar(speed_correction_value);
                iar(original_relationship);
                iar(pv);
                iar(dv);
                iar(hit_bonus);
                iar(damage_bonus);
                iar(pv_correction_value);
                iar(dv_correction_value);
                iar(damage_reaction_info);
                iar(emotion_icon);
                iar(current_map);
                iar(current_dungeon_level);
                iar(related_quest_id);
                iar(direction);
                iar(period_of_contract);
                iar(hire_count);
                iar(insanity);
                iar(curse_power);
                iar(extra_attack);
                iar(extra_shot);
                iar(decrease_physical_damage);
                iar(nullify_damage);
                iar(cut_counterattack);
                iar(anorexia_count);
                iar(continuous_action);
                iar(stops_continuous_action_if_damaged);
                iar(quality_of_performance);
                iar(tip_gold);
                iar(character_role);
                iar(shop_rank);
                iar(continuous_action_target);
                iar(shop_store_id);
                iar(time_to_restore);
                iar(cnpc_id);
                iar(initial_position);
                iar(hate);
                iar(ai_calm);
                iar(ai_move);
                iar(ai_dist);
                iar(ai_act_sub_freq);
                iar(ai_heal);
                iar(element_of_unarmed_attack);
                iar(poisoned);
                iar(sleep);
                iar(paralyzed);
                iar(blind);
                iar(confused);
                iar(fear);
                iar(dimmed);
                iar(drunk);
                iar(bleeding);
                iar(wet);
                iar(insane);
                iar(sick);
                iar(gravity);
                iar(choked);
                iar(furious);
                iar(growth_buffs);
                iar(body_parts);
                iar(normal_actions);
                iar(special_actions);
                iar(buffs);
                iar(attr_adjs);
                iar(_flags);
                iar(_156);
                iar(_203);
                iar(target_position);
            }
            {
                if (strutil::starts_with(portrait, "core."))
                {
                    portrait = "elona." + portrait.substr(5);
                }
                if (strutil::starts_with(god_id, "core."))
                {
                    god_id = "elona." + god_id.substr(5);
                }
            }
            // Dump character data to the memory stream.
            {
                oar(state_);
                oar(position);
                oar(next_position);
                oar(time_to_revive);
                oar(vision_flag);
                oar(image);
                oar(sex);
                oar(relationship);
                oar(turn_cost);
                oar(current_speed);
                oar(item_which_will_be_used);
                oar(portrait);
                oar(interest);
                oar(time_interest_revive);
                oar(personality);
                oar(impression);
                oar(talk_type);
                oar(height);
                oar(weight);
                oar(birth_year);
                oar(nutrition);
                oar(can_talk);
                oar(quality);
                oar(turn);
                oar(id);
                oar(vision_distance);
                oar(enemy_id);
                oar(gold);
                oar(platinum_coin);
                oar(equipment_type);
                oar(melee_attack_type);
                oar(fame);
                oar(experience);
                oar(required_experience);
                oar(speed_percentage);
                oar(level);
                oar(speed_percentage_in_next_turn);
                oar(skill_bonus);
                oar(total_skill_bonus);
                oar(inventory_weight);
                oar(max_inventory_weight);
                oar(inventory_weight_type);
                oar(max_level);
                oar(karma);
                oar(hp);
                oar(max_hp);
                oar(sp);
                oar(max_sp);
                oar(mp);
                oar(max_mp);
                oar(heal_value_per_nether_attack);
                oar(god_id);
                oar(piety_point);
                oar(praying_point);
                oar(sum_of_equipment_weight);
                oar(special_attack_type);
                oar(rate_to_pierce);
                oar(rate_of_critical_hit);
                oar(speed_correction_value);
                oar(original_relationship);
                oar(pv);
                oar(dv);
                oar(hit_bonus);
                oar(damage_bonus);
                oar(pv_correction_value);
                oar(dv_correction_value);
                oar(damage_reaction_info);
                oar(emotion_icon);
                oar(current_map);
                oar(current_dungeon_level);
                oar(related_quest_id);
                oar(direction);
                oar(period_of_contract);
                oar(hire_count);
                oar(insanity);
                oar(curse_power);
                oar(extra_attack);
                oar(extra_shot);
                oar(decrease_physical_damage);
                oar(nullify_damage);
                oar(cut_counterattack);
                oar(anorexia_count);
                oar(continuous_action);
                oar(stops_continuous_action_if_damaged);
                oar(quality_of_performance);
                oar(tip_gold);
                oar(character_role);
                oar(shop_rank);
                oar(continuous_action_target);
                oar(shop_store_id);
                oar(time_to_restore);
                oar(cnpc_id);
                oar(initial_position);
                oar(hate);
                oar(ai_calm);
                oar(ai_move);
                oar(ai_dist);
                oar(ai_act_sub_freq);
                oar(ai_heal);
                oar(element_of_unarmed_attack);
                oar(poisoned);
                oar(sleep);
                oar(paralyzed);
                oar(blind);
                oar(confused);
                oar(fear);
                oar(dimmed);
                oar(drunk);
                oar(bleeding);
                oar(wet);
                oar(insane);
                oar(sick);
                oar(gravity);
                oar(choked);
                oar(furious);
                oar(growth_buffs);
                oar(body_parts);
                oar(normal_actions);
                oar(special_actions);
                oar(buffs);
                oar(attr_adjs);
                oar(_flags);
                oar(_156);
                oar(_203);
                oar(target_position);
            }
        }

        // Close the file and reopen to write.
        fin.close();
        std::ofstream fout{entry.path().native(), std::ios::binary};
        // Write the data.
        fout.write(out.str().c_str(), out.str().size());
    }
}



void _update_save_data(const fs::path& save_dir, int serial_id)
{
    switch (serial_id)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
        throw std::runtime_error{
            "Too old save! Please update the save in v0.5.0 first."};
    case 15: _update_save_data_15(save_dir); break;
    default: assert(0); break;
    }
}

} // namespace



namespace elona
{

void update_save_data(const fs::path& save_dir)
{
    const auto version_filepath = save_dir / "version.s0";

    Version version;
    putit::BinaryIArchive::load(version_filepath, version);

    if (version.serial_id > latest_version.serial_id)
    {
        // FIXME:
        // It is far away from the best solution, but we do not have the way to
        // report a fatal error to end-users by GUI window, except for
        // OS-builtin exception handling.
        throw std::runtime_error{"Incompatible save data!"};
    }

    for (int serial_id = version.serial_id;
         serial_id != latest_version.serial_id;
         ++serial_id)
    {
        ELONA_LOG("save.update") << "Update save data from #" << serial_id
                                 << " to #" << (serial_id + 1) << ".";
        _update_save_data(save_dir, serial_id);
    }
    version = latest_version;
    putit::BinaryOArchive::save(version_filepath, version);
}

} // namespace elona

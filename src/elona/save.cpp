#include "save.hpp"
#include "audio.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "ctrl_file.hpp"
#include "draw.hpp"
#include "filesystem.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "log.hpp"
#include "lua_env/lua_env.hpp"
#include "putit.hpp"
#include "ui.hpp"
#include "util.hpp"



namespace elona
{

// TODO: split
void update_save_data(const fs::path& save_dir, int serial_id)
{
    switch (serial_id)
    {
    case 0:
    {
        bool is_autodig_enabled;
        {
            int dummy_i;
            std::string dummy_s;
            std::ifstream in{(save_dir / "foobar_data.s1").native(),
                             std::ios::binary};
            putit::BinaryIArchive ar{in};
            ar.load(dummy_i);
            ar.load(dummy_i);
            ar.load(dummy_i);
            ar.load(dummy_s);
            ar.load(dummy_s);
            ar.load(dummy_s);
            ar.load(is_autodig_enabled);
        }
        {
            std::ofstream out{(save_dir / "foobar_data.s1").native(),
                              std::ios::binary};
            putit::BinaryOArchive ar{out};
            ar.save(is_autodig_enabled);
        }
        break;
    }
    case 1:
    {
        // Prepend "core." prefix to old race ID.
        for (const auto& entry : filesystem::dir_entries(
                 save_dir,
                 filesystem::DirEntryRange::Type::file,
                 std::regex{u8R"(cdatan.*\.s[12])"}))
        {
            std::vector<std::string> lines;
            range::copy(
                fileutil::read_by_line(entry.path()),
                std::back_inserter(lines));

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

            // Prepend "core." prefix to the old race ID.
            for (auto&& chara : cdatan_)
            {
                const auto old_race_id = chara.at(2);
                if (!old_race_id.empty() &&
                    !strutil::starts_with(old_race_id, "core."))
                {
                    ELONA_LOG(
                        "[Save data] Prepend \"core\" prefix to "
                        << chara.at(0) << ": " << old_race_id);
                    chara.at(2) = "core." + old_race_id;
                }
            }

            std::ofstream out{entry.path().native(), std::ios::binary};
            if (!out)
            {
                throw std::runtime_error(
                    u8"Error: fail to write " +
                    filesystem::make_preferred_path_in_utf8(entry.path()));
            }

            for (const auto& chara : cdatan_)
            {
                for (const auto& line : chara)
                {
                    out << line << std::endl;
                }
            }
        }
        break;
    }
    case 2:
    {
        // Prepend "core." prefix to old class ID.
        for (const auto& entry : filesystem::dir_entries(
                 save_dir,
                 filesystem::DirEntryRange::Type::file,
                 std::regex{u8R"(cdatan.*\.s[12])"}))
        {
            std::vector<std::string> lines;
            range::copy(
                fileutil::read_by_line(entry.path()),
                std::back_inserter(lines));

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

            // Prepend "core." prefix to the old class ID.
            for (auto&& chara : cdatan_)
            {
                const auto old_class_id = chara.at(3);
                if (!old_class_id.empty() &&
                    !strutil::starts_with(old_class_id, "core."))
                {
                    ELONA_LOG(
                        "[Save data] Prepend \"core\" prefix to "
                        << chara.at(0) << ": " << old_class_id);
                    chara.at(3) = "core." + old_class_id;
                }
            }

            std::ofstream out{entry.path().native(), std::ios::binary};
            if (!out)
            {
                throw std::runtime_error(
                    u8"Error: fail to write " +
                    filesystem::make_preferred_path_in_utf8(entry.path()));
            }

            for (const auto& chara : cdatan_)
            {
                for (const auto& line : chara)
                {
                    out << line << std::endl;
                }
            }
        }
        break;
    }
    case 3:
    {
        // Prepend "core." prefix to old class ID.
        for (const auto& entry : filesystem::dir_entries(
                 save_dir,
                 filesystem::DirEntryRange::Type::file,
                 std::regex{u8R"((g_)?cdata(_.*)?\.s[12])"}))
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
            const auto begin = is_cdatas1 ? 0 : ELONA_MAX_PARTY_CHARACTERS;
            const auto end =
                is_cdatas1 ? ELONA_MAX_PARTY_CHARACTERS : ELONA_MAX_CHARACTERS;
            for (int idx = begin; idx < end; ++idx)
            {
                // DO NOT use usual serialization utilities to migrate old data
                // safely because they may be changed in the future version.

                // Prepare variables.
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
                ContinuousAction continuous_action;
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

                int _156 = 0;
                int _203 = 0;
                int _205 = 0;
                int _206 = 0;

                Character::State state_ = Character::State::empty;

                std::bitset<sizeof(int) * 8 * 50> _flags;

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
                    range::for_each(growth_buffs, [&](auto&& growth_buff) {
                        iar(growth_buff);
                    });
                    range::for_each(
                        body_parts, [&](auto&& body_part) { iar(body_part); });
                    iar(normal_actions);
                    iar(special_actions);
                    range::for_each(buffs, [&](auto&& buff) { iar(buff); });
                    range::for_each(
                        attr_adjs, [&](auto&& attr_adj) { iar(attr_adj); });
                    iar(_flags);
                    iar(_156);
                    iar(_203);
                    iar(_205);
                    iar(_206);
                }
                // Prepend "core" prefix to old god IDs.
                if (god_id != core_god::eyth &&
                    !strutil::starts_with(god_id, "core."))
                {
                    ELONA_LOG(
                        "[Save data] Prepend \"core\" prefix to character("
                        << idx << "): " << god_id);
                    god_id = "core." + god_id;
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
                    range::for_each(growth_buffs, [&](auto&& growth_buff) {
                        oar(growth_buff);
                    });
                    range::for_each(
                        body_parts, [&](auto&& body_part) { oar(body_part); });
                    oar(normal_actions);
                    oar(special_actions);
                    range::for_each(buffs, [&](auto&& buff) { oar(buff); });
                    range::for_each(
                        attr_adjs, [&](auto&& attr_adj) { oar(attr_adj); });
                    oar(_flags);
                    oar(_156);
                    oar(_203);
                    oar(_205);
                    oar(_206);
                }
            }

            // Close the file and reopen to write.
            fin.close();
            std::ofstream fout{entry.path().native(), std::ios::binary};
            // Write the data.
            fout.write(out.str().c_str(), out.str().size());
        }
        break;
    }
    case 4:
    {
        // Replace double bed and happy bed's image.
        for (const auto& entry : filesystem::dir_entries(
                 save_dir,
                 filesystem::DirEntryRange::Type::file,
                 std::regex{u8R"((g_)?inv(_.*)?\.s[12])"}))
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

            const auto is_invs1 = entry.path().filename() == "inv.s1" ||
                entry.path().filename() == "g_inv.s1";
            const auto begin = is_invs1 ? 0 : 1320;
            const auto end = is_invs1 ? 1320 : 5480;
            for (int idx = begin; idx < end; ++idx)
            {
                // DO NOT use usual serialization utilities to migrate old data
                // safely because they may be changed in the future version.

                // Prepare variables.
                int number_ = 0;
                int value = 0;
                int image = 0;
                int id = 0;
                Quality quality = Quality::none;
                Position position;
                int weight = 0;
                IdentifyState identification_state =
                    IdentifyState::unidentified;
                int count = 0;
                int dice_x = 0;
                int dice_y = 0;
                int damage_bonus = 0;
                int hit_bonus = 0;
                int dv = 0;
                int pv = 0;
                int skill = 0;
                CurseState curse_state = CurseState::none;
                int body_part = 0;
                int function = 0;
                int enhancement = 0;
                int own_state = 0;
                int color = 0;
                int subname = 0;
                int material = 0;
                int param1 = 0;
                int param2 = 0;
                int param3 = 0;
                int param4 = 0;
                int difficulty_of_identification = 0;
                int turn = 0;

                int flags = 0;

                std::vector<Enchantment> enchantments(15);

                // Load item data.
                {
                    iar(number_);
                    iar(value);
                    iar(image);
                    iar(id);
                    iar(quality);
                    iar(position);
                    iar(weight);
                    iar(identification_state);
                    iar(count);
                    iar(dice_x);
                    iar(dice_y);
                    iar(damage_bonus);
                    iar(hit_bonus);
                    iar(dv);
                    iar(pv);
                    iar(skill);
                    iar(curse_state);
                    iar(body_part);
                    iar(function);
                    iar(enhancement);
                    iar(own_state);
                    iar(color);
                    iar(subname);
                    iar(material);
                    iar(param1);
                    iar(param2);
                    iar(param3);
                    iar(param4);
                    iar(difficulty_of_identification);
                    iar(turn);
                    iar(flags);
                    range::for_each(enchantments, [&](auto&& enchantment) {
                        iar(enchantment);
                    });
                }
                // Prepend "core" prefix to old god IDs.
                if (image == 649)
                {
                    ELONA_LOG("[Save data] Change item chip 649 to 261.");
                    image = 261;
                }
                // Dump item data to the memory stream.
                {
                    oar(number_);
                    oar(value);
                    oar(image);
                    oar(id);
                    oar(quality);
                    oar(position);
                    oar(weight);
                    oar(identification_state);
                    oar(count);
                    oar(dice_x);
                    oar(dice_y);
                    oar(damage_bonus);
                    oar(hit_bonus);
                    oar(dv);
                    oar(pv);
                    oar(skill);
                    oar(curse_state);
                    oar(body_part);
                    oar(function);
                    oar(enhancement);
                    oar(own_state);
                    oar(color);
                    oar(subname);
                    oar(material);
                    oar(param1);
                    oar(param2);
                    oar(param3);
                    oar(param4);
                    oar(difficulty_of_identification);
                    oar(turn);
                    oar(flags);
                    range::for_each(enchantments, [&](auto&& enchantment) {
                        oar(enchantment);
                    });
                }
            }

            // Close the file and reopen to write.
            fin.close();
            std::ofstream fout{entry.path().native(), std::ios::binary};
            // Write the data.
            fout.write(out.str().c_str(), out.str().size());
        }
        break;
    }
    default: break;
    }
}



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
        ELONA_LOG(
            "[Save data] Update save data from #" << serial_id << " to #"
                                                  << (serial_id + 1) << ".");
        update_save_data(save_dir, serial_id);
    }
    version = latest_version;
    putit::BinaryOArchive::save(version_filepath, version);
}



void load_save_data()
{
    ELONA_LOG("Load save data: " << playerid);

    // TODO instead serialize/deserialize data
    lua::lua->get_handle_manager().clear_map_local_handles();

    Save::instance().clear();
    writeloadedbuff_clear();

    ctrl_file(FileOperation::temp_dir_delete);
    const auto save_dir = filesystem::dir::save(playerid);

    // TODO: Delete this line when the v1.0.0 stable is released!
    if (!fs::exists(save_dir / "version.s0"))
    {
        if (!fs::exists(save_dir / "foobar_data.s1"))
        {
            throw std::runtime_error{
                "Please update your save in v0.2.7 first."};
        }

        int major;
        int minor;
        int patch;
        {
            std::ifstream in{(save_dir / "foobar_data.s1").native(),
                             std::ios::binary};
            putit::BinaryIArchive ar{in};
            ar.load(major);
            ar.load(minor);
            ar.load(patch);
        }

        if (!(major == 0 && minor == 2 && patch == 7))
        {
            throw std::runtime_error{
                "Please update your save in v0.2.7 first."};
        }

        Version v028 = {0, 2, 8, 0, "", "", ""};
        putit::BinaryOArchive::save(save_dir / "version.s0", v028);
    }

    update_save_data(save_dir);
    ctrl_file(FileOperation2::global_read, save_dir);

    chara_delete(56);
    set_item_info();
    for (int cnt = 0; cnt < 16; ++cnt)
    {
        if (cdata[cnt].has_own_sprite() == 1 || cnt == 0)
        {
            create_pcpic(cnt, true);
        }
    }
    if (game_data.wizard == 1)
    {
        cdatan(1, 0) = u8"*Debug*"s;
    }
    refresh_speed(cdata.player());
    time_begin = timeGetTime() / 1000;
    ELONA_LOG("Load save data end: " << playerid);
}



void do_save_game()
{
    snd("core.write1");
    save_game();
    txt(i18n::s.get("core.locale.ui.save"), Message::color{ColorIndex::orange});
}



void save_game()
{
    ELONA_LOG("Save game: " << playerid);

    int save_f = 0;
    if (game_data.current_map == mdata_t::MapId::show_house)
    {
        txt(i18n::s.get("core.locale.misc.save.cannot_save_in_user_map"),
            Message::color{ColorIndex::red});
        update_screen();
        return;
    }
    ctrl_file(FileOperation::map_write);
    ctrl_file(FileOperation2::map_items_write, u8"inv_"s + mid + u8".s2");
    save_f = 0;
    for (const auto& entry : filesystem::dir_entries(
             filesystem::dir::save(), filesystem::DirEntryRange::Type::dir))
    {
        if (filesystem::to_utf8_path(entry.path().filename()) == playerid)
        {
            save_f = 1;
            break;
        }
    }
    const auto save_dir = filesystem::dir::save(playerid);
    if (save_f == 0)
    {
        fs::create_directory(save_dir);
    }
    Save::instance().save(save_dir);
    ctrl_file(FileOperation2::global_write, save_dir);
    Save::instance().clear();
    ELONA_LOG("Save game: finish");
}

} // namespace elona

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

void _update_save_data_0(const fs::path& save_dir)
{
    bool is_autodig_enabled;
    {
        int dummy_i;
        std::string dummy_s;
        std::ifstream in{(save_dir / "foobar_data.s1").native(),
                         std::ios::binary};
        putit::BinaryIArchive ar{in};
        ar(dummy_i);
        ar(dummy_i);
        ar(dummy_i);
        ar(dummy_s);
        ar(dummy_s);
        ar(dummy_s);
        ar(is_autodig_enabled);
    }
    {
        std::ofstream out{(save_dir / "foobar_data.s1").native(),
                          std::ios::binary};
        putit::BinaryOArchive ar{out};
        ar(is_autodig_enabled);
    }
}



void _update_save_data_1(const fs::path& save_dir)
{
    // Prepend "core." prefix to old race ID.
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

        // Prepend "core." prefix to the old race ID.
        for (auto&& chara : cdatan_)
        {
            const auto old_race_id = chara.at(2);
            if (!old_race_id.empty() &&
                !strutil::starts_with(old_race_id, "core."))
            {
                ELONA_LOG("save.update") << "Prepend \"core\" prefix to "
                                         << chara.at(0) << ": " << old_race_id;
                chara.at(2) = "core." + old_race_id;
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
}



void _update_save_data_2(const fs::path& save_dir)
{
    // Prepend "core." prefix to old class ID.
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

        // Prepend "core." prefix to the old class ID.
        for (auto&& chara : cdatan_)
        {
            const auto old_class_id = chara.at(3);
            if (!old_class_id.empty() &&
                !strutil::starts_with(old_class_id, "core."))
            {
                ELONA_LOG("save.update") << "Prepend \"core\" prefix to "
                                         << chara.at(0) << ": " << old_class_id;
                chara.at(3) = "core." + old_class_id;
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
}



void _update_save_data_3(const fs::path& save_dir)
{
    // Prepend "core." prefix to old class ID.
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
                ELONA_LOG("save.update")
                    << "Prepend \"core\" prefix to character(" << idx
                    << "): " << god_id;
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
}



void _update_save_data_4(const fs::path& save_dir)
{
    // Replace double bed and happy bed's image.
    for (const auto& entry : filesystem::glob_files(
             save_dir, std::regex{u8R"((g_)?inv(_.*)?\.s[12])"}))
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
            IdentifyState identify_state = IdentifyState::unidentified;
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
                iar(identify_state);
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
                ELONA_LOG("save.update") << "Change item chip 649 to 261.";
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
                oar(identify_state);
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
}



std::string _update_save_data_5_convert_portrait_id(int old_id, int sex)
{
    switch (old_id)
    {
    case -1: return "";
    case 0: return sex ? "core.woman1" : "core.man1";
    case 1: return sex ? "core.woman2" : "core.man2";
    case 2: return sex ? "core.woman3" : "core.man3";
    case 3: return sex ? "core.woman4" : "core.man4";
    case 4: return sex ? "core.woman5" : "core.man5";
    case 5: return sex ? "core.woman6" : "core.man6";
    case 6: return sex ? "core.woman7" : "core.man7";
    case 7: return sex ? "core.woman8" : "core.man8";
    case 8: return sex ? "core.woman9" : "core.man9";
    case 9: return sex ? "core.woman10" : "core.man10";
    case 10: return sex ? "core.woman11" : "core.man11";
    case 11: return sex ? "core.woman12" : "core.man12";
    case 12: return sex ? "core.woman13" : "core.man13";
    case 13: return sex ? "core.woman14" : "core.man14";
    case 14: return sex ? "core.woman15" : "core.man15";
    case 15: return sex ? "core.woman16" : "core.man16";
    case 16: return sex ? "core.woman17" : "core.man17";
    case 17: return sex ? "core.woman18" : "core.man18";
    case 18: return sex ? "core.woman19" : "core.man19";
    case 19: return sex ? "core.woman20" : "core.man20";
    case 20: return sex ? "core.woman21" : "core.man21";
    case 21: return sex ? "core.woman22" : "core.man22";
    case 22: return sex ? "core.woman23" : "core.man23";
    case 23: return sex ? "core.woman24" : "core.man24";
    case 24: return sex ? "core.woman25" : "core.man25";
    case 25: return sex ? "core.woman26" : "core.man26";
    case 26: return sex ? "core.woman27" : "core.man27";
    case 27: return sex ? "core.woman28" : "core.man28";
    case 28: return sex ? "core.woman29" : "core.man29";
    case 29: return sex ? "core.woman30" : "core.man30";
    case 30: return sex ? "core.woman31" : "core.man31";
    case 31: return sex ? "core.woman32" : "core.man32";
    case 32: return sex ? "core.woman34" : "core.man33";
    case 33: return sex ? "core.woman35" : "core.gilbert";
    case 34: return sex ? "core.mia" : "core.man34";
    case 35: return sex ? "core.woman36" : "core.man35";
    case 36: return sex ? "core.woman37" : "core.arnord";
    case 37: return sex ? "core.woman38" : "core.man36";
    case 38: return sex ? "core.woman39" : "core.balzak";
    case 39: return sex ? "core.woman40" : "core.conery";
    case 40: return sex ? "core.woman41" : "core.man39";
    case 41: return sex ? "core.woman42" : "core.man40";
    case 42: return sex ? "core.woman43" : "core.man41";
    case 43: return sex ? "core.woman44" : "core.man42";
    case 44: return sex ? "core.woman45" : "core.man43";
    case 45: return sex ? "core.woman46" : "core.man44";
    case 46: return "";
    case 47: return "";
    case 48: return sex ? "core.larnneire" : "core.barius";
    case 49: return sex ? "core.shena" : "core.loyter";
    case 50: return sex ? "core.miches" : "core.bethel";
    case 51: return sex ? "core.isca" : "core.orphe";
    case 52: return sex ? "core.woman47" : "core.norne";
    case 53: return sex ? "core.woman48" : "core.zeome";
    case 54: return sex ? "core.stersha" : "core.saimore";
    case 55: return sex ? "core.erystia" : "core.xabi";
    case 56: return sex ? "core.liana" : "core.karam";
    case 57: return sex ? "core.woman49" : "core.lomias";
    case 58: return sex ? "" : "core.man45";
    case 59: return sex ? "" : "core.sevilis";
    case 60: return sex ? "" : "core.man46";
    case 61: return sex ? "" : "core.man47";
    case 62: return sex ? "" : "core.man48";
    case 63: return "";
    default: return "";
    }
}



void _update_save_data_5(const fs::path& save_dir)
{
    // Convert portrait field.
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
            // Convert portrait from int to string.
            std::string portrait_;
            {
                portrait_ =
                    _update_save_data_5_convert_portrait_id(portrait, sex);
                if (idx == 0 && portrait_ == "")
                {
                    portrait_ = sex ? "core.woman1" : "core.man1";
                }
                ELONA_LOG("save.update")
                    << "Convert portrait ID of "
                    << "character(" << idx << "): " << portrait << " => "
                    << portrait_;
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
                oar(portrait_);
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
}



/// Updates save file from v6 to v7.
/// - Changes indoor flag of North Tyris south border, South Tyris north border,
///   and Test World north border in area data (adata.s1).
void _update_save_data_6(const fs::path& save_dir)
{
    const auto adata_filepath = save_dir / "adata.s1";
    // Temporary data for contents of `adata.s1`.
    std::vector<int> data(40 * 500, 0);

    {
        // Open file.
        std::ifstream in(adata_filepath.native(), std::ios::binary);
        putit::BinaryIArchive iar(in);

        // Load all of data `adata.s1` has.
        for (size_t j = 0; j < 500; ++j)
        {
            for (size_t i = 0; i < 40; ++i)
            {
                iar(data.at(j * 40 + i));
            }
        }
    }

    {
        // Modify indoor flags.

        const auto modify_indoor_flag = [&data](int map_id) {
            ELONA_LOG("save.update")
                << "Make the map(" << map_id << ") outdoor.";
            data.at(map_id * 40 + 21) = 2;
        };

        modify_indoor_flag(43); // North Tyris south border
        modify_indoor_flag(45); // South Tyris north border
        modify_indoor_flag(48); // Test World north border
    }

    {
        // Write the data.
        std::ofstream out(adata_filepath.native(), std::ios::binary);
        putit::BinaryOArchive oar(out);

        for (size_t j = 0; j < 500; ++j)
        {
            for (size_t i = 0; i < 40; ++i)
            {
                oar(data.at(j * 40 + i));
            }
        }
    }
}



/// Update save data from v7 to v8. Fix wrongly saved positions of
/// up/downstairs.
void _update_save_data_7(const fs::path& save_dir)
{
    for (const auto& entry : filesystem::glob_files(
             save_dir, std::regex{u8R"(mdata_(\d+)_(\d+)\.s2)"}))
    {
        // Temporary data for contents of each `mdata` file.
        std::vector<int> data(100, 0);

        {
            // Read mdata file.
            std::ifstream in{entry.path().native(), std::ios::binary};
            putit::BinaryIArchive iar{in};

            for (auto&& field : data)
            {
                iar(field);
            }
        }

        const auto width = data.at(0);
        const auto height = data.at(1);
        // Temporary data for contents of each `map` file. It is used to find
        // the positions of stairs.
        std::vector<int> cell_data(width * height * 10, 0);

        // Truncate directory part and "mdata". E.g., "_7_101.s2"
        const auto map_id_and_level =
            entry.path().filename().string().substr(5);
        const auto map_filepath = save_dir / ("map" + map_id_and_level);
        if (!fs::exists(map_filepath))
        {
            continue;
        }

        {
            // Read map file.
            std::ifstream in{map_filepath.native(), std::ios::binary};
            putit::BinaryIArchive iar{in};

            for (auto&& field : cell_data)
            {
                iar(field);
            }
        }

        // Find positions of upstairs/downstairs and rewrite the data if needed.
        int actual_stair_up_pos = 0;
        int actual_stair_down_pos = 0;
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                const auto feat =
                    cell_data.at(6 * height * width + y * width + x);
                const auto type = feat / 1000 % 100;
                if (type == 10)
                {
                    actual_stair_up_pos = y * 1000 + x;
                }
                if (type == 11)
                {
                    actual_stair_down_pos = y * 1000 + x;
                }
            }
        }

        auto fixed = false;
        if (actual_stair_down_pos != data.at(4))
        {
            Position old_downstairs_pos{data.at(5) % 1000, data.at(5) / 1000};
            Position new_downstairs_pos{actual_stair_down_pos % 1000,
                                        actual_stair_down_pos / 1000};

            ELONA_LOG("save.update")
                << "Correct downstairs position in " << entry.path().filename()
                << ": " << old_downstairs_pos << " -> " << new_downstairs_pos
                << ".";

            data.at(4) = actual_stair_down_pos;
            fixed = true;
        }
        if (actual_stair_up_pos != data.at(5))
        {
            Position old_upstairs_pos{data.at(4) % 1000, data.at(4) / 1000};
            Position new_upstairs_pos{actual_stair_up_pos % 1000,
                                      actual_stair_up_pos / 1000};

            ELONA_LOG("save.update")
                << "Correct upstairs position in " << entry.path().filename()
                << ": " << old_upstairs_pos << " -> " << new_upstairs_pos
                << ".";

            data.at(5) = actual_stair_up_pos;
            fixed = true;
        }

        if (!fixed)
        {
            continue;
        }

        {
            // Write mdata.
            std::ofstream out{entry.path().native(), std::ios::binary};
            putit::BinaryOArchive oar{out};

            for (auto&& field : data)
            {
                oar(field);
            }
        }
    }
}



/// Update save data from v8 to v9.
/// Write array length even if its size is fixed.
void _update_save_data_8(const fs::path& save_dir)
{
    // Character data
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

    // Item data
    for (const auto& entry : filesystem::glob_files(
             save_dir, std::regex{u8R"((g_)?inv(_.*)?\.s[12])"}))
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
            IdentifyState identify_state = IdentifyState::unidentified;
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

            std::bitset<32> _flags;

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
                iar(identify_state);
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
                iar(_flags);
                range::for_each(enchantments, [&](auto&& enchantment) {
                    iar(enchantment);
                });
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
                oar(identify_state);
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
                oar(_flags);
                oar(enchantments);
            }
        }

        // Close the file and reopen to write.
        fin.close();
        std::ofstream fout{entry.path().native(), std::ios::binary};
        // Write the data.
        fout.write(out.str().c_str(), out.str().size());
    }
}



/// Create new mod save data for saves without it.
void _update_save_data_9(const fs::path& save_dir)
{
    lua::ModSerializer mod_serializer(*lua::lua);

    // Global mod data
    {
        fs::path outpath = save_dir / "mod.s1";
        std::ofstream out{outpath.native(), std::ios::binary};
        putit::BinaryOArchive oar{out};
        mod_serializer.save_mod_store_data(
            oar, lua::ModInfo::StoreType::global);
    }

    // Global character handles
    {
        fs::path inpath = save_dir / "cdata.s1";
        std::ifstream fin{inpath.native(), std::ios::binary};
        putit::BinaryIArchive iar{fin};

        for (size_t index = 0; index < 57; ++index)
        {
            iar(cdata[index]);
            cdata[index].index = index;
            lua::lua->get_handle_manager().create_chara_handle(cdata[index]);
        }

        fs::path outpath = save_dir / "mod_cdata.s1";
        std::ofstream fout{outpath.native(), std::ios::binary};
        putit::BinaryOArchive oar{fout};

        mod_serializer.save_handles<Character>(
            oar, lua::ModInfo::StoreType::global);

        for (int index = 0; index < 57; index++)
        {
            cdata[index].set_state(Character::State::empty);
            lua::lua->get_handle_manager().remove_chara_handle(cdata[index]);
        }
    }

    // Global item handles
    {
        fs::path inpath = save_dir / "inv.s1";
        std::ifstream fin{inpath.native(), std::ios::binary};
        putit::BinaryIArchive iar{fin};

        for (size_t index = 0; index < 1320; ++index)
        {
            iar(inv[index]);
            inv[index].index = index;
            lua::lua->get_handle_manager().create_item_handle(inv[index]);
        }

        fs::path outpath = save_dir / "mod_inv.s1";
        std::ofstream fout{outpath.native(), std::ios::binary};
        putit::BinaryOArchive oar{fout};

        mod_serializer.save_handles<Item>(oar, lua::ModInfo::StoreType::global);

        for (int index = 0; index < 1320; index++)
        {
            inv[index].set_number(0);
            lua::lua->get_handle_manager().remove_item_handle(inv[index]);
        }
    }

    // Map local mod data
    for (const auto& entry :
         filesystem::glob_files(save_dir, std::regex{u8R"(map(_.*)?\.s2)"}))
    {
        fs::path outpath = save_dir /
            ("mod_"s + filepathutil::to_utf8_path(entry.path().filename()));
        std::ofstream fout{outpath.native(), std::ios::binary};
        putit::BinaryOArchive oar{fout};

        mod_serializer.save_mod_store_data(oar, lua::ModInfo::StoreType::map);
    }

    // Map local character handles
    for (const auto& entry :
         filesystem::glob_files(save_dir, std::regex{u8R"(cdata(_.*)?\.s2)"}))
    {
        std::ifstream fin{entry.path().native(), std::ios::binary};
        putit::BinaryIArchive iar{fin};

        for (size_t index = 57; index < 245; ++index)
        {
            iar(cdata[index]);
            cdata[index].index = index;
            lua::lua->get_handle_manager().create_chara_handle(cdata[index]);
        }

        fs::path outpath = save_dir /
            ("mod_"s + filepathutil::to_utf8_path(entry.path().filename()));
        std::ofstream fout{outpath.native(), std::ios::binary};
        putit::BinaryOArchive oar{fout};

        mod_serializer.save_handles<Character>(
            oar, lua::ModInfo::StoreType::map);

        for (int index = 57; index < 245; index++)
        {
            cdata[index].set_state(Character::State::empty);
            lua::lua->get_handle_manager().remove_chara_handle(cdata[index]);
        }
    }

    // Map local item handles
    for (const auto& entry :
         filesystem::glob_files(save_dir, std::regex{u8R"(inv(_.*)?\.s2)"}))
    {
        std::ifstream fin{entry.path().native(), std::ios::binary};
        putit::BinaryIArchive iar{fin};

        for (size_t index = 1320; index < 5480; ++index)
        {
            iar(inv[index]);
            inv[index].index = index;
            lua::lua->get_handle_manager().create_item_handle(inv[index]);
        }

        fs::path outpath = save_dir /
            ("mod_"s + filepathutil::to_utf8_path(entry.path().filename()));
        std::ofstream fout{outpath.native(), std::ios::binary};
        putit::BinaryOArchive oar{fout};

        mod_serializer.save_handles<Item>(oar, lua::ModInfo::StoreType::map);

        for (int index = 1320; index < 5480; index++)
        {
            inv[index].set_number(0);
            lua::lua->get_handle_manager().remove_item_handle(inv[index]);
        }
    }
}



/// Update save data from v10 to v11.
/// Update "shop*.s2" which have not been updated in _update_save_data_8() and
/// _update_save_data_9(). Migration code is similar to them except for target
/// files.
void _update_save_data_10(const fs::path& save_dir)
{
    lua::ModSerializer mod_serializer(*lua::lua);

    // _update_save_data_8
    // shop*.s2 files
    for (const auto& entry :
         filesystem::glob_files(save_dir, std::regex{u8R"(shop.*\.s2)"}))
    {
        if (fs::exists(
                save_dir /
                ("mod_" + filepathutil::to_utf8_path(entry.path().filename()))))
        {
            // This file is saved in new format. Skipping.
            continue;
        }

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

        const auto begin = 1320;
        const auto end = 5480;
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
            IdentifyState identify_state = IdentifyState::unidentified;
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

            std::bitset<32> _flags;

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
                iar(identify_state);
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
                iar(_flags);
                range::for_each(enchantments, [&](auto&& enchantment) {
                    iar(enchantment);
                });
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
                oar(identify_state);
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
                oar(_flags);
                oar(enchantments);
            }
        }

        // Close the file and reopen to write.
        fin.close();
        std::ofstream fout{entry.path().native(), std::ios::binary};
        // Write the data.
        fout.write(out.str().c_str(), out.str().size());
    }

    // _update_save_data_9
    // shop*.s2 files
    for (const auto& entry :
         filesystem::glob_files(save_dir, std::regex{u8R"(shop.*\.s2)"}))
    {
        if (fs::exists(
                save_dir /
                ("mod_" + filepathutil::to_utf8_path(entry.path().filename()))))
        {
            // Has already existed. Skipping.
            continue;
        }

        std::ifstream fin{entry.path().native(), std::ios::binary};
        putit::BinaryIArchive iar{fin};

        for (size_t index = 1320; index < 5480; ++index)
        {
            iar(inv[index]);
            inv[index].index = index;
            lua::lua->get_handle_manager().create_item_handle(inv[index]);
        }

        fs::path outpath = save_dir /
            ("mod_"s + filepathutil::to_utf8_path(entry.path().filename()));
        std::ofstream fout{outpath.native(), std::ios::binary};
        putit::BinaryOArchive oar{fout};

        mod_serializer.save_handles<Item>(oar, lua::ModInfo::StoreType::map);

        for (int index = 1320; index < 5480; index++)
        {
            inv[index].set_number(0);
            lua::lua->get_handle_manager().remove_item_handle(inv[index]);
        }
    }
}



/// Update save data from v11 to v12.
/// Fix Stersha's portrait ID from "starsha" to "stersha".
void _update_save_data_11(const fs::path& save_dir)
{
    const auto palmia_cdata_file = save_dir / "cdata_15_101.s2";
    if (!fs::exists(palmia_cdata_file))
    {
        return;
    }

    // Temporary output buffer
    std::ostringstream out;
    putit::BinaryOArchive oar{out};
    {
        // Input file
        std::ifstream in{palmia_cdata_file.native(), std::ios::binary};
        putit::BinaryIArchive iar{in};

        for (int idx = 57; idx < 245; ++idx)
        {
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

            std::bitset<sizeof(int) * 8 * 50> _flags;

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
            iar(_205);
            iar(_206);

            if (portrait == "core.starsha")
            {
                ELONA_LOG("save.update") << "Fix Stersha's portrait ID: "
                                            "core.starsha -> core.stersha";
                portrait = "core.stersha";
            }

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
            oar(_205);
            oar(_206);
        }
        // Variable in's lifetime ends up here, and the file should be closed.
    }

    // Open the file to write.
    std::ofstream fout{palmia_cdata_file.native(), std::ios::binary};
    // Write the data.
    fout.write(out.str().c_str(), out.str().size());
}



/// Update save data from v12 to v13.
/// Remove "core.item#kiroku.counter".
void _update_save_data_12(const fs::path& save_dir)
{
    for (const auto& entry : filesystem::glob_files(
             save_dir, std::regex{u8R"((g_)?inv(_.*)?\.s[12]|shop.*\.s2)"}))
    {
        // Open file.
        std::ifstream fin{entry.path().native(), std::ios::binary};
        putit::BinaryIArchive iar{fin};

        // Prepare a temporary output stream.
        std::ostringstream out;
        putit::BinaryOArchive oar{out};

        const auto is_invs1 = entry.path().filename() == "inv.s1" ||
            entry.path().filename() == "g_inv.s1";
        const auto begin = is_invs1 ? 0 : 1320;
        const auto end = is_invs1 ? 1320 : 5480;

        bool kiroku_counter_found = false;
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
            IdentifyState identify_state = IdentifyState::unidentified;
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
            std::bitset<32> _flags;
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
                iar(identify_state);
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
                iar(_flags);
                iar(enchantments);
            }

            // Replace "kiroku.counter" with gold piece.
            if (id == 900 && image == 900 && body_part == 0 && dice_x == 0 &&
                dice_y == 0 && damage_bonus == 0 && hit_bonus == 0 && pv == 0 &&
                dv == 0 && function == 0)
            {
                ELONA_LOG("save.update")
                    << filepathutil::to_utf8_path(entry.path().filename())
                    << ":" << idx
                    << ": Replace kiroku.counter -> core.gold_piece";
                id = 54;
                image = 433;

                kiroku_counter_found = true;
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
                oar(identify_state);
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
                oar(_flags);
                oar(enchantments);
            }
        }

        // Close the file and reopen to write.
        fin.close();

        if (kiroku_counter_found)
        {
            // Open the file to write.
            std::ofstream fout{entry.path().native(), std::ios::binary};
            // Write the data.
            fout.write(out.str().c_str(), out.str().size());
        }
    }
}



/// Update save data from v13 to v14.
/// Remove fixed random dungeon.
void _update_save_data_13(const fs::path& save_dir)
{
    // Remove *_8_101.s2 files.
    for (const auto& prefix : {"cdata",
                               "cdatan",
                               "inv",
                               "map",
                               "mdata",
                               "mdatan",
                               "mef",
                               "mod_cdata",
                               "mod_inv",
                               "mod_map",
                               "sdata"})
    {
        const auto path = save_dir / (std::string(prefix) + "_8_101.s2");
        if (fs::exists(path))
        {
            ELONA_LOG("save.update")
                << "remove " << filepathutil::to_utf8_path(path.filename());
            fs::remove(path);
        }
    }

    if (!fs::exists(save_dir / "adata.s1"))
        return;

    // Remove the area data from adata.s1.
    std::vector<int> data(40 * 500);
    {
        // Load
        std::ifstream in{(save_dir / "adata.s1").native(), std::ios::binary};
        putit::BinaryIArchive iar{in};

        for (size_t i = 0; i < 500; ++i)
        {
            for (size_t j = 0; j < 40; ++j)
            {
                iar(data.at(i * 40 + j));
            }
        }
    }

    // Clear the area data (index: 8).
    for (size_t j = 0; j < 40; ++j)
    {
        data.at(8 * 40 + j) = 0;
    }
    ELONA_LOG("save.update") << "clear adata(X, 8)";

    {
        // Write
        std::ofstream out{(save_dir / "adata.s1").native(), std::ios::binary};
        putit::BinaryOArchive oar{out};

        for (size_t i = 0; i < 500; ++i)
        {
            for (size_t j = 0; j < 40; ++j)
            {
                oar(data.at(i * 40 + j));
            }
        }
    }

    if (!fs::exists(save_dir / "map_4_101.s2"))
        return;

    // Remove cell data from North Tyris map.
    std::vector<int> ntyris_map(95 * 55 * 10);
    {
        // Load
        std::ifstream in{(save_dir / "map_4_101.s2").native(),
                         std::ios::binary};
        putit::BinaryIArchive iar{in};

        for (size_t i = 0; i < 10; ++i)
        {
            for (size_t y = 0; y < 95; ++y)
            {
                for (size_t x = 0; x < 55; ++x)
                {
                    iar(ntyris_map.at(i * 95 * 55 + y * 55 + x));
                }
            }
        }
    }

    // Get cell_data.feats at (27, 47).
    const auto feats = ntyris_map.at(6 * 95 * 55 + 47 * 55 + 27);
    const auto feat1 = feats / 1000 % 100;
    const auto feat2 = feats / 100000 % 100;
    const auto feat3 = feats / 10000000;

    if (feat1 == 15 && feat2 + feat3 * 100 == 8)
    {
        ntyris_map.at(6 * 95 * 55 + 47 * 55 + 27) = 0;
        ELONA_LOG("save.update")
            << "clear cell data in ntyris map at (47, 27).";
    }

    {
        // Write
        std::ofstream out{(save_dir / "map_4_101.s2").native(),
                          std::ios::binary};
        putit::BinaryOArchive oar{out};

        for (size_t i = 0; i < 10; ++i)
        {
            for (size_t y = 0; y < 95; ++y)
            {
                for (size_t x = 0; x < 55; ++x)
                {
                    oar(ntyris_map.at(i * 95 * 55 + y * 55 + x));
                }
            }
        }
    }
}



/// Update save data from v14 to v15.
/// Remove some of foobar extensions.
void _update_save_data_14(const fs::path& save_dir)
{
    for (const auto& entry : filesystem::glob_files(
             save_dir, std::regex{u8R"((g_)?inv(_.*)?\.s[12]|shop.*\.s2)"}))
    {
        // Open file.
        std::ifstream fin{entry.path().native(), std::ios::binary};
        putit::BinaryIArchive iar{fin};

        // Prepare a temporary output stream.
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
            IdentifyState identify_state = IdentifyState::unidentified;
            int count = 0;
            int dice_x = 0;
            int dice_y = 0;
            int damage_bonus = 0;
            int hit_bonus = 0;
            int dv = 0;
            int pv = 0;
            int skill = 0;
            int curse_state = 0;
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
            std::bitset<32> _flags;
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
                iar(identify_state);
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
                iar(_flags);
                iar(enchantments);
            }

            // Replace "strange_fish" with gold piece.
            if (id == 618 && subname == 37)
            {
                ELONA_LOG("save.update")
                    << filepathutil::to_utf8_path(entry.path().filename())
                    << ":" << idx << ": Replace strange_fish -> whale";
                subname = 34;
            }
            // Add function to card.
            if (id == 504 && function == 0)
            {
                ELONA_LOG("save.update")
                    << filepathutil::to_utf8_path(entry.path().filename())
                    << ":" << idx << ": Add function 38 to card";
                function = 38;
            }
            // Fix curse state's value.
            ELONA_LOG("save.update")
                << filepathutil::to_utf8_path(entry.path().filename()) << ":"
                << idx << ": Fix curse state";
            curse_state -= 2;

            // Dump item data to the memory stream.
            {
                oar(number_);
                oar(value);
                oar(image);
                oar(id);
                oar(quality);
                oar(position);
                oar(weight);
                oar(identify_state);
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
                oar(_flags);
                oar(enchantments);
            }
        }

        // Close the file and reopen to write.
        fin.close();

        {
            // Open the file to write.
            std::ofstream fout{entry.path().native(), std::ios::binary};
            // Write the data.
            fout.write(out.str().c_str(), out.str().size());
        }
    }
}



void _update_save_data(const fs::path& save_dir, int serial_id)
{
#define ELONA_CASE(n) \
    case n: _update_save_data_##n(save_dir); break;

    switch (serial_id)
    {
        ELONA_CASE(0)
        ELONA_CASE(1)
        ELONA_CASE(2)
        ELONA_CASE(3)
        ELONA_CASE(4)
        ELONA_CASE(5)
        ELONA_CASE(6)
        ELONA_CASE(7)
        ELONA_CASE(8)
        ELONA_CASE(9)
        ELONA_CASE(10)
        ELONA_CASE(11)
        ELONA_CASE(12)
        ELONA_CASE(13)
        ELONA_CASE(14)
    default: assert(0); break;
    }
#undef ELONA_CASE
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

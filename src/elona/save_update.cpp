#include "save_update.hpp"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "../util/fileutil.hpp"
#include "../util/range.hpp"
#include "../util/strutil.hpp"
#include "../version.hpp"
#include "character.hpp"
#include "item.hpp"
#include "lua_env/handle_manager.hpp"
#include "lua_env/lua_env.hpp"
#include "lua_env/mod_serializer.hpp"
#include "serialization/serialization.hpp"
#include "serialization/utils.hpp"



namespace elona
{

namespace
{

template <typename F>
void for_each_cdata(const fs::path& save_dir, F f)
{
    for (const auto& entry : filesystem::glob_files(
             save_dir, std::regex{u8R"(cdata(_.*)?\.s[12])"}))
    {
        std::ifstream fin{entry.path().native(), std::ios::binary};
        serialization::binary::IArchive iar{fin};

        std::ostringstream out;
        serialization::binary::OArchive oar{out};

        const auto is_cdatas1 = entry.path().extension().to_u8string() == ".s1";
        const auto begin = is_cdatas1 ? 0 : 57;
        const auto end = is_cdatas1 ? 57 : 245;
        for (int idx = begin; idx < end; ++idx)
        {
            const std::string map_id = is_cdatas1
                ? ""
                : entry.path().filename().to_u8string().substr(6 /* cdata_ */);
            f(iar, oar, map_id, idx);
        }

        fin.close();
        std::ofstream fout{entry.path().native(), std::ios::binary};
        fout.write(out.str().c_str(), out.str().size());
    }
}



template <typename F>
void for_each_inv(const fs::path& save_dir, F f)
{
    for (const auto& entry : filesystem::glob_files(
             save_dir, std::regex{u8R"(inv(_.*)?\.s[12]|shop.*\.s2)"}))
    {
        std::ifstream fin{entry.path().native(), std::ios::binary};
        serialization::binary::IArchive iar{fin};

        std::ostringstream out;
        serialization::binary::OArchive oar{out};

        const auto is_invs1 = entry.path().extension().to_u8string() == ".s1";
        const auto begin = is_invs1 ? 0 : 1320;
        const auto end = is_invs1 ? 1320 : 5480;
        for (int idx = begin; idx < end; ++idx)
        {
            const std::string map_id = is_invs1
                ? ""
                : entry.path().filename().to_u8string().substr(4 /* inv_ */);
            f(iar, oar, map_id, idx);
        }

        fin.close();
        std::ofstream fout{entry.path().native(), std::ios::binary};
        fout.write(out.str().c_str(), out.str().size());
    }
}



template <typename F>
void for_each_map(const fs::path& save_dir, F f)
{
    for (const auto& entry :
         filesystem::glob_files(save_dir, std::regex{u8R"(map_(.*)?\.s2)"}))
    {
        int width;
        int height;

        {
            const auto mid = entry.path().filename().to_u8string();
            const auto mdata = save_dir / fs::u8path("mdata_" + mid.substr(4));
            std::ifstream in{mdata.native(), std::ios::binary};
            serialization::binary::IArchive iar{in};
            iar(width);
            iar(height);
        }

        std::ifstream fin{entry.path().native(), std::ios::binary};
        serialization::binary::IArchive iar{fin};

        std::ostringstream out;
        serialization::binary::OArchive oar{out};

        f(width, height, iar, oar);

        fin.close();
        std::ofstream fout{entry.path().native(), std::ios::binary};
        fout.write(out.str().c_str(), out.str().size());
    }
}



void _update_save_data_15(const fs::path& save_dir)
{
    for_each_cdata(
        save_dir, [](auto& iar, auto& oar, const auto&, int chara_index) {
            int state;
            int position_x;
            int position_y;
            int next_position_x;
            int next_position_y;
            int time_to_revive;
            int vision_flag;
            int image;
            int sex;
            int relationship;
            int turn_cost;
            int current_speed;
            int ai_item;
            std::string portrait;
            int interest;
            int time_interest_revive;
            int personality;
            int impression;
            int talk_type;
            int height;
            int weight;
            int birth_year;
            int nutrition;
            int can_talk;
            int quality;
            int turn;
            int id;
            int vision_distance;
            int enemy_id;
            int gold;
            int platinum_coin;
            int combat_style;
            int melee_attack_type;
            int fame;
            int experience;
            int required_experience;
            int speed_percentage;
            int level;
            int speed_percentage_in_next_turn;
            int skill_bonus;
            int total_skill_bonus;
            int inventory_weight;
            int max_inventory_weight;
            int inventory_weight_type;
            int max_level;
            int karma;
            int hp;
            int max_hp;
            int sp;
            int max_sp;
            int mp;
            int max_mp;
            int heal_value_per_nether_attack;
            std::string god_id;
            int piety_point;
            int praying_point;
            int sum_of_equipment_weight;
            int special_attack_type;
            int rate_to_pierce;
            int rate_of_critical_hit;
            int speed_correction_value;
            int original_relationship;
            int pv;
            int dv;
            int hit_bonus;
            int damage_bonus;
            int pv_correction_value;
            int dv_correction_value;
            int damage_reaction_info;
            int emotion_icon;
            int current_map;
            int current_dungeon_level;
            int related_quest_id;
            int direction;
            int period_of_contract;
            int hire_count;
            int insanity;
            int curse_power;
            int extra_attack;
            int extra_shot;
            int decrease_physical_damage;
            int nullify_damage;
            int cut_counterattack;
            int anorexia_count;
            int activity_type;
            int activity_turn;
            int activity_item;
            int stops_activity_if_damaged;
            int quality_of_performance;
            int tip_gold;
            int character_role;
            int shop_rank;
            int activity_target;
            int shop_store_id;
            int time_to_restore;
            int cnpc_id;
            int initial_position_x;
            int initial_position_y;
            int hate;
            int ai_calm;
            int ai_move;
            int ai_dist;
            int ai_act_sub_freq;
            int ai_heal;
            int element_of_unarmed_attack;
            int poisoned;
            int sleep;
            int paralyzed;
            int blind;
            int confused;
            int fear;
            int dimmed;
            int drunk;
            int bleeding;
            int wet;
            int insane;
            int sick;
            int gravity;
            int choked;
            int furious;
            std::vector<int> growth_buffs;
            std::vector<int> equipment_slots;
            std::vector<int> normal_actions;
            std::vector<int> special_actions;
            std::vector<std::tuple<int, int, int>> buffs;
            std::vector<int> attr_adjs;
            std::bitset<sizeof(int) * 8 * 50> _flags;
            int _156;
            int _203;
            int target_position_x;
            int target_position_y;

            iar(state);
            iar(position_x);
            iar(position_y);
            iar(next_position_x);
            iar(next_position_y);
            iar(time_to_revive);
            iar(vision_flag);
            iar(image);
            iar(sex);
            iar(relationship);
            iar(turn_cost);
            iar(current_speed);
            iar(ai_item);
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
            iar(combat_style);
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
            iar(activity_type);
            iar(activity_turn);
            iar(activity_item);
            iar(stops_activity_if_damaged);
            iar(quality_of_performance);
            iar(tip_gold);
            iar(character_role);
            iar(shop_rank);
            iar(activity_target);
            iar(shop_store_id);
            iar(time_to_restore);
            iar(cnpc_id);
            iar(initial_position_x);
            iar(initial_position_y);
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
            iar(equipment_slots);
            iar(normal_actions);
            iar(special_actions);
            iar(buffs);
            iar(attr_adjs);
            iar(_flags);
            iar(_156);
            iar(_203);
            iar(target_position_x);
            iar(target_position_y);

            int64_t activity_item_ = activity_item;
            if (activity_item_ == -1)
            {
                activity_item_ = 0;
            }
            else if (activity_type == 0 || activity_type == 11)
            {
                activity_item_ = 0;
            }
            else if (activity_item_ != 0 || chara_index == 0)
            {
                activity_item_ += 1;
            }
            if (activity_item != activity_item_)
            {
                ELONA_LOG("save.update") << "cdata[" << chara_index << "]."
                                         << "activity.item: " << activity_item
                                         << " -> " << activity_item_;
            }

            int64_t ai_item_ = ai_item;
            if (ai_item_ != 0)
            {
                ai_item_ += 1;
            }
            if (ai_item != ai_item_)
            {
                ELONA_LOG("save.update")
                    << "cdata[" << chara_index << "]."
                    << "ai_item: " << ai_item << " -> " << ai_item_;
            }

            std::vector<std::tuple<int, int64_t>> equipment_slots_(
                equipment_slots.size());
            for (size_t i = 0; i < equipment_slots.size(); ++i)
            {
                const auto type = equipment_slots[i] / 10000;
                const auto index_plus_one = equipment_slots[i] % 10000;
                equipment_slots_[i] = {type, index_plus_one};
                if (type != 0)
                {
                    ELONA_LOG("save.update")
                        << "cdata[" << chara_index << "]."
                        << "equipment_slots[" << i
                        << "]: " << equipment_slots[i] << " -> (" << type
                        << ", " << index_plus_one << ")";
                }
            }

            oar(state);
            oar(position_x);
            oar(position_y);
            oar(next_position_x);
            oar(next_position_y);
            oar(time_to_revive);
            oar(vision_flag);
            oar(image);
            oar(sex);
            oar(relationship);
            oar(turn_cost);
            oar(current_speed);
            oar(ai_item_);
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
            oar(combat_style);
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
            oar(activity_type);
            oar(activity_turn);
            oar(activity_item_);
            oar(stops_activity_if_damaged);
            oar(quality_of_performance);
            oar(tip_gold);
            oar(character_role);
            oar(shop_rank);
            oar(activity_target);
            oar(shop_store_id);
            oar(time_to_restore);
            oar(cnpc_id);
            oar(initial_position_x);
            oar(initial_position_y);
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
            oar(equipment_slots_);
            oar(normal_actions);
            oar(special_actions);
            oar(buffs);
            oar(attr_adjs);
            oar(_flags);
            oar(_156);
            oar(_203);
            oar(target_position_x);
            oar(target_position_y);
        });
}



void _update_save_data_16(const fs::path& save_dir)
{
    for_each_map(save_dir, [](int width, int height, auto& iar, auto& oar) {
        size_t size = width * height;
        std::vector<int> old_cells;
        old_cells.resize(10 * size);
        for (int k = 0; k < 10; ++k)
        {
            for (int y = 0; y < height; ++y)
            {
                for (int x = 0; x < width; ++x)
                {
                    size_t i = k * width * height + y * width + x;
                    iar(old_cells[i]);
                }
            }
        }

        std::vector<
            std::tuple<int, int, int, uint64_t, uint64_t, int, int, int, int>>
            new_cells;
        new_cells.resize(size);
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                auto& new_cell = new_cells[y * width + x];
                std::get<0>(new_cell) =
                    old_cells[0 * width * height + y * width + x];
                std::get<1>(new_cell) =
                    old_cells[2 * width * height + y * width + x];
                std::get<2>(new_cell) =
                    old_cells[1 * width * height + y * width + x];
                std::get<3>(new_cell) = 0xF000'0000'0000'0000ULL;
                std::get<4>(new_cell) = 0xF000'0000'0000'0000ULL;
                std::get<5>(new_cell) =
                    old_cells[6 * width * height + y * width + x];
                std::get<6>(new_cell) =
                    old_cells[7 * width * height + y * width + x];
                std::get<7>(new_cell) =
                    old_cells[8 * width * height + y * width + x];
                std::get<8>(new_cell) =
                    old_cells[9 * width * height + y * width + x];
            }
        }

        oar(width);
        oar(height);
        oar(new_cells);
    });
}



void _update_save_data_17(const fs::path& save_dir)
{
    for (const auto& entry : filesystem::glob_files(
             save_dir, std::regex{u8R"(mod_(inv|cdata).*\.s[12])"}))
    {
        ELONA_LOG("save.update") << "Remove " << entry.path().to_u8string();
        fs::remove(entry.path());
    }


    boost::uuids::random_generator gen;

    for_each_cdata(
        save_dir, [&](auto& iar, auto& oar, const auto&, int chara_index) {
            int state;
            int position_x;
            int position_y;
            int next_position_x;
            int next_position_y;
            int time_to_revive;
            int vision_flag;
            int image;
            int sex;
            int relationship;
            int turn_cost;
            int current_speed;
            int64_t ai_item;
            std::string portrait;
            int interest;
            int time_interest_revive;
            int personality;
            int impression;
            int talk_type;
            int height;
            int weight;
            int birth_year;
            int nutrition;
            int can_talk;
            int quality;
            int turn;
            int id;
            int vision_distance;
            int enemy_id;
            int gold;
            int platinum_coin;
            int combat_style;
            int melee_attack_type;
            int fame;
            int experience;
            int required_experience;
            int speed_percentage;
            int level;
            int speed_percentage_in_next_turn;
            int skill_bonus;
            int total_skill_bonus;
            int inventory_weight;
            int max_inventory_weight;
            int inventory_weight_type;
            int max_level;
            int karma;
            int hp;
            int max_hp;
            int sp;
            int max_sp;
            int mp;
            int max_mp;
            int heal_value_per_nether_attack;
            std::string god_id;
            int piety_point;
            int praying_point;
            int sum_of_equipment_weight;
            int special_attack_type;
            int rate_to_pierce;
            int rate_of_critical_hit;
            int speed_correction_value;
            int original_relationship;
            int pv;
            int dv;
            int hit_bonus;
            int damage_bonus;
            int pv_correction_value;
            int dv_correction_value;
            int damage_reaction_info;
            int emotion_icon;
            int current_map;
            int current_dungeon_level;
            int related_quest_id;
            int direction;
            int period_of_contract;
            int hire_count;
            int insanity;
            int curse_power;
            int extra_attack;
            int extra_shot;
            int decrease_physical_damage;
            int nullify_damage;
            int cut_counterattack;
            int anorexia_count;
            int activity_type;
            int activity_turn;
            int64_t activity_item;
            int stops_activity_if_damaged;
            int quality_of_performance;
            int tip_gold;
            int character_role;
            int shop_rank;
            int activity_target;
            int shop_store_id;
            int time_to_restore;
            int cnpc_id;
            int initial_position_x;
            int initial_position_y;
            int hate;
            int ai_calm;
            int ai_move;
            int ai_dist;
            int ai_act_sub_freq;
            int ai_heal;
            int element_of_unarmed_attack;
            int poisoned;
            int sleep;
            int paralyzed;
            int blind;
            int confused;
            int fear;
            int dimmed;
            int drunk;
            int bleeding;
            int wet;
            int insane;
            int sick;
            int gravity;
            int choked;
            int furious;
            std::vector<int> growth_buffs;
            std::vector<std::tuple<int, int64_t>> equipment_slots;
            std::vector<int> normal_actions;
            std::vector<int> special_actions;
            std::vector<std::tuple<int, int, int>> buffs;
            std::vector<int> attr_adjs;
            std::bitset<sizeof(int) * 8 * 50> _flags;
            int _156;
            int _203;
            int target_position_x;
            int target_position_y;

            iar(state);
            iar(position_x);
            iar(position_y);
            iar(next_position_x);
            iar(next_position_y);
            iar(time_to_revive);
            iar(vision_flag);
            iar(image);
            iar(sex);
            iar(relationship);
            iar(turn_cost);
            iar(current_speed);
            iar(ai_item);
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
            iar(combat_style);
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
            iar(activity_type);
            iar(activity_turn);
            iar(activity_item);
            iar(stops_activity_if_damaged);
            iar(quality_of_performance);
            iar(tip_gold);
            iar(character_role);
            iar(shop_rank);
            iar(activity_target);
            iar(shop_store_id);
            iar(time_to_restore);
            iar(cnpc_id);
            iar(initial_position_x);
            iar(initial_position_y);
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
            iar(equipment_slots);
            iar(normal_actions);
            iar(special_actions);
            iar(buffs);
            iar(attr_adjs);
            iar(_flags);
            iar(_156);
            iar(_203);
            iar(target_position_x);
            iar(target_position_y);

            uint8_t obj_id[16];
            if (state == 0)
            {
                std::fill(std::begin(obj_id), std::end(obj_id), 0);
                ELONA_LOG("save.update")
                    << "cdata[" << chara_index << "].obj_id: <nil>";
            }
            else
            {
                const auto uuid = gen();
                std::copy(std::begin(uuid), std::end(uuid), std::begin(obj_id));
                ELONA_LOG("save.update")
                    << "cdata[" << chara_index << "].obj_id: " << uuid;
            }

            for (auto& b : obj_id)
            {
                oar(b);
            }
            oar(state);
            oar(position_x);
            oar(position_y);
            oar(next_position_x);
            oar(next_position_y);
            oar(time_to_revive);
            oar(vision_flag);
            oar(image);
            oar(sex);
            oar(relationship);
            oar(turn_cost);
            oar(current_speed);
            oar(ai_item);
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
            oar(combat_style);
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
            oar(activity_type);
            oar(activity_turn);
            oar(activity_item);
            oar(stops_activity_if_damaged);
            oar(quality_of_performance);
            oar(tip_gold);
            oar(character_role);
            oar(shop_rank);
            oar(activity_target);
            oar(shop_store_id);
            oar(time_to_restore);
            oar(cnpc_id);
            oar(initial_position_x);
            oar(initial_position_y);
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
            oar(equipment_slots);
            oar(normal_actions);
            oar(special_actions);
            oar(buffs);
            oar(attr_adjs);
            oar(_flags);
            oar(_156);
            oar(_203);
            oar(target_position_x);
            oar(target_position_y);
        });

    for_each_inv(
        save_dir, [&](auto& iar, auto& oar, const auto&, int item_index) {
            int number;
            int value;
            int image;
            int id;
            int quality;
            int position_x;
            int position_y;
            int weight;
            int identify_state;
            int count;
            int dice_x;
            int dice_y;
            int damage_bonus;
            int hit_bonus;
            int dv;
            int pv;
            int skill;
            int curse_state;
            int body_part;
            int function;
            int enhancement;
            int own_state;
            int color;
            int subname;
            int material;
            int param1;
            int param2;
            int param3;
            int param4;
            int identify_level;
            int turn;
            uint32_t flags;
            std::vector<std::tuple<int, int>> enchantments;

            iar(number);
            iar(value);
            iar(image);
            iar(id);
            iar(quality);
            iar(position_x);
            iar(position_y);
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
            iar(identify_level);
            iar(turn);
            iar(flags);
            iar(enchantments);

            uint8_t obj_id[16];
            if (number == 0)
            {
                std::fill(std::begin(obj_id), std::end(obj_id), 0);
                ELONA_LOG("save.update")
                    << "g_inv[" << item_index << "].obj_id: <nil>";
            }
            else
            {
                const auto uuid = gen();
                std::copy(std::begin(uuid), std::end(uuid), std::begin(obj_id));
                ELONA_LOG("save.update")
                    << "g_inv[" << item_index << "].obj_id: " << uuid;
            }

            for (auto& b : obj_id)
            {
                oar(b);
            }
            oar(number);
            oar(value);
            oar(image);
            oar(id);
            oar(quality);
            oar(position_x);
            oar(position_y);
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
            oar(identify_level);
            oar(turn);
            oar(flags);
            oar(enchantments);
        });
}



boost::uuids::uuid _update_save_data_18_convert_item_index_to_object_id(
    std::unordered_map<
        std::string,
        std::unordered_map<int64_t, boost::uuids::uuid>>& item_obj_id_registry,
    const std::string& map_id,
    int64_t item_index_plus_one)
{
    if (item_index_plus_one == 0) // null reference
    {
        boost::uuids::uuid ret;
        std::fill(std::begin(ret), std::end(ret), 0);
        return ret;
    }

    int64_t item_index = item_index_plus_one - 1;
    if (item_index < 1320)
    {
        return item_obj_id_registry[""][item_index];
    }
    else
    {
        return item_obj_id_registry[map_id][item_index];
    }
}



void _update_save_data_18(const fs::path& save_dir)
{
    std::unordered_map<
        std::string,
        std::unordered_map<int64_t, boost::uuids::uuid>>
        item_obj_id_registry;

    for_each_inv(
        save_dir,
        [&](auto& iar, auto& oar, const auto& map_id, int item_index) {
            boost::uuids::uuid obj_id;
            int number;
            int value;
            int image;
            int id;
            int quality;
            int position_x;
            int position_y;
            int weight;
            int identify_state;
            int count;
            int dice_x;
            int dice_y;
            int damage_bonus;
            int hit_bonus;
            int dv;
            int pv;
            int skill;
            int curse_state;
            int body_part;
            int function;
            int enhancement;
            int own_state;
            int color;
            int subname;
            int material;
            int param1;
            int param2;
            int param3;
            int param4;
            int identify_level;
            int turn;
            uint32_t flags;
            std::vector<std::tuple<int, int>> enchantments;

            iar(obj_id);
            iar(number);
            iar(value);
            iar(image);
            iar(id);
            iar(quality);
            iar(position_x);
            iar(position_y);
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
            iar(identify_level);
            iar(turn);
            iar(flags);
            iar(enchantments);

            bool exists = number != 0;

            oar(exists);
            if (!exists)
            {
                ELONA_LOG("save.update") << "item(" << item_index << "): nil";
                return;
            }
            else
            {
                ELONA_LOG("save.update")
                    << "item(" << item_index << "): " << obj_id;
                item_obj_id_registry[map_id][item_index] = obj_id;
            }

            oar(obj_id);
            oar(number);
            oar(value);
            oar(image);
            oar(id);
            oar(quality);
            oar(position_x);
            oar(position_y);
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
            oar(identify_level);
            oar(turn);
            oar(flags);
            oar(enchantments);
        });


    for_each_cdata(
        save_dir,
        [&](auto& iar, auto& oar, const auto& map_id, int chara_index) {
            boost::uuids::uuid obj_id;
            int state;
            int position_x;
            int position_y;
            int next_position_x;
            int next_position_y;
            int time_to_revive;
            int vision_flag;
            int image;
            int sex;
            int relationship;
            int turn_cost;
            int current_speed;
            int64_t ai_item;
            std::string portrait;
            int interest;
            int time_interest_revive;
            int personality;
            int impression;
            int talk_type;
            int height;
            int weight;
            int birth_year;
            int nutrition;
            int can_talk;
            int quality;
            int turn;
            int id;
            int vision_distance;
            int enemy_id;
            int gold;
            int platinum_coin;
            int combat_style;
            int melee_attack_type;
            int fame;
            int experience;
            int required_experience;
            int speed_percentage;
            int level;
            int speed_percentage_in_next_turn;
            int skill_bonus;
            int total_skill_bonus;
            int inventory_weight;
            int max_inventory_weight;
            int inventory_weight_type;
            int max_level;
            int karma;
            int hp;
            int max_hp;
            int sp;
            int max_sp;
            int mp;
            int max_mp;
            int heal_value_per_nether_attack;
            std::string god_id;
            int piety_point;
            int praying_point;
            int sum_of_equipment_weight;
            int special_attack_type;
            int rate_to_pierce;
            int rate_of_critical_hit;
            int speed_correction_value;
            int original_relationship;
            int pv;
            int dv;
            int hit_bonus;
            int damage_bonus;
            int pv_correction_value;
            int dv_correction_value;
            int damage_reaction_info;
            int emotion_icon;
            int current_map;
            int current_dungeon_level;
            int related_quest_id;
            int direction;
            int period_of_contract;
            int hire_count;
            int insanity;
            int curse_power;
            int extra_attack;
            int extra_shot;
            int decrease_physical_damage;
            int nullify_damage;
            int cut_counterattack;
            int anorexia_count;
            int activity_type;
            int activity_turn;
            int64_t activity_item;
            int stops_activity_if_damaged;
            int quality_of_performance;
            int tip_gold;
            int character_role;
            int shop_rank;
            int activity_target;
            int shop_store_id;
            int time_to_restore;
            int cnpc_id;
            int initial_position_x;
            int initial_position_y;
            int hate;
            int ai_calm;
            int ai_move;
            int ai_dist;
            int ai_act_sub_freq;
            int ai_heal;
            int element_of_unarmed_attack;
            int poisoned;
            int sleep;
            int paralyzed;
            int blind;
            int confused;
            int fear;
            int dimmed;
            int drunk;
            int bleeding;
            int wet;
            int insane;
            int sick;
            int gravity;
            int choked;
            int furious;
            std::vector<int> growth_buffs;
            std::vector<std::tuple<int, int64_t>> equipment_slots;
            std::vector<int> normal_actions;
            std::vector<int> special_actions;
            std::vector<std::tuple<int, int, int>> buffs;
            std::vector<int> attr_adjs;
            std::bitset<sizeof(int) * 8 * 50> _flags;
            int _156;
            int _203;
            int target_position_x;
            int target_position_y;

            iar(obj_id);
            iar(state);
            iar(position_x);
            iar(position_y);
            iar(next_position_x);
            iar(next_position_y);
            iar(time_to_revive);
            iar(vision_flag);
            iar(image);
            iar(sex);
            iar(relationship);
            iar(turn_cost);
            iar(current_speed);
            iar(ai_item);
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
            iar(combat_style);
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
            iar(activity_type);
            iar(activity_turn);
            iar(activity_item);
            iar(stops_activity_if_damaged);
            iar(quality_of_performance);
            iar(tip_gold);
            iar(character_role);
            iar(shop_rank);
            iar(activity_target);
            iar(shop_store_id);
            iar(time_to_restore);
            iar(cnpc_id);
            iar(initial_position_x);
            iar(initial_position_y);
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
            iar(equipment_slots);
            iar(normal_actions);
            iar(special_actions);
            iar(buffs);
            iar(attr_adjs);
            iar(_flags);
            iar(_156);
            iar(_203);
            iar(target_position_x);
            iar(target_position_y);

            boost::uuids::uuid activity_item_;
            std::fill(std::begin(activity_item_), std::end(activity_item_), 0);
            boost::uuids::uuid ai_item_;
            std::fill(std::begin(ai_item_), std::end(ai_item_), 0);
            std::vector<std::tuple<int, boost::uuids::uuid>> equipment_slots_{
                equipment_slots.size()};
            if (state == 0)
            {
                ELONA_LOG("save.update") << "chara(" << chara_index << "): nil";
                for (size_t i = 0; i < equipment_slots.size(); ++i)
                {
                    std::get<0>(equipment_slots_[i]) =
                        std::get<0>(equipment_slots[i]);
                    std::fill(
                        std::begin(std::get<1>(equipment_slots_[i])),
                        std::end(std::get<1>(equipment_slots_[i])),
                        0);
                }
            }
            else
            {
                ELONA_LOG("save.update")
                    << "chara(" << chara_index << "): " << obj_id;

                activity_item_ =
                    _update_save_data_18_convert_item_index_to_object_id(
                        item_obj_id_registry, map_id, activity_item);
                ai_item_ = _update_save_data_18_convert_item_index_to_object_id(
                    item_obj_id_registry, map_id, ai_item);
                ELONA_LOG("save.update") << "  activity.item: " << activity_item
                                         << " -> " << activity_item_;
                ELONA_LOG("save.update")
                    << "  ai_item: " << ai_item << " -> " << ai_item_;
                for (size_t i = 0; i < equipment_slots.size(); ++i)
                {
                    std::get<0>(equipment_slots_[i]) =
                        std::get<0>(equipment_slots[i]);
                    std::get<1>(equipment_slots_[i]) =
                        _update_save_data_18_convert_item_index_to_object_id(
                            item_obj_id_registry,
                            map_id,
                            std::get<1>(equipment_slots[i]));
                    ELONA_LOG("save.update")
                        << "  equipment_slots[" << i
                        << "].equipment: " << std::get<1>(equipment_slots[i])
                        << " -> " << std::get<1>(equipment_slots_[i]);
                }
            }

            oar(obj_id);
            oar(state);
            oar(position_x);
            oar(position_y);
            oar(next_position_x);
            oar(next_position_y);
            oar(time_to_revive);
            oar(vision_flag);
            oar(image);
            oar(sex);
            oar(relationship);
            oar(turn_cost);
            oar(current_speed);
            oar(ai_item_);
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
            oar(combat_style);
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
            oar(activity_type);
            oar(activity_turn);
            oar(activity_item_);
            oar(stops_activity_if_damaged);
            oar(quality_of_performance);
            oar(tip_gold);
            oar(character_role);
            oar(shop_rank);
            oar(activity_target);
            oar(shop_store_id);
            oar(time_to_restore);
            oar(cnpc_id);
            oar(initial_position_x);
            oar(initial_position_y);
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
            oar(equipment_slots_);
            oar(normal_actions);
            oar(special_actions);
            oar(buffs);
            oar(attr_adjs);
            oar(_flags);
            oar(_156);
            oar(_203);
            oar(target_position_x);
            oar(target_position_y);
        });
}



void _update_save_data_19(const fs::path& save_dir)
{
    for (const auto& entry :
         filesystem::glob_files(save_dir, std::regex{u8R"(shop[0-9]*\.s2)"}))
    {
        std::ifstream fin{entry.path().native(), std::ios::binary};
        serialization::binary::IArchive iar{fin};

        std::ostringstream out;
        serialization::binary::OArchive oar{out};

        ELONA_LOG("save.update") << "convert " << entry.path().to_u8string();

        const auto begin = 1320;
        const auto end = 5480;
        for (int idx = begin; idx < end; ++idx)
        {
            boost::uuids::uuid obj_id;
            int number;
            int value;
            int image;
            int id;
            int quality;
            int position_x;
            int position_y;
            int weight;
            int identify_state;
            int count;
            int dice_x;
            int dice_y;
            int damage_bonus;
            int hit_bonus;
            int dv;
            int pv;
            int skill;
            int curse_state;
            int body_part;
            int function;
            int enhancement;
            int own_state;
            int color;
            int subname;
            int material;
            int param1;
            int param2;
            int param3;
            int param4;
            int identify_level;
            int turn;
            uint32_t flags;
            std::vector<std::tuple<int, int>> enchantments;

            bool exists;
            iar(exists);
            ELONA_LOG("save.update")
                << "inv[" << idx << "]: " << (exists ? "t" : "nil");
            if (exists)
            {
                iar(obj_id);
                iar(number);
                iar(value);
                iar(image);
                iar(id);
                iar(quality);
                iar(position_x);
                iar(position_y);
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
                iar(identify_level);
                iar(turn);
                iar(flags);
                iar(enchantments);

                if (idx < 5080)
                {
                    ELONA_LOG("save.update") << "  skipping";
                    continue;
                }

                oar(exists);
                oar(obj_id);
                oar(number);
                oar(value);
                oar(image);
                oar(id);
                oar(quality);
                oar(position_x);
                oar(position_y);
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
                oar(identify_level);
                oar(turn);
                oar(flags);
                oar(enchantments);
            }
            else
            {
                if (idx < 5080)
                {
                    ELONA_LOG("save.update") << "  skipping";
                    continue;
                }

                oar(exists);
            }
        }

        fin.close();
        std::ofstream fout{entry.path().native(), std::ios::binary};
        fout.write(out.str().c_str(), out.str().size());
    }
}



/*
 * Update save data from v20 to v21.
 *
 * - Merge sdata files into cdata files (PR #1703).
 */
void _update_save_data_20(const fs::path& save_dir)
{
    constexpr int num_skills = 600;
    constexpr int num_fields = 4;

    std::unordered_map<std::string, std::vector<int>> all_sdata;

    for (const auto& entry : filesystem::glob_files(
             save_dir, std::regex{u8R"(sdata(_.*)?\.s[12])"}))
    {
        std::ifstream fin{entry.path().native(), std::ios::binary};
        serialization::binary::IArchive iar{fin};

        const auto is_sdatas1 = entry.path().extension() == ".s1";
        const auto begin = is_sdatas1 ? 0 : 57;
        const auto end = is_sdatas1 ? 57 : 245;
        const auto num_charas = end - begin + 1;
        std::vector<int> sdata(num_skills * num_fields * num_charas);
        size_t sdata_idx = 0;
        for (int idx = begin; idx < end; ++idx)
        {
            for (int skill_id = 0; skill_id < num_skills; ++skill_id)
            {
                for (int field_idx = 0; field_idx < num_fields; ++field_idx)
                {
                    iar(sdata[sdata_idx]);
                    ++sdata_idx;
                }
            }
        }
        const std::string map_id = is_sdatas1
            ? ""
            : entry.path().filename().to_u8string().substr(6 /* sdata_ */);
        all_sdata.emplace(map_id, sdata);

        fin.close();
        ELONA_LOG("save.update")
            << "Remove " << entry.path().filename().to_u8string();
        fs::remove(entry.path());
    }

    if (fs::exists(save_dir / "g_sdata.s1"))
    {
        ELONA_LOG("save.update") << "Remove g_sdata.s1";
        fs::remove(save_dir / "g_sdata.s1");
    }

    for_each_cdata(
        save_dir,
        [&](auto& iar, auto& oar, const auto& map_id, int chara_index) {
            boost::uuids::uuid obj_id;
            int state;
            int position_x;
            int position_y;
            int next_position_x;
            int next_position_y;
            int time_to_revive;
            int vision_flag;
            int image;
            int sex;
            int relationship;
            int turn_cost;
            int current_speed;
            boost::uuids::uuid ai_item;
            std::string portrait;
            int interest;
            int time_interest_revive;
            int personality;
            int impression;
            int talk_type;
            int height;
            int weight;
            int birth_year;
            int nutrition;
            int can_talk;
            int quality;
            int turn;
            int id;
            int vision_distance;
            int enemy_id;
            int gold;
            int platinum_coin;
            int combat_style;
            int melee_attack_type;
            int fame;
            int experience;
            int required_experience;
            int speed_percentage;
            int level;
            int speed_percentage_in_next_turn;
            int skill_bonus;
            int total_skill_bonus;
            int inventory_weight;
            int max_inventory_weight;
            int inventory_weight_type;
            int max_level;
            int karma;
            int hp;
            int max_hp;
            int sp;
            int max_sp;
            int mp;
            int max_mp;
            int heal_value_per_nether_attack;
            std::string god_id;
            int piety_point;
            int praying_point;
            int sum_of_equipment_weight;
            int special_attack_type;
            int rate_to_pierce;
            int rate_of_critical_hit;
            int speed_correction_value;
            int original_relationship;
            int pv;
            int dv;
            int hit_bonus;
            int damage_bonus;
            int pv_correction_value;
            int dv_correction_value;
            int damage_reaction_info;
            int emotion_icon;
            int current_map;
            int current_dungeon_level;
            int related_quest_id;
            int direction;
            int period_of_contract;
            int hire_count;
            int insanity;
            int curse_power;
            int extra_attack;
            int extra_shot;
            int decrease_physical_damage;
            int nullify_damage;
            int cut_counterattack;
            int anorexia_count;
            int activity_type;
            int activity_turn;
            boost::uuids::uuid activity_item;
            int stops_activity_if_damaged;
            int quality_of_performance;
            int tip_gold;
            int character_role;
            int shop_rank;
            int activity_target;
            int shop_store_id;
            int time_to_restore;
            int cnpc_id;
            int initial_position_x;
            int initial_position_y;
            int hate;
            int ai_calm;
            int ai_move;
            int ai_dist;
            int ai_act_sub_freq;
            int ai_heal;
            int element_of_unarmed_attack;
            int poisoned;
            int sleep;
            int paralyzed;
            int blind;
            int confused;
            int fear;
            int dimmed;
            int drunk;
            int bleeding;
            int wet;
            int insane;
            int sick;
            int gravity;
            int choked;
            int furious;
            std::vector<int> growth_buffs;
            std::vector<std::tuple<int, boost::uuids::uuid>> equipment_slots;
            std::vector<int> normal_actions;
            std::vector<int> special_actions;
            std::vector<std::tuple<int, int, int>> buffs;
            std::vector<int> attr_adjs;
            std::bitset<sizeof(int) * 8 * 50> _flags;
            int _156;
            int _203;
            int target_position_x;
            int target_position_y;

            iar(obj_id);
            iar(state);
            iar(position_x);
            iar(position_y);
            iar(next_position_x);
            iar(next_position_y);
            iar(time_to_revive);
            iar(vision_flag);
            iar(image);
            iar(sex);
            iar(relationship);
            iar(turn_cost);
            iar(current_speed);
            iar(ai_item);
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
            iar(combat_style);
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
            iar(activity_type);
            iar(activity_turn);
            iar(activity_item);
            iar(stops_activity_if_damaged);
            iar(quality_of_performance);
            iar(tip_gold);
            iar(character_role);
            iar(shop_rank);
            iar(activity_target);
            iar(shop_store_id);
            iar(time_to_restore);
            iar(cnpc_id);
            iar(initial_position_x);
            iar(initial_position_y);
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
            iar(equipment_slots);
            iar(normal_actions);
            iar(special_actions);
            iar(buffs);
            iar(attr_adjs);
            iar(_flags);
            iar(_156);
            iar(_203);
            iar(target_position_x);
            iar(target_position_y);

            std::vector<std::tuple<int, int, int, int>> skills(num_skills);
            {
                const auto relative_chara_idx =
                    chara_index < 57 ? chara_index : chara_index - 57;
                const auto& sdata = all_sdata[map_id];
                for (int skill_id = 0; skill_id < num_skills; ++skill_id)
                {
                    const auto l = sdata
                        [relative_chara_idx * num_skills * num_fields +
                         skill_id * num_fields + 0];
                    const auto b = sdata
                        [relative_chara_idx * num_skills * num_fields +
                         skill_id * num_fields + 1];
                    const auto e = sdata
                        [relative_chara_idx * num_skills * num_fields +
                         skill_id * num_fields + 2];
                    const auto p = sdata
                        [relative_chara_idx * num_skills * num_fields +
                         skill_id * num_fields + 3];

                    std::get<0>(skills[skill_id]) = l;
                    std::get<1>(skills[skill_id]) = b;
                    std::get<2>(skills[skill_id]) = e;
                    std::get<3>(skills[skill_id]) = p;

                    if (state != 0 && !(l == 0 && b == 0 && e == 0 && p == 0))
                    {
                        ELONA_LOG("save.update")
                            << "skill data[" << skill_id << "]: l=" << l
                            << " b=" << b << " e=" << e << " p=" << p;
                    }
                }
            }

            oar(obj_id);
            oar(state);
            oar(position_x);
            oar(position_y);
            oar(next_position_x);
            oar(next_position_y);
            oar(time_to_revive);
            oar(vision_flag);
            oar(image);
            oar(sex);
            oar(relationship);
            oar(turn_cost);
            oar(current_speed);
            oar(ai_item);
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
            oar(combat_style);
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
            oar(activity_type);
            oar(activity_turn);
            oar(activity_item);
            oar(stops_activity_if_damaged);
            oar(quality_of_performance);
            oar(tip_gold);
            oar(character_role);
            oar(shop_rank);
            oar(activity_target);
            oar(shop_store_id);
            oar(time_to_restore);
            oar(cnpc_id);
            oar(initial_position_x);
            oar(initial_position_y);
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
            oar(equipment_slots);
            oar(normal_actions);
            oar(special_actions);
            oar(buffs);
            oar(attr_adjs);
            oar(_flags);
            oar(_156);
            oar(_203);
            oar(target_position_x);
            oar(target_position_y);
            oar(skills);
        });
}



/*
 * Update save data from v21 to v22.
 *
 * - Merge cdatan files into cdata files.
 */
void _update_save_data_21(const fs::path& save_dir)
{
    std::unordered_map<std::string, std::vector<std::string>> all_cdatan;

    for (const auto& entry : filesystem::glob_files(
             save_dir, std::regex{u8R"(cdatan(_.*)?\.s[12])"}))
    {
        std::ifstream fin{entry.path().native(), std::ios::binary};
        std::string line;

        const auto is_cdatans1 = entry.path().extension() == ".s1";
        const auto begin = is_cdatans1 ? 0 : 57;
        const auto end = is_cdatans1 ? 57 : 245;
        const auto num_charas = end - begin + 1;
        std::vector<std::string> cdatan(10 * num_charas);
        size_t cdatan_idx = 0;
        for (int idx = begin; idx < end; ++idx)
        {
            for (int i = 0; i < 10; ++i)
            {
                std::getline(fin, line);
                cdatan[cdatan_idx] = line;
                ++cdatan_idx;
            }
        }
        const std::string map_id = is_cdatans1
            ? ""
            : entry.path().filename().to_u8string().substr(7 /* cdatan_ */);
        all_cdatan.emplace(map_id, cdatan);

        fin.close();
        ELONA_LOG("save.update")
            << "Remove " << entry.path().filename().to_u8string();
        fs::remove(entry.path());
    }

    for_each_cdata(
        save_dir,
        [&](auto& iar, auto& oar, const auto& map_id, int chara_index) {
            boost::uuids::uuid obj_id;
            int state;
            int position_x;
            int position_y;
            int next_position_x;
            int next_position_y;
            int time_to_revive;
            int vision_flag;
            int image;
            int sex;
            int relationship;
            int turn_cost;
            int current_speed;
            boost::uuids::uuid ai_item;
            std::string portrait;
            int interest;
            int time_interest_revive;
            int personality;
            int impression;
            int talk_type;
            int height;
            int weight;
            int birth_year;
            int nutrition;
            int can_talk;
            int quality;
            int turn;
            int id;
            int vision_distance;
            int enemy_id;
            int gold;
            int platinum_coin;
            int combat_style;
            int melee_attack_type;
            int fame;
            int experience;
            int required_experience;
            int speed_percentage;
            int level;
            int speed_percentage_in_next_turn;
            int skill_bonus;
            int total_skill_bonus;
            int inventory_weight;
            int max_inventory_weight;
            int inventory_weight_type;
            int max_level;
            int karma;
            int hp;
            int max_hp;
            int sp;
            int max_sp;
            int mp;
            int max_mp;
            int heal_value_per_nether_attack;
            std::string god_id;
            int piety_point;
            int praying_point;
            int sum_of_equipment_weight;
            int special_attack_type;
            int rate_to_pierce;
            int rate_of_critical_hit;
            int speed_correction_value;
            int original_relationship;
            int pv;
            int dv;
            int hit_bonus;
            int damage_bonus;
            int pv_correction_value;
            int dv_correction_value;
            int damage_reaction_info;
            int emotion_icon;
            int current_map;
            int current_dungeon_level;
            int related_quest_id;
            int direction;
            int period_of_contract;
            int hire_count;
            int insanity;
            int curse_power;
            int extra_attack;
            int extra_shot;
            int decrease_physical_damage;
            int nullify_damage;
            int cut_counterattack;
            int anorexia_count;
            int activity_type;
            int activity_turn;
            boost::uuids::uuid activity_item;
            int stops_activity_if_damaged;
            int quality_of_performance;
            int tip_gold;
            int character_role;
            int shop_rank;
            int activity_target;
            int shop_store_id;
            int time_to_restore;
            int cnpc_id;
            int initial_position_x;
            int initial_position_y;
            int hate;
            int ai_calm;
            int ai_move;
            int ai_dist;
            int ai_act_sub_freq;
            int ai_heal;
            int element_of_unarmed_attack;
            int poisoned;
            int sleep;
            int paralyzed;
            int blind;
            int confused;
            int fear;
            int dimmed;
            int drunk;
            int bleeding;
            int wet;
            int insane;
            int sick;
            int gravity;
            int choked;
            int furious;
            std::vector<int> growth_buffs;
            std::vector<std::tuple<int, boost::uuids::uuid>> equipment_slots;
            std::vector<int> normal_actions;
            std::vector<int> special_actions;
            std::vector<std::tuple<int, int, int>> buffs;
            std::vector<int> attr_adjs;
            std::bitset<sizeof(int) * 8 * 50> _flags;
            int _156;
            int _203;
            int target_position_x;
            int target_position_y;
            std::vector<std::tuple<int, int, int, int>> skills;

            iar(obj_id);
            iar(state);
            iar(position_x);
            iar(position_y);
            iar(next_position_x);
            iar(next_position_y);
            iar(time_to_revive);
            iar(vision_flag);
            iar(image);
            iar(sex);
            iar(relationship);
            iar(turn_cost);
            iar(current_speed);
            iar(ai_item);
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
            iar(combat_style);
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
            iar(activity_type);
            iar(activity_turn);
            iar(activity_item);
            iar(stops_activity_if_damaged);
            iar(quality_of_performance);
            iar(tip_gold);
            iar(character_role);
            iar(shop_rank);
            iar(activity_target);
            iar(shop_store_id);
            iar(time_to_restore);
            iar(cnpc_id);
            iar(initial_position_x);
            iar(initial_position_y);
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
            iar(equipment_slots);
            iar(normal_actions);
            iar(special_actions);
            iar(buffs);
            iar(attr_adjs);
            iar(_flags);
            iar(_156);
            iar(_203);
            iar(target_position_x);
            iar(target_position_y);
            iar(skills);

            std::string name;
            std::string alias;
            std::string race;
            std::string class_;
            std::string talk;
            {
                const auto relative_chara_idx =
                    chara_index < 57 ? chara_index : chara_index - 57;
                const auto& cdatan = all_cdatan[map_id];

                name = cdatan[relative_chara_idx * 10 + 0];
                alias = cdatan[relative_chara_idx * 10 + 1];
                race = cdatan[relative_chara_idx * 10 + 2];
                class_ = cdatan[relative_chara_idx * 10 + 3];
                talk = cdatan[relative_chara_idx * 10 + 4];

                if (state != 0)
                {
                    ELONA_LOG("save.update")
                        << "cdatan[" << chara_index << "]: n=" << name
                        << " a=" << alias << " r=" << race << " c=" << class_
                        << " t=" << talk;
                }
            }

            oar(obj_id);
            oar(state);
            oar(position_x);
            oar(position_y);
            oar(next_position_x);
            oar(next_position_y);
            oar(time_to_revive);
            oar(vision_flag);
            oar(image);
            oar(sex);
            oar(relationship);
            oar(turn_cost);
            oar(current_speed);
            oar(ai_item);
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
            oar(combat_style);
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
            oar(activity_type);
            oar(activity_turn);
            oar(activity_item);
            oar(stops_activity_if_damaged);
            oar(quality_of_performance);
            oar(tip_gold);
            oar(character_role);
            oar(shop_rank);
            oar(activity_target);
            oar(shop_store_id);
            oar(time_to_restore);
            oar(cnpc_id);
            oar(initial_position_x);
            oar(initial_position_y);
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
            oar(equipment_slots);
            oar(normal_actions);
            oar(special_actions);
            oar(buffs);
            oar(attr_adjs);
            oar(_flags);
            oar(_156);
            oar(_203);
            oar(target_position_x);
            oar(target_position_y);
            oar(name);
            oar(alias);
            oar(race);
            oar(class_);
            oar(talk);
            oar(skills);
        });
}



const char* _update_save_data_22_integer_item_id_to_string_id(int id)
{
    switch (id)
    {
    default: return "core.bug";
    case 0: return "core.bug";
    case 1: return "core.long_sword";
    case 2: return "core.dagger";
    case 3: return "core.hand_axe";
    case 4: return "core.club";
    case 5: return "core.magic_hat";
    case 6: return "core.fairy_hat";
    case 7: return "core.breastplate";
    case 8: return "core.robe";
    case 9: return "core.decorated_gloves";
    case 10: return "core.thick_gauntlets";
    case 11: return "core.heavy_boots";
    case 12: return "core.composite_boots";
    case 13: return "core.decorative_ring";
    case 14: return "core.scroll_of_identify";
    case 15: return "core.scroll_of_oracle";
    case 16: return "core.scroll_of_teleportation";
    case 17: return "core.scroll_of_incognito";
    case 18: return "core.rod_of_identify";
    case 19: return "core.rod_of_teleportation";
    case 20: return "core.spellbook_of_teleportation";
    case 21: return "core.spellbook_of_identify";
    case 22: return "core.spellbook_of_uncurse";
    case 23: return "core.book_a";
    case 24: return "core.book_b";
    case 25: return "core.bugged_book";
    case 26: return "core.bottle_of_dirty_water";
    case 27: return "core.potion_of_blindness";
    case 28: return "core.potion_of_confusion";
    case 29: return "core.potion_of_paralysis";
    case 30: return "core.sleeping_drug";
    case 31: return "core.crim_ale";
    case 32: return "core.spellbook_of_ice_bolt";
    case 33: return "core.spellbook_of_fire_bolt";
    case 34: return "core.spellbook_of_lightning_bolt";
    case 35: return "core.earth_crystal";
    case 36: return "core.mana_crystal";
    case 37: return "core.sun_crystal";
    case 38: return "core.gold_bar";
    case 39: return "core.raw_ore_of_rubynus";
    case 40: return "core.raw_ore_of_mica";
    case 41: return "core.raw_ore_of_emerald";
    case 42: return "core.raw_ore_of_diamond";
    case 43: return "core.wood_piece";
    case 44: return "core.junk_stone";
    case 45: return "core.garbage";
    case 46: return "core.broken_vase";
    case 47: return "core.washing";
    case 48: return "core.bonfire";
    case 49: return "core.flag";
    case 50: return "core.broken_sword";
    case 51: return "core.bone_fragment";
    case 52: return "core.skeleton";
    case 53: return "core.tombstone";
    case 54: return "core.gold_piece";
    case 55: return "core.platinum_coin";
    case 56: return "core.diablo";
    case 57: return "core.zantetsu";
    case 58: return "core.long_bow";
    case 59: return "core.knight_shield";
    case 60: return "core.pistol";
    case 61: return "core.arrow";
    case 62: return "core.bullet";
    case 63: return "core.scythe_of_void";
    case 64: return "core.mournblade";
    case 65: return "core.light_cloak";
    case 66: return "core.girdle";
    case 67: return "core.decorative_amulet";
    case 68: return "core.potion_of_cure_minor_wound";
    case 69: return "core.potion_of_cure_major_wound";
    case 70: return "core.potion_of_cure_critical_wound";
    case 71: return "core.potion_of_healing";
    case 72: return "core.potion_of_healer";
    case 73: return "core.ragnarok";
    case 74: return "core.potion_of_healer_odina";
    case 75: return "core.potion_of_healer_eris";
    case 76: return "core.potion_of_healer_jure";
    case 77: return "core.round_chair";
    case 78: return "core.bookshelf";
    case 79: return "core.luxury_drawer";
    case 80: return "core.boring_bed";
    case 81: return "core.rag_doll";
    case 82: return "core.toy";
    case 83: return "core.modern_table";
    case 84: return "core.dining_table";
    case 85: return "core.armor";
    case 86: return "core.lot_of_goods";
    case 87: return "core.lot_of_accessories";
    case 88: return "core.grand_piano";
    case 89: return "core.bar_table_alpha";
    case 90: return "core.bar_table_beta";
    case 91: return "core.barrel";
    case 92: return "core.modern_chair";
    case 93: return "core.pick";
    case 94: return "core.lantern";
    case 95: return "core.decorative_armor";
    case 96: return "core.anvil";
    case 97: return "core.closed_pot";
    case 98: return "core.open_pot";
    case 99: return "core.academic_table";
    case 100: return "core.rack_of_potions";
    case 101: return "core.square_chair";
    case 102: return "core.cheap_chair";
    case 103: return "core.cupboard";
    case 104: return "core.barn";
    case 105: return "core.neat_shelf";
    case 106: return "core.closet";
    case 107: return "core.variety_of_tools";
    case 108: return "core.variety_of_goods";
    case 109: return "core.well";
    case 110: return "core.variety_of_clothes";
    case 111: return "core.furnace";
    case 112: return "core.oven";
    case 113: return "core.sign";
    case 114: return "core.crossroad_sign";
    case 115: return "core.board";
    case 116: return "core.spellbook_of_minor_teleportation";
    case 117: return "core.empty_basket";
    case 118: return "core.spellbook_of_summon_monsters";
    case 119: return "core.rod_of_cure_minor_wound";
    case 120: return "core.rod_of_magic_missile";
    case 121: return "core.rod_of_summon_monsters";
    case 122: return "core.rod_of_ice_bolt";
    case 123: return "core.rod_of_fire_bolt";
    case 124: return "core.show_case_of_breads";
    case 125: return "core.rod_of_heal";
    case 126: return "core.beaker";
    case 127: return "core.alchemy_kit";
    case 128: return "core.pentagram";
    case 129: return "core.small_foliage_plant";
    case 130: return "core.rose";
    case 131: return "core.large_foliage_plant";
    case 132: return "core.sage";
    case 133: return "core.gazania";
    case 134: return "core.nerine";
    case 135: return "core.anemos";
    case 136: return "core.foxtail_grass";
    case 137: return "core.carnation";
    case 138: return "core.pillar_ornamented_with_plants";
    case 139: return "core.pillar_ornamented_with_flowers";
    case 140: return "core.canvas";
    case 141: return "core.map";
    case 142: return "core.food_maker";
    case 143: return "core.bundle_of_bows";
    case 144: return "core.bundle_of_weapons";
    case 145: return "core.decorated_cloth";
    case 146: return "core.decorated_armor";
    case 147: return "core.statue_of_armor";
    case 148: return "core.disorderly_book";
    case 149: return "core.lot_of_books";
    case 150: return "core.craft_rack";
    case 151: return "core.craft_book_shelf";
    case 152: return "core.lot_of_alcohols";
    case 153: return "core.kitchen";
    case 154: return "core.washstand";
    case 155: return "core.kitchen_oven";
    case 156: return "core.narrow_dining_table";
    case 157: return "core.elegant_table";
    case 158: return "core.gorgeous_candlestick";
    case 159: return "core.simple_shelf";
    case 160: return "core.sewing_kit";
    case 161: return "core.carpenters_tool";
    case 162: return "core.messy_cloth";
    case 163: return "core.silk_cloth";
    case 164: return "core.collapsed_grave";
    case 165: return "core.crumbled_grave";
    case 166: return "core.grave_ornamented_with_flowers";
    case 167: return "core.brand_new_grave";
    case 168: return "core.solemn_tomb";
    case 169: return "core.ancient_tomb";
    case 170: return "core.old_grave";
    case 171: return "core.altar";
    case 172: return "core.ceremony_altar";
    case 173: return "core.fountain";
    case 174: return "core.bunk_bed";
    case 175: return "core.rod_of_lightning_bolt";
    case 176: return "core.rod_of_slow";
    case 177: return "core.quwapana";
    case 178: return "core.aloe";
    case 179: return "core.edible_wild_plant";
    case 180: return "core.apple";
    case 181: return "core.grape";
    case 182: return "core.kiwi";
    case 183: return "core.cherry";
    case 184: return "core.guava";
    case 185: return "core.carrot";
    case 186: return "core.radish";
    case 187: return "core.sweet_potato";
    case 188: return "core.lettuce";
    case 189: return "core.stack_of_dishes";
    case 190: return "core.imo";
    case 191: return "core.api_nut";
    case 192: return "core.strawberry";
    case 193: return "core.healthy_leaf";
    case 194: return "core.rainbow_fruit";
    case 195: return "core.qucche";
    case 196: return "core.tangerine";
    case 197: return "core.lemon";
    case 198: return "core.green_pea";
    case 199: return "core.cbocchi";
    case 200: return "core.melon";
    case 201: return "core.leccho";
    case 202: return "core.rod_of_magic_mapping";
    case 203: return "core.rod_of_cure";
    case 204: return "core.corpse";
    case 205: return "core.bottle_of_whisky";
    case 206: return "core.ether_dagger";
    case 207: return "core.bow_of_vindale";
    case 208: return "core.worthless_fake_gold_bar";
    case 209: return "core.scroll_of_uncurse";
    case 210: return "core.stone";
    case 211: return "core.sickle";
    case 212: return "core.staff";
    case 213: return "core.spear";
    case 214: return "core.ore_piece";
    case 215: return "core.lot_of_empty_bottles";
    case 216: return "core.basket";
    case 217: return "core.empty_bowl";
    case 218: return "core.bowl";
    case 219: return "core.tight_rope";
    case 220: return "core.dead_fish";
    case 221: return "core.straw";
    case 222: return "core.animal_bone";
    case 223: return "core.pot";
    case 224: return "core.katana";
    case 225: return "core.scimitar";
    case 226: return "core.battle_axe";
    case 227: return "core.hammer";
    case 228: return "core.trident";
    case 229: return "core.long_staff";
    case 230: return "core.short_bow";
    case 231: return "core.machine_gun";
    case 232: return "core.claymore";
    case 233: return "core.ration";
    case 234: return "core.bardiche";
    case 235: return "core.halberd";
    case 236: return "core.scroll_of_return";
    case 237: return "core.figurine_of_warrior";
    case 238: return "core.figurine_of_sword";
    case 239: return "core.bejeweled_chest";
    case 240: return "core.chest";
    case 241: return "core.safe";
    case 242: return "core.scroll_of_magical_map";
    case 243: return "core.scroll_of_gain_attribute";
    case 244: return "core.scroll_of_wonder";
    case 245: return "core.scroll_of_minor_teleportation";
    case 246: return "core.spellbook_of_magic_mapping";
    case 247: return "core.spellbook_of_oracle";
    case 248: return "core.spellbook_of_return";
    case 249: return "core.spellbook_of_cure_minor_wound";
    case 250: return "core.spellbook_of_cure_critical_wound";
    case 251: return "core.spellbook_of_cure_eris";
    case 252: return "core.spellbook_of_cure_jure";
    case 253: return "core.bottle_of_beer";
    case 254: return "core.horn";
    case 255: return "core.campfire";
    case 256: return "core.portable_cooking_tool";
    case 257: return "core.spellbook_of_magic_arrow";
    case 258: return "core.stick_bread";
    case 259: return "core.raw_noodle";
    case 260: return "core.sack_of_flour";
    case 261: return "core.bomb_fish";
    case 262: return "core.poison";
    case 263: return "core.spellbook_of_nether_eye";
    case 264: return "core.spellbook_of_chaos_eye";
    case 265: return "core.spellbook_of_nerve_eye";
    case 266: return "core.wakizashi";
    case 267: return "core.spellbook_of_darkness_beam";
    case 268: return "core.spellbook_of_illusion_beam";
    case 269: return "core.spellbook_of_ice_ball";
    case 270: return "core.spellbook_of_fire_ball";
    case 271: return "core.spellbook_of_sound_ball";
    case 272: return "core.spellbook_of_chaos_ball";
    case 273: return "core.fire_wood";
    case 274: return "core.scarecrow";
    case 275: return "core.broom";
    case 276: return "core.long_pillar";
    case 277: return "core.broken_pillar";
    case 278: return "core.street_lamp";
    case 279: return "core.water_tub";
    case 280: return "core.comfortable_table";
    case 281: return "core.inner_tube";
    case 282: return "core.mysterious_map";
    case 283: return "core.suitcase";
    case 284: return "core.wallet";
    case 285: return "core.potion_of_restore_body";
    case 286: return "core.potion_of_restore_spirit";
    case 287: return "core.potion_of_potential";
    case 288: return "core.scroll_of_curse";
    case 289: return "core.spellbook_of_wishing";
    case 290: return "core.rod_of_wishing";
    case 291: return "core.well_kept_armor";
    case 292: return "core.rack_of_goods";
    case 293: return "core.rack_of_accessories";
    case 294: return "core.towel";
    case 295: return "core.ragged_table";
    case 296: return "core.cabinet";
    case 297: return "core.luxury_bed";
    case 298: return "core.vase";
    case 299: return "core.high_grade_dresser";
    case 300: return "core.neat_bar_table";
    case 301: return "core.large_bouquet";
    case 302: return "core.chest_of_clothes";
    case 303: return "core.giant_bed";
    case 304: return "core.plain_bed";
    case 305: return "core.coffin";
    case 306: return "core.food_processor";
    case 307: return "core.soft_bed";
    case 308: return "core.cheap_rack";
    case 309: return "core.dresser";
    case 310: return "core.clean_bed";
    case 311: return "core.bathtub";
    case 312: return "core.pachisuro_machine";
    case 313: return "core.casino_table";
    case 314: return "core.slot_machine";
    case 315: return "core.darts_board";
    case 316: return "core.big_foliage_plant";
    case 317: return "core.old_shelf";
    case 318: return "core.old_bookshelf";
    case 319: return "core.cheap_bed";
    case 320: return "core.cheap_table";
    case 321: return "core.neat_rack";
    case 322: return "core.simple_dresser";
    case 323: return "core.big_cupboard";
    case 324: return "core.sacred_altar";
    case 325: return "core.comfortable_bed";
    case 326: return "core.simple_rack";
    case 327: return "core.wide_chair";
    case 328: return "core.upright_piano";
    case 329: return "core.statue_of_cross";
    case 330: return "core.stump";
    case 331: return "core.dress";
    case 332: return "core.table";
    case 333: return "core.cargo_travelers_food";
    case 334: return "core.throne";
    case 335: return "core.golden_pedestal";
    case 336: return "core.statue_of_money";
    case 337: return "core.remains_skin";
    case 338: return "core.remains_blood";
    case 339: return "core.remains_eye";
    case 340: return "core.remains_heart";
    case 341: return "core.remains_bone";
    case 342: return "core.fishing_pole";
    case 343: return "core.rune";
    case 344: return "core.deed";
    case 345: return "core.moonfish";
    case 346: return "core.sardine";
    case 347: return "core.flatfish";
    case 348: return "core.manboo";
    case 349: return "core.seabream";
    case 350: return "core.salmon";
    case 351: return "core.globefish";
    case 352: return "core.tuna";
    case 353: return "core.cutlassfish";
    case 354: return "core.sandborer";
    case 355: return "core.gloves_of_vesda";
    case 356: return "core.blood_moon";
    case 357: return "core.ring_of_steel_dragon";
    case 358: return "core.staff_of_insanity";
    case 359: return "core.rankis";
    case 360: return "core.palmia_pride";
    case 361: return "core.shopkeepers_trunk";
    case 362: return "core.scroll_of_greater_identify";
    case 363: return "core.scroll_of_vanish_curse";
    case 364: return "core.potion_of_defender";
    case 365: return "core.spellbook_of_holy_shield";
    case 366: return "core.rod_of_silence";
    case 367: return "core.spellbook_of_silence";
    case 368: return "core.potion_of_silence";
    case 369: return "core.spellbook_of_regeneration";
    case 370: return "core.potion_of_troll_blood";
    case 371: return "core.spellbook_of_resistance";
    case 372: return "core.potion_of_resistance";
    case 373: return "core.spellbook_of_speed";
    case 374: return "core.spellbook_of_slow";
    case 375: return "core.potion_of_speed";
    case 376: return "core.potion_of_slow";
    case 377: return "core.rod_of_speed";
    case 378: return "core.spellbook_of_hero";
    case 379: return "core.potion_of_hero";
    case 380: return "core.spellbook_of_weakness";
    case 381: return "core.spellbook_of_elemental_scar";
    case 382: return "core.potion_of_weakness";
    case 383: return "core.spellbook_of_holy_veil";
    case 384: return "core.scroll_of_holy_veil";
    case 385: return "core.rod_of_holy_light";
    case 386: return "core.spellbook_of_holy_light";
    case 387: return "core.spellbook_of_holy_rain";
    case 388: return "core.scroll_of_holy_light";
    case 389: return "core.scroll_of_holy_rain";
    case 390: return "core.scroll_of_mana";
    case 391: return "core.rod_of_mana";
    case 392: return "core.bottle_of_sulfuric";
    case 393: return "core.gem_cutter";
    case 394: return "core.material_box";
    case 395: return "core.scroll_of_gain_material";
    case 396: return "core.spellbook_of_nightmare";
    case 397: return "core.spellbook_of_knowledge";
    case 398: return "core.scroll_of_knowledge";
    case 399: return "core.cargo_rag_doll";
    case 400: return "core.cargo_barrel";
    case 401: return "core.cargo_piano";
    case 402: return "core.cargo_rope";
    case 403: return "core.cargo_coffin";
    case 404: return "core.cargo_manboo";
    case 405: return "core.cargo_grave";
    case 406: return "core.cargo_tuna_fish";
    case 407: return "core.cargo_whisky";
    case 408: return "core.cargo_noble_toy";
    case 409: return "core.cargo_inner_tube";
    case 410: return "core.spellbook_of_detect_objects";
    case 411: return "core.scroll_of_detect_objects";
    case 412: return "core.rod_of_uncurse";
    case 413: return "core.red_treasure_machine";
    case 414: return "core.blue_treasure_machine";
    case 415: return "core.treasure_ball";
    case 416: return "core.rare_treasure_ball";
    case 417: return "core.vegetable_seed";
    case 418: return "core.fruit_seed";
    case 419: return "core.herb_seed";
    case 420: return "core.unknown_seed";
    case 421: return "core.artifact_seed";
    case 422: return "core.morgia";
    case 423: return "core.mareilon";
    case 424: return "core.spenseweed";
    case 425: return "core.curaria";
    case 426: return "core.alraunia";
    case 427: return "core.stomafillia";
    case 428: return "core.sleeping_bag";
    case 429: return "core.potion_of_weaken_resistance";
    case 430: return "core.scroll_of_growth";
    case 431: return "core.scroll_of_faith";
    case 432: return "core.potion_of_mutation";
    case 433: return "core.potion_of_cure_mutation";
    case 434: return "core.spellbook_of_mutation";
    case 435: return "core.banded_mail";
    case 436: return "core.plate_mail";
    case 437: return "core.ring_mail";
    case 438: return "core.composite_mail";
    case 439: return "core.chain_mail";
    case 440: return "core.pope_robe";
    case 441: return "core.light_mail";
    case 442: return "core.coat";
    case 443: return "core.breast_plate";
    case 444: return "core.bulletproof_jacket";
    case 445: return "core.gloves";
    case 446: return "core.plate_gauntlets";
    case 447: return "core.light_gloves";
    case 448: return "core.composite_gauntlets";
    case 449: return "core.small_shield";
    case 450: return "core.round_shield";
    case 451: return "core.shield";
    case 452: return "core.large_shield";
    case 453: return "core.kite_shield";
    case 454: return "core.tower_shield";
    case 455: return "core.shoes";
    case 456: return "core.boots";
    case 457: return "core.tight_boots";
    case 458: return "core.armored_boots";
    case 459: return "core.composite_girdle";
    case 460: return "core.plate_girdle";
    case 461: return "core.armored_cloak";
    case 462: return "core.cloak";
    case 463: return "core.feather_hat";
    case 464: return "core.heavy_helm";
    case 465: return "core.knight_helm";
    case 466: return "core.helm";
    case 467: return "core.composite_helm";
    case 468: return "core.peridot";
    case 469: return "core.talisman";
    case 470: return "core.neck_guard";
    case 471: return "core.charm";
    case 472: return "core.bejeweled_amulet";
    case 473: return "core.engagement_amulet";
    case 474: return "core.composite_ring";
    case 475: return "core.armored_ring";
    case 476: return "core.ring";
    case 477: return "core.engagement_ring";
    case 478: return "core.stethoscope";
    case 479: return "core.scroll_of_ally";
    case 480: return "core.rod_of_domination";
    case 481: return "core.spellbook_of_domination";
    case 482: return "core.crossbow";
    case 483: return "core.bolt";
    case 484: return "core.spellbook_of_web";
    case 485: return "core.rod_of_web";
    case 486: return "core.machine";
    case 487: return "core.computer";
    case 488: return "core.training_machine";
    case 489: return "core.camera";
    case 490: return "core.microwave_oven";
    case 491: return "core.server";
    case 492: return "core.storage";
    case 493: return "core.trash_can";
    case 494: return "core.chip";
    case 495: return "core.blank_disc";
    case 496: return "core.shot_gun";
    case 497: return "core.pop_corn";
    case 498: return "core.fried_potato";
    case 499: return "core.cyber_snack";
    case 500: return "core.scroll_of_inferior_material";
    case 501: return "core.scroll_of_change_material";
    case 502: return "core.scroll_of_superior_material";
    case 503: return "core.figurine";
    case 504: return "core.card";
    case 505: return "core.little_sisters_diary";
    case 506: return "core.scroll_of_enchant_weapon";
    case 507: return "core.scroll_of_greater_enchant_weapon";
    case 508: return "core.scroll_of_enchant_armor";
    case 509: return "core.scroll_of_greater_enchant_armor";
    case 510: return "core.heir_trunk";
    case 511: return "core.deed_of_heirship";
    case 512: return "core.laser_gun";
    case 513: return "core.energy_cell";
    case 514: return "core.rail_gun";
    case 515: return "core.scroll_of_recharge";
    case 516: return "core.bottle_of_water";
    case 517: return "core.rod_of_change_creature";
    case 518: return "core.rod_of_alchemy";
    case 519: return "core.bottle_of_dye";
    case 520: return "core.wing";
    case 521: return "core.deed_of_museum";
    case 522: return "core.deed_of_shop";
    case 523: return "core.tree_of_beech";
    case 524: return "core.tree_of_cedar";
    case 525: return "core.tree_of_fruitless";
    case 526: return "core.tree_of_fruits";
    case 527: return "core.dead_tree";
    case 528: return "core.tree_of_zelkova";
    case 529: return "core.tree_of_palm";
    case 530: return "core.tree_of_ash";
    case 531: return "core.furnance";
    case 532: return "core.fireplace";
    case 533: return "core.stove";
    case 534: return "core.giant_foliage_plant";
    case 535: return "core.big_table";
    case 536: return "core.painting_of_madam";
    case 537: return "core.painting_of_landscape";
    case 538: return "core.painting_of_sunflower";
    case 539: return "core.statue_of_cat";
    case 540: return "core.black_crystal";
    case 541: return "core.snow_man";
    case 542: return "core.deed_of_farm";
    case 543: return "core.deed_of_storage_house";
    case 544: return "core.disc";
    case 545: return "core.rod_of_wall_creation";
    case 546: return "core.spellbook_of_wall_creation";
    case 547: return "core.salary_chest";
    case 548: return "core.spellbook_of_healing_rain";
    case 549: return "core.scroll_of_healing_rain";
    case 550: return "core.spellbook_of_healing_hands";
    case 551: return "core.rod_of_healing_hands";
    case 552: return "core.feather";
    case 553: return "core.gem_seed";
    case 554: return "core.magical_seed";
    case 555: return "core.shelter";
    case 556: return "core.seven_league_boots";
    case 557: return "core.vindale_cloak";
    case 558: return "core.aurora_ring";
    case 559: return "core.potion_of_cure_corruption";
    case 560: return "core.masters_delivery_chest";
    case 561: return "core.shop_strongbox";
    case 562: return "core.register";
    case 563: return "core.textbook";
    case 564: return "core.spellbook_of_acid_ground";
    case 565: return "core.rod_of_acid_ground";
    case 566: return "core.acidproof_liquid";
    case 567: return "core.fireproof_blanket";
    case 568: return "core.coldproof_blanket";
    case 569: return "core.spellbook_of_fire_wall";
    case 570: return "core.rod_of_fire_wall";
    case 571: return "core.jerky";
    case 572: return "core.deed_of_ranch";
    case 573: return "core.egg";
    case 574: return "core.bottle_of_milk";
    case 575: return "core.shit";
    case 576: return "core.playback_disc";
    case 577: return "core.molotov";
    case 578: return "core.kitty_bank";
    case 579: return "core.freezer";
    case 580: return "core.modern_rack";
    case 581: return "core.rod_of_make_door";
    case 582: return "core.spellbook_of_make_door";
    case 583: return "core.torch";
    case 584: return "core.candle";
    case 585: return "core.fancy_lamp";
    case 586: return "core.modern_lamp_a";
    case 587: return "core.handful_of_snow";
    case 588: return "core.tree_of_naked";
    case 589: return "core.tree_of_fir";
    case 590: return "core.snow_scarecrow";
    case 591: return "core.mini_snow_man";
    case 592: return "core.snow_barrel";
    case 593: return "core.modern_lamp_b";
    case 594: return "core.statue_of_holy_cross";
    case 595: return "core.pillar";
    case 596: return "core.stained_glass_window";
    case 597: return "core.cargo_christmas_tree";
    case 598: return "core.cargo_snow_man";
    case 599: return "core.christmas_tree";
    case 600: return "core.giants_shackle";
    case 601: return "core.empty_bottle";
    case 602: return "core.holy_well";
    case 603: return "core.presidents_chair";
    case 604: return "core.green_plant";
    case 605: return "core.money_tree";
    case 606: return "core.barbecue_set";
    case 607: return "core.giant_cactus";
    case 608: return "core.square_window";
    case 609: return "core.window";
    case 610: return "core.triangle_plant";
    case 611: return "core.house_board";
    case 612: return "core.nice_window";
    case 613: return "core.kings_bed";
    case 614: return "core.flower_arch";
    case 615: return "core.bill";
    case 616: return "core.tax_masters_tax_box";
    case 617: return "core.bait";
    case 618: return "core.fish_a";
    case 619: return "core.fish_b";
    case 620: return "core.love_potion";
    case 621: return "core.treasure_map";
    case 622: return "core.small_medal";
    case 623: return "core.cat_sisters_diary";
    case 624: return "core.girls_diary";
    case 625: return "core.shrine_gate";
    case 626: return "core.bottle_of_hermes_blood";
    case 627: return "core.sages_helm";
    case 628: return "core.spellbook_of_incognito";
    case 629: return "core.disguise_set";
    case 630: return "core.material_kit";
    case 631: return "core.moon_gate";
    case 632: return "core.flying_scroll";
    case 633: return "core.panty";
    case 634: return "core.leash";
    case 635: return "core.mine";
    case 636: return "core.lockpick";
    case 637: return "core.skeleton_key";
    case 638: return "core.scroll_of_escape";
    case 639: return "core.happy_apple";
    case 640: return "core.unicorn_horn";
    case 641: return "core.cooler_box";
    case 642: return "core.rice_barrel";
    case 643: return "core.eastern_bed";
    case 644: return "core.decorated_window";
    case 645: return "core.king_drawer";
    case 646: return "core.menu_board";
    case 647: return "core.black_board";
    case 648: return "core.sofa";
    case 649: return "core.flowerbed";
    case 650: return "core.toilet";
    case 651: return "core.craft_cupboard";
    case 652: return "core.sink";
    case 653: return "core.junk";
    case 654: return "core.double_bed";
    case 655: return "core.hero_cheese";
    case 656: return "core.eastern_lamp";
    case 657: return "core.eastern_window";
    case 658: return "core.chochin";
    case 659: return "core.partition";
    case 660: return "core.spellbook_of_darkness_arrow";
    case 661: return "core.dal_i_thalion";
    case 662: return "core.magic_fruit";
    case 663: return "core.monster_heart";
    case 664: return "core.speed_ring";
    case 665: return "core.statue_of_opatos";
    case 666: return "core.statue_of_lulwy";
    case 667: return "core.sisters_love_fueled_lunch";
    case 668: return "core.book_of_rachel";
    case 669: return "core.cargo_art";
    case 670: return "core.cargo_canvas";
    case 671: return "core.nuclear_bomb";
    case 672: return "core.secret_treasure";
    case 673: return "core.wind_bow";
    case 674: return "core.winchester_premium";
    case 675: return "core.kumiromi_scythe";
    case 676: return "core.elemental_staff";
    case 677: return "core.holy_lance";
    case 678: return "core.lucky_dagger";
    case 679: return "core.gaia_hammer";
    case 680: return "core.lulwys_gem_stone_of_god_speed";
    case 681: return "core.jures_gem_stone_of_holy_rain";
    case 682: return "core.kumiromis_gem_stone_of_rejuvenation";
    case 683: return "core.gem_stone_of_mani";
    case 684: return "core.gene_machine";
    case 685: return "core.monster_ball";
    case 686: return "core.statue_of_jure";
    case 687: return "core.ancient_book";
    case 688: return "core.iron_maiden";
    case 689: return "core.guillotine";
    case 690: return "core.pan_flute";
    case 691: return "core.lute";
    case 692: return "core.harmonica";
    case 693: return "core.harp";
    case 694: return "core.eastern_partition";
    case 695: return "core.axe_of_destruction";
    case 696: return "core.spellbook_of_magic_ball";
    case 697: return "core.spellbook_of_magic_laser";
    case 698: return "core.potion_of_salt_solution";
    case 699: return "core.little_ball";
    case 700: return "core.town_book";
    case 701: return "core.deck";
    case 702: return "core.rabbits_tail";
    case 703: return "core.whistle";
    case 704: return "core.vomit";
    case 705: return "core.beggars_pendant";
    case 706: return "core.potion_of_descent";
    case 707: return "core.stradivarius";
    case 708: return "core.book_of_resurrection";
    case 709: return "core.scroll_of_contingency";
    case 710: return "core.spellbook_of_contingency";
    case 711: return "core.potion_of_evolution";
    case 712: return "core.deed_of_dungeon";
    case 713: return "core.shuriken";
    case 714: return "core.grenade";
    case 715: return "core.secret_experience_of_kumiromi";
    case 716: return "core.vanilla_rock";
    case 717: return "core.secret_experience_of_lomias";
    case 718: return "core.shenas_panty";
    case 719: return "core.claymore_unique";
    case 720: return "core.happy_bed";
    case 721: return "core.statue_of_ehekatl";
    case 722: return "core.arbalest";
    case 723: return "core.twin_edge";
    case 724: return "core.music_ticket";
    case 725: return "core.kill_kill_piano";
    case 726: return "core.alud";
    case 727: return "core.shield_of_thorn";
    case 728: return "core.crimson_plate";
    case 729: return "core.gift";
    case 730: return "core.token_of_friendship";
    case 731: return "core.spellbook_of_4_dimensional_pocket";
    case 732: return "core.spellbook_of_harvest";
    case 733: return "core.sand_bag";
    case 734: return "core.small_gamble_chest";
    case 735: return "core.scythe";
    case 736: return "core.fireproof_liquid";
    case 737: return "core.scroll_of_name";
    case 738: return "core.fortune_cookie";
    case 739: return "core.frisias_tail";
    case 740: return "core.unknown_shell";
    case 741: return "core.hiryu_to";
    case 742: return "core.license_of_the_void_explorer";
    case 743: return "core.plank_of_carneades";
    case 744: return "core.schrodingers_cat";
    case 745: return "core.heart";
    case 746: return "core.tamers_whip";
    case 747: return "core.book_of_bokonon";
    case 748: return "core.summoning_crystal";
    case 749: return "core.statue_of_creator";
    case 750: return "core.upstairs";
    case 751: return "core.downstairs";
    case 752: return "core.new_years_gift";
    case 753: return "core.kotatsu";
    case 754: return "core.daruma";
    case 755: return "core.kagami_mochi";
    case 756: return "core.mochi";
    case 757: return "core.five_horned_helm";
    case 758: return "core.mauser_c96_custom";
    case 759: return "core.lightsabre";
    case 760: return "core.garoks_hammer";
    case 761: return "core.goulds_piano";
    case 762: return "core.festival_wreath";
    case 763: return "core.pedestal";
    case 764: return "core.counter";
    case 765: return "core.red_stall";
    case 766: return "core.blue_stall";
    case 767: return "core.jures_body_pillow";
    case 768: return "core.new_years_decoration";
    case 769: return "core.miniature_tree";
    case 770: return "core.bottle_of_soda";
    case 771: return "core.blue_capsule_drug";
    case 772: return "core.tomato";
    case 773: return "core.large_bookshelf";
    case 774: return "core.luxury_cabinet";
    case 775: return "core.special_steamed_meat_bun";
    case 776: return "core.statue_of_kumiromi";
    case 777: return "core.statue_of_mani";
    case 778: return "core.luxury_sofa";
    case 779: return "core.deer_head";
    case 780: return "core.fur_carpet";
    case 781: return "core.kitchen_knife";
    case 782: return "core.dish";
    case 783: return "core.recipe";
    case 784: return "core.recipe_holder";
    case 785: return "core.bottle_of_salt";
    case 786: return "core.sack_of_sugar";
    case 787: return "core.puff_puff_bread";
    case 788: return "core.skull_bow";
    case 789: return "core.pot_for_testing";
    case 790: return "core.frying_pan_for_testing";
    case 791: return "core.dragon_slayer";
    case 792: return "core.putitoro";
    }
}



const char* _update_save_data_22_integer_material_id_to_string_id(int id)
{
    switch (id)
    {
    default: return "";
    case 0: return "";
    case 1: return "core.leather";
    case 2: return "core.silk";
    case 3: return "core.cloth";
    case 4: return "core.scale";
    case 5: return "core.glass";
    case 7: return "core.mithril";
    case 8: return "core.ether";
    case 9: return "core.steel";
    case 10: return "core.iron";
    case 11: return "core.crystal";
    case 12: return "core.bronze";
    case 13: return "core.diamond";
    case 14: return "core.spirit_cloth";
    case 15: return "core.rubynus";
    case 16: return "core.paper";
    case 17: return "core.dawn_cloth";
    case 18: return "core.bone";
    case 19: return "core.chain";
    case 20: return "core.obsidian";
    case 21: return "core.mica";
    case 22: return "core.pearl";
    case 23: return "core.emerald";
    case 24: return "core.dragon_scale";
    case 25: return "core.silver";
    case 26: return "core.platinum";
    case 27: return "core.zylon";
    case 28: return "core.griffon_scale";
    case 29: return "core.titanium";
    case 30: return "core.chrome";
    case 31: return "core.adamantium";
    case 32: return "core.gold";
    case 33: return "core.coral";
    case 34: return "core.lead";
    case 35: return "core.raw";
    case 36: return "core.vegetable_seed";
    case 37: return "core.fruit_seed";
    case 38: return "core.herb_seed";
    case 39: return "core.unknown_plant_seed";
    case 40: return "core.artifact_seed";
    case 41: return "core.gem_seed";
    case 42: return "core.magical_plant_seed";
    case 43: return "core.wood";
    case 1000: return "core._heavy";
    case 1001: return "core._light";
    }
}



/*
 * Update save data from v22 to v23.
 *
 * - Convert integer fields from 32 bit to 64 bit.
 * - Change item ID from integer to string.
 * - Change item material ID from integer to string.
 * - Separate bitset into boolean fields.
 */
void _update_save_data_22(const fs::path& save_dir)
{
    for_each_inv(
        save_dir, [&](auto& iar, auto& oar, const auto&, int item_index) {
            bool exists;
            boost::uuids::uuid obj_id;
            int number;
            int value;
            int image;
            int id;
            int quality;
            int position_x;
            int position_y;
            int weight;
            int identify_state;
            int count;
            int dice_x;
            int dice_y;
            int damage_bonus;
            int hit_bonus;
            int dv;
            int pv;
            int skill;
            int curse_state;
            int body_part;
            int function;
            int enhancement;
            int own_state;
            int color;
            int subname;
            int material;
            int param1;
            int param2;
            int param3;
            int param4;
            int identify_level;
            int turn;
            uint32_t flags;
            std::vector<std::tuple<int, int>> enchantments;

            iar(exists);
            if (!exists)
            {
                ELONA_LOG("save.update") << "item(" << item_index << "): nil";
                oar(exists);
                return;
            }

            iar(obj_id);
            iar(number);
            iar(value);
            iar(image);
            iar(id);
            iar(quality);
            iar(position_x);
            iar(position_y);
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
            iar(identify_level);
            iar(turn);
            iar(flags);
            iar(enchantments);

            int64_t number_;
            int64_t value_;
            std::string id_;
            int64_t weight_;
            int64_t charges_;
            int64_t dice_rolls_;
            int64_t dice_faces_;
            int64_t dice_bonus_;
            int64_t hit_bonus_;
            int64_t dv_;
            int64_t pv_;
            int64_t bonus_value_;
            std::string material_;
            int64_t identify_level_;
            int64_t turn_;
            bool is_acidproof;
            bool is_fireproof;
            bool is_coldproof;
            bool is_precious;
            bool has_charges;
            bool has_cooldown_time;
            bool is_aphrodisiac;
            bool is_poisoned;
            bool is_blessed_by_ehekatl;
            bool is_stolen;
            bool is_quest_target;
            bool is_no_drop;
            bool is_alive;
            bool is_eternal_force;
            bool is_handmade;
            bool is_showroom_only;
            {
                number_ = number;
                value_ = value;
                id_ = _update_save_data_22_integer_item_id_to_string_id(id);
                weight_ = weight;
                charges_ = count;
                dice_rolls_ = dice_x;
                dice_faces_ = dice_y;
                dice_bonus_ = damage_bonus;
                hit_bonus_ = hit_bonus;
                dv_ = dv;
                pv_ = pv;
                bonus_value_ = enhancement;
                material_ =
                    _update_save_data_22_integer_material_id_to_string_id(
                        material);
                identify_level_ = identify_level;
                turn_ = turn;
                is_acidproof = flags & (1 << 1);
                is_fireproof = flags & (1 << 2);
                is_coldproof = flags & (1 << 3);
                is_precious = flags & (1 << 5);
                has_charges = flags & (1 << 4);
                has_cooldown_time = flags & (1 << 7);
                is_aphrodisiac = flags & (1 << 6);
                is_poisoned = flags & (1 << 14);
                is_blessed_by_ehekatl = flags & (1 << 8);
                is_stolen = flags & (1 << 9);
                is_quest_target = flags & (1 << 12);
                is_no_drop = flags & (1 << 13);
                is_alive = flags & (1 << 10);
                is_eternal_force = flags & (1 << 15);
                is_handmade = flags & (1 << 17);
                is_showroom_only = flags & (1 << 16);

                ELONA_LOG("save.update")
                    << "item(" << item_index << "): i " << id << " -> " << id_
                    << " m " << material << " -> " << material_;
            }

            oar(exists);
            oar(obj_id);
            oar(number_);
            oar(value_);
            oar(image);
            oar(id_);
            oar(quality);
            oar(position_x);
            oar(position_y);
            oar(weight_);
            oar(identify_state);
            oar(charges_);
            oar(dice_rolls_);
            oar(dice_faces_);
            oar(dice_bonus_);
            oar(hit_bonus_);
            oar(dv_);
            oar(pv_);
            oar(skill);
            oar(curse_state);
            oar(body_part);
            oar(function);
            oar(bonus_value_);
            oar(own_state);
            oar(color);
            oar(subname);
            oar(material_);
            oar(param1);
            oar(param2);
            oar(param3);
            oar(param4);
            oar(identify_level_);
            oar(turn_);
            oar(is_acidproof);
            oar(is_fireproof);
            oar(is_coldproof);
            oar(is_precious);
            oar(has_charges);
            oar(has_cooldown_time);
            oar(is_aphrodisiac);
            oar(is_poisoned);
            oar(is_blessed_by_ehekatl);
            oar(is_stolen);
            oar(is_quest_target);
            oar(is_no_drop);
            oar(is_alive);
            oar(is_eternal_force);
            oar(is_handmade);
            oar(is_showroom_only);
            oar(enchantments);
        });
}



/*
 * Update save data from v23 to v24.
 *
 * - Shrink `Item::enchantments` array by deleting enchantments of ID 0.
 */
void _update_save_data_23(const fs::path& save_dir)
{
    for_each_inv(
        save_dir, [&](auto& iar, auto& oar, const auto&, int item_index) {
            bool exists;
            boost::uuids::uuid obj_id;
            int64_t number;
            int64_t value;
            int image;
            std::string id;
            int quality;
            int position_x;
            int position_y;
            int64_t weight;
            int identify_state;
            int64_t charges;
            int64_t dice_rolls;
            int64_t dice_faces;
            int64_t dice_bonus;
            int64_t hit_bonus;
            int64_t dv;
            int64_t pv;
            int skill;
            int curse_state;
            int body_part;
            int function;
            int64_t bonus_value;
            int own_state;
            int color;
            int subname;
            std::string material;
            int param1;
            int param2;
            int param3;
            int param4;
            int64_t identify_level;
            int64_t turn;
            bool is_acidproof;
            bool is_fireproof;
            bool is_coldproof;
            bool is_precious;
            bool has_charges;
            bool has_cooldown_time;
            bool is_aphrodisiac;
            bool is_poisoned;
            bool is_blessed_by_ehekatl;
            bool is_stolen;
            bool is_quest_target;
            bool is_no_drop;
            bool is_alive;
            bool is_eternal_force;
            bool is_handmade;
            bool is_showroom_only;
            std::vector<std::tuple<int, int>> enchantments;

            iar(exists);
            if (!exists)
            {
                ELONA_LOG("save.update") << "item(" << item_index << "): nil";
                oar(exists);
                return;
            }

            iar(obj_id);
            iar(number);
            iar(value);
            iar(image);
            iar(id);
            iar(quality);
            iar(position_x);
            iar(position_y);
            iar(weight);
            iar(identify_state);
            iar(charges);
            iar(dice_rolls);
            iar(dice_faces);
            iar(dice_bonus);
            iar(hit_bonus);
            iar(dv);
            iar(pv);
            iar(skill);
            iar(curse_state);
            iar(body_part);
            iar(function);
            iar(bonus_value);
            iar(own_state);
            iar(color);
            iar(subname);
            iar(material);
            iar(param1);
            iar(param2);
            iar(param3);
            iar(param4);
            iar(identify_level);
            iar(turn);
            iar(is_acidproof);
            iar(is_fireproof);
            iar(is_coldproof);
            iar(is_precious);
            iar(has_charges);
            iar(has_cooldown_time);
            iar(is_aphrodisiac);
            iar(is_poisoned);
            iar(is_blessed_by_ehekatl);
            iar(is_stolen);
            iar(is_quest_target);
            iar(is_no_drop);
            iar(is_alive);
            iar(is_eternal_force);
            iar(is_handmade);
            iar(is_showroom_only);
            iar(enchantments);

            {
                // Remove enchantments of ID 0.
                range::remove_erase_if(enchantments, [](const auto& pair) {
                    return std::get<0>(pair) == 0;
                });
                ELONA_LOG("save.update")
                    << "item(" << item_index
                    << ").enchantments truncated: " << enchantments.size();
            }

            oar(exists);
            oar(obj_id);
            oar(number);
            oar(value);
            oar(image);
            oar(id);
            oar(quality);
            oar(position_x);
            oar(position_y);
            oar(weight);
            oar(identify_state);
            oar(charges);
            oar(dice_rolls);
            oar(dice_faces);
            oar(dice_bonus);
            oar(hit_bonus);
            oar(dv);
            oar(pv);
            oar(skill);
            oar(curse_state);
            oar(body_part);
            oar(function);
            oar(bonus_value);
            oar(own_state);
            oar(color);
            oar(subname);
            oar(material);
            oar(param1);
            oar(param2);
            oar(param3);
            oar(param4);
            oar(identify_level);
            oar(turn);
            oar(is_acidproof);
            oar(is_fireproof);
            oar(is_coldproof);
            oar(is_precious);
            oar(has_charges);
            oar(has_cooldown_time);
            oar(is_aphrodisiac);
            oar(is_poisoned);
            oar(is_blessed_by_ehekatl);
            oar(is_stolen);
            oar(is_quest_target);
            oar(is_no_drop);
            oar(is_alive);
            oar(is_eternal_force);
            oar(is_handmade);
            oar(is_showroom_only);
            oar(enchantments);
        });
}



void _update_save_data(const fs::path& save_dir, int serial_id)
{
    if (serial_id <= 14)
    {
        throw std::runtime_error{
            "Too old save! Please update the save in v0.5.0 first."};
    }

#define ELONA_CASE(n) \
    case n: _update_save_data_##n(save_dir); break;

    switch (serial_id)
    {
        ELONA_CASE(15)
        ELONA_CASE(16)
        ELONA_CASE(17)
        ELONA_CASE(18)
        ELONA_CASE(19)
        ELONA_CASE(20)
        ELONA_CASE(21)
        ELONA_CASE(22)
        ELONA_CASE(23)
    default: assert(0); break;
    }
#undef ELONA_CASE
}

} // namespace



void save_update(const fs::path& save_dir)
{
    const auto version_filepath = save_dir / "version.s0";

    Version version;
    serialization::binary::load(version_filepath, version);

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
    serialization::binary::save(version_filepath, version);
}

} // namespace elona

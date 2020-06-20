#include "save_update.hpp"

#include "../util/fileutil.hpp"
#include "../util/strutil.hpp"
#include "character.hpp"
#include "item.hpp"
#include "lua_env/handle_manager.hpp"
#include "lua_env/lua_env.hpp"
#include "lua_env/mod_serializer.hpp"
#include "serialization/serialization.hpp"



namespace elona
{

namespace
{

template <typename F>
void for_each_cdata(const fs::path& save_dir, F f)
{
    for (const auto& entry : filesystem::glob_files(
             save_dir, std::regex{u8R"((g_)?cdata(_.*)?\.s[12])"}))
    {
        std::ifstream fin{entry.path().native(), std::ios::binary};
        serialization::binary::IArchive iar{fin};

        std::ostringstream out;
        serialization::binary::OArchive oar{out};

        const auto is_cdatas1 = entry.path().extension() == "s1";
        const auto begin = is_cdatas1 ? 0 : 57;
        const auto end = is_cdatas1 ? 57 : 245;
        for (int idx = begin; idx < end; ++idx)
        {
            f(iar, oar, idx);
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
            const auto mid =
                filepathutil::to_utf8_path(entry.path().filename());
            const auto mdata = save_dir / ("mdata_" + mid.substr(4));
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
    for_each_cdata(save_dir, [](auto& iar, auto& oar, int chara_index) {
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
                    << "equipment_slots[" << i << "]: " << equipment_slots[i]
                    << " -> (" << type << ", " << index_plus_one << ")";
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
    default: assert(0); break;
    }
#undef ELONA_CASE
}

} // namespace



void update_save_data(const fs::path& save_dir)
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

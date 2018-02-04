#include "character.hpp"
#include <cassert>
#include <iostream>
#include <type_traits>
#include "elona.hpp"
#include "range.hpp"
#include "variables.hpp"



namespace elona
{


character::character()
    : growth_buffs(10)
    , body_parts(30)
    , act(10)
    , buffs(16)
    , attr_adjs(10)
    , flags(31)
{
}


void character::clear()
{
    character tmp{};
    using std::swap;
    swap(*this, tmp);
}


void character::clear_flags()
{
    range::fill(flags, 0);
}


character_data::character_data()
    : storage(245)
{
}



// Serialize the entire data from offset
std::unique_ptr<char[]> character_data::serialize(int offset) const
{
#define PUT(value) \
    do \
    { \
        *reinterpret_cast<std::remove_cv_t< \
            std::remove_reference_t<decltype(storage[i].value)>>*>( \
            buf.get() + (i - offset) * sizeof(int) * 500 + j) = \
            storage[i].value; \
        j += sizeof(storage[i].value); \
    } while (0);

    std::unique_ptr<char[]> buf{
        new char[(std::size(storage) - offset) * sizeof(int) * 500]};
    std::fill(
        buf.get(),
        buf.get() + (std::size(storage) - offset) * sizeof(int) * 500,
        0);
    for (size_t i = offset; i < std::size(storage); ++i)
    {
        size_t j = 0;
        PUT(state);
        PUT(position.x);
        PUT(position.y);
        PUT(next_position.x);
        PUT(next_position.y);
        PUT(time_to_revive);
        PUT(vision_flag);
        PUT(image);
        PUT(sex);
        PUT(relationship);
        PUT(turn_cost);
        PUT(current_speed);
        PUT(item_which_will_be_used);
        PUT(portrait);
        PUT(interest);
        PUT(time_interest_revive);
        PUT(personality);
        PUT(impression);
        PUT(talk_type);
        PUT(height);
        PUT(weight);
        PUT(birth_year);
        PUT(nutrition);
        PUT(can_talk);
        PUT(quality);
        PUT(turn);
        PUT(id);
        PUT(vision_distance);
        PUT(enemy_id);
        PUT(gold);
        PUT(platinum_coin);
        PUT(equipment_type);
        PUT(melee_attack_type);
        PUT(fame);
        PUT(experience);
        PUT(required_experience);
        PUT(speed_percentage);
        PUT(level);
        PUT(speed_percentage_in_next_turn);
        PUT(skill_bonus);
        PUT(total_skill_bonus);
        PUT(inventory_weight);
        PUT(max_inventory_weight);
        PUT(inventory_weight_type);
        PUT(max_level);
        PUT(karma);
        PUT(hp);
        PUT(max_hp);
        PUT(sp);
        PUT(max_sp);
        PUT(mp);
        PUT(max_mp);
        PUT(heal_value_per_nether_attack);
        PUT(god);
        PUT(piety_point);
        PUT(praying_point);
        PUT(sum_of_equipment_weight);
        PUT(special_attack_type);
        PUT(rate_to_pierce);
        PUT(rate_of_critical_hit);
        PUT(speed_correction_value);
        PUT(original_relationship);
        PUT(pv);
        PUT(dv);
        PUT(hit_bonus);
        PUT(damage_bonus);
        PUT(pv_correction_value);
        PUT(dv_correction_value);
        PUT(damage_reaction_info);
        PUT(emotion_icon);
        PUT(current_map);
        PUT(current_dungeon_level);
        PUT(related_quest_id);
        PUT(direction);
        PUT(period_of_contract);
        PUT(hire_count);
        PUT(insanity);
        PUT(curse_power);
        PUT(extra_attack);
        PUT(extra_shot);
        PUT(decrease_physical_damage);
        PUT(nullify_damage);
        PUT(cut_counterattack);
        PUT(anorexia_count);
        PUT(continuous_action_id);
        PUT(continuous_action_turn);
        PUT(continuous_action_item);
        PUT(stops_continuous_action_if_damaged);
        PUT(quality_of_performance);
        PUT(tip_gold);
        PUT(character_role);
        PUT(shop_rank);
        PUT(continuous_action_target);
        PUT(shop_store_id);
        PUT(time_to_restore);
        PUT(cnpc_id);
        PUT(initial_position.x);
        PUT(initial_position.y);
        PUT(hate);
        PUT(ai_calm);
        PUT(ai_move);
        PUT(ai_dist);
        PUT(ai_act_sub_freq);
        PUT(ai_heal);
        PUT(ai_act_num);
        PUT(element_of_unarmed_attack);
        PUT(poisoned);
        PUT(sleep);
        PUT(paralyzed);
        PUT(blind);
        PUT(confused);
        PUT(fear);
        PUT(dimmed);
        PUT(drunk);
        PUT(bleeding);
        PUT(wet);
        PUT(insane);
        PUT(sick);
        PUT(gravity);
        PUT(choked);
        PUT(furious);
        PUT(growth_buffs[0]);
        PUT(growth_buffs[1]);
        PUT(growth_buffs[2]);
        PUT(growth_buffs[3]);
        PUT(growth_buffs[4]);
        PUT(growth_buffs[5]);
        PUT(growth_buffs[6]);
        PUT(growth_buffs[7]);
        PUT(growth_buffs[8]);
        PUT(growth_buffs[9]);
        PUT(body_parts[0]);
        PUT(body_parts[1]);
        PUT(body_parts[2]);
        PUT(body_parts[3]);
        PUT(body_parts[4]);
        PUT(body_parts[5]);
        PUT(body_parts[6]);
        PUT(body_parts[7]);
        PUT(body_parts[8]);
        PUT(body_parts[9]);
        PUT(body_parts[10]);
        PUT(body_parts[11]);
        PUT(body_parts[12]);
        PUT(body_parts[13]);
        PUT(body_parts[14]);
        PUT(body_parts[15]);
        PUT(body_parts[16]);
        PUT(body_parts[17]);
        PUT(body_parts[18]);
        PUT(body_parts[19]);
        PUT(body_parts[20]);
        PUT(body_parts[21]);
        PUT(body_parts[22]);
        PUT(body_parts[23]);
        PUT(body_parts[24]);
        PUT(body_parts[25]);
        PUT(body_parts[26]);
        PUT(body_parts[27]);
        PUT(body_parts[28]);
        PUT(body_parts[29]);
        PUT(act[0]);
        PUT(act[1]);
        PUT(act[2]);
        PUT(act[3]);
        PUT(act[4]);
        PUT(act[5]);
        PUT(act[6]);
        PUT(act[7]);
        PUT(act[8]);
        PUT(act[9]);
        PUT(buffs[0].id);
        PUT(buffs[0].power);
        PUT(buffs[0].turns);
        PUT(buffs[1].id);
        PUT(buffs[1].power);
        PUT(buffs[1].turns);
        PUT(buffs[2].id);
        PUT(buffs[2].power);
        PUT(buffs[2].turns);
        PUT(buffs[3].id);
        PUT(buffs[3].power);
        PUT(buffs[3].turns);
        PUT(buffs[4].id);
        PUT(buffs[4].power);
        PUT(buffs[4].turns);
        PUT(buffs[5].id);
        PUT(buffs[5].power);
        PUT(buffs[5].turns);
        PUT(buffs[6].id);
        PUT(buffs[6].power);
        PUT(buffs[6].turns);
        PUT(buffs[7].id);
        PUT(buffs[7].power);
        PUT(buffs[7].turns);
        PUT(buffs[8].id);
        PUT(buffs[8].power);
        PUT(buffs[8].turns);
        PUT(buffs[9].id);
        PUT(buffs[9].power);
        PUT(buffs[9].turns);
        PUT(buffs[10].id);
        PUT(buffs[10].power);
        PUT(buffs[10].turns);
        PUT(buffs[11].id);
        PUT(buffs[11].power);
        PUT(buffs[11].turns);
        PUT(buffs[12].id);
        PUT(buffs[12].power);
        PUT(buffs[12].turns);
        PUT(buffs[13].id);
        PUT(buffs[13].power);
        PUT(buffs[13].turns);
        PUT(buffs[14].id);
        PUT(buffs[14].power);
        PUT(buffs[14].turns);
        PUT(buffs[15].id);
        PUT(buffs[15].power);
        PUT(buffs[15].turns);
        PUT(attr_adjs[0]);
        PUT(attr_adjs[1]);
        PUT(attr_adjs[2]);
        PUT(attr_adjs[3]);
        PUT(attr_adjs[4]);
        PUT(attr_adjs[5]);
        PUT(attr_adjs[6]);
        PUT(attr_adjs[7]);
        PUT(attr_adjs[8]);
        PUT(attr_adjs[9]);
        PUT(flags[0]);
        PUT(flags[1]);
        PUT(flags[2]);
        PUT(flags[3]);
        PUT(flags[4]);
        PUT(flags[5]);
        PUT(flags[6]);
        PUT(flags[7]);
        PUT(flags[8]);
        PUT(flags[9]);
        PUT(flags[10]);
        PUT(flags[11]);
        PUT(flags[12]);
        PUT(flags[13]);
        PUT(flags[14]);
        PUT(flags[15]);
        PUT(flags[16]);
        PUT(flags[17]);
        PUT(flags[18]);
        PUT(flags[19]);
        PUT(flags[20]);
        PUT(flags[21]);
        PUT(flags[22]);
        PUT(flags[23]);
        PUT(flags[24]);
        PUT(flags[25]);
        PUT(flags[26]);
        PUT(flags[27]);
        PUT(flags[28]);
        PUT(flags[29]);
        PUT(flags[30]);
        PUT(_40);
        PUT(_158);
        PUT(_156);
        PUT(_203);
        PUT(_205);
        PUT(_206);

        if (storage[i].state || !std::empty(cdatan(0, i)))
            std::cout << i << "  " << storage[i].state << cdatan(0, i)
                      << std::endl;
    }
    return std::move(buf);
#undef PUT
}



void character_data::deserialize(
    std::unique_ptr<char[]> raw_data,
    int size,
    int offset)
{
#define GET(value) \
    do \
    { \
        storage[i].value = *reinterpret_cast<std::remove_cv_t< \
            std::remove_reference_t<decltype(storage[i].value)>>*>( \
            raw_data.get() + (i - offset) * sizeof(int) * 500 + j); \
        j += sizeof(storage[i].value); \
    } while (0);

    for (size_t i = size_t(offset);; ++i)
    {
        size_t j = 0;
        GET(state);
        GET(position.x);
        GET(position.y);
        GET(next_position.x);
        GET(next_position.y);
        GET(time_to_revive);
        GET(vision_flag);
        GET(image);
        GET(sex);
        GET(relationship);
        GET(turn_cost);
        GET(current_speed);
        GET(item_which_will_be_used);
        GET(portrait);
        GET(interest);
        GET(time_interest_revive);
        GET(personality);
        GET(impression);
        GET(talk_type);
        GET(height);
        GET(weight);
        GET(birth_year);
        GET(nutrition);
        GET(can_talk);
        GET(quality);
        GET(turn);
        GET(id);
        GET(vision_distance);
        GET(enemy_id);
        GET(gold);
        GET(platinum_coin);
        GET(equipment_type);
        GET(melee_attack_type);
        GET(fame);
        GET(experience);
        GET(required_experience);
        GET(speed_percentage);
        GET(level);
        GET(speed_percentage_in_next_turn);
        GET(skill_bonus);
        GET(total_skill_bonus);
        GET(inventory_weight);
        GET(max_inventory_weight);
        GET(inventory_weight_type);
        GET(max_level);
        GET(karma);
        GET(hp);
        GET(max_hp);
        GET(sp);
        GET(max_sp);
        GET(mp);
        GET(max_mp);
        GET(heal_value_per_nether_attack);
        GET(god);
        GET(piety_point);
        GET(praying_point);
        GET(sum_of_equipment_weight);
        GET(special_attack_type);
        GET(rate_to_pierce);
        GET(rate_of_critical_hit);
        GET(speed_correction_value);
        GET(original_relationship);
        GET(pv);
        GET(dv);
        GET(hit_bonus);
        GET(damage_bonus);
        GET(pv_correction_value);
        GET(dv_correction_value);
        GET(damage_reaction_info);
        GET(emotion_icon);
        GET(current_map);
        GET(current_dungeon_level);
        GET(related_quest_id);
        GET(direction);
        GET(period_of_contract);
        GET(hire_count);
        GET(insanity);
        GET(curse_power);
        GET(extra_attack);
        GET(extra_shot);
        GET(decrease_physical_damage);
        GET(nullify_damage);
        GET(cut_counterattack);
        GET(anorexia_count);
        GET(continuous_action_id);
        GET(continuous_action_turn);
        GET(continuous_action_item);
        GET(stops_continuous_action_if_damaged);
        GET(quality_of_performance);
        GET(tip_gold);
        GET(character_role);
        GET(shop_rank);
        GET(continuous_action_target);
        GET(shop_store_id);
        GET(time_to_restore);
        GET(cnpc_id);
        GET(initial_position.x);
        GET(initial_position.y);
        GET(hate);
        GET(ai_calm);
        GET(ai_move);
        GET(ai_dist);
        GET(ai_act_sub_freq);
        GET(ai_heal);
        GET(ai_act_num);
        GET(element_of_unarmed_attack);
        GET(poisoned);
        GET(sleep);
        GET(paralyzed);
        GET(blind);
        GET(confused);
        GET(fear);
        GET(dimmed);
        GET(drunk);
        GET(bleeding);
        GET(wet);
        GET(insane);
        GET(sick);
        GET(gravity);
        GET(choked);
        GET(furious);
        GET(growth_buffs[0]);
        GET(growth_buffs[1]);
        GET(growth_buffs[2]);
        GET(growth_buffs[3]);
        GET(growth_buffs[4]);
        GET(growth_buffs[5]);
        GET(growth_buffs[6]);
        GET(growth_buffs[7]);
        GET(growth_buffs[8]);
        GET(growth_buffs[9]);
        GET(body_parts[0]);
        GET(body_parts[1]);
        GET(body_parts[2]);
        GET(body_parts[3]);
        GET(body_parts[4]);
        GET(body_parts[5]);
        GET(body_parts[6]);
        GET(body_parts[7]);
        GET(body_parts[8]);
        GET(body_parts[9]);
        GET(body_parts[10]);
        GET(body_parts[11]);
        GET(body_parts[12]);
        GET(body_parts[13]);
        GET(body_parts[14]);
        GET(body_parts[15]);
        GET(body_parts[16]);
        GET(body_parts[17]);
        GET(body_parts[18]);
        GET(body_parts[19]);
        GET(body_parts[20]);
        GET(body_parts[21]);
        GET(body_parts[22]);
        GET(body_parts[23]);
        GET(body_parts[24]);
        GET(body_parts[25]);
        GET(body_parts[26]);
        GET(body_parts[27]);
        GET(body_parts[28]);
        GET(body_parts[29]);
        GET(act[0]);
        GET(act[1]);
        GET(act[2]);
        GET(act[3]);
        GET(act[4]);
        GET(act[5]);
        GET(act[6]);
        GET(act[7]);
        GET(act[8]);
        GET(act[9]);
        GET(buffs[0].id);
        GET(buffs[0].power);
        GET(buffs[0].turns);
        GET(buffs[1].id);
        GET(buffs[1].power);
        GET(buffs[1].turns);
        GET(buffs[2].id);
        GET(buffs[2].power);
        GET(buffs[2].turns);
        GET(buffs[3].id);
        GET(buffs[3].power);
        GET(buffs[3].turns);
        GET(buffs[4].id);
        GET(buffs[4].power);
        GET(buffs[4].turns);
        GET(buffs[5].id);
        GET(buffs[5].power);
        GET(buffs[5].turns);
        GET(buffs[6].id);
        GET(buffs[6].power);
        GET(buffs[6].turns);
        GET(buffs[7].id);
        GET(buffs[7].power);
        GET(buffs[7].turns);
        GET(buffs[8].id);
        GET(buffs[8].power);
        GET(buffs[8].turns);
        GET(buffs[9].id);
        GET(buffs[9].power);
        GET(buffs[9].turns);
        GET(buffs[10].id);
        GET(buffs[10].power);
        GET(buffs[10].turns);
        GET(buffs[11].id);
        GET(buffs[11].power);
        GET(buffs[11].turns);
        GET(buffs[12].id);
        GET(buffs[12].power);
        GET(buffs[12].turns);
        GET(buffs[13].id);
        GET(buffs[13].power);
        GET(buffs[13].turns);
        GET(buffs[14].id);
        GET(buffs[14].power);
        GET(buffs[14].turns);
        GET(buffs[15].id);
        GET(buffs[15].power);
        GET(buffs[15].turns);
        GET(attr_adjs[0]);
        GET(attr_adjs[1]);
        GET(attr_adjs[2]);
        GET(attr_adjs[3]);
        GET(attr_adjs[4]);
        GET(attr_adjs[5]);
        GET(attr_adjs[6]);
        GET(attr_adjs[7]);
        GET(attr_adjs[8]);
        GET(attr_adjs[9]);
        GET(flags[0]);
        GET(flags[1]);
        GET(flags[2]);
        GET(flags[3]);
        GET(flags[4]);
        GET(flags[5]);
        GET(flags[6]);
        GET(flags[7]);
        GET(flags[8]);
        GET(flags[9]);
        GET(flags[10]);
        GET(flags[11]);
        GET(flags[12]);
        GET(flags[13]);
        GET(flags[14]);
        GET(flags[15]);
        GET(flags[16]);
        GET(flags[17]);
        GET(flags[18]);
        GET(flags[19]);
        GET(flags[20]);
        GET(flags[21]);
        GET(flags[22]);
        GET(flags[23]);
        GET(flags[24]);
        GET(flags[25]);
        GET(flags[26]);
        GET(flags[27]);
        GET(flags[28]);
        GET(flags[29]);
        GET(flags[30]);
        GET(_40);
        GET(_158);
        GET(_156);
        GET(_203);
        GET(_205);
        GET(_206);

        if (storage[i].state)
            std::cout << i << "r  " << cdatan(0, i) << std::endl;

        size -= 500 * sizeof(int);
        if (size == 0)
            return;
    }

#undef GET
}



int cbit(int type, int cc)
{
    assert(type < sizeof(int) * 8 * 50);
    return cdata(cc).flags[type / 32] & (1 << (type % 32)) ? 1 : 0;
}



void cbitmod(int type, int cc, int on)
{
    assert(type < sizeof(int) * 8 * 50);
    if (on)
    {
        cdata(cc).flags[type / 32] |= 1 << (type % 32);
    }
    else
    {
        cdata(cc).flags[type / 32] &= ~(1 << (type % 32));
    }
}


} // namespace elona

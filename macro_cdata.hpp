#pragma once



#define cdata_state(cc) cdata(cc).state
#define cdata_x(cc) cdata(cc).position.x
#define cdata_y(cc) cdata(cc).position.y
#define cdata_next_x(cc) cdata(cc).next_position.x
#define cdata_next_y(cc) cdata(cc).next_position.y
#define cdata_time_to_revive(cc) cdata(cc).time_to_revive
#define cdata_vision_flag(cc) cdata(cc).vision_flag
#define cdata_image(cc) cdata(cc).image
#define cdata_sex(cc) cdata(cc).sex
#define cdata_relationship(cc) cdata(cc).relationship
#define cdata_turn_cost(cc) cdata(cc).turn_cost
#define cdata_current_speed(cc) cdata(cc).current_speed
#define cdata_item_which_will_be_used(cc) cdata(cc).item_which_will_be_used
#define cdata_portrait(cc) cdata(cc).portrait
#define cdata_interest(cc) cdata(cc).interest
#define cdata_time_interest_revive(cc) cdata(cc).time_interest_revive
#define cdata_personality(cc) cdata(cc).personality
#define cdata_impression(cc) cdata(cc).impression
#define cdata_talk_type(cc) cdata(cc).talk_type
#define cdata_height(cc) cdata(cc).height
#define cdata_weight(cc) cdata(cc).weight
#define cdata_birth_year(cc) cdata(cc).birth_year
#define cdata_nutrition(cc) cdata(cc).nutrition
#define cdata_can_talk(cc) cdata(cc).can_talk
#define cdata_quality(cc) cdata(cc).quality
#define cdata_turn(cc) cdata(cc).turn
#define cdata_id(cc) cdata(cc).id
#define cdata_vision_distance(cc) cdata(cc).vision_distance
#define cdata_enemy_id(cc) cdata(cc).enemy_id
#define cdata_gold(cc) cdata(cc).gold
#define cdata_platinum_coin(cc) cdata(cc).platinum_coin
#define cdata_equipment_type(cc) cdata(cc).equipment_type
#define cdata_melee_attack_type(cc) cdata(cc).melee_attack_type
#define cdata_fame(cc) cdata(cc).fame
#define cdata_experience(cc) cdata(cc).experience
#define cdata_required_experience(cc) cdata(cc).required_experience
#define cdata_speed_percentage(cc) cdata(cc).speed_percentage
#define cdata_level(cc) cdata(cc).level
#define cdata_speed_percentage_in_next_turn(cc) \
    cdata(cc).speed_percentage_in_next_turn
#define cdata_skill_bonus(cc) cdata(cc).skill_bonus
#define cdata_total_skill_bonus(cc) cdata(cc).total_skill_bonus
#define cdata_inventory_weight(cc) cdata(cc).inventory_weight
#define cdata_max_inventory_weight(cc) cdata(cc).max_inventory_weight
#define cdata_inventory_weight_type(cc) cdata(cc).inventory_weight_type
#define cdata_max_level(cc) cdata(cc).max_level
#define cdata_karma(cc) cdata(cc).karma
#define cdata_hp(cc) cdata(cc).hp
#define cdata_max_hp(cc) cdata(cc).max_hp
#define cdata_sp(cc) cdata(cc).sp
#define cdata_max_sp(cc) cdata(cc).max_sp
#define cdata_mp(cc) cdata(cc).mp
#define cdata_max_mp(cc) cdata(cc).max_mp
#define cdata_heal_value_per_nether_attack(cc) \
    cdata(cc).heal_value_per_nether_attack
#define cdata_god(cc) cdata(cc).god
#define cdata_piety_point(cc) cdata(cc).piety_point
#define cdata_praying_point(cc) cdata(cc).praying_point
#define cdata_sum_of_equipment_weight(cc) cdata(cc).sum_of_equipment_weight
#define cdata_special_attack_type(cc) cdata(cc).special_attack_type
#define cdata_rate_to_pierce(cc) cdata(cc).rate_to_pierce
#define cdata_rate_of_critical_hit(cc) cdata(cc).rate_of_critical_hit
#define cdata_speed_correction_value(cc) cdata(cc).speed_correction_value
#define cdata_original_relationship(cc) cdata(cc).original_relationship
#define cdata_pv(cc) cdata(cc).pv
#define cdata_dv(cc) cdata(cc).dv
#define cdata_hit_bonus(cc) cdata(cc).hit_bonus
#define cdata_damage_bonus(cc) cdata(cc).damage_bonus
#define cdata_pv_correction_value(cc) cdata(cc).pv_correction_value
#define cdata_dv_correction_value(cc) cdata(cc).dv_correction_value
#define cdata_damage_reaction_info(cc) cdata(cc).damage_reaction_info
#define cdata_emotion_icon(cc) cdata(cc).emotion_icon
#define cdata_current_map(cc) cdata(cc).current_map
#define cdata_current_dungeon_level(cc) cdata(cc).current_dungeon_level
#define cdata_related_quest_id(cc) cdata(cc).related_quest_id
#define cdata_direction(cc) cdata(cc).direction
#define cdata_period_of_contract(cc) cdata(cc).period_of_contract
#define cdata_hire_count(cc) cdata(cc).hire_count
#define cdata_insanity(cc) cdata(cc).insanity
#define cdata_curse_power(cc) cdata(cc).curse_power
#define cdata_extra_attack(cc) cdata(cc).extra_attack
#define cdata_extra_shot(cc) cdata(cc).extra_shot
#define cdata_decrease_physical_damage(cc) cdata(cc).decrease_physical_damage
#define cdata_nullify_damage(cc) cdata(cc).nullify_damage
#define cdata_cut_counterattack(cc) cdata(cc).cut_counterattack
#define cdata_anorexia_count(cc) cdata(cc).anorexia_count
#define cdata_continuous_action_id(cc) cdata(cc).continuous_action_id
#define cdata_continuous_action_turn(cc) cdata(cc).continuous_action_turn
#define cdata_continuous_action_item(cc) cdata(cc).continuous_action_item
#define cdata_stops_continuous_action_if_damaged(cc) \
    cdata(cc).stops_continuous_action_if_damaged
#define cdata_quality_of_performance(cc) cdata(cc).quality_of_performance
#define cdata_tip_gold(cc) cdata(cc).tip_gold
#define cdata_character_role(cc) cdata(cc).character_role
#define cdata_shop_rank(cc) cdata(cc).shop_rank
#define cdata_continuous_action_target(cc) cdata(cc).continuous_action_target
#define cdata_shop_store_id(cc) cdata(cc).shop_store_id
#define cdata_time_to_restore(cc) cdata(cc).time_to_restore
#define cdata_cnpc_id(cc) cdata(cc).cnpc_id
#define cdata_initial_x(cc) cdata(cc).initial_position.x
#define cdata_initial_y(cc) cdata(cc).initial_position.y
#define cdata_hate(cc) cdata(cc).hate
#define cdata_ai_calm(cc) cdata(cc).ai_calm
#define cdata_ai_move(cc) cdata(cc).ai_move
#define cdata_ai_dist(cc) cdata(cc).ai_dist
#define cdata_ai_act_sub_freq(cc) cdata(cc).ai_act_sub_freq
#define cdata_ai_heal(cc) cdata(cc).ai_heal
#define cdata_ai_act_num(cc) cdata(cc).ai_act_num
#define cdata_element_of_unarmed_attack(cc) cdata(cc).element_of_unarmed_attack
#define cdata_poisoned(cc) cdata(cc).poisoned
#define cdata_sleep(cc) cdata(cc).sleep
#define cdata_paralyzed(cc) cdata(cc).paralyzed
#define cdata_blind(cc) cdata(cc).blind
#define cdata_confused(cc) cdata(cc).confused
#define cdata_fear(cc) cdata(cc).fear
#define cdata_dimmed(cc) cdata(cc).dimmed
#define cdata_drunk(cc) cdata(cc).drunk
#define cdata_bleeding(cc) cdata(cc).bleeding
#define cdata_wet(cc) cdata(cc).wet
#define cdata_insane(cc) cdata(cc).insane
#define cdata_sick(cc) cdata(cc).sick
#define cdata_gravity(cc) cdata(cc).gravity
#define cdata_choked(cc) cdata(cc).choked
#define cdata_furious(cc) cdata(cc).furious

#define cdata_growth_buff(cc, i) cdata(cc).growth_buffs[i]

inline int cdata_body_part_index(int i)
{
    return i >= 100 ? i - 100 : i;
}
#define cdata_body_part(cc, i) cdata(cc).body_parts[cdata_body_part_index(i)]

#define cdata_ai_act(cc, i) cdata(cc).act[i]
#define cdata_ai_act_sub(cc, i) cdata(cc).act[(i) + 5]

#define cdata_buff_id(cc, i) cdata(cc).buffs[i].id
#define cdata_buff_power(cc, i) cdata(cc).buffs[i].power
#define cdata_buff_turns(cc, i) cdata(cc).buffs[i].turns

#define cdata_attr_adj(cc, i) cdata(cc).attr_adjs[i]

#define cdata_40(cc) cdata(cc)._40
#define cdata_158(cc) cdata(cc)._158

#define cdata_156(cc) cdata(cc)._156

#define cdata_203(cc) cdata(cc)._203
#define cdata_205(cc) cdata(cc)._205
#define cdata_206(cc) cdata(cc)._206



/*
state 0
x 1
y 2
next_x 3
next_y 4
time_to_revive 5
vision_flag 6
image 7
sex 8
relationship 9
turn_cost 10
current_speed 11
item_which_will_be_used 12
portrait 13
interest 14
time_interest_revive 15
personality 16
impression 17
talk_type 18
height 19
weight 20
birth_year 21
nutrition 22
can_talk 23
quality 25
turn 26
id 27
vision_distance 28
enemy_id 29
gold 30
platinum_coin 31
equipment_type 32
melee_attack_type 33
fame 34
experience 35
required_experience 36
speed_percentage 37
level 38
speed_percentage_in_next_turn 39
skill_bonus 41
total_skill_bonus 42
inventory_weight 43
max_inventory_weight 44
inventory_weight_type 45
max_level 48
karma 49
hp 50
max_hp 51
sp 52
max_sp 53
mp 55
max_mp 56
heal_value_per_nether_attack 60
god 61
piety_point 62
praying_point 63
sum_of_equipment_weight 64
special_attack_type 65
rate_to_pierce 66
rate_of_critical_hit 67
speed_correction_value 68
original_relationship 69
pv 70
dv 71
hit_bonus 72
damage_bonus 73
pv_correction_value 76
dv_correction_value 77
damage_reaction_info 78
emotion_icon 79
current_map 80
current_dungeon_level 81
related_quest_id 82
direction 83
period_of_contract 84
hire_count 85
insanity 86
curse_power 87
extra_attack 88
extra_shot 89
decrease_physical_damage 90
nullify_damage 91
cut_counterattack 92
anorexia_count 93
continuous_action_id 140
continuous_action_turn 141
continuous_action_item 142
stops_continuous_action_if_damaged 143
quality_of_performance 144
tip_gold 145
character_role 150
shop_rank 151
continuous_action_target 152
shop_store_id 153
time_to_restore 154
cnpc_id 157
initial_x 171
initial_y 172
hate 201
ai_calm 202
ai_move 207
ai_dist 208
ai_act_sub_freq 209
ai_heal 211
ai_act_num 212
element_of_unarmed_attack 230
poisoned 250
sleep 251
paralyzed 252
blind 253
confused 254
fear 255
dimmed 256
drunk 257
bleeding 258
wet 259
insane 260
sick 261
gravity 262
choked 263
furious 264

growth_buff 270 + i

body_part 100 + i

ai_act 215 + i
ai_act_sub 220 + i

buff_id 280 + i*3
buff_power 280 + i*3 + 1
buff_turns 280 + i*3 + 2

attr_adj 240 + i

40 40
158 158

156 156

203 203
205 205
206 206
*/

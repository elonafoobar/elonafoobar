#pragma once


#define inv_number(ci) inv(ci).number
#define inv_value(ci) inv(ci).value
#define inv_image(ci) inv(ci).image
#define inv_id(ci) inv(ci).id
#define inv_quality(ci) inv(ci).quality
#define inv_x(ci) inv(ci).position.x
#define inv_y(ci) inv(ci).position.y
#define inv_weight(ci) inv(ci).weight
#define inv_identification_state(ci) inv(ci).identification_state
#define inv_count(ci) inv(ci).count
#define inv_dice_x(ci) inv(ci).dice_x
#define inv_dice_y(ci) inv(ci).dice_y
#define inv_damage_bonus(ci) inv(ci).damage_bonus
#define inv_hit_bonus(ci) inv(ci).hit_bonus
#define inv_dv(ci) inv(ci).dv
#define inv_pv(ci) inv(ci).pv
#define inv_skill(ci) inv(ci).skill
#define inv_curse_state(ci) inv(ci).curse_state
#define inv_body_part(ci) inv(ci).body_part
#define inv_function(ci) inv(ci).function
#define inv_enhancement(ci) inv(ci).enhancement
#define inv_own_state(ci) inv(ci).own_state
#define inv_color(ci) inv(ci).color
#define inv_subname(ci) inv(ci).subname
#define inv_material(ci) inv(ci).material
#define inv_param1(ci) inv(ci).param1
#define inv_param2(ci) inv(ci).param2
#define inv_param3(ci) inv(ci).param3
#define inv_param4(ci) inv(ci).param4
#define inv_difficulty_of_identification(ci) \
    inv(ci).difficulty_of_identification
#define inv_turn(ci) inv(ci).turn

#define inv_enchantment_id(ci, i) inv(ci).enchantments[i].id
#define inv_enchantment_power(ci, i) inv(ci).enchantments[i].power



/*
number                       0
value                        1
image                        2
id                           3
quality                      4
x                            5
y                            6
weight                       7
identification_state         8
count                        9
dice_x                       10
dice_y                       11
damage_bonus                 12
hit_bonus                    13
dv                           14
pv                           15
skill                        16
curse_state                  17
body_part                    18
function                     19
enhancement                  20
own_state                    21
color                        22
subname                      23
material                     24
param1                       25
param2                       26
param3                       27
param4                       28
difficulty_of_identification 29
turn                         30
enchantment_id               40 + i*2
enchantment_power            40 + i*2 + 1
*/

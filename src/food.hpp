#pragma once

namespace elona
{

enum class curse_state_t;

void continuous_action_eating();
void continuous_action_eating_finish();

int chara_anorexia(int = 0);
void chara_vomit(int = 0);
void eatstatus(curse_state_t, int);
void sickifcursed(curse_state_t, int, int);
void cure_anorexia(int = 0);
void show_eating_message();
void eat_rotten_food();

void cook();

void make_dish(int, int);

void apply_general_eating_effect();
void eating_effect_eat_iron();
void eating_effect_insanity();
void eating_effect_eat_horse();
void eating_effect_eat_holy_one();
void eating_effect_eat_at();
void eating_effect_eat_guard();
void eating_effect_fire();
void eating_effect_insanity2();
void eating_effect_eat_cute_one();
void eating_effect_eat_lovely_one();
void eating_effect_eat_poisonous_one();
void eating_effect_regeneration();
void eating_effect_eat_rotten_one();
void eating_effect_strength();
void eating_effect_magic();
void eating_effect_insanity3();
void eating_effect_calm();
void eating_effect_insanity4();
void eating_effect_chaos();
void eating_effect_lightning();
void eating_effect_eat_cat();
void eating_effect_ether();
void eating_effect_constitution();
void eating_effect_magic2();
void eating_effect_strength2();
void eating_effect_will();
void eating_effect_quick();
void eating_effect_pregnant();

} // namespace elona

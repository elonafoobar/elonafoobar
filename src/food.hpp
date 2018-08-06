#pragma once
#include <string>


namespace elona
{



enum class curse_state_t;
struct character;

void chara_anorexia(character& cc);
void cure_anorexia(character& cc);

void chara_vomit(character& cc);

void eatstatus(curse_state_t, int);

void get_sick_if_cursed(curse_state_t state, character& drinker);

void get_hungry(character& cc);

void show_eating_message();
void eat_rotten_food();

void cook();

void make_dish(int, int);

void apply_general_eating_effect(int);

std::string foodname(int, const std::string&, int = 0, int = 0);



} // namespace elona

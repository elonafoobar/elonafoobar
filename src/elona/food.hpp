#pragma once

#include <string>



namespace elona
{

enum class CurseState;
struct Character;
struct Item;



void chara_anorexia(Character& cc);
void cure_anorexia(Character& cc);

void chara_vomit(Character& cc);

void eatstatus(CurseState, int);

void get_sick_if_cursed(CurseState state, Character& drinker);

void get_hungry(Character& cc);

void show_eating_message();
void eat_rotten_food();

void cook(Item& cook_tool, Item& food);

void make_dish(Item& food, int dish_rank);

void apply_general_eating_effect(Character& eater, Item& food);

std::string foodname(int, const std::string&, int = 0, int = 0);

void foods_get_rotten();

} // namespace elona

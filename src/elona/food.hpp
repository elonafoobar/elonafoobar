#pragma once

#include <string>



namespace elona
{

enum class CurseState;
struct Character;
struct Item;



void chara_anorexia(Character& chara);
void cure_anorexia(Character& chara);

void chara_vomit(Character& chara);

void food_apply_curse_state(Character& eater, CurseState curse_state);

void get_sick_if_cursed(CurseState state, Character& drinker);

void get_hungry(Character& chara);

void show_eating_message(const Character& eater);
void eat_rotten_food(Character& eater);

void food_cook(Character& cook, Item& cook_tool, Item& food);

void make_dish(Item& food, int dish_rank);

void apply_general_eating_effect(Character& eater, Item& food);

std::string foodname(int, const std::string&, int = 0, int = 0);

void foods_get_rotten();

} // namespace elona

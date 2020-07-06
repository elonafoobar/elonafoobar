#pragma once

#include <string>

#include "eobject/eobject.hpp"



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

void food_cook(Character& cook, const ItemRef& cook_tool, const ItemRef& food);

void make_dish(const ItemRef& food, int dish_rank);

void apply_general_eating_effect(Character& eater, const ItemRef& food);

std::string foodname(int, const std::string&, int = 0, int = 0);

void foods_get_rotten();

} // namespace elona

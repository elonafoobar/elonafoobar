#pragma once
#include <string>

namespace elona
{

enum class curse_state_t;

int chara_anorexia(int = 0);
void chara_vomit(int = 0);
void eatstatus(curse_state_t, int);
void sickifcursed(curse_state_t, int, int);
void cure_anorexia(int = 0);
void get_hungry(int);
void show_eating_message();
void eat_rotten_food();

void cook();

void make_dish(int, int);

void apply_general_eating_effect(int);

std::string foodname(int, const std::string&, int = 0, int = 0);

} // namespace elona

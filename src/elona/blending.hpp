#pragma once
#include <string>

#include "elona.hpp"
#include "enums.hpp"

namespace elona
{

TurnResult blending_menu();
void initialize_recipememory();
void initialize_recipe();
std::string rpmatname(int = 0);
std::string rpname(int = 0);
std::string rpsuccessrate(int = 0);
int rpdiff(int = 0, int = 0, int = 0);
void clear_rprefmat();
int blendcheckext(int = 0, int = 0);
int blendcheckmat(int = 0);
int blendmatnum(int = 0, int = 0);
void window_recipe2(int = 0);
int blendlist(elona_vector2<int>&, int);
int blending_find_required_mat();
int blending_spend_materials();
void blending_start_attempt();
void blending_proc_on_success_events();

} // namespace elona

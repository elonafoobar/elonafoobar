#pragma once
#include "enums.hpp"
#include "elona.hpp"
#include <string>

namespace elona
{

#define window_recipe(a, b, c, d, e, f) window_recipe_(b, c, d, e, f)

turn_result_t blending_menu();
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

}

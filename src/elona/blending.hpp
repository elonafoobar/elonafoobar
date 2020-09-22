#pragma once

#include <string>



namespace elona
{

enum class TurnResult;



void blending_init_recipe_data();

std::string blending_get_recipe_name(int recipe_id);

void blending_clear_recipe_memory();

TurnResult blending_menu();
void window_recipe2(int = 0);

} // namespace elona

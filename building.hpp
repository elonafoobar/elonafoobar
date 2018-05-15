#pragma once

namespace elona
{

enum class turn_result_t;

void initialize_home_adata();
turn_result_t build_new_building();
void addbuilding(int = 0, int = 0, int = 0, int = 0);
void start_home_map_mode();
void show_home_value();
void show_shop_log();
void try_extend_shop();

void prompt_hiring();
void prompt_move_ally();
void prompt_ally_staying();

void label_1723();
void update_shop_and_report();
void update_shop();
void label_1727(bool);
void update_museum();
void label_1729(int);
void label_1730();
void update_ranch();

} // namespace elona

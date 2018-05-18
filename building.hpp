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

void prepare_hourse_board_tiles();
void update_shop_and_report();
void update_shop();
void calc_collection_value(bool);
void update_museum();
void calc_hairloom_value(int);
void calc_home_rank();
void update_ranch();

} // namespace elona

#pragma once

namespace elona
{

enum class TurnResult;

void initialize_home_adata();
TurnResult build_new_building();
TurnResult show_house_board();
void addbuilding(int related_town_quest_id, int building_type, int x, int y);
void start_home_map_mode();
void show_home_value();
void show_shop_log();
void try_extend_shop();

void prompt_hiring();
void prompt_move_ally();
void prompt_ally_staying();

void update_shop_and_report();
void update_shop();
void calc_collection_value(bool);
void update_museum();
void calc_hairloom_value(int);
void calc_home_rank();
void update_ranch();

} // namespace elona

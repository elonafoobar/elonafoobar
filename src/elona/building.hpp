#pragma once

#include <vector>

#include "eobject/eobject.hpp"



namespace elona
{

enum class TurnResult;
struct Item;



void initialize_home_adata();
TurnResult build_new_building(const ItemRef& deed);
TurnResult show_house_board();
void addbuilding(int related_town_quest_id, int building_type, int x, int y);
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

struct HomeRankHeirloom
{
    ItemRef item;
    int value;
};
std::vector<HomeRankHeirloom> building_update_home_rank();

void update_ranch();

int calcincome(int = 0);
void supply_income();

void create_harvested_item();

int getworker(int = 0, int = 0);
void removeworker(int = 0);

void grow_plant(int);
void harvest_plant(int);
void try_to_grow_plant(int = 0);

} // namespace elona

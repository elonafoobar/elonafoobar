#pragma once
#include "optional.hpp"
#include "turn_sequence.hpp"

namespace elona
{

struct character;

void rowact_check(int = 0);
void rowact_item(int = 0);
void rowactend(int = 0);

void activity_handle_damage(character&);
optional<turn_result_t> activity_proc(character&);

void prompt_stop_continuous_action();
void continuous_action_perform();
void continuous_action_sex();
void continuous_action_blending();
void continuous_action_eating();
void continuous_action_eating_finish();
void continuous_action_others();

void select_random_fish();
void get_fish();
int search_material_spot();
void spot_fishing();
void spot_material();
void spot_digging();
void spot_mining_or_wall();
turn_result_t do_dig_after_sp_check();
void matdelmain(int = 0, int = 0);
void matgetmain(int = 0, int = 0, int = 0);

} // namespace elona

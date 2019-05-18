#pragma once
#include "optional.hpp"
#include "turn_sequence.hpp"

namespace elona
{

struct Character;

void rowact_check(int chara_index);
void rowact_item(int item_index);

void activity_handle_damage(Character&);
optional<TurnResult> activity_proc(Character&);

void continuous_action_perform();
void continuous_action_sex();
void continuous_action_blending();
void continuous_action_eating();
void continuous_action_eating_finish();
void continuous_action_others();

int search_material_spot();
void spot_fishing();
void spot_material();
void spot_digging();
void spot_mining_or_wall();
TurnResult do_dig_after_sp_check();
void matdelmain(int = 0, int = 0);
void matgetmain(int = 0, int = 0, int = 0);

} // namespace elona

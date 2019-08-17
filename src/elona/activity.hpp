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

void activity_perform();
void activity_sex();
void activity_blending();
void activity_eating();
void activity_eating_finish();
void activity_others();

int search_material_spot();
void spot_fishing();
void spot_material();
void spot_digging();
void spot_mining_or_wall();
TurnResult do_dig_after_sp_check();
void matdelmain(int = 0, int = 0);
void matgetmain(int = 0, int = 0, int = 0);

} // namespace elona

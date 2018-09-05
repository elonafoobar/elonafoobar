#pragma once

#include "enums.hpp"



namespace elona
{



TurnResult npc_turn();
bool turn_wrapper();
TurnResult pass_turns(bool time);
TurnResult turn_begin();
TurnResult pass_one_turn(bool label_2738_flg = true);
void update_emoicon();
TurnResult turn_end();
TurnResult pc_turn(bool advance_time = true);



} // namespace elona

#pragma once

#include "enums.hpp"



namespace elona
{



turn_result_t npc_turn();
bool turn_wrapper();
turn_result_t pass_turns(bool time);
turn_result_t turn_begin();
turn_result_t pass_one_turn(bool label_2738_flg = true);
void update_emoicon();
turn_result_t turn_end();
turn_result_t pc_turn(bool advance_time = true);



} // namespace elona

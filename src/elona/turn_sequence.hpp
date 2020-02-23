#pragma once

#include <string>

#include "enums.hpp"
#include "optional.hpp"



namespace elona
{

struct Character;



TurnResult npc_turn(Character& chara);
bool turn_wrapper();
TurnResult pass_turns(bool time);
TurnResult turn_begin();
TurnResult pass_one_turn(bool time_passing = true);
void update_emoicon();
TurnResult turn_end();
TurnResult pc_turn(bool advance_time = true);

optional<TurnResult> handle_pc_action(std::string& action);


} // namespace elona

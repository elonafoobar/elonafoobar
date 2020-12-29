#pragma once

#include <string>

#include "enums.hpp"
#include "optional.hpp"



namespace elona
{

struct Character;



TurnResult npc_turn(Character& chara);
void turn_wrapper();
TurnResult turn_begin();
TurnResult pass_one_turn(bool time_passing = true);
void update_emoicon(Character& chara);
TurnResult turn_end();
TurnResult pc_turn();

optional<TurnResult> handle_pc_action(std::string& action);

void proc_turn_end(Character& chara);

} // namespace elona

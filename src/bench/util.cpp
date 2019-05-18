#include "../elona/enums.hpp"
#include "../elona/turn_sequence.hpp"

namespace elona
{

void run_npc_turns()
{
    turn_begin();
    auto result = TurnResult::none;
    while (result != TurnResult::all_turns_finished)
    {
        result = pass_one_turn(true);

        if (result == TurnResult::npc_turn)
        {
            npc_turn();
            turn_end();
        }
    }
}

} // namespace elona

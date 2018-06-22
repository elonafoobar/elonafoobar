#include "../enums.hpp"
#include "../turn_sequence.hpp"

namespace elona
{

void run_npc_turns()
{
    turn_begin();
    auto result = turn_result_t::none;
    while (result != turn_result_t::all_turns_finished)
    {
        result = pass_one_turn(true);

        if (result == turn_result_t::npc_turn)
        {
            npc_turn();
            turn_end();
        }
    }
}

} // namespace elona

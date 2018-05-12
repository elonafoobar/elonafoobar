#pragma once

namespace elona
{

enum class talk_result_t
{
    talk_npc,
    talk_unique,
    talk_quest_giver,
    talk_house_visitor,
    talk_sleeping,
    talk_busy,
    talk_finish_escort,
    talk_game_begin,
    talk_more,
    talk_end
};

void talk_wrapper(talk_result_t);
talk_result_t talk_npc();
talk_result_t talk_unique();

}

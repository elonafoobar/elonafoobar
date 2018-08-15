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
    talk_ignored,
    talk_finish_escort,
    talk_game_begin,
    talk_more,
    talk_end
};

void talk_start();
void talk_to_npc();
void talk_end();
void talk_reset_variables();
void talk_window_init_and_show();
void talk_window_init();
void talk_window_show();
int talk_window_query();
int talk_check_trade(int = 0);
int talk_guide_quest_client();

talk_result_t talk_more();
talk_result_t talk_sleeping();
talk_result_t talk_busy();
talk_result_t talk_ignored();
talk_result_t talk_house_visitor();
talk_result_t talk_game_begin();
bool talk_give_potion_of_cure_corruption();

void talk_wrapper(talk_result_t);
talk_result_t talk_npc();
talk_result_t talk_unique();

} // namespace elona

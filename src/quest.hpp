#pragma once

namespace elona
{

enum class turn_result_t;

void quest_on_map_initialize();
void quest_place_target();
int quest_targets_remaining();
void quest_set_data(int);
void quest_refresh_list();

void quest_check();
void quest_check_all_for_failed();
void quest_update_main_quest_journal();
void quest_all_targets_killed();
void quest_failed(int);
void quest_complete();
int quest_is_return_forbidden();
void quest_exit_map();
void quest_team_victorious();
turn_result_t quest_pc_died_during_immediate_quest();

int quest_generate();
void quest_gen_scale_by_level();

} // namespace elona

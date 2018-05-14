#pragma once

namespace elona
{

enum class turn_result_t;

int quest_is_return_forbidden();
void quest_place_target();
int quest_targets_remaining();
void quest_check();
void quest_update_main_quest_journal();
void quest_set_data(int);

void quest_on_map_initialize();
void quest_gen_scale_by_level();
int quest_generate();
void quest_refresh_list();
void quest_check_all_for_failed();
void quest_exit_map();
turn_result_t quest_pc_died_during_immediate_quest();
void quest_failed(int);
void quest_team_victorious();
void quest_all_targets_killed();
void quest_complete();

} // namespace elona

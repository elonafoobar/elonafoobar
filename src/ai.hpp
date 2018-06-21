#pragma once

namespace elona
{

enum class turn_result_t;

int ai_check();
turn_result_t ai_proc_basic();
turn_result_t ai_proc_misc_map_events();
turn_result_t proc_npc_movement_event(bool = false);

} // namespace elona

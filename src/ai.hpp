#pragma once

namespace elona
{

enum class TurnResult;

int ai_check();
TurnResult ai_proc_basic();
TurnResult ai_proc_misc_map_events();
TurnResult proc_npc_movement_event(bool = false);

} // namespace elona

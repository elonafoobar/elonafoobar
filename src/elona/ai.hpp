#pragma once

namespace elona
{

enum class TurnResult;
struct Character;

TurnResult ai_proc_basic(Character& chara);
TurnResult ai_proc_misc_map_events();
TurnResult proc_npc_movement_event(Character& chara, bool retreat = false);

} // namespace elona

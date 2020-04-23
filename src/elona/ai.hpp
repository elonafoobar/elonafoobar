#pragma once



namespace elona
{

enum class TurnResult;
struct Character;



TurnResult ai_proc_basic(Character& chara, int& enemy_index);
TurnResult ai_proc_misc_map_events(Character& chara, int& enemy_index);
TurnResult proc_npc_movement_event(
    Character& chara,
    int& enemy_index,
    bool retreat = false);

} // namespace elona

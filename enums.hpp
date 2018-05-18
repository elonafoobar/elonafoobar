#pragma once



namespace elona
{

enum class curse_state_t
{
    doomed,
    cursed,
    none,
    blessed,
};


inline bool is_cursed(curse_state_t s)
{
    return s <= curse_state_t::cursed;
}


enum class identification_state_t
{
    unidentified,
    partly_identified,
    almost_identified,
    completely_identified,
};

enum class turn_result_t
{
    none,
    all_turns_finished,
    initialize_map,
    pass_one_turn,
    pass_one_turn_freeze_time,
    play_scene,
    turn_begin,
    turn_end,
    pc_turn,
    pc_turn_user_error,
    npc_turn,
    exit_map,
    pc_died,
    finish_elona,

    show_house_board,
    show_skill_list,
    show_spell_list,
    show_chat_history,
    show_message_log,
    show_quest_board,

    menu_journal,
    menu_materials,
    menu_character_sheet,
    menu_equipment,
    menu_feats,
    ctrl_inventory,
};

} // namespace elona

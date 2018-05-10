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
    pass_one_turn_false,
    play_scene,
    turn_begin,
    turn_end,
    pc_turn,
    npc_turn,
    pc_turn_false,
    exit_map,
    pc_died,
    finish_elona,

    update_journal,
    messages_menu,
    message_log_menu,

    use_house_board,

    skill_list_menu,
    spell_list_menu,

    craft_material_menu,
    show_character_sheet,
    ctrl_inventory,
    equipment_menu,
    feat_menu,
};

enum class main_menu_result_t
{
    main_title_menu,
    main_menu_new_game,
    main_menu_continue,
    main_menu_incarnate,
    character_making_select_race,
    character_making_select_sex,
    character_making_select_sex_false,
    character_making_select_class,
    character_making_select_class_false,
    character_making_role_attributes,
    character_making_role_attributes_false,
    character_making_select_feats_and_alias,
    character_making_select_feats_and_alias_false,
    character_making_final_phase,
    initialize_game,
    finish_elona,
};


} // namespace elona

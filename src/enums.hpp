#pragma once



namespace elona
{

enum stick_key
{
    left = 1 << 0,
    up = 1 << 1,
    right = 1 << 2,
    down = 1 << 3,
    space = 1 << 4,
    enter = 1 << 5,
    ctrl = 1 << 6,
    escape = 1 << 7,
    mouse_left = 1 << 8,
    mouse_right = 1 << 9,
    tab = 1 << 10,
};

enum class key_wait_delay_t {
    always,
    walk_run,
    none,
};

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

enum class damage_source_t : int
{
    trap = -1,
    overcasting = -2,
    starvation = -3,
    poisoning = -4,
    curse = -5,
    backpack_weight = -6,
    fall_from_stairs = -7,
    audience = -8,
    burn = -9,
    adventuring = -10, // used in unused casino codepath
    unseen_hand = -11,
    food_poisoning = -12,
    blood_loss = -13,
    ether_disease = -14,
    acid = -15,
    shatter = -16,
    atomic_bomb = -17,
    iron_maiden = -18,
    guillotine = -19,
    hanging = -20,
    mochi = -21,
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

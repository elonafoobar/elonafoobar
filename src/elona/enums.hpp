#pragma once

#include "../util/enumutil.hpp"



// NOTE: If anything is changed, be sure to update lua_env/lua_enums.hpp.
namespace elona
{

enum class StickKey
{
    none = 0,
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

ENUMUTIL_DEFINE_BITWISE_OPERATORS(StickKey)

enum class KeyWaitDelay
{
    always,
    walk_run,
    none,
};

// Index into c_col.
enum class ColorIndex : int
{
    // These two colors are exactly the same.
    none = 0,
    white = 1,

    green = 2,
    red = 3,
    blue = 4,
    orange = 5,
    yellow = 6,
    grey = 7,
    purple = 8,
    cyan = 9,
    light_red = 10,
    gold = 11,
    white2 = 12, // same as none/white
    light_brown = 13,
    dark_green = 14,
    light_grey = 15,
    pale_red = 16,
    light_blue = 17,
    light_purple = 18,
    light_green = 19,
    yellow_green = 20,

    // Items that are generated with a specific subset of colors.
    // Mainly used for furniture.
    random_furniture = 21,

    // Items where the color must be the same for every item of its
    // type, but the color is based on a random seed (potions, rods,
    // etc.)
    random_seeded = 22,

    // Any of the first 21 colors.
    random_any = 23,
};

enum class CurseState : int
{
    doomed = -2,
    cursed = -1,
    none = 0,
    blessed = 1,
};


inline bool is_cursed(CurseState s)
{
    return s <= CurseState::cursed;
}


enum class IdentifyState : int
{
    unidentified = 0,
    partly = 1,
    almost = 2,
    completely = 3,
};



/**
 * Quality of items or characters. They are mainly used for identification.
 * "unique" is also used instead of special.
 */
enum class Quality : int
{
    none,
    bad,
    good,
    great,
    miracle,
    godly,
    special,
};


ENUMUTIL_DEFINE_COMPARISON_OPERATORS(Quality)



enum class DamageSource : int
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

enum class BuffType
{
    buff,
    hex,
    food,
};

enum class TurnResult
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
    show_journal,

    menu_materials,
    menu_character_sheet,
    menu_equipment,
    menu_feats,
    ctrl_inventory,
};



enum class AdditionalItemInfo
{
    none,
    resistance,
    maintenance_and_ailment,

    _size,
};



ENUMUTIL_DEFINE_NEXT_PREV_FUNCTIONS_LOOPED_EXCLUSIVE_RANGE(
    AdditionalItemInfo,
    none,
    _size)

} // namespace elona

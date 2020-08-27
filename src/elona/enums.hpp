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

enum class ItemCategory : int
{
    unidentified = 0,
    melee_weapon = 10000,
    helm = 12000,
    shield = 14000,
    armor = 16000,
    boots = 18000,
    belt = 19000,
    cloak = 20000,
    gloves = 22000,
    ranged_weapon = 24000,
    ammo = 25000,
    ring = 32000,
    necklace = 34000,
    potion = 52000,
    scroll = 53000,
    spellbook = 54000,
    book = 55000,
    rod = 56000,
    food = 57000,
    tool = 59000,
    furniture = 60000,
    well = 60001,
    altar = 60002,
    bodyparts = 62000,
    junk = 64000,
    gold_piece = 68000,
    platinum_coin = 69000,
    chest = 72000,
    ore = 77000,
    tree = 80000,
    travelers_food = 91000,
    cargo = 92000,
    bug = 99999999,
};

inline bool is_equipment(ItemCategory c)
{
    return c <= static_cast<ItemCategory>(50000);
}

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



enum class Role : int
{
    none = 0,
    other = 3,
    citizen = 4,
    appraiser = 5,
    mayer = 6,
    trainer = 7,
    informer = 8,
    bartender = 9,
    arena_master = 10,
    pet_arena_master = 11,
    healer = 12,
    adventurer = 13,
    guard = 14,
    king = 15,
    shop_guard = 16,
    slave_master = 17,
    maid = 18,
    sister = 19,
    user = 20,
    returner = 21,
    horse_master = 22,
    caravan_master = 23,

    // Shopkeepers
    blacksmith = 1001,
    food_vendor = 1002,
    bakery = 1003,
    magic_vendor = 1004,
    innkeeper = 1005,
    general_vendor = 1006,
    blackmarket_vendor = 1007,
    general_store = 1008,
    trader = 1009,
    wandering_vendor = 1010,
    firearm_vendor = 1011,
    furniture_vendor = 1012,
    deed_vendor = 1013,
    fisher = 1014,
    moyer = 1015,
    miral = 1016,
    dye_vendor = 1017,
    souvenir_vendor = 1018,
    lunch_vendor = 1019,
    spell_writer = 1020,
    fence = 1021,
    street_vendor = 1022,

    // Guests
    guest_beggar = 2000,
    guest_punk = 2001,
    guest_citizen = 2002,
    guest_wandering_vendor = 2003,
    guest_trainer = 2005,
    guest_producer = 2006,
};



inline bool is_shopkeeper(Role role)
{
    return (1000 <= static_cast<int>(role) && static_cast<int>(role) < 2000) ||
        role == Role::guest_wandering_vendor;
}



inline bool is_guest(Role role)
{
    return 2000 <= static_cast<int>(role);
}



enum class OwnState : int
{
    /// Your lost items on death.
    lost = -2,

    /// Your lost items on death. When you enter the map where you died, the
    /// lost items's `OwnState` are set to this value. If you do not pick
    /// them up, they will disappear in your second visit.
    lost_disappearing = -1,

    /// Usual state. Items in character inventory or on dungeons.
    none = 0,

    /// Town's property. It cannot be obtained.
    // TODO rename?
    town = 1,

    /// It cannot be carried (e.g., wandering vendor's trunk)
    // TODO rename?
    shop = 2,

    /// Built shelter.
    shelter = 3,

    /// Crops placed in Harvest quests.
    crop = 4,

    /// Town's property, and not available for use.
    // TODO rename?
    town_special = 5,

    // Harvested crops. Defining it can fix one known bug in vanilla, but for
    // now, I don't.
    // crop_harvested = 6,
};


ENUMUTIL_DEFINE_COMPARISON_OPERATORS(OwnState)

} // namespace elona

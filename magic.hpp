#pragma once
#include "calc.hpp"
#include "enums.hpp"

namespace elona
{

enum class efsource_t : int
{
    none = 0,
    rod = 1,
    scroll = 2,
    magic = 3,
    potion = 4,
    trap = 5,
};

enum class sdataref1_t : int
{
    none = 0,
    bolt = 1,
    arrow = 2,
    aoe = 3,
    heal = 4,
    special = 6,
    summon = 7,
    teleport = 5,
    breath = 8,
    melee = 10,
};

enum class summon_t : int
{
    wild = 425,
    fire = 642,
    pawn = 641,
    cat = 639,
    yeek = 640,
    other = 643,
};

enum class heal_t : int
{
    light = 400,
    critical = 401,
    cure_of_eris = 402,
    cure_of_jure = 403,
    healing_touch = 405
};

enum class teleport_t : int
{
    self = 408,
    other = 409,
    self_short = 410,
    toward = 619,
    drawn = 620,
    dimensional_move = 627,
    thief = 635,
};

enum class mutation_t : int
{
    insane_glance = 632,
    mutation = 454,
    cursed_cure_mutation = 1121,
    evolution = 1144,
};

enum class ally_t : int
{
    ally = 1122,
    younger_sister = 1123,
    young_lady = 1137,
    younger_cat_sister = 1138,
};


enum ground_effect_t : int
{
    web = 436,
    fog = 437,
    acid = 455,
    fire = 456,
    ether = 634,
};

enum potion_consume_t
{
    drunk,
    thrown,
    spilt
};

struct magic_data // TODO name members better
{
    skill_damage damage;
    int efid;
    int efp;
    int cc;
    int tc;
    int ci;
    int tlocx;
    int tlocy;
    efsource_t efsource;
    curse_state_t efstatus;
    optional<potion_consume_t> potion_consume_type; // only used in magic_love_potion()

    magic_data(int efid, int cc) : efid(efid), cc(cc)
    {
        damage = {};
        efp = 0;
        tc = 0;
        ci = 0;
        tlocx = 0;
        tlocy = 0;
        efsource = efsource_t::none;
        efstatus = curse_state_t::none;
        potion_consume_type = none;
    }
    magic_data(int efid, int cc, int tc) : efid(efid), cc(cc), tc(tc)
    {
        damage = {};
        efp = 0;
        ci = 0;
        tlocx = 0;
        tlocy = 0;
        efsource = efsource_t::none;
        efstatus = curse_state_t::none;
        potion_consume_type = none;
    }
    magic_data(int efid, int cc, int tc, int efp) : efid(efid), cc(cc), tc(tc), efp(efp)
    {
        damage = {};
        ci = 0;
        tlocx = 0;
        tlocy = 0;
        efsource = efsource_t::none;
        efstatus = curse_state_t::none;
        potion_consume_type = none;
    }
};

struct magic_result
{
    bool turn_passed;
    bool succeeded;
    bool noeffect;
    bool obvious;        // did the magic autoidentify the type of item it came from?
    int selected_target; // actual target the magic selected
};

magic_result magic(int efid, int cc, int tc);
magic_result magic(int efid, int cc, int tc, int efp);
magic_result magic(magic_data m);

void handle_general_magic(const magic_data&, magic_result&);
void power_up_if_blessed(magic_data&);
void power_up_if_cursed(magic_data&);
void magic_add_buff(const magic_data&, magic_result&);
void magic_apply_rapidmagic(magic_data&);

void magic_melee(const magic_data&, magic_result&);
void magic_bolt(const magic_data&, magic_result&);
void magic_aoe(const magic_data&, magic_result&);
void magic_arrow(const magic_data&, magic_result&);
void magic_summon(const magic_data&, magic_result&, summon_t type);
void magic_teleport(const magic_data&, magic_result&, teleport_t type);
void magic_breath(const magic_data&, magic_result&);
void magic_insanity(const magic_data&, magic_result&);
void magic_treasure_map(const magic_data&, magic_result&);
void magic_love_potion(const magic_data&, magic_result&);
void magic_pregnancy(const magic_data&, magic_result&);
void magic_examine_self(const magic_data&, magic_result&);
void magic_milk(const magic_data&, magic_result&);
void magic_alcohol(const magic_data&, magic_result&);
void magic_acid(const magic_data&, magic_result&);
void magic_water(const magic_data&, magic_result&);
void magic_potion_stamina(const magic_data&, magic_result&);
void magic_potion_greater_stamina(const magic_data&, magic_result&);
void magic_salt(const magic_data&, magic_result&);
void magic_dirty_water(const magic_data&, magic_result&);
void magic_steal(const magic_data&, magic_result&);
void magic_mount_dismount(const magic_data&, magic_result&);
void magic_perform(const magic_data&, magic_result&);
void magic_cook(const magic_data&, magic_result&);
void magic_fish(const magic_data&, magic_result&);
void magic_remove_hex(const magic_data&, magic_result&, bool is_vanquish);
void magic_aura(const magic_data&, magic_result&);
void magic_create_material(const magic_data&, magic_result&);
void magic_heal(const magic_data&, magic_result&, heal_t type);
void magic_do_heal(const magic_data&);
void magic_special_attack(const magic_data&, magic_result&);
void magic_suck_blood(const magic_data&, magic_result&);
void magic_touch(const magic_data&, magic_result&);
void magic_disassembly(const magic_data&, magic_result&);
void magic_touch_of_fear(const magic_data&, magic_result&);
void magic_touch_of_sleep(const magic_data&, magic_result&);
void magic_hunger(const magic_data&, magic_result&);
void magic_weaken(const magic_data&, magic_result&);
void magic_flying(const magic_data&, magic_result&);
void magic_mutate(const magic_data&, magic_result&, mutation_t type);
void magic_do_mutation(const magic_data&, magic_result&, mutation_t type);
void magic_cure_mutation(const magic_data&, magic_result&);
void magic_identify(const magic_data&, magic_result&);
void magic_resurrection(const magic_data&, magic_result&);
void magic_vanquish_curse(const magic_data&, magic_result&);
void magic_oracle(const magic_data&, magic_result&);
void magic_gain_spell(const magic_data&, magic_result&);
void magic_descent(const magic_data&, magic_result&);
void magic_gain_attribute(const magic_data&, magic_result&);
void magic_faith(const magic_data&, magic_result&);
void magic_growth(const magic_data&, magic_result&);
void magic_failed_altar_takeover(const magic_data&, magic_result&);
void magic_hermes_blood(const magic_data&, magic_result&);
void magic_gain_potential(const magic_data&, magic_result&);
void magic_vanquish(const magic_data&, magic_result&);
void magic_mapping(const magic_data&, magic_result&, bool is_sense_object);
void magic_vorpal(const magic_data&, magic_result&);
void magic_restore(const magic_data&, magic_result&, bool is_restore_body);
void magic_wish(const magic_data&, magic_result&);
void magic_escape(const magic_data&, magic_result&);
void magic_return(const magic_data&, magic_result&);
void magic_restore_mana(const magic_data&, magic_result&);
void magic_absorb_mana(const magic_data&, magic_result&);
void magic_poison(const magic_data&, magic_result&);
void magic_dye(const magic_data&, magic_result&);
void magic_confusion(const magic_data&, magic_result&);
void magic_potion_numbness(const magic_data&, magic_result&);
void magic_juice(const magic_data&, magic_result&);
void magic_curse(const magic_data&, magic_result&, bool is_attack);
void magic_weaken_resistance(const magic_data&, magic_result&);
void magic_ally(const magic_data&, magic_result&, ally_t type);
void magic_domination(const magic_data&, magic_result&);
void magic_place_ground_effect(const magic_data&, magic_result&, ground_effect_t type);
void magic_create_artifact(const magic_data&, magic_result&);
void magic_superior_material(const magic_data&, magic_result&);
void magic_change_material(const magic_data&, magic_result&, bool flag);
void magic_deed_of_inheritance(const magic_data&, magic_result&);
void magic_enchant(const magic_data&, magic_result&, bool is_armor);
void magic_recharge(const magic_data&, magic_result&, bool is_fill_charge);
void magic_draw_charge(const magic_data&, magic_result&);
void magic_change_creature(const magic_data&, magic_result&);
void magic_alchemy(const magic_data&, magic_result&);
void magic_wall_creation(const magic_data&, magic_result&, bool create_door);
void magic_swarm(const magic_data&, magic_result&);
void magic_drop_item(const magic_data&, magic_result&);
void magic_gravity(const magic_data&, magic_result&);
void magic_ehekatl(const magic_data&, magic_result&);
void magic_meteorite(const magic_data&, magic_result&);
void magic_cheer(const magic_data&, magic_result&);
void magic_cure_corruption(const magic_data&, magic_result&);
void magic_corrupt_player(const magic_data&, magic_result&);
void magic_aggro(const magic_data&, magic_result&, bool is_insult);
void magic_insult(const magic_data&, magic_result&);
void magic_gaze(const magic_data&, magic_result&);
void magic_molotov(const magic_data&, magic_result&);
void magic_loot(const magic_data&, magic_result&);
void magic_fall_down(const magic_data&, magic_result&);
void magic_four_dimensional_pocket(const magic_data&, magic_result&);

int efstatusfix(curse_state_t, int = 0, int = 0, int = 0, int = 0);
std::string elename(const magic_data&);
}

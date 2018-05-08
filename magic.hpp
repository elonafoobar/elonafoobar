#pragma once

enum class efsource_t : int
{
    none = 0,
    rod = 1,
    scroll = 2,
    magic = 3,
    potion = 4,
    trap = 5,
}

struct magic_data
{
    magic_data(int efid, int cc) : efid(efid), cc(cc)
    {
        damage = { 0, 0, 0, 0, 0 };
        efp = 0;
        tc = 0;
        ci = 0;
        tlocx = 0;
        tlocy = 0;
        efsource = efsource_t::none;
        efstatus = curse_state_t::none;
    }
    magic_data(int efid, int cc, int tc) : efid(efid), cc(cc), tc(tc)
    {
        damage = { 0, 0, 0, 0, 0 };
        efp = 0;
        ci = 0;
        tlocx = 0;
        tlocy = 0;
        efsource = efsource_t::none;
        efstatus = curse_state_t::none;
    }
    magic_data(int efid, int cc, int tc, int efp) : efid(efid), cc(cc), tc(tc), efp(efp)
    {
        damage = { 0, 0, 0, 0, 0 };
        ci = 0;
        tlocx = 0;
        tlocy = 0;
        efsource = efsource_t::none;
        efstatus = curse_state_t::none;
    }
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
};
// TODO potionspill potionthrow

struct magic_result
{
    bool turn_passed;
    bool succeeded;
    bool noeffect;
    bool obvious;        // did the magic autoidentify the type of item it came from?
    int selected_target; // actual target the magic selected
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

enum class element_t : int
{
    burning = 50,
    icy = 51,
    electric = 52,
    psychic = 54,
    numb = 58,
    shivering = 57,
    poisonous = 55,
    infernal = 56,
    chaotic = 59,
    gloomy = 53,
    cut = 61,
    ether = 62,
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
}

enum class teleport_t : int
{
    self = 408,
    other = 409,
    self_short = 410,
    toward = 619,
    drawn = 620,
    dimensional_move = 627,
    thief = 635,
}

enum class mutation_t : int
{
    insane_glance = 632,
    mutation = 454,
    cursed_cure_mutation = 1121,
    evolution = 1144, // TODO not sure
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

magic_result magic(int efid, int cc);
magic_result magic(int efid, int cc, int tc);
magic_result magic(int efid, int cc, int tc, int efp);
magic_result magic(magic_data m);

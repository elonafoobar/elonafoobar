#pragma once

#include "enums.hpp"
#include "optional.hpp"


namespace elona
{


enum class animation_type
{
    bolt = 0,
    magic_arrow = 1,
    ball = 2,
    breath = 3,
    heal = 5,
    debuff = 6,
    offer = 7,
    fail_to_cast = 8,
    swarm = 9,
    healing_rain = 11,
    melee_attack = 12,
    break_ = 14,
    throw_ = 15,
    atomic_bomb = 17,
    distant_attack = 18,
    miracle = 19,
    geen_engeneering = 20,
    ragnarok = 21,
    meteor = 22,

    // TODO(ranged weapon)
    // 108, 109, 110, 111
};


// efid is only needed for animation type 0 (bolt)
void play_animation(int, element_t = element_t::none, optional<int> efid = none);


extern int FIXME_dig_animation_x;
extern int FIXME_dig_animation_y;


} // namespace elona

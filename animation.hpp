#pragma once



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


void play_animation(int);


inline int FIXME_dig_animation_x;
inline int FIXME_dig_animation_y;


} // namespace elona

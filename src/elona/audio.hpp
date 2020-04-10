#pragma once

#include "data/id.hpp"
#include "optional.hpp"



namespace elona
{

struct Position;



/* Sound */

bool audio_init_sound();

void snd(
    data::InstanceId sound_id,
    bool loop = false,
    bool allow_duplicate = true);

void snd_at(
    data::InstanceId sound_id,
    const Position& p,
    bool loop = false,
    bool allow_duplicate = true);

optional<data::InstanceId> sound_id_for_element(int element_id);
void sound_kill(const Position& position);
void sound_pick_up();
void sound_footstep(int foot);
void sound_footstep2(int foot);



/* Music */

bool audio_init_music();

void sound_play_environmental();
void stop_music();

void play_music(bool loop = true);
void play_music(data::InstanceId music_id, bool loop = true);

} // namespace elona

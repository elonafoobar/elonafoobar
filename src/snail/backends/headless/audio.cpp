#include "../../audio.hpp"



namespace elona::snail::audio
{

namespace sound
{

bool init()
{
    return true;
}



void load(int, const fs::path&)
{
}



void play(int, int)
{
}



void stop(int)
{
}



int get_volume(int)
{
    return 0;
}



void set_volume(int, int)
{
}



void set_position(int, short, unsigned char)
{
}



bool is_playing(int)
{
    return false;
}

} // namespace sound



namespace music
{

bool init()
{
    return true;
}



void load(const fs::path&)
{
}



void play(int)
{
}



void stop()
{
}



int get_volume()
{
    return 0;
}



void set_volume(int)
{
}

} // namespace music

} // namespace elona::snail::audio

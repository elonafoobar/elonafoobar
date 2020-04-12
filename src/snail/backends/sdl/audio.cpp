#include "../../audio.hpp"

#include <vector>

#include "../../application.hpp"
#include "../../detail/sdl.hpp"



namespace elona::snail::audio
{

namespace
{

// Channels:
// 0-6: reserved for SEs used very frequently
// 7: temporary(default)
// 8-12: temporary
// 13-16: reserved for weather effect

constexpr int max_channels = 17;


std::vector<::Mix_Chunk*> chunks;

::Mix_Music* played_music = nullptr;

} // namespace



namespace sound
{

bool init()
{
    ::Mix_AllocateChannels(max_channels);
    chunks.resize(max_channels);
    Application::instance().register_finalizer([&]() {
        for (const auto& chunk : chunks)
        {
            if (chunk)
            {
                ::Mix_FreeChunk(chunk);
            }
        }
    });
    return true;
}



void load(int channel, const fs::path& path)
{
    if (auto chunk = chunks[channel])
    {
        ::Mix_FreeChunk(chunk);
    }

    auto chunk = snail::detail::enforce_mixer(
        ::Mix_LoadWAV(filepathutil::to_utf8_path(path).c_str()));
    chunks[channel] = chunk;
}



void play(int channel, int loops)
{
    if (loops == 0)
    {
        return;
    }
    else if (loops == loop_forever)
    {
        ::Mix_PlayChannel(channel, chunks[channel], loops);
    }
    else
    {
        ::Mix_PlayChannel(channel, chunks[channel], loops - 1);
    }
}



void stop(int channel)
{
    ::Mix_HaltChannel(channel);
}



int get_volume(int channel)
{
    if (const auto chunk = chunks[channel])
    {
        return ::Mix_VolumeChunk(chunk, -1);
    }
    else
    {
        return 0;
    }
}



void set_volume(int channel, int volume)
{
    if (const auto chunk = chunks[channel])
    {
        ::Mix_VolumeChunk(chunk, volume);
    }
}



void set_position(int channel, short angle, unsigned char distance)
{
    ::Mix_SetPosition(channel, angle, distance);
}



bool is_playing(int channel)
{
    return ::Mix_Playing(channel);
}

} // namespace sound



namespace music
{

bool init()
{
    Application::instance().register_finalizer([&]() {
        if (played_music)
        {
            ::Mix_FreeMusic(played_music);
        }
    });
    return true;
}



void load(const fs::path& path)
{
    if (played_music)
    {
        ::Mix_FreeMusic(played_music);
    }

    played_music = snail::detail::enforce_mixer(
        ::Mix_LoadMUS(filepathutil::to_utf8_path(path).c_str()));
}



void play(int loops)
{
    detail::enforce_mixer(::Mix_PlayMusic(played_music, loops));
}



void stop()
{
    ::Mix_HaltMusic();
    if (played_music)
    {
        ::Mix_FreeMusic(played_music);
        played_music = nullptr;
    }
}



int get_volume()
{
    return ::Mix_VolumeMusic(-1);
}



void set_volume(int volume)
{
    ::Mix_VolumeMusic(volume);
}

} // namespace music

} // namespace elona::snail::audio

#include "../detail/sdl.hpp"
#include "../application.hpp"

#include <vector>

namespace
{

constexpr int max_volume = MIX_MAX_VOLUME;


// Channels:
// 0-6: reserved for SEs used very frequently
// 7: temporary(default)
// 8-12: temporary
// 13-16: reserved for weather effect

constexpr int max_channels = 17;
constexpr int temporary_channels_head = 7;
constexpr int temporary_channels_size = 6;


std::vector<Mix_Chunk*> chunks;

Mix_Music* played_music = nullptr;
} // namespace


namespace elona
{
namespace snail
{
namespace audio
{


int DSINIT()
{
    Mix_AllocateChannels(max_channels);
    chunks.resize(max_channels);
    application::instance().register_finalizer([&]() {
        for (const auto& chunk : chunks)
        {
            if (chunk)
                ::Mix_FreeChunk(chunk);
        }
    });
    return 1;
}



void DSLOADFNAME(const std::string& filepath, int channel)
{
    if (auto chunk = chunks[channel])
        Mix_FreeChunk(chunk);

    auto chunk = snail::detail::enforce_mixer(Mix_LoadWAV(filepath.c_str()));
    chunks[channel] = chunk;
}



void DSPLAY(int channel, bool loop)
{
    Mix_PlayChannel(channel, chunks[channel], loop ? -1 : 0);
}



void DSSTOP(int channel)
{
    Mix_HaltChannel(channel);
}



void DSSETVOLUME(int channel, int volume)
{
    if (const auto chunk = chunks[channel])
    {
        Mix_VolumeChunk(chunk, volume);
    }
}



bool CHECKPLAY(int channel)
{
    return Mix_Playing(channel);
}



int DMINIT()
{
    application::instance().register_finalizer([&]() {
        if (played_music)
            ::Mix_FreeMusic(played_music);
    });
    return 1;
}



void DMLOADFNAME(const std::string& filepath, int)
{
    if (played_music)
        ::Mix_FreeMusic(played_music);

    played_music = snail::detail::enforce_mixer(Mix_LoadMUS(filepath.c_str()));
}



void DMPLAY(int loop, int)
{
    detail::enforce_mixer(Mix_PlayMusic(played_music, loop ? -1 : 1));
}



void DMSTOP()
{
    ::Mix_HaltMusic();
    if (played_music)
    {
        ::Mix_FreeMusic(played_music);
        played_music = nullptr;
    }
}

} // namespace audio
} // namespace snail
} // namespace elona

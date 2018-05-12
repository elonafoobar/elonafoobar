#include "audio.hpp"
#include <unordered_map>
#include "config.hpp"
#include "elona.hpp"
#include "snail/application.hpp"
#include "variables.hpp"


namespace
{

constexpr int max_volume = MIX_MAX_VOLUME;


std::vector<fs::path> soundfile;
std::vector<int> soundlist;

std::vector<Mix_Chunk*> chunks;

int envwprev{};
int musicprev{};

Mix_Music* played_music = nullptr;
} // namespace


namespace elona
{


int DSINIT()
{
    Mix_AllocateChannels(17);
    chunks.resize(17);
    snail::application::instance().register_finalizer([&]() {
        for (const auto& chunk : chunks)
        {
            if (chunk)
                ::Mix_FreeChunk(chunk);
        }
    });
    return 1;
}



void DSLOADFNAME(const fs::path& filepath, int channel)
{
    if (auto chunk = chunks[channel])
        Mix_FreeChunk(chunk);

    auto chunk = snail::detail::enforce_mixer(
        Mix_LoadWAV(filesystem::to_utf8_path(filepath).c_str()));
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
    snail::application::instance().register_finalizer([&]() {
        if (played_music)
            ::Mix_FreeMusic(played_music);
    });
    return 1;
}



void DMLOADFNAME(const fs::path& filepath, int)
{
    if (played_music)
        ::Mix_FreeMusic(played_music);

    played_music = snail::detail::enforce_mixer(
        Mix_LoadMUS(filesystem::to_utf8_path(filepath).c_str()));
}



void DMPLAY(int loop, int)
{
    snail::detail::enforce_mixer(Mix_PlayMusic(played_music, loop ? -1 : 1));
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



void sndload(const fs::path& filepath, int prm_293)
{
    if (prm_293 < 7)
    {
        DSLOADFNAME(filepath, prm_293);
    }
    soundfile[prm_293] = filepath;
}



void initialize_sound_file()
{
    soundfile.resize(122);
    soundlist.resize(6);

    const std::pair<const char*, int> se_list[] = {
        {u8"exitmap1.wav", 49},   {u8"book1.wav", 59},
        {u8"write1.wav", 44},     {u8"pop1.wav", 1},
        {u8"kill1.wav", 8},       {u8"kill2.wav", 9},
        {u8"trap1.wav", 70},      {u8"more1.wav", 10},
        {u8"getgold1.wav", 11},   {u8"paygold1.wav", 12},
        {u8"equip1.wav", 13},     {u8"get1.wav", 14},
        {u8"get2.wav", 15},       {u8"drop1.wav", 16},
        {u8"drink1.wav", 17},     {u8"eat1.wav", 18},
        {u8"spend1.wav", 19},     {u8"ding1.wav", 60},
        {u8"ding3.wav", 61},      {u8"dead1.wav", 50},
        {u8"ok1.wav", 20},        {u8"dig1.wav", 52},
        {u8"bash1.wav", 73},      {u8"complete1.wav", 51},
        {u8"alert1.wav", 21},     {u8"locked1.wav", 22},
        {u8"chest1.wav", 23},     {u8"ding2.wav", 24},
        {u8"cook1.wav", 25},      {u8"pop2.wav", 26},
        {u8"fail1.wav", 27},      {u8"build1.wav", 58},
        {u8"bow1.wav", 29},       {u8"atk1.wav", 2},
        {u8"atk2.wav", 3},        {u8"gun1.wav", 30},
        {u8"throw1.wav", 31},     {u8"Heart1.wav", 32},
        {u8"heal1.wav", 33},      {u8"teleport1.wav", 72},
        {u8"ball1.wav", 34},      {u8"breath1.wav", 35},
        {u8"bolt1.wav", 37},      {u8"arrow1.wav", 36},
        {u8"curse1.wav", 38},     {u8"pop3.wav", 39},
        {u8"chime.wav", 53},      {u8"laser1.wav", 42},
        {u8"web.wav", 68},        {u8"cheer.wav", 69},
        {u8"door1.wav", 48},      {u8"crush1.wav", 45},
        {u8"crush2.wav", 47},     {u8"fire1.wav", 6},
        {u8"snow.wav", 86},       {u8"fish_cast.wav", 87},
        {u8"fish_get.wav", 88},   {u8"fish_fight.wav", 89},
        {u8"ammo.wav", 90},       {u8"throw2.wav", 91},
        {u8"foot1a.wav", 81},     {u8"foot2a.wav", 83},
        {u8"foot1b.wav", 82},     {u8"foot2b.wav", 84},
        {u8"foot2c.wav", 85},     {u8"click1.wav", 40},
        {u8"get3.wav", 41},       {u8"card1.wav", 71},
        {u8"water.wav", 57},      {u8"water2.wav", 46},
        {u8"dig2.wav", 54},       {u8"bush1.wav", 55},
        {u8"gasha.wav", 56},      {u8"cursor1.wav", 5},
        {u8"pop4.wav", 62},       {u8"punish1.wav", 63},
        {u8"pray1.wav", 64},      {u8"offer1.wav", 65},
        {u8"fizzle.wav", 66},     {u8"door2.wav", 67},
        {u8"foot.wav", 43},       {u8"miss.wav", 4},
        {u8"night.wav", 74},      {u8"bg_rain.wav", 75},
        {u8"bg_thunder.wav", 76}, {u8"bg_wind.wav", 77},
        {u8"bg_sea.wav", 78},     {u8"bg_town.wav", 79},
        {u8"bg_fire.wav", 80},    {u8"scroll.wav", 92},
        {u8"log.wav", 93},        {u8"chara.wav", 94},
        {u8"wear.wav", 95},       {u8"feat.wav", 96},
        {u8"port.wav", 97},       {u8"unpop1.wav", 98},
        {u8"chat.wav", 99},       {u8"inv.wav", 100},
        {u8"skill.wav", 101},     {u8"spell.wav", 102},
        {u8"dice.wav", 103},      {u8"vomit.wav", 104},
        {u8"atksword.wav", 105},  {u8"atk_ice.wav", 106},
        {u8"atk_elec.wav", 107},  {u8"atk_fire.wav", 108},
        {u8"atk_hell.wav", 109},  {u8"atk_poison.wav", 110},
        {u8"atk_nerve.wav", 111}, {u8"atk_sound.wav", 112},
        {u8"atk_mind.wav", 113},  {u8"atk_chaos.wav", 114},
        {u8"atk_dark.wav", 115},  {u8"curse2.wav", 116},
        {u8"curse3.wav", 117},    {u8"enc.wav", 118},
        {u8"enc2.wav", 119},      {u8"pray2.wav", 120},
        {u8"offer2.wav", 121},
    };

    for (const auto& se : se_list)
    {
        sndload(filesystem::dir::sound() / se.first, se.second);
    }
}



void snd(int sound_id, bool loop, bool allow_duplicate)
{
    if (!config::instance().sound)
        return;

    int channel = sound_id;
    if (channel > 7)
    {
        if (loop)
        {
            switch (sound_id)
            {
            case 78: channel = 14; break;
            case 79: channel = 15; break;
            case 80: channel = 16; break;
            default: channel = 13; break;
            }
        }
        else
        {
            channel = 7;
            bool found{};
            if (!allow_duplicate)
            {
                for (int i = 7; i < 13; ++i)
                {
                    if (CHECKPLAY(i) && soundlist[i - 7] == sound_id)
                    {
                        channel = i;
                        found = true;
                        break;
                    }
                }
            }
            if (!found)
            {
                for (int i = 7; i < 13; ++i)
                {
                    if (!CHECKPLAY(i))
                    {
                        channel = i;
                        soundlist[i - 7] = sound_id;
                    }
                }
            }
        }
        DSLOADFNAME(soundfile[sound_id], channel);
    }
    DSPLAY(channel, loop);
}



void play_music(int music_id)
{
    int env{};

    if (gdata_weather == 3)
    {
        env = 75;
    }
    if (gdata_weather == 4)
    {
        env = 76;
    }
    if (gdata_weather == 1)
    {
        env = 77;
    }
    if (env != envwprev)
    {
        envwprev = env;
        if (config::instance().sound)
        {
            if (env == 0)
            {
                DSSTOP(13);
            }
            else
            {
                snd(env, true);
            }
        }
    }
    if (mdata(14) == 2)
    {
        DSSETVOLUME(13, max_volume * 0.8);
    }
    else if (gdata_current_dungeon_level == 1 || gdata_current_map == 30)
    {
        DSSETVOLUME(13, max_volume * 0.2);
    }
    else
    {
        DSSETVOLUME(13, max_volume);
    }
    if (gdata_current_map == 11)
    {
        snd(78, true);
    }
    else
    {
        DSSTOP(14);
    }
    if (mdata(6) == 3)
    {
        snd(79, true);
    }
    else
    {
        DSSTOP(15);
    }
    if (mdata(20) == 1)
    {
        snd(80, true);
    }
    else
    {
        DSSTOP(16);
    }
    if (envonly == 1)
    {
        envonly = 0;
        return;
    }
    if (config::instance().music == 0)
    {
        return;
    }
    if (music_id == 0)
    {
        if (adata(0, gdata_current_map) == 4)
        {
            music_id = musicprev;
        }
        if (adata(0, gdata_current_map) == 3)
        {
            music_id = 51;
        }
        if (adata(0, gdata_current_map) == 5)
        {
            music_id = 67;
        }
        if (mdata(13) != 0)
        {
            music_id = mdata(13);
        }
        if (adata(0, gdata_current_map) >= 20)
        {
            music_id = 55 + gdata_hour % 6;
        }
        if (adata(16, gdata_current_map) == 8
            || adata(16, gdata_current_map) == 42)
        {
            if (gdata_current_dungeon_level == adata(10, gdata_current_map))
            {
                if (adata(20, gdata_current_map) != -1)
                {
                    music_id = 62;
                }
            }
        }
        if (gdata_current_map == 13)
        {
            if (gdata_executing_immediate_quest_type == 1001)
            {
                music_id = 76;
            }
            if (gdata_executing_immediate_quest_type == 1006)
            {
                music_id = 75;
            }
            if (gdata_executing_immediate_quest_type == 1009)
            {
                music_id = 77;
            }
            if (gdata_executing_immediate_quest_type == 1008)
            {
                music_id = 62;
            }
            if (gdata_executing_immediate_quest_type == 1010)
            {
                music_id = 73;
            }
        }
        if (gdata_current_map == 6)
        {
            music_id = 73;
        }
        if (gdata_current_map == 25)
        {
            music_id = 75;
        }
        if (gdata_current_map == 11)
        {
            music_id = 52;
        }
        if (gdata_current_map == 36)
        {
            music_id = 52;
        }
        if (gdata_current_map == 12)
        {
            music_id = 75;
        }
        if (gdata_current_map == 14)
        {
            music_id = 53;
        }
        if (gdata_current_map == 15)
        {
            music_id = 54;
        }
        if (gdata_current_map == 21)
        {
            music_id = 83;
        }
        if (gdata_current_map == 33)
        {
            music_id = 85;
        }
    }
    if (music_id == 0 || adata(0, gdata_current_map) == 1)
    {
        music_id = 86 + gdata_day % 3;
    }
    if (musicloop == 1)
    {
        musicloop = 0;
    }
    else
    {
        musicloop = 65535;
    }
    if (musicprev != music_id || music_id == 91)
    {
        musicprev = music_id;
        mmstop();
        if (config::instance().music == 1)
        {
            DMSTOP();
            DMLOADFNAME(filesystem::dir::sound() / u8"gm_on.mid", 0);
            DMPLAY(1, 0);
        }
        if (music_id != -1)
        {
            auto music_dir = filesystem::dir::user() / u8"music";
            if (!fs::exists(music_dir / musicfile(music_id)))
            {
                music_dir = filesystem::dir::sound();
                if (!fs::exists(music_dir / musicfile(music_id)))
                {
                    return;
                }
            }

            const auto is_mp3 =
                strutil::contains(musicfile(music_id), u8".mp3");

            if (config::instance().music == 2 || is_mp3)
            {
                mmload(music_dir / musicfile(music_id), 0, musicloop == 65535);
                mmplay(0);
            }
            else
            {
                DMLOADFNAME(music_dir / musicfile(music_id), 0);
                DMPLAY(musicloop, 0);
            }
        }
    }
    musicloop = 0;
}



} // namespace elona

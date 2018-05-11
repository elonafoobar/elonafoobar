#include "audio.hpp"
#include <unordered_map>
#include "config.hpp"
#include "elona.hpp"
#include "snail/application.hpp"
#include "variables.hpp"


namespace
{

constexpr int max_volume = MIX_MAX_VOLUME;
}


namespace elona
{


elona_vector1<int> soundlist;


namespace mixer_detail
{
std::unordered_map<int, Mix_Chunk*> chunks;
Mix_Music* music = nullptr;
} // namespace mixer_detail



int DSINIT()
{
    Mix_AllocateChannels(16);
    snail::application::instance().register_finalizer([&]() {
        for (const auto& pair : mixer_detail::chunks)
        {
            if (pair.second)
                ::Mix_FreeChunk(pair.second);
        }
    });
    return 1;
}



void DSLOADFNAME(const fs::path& filepath, int channel)
{
    if (mixer_detail::chunks.find(channel) != std::end(mixer_detail::chunks))
    {
        if (mixer_detail::chunks[channel])
            Mix_FreeChunk(mixer_detail::chunks[channel]);
    }
    auto chunk = snail::detail::enforce_mixer(
        Mix_LoadWAV(filesystem::to_utf8_path(filepath).c_str()));
    mixer_detail::chunks[channel] = chunk;
}



void DSPLAY(int channel, int loop)
{
    Mix_PlayChannel(-1, mixer_detail::chunks[channel], loop ? -1 : 0);
}



void DSSTOP(int channel)
{
    Mix_HaltChannel(channel);
}



void DSSETVOLUME(int channel, int volume)
{
    if (const auto chunk = mixer_detail::chunks[channel])
    {
        Mix_VolumeChunk(chunk, volume);
    }
}



int CHECKPLAY(int channel)
{
    return Mix_Playing(channel) ? 1 : 0;
}



int DMINIT()
{
    snail::application::instance().register_finalizer([&]() {
        if (mixer_detail::music)
            ::Mix_FreeMusic(mixer_detail::music);
    });
    return 1;
}



void DMLOADFNAME(const fs::path& filepath, int)
{
    if (mixer_detail::music)
        ::Mix_FreeMusic(mixer_detail::music);

    mixer_detail::music = snail::detail::enforce_mixer(
        Mix_LoadMUS(filesystem::to_utf8_path(filepath).c_str()));
}



void DMPLAY(int loop, int)
{
    snail::detail::enforce_mixer(
        Mix_PlayMusic(mixer_detail::music, loop ? -1 : 1));
}



void DMSTOP()
{
    ::Mix_HaltMusic();
    if (mixer_detail::music)
    {
        ::Mix_FreeMusic(mixer_detail::music);
        mixer_detail::music = nullptr;
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
    DIM2(soundlist, 6);

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



void snd(int prm_296, int prm_297, int prm_298)
{
    int sound_at_m18 = 0;
    int f_at_m18 = 0;
    if (!config::instance().sound)
        return;

    sound_at_m18 = prm_296;
    if (sound_at_m18 > 7)
    {
        if (prm_297)
        {
            sound_at_m18 = 13;
            if (prm_296 == 78)
            {
                sound_at_m18 = 14;
            }
            if (prm_296 == 79)
            {
                sound_at_m18 = 15;
            }
            if (prm_296 == 80)
            {
                sound_at_m18 = 16;
            }
        }
        else
        {
            sound_at_m18 = 7;
            f_at_m18 = 0;
            if (prm_298)
            {
                for (int cnt = 7; cnt < 13; ++cnt)
                {
                    if (CHECKPLAY(cnt))
                    {
                        if (soundlist(cnt - 7) == sound_at_m18)
                        {
                            sound_at_m18 = cnt;
                            f_at_m18 = 1;
                            break;
                        }
                    }
                }
            }
            if (f_at_m18 == 0)
            {
                for (int cnt = 7; cnt < 13; ++cnt)
                {
                    if (CHECKPLAY(cnt) == 0)
                    {
                        sound_at_m18 = cnt;
                        soundlist(cnt - 7) = sound_at_m18;
                    }
                }
            }
        }
        DSLOADFNAME(soundfile[prm_296], sound_at_m18);
    }
    DSPLAY(sound_at_m18, prm_297);
}



void play_music()
{
    int env = 0;
    int envwprev = 0;
    int musicprev = 0;
    int mp3 = 0;
    env = 0;
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
                snd(env, 1);
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
        snd(78, 1);
    }
    else
    {
        DSSTOP(14);
    }
    if (mdata(6) == 3)
    {
        snd(79, 1);
    }
    else
    {
        DSSTOP(15);
    }
    if (mdata(20) == 1)
    {
        snd(80, 1);
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
    if (music == 0)
    {
        if (adata(0, gdata_current_map) == 4)
        {
            music = musicprev;
        }
        if (adata(0, gdata_current_map) == 3)
        {
            music = 51;
        }
        if (adata(0, gdata_current_map) == 5)
        {
            music = 67;
        }
        if (mdata(13) != 0)
        {
            music = mdata(13);
        }
        if (adata(0, gdata_current_map) >= 20)
        {
            music = 55 + gdata_hour % 6;
        }
        if (adata(16, gdata_current_map) == 8
            || adata(16, gdata_current_map) == 42)
        {
            if (gdata_current_dungeon_level == adata(10, gdata_current_map))
            {
                if (adata(20, gdata_current_map) != -1)
                {
                    music = 62;
                }
            }
        }
        if (gdata_current_map == 13)
        {
            if (gdata_executing_immediate_quest_type == 1001)
            {
                music = 76;
            }
            if (gdata_executing_immediate_quest_type == 1006)
            {
                music = 75;
            }
            if (gdata_executing_immediate_quest_type == 1009)
            {
                music = 77;
            }
            if (gdata_executing_immediate_quest_type == 1008)
            {
                music = 62;
            }
            if (gdata_executing_immediate_quest_type == 1010)
            {
                music = 73;
            }
        }
        if (gdata_current_map == 6)
        {
            music = 73;
        }
        if (gdata_current_map == 25)
        {
            music = 75;
        }
        if (gdata_current_map == 11)
        {
            music = 52;
        }
        if (gdata_current_map == 36)
        {
            music = 52;
        }
        if (gdata_current_map == 12)
        {
            music = 75;
        }
        if (gdata_current_map == 14)
        {
            music = 53;
        }
        if (gdata_current_map == 15)
        {
            music = 54;
        }
        if (gdata_current_map == 21)
        {
            music = 83;
        }
        if (gdata_current_map == 33)
        {
            music = 85;
        }
    }
    if (music == 0 || adata(0, gdata_current_map) == 1)
    {
        music = 86 + gdata_day % 3;
    }
    if (musicloop == 1)
    {
        musicloop = 0;
    }
    else
    {
        musicloop = 65535;
    }
    if (musicprev != music || music == 91)
    {
        musicprev = music;
        mmstop();
        if (config::instance().music == 1)
        {
            DMSTOP();
            DMLOADFNAME(filesystem::dir::sound() / u8"gm_on.mid", 0);
            DMPLAY(1, 0);
        }
        fs::path music_dir;
        if (music != -1)
        {
            music_dir = filesystem::dir::user() / u8"music";
            if (!fs::exists(music_dir / musicfile(music)))
            {
                music_dir = filesystem::dir::sound();
                if (!fs::exists(music_dir / musicfile(music)))
                {
                    return;
                }
            }
            if (strutil::contains(musicfile(music), u8".mp3"))
            {
                mp3 = 1;
            }
            else
            {
                mp3 = 0;
            }
        }
        if (music != -1)
        {
            if (config::instance().music == 2 || mp3 == 1)
            {
                mmload(music_dir / musicfile(music), 0, musicloop == 65535);
                mmplay(0);
            }
            else
            {
                DMLOADFNAME(music_dir / musicfile(music), 0);
                DMPLAY(musicloop, 0);
            }
        }
    }
    music = 0;
    musicloop = 0;
    return;
}



} // namespace elona

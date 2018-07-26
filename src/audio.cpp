#include "audio.hpp"
#include <cmath>
#include <unordered_map>
#include "config.hpp"
#include "character.hpp"
#include "elona.hpp"
#include "snail/application.hpp"
#include "snail/audio.hpp"
#include "variables.hpp"
#include <boost/math/special_functions/gamma.hpp>


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

std::vector<int> soundlist;

int envwprev{};
int musicprev{};

} // namespace


namespace elona
{


int DSINIT()
{
    return snail::audio::DSINIT();
}



void DSLOADFNAME(const fs::path& filepath, int channel)
{
    snail::audio::DSLOADFNAME(filesystem::to_utf8_path(filepath), channel);
}



void DSPLAY(int channel, bool loop)
{
    snail::audio::DSPLAY(channel, loop);
}



void DSSTOP(int channel)
{
    snail::audio::DSSTOP(channel);
}



void DSSETVOLUME(int channel, int volume)
{
    snail::audio::DSSETVOLUME(channel, volume);
}



bool CHECKPLAY(int channel)
{
    return snail::audio::CHECKPLAY(channel);
}



int DMINIT()
{
    return snail::audio::DMINIT();
}



void DMLOADFNAME(const fs::path& filepath, int)
{
    snail::audio::DMLOADFNAME(filesystem::to_utf8_path(filepath), 0);
}



void DMPLAY(int loop, int)
{
    snail::audio::DMPLAY(loop, 0);
}



void DMSTOP()
{
    snail::audio::DMSTOP();
}


void sound_set_position(int channel, short angle, unsigned char distance)
{
    snail::audio::set_position(channel, angle, distance);
}


void sndload(const fs::path& filepath, int prm_293)
{
    if (prm_293 < temporary_channels_head)
    {
        DSLOADFNAME(filepath, prm_293);
    }
}



void initialize_sound_file()
{
    soundlist.resize(temporary_channels_size);

    for (const auto& se : the_sound_db)
    {
        sndload(se.file, se.id);
    }
}

std::pair<short, unsigned char> sound_calculate_position(int listener_x, int listener_y, int source_x, int source_y)
{
    // Larger means it takes more distance for sounds to become quiet.
    const constexpr double distance_factor = 8.0;

    double x = static_cast<double>(source_x - listener_x);
    double y = static_cast<double>(source_y - listener_y);

    double angle_raw = std::atan2(y, x);
    if (angle_raw < 0)
    {
        angle_raw += 2 * M_PI;
    }

    angle_raw += M_PI / 2;

    short angle = static_cast<short>(angle_raw * 180.0 / M_PI) % 360;
    int dist_raw = dist(listener_x, listener_y, source_x, source_y);
    double dist_norm = boost::math::gamma_p(distance_factor, static_cast<double>(dist_raw));
    unsigned char dist = static_cast<unsigned char>(dist_norm * 255.0);

    return {angle, dist};
}

std::pair<short, unsigned char> sound_calculate_position(const position_t& p)
{
    if (cdata[0].state == 0)
    {
        return {0, 0};
    }

    return sound_calculate_position(cdata[0].position.x, cdata[0].position.y, p.x, p.y);
}

void snd_inner(const sound_data& sound, short angle, unsigned char dist, bool loop, bool allow_duplicate)
{
    if (!config::instance().sound)
        return;

    int channel = sound.id;
    if (channel > temporary_channels_head)
    {
        if (loop)
        {
            switch (sound.id)
            {
            case 78: channel = 14; break;
            case 79: channel = 15; break;
            case 80: channel = 16; break;
            default: channel = 13; break;
            }
        }
        else
        {
            channel = temporary_channels_head;
            bool found{};
            if (!allow_duplicate)
            {
                for (int i = temporary_channels_head;
                     i < temporary_channels_head + temporary_channels_size;
                     ++i)
                {
                    if (CHECKPLAY(i)
                        && soundlist[i - temporary_channels_head] == sound.id)
                    {
                        channel = i;
                        found = true;
                        break;
                    }
                }
            }
            if (!found)
            {
                for (int i = temporary_channels_head;
                     i < temporary_channels_head + temporary_channels_size;
                     ++i)
                {
                    if (!CHECKPLAY(i))
                    {
                        channel = i;
                        soundlist[i - temporary_channels_head] = sound.id;
                    }
                }
            }
        }
        DSLOADFNAME(sound.file, channel);
    }

    if (config::instance().get<bool>("core.config.screen.stereo_sound") && dist != 0)
    {
        sound_set_position(channel, angle, dist);
    }
    else
    {
        sound_set_position(channel, 0, 0);
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
    if (mdata_map_indoors_flag == 2)
    {
        DSSETVOLUME(13, max_volume * 0.8);
    }
    else if (gdata_current_dungeon_level == 1 || gdata_current_map == mdata_t::map_id_t::shelter_)
    {
        DSSETVOLUME(13, max_volume * 0.2);
    }
    else
    {
        DSSETVOLUME(13, max_volume);
    }
    if (gdata_current_map == mdata_t::map_id_t::port_kapul)
    {
        snd(78, true);
    }
    else
    {
        DSSTOP(14);
    }
    if (mdata_map_type == mdata_t::map_type_t::town)
    {
        snd(79, true);
    }
    else
    {
        DSSTOP(15);
    }
    if (mdata_map_play_campfire_sound == 1)
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
    if (config::instance().music == "none")
    {
        return;
    }
    if (music_id == 0)
    {
        if (adata(0, gdata_current_map) == mdata_t::map_type_t::field)
        {
            music_id = musicprev;
        }
        if (adata(0, gdata_current_map) == mdata_t::map_type_t::town)
        {
            music_id = 51;
        }
        if (adata(0, gdata_current_map) == mdata_t::map_type_t::player_owned)
        {
            music_id = 67;
        }
        if (mdata_map_bgm != 0)
        {
            music_id = mdata_map_bgm;
        }
        if (adata(0, gdata_current_map) >= mdata_t::map_type_t::dungeon)
        {
            music_id = 55 + gdata_hour % 6;
        }
        if (adata(16, gdata_current_map) == mdata_t::map_id_t::random_dungeon
            || adata(16, gdata_current_map) == mdata_t::map_id_t::the_void)
        {
            if (gdata_current_dungeon_level == adata(10, gdata_current_map))
            {
                if (adata(20, gdata_current_map) != -1)
                {
                    music_id = 62;
                }
            }
        }
        if (gdata_current_map == mdata_t::map_id_t::quest)
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
        if (gdata_current_map == mdata_t::map_id_t::arena)
        {
            music_id = 73;
        }
        if (gdata_current_map == mdata_t::map_id_t::larna)
        {
            music_id = 75;
        }
        if (gdata_current_map == mdata_t::map_id_t::port_kapul)
        {
            music_id = 52;
        }
        if (gdata_current_map == mdata_t::map_id_t::lumiest)
        {
            music_id = 52;
        }
        if (gdata_current_map == mdata_t::map_id_t::yowyn)
        {
            music_id = 75;
        }
        if (gdata_current_map == mdata_t::map_id_t::derphy)
        {
            music_id = 53;
        }
        if (gdata_current_map == mdata_t::map_id_t::palmia)
        {
            music_id = 54;
        }
        if (gdata_current_map == mdata_t::map_id_t::cyber_dome)
        {
            music_id = 83;
        }
        if (gdata_current_map == mdata_t::map_id_t::noyel)
        {
            music_id = 85;
        }
    }
    if (music_id == 0 || adata(0, gdata_current_map) == mdata_t::map_type_t::world_map)
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
        if (config::instance().music == "direct_music")
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

            if (config::instance().music == "mci" || is_mp3)
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

#include "audio.hpp"
#include <cmath>
#include <unordered_map>
#include <boost/math/special_functions/gamma.hpp>
#include "character.hpp"
#include "config.hpp"
#include "elona.hpp"
#include "snail/application.hpp"
#include "snail/audio.hpp"
#include "variables.hpp"


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
shared_id musicprev{};


void sound_set_position(int channel, short angle, unsigned char distance)
{
    snail::audio::set_position(channel, angle, distance);
}

shared_id get_default_music()
{
    optional<std::string> music_id = none;

    if (adata(0, gdata_current_map) == mdata_t::map_type_t::field)
    {
        return musicprev;
    }
    if (adata(0, gdata_current_map) == mdata_t::map_type_t::town)
    {
        music_id = "core.music:core.mcTown1"s;
    }
    if (adata(0, gdata_current_map) == mdata_t::map_type_t::player_owned)
    {
        music_id = "core.music:core.mcHome"s;
    }
    if (mdata_map_bgm != 0)
    {
        music_id = **the_music_db.get_id_from_legacy(mdata_map_bgm);
    }
    if (adata(0, gdata_current_map) >= mdata_t::map_type_t::dungeon)
    {
        static const std::vector<std::string> choices = {
            "core.music:core.mcDungeon1",
            "core.music:core.mcDungeon2",
            "core.music:core.mcDungeon3",
            "core.music:core.mcDungeon4",
            "core.music:core.mcDungeon5",
            "core.music:core.mcDungeon6"};
        music_id = choices[gdata_hour % 6];
    }
    if (adata(16, gdata_current_map) == mdata_t::map_id_t::random_dungeon
        || adata(16, gdata_current_map) == mdata_t::map_id_t::the_void)
    {
        if (gdata_current_dungeon_level == adata(10, gdata_current_map))
        {
            if (adata(20, gdata_current_map) != -1)
            {
                music_id = "core.music:core.mcBoss"s;
            }
        }
    }
    if (gdata_current_map == mdata_t::map_id_t::quest)
    {
        if (gdata_executing_immediate_quest_type == 1001)
        {
            music_id = "core.music:core.mcBattle1"s;
        }
        if (gdata_executing_immediate_quest_type == 1006)
        {
            music_id = "core.music:core.mcVillage1"s;
        }
        if (gdata_executing_immediate_quest_type == 1009)
        {
            music_id = "core.music:core.mcCasino"s;
        }
        if (gdata_executing_immediate_quest_type == 1008)
        {
            music_id = "core.music:core.mcBoss"s;
        }
        if (gdata_executing_immediate_quest_type == 1010)
        {
            music_id = "core.music:core.mcArena";
        }
    }
    if (gdata_current_map == mdata_t::map_id_t::arena)
    {
        music_id = "core.music:core.mcArena"s;
    }
    if (gdata_current_map == mdata_t::map_id_t::larna)
    {
        music_id = "core.music:core.mcVillage1"s;
    }
    if (gdata_current_map == mdata_t::map_id_t::port_kapul)
    {
        music_id = "core.music:core.mcTown2"s;
    }
    if (gdata_current_map == mdata_t::map_id_t::lumiest)
    {
        music_id = "core.music:core.mcTown2"s;
    }
    if (gdata_current_map == mdata_t::map_id_t::yowyn)
    {
        music_id = "core.music:core.mcVillage1"s;
    }
    if (gdata_current_map == mdata_t::map_id_t::derphy)
    {
        music_id = "core.music:core.mcTown3"s;
    }
    if (gdata_current_map == mdata_t::map_id_t::palmia)
    {
        music_id = "core.music:core.mcTown4"s;
    }
    if (gdata_current_map == mdata_t::map_id_t::cyber_dome)
    {
        music_id = "core.music:core.mcTown5"s;
    }
    if (gdata_current_map == mdata_t::map_id_t::noyel)
    {
        music_id = "core.music:core.mcTown6"s;
    }

    if (!music_id
        || adata(0, gdata_current_map) == mdata_t::map_type_t::world_map)
    {
        static const std::vector<std::string> choices = {
            "core.music:core.mcField1",
            "core.music:core.mcField2",
            "core.music:core.mcField3"};
        music_id = choices[gdata_day % 3];
    }

    return shared_id(*music_id);
}

void play_music_inner(const shared_id& music_id, int musicloop)
{
    if (musicprev != music_id)
    {
        musicprev = music_id;
        stop_music();
        auto music = the_music_db[music_id];
        assert(music);
        if (!fs::exists(music->file))
        {
            return;
        }

        // Since we're using SDL mixer, this should load any file
        // format that mixer was compiled to support.
        DMLOADFNAME(music->file, 0);
        DMPLAY(musicloop, 0);
    }
}

} // namespace


namespace elona
{

namespace detail
{

void snd_inner(
    const sound_data& sound,
    short angle,
    unsigned char dist,
    bool loop,
    bool allow_duplicate)
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

    if (dist != 0)
    {
        sound_set_position(channel, angle, dist);
    }
    else
    {
        // implicitly unregisters distance effect on mixer
        sound_set_position(channel, 0, 0);
    }

    DSPLAY(channel, loop);
}

} // namespace detail


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

std::pair<short, unsigned char> sound_calculate_position(
    int listener_x,
    int listener_y,
    int source_x,
    int source_y)
{
    // Larger means it takes more distance for sounds to become quiet.
    const constexpr double distance_factor = 7.0;

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
    double dist_norm =
        boost::math::gamma_p(distance_factor, static_cast<double>(dist_raw));
    unsigned char dist = static_cast<unsigned char>(dist_norm * 255.0);

    return {angle, dist};
}

std::pair<short, unsigned char> sound_calculate_position(const position_t& p)
{
    if (!config::instance().get<bool>("core.config.screen.stereo_sound"))
    {
        return {0, 0};
    }
    if (cdata.player().state() == character::state_t::empty)
    {
        return {0, 0};
    }

    return sound_calculate_position(
        cdata.player().position.x, cdata.player().position.y, p.x, p.y);
}



void stop_music()
{
    mmstop();
    if (config::instance().music == "direct_music")
    {
        DMSTOP();
        DMLOADFNAME(filesystem::dir::sound() / u8"gm_on.mid", 0);
        DMPLAY(1, 0);
    }
}


void sound_play_environmental()
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
    else if (
        gdata_current_dungeon_level == 1
        || gdata_current_map == mdata_t::map_id_t::shelter_)
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
}

void play_music(const char* music_id)
{
    shared_id id = shared_id("core.music:"s + std::string(music_id));
    play_music(id);
}

void play_music(optional<shared_id> music_id)
{
    sound_play_environmental();

    if (config::instance().music == "none")
    {
        return;
    }

    if (!music_id)
    {
        music_id = get_default_music();
    }

    if (musicloop == 1)
    {
        musicloop = 0;
    }
    else
    {
        musicloop = 65535;
    }

    play_music_inner(*music_id, musicloop);

    musicloop = 0;
}



} // namespace elona

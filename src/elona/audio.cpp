#include "audio.hpp"

#include <cmath>

#include <unordered_map>

#include <boost/math/special_functions/gamma.hpp>

#include "../snail/application.hpp"
#include "../snail/audio.hpp"
#include "area.hpp"
#include "character.hpp"
#include "config.hpp"
#include "elona.hpp"
#include "map.hpp"
#include "variables.hpp"


namespace
{

constexpr int max_volume = MIX_MAX_VOLUME;


// Channels:
// 0-6: reserved for SEs used very frequently
// 7: temporary(default)
// 8-12: temporary
// 13-16: reserved for weather effect

constexpr int temporary_channels_head = 7;
constexpr int temporary_channels_size = 6;

std::vector<int> soundlist;

optional<data::InstanceId> envwprev = none;
data::InstanceId musicprev{};


void sound_set_position(int channel, short angle, unsigned char distance)
{
    snail::audio::set_position(channel, angle, distance);
}

data::InstanceId get_default_music()
{
    optional<data::InstanceId> music_id = none;

    if (area_data[game_data.current_map].type == mdata_t::MapType::field)
    {
        return musicprev;
    }
    if (area_data[game_data.current_map].type == mdata_t::MapType::town)
    {
        music_id = "core.mcTown1";
    }
    if (area_data[game_data.current_map].type == mdata_t::MapType::player_owned)
    {
        music_id = "core.mcHome";
    }
    if (map_data.bgm != 0)
    {
        music_id = the_music_db.get_id_from_legacy(map_data.bgm);
    }
    if (mdata_t::is_nefia(area_data[game_data.current_map].type))
    {
        static const std::vector<data::InstanceId> choices{
            "core.mcDungeon1",
            "core.mcDungeon2",
            "core.mcDungeon3",
            "core.mcDungeon4",
            "core.mcDungeon5",
            "core.mcDungeon6",
        };
        music_id = choices[game_data.date.hour % 6];
    }
    if (area_data[game_data.current_map].id == mdata_t::MapId::random_dungeon ||
        area_data[game_data.current_map].id == mdata_t::MapId::the_void)
    {
        if (game_data.current_dungeon_level ==
            area_data[game_data.current_map].deepest_level)
        {
            if (area_data[game_data.current_map].has_been_conquered != -1)
            {
                music_id = "core.mcBoss";
            }
        }
    }
    if (game_data.current_map == mdata_t::MapId::quest)
    {
        if (game_data.executing_immediate_quest_type == 1001)
        {
            music_id = "core.mcBattle1";
        }
        if (game_data.executing_immediate_quest_type == 1006)
        {
            music_id = "core.mcVillage1";
        }
        if (game_data.executing_immediate_quest_type == 1009)
        {
            music_id = "core.mcCasino";
        }
        if (game_data.executing_immediate_quest_type == 1008)
        {
            music_id = "core.mcBoss";
        }
        if (game_data.executing_immediate_quest_type == 1010)
        {
            music_id = "core.mcArena";
        }
    }
    if (game_data.current_map == mdata_t::MapId::arena)
    {
        music_id = "core.mcArena";
    }
    if (game_data.current_map == mdata_t::MapId::larna)
    {
        music_id = "core.mcVillage1";
    }
    if (game_data.current_map == mdata_t::MapId::port_kapul)
    {
        music_id = "core.mcTown2";
    }
    if (game_data.current_map == mdata_t::MapId::lumiest)
    {
        music_id = "core.mcTown2";
    }
    if (game_data.current_map == mdata_t::MapId::yowyn)
    {
        music_id = "core.mcVillage1";
    }
    if (game_data.current_map == mdata_t::MapId::derphy)
    {
        music_id = "core.mcTown3";
    }
    if (game_data.current_map == mdata_t::MapId::palmia)
    {
        music_id = "core.mcTown4";
    }
    if (game_data.current_map == mdata_t::MapId::cyber_dome)
    {
        music_id = "core.mcTown5";
    }
    if (game_data.current_map == mdata_t::MapId::noyel)
    {
        music_id = "core.mcTown6";
    }

    if (!music_id ||
        area_data[game_data.current_map].type == mdata_t::MapType::world_map)
    {
        static const std::vector<data::InstanceId> choices = {
            "core.mcField1",
            "core.mcField2",
            "core.mcField3",
        };
        music_id = choices[game_data.date.day % 3];
    }

    return *music_id;
}

void play_music_inner(data::InstanceId music_id, int musicloop)
{
    if (musicprev != music_id)
    {
        auto music = the_music_db[music_id];
        if (!music)
        {
            ELONA_ERROR("audio") << "Cannot load music " << music_id.get();
            return;
        }
        if (!fs::exists(music->file))
        {
            ELONA_ERROR("audio") << "Cannot load file "
                                 << filepathutil::to_utf8_path(music->file)
                                 << " for music " << music_id.get();
            return;
        }

        musicprev = music_id;
        stop_music();

        // Since we're using SDL mixer, this should load any file
        // format that mixer was compiled to support.
        DMLOADFNAME(music->file, 0);
        DMPLAY(musicloop, 0);
    }
}


void snd_inner(
    const SoundData& sound,
    short angle,
    unsigned char dist,
    bool loop,
    bool allow_duplicate)
{
    if (!g_config.sound())
        return;

    int channel = sound.legacy_id;
    if (channel > temporary_channels_head)
    {
        if (loop)
        {
            switch (sound.legacy_id)
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
                    if (CHECKPLAY(i) &&
                        soundlist[i - temporary_channels_head] ==
                            sound.legacy_id)
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
                        soundlist[i - temporary_channels_head] =
                            sound.legacy_id;
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



void _preload_sound_if_needed(const fs::path& filepath, int id)
{
    if (id < temporary_channels_head)
    {
        DSLOADFNAME(filepath, id);
    }
}

} // namespace


namespace elona
{

int DSINIT()
{
    return snail::audio::DSINIT();
}



void DSLOADFNAME(const fs::path& filepath, int channel)
{
    snail::audio::DSLOADFNAME(filepathutil::to_utf8_path(filepath), channel);
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
    snail::audio::DMLOADFNAME(filepathutil::to_utf8_path(filepath), 0);
}



void DMPLAY(int loop, int)
{
    snail::audio::DMPLAY(loop, 0);
}



void DMSTOP()
{
    snail::audio::DMSTOP();
}



void initialize_sound_file()
{
    soundlist.resize(temporary_channels_size);

    for (const auto& se : the_sound_db.values())
    {
        _preload_sound_if_needed(se.file, se.legacy_id);
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

std::pair<short, unsigned char> sound_calculate_position(const Position& p)
{
    if (!config_get_boolean("core.screen.stereo_sound"))
    {
        return {0, 0};
    }
    if (cdata.player().state() == Character::State::empty)
    {
        return {0, 0};
    }

    return sound_calculate_position(
        cdata.player().position.x, cdata.player().position.y, p.x, p.y);
}



void stop_music()
{
    mmstop();
    DMSTOP();
    DMLOADFNAME(filesystem::dirs::sound() / u8"gm_on.mid", 0);
    DMPLAY(1, 0);
}


void sound_play_environmental()
{
    optional<data::InstanceId> env = none;

    if (game_data.weather == 3)
    {
        env = "core.bg_rain";
    }
    if (game_data.weather == 4)
    {
        env = "core.bg_thunder";
    }
    if (game_data.weather == 1)
    {
        env = "core.bg_wind";
    }
    if (env != envwprev)
    {
        envwprev = env;
        if (g_config.sound())
        {
            if (env)
            {
                snd(*env, true);
            }
            else
            {
                DSSTOP(13);
            }
        }
    }
    if (map_data.indoors_flag == 2)
    {
        DSSETVOLUME(13, max_volume * 0.8);
    }
    else if (
        game_data.current_dungeon_level == 1 ||
        game_data.current_map == mdata_t::MapId::shelter_)
    {
        DSSETVOLUME(13, max_volume * 0.2);
    }
    else
    {
        DSSETVOLUME(13, max_volume);
    }
    if (game_data.current_map == mdata_t::MapId::port_kapul)
    {
        snd("core.bg_sea", true);
    }
    else
    {
        DSSTOP(14);
    }
    if (map_data.type == mdata_t::MapType::town)
    {
        snd("core.bg_town", true);
    }
    else
    {
        DSSTOP(15);
    }
    if (map_data.play_campfire_sound == 1)
    {
        snd("core.bg_fire", true);
    }
    else
    {
        DSSTOP(16);
    }
}



optional<data::InstanceId> sound_id_for_element(int element_id)
{
    switch (element_id)
    {
    case 50: return data::InstanceId{"core.atk_fire"};
    case 51: return data::InstanceId{"core.atk_ice"};
    case 52: return data::InstanceId{"core.atk_elec"};
    case 59: return data::InstanceId{"core.atk_chaos"};
    case 53: return data::InstanceId{"core.atk_dark"};
    case 58: return data::InstanceId{"core.atk_nerve"};
    case 57: return data::InstanceId{"core.atk_sound"};
    case 54: return data::InstanceId{"core.atk_mind"};
    case 55: return data::InstanceId{"core.atk_poison"};
    case 56: return data::InstanceId{"core.atk_hell"};
    case 63: return data::InstanceId{"core.atk_poison"};
    default: return none;
    }
}



void sound_kill(const Position& position)
{
    static const std::vector<data::InstanceId> sounds{
        "core.kill1",
        "core.kill2",
    };

    snd_at(choice(sounds), position, false, false);
}



void sound_pick_up()
{
    static const std::vector<data::InstanceId> sounds{
        "core.get1",
        "core.get2",
    };

    snd(choice(sounds));
}



void sound_footstep(int foot)
{
    switch (foot % 2)
    {
    case 0: snd("core.foot1a"); break;
    case 1: snd("core.foot1b"); break;
    }
}

void sound_footstep2(int foot)
{
    switch (foot % 3)
    {
    case 0: snd("core.foot2a"); break;
    case 1: snd("core.foot2b"); break;
    case 2: snd("core.foot2c"); break;
    }
}

void snd_at(
    data::InstanceId sound_id,
    const Position& p,
    bool loop,
    bool allow_duplicate)
{
    short angle;
    unsigned char dist;
    std::tie(angle, dist) = sound_calculate_position(p);

    auto sound = the_sound_db[sound_id];

    if (!sound)
    {
        ELONA_ERROR("audio") << "Cannot load sound " << sound_id.get();
        return;
    }

    snd_inner(*sound, angle, dist, loop, allow_duplicate);
}



void snd(data::InstanceId sound_id, bool loop, bool allow_duplicate)
{
    auto sound = the_sound_db[sound_id];

    if (!sound)
    {
        ELONA_ERROR("audio") << "Cannot load sound " << sound_id.get();
        return;
    }

    snd_inner(*sound, 0, 0, loop, allow_duplicate);
}



void play_music()
{
    play_music(get_default_music());
}



void play_music(data::InstanceId music_id)
{
    sound_play_environmental();

    if (!g_config.music())
        return;

    if (musicloop == 1)
    {
        musicloop = 0;
    }
    else
    {
        musicloop = 65535;
    }

    play_music_inner(music_id, musicloop);

    musicloop = 0;
}

} // namespace elona

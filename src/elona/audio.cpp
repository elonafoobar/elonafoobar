#include "audio.hpp"

#include <cmath>

#include <boost/math/special_functions/gamma.hpp>

#include "../snail/audio.hpp"
#include "area.hpp"
#include "character.hpp"
#include "config.hpp"
#include "data/types/type_music.hpp"
#include "data/types/type_sound.hpp"
#include "log.hpp"
#include "map.hpp"
#include "variables.hpp"

namespace snl_sound = snail::audio::sound;
namespace snl_music = snail::audio::music;



namespace elona
{

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



void preload_sound_if_needed(const fs::path& filepath, int id)
{
    if (id < temporary_channels_head)
    {
        snl_sound::load(id, filepath);
    }
}



void preload_sounds()
{
    soundlist.resize(temporary_channels_size);

    for (const auto& se : the_sound_db.values())
    {
        preload_sound_if_needed(se.file, se.legacy_id);
    }
}



void set_volume(int channel, int volume)
{
    snl_sound::set_volume(channel, volume * g_config.sound_volume() / 8);
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
                    if (snl_sound::is_playing(i) &&
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
                    if (!snl_sound::is_playing(i))
                    {
                        channel = i;
                        soundlist[i - temporary_channels_head] =
                            sound.legacy_id;
                    }
                }
            }
        }
        snl_sound::load(channel, sound.file);
    }

    if (dist != 0)
    {
        snl_sound::set_position(channel, angle, dist);
    }
    else
    {
        // implicitly unregisters distance effect on mixer
        snl_sound::set_position(channel, 0, 0);
    }

    set_volume(channel, sound.volume);
    snl_sound::play(channel, loop ? snail::audio::loop_forever : 1);
}



std::pair<short, unsigned char>
calculate_position(int listener_x, int listener_y, int source_x, int source_y)
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



std::pair<short, unsigned char> calculate_position(const Position& p)
{
    if (!config_get<bool>("core.screen.stereo_sound"))
    {
        return {0, 0};
    }
    if (cdata.player().state() == Character::State::empty)
    {
        return {0, 0};
    }

    return calculate_position(
        cdata.player().position.x, cdata.player().position.y, p.x, p.y);
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



void play_music_inner(data::InstanceId music_id, bool loop)
{
    if (musicprev == music_id)
        return;

    const auto music = the_music_db[music_id];
    if (!music)
    {
        ELONA_ERROR("audio") << "Cannot load music " << music_id.get();
        return;
    }
    if (!fs::exists(music->file))
    {
        ELONA_ERROR("audio") << "Cannot load file " << music->file.to_u8string()
                             << " for music " << music_id.get();
        return;
    }

    musicprev = music_id;
    stop_music();

    // Since we're using SDL mixer, this should load any file
    // format that mixer was compiled to support.
    snl_music::load(music->file);
    snl_music::set_volume(music->volume * g_config.music_volume() / 8);
    snl_music::play(loop ? snail::audio::loop_forever : 1);
}

} // namespace



/* Sound */

bool audio_init_sound()
{
    bool ok = snl_sound::init();
    if (!ok)
    {
        return false;
    }
    preload_sounds();
    return true;
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



void snd_at(
    data::InstanceId sound_id,
    const Position& p,
    bool loop,
    bool allow_duplicate)
{
    const auto [angle, dist] = calculate_position(p);

    auto sound = the_sound_db[sound_id];

    if (!sound)
    {
        ELONA_ERROR("audio") << "Cannot load sound " << sound_id.get();
        return;
    }

    snd_inner(*sound, angle, dist, loop, allow_duplicate);
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



/* Music */

bool audio_init_music()
{
    return snl_music::init();
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
                snl_sound::stop(13);
            }
        }
    }
    if (map_data.indoors_flag == 2)
    {
        set_volume(13, max_volume * 0.8);
    }
    else if (
        game_data.current_dungeon_level == 1 ||
        game_data.current_map == mdata_t::MapId::shelter_)
    {
        set_volume(13, max_volume * 0.2);
    }
    else
    {
        set_volume(13, max_volume);
    }
    if (game_data.current_map == mdata_t::MapId::port_kapul)
    {
        snd("core.bg_sea", true);
    }
    else
    {
        snl_sound::stop(14);
    }
    if (map_data.type == mdata_t::MapType::town)
    {
        snd("core.bg_town", true);
    }
    else
    {
        snl_sound::stop(15);
    }
    if (map_data.play_campfire_sound == 1)
    {
        snd("core.bg_fire", true);
    }
    else
    {
        snl_sound::stop(16);
    }
}



void stop_music()
{
    snl_music::stop();
    snl_music::load(filesystem::dirs::sound() / u8"gm_on.mid");
    snl_music::play(1);
}



void play_music(bool loop)
{
    play_music(get_default_music(), loop);
}



void play_music(data::InstanceId music_id, bool loop)
{
    sound_play_environmental();

    if (!g_config.music())
        return;

    play_music_inner(music_id, loop);
}

} // namespace elona

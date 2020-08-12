#pragma once

#include <string>

#include "../snail/window.hpp"
#include "filesystem.hpp"
#include "shared_id.hpp"



namespace elona
{

struct PreinitConfigOptions
{
public:
    static PreinitConfigOptions from_file(const fs::path& path);

    // for testing
    static PreinitConfigOptions from_string(const std::string& str);
    static PreinitConfigOptions from_stream(
        std::istream& in,
        const std::string& filepath);


    snail::Window::FullscreenMode fullscreen() const noexcept
    {
        return _fullscreen;
    }


    const std::string& display_mode() const noexcept
    {
        return _display_mode;
    }



private:
    snail::Window::FullscreenMode _fullscreen;
    std::string _display_mode;


    PreinitConfigOptions(
        snail::Window::FullscreenMode fullscreen,
        const std::string& display_mode)
        : _fullscreen(fullscreen)
        , _display_mode(display_mode)
    {
    }
};



void config_load_all_schema();

/// for testing
void config_load_schema(const std::string& config_schema, SharedId mod_id);

void config_load_options();

/// for testing
void config_load_options(const std::string& config);

/**
 * Save the current configuration.
 */
void config_save();

/**
 * Clear all configuration.
 * Testing only.
 */
void config_clear();

// get
template <typename T>
T config_get(const std::string& key);

// set
template <typename T>
void config_set(const std::string& key, const T& value);



struct Config
{
#define ELONA_DEFINE_OPTION(type, name) \
private: \
    type _##name{}; \
\
public: \
    const type& name() const noexcept \
    { \
        return _##name; \
    } \
    void set_##name(const type& value) \
    { \
        _##name = value; \
    }

public:
    // If your are vimmer, ex command ":sort /\w\+)/ r" can sort the list well.
    ELONA_DEFINE_OPTION(int, alert_wait)
    ELONA_DEFINE_OPTION(bool, allow_enhanced_skill)
    ELONA_DEFINE_OPTION(bool, always_center)
    ELONA_DEFINE_OPTION(int, animation_wait)
    ELONA_DEFINE_OPTION(bool, attack_animation)
    ELONA_DEFINE_OPTION(bool, attack_neutral_npcs)
    ELONA_DEFINE_OPTION(int, attack_wait)
    ELONA_DEFINE_OPTION(std::string, auto_turn_speed)
    ELONA_DEFINE_OPTION(bool, autodisable_numlock)
    ELONA_DEFINE_OPTION(bool, autopick)
    ELONA_DEFINE_OPTION(bool, autosave)
    ELONA_DEFINE_OPTION(bool, auto_target)
    ELONA_DEFINE_OPTION(bool, damage_popup)
    ELONA_DEFINE_OPTION(bool, digital_clock)
    ELONA_DEFINE_OPTION(std::string, display_mode)
    ELONA_DEFINE_OPTION(int, enhanced_skill_lowerbound)
    ELONA_DEFINE_OPTION(int, enhanced_skill_upperbound)
    ELONA_DEFINE_OPTION(bool, extra_class)
    ELONA_DEFINE_OPTION(bool, extra_help)
    ELONA_DEFINE_OPTION(bool, extra_race)
    ELONA_DEFINE_OPTION(std::string, font_filename)
    ELONA_DEFINE_OPTION(snail::Window::FullscreenMode, fullscreen)
    ELONA_DEFINE_OPTION(int, general_wait)
    ELONA_DEFINE_OPTION(bool, heartbeat)
    ELONA_DEFINE_OPTION(bool, hide_autoidentify)
    ELONA_DEFINE_OPTION(bool, hide_navigation)
    ELONA_DEFINE_OPTION(bool, hide_shop_updates)
    ELONA_DEFINE_OPTION(bool, high_quality_shadow)
    ELONA_DEFINE_OPTION(std::string, hp_bar_position)
    ELONA_DEFINE_OPTION(int, initial_key_repeat_wait)
    ELONA_DEFINE_OPTION(bool, joypad)
    ELONA_DEFINE_OPTION(int, key_repeat_wait)
    ELONA_DEFINE_OPTION(int, key_wait)
    ELONA_DEFINE_OPTION(std::string, language)
    ELONA_DEFINE_OPTION(bool, leash_icon)
    ELONA_DEFINE_OPTION(int, max_damage_popup)
    ELONA_DEFINE_OPTION(bool, message_add_timestamps)
    ELONA_DEFINE_OPTION(int, message_transparency)
    ELONA_DEFINE_OPTION(bool, music)
    ELONA_DEFINE_OPTION(int, music_volume)
    ELONA_DEFINE_OPTION(bool, net)
    ELONA_DEFINE_OPTION(bool, object_shadow)
    ELONA_DEFINE_OPTION(std::string, pcc_graphic_scale)
    ELONA_DEFINE_OPTION(int, restock_interval)
    ELONA_DEFINE_OPTION(int, run_wait)
    ELONA_DEFINE_OPTION(int, screen_refresh_wait)
    ELONA_DEFINE_OPTION(bool, scroll)
    ELONA_DEFINE_OPTION(bool, scroll_when_run)
    ELONA_DEFINE_OPTION(int, select_fast_start_wait)
    ELONA_DEFINE_OPTION(int, select_fast_wait)
    ELONA_DEFINE_OPTION(int, select_wait)
    ELONA_DEFINE_OPTION(bool, skip_confirm_at_shop)
    ELONA_DEFINE_OPTION(bool, skip_overcasting_warning)
    ELONA_DEFINE_OPTION(bool, skip_random_event_popups)
    ELONA_DEFINE_OPTION(bool, sound)
    ELONA_DEFINE_OPTION(int, sound_volume)
    ELONA_DEFINE_OPTION(int, start_run_wait)
    ELONA_DEFINE_OPTION(std::string, startup_script)
    ELONA_DEFINE_OPTION(bool, story)
    ELONA_DEFINE_OPTION(bool, title_effect)
    ELONA_DEFINE_OPTION(int, walk_wait)
    ELONA_DEFINE_OPTION(bool, weather_effect)
    ELONA_DEFINE_OPTION(bool, window_animation)

    ELONA_DEFINE_OPTION(bool, is_test) // testing use only
};


extern Config g_config;

} // namespace elona

#pragma once

#include <iostream>
#include <string>
#include <unordered_set>
#include "../../snail/window.hpp"
#include "../../thirdparty/json5/json5.hpp"
#include "../../thirdparty/ordered_map/ordered_map.h"
#include "../../util/noncopyable.hpp"
#include "../elona.hpp"
#include "../filesystem.hpp"
#include "../log.hpp"
#include "config_def.hpp"



namespace elona
{

class ConfigDef;

class Config
{
public:
    static Config& instance()
    {
        static Config the_instance;
        return the_instance;
    }



    Config() = default;
    ~Config() = default;



    void load_def(std::istream& is, const std::string& mod_id);
    void load_def(const fs::path& config_def_path, const std::string& mod_id);
    void load(std::istream&, const std::string&, bool);
    void save();

    void clear();

    // If your are vimmer, ex command ":sort /\w\+;/ r" can sort the list well.
    int alert_wait;
    bool allow_enhanced_skill;
    bool always_center;
    int animation_wait;
    bool attack_animation;
    bool attack_neutral_npcs;
    int attack_wait;
    std::string auto_turn_speed;
    bool autodisable_numlock;
    bool autopick;
    bool autosave;
    bool damage_popup;
    std::string display_mode;
    int enhanced_skill_lowerbound;
    int enhanced_skill_upperbound;
    bool extra_class;
    bool extra_help;
    bool extra_race;
    std::string font_filename;
    std::string fullscreen;
    int general_wait;
    bool heartbeat;
    bool hide_autoidentify;
    bool hide_shop_updates;
    bool high_quality_shadow;
    std::string hp_bar_position;
    int initial_key_repeat_wait;
    bool joypad;
    int key_repeat_wait;
    int key_wait;
    std::string language;
    bool leash_icon;
    int max_damage_popup;
    bool message_add_timestamps;
    int message_transparency;
    bool music;
    bool net;
    bool object_shadow;
    std::string pcc_graphic_scale;
    int restock_interval;
    int run_wait;
    int screen_refresh_wait;
    bool scroll;
    bool scroll_when_run;
    int select_fast_start_wait;
    int select_fast_wait;
    int select_wait;
    bool skip_confirm_at_shop;
    bool skip_overcasting_warning;
    bool skip_random_event_popups;
    bool sound;
    int start_run_wait;
    std::string startup_script;
    bool story;
    bool title_effect;
    int walk_wait;
    bool weather_effect;
    bool window_animation;
    bool wizard;

    bool is_test = false; // testing use only



    const std::unordered_set<std::string>& get_mod_ids()
    {
        return mod_ids_;
    }



    bool is_visible(const std::string& key) const
    {
        return def.get_metadata(key).is_visible();
    }



    void inject_enum(
        const std::string& key,
        std::vector<std::string> variants,
        std::string default_variant);



    void bind_getter(
        const std::string& key,
        std::function<json5::value(void)> getter)
    {
        if (!def.exists(key))
        {
            throw std::runtime_error("No such config value " + key);
        }
        getters_[key] = getter;
    }



    template <typename T>
    void bind_setter(
        const std::string& key,
        std::function<void(const T&)> setter)
    {
        if (!def.exists(key))
        {
            throw std::runtime_error("No such config value " + key);
        }
        setters_[key] = [setter](const json5::value& value) {
            setter(value.get<T>());
        };
    }



    template <typename T>
    T get(const std::string& key) const
    {
        if (storage_.find(key) == storage_.end())
        {
            // TODO fallback to default specified in config definition instead
            throw std::runtime_error("No such config value " + key);
        }
        if (!storage_.at(key).is<T>())
        {
            throw std::runtime_error(
                "Expected type \"" + def.type_to_string(key) + "\" for key " +
                key);
        }

        try
        {
            if (getters_.find(key) != getters_.end())
            {
                return getters_.at(key)().get<T>();
            }
            else
            {
                return storage_.at(key).get<T>();
            }
        }
        catch (std::exception& e)
        {
            throw std::runtime_error(
                "Error on getting config value " + key + ": " + e.what());
        }
    }



    bool check_type(const std::string& key, json5::value_type type) const;

    void set(const std::string& key, const json5::value& value);

    void run_setter(const std::string& key);



    const ConfigDef& get_def() const
    {
        return def;
    }



private:
    void load_defaults(bool);

    void visit(
        const json5::value& value,
        const std::string& current_key,
        const std::string& config_filename,
        bool preload);
    void visit_object(
        const json5::value::object_type& object,
        const std::string& current_key,
        const std::string& config_filename,
        bool preload);
    bool verify_types(
        const json5::value& value,
        const std::string& current_key);

    ConfigDef def;
    tsl::ordered_map<std::string, json5::value> storage_;
    tsl::ordered_map<std::string, std::function<json5::value(void)>> getters_;
    tsl::ordered_map<std::string, std::function<void(const json5::value&)>>
        setters_;
    std::unordered_set<std::string> mod_ids_;
};



template <>
inline void Config::bind_setter<int>(
    const std::string& key,
    std::function<void(const int&)> setter)
{
    std::function<void(const json5::integer_type&)> f =
        [=](const json5::integer_type& value) { setter(value); };
    bind_setter(key, f);
}



template <>
inline int Config::get<int>(const std::string& key) const
{
    return static_cast<int>(get<json5::value::integer_type>(key));
}



/***
 * Loads config options that are marked to be loaded before the application
 * instance is initialized, like screen size. The config file is loaded from the
 * current profile.
 */
void initialize_config_preload();

void load_config();

snail::Window::FullscreenMode config_get_fullscreen_mode();

} // namespace elona

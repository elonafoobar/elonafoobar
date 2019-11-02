#pragma once

#include <iostream>
#include <string>
#include <unordered_set>
#include "../../snail/window.hpp"
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
    static Config& instance();

    Config()
    {
    }
    ~Config() = default;

    void load_def(std::istream& is, const std::string& mod_id);
    void load_def(const fs::path& config_def_path, const std::string& mod_id);
    void load(std::istream&, const std::string&, bool);
    void save();

    void clear()
    {
        def.clear();
        storage_.clear();
        getters_.clear();
        setters_.clear();
    }

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

    void bind_getter(
        const std::string& key,
        std::function<hcl::Value(void)> getter)
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
        setters_[key] = [setter](const hcl::Value& value) {
            setter(value.as<T>());
        };
    }

    void inject_enum(
        const std::string& key,
        std::vector<std::string> variants,
        std::string default_variant)
    {
        def.inject_enum(key, variants, default_variant);

        auto EnumDef = def.get<spec::EnumDef>(key);
        if (storage_.find(key) != storage_.end())
        {
            // Check if this enum has an invalid value. If so, set it to the
            // default.
            std::string current = get<std::string>(key);
            if (!EnumDef.get_index_of(current))
            {
                ELONA_WARN("config")
                    << "Config key "s << key << " had invalid variant "s
                    << current << ". "s
                    << "("s << def.type_to_string(key) << ")"s
                    << "Setting to "s << EnumDef.get_default() << "."s;
                set(key, EnumDef.get_default());
            }
        }
        else
        {
            set(key,
                EnumDef.get_default()); // Set the enum to its default value.
        }
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
                return getters_.at(key)().as<T>();
            }
            else
            {
                return storage_.at(key).as<T>();
            }
        }
        catch (std::exception& e)
        {
            throw std::runtime_error(
                "Error on getting config value " + key + ": " + e.what());
        }
    }

    template <typename T>
    bool check_type(const std::string& key) const
    {
        const auto itr = storage_.find(key);
        if (itr == storage_.end())
        {
            throw std::runtime_error("No such config value " + key);
        }
        return itr->second.is<T>();
    }

    void set(const std::string& key, const hcl::Value value)
    {
        ELONA_LOG("config") << "Set: " << key << " to " << value;

        if (!def.exists(key))
        {
            throw std::runtime_error("No such config key " + key);
        }
        if (verify_types(value, key))
        {
            if (value.is<int>())
            {
                int temp = value.as<int>();
                temp = clamp(temp, def.get_min(key), def.get_max(key));
                storage_[key] = temp;
            }
            else
            {
                storage_[key] = std::move(value);
            }

            if (setters_.find(key) != setters_.end())
            {
                setters_[key](storage_.at(key));
            }
        }
        else
        {
            std::stringstream ss;
            ss << "Wrong config item type for key " << key << ": ";
            ss << def.type_to_string(key) << " expected, got ";
            ss << value;
            throw std::runtime_error(ss.str());
        }
    }

    void run_setter(const std::string& key)
    {
        if (storage_.find(key) == storage_.end())
        {
            return;
        }
        if (setters_.find(key) != setters_.end())
        {
            setters_[key](storage_.at(key));
        }
    }

    const ConfigDef& get_def() const
    {
        return def;
    }

private:
    void load_defaults(bool);

    void visit(const hcl::Value&, const std::string&, const std::string&, bool);
    void visit_object(
        const hcl::Object&,
        const std::string&,
        const std::string&,
        bool);
    bool verify_types(const hcl::Value&, const std::string&);

    ConfigDef def;
    tsl::ordered_map<std::string, hcl::Value> storage_;
    tsl::ordered_map<std::string, std::function<hcl::Value(void)>> getters_;
    tsl::ordered_map<std::string, std::function<void(const hcl::Value&)>>
        setters_;
    std::unordered_set<std::string> mod_ids_;
};



/***
 * Loads config options that are marked to be loaded before the application
 * instance is initialized, like screen size. The config file is loaded from the
 * current profile.
 */
void initialize_config_preload();

void load_config();

void set_config(const std::string& key, int value);
void set_config(const std::string& key, const std::string& value);
void set_config(const std::string& key, const std::string& value1, int value2);

snail::Window::FullscreenMode config_get_fullscreen_mode();


} // namespace elona

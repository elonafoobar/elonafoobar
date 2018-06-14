#pragma once

#include "filesystem.hpp"
#include "lib/noncopyable.hpp"
#include "snail/window.hpp"
#include "config_def.hpp"
#include <map>
#include <string>
#include <iostream>



namespace elona
{

class config_def;

class config : public lib::noncopyable
{
public:
    static config& instance();

    void init(const fs::path&);
    void write();

    void clear()
    {
        def.clear();
        storage.clear();
        callbacks.clear();
    }

    int alert;
    int alwayscenter;
    int animewait;
    int attackanime;
    int attackwait;
    int autonumlock;
    int autosave;
    int autoturn;
    int damage_popup;
    std::string display_mode;
    int env;
    int extraclass;
    int extrahelp;
    int extrarace;
    std::string font1;
    std::string font2;
    int fullscreen;
    int heart;
    int hideautoidentify;
    int hideshopresult;
    int hp_bar;
    int ignoredislike;
    int joypad;
    int keywait;
    int language;
    int leash_icon;
    int msgaddtime;
    int msgtrans;
    int music;
    int net;
    int netchat;
    int netwish;
    int noadebug;
    int objectshadow;
    int restock_interval;
    int runscroll;
    int runwait;
    int scroll;
    int scrsync;
    int serverlist;
    int shadow;
    int skiprandevents;
    int sound;
    int startrun;
    std::string startup_script;
    int story;
    int wait1;
    int walkwait;
    int windowanime;
    int wizard;
    int xkey;
    int zkey;

    int use_autopick;
    int use_autopick_in_home;
    int use_autopick_in_dungeon;
    int use_autopick_in_shop;
    int use_autopick_in_ranch;
    int use_autopick_in_crop;
    int use_autopick_in_storage_house;
    int use_autopick_in_shelter;
    int use_autopick_in_town;
    int use_autopick_in_conquered_nefia;
    int use_autopick_in_conquered_quest_map;

    bool is_test = false; // testing use only

    template <typename T>
    void bind(const std::string& key,
                  std::function<void(T)> callback)
    {
        if (!def.exists(key))
        {
            throw std::runtime_error("No such config value " + key);
        }
        callbacks.emplace(key, [callback](const hcl::Value& value){ callback(value.as<T>()); });
    }

    template <typename T>
    T get(const std::string& key)
    {
        if (storage.find(key) == storage.end())
        {
            // TODO fallback to default specified in config definition instead
            throw std::runtime_error("No such config value " + key);
        }
        if (!def.is<T>(key))
        {
            throw std::runtime_error("Expected type \"" + def.type_to_string(key) + "\" for key " + key);
        }
        if (!storage[key].is<T>())
        {
            throw std::runtime_error("BUG: Stored value had wrong type for key " + key +
                                     " (this should never happen)");
        }
        return storage[key].as<T>();
    }

    void set(const std::string& key, const hcl::Value value)
    {
        std::cout << "set: " << key << " to " << value << std::endl;
        if (!def.exists(key))
        {
            throw std::runtime_error("No such config key " + key);
        }
        if (verify_types(value, key))
        {
            if (value.is<int>())
            {
                int temp = value;
                if (auto max = def.get_max(key))
                {
                    temp = std::min(temp, max);
                }
                if (auto min = def.get_min(key))
                {
                    temp = std::max(temp, min);
                }
                value = temp;
            }

            storage.emplace(key, std::move(value));
        }
        else
        {
            std::stringstream ss;
            ss << "Wrong config item type for key " << key << ": ";
            ss << def.type_to_string(key) << " expected, got ";
            ss << value;
            throw std::runtime_error(ss.str());
        }

        if (callbacks.find(key) != callbacks.end())
        {
            callbacks[key](value);
        }
    }

private:
    config() {}
    ~config() = default;

    void load(std::istream&, const std::string&);
    void load_defaults();

    void visit(const hcl::Value&, const std::string&, const std::string&);
    void visit_object(const hcl::Object&, const std::string&, const std::string&);
    bool verify_types(const hcl::Value&, const std::string&);

    config_def def;
    std::map<std::string, hcl::Value> storage;
    std::map<std::string, std::function<void(const hcl::Value&)>> callbacks;
};



void load_config2(const fs::path& json_file);
void load_config(const fs::path& json_file);

void set_config(const std::string& key, int value);
void set_config(const std::string& key, const std::string& value);
void set_config(const std::string& key, const std::string& value1, int value2);

snail::window::fullscreen_mode_t config_get_fullscreen_mode();


} // namespace elona

#pragma once

#include <string>
#include "lib/noncopyable.hpp"



namespace elona
{


class config : public lib::noncopyable
{
public:
    static config& instance();

    int alert;
    int alwayscenter;
    int animewait;
    int attackanime;
    int attackwait;
    int autonumlock;
    int autoturn;
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
    int initialkeywait;
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
    int objectshadow;
    int runscroll;
    int runwait;
    int scroll;
    int scrsync;
    int serverlist;
    int shadow;
    int skiprandevents;
    int sound;
    int startrun;
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


private:
    config() = default;
};



void load_config2();
void load_config();


void set_config(const std::string& key, int value);
void set_config(const std::string& key, const std::string& value);
void set_config(const std::string& key, const std::string& value1, int value2);



} // namespace elona

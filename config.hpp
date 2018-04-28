#pragma once

#include <string>
#include "lib/noncopyable.hpp"



namespace elona
{


class config : public lib::noncopyable
{
public:
    static config& instance();

private:
    config() = default;
};



void load_config2();
void load_config();


void set_config(const std::string& key, int value);
void set_config(const std::string& key, const std::string& value);
void set_config(const std::string& key, const std::string& value1, int value2);



extern int cfg_alert;
extern int cfg_alwayscenter;
extern int cfg_animewait;
extern int cfg_attackanime;
extern int cfg_attackwait;
extern int cfg_autonumlock;
extern int cfg_autoturn;
extern int cfg_env;
extern int cfg_extraclass;
extern int cfg_extrahelp;
extern int cfg_extrarace;
extern std::string cfg_font1;
extern std::string cfg_font2;
extern int cfg_fullscreen;
extern int cfg_heart;
extern int cfg_hideautoidentify;
extern int cfg_hideshopresult;
extern int cfg_hp_bar;
extern int cfg_ignoredislike;
extern int cfg_joypad;
extern int cfg_language;
extern int cfg_leash_icon;
extern int cfg_msgaddtime;
extern int cfg_msgtrans;
extern int cfg_music;
extern int cfg_net;
extern int cfg_netchat;
extern int cfg_netwish;
extern int cfg_objectshadow;
extern int cfg_runscroll;
extern int cfg_runwait;
extern int cfg_scroll;
extern int cfg_scrsync;
extern int cfg_serverlist;
extern int cfg_shadow;
extern int cfg_skiprandevents;
extern int cfg_sound;
extern int cfg_startrun;
extern int cfg_story;
extern int cfg_wait1;
extern int cfg_walkwait;
extern int cfg_windowanime;
extern int cfg_wizard;
extern int cfg_xkey;
extern int cfg_zkey;


} // namespace elona

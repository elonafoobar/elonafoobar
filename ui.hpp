#pragma once

#include <string>
#include "snail/application.hpp"

namespace elona
{

struct position_t;

position_t gmes(const std::string&, int, int, int, const snail::color&, bool);
void initialize_ui_constants();
void display_customkey(const std::string&, int, int);
void display_key(int = 0, int = 0, int = 0);
void display_msg(int = 0, int = 0);
void display_note(const std::string&, int = 0);
void display_topic(const std::string&, int = 0, int = 0, int = 0);
void display_window(int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);
void display_window2(int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);
void fillbg(int = 0, int = 0, int = 0, int = 0, int = 0);
void drawmenu(int = 0);
void screen_txtadv();
void label_1416();
void update_entire_screen();
void update_screen_hud();
void update_screen();
void update_minimap();
void label_1420();
void render_hud();
void load_continuous_action_animation();
void render_autoturn_animation();
void draw_caption();
void update_scrolling_info();
void update_slight();
void label_1433();
void render_stair_positions_in_minimap();
void render_weather_effect_rain();
void render_weather_effect_hard_rain();
void render_weather_effect_snow();
void render_weather_effect_etherwind();
void label_1438();
void label_1439();
void draw_minimap_pixel();
void fade_out();
void label_1442();
void animation_fade_in();
void label_1444();
void label_1445();
void render_fishing_animation();
void load_background_variants(int buffer);
void clear_background_in_character_making();

void draw_scroll(int x, int y, int width, int height);
void cs_listbk();
void cs_list(
    bool is_selected,
    const std::string& text,
    int x,
    int y,
    int x_offset = 0,
    int color_mode = 0,
    int ci = 0);
void showscroll(const std::string& title, int x, int y, int width, int height);
void window(
    int prm_650 = 0,
    int prm_651 = 0,
    int prm_652 = 0,
    int prm_653 = 0,
    int = 0,
    int prm_655 = 0);
void window2(
    int prm_656 = 0,
    int prm_657 = 0,
    int prm_658 = 0,
    int prm_659 = 0,
    int prm_660 = 0,
    int prm_661 = 0);
void windowanime(
    int prm_726 = 0,
    int prm_727 = 0,
    int prm_728 = 0,
    int prm_729 = 0,
    int prm_730 = 0,
    int prm_731 = 0);
void windowanimecorner(
    int prm_732 = 0,
    int prm_733 = 0,
    int prm_734 = 0,
    int prm_735 = 0,
    int prm_736 = 0,
    int prm_737 = 0);
void showtitle(
    const std::string&,
    const std::string& prm_739,
    int prm_740 = 0,
    int = 0);


} // namespace elona

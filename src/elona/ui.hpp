#pragma once

#include <string>
#include "../snail/application.hpp"

namespace elona
{

struct Position;

Position gmes(const std::string&, int, int, int, const snail::Color&, bool);
void initialize_ui_constants();
void display_customkey(const std::string&, int, int);
void display_key(int = 0, int = 0, int = 0);
void display_msg(int = 0, int = 0);
void display_note(const std::string&, int = 0);



void display_topic(const std::string& topic, int x, int y);



void display_window(int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);
void display_window2(int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);



void fillbg(
    int tile_window_id,
    int tile_x,
    int tile_y,
    int tile_width,
    int tile_height);



void screen_txtadv();

void update_entire_screen();
void update_screen();
void update_minimap();
void ui_render_from_screensync();
void render_hud();
void load_continuous_action_animation();
void draw_caption();
void update_scrolling_info();
void update_slight();
void ui_render_non_hud();
void ui_scroll_screen();
void ui_initialize_minimap();
void fade_out();
void ui_win_screen_fade();
void animation_fade_in();
void event_7_setup();
void event_7_modify_screen();
void render_fishing_animation();
void load_background_variants(int buffer);
void clear_background_in_character_making();
void clear_background_in_continue();

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



void window(int x, int y, int width, int height, bool shadow = false);



void window2(
    int x,
    int y,
    int width,
    int height,
    int frame_style,
    int fill_style);



void window_animation(
    int x,
    int y,
    int width,
    int height,
    int duration,
    int temporary_window_id);



void window_animation_corner(
    int x,
    int y,
    int width,
    int height,
    int duration,
    int temporary_window_id);



void show_title(const std::string& title);



} // namespace elona

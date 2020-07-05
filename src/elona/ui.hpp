#pragma once

#include <string>

#include "../snail/application.hpp"
#include "eobject/eobject.hpp"



namespace elona
{

struct Position;
struct Item;

Position gmes(const std::string&, int, int, int, const snail::Color&, bool);
void initialize_ui_constants();
void display_customkey(const std::string&, int, int);
void display_key(int x = 0, int y = 0, int nth = 0);
void display_note(const std::string&, int = 0);



void display_topic(const std::string& topic, int x, int y);



void ui_display_window(
    const std::string& title,
    const std::string& key_help,
    int x,
    int y,
    int width,
    int height,
    int x_offset = 0,
    int y_offset = 0);
void ui_display_window2(
    const std::string& tips,
    int x,
    int y,
    int width,
    int height);



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
void load_activity_animation();
void ui_draw_caption(const std::string& text);
void update_scrolling_info();
void update_slight();
void ui_render_non_hud();
void ui_scroll_screen();
void ui_initialize_minimap();
void fade_out();
void ui_win_screen_fade();
void animation_fade_in();
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
    const snail::Color& text_color = {10, 10, 10});
snail::Color cs_list_get_item_color(const ItemRef& item);
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


void auto_turn(int delay);
void page_load();
void page_save();
void savecycle();
void sort_list_by_column1();
void sort_list_and_listn_by_column1();
int winposy(int = 0, int = 0);

} // namespace elona

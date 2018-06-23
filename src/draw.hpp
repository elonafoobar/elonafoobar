#pragma once

#include <string>
#include <vector>
#include "snail/color.hpp"


namespace elona
{



struct item_chip_t
{
    int x;
    int y;
    int width;
    int height;
    int offset_y;
    int stack_height;
    int shadow;
    int animation;
};


extern std::vector<item_chip_t> item_chips;



struct chara_chip_t
{
    int x;
    int y;
    int width;
    int height;
    int offset_y;
};


extern std::vector<chara_chip_t> chara_chips;



void prepare_item_image(int id, int color);
void prepare_item_image(int id, int color, int character_image);

void set_color_mod(int r, int g, int b, int window_id = -1);

enum class show_hp_bar_side
{
    left_side,
    right_side,
};

void show_hp_bar(show_hp_bar_side side, int inf_clocky);

void initialize_damage_popups();
void add_damage_popup(
    const std::string& text,
    int character,
    const snail::color& color);
void clear_damage_popups();
void show_damage_popups();

void draw_emo(int = 0, int = 0, int = 0);
void load_pcc_part(int cc, int body_part, const char* body_part_str);
void set_pcc_depending_on_equipments(int cc, int ci);
void chara_preparepic(int prm_618, int prm_619 = 0);
void create_pcpic(int cc, bool prm_410);
void initialize_map_chip();
void initialize_item_chip();

} // namespace elona

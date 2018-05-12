#pragma once

#include <string>
#include "snail/color.hpp"


namespace elona
{


void prepare_item_image(int id, int color);
void prepare_item_image(int id, int color, int character_image);

void set_color_mod(int r, int g, int b, int window_id = -1);

enum class show_hp_bar_side
{
    left_side,
    right_side,
};

void show_hp_bar(show_hp_bar_side side, int inf_clocky);

void add_damage_popup(
    const std::string& text,
    int character,
    const snail::color& color);
void clear_damage_popups();
void show_damage_popups(int inf_ver);


} // namespace elona

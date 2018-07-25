#pragma once

#include <string>
#include <vector>
#include "optional.hpp"
#include "pic_loader/extent.hpp"
#include "snail/color.hpp"
#include "shared_id.hpp"


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
    shared_id key;
    int offset_y;
};


extern std::vector<chara_chip_t> chara_chips;


optional_ref<extent> draw_get_rect_chara(int);
optional_ref<extent> draw_get_rect(const std::string&);

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

struct character;
optional_ref<extent> chara_preparepic(const character& cc);
optional_ref<extent> chara_preparepic(int image_id);

void create_pcpic(int cc, bool prm_410);
void initialize_map_chip();
void initialize_all_chips();


void bmes(
    const std::string& message,
    int x,
    int y,
    const snail::color& text_color = {255, 255, 255, 255},
    const snail::color& shadow_color = {0, 0, 0, 255});



struct image_info
{
    int window_id;
    int x;
    int y;
    int width;
    int height;
};


void init_assets();

void draw(const std::string& key, int x, int y);
void draw(const std::string& key, int x, int y, int width, int height);
void draw_rotated(
    const std::string& key,
    int center_x,
    int center_y,
    double angle);
void draw_rotated(
    const std::string& key,
    int center_x,
    int center_y,
    int width,
    int height,
    double angle);

const image_info& get_image_info(const std::string& key);

void draw_chara(const character& chara,
                int x,
                int y,
                int scale = 1,
                int alpha = 0);
void draw_chara(int image_id,
                int x,
                int y,
                int scale = 1,
                int alpha = 0);
void draw_chara_scale_height(const character& chara, int x, int y);
void draw_chara_scale_height(int image_id, int x, int y);


} // namespace elona

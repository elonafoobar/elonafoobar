#pragma once

#include <string>
#include <vector>
#include "../snail/color.hpp"
#include "optional.hpp"
#include "pic_loader/extent.hpp"
#include "shared_id.hpp"


namespace elona
{

class CharaChipDB;
class ItemChipDB;
class PortraitDB;
struct Item;

struct ItemChip
{
    // NOTE: fully qualified to avoid ID collisions in pic_loader
    SharedId key; // core.item_chip#core.putitoro

    int offset_y;
    int stack_height;
    int shadow;
    int animation;
};


extern std::vector<ItemChip> item_chips;



struct CharaChip
{
    // NOTE: fully qualified to avoid ID collisions in pic_loader
    SharedId key; // core.chara_chip#core.putit

    int offset_y;
};


extern std::vector<CharaChip> chara_chips;


optional_ref<Extent> draw_get_rect_chara(int);
optional_ref<Extent> draw_get_rect_item(int);
optional_ref<Extent> draw_get_rect_portrait(const std::string&);
optional_ref<Extent> draw_get_rect(const std::string&);

optional_ref<Extent> prepare_item_image(int id, int color);
optional_ref<Extent> prepare_item_image(int id, int color, int character_image);

void set_color_mod(int r, int g, int b, int window_id = -1);

enum class HPBarSide
{
    left_side,
    right_side,
};

void show_hp_bar(HPBarSide side, int inf_clocky);

void initialize_damage_popups();
void add_damage_popup(
    const std::string& text,
    int character,
    const snail::Color& color);
void clear_damage_popups();
void show_damage_popups();

void draw_emo(int = 0, int = 0, int = 0);
void load_pcc_part(int cc, int body_part, const char* body_part_str);
void set_pcc_depending_on_equipments(int cc, int ci);

struct Character;
optional_ref<Extent> chara_preparepic(const Character& cc);
optional_ref<Extent> chara_preparepic(int image_id);

void create_pcpic(int cc, bool with_equipments = true);
void initialize_map_chip();
void initialize_chara_chips(const CharaChipDB&);
void initialize_item_chips(const ItemChipDB&);
void initialize_portraits(const PortraitDB&);
void initialize_all_chips();
void draw_clear_loaded_chips();
void draw_init_key_select_buffer();
void draw_select_key(const std::string& key, int x, int y);


void bmes(
    const std::string& message,
    int x,
    int y,
    const snail::Color& text_color = {255, 255, 255, 255},
    const snail::Color& shadow_color = {0, 0, 0, 255});



struct ImageInfo
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

const ImageInfo& get_image_info(const std::string& key);

void draw_chara(
    const Character& chara,
    int x,
    int y,
    int scale = 1,
    int alpha = 0);
void draw_chara(int image_id, int x, int y, int scale = 1, int alpha = 0);
void draw_chara_scale_height(const Character& chara, int x, int y);
void draw_chara_scale_height(int image_id, int x, int y);

void draw_item_material(int mat_id, int x, int y);
void draw_item_with_portrait(const Item& item, int x, int y);
void draw_item_with_portrait(
    int image_id,
    int color,
    optional<int> chara_chip_id,
    int x,
    int y);

void draw_item_with_portrait_scale_height(const Item& item, int x, int y);
void draw_item_with_portrait_scale_height(
    int image_id,
    int color,
    optional<int> chara_chip_id,
    int x,
    int y);


} // namespace elona

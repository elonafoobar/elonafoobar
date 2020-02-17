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
class MapChipDB;
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


optional_ref<const Extent> draw_get_rect_chara(int);
optional_ref<const Extent> draw_get_rect_item(int);
optional_ref<const Extent> draw_get_rect_portrait(const std::string&);
optional_ref<const Extent> draw_get_rect(const std::string&);

optional_ref<const Extent> prepare_item_image(int id, int color);
optional_ref<const Extent>
prepare_item_image(int id, int color, int character_image);

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

struct Character;
optional_ref<const Extent> chara_preparepic(const Character& cc);
optional_ref<const Extent> chara_preparepic(int image_id);

void create_pcpic(Character& chara, bool with_equipments = true);
void initialize_map_chips(const MapChipDB&);
void initialize_chara_chips(const CharaChipDB&);
void initialize_item_chips(const ItemChipDB&);
void initialize_portraits(const PortraitDB&);
void initialize_all_chips();

void draw_prepare_map_chips();

void draw_clear_loaded_chips();
void draw_init_key_select_buffer();
void draw_select_key(const std::string& key, int x, int y);


void bmes(
    const std::string& message,
    int x,
    int y,
    const snail::Color& text_color = {255, 255, 255, 255},
    const snail::Color& shadow_color = {0, 0, 0, 255});


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


// Asset-related functions

struct AssetData;

const AssetData& asset_load(const std::string& key);
const AssetData& asset_load(const std::string& key, int window_id);
void init_assets();

void draw(const std::string& key, int x, int y);
void draw(const std::string& key, int x, int y, int width, int height);
void draw_centered(const std::string& key, int x, int y, int width, int height);
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
void draw_indexed(const std::string& key, int x, int y, int index);
void draw_indexed(
    const std::string& key,
    int x,
    int y,
    int index_x,
    int index_y);
void draw_indexed_rotated(
    const std::string& key,
    int x,
    int y,
    int index_x,
    int index_y,
    double angle);
void draw_region(const std::string& key, int x, int y, int width);
void draw_region(const std::string& key, int x, int y, int width, int height);
void draw_region(
    const std::string& key,
    int x,
    int y,
    int offset_x,
    int offset_y,
    int width,
    int height);
void draw_region(
    const std::string& key,
    int x,
    int y,
    int offset_x,
    int offset_y,
    int width,
    int height,
    int dst_width,
    int dst_height);
void draw_region_centered(
    const std::string& key,
    int x,
    int y,
    int offset_x,
    int offset_y,
    int width,
    int height,
    int dst_width,
    int dst_height);
void draw_region_rotated(
    const std::string& key,
    int x,
    int y,
    int offset_x,
    int offset_y,
    int width,
    int height,
    double angle);
void draw_bar(
    const std::string& key,
    int x,
    int y,
    int dst_width,
    int dst_height,
    int width);
void draw_bar_vert(
    const std::string& key,
    int x,
    int y,
    int dst_width,
    int dst_height,
    int height);
void draw_indexed_region(
    const std::string& key,
    int x,
    int y,
    int index_x,
    int index_y,
    int count_x,
    int count_y);
void draw_bg(const std::string& key);
void asset_copy_from(int window_id, int x, int y, const std::string& key);
void asset_copy_from(
    int window_id,
    int x,
    int y,
    int width,
    int height,
    const std::string& key);

void draw_map_tile(int id, int x, int y, int anim_frame = 0);
void draw_map_tile(
    int id,
    int x,
    int y,
    int width,
    int height,
    int anim_frame = 0);
void draw_map_tile(
    int id,
    int x,
    int y,
    int width,
    int height,
    int dst_width,
    int dst_height,
    int anim_frame = 0);

const AssetData& get_image_info(const std::string& key);

} // namespace elona

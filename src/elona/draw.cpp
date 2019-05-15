#include "draw.hpp"
#include <cmath>
#include "../snail/application.hpp"
#include "character.hpp"
#include "config/config.hpp"
#include "data/types/type_asset.hpp"
#include "data/types/type_chara_chip.hpp"
#include "data/types/type_item.hpp"
#include "data/types/type_item_chip.hpp"
#include "data/types/type_map_chip.hpp"
#include "data/types/type_portrait.hpp"
#include "elona.hpp"
#include "fov.hpp"
#include "hcl.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "map.hpp"
#include "mapgen.hpp"
#include "mef.hpp"
#include "pic_loader/extent.hpp"
#include "pic_loader/pic_loader.hpp"
#include "pic_loader/tinted_buffers.hpp"
#include "random.hpp"
#include "variables.hpp"



namespace
{

PicLoader loader;
TintedBuffers tinted_buffers;


struct DamagePopup
{
    int frame;
    std::string text;
    int character;
    snail::Color color{0, 0, 0};

    DamagePopup()
        : frame(-1)
        , text(std::string())
        , character(-1)
        , color(snail::Color(255, 255, 255, 0))
    {
    }
};


std::vector<DamagePopup> damage_popups;
int damage_popups_active = 0;



/*
 * TERMS OF USE - EASING EQUATIONS
 *
 * Open source under the BSD License.
 *
 * Copyright © 2001 Robert Penner
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer. Redistributions in binary
 * form must reproduce the above copyright notice, this list of conditions and
 * the following disclaimer in the documentation and/or other materials provided
 * with the distribution. Neither the name of the author nor the names of
 * contributors may be used to endorse or promote products derived from this
 * software without specific prior written permission. THIS SOFTWARE IS PROVIDED
 * BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

double elastic_easing(double t)
{
    constexpr double pi = 3.14159265358979323;

    if (t == 0)
        return 0;
    if (t == 1)
        return 1;
    return std::pow(2, -10 * t) * std::sin((t - 0.075) * (2 * pi) / 0.3) + 1;
}


double easing(double t)
{
    if (t > 0.3)
        return 0;

    return elastic_easing(t);
}



} // namespace


namespace elona
{


std::vector<ItemChip> item_chips{825};
std::vector<CharaChip> chara_chips{925};


/**
 * Obtains the window buffer and region where the character sprite with ID @a id
 * is located, for use with @ref gcopy.
 */
optional_ref<const Extent> draw_get_rect_chara(int id)
{
    return draw_get_rect(chara_chips[id].key);
}



/**
 * Obtains the window buffer and region where the item sprite with ID @a id
 * is located, for use with @ref gcopy.
 */
optional_ref<const Extent> draw_get_rect_item(int id)
{
    return draw_get_rect(item_chips[id].key);
}



/**
 * Obtains the window buffer and region where the portrait with ID @a key
 * is located, for use with @ref gcopy.
 */
optional_ref<const Extent> draw_get_rect_portrait(const std::string& key)
{
    return loader["core.portrait"s + data_id_separator + key];
}



optional_ref<const Extent> draw_get_rect(const std::string& key)
{
    return loader[key];
}


/**
 * Applies a color to the item sprite of ID @a id and copies it to the scratch
 * window (ID 1) at coordinates [0, 960], so it can be copied with @ref gcopy.
 */
optional_ref<const Extent> prepare_item_image(int id, int color)
{
    const auto rect = draw_get_rect_item(id);

    gsel(1);
    boxf(0, 960, rect->width, rect->height);

    // The color modifier is applied to the source buffer before
    // copying it to the scratch region. It is restored after copying.
    set_color_mod(
        255 - c_col(0, color),
        255 - c_col(1, color),
        255 - c_col(2, color),
        rect->buffer);
    gcopy(rect->buffer, rect->x, rect->y, rect->width, rect->height, 0, 960);
    set_color_mod(255, 255, 255, rect->buffer);

    gsel(0);
    return rect;
}



/**
 * Applies a color to the item sprite of ID @a id and copies it to the scratch
 * window (ID 1) at coordinates [0, 960], so it can be copied with @ref gcopy.
 *
 * This variant is intended for use with cards/figures and copies the character
 * sprite indicated by @a character_image to the appropriate location for each.
 */
optional_ref<const Extent>
prepare_item_image(int id, int color, int character_image)
{
    if (id != 528 && id != 531)
    {
        return prepare_item_image(id, color);
    }

    optional_ref<const Extent> item_rect;

    if (id == 528) // Cards
    {
        item_rect = draw_get_rect_item(id);
        gsel(1);
        boxf(0, 960, inf_tiles, inf_tiles * 2);

        const auto character_id = character_image % 1000;
        const auto character_color = character_image / 1000;
        auto rect = draw_get_rect_chara(character_id);
        gmode(2);

        // Modify color and restore it afterwards.
        set_color_mod(
            255 - c_col(0, color),
            255 - c_col(1, color),
            255 - c_col(2, color),
            item_rect->buffer);
        gcopy(
            item_rect->buffer,
            item_rect->x,
            item_rect->y,
            item_rect->width,
            item_rect->height,
            0,
            960);
        set_color_mod(255, 255, 255, item_rect->buffer);

        // Modify color and restore it afterwards.
        set_color_mod(
            255 - c_col(0, character_color),
            255 - c_col(1, character_color),
            255 - c_col(2, character_color),
            rect->buffer);
        gcopy(
            rect->buffer,
            rect->x + 8,
            rect->y + 4 + (rect->height > inf_tiles) * 8,
            rect->width - 16,
            rect->height - 8 - (rect->height > inf_tiles) * 10,
            0,
            1008,
            22,
            20);
        set_color_mod(255, 255, 255, rect->buffer);

        gcopy(1, 0, 1008, 22, 20, 6, 974);
        gsel(0);
    }
    else // Figures
    {
        const auto character_id = character_image % 1000;
        const auto character_color = character_image / 1000;
        auto rect = draw_get_rect_chara(character_id);

        if (rect->height > inf_tiles)
        {
            item_rect = draw_get_rect_item(564); // Tall variant
        }
        else
        {
            item_rect = draw_get_rect_item(531); // Short variant
        }
        gsel(1);
        boxf(0, 960, item_rect->width, item_rect->height);

        // Modify color and restore it afterwards.
        set_color_mod(
            255 - c_col(0, character_color),
            255 - c_col(1, character_color),
            255 - c_col(2, character_color),
            rect->buffer);
        gcopy(
            rect->buffer,
            rect->x + 8,
            rect->y + 2,
            rect->width - 16,
            rect->height - 8,
            8,
            1058 - rect->height);
        set_color_mod(255, 255, 255, rect->buffer);

        gmode(2, 192);
        // Modify color and restore it afterwards.
        set_color_mod(
            255 - c_col(0, color),
            255 - c_col(1, color),
            255 - c_col(2, color),
            item_rect->buffer);
        gcopy(
            item_rect->buffer,
            item_rect->x,
            item_rect->y,
            inf_tiles,
            rect->height + (rect->height > inf_tiles) * 48,
            0,
            960 + (rect->height == inf_tiles) * 48);
        set_color_mod(255, 255, 255, item_rect->buffer);

        gmode(2);
        gsel(0);
    }

    return item_rect;
}



void show_hp_bar(HPBarSide side, int inf_clocky)
{
    const bool right = side == HPBarSide::right_side;

    int cnt{};
    for (int i = 1; i < 16; ++i)
    {
        auto& cc = cdata[i];
        if ((cc.state() == Character::State::alive ||
             cc.state() == Character::State::pet_dead) &&
            cdata[i].has_been_used_stethoscope())
        {
            const auto name = cdatan(0, i);
            const int x = 16 + (windoww - strlen_u(name) * 7 - 16) * right;
            int y = inf_clocky + (right ? 20 : 136) + cnt * 32;

            // If they are shown left side, move them below the skill
            // trackers.
            if (!right)
            {
                for (int i = 0; i < 10; ++i)
                {
                    if (game_data.tracked_skills.at(i) % 10000 != 0)
                    {
                        y += 16;
                    }
                }
            }

            bmes(
                name,
                x,
                y,
                cc.state() == Character::State::alive
                    ? snail::Color{255, 255, 255}
                    : snail::Color{255, 35, 35});
            if (cc.state() == Character::State::alive)
            {
                const int width = clamp(cc.hp * 30 / cc.max_hp, 1, 30);
                const int x_ = 16 + (windoww - 108) * right;
                const int y_ = y + 17;
                draw_bar("ally_health_bar", x_, y_, width * 3, 9, width);

                // Show leash icon.
                if (Config::instance().leash_icon && cdata[i].is_leashed())
                {
                    constexpr int leash = 631;
                    auto rect = prepare_item_image(leash, 2);
                    const int icon_width = rect->frame_width;
                    const int icon_height = rect->height;

                    gcopy(
                        1,
                        0,
                        960,
                        icon_width,
                        icon_height,
                        right ? std::min(x, x_) - icon_width / 2
                              : std::max(x_ + 90, int(x + strlen_u(name) * 7)),
                        y,
                        icon_width / 2,
                        icon_height / 2);
                    gmode(5);
                    gcopy(
                        1,
                        0,
                        960,
                        icon_width,
                        icon_height,
                        right ? std::min(x, x_) - icon_width / 2
                              : std::max(x_ + 90, int(x + strlen_u(name) * 7)),
                        y,
                        icon_width / 2,
                        icon_height / 2);
                    gmode(2);
                }
            }
            ++cnt;
        }
    }
}


void initialize_damage_popups()
{
    damage_popups_active = 0;
    damage_popups.resize(Config::instance().max_damage_popup);
}



void add_damage_popup(
    const std::string& text,
    int character,
    const snail::Color& color)
{
    damage_popups.resize(Config::instance().max_damage_popup);
    if (damage_popups_active == Config::instance().max_damage_popup)
    {
        // Substitute a new damage popup for popup whose frame is the maximum.
        auto oldest = std::max_element(
            std::begin(damage_popups),
            std::end(damage_popups),
            [](const auto& a, const auto& b) { return a.frame < b.frame; });
        oldest->frame = 0;
        oldest->text = text;
        oldest->character = character;
        oldest->color = color;
    }
    else
    {
        for (auto&& damage_popup : damage_popups)
        {
            if (damage_popup.frame == -1)
            {
                damage_popup.frame = 0;
                damage_popup.text = text;
                damage_popup.character = character;
                damage_popup.color = color;
                ++damage_popups_active;
                break;
            }
        }
    }
}


void clear_damage_popups()
{
    for (auto&& damage_popup : damage_popups)
    {
        damage_popup.frame = -1;
    }
    damage_popups_active = 0;
}


void show_damage_popups()
{
    if (Config::instance().damage_popup == 0)
    {
        return;
    }
    if (damage_popups_active == 0)
    {
        return;
    }

    for (auto&& damage_popup : damage_popups)
    {
        if (damage_popup.frame == -1)
        {
            continue;
        }

        const auto& cc = cdata[damage_popup.character];
        if (game_data.current_map != mdata_t::MapId::pet_arena)
        {
            if (!is_in_fov(cc.position))
            {
                ++damage_popup.frame;
                continue;
            }
            if (dist(
                    cdata.player().position.x,
                    cdata.player().position.y,
                    cc.position.x,
                    cc.position.y) > cdata.player().vision_distance / 2)
            {
                ++damage_popup.frame;
                continue;
            }
        }
        int mondmgpos{};
        for (auto&& damage_popup2 : damage_popups)
        {
            if (damage_popup2.frame == -1)
                continue;

            if (damage_popup.frame >= damage_popup2.frame)
            {
                if (cc.position == cdata[damage_popup2.character].position)
                {
                    ++mondmgpos;
                }
            }
        }

        int cfg_dmgfont = easing(damage_popup.frame / 10.0) * 20 + 12;

        int x = (cc.position.x - scx) * inf_tiles + inf_screenx -
            strlen_u(damage_popup.text) * (2 + cfg_dmgfont + 1) / 2 / 2 +
            inf_tiles / 2;
        int y = (cc.position.y - scy) * inf_tiles + inf_screeny -
            mondmgpos * (2 + cfg_dmgfont + 3) - 2 * damage_popup.frame;
        x += sxfix * (scx != scxbk) * (scrollp >= 3);
        y += syfix * (scy != scybk) * (scrollp >= 3);

        font(2 + cfg_dmgfont - en * 2);

        bmes(
            damage_popup.text,
            x,
            y,
            damage_popup.color,
            {static_cast<uint8_t>(damage_popup.color.r / 3),
             static_cast<uint8_t>(damage_popup.color.g / 3),
             static_cast<uint8_t>(damage_popup.color.b / 3)});

        ++damage_popup.frame;

        if (damage_popup.frame > 20)
        {
            damage_popup = {};
            --damage_popups_active;
        }
    }
}

void draw_emo(int cc, int x, int y)
{
    gmode(2);
    draw_indexed("emotion_icons", x + 16, y, cdata[cc].emotion_icon);
}



void load_pcc_part(int cc, int body_part, const char* body_part_str)
{
    const auto filepath = filesystem::dir::graphic() /
        (u8"pcc_"s + body_part_str + (pcc(body_part, cc) % 1000) + u8".bmp");
    if (!fs::exists(filepath))
        return;

    const auto texture_id =
        10 + PicLoader::max_buffers + TintedBuffers::max_buffers + cc;

    picload(filepath, 128, 0, false);
    boxf(256, 0, 128, 198);
    gmode(2);
    pget(128, 0);
    gcopy(texture_id, 128, 0, 128, 198, 256, 0);
    gmode(2);
    set_color_mod(
        255 - c_col(0, pcc(body_part, cc) / 1000),
        255 - c_col(1, pcc(body_part, cc) / 1000),
        255 - c_col(2, pcc(body_part, cc) / 1000),
        texture_id);
    gcopy(texture_id, 256, 0, 128, 198, 0, 0);
    set_color_mod(255, 255, 255, texture_id);
}



void set_pcc_depending_on_equipments(int cc, int ci)
{
    int item_appearance = the_item_db[inv[ci].id]->appearance;
    if (item_appearance == 0)
    {
        item_appearance = 1;
    }
    switch (iequiploc(ci))
    {
    case 3: pcc(4, cc) = item_appearance + inv[ci].color * 1000; break;
    case 4: pcc(2, cc) = item_appearance + inv[ci].color * 1000; break;
    case 7: pcc(8, cc) = item_appearance + inv[ci].color * 1000; break;
    case 8: pcc(5, cc) = item_appearance + inv[ci].color * 1000; break;
    case 9: pcc(3, cc) = item_appearance + inv[ci].color * 1000; break;
    default: break;
    }
}



optional_ref<const Extent> chara_preparepic(const Character& cc)
{
    return chara_preparepic(cc.image);
}



optional_ref<const Extent> chara_preparepic(int image_id)
{
    const auto chip_id = image_id % 1000;
    const auto color_id = image_id / 1000;
    const auto& chip = chara_chips[chip_id];
    const auto rect = draw_get_rect(chip.key);

    // TODO don't crash, and instead return a default.
    assert(rect);

    gsel(rect->buffer);
    boxf(0, 960, rect->width, rect->height);
    set_color_mod(
        255 - c_col(0, color_id),
        255 - c_col(1, color_id),
        255 - c_col(2, color_id));
    gcopy(rect->buffer, rect->x, rect->y, rect->width, rect->height, 0, 960);
    set_color_mod(255, 255, 255);
    gsel(0);
    return rect;
}



void create_pcpic(int cc, bool with_equipments)
{
    buffer(
        10 + PicLoader::max_buffers + TintedBuffers::max_buffers + cc,
        384,
        198);
    boxf();

    if (pcc(15, cc) == 0)
    {
        pcc(15, cc) = cdata[cc].sex + 1;
        pcc(14, cc) = cdata[cc].sex + 7;
        pcc(1, cc) = 2 + rnd(21) * 1000;
        pcc(9, cc) = 1 + rnd(21) * 1000;
        pcc(7, cc) = 1 + rnd(21) * 1000;
        pcc(16, cc) = 1;
    }

    if (with_equipments)
    {
        pcc(4, cc) = 0;
        pcc(2, cc) = 0;
        pcc(6, cc) = 0;
        pcc(3, cc) = 0;
        pcc(8, cc) = 0;
        pcc(5, cc) = 0;
        for (int i = 0; i < 30; ++i)
        {
            if (cdata[cc].body_parts[i] % 10000 != 0)
            {
                set_pcc_depending_on_equipments(
                    cc, cdata[cc].body_parts[i] % 10000 - 1);
            }
        }
    }

    pcc(10, cc) = pcc(1, cc) / 1000 * 1000 + pcc(10, cc) % 1000;
    pcc(14, cc) = pcc(15, cc) / 1000 * 1000 + pcc(14, cc) % 1000;
    if (with_equipments)
    {
        if (pcc(24, cc) == 0)
        {
            load_pcc_part(cc, 4, u8"mantle_");
        }
    }
    load_pcc_part(cc, 1, u8"hairbk_");
    if (cc == 0 && game_data.mount != 0 && pcc(16, cc) != 0)
    {
        load_pcc_part(cc, 16, u8"ridebk_");
    }
    else
    {
        load_pcc_part(cc, 15, u8"body_");
    }
    load_pcc_part(cc, 14, u8"eye_");
    if (cc != 0 || game_data.mount == 0 || pcc(16, cc) == 0)
    {
        load_pcc_part(cc, 7, u8"pants_");
    }
    load_pcc_part(cc, 9, u8"cloth_");
    if (with_equipments)
    {
        if (pcc(20, cc) == 0)
        {
            load_pcc_part(cc, 2, u8"chest_");
        }
        if ((cc != 0 || game_data.mount == 0 || pcc(16, cc) == 0) &&
            pcc(21, cc) == 0)
        {
            load_pcc_part(cc, 3, u8"leg_");
        }
        if (pcc(22, cc) == 0)
        {
            load_pcc_part(cc, 5, u8"belt_");
        }
        if (pcc(23, cc) == 0)
        {
            load_pcc_part(cc, 8, u8"glove_");
        }
    }
    if (cc == 0)
    {
        if (game_data.mount != 0)
        {
            load_pcc_part(cc, 16, u8"ride_");
        }
    }
    if (with_equipments)
    {
        if (pcc(24, cc) == 0)
        {
            load_pcc_part(cc, 4, u8"mantlebk_");
        }
    }
    load_pcc_part(cc, 1, u8"hair_");
    load_pcc_part(cc, 10, u8"subhair_");
    load_pcc_part(cc, 11, u8"etc_");
    load_pcc_part(cc, 12, u8"etc_");
    load_pcc_part(cc, 13, u8"etc_");

    gsel(0);
}



void initialize_map_chips(const MapChipDB& db)
{
    std::vector<PicLoader::MapType> predefined_extents;
    predefined_extents.resize(ChipData::atlas_count);
    tinted_buffers.clear();

    for (const auto& pair : db)
    {
        auto& id = pair.first;
        auto& data = pair.second;
        chip_data.add(data.atlas, id, data);
    }

    {
        for (int i = 0; i < ChipData::atlas_count; i++)
        {
            PicLoader::MapType extents_chips;
            PicLoader::MapType extents_feats;

            for (const auto& pair : chip_data.get_map(i))
            {
                const auto& chip = pair.second;
                auto type = PicLoader::PageType::map_chip;
                if (chip.is_feat)
                {
                    type = PicLoader::PageType::map_feat;
                }

                if (chip.filepath)
                {
                    // chip is from an external file.
                    loader.load(*chip.filepath, chip.key, type);
                }
                else
                {
                    // chip is located in item.bmp.
                    if (chip.is_feat)
                    {
                        extents_feats[chip.key] = chip.source;
                    }
                    else
                    {
                        extents_chips[chip.key] = chip.source;
                    }
                }
            }

            loader.add_predefined_extents(
                filesystem::dir::graphic() / (u8"map"s + i + ".bmp"),
                extents_chips,
                PicLoader::PageType::map_chip);

            loader.add_predefined_extents(
                filesystem::dir::graphic() / (u8"map"s + i + ".bmp"),
                extents_feats,
                PicLoader::PageType::map_feat);
        }
    }
    for (const auto& buffer :
         loader.get_buffers_of_type(PicLoader::PageType::map_chip))
    {
        tinted_buffers.reserve_tinted_buffer(buffer);
    }
    for (const auto& buffer :
         loader.get_buffers_of_type(PicLoader::PageType::map_feat))
    {
        tinted_buffers.reserve_tinted_buffer(buffer);
    }
}



static int _get_map_chip_shadow()
{
    int shadow = 5;

    if (map_data.indoors_flag == 2)
    {
        if (game_data.date.hour >= 24 ||
            (game_data.date.hour >= 0 && game_data.date.hour < 4))
        {
            shadow = 110;
        }
        if (game_data.date.hour >= 4 && game_data.date.hour < 10)
        {
            shadow = std::min(10, 70 - (game_data.date.hour - 3) * 10);
        }
        if (game_data.date.hour >= 10 && game_data.date.hour < 12)
        {
            shadow = 10;
        }
        if (game_data.date.hour >= 12 && game_data.date.hour < 17)
        {
            shadow = 1;
        }
        if (game_data.date.hour >= 17 && game_data.date.hour < 21)
        {
            shadow = (game_data.date.hour - 17) * 20;
        }
        if (game_data.date.hour >= 21 && game_data.date.hour < 24)
        {
            shadow = 80 + (game_data.date.hour - 21) * 10;
        }
        if (game_data.weather == 3 && shadow < 40)
        {
            shadow = 40;
        }
        if (game_data.weather == 4 && shadow < 65)
        {
            shadow = 65;
        }
        if (game_data.current_map == mdata_t::MapId::noyel &&
            (game_data.date.hour >= 17 || game_data.date.hour < 7))
        {
            shadow += 35;
        }
    }

    return shadow;
}



void draw_prepare_map_chips()
{
    map_tileset(map_data.tileset);

    int shadow = _get_map_chip_shadow();
    snail::Color color{(uint8_t)(255 - shadow)};

    bool changed = false;

    gmode(0);
    for (const auto& buffer :
         loader.get_buffers_of_type(PicLoader::PageType::map_chip))
    {
        changed |= tinted_buffers.tint(buffer, color);
    }

    if (changed)
    {
        for (const auto& buffer :
             loader.get_buffers_of_type(PicLoader::PageType::map_feat))
        {
            gmode(0);
            tinted_buffers.tint(buffer, color);
            gmode(2, 30);
            tinted_buffers.tint(buffer, snail::Color{255}, true);
        }
    }

    gmode(0);

    // Contains the sprites for world map clouds.
    asset_load("map");

    gsel(0);
    gmode(2);
}



void initialize_item_chips(const ItemChipDB& db)
{
    PicLoader::MapType predefined_extents;

    for (const auto& chip_data : db.values())
    {
        SharedId key = chip_data.chip.key;
        int legacy_id = chip_data.legacy_id;

        // insert chip data into global vector.
        if (static_cast<int>(item_chips.size()) < legacy_id)
        {
            item_chips.resize(legacy_id + 1);
        }
        item_chips[legacy_id] = chip_data.chip;

        if (chip_data.filepath)
        {
            // chip is from an external file.
            loader.load(*chip_data.filepath, key, PicLoader::PageType::item);
        }
        else
        {
            // chip is located in item.bmp.
            predefined_extents[key] = chip_data.rect;
        }
    }

    loader.add_predefined_extents(
        filesystem::dir::graphic() / u8"item.bmp",
        predefined_extents,
        PicLoader::PageType::item);
}



void initialize_portraits(const PortraitDB& db)
{
    PicLoader::MapType predefined_extents;

    for (const auto& portrait_data : db.values())
    {
        SharedId key = portrait_data.key;

        if (portrait_data.filepath)
        {
            // Portrait is from an external file.
            loader.load(
                *portrait_data.filepath, key, PicLoader::PageType::portrait);
        }
        else
        {
            // Portrait is located in face1.bmp.
            predefined_extents[key] = portrait_data.rect;
        }
    }

    loader.add_predefined_extents(
        filesystem::dir::graphic() / u8"face1.bmp",
        predefined_extents,
        PicLoader::PageType::portrait);
}



void initialize_chara_chips(const CharaChipDB& db)
{
    PicLoader::MapType predefined_extents;

    for (const auto& chip_data : db.values())
    {
        SharedId key = chip_data.chip.key;
        int legacy_id = chip_data.legacy_id;

        // Insert chip data into global vector.
        if (static_cast<int>(chara_chips.size()) < legacy_id)
        {
            chara_chips.resize(legacy_id + 1);
        }
        chara_chips[legacy_id] = chip_data.chip;

        if (chip_data.filepath)
        {
            // Chip is from an external file.
            loader.load(
                *chip_data.filepath, key, PicLoader::PageType::character);
        }
        else
        {
            // Chip is located in character.bmp.
            predefined_extents[key] = chip_data.rect;
        }
    }

    loader.add_predefined_extents(
        filesystem::dir::graphic() / u8"character.bmp",
        predefined_extents,
        PicLoader::PageType::character);
}


void draw_clear_loaded_chips()
{
    loader.clear();
}


void initialize_all_chips()
{
    initialize_mef();
    SDIM3(tname, 16, 11);
    tname(1) = i18n::s.get("core.locale.item.chip.dryrock");
    tname(2) = i18n::s.get("core.locale.item.chip.field");
    draw_prepare_map_chips();
}



/**
 * Prepares a buffer of selection key sprites at [72, 30] in window 3.
 */
void draw_init_key_select_buffer()
{
    int buffer_bk = ginfo(3);
    gsel(3);
    for (int i = 0; i < 18; ++i)
    {
        draw_select_key(key_select(i), i * 24 + 72, 30);
    }
    gsel(buffer_bk);
}



void draw_select_key(const std::string& key, int x, int y)
{
    gmode(0);
    font(13);
    draw("select_key", x, y);
    const auto& image_info = get_image_info("select_key");
    const auto glyph_size =
        snail::Application::instance().get_renderer().calculate_text_size(key);
    bmes(
        key,
        x + (image_info.width - glyph_size.width) / 2 - 2,
        y + (image_info.height - glyph_size.height) / 2,
        {250, 240, 230},
        {50, 60, 80});
    gmode(2);
}



/**
 * Draws text with a shadow.
 */
void bmes(
    const std::string& message,
    int x,
    int y,
    const snail::Color& text_color,
    const snail::Color& shadow_color)
{
    auto&& r = snail::Application::instance().get_renderer();
    r.render_text_with_shadow(message, x, y, text_color, shadow_color);
}

/**
 * Draws a character using its @a image field.
 */
void draw_chara(const Character& chara, int x, int y, int scale, int alpha)
{
    draw_chara(chara.image, x, y, scale, alpha);
}

/**
 * Draws a character sprite.
 */
void draw_chara(int image_id, int x, int y, int scale, int alpha)
{
    auto rect = chara_preparepic(image_id);
    if (alpha != 0)
    {
        gmode(2, alpha);
    }
    else
    {
        gmode(2);
    }

    gcopy_c(
        rect->buffer,
        0,
        960,
        rect->width,
        rect->height,
        x,
        y,
        rect->width * scale,
        rect->height * scale);
}

/**
 * Draws a character using its @a image field. Fits the sprite to @ref
 * inf_tiles height if it is tall.
 */
void draw_chara_scale_height(const Character& chara, int x, int y)
{
    draw_chara_scale_height(chara.image, x, y);
}

/**
 * Draws a character sprite. Fits the sprite to @ref inf_tiles height if it
 * is tall.
 */
void draw_chara_scale_height(int image_id, int x, int y)
{
    auto rect = chara_preparepic(image_id);
    gmode(2);

    gcopy_c(
        rect->buffer,
        0,
        960,
        rect->width,
        rect->height,
        x,
        y,
        rect->width / (1 + (rect->height > inf_tiles)),
        inf_tiles);
}

/**
 * Draws an item sprite. For use inside the materials menu.
 */
void draw_item_material(int image_id, int x, int y)
{
    auto rect = prepare_item_image(image_id, 0);

    gmode(2);

    gcopy_c(
        1, 0, 960, inf_tiles, inf_tiles, x, y, rect->frame_width, rect->height);
}

/**
 * Draws an item with a character sprite on top, for cards/figures.
 */
void draw_item_with_portrait(const Item& item, int x, int y)
{
    draw_item_with_portrait(item.image, item.color, item.param1, x, y);
}

/**
 * Draws an item with a character sprite on top, for cards/figures.
 */
void draw_item_with_portrait(
    int image_id,
    int color,
    optional<int> chara_chip_id,
    int x,
    int y)
{
    optional_ref<const Extent> rect;

    if (chara_chip_id)
    {
        rect = prepare_item_image(image_id, color, *chara_chip_id);
    }
    else
    {
        rect = prepare_item_image(image_id, color);
    }

    gmode(2);

    gcopy_c(
        1, 0, 960, inf_tiles, inf_tiles, x, y, rect->frame_width, rect->height);
}

/**
 * Draws an item sprite with a character sprite on top, for cards/figures.
 * Fits the sprite to @ref inf_tiles height if it is tall.
 */
void draw_item_with_portrait_scale_height(const Item& item, int x, int y)
{
    draw_item_with_portrait_scale_height(
        item.image, item.color, item.param1, x, y);
}

/**
 * Draws an item sprite with a character sprite on top, for cards/figures.
 * Fits the sprite to @ref inf_tiles height if it is tall.
 */
void draw_item_with_portrait_scale_height(
    int image_id,
    int color,
    optional<int> chara_chip_id,
    int x,
    int y)
{
    optional_ref<const Extent> rect;

    if (chara_chip_id)
    {
        rect = prepare_item_image(image_id, color, *chara_chip_id);
    }
    else
    {
        rect = prepare_item_image(image_id, color);
    }

    gmode(2);

    gcopy_c(
        1,
        0,
        960,
        rect->frame_width,
        rect->height,
        x,
        y,
        rect->frame_width * inf_tiles / rect->height,
        inf_tiles);
}


void draw_map_tile(int id, int x, int y, int anim_frame)
{
    draw_map_tile(
        id, x, y, inf_tiles, inf_tiles, inf_tiles, inf_tiles, anim_frame);
}


void draw_map_tile(int id, int x, int y, int width, int height, int anim_frame)
{
    draw_map_tile(id, x, y, width, height, width, height, anim_frame);
}


void draw_map_tile(
    int id,
    int x,
    int y,
    int width,
    int height,
    int dst_width,
    int dst_height,
    int anim_frame)
{
    const auto& chip = chip_data[id];
    auto rect = draw_get_rect(chip.key);
    auto tinted_buffer = tinted_buffers.get_tinted_buffer(rect->buffer);
    assert(tinted_buffer);

    gcopy(
        *tinted_buffer,
        rect->x + anim_frame * width,
        rect->y,
        width,
        height,
        x,
        y,
        dst_width,
        dst_height);
}


} // namespace elona

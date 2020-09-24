#include "draw.hpp"

#include <cmath>

#include "../snail/application.hpp"
#include "character.hpp"
#include "config.hpp"
#include "data/types/type_asset.hpp"
#include "data/types/type_chara_chip.hpp"
#include "data/types/type_item.hpp"
#include "data/types/type_item_chip.hpp"
#include "data/types/type_map_chip.hpp"
#include "data/types/type_portrait.hpp"
#include "elona.hpp"
#include "fov.hpp"
#include "game.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "map.hpp"
#include "mapgen.hpp"
#include "mef.hpp"
#include "pic_loader/extent.hpp"
#include "pic_loader/pic_loader.hpp"
#include "pic_loader/tinted_buffers.hpp"
#include "random.hpp"
#include "ui.hpp"
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



void _set_pcc_depending_on_equipments(
    Character& chara,
    const ItemRef& equipment)
{
    int item_appearance = the_item_db[equipment->id]->appearance;
    if (item_appearance == 0)
    {
        item_appearance = 1;
    }

    const auto body_part_id = iequiploc(equipment);
    if (body_part_id == "core.back")
    {
        pcc(4, chara.index) =
            item_appearance + color_to_color_index(equipment->tint) * 1000;
    }
    else if (body_part_id == "core.body")
    {
        pcc(2, chara.index) =
            item_appearance + color_to_color_index(equipment->tint) * 1000;
    }
    else if (body_part_id == "core.arm")
    {
        pcc(8, chara.index) =
            item_appearance + color_to_color_index(equipment->tint) * 1000;
    }
    else if (body_part_id == "core.waist")
    {
        pcc(5, chara.index) =
            item_appearance + color_to_color_index(equipment->tint) * 1000;
    }
    else if (body_part_id == "core.leg")
    {
        pcc(3, chara.index) =
            item_appearance + color_to_color_index(equipment->tint) * 1000;
    }
}



void _load_pcc_part(Character& chara, int body_part, const char* body_part_str)
{
    const auto idx = chara.index;

    const auto filepath = filesystem::dirs::graphic() /
        fs::u8path(u8"pcc_"s + body_part_str + (pcc(body_part, idx) % 1000) +
                   u8".bmp");
    if (!fs::exists(filepath))
        return;

    const auto texture_id =
        10 + PicLoader::max_buffers + TintedBuffers::max_buffers + idx;

    picload(filepath, 128, 0, false);
    boxf(256, 0, 128, 198);
    gmode(2);
    pget(128, 0);
    gcopy(texture_id, 128, 0, 128, 198, 256, 0);
    gmode(2);
    set_color_mod(
        255 - c_col(0, pcc(body_part, idx) / 1000),
        255 - c_col(1, pcc(body_part, idx) / 1000),
        255 - c_col(2, pcc(body_part, idx) / 1000),
        texture_id);
    gcopy(texture_id, 256, 0, 128, 198, 0, 0);
    set_color_mod(255, 255, 255, texture_id);
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
    return draw_get_rect(
        data::make_fqid("core.portrait", data::InstanceId{key}));
}



optional_ref<const Extent> draw_get_rect(data::FullyQualifiedId id)
{
    return loader[id];
}



optional_ref<const Extent> prepare_item_image(int id, int color_index)
{
    return prepare_item_image(id, color_index_to_color(color_index));
}



/**
 * Applies a color to the item sprite of ID @a id and copies it to the scratch
 * window (ID 1) at coordinates [0, 960], so it can be copied with @ref gcopy.
 */
optional_ref<const Extent> prepare_item_image(int id, const Color& color)
{
    const auto rect = draw_get_rect_item(id);

    gsel(1);
    boxf(0, 960, rect->width, rect->height);

    // The color modifier is applied to the source buffer before
    // copying it to the scratch region. It is restored after copying.
    set_color_mod(color.r, color.g, color.b, rect->buffer);
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
prepare_item_image(int id, const Color& color, int character_image)
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
        set_color_mod(color.r, color.g, color.b, item_rect->buffer);
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
        set_color_mod(color.r, color.g, color.b, item_rect->buffer);
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
    for (const auto& ally : cdata.allies())
    {
        if ((ally.state() == Character::State::alive ||
             ally.state() == Character::State::pet_dead) &&
            ally.has_been_used_stethoscope())
        {
            const auto name = ally.name;
            const int x = 16 + (windoww - strlen_u(name) * 7 - 16) * right;
            int y = inf_clocky + (right ? 20 : 136) + cnt * 32;

            // If they are shown left side, move them below the skill
            // trackers.
            if (!right)
            {
                for (int i = 0; i < 10; ++i)
                {
                    if (game()->tracked_skills.at(i) % 10000 != 0)
                    {
                        y += 16;
                    }
                }
            }

            bmes(
                name,
                x,
                y,
                ally.state() == Character::State::alive
                    ? snail::Color{255, 255, 255}
                    : snail::Color{255, 35, 35});
            if (ally.state() == Character::State::alive)
            {
                const int width = clamp(ally.hp * 30 / ally.max_hp, 1, 30);
                const int x_ = 16 + (windoww - 108) * right;
                const int y_ = y + 17;
                draw_bar("core.ally_health_bar", x_, y_, width * 3, 9, width);

                // Show leash icon.
                if (g_config.leash_icon() && ally.is_leashed())
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
    damage_popups.resize(g_config.max_damage_popup());
}



void add_damage_popup(
    const std::string& text,
    int character,
    const snail::Color& color)
{
    damage_popups.resize(g_config.max_damage_popup());
    if (damage_popups_active == g_config.max_damage_popup())
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
    if (g_config.damage_popup() == 0)
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

        const auto& chara = cdata[damage_popup.character];
        if (game()->current_map != mdata_t::MapId::pet_arena)
        {
            if (!is_in_fov(chara.position))
            {
                ++damage_popup.frame;
                continue;
            }
            if (dist(cdata.player().position, chara.position) >
                cdata.player().vision_distance / 2)
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
                if (chara.position == cdata[damage_popup2.character].position)
                {
                    ++mondmgpos;
                }
            }
        }

        int cfg_dmgfont = easing(damage_popup.frame / 10.0) * 20 + 12;

        int x = (chara.position.x - scx) * inf_tiles + inf_screenx -
            strlen_u(damage_popup.text) * (2 + cfg_dmgfont + 1) / 2 / 2 +
            inf_tiles / 2;
        int y = (chara.position.y - scy) * inf_tiles + inf_screeny -
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



void draw_emo(const Character& chara, int x, int y)
{
    gmode(2);
    draw_indexed("core.emotion_icons", x + 16, y, chara.emotion_icon);
}



optional_ref<const Extent> chara_preparepic(const Character& chara)
{
    return chara_preparepic(chara.image);
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



void create_pcpic(Character& chara, bool with_equipments)
{
    const auto idx = chara.index;

    buffer(
        10 + PicLoader::max_buffers + TintedBuffers::max_buffers + idx,
        384,
        198);
    boxf();

    if (pcc(15, idx) == 0)
    {
        pcc(15, idx) = chara.sex + 1;
        pcc(14, idx) = chara.sex + 7;
        pcc(1, idx) = 2 + rnd(21) * 1000;
        pcc(9, idx) = 1 + rnd(21) * 1000;
        pcc(7, idx) = 1 + rnd(21) * 1000;
        pcc(16, idx) = 1;
    }

    if (with_equipments)
    {
        pcc(4, idx) = 0;
        pcc(2, idx) = 0;
        pcc(6, idx) = 0;
        pcc(3, idx) = 0;
        pcc(8, idx) = 0;
        pcc(5, idx) = 0;
        for (const auto& body_part : chara.body_parts)
        {
            if (body_part.is_equip())
            {
                _set_pcc_depending_on_equipments(
                    chara, body_part.equipment().unwrap());
            }
        }
    }

    pcc(10, idx) = pcc(1, idx) / 1000 * 1000 + pcc(10, idx) % 1000;
    pcc(14, idx) = pcc(15, idx) / 1000 * 1000 + pcc(14, idx) % 1000;
    if (with_equipments)
    {
        if (pcc(24, idx) == 0)
        {
            _load_pcc_part(chara, 4, u8"mantle_");
        }
    }
    _load_pcc_part(chara, 1, u8"hairbk_");
    if (idx == 0 && game()->mount != 0 && pcc(16, idx) != 0)
    {
        _load_pcc_part(chara, 16, u8"ridebk_");
    }
    else
    {
        _load_pcc_part(chara, 15, u8"body_");
    }
    _load_pcc_part(chara, 14, u8"eye_");
    if (idx != 0 || game()->mount == 0 || pcc(16, idx) == 0)
    {
        _load_pcc_part(chara, 7, u8"pants_");
    }
    _load_pcc_part(chara, 9, u8"cloth_");
    if (with_equipments)
    {
        if (pcc(20, idx) == 0)
        {
            _load_pcc_part(chara, 2, u8"chest_");
        }
        if ((idx != 0 || game()->mount == 0 || pcc(16, idx) == 0) &&
            pcc(21, idx) == 0)
        {
            _load_pcc_part(chara, 3, u8"leg_");
        }
        if (pcc(22, idx) == 0)
        {
            _load_pcc_part(chara, 5, u8"belt_");
        }
        if (pcc(23, idx) == 0)
        {
            _load_pcc_part(chara, 8, u8"glove_");
        }
    }
    if (idx == 0)
    {
        if (game()->mount != 0)
        {
            _load_pcc_part(chara, 16, u8"ride_");
        }
    }
    if (with_equipments)
    {
        if (pcc(24, idx) == 0)
        {
            _load_pcc_part(chara, 4, u8"mantlebk_");
        }
    }
    _load_pcc_part(chara, 1, u8"hair_");
    _load_pcc_part(chara, 10, u8"subhair_");
    _load_pcc_part(chara, 11, u8"etc_");
    _load_pcc_part(chara, 12, u8"etc_");
    _load_pcc_part(chara, 13, u8"etc_");

    gsel(0);
}



void initialize_map_chips(const MapChipDB& db)
{
    std::vector<PicLoader::MapType> predefined_extents;
    predefined_extents.resize(ChipData::atlas_count);
    tinted_buffers.clear();

    for (const auto& data : db.values())
    {
        auto& atlas = chip_data.get_map(data.atlas);

        atlas[data.integer_id] = data;
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
                filesystem::dirs::graphic() / fs::u8path(u8"map"s + i + ".bmp"),
                extents_chips,
                PicLoader::PageType::map_chip);

            loader.add_predefined_extents(
                filesystem::dirs::graphic() / fs::u8path(u8"map"s + i + ".bmp"),
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
        const auto h = game_time().hour();
        if (h < 4)
        {
            shadow = 110;
        }
        else if (h < 10)
        {
            shadow = std::min(10, 70 - (h - 3) * 10);
        }
        else if (h < 12)
        {
            shadow = 10;
        }
        else if (h < 17)
        {
            shadow = 1;
        }
        else if (h < 21)
        {
            shadow = (h - 17) * 20;
        }
        else
        {
            shadow = 80 + (h - 21) * 10;
        }
        if (game()->weather == "core.rain" && shadow < 40)
        {
            shadow = 40;
        }
        if (game()->weather == "core.hard_rain" && shadow < 65)
        {
            shadow = 65;
        }
        if (game()->current_map == mdata_t::MapId::noyel && (h >= 17 || h < 7))
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
    asset_load("core.map");

    gsel(0);
    gmode(2);
}



void initialize_item_chips(const ItemChipDB& db)
{
    PicLoader::MapType predefined_extents;

    for (const auto& chip_data : db.values())
    {
        const auto key = chip_data.chip.key;
        int integer_id = chip_data.integer_id;

        // insert chip data into global vector.
        if (static_cast<int>(item_chips.size()) < integer_id)
        {
            item_chips.resize(integer_id + 1);
        }
        item_chips[integer_id] = chip_data.chip;

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
        filesystem::dirs::graphic() / u8"item.bmp",
        predefined_extents,
        PicLoader::PageType::item);
}



void initialize_portraits(const PortraitDB& db)
{
    PicLoader::MapType predefined_extents;

    for (const auto& portrait_data : db.values())
    {
        const auto key = portrait_data.key;

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
        filesystem::dirs::graphic() / u8"face1.bmp",
        predefined_extents,
        PicLoader::PageType::portrait);
}



void initialize_chara_chips(const CharaChipDB& db)
{
    PicLoader::MapType predefined_extents;

    for (const auto& chip_data : db.values())
    {
        const auto key = chip_data.chip.key;
        int integer_id = chip_data.integer_id;

        // Insert chip data into global vector.
        if (static_cast<int>(chara_chips.size()) < integer_id)
        {
            chara_chips.resize(integer_id + 1);
        }
        chara_chips[integer_id] = chip_data.chip;

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
        filesystem::dirs::graphic() / u8"character.bmp",
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
    draw("core.select_key", x, y);
    const auto& image_info = get_image_info("core.select_key");
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
    auto rect = prepare_item_image(image_id);

    gmode(2);

    gcopy_c(
        1, 0, 960, inf_tiles, inf_tiles, x, y, rect->frame_width, rect->height);
}

/**
 * Draws an item with a character sprite on top, for cards/figures.
 */
void draw_item_with_portrait(const ItemRef& item, int x, int y)
{
    draw_item_with_portrait(item->image, item->tint, item->param1, x, y);
}

/**
 * Draws an item with a character sprite on top, for cards/figures.
 */
void draw_item_with_portrait(
    int image_id,
    const Color& color,
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
void draw_item_with_portrait_scale_height(const ItemRef& item, int x, int y)
{
    draw_item_with_portrait_scale_height(
        item->image, item->tint, item->param1, x, y);
}

/**
 * Draws an item sprite with a character sprite on top, for cards/figures.
 * Fits the sprite to @ref inf_tiles height if it is tall.
 */
void draw_item_with_portrait_scale_height(
    int image_id,
    const Color& color,
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



void draw_sleep_background_frame()
{
    gcopy(4, 0, 0, windoww, windowh - inf_verh, 0, 0);
    gmode(2);
    render_hud();
    if (screenupdate == 0)
    {
        redraw();
    }
    screenupdate = 0;
}



void load_sleep_background()
{
    gmode(0);
    asset_load("core.bg_night");
    draw("core.bg_night", 0, 0, windoww, windowh - inf_verh);
    gsel(0);
}

} // namespace elona

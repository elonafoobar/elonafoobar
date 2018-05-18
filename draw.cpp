#include "draw.hpp"
#include <cmath>
#include "character.hpp"
#include "config.hpp"
#include "elona.hpp"
#include "fov.hpp"
#include "item.hpp"
#include "item_db.hpp"
#include "map.hpp"
#include "mef.hpp"
#include "variables.hpp"


namespace
{


// TODO: it should be configurable.
constexpr size_t max_damage_popups = 20; // compatible with oomEx

struct damage_popup_t
{
    int frame;
    std::string text;
    int character;
    snail::color color;


    damage_popup_t(
        const std::string& text,
        int character,
        const snail::color& color)
        : frame(0)
        , text(text)
        , character(character)
        , color(color)
    {
    }
};


std::vector<damage_popup_t> damage_popups;



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


void prepare_item_image(int id, int color)
{
    const auto x = chipi(0, id);
    const auto y = chipi(1, id);
    const auto w = chipi(2, id);
    const auto h = chipi(3, id);

    gsel(1);
    boxf(0, 960, w, h + 960);

    pos(0, 960);
    set_color_mod(
        255 - c_col(0, color), 255 - c_col(1, color), 255 - c_col(2, color));
    gcopy(1, x, y, w, h);
    set_color_mod(255, 255, 255);
    gfini(w, h);
    gfdec2(c_col(0, color), c_col(1, color), c_col(2, color));
    gsel(0);
}



void prepare_item_image(int id, int color, int character_image)
{
    if (id != 528 && id != 531)
    {
        prepare_item_image(id, color);
        return;
    }

    const auto w = chipi(2, id);
    const auto h = chipi(3, id);

    gsel(1);
    boxf(0, 960, w, h + 960);

    if (id == 528) // Cards
    {
        const auto character_id = character_image % 1000;
        const auto character_color = character_image / 1000;
        gmode(2);
        pos(0, 960);
        set_color_mod(
            255 - c_col(0, color),
            255 - c_col(1, color),
            255 - c_col(2, color));
        gcopy(1, 0, 768, inf_tiles, inf_tiles);
        set_color_mod(255, 255, 255);
        pos(0, 1008);
        set_color_mod(
            255 - c_col(0, character_color),
            255 - c_col(1, character_color),
            255 - c_col(2, character_color),
            5);
        gzoom(
            5,
            chipc(0, character_id) + 8,
            chipc(1, character_id) + 4
                + (chipc(3, character_id) > inf_tiles) * 8,
            chipc(2, character_id) - 16,
            chipc(3, character_id) - 8
                - (chipc(3, character_id) > inf_tiles) * 10,
            22,
            20);
        set_color_mod(255, 255, 255, 5);
        pos(6, 974);
        gcopy(1, 0, 1008, 22, 20);
        gsel(0);
    }
    else // Figures
    {
        const auto character_id = character_image % 1000;
        const auto character_color = character_image / 1000;
        pos(8, 1058 - chipc(3, character_id));
        set_color_mod(
            255 - c_col(0, character_color),
            255 - c_col(1, character_color),
            255 - c_col(2, character_color),
            5);
        gcopy(
            5,
            chipc(0, character_id) + 8,
            chipc(1, character_id) + 2,
            chipc(2, character_id) - 16,
            chipc(3, character_id) - 8);
        set_color_mod(255, 255, 255, 5);
        gmode(4, -1, -1, 192);
        pos(0, 960 + (chipc(3, character_id) == inf_tiles) * 48);
        set_color_mod(
            255 - c_col(0, color),
            255 - c_col(1, color),
            255 - c_col(2, color));
        gcopy(
            1,
            144,
            768 + (chipc(3, character_id) > inf_tiles) * 48,
            inf_tiles,
            chipc(3, character_id) + (chipc(3, character_id) > inf_tiles) * 48);
        set_color_mod(255, 255, 255);
        gmode(2);
        gsel(0);
    }
}



void show_hp_bar(show_hp_bar_side side, int inf_clocky)
{
    const bool right = side == show_hp_bar_side::right_side;

    int cnt{};
    for (int i = 1; i < 16; ++i)
    {
        auto& cc = cdata[i];
        if ((cc.state == 1 || cc.state == 6)
            && cdata[i].has_been_used_stethoscope())
        {
            const auto name = cdatan(0, i);
            const int x = 16 + (windoww - strlen_u(name) * 7 - 16) * right;
            const int y = inf_clocky + 200 - 180 * right + cnt * 32;
            // std::cout << "HP bar(" << i << "):name: " << position_t{x, y} <<
            // std::endl;
            pos(x, y);
            color(0, 0, 0);
            const auto color = cc.state == 1 ? snail::color{255, 255, 255}
                                             : snail::color{255, 35, 35};
            bmes(name, color.r, color.g, color.b);
            if (cc.state == 1)
            {
                const int width = clamp(cc.hp * 30 / cc.max_hp, 1, 30);
                const int x_ = 16 + (windoww - 108) * right;
                const int y_ = y + 17;
                // std::cout << "HP bar(" << i << "):bar:  " << position_t{x_,
                // y_} << std::endl;
                pos(x_, y_);
                gzoom(3, 480 - width, 517, width, 3, width * 3, 9);

                // Show leash icon.
                if (config::instance().leash_icon && cdata[i].is_leashed())
                {
                    constexpr int leash = 631;
                    prepare_item_image(leash, 2);
                    const int icon_width = chipi(2, leash);
                    const int icon_height = chipi(3, leash);

                    pos(right ? std::min(x, x_) - icon_width / 2
                              : std::max(x_ + 90, int(x + strlen_u(name) * 7)),
                        y);
                    gzoom(
                        1,
                        0,
                        960,
                        icon_width,
                        icon_height,
                        icon_width / 2,
                        icon_height / 2,
                        true);
                    gmode(5);
                    gzoom(
                        1,
                        0,
                        960,
                        icon_width,
                        icon_height,
                        icon_width / 2,
                        icon_height / 2,
                        true);
                    gmode(2);
                }
            }
            ++cnt;
        }
    }
}



void add_damage_popup(
    const std::string& text,
    int character,
    const snail::color& color)
{
    if (damage_popups.size() == max_damage_popups)
    {
        // Substitute a new damage popup for popup whose frame is the maximum.
        auto oldest = std::max_element(
            std::begin(damage_popups),
            std::end(damage_popups),
            [](const auto& a, const auto& b) { return a.frame < b.frame; });
        *oldest = damage_popup_t{text, character, color};
    }
    else
    {
        damage_popups.emplace_back(text, character, color);
    }
}


void clear_damage_popups()
{
    damage_popups.clear();
}


void show_damage_popups(int inf_ver)
{
    for (auto&& damage_popup : damage_popups)
    {
        const auto& cc = cdata[damage_popup.character];
        if (gdata(20) != 40)
        {
            if (!is_in_fov(cc.position))
            {
                ++damage_popup.frame;
                continue;
            }
            if (dist(
                    cdata[0].position.x,
                    cdata[0].position.y,
                    cc.position.x,
                    cc.position.y)
                > cdata[0].vision_distance / 2)
            {
                ++damage_popup.frame;
                continue;
            }
        }
        int mondmgpos{};
        for (auto&& damage_popup2 : damage_popups)
        {
            if (damage_popup.frame >= damage_popup2.frame)
            {
                if (cc.position == cdata[damage_popup2.character].position)
                {
                    ++mondmgpos;
                }
            }
        }

        int cfg_dmgfont = easing(damage_popup.frame / 10.0) * 20 + 12;

        int x = (cc.position.x - scx) * inf_tiles + inf_screenx
            - strlen_u(damage_popup.text) * (2 + cfg_dmgfont + 1) / 2 / 2
            + inf_tiles / 2;
        int y = (cc.position.y - scy) * inf_tiles + inf_screeny
            - mondmgpos * (2 + cfg_dmgfont + 3) - 2 * damage_popup.frame;
        x += sxfix * (scx != scxbk) * (scrollp >= 3);
        y += syfix * (scy != scybk) * (scrollp >= 3);

        font(2 + cfg_dmgfont - en * 2);
        pos(x, y);
        color(damage_popup.color.r, damage_popup.color.g, damage_popup.color.b);
        bmes(damage_popup.text, 255, 255, 255);
        color(0, 0, 0);

        ++damage_popup.frame;
    }
    damage_popups.erase(
        std::remove_if(
            std::begin(damage_popups),
            std::end(damage_popups),
            [](const auto& d) { return d.frame > 20; }),
        std::end(damage_popups));
}

void draw_emo(int cc, int x, int y)
{
    gmode(2, 16, 16);
    pos(x + 16, y);
    gcopy(3, 32 + cdata[cc].emotion_icon % 100 * 16, 608);
}



void load_pcc_part(int cc, int body_part, const char* body_part_str)
{
    const auto filepath = filesystem::dir::graphic()
        / (u8"pcc_"s + body_part_str + (pcc(body_part, cc) % 1000) + u8".bmp");
    if (!fs::exists(filepath))
        return;

    pos(128, 0);
    picload(filepath, 1);
    boxf(256, 0, 384, 198);
    gmode(4, -1, -1, 256);
    pget(128, 0);
    pos(256, 0);
    gcopy(10 + cc, 128, 0, 128, 198);
    pos(256, 0);
    gfini(128, 198);
    gfdec2(
        c_col(0, pcc(body_part, cc) / 1000),
        c_col(1, pcc(body_part, cc) / 1000),
        c_col(2, pcc(body_part, cc) / 1000));
    gmode(2);
    pos(0, 0);
    set_color_mod(
            255 - c_col(0, pcc(body_part, cc) / 1000),
            255 - c_col(1, pcc(body_part, cc) / 1000),
            255 - c_col(2, pcc(body_part, cc) / 1000),
            10 + cc);
    gcopy(10 + cc, 256, 0, 128, 198);
    set_color_mod(255, 255, 255, 10 + cc);
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


void chara_preparepic(int prm_618, int prm_619)
{
    int p_at_m83 = 0;
    if (prm_619 == 0)
    {
        p_at_m83 = prm_618 / 1000;
    }
    else
    {
        p_at_m83 = prm_619;
    }
    gsel(5);
    boxf(0, 960, chipc(2, prm_618), chipc(3, prm_618) + 960);
    pos(0, 960);
    set_color_mod(
        255 - c_col(0, p_at_m83),
        255 - c_col(1, p_at_m83),
        255 - c_col(2, p_at_m83));
    gcopy(
        5,
        chipc(0, prm_618),
        chipc(1, prm_618),
        chipc(2, prm_618),
        chipc(3, prm_618));
    set_color_mod(255, 255, 255);
    gfini(chipc(2, prm_618), chipc(3, prm_618));
    gfdec2(c_col(0, p_at_m83), c_col(1, p_at_m83), c_col(2, p_at_m83));
    gsel(0);
    return;
}



void create_pcpic(int cc, bool prm_410)
{
    buffer(10 + cc, 384, 198);
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

    if (prm_410)
    {
        pcc(4, cc) = 0;
        pcc(2, cc) = 0;
        pcc(6, cc) = 0;
        pcc(3, cc) = 0;
        pcc(8, cc) = 0;
        pcc(5, cc) = 0;
        for (int i = 0; i < 30; ++i)
        {
            if (cdata_body_part(cc, i) % 10000 != 0)
            {
                set_pcc_depending_on_equipments(
                    cc, cdata_body_part(cc, i) % 10000 - 1);
            }
        }
    }

    pcc(10, cc) = pcc(1, cc) / 1000 * 1000 + pcc(10, cc) % 1000;
    pcc(14, cc) = pcc(15, cc) / 1000 * 1000 + pcc(14, cc) % 1000;
    if (prm_410)
    {
        if (pcc(24, cc) == 0)
        {
            load_pcc_part(cc, 4, u8"mantle_");
        }
    }
    load_pcc_part(cc, 1, u8"hairbk_");
    if (cc == 0 && gdata_mount != 0 && pcc(16, cc) != 0)
    {
        load_pcc_part(cc, 16, u8"ridebk_");
    }
    else
    {
        load_pcc_part(cc, 15, u8"body_");
    }
    load_pcc_part(cc, 14, u8"eye_");
    if (cc != 0 || gdata_mount == 0 || pcc(16, cc) == 0)
    {
        load_pcc_part(cc, 7, u8"pants_");
    }
    load_pcc_part(cc, 9, u8"cloth_");
    if (prm_410)
    {
        if (pcc(20, cc) == 0)
        {
            load_pcc_part(cc, 2, u8"chest_");
        }
        if ((cc != 0 || gdata_mount == 0 || pcc(16, cc) == 0)
            && pcc(21, cc) == 0)
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
        if (gdata_mount != 0)
        {
            load_pcc_part(cc, 16, u8"ride_");
        }
    }
    if (prm_410)
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



void initialize_map_chip()
{
    DIM3(chipm, 8, 825);
    if (mdata(2) == 0)
    {
        chipm(5, 233) = 0;
        chipm(6, 233) = 0;
        for (int cnt = 26; cnt < 33; ++cnt)
        {
            chipm(0, cnt) = 4;
        }
        chipm(0, 568) = 4;
        chipm(0, 569) = 4;
        chipm(0, 570) = 4;
        for (int cnt = 99; cnt < 132; ++cnt)
        {
            chipm(0, cnt) = 7;
        }
        for (int cnt = 165; cnt < 198; ++cnt)
        {
            chipm(0, cnt) = 8;
        }
        for (int cnt = 198; cnt < 231; ++cnt)
        {
            chipm(0, cnt) = 4;
        }
        for (int cnt = 594; cnt < 599; ++cnt)
        {
            chipm(0, cnt) = 7;
        }
        for (int cnt = 599; cnt < 604; ++cnt)
        {
            chipm(0, cnt) = 8;
        }
        for (int cnt = 107; cnt < 119; ++cnt)
        {
            chipm(1, cnt) = 9;
        }
        for (int cnt = 173; cnt < 185; ++cnt)
        {
            chipm(1, cnt) = 9;
        }
        for (int cnt = 206; cnt < 218; ++cnt)
        {
            chipm(1, cnt) = 9;
        }
        chipm(0, 604) = 10;
        for (int cnt = 605; cnt < 617; ++cnt)
        {
            chipm(0, cnt) = 10;
            chipm(1, cnt) = 9;
        }
        for (int cnt = 396; cnt < 825; ++cnt)
        {
            chipm(7, cnt) = 5;
        }
        for (int cnt = 264; cnt < 297; ++cnt)
        {
            chipm(7, cnt) = 4;
        }
        chipm(5, 135) = 8;
        chipm(5, 137) = 16;
        chipm(5, 140) = 6;
        chipm(5, 145) = 16;
        chipm(5, 149) = 16;
    }
    if (mdata(2) == 1)
    {
        for (int cnt = 396; cnt < 825; ++cnt)
        {
            chipm(7, cnt) = 5;
        }
        chipm(5, 233) = 56;
        chipm(6, 233) = 48;
        chipm(7, 594) = 4;
        chipm(7, 628) = 4;
        chipm(7, 637) = 4;
        chipm(7, 641) = 4;
        chipm(7, 733) = 4;
        for (int cnt = 45; cnt < 61; ++cnt)
        {
            chipm(0, cnt) = 4;
        }
        chipm(0, 82) = 4;
        chipm(0, 83) = 4;
        chipm(0, 84) = 4;
        for (int cnt = 462; cnt < 528; ++cnt)
        {
            chipm(2, cnt) = 1;
            chipm(2, cnt - 66) = 1;
        }
        for (int cnt = 462; cnt < 495; ++cnt)
        {
            chipm(2, cnt) = 2;
            chipm(2, cnt - 66) = 2;
        }
        chipm(0, 29) = 1;
        chipm(0, 30) = 2;
        chipm(0, 31) = 2;
        chipm(0, 464) = 6;
        chipm(3, 550) = 2;
        chipm(2, 550) = 1;
        chipm(0, 165) = 3;
        chipm(3, 165) = 3;
        chipm(0, 168) = 3;
        chipm(3, 168) = 3;
        chipm(0, 171) = 3;
        chipm(1, 171) = 5;
        chipm(3, 171) = 3;
        chipm(0, 594) = 3;
        chipm(3, 594) = 3;
    }
    if (mdata(2) == 2)
    {
        for (int cnt = 0; cnt < 11; ++cnt)
        {
            int cnt2 = cnt;
            for (int cnt = 0; cnt < 13; ++cnt)
            {
                chipm(0, cnt2 * 33 + cnt + 20) = 4;
            }
        }
        for (int cnt = 33; cnt < 66; ++cnt)
        {
            chipm(0, cnt) = 4;
        }
        for (int cnt = 396; cnt < 825; ++cnt)
        {
            chipm(7, cnt) = 5;
        }
        chipm(5, 233) = 56;
        chipm(6, 233) = 48;
        chipm(7, 594) = 4;
        for (int cnt = 462; cnt < 528; ++cnt)
        {
            chipm(2, cnt) = 1;
            chipm(2, cnt - 66) = 1;
        }
        for (int cnt = 462; cnt < 495; ++cnt)
        {
            chipm(2, cnt) = 2;
            chipm(2, cnt - 66) = 2;
        }
        chipm(3, 550) = 2;
        chipm(2, 550) = 1;
        chipm(0, 165) = 3;
        chipm(3, 165) = 3;
        chipm(0, 168) = 3;
        chipm(3, 168) = 3;
        chipm(0, 171) = 3;
        chipm(1, 171) = 5;
        chipm(3, 171) = 3;
        chipm(0, 594) = 3;
        chipm(3, 594) = 3;
        chipm(2, 476) = 0;
        chipm(2, 509) = 0;
    }
    return;
}



void initialize_item_chip()
{
    initialize_mef();
    SDIM3(tname, 16, 11);
    tname(1) = lang(u8"日干し岩"s, u8"a dryrock"s);
    tname(2) = lang(u8"畑"s, u8"a field"s);
    DIM3(chipc, 6, 925);
    DIM3(chipi, 8, 825);
    for (int cnt = 0; cnt < 825; ++cnt)
    {
        chipc(0, cnt) = cnt % 33 * inf_tiles;
        chipc(1, cnt) = cnt / 33 * inf_tiles;
        chipc(2, cnt) = inf_tiles;
        chipc(3, cnt) = inf_tiles;
        chipc(4, cnt) = 16;
        chipi(0, cnt) = cnt % 33 * inf_tiles;
        chipi(1, cnt) = cnt / 33 * inf_tiles;
        chipi(2, cnt) = inf_tiles;
        chipi(3, cnt) = inf_tiles;
        chipi(4, cnt) = 0;
        chipi(5, cnt) = 8;
        chipi(6, cnt) = 40;
    }
    for (int cnt = 825; cnt < 925; ++cnt)
    {
        chipc(0, cnt) = cnt % 33 * inf_tiles;
        chipc(1, cnt) = cnt / 33 * inf_tiles;
        chipc(2, cnt) = inf_tiles;
        chipc(3, cnt) = inf_tiles;
        chipc(4, cnt) = 16;
    }
    chipi(4, 24) = 16;
    chipi(4, 30) = 16;
    chipi(4, 72) = 22;
    chipi(4, 73) = 22;
    chipi(4, 74) = 22;
    chipi(4, 75) = 22;
    chipi(4, 76) = 22;
    chipi(5, 76) = 28;
    chipi(4, 78) = 22;
    chipi(4, 80) = 22;
    chipi(4, 85) = 8;
    chipi(5, 85) = 8;
    chipi(6, 85) = 150;
    chipi(4, 87) = 22;
    chipi(4, 88) = 22;
    chipi(4, 91) = 22;
    chipi(4, 95) = 22;
    chipi(4, 96) = 22;
    chipi(5, 96) = 18;
    chipi(4, 97) = 22;
    chipi(4, 99) = 22;
    chipi(4, 98) = 22;
    chipi(4, 100) = 22;
    chipi(4, 102) = 22;
    chipi(4, 103) = 22;
    chipi(4, 104) = 22;
    chipi(4, 107) = 22;
    chipi(4, 116) = 22;
    chipi(4, 117) = 22;
    chipi(4, 123) = 12;
    chipi(4, 125) = 12;
    chipi(4, 130) = 12;
    chipi(4, 132) = 22;
    chipi(4, 134) = 12;
    chipi(4, 136) = 12;
    chipi(4, 137) = 22;
    chipi(4, 138) = 22;
    chipi(4, 139) = 22;
    chipi(4, 142) = 22;
    chipi(5, 142) = 36;
    chipi(4, 143) = 22;
    chipi(5, 143) = 36;
    chipi(4, 145) = 22;
    chipi(4, 146) = 22;
    chipi(4, 147) = 22;
    chipi(4, 150) = 22;
    chipi(5, 150) = 8;
    chipi(6, 150) = 70;
    chipi(4, 151) = 22;
    chipi(4, 156) = 8;
    chipi(5, 156) = 20;
    chipi(6, 156) = 150;
    chipi(4, 158) = 8;
    chipi(5, 158) = 24;
    chipi(6, 158) = 150;
    chipi(4, 159) = 8;
    chipi(5, 159) = 24;
    chipi(6, 159) = 150;
    chipi(4, 160) = 22;
    chipi(4, 163) = 22;
    chipi(5, 163) = 16;
    chipi(4, 164) = 22;
    chipi(4, 118) = 22;
    chipi(4, 166) = 22;
    chipi(4, 197) = 22;
    chipi(5, 197) = 24;
    chipi(4, 232) = 22;
    chipi(4, 248) = 22;
    chipi(4, 234) = 22;
    chipi(5, 234) = 24;
    chipi(4, 235) = 22;
    chipi(5, 235) = 36;
    chipi(4, 236) = 22;
    chipi(4, 242) = 22;
    chipi(5, 242) = 8;
    chipi(6, 242) = 250;
    chipi(4, 259) = 8;
    chipi(5, 259) = 12;
    chipi(4, 260) = 22;
    chipi(5, 260) = 22;
    chipi(4, 262) = 22;
    chipi(4, 263) = 22;
    chipi(4, 264) = 22;
    chipi(4, 266) = 22;
    chipi(5, 266) = 24;
    chipi(4, 270) = 22;
    chipi(4, 272) = 22;
    chipi(5, 272) = 34;
    chipi(4, 273) = 22;
    chipi(4, 276) = 22;
    chipi(4, 277) = 8;
    chipi(4, 278) = 22;
    chipi(4, 279) = 22;
    chipi(4, 281) = 22;
    chipi(5, 281) = 40;
    chipi(4, 282) = 22;
    chipi(4, 285) = 22;
    chipi(4, 286) = 22;
    chipi(4, 288) = 22;
    chipi(5, 288) = 18;
    chipi(4, 291) = 22;
    chipi(4, 292) = 22;
    chipi(5, 292) = 32;
    chipi(4, 293) = 22;
    chipi(4, 295) = 22;
    chipi(4, 296) = 22;
    chipi(4, 299) = 22;
    chipi(5, 299) = 8;
    chipi(6, 299) = 250;
    chipi(4, 300) = 22;
    chipi(4, 320) = 22;
    chipi(4, 321) = 22;
    chipi(4, 325) = 22;
    chipi(4, 327) = 22;
    chipi(4, 331) = 22;
    chipi(4, 332) = 22;
    chipi(4, 348) = 22;
    chipi(4, 353) = 48;
    chipi(5, 354) = 8;
    chipi(6, 354) = 20;
    chipi(4, 360) = 0;
    chipi(5, 360) = 2;
    chipi(6, 360) = 1;
    chipi(4, 364) = 22;
    chipi(5, 364) = 8;
    chipi(6, 364) = 250;
    chipi(4, 367) = 22;
    chipi(4, 368) = 22;
    chipi(4, 370) = 8;
    chipi(4, 372) = 22;
    chipi(4, 373) = 22;
    chipi(4, 375) = 22;
    chipi(4, 376) = 22;
    chipi(4, 377) = 22;
    chipi(4, 395) = 22;
    chipi(4, 378) = 48;
    chipi(4, 379) = 48;
    chipi(4, 380) = 8;
    chipi(4, 381) = 22;
    chipi(4, 382) = 48;
    chipi(4, 384) = 22;
    chipi(4, 442) = 8;
    chipi(5, 442) = 24;
    chipi(6, 442) = 100;
    chipi(4, 507) = 22;
    chipi(4, 508) = 22;
    chipi(4, 506) = 22;
    chipi(4, 510) = 22;
    chipi(4, 511) = 22;
    chipi(5, 511) = 28;
    chipi(4, 512) = 22;
    chipi(4, 513) = 22;
    chipi(4, 541) = 22;
    chipi(5, 541) = 36;
    chipi(4, 543) = 22;
    chipi(4, 544) = 48;
    chipi(4, 545) = 0;
    chipi(5, 545) = 0;
    chipi(6, 545) = 0;
    chipi(4, 627) = 22;
    chipi(4, 637) = 22;
    chipi(4, 639) = 48;
    chipi(4, 640) = 22;
    chipi(5, 640) = 34;
    chipi(4, 641) = 22;
    chipi(4, 642) = 22;
    chipi(4, 643) = 22;
    chipi(4, 644) = 32;
    chipi(4, 646) = 22;
    chipi(4, 647) = 22;
    chipi(4, 648) = 22;
    chipi(4, 650) = 22;
    chipi(4, 651) = 48;
    chipi(4, 652) = 48;
    chipi(4, 653) = 32;
    chipi(4, 655) = 22;
    chipi(4, 659) = 22;
    chipi(4, 662) = 22;
    chipi(6, 664) = 0;
    chipi(6, 665) = 0;
    chipi(6, 667) = 0;
    chipi(4, 668) = 8;
    chipi(4, 669) = 8;
    chipi(4, 672) = 38;
    chipi(4, 674) = 22;
    chipi(5, 674) = 24;
    chipi(4, 675) = 16;
    chipi(4, 676) = 40;
    chipi(4, 677) = 16;
    chipi(5, 677) = 8;
    chipi(6, 677) = 50;
    chipi(6, 679) = 1;
    chipi(3, 523) = inf_tiles * 2;
    chipi(4, 523) = inf_tiles + 16;
    chipi(5, 523) = 40;
    chipi(6, 523) = 6;
    chipi(3, 524) = inf_tiles * 2;
    chipi(4, 524) = inf_tiles + 16;
    chipi(5, 524) = 65;
    chipi(3, 525) = inf_tiles * 2;
    chipi(4, 525) = inf_tiles + 20;
    chipi(3, 526) = inf_tiles * 2;
    chipi(4, 526) = inf_tiles + 20;
    chipi(3, 527) = inf_tiles * 2;
    chipi(4, 527) = inf_tiles + 20;
    chipi(3, 531) = inf_tiles * 2;
    chipi(4, 531) = inf_tiles + 16;
    chipi(5, 531) = 40;
    chipi(3, 563) = inf_tiles * 2;
    chipi(4, 563) = inf_tiles + 15;
    chipi(3, 566) = inf_tiles * 2;
    chipi(4, 566) = inf_tiles + 12;
    chipi(3, 567) = inf_tiles * 2;
    chipi(4, 567) = inf_tiles + 12;
    chipi(3, 568) = inf_tiles * 2;
    chipi(4, 568) = inf_tiles + 12;
    chipi(3, 569) = inf_tiles * 2;
    chipi(4, 569) = inf_tiles + 12;
    chipi(5, 569) = 70;
    chipi(6, 569) = 6;
    chipi(3, 570) = inf_tiles * 2;
    chipi(4, 570) = inf_tiles + 20;
    chipi(3, 571) = inf_tiles * 2;
    chipi(4, 571) = inf_tiles + 20;
    chipi(5, 571) = 64;
    chipi(3, 572) = inf_tiles * 2;
    chipi(4, 572) = inf_tiles + 20;
    chipi(3, 573) = inf_tiles * 2;
    chipi(4, 573) = inf_tiles + 20;
    chipi(3, 574) = inf_tiles * 2;
    chipi(4, 574) = inf_tiles + 20;
    chipi(3, 575) = inf_tiles * 2;
    chipi(4, 575) = inf_tiles + 20;
    chipi(3, 576) = inf_tiles * 2;
    chipi(4, 576) = inf_tiles + 20;
    chipi(3, 577) = inf_tiles * 2;
    chipi(4, 577) = inf_tiles + 20;
    chipi(5, 577) = 48;
    chipi(6, 577) = 6;
    chipi(3, 578) = inf_tiles * 2;
    chipi(4, 578) = inf_tiles + 20;
    chipi(3, 579) = inf_tiles * 2;
    chipi(4, 579) = inf_tiles + 20;
    chipi(3, 580) = inf_tiles * 2;
    chipi(4, 580) = inf_tiles + 20;
    chipi(5, 580) = 40;
    chipi(6, 580) = 6;
    chipi(3, 581) = inf_tiles * 2;
    chipi(4, 581) = inf_tiles + 20;
    chipi(3, 582) = inf_tiles * 2;
    chipi(4, 582) = inf_tiles + 20;
    chipi(3, 583) = inf_tiles * 2;
    chipi(4, 583) = inf_tiles + 20;
    chipi(5, 583) = 44;
    chipi(6, 583) = 6;
    chipi(3, 584) = inf_tiles * 2;
    chipi(4, 584) = inf_tiles + 20;
    chipi(5, 584) = 40;
    chipi(6, 584) = 6;
    chipi(3, 585) = inf_tiles * 2;
    chipi(4, 585) = inf_tiles + 20;
    chipi(3, 586) = inf_tiles * 2;
    chipi(4, 586) = inf_tiles + 20;
    chipi(5, 586) = 44;
    chipi(6, 586) = 6;
    chipi(3, 587) = inf_tiles * 2;
    chipi(4, 587) = inf_tiles + 20;
    chipi(3, 588) = inf_tiles * 2;
    chipi(4, 588) = inf_tiles + 20;
    chipi(3, 589) = inf_tiles * 2;
    chipi(4, 589) = inf_tiles + 20;
    chipi(3, 590) = inf_tiles * 2;
    chipi(4, 590) = inf_tiles + 20;
    chipi(3, 591) = inf_tiles * 2;
    chipi(4, 591) = inf_tiles + 20;
    chipi(3, 592) = inf_tiles * 2;
    chipi(4, 592) = inf_tiles + 20;
    chipi(3, 593) = inf_tiles * 2;
    chipi(4, 593) = inf_tiles + 20;
    chipi(3, 680) = inf_tiles * 2;
    chipi(4, 680) = inf_tiles + 16;
    chipi(3, 681) = inf_tiles * 2;
    chipi(4, 681) = inf_tiles + 16;
    chipi(3, 682) = inf_tiles * 2;
    chipi(4, 682) = inf_tiles + 16;
    chipi(3, 683) = inf_tiles * 2;
    chipi(4, 683) = inf_tiles + 22;
    chipi(5, 683) = 50;
    chipi(3, 685) = inf_tiles * 2;
    chipi(4, 685) = inf_tiles + 52;
    chipi(5, 685) = 50;
    chipi(6, 685) = 18;
    chipi(3, 684) = inf_tiles * 2;
    chipi(4, 684) = inf_tiles + 52;
    chipi(5, 684) = 50;
    chipi(6, 684) = 18;
    chipi(3, 686) = inf_tiles * 2;
    chipi(4, 686) = inf_tiles + 16;
    chipi(3, 687) = inf_tiles * 2;
    chipi(4, 687) = inf_tiles + 16;
    chipi(3, 688) = inf_tiles * 2;
    chipi(4, 688) = inf_tiles + 16;
    chipi(3, 689) = inf_tiles * 2;
    chipi(4, 689) = inf_tiles + 16;
    chipi(3, 690) = inf_tiles * 2;
    chipi(4, 690) = inf_tiles + 16;
    chipi(3, 691) = inf_tiles * 2;
    chipi(4, 691) = inf_tiles + 16;
    chipi(5, 691) = 48;
    chipi(3, 692) = inf_tiles * 2;
    chipi(4, 692) = inf_tiles + 16;
    chipi(7, 19) = 2;
    chipi(7, 24) = 3;
    chipi(7, 27) = 3;
    chipi(7, 30) = 2;
    chipi(7, 349) = 3;
    chipi(7, 355) = 3;
    chipc(4, 176) = 8;
    chipc(4, 225) = 29;
    chipc(4, 230) = 12;
    chipc(4, 256) = 16;
    chipc(4, 277) = 29;
    chipc(3, 201) = inf_tiles * 2;
    chipc(4, 201) = inf_tiles + 16;
    chipc(3, 228) = inf_tiles * 2;
    chipc(4, 228) = inf_tiles + 8;
    chipc(3, 231) = inf_tiles * 2;
    chipc(4, 231) = inf_tiles + 16;
    chipc(3, 232) = inf_tiles * 2;
    chipc(4, 232) = inf_tiles + 16;
    chipc(3, 233) = inf_tiles * 2;
    chipc(4, 233) = inf_tiles + 8;
    chipc(3, 297) = inf_tiles * 2;
    chipc(4, 297) = inf_tiles + 16;
    chipc(3, 235) = inf_tiles * 2;
    chipc(4, 235) = inf_tiles + 16;
    chipc(3, 280) = inf_tiles * 2;
    chipc(4, 280) = inf_tiles + 32;
    chipc(3, 338) = inf_tiles * 2;
    chipc(4, 338) = inf_tiles + 32;
    chipc(3, 339) = inf_tiles * 2;
    chipc(4, 339) = inf_tiles + 16;
    chipc(3, 341) = inf_tiles * 2;
    chipc(4, 341) = inf_tiles + 16;
    chipc(3, 342) = inf_tiles * 2;
    chipc(4, 342) = inf_tiles + 12;
    chipc(3, 343) = inf_tiles * 2;
    chipc(4, 343) = inf_tiles + 16;
    chipc(3, 349) = inf_tiles * 2;
    chipc(4, 349) = inf_tiles + 8;
    chipc(3, 351) = inf_tiles * 2;
    chipc(4, 351) = inf_tiles + 8;
    chipc(3, 389) = inf_tiles * 2;
    chipc(4, 389) = inf_tiles + 16;
    chipc(3, 391) = inf_tiles * 2;
    chipc(4, 391) = inf_tiles + 16;
    chipc(3, 393) = inf_tiles * 2;
    chipc(4, 393) = inf_tiles + 16;
    chipc(3, 398) = inf_tiles * 2;
    chipc(4, 398) = inf_tiles + 16;
    chipc(3, 404) = inf_tiles * 2;
    chipc(4, 404) = inf_tiles + 16;
    chipc(3, 405) = inf_tiles * 2;
    chipc(4, 405) = inf_tiles + 16;
    chipc(3, 408) = inf_tiles * 2;
    chipc(4, 408) = inf_tiles + 16;
    chipc(3, 413) = inf_tiles * 2;
    chipc(4, 413) = inf_tiles + 16;
    chipc(3, 429) = inf_tiles * 2;
    chipc(4, 429) = inf_tiles + 8;
    chipc(3, 430) = inf_tiles * 2;
    chipc(4, 430) = inf_tiles + 8;
    chipc(3, 432) = inf_tiles * 2;
    chipc(4, 432) = inf_tiles + 8;
    chipc(3, 433) = inf_tiles * 2;
    chipc(4, 433) = inf_tiles + 8;
    chipc(3, 439) = inf_tiles * 2;
    chipc(4, 439) = inf_tiles + 8;
    chipc(3, 442) = inf_tiles * 2;
    chipc(4, 442) = inf_tiles + 8;
    chipc(3, 447) = inf_tiles * 2;
    chipc(4, 447) = inf_tiles + 16;
    DIM3(deco, 3, 300);
    for (int cnt = 0; cnt < 16; ++cnt)
    {
        deco(0, 1 + cnt * 16) = 0;
        deco(1, 1 + cnt * 16) = 1;
        deco(0, 2 + cnt * 16) = 1;
        deco(1, 2 + cnt * 16) = 2;
        deco(0, 4 + cnt * 16) = 1;
        deco(1, 4 + cnt * 16) = 0;
        deco(0, 6 + cnt * 16) = -1;
        deco(1, 6 + cnt * 16) = 21;
        deco(0, 7 + cnt * 16) = -1;
        deco(1, 7 + cnt * 16) = 30;
        deco(0, 8 + cnt * 16) = 2;
        deco(1, 8 + cnt * 16) = 1;
        deco(0, 9 + cnt * 16) = -1;
        deco(1, 9 + cnt * 16) = 20;
        deco(0, 10 + cnt * 16) = 2;
        deco(1, 10 + cnt * 16) = 2;
        deco(0, 11 + cnt * 16) = -1;
        deco(1, 11 + cnt * 16) = 33;
        deco(0, 12 + cnt * 16) = 2;
        deco(1, 12 + cnt * 16) = 0;
        deco(0, 13 + cnt * 16) = -1;
        deco(1, 13 + cnt * 16) = 32;
        deco(0, 14 + cnt * 16) = -1;
        deco(1, 14 + cnt * 16) = 31;
        deco(0, 15 + cnt * 16) = 3;
        deco(1, 15 + cnt * 16) = 1;
        deco(0, 16 + cnt * 16) = -1;
        deco(1, 16 + cnt * 16) = -1;
        deco(0, 19 + cnt * 16) = 0;
        deco(1, 19 + cnt * 16) = 2;
    }
    deco(2, 49) = 2;
    deco(2, 52) = 2;
    deco(2, 53) = 2;
    deco(2, 97) = 2;
    deco(2, 113) = 2;
    deco(2, 117) = 2;
    deco(2, 164) = 2;
    deco(2, 180) = 2;
    deco(2, 181) = 2;
    deco(2, 145) = 4;
    deco(2, 162) = 4;
    deco(2, 194) = 4;
    deco(2, 195) = 4;
    deco(2, 209) = 4;
    deco(2, 226) = 4;
    deco(2, 243) = 4;
    deco(2, 84) = 3;
    deco(2, 104) = 3;
    deco(2, 196) = 3;
    deco(2, 200) = 3;
    deco(2, 204) = 3;
    deco(2, 212) = 3;
    deco(2, 220) = 3;
    deco(2, 232) = 3;
    deco(2, 236) = 3;
    deco(2, 24) = 1;
    deco(2, 50) = 1;
    deco(2, 56) = 1;
    deco(2, 58) = 1;
    deco(2, 82) = 1;
    deco(2, 114) = 1;
    deco(2, 122) = 1;
    deco(2, 152) = 1;
    deco(2, 184) = 1;
    deco(2, 186) = 1;
    deco(2, 178) = 8;
    deco(2, 241) = 10;
    deco(2, 242) = 8;
    deco(2, 244) = 7;
    deco(0, 16) = -1;
    deco(1, 16) = 1;
    deco(0, 32) = -1;
    deco(1, 32) = 2;
    deco(0, 64) = -1;
    deco(1, 64) = 3;
    deco(0, 128) = -1;
    deco(1, 128) = 4;
    deco(0, 48) = -1;
    deco(1, 48) = 5;
    deco(0, 192) = -1;
    deco(1, 192) = 6;
    deco(0, 96) = -1;
    deco(1, 96) = 7;
    deco(0, 144) = -1;
    deco(1, 144) = 8;
    deco(0, 80) = -1;
    deco(1, 80) = 9;
    deco(0, 160) = -1;
    deco(1, 160) = 10;
    deco(0, 91) = 0;
    deco(1, 91) = 1;
    deco(0, 93) = 0;
    deco(1, 93) = 1;
    deco(0, 21) = 0;
    deco(1, 21) = 0;
    deco(0, 85) = 0;
    deco(1, 85) = 0;
    deco(0, 213) = 0;
    deco(1, 213) = 0;
    deco(0, 149) = 0;
    deco(1, 149) = 0;
    initialize_map_chip();
    return;
}


} // namespace elona

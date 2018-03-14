#include "draw.hpp"
#include <cmath>
#include "character.hpp"
#include "config.hpp"
#include "elona.hpp"
#include "map.hpp"
#include "variables.hpp"


namespace
{


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
    damage_popups.emplace_back(text, character, color);
}


void show_damage_popups(int inf_ver)
{
    for (auto&& damage_popup : damage_popups)
    {
        const auto& cc = cdata[damage_popup.character];
        if (gdata(20) != 40)
        {
            if (!is_in_fov(cc.position))
                continue;
            if (dist(
                    cdata[0].position.x,
                    cdata[0].position.y,
                    cc.position.x,
                    cc.position.y)
                > cdata[0].vision_distance / 2)
                continue;
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

        font(lang(cfg_font1, cfg_font2), 2 + cfg_dmgfont - en * 2, 0);
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
            [](const auto& d) { return d.frame > 50; }),
        std::end(damage_popups));
}



} // namespace elona

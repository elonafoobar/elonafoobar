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
#include "random.hpp"
#include "thirdparty/microhcl/hcl.hpp"
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

    damage_popup_t()
        : frame(-1)
        , text(std::string())
        , character(-1)
        , color(snail::color(255, 255, 255, 255))
    {
    }
};


std::vector<damage_popup_t> damage_popups;
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



void initialize_item_chips()
{
    for (size_t i = 0; i < item_chips.size(); ++i)
    {
        item_chips[i].x = i % 33 * inf_tiles;
        item_chips[i].y = i / 33 * inf_tiles;
        item_chips[i].width = inf_tiles;
        item_chips[i].height = inf_tiles;
        item_chips[i].offset_y = 0;
        item_chips[i].stack_height = 8;
        item_chips[i].shadow = 40;
        item_chips[i].animation = 0;
    }

    item_chips[24].offset_y = 16;
    item_chips[30].offset_y = 16;
    item_chips[72].offset_y = 22;
    item_chips[73].offset_y = 22;
    item_chips[74].offset_y = 22;
    item_chips[75].offset_y = 22;
    item_chips[76].offset_y = 22;
    item_chips[76].stack_height = 28;
    item_chips[78].offset_y = 22;
    item_chips[80].offset_y = 22;
    item_chips[85].offset_y = 8;
    item_chips[85].stack_height = 8;
    item_chips[85].shadow = 150;
    item_chips[87].offset_y = 22;
    item_chips[88].offset_y = 22;
    item_chips[91].offset_y = 22;
    item_chips[95].offset_y = 22;
    item_chips[96].offset_y = 22;
    item_chips[96].stack_height = 18;
    item_chips[97].offset_y = 22;
    item_chips[99].offset_y = 22;
    item_chips[98].offset_y = 22;
    item_chips[100].offset_y = 22;
    item_chips[102].offset_y = 22;
    item_chips[103].offset_y = 22;
    item_chips[104].offset_y = 22;
    item_chips[107].offset_y = 22;
    item_chips[116].offset_y = 22;
    item_chips[117].offset_y = 22;
    item_chips[123].offset_y = 12;
    item_chips[125].offset_y = 12;
    item_chips[130].offset_y = 12;
    item_chips[132].offset_y = 22;
    item_chips[134].offset_y = 12;
    item_chips[136].offset_y = 12;
    item_chips[137].offset_y = 22;
    item_chips[138].offset_y = 22;
    item_chips[139].offset_y = 22;
    item_chips[142].offset_y = 22;
    item_chips[142].stack_height = 36;
    item_chips[143].offset_y = 22;
    item_chips[143].stack_height = 36;
    item_chips[145].offset_y = 22;
    item_chips[146].offset_y = 22;
    item_chips[147].offset_y = 22;
    item_chips[150].offset_y = 22;
    item_chips[150].stack_height = 8;
    item_chips[150].shadow = 70;
    item_chips[151].offset_y = 22;
    item_chips[156].offset_y = 8;
    item_chips[156].stack_height = 20;
    item_chips[156].shadow = 150;
    item_chips[158].offset_y = 8;
    item_chips[158].stack_height = 24;
    item_chips[158].shadow = 150;
    item_chips[159].offset_y = 8;
    item_chips[159].stack_height = 24;
    item_chips[159].shadow = 150;
    item_chips[160].offset_y = 22;
    item_chips[163].offset_y = 22;
    item_chips[163].stack_height = 16;
    item_chips[164].offset_y = 22;
    item_chips[118].offset_y = 22;
    item_chips[166].offset_y = 22;
    item_chips[197].offset_y = 22;
    item_chips[197].stack_height = 24;
    item_chips[232].offset_y = 22;
    item_chips[248].offset_y = 22;
    item_chips[234].offset_y = 22;
    item_chips[234].stack_height = 24;
    item_chips[235].offset_y = 22;
    item_chips[235].stack_height = 36;
    item_chips[236].offset_y = 22;
    item_chips[242].offset_y = 22;
    item_chips[242].stack_height = 8;
    item_chips[242].shadow = 250;
    item_chips[259].offset_y = 8;
    item_chips[259].stack_height = 12;
    item_chips[260].offset_y = 22;
    item_chips[260].stack_height = 22;
    item_chips[262].offset_y = 22;
    item_chips[263].offset_y = 22;
    item_chips[264].offset_y = 22;
    item_chips[266].offset_y = 22;
    item_chips[266].stack_height = 24;
    item_chips[270].offset_y = 22;
    item_chips[272].offset_y = 22;
    item_chips[272].stack_height = 34;
    item_chips[273].offset_y = 22;
    item_chips[276].offset_y = 22;
    item_chips[277].offset_y = 8;
    item_chips[278].offset_y = 22;
    item_chips[279].offset_y = 22;
    item_chips[281].offset_y = 22;
    item_chips[281].stack_height = 40;
    item_chips[282].offset_y = 22;
    item_chips[285].offset_y = 22;
    item_chips[286].offset_y = 22;
    item_chips[288].offset_y = 22;
    item_chips[288].stack_height = 18;
    item_chips[291].offset_y = 22;
    item_chips[292].offset_y = 22;
    item_chips[292].stack_height = 32;
    item_chips[293].offset_y = 22;
    item_chips[295].offset_y = 22;
    item_chips[296].offset_y = 22;
    item_chips[299].offset_y = 22;
    item_chips[299].stack_height = 8;
    item_chips[299].shadow = 250;
    item_chips[300].offset_y = 22;
    item_chips[320].offset_y = 22;
    item_chips[321].offset_y = 22;
    item_chips[325].offset_y = 22;
    item_chips[327].offset_y = 22;
    item_chips[331].offset_y = 22;
    item_chips[332].offset_y = 22;
    item_chips[348].offset_y = 22;
    item_chips[353].offset_y = 48;
    item_chips[354].stack_height = 8;
    item_chips[354].shadow = 20;
    item_chips[360].offset_y = 0;
    item_chips[360].stack_height = 2;
    item_chips[360].shadow = 1;
    item_chips[364].offset_y = 22;
    item_chips[364].stack_height = 8;
    item_chips[364].shadow = 250;
    item_chips[367].offset_y = 22;
    item_chips[368].offset_y = 22;
    item_chips[370].offset_y = 8;
    item_chips[372].offset_y = 22;
    item_chips[373].offset_y = 22;
    item_chips[375].offset_y = 22;
    item_chips[376].offset_y = 22;
    item_chips[377].offset_y = 22;
    item_chips[395].offset_y = 22;
    item_chips[378].offset_y = 48;
    item_chips[379].offset_y = 48;
    item_chips[380].offset_y = 8;
    item_chips[381].offset_y = 22;
    item_chips[382].offset_y = 48;
    item_chips[384].offset_y = 22;
    item_chips[442].offset_y = 8;
    item_chips[442].stack_height = 24;
    item_chips[442].shadow = 100;
    item_chips[507].offset_y = 22;
    item_chips[508].offset_y = 22;
    item_chips[506].offset_y = 22;
    item_chips[510].offset_y = 22;
    item_chips[511].offset_y = 22;
    item_chips[511].stack_height = 28;
    item_chips[512].offset_y = 22;
    item_chips[513].offset_y = 22;
    item_chips[541].offset_y = 22;
    item_chips[541].stack_height = 36;
    item_chips[543].offset_y = 22;
    item_chips[544].offset_y = 48;
    item_chips[545].offset_y = 0;
    item_chips[545].stack_height = 0;
    item_chips[545].shadow = 0;
    item_chips[627].offset_y = 22;
    item_chips[637].offset_y = 22;
    item_chips[639].offset_y = 48;
    item_chips[640].offset_y = 22;
    item_chips[640].stack_height = 34;
    item_chips[641].offset_y = 22;
    item_chips[642].offset_y = 22;
    item_chips[643].offset_y = 22;
    item_chips[644].offset_y = 32;
    item_chips[646].offset_y = 22;
    item_chips[647].offset_y = 22;
    item_chips[648].offset_y = 22;
    item_chips[650].offset_y = 22;
    item_chips[651].offset_y = 48;
    item_chips[652].offset_y = 48;
    item_chips[653].offset_y = 32;
    item_chips[655].offset_y = 22;
    item_chips[659].offset_y = 22;
    item_chips[662].offset_y = 22;
    item_chips[664].shadow = 0;
    item_chips[665].shadow = 0;
    item_chips[667].shadow = 0;
    item_chips[668].offset_y = 8;
    item_chips[669].offset_y = 8;
    item_chips[672].offset_y = 38;
    item_chips[674].offset_y = 22;
    item_chips[674].stack_height = 24;
    item_chips[675].offset_y = 16;
    item_chips[676].offset_y = 40;
    item_chips[677].offset_y = 16;
    item_chips[677].stack_height = 8;
    item_chips[677].shadow = 50;
    item_chips[679].shadow = 1;
    item_chips[523].height = inf_tiles * 2;
    item_chips[523].offset_y = inf_tiles + 16;
    item_chips[523].stack_height = 40;
    item_chips[523].shadow = 6;
    item_chips[524].height = inf_tiles * 2;
    item_chips[524].offset_y = inf_tiles + 16;
    item_chips[524].stack_height = 65;
    item_chips[525].height = inf_tiles * 2;
    item_chips[525].offset_y = inf_tiles + 20;
    item_chips[526].height = inf_tiles * 2;
    item_chips[526].offset_y = inf_tiles + 20;
    item_chips[527].height = inf_tiles * 2;
    item_chips[527].offset_y = inf_tiles + 20;
    item_chips[531].height = inf_tiles * 2;
    item_chips[531].offset_y = inf_tiles + 16;
    item_chips[531].stack_height = 40;
    item_chips[563].height = inf_tiles * 2;
    item_chips[563].offset_y = inf_tiles + 15;
    item_chips[566].height = inf_tiles * 2;
    item_chips[566].offset_y = inf_tiles + 12;
    item_chips[567].height = inf_tiles * 2;
    item_chips[567].offset_y = inf_tiles + 12;
    item_chips[568].height = inf_tiles * 2;
    item_chips[568].offset_y = inf_tiles + 12;
    item_chips[569].height = inf_tiles * 2;
    item_chips[569].offset_y = inf_tiles + 12;
    item_chips[569].stack_height = 70;
    item_chips[569].shadow = 6;
    item_chips[570].height = inf_tiles * 2;
    item_chips[570].offset_y = inf_tiles + 20;
    item_chips[571].height = inf_tiles * 2;
    item_chips[571].offset_y = inf_tiles + 20;
    item_chips[571].stack_height = 64;
    item_chips[572].height = inf_tiles * 2;
    item_chips[572].offset_y = inf_tiles + 20;
    item_chips[573].height = inf_tiles * 2;
    item_chips[573].offset_y = inf_tiles + 20;
    item_chips[574].height = inf_tiles * 2;
    item_chips[574].offset_y = inf_tiles + 20;
    item_chips[575].height = inf_tiles * 2;
    item_chips[575].offset_y = inf_tiles + 20;
    item_chips[576].height = inf_tiles * 2;
    item_chips[576].offset_y = inf_tiles + 20;
    item_chips[577].height = inf_tiles * 2;
    item_chips[577].offset_y = inf_tiles + 20;
    item_chips[577].stack_height = 48;
    item_chips[577].shadow = 6;
    item_chips[578].height = inf_tiles * 2;
    item_chips[578].offset_y = inf_tiles + 20;
    item_chips[579].height = inf_tiles * 2;
    item_chips[579].offset_y = inf_tiles + 20;
    item_chips[580].height = inf_tiles * 2;
    item_chips[580].offset_y = inf_tiles + 20;
    item_chips[580].stack_height = 40;
    item_chips[580].shadow = 6;
    item_chips[581].height = inf_tiles * 2;
    item_chips[581].offset_y = inf_tiles + 20;
    item_chips[582].height = inf_tiles * 2;
    item_chips[582].offset_y = inf_tiles + 20;
    item_chips[583].height = inf_tiles * 2;
    item_chips[583].offset_y = inf_tiles + 20;
    item_chips[583].stack_height = 44;
    item_chips[583].shadow = 6;
    item_chips[584].height = inf_tiles * 2;
    item_chips[584].offset_y = inf_tiles + 20;
    item_chips[584].stack_height = 40;
    item_chips[584].shadow = 6;
    item_chips[585].height = inf_tiles * 2;
    item_chips[585].offset_y = inf_tiles + 20;
    item_chips[586].height = inf_tiles * 2;
    item_chips[586].offset_y = inf_tiles + 20;
    item_chips[586].stack_height = 44;
    item_chips[586].shadow = 6;
    item_chips[587].height = inf_tiles * 2;
    item_chips[587].offset_y = inf_tiles + 20;
    item_chips[588].height = inf_tiles * 2;
    item_chips[588].offset_y = inf_tiles + 20;
    item_chips[589].height = inf_tiles * 2;
    item_chips[589].offset_y = inf_tiles + 20;
    item_chips[590].height = inf_tiles * 2;
    item_chips[590].offset_y = inf_tiles + 20;
    item_chips[591].height = inf_tiles * 2;
    item_chips[591].offset_y = inf_tiles + 20;
    item_chips[592].height = inf_tiles * 2;
    item_chips[592].offset_y = inf_tiles + 20;
    item_chips[593].height = inf_tiles * 2;
    item_chips[593].offset_y = inf_tiles + 20;
    item_chips[680].height = inf_tiles * 2;
    item_chips[680].offset_y = inf_tiles + 16;
    item_chips[681].height = inf_tiles * 2;
    item_chips[681].offset_y = inf_tiles + 16;
    item_chips[682].height = inf_tiles * 2;
    item_chips[682].offset_y = inf_tiles + 16;
    item_chips[683].height = inf_tiles * 2;
    item_chips[683].offset_y = inf_tiles + 22;
    item_chips[683].stack_height = 50;
    item_chips[685].height = inf_tiles * 2;
    item_chips[685].offset_y = inf_tiles + 52;
    item_chips[685].stack_height = 50;
    item_chips[685].shadow = 18;
    item_chips[684].height = inf_tiles * 2;
    item_chips[684].offset_y = inf_tiles + 52;
    item_chips[684].stack_height = 50;
    item_chips[684].shadow = 18;
    item_chips[686].height = inf_tiles * 2;
    item_chips[686].offset_y = inf_tiles + 16;
    item_chips[687].height = inf_tiles * 2;
    item_chips[687].offset_y = inf_tiles + 16;
    item_chips[688].height = inf_tiles * 2;
    item_chips[688].offset_y = inf_tiles + 16;
    item_chips[689].height = inf_tiles * 2;
    item_chips[689].offset_y = inf_tiles + 16;
    item_chips[690].height = inf_tiles * 2;
    item_chips[690].offset_y = inf_tiles + 16;
    item_chips[691].height = inf_tiles * 2;
    item_chips[691].offset_y = inf_tiles + 16;
    item_chips[691].stack_height = 48;
    item_chips[692].height = inf_tiles * 2;
    item_chips[692].offset_y = inf_tiles + 16;
    item_chips[19].animation = 2;
    item_chips[24].animation = 3;
    item_chips[27].animation = 3;
    item_chips[30].animation = 2;
    item_chips[349].animation = 3;
    item_chips[355].animation = 3;
}



void initialize_chara_chips()
{
    for (size_t i = 0; i < chara_chips.size(); ++i)
    {
        chara_chips[i].x = i % 33 * inf_tiles;
        chara_chips[i].y = i / 33 * inf_tiles;
        chara_chips[i].width = inf_tiles;
        chara_chips[i].height = inf_tiles;
        chara_chips[i].offset_y = 16;
    }

    chara_chips[176].offset_y = 8;
    chara_chips[225].offset_y = 29;
    chara_chips[230].offset_y = 12;
    chara_chips[256].offset_y = 16;
    chara_chips[277].offset_y = 29;
    chara_chips[201].height = inf_tiles * 2;
    chara_chips[201].offset_y = inf_tiles + 16;
    chara_chips[228].height = inf_tiles * 2;
    chara_chips[228].offset_y = inf_tiles + 8;
    chara_chips[231].height = inf_tiles * 2;
    chara_chips[231].offset_y = inf_tiles + 16;
    chara_chips[232].height = inf_tiles * 2;
    chara_chips[232].offset_y = inf_tiles + 16;
    chara_chips[233].height = inf_tiles * 2;
    chara_chips[233].offset_y = inf_tiles + 8;
    chara_chips[297].height = inf_tiles * 2;
    chara_chips[297].offset_y = inf_tiles + 16;
    chara_chips[235].height = inf_tiles * 2;
    chara_chips[235].offset_y = inf_tiles + 16;
    chara_chips[280].height = inf_tiles * 2;
    chara_chips[280].offset_y = inf_tiles + 32;
    chara_chips[338].height = inf_tiles * 2;
    chara_chips[338].offset_y = inf_tiles + 32;
    chara_chips[339].height = inf_tiles * 2;
    chara_chips[339].offset_y = inf_tiles + 16;
    chara_chips[341].height = inf_tiles * 2;
    chara_chips[341].offset_y = inf_tiles + 16;
    chara_chips[342].height = inf_tiles * 2;
    chara_chips[342].offset_y = inf_tiles + 12;
    chara_chips[343].height = inf_tiles * 2;
    chara_chips[343].offset_y = inf_tiles + 16;
    chara_chips[349].height = inf_tiles * 2;
    chara_chips[349].offset_y = inf_tiles + 8;
    chara_chips[351].height = inf_tiles * 2;
    chara_chips[351].offset_y = inf_tiles + 8;
    chara_chips[389].height = inf_tiles * 2;
    chara_chips[389].offset_y = inf_tiles + 16;
    chara_chips[391].height = inf_tiles * 2;
    chara_chips[391].offset_y = inf_tiles + 16;
    chara_chips[393].height = inf_tiles * 2;
    chara_chips[393].offset_y = inf_tiles + 16;
    chara_chips[398].height = inf_tiles * 2;
    chara_chips[398].offset_y = inf_tiles + 16;
    chara_chips[404].height = inf_tiles * 2;
    chara_chips[404].offset_y = inf_tiles + 16;
    chara_chips[405].height = inf_tiles * 2;
    chara_chips[405].offset_y = inf_tiles + 16;
    chara_chips[408].height = inf_tiles * 2;
    chara_chips[408].offset_y = inf_tiles + 16;
    chara_chips[413].height = inf_tiles * 2;
    chara_chips[413].offset_y = inf_tiles + 16;
    chara_chips[429].height = inf_tiles * 2;
    chara_chips[429].offset_y = inf_tiles + 8;
    chara_chips[430].height = inf_tiles * 2;
    chara_chips[430].offset_y = inf_tiles + 8;
    chara_chips[432].height = inf_tiles * 2;
    chara_chips[432].offset_y = inf_tiles + 8;
    chara_chips[433].height = inf_tiles * 2;
    chara_chips[433].offset_y = inf_tiles + 8;
    chara_chips[439].height = inf_tiles * 2;
    chara_chips[439].offset_y = inf_tiles + 8;
    chara_chips[442].height = inf_tiles * 2;
    chara_chips[442].offset_y = inf_tiles + 8;
    chara_chips[447].height = inf_tiles * 2;
    chara_chips[447].offset_y = inf_tiles + 16;
}



struct image_info
{
    int window_id;
    int x;
    int y;
    int width;
    int height;
};

std::unordered_map<std::string, image_info> images = {};


std::unordered_map<std::string, int> window_id_table = {
    {"interface.bmp", 3},
};



} // namespace


namespace elona
{


std::vector<item_chip_t> item_chips{825};
std::vector<chara_chip_t> chara_chips{925};



void prepare_item_image(int id, int color)
{
    const auto x = item_chips[id].x;
    const auto y = item_chips[id].y;
    const auto w = item_chips[id].width;
    const auto h = item_chips[id].height;

    gsel(1);
    boxf(0, 960, w, h);

    pos(0, 960);
    set_color_mod(
        255 - c_col(0, color), 255 - c_col(1, color), 255 - c_col(2, color));
    gcopy(1, x, y, w, h);
    set_color_mod(255, 255, 255);
    gsel(0);
}



void prepare_item_image(int id, int color, int character_image)
{
    if (id != 528 && id != 531)
    {
        prepare_item_image(id, color);
        return;
    }

    const auto w = item_chips[id].width;
    const auto h = item_chips[id].height;

    gsel(1);
    boxf(0, 960, w, h);

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
        gcopy(
            5,
            chara_chips[character_id].x + 8,
            chara_chips[character_id].y + 4
                + (chara_chips[character_id].height > inf_tiles) * 8,
            chara_chips[character_id].width - 16,
            chara_chips[character_id].height - 8
                - (chara_chips[character_id].height > inf_tiles) * 10,
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
        pos(8, 1058 - chara_chips[character_id].height);
        set_color_mod(
            255 - c_col(0, character_color),
            255 - c_col(1, character_color),
            255 - c_col(2, character_color),
            5);
        gcopy(
            5,
            chara_chips[character_id].x + 8,
            chara_chips[character_id].y + 2,
            chara_chips[character_id].width - 16,
            chara_chips[character_id].height - 8);
        set_color_mod(255, 255, 255, 5);
        gmode(4, 192);
        pos(0, 960 + (chara_chips[character_id].height == inf_tiles) * 48);
        set_color_mod(
            255 - c_col(0, color),
            255 - c_col(1, color),
            255 - c_col(2, color));
        gcopy(
            1,
            144,
            768 + (chara_chips[character_id].height > inf_tiles) * 48,
            inf_tiles,
            chara_chips[character_id].height
                + (chara_chips[character_id].height > inf_tiles) * 48);
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
            bmes(
                name,
                x,
                y,
                cc.state == 1 ? snail::color{255, 255, 255}
                              : snail::color{255, 35, 35});
            if (cc.state == 1)
            {
                const int width = clamp(cc.hp * 30 / cc.max_hp, 1, 30);
                const int x_ = 16 + (windoww - 108) * right;
                const int y_ = y + 17;
                // std::cout << "HP bar(" << i << "):bar:  " << position_t{x_,
                // y_} << std::endl;
                pos(x_, y_);
                gcopy(3, 480 - width, 517, width, 3, width * 3, 9);

                // Show leash icon.
                if (config::instance().leash_icon && cdata[i].is_leashed())
                {
                    constexpr int leash = 631;
                    prepare_item_image(leash, 2);
                    const int icon_width = item_chips[leash].width;
                    const int icon_height = item_chips[leash].height;

                    pos(right ? std::min(x, x_) - icon_width / 2
                              : std::max(x_ + 90, int(x + strlen_u(name) * 7)),
                        y);
                    gcopy(
                        1,
                        0,
                        960,
                        icon_width,
                        icon_height,
                        icon_width / 2,
                        icon_height / 2);
                    gmode(5);
                    gcopy(
                        1,
                        0,
                        960,
                        icon_width,
                        icon_height,
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
    for (size_t i = 0; i < max_damage_popups; i++)
    {
        damage_popups.emplace_back(damage_popup_t{});
    }
}

void add_damage_popup(
    const std::string& text,
    int character,
    const snail::color& color)
{
    if (damage_popups_active == max_damage_popups)
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
    if (config::instance().damage_popup == 0)
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

        int x = (cc.position.x - scx) * inf_tiles + inf_screenx
            - strlen_u(damage_popup.text) * (2 + cfg_dmgfont + 1) / 2 / 2
            + inf_tiles / 2;
        int y = (cc.position.y - scy) * inf_tiles + inf_screeny
            - mondmgpos * (2 + cfg_dmgfont + 3) - 2 * damage_popup.frame;
        x += sxfix * (scx != scxbk) * (scrollp >= 3);
        y += syfix * (scy != scybk) * (scrollp >= 3);

        font(2 + cfg_dmgfont - en * 2);
        bmes(damage_popup.text, x, y, {255, 255, 255}, damage_popup.color);

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
    pos(x + 16, y);
    gcopy(3, 32 + cdata[cc].emotion_icon % 100 * 16, 608, 16, 16);
}



void load_pcc_part(int cc, int body_part, const char* body_part_str)
{
    const auto filepath = filesystem::dir::graphic()
        / (u8"pcc_"s + body_part_str + (pcc(body_part, cc) % 1000) + u8".bmp");
    if (!fs::exists(filepath))
        return;

    pos(128, 0);
    picload(filepath, 1);
    boxf(256, 0, 128, 198);
    gmode(4, 256);
    pget(128, 0);
    pos(256, 0);
    gcopy(10 + cc, 128, 0, 128, 198);
    pos(256, 0);
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



void chara_preparepic(const character& cc)
{
    chara_preparepic(cc.image);
}



void chara_preparepic(int image_id)
{
    const auto chip_id = image_id % 1000;
    const auto color_id = image_id / 1000;
    const auto& chip = chara_chips[chip_id];
    gsel(5);
    boxf(0, 960, chip.width, chip.height);
    pos(0, 960);
    set_color_mod(
        255 - c_col(0, color_id),
        255 - c_col(1, color_id),
        255 - c_col(2, color_id));
    gcopy(5, chip.x, chip.y, chip.width, chip.height);
    set_color_mod(255, 255, 255);
    gsel(0);
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
    initialize_item_chips();
    initialize_chara_chips();
    initialize_map_chip();
}



void bmes(
    const std::string& message,
    int x,
    int y,
    const snail::color& text_color,
    const snail::color& shadow_color)
{
    color(shadow_color.r, shadow_color.g, shadow_color.b);
    for (int dy = -1; dy <= 1; ++dy)
    {
        for (int dx = -1; dx <= 1; ++dx)
        {
            pos(x + dx, y + dy);
            mes(message);
        }
    }
    color(text_color.r, text_color.g, text_color.b);
    pos(x, y);
    mes(message);
    color(0, 0, 0);
}



void init_assets()
{
    const auto filepath = filesystem::dir::exe() / "assets.hcl";
    std::ifstream in{filepath.native()};
    if (!in)
    {
        throw std::runtime_error{
            "Failed to open "
            + filesystem::make_preferred_path_in_utf8(filepath)};
    }
    const auto& result = hcl::parse(in);
    if (!result.valid())
    {
        throw std::runtime_error{result.errorReason};
    }
    const auto& value = result.value;
    if (!value.is<hcl::Object>() || !value.has("images"))
    {
        throw std::runtime_error{"\"images\" object not found"};
    }

    for (const auto& pair : value.get<hcl::Object>("images"))
    {
        images[pair.first] = {
            window_id_table[pair.second.get<std::string>("source")],
            pair.second.get<int>("x"),
            pair.second.get<int>("y"),
            pair.second.get<int>("width"),
            pair.second.get<int>("height"),
        };
    }
}



void draw(const std::string& key, int x, int y)
{
    const auto itr = images.find(key);
    if (itr == std::end(images))
        throw std::runtime_error{u8"Unknown image ID: "s + key};
    const auto& info = itr->second;

    pos(x, y);
    gcopy(info.window_id, info.x, info.y, info.width, info.height);
}



void draw(const std::string& key, int x, int y, int width, int height)
{
    const auto itr = images.find(key);
    if (itr == std::end(images))
        throw std::runtime_error{u8"Unknown image ID: "s + key};
    const auto& info = itr->second;

    pos(x, y);
    gcopy(
        info.window_id, info.x, info.y, info.width, info.height, width, height);
}



} // namespace elona

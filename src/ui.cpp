#include "ui.hpp"
#include "ability.hpp"
#include "audio.hpp"
#include "character.hpp"
#include "config.hpp"
#include "debug.hpp"
#include "draw.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "random.hpp"
#include "variables.hpp"


namespace
{


int inf_barh;
int inf_bary;
int inf_clockarrowx;
int inf_clockarrowy;
int inf_hpx;
int inf_hpy;
int inf_mpx;
int inf_mpy;
int inf_radarw;
int inf_radarx;
int inf_radary;
int scposy;

int cs_posbk_x;
int cs_posbk_y;
int cs_posbk_w;
int cs_posbk_h;



void update_screen_hud()
{
    gmode(2);
    ap = windoww / 192;
    for (int cnt = 0, cnt_end = (ap + 1); cnt < cnt_end; ++cnt)
    {
        if (cnt == ap)
        {
            sx = windoww % 192;
        }
        else
        {
            sx = 192;
        }
        pos(cnt * 192, inf_bary);
        gcopy(3, 0, 464 - inf_barh, sx, inf_barh);
        pos(cnt * 192, inf_msgy);
        gcopy(3, 496, 528, sx, inf_msgh);
    }
    pos(0, inf_msgy);
    gcopy(3, 120, 504, inf_msgx, inf_verh);
    pos(inf_radarw + 6, inf_bary);
    gcopy(3, 208, 376, 16, 16);
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        sx = 0;
        if (cnt == 8)
        {
            sx = 8;
        }
        if (cnt == 9)
        {
            sx = 14;
        }
        pos(inf_radarw + cnt * 47 + 148 + sx, inf_bary + 1);
        gcopy(3, cnt * 16, 376, 16, 16);
    }
    font(12 + sizefix - en * 2);
    pos(inf_radarw + 24, inf_bary + 3 + vfix - en);
    if (strlen_u(mdatan(0)) > size_t(16 - (maplevel() != ""s) * 4))
    {
        mes(cnven(strmid(mdatan(0), 0, 16 - (maplevel() != ""s) * 4)));
    }
    else
    {
        mes(cnven(mdatan(0)));
    }
    pos(inf_radarw + 114, inf_bary + 3 + vfix - en);
    mes(maplevel());
}



void render_weather_effect_rain()
{
    static std::vector<position_t> particles;

    const auto max_particles = windoww * windowh / 3500;
    if (particles.empty())
    {
        particles.resize(max_particles * 2);
    }

    for (int i = 0; i < max_particles * (1 + (mdata(6) == 1)); ++i)
    {
        auto&& particle = particles[i];
        const auto brightness = rnd(100);
        line(
            particle.x,
            particle.y,
            particle.x + i % 2 + 1,
            particle.y + i % 3 + 1,
            {static_cast<uint8_t>(70 + brightness),
             static_cast<uint8_t>(100 + brightness),
             static_cast<uint8_t>(150 + brightness)});

        if (particle == position_t{0, 0})
        {
            particle.x = rnd(windoww);
            particle.y = rnd(windowh - inf_verh) - 6;
        }
        else
        {
            particle.x += 2;
            particle.y += 16 + i % 8;
            if (particle.y > windowh - inf_verh - 4)
            {
                particle = {0, 0};
            }
        }
    }
}



void render_weather_effect_hard_rain()
{
    static std::vector<position_t> particles;

    const auto max_particles = windoww * windowh / 3500;
    if (particles.empty())
    {
        particles.resize(max_particles * 2);
    }

    for (int i = 0; i < max_particles * (1 + (mdata(6) == 1)); ++i)
    {
        auto&& particle = particles[i];
        const auto brightness = rnd(100);
        line(
            particle.x,
            particle.y,
            particle.x + i % 2 + 1,
            particle.y + i % 5 + 4,
            {static_cast<uint8_t>(70 + brightness),
             static_cast<uint8_t>(100 + brightness),
             static_cast<uint8_t>(150 + brightness)});

        if (particle == position_t{0, 0})
        {
            particle.x = rnd(windoww);
            particle.y = rnd(windowh - inf_verh) - 6;
        }
        else
        {
            ++particle.x;
            particle.y += 24 + i % 8;
            if (particle.y > windowh - inf_verh - 9)
            {
                particle = {0, 0};
            }
        }
    }
}



void render_weather_effect_snow()
{
    static std::vector<position_t> particles;

    const auto max_particles = windoww * windowh / 1750;
    if (particles.empty())
    {
        particles.resize(max_particles);
    }

    for (int i = 0; i < max_particles; ++i)
    {
        auto&& particle = particles[i];
        if (i % 30 == 0)
        {
            gmode(4, 100 + i % 150);
        }
        pos(particle.x, particle.y);
        gcopy(3, particle.x % 2 * 8, 600 + i % 6 * 8, 8, 8);

        if (particle == position_t{0, 0} || weatherbk != gdata_weather)
        {
            particle.x = rnd(windoww);
            particle.y = -rnd(windowh / 2);
        }
        else
        {
            particle.x += rnd(3) - 1;
            particle.y += rnd(2) + i % 5;
            if (particle.y > windowh - inf_verh - 10 || rnd(500) == 0)
            {
                particle = {0, 0};
            }
        }
    }
}



void render_weather_effect_etherwind()
{
    static std::vector<position_t> particles;

    const auto max_particles = windoww * windowh / 3500;
    if (particles.empty())
    {
        particles.resize(max_particles);
    }

    for (int i = 0; i < max_particles; ++i)
    {
        auto&& particle = particles[i];
        if (i % 20 == 0)
        {
            gmode(4, 100 + i % 150);
        }
        pos(particle.x, particle.y);
        gcopy(3, 16 + particle.x % 2 * 8, 600 + i % 6 * 8, 8, 8);

        if (particle == position_t{0, 0} || weatherbk != gdata_weather)
        {
            particle.x = rnd(windoww);
            particle.y = windowh - inf_verh - 8 - rnd(100);
        }
        else
        {
            particle.x += rnd(3) - 1;
            particle.y -= rnd(2) + i % 5;
            if (particle.y < 0)
            {
                particle = {0, 0};
            }
        }
    }
}



void render_weather_effect()
{
    if (!config::instance().env)
        return;
    if (mdata(14) != 2)
        return;

    switch (gdata_weather)
    {
    case 3: render_weather_effect_rain(); break;
    case 4: render_weather_effect_hard_rain(); break;
    case 2: render_weather_effect_snow(); break;
    case 1: render_weather_effect_etherwind(); break;
    default: break;
    }

    weatherbk = gdata_weather;
    gmode(2);
}



void draw_minimap_pixel(int x, int y)
{
    const auto x2 = 120 * x / mdata(0);
    const auto y2 = 84 * y / mdata(1);
    pos(inf_radarx + x2, inf_radary + y2);
    gcopy(3, 688 + x2, 528 + y2, raderw, raderh);
}



void highlight_characters_in_pet_arena()
{
    for (int cc = 0; cc < ELONA_MAX_CHARACTERS; ++cc)
    {
        if (cdata[cc].state != 1)
            continue;
        if (cc == 0)
            continue;
        snail::color color{0};
        if (cdata[cc].relationship == 10)
        {
            color = {127, 127, 255, 32};
        }
        else if (cdata[cc].relationship == -3)
        {
            color = {255, 127, 127, 32};
        }
        else
        {
            continue;
        }
        const int x = (cdata[cc].position.x - scx) * inf_tiles + inf_screenx;
        const int y = (cdata[cc].position.y - scy) * inf_tiles + inf_screeny;
        if (0 <= x && x - inf_screenx < (inf_screenw - 1) * inf_tiles && 0 <= y
            && y < (inf_screenh - 1) * inf_tiles)
        {
            boxf(
                x,
                y * (y > 0),
                inf_tiles,
                inf_tiles + (y < 0) * inf_screeny,
                color);
            if (cc == camera)
            {
                gmode(4, 120);
                pos(x + 36, y + 32);
                gcopy(3, 240, 410, 24, 16);
                gmode(2);
            }
        }
    }
}



void render_pc_position_in_minimap()
{
    const auto x = clamp(120 * cdata[0].position.x / mdata(0), 2, 112);
    const auto y = clamp(84 * cdata[0].position.y / mdata(1), 2, 76);

    raderx = x;
    radery = y;
    pos(inf_radarx + x, inf_radary + y);
    gcopy(3, 15, 338, 6, 6);
}



void render_stair_positions_in_minimap()
{
    for (int y = 0; y < mdata(1); ++y)
    {
        for (int x = 0; x < mdata(0); ++x)
        {
            int sx = clamp(120 * x / mdata(0), 2, 112);
            int sy = clamp(84 * y / mdata(1), 2, 76);
            if (map(x, y, 6) / 1000 % 100 == 11)
            {
                // Downstairs
                pos(inf_radarx + sx, inf_radary + sy);
                gcopy(3, 15, 338, 6, 6);
            }
            else if (map(x, y, 6) / 1000 % 100 == 10)
            {
                // Upstairs
                pos(inf_radarx + sx, inf_radary + sy);
                gcopy(3, 15, 338, 6, 6);
            }
        }
    }
}



} // namespace



namespace elona
{

int msgy = 0;
int evx = 0;
int evy = 0;
int evtiles = 0;
int evscrh = 0;
int evscrw = 0;

position_t gmes(
    const std::string& text,
    int x_base,
    int y_base,
    int width,
    const snail::color& text_color_base,
    bool shadow)
{
    int font_size = 14;
    font(font_size - en * 2);

    const auto message = text + u8"$end";
    int x = x_base;
    int y = y_base;
    size_t pos = 0;
    snail::color text_color = text_color_base;

    while (message.find(u8"$end", pos) != pos)
    {
        bool wait_to_break_line = false;
        uint8_t first = message[pos];
        size_t byte;
        if (first <= 0x7F)
            byte = 1;
        else if (first >= 0xc2 && first <= 0xdf)
            byte = 2;
        else if (first >= 0xe0 && first <= 0xef)
            byte = 3;
        else if (first >= 0xf0 && first <= 0xf7)
            byte = 4;
        else if (first >= 0xf8 && first <= 0xfb)
            byte = 5;
        else if (first >= 0xfc && first <= 0xfd)
            byte = 6;
        else
            byte = 1;
        std::string m_ = strmid(message, pos, byte);
        pos += byte;
        if (m_ == u8"。" || m_ == u8"、" || m_ == u8"」" || m_ == u8"』"
            || m_ == u8"！" || m_ == u8"？" || m_ == u8"…")
        {
            wait_to_break_line = true;
        }
        else if (m_ == u8"<")
        {
            const auto tag = strmid(message, pos, instr(message, pos, u8">"));
            pos += instr(message, pos, u8">") + 1;
            if (tag == u8"emp1")
            {
                font(font_size - en * 2, snail::font_t::style_t::underline);
                text_color = {50, 50, 255};
            }
            else if (tag == u8"emp2")
            {
                font(font_size - en * 2, snail::font_t::style_t::bold);
                text_color = {40, 130, 40};
            }
            else if (tag == u8"title1")
            {
                font_size = 12;
                font(font_size - en * 2, snail::font_t::style_t::bold);
                text_color = {100, 50, 50};
            }
            else if (tag == u8"def")
            {
                font_size = 14;
                font(font_size - en * 2);
                text_color = text_color_base;
            }
            else if (tag == u8"p")
            {
                y += 24;
                x = x_base;
            }
            else if (tag == u8"br")
            {
                y += 16;
                x = x_base;
            }
            else if (tag == u8"b")
            {
                font(font_size - en * 2, snail::font_t::style_t::bold);
            }
            else if (tag == u8"green")
            {
                text_color = {20, 120, 20};
            }
            else if (tag == u8"red")
            {
                text_color = {120, 20, 20};
            }
            else if (tag == u8"col")
            {
                text_color = text_color_base;
            }
            continue;
        }
        if (m_ == u8"^")
        {
            m_ = strmid(message, pos, 1);
            ++pos;
        }
        if (!wait_to_break_line)
        {
            if (x >= x_base + width)
            {
                x = x_base;
                y += font_size + 2;
            }
        }
        if (shadow)
        {
            color(180, 160, 140);
            elona::pos(x + 1, y + 1);
            mes(m_);
            color(0, 0, 0);
        }
        color(text_color.r, text_color.g, text_color.b);
        elona::pos(x, y);
        mes(m_);
        color(0, 0, 0);
        x += font_size / 2 * (byte == 1 ? 1 : 2);
    }

    return {x_base, y + font_size + 4};
}



void initialize_ui_constants()
{
    inf_clockarrowx = inf_clockx + 62;
    inf_clockarrowy = inf_clocky + 48;
    inf_barh = 16;
    inf_msgh = 72;
    inf_verh = inf_barh + inf_msgh;
    inf_msgline = 4;
    inf_radarx = 1;
    inf_radarw = 136;
    inf_screenw = windoww / inf_tiles + (windoww % inf_tiles != 0);
    if (windowh > 1200)
    {
        windowh = 1200;
    }
    inf_screenh = (windowh - inf_verh) / inf_tiles;
    if ((windowh - inf_verh) % inf_tiles != 0)
    {
        ++inf_screenh;
    }
    if (inf_vertype == 0)
    {
        inf_ver = 0;
        inf_bary = 0;
        inf_msgy = inf_ver + inf_barh;
        inf_screeny = inf_verh;
        inf_clocky = windowh - inf_clockh;
        inf_radary = 1;
    }
    else
    {
        inf_screeny = 0;
        if ((windowh - inf_verh) % inf_tiles != 0)
        {
            inf_screeny = 0 - inf_tiles + (windowh - inf_verh) % inf_tiles;
        }
        inf_ver = windowh - inf_verh;
        inf_bary = windowh - inf_barh;
        inf_msgy = inf_ver;
        inf_clocky = 0;
        inf_radary = windowh - 86;
    }
    scposy = inf_screenh / 2 - 1;
    inf_hpx = (windoww - 84) / 2 - 100;
    inf_hpy = inf_ver - 12;
    inf_mpx = (windoww - 84) / 2 + 40;
    inf_mpy = inf_ver - 12;
    inf_msgx = inf_radarw;
    inf_msgspace = 15;
    int inf_maxmsglen_i =
        std::max((windoww - inf_msgx - 28) / inf_mesfont * 2 - 1, 0);
    inf_maxmsglen = static_cast<size_t>(inf_maxmsglen_i);
    inf_maxlog = (inf_msgy - 100) / inf_msgspace + 3;
    inf_very = windowh - inf_verh;
    screenmsgy = inf_screeny + inf_tiles * 2;
    prompty = (windowh - inf_verh - 30) / 2 - 4;
    promptx = (windoww - 10) / 2 + 3;
}



void update_entire_screen()
{
    update_screen_hud();
    update_minimap();
    update_screen();
}



void update_screen()
{
    gmode(2);
    if (mode == 9)
    {
        screen_txtadv();
    }
    else
    {
        sxfix = 0;
        syfix = 0;
        update_scrolling_info();
        update_slight();
        label_1433();
    }

    render_hud();
    if (autoturn == 1)
    {
        render_autoturn_animation();
    }
    else
    {
        firstautoturn = 1;
        racount = 0;
    }
    if (screenupdate != -1)
    {
        redraw();
    }
    screenupdate = 0;
}



void screen_txtadv()
{
    gmode(0);
    pos(0, 0);
    if (txtadvscreenupdate == 1)
    {
        gcopy(4, 0, 0, windoww, windowh - inf_verh);
    }
    else
    {
        gcopy(4, 0, 0, windoww, 100);
    }
    gmode(2);
    for (int i = 0; i < 4; ++i)
    {
        font(13 - en * 2);
        color(250, 250, 250);
        if (i == 0)
        {
            sx = 265;
            sy = 8;
            pos(sx - 30, 5);
            gcopy(3, 192, 360, 24, 16);
            pos(sx + atxinfon(0).size() * 13 / 2 + 14, 5);
            gcopy(3, 216, 360, 24, 16);
        }
        else
        {
            sx = 220;
            sy = 10 + i * 14;
        }
        pos(sx, sy);
        mes(atxinfon(i));
    }
    txtadvscreenupdate = 1;
}



void update_minimap()
{
    for (int y = 0; y < mdata(1); ++y)
    {
        for (int x = 0; x < mdata(0); ++x)
        {
            if (map(x, y, 2) == map(x, y, 0))
            {
                draw_minimap_pixel(x, y);
            }
        }
    }
}



void label_1420()
{
    gmode(2);
    label_1433();
    render_hud();
    redraw();
    screenupdate = 0;
}



void render_hud()
{
    int ap3 = 0;
    int ap2 = 0;
    font(12 - en * 2, snail::font_t::style_t::bold);
    pos(inf_hpx, inf_hpy);
    gcopy(3, 312, 504, 104, 15);
    pos(inf_mpx, inf_mpy);
    gcopy(3, 312, 504, 104, 15);
    if (cdata[0].hp > 0) // TODO coupling
    {
        ap = cdata[0].hp * 84 / cdata[0].max_hp;
        if (ap > 100)
        {
            ap = 100;
        }
        pos(inf_hpx + 16, inf_hpy + 5);
        gcopy(3, 412 - ap, 520, ap, 6);
    }
    if (cdata[0].mp > 0)
    {
        ap = cdata[0].mp * 84 / cdata[0].max_mp;
        if (ap > 100)
        {
            ap = 100;
        }
        pos(inf_mpx + 16, inf_mpy + 5);
        gcopy(3, 532 - ap, 520, ap, 6);
    }
    if (gdata_mount != 0)
    {
        if (cdata[gdata_mount].state == 1)
        {
            pos(inf_hpx - 120, inf_hpy);
            gcopy(3, 312, 504, 104, 15);
            ap = cdata[gdata_mount].hp * 84 / cdata[gdata_mount].max_hp;
            if (ap > 100)
            {
                ap = 100;
            }
            pos(inf_hpx - 120 + 16, inf_hpy + 5);
            gcopy(3, 412 - ap, 520, ap, 6);
        }
    }
    sx = inf_hpx + 16;
    sy = inf_hpy - 8;
    bmes(""s + cdata[0].hp + u8"("s + cdata[0].max_hp + u8")"s, sx + 4, sy);
    sx = inf_mpx + 16;
    sy = inf_mpy - 8;
    bmes(""s + cdata[0].mp + u8"("s + cdata[0].max_mp + u8")"s, sx + 4, sy);
    font(13 - en * 2);
    sy = inf_bary + 2 + vfix;
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        sx = inf_radarw + cnt * 47 + 168 - 2;
        if (cnt < 8)
        {
            if (cdata[0].attr_adjs[cnt] < 0)
            {
                color(200, 0, 0);
            }
            else
            {
                color(0, 0, 0);
            }
            pos(sx, sy);
            gcopy(3, 0, 440, 28, 16);
            mes(sdata(10 + cnt, 0)); // TODO coupling
            color(0, 0, 0);
        }
        else if (cnt == 8)
        {
            pos(sx + 8, sy);
            gcopy(3, 0, 440, 34, 16);
            if (gspdorg > gspd)
            {
                color(200, 0, 0);
            }
            else if (gspdorg < gspd)
            {
                color(0, 120, 0);
            }
            else
            {
                color(0, 0, 0);
            }
            mes(""s + gspd);
            color(0, 0, 0);
        }
        else
        {
            pos(sx + 14, sy);
            gcopy(3, 0, 440, 64, 16);
            mes(""s + cdata[0].dv + u8"/"s + cdata[0].pv);
        }
    }
    font(13 - en * 2);
    sy = inf_ver - 16;
    sx = windoww - 240;
    pos(sx, sy);
    gcopy(3, 0, 392, 24, 24);
    bmes(""s + cdata[0].gold + u8" gp"s, sx + 28, sy + 2);
    sx = windoww - 120;
    pos(sx, sy);
    gcopy(3, 24, 392, 24, 24);
    bmes(""s + cdata[0].platinum_coin + u8" pp"s, sx + 28, sy + 2);
    pos(4, inf_ver - 16);
    gcopy(3, 48, 392, 24, 24);
    bmes(
        u8"Lv"s + cdata[0].level + u8"/"s
            + (cdata[0].required_experience - cdata[0].experience),
        32,
        inf_ver - 14);
    if (cdata[0].position.x < 6)
    {
        if (mode != 9)
        {
            if (mdata(6) != 1)
            {
                if (cdata[0].continuous_action_id == 0)
                {
                    gmode(4, 150);
                }
            }
        }
    }
    sx = 8;
    sy = inf_ver - 50;
    if (cdata[0].nutrition >= 12000)
    {
        pos(sx, sy);
        gcopy(3, 0, 416, 50 + en * 30, 15);
        pos(sx + 6, sy + 1);
        mes(i18n::_(u8"ui", u8"hunger", u8"_12"));
        sy -= 20;
    }
    else if (cdata[0].nutrition >= 1000)
    {
        if (cdata[0].nutrition <= 4000)
        {
            color(200, 0, 0);
        }
        if (i18n::_(u8"ui", u8"hunger", u8"_"s + (cdata[0].nutrition / 1000))
            != ""s)
        {
            pos(sx, sy);
            gcopy(3, 0, 416, 50 + en * 30, 15);
            pos(sx + 6, sy + 1);
            mes(i18n::_(
                u8"ui", u8"hunger", u8"_"s + (cdata[0].nutrition / 1000)));
            sy -= 20;
        }
        color(0, 0, 0);
    }
    else
    {
        color(250, 0, 0);
        pos(sx, sy);
        gcopy(3, 0, 416, 50 + en * 30, 15);
        pos(sx + 6, sy + 1);
        mes(i18n::_(u8"ui", u8"hunger", u8"_0"));
        color(0, 0, 0);
        sy -= 20;
    }
    if (cdata[0].sick != 0)
    {
        color(80, 120, 0);
        if (cdata[0].sick >= 30)
        {
            pos(sx, sy);
            gcopy(3, 0, 416, 50 + en * 30, 15);
            pos(sx + 6, sy + 1);
            mes(i18n::_(u8"ui", u8"sick", u8"_1"));
            sy -= 20;
        }
        else
        {
            pos(sx, sy);
            gcopy(3, 0, 416, 50 + en * 30, 15);
            pos(sx + 6, sy + 1);
            mes(i18n::_(u8"ui", u8"sick", u8"_0"));
            sy -= 20;
        }
        color(0, 0, 0);
    }
    if (cdata[0].poisoned != 0)
    {
        color(0, 150, 0);
        if (cdata[0].poisoned >= 30)
        {
            pos(sx, sy);
            gcopy(3, 0, 416, 50 + en * 30, 15);
            pos(sx + 6, sy + 1);
            mes(i18n::_(u8"ui", u8"poison", u8"_1"));
            sy -= 20;
        }
        else
        {
            pos(sx, sy);
            gcopy(3, 0, 416, 50 + en * 30, 15);
            pos(sx + 6, sy + 1);
            mes(i18n::_(u8"ui", u8"poison", u8"_0"));
            sy -= 20;
        }
        color(0, 0, 0);
    }
    if (cdata[0].sleep != 0)
    {
        color(0, 50, 50);
        if (cdata[0].sleep >= 30)
        {
            pos(sx, sy);
            gcopy(3, 0, 416, 50 + en * 30, 15);
            pos(sx + 6, sy + 1);
            mes(i18n::_(u8"ui", u8"sleep", u8"_1"));
            sy -= 20;
        }
        else
        {
            pos(sx, sy);
            gcopy(3, 0, 416, 50 + en * 30, 15);
            pos(sx + 6, sy + 1);
            mes(i18n::_(u8"ui", u8"sleep", u8"_0"));
            sy -= 20;
        }
        color(0, 0, 0);
    }
    if (cdata[0].blind != 0)
    {
        color(100, 100, 0);
        pos(sx, sy);
        gcopy(3, 0, 416, 50 + en * 30, 15);
        pos(sx + 6, sy + 1);
        mes(i18n::_(u8"ui", u8"blind"));
        color(0, 0, 0);
        sy -= 20;
    }
    if (cdata[0].paralyzed != 0)
    {
        color(0, 100, 100);
        pos(sx, sy);
        gcopy(3, 0, 416, 50 + en * 30, 15);
        pos(sx + 6, sy + 1);
        mes(i18n::_(u8"ui", u8"paralyzed"));
        color(0, 0, 0);
        sy -= 20;
    }
    if (cdata[0].choked != 0)
    {
        color(0, 100, 100);
        pos(sx, sy);
        gcopy(3, 0, 416, 50 + en * 30, 15);
        pos(sx + 6, sy + 1);
        mes(i18n::_(u8"ui", u8"choked"));
        color(0, 0, 0);
        sy -= 20;
    }
    if (cdata[0].confused != 0)
    {
        color(100, 0, 100);
        pos(sx, sy);
        gcopy(3, 0, 416, 50 + en * 30, 15);
        pos(sx + 6, sy + 1);
        mes(i18n::_(u8"ui", u8"confused"));
        color(0, 0, 0);
        sy -= 20;
    }
    if (cdata[0].fear != 0)
    {
        color(100, 0, 100);
        pos(sx, sy);
        gcopy(3, 0, 416, 50 + en * 30, 15);
        pos(sx + 6, sy + 1);
        mes(i18n::_(u8"ui", u8"fear"));
        color(0, 0, 0);
        sy -= 20;
    }
    if (cdata[0].dimmed != 0)
    {
        color(0, 100, 100);
        if (cdata[0].dimmed >= 60)
        {
            pos(sx, sy);
            gcopy(3, 0, 416, 50 + en * 30, 15);
            pos(sx + 6, sy + 1);
            mes(i18n::_(u8"ui", u8"dimmed", u8"_2"));
            sy -= 20;
        }
        else if (cdata[0].dimmed >= 30)
        {
            pos(sx, sy);
            gcopy(3, 0, 416, 50 + en * 30, 15);
            pos(sx + 6, sy + 1);
            mes(i18n::_(u8"ui", u8"dimmed", u8"_1"));
            sy -= 20;
        }
        else
        {
            pos(sx, sy);
            gcopy(3, 0, 416, 50 + en * 30, 15);
            pos(sx + 6, sy + 1);
            mes(i18n::_(u8"ui", u8"dimmed", u8"_0"));
            sy -= 20;
        }
        color(0, 0, 0);
    }
    if (cdata[0].furious != 0)
    {
        color(150, 0, 0);
        if (cdata[0].furious >= 30)
        {
            pos(sx, sy);
            gcopy(3, 0, 416, 50 + en * 30, 15);
            pos(sx + 6, sy + 1);
            mes(i18n::_(u8"ui", u8"angry", u8"_1"));
            sy -= 20;
        }
        else
        {
            pos(sx, sy);
            gcopy(3, 0, 416, 50 + en * 30, 15);
            pos(sx + 6, sy + 1);
            mes(i18n::_(u8"ui", u8"angry", u8"_0"));
            sy -= 20;
        }
        color(0, 0, 0);
    }
    if (cdata[0].bleeding != 0)
    {
        color(150, 0, 0);
        if (cdata[0].bleeding >= 20)
        {
            pos(sx, sy);
            gcopy(3, 0, 416, 50 + en * 30, 15);
            pos(sx + 6, sy + 1);
            mes(i18n::_(u8"ui", u8"bleeding", u8"_2"));
            sy -= 20;
        }
        else if (cdata[0].bleeding >= 10)
        {
            pos(sx, sy);
            gcopy(3, 0, 416, 50 + en * 30, 15);
            pos(sx + 6, sy + 1);
            mes(i18n::_(u8"ui", u8"bleeding", u8"_1"));
            sy -= 20;
        }
        else
        {
            pos(sx, sy);
            gcopy(3, 0, 416, 50 + en * 30, 15);
            pos(sx + 6, sy + 1);
            mes(i18n::_(u8"ui", u8"bleeding", u8"_0"));
            sy -= 20;
        }
        color(0, 0, 0);
    }
    if (cdata[0].insane != 0)
    {
        color(150, 100, 0);
        if (cdata[0].insane >= 50)
        {
            pos(sx, sy);
            gcopy(3, 0, 416, 50 + en * 30, 15);
            pos(sx + 6, sy + 1);
            mes(i18n::_(u8"ui", u8"insane", u8"_2"));
            sy -= 20;
        }
        else if (cdata[0].insane >= 25)
        {
            pos(sx, sy);
            gcopy(3, 0, 416, 50 + en * 30, 15);
            pos(sx + 6, sy + 1);
            mes(i18n::_(u8"ui", u8"insane", u8"_1"));
            sy -= 20;
        }
        else
        {
            pos(sx, sy);
            gcopy(3, 0, 416, 50 + en * 30, 15);
            pos(sx + 6, sy + 1);
            mes(i18n::_(u8"ui", u8"insane", u8"_0"));
            sy -= 20;
        }
        color(0, 0, 0);
    }
    if (cdata[0].drunk != 0)
    {
        color(100, 0, 100);
        pos(sx, sy);
        gcopy(3, 0, 416, 50 + en * 30, 15);
        pos(sx + 6, sy + 1);
        mes(i18n::_(u8"ui", u8"drunk"));
        color(0, 0, 0);
        sy -= 20;
    }
    if (cdata[0].wet != 0)
    {
        color(0, 0, 160);
        pos(sx, sy);
        gcopy(3, 0, 416, 50 + en * 30, 15);
        pos(sx + 6, sy + 1);
        mes(i18n::_(u8"ui", u8"wet"));
        color(0, 0, 0);
        sy -= 20;
    }
    if (cdata[0].gravity != 0)
    {
        color(0, 80, 80);
        pos(sx, sy);
        gcopy(3, 0, 416, 50 + en * 30, 15);
        pos(sx + 6, sy + 1);
        mes(i18n::_(u8"ui", u8"gravity"));
        color(0, 0, 0);
        sy -= 20;
    }
    if (gdata_continuous_active_hours >= 15)
    {
        if (gdata_continuous_active_hours >= 50)
        {
            color(255, 0, 0);
            pos(sx, sy);
            gcopy(3, 0, 416, 50 + en * 30, 15);
            pos(sx + 6, sy + 1);
            mes(i18n::_(u8"ui", u8"sleepy", u8"_2"));
            sy -= 20;
        }
        else if (gdata_continuous_active_hours >= 30)
        {
            color(100, 100, 0);
            pos(sx, sy);
            gcopy(3, 0, 416, 50 + en * 30, 15);
            pos(sx + 6, sy + 1);
            mes(i18n::_(u8"ui", u8"sleepy", u8"_1"));
            sy -= 20;
        }
        else
        {
            color(0, 0, 0);
            pos(sx, sy);
            gcopy(3, 0, 416, 50 + en * 30, 15);
            pos(sx + 6, sy + 1);
            mes(i18n::_(u8"ui", u8"sleepy", u8"_0"));
            sy -= 20;
        }
        color(0, 0, 0);
    }
    if (cdata[0].sp < 50)
    {
        if (cdata[0].sp < 0)
        {
            color(120, 120, 0);
            pos(sx, sy);
            gcopy(3, 0, 416, 50 + en * 30, 15);
            pos(sx + 6, sy + 1);
            mes(i18n::_(u8"ui", u8"tired", u8"_2"));
            sy -= 20;
        }
        else if (cdata[0].sp < 25)
        {
            color(80, 80, 0);
            pos(sx, sy);
            gcopy(3, 0, 416, 50 + en * 30, 15);
            pos(sx + 6, sy + 1);
            mes(i18n::_(u8"ui", u8"tired", u8"_1"));
            sy -= 20;
        }
        else
        {
            color(60, 60, 0);
            pos(sx, sy);
            gcopy(3, 0, 416, 50 + en * 30, 15);
            pos(sx + 6, sy + 1);
            mes(i18n::_(u8"ui", u8"tired", u8"_0"));
            sy -= 20;
        }
        color(0, 0, 0);
    }
    if (cdata[0].inventory_weight_type != 0)
    {
        color(
            0,
            cdata[0].inventory_weight_type * 40,
            cdata[0].inventory_weight_type * 40);
        pos(sx, sy);
        gcopy(3, 0, 416, 50 + en * 30, 15);
        pos(sx + 6, sy + 1);
        mes(i18n::_(
            u8"ui", u8"burden", u8"_"s + cdata[0].inventory_weight_type));
        color(0, 0, 0);
        sy -= 20;
    }

    if (foobar_data.is_autodig_enabled)
    {
        pos(sx, sy);
        gcopy(3, 0, 416, 50 + en * 30, 15);
        pos(sx + 6, sy + 1);
        mes(i18n::_(u8"ui", u8"autodig", u8"mode"));
        sy -= 20;
    }

    pos(inf_clockx, inf_clocky);
    gcopy(3, 448, 408, inf_clockw, inf_clockh);
    pos(inf_clockx + 78, inf_clocky + 8);
    gcopy(3, 448, 376, 128, 24);
    gmode(4, 180);
    sx = windoww - 40;
    sy = inf_ver - 40;
    for (int cnt = 0; cnt < 16; ++cnt)
    {
        if (cdata[0].buffs[cnt].id == 0)
        {
            break;
        }
        pos(sx, sy);
        gcopy(5, cdata[0].buffs[cnt].id * 32, 1120, 32, 32);
        pos(sx + 3, sy + 19);
        mes(cdata[0].buffs[cnt].turns);
        color(255, 255, 255);
        pos(sx + 2, sy + 18);
        mes(cdata[0].buffs[cnt].turns);
        color(0, 0, 0);
        sy -= 32;
    }
    pos(inf_clockarrowx, inf_clockarrowy);
    gmode(2);
    grotate(3, 0, 288, 48, 48, 0.0174532925199433 * (gdata_hour * 30));
    pos(inf_clockw - 3, inf_clocky + 17 + vfix);
    mes(""s + gdata_year + u8"/"s + gdata_month + u8"/"s + gdata_day);
    bmes(
        i18n::_(u8"ui", u8"time", u8"_"s + gdata_hour / 4) + u8" "s
            + i18n::_(u8"ui", u8"weather", u8"_"s + gdata_weather),
        inf_clockw + 6,
        inf_clocky + 35);
    ap3 = 0;
    for (int cnt = 0; cnt < 3; ++cnt)
    {
        ap = gdata((750 + cnt)) % 10000;
        if (ap == 0)
        {
            continue;
        }
        ap2 = gdata((750 + cnt)) / 10000;
        if (cdata[ap2].state != 1)
        {
            if (ap2 != 0)
            {
                gdata(750 + cnt) = 0;
            }
            continue;
        }
        bmes(
            ""s
                + strmid(
                      i18n::_(u8"ability", std::to_string(ap), u8"name"), 0, 6),
            16,
            inf_clocky + 155 - ap3 * 16);
        bmes(
            ""s + sdata.get(ap, ap2).original_level + u8"."s
                + std::to_string(1000 + sdata.get(ap, ap2).experience % 1000)
                      .substr(1),
            66,
            inf_clocky + 155 - ap3 * 16);
        ++ap3;
    }
    if (config::instance().hp_bar)
    {
        show_hp_bar(
            config::instance().hp_bar == 1 ? show_hp_bar_side::left_side
                                           : show_hp_bar_side::right_side,
            inf_clocky);
    }

    show_damage_popups();
}



void load_continuous_action_animation()
{
    gsel(9);
    pos(0, 0);
    if (cdata[0].continuous_action_id == 5)
    {
        picload(filesystem::dir::graphic() / u8"anime1.bmp");
    }
    if (cdata[0].continuous_action_id == 7)
    {
        if (rowactre)
        {
            picload(filesystem::dir::graphic() / u8"anime2.bmp");
        }
    }
    if (cdata[0].continuous_action_id == 8)
    {
        picload(filesystem::dir::graphic() / u8"anime3.bmp");
    }
    if (cdata[0].continuous_action_id == 9)
    {
        picload(filesystem::dir::graphic() / u8"anime4.bmp");
    }
    gsel(0);
}



void render_autoturn_animation()
{
    if (racount == 0 && config::instance().animewait != 0)
    {
        load_continuous_action_animation();
    }
    if (msgtemp != ""s
        || (cdata[0].continuous_action_id == 7 && rowactre == 0
            && fishanime == 0))
    {
        label_1433();
        msgtemp = "";
        render_hud();
    }
    if (cdata[0].continuous_action_id == 7)
    {
        if (rowactre == 0 && config::instance().animewait != 0)
        {
            render_fishing_animation();
        }
    }
    sx = windoww - 156;
    sy = inf_ver - 30;
    int w = 148;
    int h = 25;

    window2(sx, sy, w, h, 0, 5);
    font(13 - en * 2, snail::font_t::style_t::bold);
    bmes(u8"AUTO TURN"s, sx + 43, sy + 6, {235, 235, 235});
    pos(sx + 18, sy + 12);
    gmode(2);
    grotate(3, 72, 392, 24, 24, 0.0174532925199433 * (gdata_minute / 4 % 2 * 90));

    if (cdata[0].continuous_action_id == 9 || cdata[0].continuous_action_id == 5
        || cdata[0].continuous_action_id == 8
        || (cdata[0].continuous_action_id == 7 && rowactre != 0))
    {
        if (config::instance().animewait != 0)
        {
            window2(sx, sy - 104, 148, 101, 0, 5);
            if (racount % 15 == 0)
            {
                for (int cnt = 0; cnt < 10; ++cnt)
                {
                    gmode(0);
                    pos(sx + 2, sy - 102);
                    if (cdata[0].continuous_action_id == 5)
                    {
                        if (cnt == 2)
                        {
                            snd(52);
                        }
                        gcopy(9, cnt / 2 % 5 * 144, 0, 144, 96);
                        await(config::instance().animewait * 2);
                    }
                    if (cdata[0].continuous_action_id == 7)
                    {
                        if (racount == 0)
                        {
                            if (cnt == 0)
                            {
                                snd(57);
                            }
                        }
                        gcopy(9, cnt / 3 % 3 * 144, 0, 144, 96);
                        await(config::instance().animewait * 2.5);
                    }
                    if (cdata[0].continuous_action_id == 8)
                    {
                        if (cnt == 4)
                        {
                            snd(55);
                        }
                        gcopy(9, cnt / 2 % 3 * 144, 0, 144, 96);
                        await(config::instance().animewait * 2.75);
                    }
                    if (cdata[0].continuous_action_id == 9)
                    {
                        if (cnt == 2)
                        {
                            snd(54);
                        }
                        gcopy(9, cnt / 2 % 4 * 144, 0, 144, 96);
                        await(config::instance().animewait * 3);
                    }
                    redraw();
                }
            }
            else
            {
                gcopy(9, 0, 0, 144, 96);
            }
        }
        ++racount;
        redraw();
    }
    if (firstautoturn == 1)
    {
        redraw();
        firstautoturn = 0;
    }
    gmode(2);
}



void draw_caption()
{
    int msgx = 0;
    gmode(0);
    font(16 - en * 2);
    color(245, 245, 245);
    msgx = 20;
    msgy = 30;
    sx = 760;
    sx = s(0).size() * 8 + 45;
    if (sx > 760)
    {
        sx = 760;
    }
    ap = sx / 128 + 1;
    for (int cnt = 0, cnt_end = (ap); cnt < cnt_end; ++cnt)
    {
        if (cnt == sx / 128)
        {
            ap = sx % 128;
        }
        else
        {
            ap = 128;
        }
        pos(cnt * 128 + msgx, msgy);
        gcopy(3, 672, 477, ap, 3);
        pos(cnt * 128 + msgx, msgy + 2);
        gcopy(3, 672, 480, ap, 22);
        pos(cnt * 128 + msgx, msgy + 22);
        gcopy(3, 672, 477, ap, 2);
    }
    pos(msgx + 18, msgy + 4);
    mes(s);
    gmode(2);
}



void update_scrolling_info()
{
    if (scposval == 0)
    {
        if (scroll)
        {
            sx(0) = cdata[0].next_position.x - scx;
            sx(1) = cdata[0].next_position.x;
            sy(0) = cdata[0].next_position.y - scy;
            sy(1) = cdata[0].next_position.y;
        }
        else
        {
            sx(0) = cdata[0].position.x - scx;
            sx(1) = cdata[0].position.x;
            sy(0) = cdata[0].position.y - scy;
            sy(1) = cdata[0].position.y;
        }
    }
    else
    {
        sx(0) = tlocx - scx;
        sx(1) = tlocx;
        sy(0) = tlocy - scy;
        sy(1) = tlocy;
    }
    if (gdata_current_map == 40)
    {
        sx(0) = cdata[camera].position.x - scx;
        sx(1) = cdata[camera].position.x;
        sy(0) = cdata[camera].position.y - scy;
        sy(1) = cdata[camera].position.y;
    }
    if (config::instance().alwayscenter)
    {
        scx = sx + scx - inf_screenw / 2;
        scy = sy + scy - inf_screenh / 2;
    }
    else
    {
        if (sy < scposy)
        {
            scy = sy(1) - scposy;
        }
        if (sx < 6)
        {
            scx = sx(1) - 6;
        }
        if (sx > inf_screenw - 7)
        {
            scx = sx(1) - (inf_screenw - 7);
        }
        if (sy > inf_screenh - scposy - 1)
        {
            scy = sy(1) - (inf_screenh - scposy - 1);
        }
    }
    if (scx + inf_screenw >= mdata(0))
    {
        scx = mdata(0) - inf_screenw;
    }
    if (scy + inf_screenh >= mdata(1))
    {
        scy = mdata(1) - inf_screenh;
    }
    if (scy < 0)
    {
        scy = 0;
    }
    if (scx < 0)
    {
        scx = 0;
    }
}



void update_slight()
{
    int ly = 0;
    int lx = 0;
    slight.clear();
    ++msync;

    position_t center{cdata[0].position.x - (fov_max + 2) / 2,
                      (fov_max + 2) / 2 - cdata[0].position.y};
    sy(2) = cdata[0].position.y - fov_max / 2;
    sy(3) = cdata[0].position.y + fov_max / 2;

    if (config::instance().scroll)
    {
        repw(0) = inf_screenw + 2;
        repw(1) = scx - 1;
        reph(0) = inf_screenh + 2;
        reph(1) = scy - 1;
    }
    else
    {
        repw(0) = inf_screenw;
        repw(1) = scx;
        reph(0) = inf_screenh;
        reph(1) = scy;
    }
    ly = 1 + (config::instance().scroll == 0);
    for (int cnt = reph(1), cnt_end = cnt + (reph); cnt < cnt_end; ++cnt)
    {
        sy = cnt;
        lx = 1 + (config::instance().scroll == 0);
        if (sy < 0 || sy >= mdata(1))
        {
            for (int cnt = repw(1), cnt_end = cnt + (repw); cnt < cnt_end;
                 ++cnt)
            {
                slight(lx + 1, ly) += 1;
                slight(lx - 1, ly) += 8;
                slight(lx, ly - 1) += 2;
                slight(lx, ly + 1) += 4;
                slight(lx + 1, ly + 1) += 16;
                slight(lx - 1, ly - 1) += 32;
                slight(lx + 1, ly - 1) += 64;
                slight(lx - 1, ly + 1) += 128;
                ++lx;
            }
            ++ly;
            continue;
        }
        for (int cnt = repw(1), cnt_end = cnt + (repw); cnt < cnt_end; ++cnt)
        {
            sx = cnt;
            if (sx < 0 || sx >= mdata(0))
            {
                slight(lx + 1, ly) += 1;
                slight(lx - 1, ly) += 8;
                slight(lx, ly - 1) += 2;
                slight(lx, ly + 1) += 4;
                slight(lx + 1, ly + 1) += 16;
                slight(lx - 1, ly - 1) += 32;
                slight(lx + 1, ly - 1) += 64;
                slight(lx - 1, ly + 1) += 128;
                ++lx;
                continue;
            }
            if (gdata_current_map == 40)
            {
                goto label_1430_internal;
            }
            if (cdata[0].blind != 0)
            {
                if (sx != cdata[0].position.x || sy != cdata[0].position.y)
                {
                    goto label_1431_internal;
                }
            }
            if (sy(2) <= sy && sy <= sy(3))
            {
                if (sx >= fovlist[sy + center.y][0] + center.x
                    && sx < fovlist[sy + center.y][1] + center.x)
                {
                    if (fov_los(
                            cdata[0].position.x, cdata[0].position.y, sx, sy))
                    {
                    label_1430_internal:
                        mapsync(sx, sy) = msync;
                        if (map(sx, sy, 1) != 0)
                        {
                            cdata[map(sx, sy, 1) - 1].vision_flag = msync;
                        }
                        if (map(sx, sy, 2) != map(sx, sy, 0))
                        {
                            map(sx, sy, 2) = map(sx, sy, 0);
                            draw_minimap_pixel(sx, sy);
                        }
                        map(sx, sy, 5) = map(sx, sy, 4);
                        ++lx;
                        continue;
                    }
                }
            }
        label_1431_internal:
            slight(lx, ly) += 1000;
            slight(lx + 1, ly) += 1;
            slight(lx - 1, ly) += 8;
            slight(lx, ly - 1) += 2;
            slight(lx, ly + 1) += 4;
            slight(lx + 1, ly + 1) += 16;
            slight(lx - 1, ly - 1) += 32;
            slight(lx + 1, ly - 1) += 64;
            slight(lx - 1, ly + 1) += 128;
            ++lx;
        }
        ++ly;
    }
}



void label_1433()
{
    cell_draw();

    if (gdata_current_map == 40)
    {
        highlight_characters_in_pet_arena();
    }

    if (raderx != -1)
    {
        pos(inf_radarx + raderx, inf_radary + radery);
        gcopy(3, 688 + raderx, 528 + radery, 6, 6);
    }

    render_pc_position_in_minimap();

    if (debug::voldemort)
    {
        render_stair_positions_in_minimap();
    }

    render_weather_effect();
}



void label_1438()
{
    int scxbk2 = 0;
    int scybk2 = 0;
    if (std::abs(cdata[0].next_position.x - cdata[0].position.x) > 1)
    {
        return;
    }
    if (std::abs(cdata[0].next_position.y - cdata[0].position.y) > 1)
    {
        return;
    }
    scrollp = config::instance().walkwait;
    if (mdata(6) == 1)
    {
        scrollp = 6;
        keybd_wait = 1000;
        if (chipm(0, map(cdata[0].position.x, cdata[0].position.y, 0)) == 4)
        {
            scrollp = 9;
        }
    }
    else if (keybd_wait > config::instance().startrun)
    {
        scrollp = 3;
        if (config::instance().runscroll == 0)
        {
            return;
        }
        if (keybd_wait >= 100000)
        {
            scrollp = 1;
        }
    }
    scxbk2 = scx;
    scybk2 = scy;
    scroll = 1;
    update_scrolling_info();
    scroll = 0;
    scxbk = scx;
    scybk = scy;
    scx = scxbk2;
    scy = scybk2;
    scrollanime = 1;
    for (int cnt = 1, cnt_end = cnt + (scrollp - 1); cnt < cnt_end; ++cnt)
    {
        if (cnt % 2 == 1)
        {
            ++scrturn;
        }
        sxfix = (cdata[0].next_position.x - cdata[0].position.x) * cnt
            * inf_tiles / scrollp * -1;
        syfix = (cdata[0].next_position.y - cdata[0].position.y) * cnt
            * inf_tiles / scrollp * -1;
        gsel(4);
        pos(0, 0);
        gmode(0);
        gcopy(0, 0, windowh - inf_verh, windoww, inf_tiles);
        gsel(0);
        gmode(2);
        label_1433();
        gmode(0);
        pos(0, windowh - inf_verh);
        gcopy(4, 0, 0, windoww, inf_tiles);
        gmode(2);
        render_hud();
        gmode(2);
        redraw();
        await(40);
    }
    scrollanime = 0;
}



void label_1439()
{
    gsel(3);
    for (int cnt = 0, cnt_end = (mdata(1)); cnt < cnt_end; ++cnt)
    {
        sy = cnt;
        for (int cnt = 0, cnt_end = (mdata(0)); cnt < cnt_end; ++cnt)
        {
            sx = cnt;
            sy(1) = 84 * sy / mdata(1);
            sx(1) = 120 * sx / mdata(0);
            pos(688 + sx(1), 528 + sy(1));
            gcopy(
                2,
                map(sx, sy, 0) % 33 * inf_tiles + sx % 16,
                map(sx, sy, 0) / 33 * inf_tiles + sy % 12,
                raderw,
                raderh);
            pos(688 + sx(1), 528 + sy(1));
            if (chipm(7, map(sx, sy, 0)) & 4)
            {
                boxf(688 + sx(1), 528 + sy(1), raderw, raderh, {0, 0, 0, 100});
            }
        }
    }
    boxf(688, 528, raderw * mdata(0), raderh * mdata(1), {255, 255, 255, 10});
    gsel(0);
}



void fade_out()
{
    gsel(4);
    gmode(0);
    pos(0, 0);
    gcopy(0, 0, 0, windoww, windowh);
    gsel(0);
    gmode(0);
    for (int cnt = 0; cnt < 50; ++cnt)
    {
        await(20);
        boxf(0, 0, windoww, windowh, {0, 0, 0, 5});
        redraw();
    }
    for (int cnt = 0; cnt < 30; ++cnt)
    {
        gmode(4, 10 + cnt * 5);
        await(20);
        pos(0, 0);
        gcopy(4, 0, 0, windoww, windowh);
        redraw();
    }
    gmode(2);
}



void label_1442()
{
    for (int i = 0; i < 50; ++i)
    {
        await(20);
        boxf(0, 0, windoww, windowh, {0, 0, 0, 5});
        redraw();
    }
}



void animation_fade_in()
{
    for (int cnt = 0; cnt < 30; ++cnt)
    {
        gmode(4, 10 + cnt * 5);
        await(20);
        pos(0, 0);
        gcopy(4, 0, 0, windoww, windowh);
        redraw();
    }
    gmode(2);
}



void label_1444()
{
    boxf();
    evx = 12;
    evy = 14;
    evtiles = 48;
    evscrh = windowh / evtiles - 1;
    evscrw = windoww / evtiles + 2;
    label_1445();
    redraw();
}



void label_1445()
{
    for (int cnt = 0, cnt_end = (evscrh); cnt < cnt_end; ++cnt)
    {
        y = cnt;
        dy = cnt + evy;
        if (dy >= mdata(1))
        {
            dy = mdata(1);
        }
        for (int cnt = 0, cnt_end = (evscrw); cnt < cnt_end; ++cnt)
        {
            x = cnt;
            dx = cnt + evx;
            if (dx >= mdata(0))
            {
                dx = mdata(0);
            }
            ap = map(dx, dy, 0);
            pos(x * evtiles, y * evtiles);
            gmode(0);
            gcopy_c(
                2,
                ap % 33 * inf_tiles,
                ap / 33 * inf_tiles,
                inf_tiles,
                inf_tiles,
                evtiles,
                evtiles);
        }
    }
}



void render_fishing_animation()
{
    elona_vector1<int> fishdir;
    int sx2 = 0;
    int sy2 = 0;
    fishdir(0) = 0;
    fishdir(1) = 1;
    fishdir(2) = 3;
    fishdir(3) = 2;
    fishdir = fishdir(cdata[0].direction);
    randomize(cdata[0].turn / 3);
    gmode(2);
    if (fishanime == 4)
    {
        sx = (fishx - scx) * inf_tiles + inf_screenx;
        sy = (fishy - scy) * inf_tiles + inf_screeny;
        if (fishanime(1) > 15)
        {
            sx += (cdata[0].position.x - fishx) * 8 * (fishanime(1) - 15);
            sy += (cdata[0].position.y - fishy) * 8 * (fishanime(1) - 15)
                + fishanime(1);
            pos(sx, sy - 44);
            gcopy(9, 144 + fishanime(1) / 2 % 2 * 48, 0, 48, 48);
        }
        else
        {
            pos(sx, sy - fishanime(1) * 3 + 14);
            gcopy(
                9,
                144 + fishanime(1) % 2 * 48,
                0,
                48,
                clamp(fishanime(1) * 5, 1, 48));
        }
        return;
    }
    sx = (cdata[0].position.x - scx) * inf_tiles + inf_screenx + 20;
    if (fishdir == 1)
    {
        sx -= 48;
    }
    if (fishdir == 3)
    {
        sx += 48;
    }
    sy = (cdata[0].position.y - scy) * inf_tiles + inf_screeny + 20;
    if (fishdir == 0)
    {
        sy += 48;
    }
    if (fishdir == 2)
    {
        sy -= 48;
    }
    ap = rnd(2);
    if (fishanime == 1)
    {
        ap = fishanime(1);
    }
    else if (fishanime >= 2)
    {
        ap = 10;
    }
    pos(sx, sy - 5 + ap);
    gcopy(9, 116, 18, 14, 10 - ap);
    sx = (cdata[0].position.x - scx) * inf_tiles + inf_screenx;
    sy = (cdata[0].position.y - scy) * inf_tiles + inf_screeny;
    gmode(2);
    if (fishdir == 0)
    {
        sx2 = inf_tiles / 2 + rnd(3) - 1;
        sy2 = inf_tiles / 2 + 12;
        pos(sx + sx2 + 1, sy + sy2 + 40);
        gmode(2);
        gcopy_c(9, 48, 0, 48, 48);
    }
    if (fishdir == 1)
    {
        sx2 = inf_tiles / 2 - 26;
        sy2 = inf_tiles / 2 - 12 + rnd(3) - 3;
        pos(sx + sx2 - 16, sy + sy2 + 25);
        gmode(2);
        gcopy_c(9, 48, 0, 48, 48);
    }
    if (fishdir == 2)
    {
        sx2 = inf_tiles / 2 + rnd(3) + 1;
        sy2 = inf_tiles / 2 - 46;
    }
    if (fishdir == 3)
    {
        sx2 = inf_tiles / 2 + 26;
        sy2 = inf_tiles / 2 - 12 + rnd(3) - 3;
        pos(sx + sx2 + 14, sy + sy2 + 25);
        gmode(2);
        gcopy_c(9, 48, 0, 48, 48);
    }
    if (fishdir == 2)
    {
        gmode(2);
        pos(sx + sx2, sy + sy2);
        grotate(9, 0, 24, 48, 24, 0.5 * fishdir * 3.14);
    }
    else
    {
        gmode(2);
        pos(sx + sx2, sy + sy2);
        grotate(9, 0, 0, 48, 48, 0.5 * fishdir * 3.14);
    }
    randomize();
}



void display_window2(
    int prm_662,
    int prm_663,
    int prm_664,
    int prm_665,
    int prm_666,
    int prm_667)
{
    gmode(2);
    pos(prm_662, prm_663);
    gcopy(prm_666, 0, 0, prm_664, prm_665);
    font(12 + sizefix - en * 2, snail::font_t::style_t::bold);
    if (s != ""s)
    {
        pos(prm_662 + prm_664 - strlen_u(s) * 7 - 140,
            prm_663 + prm_665 - 24 - prm_665 % 8 + prm_667);
        mes(s);
    }
    if (pagesize != 0)
    {
        s = u8"Page."s + (page + 1) + u8"/"s + (pagemax + 1);
        pos(prm_662 + prm_664 - strlen_u(s) * 7 - 40,
            prm_663 + prm_665 - 24 - prm_665 % 8 + prm_667);
        mes(s);
    }
}



void display_window(
    int prm_668,
    int prm_669,
    int prm_670,
    int prm_671,
    int prm_672,
    int prm_673)
{
    if (windowshadow == 1)
    {
        window(prm_668 + 4, prm_669 + 4, prm_670, prm_671 - prm_671 % 8, true);
        windowshadow = 0;
    }
    window(prm_668, prm_669, prm_670, prm_671 - prm_671 % 8);
    if (s != ""s)
    {
        window2(
            prm_668 + 34,
            prm_669 - 4,
            45 * prm_670 / 100 + clamp(int(strlen_u(s) * 8 - 120), 0, 200),
            32,
            1,
            1);
    }
    gmode(2);
    pos(prm_668 + 30 + prm_672, prm_669 + prm_671 - 47 - prm_671 % 8);
    gcopy(3, 96, 360, 24, 16);
    line(
        prm_668 + 50 + prm_672,
        prm_669 + prm_671 - 48 - prm_671 % 8,
        prm_668 + prm_670 - 40,
        prm_669 + prm_671 - 48 - prm_671 % 8,
        {194, 170, 146});
    line(
        prm_668 + 50 + prm_672,
        prm_669 + prm_671 - 49 - prm_671 % 8,
        prm_668 + prm_670 - 40,
        prm_669 + prm_671 - 49 - prm_671 % 8,
        {234, 220, 188});
    font(15 + en - en * 2);
    bmes(
        s,
        prm_668 + 45 * prm_670 / 200 + 34 - strlen_u(s) * 4
            + clamp(int(s(0).size() * 8 - 120), 0, 200) / 2,
        prm_669 + 4 + vfix,
        {255, 255, 255},
        {20, 10, 0});
    font(12 + sizefix - en * 2);
    pos(prm_668 + 58 + prm_672, prm_669 + prm_671 - 43 - prm_671 % 8);
    mes(s(1));
    if (pagesize != 0)
    {
        s = u8"Page."s + (page + 1) + u8"/"s + (pagemax + 1);
        font(12 + sizefix - en * 2, snail::font_t::style_t::bold);
        pos(prm_668 + prm_670 - strlen_u(s) * 7 - 40 - prm_673,
            prm_669 + prm_671 - 65 - prm_671 % 8);
        mes(s);
    }
    wx = prm_668;
    wy = prm_669;
    ww = prm_670;
    wh = prm_671;
}



void display_note(const std::string& prm_674, int prm_675)
{
    font(12 + sizefix - en * 2, snail::font_t::style_t::bold);
    pos(wx + ww - strlen_u(prm_674) * 7 - 140 - prm_675, wy + wh - 65 - wh % 8);
    mes(prm_674);
}



void display_topic(const std::string& topic, int x, int y)
{
    font(12 + sizefix - en * 2, snail::font_t::style_t::bold);
    pos(x, y + 7);
    gcopy(3, 120, 360, 24, 16);
    pos(x + 26, y + 8);
    mes(topic);
    line(x + 22, y + 21, x + strlen_u(topic) * 7 + 36, y + 21);
}



void display_customkey(const std::string& key, int x, int y)
{
    gsel(3);
    gmode(0);
    font(15 - en * 2);
    pos(624, 30);
    gcopy(3, 0, 30, 24, 18);
    bmes(key, 629, 31, {250, 240, 230}, {50, 60, 80});
    gmode(2);
    gsel(0);
    pos(x, y);
    gcopy(3, 624, 30, 24, 18);
}



void display_key(int x, int y, int nth)
{
    pos(x, y);
    gcopy(3, nth * 24 + 72, 30, 24, 18);
}



void display_msg(int prm_680, int prm_681)
{
    msgkeep = prm_681;
    msgy = prm_680;
}



void drawmenu(int prm_742)
{
    int y_at_m107 = 0;
    elona_vector1<int> x_at_m107;
    y_at_m107 = 34;
    if (prm_742 == 0)
    {
        x_at_m107(0) = windoww - 260;
        x_at_m107(1) = 240;
        p(0) = 9;
        p(1) = 10;
        p(2) = 11;
        p(3) = 12;
        s(0) = lang(u8"情報"s, u8"Chara"s);
        s(1) = lang(u8"装備"s, u8"Wear"s);
        s(2) = lang(u8"特徴"s, u8"Feat"s);
        s(3) = lang(u8"ﾏﾃﾘｱﾙ"s, u8"Material"s);
        s(4) = "";
    }
    if (prm_742 == 1)
    {
        x_at_m107(0) = windoww - 160;
        x_at_m107(1) = 140;
        p(0) = 13;
        p(1) = 14;
        s(0) = lang(u8"魔法"s, u8"Spell"s);
        s(1) = lang(u8"技能"s, u8"Skill"s);
        s(2) = "";
    }
    if (prm_742 == 2)
    {
        x_at_m107(0) = windoww - 210;
        x_at_m107(1) = 190;
        p(0) = 15;
        p(1) = 3;
        p(2) = 16;
        s(0) = lang(u8"ログ"s, u8"Log"s);
        s(1) = lang(u8"日誌"s, u8"Journal"s);
        s(2) = lang(u8"チャット"s, u8"Chat"s);
        s(3) = "";
    }
    if (prm_742 == 3)
    {
        x_at_m107(0) = windoww - 210;
        x_at_m107(1) = 190;
        p(0) = 19;
        p(1) = 20;
        p(2) = 21;
        s(0) = lang(u8"チャート"s, u8"Chart"s);
        s(1) = lang(u8"街情報"s, u8"City"s);
        s(2) = lang(u8"法律"s, u8"Law"s);
        s(3) = "";
    }
    if (menucycle == 0)
    {
        return;
    }
    font(12 + sizefix - en * 2);
    window2(x_at_m107, y_at_m107, x_at_m107(1), 22, 5, 5);
    pos(x_at_m107 - 28, y_at_m107 - 8);
    gcopy(3, 64, 288, 50, 32);
    for (int cnt = 0; cnt < 8; ++cnt)
    {
        if (s(cnt) == ""s)
        {
            break;
        }
        pos(x_at_m107 + cnt * 50 + 20, y_at_m107 - 24);
        gcopy(3, 288 + p(cnt) * 48, 48, 48, 48);
        if (curmenu == cnt)
        {
            gmode(5, 70);
            pos(x_at_m107 + cnt * 50 + 20, y_at_m107 - 24);
            gcopy(3, 288 + p(cnt) * 48, 48, 48, 48);
            gmode(2);
        }
        bmes(
            s(cnt),
            x_at_m107 + cnt * 50 + 46 - strlen_u(s(cnt)) * 3,
            y_at_m107 + 7,
            curmenu == cnt ? snail::color{255, 255, 255}
                           : snail::color{165, 165, 165});
    }
    bmes(
        ""s + key_prev + u8","s + key_next + u8",Tab "s
            + lang(u8"[メニュー切替]"s, u8"[Change]"s),
        x_at_m107 + x_at_m107(1) - 150,
        y_at_m107 + 28);
}



void fillbg(
    int tile_window_id,
    int tile_x,
    int tile_y,
    int tile_width,
    int tile_height)
{
    gmode(0);

    for (int dy = 0; dy < inf_ver / tile_height + 1; ++dy)
    {
        for (int dx = 0; dx < windoww / tile_width + 1; ++dx)
        {
            pos(windoww - (dx + 1) * tile_width,
                inf_ver - (dy + 1) * tile_height);
            gcopy(tile_window_id, tile_x, tile_y, tile_width, tile_height);
        }
    }

    gmode(2);
}



void load_background_variants(int buffer)
{
    int buffer_bk = ginfo(3);
    gsel(buffer);
    for (int cnt = 0; cnt < 8; ++cnt)
    {
        pos(cnt % 4 * 180, cnt / 4 * 300);
        picload(
            filesystem::dir::graphic() / (u8"g"s + (cnt + 1) + u8".bmp"), 1);
    }
    gsel(buffer_bk);
}



void clear_background_in_character_making()
{
    gsel(4);
    pos(0, 0);
    picload(filesystem::dir::graphic() / u8"void.bmp", 1);
    gcopy(4, 0, 0, 800, 600, windoww, windowh);
    gsel(0);
    gmode(0);
    pos(0, 0);
    gcopy(4, 0, 0, windoww, 64);
    gmode(2);
}



void clear_background_in_continue()
{
    gsel(4);
    pos(0, 0);
    picload(filesystem::dir::graphic() / u8"void.bmp", 1);
    gcopy(4, 0, 0, 800, 600, windoww, windowh);
    gsel(0);
    gmode(0);
    pos(0, 0);
    gcopy(4, 0, 0, windoww, windowh);
    gmode(2);
}



void draw_scroll(int x, int y, int width, int height)
{
    int x3 = width + x - width % 8 - 64;
    int y3 = height + y - height % 8 - 64;

    for (int i = 0; i < width / 8; ++i)
    {
        if (i < 8)
        {
            if (i == 0)
            {
                pos(x, y);
                gcopy(7, 0, 0, 64, 48);
                pos(x, y3);
                gcopy(7, 0, 144, 64, 48);
            }
            continue;
        }
        if (i < width / 8 - 8)
        {
            pos(i * 8 + x, y);
            gcopy(7, (i - 8) % 18 * 8 + 64, 0, 8, 48);
            pos(i * 8 + x, y3);
            gcopy(7, (i - 8) % 18 * 8 + 64, 144, 8, 48);
            continue;
        }
        pos(x3, y);
        gcopy(7, 208, 0, 64, 48);
        pos(x3, y3);
        gcopy(7, 208, 144, 64, 48);
        break;
    }

    for (int i = 0; i < height / 8 - 14; ++i)
    {
        for (int j = 0; j < width / 8; ++j)
        {
            if (j == 0)
            {
                pos(x, i * 8 + y + 48);
                gcopy(7, 0, i % 12 * 8 + 48, 64, 8);
                continue;
            }
            if (j < width / 8 - 15)
            {
                pos(j * 8 + x + 56, i * 8 + y + 48);
                gcopy(7, j % 18 * 8 + 64, i % 12 * 8 + 48, 8, 8);
                continue;
            }
            pos(x3, i * 8 + y + 48);
            gcopy(7, 208, i % 12 * 8 + 48, 64, 8);
            break;
        }
    }
}



void cs_listbk()
{
    if (cs_bk == -1)
        return;
    pos(cs_posbk_x, cs_posbk_y);
    gcopy(3, 264, 96, cs_posbk_w, cs_posbk_h);
}



void cs_list(
    bool is_selected,
    const std::string& text,
    int x,
    int y,
    int x_offset,
    int color_mode,
    int ci)
{
    if (is_selected)
    {
        const auto width =
            clamp(int(strlen_u(text)) * 7 + 32 + x_offset, 10, 480);

        gsel(3);
        pos(264, 96);
        gcopy(0, x, y, width, 19);
        gsel(0);

        const auto colorbk_r = ginfo(16);
        const auto colorbk_g = ginfo(17);
        const auto colorbk_b = ginfo(18);
        boxf(x, y, width, 19, {127, 191, 255, 63});
        color(colorbk_r, colorbk_g, colorbk_b);
        pos(x + width - 20, y + 4);
        gcopy(3, 48, 360, 16, 16);

        cs_posbk_x = x;
        cs_posbk_y = y;
        cs_posbk_w = width;
        cs_posbk_h = 19;
    }

    switch (color_mode)
    {
    case 0: color(10, 10, 10); break;
    case 1:
        color(0, 0, 0);
        if (inv[ci].identification_state
            == identification_state_t::completely_identified)
        {
            switch (inv[ci].curse_state)
            {
            case curse_state_t::doomed: color(100, 10, 100); break;
            case curse_state_t::cursed: color(150, 10, 10); break;
            case curse_state_t::none: color(10, 40, 120); break;
            case curse_state_t::blessed: color(10, 110, 30); break;
            }
        }
        if (ibit(13, ci))
        {
            color(120, 80, 0);
        }
        break;
    case 2: color(240, 240, 240); break;
    case 3: color(160, 10, 10); break;
    case 4: color(128, 128, 128); break;
    default:
        // Use current color.
        break;
    }

    pos(x + 4 + x_offset, y + 3);
    mes(text);
    color(0, 0, 0);
}



void showscroll(const std::string& title, int x, int y, int width, int height)
{
    if (windowshadow != 0)
    {
        gmode(6, 80);
        draw_scroll(x + 3, y + 3, width, height);
        windowshadow = 0;
        gmode(2);
    }
    draw_scroll(x, y, width, height);

    if (title.empty())
        return;

    pos(x + 40, y + height - 67 - height % 8);
    gcopy(3, 96, 360, 24, 16);
    line(
        x + 60,
        y + height - 68 - height % 8,
        x + width - 40,
        y + height - 68 - height % 8,
        {194, 173, 161});
    line(
        x + 60,
        y + height - 69 - height % 8,
        x + width - 40,
        y + height - 69 - height % 8,
        {224, 213, 191});
    font(12 + sizefix - en * 2);
    color(0, 0, 0);
    pos(x + 68, y + height - 63 - height % 8);
    mes(s);
    if (pagesize != 0)
    {
        s = u8"Page."s + (page + 1) + u8"/"s + (pagemax + 1);
        font(12 + sizefix - en * 2, snail::font_t::style_t::bold);
        pos(x + width - strlen_u(s) * 7 - 40, y + height - 63 - height % 8);
        mes(s);
    }
}



void window(int x, int y, int width, int height, bool shadow)
{
    if (shadow)
    {
        gmode(2, 127);
        set_color_mod(31, 31, 31, 3);
    }
    else
    {
        gmode(2);
    }

    int x3 = width + x - width % 8 - 64;
    int y3 = height + y - height % 8 - 64;
    if (y3 < y + 14)
    {
        y3 = y + 14;
    }

    if (!shadow)
    {
        // Top left
        pos(x, y);
        gcopy(3, 0, 48, 64, 48);
    }
    // Top right
    pos(x3, y);
    gcopy(3, 208, 48, 56, 48);
    // Bottom left
    pos(x, y3);
    gcopy(3, 0, 48 + 144, 64, 48);
    // Bottom right
    pos(x3, y3);
    gcopy(3, 208, 48 + 144, 56, 48);

    for (int dx = 8; dx < width / 8 - 8; ++dx)
    {
        if (!shadow)
        {
            // Top middle
            pos(dx * 8 + x, y);
            gcopy(3, (dx - 8) % 18 * 8 + 36, 48, 8, 48);
        }
        // Bottom middle
        pos(dx * 8 + x, y3);
        gcopy(3, (dx - 8) % 18 * 8 + 54, 48 + 144, 8, 48);
    }

    for (int dy = 0; dy < height / 8 - 14; ++dy)
    {
        if (!shadow)
        {
            // Middle left
            pos(x, dy * 8 + y + 48);
            gcopy(3, 0, dy % 12 * 8 + 48 + 48, 64, 8);
            // Middle middle
            for (int dx = 1; dx < width / 8 - 15; ++dx)
            {
                pos(dx * 8 + x + 56, dy * 8 + y + 48);
                gcopy(3, dx % 18 * 8 + 64, dy % 12 * 8 + 48 + 48, 8, 8);
            }
        }
        // Middle right
        pos(x3, dy * 8 + y + 48);
        gcopy(3, 208, dy % 12 * 8 + 48 + 48, 56, 8);
    }

    gmode(2);
    if (shadow)
    {
        set_color_mod(255, 255, 255, 3);
    }
}



void window2(
    int x,
    int y,
    int width,
    int height,
    int frame_style,
    int fill_style)
{
    if (width < 32)
    {
        width = 32;
    }
    if (height < 24)
    {
        height = 24;
    }

    switch (fill_style)
    {
    case 0:
        pos(x + 4, y + 4);
        gcopy(3, 24, 72, 228, 144, width - 6, height - 8);
        break;
    case 1:
        pos(x + 4, y + 4);
        gcopy(3, 24, 72, 228, 144, width - 6, height - 8);
        boxf(x + 4, y + 4, width - 4, height - 4, {0, 0, 0, 195});
        break;
    case 2:
        pos(x + 4, y + 4);
        gcopy(3, 24, 72, 228, 144, width - 6, height - 8);
        boxf(x + 4, y + 4, width - 4, height - 4, {0, 0, 0, 210});
        break;
    case 3:
        pos(x + 4, y + 4);
        gcopy(3, 24, 72, 228, 144, width - 6, height - 8);
        boxf(x + 4, y + 4, width - 4, height - 4, {0, 0, 0, 10});
        break;
    case 4:
        pos(x + 4, y + 4);
        gcopy(3, 24, 72, 228, 144, width - 6, height - 8);
        boxf(x + 4, y + 4, width - 4, height - 4, {0, 0, 0, 195});
        break;
    case 5: break;
    case 6:
        pos(x + width / 2, y + height / 2);
        gmode(4, 180);
        gcopy_c(3, 24, 72, 228, 144, width - 4, height - 4);
        break;
    default: break;
    }

    gmode(2);
    for (int cnt = 0, cnt_end = (width / 16 - 2); cnt < cnt_end; ++cnt)
    {
        pos(cnt * 16 + x + 16, y);
        gcopy(3, frame_style * 48 + 16, 240, 16, 16);
        pos(cnt * 16 + x + 16, y + height - 16);
        gcopy(3, frame_style * 48 + 16, 240 + 32, 16, 16);
    }

    const auto x2 = x + width / 16 * 16 - 16;
    const auto y2 = y + height / 16 * 16 - 16;

    pos(x2, y);
    gcopy(3, frame_style * 48 + 16, 240, width % 16, 16);
    pos(x2, y + height - 16);
    gcopy(3, frame_style * 48 + 16, 240 + 32, width % 16, 16);

    for (int i = 0; i < height / 16 - 2; ++i)
    {
        pos(x, i * 16 + y + 16);
        gcopy(3, frame_style * 48, 240 + 16, 16, 16);
        pos(x + width - 16, i * 16 + y + 16);
        gcopy(3, frame_style * 48 + 32, 240 + 16, 16, 16);
    }
    pos(x, y2);
    gcopy(3, frame_style * 48, 240 + 16, 16, height % 16);
    pos(x + width - 16, y2);
    gcopy(3, frame_style * 48 + 32, 240 + 16, 16, height % 16);
    pos(x, y);
    gcopy(3, frame_style * 48, 240, 16, 16);
    pos(x, y + height - 16);
    gcopy(3, frame_style * 48, 240 + 32, 16, 16);
    pos(x + width - 16, y);
    gcopy(3, frame_style * 48 + 32, 240, 16, 16);
    pos(x + width - 16, y + height - 16);
    gcopy(3, frame_style * 48 + 32, 240 + 32, 16, 16);

    if (fill_style == 5)
    {
        pos(x + 2, y + 2);
        gcopy(3, 24, 72, 228, 144, width - 4, height - 5);
        boxf(x + 4, y + 4, width - 4, height - 4, {0, 0, 0, 195});
    }
}



void window_animation(
    int x,
    int y,
    int width,
    int height,
    int duration,
    int temporary_window_id)
{
    if (nowindowanime)
    {
        nowindowanime = 0;
        return;
    }
    if (!config::instance().windowanime)
        return;
    if (duration == 0)
        return;

    gsel(temporary_window_id);
    gmode(0);
    pos(0, 0);
    gcopy(0, x, y, width, height);
    gsel(0);
    gmode(0);

    const auto w2 = width / 2;
    const auto h2 = height / 2;
    for (int i = 0; i < duration; ++i)
    {
        const auto frame_width = width / (duration + 1) * (i + 1);
        const auto frame_height = height / (duration + 1) * (i + 1);
        boxl(
            x + w2 - frame_width / 2,
            y + h2 - frame_height / 2,
            frame_width,
            frame_height,
            {30, 30, 30});
        boxl(
            x + w2 - frame_width / 2 - 1,
            y + h2 - frame_height / 2 - 1,
            frame_width - 1,
            frame_height - 1,
            {240, 240, 240});
        redraw();
        if (i != duration - 1)
        {
            await(config::instance().animewait * 0.75);
        }
        pos(x, y);
        gcopy(temporary_window_id, 0, 0, width, height);
    }

    gmode(2);
}



void window_animation_corner(
    int x,
    int y,
    int width,
    int height,
    int duration,
    int temporary_window_id)
{
    if (!config::instance().windowanime)
        return;
    if (duration == 0)
        return;

    gsel(temporary_window_id);
    gmode(0);
    pos(0, 0);
    gcopy(0, x, y, width, height);
    gsel(0);
    gmode(0);

    for (int i = 0; i < duration; ++i)
    {
        boxl(
            x + width,
            y + height,
            (x - width) / duration * (i + 1),
            (y - height) / duration * (i + 1),
            {30, 30, 30});
        boxl(
            x + width - 1,
            y + height - 1,
            (x - width) / duration * (i + 1),
            (y - height) / duration * (i + 1),
            {240, 240, 240});
        redraw();
        if (i != duration - 1)
        {
            await(config::instance().animewait * 0.75);
        }
        pos(x, y);
        gcopy(temporary_window_id, 0, 0, width, height);
    }

    gmode(2);
}



void show_title(const std::string& title)
{
    int x;
    int y;
    if (mode != 1)
    {
        x = 226;
        y = 0;
    }
    else
    {
        x = 240;
        y = windowh - 16;
    }
    for (int i = 0; i < (windoww - x - 8) / 192 + 1; ++i)
    {
        pos(x + 8 + i * 192, y);
        gcopy(3, 496, 581, 192, 18);
    }
    gmode(2);
    pos(x, y + (mode != 1));
    gcopy(3, 96, 360, 24, 16);
    font(12 + sizefix - en * 2);
    bmes(title, x + 32, y + 1 + jp, {250, 250, 250});
}



} // namespace elona

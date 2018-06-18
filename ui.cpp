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

int cs_posbk_x{};
int cs_posbk_y{};
int cs_posbk_w{};
int cs_posbk_h{};
int x2_at_m105 = 0;
int y2_at_m105 = 0;

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
    inf_raderx = 1;
    inf_raderw = 136;
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
        inf_radery = 1;
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
        inf_radery = windowh - 86;
    }
    scposy = inf_screenh / 2 - 1;
    inf_hpx = (windoww - 84) / 2 - 100;
    inf_hpy = inf_ver - 12;
    inf_mpx = (windoww - 84) / 2 + 40;
    inf_mpy = inf_ver - 12;
    inf_msgx = inf_raderw;
    inf_msgspace = 15;
    int inf_maxmsglen_i = std::max((windoww - inf_msgx - 28) / inf_mesfont * 2 - 1, 0);
    inf_maxmsglen = static_cast<size_t>(inf_maxmsglen_i);
    inf_maxlog = (inf_msgy - 100) / inf_msgspace + 3;
    inf_very = windowh - inf_verh;
    screenmsgy = inf_screeny + inf_tiles * 2;
    prompty = (windowh - inf_verh - 30) / 2 - 4;
    promptx = (windoww - 10) / 2 + 3;
    return;
}

void label_1416()
{
    gmode(2);
    update_screen();
    return;
}

void update_entire_screen()
{
    update_screen_hud();
    update_minimap();
    update_screen();
    return;
}

void update_screen()
{
    screendrawhack = 1;
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
    screendrawhack = 10;
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
    screendrawhack = 0;
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
    pos(inf_raderw + 6, inf_bary);
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
        pos(inf_raderw + cnt * 47 + 148 + sx, inf_bary + 1);
        gcopy(3, cnt * 16, 376, 16, 16);
    }
    font(12 + sizefix - en * 2);
    pos(inf_raderw + 24, inf_bary + 3 + vfix - en);
    if (strlen_u(mdatan(0)) > size_t(16 - (maplevel() != ""s) * 4))
    {
        mes(cnven(strmid(mdatan(0), 0, 16 - (maplevel() != ""s) * 4)));
    }
    else
    {
        mes(cnven(mdatan(0)));
    }
    pos(inf_raderw + 114, inf_bary + 3 + vfix - en);
    mes(maplevel());
    return;
}

void update_minimap()
{
    for (int cnt = 0, cnt_end = (mdata(1)); cnt < cnt_end; ++cnt)
    {
        sy = cnt;
        for (int cnt = 0, cnt_end = (mdata(0)); cnt < cnt_end; ++cnt)
        {
            sx = cnt;
            if (map(sx, sy, 2) == map(sx, sy, 0))
            {
                draw_minimap_pixel();
            }
        }
    }
    return;
}

void label_1420()
{
    gmode(2);
    label_1433();
    render_hud();
    redraw();
    screenupdate = 0;
    return;
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
    pos(sx + 4, sy);
    bmes(""s + cdata[0].hp + u8"("s + cdata[0].max_hp + u8")"s, 255, 255, 255);
    sx = inf_mpx + 16;
    sy = inf_mpy - 8;
    pos(sx + 4, sy);
    bmes(""s + cdata[0].mp + u8"("s + cdata[0].max_mp + u8")"s, 255, 255, 255);
    font(13 - en * 2);
    sy = inf_bary + 2 + vfix;
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        sx = inf_raderw + cnt * 47 + 168 - 2;
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
    pos(sx + 28, sy + 2);
    bmes(""s + cdata[0].gold + u8" gp"s, 255, 255, 255);
    sx = windoww - 120;
    pos(sx, sy);
    gcopy(3, 24, 392, 24, 24);
    pos(sx + 28, sy + 2);
    bmes(""s + cdata[0].platinum_coin + u8" pp"s, 255, 255, 255);
    pos(4, inf_ver - 16);
    gcopy(3, 48, 392, 24, 24);
    pos(32, inf_ver - 14);
    bmes(
        u8"Lv"s + cdata[0].level + u8"/"s
            + (cdata[0].required_experience - cdata[0].experience),
        255,
        255,
        255);
    if (cdata[0].position.x < 6)
    {
        if (mode != 9)
        {
            if (mdata(6) != 1)
            {
                if (cdata[0].continuous_action_id == 0)
                {
                    gmode(4, -1, -1, 150);
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
    gmode(4, -1, -1, 180);
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
    gmode(2, 48, 48);
    grotate(3, 0, 288, 0.0174532925199433 * (gdata_hour * 30), 48, 48);
    pos(inf_clockw - 3, inf_clocky + 17 + vfix);
    mes(""s + gdata_year + u8"/"s + gdata_month + u8"/"s + gdata_day);
    pos(inf_clockw + 6, inf_clocky + 35);
    bmes(
        i18n::_(u8"ui", u8"time", u8"_"s + gdata_hour / 4) + u8" "s
            + i18n::_(u8"ui", u8"weather", u8"_"s + gdata_weather),
        255,
        255,
        255);
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
        pos(16, inf_clocky + 155 - ap3 * 16);
        bmes(
            ""s
                + strmid(
                      i18n::_(u8"ability", std::to_string(ap), u8"name"), 0, 6),
            255,
            255,
            255);
        pos(66, inf_clocky + 155 - ap3 * 16);
        bmes(
            ""s + sdata.get(ap, ap2).original_level + u8"."s
                + std::to_string(1000 + sdata.get(ap, ap2).experience % 1000)
                      .substr(1),
            255,
            255,
            255);
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
    return;
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
    pos(sx + 43, sy + 6);
    bmes(u8"AUTO TURN"s, 235, 235, 235);
    pos(sx + 18, sy + 12);
    gmode(2, 24, 24);
    grotate(3, 72, 392, 0.0174532925199433 * (gdata_minute / 4 % 2 * 90));

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
    return;
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
    return;
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
    return;
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
                            draw_minimap_pixel();
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
    return;
}

void label_1433()
{
    screendrawhack = 2;
    cell_draw();
    screendrawhack = 3;
    if (gdata_current_map == 40)
    {
        for (int cnt = 0; cnt < ELONA_MAX_CHARACTERS; ++cnt)
        {
            if (cdata[cnt].state != 1)
            {
                continue;
            }
            ap = 0;
            if (cdata[cnt].relationship == 10)
            {
                ap(0) = 1;
                ap(1) = 1;
                ap(2) = 25;
            }
            if (cdata[cnt].relationship == -3)
            {
                ap(0) = 25;
                ap(1) = 1;
                ap(2) = 1;
            }
            if (cnt == 0)
            {
                ap = 0;
            }
            if (ap != 0)
            {
                sx = (cdata[cnt].position.x - scx) * inf_tiles + inf_screenx;
                sy = (cdata[cnt].position.y - scy) * inf_tiles + inf_screeny;
                if (sx >= 0)
                {
                    if (sy >= 0)
                    {
                        if (sx - inf_screenx < (inf_screenw - 1) * inf_tiles)
                        {
                            if (sy < (inf_screenh - 1) * inf_tiles)
                            {
                                pos(sx, sy * (sy > 0));
                                gfini(
                                    inf_tiles,
                                    inf_tiles + (sy < 0) * inf_screeny);
                                gfinc(ap, ap(1), ap(2));
                                if (cnt == camera)
                                {
                                    gmode(4, -1, -1, 120);
                                    pos(sx + 36, sy + 32);
                                    gcopy(3, 240, 410, 24, 16);
                                    gmode(2);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    screendrawhack = 4;
    sy = 84 * cdata[0].position.y / mdata(1);
    if (sy < 2)
    {
        sy = 2;
    }
    else if (sy > 76)
    {
        sy = 76;
    }
    sx = 120 * cdata[0].position.x / mdata(0);
    if (sx < 2)
    {
        sx = 2;
    }
    else if (sx > 112)
    {
        sx = 112;
    }
    if (raderx != -1)
    {
        pos(inf_raderx + raderx, inf_radery + radery);
        gcopy(3, 688 + raderx, 528 + radery, 6, 6);
    }
    raderx = sx;
    radery = sy;
    pos(inf_raderx + sx, inf_radery + sy);
    gcopy(3, 15, 338, 6, 6);
    if (debug::voldemort)
    {
        render_stair_positions_in_minimap();
    }
    screendrawhack = 5;
    if (config::instance().env)
    {
        if (gdata_weather == 3)
        {
            render_weather_effect_rain();
        }
        if (gdata_weather == 4)
        {
            render_weather_effect_hard_rain();
        }
        if (gdata_weather == 2)
        {
            render_weather_effect_snow();
        }
        if (gdata_weather == 1)
        {
            render_weather_effect_etherwind();
        }
    }
    return;
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
                pos(inf_raderx + sx, inf_radery + sy);
                gcopy(3, 15, 338, 6, 6);
            }
            else if (map(x, y, 6) / 1000 % 100 == 10)
            {
                // Upstairs
                pos(inf_raderx + sx, inf_radery + sy);
                gcopy(3, 15, 338, 6, 6);
            }
        }
    }
}

void render_weather_effect_rain()
{
    if (mdata(14) != 2)
    {
        return;
    }
    for (int cnt = 0, cnt_end = (maxrain * (1 + (mdata(6) == 1)));
         cnt < cnt_end;
         ++cnt)
    {
        s_p = rnd(100);
        color(170 - s_p, 200 - s_p, 250 - s_p);
        line(
            rainx(cnt) - 40,
            rainy(cnt) - cnt % 3 - 1,
            rainx(cnt) - 39 + cnt % 2,
            rainy(cnt));
        color(0, 0, 0);
        if (rainx(cnt) == 0)
        {
            rainx(cnt) = rnd(windoww) + 40;
        }
        else
        {
            rainx(cnt) += 2;
        }
        if (rainy(cnt) == 0)
        {
            rainy(cnt) = rnd(windowh - inf_verh) - 6;
        }
        else
        {
            rainy(cnt) += 16 + cnt % 8;
            if (rainy(cnt) > windowh - inf_verh - 6)
            {
                rainy(cnt) = 0;
                rainx(cnt) = 0;
            }
        }
    }
    weatherbk = gdata_weather;
    return;
}

void render_weather_effect_hard_rain()
{
    if (mdata(14) != 2)
    {
        return;
    }
    for (int cnt = 0, cnt_end = (maxrain * (1 + (mdata(6) == 1)));
         cnt < cnt_end;
         ++cnt)
    {
        s_p = rnd(100);
        color(170 - s_p, 200 - s_p, 250 - s_p);
        line(
            rainx(cnt) - 40,
            rainy(cnt) - cnt % 5 - 4,
            rainx(cnt) - 39 + cnt % 2,
            rainy(cnt));
        color(0, 0, 0);
        if (rainx(cnt) == 0)
        {
            rainx(cnt) = rnd(windoww) + 40;
        }
        else
        {
            rainx(cnt) += 1;
        }
        if (rainy(cnt) == 0)
        {
            rainy(cnt) = rnd(windowh - inf_verh) - 6;
        }
        else
        {
            rainy(cnt) += 24 + cnt % 8;
            if (rainy(cnt) > windowh - inf_verh - 10)
            {
                rainy(cnt) = 0;
                rainx(cnt) = 0;
            }
        }
    }
    weatherbk = gdata_weather;
    return;
}

void render_weather_effect_snow()
{
    if (mdata(14) != 2)
    {
        return;
    }
    for (int cnt = 0, cnt_end = (maxrain * 2); cnt < cnt_end; ++cnt)
    {
        if (cnt % 30 == 0)
        {
            gmode(4, 8, 8, 100 + cnt % 150);
        }
        if (rainy(cnt) == 0 || weatherbk != gdata_weather)
        {
            rainy(cnt) = rnd(windowh / 2) * -1;
            rainx(cnt) = rnd(windoww);
        }
        else
        {
            rainx(cnt) += rnd(3) - 1;
            rainy(cnt) += rnd(2) + cnt % 5;
            if (rainy(cnt) > windowh - inf_verh - 10 || rnd(500) == 0)
            {
                rainy(cnt) = 0;
                rainx(cnt) = 0;
            }
        }
        pos(rainx(cnt), rainy(cnt));
        gcopy(3, rainx(cnt) % 2 * 8, 600 + cnt % 6 * 8);
    }
    weatherbk = gdata_weather;
    gmode(2);
    return;
}

void render_weather_effect_etherwind()
{
    if (mdata(14) != 2)
    {
        return;
    }
    for (int cnt = 0, cnt_end = (maxrain); cnt < cnt_end; ++cnt)
    {
        if (cnt % 20 == 0)
        {
            gmode(4, 8, 8, 100 + cnt % 150);
        }
        if (rainy(cnt) <= 0 || weatherbk != gdata_weather)
        {
            rainy(cnt) = windowh - inf_verh - 8 - rnd(100);
            rainx(cnt) = rnd(windoww);
        }
        else
        {
            pos(rainx(cnt), rainy(cnt));
            gcopy(3, 16 + rainx(cnt) % 2 * 8, 600 + cnt % 6 * 8);
            rainx(cnt) += rnd(3) - 1;
            rainy(cnt) -= rnd(2) + cnt % 5;
        }
    }
    weatherbk = gdata_weather;
    gmode(2);
    return;
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
    return;
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
            gfini(raderw, raderh);
            if (chipm(7, map(sx, sy, 0)) & 4)
            {
                gfdec2(100, 100, 100);
            }
        }
    }
    pos(688, 528);
    gfini(raderw * mdata(0), raderh * mdata(1));
    gfinc(10, 10, 10);
    gsel(0);
    return;
}

void draw_minimap_pixel()
{
    sy(1) = 84 * sy / mdata(1);
    sx(1) = 120 * sx / mdata(0);
    pos(inf_raderx + sx(1), inf_radery + sy(1));
    gcopy(3, 688 + sx(1), 528 + sy(1), raderw, raderh);
    return;
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
        pos(0, 0);
        gfini(windoww, windowh);
        gfdec2(5, 5, 5);
        redraw();
    }
    for (int cnt = 0; cnt < 30; ++cnt)
    {
        gmode(4, 0, 0, 10 + cnt * 5);
        await(20);
        pos(0, 0);
        gcopy(4, 0, 0, windoww, windowh);
        redraw();
    }
    gmode(2);
    return;
}

void label_1442()
{
    for (int cnt = 0; cnt < 50; ++cnt)
    {
        await(20);
        pos(0, 0);
        gfini(windoww, windowh);
        gfdec2(5, 5, 5);
        redraw();
    }
    return;
}

void animation_fade_in()
{
    for (int cnt = 0; cnt < 30; ++cnt)
    {
        gmode(4, 0, 0, 10 + cnt * 5);
        await(20);
        pos(0, 0);
        gcopy(4, 0, 0, windoww, windowh);
        redraw();
    }
    gmode(2);
    return;
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
    return;
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
            pos(x * evtiles, y * evtiles);
            gmode(0, inf_tiles, inf_tiles);
            ap = map(dx, dy, 0);
            grotate(
                2,
                ap % 33 * inf_tiles,
                ap / 33 * inf_tiles,
                0,
                evtiles,
                evtiles);
        }
    }
    return;
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
    gmode(2, 48, 48);
    if (fishdir == 0)
    {
        sx2 = inf_tiles / 2 + rnd(3) - 1;
        sy2 = inf_tiles / 2 + 12;
        gmode(2, 48, 48);
        pos(sx + sx2 + 1, sy + sy2 + 40);
        grotate(9, 48, 0, 0, 48, 48);
    }
    if (fishdir == 1)
    {
        sx2 = inf_tiles / 2 - 26;
        sy2 = inf_tiles / 2 - 12 + rnd(3) - 3;
        pos(sx + sx2 - 16, sy + sy2 + 25);
        grotate(9, 48, 0, 0, 48, 48);
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
        grotate(9, 48, 0, 0, 48, 48);
    }
    if (fishdir == 2)
    {
        gmode(2, 48, 24);
        pos(sx + sx2, sy + sy2);
        grotate(9, 0, 24, 0.5 * fishdir * 3.14, 48, 24);
    }
    else
    {
        gmode(2, 48, 48);
        pos(sx + sx2, sy + sy2);
        grotate(9, 0, 0, 0.5 * fishdir * 3.14, 48, 48);
    }
    randomize();
    return;
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
    return;
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
        window(prm_668 + 4, prm_669 + 4, prm_670, prm_671 - prm_671 % 8, 0, -1);
        windowshadow = 0;
    }
    window(prm_668, prm_669, prm_670, prm_671 - prm_671 % 8, 0, 0);
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
    color(194, 170, 146);
    line(
        prm_668 + 50 + prm_672,
        prm_669 + prm_671 - 48 - prm_671 % 8,
        prm_668 + prm_670 - 40,
        prm_669 + prm_671 - 48 - prm_671 % 8);
    color(234, 220, 188);
    line(
        prm_668 + 50 + prm_672,
        prm_669 + prm_671 - 49 - prm_671 % 8,
        prm_668 + prm_670 - 40,
        prm_669 + prm_671 - 49 - prm_671 % 8);
    font(15 + en - en * 2);
    color(0, 0, 0);
    pos(prm_668 + 45 * prm_670 / 200 + 34 - strlen_u(s) * 4
            + clamp(int(s(0).size() * 8 - 120), 0, 200) / 2,
        prm_669 + 4 + vfix);
    color(20, 10, 0);
    bmes(s, 255, 255, 255);
    font(12 + sizefix - en * 2);
    color(0, 0, 0);
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
    return;
}

void display_note(const std::string& prm_674, int prm_675)
{
    font(12 + sizefix - en * 2, snail::font_t::style_t::bold);
    pos(wx + ww - strlen_u(prm_674) * 7 - 140 - prm_675, wy + wh - 65 - wh % 8);
    mes(prm_674);
    return;
}

void display_topic(const std::string& prm_676, int prm_677, int prm_678, int)
{
    font(12 + sizefix - en * 2, snail::font_t::style_t::bold);
    pos(prm_677, prm_678 + 7);
    gcopy(3, 120, 360, 24, 16);
    pos(prm_677 + 26, prm_678 + 8);
    mes(prm_676);
    line(
        prm_677 + 22,
        prm_678 + 21,
        prm_677 + strlen_u(prm_676) * 7 + 36,
        prm_678 + 21);
    return;
}

void display_customkey(const std::string& key, int x, int y)
{
    gsel(3);
    gmode(0);
    font(15 - en * 2);
    pos(624, 30);
    gcopy(3, 0, 30, 24, 18);
    pos(629, 31);
    color(50, 60, 80);
    bmes(key, 250, 240, 230);
    color(0, 0, 0);
    gmode(2, inf_tiles, inf_tiles);
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
    return;
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
            gmode(5, -1, -1, 70);
            pos(x_at_m107 + cnt * 50 + 20, y_at_m107 - 24);
            gcopy(3, 288 + p(cnt) * 48, 48, 48, 48);
            gmode(2);
        }
        pos(x_at_m107 + cnt * 50 + 46 - strlen_u(s(cnt)) * 3, y_at_m107 + 7);
        if (curmenu == cnt)
        {
            bmes(s(cnt), 255, 255, 255);
        }
        else
        {
            bmes(s(cnt), 165, 165, 165);
        }
    }
    pos(x_at_m107 + x_at_m107(1) - 150, y_at_m107 + 28);
    bmes(
        ""s + key_prev + u8","s + key_next + u8",Tab "s
            + lang(u8"[メニュー切替]"s, u8"[Change]"s),
        255,
        255,
        255);
    return;
}

void fillbg(int prm_743, int prm_744, int prm_745, int prm_746, int prm_747)
{
    int cnt2_at_m108 = 0;
    gmode(0);
    for (int cnt = 0, cnt_end = (inf_ver / prm_747 + 1); cnt < cnt_end; ++cnt)
    {
        cnt2_at_m108 = cnt;
        for (int cnt = 0, cnt_end = (windoww / prm_746 + 1); cnt < cnt_end;
             ++cnt)
        {
            pos(windoww - (cnt + 1) * prm_746,
                inf_ver - (cnt2_at_m108 + 1) * prm_747);
            gcopy(prm_743, prm_744, prm_745, prm_746, prm_747);
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
    gzoom(4, 0, 0, 800, 600, windoww, windowh);
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
    gzoom(4, 0, 0, 800, 600, windoww, windowh);
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
        boxf(x, y, x + width, y + 19, {127, 191, 255, 63});
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
        gmode(6, -1, -1, 80);
        draw_scroll(x + 3, y + 3, width, height);
        windowshadow = 0;
        gmode(2);
    }
    draw_scroll(x, y, width, height);

    if (title.empty())
        return;

    pos(x + 40, y + height - 67 - height % 8);
    gcopy(3, 96, 360, 24, 16);
    color(194, 173, 161);
    line(
        x + 60,
        y + height - 68 - height % 8,
        x + width - 40,
        y + height - 68 - height % 8);
    color(224, 213, 191);
    line(
        x + 60,
        y + height - 69 - height % 8,
        x + width - 40,
        y + height - 69 - height % 8);
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



void window(
    int prm_650,
    int prm_651,
    int prm_652,
    int prm_653,
    int,
    int prm_655)
{
    int dx_at_m92 = 0;
    int dy_at_m92 = 0;
    int x3_at_m92 = 0;
    int y3_at_m92 = 0;
    int p_at_m92 = 0;
    int cnt2_at_m92 = 0;
    if (prm_655 == -1)
    {
        gmode(6, -1, -1, 80);
    }
    else
    {
        gmode(2);
    }
    dx_at_m92 = 0;
    dy_at_m92 = 48;
    x3_at_m92 = prm_652 + prm_650 - prm_652 % 8 - 64;
    y3_at_m92 = prm_653 + prm_651 - prm_653 % 8 - 64;
    if (y3_at_m92 < prm_651 + 14)
    {
        y3_at_m92 = prm_651 + 14;
    }
    for (int cnt = 0, cnt_end = (prm_652 / 8); cnt < cnt_end; ++cnt)
    {
        if (cnt < 8)
        {
            if (cnt == 0)
            {
                pos(prm_650, prm_651);
                gcopy(3, dx_at_m92, dy_at_m92, 64, 48);
                pos(prm_650, y3_at_m92);
                gcopy(3, dx_at_m92, dy_at_m92 + 144, 64, 48);
            }
            continue;
        }
        if (cnt < prm_652 / 8 - 8)
        {
            pos(cnt * 8 + prm_650, prm_651);
            gcopy(3, (cnt - 8) % 18 * 8 + dx_at_m92 + 36, dy_at_m92, 8, 48);
            pos(cnt * 8 + prm_650, y3_at_m92);
            gcopy(
                3, (cnt - 8) % 18 * 8 + dx_at_m92 + 54, dy_at_m92 + 144, 8, 48);
            continue;
        }
        pos(x3_at_m92, prm_651);
        gcopy(3, dx_at_m92 + 208, dy_at_m92, 56, 48);
        pos(x3_at_m92, y3_at_m92);
        gcopy(3, dx_at_m92 + 208, dy_at_m92 + 144, 56, 48);
        break;
    }
    p_at_m92 = prm_653 / 8 - 14;
    if (p_at_m92 < 0)
    {
        p_at_m92 = 0;
    }
    for (int cnt = 0, cnt_end = (p_at_m92); cnt < cnt_end; ++cnt)
    {
        cnt2_at_m92 = cnt;
        for (int cnt = 0, cnt_end = (prm_652 / 8); cnt < cnt_end; ++cnt)
        {
            if (cnt == 0)
            {
                pos(prm_650, cnt2_at_m92 * 8 + prm_651 + 48);
                gcopy(
                    3, dx_at_m92, cnt2_at_m92 % 12 * 8 + dy_at_m92 + 48, 64, 8);
                continue;
            }
            if (cnt < prm_652 / 8 - 15)
            {
                pos(cnt * 8 + prm_650 + 56, cnt2_at_m92 * 8 + prm_651 + 48);
                gcopy(
                    3,
                    cnt % 18 * 8 + dx_at_m92 + 64,
                    cnt2_at_m92 % 12 * 8 + dy_at_m92 + 48,
                    8,
                    8);
                continue;
            }
            pos(x3_at_m92, cnt2_at_m92 * 8 + prm_651 + 48);
            gcopy(
                3,
                dx_at_m92 + 208,
                cnt2_at_m92 % 12 * 8 + dy_at_m92 + 48,
                56,
                8);
            break;
        }
    }
    gmode(2);
    return;
}



void window2(
    int prm_656,
    int prm_657,
    int prm_658,
    int prm_659,
    int prm_660,
    int prm_661)
{
    int dx_at_m93 = 0;
    int dy_at_m93 = 0;
    int x2_at_m93 = 0;
    int y2_at_m93 = 0;
    int x3_at_m93 = 0;
    int y3_at_m93 = 0;
    int p_at_m93 = 0;
    dx_at_m93 = 0;
    dy_at_m93 = 240;
    x2_at_m93 = prm_658;
    y2_at_m93 = prm_659;
    if (x2_at_m93 < 32)
    {
        x2_at_m93 = 32;
    }
    if (y2_at_m93 < 24)
    {
        y2_at_m93 = 24;
    }
    x3_at_m93 = prm_656 + x2_at_m93 / 16 * 16 - 16;
    y3_at_m93 = prm_657 + y2_at_m93 / 16 * 16 - 16;
    if (prm_661 == 0)
    {
        pos(prm_656 + 4, prm_657 + 4);
        gzoom(3, 24, 72, 228, 144, x2_at_m93 - 6, y2_at_m93 - 8);
    }
    if (prm_661 == 1)
    {
        pos(prm_656 + 4, prm_657 + 4);
        gzoom(3, 24, 72, 228, 144, x2_at_m93 - 6, y2_at_m93 - 8);
        pos(prm_656 + 4, prm_657 + 4);
        gfini(x2_at_m93 - 4, y2_at_m93 - 4);
        gfdec2(195, 205, 195);
    }
    if (prm_661 == 2)
    {
        pos(prm_656 + 4, prm_657 + 4);
        gzoom(3, 24, 72, 228, 144, x2_at_m93 - 6, y2_at_m93 - 8);
        pos(prm_656 + 4, prm_657 + 4);
        gfini(x2_at_m93 - 4, y2_at_m93 - 4);
        gfdec2(210, 215, 205);
    }
    if (prm_661 == 3)
    {
        pos(prm_656 + 4, prm_657 + 4);
        gzoom(3, 24, 72, 228, 144, x2_at_m93 - 6, y2_at_m93 - 8);
        pos(prm_656 + 4, prm_657 + 4);
        gfini(x2_at_m93 - 4, y2_at_m93 - 4);
        gfdec2(10, 13, 16);
    }
    if (prm_661 == 4)
    {
        pos(prm_656 + 4, prm_657 + 4);
        gzoom(3, 24, 72, 228, 144, x2_at_m93 - 6, y2_at_m93 - 8);
        pos(prm_656 + 4, prm_657 + 4);
        gfini(x2_at_m93 - 4, y2_at_m93 - 4);
        gfdec2(195, 205, 195);
    }
    if (prm_661 == 6)
    {
        pos(prm_656 + x2_at_m93 / 2, prm_657 + y2_at_m93 / 2);
        gmode(4, 228, 144, 180);
        grotate(3, 24, 72, 0, x2_at_m93 - 4, y2_at_m93 - 4);
    }
    gmode(2, 16, 16);
    for (int cnt = 0, cnt_end = (x2_at_m93 / 16 - 2); cnt < cnt_end; ++cnt)
    {
        pos(cnt * 16 + prm_656 + 16, prm_657);
        gcopy(3, prm_660 * 48 + dx_at_m93 + 16, dy_at_m93);
        pos(cnt * 16 + prm_656 + 16, prm_657 + y2_at_m93 - 16);
        gcopy(3, prm_660 * 48 + dx_at_m93 + 16, dy_at_m93 + 32);
    }
    pos(x3_at_m93, prm_657);
    gcopy(3, prm_660 * 48 + dx_at_m93 + 16, dy_at_m93, x2_at_m93 % 16, 16);
    pos(x3_at_m93, prm_657 + y2_at_m93 - 16);
    gcopy(3, prm_660 * 48 + dx_at_m93 + 16, dy_at_m93 + 32, x2_at_m93 % 16, 16);
    p_at_m93 = y2_at_m93 / 16 - 2;
    if (p_at_m93 < 0)
    {
        p_at_m93 = 0;
    }
    for (int cnt = 0, cnt_end = (p_at_m93); cnt < cnt_end; ++cnt)
    {
        pos(prm_656, cnt * 16 + prm_657 + 16);
        gcopy(3, prm_660 * 48 + dx_at_m93, dy_at_m93 + 16);
        pos(prm_656 + x2_at_m93 - 16, cnt * 16 + prm_657 + 16);
        gcopy(3, prm_660 * 48 + dx_at_m93 + 32, dy_at_m93 + 16);
    }
    pos(prm_656, y3_at_m93);
    gcopy(3, prm_660 * 48 + dx_at_m93, dy_at_m93 + 16, 16, y2_at_m93 % 16);
    pos(prm_656 + x2_at_m93 - 16, y3_at_m93);
    gcopy(3, prm_660 * 48 + dx_at_m93 + 32, dy_at_m93 + 16, 16, y2_at_m93 % 16);
    pos(prm_656, prm_657);
    gcopy(3, prm_660 * 48 + dx_at_m93, dy_at_m93);
    pos(prm_656, prm_657 + y2_at_m93 - 16);
    gcopy(3, prm_660 * 48 + dx_at_m93, dy_at_m93 + 32);
    pos(prm_656 + x2_at_m93 - 16, prm_657);
    gcopy(3, prm_660 * 48 + dx_at_m93 + 32, dy_at_m93);
    pos(prm_656 + x2_at_m93 - 16, prm_657 + y2_at_m93 - 16);
    gcopy(3, prm_660 * 48 + dx_at_m93 + 32, dy_at_m93 + 32);
    if (prm_661 == 5)
    {
        pos(prm_656 + 2, prm_657 + 2);
        gzoom(3, 24, 72, 228, 144, x2_at_m93 - 4, y2_at_m93 - 5);
        pos(prm_656 + 2, prm_657 + 2);
        gfini(x2_at_m93 - 4, y2_at_m93 - 4);
        gfdec2(195, 205, 195);
    }
    return;
}



void windowanime(
    int prm_726,
    int prm_727,
    int prm_728,
    int prm_729,
    int prm_730,
    int prm_731)
{
    int cenx_at_m105 = 0;
    int ceny_at_m105 = 0;
    if (nowindowanime)
    {
        nowindowanime = 0;
        return;
    }
    if (config::instance().windowanime == 0)
    {
        return;
    }
    gsel(prm_731);
    gmode(0);
    pos(0, 0);
    gcopy(0, prm_726, prm_727, prm_728, prm_729);
    gsel(0);
    gmode(0);
    x2_at_m105 = prm_728 / 2;
    y2_at_m105 = prm_729 / 2;
    cenx_at_m105 = prm_726 + x2_at_m105;
    ceny_at_m105 = prm_727 + y2_at_m105;
    for (int cnt = 1, cnt_end = cnt + (prm_730 - 1); cnt < cnt_end; ++cnt)
    {
        color(30, 30, 30);
        boxl(
            cenx_at_m105 - x2_at_m105 / prm_730 * cnt,
            ceny_at_m105 - y2_at_m105 / prm_730 * cnt,
            cenx_at_m105 + x2_at_m105 / prm_730 * cnt,
            ceny_at_m105 + y2_at_m105 / prm_730 * cnt);
        color(240, 240, 240);
        boxl(
            cenx_at_m105 - x2_at_m105 / prm_730 * cnt - 1,
            ceny_at_m105 - y2_at_m105 / prm_730 * cnt - 1,
            cenx_at_m105 + x2_at_m105 / prm_730 * cnt - 1,
            ceny_at_m105 + y2_at_m105 / prm_730 * cnt - 1);
        color(0, 0, 0);
        redraw();
        if (cnt != prm_730 - 1)
        {
            await(config::instance().animewait * 0.75);
        }
        pos(prm_726, prm_727);
        gcopy(prm_731, 0, 0, prm_728, prm_729);
    }
    gmode(2);
    return;
}



void windowanimecorner(
    int prm_732,
    int prm_733,
    int prm_734,
    int prm_735,
    int prm_736,
    int prm_737)
{
    if (config::instance().windowanime == 0)
    {
        return;
    }
    gsel(prm_737);
    gmode(0);
    pos(0, 0);
    gcopy(0, prm_732, prm_733, prm_734, prm_735);
    gsel(0);
    gmode(0);
    x2_at_m105 = prm_734 - prm_732;
    y2_at_m105 = prm_735 - prm_733;
    for (int cnt = 1, cnt_end = cnt + (prm_736); cnt < cnt_end; ++cnt)
    {
        color(30, 30, 30);
        boxl(
            prm_732 + prm_734,
            prm_733 + prm_735,
            prm_732 + prm_734 - (prm_734 - prm_732) / prm_736 * cnt,
            prm_733 + prm_735 - (prm_735 - prm_733) / prm_736 * cnt);
        color(240, 240, 240);
        boxl(
            prm_732 + prm_734 - 1,
            prm_733 + prm_735 - 1,
            prm_732 + prm_734 - (prm_734 - prm_732) / prm_736 * cnt - 1,
            prm_733 + prm_735 - (prm_735 - prm_733) / prm_736 * cnt - 1);
        color(0, 0, 0);
        redraw();
        if (cnt != prm_736)
        {
            await(config::instance().animewait * 0.75);
        }
        pos(prm_732, prm_733);
        gcopy(prm_737, 0, 0, prm_734, prm_735);
    }
    gmode(2);
    return;
}



void showtitle(const std::string&, const std::string& prm_739, int prm_740, int)
{
    int x_at_m106 = 0;
    int y_at_m106 = 0;
    font(12 + sizefix - en * 2);
    if (mode != 1)
    {
        x_at_m106 = prm_740 - 10;
        y_at_m106 = 0;
    }
    else
    {
        x_at_m106 = 240;
        y_at_m106 = windowh - 16;
    }
    for (int cnt = 0, cnt_end = ((windoww - x_at_m106 - 8) / 192 + 1);
         cnt < cnt_end;
         ++cnt)
    {
        pos(x_at_m106 + 8 + cnt * 192, y_at_m106);
        gcopy(3, 496, 581, 192, 18);
    }
    gmode(2);
    pos(x_at_m106, y_at_m106 + (mode != 1));
    gcopy(3, 96, 360, 24, 16);
    pos(x_at_m106 + 32, y_at_m106 + 1 + jp);
    bmes(prm_739, 250, 250, 250);
    return;
}



} // namespace elona

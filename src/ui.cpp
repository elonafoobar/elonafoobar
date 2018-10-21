#include "ui.hpp"
#include "ability.hpp"
#include "audio.hpp"
#include "character.hpp"
#include "config/config.hpp"
#include "debug.hpp"
#include "draw.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "map.hpp"
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
    draw("map_name_icon", inf_radarw + 6, inf_bary);
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
    static std::vector<Position> particles;

    const auto max_particles = windoww * windowh / 3500;
    if (particles.empty())
    {
        particles.resize(max_particles * 2);
    }

    for (int i = 0; i
         < max_particles * (1 + (map_data.type == mdata_t::MapType::world_map));
         ++i)
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

        if (particle == Position{0, 0})
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
    static std::vector<Position> particles;

    const auto max_particles = windoww * windowh / 3500;
    if (particles.empty())
    {
        particles.resize(max_particles * 2);
    }

    for (int i = 0; i
         < max_particles * (1 + (map_data.type == mdata_t::MapType::world_map));
         ++i)
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

        if (particle == Position{0, 0})
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
    static std::vector<Position> particles;

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

        if (particle == Position{0, 0} || weatherbk != game_data.weather)
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
    static std::vector<Position> particles;

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

        if (particle == Position{0, 0} || weatherbk != game_data.weather)
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
    if (!Config::instance().env)
        return;
    if (map_data.indoors_flag != 2)
        return;

    switch (game_data.weather)
    {
    case 3: render_weather_effect_rain(); break;
    case 4: render_weather_effect_hard_rain(); break;
    case 2: render_weather_effect_snow(); break;
    case 1: render_weather_effect_etherwind(); break;
    default: break;
    }

    weatherbk = game_data.weather;
    gmode(2);
}



void draw_minimap_pixel(int x, int y)
{
    const auto x2 = 120 * x / map_data.width;
    const auto y2 = 84 * y / map_data.height;
    pos(inf_radarx + x2, inf_radary + y2);
    gcopy(3, 688 + x2, 528 + y2, raderw, raderh);
}



void highlight_characters_in_pet_arena()
{
    for (auto&& cc : cdata.all())
    {
        if (cc.state() != Character::State::alive)
            continue;
        if (cc.index == 0)
            continue;
        snail::Color color{0};
        if (cc.relationship == 10)
        {
            color = {127, 127, 255, 32};
        }
        else if (cc.relationship == -3)
        {
            color = {255, 127, 127, 32};
        }
        else
        {
            continue;
        }
        const int x = (cc.position.x - scx) * inf_tiles + inf_screenx;
        const int y = (cc.position.y - scy) * inf_tiles + inf_screeny;
        if (0 <= x && x - inf_screenx < (inf_screenw - 1) * inf_tiles && 0 <= y
            && y < (inf_screenh - 1) * inf_tiles)
        {
            boxf(
                x,
                y * (y > 0),
                inf_tiles,
                inf_tiles + (y < 0) * inf_screeny,
                color);
            if (cc.index == camera)
            {
                gmode(4, 120);
                draw("camera", x + 36, y + 32);
                gmode(2);
            }
        }
    }
}



void render_pc_position_in_minimap()
{
    const auto x =
        clamp(120 * cdata.player().position.x / map_data.width, 2, 112);
    const auto y =
        clamp(84 * cdata.player().position.y / map_data.height, 2, 76);

    raderx = x;
    radery = y;
    draw("minimap_position", inf_radarx + x, inf_radary + y);
}



void render_stair_positions_in_minimap()
{
    for (int y = 0; y < map_data.height; ++y)
    {
        for (int x = 0; x < map_data.width; ++x)
        {
            const auto n = cell_data.at(x, y).feats / 1000 % 100;
            if (n == 10 || n == 11)
            {
                const auto sx = clamp(120 * x / map_data.width, 2, 112);
                const auto sy = clamp(84 * y / map_data.height, 2, 76);
                draw("minimap_position", inf_radarx + sx, inf_radary + sy);
            }
        }
    }
}



void _render_hp_or_mp_bar(
    int value,
    int max,
    int x,
    int y,
    int bar_offset_x,
    bool show_digit = false)
{
    draw("hp_bar_frame", x, y);

    if (value > 0)
    {
        const auto width = std::min(value * 84 / max, 100);
        pos(x + 16, y + 5);
        gcopy(3, bar_offset_x - width, 520, width, 6);
    }

    if (show_digit)
    {
        bmes(""s + value + u8"("s + max + u8")"s, x + 20, y - 8);
    }
}



void render_hp_bar(const Character& cc, int x, int y, bool show_digit = false)
{
    _render_hp_or_mp_bar(cc.hp, cc.max_hp, x, y, 412, show_digit);
}



void render_mp_bar(const Character& cc, int x, int y, bool show_digit = false)
{
    _render_hp_or_mp_bar(cc.mp, cc.max_mp, x, y, 532, show_digit);
}



void render_basic_attributes_and_pv_dv()
{
    const auto y = inf_bary + 2 + vfix;
    for (int i = 0; i < 10; ++i)
    {
        const auto x = inf_radarw + i * 47 + 166;
        if (i < 8)
        {
            // Basic attributes except for Speed
            if (cdata.player().attr_adjs[i] < 0)
            {
                color(200, 0, 0);
            }
            else
            {
                color(0, 0, 0);
            }
            pos(x, y);
            gcopy(3, 0, 440, 28, 16);
            mes(sdata(10 + i, 0));
            color(0, 0, 0);
        }
        else if (i == 8)
        {
            // Speed
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
            pos(x + 8, y);
            gcopy(3, 0, 440, 34, 16);
            mes(gspd);
            color(0, 0, 0);
        }
        else
        {
            // PV/DV
            pos(x + 14, y);
            gcopy(3, 0, 440, 64, 16);
            mes(""s + cdata.player().dv + u8"/"s + cdata.player().pv);
        }
    }
}



void _render_gold_or_platinum(
    int value,
    int x,
    int y,
    const std::string& icon_id,
    const std::string& unit)
{
    draw(icon_id, x, y);
    bmes(""s + value + " " + unit, x + 28, y + 2);
}



void render_gold()
{
    _render_gold_or_platinum(
        cdata.player().gold, windoww - 240, inf_ver - 16, "gold_coin", "gp");
}



void render_platinum()
{
    _render_gold_or_platinum(
        cdata.player().platinum_coin,
        windoww - 120,
        inf_ver - 16,
        "platinum_coin",
        "pp");
}



void render_character_level()
{
    const auto lvl = cdata.player().level;
    const auto exp =
        cdata.player().required_experience - cdata.player().experience;

    draw("character_level_icon", 4, inf_ver - 16);
    bmes(u8"Lv"s + lvl + u8"/"s + exp, 32, inf_ver - 14);
}



void render_date_label()
{
    pos(inf_clockx, inf_clocky);
    gcopy(3, 448, 408, inf_clockw, inf_clockh);
    draw("date_label_frame", inf_clockx + 78, inf_clocky + 8);
}



void render_buffs()
{
    const auto x = windoww - 40;
    auto y = inf_ver - 40;

    for (auto&& buff : cdata.player().buffs)
    {
        if (buff.id == 0)
            break;

        // Icon
        pos(x, y);
        gcopy(5, buff.id * 32, 1120, 32, 32);
        // Turns
        pos(x + 3, y + 19);
        mes(buff.turns);
        // Turns
        color(255, 255, 255);
        pos(x + 2, y + 18);
        mes(buff.turns);
        color(0, 0, 0);

        y -= 32;
    }
}



void render_clock()
{
    const auto& info = get_image_info("clock_hand");

    // Short hand
    draw_rotated(
        "clock_hand",
        inf_clockarrowx,
        inf_clockarrowy,
        game_data.date.hour * 30 + game_data.date.minute / 2);
    // Long hand
    draw_rotated(
        "clock_hand",
        inf_clockarrowx,
        inf_clockarrowy,
        info.width / 2,
        info.height,
        game_data.date.minute * 6);

    pos(inf_clockw - 3, inf_clocky + 17 + vfix);
    mes(""s + game_data.date.year + u8"/"s + game_data.date.month + u8"/"s
        + game_data.date.day);
    bmes(
        i18n::_(u8"ui", u8"time", u8"_"s + game_data.date.hour / 4) + u8" "s
            + i18n::_(u8"ui", u8"weather", u8"_"s + game_data.weather),
        inf_clockw + 6,
        inf_clocky + 35);
}



void render_skill_trackers()
{
    int y{};
    for (int i = 0; i < 10; ++i)
    {
        const auto skill = game_data.tracked_skills.at(i) % 10000;
        if (skill == 0)
        {
            continue;
        }
        const auto chara = game_data.tracked_skills.at(i) / 10000;
        if (chara != 0 && cdata[chara].state() != Character::State::alive)
        {
            game_data.tracked_skills.at(i) = 0;
            continue;
        }
        bmes(
            strutil::take_by_width(
                i18n::_(u8"ability", std::to_string(skill), u8"name"), 6),
            16,
            inf_clocky + 107 + y * 16);
        bmes(
            ""s + sdata.get(skill, chara).original_level + u8"."s
                + std::to_string(
                      1000 + sdata.get(skill, chara).experience % 1000)
                      .substr(1),
            66,
            inf_clocky + 107 + y * 16);
        if (elona::Config::instance().allow_enhanced_skill)
        {
            elona::snail::Color col{255, 130, 130};

            if (sdata.get(skill, chara).potential
                > elona::Config::instance().enhanced_skill_upperbound)
            {
                col = {130, 255, 130};
            }
            else if (
                sdata.get(skill, chara).potential
                > elona::Config::instance().enhanced_skill_lowerbound)
            {
                col = {255, 255, 130};
            }

            bmes(
                ""s + sdata.get(skill, chara).potential + u8"%"s,
                128,
                inf_clocky + 107 + y * 16,
                col);
        }

        ++y;
    }
}



template <typename F1, typename F2, typename F3>
int render_one_status_ailment(
    int value,
    int x,
    int y,
    F1 do_render,
    F2 get_text,
    F3 get_color)
{
    // Check signatures.
    static_assert(
        std::is_same<decltype(do_render(value)), bool>::value,
        "F1 signature: bool do_render(int value)");
    static_assert(
        std::is_same<decltype(get_text(value)), std::string>::value,
        "F2 signature: std::string get_text(int value)");
    static_assert(
        std::is_same<decltype(get_color(value)), snail::Color>::value,
        "F3 signature: snail::Color get_color(int value)");

    if (!do_render(value))
        return y;

    const auto text_color = get_color(value);
    color(text_color.r, text_color.g, text_color.b);
    pos(x, y);
    gcopy(3, 0, 416, 50 + en * 30, 15);
    pos(x + 6, y + 1);
    mes(get_text(value));
    color(0, 0, 0);

    return y - 20;
}



template <typename F1, typename F3>
int render_one_status_ailment(
    int value,
    int x,
    int y,
    F1 do_render,
    const std::string& text,
    F3 get_color)
{
    return render_one_status_ailment(
        value, x, y, do_render, [&](auto) { return text; }, get_color);
}



template <typename F1, typename F2>
int render_one_status_ailment(
    int value,
    int x,
    int y,
    F1 do_render,
    F2 get_text,
    const snail::Color& text_color)
{
    return render_one_status_ailment(
        value, x, y, do_render, get_text, [&](auto) { return text_color; });
}



template <typename F1>
int render_one_status_ailment(
    int value,
    int x,
    int y,
    F1 do_render,
    const std::string& text,
    const snail::Color& text_color)
{
    return render_one_status_ailment(
        value,
        x,
        y,
        do_render,
        [&](auto) { return text; },
        [&](auto) { return text_color; });
}



void render_status_ailments()
{
    const auto x = 8;
    auto y = inf_ver - 50;

    y = render_one_status_ailment(
        cdata.player().nutrition / 1000,
        x,
        y,
        [](auto nutrition) { return !(5 <= nutrition && nutrition <= 9); },
        [](auto nutrition) {
            return (nutrition >= 12)
                ? i18n::_("ui", "hunger", "_12")
                : (nutrition >= 1) ? i18n::_("ui", "hunger", "_"s + nutrition)
                                   : i18n::_("ui", "hunger", "_0");
        },
        [](auto nutrition) {
            return (nutrition >= 10)
                ? snail::Color{0, 0, 0}
                : (nutrition >= 1) ? snail::Color{200, 0, 0}
                                   : snail::Color{250, 0, 0};
        });

    y = render_one_status_ailment(
        cdata.player().sick,
        x,
        y,
        [](auto turn) { return turn != 0; },
        [](auto turn) {
            return (turn >= 30) ? i18n::_("ui", "sick", "_1")
                                : i18n::_("ui", "sick", "_0");
        },
        {80, 120, 0});

    y = render_one_status_ailment(
        cdata.player().poisoned,
        x,
        y,
        [](auto turn) { return turn != 0; },
        [](auto turn) {
            return (turn >= 30) ? i18n::_("ui", "poison", "_1")
                                : i18n::_("ui", "poison", "_0");
        },
        {0, 150, 0});

    y = render_one_status_ailment(
        cdata.player().sleep,
        x,
        y,
        [](auto turn) { return turn != 0; },
        [](auto turn) {
            return (turn >= 30) ? i18n::_("ui", "sleep", "_1")
                                : i18n::_("ui", "sleep", "_0");
        },
        {0, 50, 50});

    y = render_one_status_ailment(
        cdata.player().blind,
        x,
        y,
        [](auto turn) { return turn != 0; },
        i18n::_("ui", "blind"),
        {100, 100, 0});

    y = render_one_status_ailment(
        cdata.player().paralyzed,
        x,
        y,
        [](auto turn) { return turn != 0; },
        i18n::_("ui", "paralyzed"),
        {0, 100, 100});

    y = render_one_status_ailment(
        cdata.player().choked,
        x,
        y,
        [](auto turn) { return turn != 0; },
        i18n::_("ui", "choked"),
        {0, 100, 100});

    y = render_one_status_ailment(
        cdata.player().confused,
        x,
        y,
        [](auto turn) { return turn != 0; },
        i18n::_("ui", "confused"),
        {100, 0, 100});

    y = render_one_status_ailment(
        cdata.player().fear,
        x,
        y,
        [](auto turn) { return turn != 0; },
        i18n::_("ui", "fear"),
        {100, 0, 100});

    y = render_one_status_ailment(
        cdata.player().dimmed,
        x,
        y,
        [](auto turn) { return turn != 0; },
        [](auto turn) {
            return (turn >= 60)
                ? i18n::_(u8"ui", u8"dimmed", u8"_2")
                : (turn >= 30) ? i18n::_(u8"ui", u8"dimmed", u8"_1")
                               : i18n::_(u8"ui", u8"dimmed", u8"_0");
        },
        {0, 100, 100});

    y = render_one_status_ailment(
        cdata.player().furious,
        x,
        y,
        [](auto turn) { return turn != 0; },
        [](auto turn) {
            return (turn >= 30) ? i18n::_(u8"ui", u8"angry", u8"_1")
                                : i18n::_(u8"ui", u8"angry", u8"_0");
        },
        {150, 0, 0});

    y = render_one_status_ailment(
        cdata.player().bleeding,
        x,
        y,
        [](auto turn) { return turn != 0; },
        [](auto turn) {
            return (turn >= 20)
                ? i18n::_(u8"ui", u8"bleeding", u8"_2")
                : (turn >= 10) ? i18n::_(u8"ui", u8"bleeding", u8"_1")
                               : i18n::_(u8"ui", u8"bleeding", u8"_0");
        },
        {150, 0, 0});

    y = render_one_status_ailment(
        cdata.player().insane,
        x,
        y,
        [](auto turn) { return turn != 0; },
        [](auto turn) {
            return (turn >= 50)
                ? i18n::_(u8"ui", u8"insane", u8"_2")
                : (turn >= 25) ? i18n::_(u8"ui", u8"insane", u8"_1")
                               : i18n::_(u8"ui", u8"insane", u8"_0");
        },
        {150, 100, 0});

    y = render_one_status_ailment(
        cdata.player().drunk,
        x,
        y,
        [](auto turn) { return turn != 0; },
        i18n::_(u8"ui", u8"drunk"),
        {100, 0, 100});

    y = render_one_status_ailment(
        cdata.player().wet,
        x,
        y,
        [](auto turn) { return turn != 0; },
        i18n::_(u8"ui", u8"wet"),
        {0, 0, 160});

    y = render_one_status_ailment(
        cdata.player().gravity,
        x,
        y,
        [](auto turn) { return turn != 0; },
        i18n::_(u8"ui", u8"gravity"),
        {0, 80, 80});

    y = render_one_status_ailment(
        game_data.continuous_active_hours,
        x,
        y,
        [](auto hours) { return hours >= 15; },
        [](auto hours) {
            return (hours >= 50)
                ? i18n::_(u8"ui", u8"sleepy", u8"_2")
                : (hours >= 30) ? i18n::_(u8"ui", u8"sleepy", u8"_1")
                                : i18n::_(u8"ui", u8"sleepy", u8"_0");
        },
        [](auto hours) {
            return (hours >= 50) ? snail::Color{255, 0, 0}
                                 : (hours >= 30) ? snail::Color{100, 100, 0}
                                                 : snail::Color{0, 0, 0};
        });

    y = render_one_status_ailment(
        cdata.player().sp,
        x,
        y,
        [](auto sp) { return sp < 50; },
        [](auto sp) {
            return (sp < 0) ? i18n::_(u8"ui", u8"tired", u8"_2")
                            : (sp < 25) ? i18n::_(u8"ui", u8"tired", u8"_1")
                                        : i18n::_(u8"ui", u8"tired", u8"_0");
        },
        [](auto sp) {
            return (sp < 0)
                ? snail::Color{120, 120, 0}
                : (sp < 25) ? snail::Color{80, 80, 0} : snail::Color{60, 60, 0};
        });

    y = render_one_status_ailment(
        cdata.player().inventory_weight_type,
        x,
        y,
        [](auto state) { return state != 0; },
        [](auto state) { return i18n::_(u8"ui", u8"burden", u8"_"s + state); },
        [](auto state) {
            return snail::Color{0,
                                static_cast<uint8_t>(state * 40),
                                static_cast<uint8_t>(state * 40)};
        });

    y = render_one_status_ailment(
        static_cast<int>(foobar_data.is_autodig_enabled),
        x,
        y,
        [](auto is_enabled) { return is_enabled == 1; },
        i18n::_(u8"ui", u8"autodig", u8"mode"),
        {0, 0, 0});
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

Position gmes(
    const std::string& text,
    int x_base,
    int y_base,
    int width,
    const snail::Color& text_color_base,
    bool shadow)
{
    int font_size = 14;
    font(font_size - en * 2);

    const auto message = text + u8"$end";
    int x = x_base;
    int y = y_base;
    size_t pos = 0;
    snail::Color text_color = text_color_base;

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
                font(font_size - en * 2, snail::Font::Style::underline);
                text_color = {50, 50, 255};
            }
            else if (tag == u8"emp2")
            {
                font(font_size - en * 2, snail::Font::Style::bold);
                text_color = {40, 130, 40};
            }
            else if (tag == u8"title1")
            {
                font_size = 12;
                font(font_size - en * 2, snail::Font::Style::bold);
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
                font(font_size - en * 2, snail::Font::Style::bold);
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
        ui_render_non_hud();
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
            draw("casino_title_decoration_left", sx - 30, 5);
            draw(
                "casino_title_decoration_right",
                sx + strlen_u(atxinfon(0)) * 13 / 2 + 14,
                5);
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
    for (int y = 0; y < map_data.height; ++y)
    {
        for (int x = 0; x < map_data.width; ++x)
        {
            if (cell_data.at(x, y).chip_id_memory
                == cell_data.at(x, y).chip_id_actual)
            {
                draw_minimap_pixel(x, y);
            }
        }
    }
}



void ui_render_from_screensync()
{
    gmode(2);
    ui_render_non_hud();
    render_hud();
    redraw();
    screenupdate = 0;
}



void render_hud()
{
    gmode(2);

    // HP/MP bar
    font(12 - en * 2, snail::Font::Style::bold);
    render_hp_bar(cdata.player(), inf_hpx, inf_hpy, true);
    render_mp_bar(cdata.player(), inf_mpx, inf_mpy, true);
    if (game_data.mount != 0
        && cdata[game_data.mount].state() == Character::State::alive)
    {
        render_hp_bar(cdata[game_data.mount], inf_hpx - 120, inf_hpy);
    }

    // Basic attributes and PV/DV.
    font(13 - en * 2);
    render_basic_attributes_and_pv_dv();

    // Gold/platinum
    render_gold();
    render_platinum();

    // Character level
    render_character_level();

    // Set transparency of UI parts.
    if (cdata.player().position.x < 6)
    {
        if (mode != 9)
        {
            if (map_data.type != mdata_t::MapType::world_map)
            {
                if (!cdata.player().continuous_action)
                {
                    gmode(4, 150);
                }
            }
        }
    }

    // Status ailments
    render_status_ailments();

    // Date label
    render_date_label();

    // Buffs
    gmode(4, 180);
    render_buffs();
    gmode(2);

    // Clock
    render_clock();

    // Skill trackers
    render_skill_trackers();

    // HP bars(pets)
    if (Config::instance().hp_bar != "hide")
    {
        show_hp_bar(
            Config::instance().hp_bar == "left" ? HPBarSide::left_side
                                                : HPBarSide::right_side,
            inf_clocky);
    }

    // Damage popups
    show_damage_popups();

    // Lua console, if active
    lua::lua->get_console().draw();
}



void load_continuous_action_animation()
{
    gsel(9);
    pos(0, 0);
    if (cdata.player().continuous_action.type
        == ContinuousAction::Type::dig_wall)
    {
        picload(filesystem::dir::graphic() / u8"anime1.bmp");
    }
    if (cdata.player().continuous_action.type == ContinuousAction::Type::fish)
    {
        if (rowactre)
        {
            picload(filesystem::dir::graphic() / u8"anime2.bmp");
        }
    }
    if (cdata.player().continuous_action.type
        == ContinuousAction::Type::search_material)
    {
        picload(filesystem::dir::graphic() / u8"anime3.bmp");
    }
    if (cdata.player().continuous_action.type
        == ContinuousAction::Type::dig_ground)
    {
        picload(filesystem::dir::graphic() / u8"anime4.bmp");
    }
    gsel(0);
}



void render_autoturn_animation()
{
    if (racount == 0 && Config::instance().animewait != 0)
    {
        load_continuous_action_animation();
    }
    if (msgtemp != ""s
        || (cdata.player().continuous_action.type
                == ContinuousAction::Type::fish
            && rowactre == 0 && fishanime == 0))
    {
        ui_render_non_hud();
        msgtemp = "";
        render_hud();
    }
    if (cdata.player().continuous_action.type == ContinuousAction::Type::fish)
    {
        if (rowactre == 0 && Config::instance().animewait != 0)
        {
            render_fishing_animation();
        }
    }
    sx = windoww - 156;
    sy = inf_ver - 30;
    int w = 148;
    int h = 25;

    window2(sx, sy, w, h, 0, 5);
    font(13 - en * 2, snail::Font::Style::bold);
    bmes(u8"AUTO TURN"s, sx + 43, sy + 6, {235, 235, 235});
    gmode(2);
    draw_rotated("hourglass", sx + 18, sy + 12, game_data.date.minute / 4 * 24);

    if (cdata.player().continuous_action.type
            == ContinuousAction::Type::dig_ground
        || cdata.player().continuous_action.type
            == ContinuousAction::Type::dig_wall
        || cdata.player().continuous_action.type
            == ContinuousAction::Type::search_material
        || (cdata.player().continuous_action.type
                == ContinuousAction::Type::fish
            && rowactre != 0))
    {
        if (Config::instance().animewait != 0)
        {
            window2(sx, sy - 104, 148, 101, 0, 5);
            if (racount % 15 == 0)
            {
                for (int cnt = 0; cnt < 10; ++cnt)
                {
                    gmode(0);
                    pos(sx + 2, sy - 102);
                    if (cdata.player().continuous_action.type
                        == ContinuousAction::Type::dig_wall)
                    {
                        if (cnt == 2)
                        {
                            snd("core.dig1");
                        }
                        gcopy(9, cnt / 2 % 5 * 144, 0, 144, 96);
                        await(Config::instance().animewait * 2);
                    }
                    if (cdata.player().continuous_action.type
                        == ContinuousAction::Type::fish)
                    {
                        if (racount == 0)
                        {
                            if (cnt == 0)
                            {
                                snd("core.water");
                            }
                        }
                        gcopy(9, cnt / 3 % 3 * 144, 0, 144, 96);
                        await(Config::instance().animewait * 2.5);
                    }
                    if (cdata.player().continuous_action.type
                        == ContinuousAction::Type::search_material)
                    {
                        if (cnt == 4)
                        {
                            snd("core.bush1");
                        }
                        gcopy(9, cnt / 2 % 3 * 144, 0, 144, 96);
                        await(Config::instance().animewait * 2.75);
                    }
                    if (cdata.player().continuous_action.type
                        == ContinuousAction::Type::dig_ground)
                    {
                        if (cnt == 2)
                        {
                            snd("core.dig2");
                        }
                        gcopy(9, cnt / 2 % 4 * 144, 0, 144, 96);
                        await(Config::instance().animewait * 3);
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
            sx(0) = cdata.player().next_position.x - scx;
            sx(1) = cdata.player().next_position.x;
            sy(0) = cdata.player().next_position.y - scy;
            sy(1) = cdata.player().next_position.y;
        }
        else
        {
            sx(0) = cdata.player().position.x - scx;
            sx(1) = cdata.player().position.x;
            sy(0) = cdata.player().position.y - scy;
            sy(1) = cdata.player().position.y;
        }
    }
    else
    {
        sx(0) = tlocx - scx;
        sx(1) = tlocx;
        sy(0) = tlocy - scy;
        sy(1) = tlocy;
    }
    if (game_data.current_map == mdata_t::MapId::pet_arena)
    {
        sx(0) = cdata[camera].position.x - scx;
        sx(1) = cdata[camera].position.x;
        sy(0) = cdata[camera].position.y - scy;
        sy(1) = cdata[camera].position.y;
    }
    if (Config::instance().alwayscenter)
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
    if (scx + inf_screenw >= map_data.width)
    {
        scx = map_data.width - inf_screenw;
    }
    if (scy + inf_screenh >= map_data.height)
    {
        scy = map_data.height - inf_screenh;
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

    Position center{cdata.player().position.x - (fov_max + 2) / 2,
                    (fov_max + 2) / 2 - cdata.player().position.y};
    sy(2) = cdata.player().position.y - fov_max / 2;
    sy(3) = cdata.player().position.y + fov_max / 2;

    if (Config::instance().scroll)
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
    ly = 1 + (Config::instance().scroll == 0);
    for (int cnt = reph(1), cnt_end = cnt + (reph); cnt < cnt_end; ++cnt)
    {
        sy = cnt;
        lx = 1 + (Config::instance().scroll == 0);
        if (sy < 0 || sy >= map_data.height)
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
            if (sx < 0 || sx >= map_data.width)
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
            if (game_data.current_map == mdata_t::MapId::pet_arena)
            {
                goto label_1430_internal;
            }
            if (cdata.player().blind != 0)
            {
                if (sx != cdata.player().position.x
                    || sy != cdata.player().position.y)
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
                            cdata.player().position.x,
                            cdata.player().position.y,
                            sx,
                            sy))
                    {
                    label_1430_internal:
                        mapsync(sx, sy) = msync;
                        if (cell_data.at(sx, sy).chara_index_plus_one != 0)
                        {
                            cdata[cell_data.at(sx, sy).chara_index_plus_one - 1]
                                .vision_flag = msync;
                        }
                        if (cell_data.at(sx, sy).chip_id_memory
                            != cell_data.at(sx, sy).chip_id_actual)
                        {
                            cell_data.at(sx, sy).chip_id_memory =
                                cell_data.at(sx, sy).chip_id_actual;
                            draw_minimap_pixel(sx, sy);
                        }
                        cell_data.at(sx, sy).item_appearances_memory =
                            cell_data.at(sx, sy).item_appearances_actual;
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



void ui_render_non_hud()
{
    cell_draw();

    if (game_data.current_map == mdata_t::MapId::pet_arena)
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



void ui_scroll_screen()
{
    int scxbk2 = 0;
    int scybk2 = 0;
    if (std::abs(cdata.player().next_position.x - cdata.player().position.x)
        > 1)
    {
        return;
    }
    if (std::abs(cdata.player().next_position.y - cdata.player().position.y)
        > 1)
    {
        return;
    }
    scrollp = Config::instance().walkwait;
    if (map_data.type == mdata_t::MapType::world_map)
    {
        scrollp = 6;
        keybd_wait = 1000;
        if (chipm(
                0,
                cell_data
                    .at(cdata.player().position.x, cdata.player().position.y)
                    .chip_id_actual)
            == 4)
        {
            scrollp = 9;
        }
    }
    else if (keybd_wait > Config::instance().startrun)
    {
        scrollp = 3;
        if (Config::instance().runscroll == 0)
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
        sxfix = (cdata.player().next_position.x - cdata.player().position.x)
            * cnt * inf_tiles / scrollp * -1;
        syfix = (cdata.player().next_position.y - cdata.player().position.y)
            * cnt * inf_tiles / scrollp * -1;
        gsel(4);
        pos(0, 0);
        gmode(0);
        gcopy(0, 0, windowh - inf_verh, windoww, inf_tiles);
        gsel(0);
        gmode(2);
        ui_render_non_hud();
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



void ui_initialize_minimap()
{
    gsel(3);
    for (int cnt = 0, cnt_end = (map_data.height); cnt < cnt_end; ++cnt)
    {
        sy = cnt;
        for (int cnt = 0, cnt_end = (map_data.width); cnt < cnt_end; ++cnt)
        {
            sx = cnt;
            sy(1) = 84 * sy / map_data.height;
            sx(1) = 120 * sx / map_data.width;
            pos(688 + sx(1), 528 + sy(1));
            gcopy(
                2,
                cell_data.at(sx, sy).chip_id_actual % 33 * inf_tiles + sx % 16,
                cell_data.at(sx, sy).chip_id_actual / 33 * inf_tiles + sy % 12,
                raderw,
                raderh);
            pos(688 + sx(1), 528 + sy(1));
            if (chipm(7, cell_data.at(sx, sy).chip_id_actual) & 4)
            {
                boxf(688 + sx(1), 528 + sy(1), raderw, raderh, {0, 0, 0, 100});
            }
        }
    }
    boxf(
        688,
        528,
        raderw * map_data.width,
        raderh * map_data.height,
        {255, 255, 255, 10});
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



void ui_win_screen_fade()
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



void event_7_setup()
{
    boxf();
    evx = 12;
    evy = 14;
    evtiles = 48;
    evscrh = windowh / evtiles - 1;
    evscrw = windoww / evtiles + 2;
    event_7_modify_screen();
    redraw();
}



void event_7_modify_screen()
{
    for (int cnt = 0, cnt_end = (evscrh); cnt < cnt_end; ++cnt)
    {
        y = cnt;
        dy = cnt + evy;
        if (dy >= map_data.height)
        {
            dy = map_data.height;
        }
        for (int cnt = 0, cnt_end = (evscrw); cnt < cnt_end; ++cnt)
        {
            x = cnt;
            dx = cnt + evx;
            if (dx >= map_data.width)
            {
                dx = map_data.width;
            }
            ap = cell_data.at(dx, dy).chip_id_actual;
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
    fishdir = fishdir(cdata.player().direction);
    randomize(cdata.player().turn / 3);
    gmode(2);
    if (fishanime == 4)
    {
        sx = (fishx - scx) * inf_tiles + inf_screenx;
        sy = (fishy - scy) * inf_tiles + inf_screeny;
        if (fishanime(1) > 15)
        {
            sx += (cdata.player().position.x - fishx) * 8 * (fishanime(1) - 15);
            sy += (cdata.player().position.y - fishy) * 8 * (fishanime(1) - 15)
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
    sx = (cdata.player().position.x - scx) * inf_tiles + inf_screenx + 20;
    if (fishdir == 1)
    {
        sx -= 48;
    }
    if (fishdir == 3)
    {
        sx += 48;
    }
    sy = (cdata.player().position.y - scy) * inf_tiles + inf_screeny + 20;
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
    sx = (cdata.player().position.x - scx) * inf_tiles + inf_screenx;
    sy = (cdata.player().position.y - scy) * inf_tiles + inf_screeny;
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
    font(12 + sizefix - en * 2, snail::Font::Style::bold);
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
    int window_x,
    int window_y,
    int window_width,
    int window_height,
    int prm_672,
    int prm_673)
{
    if (windowshadow == 1)
    {
        window(
            window_x + 4,
            window_y + 4,
            window_width,
            window_height - window_height % 8,
            true);
        windowshadow = 0;
    }
    window(window_x, window_y, window_width, window_height - window_height % 8);
    if (s != ""s)
    {
        window2(
            window_x + 34,
            window_y - 4,
            45 * window_width / 100 + clamp(int(strlen_u(s) * 8 - 120), 0, 200),
            32,
            1,
            1);
    }
    gmode(2);
    draw(
        "tip_icon",
        window_x + 30 + prm_672,
        window_y + window_height - 47 - window_height % 8);
    line(
        window_x + 50 + prm_672,
        window_y + window_height - 48 - window_height % 8,
        window_x + window_width - 40,
        window_y + window_height - 48 - window_height % 8,
        {194, 170, 146});
    line(
        window_x + 50 + prm_672,
        window_y + window_height - 49 - window_height % 8,
        window_x + window_width - 40,
        window_y + window_height - 49 - window_height % 8,
        {234, 220, 188});
    font(15 + en - en * 2);
    bmes(
        s,
        window_x + 45 * window_width / 200 + 34 - strlen_u(s) * 4
            + clamp(int(strlen_u(s) * 8 - 120), 0, 200) / 2,
        window_y + 4 + vfix,
        {255, 255, 255},
        {20, 10, 0});
    font(12 + sizefix - en * 2);
    pos(window_x + 58 + prm_672,
        window_y + window_height - 43 - window_height % 8);
    mes(s(1));
    if (pagesize != 0)
    {
        s = u8"Page."s + (page + 1) + u8"/"s + (pagemax + 1);
        font(12 + sizefix - en * 2, snail::Font::Style::bold);
        pos(window_x + window_width - strlen_u(s) * 7 - 40 - prm_673,
            window_y + window_height - 65 - window_height % 8);
        mes(s);
    }
    wx = window_x;
    wy = window_y;
    ww = window_width;
    wh = window_height;
}



void display_note(const std::string& prm_674, int prm_675)
{
    font(12 + sizefix - en * 2, snail::Font::Style::bold);
    pos(wx + ww - strlen_u(prm_674) * 7 - 140 - prm_675, wy + wh - 65 - wh % 8);
    mes(prm_674);
}



void display_topic(const std::string& topic, int x, int y)
{
    font(12 + sizefix - en * 2, snail::Font::Style::bold);
    draw("topic_icon", x, y + 7);
    pos(x + 26, y + 8);
    mes(topic);
    line(x + 22, y + 21, x + strlen_u(topic) * 7 + 36, y + 21);
}



void display_customkey(const std::string& key, int x, int y)
{
    gsel(3);
    gmode(0);
    font(15 - en * 2);
    draw("select_key", 624, 30);
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
            == IdentifyState::completely_identified)
        {
            switch (inv[ci].curse_state)
            {
            case CurseState::doomed: color(100, 10, 100); break;
            case CurseState::cursed: color(150, 10, 10); break;
            case CurseState::none: color(10, 40, 120); break;
            case CurseState::blessed: color(10, 110, 30); break;
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



void showscroll(const std::string& hint, int x, int y, int width, int height)
{
    if (windowshadow != 0)
    {
        gmode(6, 80);
        draw_scroll(x + 3, y + 3, width, height);
        windowshadow = 0;
        gmode(2);
    }
    draw_scroll(x, y, width, height);

    if (hint.empty())
        return;

    draw("tip_icon", x + 40, y + height - 67 - height % 8);
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
    mes(hint);
    if (pagesize != 0)
    {
        s = u8"Page."s + (page + 1) + u8"/"s + (pagemax + 1);
        font(12 + sizefix - en * 2, snail::Font::Style::bold);
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
        boxf(x + 2, y + 2, width - 4, height - 4, {0, 0, 0, 195});
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
    if (!Config::instance().windowanime)
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
            await(Config::instance().animewait * 0.75);
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
    if (!Config::instance().windowanime)
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
            await(Config::instance().animewait * 0.75);
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
        draw("title_label_frame", x + 8 + i * 192, y);
    }
    gmode(2);
    draw("tip_icon", x, y + (mode != 1));
    font(12 + sizefix - en * 2);
    bmes(title, x + 32, y + 1 + jp, {250, 250, 250});
}



} // namespace elona

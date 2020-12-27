#include "ui.hpp"

#include "../util/strutil.hpp"
#include "audio.hpp"
#include "cell_draw.hpp"
#include "character.hpp"
#include "config.hpp"
#include "data/types/type_asset.hpp"
#include "data/types/type_buff.hpp"
#include "data/types/type_skill.hpp"
#include "debug.hpp"
#include "draw.hpp"
#include "fov.hpp"
#include "game.hpp"
#include "globals.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "lua_env/console.hpp"
#include "map.hpp"
#include "random.hpp"
#include "skill.hpp"
#include "text.hpp"
#include "variables.hpp"



namespace
{

constexpr int inf_clockw = 120;

int raderh;
int raderw;
int raderx;
int radery;

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

int pagebk = 0;
int csprev = 0;
int pagesaved = 0;



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
        draw_bar_vert(
            "core.hud_bar", cnt * 192, inf_bary, sx, inf_barh, inf_barh);
        draw_region("core.message_window", cnt * 192, inf_msgy, sx, inf_msgh);
    }
    draw_region("core.hud_minimap", 0, inf_msgy, inf_msgx, inf_verh);
    draw("core.map_name_icon", inf_radarw + 6, inf_bary);
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
        draw_indexed(
            "core.attribute_icon",
            inf_radarw + cnt * 47 + 148 + sx,
            inf_bary + 1,
            cnt);
    }
    font(12 + sizefix - en * 2);

    auto map_name = mdatan(0);
    if (strlen_u(map_name) > size_t(16 - (maplevel() != ""s) * 4))
    {
        map_name =
            strutil::take_by_width(map_name, 16 - (maplevel() != ""s) * 4);
    }
    mes(inf_radarw + 24, inf_bary + 3 + vfix - en, cnven(map_name));

    mes(inf_radarw + 114, inf_bary + 3 + vfix - en, maplevel());
}



void render_weather_effect_rain()
{
    static std::vector<Position> particles;

    const auto max_particles = windoww * windowh / 3500;
    if (particles.empty())
    {
        particles.resize(max_particles * 2);
    }

    for (int i = 0; i <
         max_particles * (1 + (map_data.type == mdata_t::MapType::world_map));
         ++i)
    {
        auto&& particle = particles[i];

        if (particle != Position{0, 0})
        {
            const auto brightness = rnd(100);
            // Draw.
            line(
                particle.x,
                particle.y,
                particle.x + i % 2 + 1,
                particle.y + i % 3 + 1,
                {static_cast<uint8_t>(70 + brightness),
                 static_cast<uint8_t>(100 + brightness),
                 static_cast<uint8_t>(150 + brightness)});
        }

        if (particle == Position{0, 0})
        {
            // Create new particle.
            particle.x = rnd(windoww);
            particle.y = rnd(windowh - inf_verh) - 6;
        }
        else
        {
            // Update position.
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

    for (int i = 0; i <
         max_particles * (1 + (map_data.type == mdata_t::MapType::world_map));
         ++i)
    {
        auto&& particle = particles[i];

        if (particle != Position{0, 0})
        {
            const auto brightness = rnd(100);
            // Draw.
            line(
                particle.x,
                particle.y,
                particle.x + i % 2 + 1,
                particle.y + i % 5 + 4,
                {static_cast<uint8_t>(70 + brightness),
                 static_cast<uint8_t>(100 + brightness),
                 static_cast<uint8_t>(150 + brightness)});
        }

        if (particle == Position{0, 0})
        {
            // Create new particle.
            particle.x = rnd(windoww);
            particle.y = rnd(windowh - inf_verh) - 6;
        }
        else
        {
            // Update position.
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
            gmode(2, 100 + i % 150);
        }

        if (particle != Position{0, 0})
        {
            // Draw.
            draw_indexed_region(
                "core.weather_particle",
                particle.x,
                particle.y,
                particle.x % 2,
                i % 6,
                1,
                1);
        }

        if (particle == Position{0, 0} || g_prev_weather != game()->weather)
        {
            // Create new particle.
            particle.x = rnd(windoww);
            particle.y = -rnd(windowh / 2);
        }
        else
        {
            // Update position.
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
            gmode(2, 100 + i % 150);
        }

        if (particle != Position{0, 0})
        {
            // Draw.
            draw_indexed_region(
                "core.weather_particle",
                particle.x,
                particle.y,
                2 + particle.x % 2,
                i % 6,
                1,
                1);
        }

        if (particle == Position{0, 0} || g_prev_weather != game()->weather)
        {
            // Create new particle.
            particle.x = rnd(windoww);
            particle.y = windowh - inf_verh - 8 - rnd(100);
        }
        else
        {
            // Update position.
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
    if (!g_config.weather_effect())
        return;
    if (map_data.indoors_flag != 2)
        return;

    if (game()->weather == "core.etherwind")
    {
        render_weather_effect_etherwind();
    }
    else if (game()->weather == "core.snow")
    {
        render_weather_effect_snow();
    }
    else if (game()->weather == "core.rain")
    {
        render_weather_effect_rain();
    }
    else if (game()->weather == "core.hard_rain")
    {
        render_weather_effect_hard_rain();
    }

    g_prev_weather = game()->weather;
    gmode(2);
}



void draw_minimap_pixel(int x, int y)
{
    const auto x2 = 120 * x / map_data.width;
    const auto y2 = 84 * y / map_data.height;
    draw_region(
        "core.minimap_scratch",
        inf_radarx + x2,
        inf_radary + y2,
        x2,
        y2,
        raderw,
        raderh);
}



void highlight_characters_in_pet_arena()
{
    for (auto&& chara : cdata.all())
    {
        if (chara.state() != Character::State::alive)
            continue;
        if (chara.is_player())
            continue;
        snail::Color color{0};
        if (chara.relationship == Relationship::ally)
        {
            color = {127, 127, 255, 32};
        }
        else if (chara.relationship == Relationship::enemy)
        {
            color = {255, 127, 127, 32};
        }
        else
        {
            continue;
        }
        const int x = (chara.position.x - scx) * inf_tiles + inf_screenx;
        const int y = (chara.position.y - scy) * inf_tiles + inf_screeny;
        if (0 <= x && x - inf_screenx < (inf_screenw - 1) * inf_tiles &&
            0 <= y && y < (inf_screenh - 1) * inf_tiles)
        {
            boxf(
                x,
                y * (y > 0),
                inf_tiles,
                inf_tiles + (y < 0) * inf_screeny,
                color);
            if (chara.index == camera)
            {
                gmode(2, 120);
                draw("core.camera", x + 36, y + 32);
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
    draw("core.minimap_position", inf_radarx + x, inf_radary + y);
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
                draw("core.minimap_position", inf_radarx + sx, inf_radary + sy);
            }
        }
    }
}



void _render_hp_or_mp_bar(
    int value,
    int max,
    int x,
    int y,
    data::InstanceId bar_id,
    bool show_digit = false)
{
    draw("core.hp_bar_frame", x, y);

    if (value > 0)
    {
        const auto width = std::min(value * 84 / max, 100);
        draw_bar(bar_id, x + 16, y + 5, width, 6, width);
    }

    if (show_digit)
    {
        bmes(""s + value + "("s + max + ")"s, x + 20, y - 8);
    }
}



void render_hp_bar(
    const Character& chara,
    int x,
    int y,
    bool show_digit = false)
{
    _render_hp_or_mp_bar(
        chara.hp, chara.max_hp, x, y, "core.hud_hp_bar", show_digit);
}



void render_mp_bar(
    const Character& chara,
    int x,
    int y,
    bool show_digit = false)
{
    _render_hp_or_mp_bar(
        chara.mp, chara.max_mp, x, y, "core.hud_mp_bar", show_digit);
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
            draw_region("core.attributes_bar", x, y, 28);
            const auto text_color = cdata.player().attr_adjs[i] < 0
                ? snail::Color{200, 0, 0}
                : snail::Color{0, 0, 0};
            mes(x,
                y,
                std::to_string(cdata.player().skills().level(
                    *the_skill_db.get_id_from_integer(10 + i))),
                text_color);
        }
        else if (i == 8)
        {
            // Speed
            draw_region("core.attributes_bar", x + 8, y, 34);
            snail::Color text_color{0, 0, 0};
            if (gspdorg > gspd)
            {
                text_color = snail::Color{200, 0, 0};
            }
            else if (gspdorg < gspd)
            {
                text_color = snail::Color{0, 120, 0};
            }
            else
            {
                text_color = snail::Color{0, 0, 0};
            }
            mes(x + 8, y, std::to_string(gspd), text_color);
        }
        else
        {
            // PV/DV
            draw_region("core.attributes_bar", x + 14, y, 64);
            mes(x + 14, y, ""s + cdata.player().dv + "/"s + cdata.player().pv);
        }
    }
}



void _render_gold_or_platinum(
    int value,
    int x,
    int y,
    data::InstanceId icon_id,
    const std::string& unit)
{
    draw(icon_id, x, y);
    bmes(""s + value + " " + unit, x + 28, y + 2);
}



void render_gold()
{
    _render_gold_or_platinum(
        cdata.player().gold,
        windoww - 240,
        inf_ver - 16,
        "core.gold_coin",
        "gp");
}



void render_platinum()
{
    _render_gold_or_platinum(
        cdata.player().platinum,
        windoww - 120,
        inf_ver - 16,
        "core.platinum_coin",
        "pp");
}



void render_character_level()
{
    const auto lvl = cdata.player().level;
    const auto exp =
        cdata.player().required_experience - cdata.player().experience;

    draw("core.character_level_icon", 4, inf_ver - 16);
    bmes("Lv"s + lvl + "/"s + exp, 32, inf_ver - 14);
}



void render_date_label()
{
    draw("core.clock", 0, inf_clocky);
    draw("core.date_label_frame", 78, inf_clocky + 8);
}



void render_buffs()
{
    const auto x = windoww - 40;
    auto y = inf_ver - 40;

    for (auto&& buff : cdata.player().buffs)
    {
        // Icon
        draw_indexed(
            "core.buff_icon", x, y, the_buff_db.ensure(buff.id).integer_id);
        // Turns
        mes(x + 3, y + 19, std::to_string(buff.turns));
        // Turns
        mes(x + 2, y + 18, std::to_string(buff.turns), {255, 255, 255});

        y -= 32;
    }
}



void render_analogue_clock()
{
    const auto& info = get_image_info("core.clock_hand");

    const auto dt = game_date_time();

    // Short hand
    draw_rotated(
        "core.clock_hand",
        inf_clockarrowx,
        inf_clockarrowy,
        dt.hour() * 30 + dt.minute() / 2);
    // Long hand
    draw_rotated(
        "core.clock_hand",
        inf_clockarrowx,
        inf_clockarrowy,
        info.width / 2,
        info.height,
        dt.minute() * 6);

    mes(inf_clockw - 3,
        inf_clocky + 17 + vfix,
        std::to_string(dt.year()) + "/" + std::to_string(dt.month()) + "/" +
            std::to_string(dt.day()));
    bmes(
        i18n::s.get_enum("core.ui.time", dt.hour() / 4) + " "s +
            i18n::s.get_data_text("core.weather", game()->weather, "name"),
        inf_clockw + 6,
        inf_clocky + 35);
}



void render_digital_clock()
{
    const auto dt = game_date_time();

    // 24 hour digital clock, 57 pixels wide
    font(16 - en * 2);
    bmes(
        i18n::s.get(
            "core.ui.digital_clock.time", dt.hour(), dt.minute(), dt.second()),
        8,
        8);

    // date, 64 pixel wide
    font(15 - en * 2);
    int datex = 8 + 57 + 18;
    bmes(
        i18n::s.get(
            "core.ui.digital_clock.date", dt.year(), dt.month(), dt.day()),
        datex,
        8);

    // time of day + weather
    bmes(
        i18n::s.get_enum("core.ui.time", dt.hour() / 4) + " "s +
            i18n::s.get_data_text("core.weather", game()->weather, "name"),
        datex + 64 + 12,
        8);
}



void render_skill_trackers()
{
    int y{};
    for (int i = 0; i < 10; ++i)
    {
        const auto skill = game()->tracked_skills.at(i) % 10000;
        if (skill == 0)
        {
            continue;
        }
        const auto chara = game()->tracked_skills.at(i) / 10000;
        if (chara != 0 && cdata[chara].state() != Character::State::alive)
        {
            game()->tracked_skills.at(i) = 0;
            continue;
        }
        bmes(
            strutil::take_by_width(the_skill_db.get_text(skill, "name"), 6),
            16,
            inf_clocky + 107 + y * 16);
        bmes(
            ""s +
                cdata[chara].skills().base_level(
                    *the_skill_db.get_id_from_integer(skill)) +
                "."s +
                std::to_string(
                    1000 +
                    cdata[chara].skills().experience(
                        *the_skill_db.get_id_from_integer(skill)) %
                        1000)
                    .substr(1),
            66,
            inf_clocky + 107 + y * 16);
        if (elona::g_config.allow_enhanced_skill())
        {
            elona::snail::Color col{255, 130, 130};

            if (cdata[chara].skills().potential(
                    *the_skill_db.get_id_from_integer(skill)) >
                elona::g_config.enhanced_skill_upperbound())
            {
                col = {130, 255, 130};
            }
            else if (
                cdata[chara].skills().potential(
                    *the_skill_db.get_id_from_integer(skill)) >
                elona::g_config.enhanced_skill_lowerbound())
            {
                col = {255, 255, 130};
            }

            bmes(
                ""s +
                    cdata[chara].skills().potential(
                        *the_skill_db.get_id_from_integer(skill)) +
                    "%"s,
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
        std::is_same_v<decltype(do_render(value)), bool>,
        "F1 signature: bool do_render(int value)");
    static_assert(
        std::is_same_v<decltype(get_text(value)), std::string>,
        "F2 signature: std::string get_text(int value)");
    static_assert(
        std::is_same_v<decltype(get_color(value)), snail::Color>,
        "F3 signature: snail::Color get_color(int value)");

    if (!do_render(value))
        return y;

    draw_region("core.status_ailment_bar", x, y, 50 + en * 30);
    const auto text_color = get_color(value);
    mes(x + 6, y + vfix + 1, get_text(value), text_color);

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
            int index = 0;
            if (nutrition >= 1)
                index = nutrition;
            if (nutrition >= 12)
                index = 12;

            return i18n::s.get_enum("core.status_ailment.name.hunger", index);
        },
        [](auto nutrition) {
            return (nutrition >= 10) ? snail::Color{0, 0, 0}
                : (nutrition >= 1)   ? snail::Color{200, 0, 0}
                                     : snail::Color{250, 0, 0};
        });

    y = render_one_status_ailment(
        cdata.player().sick,
        x,
        y,
        [](auto turn) { return turn != 0; },
        [](auto turn) {
            int index = 0;
            if (turn >= 30)
                index = 1;

            return i18n::s.get_enum("core.status_ailment.name.sick", index);
        },
        {80, 120, 0});

    y = render_one_status_ailment(
        cdata.player().poisoned,
        x,
        y,
        [](auto turn) { return turn != 0; },
        [](auto turn) {
            int index = 0;
            if (turn >= 30)
                index = 1;

            return i18n::s.get_enum("core.status_ailment.name.poison", index);
        },
        {0, 150, 0});

    y = render_one_status_ailment(
        cdata.player().sleep,
        x,
        y,
        [](auto turn) { return turn != 0; },
        [](auto turn) {
            int index = 0;
            if (turn >= 30)
                index = 1;

            return i18n::s.get_enum("core.status_ailment.name.sleep", index);
        },
        {0, 50, 50});

    y = render_one_status_ailment(
        cdata.player().blind,
        x,
        y,
        [](auto turn) { return turn != 0; },
        i18n::s.get("core.status_ailment.name.blind"),
        {100, 100, 0});

    y = render_one_status_ailment(
        cdata.player().paralyzed,
        x,
        y,
        [](auto turn) { return turn != 0; },
        i18n::s.get("core.status_ailment.name.paralyzed"),
        {0, 100, 100});

    y = render_one_status_ailment(
        cdata.player().choked,
        x,
        y,
        [](auto turn) { return turn != 0; },
        i18n::s.get("core.status_ailment.name.choked"),
        {0, 100, 100});

    y = render_one_status_ailment(
        cdata.player().confused,
        x,
        y,
        [](auto turn) { return turn != 0; },
        i18n::s.get("core.status_ailment.name.confused"),
        {100, 0, 100});

    y = render_one_status_ailment(
        cdata.player().fear,
        x,
        y,
        [](auto turn) { return turn != 0; },
        i18n::s.get("core.status_ailment.name.fear"),
        {100, 0, 100});

    y = render_one_status_ailment(
        cdata.player().dimmed,
        x,
        y,
        [](auto turn) { return turn != 0; },
        [](auto turn) {
            int index = 0;
            if (turn >= 30)
                index = 1;
            if (turn >= 60)
                index = 2;

            return i18n::s.get_enum("core.status_ailment.name.dimmed", index);
        },
        {0, 100, 100});

    y = render_one_status_ailment(
        cdata.player().furious,
        x,
        y,
        [](auto turn) { return turn != 0; },
        [](auto turn) {
            int index = 0;
            if (turn >= 30)
                index = 1;

            return i18n::s.get_enum("core.status_ailment.name.angry", index);
        },
        {150, 0, 0});

    y = render_one_status_ailment(
        cdata.player().bleeding,
        x,
        y,
        [](auto turn) { return turn != 0; },
        [](auto turn) {
            int index = 0;
            if (turn >= 10)
                index = 1;
            if (turn >= 20)
                index = 2;

            return i18n::s.get_enum("core.status_ailment.name.bleeding", index);
        },
        {150, 0, 0});

    y = render_one_status_ailment(
        cdata.player().insane,
        x,
        y,
        [](auto turn) { return turn != 0; },
        [](auto turn) {
            int index = 0;
            if (turn >= 25)
                index = 1;
            if (turn >= 50)
                index = 2;

            return i18n::s.get_enum("core.status_ailment.name.insane", index);
        },
        {150, 100, 0});

    y = render_one_status_ailment(
        cdata.player().drunk,
        x,
        y,
        [](auto turn) { return turn != 0; },
        i18n::s.get("core.status_ailment.name.drunk"),
        {100, 0, 100});

    y = render_one_status_ailment(
        cdata.player().wet,
        x,
        y,
        [](auto turn) { return turn != 0; },
        i18n::s.get("core.status_ailment.name.wet"),
        {0, 0, 160});

    y = render_one_status_ailment(
        cdata.player().gravity,
        x,
        y,
        [](auto turn) { return turn != 0; },
        i18n::s.get("core.status_ailment.name.gravity"),
        {0, 80, 80});

    y = render_one_status_ailment(
        cdata.player().sleepiness,
        x,
        y,
        [](auto hours) { return hours >= 15; },
        [](auto hours) {
            int index = 0;
            if (hours >= 30)
                index = 1;
            if (hours >= 50)
                index = 2;

            return i18n::s.get_enum("core.status_ailment.name.sleepy", index);
        },
        [](auto hours) {
            return (hours >= 50) ? snail::Color{255, 0, 0}
                : (hours >= 30)  ? snail::Color{100, 100, 0}
                                 : snail::Color{0, 0, 0};
        });

    y = render_one_status_ailment(
        cdata.player().sp,
        x,
        y,
        [](auto sp) { return sp < 50; },
        [](auto sp) {
            int index = 0;
            if (sp < 25)
                index = 1;
            if (sp < 0)
                index = 2;

            return i18n::s.get_enum("core.status_ailment.name.tired", index);
        },
        [](auto sp) {
            return (sp < 0) ? snail::Color{120, 120, 0}
                : (sp < 25) ? snail::Color{80, 80, 0}
                            : snail::Color{60, 60, 0};
        });

    y = render_one_status_ailment(
        cdata.player().burden_state,
        x,
        y,
        [](auto state) { return state != 0; },
        [](auto state) {
            return i18n::s.get_enum("core.status_ailment.name.burden", state);
        },
        [](auto state) {
            return snail::Color{
                0,
                static_cast<uint8_t>(state * 40),
                static_cast<uint8_t>(state * 40)};
        });

    y = render_one_status_ailment(
        static_cast<int>(g_is_autodig_enabled),
        x,
        y,
        [](auto is_enabled) { return is_enabled == 1; },
        i18n::s.get("core.ui.autodig.mode"),
        {0, 0, 0});
}



void render_autoturn_animation()
{
    if (racount == 0 && g_config.animation_wait() != 0)
    {
        load_activity_animation();
    }

    if (firstautoturn ||
        (cdata.player().activity.id == "core.fish" && rowactre == 0 &&
         fishanime == 0))
    {
        ui_render_non_hud();
        render_hud();
    }

    if (cdata.player().activity.id == "core.fish")
    {
        if (rowactre == 0 && g_config.animation_wait() != 0)
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
    bmes("AUTO TURN"s, sx + 43, sy + vfix + 6, {235, 235, 235});
    gmode(2);
    draw_rotated(
        "core.hourglass", sx + 18, sy + 12, game_time().minute() / 4 * 24);

    if (cdata.player().activity.id == "core.dig_ground" ||
        cdata.player().activity.id == "core.dig_wall" ||
        cdata.player().activity.id == "core.search_material" ||
        (cdata.player().activity.id == "core.fish" && rowactre != 0))
    {
        if (g_config.animation_wait() != 0)
        {
            window2(sx, sy - 104, 148, 101, 0, 5);
            if (racount % 15 == 0)
            {
                for (int cnt = 0; cnt < 10; ++cnt)
                {
                    gmode(0);
                    if (cdata.player().activity.id == "core.dig_wall")
                    {
                        if (cnt == 2)
                        {
                            snd("core.dig1");
                        }
                        gcopy(
                            9, cnt / 2 % 5 * 144, 0, 144, 96, sx + 2, sy - 102);
                        await(g_config.animation_wait() * 2);
                    }
                    if (cdata.player().activity.id == "core.fish")
                    {
                        if (racount == 0)
                        {
                            if (cnt == 0)
                            {
                                snd("core.water");
                            }
                        }
                        gcopy(
                            9, cnt / 3 % 3 * 144, 0, 144, 96, sx + 2, sy - 102);
                        await(g_config.animation_wait() * 2.5);
                    }
                    if (cdata.player().activity.id == "core.search_material")
                    {
                        if (cnt == 4)
                        {
                            snd("core.bush1");
                        }
                        gcopy(
                            9, cnt / 2 % 3 * 144, 0, 144, 96, sx + 2, sy - 102);
                        await(g_config.animation_wait() * 2.75);
                    }
                    if (cdata.player().activity.id == "core.dig_ground")
                    {
                        if (cnt == 2)
                        {
                            snd("core.dig2");
                        }
                        gcopy(
                            9, cnt / 2 % 4 * 144, 0, 144, 96, sx + 2, sy - 102);
                        await(g_config.animation_wait() * 3);
                    }
                    redraw();
                }
            }
            else
            {
                gcopy(9, 0, 0, 144, 96, sx + 2, sy - 102);
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



void _update_slight_internal(int x, int y)
{
    slight(x + 1, y) += 1;
    slight(x - 1, y) += 8;
    slight(x, y - 1) += 2;
    slight(x, y + 1) += 4;
    slight(x + 1, y + 1) += 16;
    slight(x - 1, y - 1) += 32;
    slight(x + 1, y - 1) += 64;
    slight(x - 1, y + 1) += 128;
}

} // namespace



namespace elona
{

int msgy = 0;



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

    int x = x_base;
    int y = y_base;
    size_t pos = 0;
    snail::Color text_color = text_color_base;

    while (pos < text.size())
    {
        bool wait_to_break_line = false;
        const auto byte = strutil::byte_count(text[pos]);
        std::string one_char = text.substr(pos, byte);
        pos += byte;

        if (one_char == "。" || one_char == "、" || one_char == "」" ||
            one_char == "』" || one_char == "！" || one_char == "？" ||
            one_char == "…")
        {
            wait_to_break_line = true;
        }
        else if (one_char == "<")
        {
            const auto closing_tag_pos = text.find(">", pos);
            if (closing_tag_pos == std::string::npos)
            {
                ELONA_ERROR("Text: invalid notation: missing '>'");
                // Stop processing, return immediately.
                return {x_base, y + font_size + 4};
            }
            const auto tag = text.substr(pos, closing_tag_pos - pos);
            pos = closing_tag_pos + 1;
            if (tag == "emp1")
            {
                font(font_size - en * 2, snail::Font::Style::underline);
                text_color = {50, 50, 255};
            }
            else if (tag == "emp2")
            {
                font(font_size - en * 2, snail::Font::Style::bold);
                text_color = {40, 130, 40};
            }
            else if (tag == "title1")
            {
                font_size = 12;
                font(font_size - en * 2, snail::Font::Style::bold);
                text_color = {100, 50, 50};
            }
            else if (tag == "def")
            {
                font_size = 14;
                font(font_size - en * 2);
                text_color = text_color_base;
            }
            else if (tag == "p")
            {
                y += 24;
                x = x_base;
            }
            else if (tag == "br")
            {
                y += 16;
                x = x_base;
            }
            else if (tag == "b")
            {
                font(font_size - en * 2, snail::Font::Style::bold);
            }
            else if (tag == "green")
            {
                text_color = {20, 120, 20};
            }
            else if (tag == "red")
            {
                text_color = {120, 20, 20};
            }
            else if (tag == "col")
            {
                text_color = text_color_base;
            }
            continue;
        }
        else if (one_char == "^")
        {
            // Escape
            one_char = text.substr(pos, 1);
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
            mes(x + 1, y + 1, one_char, {180, 160, 140});
        }
        mes(x, y, one_char, text_color);
        x += font_size / 2 * (byte == 1 ? 1 : 2);
    }

    return {x_base, y + font_size + 4};
}



void initialize_ui_constants()
{
    inf_clockarrowx = 62;
    inf_clockarrowy = inf_clocky + 48;
    inf_barh = 16;
    inf_msgh = 72;
    inf_verh = inf_barh + inf_msgh;
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
    scposy = inf_screenh / 2 - 1;
    inf_hpx = (windoww - 84) / 2 - 100;
    inf_hpy = inf_ver - 12;
    inf_mpx = (windoww - 84) / 2 + 40;
    inf_mpy = inf_ver - 12;
    inf_msgx = inf_radarw;
    inf_msgspace = 15;
    int inf_maxmsglen_i = std::max((windoww - inf_msgx - 28) / 14 * 2 - 1, 0);
    inf_maxmsglen = static_cast<size_t>(inf_maxmsglen_i);
    inf_maxlog = (inf_msgy - 100) / inf_msgspace + 3;
    inf_very = windowh - inf_verh;
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
    if (txtadvscreenupdate == 1)
    {
        gcopy(4, 0, 0, windoww, windowh - inf_verh, 0, 0);
    }
    else
    {
        gcopy(4, 0, 0, windoww, 100, 0, 0);
    }
    gmode(2);
    for (int i = 0; i < 4; ++i)
    {
        font(13 - en * 2);
        if (i == 0)
        {
            sx = 265;
            sy = 8;
            draw("core.casino_title_decoration_left", sx - 30, 5);
            draw(
                "core.casino_title_decoration_right",
                sx + strlen_u(atxinfon(0)) * 13 / 2 + 14,
                5);
        }
        else
        {
            sx = 220;
            sy = 10 + i * 14;
        }
        mes(sx, sy, atxinfon(i), {250, 250, 250});
    }
    txtadvscreenupdate = 1;
}



void update_minimap()
{
    for (int y = 0; y < map_data.height; ++y)
    {
        for (int x = 0; x < map_data.width; ++x)
        {
            if (cell_data.at(x, y).chip_id_memory ==
                cell_data.at(x, y).chip_id_actual)
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
    if (game()->mount != 0 &&
        cdata[game()->mount].state() == Character::State::alive)
    {
        render_hp_bar(cdata[game()->mount], inf_hpx - 120, inf_hpy);
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
                if (!cdata.player().activity)
                {
                    gmode(2, 150);
                }
            }
        }
    }

    // Status ailments
    render_status_ailments();

    // Date label
    if (!g_config.digital_clock())
        render_date_label();

    // Buffs
    gmode(2, 180);
    render_buffs();
    gmode(2);

    // Clock
    g_config.digital_clock() ? render_digital_clock() : render_analogue_clock();

    // Skill trackers
    render_skill_trackers();

    // HP bars(pets)
    if (g_config.hp_bar_position() != "hide")
    {
        show_hp_bar(
            g_config.hp_bar_position() == "left" ? HPBarSide::left_side
                                                 : HPBarSide::right_side,
            inf_clocky);
    }

    // Damage popups
    show_damage_popups();

    // Lua console, if active
    lua::lua->get_console().draw();
}



void load_activity_animation()
{
    gsel(9);
    if (cdata.player().activity.id == "core.dig_wall")
    {
        picload(filesystem::dirs::graphic() / "anime1.bmp", 0, 0, true);
    }
    if (cdata.player().activity.id == "core.fish")
    {
        if (rowactre)
        {
            picload(filesystem::dirs::graphic() / "anime2.bmp", 0, 0, true);
        }
    }
    if (cdata.player().activity.id == "core.search_material")
    {
        picload(filesystem::dirs::graphic() / "anime3.bmp", 0, 0, true);
    }
    if (cdata.player().activity.id == "core.dig_ground")
    {
        picload(filesystem::dirs::graphic() / "anime4.bmp", 0, 0, true);
    }
    gsel(0);
}



void ui_draw_caption(const std::string& text)
{
    int msgx = 0;
    gmode(0);
    font(16 - en * 2);
    msgx = 20;
    msgy = 30;
    sx = 760;
    sx = strlen_u(text) * 8 + 45;
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

        draw_region("core.caption", cnt * 128 + msgx, msgy, 0, 0, ap, 3);
        draw_region("core.caption", cnt * 128 + msgx, msgy + 2, 0, 3, ap, 22);
        draw_region("core.caption", cnt * 128 + msgx, msgy + 22, 0, 0, ap, 2);
    }
    mes(msgx + 18, msgy + vfix + 4, text, {245, 245, 245});
    gmode(2);

    // __s__
    elona::s(0) = text;
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
    if (game()->current_map == mdata_t::MapId::pet_arena)
    {
        sx(0) = cdata[camera].position.x - scx;
        sx(1) = cdata[camera].position.x;
        sy(0) = cdata[camera].position.y - scy;
        sy(1) = cdata[camera].position.y;
    }
    if (g_config.always_center())
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
    slight.clear();
    ++msync;

    const Position center{
        cdata.player().position.x - (fov_max + 2) / 2,
        (fov_max + 2) / 2 - cdata.player().position.y};
    sy(2) = cdata.player().position.y - fov_max / 2;
    sy(3) = cdata.player().position.y + fov_max / 2;

    if (g_config.scroll())
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
    const auto _repwidth = repw(0);
    const auto _repx = repw(1);
    const auto _repheight = reph(0);
    const auto _repy = reph(1);
    const auto _fov_y_top = sy(2);
    const auto _fov_y_bottom = sy(3);

    // (sx, sy): absolute position.
    // (lx, ly): relative position based on the viewport.

    int ly = g_config.scroll() ? 1 : 2;
    for (int sy = _repy; sy < _repy + _repheight; ++sy, ++ly)
    {
        int lx = g_config.scroll() ? 1 : 2;
        if (sy < 0 || map_data.height <= sy)
        {
            for (int sx = _repx; sx < _repx + _repwidth; ++sx, ++lx)
            {
                _update_slight_internal(lx, ly);
            }
            continue;
        }
        for (int sx = _repx; sx < _repx + _repwidth; ++sx, ++lx)
        {
            if (sx < 0 || map_data.width <= sx)
            {
                _update_slight_internal(lx, ly);
                continue;
            }
            const auto all_cells_visible =
                game()->current_map == mdata_t::MapId::pet_arena;
            bool blinded = false;
            if (cdata.player().blind != 0)
            {
                if (sx != cdata.player().position.x ||
                    sy != cdata.player().position.y)
                {
                    blinded = true;
                }
            }
            if (all_cells_visible ||
                (!blinded && (_fov_y_top <= sy && sy <= _fov_y_bottom) &&
                 (sx >= fovlist[sy + center.y][0] + center.x &&
                  sx < fovlist[sy + center.y][1] + center.x) &&
                 fov_los(cdata.player().position, {sx, sy})))
            {
                mapsync(sx, sy) = msync;
                if (cell_data.at(sx, sy).chara_index_plus_one != 0)
                {
                    cdata[cell_data.at(sx, sy).chara_index_plus_one - 1]
                        .fov_flag = msync;
                }
                if (cell_data.at(sx, sy).chip_id_memory !=
                    cell_data.at(sx, sy).chip_id_actual)
                {
                    cell_data.at(sx, sy).chip_id_memory =
                        cell_data.at(sx, sy).chip_id_actual;
                    draw_minimap_pixel(sx, sy);
                }
                cell_data.at(sx, sy).item_info_memory =
                    cell_data.at(sx, sy).item_info_actual;
            }
            else
            {
                slight(lx, ly) += 1000;
                _update_slight_internal(lx, ly);
            }
        }
    }

    // TODO: are they really needed?
    sx = _repx + _repwidth - 1;
    sy = _repy + _repheight - 1;
}



void ui_render_non_hud()
{
    cell_draw();

    if (game()->current_map == mdata_t::MapId::pet_arena)
    {
        highlight_characters_in_pet_arena();
    }

    if (raderx != -1)
    {
        draw_region(
            "core.minimap_scratch",
            inf_radarx + raderx,
            inf_radary + radery,
            raderx,
            radery,
            6,
            6);
    }

    render_pc_position_in_minimap();

    if (debug_is_wizard())
    {
        render_stair_positions_in_minimap();
    }

    render_weather_effect();
}



void ui_scroll_screen()
{
    int scxbk2 = 0;
    int scybk2 = 0;
    if (std::abs(cdata.player().next_position.x - cdata.player().position.x) >
        1)
    {
        return;
    }
    if (std::abs(cdata.player().next_position.y - cdata.player().position.y) >
        1)
    {
        return;
    }
    scrollp = g_config.walk_wait();
    if (map_data.type == mdata_t::MapType::world_map)
    {
        scrollp = 6;
        keybd_wait = 1000;
        if (chip_data
                .for_cell(cdata.player().position.x, cdata.player().position.y)
                .kind == 4)
        {
            scrollp = 9;
        }
    }
    else if (keybd_wait > g_config.start_run_wait())
    {
        scrollp = 3;
        if (!g_config.scroll_when_run())
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
        sxfix = (cdata.player().next_position.x - cdata.player().position.x) *
            cnt * inf_tiles / scrollp * -1;
        syfix = (cdata.player().next_position.y - cdata.player().position.y) *
            cnt * inf_tiles / scrollp * -1;
        gsel(4);
        gmode(0);
        gcopy(0, 0, windowh - inf_verh, windoww, inf_tiles, 0, 0);
        gsel(0);
        gmode(2);
        ui_render_non_hud();
        gmode(0);
        gcopy(4, 0, 0, windoww, inf_tiles, 0, windowh - inf_verh);
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
    raderx = -1;
    radery = -1;
    raderw = 120 / map_data.width + 2;
    raderh = 84 / map_data.height + 2;

    gsel(3);
    for (int cnt = 0, cnt_end = (map_data.height); cnt < cnt_end; ++cnt)
    {
        sy = cnt;
        for (int cnt = 0, cnt_end = (map_data.width); cnt < cnt_end; ++cnt)
        {
            sx = cnt;
            sy(1) = 84 * sy / map_data.height;
            sx(1) = 120 * sx / map_data.width;
            const auto rect = draw_get_rect(chip_data.for_cell(sx, sy).key);
            gcopy(
                rect->buffer,
                rect->x + sx % 16,
                rect->y + sy % 12,
                raderw,
                raderh,
                688 + sx(1),
                528 + sy(1));
            if (chip_data.for_cell(sx, sy).effect & 4)
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
    gcopy(0, 0, 0, windoww, windowh, 0, 0);
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
        gmode(2, 10 + cnt * 5);
        await(20);
        gcopy(4, 0, 0, windoww, windowh, 0, 0);
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
        gmode(2, 10 + cnt * 5);
        await(20);
        gcopy(4, 0, 0, windoww, windowh, 0, 0);
        redraw();
    }
    gmode(2);
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
    randomize(cdata.player().turns / 3);
    gmode(2);
    if (fishanime == 4)
    {
        sx = (fishx - scx) * inf_tiles + inf_screenx;
        sy = (fishy - scy) * inf_tiles + inf_screeny;
        if (fishanime(1) > 15)
        {
            sx += (cdata.player().position.x - fishx) * 8 * (fishanime(1) - 15);
            sy +=
                (cdata.player().position.y - fishy) * 8 * (fishanime(1) - 15) +
                fishanime(1);
            gcopy(9, 144 + fishanime(1) / 2 % 2 * 48, 0, 48, 48, sx, sy - 44);
        }
        else
        {
            gcopy(
                9,
                144 + fishanime(1) % 2 * 48,
                0,
                48,
                clamp(fishanime(1) * 5, 1, 48),
                sx,
                sy - fishanime(1) * 3 + 14);
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
    gcopy(9, 116, 18, 14, 10 - ap, sx, sy - 5 + ap);
    sx = (cdata.player().position.x - scx) * inf_tiles + inf_screenx;
    sy = (cdata.player().position.y - scy) * inf_tiles + inf_screeny;
    gmode(2);
    if (fishdir == 0)
    {
        sx2 = inf_tiles / 2 + rnd(3) - 1;
        sy2 = inf_tiles / 2 + 12;
        gmode(2);
        gcopy_c(9, 48, 0, 48, 48, sx + sx2 + 1, sy + sy2 + 40);
    }
    if (fishdir == 1)
    {
        sx2 = inf_tiles / 2 - 26;
        sy2 = inf_tiles / 2 - 12 + rnd(3) - 3;
        gmode(2);
        gcopy_c(9, 48, 0, 48, 48, sx + sx2 - 16, sy + sy2 + 25);
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
        gmode(2);
        gcopy_c(9, 48, 0, 48, 48, sx + sx2 + 14, sy + sy2 + 25);
    }
    if (fishdir == 2)
    {
        gmode(2);
        grotate(9, 0, 24, 48, 24, sx + sx2, sy + sy2, 0.5 * fishdir * 3.14);
    }
    else
    {
        gmode(2);
        grotate(9, 0, 0, 48, 48, sx + sx2, sy + sy2, 0.5 * fishdir * 3.14);
    }
    randomize();
}



void ui_display_window(
    const std::string& title,
    const std::string& key_help,
    int x,
    int y,
    int width,
    int height,
    int x_offset,
    int y_offset)
{
    if (windowshadow == 1)
    {
        window(x + 4, y + 4, width, height - height % 8, true);
        windowshadow = 0;
    }
    window(x, y, width, height - height % 8);
    if (title != "")
    {
        window2(
            x + 34,
            y - 4,
            45 * width / 100 + clamp(int(strlen_u(title) * 8 - 120), 0, 200),
            32,
            1,
            1);
    }
    gmode(2);
    draw("core.tip_icon", x + 30 + x_offset, y + height - 47 - height % 8);
    line(
        x + 50 + x_offset,
        y + height - 48 - height % 8,
        x + width - 40,
        y + height - 48 - height % 8,
        {194, 170, 146});
    line(
        x + 50 + x_offset,
        y + height - 49 - height % 8,
        x + width - 40,
        y + height - 49 - height % 8,
        {234, 220, 188});
    font(15 + en - en * 2);
    bmes(
        title,
        x + 45 * width / 200 + 34 - strlen_u(title) * 4 +
            clamp(int(strlen_u(title) * 8 - 120), 0, 200) / 2,
        y + 4 + vfix,
        {255, 255, 255},
        {20, 10, 0});
    font(12 + sizefix - en * 2);
    mes(x + 58 + x_offset, y + height - 43 - height % 8, key_help);
    if (pagesize != 0)
    {
        const auto page_str = "Page."s + (page + 1) + "/"s + (pagemax + 1);
        font(12 + sizefix - en * 2, snail::Font::Style::bold);
        mes(x + width - strlen_u(page_str) * 7 - 40 - y_offset,
            y + height - 65 - height % 8,
            page_str);

        // __s__
        elona::s(0) = title;
        elona::s(1) = page_str;
    }
    else
    {
        // __s__
        elona::s(0) = title;
        elona::s(1) = key_help;
    }
    wx = x;
    wy = y;
    ww = width;
    wh = height;
}



void ui_display_window2(
    const std::string& tips,
    int x,
    int y,
    int width,
    int height)
{
    gmode(2);
    gcopy(7, 0, 0, width, height, x, y);
    font(12 + sizefix - en * 2, snail::Font::Style::bold);
    if (tips != ""s)
    {
        mes(x + width - strlen_u(tips) * 7 - 140,
            y + height - 24 - height % 8 + 0,
            tips);
    }
    if (pagesize != 0)
    {
        const auto page_str = "Page."s + (page + 1) + "/"s + (pagemax + 1);
        mes(x + width - strlen_u(page_str) * 7 - 40,
            y + height - 24 - height % 8 + 0,
            page_str);

        // __s__
        elona::s(0) = page_str;
    }
    else
    {
        // __s__
        elona::s(0) = tips;
    }
}



void display_note(const std::string& text, int x_offset)
{
    font(12 + sizefix - en * 2, snail::Font::Style::bold);
    mes(wx + ww - strlen_u(text) * 7 - 140 - x_offset,
        wy + wh - 65 - wh % 8,
        text);
}



void display_topic(const std::string& topic, int x, int y)
{
    font(12 + sizefix - en * 2, snail::Font::Style::bold);
    draw("core.topic_icon", x, y + 7);
    mes(x + 26, y + vfix + 8, topic);
    line(x + 22, y + 21, x + strlen_u(topic) * 7 + 36, y + 21);
}



void display_customkey(const std::string& key, int x, int y)
{
    gsel(3);
    draw_select_key(key, 624, 30);
    gsel(0);
    gcopy(3, 624, 30, 24, 18, x, y);
}



/**
 * Draws a selection key sprite that was previously buffered by @ref
 * draw_init_key_select_buffer.
 */
void display_key(int x, int y, int nth)
{
    gcopy(3, nth * 24 + 72, 30, 24, 18, x, y);
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
            gcopy(
                tile_window_id,
                tile_x,
                tile_y,
                tile_width,
                tile_height,
                windoww - (dx + 1) * tile_width,
                inf_ver - (dy + 1) * tile_height);
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
        picload(
            filesystem::dirs::graphic() / fs::u8path("g"s + (cnt + 1) + ".bmp"),
            cnt % 4 * 180,
            cnt / 4 * 300,
            false);
    }
    gsel(buffer_bk);
}



void clear_background_in_character_making()
{
    asset_load("core.void");
    draw("core.void", 0, 0, windoww, windowh);
    gsel(0);
    gmode(0);
    draw_region("core.void", 0, 0, 0, 0, windoww, 64);
    gmode(2);
}



void clear_background_in_continue()
{
    asset_load("core.void");
    draw("core.void", 0, 0, windoww, windowh);
    gsel(0);
    gmode(0);
    draw("core.void", 0, 0, windoww, windowh);
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
                draw_region("core.ie_scroll", x, y, 0, 0, 64, 48);
                draw_region("core.ie_scroll", x, y3, 0, 144, 64, 48);
            }
            continue;
        }
        if (i < width / 8 - 8)
        {
            draw_region(
                "core.ie_scroll",
                i * 8 + x,
                y,
                (i - 8) % 18 * 8 + 64,
                0,
                8,
                48);
            draw_region(
                "core.ie_scroll",
                i * 8 + x,
                y3,
                (i - 8) % 18 * 8 + 64,
                144,
                8,
                48);
            continue;
        }
        draw_region("core.ie_scroll", x3, y, 208, 0, 64, 48);
        draw_region("core.ie_scroll", x3, y3, 208, 144, 64, 48);
        break;
    }

    for (int i = 0; i < height / 8 - 14; ++i)
    {
        for (int j = 0; j < width / 8; ++j)
        {
            if (j == 0)
            {
                draw_region(
                    "core.ie_scroll",
                    x,
                    i * 8 + y + 48,
                    0,
                    i % 12 * 8 + 48,
                    64,
                    8);
                continue;
            }
            if (j < width / 8 - 15)
            {
                draw_region(
                    "core.ie_scroll",
                    j * 8 + x + 56,
                    i * 8 + y + 48,
                    j % 18 * 8 + 64,
                    i % 12 * 8 + 48,
                    8,
                    8);
                continue;
            }
            draw_region(
                "core.ie_scroll",
                x3,
                i * 8 + y + 48,
                208,
                i % 12 * 8 + 48,
                64,
                8);
            break;
        }
    }
}



void cs_listbk()
{
    if (cs_bk == -1)
        return;
    draw_region(
        "core.list_scratch", cs_posbk_x, cs_posbk_y, cs_posbk_w, cs_posbk_h);
}



void cs_list(
    bool is_selected,
    const std::string& text,
    int x,
    int y,
    int x_offset,
    const snail::Color& text_color)
{
    if (is_selected)
    {
        const auto width =
            clamp(int(strlen_u(text)) * 7 + 32 + x_offset, 10, 480);

        gsel(3);
        gcopy(0, x, y, width, 19, 264, 96);
        asset_copy_from(0, x, y, width, 19, "core.list_scratch");
        gsel(0);

        boxf(x, y, width, 19, {127, 191, 255, 63});
        draw("core.list_bullet", x + width - 20, y + 4);

        cs_posbk_x = x;
        cs_posbk_y = y;
        cs_posbk_w = width;
        cs_posbk_h = 19;
    }

    mes(x + 4 + x_offset, y + vfix + 3, text, text_color);
}



snail::Color cs_list_get_item_color(const ItemRef& item)
{
    if (item->is_no_drop)
    {
        return {120, 80, 0};
    }

    if (item->identify_state == IdentifyState::completely)
    {
        switch (item->curse_state)
        {
        case CurseState::doomed: return {100, 10, 100};
        case CurseState::cursed: return {150, 10, 10};
        case CurseState::none: return {10, 40, 120};
        case CurseState::blessed: return {10, 110, 30};
        default: assert(0); return {0, 0, 0};
        }
    }
    else
    {
        return {0, 0, 0};
    }
}



void showscroll(const std::string& hint, int x, int y, int width, int height)
{
    if (windowshadow != 0)
    {
        gmode(2, 80);
        draw_scroll(x + 3, y + 3, width, height);
        windowshadow = 0;
        gmode(2);
    }
    draw_scroll(x, y, width, height);

    if (hint.empty())
        return;

    draw("core.tip_icon", x + 40, y + height - 67 - height % 8);
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
    mes(x + 68, y + height - 63 - height % 8, hint);
    if (pagesize != 0)
    {
        const auto page_str = "Page."s + (page + 1) + "/"s + (pagemax + 1);
        font(12 + sizefix - en * 2, snail::Font::Style::bold);
        mes(x + width - strlen_u(page_str) * 7 - 40,
            y + height - 63 - height % 8,
            page_str);

        // __s__
        elona::s(0) = page_str;
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
        draw_region("core.window", x, y, 0, 0, 64, 48);
    }
    // Top right
    draw_region("core.window", x3, y, 208, 0, 56, 48);
    // Bottom left
    draw_region("core.window", x, y3, 0, 144, 64, 48);
    // Bottom right
    draw_region("core.window", x3, y3, 208, 144, 56, 48);

    for (int dx = 8; dx < width / 8 - 8; ++dx)
    {
        if (!shadow)
        {
            // Top middle
            draw_region(
                "core.window", dx * 8 + x, y, (dx - 8) % 18 * 8 + 36, 0, 8, 48);
        }
        // Bottom middle
        draw_region(
            "core.window", dx * 8 + x, y3, (dx - 8) % 18 * 8 + 54, 144, 8, 48);
    }

    for (int dy = 0; dy < height / 8 - 14; ++dy)
    {
        if (!shadow)
        {
            // Middle left
            draw_region(
                "core.window", x, dy * 8 + y + 48, 0, dy % 12 * 8 + 48, 64, 8);
            // Middle middle
            for (int dx = 1; dx < width / 8 - 15; ++dx)
            {
                draw_region(
                    "core.window",
                    dx * 8 + x + 56,
                    dy * 8 + y + 48,
                    dx % 18 * 8 + 64,
                    dy % 12 * 8 + 48,
                    8,
                    8);
            }
        }
        // Middle right
        draw_region(
            "core.window", x3, dy * 8 + y + 48, 208, dy % 12 * 8 + 48, 56, 8);
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
        draw_region(
            "core.window",
            x + 4,
            y + 4,
            24,
            24,
            228,
            144,
            width - 6,
            height - 8);
        break;
    case 1:
        draw_region(
            "core.window",
            x + 4,
            y + 4,
            24,
            24,
            228,
            144,
            width - 6,
            height - 8);
        boxf(x + 4, y + 4, width - 4, height - 4, {0, 0, 0, 195});
        break;
    case 2:
        draw_region(
            "core.window",
            x + 4,
            y + 4,
            24,
            24,
            228,
            144,
            width - 6,
            height - 8);
        boxf(x + 4, y + 4, width - 4, height - 4, {0, 0, 0, 210});
        break;
    case 3:
        draw_region(
            "core.window",
            x + 4,
            y + 4,
            24,
            24,
            228,
            144,
            width - 6,
            height - 8);
        boxf(x + 4, y + 4, width - 4, height - 4, {0, 0, 0, 10});
        break;
    case 4:
        draw_region(
            "core.window",
            x + 4,
            y + 4,
            24,
            24,
            228,
            144,
            width - 6,
            height - 8);
        boxf(x + 4, y + 4, width - 4, height - 4, {0, 0, 0, 195});
        break;
    case 5: break;
    case 6:
        gmode(2, 180);
        draw_region_centered(
            "core.window",
            x + width / 2,
            y + height / 2,
            24,
            24,
            228,
            144,
            width - 4,
            height - 4);
        break;
    default: break;
    }

    gmode(2);
    for (int cnt = 0, cnt_end = (width / 16 - 2); cnt < cnt_end; ++cnt)
    {
        draw_region(
            "core.window_frame",
            cnt * 16 + x + 16,
            y,
            frame_style * 48 + 16,
            0,
            16,
            16);
        draw_region(
            "core.window_frame",
            cnt * 16 + x + 16,
            y + height - 16,
            frame_style * 48 + 16,
            32,
            16,
            16);
    }

    const auto x2 = x + width / 16 * 16 - 16;
    const auto y2 = y + height / 16 * 16 - 16;

    draw_region(
        "core.window_frame", x2, y, frame_style * 48 + 16, 0, width % 16, 16);
    draw_region(
        "core.window_frame",
        x2,
        y + height - 16,
        frame_style * 48 + 16,
        32,
        width % 16,
        16);

    for (int i = 0; i < height / 16 - 2; ++i)
    {
        draw_region(
            "core.window_frame",
            x,
            i * 16 + y + 16,
            frame_style * 48,
            16,
            16,
            16);
        draw_region(
            "core.window_frame",
            x + width - 16,
            i * 16 + y + 16,
            frame_style * 48 + 32,
            16,
            16,
            16);
    }
    draw_region(
        "core.window_frame", x, y2, frame_style * 48, 16, 16, height % 16);
    draw_region(
        "core.window_frame",
        x + width - 16,
        y2,
        frame_style * 48 + 32,
        16,
        16,
        height % 16);
    draw_region("core.window_frame", x, y, frame_style * 48, 0, 16, 16);
    draw_region(
        "core.window_frame", x, y + height - 16, frame_style * 48, 32, 16, 16);
    draw_region(
        "core.window_frame",
        x + width - 16,
        y,
        frame_style * 48 + 32,
        0,
        16,
        16);
    draw_region(
        "core.window_frame",
        x + width - 16,
        y + height - 16,
        frame_style * 48 + 32,
        32,
        16,
        16);

    if (fill_style == 5)
    {
        draw_region(
            "core.window",
            x + 2,
            y + 2,
            24,
            24,
            228,
            144,
            width - 4,
            height - 5);
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
    if (!g_config.window_animation())
        return;
    if (duration == 0)
        return;

    gsel(temporary_window_id);
    gmode(0);
    gcopy(0, x, y, width, height, 0, 0);
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
            await(g_config.animation_wait() * 0.75);
        }
        gcopy(temporary_window_id, 0, 0, width, height, x, y);
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
    if (!g_config.window_animation())
        return;
    if (duration == 0)
        return;

    gsel(temporary_window_id);
    gmode(0);
    gcopy(0, x, y, width, height, 0, 0);
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
            await(g_config.animation_wait() * 0.75);
        }
        gcopy(temporary_window_id, 0, 0, width, height, x, y);
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
        draw("core.title_label_frame", x + 8 + i * 192, y);
    }
    gmode(2);
    draw("core.tip_icon", x, y + (mode != 1));
    font(12 + sizefix - en * 2);
    bmes(title, x + 32, y + 1 + vfix + jp, {250, 250, 250});
}



void auto_turn(int delay)
{
    autoturn = 1;
    if (g_config.auto_turn_speed() == "normal")
    {
        await(delay);
        ++scrturn;
    }
    if (g_config.auto_turn_speed() != "highest" || firstautoturn == 1)
    {
        screenupdate = -1;
        update_screen();
    }
    if (g_config.auto_turn_speed() == "normal")
    {
        redraw();
    }
}



void page_save()
{
    pagebk = page;
    csprev = cs;
    pagesaved = 1;
}



void page_load()
{
    if (pagesaved == 1)
    {
        page = pagebk;
        cs = csprev;
        pagesaved = 0;
    }
}



void savecycle()
{
    if (menucycle == 1)
    {
        menucycle = 0;
        if (invally == 0 && invcontainer == 0)
        {
            lastctrl = invctrl;
        }
    }
}



void sort_list_by_column1()
{
    if (listmax < 1)
    {
        return;
    }
    while (1)
    {
        p = 0;
        for (int cnt = 0, cnt_end = (listmax - 1); cnt < cnt_end; ++cnt)
        {
            if (list(1, cnt) > list(1, cnt + 1))
            {
                p(0) = list(0, cnt);
                p(1) = list(1, cnt);
                list(0, cnt) = list(0, cnt + 1);
                list(1, cnt) = list(1, cnt + 1);
                list(0, cnt + 1) = p;
                list(1, cnt + 1) = p(1);
                p = 1;
            }
        }
        if (p == 0)
        {
            break;
        }
    }
}



void sort_list_and_listn_by_column1()
{
    if (listmax < 1)
    {
        return;
    }
    while (1)
    {
        p = 0;
        for (int cnt = 0, cnt_end = (listmax - 1); cnt < cnt_end; ++cnt)
        {
            if (list(1, cnt) > list(1, cnt + 1))
            {
                p(0) = list(0, cnt);
                p(1) = list(1, cnt);
                list(0, cnt) = list(0, cnt + 1);
                list(1, cnt) = list(1, cnt + 1);
                list(0, cnt + 1) = p;
                list(1, cnt + 1) = p(1);
                s(0) = listn(0, cnt);
                s(1) = listn(1, cnt);
                listn(0, cnt) = listn(0, cnt + 1);
                listn(1, cnt) = listn(1, cnt + 1);
                listn(0, cnt + 1) = s;
                listn(1, cnt + 1) = s(1);
                p = 1;
            }
        }
        if (p == 0)
        {
            break;
        }
    }
}



int winposy(int y, int not_gaming)
{
    if (not_gaming == 0)
    {
        return ((inf_screenh + 1) * inf_tiles - y) / 2 + 8;
    }
    return (windowh - y) / 2;
}

} // namespace elona

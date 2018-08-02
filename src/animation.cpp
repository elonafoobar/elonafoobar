#include "animation.hpp"
#include "ability.hpp"
#include "audio.hpp"
#include "character.hpp"
#include "config.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "fov.hpp"
#include "item.hpp"
#include "item_db.hpp"
#include "map.hpp"
#include "random.hpp"
#include "ui.hpp"
#include "variables.hpp"

using namespace elona;



namespace
{



void set_color_modulator(int color_id, int window_id = -1)
{
    set_color_mod(
        255 - c_col(0, color_id),
        255 - c_col(1, color_id),
        255 - c_col(2, color_id),
        window_id);
}



void clear_color_modulator(int window_id = -1)
{
    set_color_mod(255, 255, 255, window_id);
}



position_t rendering_base_position(const position_t& position)
{
    return {
        (position.x - scx) * inf_tiles + inf_screenx,
        (position.y - scy) * inf_tiles + inf_screeny,
    };
}



position_t rendering_base_position(const character& cc)
{
    return rendering_base_position(cc.position);
}



position_t rendering_base_position_center(const position_t& position)
{
    return {
        (position.x - scx) * inf_tiles + inf_screenx + inf_tiles / 2,
        (position.y - scy) * inf_tiles + inf_screeny + inf_tiles / 2,
    };
}



position_t rendering_base_position_center(const character& cc)
{
    return rendering_base_position_center(cc.position);
}



std::vector<position_t> breath_pos()
{
    std::vector<position_t> ret(maxbreath);
    for (int i = 0; i < maxbreath; ++i)
    {
        ret[i] = {breathlist(0, i), breathlist(1, i)};
    }
    return ret;
}



template <typename F>
void do_animation(
    const position_t& center,
    const std::string& image_key,
    int duration,
    F draw)
{
    const auto& image_info = get_image_info(image_key);
    const auto size = std::max(image_info.width, image_info.height) * 2;

    gsel(4);
    gmode(0);
    pos(0, 0);
    gcopy(0, center.x - size / 2, center.y - size / 2, size, size);
    gmode(2);
    gsel(0);

    for (int t = 0; t < duration; ++t)
    {
        gmode(0);
        pos(center.x - size / 2, center.y - size / 2);
        gcopy(4, 0, 0, size, size);
        gmode(2);
        draw(image_key, center, t);
        redraw();
        await(config::instance().animewait);
    }
}



template <typename F, typename G>
void do_particle_animation(
    const position_t& center,
    const std::string& image_key,
    int duration,
    int max_particles,
    F create_particle,
    G draw)
{
    const auto& image_info = get_image_info(image_key);
    const auto size = std::max(image_info.width, image_info.height) * 2;

    gsel(4);
    gmode(0);
    pos(0, 0);
    gcopy(0, center.x - size / 2, center.y - size / 2, size, size);
    gmode(2);
    gsel(0);

    std::vector<position_t> particles(max_particles);
    for (int i = 0; i < max_particles; ++i)
    {
        particles[i] = create_particle(i);
    }

    for (int t = 0; t < duration; ++t)
    {
        gmode(0);
        pos(center.x - size / 2, center.y - size / 2);
        gcopy(4, 0, 0, size, size);
        gmode(2);
        for (int i = 0; i < max_particles; ++i)
        {
            draw(image_key, center, t, particles[i], i);
        }
        redraw();
        await(config::instance().animewait);
    }
}



bool is_in_screen(int x, int y)
{
    return x < windoww
        && y < inf_screenh * inf_tiles + inf_screeny - inf_tiles / 2;
}



} // namespace



namespace elona
{



void draw_rotated(
    const std::string& key,
    int x,
    int y,
    double scale,
    double angle)
{
    const auto& image_info = get_image_info(key);
    draw_rotated(
        key, x, y, image_info.width * scale, image_info.height * scale, angle);
}



int dist(const position_t& p, int x, int y)
{
    return dist(p.x, p.y, x, y);
}



int dist(int x, int y, const position_t& p)
{
    return dist(x, y, p.x, p.y);
}



int dist(const position_t& p1, const position_t& p2)
{
    return dist(p1.x, p1.y, p2.x, p2.y);
}



void abstract_animation::play()
{
    if (mode == 9)
        return;
    if (config::instance().animewait == 0)
        return;

    if (updates_screen())
        update_screen();

    gmode(2);
    do_play();
    gmode(2);
}



void failure_to_cast_animation::do_play()
{
    if (!is_in_fov(caster))
        return;

    snd_at(66, caster.position);

    do_animation(
        rendering_base_position_center(caster),
        "failure_to_cast_effect",
        12,
        [](const auto& key, const auto& center, auto t) {
            draw_rotated(
                key,
                center.x,
                center.y - inf_tiles / 6,
                double(t + 40) / inf_tiles,
                75 * t);
        });
}



void bright_aura_animation::do_play()
{
    constexpr auto max_particles = 15;

    if (is_in_fov(cc) == 0)
        return;

    // Load image and play sound.
    switch (type)
    {
    case type_t::debuff:
        prepare_item_image(8, 0);
        snd_at(38, cdata[cc].position);
        break;
    case type_t::offering: prepare_item_image(9, 0); break;
    case type_t::healing:
    case type_t::healing_rain:
        prepare_item_image(7, 0);
        snd_at(33, cdata[cc].position);
        break;
    }

    const auto base_pos = rendering_base_position(cc);

    // Store part of the previous screen.
    gsel(4);
    gmode(0);
    pos(0, 0);
    gcopy(
        0,
        base_pos.x - inf_tiles / 2,
        base_pos.y - inf_tiles / 2,
        inf_tiles * 2,
        inf_tiles * 2);
    gmode(2);
    gsel(0);

    // Initialize particles.
    std::vector<position_t> particles_pos(max_particles);
    std::vector<int> particles_n(max_particles);
    for (int i = 0; i < max_particles; ++i)
    {
        particles_pos[i] = {rnd(inf_tiles), rnd(inf_tiles)};
        particles_n[i] = -(rnd(4) + 1);
        if (type == type_t::debuff)
        {
            particles_n[i] *= -1;
        }
    }

    // Do animation.
    for (int i = 0; i < 10; ++i)
    {
        if (type == type_t::healing_rain)
        {
            await(config::instance().animewait / 4);
        }
        else
        {
            await(config::instance().animewait);
        }
        pos(base_pos.x - inf_tiles / 2, base_pos.y - inf_tiles / 2);
        gcopy(4, 0, 0, inf_tiles * 2, inf_tiles * 2);
        for (int j = 0; j < max_particles; ++j)
        {
            pos(base_pos.x + particles_pos[j].x,
                base_pos.y + particles_pos[j].y + i * 2 / particles_n[j]);
            grotate(
                1,
                0,
                960,
                48,
                48,
                inf_tiles - i * 4,
                inf_tiles - i * 4,
                i * 2 * particles_n[j]);
        }
        redraw();
    }
}



void breath_animation::do_play()
{
    // Play sound.
    snd_at(35, attacker.position);

    // Prepare image.
    gsel(7);
    picload(filesystem::dir::graphic() / u8"anime7.bmp");

    // Store entire of the previous screen.
    pos(0, 0);
    gsel(4);
    pos(0, 0);
    gmode(0);
    gcopy(0, 0, 0, windoww, windowh);
    gsel(0);

    for (int i = 0; i < 6; ++i)
    {
        // Restore entire of the previous screen.
        pos(0, 0);
        gmode(0);
        gcopy(4, 0, 0, windoww, windowh);

        bool did_draw{};
        for (const auto& position : breath_pos())
        {
            const auto dx = position.x;
            const auto dy = position.y;
            if (!fov_los(attacker.position.x, attacker.position.y, dx, dy))
            {
                continue;
            }
            const auto sx =
                (dx - scx) * inf_tiles + inf_screenx + inf_tiles / 2;
            const auto sy = (dy - scy) * inf_tiles + inf_screeny + 16;
            if (sx < windoww
                && sy < inf_screenh * inf_tiles + inf_screeny - inf_tiles / 2)
            {
                pos(sx, sy);
                gmode(2);
                set_color_modulator(eleinfo(element, 0), 7);
                grotate(
                    7,
                    i * 48,
                    0,
                    inf_tiles,
                    inf_tiles,
                    std::atan2(
                        tlocx - attacker.position.x,
                        attacker.position.y - tlocy));
                clear_color_modulator(7);
                did_draw = true;
            }
        }
        if (did_draw)
        {
            await(config::instance().animewait);
            redraw();
        }
    }

    // Play sound
    if (const auto se = eleinfo(element, 1))
    {
        snd_at(se, attacker.position, false, false);
    }
}



void ball_animation::do_play()
{
    int anicol{};
    int anisound{};
    if (type == type_t::ball)
    {
        anicol = eleinfo(ele, 0);
        anisound = eleinfo(ele, 1);
    }

    snd_at(34, {anix, aniy});

    // Load image.
    gsel(7);
    pos(0, 0);
    picload(filesystem::dir::graphic() / u8"anime5.bmp");

    // Store entire of the previous screen.
    gsel(4);
    gmode(0);
    pos(0, 0);
    gcopy(0, 0, 0, windoww, windowh);
    gmode(2);
    gsel(0);

    int anidx = (anix - scx) * inf_tiles + inf_screenx + 24;
    int anidy = (aniy - scy) * inf_tiles + inf_screeny + 24;

    for (int cnt = 0; cnt < 10; ++cnt)
    {
        int anip = cnt;
        int anip1 = 0;
        for (int cnt = 0, cnt_end = (aniref * 2 + 1); cnt < cnt_end; ++cnt)
        {
            anidy = aniy - aniref + cnt;
            sy = anidy - scy;
            if (sy < 0 || sy >= inf_screenh)
            {
                continue;
            }
            for (int cnt = 0, cnt_end = (aniref * 2 + 1); cnt < cnt_end; ++cnt)
            {
                anidx = anix - aniref + cnt;
                sx = anidx - scx;
                if (sx < 0 || sx >= inf_screenw)
                {
                    continue;
                }
                anip1 = dist(anix, aniy, anidx, anidy);
                if (anip1 > aniref)
                {
                    continue;
                }
                anip1 = 48 - (anip - 4) * (anip - 4) * 2;
                if (type == type_t::ball)
                {
                    if (fov_los(anix, aniy, anidx, anidy) == 0)
                    {
                        continue;
                    }
                }
                if (sx * inf_tiles + inf_screenx < windoww)
                {
                    if (sy * inf_tiles + inf_screeny
                        < inf_screenh * inf_tiles + inf_screeny - inf_tiles / 2)
                    {
                        pos(sx * inf_tiles + inf_screenx,
                            sy * inf_tiles + inf_screeny);
                        gmode(2);
                        set_color_modulator(anicol, 7);
                        gcopy(7, anip * 48, 96, 48, 48);
                        clear_color_modulator(7);
                    }
                }
            }
        }
        anidx = (anix - scx) * inf_tiles + inf_screenx + 24;
        anidy = (aniy - scy) * inf_tiles + inf_screeny + 24;
        if (anidx < windoww)
        {
            if (anidy < inf_screenh * inf_tiles + inf_screeny - inf_tiles / 2)
            {
                pos(anidx, anidy);
                gmode(4, 250 - cnt * cnt * 2);
                gcopy_c(7, cnt * 96, 0, 96, 96);
            }
        }
        redraw();
        gmode(0);
        pos(0, 0);
        gcopy(4, 0, 0, windoww, windowh);
        await(config::instance().animewait);
    }

    // Play sound.
    if (anisound)
    {
        snd_at(anisound, {anix, aniy}, false, false);
    }
}



void bolt_animation::do_play()
{
    elona_vector1<int> ax;
    elona_vector1<int> ay;

    snd_at(37, attacker.position);

    gsel(7);
    picload(filesystem::dir::graphic() / u8"anime6.bmp");

    pos(0, 0);
    gsel(4);
    gmode(0);
    pos(0, 0);
    gcopy(0, 0, 0, windoww, windowh);
    gsel(0);

    int x = attacker.position.x;
    int y = attacker.position.y;
    ap(20) = -1;
    for (int t = 0; t < 20; ++t)
    {
        if (ap(20) == -1)
        {
            int stat = route_info(x, y, t);
            if (stat == -1)
            {
                ap(t) = -1;
                continue;
            }
            else if (stat == 0)
            {
                ap(t) = -2;
                ap(20) = 4;
                continue;
            }
            if (dist(x, y, attacker.position)
                > the_ability_db[efid]->sdataref3 % 1000 + 1)
            {
                ap(t) = -2;
                ap(20) = 4;
                continue;
            }
            ax(t) = (x - scx) * inf_tiles + inf_screenx + inf_tiles / 2;
            ay(t) = (y - scy) * inf_tiles + inf_screeny + 8;
            ap(t) = 0;
        }
        else
        {
            --ap(20);
            if (ap(20) == 0)
            {
                break;
            }
        }

        pos(0, 0);
        gmode(0);
        gcopy(4, 0, 0, windoww, windowh);

        bool did_draw{};
        for (int u = 0; u < t + 1; ++u)
        {
            if (ap(u) == -1)
            {
                continue;
            }
            if (ap(u) == -2)
            {
                break;
            }
            if (ap(u) < 5 && is_in_screen(ax(u), ay(u)))
            {
                pos(ax(u), ay(u));
                gmode(2);
                set_color_modulator(eleinfo(element, 0), 7);
                grotate(
                    7,
                    ap(u) * 48,
                    0,
                    inf_tiles,
                    inf_tiles,
                    std::atan2(
                        tlocx - attacker.position.x,
                        attacker.position.y - tlocy));
                clear_color_modulator(7);
                did_draw = true;
            }
            ++ap(u);
        }
        if (did_draw)
        {
            await(config::instance().animewait * 1.75);
            redraw();
        }
    }

    if (const auto sound = eleinfo(element, 1))
    {
        snd_at(sound, attacker.position, false, false);
    }
}



void throwing_object_animation::do_play()
{
    if (!is_in_fov(target))
        return;

    prepare_item_image(aniref, aniref(1));
    int x = (target.position.x - scx) * inf_tiles;
    int y = (target.position.y - scy) * inf_tiles;
    int p = dist(target.position, anix, aniy) / 2 + 1;

    for (int t = 0; t < p; ++t)
    {
        x -= (target.position.x - anix) * inf_tiles / p;
        y -= (target.position.y - aniy) * inf_tiles / p;

        gsel(4);
        gmode(0);
        pos(0, 0);
        gcopy(0, x, y - inf_tiles / 2, inf_tiles, inf_tiles);
        gmode(2);
        gsel(0);
        gmode(2);

        if (is_in_screen(x + inf_tiles / 2, y))
        {
            pos(x + inf_tiles / 2, y);
            grotate(
                1,
                0,
                960,
                inf_tiles,
                inf_tiles,
                std::atan2(anix - target.position.x, target.position.y - aniy));
        }
        redraw();
        gmode(0);
        pos(x, y - inf_tiles / 2);
        gcopy(4, 0, 0, inf_tiles, inf_tiles);
        gmode(2);
        await(config::instance().animewait);
    }
}



void ranged_attack_animation::do_play()
{
    if (!is_in_fov(cc))
        return;

    int anicol{};
    int anisound{};
    const auto& chara_pos = cdata[cc].position;
    if (type == type_t::magic_arrow)
    {
        anicol = eleinfo(ele, 0);
        anisound = eleinfo(ele, 1);
    }
    prepare_item_image(6, anicol);
    if (type == type_t::distant_attack)
    {
        prepare_item_image(23, 0);
        snd_at(29, chara_pos);
    }
    if (type == type_t::bow)
    {
        prepare_item_image(1, anicol);
        snd_at(29, chara_pos);
    }
    if (type == type_t::crossbow)
    {
        prepare_item_image(2, anicol);
        snd_at(29, chara_pos);
    }
    if (type == type_t::firearm)
    {
        ap = the_item_db[inv[aniref].id]->subcategory;
        if (ap == 24021)
        {
            prepare_item_image(13, anicol);
            snd_at(42, chara_pos);
        }
        if (ap == 24020)
        {
            prepare_item_image(2, anicol);
            snd_at(30, chara_pos);
        }
    }
    if (type == type_t::throwing)
    {
        prepare_item_image(inv[aniref].image % 1000, inv[aniref].image / 1000);
        snd_at(31, chara_pos);
    }
    if (type == type_t::magic_arrow)
    {
        snd_at(36, chara_pos);
    }

    int ax = (cdata[cc].position.x - scx) * inf_tiles;
    int ay = (cdata[cc].position.y - scy) * inf_tiles + inf_screeny + 8;
    int ap = dist(cdata[cc].position, cdata[tc].position) / 2 + 1;

    for (int t = 0; t < ap; ++t)
    {
        ax -= (cdata[cc].position.x - cdata[tc].position.x) * inf_tiles / ap;
        ay -= (cdata[cc].position.y - cdata[tc].position.y) * inf_tiles / ap;

        gsel(4);
        gmode(0);
        pos(0, 0);
        gcopy(0, ax, ay - inf_tiles / 2, inf_tiles, inf_tiles);
        gmode(2);
        gsel(0);
        gmode(2);

        pos(ax + inf_tiles / 2, ay);
        grotate(
            1,
            0,
            960,
            inf_tiles,
            inf_tiles,
            std::atan2(
                cdata[tc].position.x - cdata[cc].position.x,
                cdata[cc].position.y - cdata[tc].position.y));

        redraw();
        gmode(0);
        pos(ax, ay - inf_tiles / 2);
        gcopy(4, 0, 0, inf_tiles, inf_tiles);
        gmode(2);
        await(config::instance().animewait);
    }

    if (anisound)
    {
        snd_at(anisound, cdata[tc].position, false, false);
    }
}



void swarm_animation::do_play()
{
    snd_at(2, target.position);

    do_animation(
        rendering_base_position_center(target),
        "swarm_effect",
        4,
        [](const auto& key, const auto& center, auto t) {
            draw_rotated(
                key,
                center.x,
                center.y,
                double(t * 8 + 18) / inf_tiles,
                30 * t - 45);
        });
}



void melee_attack_animation::do_play()
{
    int anix1;
    switch (attackskill)
    {
    case 100:
    case 101:
    case 102:
    case 104:
    case 107: ap = 1; break;
    case 108:
    case 109:
    case 110:
    case 111: ap = 2; break;
    default: ap = 0; break;
    }
    aniref = aniref / 4 + 1;
    if (aniref > 20)
    {
        aniref = 20;
    }
    if (cdata[tc].breaks_into_debris())
    {
        anix1 = 1104;
    }
    else
    {
        anix1 = 720;
    }
    if (ap == 0)
    {
        prepare_item_image(17, 0);
    }
    for (int cnt = 0, cnt_end = (aniref); cnt < cnt_end; ++cnt)
    {
        sx(cnt) = rnd(24) - 12;
        sy(cnt) = rnd(8);
    }
    int anidx = (cdata[tc].position.x - scx) * inf_tiles + inf_screenx;
    int anidy = (cdata[tc].position.y - scy) * inf_tiles + inf_screeny;
    gsel(4);
    gmode(0);
    pos(0, 0);
    gcopy(0, anidx - 24, anidy - 48, 96, 144);
    if (critical)
    {
        gsel(7);
        picload(filesystem::dir::graphic() / u8"anime28.bmp");
    }
    gmode(2);
    gsel(0);
    for (int cnt = 0, cnt_end = (4 + (critical != 0)); cnt < cnt_end; ++cnt)
    {
        gmode(2);
        int cnt2 = cnt * 2;
        gmode(2);
        if (critical)
        {
            pos(anidx - 24, anidy - 32);
            gcopy(7, cnt * 96, 0, 96, 96);
        }
        for (int cnt = 0, cnt_end = (aniref); cnt < cnt_end; ++cnt)
        {
            pos(anidx + 24 + sx(cnt)
                    + (sx(cnt) < 4) * ((1 + (cnt % 2 == 0)) * -1) * cnt2
                    + (sx(cnt) > -4) * (1 + (cnt % 2 == 0)) * cnt2,
                anidy + sy(cnt) + cnt2 * cnt2 / 3);
            grotate(1, anix1, 0, inf_tiles, inf_tiles, 6, 6, 0.4 * cnt);
        }
        if (ap == 0)
        {
            pos(anidx + sx + 24, anidy + sy + 10);
            grotate(
                1,
                0,
                960,
                inf_tiles,
                inf_tiles,
                cnt * 10 + aniref,
                cnt * 10 + aniref,
                0.5 * cnt - 0.8);
        }
        if (ap == 1)
        {
            pos(anidx, anidy);
            gcopy(3, 1008 + cnt * 48, 432, 48, 48);
        }
        if (ap == 2)
        {
            pos(anidx, anidy);
            gcopy(3, 816 + cnt * 48, 432, 48, 48);
        }
        redraw();
        gmode(0);
        pos(anidx - 24, anidy - 48);
        gcopy(4, 0, 0, 96, 144);
        gmode(2);
        await(config::instance().animewait);
    }
}



void geen_engineering_animation::do_play()
{
    snd_at(107, cdata[anic].position);
    if (!is_in_fov(anic))
        return;

    gsel(7);
    picload(filesystem::dir::graphic() / u8"anime13.bmp");

    gsel(4);
    gmode(0);
    pos(0, 0);
    gcopy(0, 0, 0, windoww, windowh);
    gsel(0);

    int anidx = (cdata[anic].position.x - scx) * inf_tiles + inf_screenx - 24;
    int anidy = (cdata[anic].position.y - scy) * inf_tiles + inf_screeny - 60;
    for (int t = 0; t < 10; ++t)
    {
        pos(0, 0);
        gmode(0);
        gcopy(4, 0, 0, windoww, windowh);
        gmode(2);

        for (int i = 0; i < anidy / 96 + 2; ++i)
        {
            pos(anidx, anidy - i * 96);
            gcopy(7, t / 2 * 96, (i == 0) * 96, 96, 96);
        }

        await(config::instance().animewait * 2.25);
        redraw();
    }
}



void miracle_animation::do_play()
{
    elona_vector1<int> ax;
    elona_vector1<int> ay;

    gsel(7);
    picload(filesystem::dir::graphic() / u8"anime12.bmp");
    gsel(4);
    pos(0, 0);
    gmode(0);
    gcopy(0, 0, 0, windoww, windowh);
    gsel(0);
    am = 0;
    for (int cnt = 0; cnt < ELONA_MAX_CHARACTERS; ++cnt)
    {
        if (cdata[cnt].state != 1)
        {
            continue;
        }
        if (animode == 0)
        {
            if (cnt == cc)
            {
                continue;
            }
        }
        if (animode >= 100)
        {
            if (cnt != animode - 100)
            {
                continue;
            }
        }
        ax(am) = (cdata[cnt].position.x - scx) * inf_tiles + inf_screenx - 24;
        if (am != 0)
        {
            ax(am) += 4 - rnd(8);
        }
        ay(am) = (cdata[cnt].position.y - scy) * inf_tiles + inf_screeny + 32;
        if (ay(am) < 0 || ay(am) > inf_screenh * inf_tiles + inf_screeny)
        {
            continue;
        }
        if (ax(am) < -20 || ax(am) > windoww + 20)
        {
            continue;
        }
        ap(am) = 20 + (am != 0) * rnd(5);
        ++am;
    }
    for (int cnt = 0;; ++cnt)
    {
        pos(0, 0);
        gmode(0);
        gcopy(4, 0, 0, windoww, windowh);
        int af = 0;
        for (int cnt = 0, cnt_end = (am); cnt < cnt_end; ++cnt)
        {
            if (ap(cnt) <= 0)
            {
                continue;
            }
            af = 1;
            int cnt2 = cnt;
            int anidy = ay(cnt) * clamp((20 - ap(cnt)), 0, 6) / 6 - 96;
            gmode(2);
            pos(ax(cnt), anidy);
            gcopy(
                7,
                clamp((8 - ap(cnt)), 0, 8) * 96 + 96 * (ap(cnt) < 15),
                0,
                96,
                96);
            if (ap(cnt) <= 14)
            {
                if (ap(cnt) >= 6)
                {
                    pos(ax(cnt), anidy + 16);
                    gcopy(7, (14 - ap(cnt)) / 2 * 96, 96, 96, 96);
                }
            }
            int anidx =
                clamp(anidy / 55 + 1, 0, 7 - clamp((11 - ap(cnt)) * 2, 0, 7));
            for (int cnt = 1, cnt_end = cnt + (anidx); cnt < cnt_end; ++cnt)
            {
                pos(ax(cnt2), anidy - cnt * 55);
                gcopy(7, 96 * (ap(cnt2) < 15), 0, 96, 55);
                if (cnt == anidx)
                {
                    pos(ax(cnt2), anidy - cnt * 55 - 40);
                    gcopy(7, 288, 0, 96, 40);
                }
            }
            if (ap(cnt) >= 20)
            {
                ap(cnt) -= rnd(2);
            }
            else
            {
                --ap(cnt);
            }
        }
        if (cnt % 2 == 0)
        {
            if (cnt < 30)
            {
                if (cnt / 3 < am)
                {
                    if (animode == 0)
                    {
                        snd(37);
                    }
                    if (animode >= 100)
                    {
                        snd(33);
                    }
                }
            }
        }
        if (af == 0)
        {
            break;
        }
        await(config::instance().animewait * 2.25);
        redraw();
    }
}



void meteor_animation::do_play()
{
    elona_vector1<int> ax;
    elona_vector1<int> ay;

    gsel(7);
    picload(filesystem::dir::graphic() / u8"anime17.bmp");
    gsel(4);
    pos(0, 0);
    gmode(0);
    gcopy(0, 0, 0, windoww, windowh);
    gsel(0);
    am = 0;
    for (int cnt = 0; cnt < 75; ++cnt)
    {
        ax(am) = 240 + rnd(windoww);
        ay(am) = -96;
        ap(am) = rnd(8);
        ++am;
    }
    for (int cnt = 0;; ++cnt)
    {
        if (cnt < 4)
        {
            pos(0, 0);
        }
        else
        {
            pos(5 - rnd(10), 5 - rnd(10));
        }
        gmode(0);
        gcopy(4, 0, 0, windoww, windowh);
        int af = 0;
        for (int cnt = 0, cnt_end = (am); cnt < cnt_end; ++cnt)
        {
            if (ap(cnt) >= 16)
            {
                continue;
            }
            af = 1;
            gmode(2);
            if (ap(cnt) < 9)
            {
                ax(cnt) -= 16 + cnt % (windoww / 30);
                ay(cnt) += 24 + cnt % (windowh / 10);
            }
            if (ap(cnt) >= 10)
            {
                pos(ax(cnt) - 48, ay(cnt));
                gcopy(7, (ap(cnt) - 10) * 192, 96, 192, 96);
            }
            if (ap(cnt) < 16)
            {
                pos(ax(cnt), ay(cnt));
                gcopy(7, clamp((ap(cnt) - 8), 0, 8) * 96, 0, 96, 96);
            }
            ++ap(cnt);
        }
        if (cnt % 2 == 0)
        {
            if (cnt < 8)
            {
                if (cnt / 3 < am)
                {
                    snd(108);
                }
            }
        }
        if (af == 0)
        {
            break;
        }
        await(config::instance().animewait * 3);
        redraw();
    }
    await(config::instance().animewait);
    pos(0, 0);
    gmode(0);
    gcopy(4, 0, 0, windoww, windowh);
    gmode(2);
    redraw();
}



void ragnarok_animation::do_play()
{
    constexpr auto TODO = 100;

    elona_vector1<int> ax;
    elona_vector1<int> ay;

    // Load image.
    gsel(7);
    picload(filesystem::dir::graphic() / u8"anime16.bmp");

    // Store entire of the previous screen.
    gsel(4);
    pos(0, 0);
    gmode(0);
    gcopy(0, 0, 0, windoww, windowh);
    gsel(0);

    for (int i = 0; i < TODO; ++i)
    {
        ax(i) = rnd(windoww);
        ay(i) = rnd(inf_screenh * inf_tiles) - 96 - 24;
        ap(i) = -rnd(3);
    }

    for (int t = 0;; ++t)
    {
        gmode(0);
        pos(5 - rnd(10), 5 - rnd(10));
        gcopy(4, 0, 0, windoww, windowh);
        gmode(2);

        bool did_draw{};
        for (int i = 0; i < TODO; ++i)
        {
            if (ap(i) >= 10)
            {
                continue;
            }
            did_draw = true;
            if (0 <= ap(i) && ap(i) < 10)
            {
                pos(ax(i), ay(i));
                gcopy(7, ap(i) * 96, 96, 96, 96);
                pos(ax(i), ay(i) - 96);
                gcopy(7, ap(i) * 96, 0, 96, 96);
            }
            if (ap(i) < 0)
            {
                ap(i) += rnd(2);
            }
            else
            {
                ++ap(i);
            }
        }

        if (t % 2 == 0 && t < 8 && t / 3 < TODO)
        {
            snd(108);
        }
        if (!did_draw)
        {
            break;
        }
        await(config::instance().animewait * 3);
        redraw();
    }

    await(config::instance().animewait);
    pos(0, 0);
    gmode(0);
    gcopy(4, 0, 0, windoww, windowh);
    gmode(2);
    redraw();
}



void breaking_animation::do_play()
{
    do_particle_animation(
        rendering_base_position_center(position),
        "breaking_effect",
        5,
        4,
        [](auto) {
            return position_t{rnd(24) - 12, rnd(8)};
        },
        [](const auto& key,
           const auto& center,
           auto t,
           const auto& particle,
           auto i) {
            const auto x = center.x + particle.x
                + (particle.x < 4) * -(1 + (i % 2 == 0)) * t
                + (particle.x > -4) * (1 + (i % 2 == 0)) * t;
            const auto y = center.y - inf_tiles / 4 + particle.y + t * t / 3;
            draw_rotated(key, x, y, 0.5, 23 * i);
        });
}



} // namespace elona

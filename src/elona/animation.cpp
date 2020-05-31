#include "animation.hpp"

#include "ability.hpp"
#include "audio.hpp"
#include "character.hpp"
#include "config.hpp"
#include "data/types/type_asset.hpp"
#include "data/types/type_item.hpp"
#include "draw.hpp"
#include "element.hpp"
#include "elona.hpp"
#include "fov.hpp"
#include "item.hpp"
#include "map.hpp"
#include "random.hpp"
#include "ui.hpp"
#include "variables.hpp"

using namespace elona;



namespace
{

int am;
double r_at_m133;
int dx_at_m133 = 0;
elona_vector1<int> dy_at_m133;



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



Position rendering_base_position(const Position& position)
{
    return {
        (position.x - scx) * inf_tiles + inf_screenx,
        (position.y - scy) * inf_tiles + inf_screeny,
    };
}



Position rendering_base_position_center(const Position& position)
{
    return {
        (position.x - scx) * inf_tiles + inf_screenx + inf_tiles / 2,
        (position.y - scy) * inf_tiles + inf_screeny + inf_tiles / 2,
    };
}



std::vector<Position> breath_pos()
{
    std::vector<Position> ret(maxbreath);
    for (int i = 0; i < maxbreath; ++i)
    {
        ret[i] = {breathlist(0, i), breathlist(1, i)};
    }
    return ret;
}



template <typename F>
void do_animation(
    const Position& center,
    data::InstanceId image_id,
    int duration,
    F draw)
{
    const auto& image_info = get_image_info(image_id);
    const auto size = std::max(image_info.width, image_info.height) * 2;

    gsel(4);
    gmode(0);
    gcopy(0, center.x - size / 2, center.y - size / 2, size, size, 0, 0);
    gmode(2);
    gsel(0);

    for (int t = 0; t < duration; ++t)
    {
        gmode(0);
        gcopy(4, 0, 0, size, size, center.x - size / 2, center.y - size / 2);
        gmode(2);
        draw(image_id, center, t);
        redraw();
        await(g_config.animation_wait());
    }
}



template <typename F, typename G>
void do_particle_animation(
    const Position& center,
    data::InstanceId image_id,
    int duration,
    int max_particles,
    F create_particle,
    G draw)
{
    const auto& image_info = get_image_info(image_id);
    const auto size = std::max(image_info.width, image_info.height) * 2;

    gsel(4);
    gmode(0);
    gcopy(0, center.x - size / 2, center.y - size / 2, size, size, 0, 0);
    gmode(2);
    gsel(0);

    std::vector<Position> particles(max_particles);
    for (int i = 0; i < max_particles; ++i)
    {
        particles[i] = create_particle(i);
    }

    for (int t = 0; t < duration; ++t)
    {
        gmode(0);
        gcopy(4, 0, 0, size, size, center.x - size / 2, center.y - size / 2);
        gmode(2);
        for (int i = 0; i < max_particles; ++i)
        {
            draw(image_id, center, t, particles[i], i);
        }
        redraw();
        await(g_config.animation_wait());
    }
}



bool is_in_screen(int x, int y)
{
    return x < windoww &&
        y < inf_screenh * inf_tiles + inf_screeny - inf_tiles / 2;
}



} // namespace



namespace elona
{



void draw_rotated(data::InstanceId id, int x, int y, double scale, double angle)
{
    const auto& image_info = get_image_info(id);
    draw_rotated(
        id, x, y, image_info.width * scale, image_info.height * scale, angle);
}



int dist(const Position& p, int x, int y)
{
    return dist(p.x, p.y, x, y);
}



int dist(int x, int y, const Position& p)
{
    return dist(x, y, p.x, p.y);
}



int dist(const Position& p1, const Position& p2)
{
    return dist(p1.x, p1.y, p2.x, p2.y);
}



void AbstractAnimation::play()
{
    if (mode == 9)
        return;
    if (g_config.animation_wait() == 0)
        return;

    if (updates_screen())
        update_screen();

    gmode(2);
    do_play();
    gmode(2);
}



void FailureToCastAnimation::do_play()
{
    if (!is_in_fov(caster_pos))
        return;

    snd_at("core.fizzle", caster_pos);

    do_animation(
        rendering_base_position_center(caster_pos),
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



void BrightAuraAnimation::do_play()
{
    constexpr auto max_particles = 15;

    if (!is_in_fov(target_pos))
        return;

    // Load image and play sound.
    switch (type)
    {
    case Type::debuff:
        prepare_item_image(8, 0);
        snd_at("core.curse1", target_pos);
        break;
    case Type::offering: prepare_item_image(9, 0); break;
    case Type::healing:
    case Type::healing_rain:
        prepare_item_image(7, 0);
        snd_at("core.heal1", target_pos);
        break;
    }

    const auto base_pos = rendering_base_position(target_pos);

    // Store part of the previous screen.
    gsel(4);
    gmode(0);
    gcopy(
        0,
        base_pos.x - inf_tiles / 2,
        base_pos.y - inf_tiles / 2,
        inf_tiles * 2,
        inf_tiles * 2,
        0,
        0);
    gmode(2);
    gsel(0);

    // Initialize particles.
    std::vector<Position> particles_pos(max_particles);
    std::vector<int> particles_n(max_particles);
    for (int i = 0; i < max_particles; ++i)
    {
        particles_pos[i] = {rnd(inf_tiles), rnd(inf_tiles)};
        particles_n[i] = -(rnd(4) + 1);
        if (type == Type::debuff)
        {
            particles_n[i] *= -1;
        }
    }

    // Do animation.
    for (int i = 0; i < 10; ++i)
    {
        if (type == Type::healing_rain)
        {
            await(g_config.animation_wait() / 4);
        }
        else
        {
            await(g_config.animation_wait());
        }
        gcopy(
            4,
            0,
            0,
            inf_tiles * 2,
            inf_tiles * 2,
            base_pos.x - inf_tiles / 2,
            base_pos.y - inf_tiles / 2);
        for (int j = 0; j < max_particles; ++j)
        {
            grotate(
                1,
                0,
                960,
                48,
                48,
                base_pos.x + particles_pos[j].x,
                base_pos.y + particles_pos[j].y + i * 2 / particles_n[j],
                inf_tiles - i * 4,
                inf_tiles - i * 4,
                i * 2 * particles_n[j]);
        }
        redraw();
    }
}



void BreathAnimation::do_play()
{
    // Play sound.
    snd_at("core.breath1", attacker_pos);

    // Prepare image.
    gsel(7);
    picload(filesystem::dirs::graphic() / u8"anime7.bmp", 0, 0, true);

    // Store entire of the previous screen.
    gsel(4);
    gmode(0);
    gcopy(0, 0, 0, windoww, windowh, 0, 0);
    gsel(0);

    for (int i = 0; i < 6; ++i)
    {
        // Restore entire of the previous screen.
        gmode(0);
        gcopy(4, 0, 0, windoww, windowh, 0, 0);

        bool did_draw{};
        for (const auto& position : breath_pos())
        {
            const auto dx = position.x;
            const auto dy = position.y;
            if (!fov_los(attacker_pos, {dx, dy}))
            {
                continue;
            }
            const auto sx =
                (dx - scx) * inf_tiles + inf_screenx + inf_tiles / 2;
            const auto sy = (dy - scy) * inf_tiles + inf_screeny + 16;
            if (sx < windoww &&
                sy < inf_screenh * inf_tiles + inf_screeny - inf_tiles / 2)
            {
                gmode(2);
                set_color_modulator(element_color_id(element), 7);
                grotate(
                    7,
                    i * 48,
                    0,
                    inf_tiles,
                    inf_tiles,
                    sx,
                    sy,
                    std::atan2(
                        target_pos.x - attacker_pos.x,
                        attacker_pos.y - target_pos.y));
                clear_color_modulator(7);
                did_draw = true;
            }
        }
        if (did_draw)
        {
            await(g_config.animation_wait());
            redraw();
        }
    }

    // Play sound
    if (const auto se = sound_id_for_element(element))
    {
        snd_at(*se, attacker_pos, false, false);
    }
}



void BallAnimation::do_play()
{
    int anicol{};
    optional<data::InstanceId> anisound{};
    if (type == Type::ball)
    {
        anicol = element_color_id(element);
        anisound = sound_id_for_element(element);
    }

    snd_at("core.ball1", position);

    // Load image.
    gsel(7);
    picload(filesystem::dirs::graphic() / u8"anime5.bmp", 0, 0, true);

    // Store entire of the previous screen.
    gsel(4);
    gmode(0);
    gcopy(0, 0, 0, windoww, windowh, 0, 0);
    gmode(2);
    gsel(0);

    int anidx = (position.x - scx) * inf_tiles + inf_screenx + 24;
    int anidy = (position.y - scy) * inf_tiles + inf_screeny + 24;

    for (int cnt = 0; cnt < 10; ++cnt)
    {
        int anip = cnt;
        int anip1 = 0;
        for (int cnt = 0, cnt_end = (range * 2 + 1); cnt < cnt_end; ++cnt)
        {
            anidy = position.y - range + cnt;
            sy = anidy - scy;
            if (sy < 0 || sy >= inf_screenh)
            {
                continue;
            }
            for (int cnt = 0, cnt_end = (range * 2 + 1); cnt < cnt_end; ++cnt)
            {
                anidx = position.x - range + cnt;
                sx = anidx - scx;
                if (sx < 0 || sx >= inf_screenw)
                {
                    continue;
                }
                anip1 = dist(position.x, position.y, anidx, anidy);
                if (anip1 > range)
                {
                    continue;
                }
                anip1 = 48 - (anip - 4) * (anip - 4) * 2;
                if (type == Type::ball)
                {
                    if (!fov_los(position, {anidx, anidy}))
                    {
                        continue;
                    }
                }
                if (sx * inf_tiles + inf_screenx < windoww)
                {
                    if (sy * inf_tiles + inf_screeny <
                        inf_screenh * inf_tiles + inf_screeny - inf_tiles / 2)
                    {
                        gmode(2);
                        set_color_modulator(anicol, 7);
                        gcopy(
                            7,
                            anip * 48,
                            96,
                            48,
                            48,
                            sx * inf_tiles + inf_screenx,
                            sy * inf_tiles + inf_screeny);
                        clear_color_modulator(7);
                    }
                }
            }
        }
        anidx = (position.x - scx) * inf_tiles + inf_screenx + 24;
        anidy = (position.y - scy) * inf_tiles + inf_screeny + 24;
        if (anidx < windoww)
        {
            if (anidy < inf_screenh * inf_tiles + inf_screeny - inf_tiles / 2)
            {
                gmode(2, 250 - cnt * cnt * 2);
                gcopy_c(7, cnt * 96, 0, 96, 96, anidx, anidy);
            }
        }
        redraw();
        gmode(0);
        gcopy(4, 0, 0, windoww, windowh, 0, 0);
        await(g_config.animation_wait());
    }

    // Play sound.
    if (anisound)
    {
        snd_at(*anisound, position, false, false);
    }
}



void BoltAnimation::do_play()
{
    elona_vector1<int> ax;
    elona_vector1<int> ay;

    snd_at("core.bolt1", attacker_pos);

    gsel(7);
    picload(filesystem::dirs::graphic() / u8"anime6.bmp", 0, 0, true);

    gsel(4);
    gmode(0);
    gcopy(0, 0, 0, windoww, windowh, 0, 0);
    gsel(0);

    int x = attacker_pos.x;
    int y = attacker_pos.y;
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
            if (dist(x, y, attacker_pos) > distance)
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

        gmode(0);
        gcopy(4, 0, 0, windoww, windowh, 0, 0);

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
                gmode(2);
                set_color_modulator(element_color_id(element), 7);
                grotate(
                    7,
                    ap(u) * 48,
                    0,
                    inf_tiles,
                    inf_tiles,
                    ax(u),
                    ay(u),
                    std::atan2(
                        target_pos.x - attacker_pos.x,
                        attacker_pos.y - target_pos.y));
                clear_color_modulator(7);
                did_draw = true;
            }
            ++ap(u);
        }
        if (did_draw)
        {
            await(g_config.animation_wait() * 1.75);
            redraw();
        }
    }

    if (const auto sound = sound_id_for_element(element))
    {
        snd_at(*sound, attacker_pos, false, false);
    }
}



void ThrowingObjectAnimation::do_play()
{
    if (!is_in_fov(target_pos))
        return;

    prepare_item_image(item_chip, item_color);
    int x = (target_pos.x - scx) * inf_tiles;
    int y = (target_pos.y - scy) * inf_tiles;
    int p = dist(target_pos, attacker_pos.x, attacker_pos.y) / 2 + 1;

    for (int t = 0; t < p; ++t)
    {
        x -= (target_pos.x - attacker_pos.x) * inf_tiles / p;
        y -= (target_pos.y - attacker_pos.y) * inf_tiles / p;

        gsel(4);
        gmode(0);
        gcopy(0, x, y - inf_tiles / 2, inf_tiles, inf_tiles, 0, 0);
        gmode(2);
        gsel(0);
        gmode(2);

        if (is_in_screen(x + inf_tiles / 2, y))
        {
            grotate(
                1,
                0,
                960,
                inf_tiles,
                inf_tiles,
                x + inf_tiles / 2,
                y,
                std::atan2(
                    attacker_pos.x - target_pos.x,
                    target_pos.y - attacker_pos.y));
        }
        redraw();
        gmode(0);
        gcopy(4, 0, 0, inf_tiles, inf_tiles, x, y - inf_tiles / 2);
        gmode(2);
        await(g_config.animation_wait());
    }
}



void RangedAttackAnimation::do_play()
{
    if (!is_in_fov(attacker_pos))
        return;

    int anicol{};
    optional<data::InstanceId> anisound = none;
    if (type == Type::magic_arrow)
    {
        anicol = element_color_id(ele);
        anisound = sound_id_for_element(ele);
    }
    prepare_item_image(6, anicol);
    if (type == Type::distant_attack)
    {
        prepare_item_image(23, 0);
        snd_at("core.bow1", attacker_pos);
    }
    if (type == Type::bow)
    {
        prepare_item_image(1, anicol);
        snd_at("core.bow1", attacker_pos);
    }
    if (type == Type::crossbow)
    {
        prepare_item_image(1, anicol);
        snd_at("core.bow1", attacker_pos);
    }
    if (type == Type::firearm)
    {
        if (fired_item_subcategory == 24021)
        {
            prepare_item_image(13, anicol);
            snd_at("core.laser1", attacker_pos);
        }
        if (fired_item_subcategory == 24020)
        {
            prepare_item_image(2, anicol);
            snd_at("core.gun1", attacker_pos);
        }
    }
    if (type == Type::throwing)
    {
        prepare_item_image(fired_item_image, fired_item_color);
        snd_at("core.throw1", attacker_pos);
    }
    if (type == Type::magic_arrow)
    {
        snd_at("core.arrow1", attacker_pos);
    }

    int ax = (attacker_pos.x - scx) * inf_tiles;
    int ay = (attacker_pos.y - scy) * inf_tiles + inf_screeny + 8;
    int ap = dist(attacker_pos, target_pos) / 2 + 1;

    for (int t = 0; t < ap; ++t)
    {
        ax -= (attacker_pos.x - target_pos.x) * inf_tiles / ap;
        ay -= (attacker_pos.y - target_pos.y) * inf_tiles / ap;

        gsel(4);
        gmode(0);
        gcopy(0, ax, ay - inf_tiles / 2, inf_tiles, inf_tiles, 0, 0);
        gmode(2);
        gsel(0);
        gmode(2);

        grotate(
            1,
            0,
            960,
            inf_tiles,
            inf_tiles,
            ax + inf_tiles / 2,
            ay,
            std::atan2(
                target_pos.x - attacker_pos.x, attacker_pos.y - target_pos.y));

        redraw();
        gmode(0);
        gcopy(4, 0, 0, inf_tiles, inf_tiles, ax, ay - inf_tiles / 2);
        gmode(2);
        await(g_config.animation_wait());
    }

    if (anisound)
    {
        snd_at(*anisound, target_pos, false, false);
    }
}



void SwarmAnimation::do_play()
{
    snd_at("core.atk1", target_pos);

    do_animation(
        rendering_base_position_center(target_pos),
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



void MeleeAttackAnimation::do_play()
{
    int anix1;
    switch (attack_skill)
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
    damage_percent = damage_percent / 4 + 1;
    if (damage_percent > 20)
    {
        damage_percent = 20;
    }
    if (debris)
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
    for (int cnt = 0, cnt_end = (damage_percent); cnt < cnt_end; ++cnt)
    {
        sx(cnt) = rnd(24) - 12;
        sy(cnt) = rnd(8);
    }
    int anidx = (position.x - scx) * inf_tiles + inf_screenx;
    int anidy = (position.y - scy) * inf_tiles + inf_screeny;
    gsel(4);
    gmode(0);
    gcopy(0, anidx - 24, anidy - 48, 96, 144, 0, 0);
    if (is_critical)
    {
        gsel(7);
        picload(filesystem::dirs::graphic() / u8"anime28.bmp", 0, 0, true);
    }
    gmode(2);
    gsel(0);
    for (int cnt = 0, cnt_end = (4 + (is_critical != 0)); cnt < cnt_end; ++cnt)
    {
        gmode(2);
        int cnt2 = cnt * 2;
        gmode(2);
        if (is_critical)
        {
            gcopy(7, cnt * 96, 0, 96, 96, anidx - 24, anidy - 32);
        }
        for (int cnt = 0, cnt_end = (damage_percent); cnt < cnt_end; ++cnt)
        {
            grotate(
                1,
                anix1,
                0,
                inf_tiles,
                inf_tiles,
                anidx + 24 + sx(cnt) +
                    (sx(cnt) < 4) * ((1 + (cnt % 2 == 0)) * -1) * cnt2 +
                    (sx(cnt) > -4) * (1 + (cnt % 2 == 0)) * cnt2,
                anidy + sy(cnt) + cnt2 * cnt2 / 3,
                6,
                6,
                0.4 * cnt);
        }
        if (ap == 0)
        {
            grotate(
                1,
                0,
                960,
                inf_tiles,
                inf_tiles,
                anidx + sx + 24,
                anidy + sy + 10,
                cnt * 10 + damage_percent,
                cnt * 10 + damage_percent,
                0.5 * cnt - 0.8);
        }
        if (ap == 1)
        {
            draw_indexed("anim_slash", anidx, anidy, cnt);
        }
        if (ap == 2)
        {
            draw_indexed("anim_bash", anidx, anidy, cnt);
        }
        redraw();
        gmode(0);
        gcopy(4, 0, 0, 96, 144, anidx - 24, anidy - 48);
        gmode(2);
        await(g_config.animation_wait());
    }
}



void GeneEngineeringAnimation::do_play()
{
    snd_at("core.atk_elec", position);
    if (!is_in_fov(position))
        return;

    gsel(7);
    picload(filesystem::dirs::graphic() / u8"anime13.bmp", 0, 0, true);

    gsel(4);
    gmode(0);
    gcopy(0, 0, 0, windoww, windowh, 0, 0);
    gsel(0);

    int anidx = (position.x - scx) * inf_tiles + inf_screenx - 24;
    int anidy = (position.y - scy) * inf_tiles + inf_screeny - 60;
    for (int t = 0; t < 10; ++t)
    {
        gmode(0);
        gcopy(4, 0, 0, windoww, windowh, 0, 0);
        gmode(2);

        for (int i = 0; i < anidy / 96 + 2; ++i)
        {
            gcopy(7, t / 2 * 96, (i == 0) * 96, 96, 96, anidx, anidy - i * 96);
        }

        await(g_config.animation_wait() * 2.25);
        redraw();
    }
}



void MiracleAnimation::do_play()
{
    elona_vector1<int> ax;
    elona_vector1<int> ay;

    gsel(7);
    picload(filesystem::dirs::graphic() / u8"anime12.bmp", 0, 0, true);
    gsel(4);
    gmode(0);
    gcopy(0, 0, 0, windoww, windowh, 0, 0);
    gsel(0);
    am = 0;
    for (auto&& cnt : cdata.all())
    {
        if (cnt.state() != Character::State::alive)
        {
            continue;
        }
        if (_mode == Mode::target_one)
        {
            if (cnt.index != _chara.index)
            {
                continue;
            }
        }
        else
        {
            if (cnt.index == _chara.index)
            {
                continue;
            }
        }
        ax(am) = (cnt.position.x - scx) * inf_tiles + inf_screenx - 24;
        if (am != 0)
        {
            ax(am) += 4 - rnd(8);
        }
        ay(am) = (cnt.position.y - scy) * inf_tiles + inf_screeny + 32;
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
        gmode(0);
        gcopy(4, 0, 0, windoww, windowh, 0, 0);
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
            gcopy(
                7,
                clamp((8 - ap(cnt)), 0, 8) * 96 + 96 * (ap(cnt) < 15),
                0,
                96,
                96,
                ax(cnt),
                anidy);
            if (ap(cnt) <= 14)
            {
                if (ap(cnt) >= 6)
                {
                    gcopy(
                        7,
                        (14 - ap(cnt)) / 2 * 96,
                        96,
                        96,
                        96,
                        ax(cnt),
                        anidy + 16);
                }
            }
            int anidx =
                clamp(anidy / 55 + 1, 0, 7 - clamp((11 - ap(cnt)) * 2, 0, 7));
            for (int cnt = 1, cnt_end = cnt + (anidx); cnt < cnt_end; ++cnt)
            {
                gcopy(
                    7,
                    96 * (ap(cnt2) < 15),
                    0,
                    96,
                    55,
                    ax(cnt2),
                    anidy - cnt * 55);
                if (cnt == anidx)
                {
                    gcopy(7, 288, 0, 96, 40, ax(cnt2), anidy - cnt * 55 - 40);
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
                    if (_mode == Mode::target_one)
                    {
                        snd("core.heal1");
                    }
                    else
                    {
                        snd("core.bolt1");
                    }
                }
            }
        }
        if (af == 0)
        {
            break;
        }
        await(g_config.animation_wait() * 2.25);
        redraw();
    }
}



void MeteorAnimation::do_play()
{
    elona_vector1<int> ax;
    elona_vector1<int> ay;

    gsel(7);
    picload(filesystem::dirs::graphic() / u8"anime17.bmp", 0, 0, true);
    gsel(4);
    gmode(0);
    gcopy(0, 0, 0, windoww, windowh, 0, 0);
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
        int x = 0, y = 0;
        if (cnt >= 4)
        {
            x = 5 - rnd(10);
            y = 5 - rnd(10);
        }
        gmode(0);
        gcopy(4, 0, 0, windoww, windowh, x, y);
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
                gcopy(
                    7,
                    (ap(cnt) - 10) * 192,
                    96,
                    192,
                    96,
                    ax(cnt) - 48,
                    ay(cnt));
            }
            if (ap(cnt) < 16)
            {
                gcopy(
                    7,
                    clamp((ap(cnt) - 8), 0, 8) * 96,
                    0,
                    96,
                    96,
                    ax(cnt),
                    ay(cnt));
            }
            ++ap(cnt);
        }
        if (cnt % 2 == 0)
        {
            if (cnt < 8)
            {
                if (cnt / 3 < am)
                {
                    snd("core.atk_fire");
                }
            }
        }
        if (af == 0)
        {
            break;
        }
        await(g_config.animation_wait() * 3);
        redraw();
    }
    await(g_config.animation_wait());
    gmode(0);
    gcopy(4, 0, 0, windoww, windowh, 0, 0);
    gmode(2);
    redraw();
}



void RagnarokAnimation::do_play()
{
    constexpr auto TODO = 100;

    elona_vector1<int> ax;
    elona_vector1<int> ay;

    // Load image.
    gsel(7);
    picload(filesystem::dirs::graphic() / u8"anime16.bmp", 0, 0, true);

    // Store entire of the previous screen.
    gsel(4);
    gmode(0);
    gcopy(0, 0, 0, windoww, windowh, 0, 0);
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
        gcopy(4, 0, 0, windoww, windowh, 5 - rnd(10), 5 - rnd(10));
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
                gcopy(7, ap(i) * 96, 96, 96, 96, ax(i), ay(i));
                gcopy(7, ap(i) * 96, 0, 96, 96, ax(i), ay(i) - 96);
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
            snd("core.atk_fire");
        }
        if (!did_draw)
        {
            break;
        }
        await(g_config.animation_wait() * 3);
        redraw();
    }

    await(g_config.animation_wait());
    gmode(0);
    gcopy(4, 0, 0, windoww, windowh, 0, 0);
    gmode(2);
    redraw();
}



void BreakingAnimation::do_play()
{
    if (!is_in_fov(position))
    {
        return;
    }

    do_particle_animation(
        rendering_base_position_center(position),
        "breaking_effect",
        5,
        4,
        [](auto) {
            return Position{rnd(24) - 12, rnd(8)};
        },
        [](const auto& key,
           const auto& center,
           auto t,
           const auto& particle,
           auto i) {
            const auto x = center.x + particle.x +
                (particle.x < 4) * -(1 + (i % 2 == 0)) * t +
                (particle.x > -4) * (1 + (i % 2 == 0)) * t;
            const auto y = center.y - inf_tiles / 4 + particle.y + t * t / 3;
            draw_rotated(key, x, y, 0.5, 23 * i);
        });
}



void animeload(int animation_type, const Character& chara)
{
    elona_vector1<int> i_at_m133;
    if (mode != 0)
    {
        return;
    }
    if (is_in_fov(chara) == 0)
    {
        return;
    }
    if (g_config.animation_wait() == 0)
    {
        return;
    }
    screenupdate = -1;
    update_screen();
    dx_at_m133 = (chara.position.x - scx) * inf_tiles + inf_screenx;
    dy_at_m133 = (chara.position.y - scy) * inf_tiles + inf_screeny;
    gsel(7);
    picload(
        filesystem::dirs::graphic() / (u8"anime"s + animation_type + u8".bmp"),
        0,
        0,
        true);
    gsel(4);
    gmode(0);
    gcopy(0, dx_at_m133 - 24, dy_at_m133 - 40, 96, 96, 0, 0);
    gsel(0);
    gmode(2);
    i_at_m133(0) = 5;
    i_at_m133(1) = g_config.animation_wait() * 3.5;
    r_at_m133 = 0;
    if (animation_type == 8)
    {
        snd("core.offer1");
    }
    if (animation_type == 10)
    {
        i_at_m133(0) = 8;
        i_at_m133(1) = g_config.animation_wait() * 2.5;
        r_at_m133 = 0.2;
        snd("core.enc2");
    }
    if (animation_type == 11)
    {
        i_at_m133(0) = 5;
        i_at_m133(1) = g_config.animation_wait() * 3.5;
        r_at_m133 = 0;
        snd("core.enc");
    }
    if (animation_type == 14)
    {
        i_at_m133(0) = 6;
        i_at_m133(1) = g_config.animation_wait() * 3.5;
    }
    for (int cnt = 0, cnt_end = (i_at_m133); cnt < cnt_end; ++cnt)
    {
        gmode(2);
        grotate(
            7,
            cnt * 96,
            0,
            96,
            96,
            dx_at_m133 + 24,
            dy_at_m133 + 8,
            r_at_m133 * cnt);
        gmode(0);
        redraw();
        gcopy(4, 0, 0, 96, 96, dx_at_m133 - 24, dy_at_m133 - 40);
        await(i_at_m133(1));
    }
    gmode(2);
}



void animeblood(const Character& chara, int animation_type, int element)
{
    if (is_in_fov(chara) == 0)
        return;
    if (g_config.animation_wait() == 0)
        return;

    int cnt2_at_m133 = 0;

    screenupdate = -1;
    update_screen();

    if (animation_type == 0)
    {
        prepare_item_image(16, 0);
    }
    if (animation_type == 1)
    {
        prepare_item_image(18, 0);
    }
    dx_at_m133 = (chara.position.x - scx) * inf_tiles + inf_screenx;
    dy_at_m133(0) = (chara.position.y - scy) * inf_tiles + inf_screeny;
    dy_at_m133(1) = 0;
    gsel(4);
    gmode(0);
    gcopy(0, dx_at_m133 - 48, dy_at_m133 - 56, 144, 160, 0, 0);

    int ele2_at_m133 = 1;
    gsel(7);
    switch (element)
    {
    case 52:
        picload(filesystem::dirs::graphic() / u8"anime18.bmp", 0, 0, true);
        dy_at_m133(1) = -16;
        break;
    case 51:
        picload(filesystem::dirs::graphic() / u8"anime19.bmp", 0, 0, true);
        dy_at_m133(1) = -16;
        break;
    case 50:
        picload(filesystem::dirs::graphic() / u8"anime20.bmp", 0, 0, true);
        dy_at_m133(1) = -20;
        break;
    case 56:
        picload(filesystem::dirs::graphic() / u8"anime22.bmp", 0, 0, true);
        dy_at_m133(1) = -24;
        break;
    case 53:
        picload(filesystem::dirs::graphic() / u8"anime21.bmp", 0, 0, true);
        dy_at_m133(1) = -16;
        break;
    case 54:
        picload(filesystem::dirs::graphic() / u8"anime23.bmp", 0, 0, true);
        dy_at_m133(1) = -16;
        break;
    case 57:
        picload(filesystem::dirs::graphic() / u8"anime24.bmp", 0, 0, true);
        dy_at_m133(1) = -16;
        break;
    case 59:
        picload(filesystem::dirs::graphic() / u8"anime25.bmp", 0, 0, true);
        dy_at_m133(1) = -16;
        break;
    case 58:
        picload(filesystem::dirs::graphic() / u8"anime26.bmp", 0, 0, true);
        dy_at_m133(1) = -16;
        break;
    case 55:
    case 63:
        picload(filesystem::dirs::graphic() / u8"anime27.bmp", 0, 0, true);
        dy_at_m133(1) = -16;
        break;
    default: ele2_at_m133 = 0; break;
    }

    gmode(2);
    gsel(0);

    elona_vector1<int> x_at_m133;
    elona_vector1<int> y_at_m133;
    for (int cnt = 0; cnt < 20; ++cnt)
    {
        x_at_m133(cnt) = rnd(48) - 24;
        y_at_m133(cnt) = rnd(16);
    }

    for (int cnt = 0; cnt < 6; ++cnt)
    {
        cnt2_at_m133 = cnt * 2;
        gmode(2);
        if (ele2_at_m133)
        {
            gcopy(
                7,
                cnt * 96,
                0,
                96,
                96,
                dx_at_m133 - 24,
                dy_at_m133 - 32 + dy_at_m133(1));
        }
        for (int cnt = 0; cnt < 20; ++cnt)
        {
            grotate(
                1,
                0,
                960,
                inf_tiles,
                inf_tiles,
                dx_at_m133 + 24 + x_at_m133(cnt) +
                    (x_at_m133(cnt) < 3) * ((1 + (cnt % 2 == 0)) * -1) *
                        cnt2_at_m133 +
                    (x_at_m133(cnt) > -4) * (1 + (cnt % 2 == 0)) * cnt2_at_m133,
                dy_at_m133 + y_at_m133(cnt) + cnt2_at_m133 * cnt2_at_m133 / 2 -
                    12 + cnt,
                24 - cnt2_at_m133 * 2,
                24 - cnt2_at_m133 * 2,
                0.2 * cnt);
        }
        gmode(0);
        redraw();
        gcopy(4, 0, 0, 144, 160, dx_at_m133 - 48, dy_at_m133 - 56);
        await(g_config.animation_wait() * (ele2_at_m133 == 0 ? 1.75 : 2.75));
    }

    gmode(2);
}

} // namespace elona

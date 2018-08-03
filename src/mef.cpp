#include "mef.hpp"
#include "ability.hpp"
#include "audio.hpp"
#include "character.hpp"
#include "dmgheal.hpp"
#include "draw.hpp"
#include "event.hpp"
#include "fov.hpp"
#include "item.hpp"
#include "map.hpp"
#include "random.hpp"
#include "variables.hpp"

namespace elona
{

int i_at_m79 = 0;

void initialize_mef()
{
    DIM3(mefsubref, 6, 6);
    mefsubref(0, 1) = 144;
    mefsubref(1, 1) = 624;
    mefsubref(0, 2) = 272;
    mefsubref(1, 2) = 624;
    mefsubref(2, 2) = 1;
    mefsubref(0, 3) = 304;
    mefsubref(1, 3) = 624;
    mefsubref(2, 3) = 1;
    mefsubref(0, 4) = 368;
    mefsubref(1, 4) = 624;
    mefsubref(0, 5) = 464;
    mefsubref(1, 5) = 624;
}

void mef_delete(int prm_581)
{
    if (mef(0, prm_581) == 7)
    {
        event_add(21, mef(2, prm_581), mef(3, prm_581));
    }
    map(mef(2, prm_581), mef(3, prm_581), 8) = 0;
    mef(0, prm_581) = 0;
    i_at_m79 = 199;
    for (int cnt = 0, cnt_end = (MEF_MAX - prm_581); cnt < cnt_end; ++cnt)
    {
        if (mef(0, i_at_m79) != 0)
        {
            for (int cnt = 0; cnt < 9; ++cnt)
            {
                mef(cnt, prm_581) = mef(cnt, i_at_m79);
            }
            map(mef(2, i_at_m79), mef(3, i_at_m79), 8) = prm_581 + 1;
            mef(0, i_at_m79) = 0;
            break;
        }
        --i_at_m79;
    }
    return;
}



void mef_add(
    int pos_x,
    int pos_y,
    int prm_584,
    int prm_585,
    int prm_586,
    int effect_power,
    int chara,
    int prm_589,
    int prm_590,
    int prm_591)
{
    int p_at_m79 = 0;
    p_at_m79 = map(pos_x, pos_y, 0);
    if (prm_584 == 5)
    {
        if (chipm(0, p_at_m79) == 3)
        {
            return;
        }
    }
    if (map(pos_x, pos_y, 8) != 0)
    {
        i_at_m79 = map(pos_x, pos_y, 8) - 1;
    }
    else
    {
        i_at_m79 = -1;
        for (int cnt = 0; cnt < MEF_MAX; ++cnt)
        {
            if (mef(0, cnt) == 0)
            {
                i_at_m79 = cnt;
                break;
            }
        }
        if (i_at_m79 == -1)
        {
            i_at_m79 = rnd(MEF_MAX);
            map(mef(2, i_at_m79), mef(3, i_at_m79), 8) = 0;
        }
    }
    mef(0, i_at_m79) = prm_584;
    mef(1, i_at_m79) = prm_585 + prm_591 * 10000;
    mef(2, i_at_m79) = pos_x;
    mef(3, i_at_m79) = pos_y;
    mef(4, i_at_m79) = prm_586;
    mef(5, i_at_m79) = effect_power;
    mef(6, i_at_m79) = chara;
    mef(7, i_at_m79) = prm_589;
    mef(8, i_at_m79) = prm_590;
    map(pos_x, pos_y, 8) = i_at_m79 + 1;
    return;
}

void mef_update()
{
    int sound = 0;
    for (int cnt = 0; cnt < MEF_MAX; ++cnt)
    {
        if (mef(0, cnt) == 0)
        {
            break;
        }
        if (mef(0, cnt) == 5)
        {
            if (mdata_map_indoors_flag == 2)
            {
                if (mdata_map_type != mdata_t::map_type_t::world_map)
                {
                    if (gdata_weather == 3 || gdata_weather == 4)
                    {
                        mef_delete(cnt);
                        continue;
                    }
                    dx = mef(2, cnt);
                    dy = mef(3, cnt);
                    i = mef(6, cnt);
                    p = 0;
                    if (rnd(35) == 0)
                    {
                        p = 3;
                        if (dist(
                                dx,
                                dy,
                                cdata[0].position.x,
                                cdata[0].position.y)
                            < 6)
                        {
                            sound = 6;
                        }
                    }
                    for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
                    {
                        x = rnd(2) + dx - rnd(2);
                        y = rnd(2) + dy - rnd(2);
                        if (x < 0 || y < 0 || x >= mdata_map_width
                            || y >= mdata_map_height)
                        {
                            f = 0;
                            continue;
                        }
                        if (chipm(7, map(x, y, 0)) & 4)
                        {
                            map(x, y, 0) = 37;
                            cnt = 0 - 1;
                            continue;
                        }
                        mef_add(x, y, 5, 24, rnd(15) + 20, 50, i);
                        mapitem_fire(x, y);
                    }
                }
            }
        }
        if (mef(0, cnt) == 7)
        {
            txtef(3);
            txt(lang(u8" *"s, u8"*"s) + mef(4, cnt) + lang(u8"* "s, u8"*"s));
        }
        if (mef(4, cnt) != -1)
        {
            --mef(4, cnt);
            if (mef(4, cnt) == 0)
            {
                mef_delete(cnt);
            }
        }
    }
    if (sound != 0)
    {
        snd(sound);
    }
}

void mef_proc(int tc)
{
    int ef = map(cdata[tc].position.x, cdata[tc].position.y, 8) - 1;
    if (mef(0, ef) == 0)
    {
        return;
    }
    if (mef(0, ef) == 3)
    {
        if (cdata[tc].is_floating() == 0 || cdata[tc].gravity > 0)
        {
            if (sdata(63, tc) / 50 < 7)
            {
                if (is_in_fov(tc))
                {
                    snd(46);
                    txt(lang(
                        name(tc) + u8"は酸に焼かれた。"s,
                        name(tc) + u8" melt"s + _s(tc) + u8"."s));
                }
                if (mef(6, ef) == 0)
                {
                    if (tc != 0)
                    {
                        hostileaction(0, tc);
                    }
                }
                int stat = dmghp(
                    tc, rnd(mef(5, ef) / 25 + 5) + 1, -15, 63, mef(5, ef));
                if (stat == 0)
                {
                    check_kill(mef(6, ef), tc);
                }
            }
        }
    }
    if (mef(0, ef) == 5)
    {
        if (is_in_fov(tc))
        {
            snd(6);
            txt(lang(
                name(tc) + u8"は燃えた。"s,
                name(tc) + u8" "s + is(tc) + u8" burnt."s));
        }
        if (mef(6, ef) == 0)
        {
            if (tc != 0)
            {
                hostileaction(0, tc);
            }
        }
        int stat = dmghp(tc, rnd(mef(5, ef) / 15 + 5) + 1, -9, 50, mef(5, ef));
        if (stat == 0)
        {
            check_kill(mef(6, ef), tc);
        }
    }
    if (mef(0, ef) == 6)
    {
        if (cdata[tc].is_floating() == 0 || cdata[tc].gravity > 0)
        {
            if (is_in_fov(tc))
            {
                snd(46);
                txt(lang(
                    name(tc) + u8"は地面の液体を浴びた。"s,
                    name(tc) + u8" step"s + _s(tc) + u8" in the pool."s));
            }
            wet(tc, 25);
            if (mef(6, ef) == 0)
            {
                if (tc != 0)
                {
                    hostileaction(0, tc);
                }
            }
            potionspill = 1;
            efstatus = static_cast<curse_state_t>(mef(8, ef)); // TODO
            dbid = mef(7, ef);
            access_item_db(15);
            if (cdata[tc].state() == character::state::empty)
            {
                check_kill(mef(6, ef), tc);
            }
            mef_delete(ef);
        }
    }
}

// returns true if turn ended
bool mef_proc_from_movement(int cc)
{
    int i = map(cdata[cc].position.x, cdata[cc].position.y, 8) - 1;
    if (mef(0, i) == 0)
    {
        return false;
    }
    if (mef(0, i) == 1)
    {
        if (cdatan(2, cc) != u8"spider"s)
        {
            if (rnd(mef(5, i) + 25) < rnd(sdata(10, cc) + sdata(12, cc) + 1)
                || cdata[cc].weight > 100)
            {
                if (is_in_fov(cc))
                {
                    txt(lang(
                        name(cc) + u8"は蜘蛛の巣を振り払った。"s,
                        name(cc) + u8" destroy"s + _s(cc) + u8" the cobweb."s));
                }
                mef_delete(i);
            }
            else
            {
                mef(5, i) = mef(5, i) * 3 / 4;
                if (is_in_fov(cc))
                {
                    txt(lang(
                        name(cc) + u8"は蜘蛛の巣にひっかかった。"s,
                        name(cc) + u8" "s + is(cc)
                            + u8" caught in a cobweb."s));
                }
                return true;
            }
        }
    }
    return false;
}

// returns true if caller needs to return directly after
bool mef_proc_from_physical_attack(int tc)
{
    int i = map(cdata[tc].position.x, cdata[tc].position.y, 8) - 1;
    if (mef(0, i) == 0)
    {
        return false;
    }
    if (mef(0, i) == 2)
    {
        if (rnd(2) == 0)
        {
            if (is_in_fov(cc))
            {
                txt(lang(
                    name(cc) + u8"は霧の中の幻影を攻撃した。"s,
                    name(cc) + u8" attack"s + _s(cc)
                        + u8" an illusion in the mist."s));
                add_damage_popup(u8"miss", tc, {191, 191, 191});
            }
            return true;
        }
    }
    return false;
}

void mef_clear_all()
{
    for (int cnt = 0; cnt < MEF_MAX; ++cnt)
    {
        mef(0, cnt) = 0;
    }
}



} // namespace elona

#include "mef.hpp"

#include "ability.hpp"
#include "audio.hpp"
#include "character.hpp"
#include "deferred_event.hpp"
#include "dmgheal.hpp"
#include "draw.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "map.hpp"
#include "message.hpp"
#include "random.hpp"
#include "variables.hpp"



namespace elona
{

int i_at_m79 = 0;

void initialize_mef()
{
    DIM3(mefsubref, 6, 6);
    mefsubref(0, 1) = 0;
    mefsubref(1, 1) = 0;
    mefsubref(0, 2) = 4;
    mefsubref(1, 2) = 0;
    mefsubref(2, 2) = 1;
    mefsubref(0, 3) = 5;
    mefsubref(1, 3) = 0;
    mefsubref(2, 3) = 1;
    mefsubref(0, 4) = 7;
    mefsubref(1, 4) = 0;
    mefsubref(0, 5) = 10;
    mefsubref(1, 5) = 0;
}

void mef_delete(int mef_index)
{
    if (mef(0, mef_index) == 7)
    {
        event_add(21, mef(2, mef_index), mef(3, mef_index));
    }
    cell_data.at(mef(2, mef_index), mef(3, mef_index)).mef_index_plus_one = 0;
    mef(0, mef_index) = 0;
    i_at_m79 = 199;
    for (int cnt = 0, cnt_end = (MEF_MAX - mef_index); cnt < cnt_end; ++cnt)
    {
        if (mef(0, i_at_m79) != 0)
        {
            for (int cnt = 0; cnt < 9; ++cnt)
            {
                mef(cnt, mef_index) = mef(cnt, i_at_m79);
            }
            cell_data.at(mef(2, i_at_m79), mef(3, i_at_m79))
                .mef_index_plus_one = mef_index + 1;
            mef(0, i_at_m79) = 0;
            break;
        }
        --i_at_m79;
    }
}



void mef_add(
    int pos_x,
    int pos_y,
    int type,
    int item_chip,
    int turns,
    int effect_power,
    int chara,
    int potion_item_id,
    int potion_item_curse_status,
    int color)
{
    int p_at_m79 = 0;
    p_at_m79 = cell_data.at(pos_x, pos_y).chip_id_actual;
    if (type == 5)
    {
        if (chip_data[p_at_m79].kind == 3)
        {
            return;
        }
    }
    if (cell_data.at(pos_x, pos_y).mef_index_plus_one != 0)
    {
        i_at_m79 = cell_data.at(pos_x, pos_y).mef_index_plus_one - 1;
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
            cell_data.at(mef(2, i_at_m79), mef(3, i_at_m79))
                .mef_index_plus_one = 0;
        }
    }
    mef(0, i_at_m79) = type;
    mef(1, i_at_m79) = item_chip + color * 10000;
    mef(2, i_at_m79) = pos_x;
    mef(3, i_at_m79) = pos_y;
    mef(4, i_at_m79) = turns;
    mef(5, i_at_m79) = effect_power;
    mef(6, i_at_m79) = chara;
    mef(7, i_at_m79) = potion_item_id;
    mef(8, i_at_m79) = potion_item_curse_status;
    cell_data.at(pos_x, pos_y).mef_index_plus_one = i_at_m79 + 1;
}

void mef_update()
{
    optional<data::InstanceId> sound = none;
    for (int cnt = 0; cnt < MEF_MAX; ++cnt)
    {
        if (mef(0, cnt) == 0)
        {
            break;
        }
        if (mef(0, cnt) == 5)
        {
            if (map_data.indoors_flag == 2)
            {
                if (map_data.type != mdata_t::MapType::world_map)
                {
                    if (game_data.weather == 3 || game_data.weather == 4)
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
                                cdata.player().position.x,
                                cdata.player().position.y) < 6)
                        {
                            sound = "core.fire1";
                        }
                    }
                    for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
                    {
                        x = rnd(2) + dx - rnd(2);
                        y = rnd(2) + dy - rnd(2);
                        if (x < 0 || y < 0 || x >= map_data.width ||
                            y >= map_data.height)
                        {
                            f = 0;
                            continue;
                        }
                        if (chip_data.for_cell(x, y).effect & 4)
                        {
                            cell_data.at(x, y).chip_id_actual = 37;
                            cnt = 0 - 1;
                            continue;
                        }
                        mef_add(x, y, 5, 24, rnd(15) + 20, 50, i);
                        mapitem_fire(
                            i == -1 ? optional_ref<Character>{}
                                    : optional_ref<Character>{cdata[i]},
                            x,
                            y);
                    }
                }
            }
        }
        if (mef(0, cnt) == 7)
        {
            txt(i18n::s.get("core.mef.bomb_counter", mef(4, cnt)),
                Message::color{ColorIndex::red});
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
    if (sound)
    {
        snd(*sound);
    }
}



void mef_proc(Character& chara)
{
    int ef =
        cell_data.at(chara.position.x, chara.position.y).mef_index_plus_one - 1;
    if (mef(0, ef) == 0)
    {
        return;
    }
    if (mef(0, ef) == 3)
    {
        if (chara.is_floating() == 0 || chara.gravity > 0)
        {
            if (sdata(63, chara.index) / 50 < 7)
            {
                if (is_in_fov(chara))
                {
                    snd("core.water2");
                    txt(i18n::s.get("core.mef.melts", chara));
                }
                if (mef(6, ef) == 0)
                {
                    if (chara.index != 0)
                    {
                        hostileaction(0, chara.index);
                    }
                }
                int stat = damage_hp(
                    chara,
                    rnd_capped(mef(5, ef) / 25 + 5) + 1,
                    -15,
                    63,
                    mef(5, ef));
                if (stat == 0)
                {
                    check_kill(mef(6, ef), chara.index);
                }
            }
        }
    }
    if (mef(0, ef) == 5)
    {
        if (is_in_fov(chara))
        {
            snd("core.fire1");
            txt(i18n::s.get("core.mef.is_burnt", chara));
        }
        if (mef(6, ef) == 0)
        {
            if (chara.index != 0)
            {
                hostileaction(0, chara.index);
            }
        }
        int stat = damage_hp(
            chara, rnd_capped(mef(5, ef) / 15 + 5) + 1, -9, 50, mef(5, ef));
        if (stat == 0)
        {
            check_kill(mef(6, ef), chara.index);
        }
    }
    if (mef(0, ef) == 6)
    {
        if (chara.is_floating() == 0 || chara.gravity > 0)
        {
            if (is_in_fov(chara))
            {
                snd("core.water2");
                txt(i18n::s.get("core.mef.steps_in_pool", chara));
            }
            wet(chara.index, 25);
            if (mef(6, ef) == 0)
            {
                if (chara.index != 0)
                {
                    hostileaction(0, chara.index);
                }
            }
            potionspill = 1;
            efstatus = static_cast<CurseState>(mef(8, ef));
            item_db_on_drink(chara, none, mef(7, ef));
            if (chara.state() == Character::State::empty)
            {
                check_kill(mef(6, ef), chara.index);
            }
            mef_delete(ef);
        }
    }
}



// returns true if turn ended
bool mef_proc_from_movement(Character& chara)
{
    int i =
        cell_data.at(chara.position.x, chara.position.y).mef_index_plus_one - 1;
    if (mef(0, i) == 0)
    {
        return false;
    }
    if (mef(0, i) == 1)
    {
        if (cdatan(2, chara.index) != u8"core.spider"s)
        {
            if (rnd_capped(mef(5, i) + 25) <
                    rnd_capped(
                        sdata(10, chara.index) + sdata(12, chara.index) + 1) ||
                chara.weight > 100)
            {
                if (is_in_fov(chara))
                {
                    txt(i18n::s.get("core.mef.destroys_cobweb", chara));
                }
                mef_delete(i);
            }
            else
            {
                mef(5, i) = mef(5, i) * 3 / 4;
                if (is_in_fov(chara))
                {
                    txt(i18n::s.get("core.mef.is_caught_in_cobweb", chara));
                }
                return true;
            }
        }
    }
    return false;
}



// returns true if caller needs to return directly after
bool mef_proc_from_physical_attack(
    const Character& attacker,
    const Character& target)
{
    int i =
        cell_data.at(target.position.x, target.position.y).mef_index_plus_one -
        1;
    if (mef(0, i) == 0)
    {
        return false;
    }
    if (mef(0, i) == 2)
    {
        if (rnd(2) == 0)
        {
            if (is_in_fov(attacker))
            {
                txt(i18n::s.get("core.mef.attacks_illusion_in_mist", attacker));
                add_damage_popup(u8"miss", target.index, {191, 191, 191});
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

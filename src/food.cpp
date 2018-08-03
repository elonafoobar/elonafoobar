#include "food.hpp"
#include "ability.hpp"

#include "audio.hpp"
#include "buff.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "debug.hpp"
#include "dmgheal.hpp"
#include "elona.hpp"
#include "event.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "item_db.hpp"
#include "itemgen.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "random.hpp"
#include "status_ailment.hpp"
#include "trait.hpp"
#include "variables.hpp"

namespace elona
{

int cieat = 0;
int nutrition = 0;
int fdmax = 0;
elona_vector2<int> fdlist;


void get_hungry(int cc)
{
    if ((trait(158) && rnd(3) == 0) || debug::voldemort)
        return;

    int p = cdata[cc].nutrition / 1000;
    cdata[cc].nutrition -= 8;
    if (cdata[cc].nutrition / 1000 != p)
    {
        if (p == 1)
        {
            msgalert = 1;
            txt(i18n::s.get_enum(
                "core.locale.food.hunger_status.starving", rnd(2)));
        }
        else if (p == 2)
        {
            msgalert = 1;
            txt(i18n::s.get_enum(
                "core.locale.food.hunger_status.very_hungry", rnd(2)));
        }
        else if (p == 5)
        {
            msgalert = 1;
            txt(i18n::s.get_enum(
                "core.locale.food.hunger_status.hungry", rnd(3)));
        }
        refreshspeed(cc);
    }
}


void show_eating_message()
{
    txtef(2);
    if (cdata[cc].nutrition >= 12000)
    {
        txt(i18n::s.get_enum(
            "core.locale.food.eating_message.bloated", rnd(3)));
    }
    else if (cdata[cc].nutrition >= 10000)
    {
        txt(i18n::s.get_enum(
            "core.locale.food.eating_message.satisfied", rnd(4)));
    }
    else if (cdata[cc].nutrition >= 5000)
    {
        txt(i18n::s.get_enum("core.locale.food.eating_message.normal", rnd(3)));
    }
    else if (cdata[cc].nutrition >= 2000)
    {
        txt(i18n::s.get_enum("core.locale.food.eating_message.hungry", rnd(4)));
    }
    else if (cdata[cc].nutrition >= 1000)
    {
        txt(i18n::s.get_enum(
            "core.locale.food.eating_message.very_hungry", rnd(3)));
    }
    else
    {
        txt(i18n::s.get_enum(
            "core.locale.food.eating_message.starving", rnd(3)));
    }
}



void eat_rotten_food()
{
    if (cdata[cc].can_digest_rotten_food() == 1)
    {
        txt(i18n::s.get("core.locale.food.not_affected_by_rotten", cdata[cc]));
        return;
    }
    fdmax = 0;
    if (fdmax < 10)
    {
        fdlist(0, fdmax) = 10;
        fdlist(1, fdmax) = -100;
        ++fdmax;
    }
    if (fdmax < 10)
    {
        fdlist(0, fdmax) = 11;
        fdlist(1, fdmax) = -100;
        ++fdmax;
    }
    if (fdmax < 10)
    {
        fdlist(0, fdmax) = 17;
        fdlist(1, fdmax) = -100;
        ++fdmax;
    }
    if (fdmax < 10)
    {
        fdlist(0, fdmax) = 16;
        fdlist(1, fdmax) = -100;
        ++fdmax;
    }
    if (fdmax < 10)
    {
        fdlist(0, fdmax) = 12;
        fdlist(1, fdmax) = -100;
        ++fdmax;
    }
    if (fdmax < 10)
    {
        fdlist(0, fdmax) = 13;
        fdlist(1, fdmax) = -100;
        ++fdmax;
    }
    if (fdmax < 10)
    {
        fdlist(0, fdmax) = 14;
        fdlist(1, fdmax) = -100;
        ++fdmax;
    }
    if (fdmax < 10)
    {
        fdlist(0, fdmax) = 15;
        fdlist(1, fdmax) = -100;
        ++fdmax;
    }
    nutrition = 1000;
    dmgcon(cc, status_ailment_t::paralyzed, 100);
    dmgcon(cc, status_ailment_t::confused, 200);
    return;
}



void cure_anorexia(int cc)
{
    if (cdata[cc].has_anorexia() == 0)
        return;

    cdata[cc].has_anorexia() = false;
    if (is_in_fov(cc) || cc < 16)
    {
        txt(i18n::s.get("core.locale.food.anorexia.recovers_from", cdata[cc]));
        snd(65);
    }
}



void chara_vomit(int prm_876)
{
    int p_at_m146 = 0;
    ++cdata[prm_876].anorexia_count;
    if (is_in_fov(prm_876))
    {
        snd(104);
        txt(i18n::s.get("core.locale.food.vomits", cdata[prm_876]));
    }
    if (cdata[prm_876].is_pregnant())
    {
        cdata[prm_876].is_pregnant() = false;
        if (is_in_fov(prm_876))
        {
            txt(i18n::s.get(
                "core.locale.food.spits_alien_children", cdata[prm_876]));
        }
    }
    if (cdata[prm_876].buffs[0].id != 0)
    {
        for (int cnt = 0; cnt < 16; ++cnt)
        {
            if (cdata[prm_876].buffs[cnt].id == 0)
            {
                break;
            }
            if (the_buff_db[cdata[prm_876].buffs[cnt].id]->type
                == buff_data::type_t::food)
            {
                buff_delete(prm_876, cnt);
                --cnt;
                continue;
            }
        }
    }
    if (mdata_map_type != mdata_t::map_type_t::world_map)
    {
        p_at_m146 = 2;
        for (const auto& cnt : items(-1))
        {
            if (inv[cnt].number() > 0)
            {
                if (inv[cnt].id == 704)
                {
                    ++p_at_m146;
                }
            }
        }
        if (rnd(p_at_m146 * p_at_m146 * p_at_m146) == 0 || prm_876 == 0)
        {
            flt();
            int stat = itemcreate(
                -1,
                704,
                cdata[prm_876].position.x,
                cdata[prm_876].position.y,
                0);
            if (stat != 0)
            {
                if (prm_876 != 0)
                {
                    inv[ci].subname = cdata[prm_876].id;
                }
            }
        }
    }
    if (cdata[prm_876].has_anorexia() == 0)
    {
        if ((prm_876 < 16 && cdata[prm_876].anorexia_count > 10)
            || (prm_876 >= 16 && rnd(4) == 0))
        {
            if (rnd(5) == 0)
            {
                cdata[prm_876].has_anorexia() = true;
                if (is_in_fov(prm_876))
                {
                    txt(i18n::s.get(
                        "core.locale.food.anorexia.develops", cdata[prm_876]));
                    snd(65);
                }
            }
        }
    }
    else
    {
        skillmod(10, prm_876, -50);
        skillmod(11, prm_876, -75);
        skillmod(17, prm_876, -100);
    }
    dmgcon(prm_876, status_ailment_t::dimmed, 100);
    modweight(prm_876, -(1 + rnd(5)));
    if (cdata[prm_876].nutrition <= 0)
    {
        dmghp(prm_876, 9999, -3);
    }
    cdata[prm_876].nutrition -= 3000;
    return;
}



void eatstatus(curse_state_t curse_state, int eater)
{
    if (cdata[eater].state() != character::state_t::alive)
        return;

    if (is_cursed(curse_state))
    {
        cdata[eater].nutrition -= 1500;
        if (is_in_fov(eater))
        {
            txt(i18n::s.get("core.locale.food.eat_status.bad", cdata[eater]));
        }
        chara_vomit(eater);
    }
    else if (curse_state == curse_state_t::blessed)
    {
        if (is_in_fov(eater))
        {
            txt(i18n::s.get("core.locale.food.eat_status.good", cdata[eater]));
        }
        if (rnd(5) == 0)
        {
            buff_add(eater, 19, 100, 500 + rnd(500));
        }
        healsan(eater, 2);
    }
}



int chara_anorexia(int prm_879)
{
    if (cdata[prm_879].has_anorexia() == 0)
    {
        return 0;
    }
    chara_vomit(prm_879);
    return 1;
}



void sickifcursed(curse_state_t curse_state, int drinker, int prm_882)
{
    if (!is_cursed(curse_state))
        return;

    if (rnd(prm_882) == 0)
    {
        if (is_in_fov(drinker))
        {
            txt(i18n::s.get(
                "core.locale.food.eat_status.cursed_drink", cdata[drinker]));
        }
        dmgcon(drinker, status_ailment_t::sick, 200);
    }
}



void cook()
{
    snd(25);
    item_separate(ci);
    s = itemname(ci);
    p = rnd(sdata(184, cc) + 6) + rnd((inv[cooktool].param1 / 50 + 1));
    if (p > sdata(184, cc) / 5 + 7)
    {
        p = sdata(184, cc) / 5 + 7;
    }
    p = rnd(p + 1);
    if (p > 3)
    {
        p = rnd(p);
    }
    if (sdata(184, cc) >= 5)
    {
        if (p < 3)
        {
            if (rnd(4) == 0)
            {
                p = 3;
            }
        }
    }
    if (sdata(184, cc) >= 10)
    {
        if (p < 3)
        {
            if (rnd(3) == 0)
            {
                p = 3;
            }
        }
    }
    p += inv[cooktool].param1 / 100;
    if (p > 9)
    {
        p = 9;
    }
    if (p < 1)
    {
        p = 1;
    }
    make_dish(ci, p);
    txt(i18n::s.get("core.locale.food.cook", s(0), inv[cooktool], inv[ci]));
    item_stack(0, ci, 1);
    int rank = inv[ci].param2;
    if (rank > 2)
    {
        skillexp(184, cc, 30 + rank * 5);
    }
    refresh_burden_state();
    return;
}



void make_dish(int ci, int type)
{
    inv[ci].image = picfood(type, inv[ci].param1 / 1000);
    inv[ci].weight = 500;
    inv[ci].param2 = type;
    if (inv[ci].material == 35 && inv[ci].param3 >= 0)
    {
        inv[ci].param3 = gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
            + gdata_year * 24 * 30 * 12 + 72;
    }
}



void apply_general_eating_effect(int cieat)
{
    tc = cc;
    DIM3(fdlist, 2, 10);
    for (int cnt = 0, cnt_end = (fdmax); cnt < cnt_end; ++cnt)
    {
        fdlist(0, cnt) = 0;
        fdlist(1, cnt) = 0;
    }
    nutrition = 2500;
    if (the_item_db[inv[ci].id]->is_cargo == 1)
    {
        nutrition += 2500;
    }
    fdmax = 0;
    i = inv[ci].param1 / 1000;
    if (i == 1)
    {
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 10;
            fdlist(1, fdmax) = 30;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 11;
            fdlist(1, fdmax) = 40;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 17;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        nutrition = 3500;
    }
    if (i == 8)
    {
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 17;
            fdlist(1, fdmax) = 20;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 13;
            fdlist(1, fdmax) = 20;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 15;
            fdlist(1, fdmax) = 20;
            ++fdmax;
        }
        nutrition = 2000;
    }
    if (i == 2)
    {
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 15;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        nutrition = 2000;
    }
    if (i == 3)
    {
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 16;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 17;
            fdlist(1, fdmax) = 20;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 13;
            fdlist(1, fdmax) = 30;
            ++fdmax;
        }
        nutrition = 1500;
    }
    if (i == 7)
    {
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 10;
            fdlist(1, fdmax) = 25;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 25;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 25;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 11;
            fdlist(1, fdmax) = 25;
            ++fdmax;
        }
        nutrition = 2800;
    }
    if (i == 4)
    {
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 16;
            fdlist(1, fdmax) = 40;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 30;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 30;
            ++fdmax;
        }
        nutrition = 1500;
    }
    if (i == 6)
    {
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 40;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 40;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 13;
            fdlist(1, fdmax) = 20;
            ++fdmax;
        }
        nutrition = 3000;
    }
    if (i == 5)
    {
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 11;
            fdlist(1, fdmax) = 60;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 40;
            ++fdmax;
        }
        nutrition = 3500;
    }
    if (the_item_db[inv[ci].id]->category == 57000)
    {
        nutrition = nutrition * (100 + inv[ci].param2 * 15) / 100;
    }
    for (int cnt = 0, cnt_end = (fdmax); cnt < cnt_end; ++cnt)
    {
        if (fdlist(1, cnt) > 0)
        {
            if (inv[ci].param2 < 3)
            {
                fdlist(1, cnt) = fdlist(1, cnt) / 2;
            }
            else
            {
                fdlist(1, cnt) =
                    fdlist(1, cnt) * (50 + inv[ci].param2 * 20) / 100;
            }
        }
        else if (inv[ci].param2 < 3)
        {
            fdlist(1, cnt) =
                fdlist(1, cnt) * ((3 - inv[ci].param2) * 100 + 100) / 100;
        }
        else
        {
            fdlist(1, cnt) = fdlist(1, cnt) * 100 / (inv[ci].param2 * 50);
        }
    }
    if (cc == 0)
    {
        p = inv[ci].param1 / 1000;
        for (int cnt = 0; cnt < 1; ++cnt)
        {
            if (cc == 0)
            {
                if (trait(41))
                {
                    if (inv[ci].id == 204)
                    {
                        s = chara_refstr(inv[ci].subname, 8);
                        if (strutil::contains(s(0), u8"/man/"))
                        {
                            txt(i18n::s.get(
                                "core.locale.food.effect.human.delicious"));
                            break;
                        }
                    }
                }
            }
            if (inv[ci].material == 35)
            {
                if (inv[ci].param3 < 0)
                {
                    txt(i18n::s.get("core.locale.food.effect.rotten"));
                    break;
                }
            }
            if (inv[ci].param2 == 0)
            {
                if (p == 1)
                {
                    txt(i18n::s.get("core.locale.food.effect.raw_meat"));
                    break;
                }
                if (p == 7)
                {
                    txt(i18n::s.get("core.locale.food.effect.powder"));
                    break;
                }
                if (p == 5)
                {
                    txt(i18n::s.get("core.locale.food.effect.raw"));
                    break;
                }
                txt(i18n::s.get_enum("core.locale.food.effect.boring", rnd(2)));
                break;
            }
            if (inv[ci].param2 < 3)
            {
                txt(i18n::s.get_enum(
                    "core.locale.food.effect.quality.bad", rnd(3)));
                break;
            }
            if (inv[ci].param2 < 5)
            {
                txt(i18n::s.get_enum(
                    "core.locale.food.effect.quality.so_so", rnd(2)));
                break;
            }
            if (inv[ci].param2 < 7)
            {
                txt(i18n::s.get_enum(
                    "core.locale.food.effect.quality.good", rnd(2)));
                break;
            }
            if (inv[ci].param2 < 9)
            {
                txt(i18n::s.get_enum(
                    "core.locale.food.effect.quality.great", rnd(3)));
                break;
            }
            txt(i18n::s.get_enum(
                "core.locale.food.effect.quality.delicious", rnd(3)));
        }
    }
    else if (inv[ci].material == 35)
    {
        if (inv[ci].param3 < 0)
        {
            txt(i18n::s.get("core.locale.food.effect.raw_glum", cdata[cc]));
        }
    }
    if (inv[ci].id == 425)
    {
        fdmax = 0;
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 10;
            fdlist(1, fdmax) = 100;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 11;
            fdlist(1, fdmax) = 100;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 17;
            fdlist(1, fdmax) = 100;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 16;
            fdlist(1, fdmax) = 100;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 100;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 13;
            fdlist(1, fdmax) = 100;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 100;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 15;
            fdlist(1, fdmax) = 100;
            ++fdmax;
        }
        nutrition = 2500;
        if (cc == 0)
        {
            txtef(2);
            txt(i18n::s.get("core.locale.food.effect.herb.curaria"));
        }
    }
    if (inv[ci].id == 422)
    {
        fdmax = 0;
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 10;
            fdlist(1, fdmax) = 900;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 11;
            fdlist(1, fdmax) = 700;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 17;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 16;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 13;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 15;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        nutrition = 500;
        modify_potential(cc, 10, 2);
        modify_potential(cc, 11, 2);
        if (cc == 0)
        {
            txtef(2);
            txt(i18n::s.get("core.locale.food.effect.herb.morgia"));
        }
    }
    if (inv[ci].id == 423)
    {
        fdmax = 0;
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 10;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 11;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 17;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 16;
            fdlist(1, fdmax) = 800;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 13;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 15;
            fdlist(1, fdmax) = 800;
            ++fdmax;
        }
        nutrition = 500;
        modify_potential(cc, 16, 2);
        modify_potential(cc, 15, 2);
        if (cc == 0)
        {
            txtef(2);
            txt(i18n::s.get("core.locale.food.effect.herb.mareilon"));
        }
    }
    if (inv[ci].id == 424)
    {
        fdmax = 0;
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 10;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 11;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 17;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 16;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 750;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 13;
            fdlist(1, fdmax) = 800;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 15;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        modify_potential(cc, 12, 2);
        modify_potential(cc, 13, 2);
        nutrition = 500;
        if (cc == 0)
        {
            txtef(2);
            txt(i18n::s.get("core.locale.food.effect.herb.spenseweed"));
        }
    }
    if (inv[ci].id == 426)
    {
        fdmax = 0;
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 10;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 11;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 17;
            fdlist(1, fdmax) = 850;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 16;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 13;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 700;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 15;
            fdlist(1, fdmax) = 10;
            ++fdmax;
        }
        nutrition = 500;
        modify_potential(cc, 17, 2);
        modify_potential(cc, 14, 2);
        if (cc == 0)
        {
            txtef(2);
            txt(i18n::s.get("core.locale.food.effect.herb.alraunia"));
        }
    }
    if (inv[ci].id == 427)
    {
        fdmax = 0;
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 10;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 11;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 17;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 16;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 12;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 13;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 14;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        if (fdmax < 10)
        {
            fdlist(0, fdmax) = 15;
            fdlist(1, fdmax) = 50;
            ++fdmax;
        }
        nutrition = 20000;
    }
    if (inv[ci].id == 738)
    {
        nutrition = 750;
    }
    if (cc == 0)
    {
        if (inv[ci].material == 35)
        {
            if (inv[ci].param3 < 0)
            {
                eat_rotten_food();
            }
        }
    }
    if (inv[ci].id == 204)
    {
        s = chara_refstr(inv[ci].subname, 8);
        if (cc == 0)
        {
            if (strutil::contains(s(0), u8"/man/"))
            {
                if (trait(41))
                {
                    txt(i18n::s.get("core.locale.food.effect.human.like"));
                }
                else
                {
                    txt(i18n::s.get("core.locale.food.effect.human.dislike"));
                    damage_insanity(cc, 15);
                    dmgcon(cc, status_ailment_t::insane, 150);
                    if (trait(41) == 0)
                    {
                        if (rnd(5) == 0)
                        {
                            trait_get_info(0, 41);
                            txtef(2);
                            txt(traitrefn(0));
                            trait(41) = 1;
                        }
                    }
                }
            }
            else if (trait(41))
            {
                txt(i18n::s.get(
                    "core.locale.food.effect.human.would_have_rather_eaten"));
                nutrition = nutrition * 2 / 3;
            }
        }
    }
    if (inv[ci].id == 204
        || ((inv[ci].id == 571 || inv[ci].id == 573) && rnd(3) == 0))
    {
        dbmode = 12;
        dbid = inv[ci].subname;
        access_character_info();
    }
    for (int cnt = 0, cnt_end = (fdmax); cnt < cnt_end; ++cnt)
    {
        i = 100;
        if (cdata[cc].nutrition >= 5000)
        {
            p = (cdata[cc].nutrition - 5000) / 25;
            i = i * 100 / (100 + p);
        }
        if (cc != 0)
        {
            i = 1500;
            if (inv[ci].material == 35)
            {
                if (inv[ci].param3 < 0)
                {
                    i = 500;
                }
            }
        }
        if (i > 0)
        {
            skillexp(fdlist(0, cnt), cc, fdlist(1, cnt) * i / 100);
        }
    }
    if (inv[ci].curse_state == curse_state_t::blessed)
    {
        nutrition = nutrition * 150 / 100;
    }
    if (is_cursed(inv[ci].curse_state))
    {
        nutrition = nutrition * 50 / 100;
    }
    cdata[cc].nutrition += nutrition;
    if (nutrition >= 3000)
    {
        if (rnd(10) == 0 || cdata[cc].nutrition >= 12000)
        {
            modweight(
                cc,
                rnd(3) + 1,
                cdata[cc].nutrition >= 20000
                    && rnd(30000 / std::max(1, cdata[cc].nutrition) + 2) == 0);
        }
    }
    if (cdata[cc].id == 261)
    {
        if (nutrition >= 2000)
        {
            int cibk = ci;
            flt(calcobjlv(cdata[cc].level));
            flttypeminor = 58500;
            itemcreate(-1, 0, cdata[cc].position.x, cdata[cc].position.y, 0);
            txtef(9);
            txt(i18n::s.get(
                "core.locale.food.effect.bomb_fish", cdata[cc], inv[ci]));
            ci = cibk;
        }
    }
    if (inv[ci].id == 204)
    {
        if (inv[ci].subname == 319)
        {
            txtef(2);
            txt(i18n::s.get(
                "core.locale.food.effect.little_sister", cdata[cc]));
            if (rnd(sdata.get(2, cc).original_level
                        * sdata.get(2, cc).original_level
                    + 1)
                < 2000)
            {
                skillmod(2, cc, 1000);
            }
            if (rnd(sdata.get(3, cc).original_level
                        * sdata.get(3, cc).original_level
                    + 1)
                < 2000)
            {
                skillmod(3, cc, 1000);
            }
            for (int cnt = 100; cnt < 400; ++cnt)
            {
                if (!the_ability_db[cnt]
                    || the_ability_db[cnt]->related_basic_attribute == 0
                    || sdata.get(cnt, cc).original_level == 0)
                {
                    continue;
                }
                modify_potential(cc, cnt, rnd(10) + 1);
            }
        }
    }
    if (inv[ci].id == 755)
    {
        txt(i18n::s.get("core.locale.food.effect.hero_cheese"));
        skillmod(19, cc, 2000);
    }
    if (inv[ci].id == 702)
    {
        skillmod(19, cc, 1000);
    }
    if (inv[ci].id == 639)
    {
        skillmod(19, cc, 20000);
    }
    if (inv[ci].id == 655)
    {
        skillmod(2, cc, 3000);
    }
    if (inv[ci].id == 662)
    {
        skillmod(3, cc, 3000);
    }
    if (inv[ci].id == 738)
    {
        if (cc < 16)
        {
            txt(i18n::s.get(
                "core.locale.food.effect.fortune_cookie", cdata[cc]));
            read_talk_file(u8"%COOKIE2");
            if (inv[ci].curse_state == curse_state_t::blessed
                || (inv[ci].curse_state == curse_state_t::none && rnd(2)))
            {
                read_talk_file(u8"%COOKIE1");
            }
            txtef(5);
            txt(""s + buff);
        }
    }
    if (inv[ci].id == 667)
    {
        txt(i18n::s.get(
            "core.locale.food.effect.sisters_love_fueled_lunch", cdata[cc]));
        healsan(cc, 30);
    }
    if (ibit(14, ci) == 1)
    {
        if (is_in_fov(cc))
        {
            txt(i18n::s.get(
                "core.locale.food.effect.poisoned.text", cdata[cc]));
            txt(i18n::s.get_enum(
                "core.locale.food.effect.poisoned.dialog", rnd(2)));
        }
        dmghp(cc, rnd(250) + 250, -4);
        if (cdata[cc].state() != character::state_t::alive)
        {
            if (cc != 0)
            {
                if (cdata[cc].relationship >= 0)
                {
                    modify_karma(0, -1);
                }
            }
            return;
        }
    }
    if (ibit(6, ci) == 1)
    {
        if (cc == 0)
        {
            txt(i18n::s.get("core.locale.food.effect.spiked.self"));
        }
        else
        {
            txtef(9);
            txt(i18n::s.get_enum(
                "core.locale.food.effect.spiked.other", rnd(2), cdata[cc]));
            cdata[cc].emotion_icon = 317;
            chara_mod_impression(cc, 30);
            modify_karma(0, -10);
            lovemiracle(cc);
        }
        dmgcon(cc, status_ailment_t::dimmed, 500);
        cdata[cc].emotion_icon = 317;
    }
    for (int cnt = 0; cnt < 15; ++cnt)
    {
        if (inv[ci].enchantments[cnt].id == 0)
        {
            break;
        }
        enc = inv[ci].enchantments[cnt].id;
        if (enc == 36)
        {
            p = rnd(inv[ci].enchantments[cnt].power / 50 + 1) + 1;
            healsp(cc, p);
            continue;
        }
        if (enc == 38)
        {
            p = rnd(inv[ci].enchantments[cnt].power / 25 + 1) + 1;
            healmp(cc, p / 5);
            continue;
        }
        if (enc == 37)
        {
            event_add(18, cc);
            continue;
        }
        if (enc == 40)
        {
            if (gdata_left_turns_of_timestop == 0)
            {
                txtef(9);
                txt(i18n::s.get(
                    "core.locale.action.time_stop.begins", cdata[cc]));
                gdata_left_turns_of_timestop =
                    inv[ci].enchantments[cnt].power / 100 + 1 + 1;
                continue;
            }
        }
        enc2 = enc / 10000;
        if (enc2 != 0)
        {
            enc = enc % 10000;
            if (enc2 == 1)
            {
                skillexp(
                    enc,
                    cc,
                    (inv[ci].enchantments[cnt].power / 50 + 1) * 100
                        * (1 + (cc != 0) * 5));
                if (is_in_fov(cc))
                {
                    if (inv[ci].enchantments[cnt].power / 50 + 1 >= 0)
                    {
                        txt(i18n::s.get(
                            "core.locale.food.effect.ability.develops",
                            cdata[cc],
                            i18n::_(
                                u8"ability", std::to_string(enc), u8"name")));
                    }
                    else
                    {
                        txt(i18n::s.get(
                            "core.locale.food.effect.ability.deteriorates",
                            cdata[cc],
                            i18n::_(
                                u8"ability", std::to_string(enc), u8"name")));
                    }
                }
                continue;
            }
            if (enc2 == 6)
            {
                if (is_in_fov(cc))
                {
                    txt(i18n::s.get(
                        "core.locale.food.effect.growth",
                        cdata[cc],
                        i18n::_(u8"ability", std::to_string(enc), u8"name")));
                }
                buff_add(
                    cc,
                    20 + (enc - 10),
                    (inv[ci].enchantments[cnt].power / 50 + 1) * 5
                        * (1 + (cc != 0) * 2),
                    2000);
                continue;
            }
        }
    }
    eatstatus(inv[cieat].curse_state, cc);
    return;
}



std::string
foodname(int type, const std::string& ingredient_, int rank, int character_id)
{
    std::string ingredient = ingredient_;
    if (type == 1 || type == 8)
    {
        // Food created from character drops (meat and eggs)
        if (character_id == 0)
        {
            ingredient = i18n::s.get_enum_property(
                "core.locale.food.names", "default_origin", type);
        }
        else
        {
            ingredient = chara_refstr(character_id, 2);
        }
    }
    else if (type == 5 || type == 7)
    {
        // Food that always always has a default origin (bread and noodles)
        ingredient = i18n::s.get_enum_property(
            "core.locale.food.names", "default_origin", type);
    }
    else if (ingredient == ""s)
    {
        // No ingredient name was provided
        ingredient = i18n::s.get_enum_property(
            "core.locale.food.names", "default_origin", type);
    }

    if ((type < 1 || type > 8) || (rank < 1 || rank > 9))
    {
        return ingredient;
    }
    else
    {
        return i18n::s.get_enum_property(
            "core.locale.food.names",
            type,
            "_" + std::to_string(rank),
            ingredient);
    }
}

} // namespace elona

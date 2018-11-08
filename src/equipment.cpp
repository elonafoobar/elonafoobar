#include "equipment.hpp"
#include "adventurer.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "class.hpp"
#include "data/types/type_item.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "random.hpp"
#include "variables.hpp"

namespace elona
{

int i_at_m66 = 0;

void equipinfo(int prm_529, int prm_530, int prm_531)
{
    int p_at_m66 = 0;
    std::string s_at_m66;
    if (inv[prm_529].identification_state
        != IdentifyState::completely_identified)
    {
        return;
    }
    for (int cnt = 0; cnt < 15; ++cnt)
    {
        p_at_m66 = inv[prm_529].enchantments[cnt].id;
        if (p_at_m66 == 0)
        {
            break;
        }
        i_at_m66 = p_at_m66 / 10000;
        if (i_at_m66 != 2)
        {
            continue;
        }
        i_at_m66 = p_at_m66 % 10000;
        pos(prm_530 + (i_at_m66 - 50) * 20, prm_531);
        p_at_m66 = std::abs(inv[prm_529].enchantments[cnt].power / 2 / 50) + 1;
        if (p_at_m66 > 5)
        {
            s_at_m66 = u8"+"s;
        }
        else
        {
            s_at_m66 = ""s + p_at_m66;
        }
        if (jp)
        {
            colorres();
            if (inv[prm_529].enchantments[cnt].power >= 0)
            {
                mes(u8"●"s);
            }
            else
            {
                mes(u8"▼"s);
            }
            pos(prm_530 + (i_at_m66 - 50) * 20 + 5, prm_531 + 1);
            mes(s_at_m66);
            pos(prm_530 + (i_at_m66 - 50) * 20 + 4, prm_531);
            color(255, 255, 255);
            mes(s_at_m66);
            color(0, 0, 0);
        }
        else
        {
            color(80, 60, 40);
            pos(prm_530 + (i_at_m66 - 50) * 20 + 5, prm_531);
            mes(""s + p_at_m66);
            color(0, 0, 0);
            colorres();
            pos(prm_530 + (i_at_m66 - 50) * 20 + 4, prm_531);
            mes(""s + p_at_m66);
            color(0, 0, 0);
        }
    }
}


int eqweaponlight()
{
    if (rnd(2))
    {
        return 10003;
    }
    if (rnd(2))
    {
        return 10009;
    }
    return 10004;
}



int eqweaponheavy()
{
    if (rnd(3) == 0)
    {
        return 10001;
    }
    if (rnd(3) == 0)
    {
        return 10010;
    }
    if (rnd(3) == 0)
    {
        return 10008;
    }
    return 10005;
}



void eqrandweaponmage(int prm_929)
{
    int p_at_m162 = 0;
    p_at_m162 = rnd(2);
    if (p_at_m162 == 0)
    {
        eqweapon1(0) = 10003;
        eqweapon1(1) = prm_929;
    }
    if (p_at_m162 == 1)
    {
        eqweapon1(0) = 10006;
        eqweapon1(1) = prm_929;
    }
}

void wear_most_valuable_equipment_for_all_body_parts()
{
    for (const auto& cnt : items(rc))
    {
        ci = cnt;
        if (inv[cnt].number() == 0 || inv[cnt].body_part != 0)
        {
            continue;
        }
        wear_most_valuable_equipment();
    }
}



void wear_most_valuable_equipment()
{
    int eqdup = 0;
    elona_vector1<int> bodylist;
    i = iequiploc(ci);
    if (i != 0)
    {
        eqdup = 0;
        for (int j = 0; j < 30; ++j)
        {
            if (cdata[rc].body_parts[j] / 10000 == i)
            {
                bodylist(eqdup) = j + 100;
                ++eqdup;
            }
        }
        if (eqdup == 0)
        {
            return;
        }
        for (int cnt = 0, cnt_end = (eqdup); cnt < cnt_end; ++cnt)
        {
            body = bodylist(cnt);
            i = cdata[rc].body_parts[body - 100] % 10000;
            if (i == 0)
            {
                equip_item(rc);
                break;
            }
            --i;
            f = 0;
            if (inv[ci].value >= inv[i].value)
            {
                f = 1;
            }
            if (eqdup > cnt + 1)
            {
                if (cdata[rc].body_parts[bodylist(cnt + 1) - 100] % 10000 == 0)
                {
                    f = 0;
                }
                else if (
                    inv[i].value
                    >= inv[cdata[rc].body_parts[bodylist(cnt + 1) - 100] % 10000
                           - 1]
                           .value)
                {
                    f = 0;
                }
            }
            if (f == 1)
            {
                int cibk = ci;
                unequip_item(rc);
                ci = cibk;
                equip_item(rc);
                break;
            }
        }
    }
}



void supply_new_equipment()
{
    int haveweapon = 0;
    int mustequip = 0;
    haveweapon = 0;
    for (int cnt = 0; cnt < 100; ++cnt)
    {
        f = 0;
        for (int cnt = 0; cnt < 4; ++cnt)
        {
            ci = get_random_inv(rc);
            if (inv[ci].number() == 0)
            {
                f = 1;
                break;
            }
            if (inv[ci].body_part != 0)
            {
                continue;
            }
            if (ibit(12, ci))
            {
                continue;
            }
            if (inv[ci].number() != 0)
            {
                inv[ci].remove();
                f = 1;
                break;
            }
        }
        if (f == 0)
        {
            ci = invhead + invrange - 1;
        }
        if (cdata[rc].character_role == 13)
        {
            flt(cdata[rc].level, Quality::great);
        }
        else
        {
            flt(cdata[rc].level, calcfixlv(Quality::bad));
        }
        mustequip = 0;
        for (int cnt = 0; cnt < 30; ++cnt)
        {
            p = cdata[rc].body_parts[cnt] / 10000;
            if (p == 0)
            {
                break;
            }
            if (cdata[rc].body_parts[cnt] % 10000 != 0)
            {
                if (p == 5)
                {
                    if (haveweapon == 0)
                    {
                        if (the_item_db
                                [inv[cdata[rc].body_parts[cnt] % 10000 - 1].id]
                                    ->category
                            == 10000)
                        {
                            haveweapon = 1;
                        }
                    }
                }
                continue;
            }
            if (p == 5)
            {
                if (haveweapon == 0)
                {
                    flttypemajor = 10000;
                    mustequip = 1;
                    break;
                }
            }
            if (p == 1)
            {
                flttypemajor = 12000;
                mustequip = 1;
                break;
            }
            if (p == 4)
            {
                flttypemajor = 16000;
                mustequip = 1;
                break;
            }
            if (p == 10)
            {
                flttypeminor = 24001;
                mustequip = 1;
                break;
            }
            if (p == 11)
            {
                flttypeminor = 25001;
                mustequip = 1;
                break;
            }
        }
        if (mustequip == 0)
        {
            break;
        }
        int stat = itemcreate(rc, 0, -1, -1, 0);
        if (stat == 0)
        {
            break;
        }
        inv[ci].identification_state = IdentifyState::completely_identified;
        if (inv[ci].quality >= Quality::miracle)
        {
            if (the_item_db[inv[ci].id]->category < 50000)
            {
                if (cdata[rc].character_role == 13)
                {
                    addnews(1, rc, 0, itemname(ci));
                }
            }
        }
        wear_most_valuable_equipment();
        if (cdata[rc].character_role != 13)
        {
            if (rnd(3))
            {
                break;
            }
        }
    }
}



void supply_initial_equipments()
{
    elona_vector1<int> eqhelm;
    elona_vector1<int> eqshield;
    elona_vector1<int> eqweapon2;
    elona_vector1<int> eqarmor;
    elona_vector1<int> eqglove;
    elona_vector1<int> eqboots;
    elona_vector1<int> eqcloack;
    elona_vector1<int> eqgirdle;
    elona_vector1<int> eqring2;
    elona_vector1<int> eqamulet1;
    elona_vector1<int> eqamulet2;
    int fixeq = 0;
    int probeq = 0;
    int eqtwowield = 0;
    if (cdatan(2, rc) == u8"core.mutant"s)
    {
        for (int cnt = 0, cnt_end = cnt + clamp(cdata[rc].level / 3, 0, 12);
             cnt < cnt_end;
             ++cnt)
        {
            gain_new_body_part(cdata[rc]);
        }
    }

    eqhelm.clear();
    eqweapon1.clear();
    eqshield.clear();
    eqrange.clear();
    eqammo.clear();
    eqweapon2.clear();
    eqarmor.clear();
    eqglove.clear();
    eqboots.clear();
    eqcloack.clear();
    eqgirdle.clear();
    eqring1.clear();
    eqring2.clear();
    eqamulet1.clear();
    eqamulet2.clear();

    if (mode == 1)
    {
        fixeq = 0;
        probeq = 10;
    }
    else if (cdata[rc].quality <= Quality::good)
    {
        probeq = 3;
        fixeq = 0;
    }
    else if (cdata[rc].quality == Quality::great)
    {
        probeq = 6;
        fixeq = 0;
    }
    else if (cdata[rc].quality == Quality::miracle)
    {
        probeq = 8;
        fixeq = 1;
    }
    else
    {
        probeq = 10;
        fixeq = 1;
    }
    if (cequipment == 1)
    {
        generatemoney(rc);
        eqweapon1(0) = eqweaponheavy();
        eqweapon1(1) = 2;
        eqshield(0) = 14003;
        eqshield(1) = 1;
        if (rnd(10) < probeq)
        {
            eqarmor(0) = 16001;
            eqarmor(1) = 1;
        }
        if (rnd(10) < probeq)
        {
            eqhelm(0) = 12001;
            eqhelm(1) = 1;
        }
        if (rnd(10) < probeq)
        {
            eqboots(0) = 18001;
            eqboots(1) = 1;
        }
        if (rnd(10) < probeq)
        {
            eqgirdle(0) = 19001;
            eqgirdle(1) = 1;
        }
        eqrange(0) = 24030;
        eqrange(1) = 1;
    }
    if (cequipment == 8)
    {
        generatemoney(rc);
        eqweapon1(0) = 232;
        eqweapon1(1) = 3;
        if (rnd(10) < probeq)
        {
            eqboots(0) = 18001;
            eqboots(1) = 1;
        }
        if (rnd(10) < probeq)
        {
            eqgirdle(0) = 19001;
            eqgirdle(1) = 1;
        }
        if (rnd(10) < probeq)
        {
            eqcloack(0) = 20001;
            eqcloack(1) = 2;
        }
        eqrange(0) = 24030;
        eqrange(1) = 1;
        eqtwohand = 1;
    }
    if (cequipment == 7)
    {
        generatemoney(rc);
        eqweapon1(0) = eqweaponlight();
        eqweapon1(1) = 2;
        eqweapon2(0) = eqweaponlight();
        eqweapon2(1) = 2;
        if (rnd(10) < probeq)
        {
            eqarmor(0) = 16001;
            eqarmor(1) = 1;
        }
        if (rnd(10) < probeq)
        {
            eqhelm(0) = 12001;
            eqhelm(1) = 1;
        }
        if (rnd(10) < probeq)
        {
            eqboots(0) = 18001;
            eqboots(1) = 1;
        }
        if (rnd(10) < probeq)
        {
            eqgirdle(0) = 19001;
            eqgirdle(1) = 1;
        }
        eqrange(0) = 24030;
        eqrange(1) = 1;
        eqtwowield = 1;
    }
    if (cequipment == 6)
    {
        generatemoney(rc);
        eqweapon1(0) = 10004;
        eqweapon1(1) = 1;
        if (rnd(10) < probeq)
        {
            eqshield(0) = 14003;
            eqshield(1) = 1;
        }
        if (rnd(10) < probeq)
        {
            eqarmor(0) = 16001;
            eqarmor(1) = 1;
        }
        if (rnd(10) < probeq)
        {
            eqhelm(0) = 12001;
            eqhelm(1) = 1;
        }
        if (rnd(10) < probeq)
        {
            eqboots(0) = 18001;
            eqboots(1) = 1;
        }
    }
    if (cequipment == 3)
    {
        generatemoney(rc);
        eqweapon1(0) = 10002;
        eqweapon1(1) = 1;
        eqrange(0) = 24001;
        eqrange(1) = 1;
        eqammo(0) = 25001;
        eqammo(1) = 1;
        eqcloack(0) = 20001;
        eqcloack(1) = 1;
        if (rnd(10) < probeq)
        {
            eqarmor(0) = 16001;
            eqarmor(1) = 1;
        }
        if (rnd(10) < probeq)
        {
            eqglove(0) = 22001;
            eqglove(1) = 1;
        }
        if (rnd(10) < probeq)
        {
            eqboots(0) = 18001;
            eqboots(1) = 1;
        }
    }
    if (cequipment == 2)
    {
        generatemoney(rc);
        eqrandweaponmage(2);
        eqamulet1(0) = 34001;
        eqamulet1(1) = 1;
        eqring1(0) = 32001;
        eqring1(1) = 2;
        eqring2(0) = 32001;
        eqring2(1) = 1;
        if (rnd(10) < probeq)
        {
            eqarmor(0) = 16003;
            eqarmor(1) = 1;
        }
        if (rnd(10) < probeq)
        {
            eqcloack(0) = 20001;
            eqcloack(1) = 1;
        }
    }
    if (cequipment == 4)
    {
        generatemoney(rc);
        eqweapon1(0) = 10002;
        eqweapon1(1) = 1;
        if (rnd(4) != 0)
        {
            eqrange(0) = 24020;
            eqrange(1) = 2;
            eqammo(0) = 25020;
            eqammo(1) = 1;
        }
        else
        {
            eqrange(0) = 24021;
            eqrange(1) = 2;
            eqammo(0) = 25030;
            eqammo(1) = 1;
        }
        eqcloack(0) = 20001;
        eqcloack(1) = 1;
        if (rnd(10) < probeq)
        {
            eqarmor(0) = 16001;
            eqarmor(1) = 1;
        }
        if (rnd(10) < probeq)
        {
            eqglove(0) = 22001;
            eqglove(1) = 1;
        }
        if (rnd(10) < probeq)
        {
            eqboots(0) = 18001;
            eqboots(1) = 1;
        }
    }
    if (cequipment == 5)
    {
        generatemoney(rc);
        eqrandweaponmage(2);
        eqamulet1(0) = 34001;
        eqamulet1(1) = 1;
        eqring1(0) = 32001;
        eqring1(1) = 2;
        eqring2(0) = 32001;
        eqring2(1) = 1;
        if (rnd(10) < probeq)
        {
            eqarmor(0) = 16001;
            eqarmor(1) = 1;
        }
        if (rnd(10) < probeq)
        {
            eqcloack(0) = 20001;
            eqcloack(1) = 1;
        }
    }
    if (cdata[rc].quality >= Quality::miracle)
    {
        for (int cnt = 0; cnt < 2; ++cnt)
        {
            if (rnd(2) == 0)
            {
                switch (rnd(20))
                {
                case 0: eqhelm(1) = 3; break;
                case 1: eqweapon1(1) = 3; break;
                case 2: eqshield(1) = 3; break;
                case 3: eqrange(1) = 3; break;
                case 4: eqammo(1) = 3; break;
                case 5: eqweapon2(1) = 3; break;
                case 6: eqarmor(1) = 3; break;
                case 7: eqglove(1) = 3; break;
                case 8: eqboots(1) = 3; break;
                case 9: eqcloack(1) = 3; break;
                case 10: eqgirdle(1) = 3; break;
                case 11: eqring1(1) = 3; break;
                case 12: eqring2(1) = 3; break;
                case 13: eqamulet1(1) = 3; break;
                case 14: eqamulet2(1) = 3; break;
                default: break;
                }
            }
            if (rnd(2) == 0)
            {
                --cnt;
                continue;
            }
        }
    }
    if (cspecialeq)
    {
        dbmode = 4;
        dbid = cdata[rc].id;
        access_character_info();
    }
    if (eqtwohand)
    {
        eqshield = 0;
    }
    if (cdata[rc].id == 9)
    {
        if (rnd(120) == 0)
        {
            eqamulet1 = 705;
        }
    }
    if (cdata[rc].id == 274)
    {
        if (rnd(100) == 0)
        {
            eqrange = 718;
        }
    }
    if (cdata[rc].id == 163)
    {
        if (rnd(200) == 0)
        {
            eqrange = 716;
        }
    }
    if (cdata[rc].id == 186 || cdata[rc].id == 187 || cdata[rc].id == 188)
    {
        if (rnd(800) == 0)
        {
            eqgirdle = 728;
        }
    }
    if (cdata[rc].id == 317)
    {
        if (rnd(150) == 0)
        {
            eqweapon1 = 719;
        }
    }
    if (cdata[rc].id == 309 || cdata[rc].id == 310 || cdata[rc].id == 311)
    {
        if (rnd(600) == 0)
        {
            eqamulet1 = 723;
        }
    }
    if (cdata[rc].id == 304)
    {
        if (rnd(250) == 0)
        {
            eqamulet1 = 722;
        }
    }
    for (int i = 0; i < 30; ++i)
    {
        p = cdata[rc].body_parts[i] / 10000;
        if (p == 0)
        {
            break;
        }
        if (p == 2)
        {
            if (eqamulet1)
            {
                if (eqamulet1 >= 10000)
                {
                    flt(calcobjlv(cdata[rc].level),
                        calcfixlv(static_cast<Quality>(fixeq + eqamulet1(1))));
                    flttypeminor = eqamulet1;
                    dbid = -1;
                }
                else
                {
                    flt();
                    dbid = eqamulet1;
                }
                itemcreate(rc, dbid, -1, -1, 0);
                body = 100 + i;
                equip_item(rc);
                eqamulet1 = 0;
                continue;
            }
            if (eqamulet2)
            {
                if (eqamulet2 >= 10000)
                {
                    flt(calcobjlv(cdata[rc].level),
                        calcfixlv(static_cast<Quality>(fixeq + eqamulet2(1))));
                    flttypeminor = eqamulet2;
                    dbid = -1;
                }
                else
                {
                    flt();
                    dbid = eqamulet2;
                }
                itemcreate(rc, dbid, -1, -1, 0);
                body = 100 + i;
                equip_item(rc);
                eqamulet2 = 0;
                continue;
            }
        }
        if (p == 6)
        {
            if (eqring1)
            {
                if (eqring1 >= 10000)
                {
                    flt(calcobjlv(cdata[rc].level),
                        calcfixlv(static_cast<Quality>(fixeq + eqring1(1))));
                    flttypeminor = eqring1;
                    dbid = -1;
                }
                else
                {
                    flt();
                    dbid = eqring1;
                }
                itemcreate(rc, dbid, -1, -1, 0);
                body = 100 + i;
                equip_item(rc);
                eqring1 = 0;
                continue;
            }
            if (eqring2)
            {
                if (eqring2 >= 10000)
                {
                    flt(calcobjlv(cdata[rc].level),
                        calcfixlv(static_cast<Quality>(fixeq + eqring2(1))));
                    flttypeminor = eqring2;
                    dbid = -1;
                }
                else
                {
                    flt();
                    dbid = eqring2;
                }
                itemcreate(rc, dbid, -1, -1, 0);
                body = 100 + i;
                equip_item(rc);
                eqring2 = 0;
                continue;
            }
        }
        if (p == 3)
        {
            if (eqcloack)
            {
                if (eqcloack >= 10000)
                {
                    flt(calcobjlv(cdata[rc].level),
                        calcfixlv(static_cast<Quality>(fixeq + eqcloack(1))));
                    flttypeminor = eqcloack;
                    dbid = -1;
                }
                else
                {
                    flt();
                    dbid = eqcloack;
                }
                itemcreate(rc, dbid, -1, -1, 0);
                body = 100 + i;
                equip_item(rc);
                eqcloack = 0;
                continue;
            }
            continue;
        }
        if (p == 8)
        {
            if (eqgirdle)
            {
                if (eqgirdle >= 10000)
                {
                    flt(calcobjlv(cdata[rc].level),
                        calcfixlv(static_cast<Quality>(fixeq + eqgirdle(1))));
                    flttypeminor = eqgirdle;
                    dbid = -1;
                }
                else
                {
                    flt();
                    dbid = eqgirdle;
                }
                itemcreate(rc, dbid, -1, -1, 0);
                body = 100 + i;
                equip_item(rc);
                eqgirdle = 0;
                continue;
            }
            continue;
        }
        if (p == 1)
        {
            if (eqhelm)
            {
                if (eqhelm >= 10000)
                {
                    flt(calcobjlv(cdata[rc].level),
                        calcfixlv(static_cast<Quality>(fixeq + eqhelm(1))));
                    flttypeminor = eqhelm;
                    dbid = -1;
                }
                else
                {
                    flt();
                    dbid = eqhelm;
                }
                itemcreate(rc, dbid, -1, -1, 0);
                body = 100 + i;
                equip_item(rc);
                eqhelm = 0;
                continue;
            }
            continue;
        }
        if (p == 4)
        {
            if (eqarmor)
            {
                if (eqarmor >= 10000)
                {
                    flt(calcobjlv(cdata[rc].level),
                        calcfixlv(static_cast<Quality>(fixeq + eqarmor(1))));
                    flttypeminor = eqarmor;
                    dbid = -1;
                }
                else
                {
                    flt();
                    dbid = eqarmor;
                }
                itemcreate(rc, dbid, -1, -1, 0);
                body = 100 + i;
                equip_item(rc);
                eqarmor = 0;
                continue;
            }
            continue;
        }
        if (p == 7)
        {
            if (eqglove)
            {
                if (eqglove >= 10000)
                {
                    flt(calcobjlv(cdata[rc].level),
                        calcfixlv(static_cast<Quality>(fixeq + eqglove(1))));
                    flttypeminor = eqglove;
                    dbid = -1;
                }
                else
                {
                    flt();
                    dbid = eqglove;
                }
                itemcreate(rc, dbid, -1, -1, 0);
                body = 100 + i;
                equip_item(rc);
                eqglove = 0;
                continue;
            }
            continue;
        }
        if (p == 9)
        {
            if (eqboots)
            {
                if (eqboots >= 10000)
                {
                    flt(calcobjlv(cdata[rc].level),
                        calcfixlv(static_cast<Quality>(fixeq + eqboots(1))));
                    flttypeminor = eqboots;
                    dbid = -1;
                }
                else
                {
                    flt();
                    dbid = eqboots;
                }
                itemcreate(rc, dbid, -1, -1, 0);
                body = 100 + i;
                equip_item(rc);
                eqboots = 0;
                continue;
            }
            continue;
        }
        if (p == 5)
        {
            if (eqmultiweapon)
            {
                for (int cnt = 0; cnt < 15; ++cnt)
                {
                    flt(calcobjlv(cdata[rc].level),
                        calcfixlv(static_cast<Quality>(2 + fixeq)));
                    itemcreate(rc, eqmultiweapon, -1, -1, 0);
                    if (inv[ci].weight > 1500)
                    {
                        if (cnt < 14)
                        {
                            inv[ci].remove();
                            continue;
                        }
                    }
                    break;
                }
                body = 100 + i;
                equip_item(rc);
                eqweapon1 = 0;
                continue;
            }
            if (eqweapon1)
            {
                if (eqweapon1 >= 10000)
                {
                    for (int cnt = 0; cnt < 15; ++cnt)
                    {
                        flt(calcobjlv(cdata[rc].level),
                            calcfixlv(
                                static_cast<Quality>(fixeq + eqweapon1(1))));
                        flttypeminor = eqweapon1;
                        dbid = -1;
                        itemcreate(rc, dbid, -1, -1, 0);
                        if (eqtwohand)
                        {
                            if (inv[ci].weight < 4000)
                            {
                                if (cnt < 14)
                                {
                                    inv[ci].remove();
                                    continue;
                                }
                            }
                        }
                        if (eqtwowield)
                        {
                            if (inv[ci].weight > 1500)
                            {
                                if (cnt < 14)
                                {
                                    inv[ci].remove();
                                    continue;
                                }
                            }
                        }
                        break;
                    }
                }
                else
                {
                    flt();
                    dbid = eqweapon1;
                    itemcreate(rc, dbid, -1, -1, 0);
                }
                body = 100 + i;
                equip_item(rc);
                eqweapon1 = 0;
                continue;
            }
            if (eqweapon2)
            {
                if (eqweapon2 >= 10000)
                {
                    for (int cnt = 0; cnt < 15; ++cnt)
                    {
                        flt(calcobjlv(cdata[rc].level),
                            calcfixlv(
                                static_cast<Quality>(fixeq + eqweapon2(1))));
                        flttypeminor = eqweapon2;
                        dbid = -1;
                        itemcreate(rc, dbid, -1, -1, 0);
                        if (eqtwowield)
                        {
                            if (inv[ci].weight > 1500)
                            {
                                if (cnt < 14)
                                {
                                    inv[ci].remove();
                                    continue;
                                }
                            }
                        }
                        break;
                    }
                }
                else
                {
                    flt();
                    dbid = eqweapon2;
                    itemcreate(rc, dbid, -1, -1, 0);
                }
                eqweapon2 = 0;
                body = 100 + i;
                equip_item(rc);
                continue;
            }
            if (eqshield)
            {
                if (eqshield >= 10000)
                {
                    flt(calcobjlv(cdata[rc].level),
                        calcfixlv(static_cast<Quality>(fixeq + eqshield(1))));
                    flttypeminor = eqshield;
                    dbid = -1;
                }
                else
                {
                    flt();
                    dbid = eqshield;
                }
                itemcreate(rc, dbid, -1, -1, 0);
                body = 100 + i;
                equip_item(rc);
                eqshield = 0;
                continue;
            }
            continue;
        }
        if (p == 10)
        {
            if (eqrange)
            {
                if (eqrange >= 10000)
                {
                    flt(calcobjlv(cdata[rc].level),
                        calcfixlv(static_cast<Quality>(fixeq + eqrange(1))));
                    flttypeminor = eqrange;
                    dbid = -1;
                }
                else
                {
                    flt();
                    dbid = eqrange;
                }
                itemcreate(rc, dbid, -1, -1, 0);
                body = 100 + i;
                equip_item(rc);
                eqrange = 0;
                continue;
            }
            continue;
        }
        if (p == 11)
        {
            if (eqammo)
            {
                if (eqammo >= 10000)
                {
                    flt(calcobjlv(cdata[rc].level),
                        calcfixlv(static_cast<Quality>(fixeq + eqammo(1))));
                    flttypeminor = eqammo;
                    dbid = -1;
                }
                else
                {
                    flt();
                    dbid = eqammo;
                }
                itemcreate(rc, dbid, -1, -1, 0);
                body = 100 + i;
                equip_item(rc);
                eqammo = 0;
                continue;
            }
            continue;
        }
    }
    if (cdata[rc].id == 326)
    {
        if (rnd(150) == 0)
        {
            flt();
            itemcreate(rc, 707, -1, -1, 0);
        }
        else
        {
            flt(calcobjlv(cdata[rc].level), calcfixlv());
            flttypeminor = 60005;
            itemcreate(rc, 0, -1, -1, 0);
        }
    }
    if (cdata[rc].id == 351 || cdata[rc].id == 352)
    {
        for (int cnt = 0; cnt < 6; ++cnt)
        {
            flt();
            nostack = 1;
            int stat = itemcreate(rc, 772, -1, -1, 0);
            if (stat != 0)
            {
                inv[ci].modify_number(rnd(4));
                if (rnd(2))
                {
                    inv[ci].param3 = -1;
                    inv[ci].image = 336;
                }
            }
        }
    }
    eqtwohand = 0;
    eqtwowield = 0;
    eqmultiweapon = 0;
}

void colorres(int)
{
    color(0, 0, 0);
    if (i_at_m66 == 50)
    {
        color(150, 0, 0);
    }
    if (i_at_m66 == 51)
    {
        color(0, 0, 150);
    }
    if (i_at_m66 == 52)
    {
        color(150, 150, 0);
    }
    if (i_at_m66 == 59)
    {
        color(150, 0, 150);
    }
    if (i_at_m66 == 53)
    {
        color(100, 80, 80);
    }
    if (i_at_m66 == 55)
    {
        color(0, 150, 0);
    }
    if (i_at_m66 == 60)
    {
        color(150, 100, 100);
    }
    if (i_at_m66 == 57)
    {
        color(50, 100, 150);
    }
    if (i_at_m66 == 58)
    {
        color(100, 150, 50);
    }
    if (i_at_m66 == 54)
    {
        color(150, 100, 50);
    }
    if (i_at_m66 == 56)
    {
        color(150, 50, 0);
    }
}

} // namespace elona

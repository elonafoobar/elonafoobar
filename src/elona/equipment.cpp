#include "equipment.hpp"

#include "adventurer.hpp"
#include "calc.hpp"
#include "chara_db.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "class.hpp"
#include "data/types/type_item.hpp"
#include "draw.hpp"
#include "enchantment.hpp"
#include "globals.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "random.hpp"
#include "variables.hpp"



namespace elona
{

namespace
{

snail::Color _get_element_color(int element)
{
    switch (element)
    {
    case 50: return {150, 0, 0};
    case 51: return {0, 0, 150};
    case 52: return {150, 150, 0};
    case 59: return {150, 0, 150};
    case 53: return {100, 80, 80};
    case 55: return {0, 150, 0};
    case 60: return {150, 100, 100};
    case 57: return {50, 100, 150};
    case 58: return {100, 150, 50};
    case 54: return {150, 100, 50};
    case 56: return {150, 50, 0};
    default: return {0, 0, 0};
    }
}



void draw_additional_item_info_resistance(const Item& equip, int x, int y)
{
    for (const auto& enc : equip.enchantments)
    {
        if (enc.id == 0)
            break;
        if (enc.id / 10000 != 2)
            continue;

        const auto power_level = std::abs(enc.power / 2 / 50) + 1;
        const auto element = enc.id % 10000;
        const auto color = _get_element_color(element);
        if (jp)
        {
            const auto s =
                power_level > 5 ? u8"+"s : std::to_string(power_level);
            const auto glyph = enc.power >= 0 ? u8"●" : u8"▼";
            mes(x + (element - 50) * 20, y, glyph, color);
            mes(x + (element - 50) * 20 + 5, y + 1, s, color);
            mes(x + (element - 50) * 20 + 4, y, s, {255, 255, 255});
        }
        else
        {
            mes(x + (element - 50) * 20 + 5,
                y,
                std::to_string(power_level),
                {80, 60, 40});
            mes(x + (element - 50) * 20 + 4,
                y,
                std::to_string(power_level),
                color);
        }
    }
}



void draw_additional_item_info_maintenance_and_ailment(
    const Item& equip,
    int x,
    int y)
{
    for (int i = 0; i < 10; ++i)
    {
        if (enchantment_find(equip, 60000 + 10 + i))
        {
            mes(x - 100 + i * 20, y, jp ? u8"●" : "#", {0, 100, 100});
        }
        else
        {
            mes(x - 100 + i * 20, y, "-", {0, 100, 100});
        }
    }
    for (int i = 0; i < 6; ++i)
    {
        if (enchantment_find(equip, 23 + i))
        {
            mes(x + 100 + i * 20, y, jp ? u8"●" : "#", {100, 32, 0});
        }
        else
        {
            mes(x + 100 + i * 20, y, "-", {100, 32, 0});
        }
    }
}

} // namespace



int i_at_m66 = 0;



void draw_additional_item_info_label(int x, int y)
{
    switch (g_show_additional_item_info)
    {
    case AdditionalItemInfo::none:
    case AdditionalItemInfo::_size: break;
    case AdditionalItemInfo::resistance:
        for (int i = 0; i < 11; ++i)
        {
            mes(x + 20 * i, y, i18n::s.get_enum("core.ui.equip.resist", i));
        }
        break;
    case AdditionalItemInfo::maintenance_and_ailment:
        for (int i = 0; i < 10; ++i)
        {
            mes(x - 100 + 20 * i,
                y,
                i18n::s.get_enum("core.ui.equip.maintenance", i));
        }
        for (int i = 0; i < 6; ++i)
        {
            mes(x + 100 + 20 * i,
                y,
                i18n::s.get_enum("core.ui.equip.ailment", i));
        }
        break;
    }
}



void draw_additional_item_info(const Item& equip, int x, int y)
{
    if (equip.identify_state != IdentifyState::completely)
        return;

    switch (g_show_additional_item_info)
    {
    case AdditionalItemInfo::none:
    case AdditionalItemInfo::_size: break;
    case AdditionalItemInfo::resistance:
        draw_additional_item_info_resistance(equip, x, y);
        break;
    case AdditionalItemInfo::maintenance_and_ailment:
        draw_additional_item_info_maintenance_and_ailment(equip, x, y);
        break;
    }
}



std::string cut_item_name_for_additional_info(
    const std::string& name,
    size_t adjustment)
{
    size_t width;
    switch (g_show_additional_item_info)
    {
    case AdditionalItemInfo::none:
    case AdditionalItemInfo::_size: return name;
    case AdditionalItemInfo::resistance: width = 24; break;
    case AdditionalItemInfo::maintenance_and_ailment: width = 14; break;
    }
    width -= adjustment;

    return strutil::take_by_width(name, width);
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



void eqrandweaponmage()
{
    if (rnd(2))
    {
        eqweapon1(0) = 10006;
        eqweapon1(1) = 2;
    }
    else
    {
        eqweapon1(0) = 10003;
        eqweapon1(1) = 2;
    }
}

void wear_most_valuable_equipment_for_all_body_parts()
{
    for (const auto& item : inv.for_chara(cdata[rc]))
    {
        ci = item.index;
        if (item.number() == 0 || item.body_part != 0)
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
    i = iequiploc(inv[ci]);
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
                    inv[i].value >=
                    inv[cdata[rc].body_parts[bodylist(cnt + 1) - 100] % 10000 -
                        1]
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
        for (int _j = 0; _j < 4; ++_j)
        {
            auto&& item = get_random_inv(rc);
            if (item.number() == 0)
            {
                f = 1;
                break;
            }
            if (item.body_part != 0)
            {
                continue;
            }
            if (item.is_quest_target())
            {
                continue;
            }
            if (item.number() != 0)
            {
                item.remove();
                f = 1;
                break;
            }
        }
        if (f == 0)
        {
            break;
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
                                [itemid2int(
                                     inv[cdata[rc].body_parts[cnt] % 10000 - 1]
                                         .id)]
                                    ->category == 10000)
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
        if (const auto item = itemcreate_chara_inv(rc, 0, 0))
        {
            item->identify_state = IdentifyState::completely;
            if (item->quality >= Quality::miracle)
            {
                if (the_item_db[itemid2int(item->id)]->category < 50000)
                {
                    if (cdata[rc].character_role == 13)
                    {
                        addnews(1, rc, 0, itemname(item->index));
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
        else
        {
            break;
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

    switch (class_get_equipment_type(cdatan(3, rc)))
    {
    case 0: break;
    case 1:
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
        break;
    case 2:
        generatemoney(rc);
        eqrandweaponmage();
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
        break;
    case 3:
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
        break;
    case 4:
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
        break;
    case 5:
        generatemoney(rc);
        eqrandweaponmage();
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
        break;
    case 6:
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
        break;
    case 7:
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
        break;
    case 8:
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
        break;
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
        chara_db_get_special_equipments(cdata[rc].id);
    }
    if (eqtwohand)
    {
        eqshield = 0;
    }
    if (cdata[rc].id == CharaId::beggar)
    {
        if (rnd(120) == 0)
        {
            eqamulet1 = 705;
        }
    }
    if (cdata[rc].id == CharaId::noble)
    {
        if (rnd(100) == 0)
        {
            eqrange = 718;
        }
    }
    if (cdata[rc].id == CharaId::rock_thrower)
    {
        if (rnd(200) == 0)
        {
            eqrange = 716;
        }
    }
    if (cdata[rc].id == CharaId::blade ||
        cdata[rc].id == CharaId::blade_alpha ||
        cdata[rc].id == CharaId::blade_omega)
    {
        if (rnd(800) == 0)
        {
            eqgirdle = 728;
        }
    }
    if (cdata[rc].id == CharaId::silver_eyed_witch)
    {
        if (rnd(150) == 0)
        {
            eqweapon1 = 719;
        }
    }
    if (cdata[rc].id == CharaId::asura || cdata[rc].id == CharaId::mitra ||
        cdata[rc].id == CharaId::varuna)
    {
        if (rnd(600) == 0)
        {
            eqamulet1 = 723;
        }
    }
    if (cdata[rc].id == CharaId::rogue_archer)
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
                int item_id;
                if (eqamulet1 >= 10000)
                {
                    flt(calcobjlv(cdata[rc].level),
                        calcfixlv(static_cast<Quality>(fixeq + eqamulet1(1))));
                    flttypeminor = eqamulet1;
                    item_id = -1;
                }
                else
                {
                    flt();
                    item_id = eqamulet1;
                }
                itemcreate_chara_inv(rc, item_id, 0);
                body = 100 + i;
                equip_item(rc);
                eqamulet1 = 0;
                continue;
            }
            if (eqamulet2)
            {
                int item_id;
                if (eqamulet2 >= 10000)
                {
                    flt(calcobjlv(cdata[rc].level),
                        calcfixlv(static_cast<Quality>(fixeq + eqamulet2(1))));
                    flttypeminor = eqamulet2;
                    item_id = -1;
                }
                else
                {
                    flt();
                    item_id = eqamulet2;
                }
                itemcreate_chara_inv(rc, item_id, 0);
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
                int item_id;
                if (eqring1 >= 10000)
                {
                    flt(calcobjlv(cdata[rc].level),
                        calcfixlv(static_cast<Quality>(fixeq + eqring1(1))));
                    flttypeminor = eqring1;
                    item_id = -1;
                }
                else
                {
                    flt();
                    item_id = eqring1;
                }
                itemcreate_chara_inv(rc, item_id, 0);
                body = 100 + i;
                equip_item(rc);
                eqring1 = 0;
                continue;
            }
            if (eqring2)
            {
                int item_id;
                if (eqring2 >= 10000)
                {
                    flt(calcobjlv(cdata[rc].level),
                        calcfixlv(static_cast<Quality>(fixeq + eqring2(1))));
                    flttypeminor = eqring2;
                    item_id = -1;
                }
                else
                {
                    flt();
                    item_id = eqring2;
                }
                itemcreate_chara_inv(rc, item_id, 0);
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
                int item_id;
                if (eqcloack >= 10000)
                {
                    flt(calcobjlv(cdata[rc].level),
                        calcfixlv(static_cast<Quality>(fixeq + eqcloack(1))));
                    flttypeminor = eqcloack;
                    item_id = -1;
                }
                else
                {
                    flt();
                    item_id = eqcloack;
                }
                itemcreate_chara_inv(rc, item_id, 0);
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
                int item_id;
                if (eqgirdle >= 10000)
                {
                    flt(calcobjlv(cdata[rc].level),
                        calcfixlv(static_cast<Quality>(fixeq + eqgirdle(1))));
                    flttypeminor = eqgirdle;
                    item_id = -1;
                }
                else
                {
                    flt();
                    item_id = eqgirdle;
                }
                itemcreate_chara_inv(rc, item_id, 0);
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
                int item_id;
                if (eqhelm >= 10000)
                {
                    flt(calcobjlv(cdata[rc].level),
                        calcfixlv(static_cast<Quality>(fixeq + eqhelm(1))));
                    flttypeminor = eqhelm;
                    item_id = -1;
                }
                else
                {
                    flt();
                    item_id = eqhelm;
                }
                itemcreate_chara_inv(rc, item_id, 0);
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
                int item_id;
                if (eqarmor >= 10000)
                {
                    flt(calcobjlv(cdata[rc].level),
                        calcfixlv(static_cast<Quality>(fixeq + eqarmor(1))));
                    flttypeminor = eqarmor;
                    item_id = -1;
                }
                else
                {
                    flt();
                    item_id = eqarmor;
                }
                itemcreate_chara_inv(rc, item_id, 0);
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
                int item_id;
                if (eqglove >= 10000)
                {
                    flt(calcobjlv(cdata[rc].level),
                        calcfixlv(static_cast<Quality>(fixeq + eqglove(1))));
                    flttypeminor = eqglove;
                    item_id = -1;
                }
                else
                {
                    flt();
                    item_id = eqglove;
                }
                itemcreate_chara_inv(rc, item_id, 0);
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
                int item_id;
                if (eqboots >= 10000)
                {
                    flt(calcobjlv(cdata[rc].level),
                        calcfixlv(static_cast<Quality>(fixeq + eqboots(1))));
                    flttypeminor = eqboots;
                    item_id = -1;
                }
                else
                {
                    flt();
                    item_id = eqboots;
                }
                itemcreate_chara_inv(rc, item_id, 0);
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
                    itemcreate_chara_inv(rc, eqmultiweapon, 0);
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
                        itemcreate_chara_inv(rc, -1, 0);
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
                    itemcreate_chara_inv(rc, eqweapon1, 0);
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
                        itemcreate_chara_inv(rc, -1, 0);
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
                    itemcreate_chara_inv(rc, eqweapon2, 0);
                }
                eqweapon2 = 0;
                body = 100 + i;
                equip_item(rc);
                continue;
            }
            if (eqshield)
            {
                int item_id;
                if (eqshield >= 10000)
                {
                    flt(calcobjlv(cdata[rc].level),
                        calcfixlv(static_cast<Quality>(fixeq + eqshield(1))));
                    flttypeminor = eqshield;
                    item_id = -1;
                }
                else
                {
                    flt();
                    item_id = eqshield;
                }
                itemcreate_chara_inv(rc, item_id, 0);
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
                int item_id;
                if (eqrange >= 10000)
                {
                    flt(calcobjlv(cdata[rc].level),
                        calcfixlv(static_cast<Quality>(fixeq + eqrange(1))));
                    flttypeminor = eqrange;
                    item_id = -1;
                }
                else
                {
                    flt();
                    item_id = eqrange;
                }
                itemcreate_chara_inv(rc, item_id, 0);
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
                int item_id;
                if (eqammo >= 10000)
                {
                    flt(calcobjlv(cdata[rc].level),
                        calcfixlv(static_cast<Quality>(fixeq + eqammo(1))));
                    flttypeminor = eqammo;
                    item_id = -1;
                }
                else
                {
                    flt();
                    item_id = eqammo;
                }
                itemcreate_chara_inv(rc, item_id, 0);
                body = 100 + i;
                equip_item(rc);
                eqammo = 0;
                continue;
            }
            continue;
        }
    }
    if (cdata[rc].id == CharaId::bard)
    {
        if (rnd(150) == 0)
        {
            flt();
            itemcreate_chara_inv(rc, 707, 0);
        }
        else
        {
            flt(calcobjlv(cdata[rc].level), calcfixlv());
            flttypeminor = 60005;
            itemcreate_chara_inv(rc, 0, 0);
        }
    }
    if (cdata[rc].id == CharaId::the_leopard_warrior ||
        cdata[rc].id == CharaId::silvia)
    {
        for (int cnt = 0; cnt < 6; ++cnt)
        {
            flt();
            nostack = 1;
            if (const auto item = itemcreate_chara_inv(rc, 772, 0))
            {
                item->modify_number(rnd(4));
                if (rnd(2))
                {
                    item->param3 = -1;
                    item->image = 336;
                }
            }
        }
    }
    eqtwohand = 0;
    eqtwowield = 0;
    eqmultiweapon = 0;
}

} // namespace elona

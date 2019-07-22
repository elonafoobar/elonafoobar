#include "itemgen.hpp"
#include "ability.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "data/types/type_item.hpp"
#include "enchantment.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "item_material.hpp"
#include "lua_env/lua_env.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "random.hpp"
#include "variables.hpp"


namespace
{

int initnum;



int calculate_original_value(const Item& ci)
{
    if (the_item_db[ci.id]->category == 60000)
    {
        return ci.value * 100 / (80 + std::max(1, ci.subname) * 20) -
            the_item_material_db[ci.material]->value * 2;
    }
    else
    {
        return ci.value * 100 / the_item_material_db[ci.material]->value;
    }
}

} // namespace



namespace elona
{

optional<int> itemcreate(int slot, int id, int x, int y, int number)
{
    if (flttypeminor != 0)
    {
        flttypemajor = 0;
    }
    dbid = id == 0 ? -1 : id;
    initnum = number;
    return do_create_item(slot, x, y);
}


void get_random_item_id()
{
    WeightedRandomSampler<int> sampler;

    for (const auto& data : the_item_db.values())
    {
        if (data.level > objlv)
            continue;
        if (fltselect != data.fltselect)
            continue;
        if (flttypemajor != 0 && flttypemajor != data.category)
            continue;
        if (flttypeminor != 0 && flttypeminor != data.subcategory)
            continue;
        if (filtermax != 0)
        {
            // FIXME: use std::all_of
            bool ok = true;
            for (int i = 0; i < filtermax; ++i)
            {
                if (the_item_db[data.legacy_id]->filter.find(filtern(i)) ==
                    std::string::npos)
                {
                    ok = false;
                    break;
                }
            }
            if (!ok)
                continue;
        }
        sampler.add(
            data.legacy_id,
            data.rarity /
                    (1000 + std::abs(data.level - objlv) * data.coefficient) +
                1);
    }

    dbid = sampler.get().value_or(25);
}



optional<int> do_create_item(int slot, int x, int y)
{
    if ((slot == 0 || slot == -1) && fixlv < Quality::godly)
    {
        if (sdata(19, 0) > rnd(5000)) // TODO coupling
        {
            fixlv = static_cast<Quality>(static_cast<int>(fixlv) + 1);
        }
    }

    ci = inv_getfreeid(slot);
    if (ci == -1)
        return none;

    item_delete(ci);
    inv[ci].index = ci;

    if (slot == -1 && mode != 6 && mode != 9)
    {
        bool ok = false;
        for (int i = 0; i < 100; ++i)
        {
            if (x == -1)
            {
                sx = rnd(map_data.width - 2) + 2;
                sy = rnd(map_data.height - 2) + 2;
                if (cell_data.at(sx, sy).item_appearances_actual != 0)
                {
                    continue;
                }
            }
            else
            {
                if (i == 0)
                {
                    sx = x;
                    sy = y;
                }
                else
                {
                    sx = x + rnd(i + 1) - rnd(i + 1);
                    sy = y + rnd(i + 1) - rnd(i + 1);
                }
                if (sx < 0 || sy < 0 || sx > map_data.width - 1 ||
                    sy > map_data.height - 1)
                {
                    continue;
                }
            }
            if (x != -1 && i == 0)
            {
                ok = true;
                inv[ci].position.x = sx;
                inv[ci].position.y = sy;
                break;
            }
            if (cell_data.at(sx, sy).feats != 0)
            {
                if (cell_data.at(sx, sy).feats / 1000 % 100 == 22 ||
                    cell_data.at(sx, sy).feats / 1000 % 100 == 20 ||
                    cell_data.at(sx, sy).feats / 1000 % 100 == 21)
                {
                    continue;
                }
            }
            if ((chip_data.for_cell(sx, sy).effect & 4) == 0)
            {
                ok = true;
                inv[ci].position.x = sx;
                inv[ci].position.y = sy;
                break;
            }
        }
        if (!ok)
            return none;
    }

    if (dbid == -1)
    {
        if (fltselect == 0 && mode != 6)
        {
            if (fixlv == Quality::great)
            {
                if (rnd(1000) == 0)
                {
                    fltselect = 2;
                }
            }
            if (fixlv == Quality::miracle)
            {
                if (rnd(100) == 0)
                {
                    fltselect = 2;
                }
            }
        }
        dbmode = 1;
        get_random_item_id();
        if (dbid == 25)
        {
            if (fltselect == 2)
            {
                fixlv = Quality::miracle;
            }
            objlv += 10;
            fltselect = 0;
            dbmode = 1;
            get_random_item_id();
        }
    }

    if (dbid == 25 && flttypemajor == 60002)
    {
        dbid = 501;
    }

    item_db_set_full_stats(inv[ci], dbid);
    item_db_get_charge_level(inv[ci], dbid);

    inv[ci].color = generate_color(the_item_db[inv[ci].id]->color, inv[ci].id);

    if (inv[ci].id == 24 && inv[ci].param1 == 0)
    {
        inv[ci].param1 = choice(isetbook);
    }
    if (inv[ci].id == 563 && inv[ci].param1 == 0)
    {
        inv[ci].param1 = randskill();
    }
    if (inv[ci].id == 783)
    {
        inv[ci].subname = choice(rpsourcelist);
        inv[ci].param1 = 1;
    }

    ++itemmemory(1, dbid);

    inv[ci].quality = static_cast<Quality>(fixlv);
    if (fixlv == Quality::special && mode != 6 && nooracle == 0)
    {
        int owner = inv_getowner(ci);
        if (owner != -1)
        {
            if (cdata[owner].character_role == 13)
            {
                artifactlocation.push_back(i18n::s.get(
                    "core.magic.oracle.was_held_by",
                    cnven(iknownnameref(inv[ci].id)),
                    cdata[owner],
                    mapname(cdata[owner].current_map),
                    game_data.date.day,
                    game_data.date.month,
                    game_data.date.year));
            }
            else
            {
                owner = -1;
            }
        }
        if (owner == -1)
        {
            artifactlocation.push_back(i18n::s.get(
                "core.magic.oracle.was_created_at",
                iknownnameref(inv[ci].id),
                mdatan(0),
                game_data.date.day,
                game_data.date.month,
                game_data.date.year));
        }
    }

    if (inv[ci].id == 617)
    {
        inv[ci].param1 = rnd(6);
        inv[ci].image = 385 + inv[ci].param1;
        inv[ci].value = inv[ci].param1 * inv[ci].param1 * 500 + 200;
    }

    if (inv[ci].id == 344)
    {
        inv[ci].param1 = rnd(5) + 1;
        if (mode != 6)
        {
            inv[ci].param1 = 2;
        }
        inv[ci].subname = inv[ci].param1;
        inv[ci].value = 5000 +
            4500 * inv[ci].param1 * inv[ci].param1 * inv[ci].param1 +
            inv[ci].param1 * 20000;
        if (inv[ci].param1 == 5)
        {
            inv[ci].value *= 2;
        }
    }

    if (inv[ci].id == 54)
    {
        inv[ci].set_number(calcinitgold(slot));
        if (inv[ci].quality == Quality::great)
        {
            inv[ci].set_number(inv[ci].number() * 2);
        }
        if (inv[ci].quality >= Quality::miracle)
        {
            inv[ci].set_number(inv[ci].number() * 4);
        }
        if (slot >= 0)
        {
            earn_gold(cdata[slot], inv[ci].number());
            inv[ci].remove();
            return ci;
        }
    }

    if (inv[ci].id == 729)
    {
        inv[ci].param4 = rnd(rnd(rnd(giftvalue.size()) + 1) + 1);
        inv[ci].value = inv[ci].param4 * 2500 + 500;
    }

    if (inv[ci].id == 578)
    {
        inv[ci].param2 = rnd(rnd(moneybox.size()) + 1);
        inv[ci].value =
            inv[ci].param2 * inv[ci].param2 * inv[ci].param2 * 1000 + 1000;
    }

    if (inv[ci].id == 685)
    {
        inv[ci].param2 = rnd(objlv + 1) + 1;
        inv[ci].value =
            2000 + inv[ci].param2 * inv[ci].param2 + inv[ci].param2 * 100;
    }

    if (inv[ci].id == 630)
    {
        initialize_item_material(inv[ci]);
    }

    if (inv[ci].id == 687)
    {
        inv[ci].param1 = rnd(rnd(clamp(objlv / 2, 1, 15)) + 1);
    }

    if (inv[ci].id == 667)
    {
        inv[ci].is_handmade() = true;
    }

    if (inv[ci].id == 641)
    {
        ++game_data.next_inventory_serial_id;
        inv[ci].count = game_data.next_inventory_serial_id;
    }

    if (inv[ci].id == 510)
    {
        inv[ci].count = 3;
    }

    if (inv[ci].id == 561)
    {
        inv[ci].count = 5;
    }

    if (inv[ci].id == 547)
    {
        inv[ci].count = 4;
    }

    if (inv[ci].id == 579)
    {
        inv[ci].count = 6;
    }

    if (reftype == 72000)
    {
        inv[ci].param1 = game_data.current_dungeon_level *
                (game_data.current_map != mdata_t::MapId::shelter_) +
            5;
        if (inv[ci].id == 283)
        {
            inv[ci].param1 = (rnd(10) + 1) * (cdata.player().level / 10 + 1);
        }
        if (inv[ci].id == 415 || inv[ci].id == 416)
        {
            inv[ci].param1 = cdata.player().level;
        }
        inv[ci].param2 =
            rnd(std::abs(game_data.current_dungeon_level) *
                    (game_data.current_map != mdata_t::MapId::shelter_) +
                1);
        if (inv[ci].id == 284 || inv[ci].id == 283)
        {
            inv[ci].param2 = rnd(15);
        }
        inv[ci].param3 = rnd(30000);
        if (inv[ci].id == 734)
        {
            inv[ci].param2 = rnd(rnd(100) + 1) + 1;
            inv[ci].value = inv[ci].param2 * 25 + 150;
            initnum = rnd(8);
        }
    }

    if (reftype == 57000 && inv[ci].param1 != 0)
    {
        if (mode == 6)
        {
            if (rnd(2) == 0)
            {
                inv[ci].param2 = 0;
            }
            else
            {
                inv[ci].param2 = 3 + rnd(3);
            }
        }
        if (inv[ci].param2 != 0)
        {
            inv[ci].image = picfood(inv[ci].param2, inv[ci].param1 / 1000);
        }
        if (inv[ci].material == 35)
        {
            inv[ci].param3 += game_data.date.hours();
        }
    }

    init_item_quality_curse_state_material_and_equipments(inv[ci]);
    if (reftype == 60000)
    {
        if (rnd(3) == 0)
        {
            inv[ci].subname = rnd(rnd(12) + 1);
        }
        else
        {
            inv[ci].subname = 0;
        }
    }

    if (mode == 6)
    {
        inv[ci].identify_state = IdentifyState::completely;
    }
    if (reftype == 68000 || reftype == 69000 || inv[ci].id == 622 ||
        inv[ci].id == 724 || inv[ci].id == 730 || inv[ci].id == 615)
    {
        inv[ci].curse_state = CurseState::none;
        inv[ci].identify_state = IdentifyState::completely;
    }
    if (reftype == 92000)
    {
        inv[ci].identify_state = IdentifyState::completely;
        inv[ci].curse_state = CurseState::none;
        itemmemory(0, inv[ci].id) = 1;
    }
    if (reftype == 62000 || reftype == 64000 || reftype == 77000)
    {
        inv[ci].curse_state = CurseState::none;
    }
    if (mode != 6)
    {
        if (reftype < 50000)
        {
            if (rnd(sdata(162, 0) + 1) > 5)
            {
                inv[ci].identify_state = IdentifyState::almost;
            }
        }
    }

    calc_furniture_value(inv[ci]);

    itemturn(ci);

    if (initnum != 0)
    {
        inv[ci].set_number(initnum);
    }

    if (nostack == 1)
    {
        nostack = 0;
    }
    else
    {
        int stat = item_stack(slot, ci);
        if (stat == 1)
        {
            ci = ti;
            return ci;
        }
    }

    if (slot == -1)
    {
        cell_refresh(inv[ci].position.x, inv[ci].position.y);
    }
    return ci;
}



void init_item_quality_curse_state_material_and_equipments(Item& item)
{
    if (reftype < 60000)
    {
        if (rnd(12) == 0)
        {
            item.curse_state = CurseState::blessed;
        }
        if (rnd(13) == 0)
        {
            item.curse_state = CurseState::cursed;
            if (the_item_db[item.id]->category < 50000)
            {
                if (rnd(4) == 0)
                {
                    item.curse_state = CurseState::doomed;
                }
            }
        }
    }
    if (cm || mode == 1 || item.quality == Quality::special)
    {
        item.curse_state = CurseState::none;
    }
    if (reftype < 50000 || (reftype == 60000 && rnd(5) == 0))
    {
        if (item.material >= 1000 || reftype == 60000)
        {
            initialize_item_material(item);
        }
        else
        {
            set_material_specific_attributes(item);
        }
    }
    if (fixeditemenc != 0)
    {
        for (int cnt = 0; cnt < 10; ++cnt)
        {
            if (fixeditemenc(cnt * 2) == 0)
            {
                break;
            }
            enchantment_add(
                ci,
                fixeditemenc(cnt * 2),
                fixeditemenc(cnt * 2 + 1),
                0,
                0,
                0,
                1);
        }
    }
    if (reftype < 52000)
    {
        add_enchantments();
    }
    else if (item.quality != Quality::special)
    {
        item.quality = Quality::good;
    }
}

void calc_furniture_value(Item& item)
{
    if (reftype == 60000)
    {
        if (item.subname != 0)
        {
            item.value = item.value * (80 + item.subname * 20) / 100;
        }
    }
}


void initialize_item_material(Item& item)
{
    determine_item_material(item);
    apply_item_material(item);
}

void determine_item_material(Item& item)
{
    int mtlv = 0;
    if (cm)
    {
        mtlv = cdata[rc].level / 15 + 1;
    }
    else
    {
        mtlv = rnd((objlv + 1)) / 10 + 1;
    }
    if (item.id == 630)
    {
        mtlv = rnd(mtlv + 1);
        if (rnd(3))
        {
            item.material = 1000;
        }
        else
        {
            item.material = 1001;
        }
    }
    p = rnd(100);
    for (int cnt = 0; cnt < 1; ++cnt)
    {
        if (p < 5)
        {
            p = 3;
            break;
        }
        if (p < 25)
        {
            p = 2;
            break;
        }
        if (p < 55)
        {
            p = 1;
            break;
        }
        p = 0;
    }
    if (mode == 1)
    {
        mtlv = 0;
        p = 0;
    }
    if (mtlv >= 5)
    {
        mtlv = 4;
    }
    mtlv = clamp(rnd(mtlv + 1) + objfix, 0, 4);
    objfix = 0;
    if (reftype == 60000)
    {
        if (rnd(2) == 0)
        {
            item.material = 1000;
        }
        else
        {
            item.material = 1001;
        }
    }
    if (item.material == 1000)
    {
        if (rnd(10) != 0)
        {
            item.material = item_material_lookup_metal(p, mtlv);
        }
        else
        {
            item.material = item_material_lookup_leather(p, mtlv);
        }
    }
    if (item.material == 1001)
    {
        if (rnd(10) != 0)
        {
            item.material = item_material_lookup_leather(p, mtlv);
        }
        else
        {
            item.material = item_material_lookup_metal(p, mtlv);
        }
    }
    if (rnd(25) == 0)
    {
        item.material = 35;
    }
}

void change_item_material(Item& item, int material_id)
{
    item.color = 0;
    p = item.material;
    reftype = the_item_db[item.id]->category;
    fixlv = item.quality;
    for (auto e : the_item_material_db[p]->enchantments)
    {
        enchantment_remove(item, e.first, e.second);
    }

    const auto original_value = calculate_original_value(item);

    dbid = item.id;
    item_db_set_basic_stats(inv[ci], dbid);
    item.value = original_value;
    if (material_id != 0)
    {
        item.material = material_id;
        fixmaterial = 0;
    }
    else
    {
        determine_item_material(item);
    }
    apply_item_material(item);
    calc_furniture_value(item);
    chara_refresh(cc);
}

void apply_item_material(Item& item)
{
    if (reftype == 60000)
    {
        if (item.material == 3 || item.material == 16 || item.material == 21 ||
            item.material == 2)
        {
            item.material = 43;
        }
    }
    p = item.material;
    item.weight = item.weight * the_item_material_db[p]->weight / 100;
    if (reftype == 60000)
    {
        item.value += the_item_material_db[p]->value * 2;
    }
    else
    {
        item.value = item.value * the_item_material_db[p]->value / 100;
    }
    if (item.color == 0)
    {
        item.color = the_item_material_db[p]->color;
    }
    p(1) = 120;
    p(2) = 80;
    if (fixlv == Quality::bad)
    {
        p(1) = 150;
        p(2) = 80;
    }
    if (fixlv == Quality::great)
    {
        p(1) = 100;
        p(2) = 70;
    }
    if (fixlv >= Quality::miracle)
    {
        p(1) = 80;
        p(2) = 70;
    }
    if (item.hit_bonus != 0)
    {
        item.hit_bonus = the_item_material_db[p]->hit_bonus * item.hit_bonus *
            9 / (p(1) - rnd(30));
    }
    if (item.damage_bonus != 0)
    {
        item.damage_bonus = the_item_material_db[p]->damage_bonus *
            item.damage_bonus * 5 / (p(1) - rnd(30));
    }
    if (item.dv != 0)
    {
        item.dv = the_item_material_db[p]->dv * item.dv * 7 / (p(1) - rnd(30));
    }
    if (item.pv != 0)
    {
        item.pv = the_item_material_db[p]->pv * item.pv * 9 / (p(1) - rnd(30));
    }
    if (item.dice_y != 0)
    {
        item.dice_y =
            item.dice_y * the_item_material_db[p]->dice_y / (p(1) + rnd(25));
    }
    set_material_specific_attributes(item);
}

void set_material_specific_attributes(Item& item)
{
    p = item.material;
    for (auto e : the_item_material_db[p]->enchantments)
    {
        enchantment_add(ci, e.first, e.second, 0, 1);
    }
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        if (the_item_material_db[p]->fireproof)
        {
            item.is_acidproof() = true;
        }
        if (the_item_material_db[p]->acidproof)
        {
            item.is_fireproof() = true;
        }
    }
}

} // namespace elona

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
    if (the_item_db[itemid2int(ci.id)]->category == 60000)
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

optional_ref<Item> do_create_item(int, int, int, int);



optional_ref<Item> itemcreate(int slot, int id, int x, int y, int number)
{
    if (flttypeminor != 0)
    {
        flttypemajor = 0;
    }
    initnum = number;
    return do_create_item(id == 0 ? -1 : id, slot, x, y);
}



optional_ref<Item> itemcreate(int slot, int id, const Position& pos, int number)
{
    return itemcreate(slot, id, pos.x, pos.y, number);
}



optional_ref<Item> itemcreate_player_inv(int id, int number)
{
    return itemcreate_chara_inv(0, id, number);
}



optional_ref<Item> itemcreate_chara_inv(int chara_index, int id, int number)
{
    return itemcreate(chara_index, id, -1, -1, number);
}



optional_ref<Item> itemcreate_extra_inv(int id, int x, int y, int number)
{
    return itemcreate(-1, id, x, y, number);
}



optional_ref<Item> itemcreate_extra_inv(int id, const Position& pos, int number)
{
    return itemcreate_extra_inv(id, pos.x, pos.y, number);
}



int get_random_item_id()
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

    return sampler.get().value_or(25);
}



optional_ref<Item> do_create_item(int item_id, int slot, int x, int y)
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

    auto&& item = inv[ci];

    item_delete(item);
    item.index = ci; // needed?

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
                item.position.x = sx;
                item.position.y = sy;
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
                item.position.x = sx;
                item.position.y = sy;
                break;
            }
        }
        if (!ok)
            return none;
    }

    if (item_id == -1)
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
        item_id = get_random_item_id();
        if (item_id == 25)
        {
            if (fltselect == 2)
            {
                fixlv = Quality::miracle;
            }
            objlv += 10;
            fltselect = 0;
            item_id = get_random_item_id();
        }
    }

    if (item_id == 25 && flttypemajor == 60002)
    {
        item_id = 501;
    }

    item_db_set_full_stats(item, item_id);
    item_db_get_charge_level(item, item_id);

    item.color = generate_color(
        the_item_db[itemid2int(item.id)]->color, itemid2int(item.id));

    if (item.id == ItemId::book_b && item.param1 == 0)
    {
        item.param1 = choice(isetbook);
    }
    if (item.id == ItemId::textbook && item.param1 == 0)
    {
        item.param1 = randskill();
    }
    if (item.id == ItemId::recipe)
    {
        item.subname = choice(rpsourcelist);
        item.param1 = 1;
    }

    ++itemmemory(1, item_id);

    item.quality = static_cast<Quality>(fixlv);
    if (fixlv == Quality::special && mode != 6 && nooracle == 0)
    {
        int owner = inv_getowner(item.index);
        if (owner != -1)
        {
            if (cdata[owner].character_role == 13)
            {
                artifactlocation.push_back(i18n::s.get(
                    "core.magic.oracle.was_held_by",
                    cnven(iknownnameref(itemid2int(item.id))),
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
                iknownnameref(itemid2int(item.id)),
                mdatan(0),
                game_data.date.day,
                game_data.date.month,
                game_data.date.year));
        }
    }

    if (item.id == ItemId::bait)
    {
        item.param1 = rnd(6);
        item.image = 385 + item.param1;
        item.value = item.param1 * item.param1 * 500 + 200;
    }

    if (item.id == ItemId::deed)
    {
        item.param1 = rnd(5) + 1;
        if (mode != 6)
        {
            item.param1 = 2;
        }
        item.subname = item.param1;
        item.value = 5000 + 4500 * item.param1 * item.param1 * item.param1 +
            item.param1 * 20000;
        if (item.param1 == 5)
        {
            item.value *= 2;
        }
    }

    if (item.id == ItemId::gold_piece)
    {
        item.set_number(calcinitgold(slot));
        if (item.quality == Quality::great)
        {
            item.set_number(item.number() * 2);
        }
        if (item.quality >= Quality::miracle)
        {
            item.set_number(item.number() * 4);
        }
        if (slot >= 0)
        {
            earn_gold(cdata[slot], item.number());
            item.remove();
            return item; // TODO: invalid return value!
        }
    }

    if (item.id == ItemId::gift)
    {
        item.param4 = rnd(rnd(rnd(giftvalue.size()) + 1) + 1);
        item.value = item.param4 * 2500 + 500;
    }

    if (item.id == ItemId::kitty_bank)
    {
        item.param2 = rnd(rnd(moneybox.size()) + 1);
        item.value = item.param2 * item.param2 * item.param2 * 1000 + 1000;
    }

    if (item.id == ItemId::monster_ball)
    {
        item.param2 = rnd_capped(objlv + 1) + 1;
        item.value = 2000 + item.param2 * item.param2 + item.param2 * 100;
    }

    if (item.id == ItemId::material_kit)
    {
        initialize_item_material(item);
    }

    if (item.id == ItemId::ancient_book)
    {
        item.param1 = rnd(rnd_capped(clamp(objlv / 2, 1, 15)) + 1);
    }

    if (item.id == ItemId::sisters_love_fueled_lunch)
    {
        item.is_handmade() = true;
    }

    if (item.id == ItemId::cooler_box)
    {
        ++game_data.next_inventory_serial_id;
        item.count = game_data.next_inventory_serial_id;
    }

    if (item.id == ItemId::heir_trunk)
    {
        item.count = 3;
    }

    if (item.id == ItemId::shop_strongbox)
    {
        item.count = 5;
    }

    if (item.id == ItemId::salary_chest)
    {
        item.count = 4;
    }

    if (item.id == ItemId::freezer)
    {
        item.count = 6;
    }

    if (reftype == 72000)
    {
        item.param1 = game_data.current_dungeon_level *
                (game_data.current_map != mdata_t::MapId::shelter_) +
            5;
        if (item.id == ItemId::suitcase)
        {
            item.param1 = (rnd(10) + 1) * (cdata.player().level / 10 + 1);
        }
        if (item.id == ItemId::treasure_ball ||
            item.id == ItemId::rare_treasure_ball)
        {
            item.param1 = cdata.player().level;
        }
        item.param2 = rnd_capped(
            std::abs(game_data.current_dungeon_level) *
                (game_data.current_map != mdata_t::MapId::shelter_) +
            1);
        if (item.id == ItemId::wallet || item.id == ItemId::suitcase)
        {
            item.param2 = rnd(15);
        }
        item.param3 = rnd(30000);
        if (item.id == ItemId::small_gamble_chest)
        {
            item.param2 = rnd(rnd(100) + 1) + 1;
            item.value = item.param2 * 25 + 150;
            initnum = rnd(8);
        }
    }

    if (reftype == 57000 && item.param1 != 0)
    {
        if (mode == 6)
        {
            if (rnd(2) == 0)
            {
                item.param2 = 0;
            }
            else
            {
                item.param2 = 3 + rnd(3);
            }
        }
        if (item.param2 != 0)
        {
            item.image = picfood(item.param2, item.param1 / 1000);
        }
        if (item.material == 35)
        {
            item.param3 += game_data.date.hours();
        }
    }

    init_item_quality_curse_state_material_and_equipments(item);
    if (reftype == 60000)
    {
        if (rnd(3) == 0)
        {
            item.subname = rnd(rnd(12) + 1);
        }
        else
        {
            item.subname = 0;
        }
    }

    if (mode == 6)
    {
        item.identify_state = IdentifyState::completely;
    }
    if (reftype == 68000 || reftype == 69000 ||
        item.id == ItemId::small_medal || item.id == ItemId::music_ticket ||
        item.id == ItemId::token_of_friendship || item.id == ItemId::bill)
    {
        item.curse_state = CurseState::none;
        item.identify_state = IdentifyState::completely;
    }
    if (reftype == 92000)
    {
        item.identify_state = IdentifyState::completely;
        item.curse_state = CurseState::none;
        itemmemory(0, itemid2int(item.id)) = 1;
    }
    if (reftype == 62000 || reftype == 64000 || reftype == 77000)
    {
        item.curse_state = CurseState::none;
    }
    if (mode != 6)
    {
        if (reftype < 50000)
        {
            if (rnd_capped(sdata(162, 0) + 1) > 5)
            {
                item.identify_state = IdentifyState::almost;
            }
        }
    }

    calc_furniture_value(item);

    itemturn(item);

    if (initnum != 0)
    {
        item.set_number(initnum);
    }

    if (nostack == 1)
    {
        nostack = 0;
    }
    else
    {
        if (item_stack(slot, item))
        {
            ci = ti;
            return inv[ti];
        }
    }

    if (slot == -1)
    {
        cell_refresh(item.position.x, item.position.y);
    }
    return item;
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
            if (the_item_db[itemid2int(item.id)]->category < 50000)
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
                item,
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
        add_enchantments(item);
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
    if (item.id == ItemId::material_kit)
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
    reftype = the_item_db[itemid2int(item.id)]->category;
    fixlv = item.quality;
    for (auto e : the_item_material_db[p]->enchantments)
    {
        enchantment_remove(item, e.first, e.second);
    }

    const auto original_value = calculate_original_value(item);

    item_db_set_basic_stats(item, itemid2int(item.id));
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
        enchantment_add(item, e.first, e.second, 0, 1);
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

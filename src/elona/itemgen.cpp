#include "itemgen.hpp"

#include "ability.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "data/types/type_item.hpp"
#include "data/types/type_item_material.hpp"
#include "enchantment.hpp"
#include "i18n.hpp"
#include "inventory.hpp"
#include "item.hpp"
#include "item_material.hpp"
#include "lua_env/lua_env.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "random.hpp"
#include "text.hpp"
#include "variables.hpp"



namespace
{

int initnum;



int calculate_original_value(const ItemRef& item)
{
    if (item->material == "")
        return item->value;

    if (the_item_db[item->id]->category == ItemCategory::furniture)
    {
        return item->value * 100 / (80 + std::max(1, item->subname) * 20) -
            the_item_material_db[item->material]->value * 2;
    }
    else
    {
        return item->value * 100 / the_item_material_db[item->material]->value;
    }
}

} // namespace



namespace elona
{

OptionalItemRef do_create_item(int, const InventoryRef&, int, int);



OptionalItemRef
itemcreate(const InventoryRef& inv, int id, int x, int y, int number)
{
    if (flttypeminor != 0)
    {
        flttypemajor = 0;
    }
    initnum = number;
    return do_create_item(id == 0 ? -1 : id, inv, x, y);
}



OptionalItemRef
itemcreate(const InventoryRef& inv, int id, const Position& pos, int number)
{
    return itemcreate(inv, id, pos.x, pos.y, number);
}



OptionalItemRef itemcreate_player_inv(int id, int number)
{
    return itemcreate_chara_inv(cdata.player(), id, number);
}



OptionalItemRef itemcreate_chara_inv(Character& chara, int id, int number)
{
    return itemcreate(g_inv.for_chara(chara), id, -1, -1, number);
}



OptionalItemRef itemcreate_map_inv(int id, int x, int y, int number)
{
    return itemcreate(g_inv.ground(), id, x, y, number);
}



OptionalItemRef itemcreate_map_inv(int id, const Position& pos, int number)
{
    return itemcreate_map_inv(id, pos.x, pos.y, number);
}



OptionalItemRef itemcreate_tmp_inv(int id, int number)
{
    return itemcreate(g_inv.tmp(), id, -1, -1, number);
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
        if (flttypemajor != 0 && flttypemajor != (int)data.category)
            continue;
        if (flttypeminor != 0 && flttypeminor != data.subcategory)
            continue;
        if (filtermax != 0)
        {
            // FIXME: use std::all_of
            bool ok = true;
            for (int i = 0; i < filtermax; ++i)
            {
                if (the_item_db[data.integer_id]->filter.find(filtern(i)) ==
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
            data.integer_id,
            data.rarity /
                    (1000 + std::abs(data.level - objlv) * data.coefficient) +
                1);
    }

    return sampler.get().value_or(25);
}



bool upgrade_item_quality(const InventoryRef& inv)
{
    const auto owner_chara = inv_get_owner(inv).as_character();
    if (owner_chara && !owner_chara->is_player())
        return false;

    return cdata.player().get_skill(19).level > rnd(5000);
}



OptionalItemRef
do_create_item(int item_id, const InventoryRef& inv, int x, int y)
{
    if (fixlv < Quality::godly && upgrade_item_quality(inv))
    {
        fixlv = static_cast<Quality>(static_cast<int>(fixlv) + 1);
    }

    const auto empty_slot_opt = inv_make_free_slot(inv);
    if (!empty_slot_opt)
        return nullptr;

    const auto empty_slot = *empty_slot_opt;

    optional<Position> item_pos;
    if (inv_get_owner(inv).is_map())
    {
        bool ok = false;
        for (int i = 0; i < 100; ++i)
        {
            if (x == -1)
            {
                sx = rnd(map_data.width - 2) + 2;
                sy = rnd(map_data.height - 2) + 2;
                if (!cell_data.at(sx, sy).item_info_actual.is_empty())
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
                item_pos = Position{sx, sy};
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
                item_pos = Position{sx, sy};
                break;
            }
        }
        if (!ok)
            return nullptr;
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

    const auto item = Inventory::create(empty_slot);
    if (item_pos)
    {
        item->set_position(*item_pos);
    }

    if (item_id == 25 && flttypemajor == 60002)
    {
        item_id = 501;
    }

    item_db_set_full_stats(item, item_id);
    item_db_get_charge_level(item, item_id);

    item->tint = generate_color(
        the_item_db[item->id]->tint, the_item_db[item->id]->integer_id);

    if (item->id == "core.book_b" && item->param1 == 0)
    {
        item->param1 = choice(isetbook);
    }
    if (item->id == "core.textbook" && item->param1 == 0)
    {
        item->param1 = randskill();
    }
    if (item->id == "core.recipe")
    {
        item->subname = choice(rpsourcelist);
        item->param1 = 1;
    }

    ++itemmemory(1, item_id);

    item->quality = static_cast<Quality>(fixlv);
    if (fixlv == Quality::special && mode != 6 && nooracle == 0)
    {
        const auto owner = item_get_owner(item).as_character();
        if (owner && owner->role == Role::adventurer)
        {
            artifactlocation.push_back(i18n::s.get(
                "core.magic.oracle.was_held_by",
                cnven(iknownnameref(the_item_db[item->id]->integer_id)),
                *owner,
                mapname(owner->current_map),
                game_data.date.day,
                game_data.date.month,
                game_data.date.year));
        }
        else
        {
            artifactlocation.push_back(i18n::s.get(
                "core.magic.oracle.was_created_at",
                iknownnameref(the_item_db[item->id]->integer_id),
                mdatan(0),
                game_data.date.day,
                game_data.date.month,
                game_data.date.year));
        }
    }

    if (item->id == "core.bait")
    {
        item->param1 = rnd(6);
        item->image = 385 + item->param1;
        item->value = item->param1 * item->param1 * 500 + 200;
    }

    if (item->id == "core.deed")
    {
        item->param1 = rnd(5) + 1;
        if (mode != 6)
        {
            item->param1 = 2;
        }
        item->subname = item->param1;
        item->value = 5000 + 4500 * item->param1 * item->param1 * item->param1 +
            item->param1 * 20000;
        if (item->param1 == 5)
        {
            item->value *= 2;
        }
    }

    if (item->id == "core.gold_piece")
    {
        const auto owner_chara = inv_get_owner(inv).as_character();
        item->set_number(calcinitgold(owner_chara ? owner_chara->index : -1));
        if (item->quality == Quality::great)
        {
            item->set_number(item->number() * 2);
        }
        if (item->quality >= Quality::miracle)
        {
            item->set_number(item->number() * 4);
        }
        if (owner_chara)
        {
            earn_gold(*owner_chara, item->number());
            item->remove();
            return item; // TODO: invalid return value!
        }
    }

    if (item->id == "core.gift")
    {
        item->param4 = rnd(rnd(rnd(giftvalue.size()) + 1) + 1);
        item->value = item->param4 * 2500 + 500;
    }

    if (item->id == "core.kitty_bank")
    {
        item->param2 = rnd(rnd(moneybox.size()) + 1);
        item->value = item->param2 * item->param2 * item->param2 * 1000 + 1000;
    }

    if (item->id == "core.monster_ball")
    {
        item->param2 = rnd_capped(objlv + 1) + 1;
        item->value = 2000 + item->param2 * item->param2 + item->param2 * 100;
    }

    if (item->id == "core.material_kit")
    {
        initialize_item_material(item);
    }

    if (item->id == "core.ancient_book")
    {
        item->param1 = rnd(rnd_capped(clamp(objlv / 2, 1, 15)) + 1);
    }

    if (item->id == "core.sisters_love_fueled_lunch")
    {
        item->is_handmade = true;
    }

    if (item->id == "core.cooler_box")
    {
        ++game_data.next_inventory_serial_id;
        item->charges = game_data.next_inventory_serial_id;
    }

    if (item->id == "core.heir_trunk")
    {
        item->charges = 3;
    }

    if (item->id == "core.shop_strongbox")
    {
        item->charges = 5;
    }

    if (item->id == "core.salary_chest")
    {
        item->charges = 4;
    }

    if (item->id == "core.freezer")
    {
        item->charges = 6;
    }

    const auto category = the_item_db[item->id]->category;

    if (category == ItemCategory::chest)
    {
        item->param1 = game_data.current_dungeon_level *
                (game_data.current_map != mdata_t::MapId::shelter_) +
            5;
        if (item->id == "core.suitcase")
        {
            item->param1 = (rnd(10) + 1) * (cdata.player().level / 10 + 1);
        }
        if (item->id == "core.treasure_ball" ||
            item->id == "core.rare_treasure_ball")
        {
            item->param1 = cdata.player().level;
        }
        item->param2 = rnd_capped(
            std::abs(game_data.current_dungeon_level) *
                (game_data.current_map != mdata_t::MapId::shelter_) +
            1);
        if (item->id == "core.wallet" || item->id == "core.suitcase")
        {
            item->param2 = rnd(15);
        }
        item->param3 = rnd(30000);
        if (item->id == "core.small_gamble_chest")
        {
            item->param2 = rnd(rnd(100) + 1) + 1;
            item->value = item->param2 * 25 + 150;
            initnum = rnd(8);
        }
    }

    if (category == ItemCategory::food && item->param1 != 0)
    {
        if (mode == 6)
        {
            if (rnd(2) == 0)
            {
                item->param2 = 0;
            }
            else
            {
                item->param2 = 3 + rnd(3);
            }
        }
        if (item->param2 != 0)
        {
            item->image = picfood(item->param2, item->param1 / 1000);
        }
        if (item->material == "core.raw")
        {
            item->param3 += game_data.date.hours();
        }
    }

    init_item_quality_curse_state_material_and_equipments(item);
    if (category == ItemCategory::furniture)
    {
        if (rnd(3) == 0)
        {
            item->subname = rnd(rnd(12) + 1);
        }
        else
        {
            item->subname = 0;
        }
    }

    if (mode == 6)
    {
        item->identify_state = IdentifyState::completely;
    }
    if (category == ItemCategory::gold_piece ||
        category == ItemCategory::platinum_coin ||
        item->id == "core.small_medal" || item->id == "core.music_ticket" ||
        item->id == "core.token_of_friendship" || item->id == "core.bill")
    {
        item->curse_state = CurseState::none;
        item->identify_state = IdentifyState::completely;
    }
    if (category == ItemCategory::cargo)
    {
        item->identify_state = IdentifyState::completely;
        item->curse_state = CurseState::none;
        itemmemory(0, the_item_db[item->id]->integer_id) = 1;
    }
    if (category == ItemCategory::bodyparts || category == ItemCategory::junk ||
        category == ItemCategory::ore)
    {
        item->curse_state = CurseState::none;
    }
    if (mode != 6)
    {
        if (reftype < 50000)
        {
            if (rnd_capped(cdata.player().get_skill(162).level + 1) > 5)
            {
                item->identify_state = IdentifyState::almost;
            }
        }
    }

    calc_furniture_value(item);

    itemturn(item);

    if (initnum != 0)
    {
        item->set_number(initnum);
    }

    if (nostack == 1)
    {
        nostack = 0;
    }
    else
    {
        auto inv_stack_result = inv_stack(inv, item);
        if (inv_stack_result.stacked)
        {
            return inv_stack_result.stacked_item;
        }
    }

    if (inv_get_owner(inv).is_map())
    {
        cell_refresh(item->position().x, item->position().y);
    }
    return item;
}



void init_item_quality_curse_state_material_and_equipments(const ItemRef& item)
{
    const auto category = the_item_db[item->id]->category;

    if (category < ItemCategory::furniture)
    {
        if (rnd(12) == 0)
        {
            item->curse_state = CurseState::blessed;
        }
        if (rnd(13) == 0)
        {
            item->curse_state = CurseState::cursed;
            if (is_equipment(category))
            {
                if (rnd(4) == 0)
                {
                    item->curse_state = CurseState::doomed;
                }
            }
        }
    }
    if (cm || mode == 1 || item->quality == Quality::special)
    {
        item->curse_state = CurseState::none;
    }
    if (is_equipment(category) ||
        (category == ItemCategory::furniture && rnd(5) == 0))
    {
        if (item->material == "core._light" ||
            item->material == "core._heavy" ||
            category == ItemCategory::furniture)
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
    if (category < ItemCategory::potion)
    {
        add_enchantments(item);
    }
    else if (item->quality != Quality::special)
    {
        item->quality = Quality::good;
    }
}



void calc_furniture_value(const ItemRef& item)
{
    if (the_item_db[item->id]->category == ItemCategory::furniture)
    {
        if (item->subname != 0)
        {
            item->value = item->value * (80 + item->subname * 20) / 100;
        }
    }
}



void initialize_item_material(const ItemRef& item)
{
    determine_item_material(item);
    apply_item_material(item);
}



void determine_item_material(const ItemRef& item)
{
    int mtlv = 0;
    if (cm)
    {
        mtlv = cdata[cm - 1].level / 15 + 1;
    }
    else
    {
        mtlv = rnd((objlv + 1)) / 10 + 1;
    }
    if (item->id == "core.material_kit")
    {
        mtlv = rnd(mtlv + 1);
        if (rnd(3))
        {
            item->material = "core._heavy";
        }
        else
        {
            item->material = "core._light";
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

    if (the_item_db[item->id]->category == ItemCategory::furniture)
    {
        if (rnd(2) == 0)
        {
            item->material = "core._heavy";
        }
        else
        {
            item->material = "core._light";
        }
    }
    if (item->material == "core._heavy")
    {
        if (rnd(10) != 0)
        {
            item->material = item_material_lookup_metal(p, mtlv);
        }
        else
        {
            item->material = item_material_lookup_leather(p, mtlv);
        }
    }
    if (item->material == "core._light")
    {
        if (rnd(10) != 0)
        {
            item->material = item_material_lookup_leather(p, mtlv);
        }
        else
        {
            item->material = item_material_lookup_metal(p, mtlv);
        }
    }
    if (rnd(25) == 0)
    {
        item->material = "core.raw";
    }
}



void change_item_material(const ItemRef& item, data::InstanceId material)
{
    item->tint = 0;

    fixlv = item->quality;
    if (item->material != "")
    {
        for (auto e : the_item_material_db[item->material]->enchantments)
        {
            enchantment_remove(item, e.first, e.second);
        }
    }

    const auto original_value = calculate_original_value(item);

    item_db_set_basic_stats(item, the_item_db[item->id]->integer_id);
    item->value = original_value;
    if (material != "")
    {
        item->material = material;
        fixmaterial = 0;
    }
    else
    {
        determine_item_material(item);
    }
    apply_item_material(item);
    calc_furniture_value(item);
    chara_refresh(cdata.player());
}



void apply_item_material(const ItemRef& item)
{
    const auto category = the_item_db[item->id]->category;
    if (category == ItemCategory::furniture)
    {
        if (item->material == "core.cloth" || item->material == "core.paper" ||
            item->material == "core.mica" || item->material == "core.silk")
        {
            item->material = "core.wood";
        }
    }
    if (item->material == "")
    {
        p = 0;
    }
    else
    {
        p = the_item_material_db[item->material]->integer_id;
    }
    item->weight = item->weight * the_item_material_db[p]->weight / 100;
    if (category == ItemCategory::furniture)
    {
        item->value += the_item_material_db[p]->value * 2;
    }
    else
    {
        item->value = item->value * the_item_material_db[p]->value / 100;
    }
    if (item->tint == 0)
    {
        item->tint = the_item_material_db[p]->tint;
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
    if (item->hit_bonus != 0)
    {
        item->hit_bonus = the_item_material_db[p]->hit_bonus * item->hit_bonus *
            9 / (p(1) - rnd(30));
    }
    if (item->dice.bonus != 0)
    {
        item->dice.bonus = the_item_material_db[p]->damage_bonus *
            item->dice.bonus * 5 / (p(1) - rnd(30));
    }
    if (item->dv != 0)
    {
        item->dv =
            the_item_material_db[p]->dv * item->dv * 7 / (p(1) - rnd(30));
    }
    if (item->pv != 0)
    {
        item->pv =
            the_item_material_db[p]->pv * item->pv * 9 / (p(1) - rnd(30));
    }
    if (item->dice.faces != 0)
    {
        item->dice.faces = item->dice.faces * the_item_material_db[p]->dice_y /
            (p(1) + rnd(25));
    }
    set_material_specific_attributes(item);
}



void set_material_specific_attributes(const ItemRef& item)
{
    if (item->material == "")
        return;

    const auto& material_data = the_item_material_db.ensure(item->material);
    for (auto e : material_data.enchantments)
    {
        enchantment_add(item, e.first, e.second, 0, 1);
    }
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        if (material_data.fireproof)
        {
            item->is_acidproof = true;
        }
        if (material_data.acidproof)
        {
            item->is_fireproof = true;
        }
    }
}



int discsetmc()
{
    return rnd(47);
}

} // namespace elona

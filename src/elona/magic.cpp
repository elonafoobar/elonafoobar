#include <stack>

#include "../util/scope_guard.hpp"
#include "ability.hpp"
#include "activity.hpp"
#include "animation.hpp"
#include "area.hpp"
#include "attack.hpp"
#include "audio.hpp"
#include "buff.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "command.hpp"
#include "config.hpp"
#include "crafting.hpp"
#include "ctrl_file.hpp"
#include "data/types/type_asset.hpp"
#include "data/types/type_buff.hpp"
#include "data/types/type_item.hpp"
#include "debug.hpp"
#include "dmgheal.hpp"
#include "draw.hpp"
#include "element.hpp"
#include "elona.hpp"
#include "enchantment.hpp"
#include "food.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "mef.hpp"
#include "menu.hpp"
#include "message.hpp"
#include "quest.hpp"
#include "random.hpp"
#include "save.hpp"
#include "status_ailment.hpp"
#include "text.hpp"
#include "trait.hpp"
#include "ui.hpp"
#include "variables.hpp"
#include "wish.hpp"



namespace
{

// Eye of Insanity
bool _magic_636(Character& subject, Character& target)
{
    txt(i18n::s.get("core.magic.insanity", subject, target),
        Message::color{ColorIndex::purple});
    damage_insanity(target, rnd_capped(roll(dice1, dice2, bonus) + 1));
    return true;
}



// Item: treasure map
bool _magic_1136(Item& treasure_map)
{
    if (map_data.type != mdata_t::MapType::world_map)
    {
        txt(i18n::s.get("core.magic.map.need_global_map"));
        return true;
    }
    if (is_cursed(efstatus))
    {
        if (rnd(5) == 0)
        {
            txt(i18n::s.get("core.magic.map.cursed"));
            treasure_map.modify_number(-1);
            return true;
        }
    }
    if (treasure_map.param1 == 0)
    {
        item_separate(treasure_map);
        for (int cnt = 0; cnt < 1000; ++cnt)
        {
            dx = 4 + rnd(map_data.width - 8);
            dy = 3 + rnd(map_data.height - 6);
            if (dx >= 50 && dy >= 39 && dx <= 73 && dy <= 54)
            {
                continue;
            }
            x(0) = 1;
            x(1) = -1;
            x(2) = 0;
            x(3) = 0;
            y(0) = 0;
            y(1) = 0;
            y(2) = 1;
            y(3) = -1;
            for (int cnt = 0; cnt < 4; ++cnt)
            {
                f = 1;
                int cnt2 = cnt;
                for (int cnt = 0; cnt < 3; ++cnt)
                {
                    p = cell_data.at(dx + x(cnt2) * cnt, dy + y(cnt2) * cnt)
                            .chip_id_actual;
                    if ((264 <= p && p < 363) || chip_data[p].effect & 4)
                    {
                        f = 0;
                        break;
                    }
                }
                if (f == 1)
                {
                    break;
                }
            }
            if (f == 1)
            {
                break;
            }
        }
        treasure_map.param1 = dx;
        treasure_map.param2 = dy;
    }
    txt(i18n::s.get("core.magic.map.apply"));
    snd("core.book1");
    const auto& info = asset_load("paper");
    gsel(0);
    ww = info.width;
    wh = info.height;
    wx = (windoww - ww) / 2 + inf_screenx;
    wy = winposy(wh);
    gmode(2);
    gcopy(4, 0, 0, ww, wh, wx, wy);
    gmode(0);
    for (int cnt = 0; cnt < 5; ++cnt)
    {
        y = cnt + treasure_map.param2 - 2;
        sy = cnt * inf_tiles + wy + 26;
        for (int cnt = 0; cnt < 7; ++cnt)
        {
            x = cnt + treasure_map.param1 - 3;
            sx = cnt * inf_tiles + wx + 46;
            draw_map_tile(cell_data.at(x, y).chip_id_actual, sx + 1, sy + 1);
            if (x == treasure_map.param1)
            {
                if (y == treasure_map.param2)
                {
                    font(40 - en * 2, snail::Font::Style::italic);
                    mes(sx,
                        sy,
                        i18n::s.get("core.magic.map.mark"),
                        {255, 20, 20});
                }
            }
        }
    }
    gmode(2);
    gcopy(4, 400, 0, ww, wh, wx, wy);
    redraw();
    wait_key_pressed();
    snd("core.card1");
    return true;
}



// Item: love potion
bool _magic_1135(Character& target)
{
    if (is_cursed(efstatus))
    {
        if (target.index == 0)
        {
            food_apply_curse_state(target, efstatus);
        }
        else
        {
            txt(i18n::s.get("core.magic.love_potion.cursed", target));
            chara_modify_impression(target, -15);
        }
        obvious = 0;
        return true;
    }
    target.emotion_icon = 317;
    if (potionspill || potionthrow)
    {
        txt(i18n::s.get("core.magic.love_potion.spill", target));
        chara_modify_impression(target, clamp(efp / 15, 0, 15));
        status_ailment_damage(target, StatusAilment::dimmed, 100);
        lovemiracle(target.index);
        return true;
    }
    if (target.index == 0)
    {
        txt(i18n::s.get("core.magic.love_potion.self", target));
    }
    else
    {
        txt(i18n::s.get("core.magic.love_potion.other", target));
        lovemiracle(target.index);
        chara_modify_impression(target, clamp(efp / 4, 0, 25));
    }
    status_ailment_damage(target, StatusAilment::dimmed, 500);
    return true;
}



// Pregnant
bool _magic_654(Character& subject, Character& target)
{
    if (is_in_fov(target))
    {
        txt(i18n::s.get("core.magic.pregnant", subject, target));
    }
    get_pregnant(target);
    return true;
}



// Mirror
bool _magic_626(Character& target)
{
    txt(i18n::s.get("core.magic.mirror"));
    animeload(10, target);
    screen_analyze_self();
    return true;
}



// Item: milk
bool _magic_1101(Character& subject, Character& target)
{
    if (is_in_fov(target))
    {
        snd("core.atk_elec");
        if (is_cursed(efstatus))
        {
            if (target.index == 0)
            {
                txt(i18n::s.get("core.magic.milk.cursed.self"));
            }
            else
            {
                txt(i18n::s.get("core.magic.milk.cursed.other"),
                    Message::color{ColorIndex::cyan});
            }
        }
        else if (target.index == 0)
        {
            txt(i18n::s.get("core.magic.milk.self"));
        }
        else
        {
            txt(i18n::s.get("core.magic.milk.other"),
                Message::color{ColorIndex::cyan});
        }
    }
    if (efstatus == CurseState::blessed)
    {
        modify_height(target, rnd(5) + 1);
    }
    if (is_cursed(efstatus))
    {
        modify_height(target, (rnd(5) + 1) * -1);
    }
    target.nutrition += 1000 * (efp / 100);
    if (target.index == 0)
    {
        show_eating_message(subject);
    }
    food_apply_curse_state(target, efstatus);
    animeload(15, target);
    return true;
}



// Item: alcohol
bool _magic_1102(Character& target)
{
    if (is_in_fov(target))
    {
        if (is_cursed(efstatus))
        {
            txt(i18n::s.get("core.magic.alcohol.cursed"),
                Message::color{ColorIndex::cyan});
        }
        else
        {
            txt(i18n::s.get("core.magic.alcohol.normal"),
                Message::color{ColorIndex::cyan});
        }
    }
    status_ailment_damage(target, StatusAilment::drunk, efp);
    food_apply_curse_state(target, efstatus);
    return true;
}



// Item: acid
bool _magic_1116(Character& target)
{
    if (is_in_fov(target))
    {
        if (target.index == 0)
        {
            txt(i18n::s.get("core.magic.acid.self"));
        }
        txt(i18n::s.get("core.magic.acid.apply", target));
    }
    if (target.is_pregnant())
    {
        target.is_pregnant() = false;
        if (is_in_fov(target))
        {
            txt(i18n::s.get("core.magic.common.melts_alien_children", target));
        }
    }
    damage_hp(
        target, efp * efstatusfix(500, 400, 100, 50) / 1000, -15, 63, efp);
    return true;
}



// Item: water
bool _magic_1103(Character& target)
{
    if (is_in_fov(target))
    {
        if (target.index == 0)
        {
            txt(i18n::s.get("core.magic.water.self"));
        }
        else
        {
            txt(i18n::s.get("core.magic.water.other"));
        }
    }
    get_sick_if_cursed(efstatus, target);
    return true;
}



// Item: soda
bool _magic_1146(Character& target)
{
    if (is_in_fov(target))
    {
        txt(i18n::s.get("core.magic.restore_stamina.dialog"));
        txt(i18n::s.get("core.magic.restore_stamina.apply", target));
    }
    heal_sp(target, 25);
    get_sick_if_cursed(efstatus, target);
    return true;
}



// Item: blue capsule drug
bool _magic_1147(Character& target)
{
    if (is_in_fov(target))
    {
        txt(i18n::s.get("core.magic.restore_stamina_greater.dialog"));
        txt(i18n::s.get("core.magic.restore_stamina_greater.apply", target));
    }
    heal_sp(target, 100);
    get_sick_if_cursed(efstatus, target);
    return true;
}



// Item: salt solution
bool _magic_1142(Character& target)
{
    if (target.race == "core.snail")
    {
        if (is_in_fov(target))
        {
            txt(i18n::s.get("core.magic.salt.snail", target),
                Message::color{ColorIndex::red});
        }
        if (target.hp > 10)
        {
            damage_hp(target, target.hp - rnd(10), -15);
        }
        else
        {
            damage_hp(target, rnd(20000), -15);
        }
    }
    else if (is_in_fov(target))
    {
        txt(i18n::s.get("core.magic.salt.apply"),
            Message::color{ColorIndex::cyan});
    }
    return true;
}



// Item: dirty water
bool _magic_1130(Character& target)
{
    if (is_in_fov(target))
    {
        if (target.index == 0)
        {
            txt(i18n::s.get("core.magic.dirty_water.self"));
        }
        else
        {
            txt(i18n::s.get("core.magic.dirty_water.other"));
        }
    }
    get_sick_if_cursed(efstatus, target);
    return true;
}



// Pickpocket
bool _magic_300(Character& subject, Character& target)
{
    if (game_data.executing_immediate_quest_type == 1008 ||
        game_data.executing_immediate_quest_type == 1010)
    {
        txt(i18n::s.get("core.magic.steal.in_quest"));
        return false;
    }
    if (subject.index == 0)
    {
        if (cdata.player().sp < 50)
        {
            if (cdata.player().sp < rnd(75))
            {
                txt(i18n::s.get("core.magic.common.too_exhausted"));
                damage_sp(cdata.player(), the_ability_db[efid]->cost / 2 + 1);
                return true;
            }
        }
        damage_sp(
            cdata.player(),
            rnd(the_ability_db[efid]->cost / 2 + 1) +
                the_ability_db[efid]->cost / 2 + 1);
    }
    invsubroutine = 1;
    invctrl(0) = 27;
    invctrl(1) = 0;
    snd("core.inv");
    // In Pickpocket spact, target == player means that you attempts to steal
    // items on the ground, not in someone's inventory.
    ctrl_inventory(
        target.index == 0 ? optional_ref<Character>{}
                          : optional_ref<Character>{target});
    return true;
}



// Riding
bool _magic_301(Character& subject, Character& target)
{
    if (subject.index == 0)
    {
        if (cdata.player().sp < 50)
        {
            if (cdata.player().sp < rnd(75))
            {
                txt(i18n::s.get("core.magic.common.too_exhausted"));
                damage_sp(cdata.player(), the_ability_db[efid]->cost / 2 + 1);
                return true;
            }
        }
        damage_sp(
            cdata.player(),
            rnd(the_ability_db[efid]->cost / 2 + 1) +
                the_ability_db[efid]->cost / 2 + 1);
    }
    if (game_data.mount != 0)
    {
        if (target.index == subject.index)
        {
            int stat = cell_findspace(
                cdata.player().position.x, cdata.player().position.y, 1);
            if (stat == 0)
            {
                txt(i18n::s.get("core.magic.mount.no_place_to_get_off"));
                return true;
            }
            cell_setchara(game_data.mount, rtval, rtval(1));
            txt(i18n::s.get(
                "core.magic.mount.dismount", cdata[game_data.mount]));
            txt(name(game_data.mount) +
                    i18n::s.get("core.magic.mount.dismount_dialog"),
                Message::color{ColorIndex::cyan});
            ride_end();
            return true;
        }
    }
    if (target.index >= 16)
    {
        txt(i18n::s.get("core.magic.mount.only_ally"));
        return true;
    }
    if (target.is_escorted() == 1 || target.is_escorted_in_sub_quest() == 1)
    {
        txt(i18n::s.get("core.magic.mount.not_client"));
        return true;
    }
    if (target.index == subject.index)
    {
        if (game_data.mount == 0)
        {
            txt(i18n::s.get("core.magic.mount.ride_self", subject));
        }
        return true;
    }
    if (target.current_map != 0)
    {
        txt(i18n::s.get("core.magic.mount.stays_in_area"));
        return true;
    }
    if (game_data.mount != 0)
    {
        txt(i18n::s.get(
            "core.magic.mount.currently_riding",
            subject,
            cdata[game_data.mount]));
    }
    else
    {
        ride_begin(target.index);
        txt(name(game_data.mount) + i18n::space_if_needed() +
                i18n::s.get("core.magic.mount.mount.dialog"),
            Message::color{ColorIndex::cyan});
    }
    return true;
}



// Performance
bool _magic_183(Character& subject, OptionalItemRef instrument)
{
    assert(subject.index != 0 || instrument);

    if (subject.index != 0)
    {
        for (const auto& item : g_inv.for_chara(subject))
        {
            if (item->skill == 183)
            {
                instrument = item.clone();
                break;
            }
        }
        if (!instrument)
        {
            return false;
        }
    }
    if (sdata(183, subject.index) == 0)
    {
        if (is_in_fov(subject))
        {
            txt(i18n::s.get("core.magic.perform.do_not_know", subject));
            return false;
        }
    }
    if (subject.index == 0)
    {
        if (cdata.player().sp < 50)
        {
            if (cdata.player().sp < rnd(75))
            {
                txt(i18n::s.get("core.magic.common.too_exhausted"));
                damage_sp(cdata.player(), the_ability_db[efid]->cost / 2 + 1);
                return true;
            }
        }
        damage_sp(
            cdata.player(),
            rnd(the_ability_db[efid]->cost / 2 + 1) +
                the_ability_db[efid]->cost / 2 + 1);
    }
    activity_perform(subject, *instrument);
    return true;
}



// Cooking
bool _magic_184(Character& subject, Item& cook_tool)
{
    if (sdata(184, 0) == 0)
    {
        txt(i18n::s.get("core.magic.cook.do_not_know"));
        return false;
    }
    invsubroutine = 1;
    invctrl = 16;
    snd("core.inv");
    const auto& [menu_result, food_opt] = ctrl_inventory();
    if (!menu_result.succeeded)
    {
        return false;
    }
    assert(food_opt);
    auto& food = *food_opt;
    if (subject.index == 0)
    {
        if (cdata.player().sp < 50)
        {
            if (cdata.player().sp < rnd(75))
            {
                txt(i18n::s.get("core.magic.common.too_exhausted"));
                damage_sp(cdata.player(), the_ability_db[efid]->cost / 2 + 1);
                return true;
            }
        }
        damage_sp(
            cdata.player(),
            rnd(the_ability_db[efid]->cost / 2 + 1) +
                the_ability_db[efid]->cost / 2 + 1);
    }
    food_cook(subject, cook_tool, food);
    return true;
}



// Fishing
bool _magic_185(Character& subject, Item& rod)
{
    if (sdata(185, 0) == 0)
    {
        txt(i18n::s.get("core.magic.fish.do_not_know"));
        return false;
    }
    if (!inv_getspace(0))
    {
        txt(i18n::s.get("core.ui.inv.common.inventory_is_full"));
        return false;
    }
    if (rod.count == 0)
    {
        txt(i18n::s.get("core.magic.fish.need_bait"));
        return false;
    }
    f = 0;
    for (int cnt = 0; cnt < 3; ++cnt)
    {
        y = subject.position.y + cnt - 1;
        x = subject.position.x;
        if (x < 0 || y < 0 || x >= map_data.width || y >= map_data.height)
        {
            continue;
        }
        if (chip_data.for_cell(x, y).kind == 3)
        {
            f = 1;
            break;
        }
    }
    if (f == 0)
    {
        for (int cnt = 0; cnt < 3; ++cnt)
        {
            y = subject.position.y;
            x = subject.position.x + cnt - 1;
            if (x < 0 || y < 0 || x >= map_data.width || y >= map_data.height)
            {
                continue;
            }
            if (chip_data.for_cell(x, y).kind == 3)
            {
                f = 1;
                break;
            }
        }
    }
    if (f == 0)
    {
        txt(i18n::s.get("core.magic.fish.not_good_place"),
            Message::only_once{true});
        update_screen();
        return false;
    }
    if (chip_data.for_cell(cdata.player().position.x, cdata.player().position.y)
            .kind == 3)
    {
        txt(i18n::s.get("core.magic.fish.cannot_during_swim"));
        update_screen();
        return false;
    }
    if (cdata.player().position.x - x > 0)
    {
        cdata.player().direction = 1;
    }
    if (cdata.player().position.x - x < 0)
    {
        cdata.player().direction = 2;
    }
    if (cdata.player().position.y - y > 0)
    {
        cdata.player().direction = 3;
    }
    if (cdata.player().position.y - y < 0)
    {
        cdata.player().direction = 0;
    }
    game_data.player_next_move_direction = cdata.player().direction;
    fishx = x;
    fishy = y;
    addefmap(fishx, fishy, 1, 3);
    if (subject.index == 0)
    {
        if (cdata.player().sp < 50)
        {
            if (cdata.player().sp < rnd(75))
            {
                txt(i18n::s.get("core.magic.common.too_exhausted"));
                damage_sp(cdata.player(), the_ability_db[efid]->cost / 2 + 1);
                return true;
            }
        }
        damage_sp(
            cdata.player(),
            rnd(the_ability_db[efid]->cost / 2 + 1) +
                the_ability_db[efid]->cost / 2 + 1);
    }
    item_separate(rod);
    --rod.count;
    rowactre = 0;
    spot_fishing(subject, OptionalItemRef{&rod});
    return true;
}



bool _magic_645_1114(Character&, Character&);

// Holy Light / Vanquish Hex
bool _magic_406_407(Character& subject, Character& target)
{
    if (is_cursed(efstatus))
    {
        if (is_in_fov(target))
        {
            txt(i18n::s.get("core.magic.common.cursed", target));
        }
        return _magic_645_1114(subject, target);
    }
    p = 0;
    for (int cnt = 0; cnt < 16; ++cnt)
    {
        i = 16 - cnt - 1;
        if (efid == 406)
        {
            if (p >= 1)
            {
                break;
            }
        }
        if (target.buffs[i].id == 0)
        {
            continue;
        }
        if (target.buffs[i].id == 13)
        {
            continue;
        }
        if (the_buff_db[target.buffs[i].id]->type != BuffType::hex)
        {
            continue;
        }
        if (rnd_capped(efp * 2 + 1) > rnd_capped(target.buffs[i].power + 1))
        {
            buff_delete(target, i);
            ++p;
            --cnt;
            continue;
        }
    }
    buff_add(target, "core.holy_veil", efp, 5 + efp / 30, subject);
    animeload(11, target);
    return true;
}



// Prayer
bool _magic_1120(Character& target)
{
    txt(i18n::s.get("core.magic.prayer", target),
        Message::color{ColorIndex::orange});
    heal_completely(target);
    BrightAuraAnimation(target.position, BrightAuraAnimation::Type::healing)
        .play();
    return true;
}



// Random craft material
bool _magic_1117(Character& target)
{
    if (target.index >= 16)
    {
        txt(i18n::s.get("core.common.nothing_happens"));
        obvious = 0;
        return true;
    }
    if (!is_cursed(efstatus))
    {
        s = i18n::s.get("core.magic.create_material.materials");
    }
    else
    {
        s = i18n::s.get("core.magic.create_material.junks");
    }
    snd("core.ding2");
    txt(i18n::s.get("core.magic.create_material.apply", s(0)));
    save_set_autosave();
    for (int cnt = 0,
             cnt_end = (rnd(3) + 3 + (efstatus == CurseState::blessed) * 6);
         cnt < cnt_end;
         ++cnt)
    {
        atxspot = 19;
        if (!is_cursed(efstatus))
        {
            p = random_material(efp / 10, efp / 50);
        }
        else
        {
            p = 0;
        }
        matgetmain(p, 1);
    }
    return true;
}



bool _magic_628(Character& subject, Character& target);

// Eye of Mutation / Mutation
bool _magic_632_454_1144(
    Character& subject,
    Character& target,
    bool is_cursed_potion_of_cure_mutation = false)
{
    if (!is_cursed_potion_of_cure_mutation)
    {
        if (target.index != 0)
        {
            return _magic_628(subject, target);
        }
        if (efid == 632)
        {
            txt(i18n::s.get("core.magic.mutation.spell", subject, target));
            if (rnd(3))
            {
                return true;
            }
        }
        if (target.index != 0)
        {
            txt(i18n::s.get("core.common.nothing_happens"));
            return true;
        }
        if (enchantment_find(target, 33))
        {
            if (rnd(5))
            {
                txt(i18n::s.get("core.magic.mutation.resist"));
                return true;
            }
        }
    }

    f = 0;
    p = 1;
    if (efid == 1144)
    {
        p = 2 + rnd(3);
    }
    for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
    {
        for (int cnt = 0; cnt < 100; ++cnt)
        {
            int tid = rnd(45);
            int stat = trait_get_info(0, tid);
            if (stat == 0 || traitref != 1)
            {
                continue;
            }
            if (rnd(2))
            {
                p = 1;
            }
            else
            {
                p = -1;
            }
            if (trait(tid) >= traitref(2))
            {
                p = -1;
            }
            if (trait(tid) <= traitref(1))
            {
                p = 1;
            }
            if (is_cursed(efstatus))
            {
                if (p == 1)
                {
                    continue;
                }
            }
            else if (p == -1)
            {
                if (efstatus == CurseState::blessed)
                {
                    if (rnd(3) == 0)
                    {
                        continue;
                    }
                }
                if (efid == 1144)
                {
                    continue;
                }
            }
            trait(tid) += p;
            txt(i18n::s.get("core.magic.mutation.apply"));
            if (p > 0)
            {
                txt(traitrefn(0), Message::color{ColorIndex::green});
            }
            else
            {
                txt(traitrefn(1), Message::color{ColorIndex::red});
            }
            animeload(8, cdata.player());
            f = 1;
            break;
        }
    }
    if (f == 0)
    {
        txt(i18n::s.get("core.common.nothing_happens"));
        obvious = 0;
    }
    chara_refresh(cdata.player());
    return true;
}



// Item: potion of cure mutation
bool _magic_1121(Character& subject, Character& target)
{
    if (target.index != 0)
    {
        txt(i18n::s.get("core.common.nothing_happens"));
        return true;
    }
    if (is_cursed(efstatus))
    {
        if (is_in_fov(target))
        {
            txt(i18n::s.get("core.magic.common.it_is_cursed"));
        }
        return _magic_632_454_1144(subject, target, true);
    }
    f = 0;
    for (int cnt = 0,
             cnt_end = cnt +
             (1 + (efstatus == CurseState::blessed) + (!is_cursed(efstatus)) +
              rnd(2));
         cnt < cnt_end;
         ++cnt)
    {
        for (int cnt = 0; cnt < 100; ++cnt)
        {
            int tid = rnd(217);
            int stat = trait_get_info(0, tid);
            if (stat == 0 || traitref != 1)
            {
                continue;
            }
            if (trait(tid) == 0)
            {
                continue;
            }
            if (trait(tid) > 0)
            {
                p = -1;
            }
            if (trait(tid) < 0)
            {
                p = 1;
            }
            trait(tid) = 0;
            txt(i18n::s.get("core.magic.cure_mutation"));
            if (p > 0)
            {
                txt(traitrefn(0), Message::color{ColorIndex::green});
            }
            else
            {
                txt(traitrefn(1), Message::color{ColorIndex::red});
            }
            f = 1;
            break;
        }
    }
    if (f == 0)
    {
        txt(i18n::s.get("core.common.nothing_happens"));
        obvious = 0;
    }
    chara_refresh(cdata.player());
    return true;
}



// Identify
bool _magic_411(Character& subject)
{
    if (subject.index != 0)
    {
        txt(i18n::s.get("core.common.nothing_happens"));
        obvious = 0;
        return true;
    }
    invsubroutine = 1;
    invctrl = 13;
    snd("core.inv");
    ctrl_inventory();
    return true;
}



// Resurrection
bool _magic_461(Character& subject)
{
    if (map_data.type == mdata_t::MapType::world_map)
    {
        txt(i18n::s.get("core.common.nothing_happens"));
        obvious = 0;
        return true;
    }
    if (is_cursed(efstatus))
    {
        txt(i18n::s.get("core.magic.resurrection.cursed"));
        for (int cnt = 0, cnt_end = (4 + rnd(4)); cnt < cnt_end; ++cnt)
        {
            flt(calcobjlv(cdata.player().level), calcfixlv(Quality::good));
            fltn(u8"undead"s);
            chara_create(
                -1, 0, cdata.player().position.x, cdata.player().position.y);
        }
        obvious = 0;
        return true;
    }
    int stat = show_hire_menu(HireOperation::revive);
    if (stat == -1)
    {
        txt(i18n::s.get("core.common.nothing_happens"));
        obvious = 0;
        return true;
    }
    if (bonus < rnd(100))
    {
        if (is_in_fov(subject))
        {
            txt(i18n::s.get("core.magic.resurrection.fail", subject));
        }
        return true;
    }
    do_chara_revival(cdata[stat]);
    cxinit = subject.position.x;
    cyinit = subject.position.y;
    chara_place(cdata[stat]);
    cdata[stat].current_map = 0;
    txt(i18n::s.get(
            "core.magic.resurrection.apply",
            cnven(cdata[stat].name),
            cdata[stat]),
        Message::color{ColorIndex::orange});
    txt(i18n::s.get("core.magic.resurrection.dialog"));
    MiracleAnimation(MiracleAnimation::Mode::target_one, cdata[stat]).play();
    snd("core.pray2");
    cdata[stat].emotion_icon = 317;
    if (subject.index == 0)
    {
        chara_modify_impression(cdata[stat], 15);
        if (stat >= 16)
        {
            modify_karma(cdata.player(), 2);
        }
    }
    return true;
}



bool _magic_645_1114(Character&, Character&);

// Uncurse
bool _magic_412(Character& subject, Character& target)
{
    if (efstatus == CurseState::none)
    {
        if (is_in_fov(target))
        {
            txt(i18n::s.get("core.magic.uncurse.apply", target));
        }
    }
    if (efstatus == CurseState::blessed)
    {
        if (is_in_fov(target))
        {
            txt(i18n::s.get("core.magic.uncurse.blessed", target));
        }
    }
    if (is_cursed(efstatus))
    {
        if (is_in_fov(target))
        {
            txt(i18n::s.get("core.magic.common.cursed", target));
        }
        return _magic_645_1114(subject, target);
    }
    p(1) = 0;
    p(2) = 0;
    for (const auto& item : g_inv.for_chara(target))
    {
        if (!is_cursed(item->curse_state))
        {
            continue;
        }
        p = 0;
        if (item->curse_state == CurseState::cursed)
        {
            p = rnd(200) + 1;
        }
        if (item->curse_state == CurseState::doomed)
        {
            p = rnd(1000) + 1;
        }
        if (efstatus == CurseState::blessed)
        {
            p = p / 2 + 1;
        }
        else if (item->body_part == 0)
        {
            continue;
        }
        if (p != 0)
        {
            if (efp >= p)
            {
                ++p(1);
                item->curse_state = CurseState::none;
                item_stack(target.index, *item, true);
            }
            else
            {
                ++p(2);
            }
        }
    }
    if (efstatus == CurseState::blessed)
    {
        if (p(1) != 0)
        {
            if (is_in_fov(target))
            {
                txt(i18n::s.get("core.magic.uncurse.item", target));
            }
        }
    }
    else if (p(1) != 0)
    {
        if (is_in_fov(target))
        {
            txt(i18n::s.get("core.magic.uncurse.equipment", target));
        }
    }
    if (p(2) != 0)
    {
        if (is_in_fov(target))
        {
            txt(i18n::s.get("core.magic.uncurse.resist"));
        }
    }
    if (p(1) == 0 && p(2) == 0)
    {
        txt(i18n::s.get("core.common.nothing_happens"));
        obvious = 0;
    }
    else
    {
        animeload(10, target);
    }
    chara_refresh(target);
    return true;
}



// Oracle
bool _magic_413(Character& target)
{
    if (target.index >= 16)
    {
        txt(i18n::s.get("core.common.nothing_happens"));
        return true;
    }
    if (is_cursed(efstatus))
    {
        artifactlocation.clear();
        txt(i18n::s.get("core.magic.oracle.cursed"));
        return true;
    }
    if (artifactlocation.empty())
    {
        txt(i18n::s.get("core.magic.oracle.no_artifacts"));
    }
    else
    {
        range::for_each(
            artifactlocation, [](const auto& line) { txt(cnven(line)); });
        artifactlocation.clear();
    }
    return true;
}



// Gain spell stock
bool _magic_1104(Character& target)
{
    if (target.index != 0)
    {
        txt(i18n::s.get("core.common.nothing_happens"));
        obvious = 0;
        return true;
    }
    f = 0;
    for (int cnt = 0, cnt_end = (1 + (efstatus == CurseState::blessed));
         cnt < cnt_end;
         ++cnt)
    {
        int cnt2 = cnt;
        for (int cnt = 0; cnt < 2000; ++cnt)
        {
            p = rnd(67) + 400;
            if (p == 441)
            {
                if (rnd(10))
                {
                    continue;
                }
            }
            if (!is_cursed(efstatus))
            {
                if (the_ability_db[p])
                {
                    if (cnt2 == 0)
                    {
                        s = i18n::s.get("core.magic.gain_knowledge.suddenly");
                    }
                    else
                    {
                        s = i18n::s.get(
                            "core.magic.gain_knowledge.furthermore");
                    }
                    chara_gain_skill(cdata.player(), p, 1, 200);
                    txt(s +
                            i18n::s.get(
                                "core.magic.gain_knowledge.gain",
                                the_ability_db.get_text(p, "name")),
                        Message::color{ColorIndex::green});
                    snd("core.ding2");
                    f = 1;
                    break;
                }
            }
            else
            {
                p = p - 400;
                if (spell(p) > 0)
                {
                    spell(p) = 0;
                    txt(i18n::s.get("core.magic.common.it_is_cursed"));
                    txt(i18n::s.get(
                            "core.magic.gain_knowledge.lose",
                            the_ability_db.get_text(p + 400, "name")),
                        Message::color{ColorIndex::red});
                    snd("core.curse3");
                    animeload(14, cdata.player());
                    f = 1;
                    break;
                }
            }
        }
    }
    if (f == 0)
    {
        txt(i18n::s.get("core.common.nothing_happens"));
        obvious = 0;
        return true;
    }
    save_set_autosave();
    return true;
}



// Item: potion of descent
bool _magic_1143(Character& target)
{
    if (efstatus == CurseState::blessed)
    {
        target.experience = target.required_experience;
        r2 = 0;
        gain_level(target);
        if (is_in_fov(target))
        {
            snd("core.ding1");
        }
    }
    else
    {
        if (target.level <= 1)
        {
            txt(i18n::s.get("core.common.nothing_happens"));
            obvious = 0;
            return true;
        }
        --target.level;
        target.experience = 0;
        update_required_experience(target);
        txt(i18n::s.get("core.magic.descent", target),
            Message::color{ColorIndex::purple});
    }
    if (is_cursed(efstatus))
    {
        txt(i18n::s.get("core.magic.common.it_is_cursed"));
        for (int cnt = 10; cnt < 50; ++cnt)
        {
            if (rnd(3) == 0)
            {
                if (cnt <= 17)
                {
                    if (sdata(cnt, target.index) != 0)
                    {
                        chara_gain_skill_exp(target, cnt, -1000);
                    }
                }
            }
        }
        animeload(8, target);
    }
    chara_refresh(target);
    return true;
}



// Item: scroll of gain attribute
bool _magic_1105(Character& target)
{
    for (int cnt = 0;; ++cnt)
    {
        p = rnd(300) + 100;
        if (the_ability_db[p])
        {
            if (!is_cursed(efstatus))
            {
                if (cnt < efstatusfix(0, 0, 100, 2000))
                {
                    if (sdata(p, target.index) != 0)
                    {
                        continue;
                    }
                }
                chara_gain_skill(target, p, 1);
                if (is_in_fov(target))
                {
                    snd("core.ding2");
                    txt(i18n::s.get(
                            "core.magic.gain_skill",
                            target,
                            the_ability_db.get_text(p, "name")),
                        Message::color{ColorIndex::green});
                }
                break;
            }
            else
            {
                if (sdata(p, target.index) == 0)
                {
                    continue;
                }
                if (is_in_fov(target))
                {
                    snd("core.curse1");
                    txt(i18n::s.get("core.magic.common.it_is_cursed"));
                }
                chara_gain_skill_exp(target, p, -1000);
                break;
            }
        }
    }
    chara_refresh(target);
    save_set_autosave();
    return true;
}



// Item: scroll of faith
bool _magic_1107(Character& target)
{
    if (target.index != 0)
    {
        txt(i18n::s.get("core.common.nothing_happens"));
        obvious = 0;
        return true;
    }
    if (cdata.player().god_id == core_god::eyth)
    {
        txt(i18n::s.get("core.common.nothing_happens"));
        obvious = 0;
        return true;
    }
    if (is_cursed(efstatus))
    {
        txt(i18n::s.get("core.magic.faith.doubt"));
        snd("core.curse3");
        animeload(14, cdata.player());
        chara_gain_skill_exp(cdata.player(), 181, -1000);
        return true;
    }
    txt(i18n::s.get("core.magic.faith.apply", god_name(cdata.player().god_id)),
        Message::color{ColorIndex::green});
    if (efstatus == CurseState::blessed)
    {
        txt(i18n::s.get("core.magic.faith.blessed"));
    }
    MiracleAnimation(MiracleAnimation::Mode::target_one, target).play();
    snd("core.pray2");
    cdata.player().praying_point += 500;
    god_modify_piety(75);
    chara_gain_skill_exp(
        cdata.player(),
        181,
        1000 + (efstatus == CurseState::blessed) * 750,
        6,
        1000);
    chara_refresh(target);
    return true;
}



// Item: scroll of growth
bool _magic_1119(Character& target)
{
    for (int cnt = 0, cnt_end = (1 + (efstatus == CurseState::blessed));
         cnt < cnt_end;
         ++cnt)
    {
        int cnt2 = cnt;
        while (1)
        {
            p = rnd(300) + 100;
            if (the_ability_db[p])
            {
                if (sdata.get(p, target.index).original_level == 0)
                {
                    continue;
                }
                modify_potential(
                    target, p, efp * efstatusfix(-4, -2, 5, 5) / 100);
                if (cnt2 == 0)
                {
                    s = i18n::s.get("core.magic.gain_skill_potential.the");
                }
                else
                {
                    s = i18n::s.get(
                        "core.magic.gain_skill_potential.furthermore_the");
                }
                if (!is_cursed(efstatus))
                {
                    if (is_in_fov(target))
                    {
                        snd("core.ding2");
                        txt(s +
                                i18n::s.get(
                                    "core.magic.gain_skill_potential.increases",
                                    target,
                                    the_ability_db.get_text(p, "name")),
                            Message::color{ColorIndex::green});
                    }
                }
                else if (is_in_fov(target))
                {
                    snd("core.curse3");
                    txt(i18n::s.get(
                            "core.magic.gain_skill_potential.decreases",
                            target,
                            the_ability_db.get_text(p, "name")),
                        Message::color{ColorIndex::red});
                }
                break;
            }
        }
    }
    chara_refresh(target);
    save_set_autosave();
    return true;
}



// Lose stats' experience
bool _magic_1106(Character& target)
{
    i = rnd(10) + 10;
    chara_gain_skill_exp(target, i, efstatusfix(-2000, -2000, -1000, -250));
    BrightAuraAnimation(target.position, BrightAuraAnimation::Type::debuff)
        .play();
    chara_refresh(target);
    return true;
}



// Item: troll blood
bool _magic_1139(Character& target)
{
    txt(i18n::s.get("core.magic.troll_blood.apply", target));
    chara_gain_skill_exp(target, 18, efstatusfix(-4000, -1000, 8000, 12000));
    if (efstatus == CurseState::blessed)
    {
        modify_potential(target, 18, 15);
        txt(i18n::s.get("core.magic.troll_blood.blessed"),
            Message::color{ColorIndex::green});
    }
    chara_refresh(target);
    return true;
}



// Gain stats' potential
bool _magic_1113(Character& target)
{
    if (efstatus == CurseState::blessed)
    {
        for (int cnt = 10; cnt < 18; ++cnt)
        {
            modify_potential(
                target,
                cnt,
                rnd(sdata.get(cnt, target.index).potential / 20 + 3) + 1);
        }
        txt(i18n::s.get("core.magic.gain_potential.blessed", target));
        MiracleAnimation(MiracleAnimation::Mode::target_one, target).play();
        snd("core.ding3");
    }
    else
    {
        i = rnd(8) + 10;
        const auto valn = the_ability_db.get_text(i, "name");
        if (efstatus == CurseState::none)
        {
            txt(i18n::s.get(
                "core.magic.gain_potential.increases", target, valn));
            modify_potential(
                target,
                i,
                rnd(sdata.get(i, target.index).potential / 10 + 10) + 1);
            snd("core.ding2");
        }
        else
        {
            txt(i18n::s.get(
                "core.magic.gain_potential.decreases", target, valn));
            modify_potential(
                target,
                i,
                (rnd(sdata.get(i, target.index).potential / 10 + 10) + 1) * -1);
            snd("core.curse3");
        }
    }
    if (target.index == 0)
    {
        save_set_autosave();
    }
    return true;
}



// Vanish
bool _magic_653(Character& target)
{
    if (target.index < 57)
    {
        return true;
    }
    if (target.quality >= Quality::miracle)
    {
        return true;
    }
    txt(i18n::s.get("core.magic.vanish", target));
    chara_vanquish(target);
    quest_check();
    return true;
}



// Sense Object / Magic Map
bool _magic_430_429(Character& target)
{
    if (target.index >= 16)
    {
        txt(i18n::s.get("core.common.nothing_happens"));
        obvious = 0;
        return true;
    }
    p = 1;
    if (efid == 430)
    {
        p = 2;
    }
    for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
    {
        for (int cnt = 0, cnt_end = (map_data.height); cnt < cnt_end; ++cnt)
        {
            y = cnt;
            for (int cnt = 0, cnt_end = (map_data.width); cnt < cnt_end; ++cnt)
            {
                x = cnt;
                p = dist(target.position.x, target.position.y, x, y);
                if (is_cursed(efstatus))
                {
                    if (efid == 429)
                    {
                        cell_data.at(x, y).chip_id_memory = tile_default;
                    }
                    if (efid == 430)
                    {
                        cell_data.at(x, y).item_info_memory.clear();
                    }
                    continue;
                }
                if (p < 7 || rnd_capped(efp + 1) > rnd(p * 8 + 1) ||
                    efstatus == CurseState::blessed)
                {
                    if (efid == 429)
                    {
                        cell_data.at(x, y).chip_id_memory =
                            cell_data.at(x, y).chip_id_actual;
                    }
                    if (efid == 430)
                    {
                        if (cell_data.at(x, y).feats != 0 ||
                            !cell_data.at(x, y).item_info_memory.is_empty())
                        {
                            cell_data.at(x, y).chip_id_memory =
                                cell_data.at(x, y).chip_id_actual;
                        }
                    }
                }
            }
        }
    }
    if (is_cursed(efstatus))
    {
        txt(i18n::s.get("core.magic.sense.cursed"));
    }
    else
    {
        if (efid == 429)
        {
            txt(i18n::s.get("core.magic.sense.magic_mapping", target));
        }
        if (efid == 430)
        {
            txt(i18n::s.get("core.magic.sense.sense_object", target));
        }
    }
    animeload(10, target);
    update_minimap();
    update_screen();
    return true;
}



// Decapitation
bool _magic_658(Character& subject, Character& target)
{
    if (target.hp > target.max_hp / 8)
    {
        return true;
    }
    if (is_in_fov(target))
    {
        snd("core.atksword");
        txt(i18n::s.get("core.magic.vorpal.sound"),
            Message::color{ColorIndex::red});
        if (target.index >= 16)
        {
            game_data.proc_damage_events_flag = 2;
            txt3rd = 1;
            txt(i18n::s.get("core.magic.vorpal.other", subject, target));
        }
        else
        {
            txt(i18n::s.get("core.magic.vorpal.ally", subject, target));
        }
    }
    damage_hp(target, target.max_hp, subject.index, 658);
    return true;
}



// Restore Spirit / Restore Body
bool _magic_440_439(Character& target)
{
    if (efid == 439)
    {
        if (is_in_fov(target))
        {
            if (is_cursed(efstatus))
            {
                snd("core.curse3");
                txt(i18n::s.get("core.magic.restore.body.cursed", target));
            }
            else
            {
                txt(i18n::s.get("core.magic.restore.body.apply", target));
                animeload(10, target);
            }
            if (efstatus == CurseState::blessed)
            {
                txt(i18n::s.get("core.magic.restore.body.blessed", target));
                animeload(10, target);
            }
        }
        p(0) = 10;
        p(1) = 11;
        p(2) = 12;
        p(3) = 17;
        p(4) = 18;
        p(5) = -1;
    }
    if (efid == 440)
    {
        if (is_in_fov(target))
        {
            if (is_cursed(efstatus))
            {
                snd("core.curse3");
                txt(i18n::s.get("core.magic.restore.mind.cursed", target));
            }
            else
            {
                txt(i18n::s.get("core.magic.restore.mind.apply", target));
                animeload(10, target);
            }
            if (efstatus == CurseState::blessed)
            {
                txt(i18n::s.get("core.magic.restore.mind.blessed", target));
                animeload(10, target);
            }
        }
        p(0) = 14;
        p(1) = 13;
        p(2) = 16;
        p(3) = 15;
        p(4) = 19;
        p(5) = -1;
    }
    for (int cnt = 0;; ++cnt)
    {
        if (p(cnt) == -1)
        {
            break;
        }
        const auto attr = p(cnt) - 10;
        if (is_cursed(efstatus))
        {
            if (target.quality <= Quality::great)
            {
                target.attr_adjs[attr] -=
                    rnd(sdata.get(p(cnt), target.index).original_level) / 5 +
                    rnd(5);
                continue;
            }
        }
        if (target.attr_adjs[attr] < 0)
        {
            target.attr_adjs[attr] = 0;
        }
        if (efstatus == CurseState::blessed)
        {
            target.attr_adjs[attr] =
                sdata.get(p(cnt), target.index).original_level / 10 + 5;
        }
    }
    chara_refresh(target);
    return true;
}



// Wish
bool _magic_441(Character& subject)
{
    what_do_you_wish_for(subject);
    screenupdate = -1;
    gmode(2);
    update_screen();
    return true;
}



// Item: scroll of escape
bool _magic_1141(Character& target)
{
    if (target.index != 0)
    {
        txt(i18n::s.get("core.common.nothing_happens"));
        obvious = 0;
        return true;
    }
    if (game_data.is_returning_or_escaping != 0)
    {
        txt(i18n::s.get("core.magic.escape.cancel"));
        game_data.is_returning_or_escaping = 0;
    }
    else
    {
        int stat = quest_is_return_forbidden();
        if (stat == 1)
        {
            txt(i18n::s.get("core.magic.escape.during_quest"));
            if (!yes_no())
            {
                return true;
            }
        }
        txt(i18n::s.get("core.magic.escape.begin"));
        if (area_data[game_data.current_map].id ==
            mdata_t::MapId::random_dungeon)
        {
            if (game_data.current_dungeon_level ==
                area_data[game_data.current_map].deepest_level)
            {
                if (area_data[game_data.current_map].has_been_conquered != -1)
                {
                    txt(i18n::s.get("core.magic.escape.lord_may_disappear"));
                }
            }
        }
        game_data.destination_map = game_data.destination_outer_map;
        game_data.destination_dungeon_level = 1;
        if (is_cursed(efstatus))
        {
            if (rnd(3) == 0)
            {
                game_data.destination_map = 41;
                game_data.destination_dungeon_level = 1;
            }
        }
        game_data.is_returning_or_escaping = 5 + rnd(10);
    }
    return true;
}



// Return
bool _magic_428(Character& target)
{
    if (target.index != 0)
    {
        txt(i18n::s.get("core.common.nothing_happens"));
        obvious = 0;
        return true;
    }
    if (game_data.is_returning_or_escaping != 0)
    {
        txt(i18n::s.get("core.magic.return.cancel"));
        game_data.is_returning_or_escaping = 0;
    }
    else
    {
        try_to_return();
        if (is_cursed(efstatus))
        {
            if (rnd(3) == 0)
            {
                game_data.destination_map = 41;
                game_data.destination_dungeon_level = 1;
            }
        }
    }
    return true;
}



// Harvest Mana
bool _magic_621(Character& target)
{
    heal_mp(target, efp / 2 + rnd_capped(efp / 2 + 1));
    if (is_in_fov(target))
    {
        txt(i18n::s.get("core.magic.harvest_mana", target));
        BrightAuraAnimation(target.position, BrightAuraAnimation::Type::healing)
            .play();
    }
    return true;
}



// Absorb Magic
bool _magic_624(Character& target)
{
    heal_mp(target, roll(dice1, dice2, bonus));
    if (is_in_fov(target))
    {
        txt(i18n::s.get("core.magic.absorb_magic", target));
        BrightAuraAnimation(target.position, BrightAuraAnimation::Type::healing)
            .play();
    }
    return true;
}



// Item: poison
bool _magic_1108(Character& target)
{
    if (is_in_fov(target))
    {
        txt(i18n::s.get("core.magic.poison_attack", target));
    }
    if (target.is_pregnant())
    {
        target.is_pregnant() = false;
        if (is_in_fov(target))
        {
            txt(i18n::s.get("core.magic.common.melts_alien_children", target));
        }
    }
    status_ailment_damage(target, StatusAilment::poisoned, efp);
    return true;
}



// Item: potion of blindness
bool _magic_1111(Character& target)
{
    if (is_in_fov(target))
    {
        txt(i18n::s.get("core.magic.ink_attack", target));
    }
    status_ailment_damage(target, StatusAilment::blinded, efp);
    return true;
}



// Item: potion of confusion
bool _magic_1109(Character& target)
{
    if (is_in_fov(target))
    {
        txt(i18n::s.get("core.magic.confusion", target));
    }
    status_ailment_damage(target, StatusAilment::confused, efp);
    return true;
}



// Item: potion of paralysis
bool _magic_1110(Character& target)
{
    if (is_in_fov(target))
    {
        txt(i18n::s.get("core.magic.paralysis", target));
    }
    status_ailment_damage(target, StatusAilment::paralyzed, efp);
    return true;
}



// Item: sleeping drug
bool _magic_1112(Character& target)
{
    if (is_in_fov(target))
    {
        txt(i18n::s.get("core.magic.sleep", target));
    }
    status_ailment_damage(target, StatusAilment::sleep, efp);
    return true;
}



// Curse / Item: scroll of curse
bool _magic_645_1114(Character& subject, Character& target)
{
    if (efid == 645)
    {
        if (is_in_fov(target))
        {
            txt(i18n::s.get("core.magic.curse.spell", subject, target));
        }
    }
    int p = 75 + sdata(19, target.index);
    if (const auto anticurse = enchantment_find(target, 43))
    {
        p += *anticurse / 2;
    }
    if (rnd_capped(p) > efp / 2 + (is_cursed(efstatus)) * 100)
    {
        return true;
    }
    if (target.index < 16)
    {
        if (rnd(3))
        {
            if (trait(42))
            {
                txt(i18n::s.get("core.magic.curse.no_effect"));
                return true;
            }
        }
    }
    std::vector<std::reference_wrapper<Item>> candidates;
    for (const auto& [_type, equipment] : target.equipment_slots)
    {
        if (!equipment)
        {
            continue;
        }
        if (equipment->curse_state == CurseState::blessed)
        {
            if (rnd(10))
            {
                continue;
            }
        }
        candidates.emplace_back(std::ref(*equipment));
    }
    if (candidates.empty())
    {
        for (int _i = 0; _i < 200; ++_i)
        {
            auto& item = get_random_inv(target.index);
            if (item.number() == 0)
            {
                continue;
            }
            if (item.curse_state == CurseState::blessed)
            {
                if (rnd(10))
                {
                    continue;
                }
            }
            candidates.emplace_back(std::ref(item));
            break;
        }
    }
    if (!candidates.empty())
    {
        const auto& cursed_item_wr = choice(candidates);
        auto& cursed_item = cursed_item_wr.get();
        const auto original_item_name = itemname(cursed_item, 1, false);
        if (cursed_item.curse_state == CurseState::cursed)
        {
            cursed_item.curse_state = CurseState::doomed;
        }
        else
        {
            cursed_item.curse_state = CurseState::cursed;
        }
        if (is_in_fov(target))
        {
            txt(i18n::s.get(
                "core.magic.curse.apply", target, original_item_name));
        }
        chara_refresh(target);
        snd("core.curse3");
        animeload(14, target);
        item_stack(target.index, cursed_item, true);
    }
    else
    {
        txt(i18n::s.get("core.common.nothing_happens"));
        obvious = 0;
    }
    return true;
}



// Weaken resistance
bool _magic_1118(Character& target)
{
    f = 0;
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        p = rnd(11) + 50;
        if (sdata.get(p, target.index).original_level >= 150)
        {
            ++f;
            chara_gain_registance(target, p, 50 * -1);
            if (f >= efp / 100)
            {
                break;
            }
        }
    }
    if (f == 0)
    {
        txt(i18n::s.get("core.magic.weaken_resistance.nothing_happens"));
        obvious = 0;
    }
    else
    {
        snd("core.curse1");
    }
    chara_refresh(target);
    return true;
}



// Item: diary of cat sister / diary of younger sister / scroll of ally / diary
// of young lady
bool _magic_1138_1123_1122_1137(Character& subject)
{
    if (subject.index != 0 && subject.index < 16)
    {
        txt(i18n::s.get("core.common.nothing_happens"));
        return true;
    }
    flt(cdata.player().level / 2 + 5, Quality::great);
    p = 0;
    if (rnd(3) == 0)
    {
        fltn(u8"man"s);
    }
    if (efid == 1138)
    {
        txt(i18n::s.get("core.magic.diary.cat_sister"));
        p = 210;
    }
    if (efid == 1123)
    {
        txt(i18n::s.get("core.magic.diary.younger_sister"));
        p = 176;
    }
    if (efid == 1137)
    {
        txt(i18n::s.get("core.magic.diary.young_lady"));
        p = 211;
    }
    novoidlv = 1;
    chara_create(56, p, -3, 0);
    new_ally_joins(cdata.tmp());
    return true;
}



// Dominate
bool _magic_435(Character& subject, Character& target)
{
    if (subject.index != 0 || target.index == 0 || target.relationship == 10)
    {
        txt(i18n::s.get("core.common.nothing_happens"));
        obvious = 0;
        return true;
    }
    if (map_prevents_domination())
    {
        obvious = 0;
        txt(i18n::s.get("core.magic.domination.does_not_work_in_area"));
        return true;
    }
    f = 1;
    {
        if (inv_find(ItemId::monster_heart, subject.index))
        {
            efp = efp * 3 / 2;
        }
    }
    if (rnd_capped(efp / 15 + 5) < target.level)
    {
        f = 0;
    }
    if (target.quality >= Quality::miracle || target.role != Role::none ||
        target.is_lord_of_dungeon() == 1)
    {
        f = -1;
    }
    if (f == 1)
    {
        new_ally_joins(target);
        quest_check();
    }
    else if (f == 0)
    {
        txt(i18n::s.get("core.magic.common.resists", target));
    }
    else
    {
        txt(i18n::s.get("core.magic.domination.cannot_be_charmed", target));
    }
    return true;
}



// Web / Mist of Darkness / Acid Ground / Ether Ground / Fire Wall
bool _magic_436_437_455_634_456(Character& subject)
{
    if (efid == 436)
    {
        p(0) = 3;
        p(1) = 2 + rnd_capped(efp / 50 + 1);
        txt(i18n::s.get("core.magic.map_effect.web"));
    }
    if (efid == 437)
    {
        txt(i18n::s.get("core.magic.map_effect.fog"));
        p(0) = 3;
        p(1) = 2 + rnd_capped(efp / 50 + 1);
    }
    if (efid == 455)
    {
        txt(i18n::s.get("core.magic.map_effect.acid"));
        p(0) = 2;
        p(1) = 2 + rnd_capped(efp / 50 + 1);
    }
    if (efid == 456)
    {
        txt(i18n::s.get("core.magic.map_effect.fire"));
        p(0) = 2;
        p(1) = 2 + rnd_capped(efp / 50 + 1);
    }
    if (efid == 634)
    {
        txt(i18n::s.get("core.magic.map_effect.ether_mist"));
        p(0) = 2;
        p(1) = 1 + rnd_capped(efp / 100 + 2);
    }
    snd("core.web");
    for (int cnt = 0, cnt_end = (p(1)); cnt < cnt_end; ++cnt)
    {
        x = rnd(p(0)) + tlocx - rnd(p(0));
        y = rnd(p(0)) + tlocy - rnd(p(0));
        f = 1;
        if (x < 0 || y < 0 || x >= map_data.width || y >= map_data.height)
        {
            f = 0;
        }
        else if (chip_data.for_cell(x, y).effect & 4)
        {
            f = 0;
        }
        if (dist(tlocx, tlocy, x, y) >= p)
        {
            f = 0;
        }
        if (f == 0)
        {
            if (rnd(2) == 0)
            {
                continue;
            }
            else
            {
                --cnt;
                continue;
            }
        }
        if (efid == 634)
        {
            mef_add(x, y, 4, 20, rnd(4) + 2, efp, subject.index);
        }
        if (efid == 455)
        {
            mef_add(x, y, 3, 19, rnd(10) + 5, efp, subject.index);
        }
        if (efid == 456)
        {
            mef_add(x, y, 5, 24, rnd(10) + 5, efp, subject.index);
            mapitem_fire(subject, x, y);
        }
        if (efid == 436)
        {
            mef_add(x, y, 1, 11, -1, efp * 2);
        }
        if (efid == 437)
        {
            mef_add(x, y, 2, 30, 8 + rnd_capped(15 + efp / 25), efp);
        }
    }
    return true;
}



// Item: scroll of name
bool _magic_1145(Character& subject)
{
    if (subject.index != 0)
    {
        txt(i18n::s.get("core.common.nothing_happens"));
        obvious = 0;
        return true;
    }
    invsubroutine = 1;
    invctrl(0) = 23;
    invctrl(1) = 0;
    snd("core.inv");
    const auto& [menu_result, target_item_opt] = ctrl_inventory();
    if (!menu_result.succeeded || target_item_opt->quality < Quality::miracle ||
        target_item_opt->quality == Quality::special)
    {
        txt(i18n::s.get("core.common.it_is_impossible"));
        obvious = 0;
        return true;
    }
    assert(target_item_opt);
    auto& target_item = *target_item_opt;
    txt(i18n::s.get("core.magic.name.prompt"));
    {
        int stat = select_alias(3);
        if (stat == 0)
        {
            obvious = 0;
            randomize();
            return true;
        }
        p = stat;
    }
    target_item.subname = list(1, p) + 40000;
    randomize();
    txt(i18n::s.get("core.magic.name.apply", listn(0, p)));
    return true;
}



// Item: Garok's hammer
bool _magic_49(Character& subject, Item& hammer)
{
    if (subject.index != 0)
    {
        txt(i18n::s.get("core.common.nothing_happens"));
        obvious = 0;
        return true;
    }
    invsubroutine = 1;
    invctrl(0) = 23;
    invctrl(1) = 7;
    snd("core.inv");
    const auto& [menu_result, target_item_opt] = ctrl_inventory();
    if (!menu_result.succeeded)
    {
        return true;
    }
    assert(target_item_opt);
    auto& target_item = *target_item_opt;
    if (target_item.quality >= Quality::miracle || target_item.is_alive())
    {
        txt(i18n::s.get("core.magic.garoks_hammer.no_effect"));
        fixmaterial = 0;
        objfix = 0;
        return true;
    }
    randomize(hammer.param1);
    equip = target_item.body_part;
    animeload(8, subject);
    target_item.quality = Quality::miracle;
    change_item_material(target_item, target_item.material);
    randomize(hammer.param1);
    target_item.subname = 40000 + rnd(30000);
    p = rnd(rnd(rnd(10) + 1) + 3) + 3;
    egolv = rnd(clamp(rnd(6), 0, 4) + 1);
    for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
    {
        randomize(hammer.param1);
        enchantment_add(
            target_item,
            enchantment_generate(enchantment_gen_level(egolv)),
            enchantment_gen_p() + (fixlv == Quality::godly) * 100 +
                (target_item.is_eternal_force()) * 100,
            20 - (fixlv == Quality::godly) * 10 -
                (target_item.is_eternal_force()) * 20);
    }
    randomize();
    txt(i18n::s.get("core.magic.garoks_hammer.apply", target_item));
    if (equip != 0)
    {
        subject.equipment_slots[equip - 100].equip(target_item);
        target_item.body_part = equip;
    }
    chara_refresh(subject);
    fixmaterial = 0;
    objfix = 0;
    hammer.modify_number(-1);
    save_set_autosave();
    return true;
}



// Item: scroll of change material
bool _magic_21_1127(Character& subject)
{
    if (subject.index != 0)
    {
        txt(i18n::s.get("core.common.nothing_happens"));
        obvious = 0;
        return true;
    }
    invsubroutine = 1;
    invctrl(0) = 23;
    invctrl(1) = 0;
    snd("core.inv");

    const auto& [menu_result, target_item_opt] = ctrl_inventory();
    f = menu_result.succeeded ? 1 : 0;
    if (f)
    {
        if (target_item_opt->quality == Quality::godly ||
            target_item_opt->is_alive())
        {
            if (efid == 1127)
            {
                f = 0;
            }
        }
    }
    if (f == 1)
    {
        assert(target_item_opt);
        auto& target_item = *target_item_opt;
        equip = target_item.body_part;
        if (target_item.quality == Quality::special)
        {
            if (efp < 350)
            {
                txt(i18n::s.get(
                    "core.magic.change_material.more_power_needed"));
                return true;
            }
            animeload(8, subject);
            txt(i18n::s.get(
                "core.magic.change_material.artifact_reconstructed",
                subject,
                target_item));
            target_item.modify_number(-1);
            flt();
            const auto reconstructed_artifact =
                itemcreate_player_inv(itemid2int(target_item.id), 0);
            assert(reconstructed_artifact);
            if (equip != 0)
            {
                subject.equipment_slots[equip - 100].equip(
                    *reconstructed_artifact);
                reconstructed_artifact->body_part = equip;
            }
        }
        else
        {
            int material = fixmaterial;

            animeload(8, subject);
            if (efp <= 50)
            {
                if (rnd(3) == 0)
                {
                    material = 35;
                }
            }
            s = itemname(target_item, 1, false);
            objlv = efp / 10;
            objfix = efp / 100;
            randomize();
            change_item_material(target_item, material);
            txt(i18n::s.get(
                "core.magic.change_material.apply",
                subject,
                s(0),
                target_item));
            if (equip != 0)
            {
                subject.equipment_slots[equip - 100].equip(target_item);
                target_item.body_part = equip;
            }
        }
    }
    else
    {
        txt(i18n::s.get("core.common.nothing_happens"));
        obvious = 0;
    }
    chara_refresh(subject);
    fixmaterial = 0;
    objfix = 0;
    return true;
}



// Item: deed of inheritance
bool _magic_1128(Character& subject)
{
    if (subject.index != 0)
    {
        txt(i18n::s.get("core.common.nothing_happens"));
        obvious = 0;
        return true;
    }
    snd("core.ding2");
    p = rnd_capped(efp + 1) / 100 + 1;
    game_data.rights_to_succeed_to += p;
    txt(i18n::s.get("core.magic.deed_of_inheritance.claim", p(0)),
        Message::color{ColorIndex::orange});
    txt(i18n::s.get(
        "core.magic.deed_of_inheritance.can_now_inherit",
        game_data.rights_to_succeed_to));
    return true;
}



// Item: scroll of enchant weapon / armor
bool _magic_1124_1125(Character& subject)
{
    if (subject.index != 0)
    {
        txt(i18n::s.get("core.common.nothing_happens"));
        return true;
    }
    invsubroutine = 1;
    if (efid == 1124)
    {
        invctrl(0) = 23;
        invctrl(1) = 1;
    }
    else
    {
        invctrl(0) = 23;
        invctrl(1) = 2;
    }
    snd("core.inv");
    const auto& [menu_result, target_item_opt] = ctrl_inventory();
    if (menu_result.succeeded)
    {
        assert(target_item_opt);
        auto& target_item = *target_item_opt;
        if (target_item.enhancement < efp / 100)
        {
            snd("core.ding2");
            txt(i18n::s.get("core.magic.enchant.apply", target_item));
            ++target_item.enhancement;
        }
        else
        {
            txt(i18n::s.get("core.magic.enchant.resist", target_item));
        }
        chara_refresh(subject);
    }
    else
    {
        obvious = 0;
    }
    return true;
}



// Fill Charge / Item: scroll of charge
bool _magic_630_1129(Character& subject)
{
    if (subject.index != 0)
    {
        txt(i18n::s.get("core.common.nothing_happens"));
        obvious = 0;
        return true;
    }
    if (efid == 630)
    {
        if (game_data.charge_power < 10)
        {
            txt(i18n::s.get("core.magic.fill_charge.more_power_needed"));
            return true;
        }
        game_data.charge_power -= 10;
        txt(i18n::s.get(
            "core.magic.fill_charge.spend", game_data.charge_power));
    }
    invsubroutine = 1;
    invctrl(0) = 23;
    invctrl(1) = 3;
    snd("core.inv");

    const auto& [menu_result, target_item_opt] = ctrl_inventory();
    if (menu_result.succeeded)
    {
        assert(target_item_opt);
        auto& target_item = *target_item_opt;
        item_db_get_charge_level(target_item, itemid2int(target_item.id));
        if (ichargelevel < 1 || target_item.id == ItemId::rod_of_wishing ||
            target_item.id == ItemId::rod_of_domination ||
            target_item.id == ItemId::spellbook_of_wishing ||
            target_item.id == ItemId::spellbook_of_harvest ||
            (target_item.id == ItemId::ancient_book && target_item.param2 != 0))
        {
            txt(i18n::s.get("core.magic.fill_charge.cannot_recharge"));
            return true;
        }
        f = 1;
        if (target_item.count > ichargelevel)
        {
            f = -1;
        }
        if (f == -1)
        {
            txt(i18n::s.get(
                "core.magic.fill_charge.cannot_recharge_anymore", target_item));
            return true;
        }
        if (rnd_capped(efp / 25 + 1) == 0)
        {
            f = 0;
        }
        if (the_item_db[itemid2int(target_item.id)]->category ==
            ItemCategory::spellbook)
        {
            if (rnd(4) == 0)
            {
                f = 0;
            }
        }
        if (rnd(ichargelevel * ichargelevel + 1) == 0)
        {
            f = 0;
        }
        if (f == 1)
        {
            p = 1 + rnd((ichargelevel / 2 + 1));
            if (p + target_item.count > ichargelevel)
            {
                p = ichargelevel - target_item.count + 1;
            }
            if (the_item_db[itemid2int(target_item.id)]->category ==
                ItemCategory::spellbook)
            {
                p = 1;
            }
            txt(i18n::s.get("core.magic.fill_charge.apply", target_item, p(0)));
            target_item.count += p;
            animeload(8, subject);
        }
        else
        {
            if (rnd(4) == 0)
            {
                txt(i18n::s.get(
                    "core.magic.fill_charge.explodes", target_item));
                target_item.modify_number(-1);
                refresh_burden_state();
                return true;
            }
            txt(i18n::s.get("core.magic.fill_charge.fail", target_item));
        }
    }
    else
    {
        obvious = 0;
    }

    return true;
}



// Draw Charge
bool _magic_629(Character& subject)
{
    if (subject.index != 0)
    {
        txt(i18n::s.get("core.common.nothing_happens"));
        obvious = 0;
        return true;
    }
    invsubroutine = 1;
    invctrl(0) = 23;
    invctrl(1) = 5;
    snd("core.inv");

    const auto& [menu_result, target_item_opt] = ctrl_inventory();
    if (menu_result.succeeded)
    {
        assert(target_item_opt);
        auto& target_item = *target_item_opt;
        item_db_get_charge_level(target_item, itemid2int(target_item.id));
        for (int cnt = 0; cnt < 1; ++cnt)
        {
            if (ichargelevel == 1)
            {
                p = 100;
                break;
            }
            if (ichargelevel == 2)
            {
                p = 25;
                break;
            }
            if (ichargelevel <= 4)
            {
                p = 5;
                break;
            }
            if (ichargelevel <= 6)
            {
                p = 3;
                break;
            }
            p = 1;
        }
        animeload(8, subject);
        p = p * target_item.count;
        game_data.charge_power += p;
        txt(i18n::s.get(
            "core.magic.draw_charge",
            target_item,
            p(0),
            game_data.charge_power));
        target_item.remove();
        refresh_burden_state();
    }

    return true;
}



// Change
bool _magic_628(Character& subject, Character& target)
{
    if (target.index == 0)
    {
        txt(i18n::s.get("core.common.nothing_happens"));
        obvious = 0;
        return true;
    }
    f = 1;
    if (efp / 10 + 10 < target.level)
    {
        f = 0;
    }
    if (target.quality >= Quality::miracle || target.role != Role::none ||
        target.is_escorted() == 1 || target.is_lord_of_dungeon() == 1)
    {
        f = -1;
    }
    if (target.index < 57)
    {
        f = 0;
    }
    if (f == 1)
    {
        animeload(8, target);
        txt(i18n::s.get("core.magic.change.apply", target));
        flt(calcobjlv(target.level + 3), Quality::good);
        chara_create(56, 0, -3, 0);
        chara_relocate(cdata.tmp(), target, CharaRelocationMode::change);
        target.enemy_id = subject.index;
        target.is_quest_target() = false;
        quest_check();
    }
    else if (f == 0)
    {
        txt(i18n::s.get("core.magic.common.resists", target));
    }
    else
    {
        txt(i18n::s.get("core.magic.change.cannot_be_changed", target));
    }
    return true;
}



// Item: scroll of flying
bool _magic_1140(Character& subject)
{
    if (subject.index != 0)
    {
        txt(i18n::s.get("core.common.nothing_happens"));
        obvious = 0;
        return true;
    }
    invsubroutine = 1;
    invctrl(0) = 23;
    invctrl(1) = 6;
    snd("core.inv");

    const auto& [menu_result, target_item_opt] = ctrl_inventory();
    if (menu_result.succeeded)
    {
        assert(target_item_opt);
        auto& target_item = *target_item_opt;
        save_set_autosave();
        animeload(8, subject);
        if (!is_cursed(efstatus))
        {
            if (target_item.weight > 0)
            {
                target_item.weight = clamp(
                    target_item.weight * (100 - efp / 10) / 100,
                    1,
                    target_item.weight);
                if (target_item.pv > 0)
                {
                    target_item.pv -= target_item.pv / 10 + 1 +
                        (efstatus != CurseState::blessed);
                }
                if (target_item.damage_bonus > 0)
                {
                    target_item.damage_bonus -= target_item.damage_bonus / 10 +
                        1 + (efstatus != CurseState::blessed);
                }
            }
            txt(i18n::s.get("core.magic.flying.apply", target_item));
        }
        else
        {
            target_item.weight = target_item.weight * 150 / 100 + 1000;
            if (target_item.pv > 0)
            {
                target_item.pv += clamp(target_item.pv / 10, 1, 5);
            }
            if (target_item.damage_bonus > 0)
            {
                target_item.damage_bonus +=
                    clamp(target_item.damage_bonus / 10, 1, 5);
            }
            txt(i18n::s.get("core.magic.flying.cursed", target_item));
        }
        refresh_burden_state();
    }
    else
    {
        txt(i18n::s.get("core.common.nothing_happens"));
        obvious = 0;
    }

    chara_refresh(subject);
    return true;
}



// Item: rod of alchemy
bool _magic_1132(Character& subject, int& fltbk, int& valuebk)
{
    if (subject.index != 0)
    {
        txt(i18n::s.get("core.common.nothing_happens"));
        obvious = 0;
        return true;
    }
    invsubroutine = 1;
    invctrl(0) = 23;
    invctrl(1) = 4;
    snd("core.inv");

    const auto& [menu_result, target_item_opt] = ctrl_inventory();
    f = menu_result.succeeded ? 1 : 0;

    if (f)
    {
        assert(target_item_opt);
        if (target_item_opt->quality > Quality::miracle ||
            target_item_opt->is_precious())
        {
            f = 0;
        }
    }
    if (f == 1)
    {
        assert(target_item_opt);
        auto& target_item = *target_item_opt;
        save_set_autosave();
        animeload(8, subject);
        fltbk = (int)the_item_db[itemid2int(target_item.id)]->category;
        valuebk = calcitemvalue(target_item, 0);
        target_item.remove();
        for (int cnt = 0;; ++cnt)
        {
            flt(calcobjlv(efp / 10) + 5, calcfixlv(Quality::good));
            if (cnt < 10)
            {
                flttypemajor = fltbk;
            }
            if (const auto item = itemcreate_player_inv(0, 0))
            {
                if (item->value > valuebk * 3 / 2 + 1000)
                {
                    item->remove();
                    continue;
                }
                else
                {
                    txt(i18n::s.get("core.magic.alchemy", *item));
                    break;
                }
            }
            else
            {
                continue;
            }
        }
        refresh_burden_state();
    }
    else
    {
        txt(i18n::s.get("core.common.nothing_happens"));
        obvious = 0;
    }
    return true;
}



// Door Creation / Wall Creation
bool _magic_457_438()
{
    x = tlocx;
    y = tlocy;
    f = 1;
    if (x < 0 || y < 0 || x >= map_data.width || y >= map_data.height)
    {
        f = 0;
    }
    else
    {
        if (chip_data.for_cell(x, y).effect & 4)
        {
            if (homemapmode == 0)
            {
                if (efid != 457)
                {
                    f = 0;
                }
                else if (chip_data.for_cell(x, y).kind == 3)
                {
                    f = 0;
                }
            }
        }
        if (cell_data.at(x, y).chara_index_plus_one != 0 ||
            cell_data.at(x, y).feats != 0)
        {
            f = 0;
        }
    }
    if (f == 1)
    {
        if (efid == 438)
        {
            if (homemapmode == 0)
            {
                txt(i18n::s.get("core.magic.create.wall"));
                p = tile_wall;
            }
            else
            {
                p = tile;
            }
            if (cell_data.at(x, y).chip_id_actual != p)
            {
                snd("core.offer1");
            }
            cell_data.at(x, y).chip_id_actual = p;
            cell_data.at(x, y).chip_id_memory = p;
        }
        if (efid == 457)
        {
            snd("core.offer1");
            if (chip_data.for_cell(x, y).kind == 6)
            {
                txt(i18n::s.get("core.magic.create.door.resist"));
                return true;
            }
            txt(i18n::s.get("core.magic.create.door.apply"));
            cell_featset(x, y, tile_doorclosed, 21, rnd_capped(efp / 10 + 1));
            if (chip_data.for_cell(x, y).effect & 4)
            {
                cell_data.at(x, y).chip_id_actual = tile_tunnel;
            }
        }
    }
    else
    {
        if (homemapmode == 0)
        {
            txt(i18n::s.get("core.common.nothing_happens"));
        }
        obvious = 0;
    }
    return true;
}



// Swarm
bool _magic_631(Character& subject)
{
    txt(i18n::s.get("core.magic.swarm"), Message::color{ColorIndex::blue});
    for (auto&& cnt : cdata.all())
    {
        if (subject.state() != Character::State::alive)
        {
            continue;
        }
        if (cnt.state() != Character::State::alive)
        {
            continue;
        }
        if (subject.index == cnt.index)
        {
            continue;
        }
        if (belong_to_same_team(subject, cnt))
        {
            continue;
        }
        dx = cnt.position.x;
        dy = cnt.position.y;
        if (dist(subject.position.x, subject.position.y, dx, dy) >
            the_ability_db[631]->range % 1000 + 1)
        {
            continue;
        }
        if (!fov_los(subject.position, {dx, dy}))
        {
            continue;
        }
        SwarmAnimation(cnt.position).play();
        try_to_melee_attack(subject, cnt);
    }
    return true;
}



// Drop Mine
bool _magic_659(Character& subject)
{
    if (map_data.type == mdata_t::MapType::world_map)
    {
        return true;
    }
    if (cell_data.at(subject.position.x, subject.position.y).feats != 0)
    {
        return true;
    }
    cell_featset(
        subject.position.x, subject.position.y, 0, 14, 7, subject.index);
    if (is_in_fov(subject))
    {
        txt(i18n::s.get("core.magic.drop_mine", subject));
    }
    return true;
}



// Gravity
bool _magic_466(Character& subject)
{
    for (auto&& cnt : cdata.all())
    {
        if (cnt.state() != Character::State::alive)
        {
            continue;
        }
        if (subject.index == cnt.index)
        {
            continue;
        }
        if (cnt.is_immune_to_mine())
        {
            continue;
        }
        dx = cnt.position.x;
        dy = cnt.position.y;
        if (dist(subject.position.x, subject.position.y, dx, dy) > 4)
        {
            continue;
        }
        if (is_in_fov(cnt))
        {
            txt(i18n::s.get("core.magic.gravity", cnt));
        }
        cnt.gravity += 100 + rnd(100);
    }
    return true;
}



// Mewmewmew!
bool _magic_657(Character& subject)
{
    txt(i18n::s.get("core.magic.mewmewmew"), Message::color{ColorIndex::blue});
    MiracleAnimation(MiracleAnimation::Mode::target_all, subject).play();
    for (auto&& cnt : cdata.all())
    {
        if (subject.state() != Character::State::alive)
        {
            continue;
        }
        if (cnt.state() != Character::State::alive)
        {
            continue;
        }
        if (subject.index == cnt.index)
        {
            continue;
        }
        damage_hp(cnt, 9999999, subject.index);
    }
    return true;
}



// Meteor
bool _magic_465(Character& subject)
{
    txt(i18n::s.get("core.magic.meteor"), Message::color{ColorIndex::blue});
    MeteorAnimation().play();
    for (int cnt = 0, cnt_end = (map_data.height); cnt < cnt_end; ++cnt)
    {
        dy = cnt;
        for (int cnt = 0, cnt_end = (map_data.width); cnt < cnt_end; ++cnt)
        {
            dx = cnt;
            if (rnd(3) == 0)
            {
                cell_data.at(dx, dy).chip_id_actual = 12 + rnd(2);
            }
            if (rnd(40) == 0)
            {
                mef_add(dx, dy, 5, 24, rnd(4) + 3, 50);
            }
            if (cell_data.at(dx, dy).chara_index_plus_one != 0)
            {
                dmg = sdata(16, subject.index) * efp / 10;
                damage_hp(
                    cdata[cell_data.at(dx, dy).chara_index_plus_one - 1],
                    dmg,
                    subject.index,
                    50,
                    1000);
            }
        }
    }
    return true;
}



// Cheer
bool _magic_656(Character& subject)
{
    if (is_in_fov(subject))
    {
        txt(i18n::s.get("core.magic.cheer.apply", subject));
    }
    for (auto&& cnt : cdata.all())
    {
        if (cnt.state() != Character::State::alive)
        {
            continue;
        }
        if (subject.index == cnt.index)
        {
            continue;
        }
        if (subject.index < 16)
        {
            if (cnt.index >= 16)
            {
                continue;
            }
            else if (subject.relationship != cnt.relationship)
            {
                continue;
            }
        }
        dx = cnt.position.x;
        dy = cnt.position.y;
        if (dist(subject.position.x, subject.position.y, dx, dy) >
            the_ability_db[656]->range % 1000 + 1)
        {
            continue;
        }
        if (!fov_los(subject.position, {dx, dy}))
        {
            continue;
        }
        if (is_in_fov(cnt))
        {
            txt(i18n::s.get("core.magic.cheer.is_excited", cnt),
                Message::color{ColorIndex::blue});
        }
        buff_add(
            cnt, "core.speed", sdata(17, subject.index) * 5 + 50, 15, subject);
        buff_add(
            cnt, "core.hero", sdata(17, subject.index) * 5 + 100, 60, subject);
        buff_add(cnt, "core.contingency", 1500, 30, subject);
    }
    return true;
}



// Item: potion of cure corruption
bool _magic_1131(Character& target)
{
    if (target.index != 0)
    {
        txt(i18n::s.get("core.common.nothing_happens"));
        return true;
    }
    snd("core.pray1");
    if (!is_cursed(efstatus))
    {
        txt(i18n::s.get("core.magic.cure_corruption.apply"),
            Message::color{ColorIndex::green});
        modify_ether_disease_stage(efp * -10);
    }
    else
    {
        txt(i18n::s.get("core.magic.cure_corruption.cursed"),
            Message::color{ColorIndex::purple});
        modify_ether_disease_stage(200);
    }
    return true;
}



// Eye of Ether
bool _magic_633(Character& subject, Character& target)
{
    if (target.index != 0)
    {
        return true;
    }
    txt(i18n::s.get("core.magic.eye_of_ether", subject),
        Message::color{ColorIndex::purple});
    modify_ether_disease_stage(100);
    return true;
}



// Eye of Dimness
bool _magic_638_648(Character& subject, Character& target)
{
    if (efid == 648)
    {
        if (is_in_fov(target))
        {
            txt(i18n::s.get("core.magic.insult.apply", subject, target));
            if (subject.sex == 0)
            {
                txt(i18n::s.get("core.magic.insult.man"),
                    Message::color{ColorIndex::cyan});
            }
            else
            {
                txt(i18n::s.get("core.magic.insult.woman"),
                    Message::color{ColorIndex::cyan});
            }
        }
    }
    if (efid == 638)
    {
        if (is_in_fov(target))
        {
            txt(i18n::s.get("core.magic.gaze", subject, target));
        }
    }
    status_ailment_damage(target, StatusAilment::dimmed, 200);
    return true;
}



// Insult
bool _magic_652(Character& subject, Character& target)
{
    if (is_in_fov(target))
    {
        txt(i18n::s.get("core.magic.gaze", subject, target));
    }
    damage_mp(target, rnd(20) + 1);
    return true;
}



// Item: molotov
bool _magic_1133(Character& subject, Character& target)
{
    if (is_in_fov(target))
    {
        txt(i18n::s.get("core.magic.molotov", target));
    }
    mef_add(
        target.position.x,
        target.position.y,
        5,
        24,
        rnd(15) + 25,
        efp,
        subject.index);
    mapitem_fire(subject, target.position.x, target.position.y);
    return true;
}



// Scavenge
bool _magic_651(Character& subject, Character& target)
{
    if (is_in_fov(target))
    {
        txt(i18n::s.get("core.magic.scavenge.apply", subject, target));
    }
    OptionalItemRef eat_item_opt;
    for (const auto& item : g_inv.for_chara(target))
    {
        if (item->id == ItemId::fish_a)
        {
            eat_item_opt = item.clone();
            break;
        }
    }
    if (!eat_item_opt)
    {
        for (const auto& item : g_inv.for_chara(target))
        {
            if (item->is_precious())
            {
                continue;
            }
            if (the_item_db[itemid2int(item->id)]->category !=
                ItemCategory::food)
            {
                continue;
            }
            eat_item_opt = item.clone();
            break;
        }
    }
    if (!eat_item_opt)
    {
        return true;
    }
    auto& eat_item = *eat_item_opt;
    if (eat_item.is_aphrodisiac())
    {
        if (is_in_fov(target))
        {
            txt(i18n::s.get("core.magic.scavenge.rotten", subject, eat_item));
        }
        return true;
    }
    rowact_item(eat_item);
    if (is_in_fov(target))
    {
        snd("core.eat1");
        txt(i18n::s.get("core.magic.scavenge.eats", subject, eat_item));
    }
    heal_hp(subject, subject.max_hp / 3);
    activity_eating_finish(subject, eat_item);
    refresh_burden_state();
    return true;
}



// Wizard's Harvest
bool _magic_464(Character& subject, Character& target)
{
    bool fastest = g_config.animation_wait() == 0;
    std::string messages;

    animeload(10, target);
    for (int i = 0, n = clamp(4 + rnd_capped(efp / 50 + 1), 1, 15); i < n; ++i)
    {
        snd("core.pray1");
        flt(calcobjlv(efp / 10), calcfixlv(Quality::good));
        int item_id = 54;
        int number = 400 + rnd_capped(efp);
        if (rnd(30) == 0)
        {
            item_id = 55;
            number = 1;
        }
        if (rnd(80) == 0)
        {
            item_id = 622;
            number = 1;
        }
        if (rnd(2000) == 0)
        {
            item_id = 290;
            number = 1;
        }
        nostack = 1;
        if (const auto item =
                itemcreate_extra_inv(item_id, subject.position, number))
        {
            const auto message =
                i18n::s.get("core.magic.wizards_harvest", *item);
            if (fastest)
            {
                messages += message;
            }
            else
            {
                txt(message);
                await(g_config.animation_wait() * 4);
                redraw();
            }
        }
    }
    if (fastest)
    {
        txt(messages);
        redraw();
    }
    return true;
}



// 4-Dimentional Pocket
bool _magic_463()
{
    snd("core.teleport1");
    txt(i18n::s.get("core.magic.four_dimensional_pocket"));
    invfile = 8;
    ctrl_file(FileOperation2::map_items_write, u8"shoptmp.s2");
    tmpload(filepathutil::u8path(u8"shop"s + invfile + u8".s2"));
    if (fs::exists(filesystem::dirs::tmp() / (u8"shop"s + invfile + u8".s2")))
    {
        ctrl_file(
            FileOperation2::map_items_read, u8"shop"s + invfile + u8".s2");
    }
    else
    {
        for (const auto& item : g_inv.ground())
        {
            item->remove();
        }
    }
    shoptrade = 0;
    menucycle = 1;
    invsubroutine = 1;
    invctrl(0) = 22;
    invctrl(1) = 5;
    invcontainer = clamp(efp / 10 + 10, 10, 300);
    mode = 6;
    snd("core.inv");
    ctrl_inventory();
    invcontainer = 0;
    ctrl_file(FileOperation2::map_items_write, u8"shop"s + invfile + u8".s2");
    ctrl_file(FileOperation2::map_items_read, u8"shoptmp.s2");
    mode = 0;
    return true;
}



int _calc_ball_spell_range(Character& subject)
{
    int ret = the_ability_db[efid]->range % 1000 + 1;
    if (debug::voldemort && subject.index == 0)
    {
        ret *= 2;
    }
    if (efid == 644)
    {
        ret = 2;
    }
    return ret;
}



optional_ref<Character> _ball_spell_internal(
    Character& subject,
    std::stack<Character*>& bomb_chain)
{
    subject.will_explode_soon() = false;

    range_ = _calc_ball_spell_range(subject);

    if (efid != 404 && efid != 637)
    {
        BallAnimation({tlocx, tlocy}, range_, BallAnimation::Type::ball, ele)
            .play();
    }

    for (int dy_ = 0; dy_ < range_ * 2 + 1; ++dy_)
    {
        dy = tlocy - range_ + dy_;
        if (dy < 0 || map_data.height <= dy)
        {
            continue;
        }
        for (int dx_ = 0; dx_ < range_ * 2 + 1; ++dx_)
        {
            dx = tlocx - range_ + dx_;
            if (dx < 0 || map_data.width <= dx)
            {
                continue;
            }
            if (dist(tlocx, tlocy, dx, dy) > range_)
            {
                continue;
            }
            if (!fov_los({tlocx, tlocy}, {dx, dy}))
            {
                continue;
            }
            if (cell_data.at(dx, dy).chara_index_plus_one == 0)
            {
                continue;
            }
            const auto target_index =
                cell_data.at(dx, dy).chara_index_plus_one - 1;
            if (efid == 404)
            {
                f = 0;
                if (subject.index == 0 || subject.relationship >= 0)
                {
                    if (cdata[target_index].relationship >= 0)
                    {
                        f = 1;
                    }
                }
                else if (cdata[target_index].relationship <= -1)
                {
                    f = 1;
                }
                if (f)
                {
                    BrightAuraAnimation(
                        cdata[target_index].position,
                        BrightAuraAnimation::Type::healing_rain)
                        .play();
                    if (is_in_fov(cdata[target_index]))
                    {
                        txt(i18n::s.get(
                            "core.magic.healed.normal", cdata[target_index]));
                    }
                    heal_both_rider_and_mount(cdata[target_index]);
                }
                continue;
            }
            if (efid == 637)
            {
                f = 0;
                if (subject.index == 0 || subject.relationship >= 0)
                {
                    if (cdata[target_index].relationship >= 0)
                    {
                        f = 1;
                    }
                }
                else if (cdata[target_index].relationship <= -1)
                {
                    f = 1;
                }
                if (f)
                {
                    BrightAuraAnimation(
                        cdata[target_index].position,
                        BrightAuraAnimation::Type::healing_rain)
                        .play();
                    txt(i18n::s.get(
                        "core.magic.rain_of_sanity", cdata[target_index]));
                    heal_insanity(cdata[target_index], efp / 10);
                    status_ailment_heal(
                        cdata[target_index], StatusAilment::insane, 9999);
                }
                continue;
            }
            if (dx == subject.position.x && dy == subject.position.y)
            {
                continue;
            }
            if (game_data.mount != 0)
            {
                if (game_data.mount == subject.index)
                {
                    if (target_index == 0)
                    {
                        continue;
                    }
                }
            }
            if (ele == 50)
            {
                mapitem_fire(subject, dx, dy);
            }
            if (ele == 51)
            {
                mapitem_cold(dx, dy);
            }
            if (subject.index == target_index)
            {
                continue;
            }
            dmg = roll(dice1, dice2, bonus) * 100 /
                (75 + dist(tlocx, tlocy, dx, dy) * 25);
            if (calc_magic_control(subject, cdata[target_index]))
            {
                continue;
            }
            if (efid == 644)
            {
                if (is_in_fov(cdata[target_index]))
                {
                    if (target_index >= 16)
                    {
                        game_data.proc_damage_events_flag = 2;
                        txt3rd = 1;
                        txt(i18n::s.get(
                            "core.magic.explosion.other", cdata[target_index]));
                    }
                    else
                    {
                        txt(i18n::s.get(
                            "core.magic.explosion.ally", cdata[target_index]));
                    }
                }
                if (cdata[target_index].explodes())
                {
                    bomb_chain.push(&cdata[target_index]);
                    continue;
                }
            }
            else if (is_in_fov(cdata[target_index]))
            {
                if (target_index >= 16)
                {
                    game_data.proc_damage_events_flag = 2;
                    txt3rd = 1;
                    txt(i18n::s.get(
                        "core.magic.ball.other", cdata[target_index]));
                }
                else
                {
                    txt(i18n::s.get(
                        "core.magic.ball.ally", cdata[target_index]));
                }
            }
            damage_hp(cdata[target_index], dmg, subject.index, ele, elep);
        }
    }

    if (efid == 644)
    {
        damage_hp(subject, 99999, -16);
    }

    if (!bomb_chain.empty())
    {
        auto& next_subject = *bomb_chain.top();
        bomb_chain.pop();
        tlocx = next_subject.position.x;
        tlocy = next_subject.position.y;
        if (next_subject.state() == Character::State::alive)
        {
            const auto damage = calc_skill_damage(next_subject, efid, efp);
            dice1 = damage->dice_x;
            dice2 = damage->dice_y;
            bonus = damage->damage_bonus;
            ele = damage->element;
            elep = damage->element_power;
            if (is_in_fov(next_subject))
            {
                txt(i18n::s.get("core.magic.explosion.chain", next_subject));
            }
            return next_subject;
        }
    }

    return none;
}



void _ball_spell(Character& subject)
{
    std::stack<Character*> bomb_chain;

    if (efid == 644)
    {
        if (is_in_fov(subject))
        {
            txt(i18n::s.get("core.magic.explosion.begins", subject));
        }
    }

    optional_ref<Character> subject_ = subject;
    while (subject_)
    {
        subject_ = _ball_spell_internal(*subject_, bomb_chain);
    }
}



optional<bool> _proc_general_magic(Character& subject, Character& target)
{
    int efbad = 0;
    int telex = 0;
    int teley = 0;
    int efidprev = 0;

    f = 0;
    if (the_ability_db[efid]->ability_type / 1000 == 1)
    {
        f = 1;
        p = the_ability_db[efid]->ability_type % 1000;
        if (the_buff_db[p]->type == BuffType::hex)
        {
            efbad = 1;
        }
    }
    if (the_ability_db[efid]->ability_type == 7)
    {
        efbad = 1;
    }
    if (efbad == 0)
    {
        if (efstatus == CurseState::blessed)
        {
            efp = efp * 150 / 100;
        }
        if (is_cursed(efstatus))
        {
            efp = 50;
        }
    }
    else
    {
        if (efstatus == CurseState::blessed)
        {
            efp = 50;
        }
        if (is_cursed(efstatus))
        {
            efp = efp * 150 / 100;
        }
    }
    if (f)
    {
        const auto& buff_data = the_buff_db.ensure(p);

        if (buff_data.type == BuffType::buff)
        {
            animeload(11, target);
        }
        else if (buff_data.type == BuffType::hex)
        {
            BrightAuraAnimation(
                target.position, BrightAuraAnimation::Type::debuff)
                .play();
        }
        if (efid == 625 || efid == 446)
        {
            if ((target.index == 0 && subject.index == 0) ||
                subject.index == game_data.mount)
            {
                if (game_data.mount != 0)
                {
                    target.index = game_data.mount;
                }
            }
        }

        buff_add(
            target,
            buff_data.id,
            efp,
            buff_calc_duration(buff_data.id, efp),
            subject);

        if (efid == 447)
        {
            if (efstatus == CurseState::blessed)
            {
                target.birth_year += rnd(3) + 1;
                if (target.birth_year + 12 > game_data.date.year)
                {
                    target.birth_year = game_data.date.year - 12;
                }
                if (is_in_fov(target))
                {
                    txt(i18n::s.get("core.magic.slow", target),
                        Message::color{ColorIndex::green});
                }
            }
        }
        if (efid == 446)
        {
            if (is_cursed(efstatus))
            {
                target.birth_year -= rnd(3) + 1;
                if (is_in_fov(target))
                {
                    txt(i18n::s.get("core.magic.speed", target),
                        Message::color{ColorIndex::purple});
                }
            }
        }
        if (efid == 458)
        {
            if (target.index == 0)
            {
                incognitobegin();
            }
        }
        return true;
    }
    if (const auto damage = calc_skill_damage(subject, efid, efp))
    {
        dice1 = damage->dice_x;
        dice2 = damage->dice_y;
        bonus = damage->damage_bonus;
        ele = damage->element;
        elep = damage->element_power;
    }
    if (subject.index == 0)
    {
        if (trait(165))
        {
            if (ele == 50 || ele == 51 || ele == 52)
            {
                dice2 = dice2 * 125 / 100;
            }
        }
    }
    if (rapidmagic)
    {
        elep = elep * 4 / 5 + 1;
        dice1 = dice1 * 4 / 5 + 1;
        dice2 = dice2 * 4 / 5 + 1;
        bonus = bonus * 4 / 5 + 1;
    }
    switch (the_ability_db[efid]->ability_type)
    {
    default: return none;
    case 10:
        RangedAttackAnimation(
            subject.position,
            target.position,
            RangedAttackAnimation::Type::distant_attack)
            .play();
        try_to_melee_attack(subject, target);
        return true;
    case 1: {
        int stat =
            get_route(subject.position.x, subject.position.y, tlocx, tlocy);
        if (stat == 0)
        {
            return true;
        }
    }
        {
            int distance = the_ability_db[efid]->range % 1000 + 1;
            BoltAnimation(subject.position, {tlocx, tlocy}, ele, distance)
                .play();
        }
        dx = subject.position.x;
        dy = subject.position.y;
        for (int cnt = 0; cnt < 20; ++cnt)
        {
            int stat = route_info(dx, dy, cnt);
            if (stat == 0)
            {
                break;
            }
            else if (stat == -1)
            {
                continue;
            }
            if (dist(dx, dy, subject.position.x, subject.position.y) >
                the_ability_db[efid]->range % 1000 + 1)
            {
                break;
            }
            if (dx == subject.position.x && dy == subject.position.y)
            {
                continue;
            }
            if (ele == 50)
            {
                mapitem_fire(subject, dx, dy);
            }
            if (ele == 51)
            {
                mapitem_cold(dx, dy);
            }
            if (cell_data.at(dx, dy).chara_index_plus_one != 0)
            {
                const auto target_index =
                    cell_data.at(dx, dy).chara_index_plus_one - 1;
                if (subject.index != target_index)
                {
                    if (game_data.mount != 0)
                    {
                        if (game_data.mount == subject.index)
                        {
                            if (target_index == 0)
                            {
                                continue;
                            }
                        }
                    }
                    dmg = roll(dice1, dice2, bonus);
                    if (calc_magic_control(subject, cdata[target_index]))
                    {
                        continue;
                    }
                    if (is_in_fov(cdata[target_index]))
                    {
                        if (target_index >= 16)
                        {
                            game_data.proc_damage_events_flag = 2;
                            txt3rd = 1;
                            txt(i18n::s.get(
                                "core.magic.bolt.other", cdata[target_index]));
                        }
                        else
                        {
                            txt(i18n::s.get(
                                "core.magic.bolt.ally", cdata[target_index]));
                        }
                    }
                    damage_hp(
                        cdata[target_index], dmg, subject.index, ele, elep);
                }
            }
        }
        return true;
    case 3: _ball_spell(subject); return true;
    case 2:
        RangedAttackAnimation(
            subject.position,
            target.position,
            RangedAttackAnimation::Type::magic_arrow)
            .play();
        dmg = roll(dice1, dice2, bonus);
        if (is_in_fov(target))
        {
            if (target.index >= 16)
            {
                game_data.proc_damage_events_flag = 2;
                txt3rd = 1;
                txt(i18n::s.get("core.magic.arrow.other", target));
            }
            else
            {
                txt(i18n::s.get("core.magic.arrow.ally", target));
            }
        }
        damage_hp(target, dmg, subject.index, ele, elep);
        return true;
    case 4:
        if (efid == 400)
        {
            if (is_in_fov(target))
            {
                txt(i18n::s.get("core.magic.healed.slightly", target));
            }
        }
        if (efid == 401 || efid == 405)
        {
            if (is_in_fov(target))
            {
                txt(i18n::s.get("core.magic.healed.normal", target));
            }
        }
        if (efid == 402)
        {
            if (is_in_fov(target))
            {
                txt(i18n::s.get("core.magic.healed.greatly", target));
            }
        }
        if (efid == 403)
        {
            if (is_in_fov(target))
            {
                txt(i18n::s.get("core.magic.healed.completely", target));
            }
        }
        heal_both_rider_and_mount(target);
        if (efstatus == CurseState::blessed)
        {
            status_ailment_heal(target, StatusAilment::sick, 5 + rnd(5));
        }
        if (rnd(3) == 0)
        {
            get_sick_if_cursed(efstatus, target);
        }
        BrightAuraAnimation(target.position, BrightAuraAnimation::Type::healing)
            .play();
        return true;
    case 6:
        if (subject.special_attack_type != 0)
        {
            if (is_in_fov(subject))
            {
                if (subject.index == 0)
                {
                    txt(i18n::s.get(
                        "core.magic.special_attack.self",
                        subject,
                        the_ability_db.get_text(efid, "name"),
                        i18n::s.get_enum(
                            "core.ui.cast_style",
                            subject.special_attack_type)));
                }
                else
                {
                    txt(i18n::s.get(
                        "core.magic.special_attack.other",
                        subject,
                        i18n::s.get_enum(
                            "core.ui.cast_style",
                            subject.special_attack_type)));
                }
            }
        }
        else if (efid == 601)
        {
            if (is_in_fov(subject))
            {
                if (target.index >= 16)
                {
                    game_data.proc_damage_events_flag = 2;
                    txt(i18n::s.get(
                        "core.magic.sucks_blood.other", subject, target));
                }
                else
                {
                    txt(i18n::s.get(
                        "core.magic.sucks_blood.ally", subject, target));
                }
            }
        }
        else if (efid == 660)
        {
            if (is_in_fov(subject))
            {
                txt(i18n::s.get("core.magic.disassembly"));
            }
        }
        else if (is_in_fov(subject))
        {
            if (target.index >= 16)
            {
                game_data.proc_damage_events_flag = 2;
                txt(i18n::s.get(
                    "core.magic.touch.other",
                    subject,
                    target,
                    elename(ele),
                    _melee(2, subject.melee_attack_type),
                    _melee(0, subject.melee_attack_type)));
            }
            else
            {
                txt(i18n::s.get(
                    "core.magic.touch.ally",
                    subject,
                    target,
                    elename(ele),
                    _melee(2, subject.melee_attack_type),
                    _melee(1, subject.melee_attack_type)));
            }
        }
        if (efid == 660)
        {
            target.hp = target.max_hp / 12 + 1;
            return true;
        }
        damage_hp(target, roll(dice1, dice2, bonus), subject.index, ele, elep);
        if (efid == 617)
        {
            status_ailment_damage(target, StatusAilment::fear, elep);
        }
        if (efid == 618)
        {
            status_ailment_damage(target, StatusAilment::sleep, elep);
        }
        if (efid == 614)
        {
            target.nutrition -= 800;
            if (is_in_fov(target))
            {
                txt(i18n::s.get("core.magic.hunger", target),
                    Message::color{ColorIndex::purple});
            }
            get_hungry(target);
        }
        if (efid == 613)
        {
            p = rnd(10);
            if ((target.quality >= Quality::miracle && rnd(4)) ||
                enchantment_find(target, 60010 + p))
            {
                p = -1;
            }
            if (p != -1)
            {
                i = sdata.get(10 + p, target.index).original_level +
                    target.attr_adjs[p];
                if (i > 0)
                {
                    i = i * efp / 2000 + 1;
                    target.attr_adjs[p] -= i;
                }
                if (is_in_fov(target))
                {
                    txt(i18n::s.get("core.magic.weaken", target),
                        Message::color{ColorIndex::purple});
                }
                chara_refresh(target);
            }
        }
        return true;
    case 7:
        if (subject.index == 0)
        {
            if (game_data.crowd_density + 100 >= ELONA_MAX_OTHER_CHARACTERS)
            {
                txt(i18n::s.get("core.common.nothing_happens"));
                obvious = 0;
                return true;
            }
        }
        p = 3;
        efp = (efp / 25 + efp * efp / 10000 + subject.level) / 2;
        if (efp < 1)
        {
            efp = 1;
        }
        if (efid == 641)
        {
            efp = 15 + rnd(8);
        }
        if (efid == 639)
        {
            efp = 2 + rnd(18);
        }
        if (efid == 642)
        {
            efp = 15 + rnd(15);
        }
        if (efid == 640)
        {
            efp = 5 + rnd(12);
        }
        if (efid == 643)
        {
            p = 10;
        }
        for (int cnt = 0, cnt_end = (1 + rnd(p(0))); cnt < cnt_end; ++cnt)
        {
            flt(calcobjlv(efp), Quality::good);
            int chara_id = 0;
            if (efid == 425)
            {
                fltn(u8"wild"s);
            }
            if (efid == 642)
            {
                fltn(u8"fire"s);
            }
            if (efid == 641)
            {
                fltn(u8"pawn"s);
            }
            if (efid == 639)
            {
                fltn(u8"cat"s);
            }
            if (efid == 640)
            {
                fltn(u8"yeek"s);
            }
            if (efid == 643)
            {
                chara_id = 176;
            }
            if (const auto chara = chara_create(
                    -1, chara_id, target.position.x, target.position.y))
            {
                if (efid != 643)
                {
                    if (chara->id == subject.id)
                    {
                        chara_vanquish(*chara);
                        --cnt;
                        continue;
                    }
                }
            }
        }
        if (is_in_fov(subject))
        {
            txt(i18n::s.get("core.magic.summon"));
        }
        return true;
    case 5: {
        if (game_data.mount != 0)
        {
            if (game_data.mount == target.index)
            {
                return true;
            }
        }
        auto target_index = target.index;
        if (efid == 408)
        {
            target_index = subject.index;
        }
        if (efid == 619)
        {
            telex = cdata[target_index].position.x;
            teley = cdata[target_index].position.y;
            target_index = subject.index;
            if (game_data.mount != 0 && game_data.mount == target_index)
            {
                return true;
            }
        }
        if (efid == 620)
        {
            telex = subject.position.x;
            teley = subject.position.y;
        }
        if (efid == 409 || efid == 635)
        {
            if (cell_data.at(tlocx, tlocy).chara_index_plus_one == 0)
            {
                txt(i18n::s.get("core.common.nothing_happens"));
                obvious = 0;
                return true;
            }
            target_index = cell_data.at(tlocx, tlocy).chara_index_plus_one - 1;
        }
        if (map_prevents_teleport())
        {
            if (is_in_fov(cdata[target_index]))
            {
                txt(i18n::s.get("core.magic.teleport.prevented"));
            }
            return true;
        }
        if (efid != 619 && efid != 635 &&
            enchantment_find(cdata[target_index], 22))
        {
            if (is_in_fov(cdata[target_index]))
            {
                txt(i18n::s.get("core.magic.teleport.prevented"));
            }
            return true;
        }
        if (efid == 635)
        {
            if (enchantment_find(subject, 22))
            {
                if (is_in_fov(cdata[target_index]))
                {
                    txt(i18n::s.get("core.magic.teleport.prevented"));
                }
                return true;
            }
            p = rnd_capped(cdata[target_index].gold / 10 + 1);
            if (rnd_capped(sdata(13, target_index)) >
                    rnd_capped(sdata(12, subject.index) * 4) ||
                cdata[target_index].is_protected_from_thieves() == 1)
            {
                txt(i18n::s.get(
                    "core.magic.teleport.suspicious_hand.prevented",
                    cdata[target_index]));
                p = 0;
            }
            if (p != 0)
            {
                snd("core.paygold1");
                cdata[target_index].gold -= p;
                txt(i18n::s.get(
                    "core.magic.teleport.suspicious_hand.succeeded",
                    subject,
                    cdata[target_index],
                    p(0)));
                earn_gold(subject, p);
            }
            target_index = subject.index;
            if (game_data.mount != 0)
            {
                if (game_data.mount == target_index)
                {
                    return true;
                }
            }
        }
        if (is_in_fov(cdata[target_index]))
        {
            snd_at("core.teleport1", cdata[target_index].position);
        }
        tx = cdata[target_index].position.x;
        ty = cdata[target_index].position.y;
        efidprev = efid;
        for (int cnt = 0; cnt < 200; ++cnt)
        {
            if (efidprev == 410 || efidprev == 627)
            {
                p(0) = -1;
                p(1) = 1;
                cdata[target_index].next_position.x =
                    cdata[target_index].position.x +
                    (3 - cnt / 70 + rnd(5)) * p(rnd(2));
                cdata[target_index].next_position.y =
                    cdata[target_index].position.y +
                    (3 - cnt / 70 + rnd(5)) * p(rnd(2));
            }
            else if (efidprev == 619)
            {
                cdata[target_index].next_position.x =
                    telex + rnd((cnt / 8 + 2)) - rnd((cnt / 8 + 2));
                cdata[target_index].next_position.y =
                    teley + rnd((cnt / 8 + 2)) - rnd((cnt / 8 + 2));
            }
            else if (efidprev == 620)
            {
                cdata[target_index].next_position.x =
                    telex + rnd((cnt / 8 + 2)) - rnd((cnt / 8 + 2));
                cdata[target_index].next_position.y =
                    teley + rnd((cnt / 8 + 2)) - rnd((cnt / 8 + 2));
            }
            else
            {
                cdata[target_index].next_position.x =
                    rnd(map_data.width - 2) + 1;
                cdata[target_index].next_position.y =
                    rnd(map_data.height - 2) + 1;
            }
            cell_check(
                cdata[target_index].next_position.x,
                cdata[target_index].next_position.y);
            if (cellaccess == 1)
            {
                if (efidprev == 619)
                {
                    if (is_in_fov(subject))
                    {
                        txt(i18n::s.get(
                            "core.magic.teleport.shadow_step",
                            subject,
                            target));
                    }
                }
                else if (efidprev == 620)
                {
                    if (is_in_fov(subject))
                    {
                        txt(i18n::s.get(
                            "core.magic.teleport.draw_shadow",
                            cdata[target_index]));
                    }
                }
                else if (is_in_fov(subject))
                {
                    if (efidprev == 635)
                    {
                        txt(i18n::s.get(
                            "core.magic.teleport.suspicious_hand.after"));
                    }
                    else
                    {
                        txt(i18n::s.get(
                            "core.magic.teleport.disappears",
                            cdata[target_index]));
                    }
                }
                subject.activity.finish();
                move_character(cdata[target_index]);
                if (target_index == 0)
                {
                    update_screen();
                }
                break;
            }
        }
        return true;
    }
    case 8:
        int stat =
            get_route(subject.position.x, subject.position.y, tlocx, tlocy);
        if (stat == 0)
        {
            return true;
        }
        std::string valn;
        if (ele)
        {
            valn = i18n::s.get(
                "core.magic.breath.named",
                the_ability_db.get_text(ele, "name"));
        }
        else
        {
            valn = i18n::s.get("core.magic.breath.no_element");
        }
        if (is_in_fov(subject))
        {
            txt(i18n::s.get("core.magic.breath.bellows", subject, valn));
        }
        breath_list(subject.position);
        BreathAnimation(subject.position, {tlocx, tlocy}, ele).play();
        for (int cnt = 0, cnt_end = (maxbreath); cnt < cnt_end; ++cnt)
        {
            dx = breathlist(0, cnt);
            dy = breathlist(1, cnt);
            if (!fov_los(subject.position, {dx, dy}))
            {
                continue;
            }
            if (dx == subject.position.x && dy == subject.position.y)
            {
                continue;
            }
            if (ele == 50)
            {
                mapitem_fire(subject, dx, dy);
            }
            if (ele == 51)
            {
                mapitem_cold(dx, dy);
            }
            if (cell_data.at(dx, dy).chara_index_plus_one != 0)
            {
                const auto target_index =
                    cell_data.at(dx, dy).chara_index_plus_one - 1;
                if (subject.index != target_index)
                {
                    dmg = roll(dice1, dice2, bonus);
                    if (is_in_fov(cdata[target_index]))
                    {
                        if (target_index >= 16)
                        {
                            game_data.proc_damage_events_flag = 2;
                            txt3rd = 1;
                            txt(i18n::s.get(
                                "core.magic.breath.other",
                                cdata[target_index]));
                        }
                        else
                        {
                            txt(i18n::s.get(
                                "core.magic.breath.ally", cdata[target_index]));
                        }
                    }
                    damage_hp(
                        cdata[target_index], dmg, subject.index, ele, elep);
                }
            }
        }
        return true;
    }
}



bool _proc_magic(
    Character& subject,
    Character& target,
    const OptionalItemRef& efitem,
    int efid,
    int& fltbk,
    int& valuebk)
{
    switch (efid)
    {
    case 636: return _magic_636(subject, target);
    case 1136: assert(efitem); return _magic_1136(*efitem);
    case 1135: return _magic_1135(target);
    case 654: return _magic_654(subject, target);
    case 626: return _magic_626(target);
    case 1101: return _magic_1101(subject, target);
    case 1102: return _magic_1102(target);
    case 1116: return _magic_1116(target);
    case 1103: return _magic_1103(target);
    case 1146: return _magic_1146(target);
    case 1147: return _magic_1147(target);
    case 1142: return _magic_1142(target);
    case 1130: return _magic_1130(target);
    case 300: return _magic_300(subject, target);
    case 301: return _magic_301(subject, target);
    case 183: return _magic_183(subject, efitem.clone());
    case 184: assert(efitem); return _magic_184(subject, *efitem);
    case 185: assert(efitem); return _magic_185(subject, *efitem);
    case 406:
    case 407: return _magic_406_407(subject, target);
    case 1120: return _magic_1120(target);
    case 1117: return _magic_1117(target);
    case 632:
    case 454:
    case 1144: return _magic_632_454_1144(subject, target);
    case 1121: return _magic_1121(subject, target);
    case 411: return _magic_411(subject);
    case 461: return _magic_461(subject);
    case 412: return _magic_412(subject, target);
    case 413: return _magic_413(target);
    case 1104: return _magic_1104(target);
    case 1143: return _magic_1143(target);
    case 1105: return _magic_1105(target);
    case 1107: return _magic_1107(target);
    case 1119: return _magic_1119(target);
    case 1106: return _magic_1106(target);
    case 1139: return _magic_1139(target);
    case 1113: return _magic_1113(target);
    case 653: return _magic_653(target);
    case 430:
    case 429: return _magic_430_429(target);
    case 658: return _magic_658(subject, target);
    case 440:
    case 439: return _magic_440_439(target);
    case 441: return _magic_441(subject);
    case 1141: return _magic_1141(target);
    case 428: return _magic_428(target);
    case 621: return _magic_621(target);
    case 624: return _magic_624(target);
    case 1108: return _magic_1108(target);
    case 1111: return _magic_1111(target);
    case 1109: return _magic_1109(target);
    case 1110: return _magic_1110(target);
    case 1112: return _magic_1112(target);
    case 645:
    case 1114: return _magic_645_1114(subject, target);
    case 1118: return _magic_1118(target);
    case 1138:
    case 1123:
    case 1122:
    case 1137: return _magic_1138_1123_1122_1137(subject);
    case 435: return _magic_435(subject, target);
    case 436:
    case 437:
    case 455:
    case 634:
    case 456: return _magic_436_437_455_634_456(subject);
    case 1145: return _magic_1145(subject);
    case 49: assert(efitem); return _magic_49(subject, *efitem);
    case 21:
    case 1127: return _magic_21_1127(subject);
    case 1128: return _magic_1128(subject);
    case 1124:
    case 1125: return _magic_1124_1125(subject);
    case 630:
    case 1129: return _magic_630_1129(subject);
    case 629: return _magic_629(subject);
    case 628: return _magic_628(subject, target);
    case 1140: return _magic_1140(subject);
    case 1132: return _magic_1132(subject, fltbk, valuebk);
    case 457:
    case 438: return _magic_457_438();
    case 631: return _magic_631(subject);
    case 659: return _magic_659(subject);
    case 466: return _magic_466(subject);
    case 657: return _magic_657(subject);
    case 465: return _magic_465(subject);
    case 656: return _magic_656(subject);
    case 1131: return _magic_1131(target);
    case 633: return _magic_633(subject, target);
    case 638:
    case 648: return _magic_638_648(subject, target);
    case 652: return _magic_652(subject, target);
    case 1133: return _magic_1133(subject, target);
    case 651: return _magic_651(subject, target);
    case 464: return _magic_464(subject, target);
    case 463: return _magic_463();
    default: return true;
    }
}

} // namespace



namespace elona
{

bool magic(Character& subject, Character& target, const OptionalItemRef& efitem)
{
    int fltbk = 0;
    int valuebk = 0;
    efcancel = 0;
    obvious = 1;
    if (efsource != 4 && efsource != 1 && efsource != 2)
    {
        efstatus = CurseState::none;
    }
    efsource = 0;

    lib::scope_guard restore([&]() {
        efstatus = CurseState::none;
        efsource = 0;
    });

    if (efid >= 300)
    {
        if (efid < 661)
        {
            if (const auto ret = _proc_general_magic(subject, target))
            {
                return *ret;
            }
        }
        else
        {
            if (efstatus == CurseState::blessed)
            {
                efp = efp * 150 / 100;
            }
            if (is_cursed(efstatus))
            {
                efp = 50;
            }
        }
    }

    return _proc_magic(subject, target, efitem, efid, fltbk, valuebk);
}

} // namespace elona

#include "command.hpp"

#include "../snail/application.hpp"
#include "ability.hpp"
#include "activity.hpp"
#include "animation.hpp"
#include "area.hpp"
#include "attack.hpp"
#include "audio.hpp"
#include "autopick.hpp"
#include "buff.hpp"
#include "building.hpp"
#include "calc.hpp"
#include "casino.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "config.hpp"
#include "crafting.hpp"
#include "ctrl_file.hpp"
#include "data/types/type_item.hpp"
#include "debug.hpp"
#include "dmgheal.hpp"
#include "draw.hpp"
#include "enchantment.hpp"
#include "food.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "input_prompt.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "lua_env/interface.hpp"
#include "macro.hpp"
#include "magic.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "mef.hpp"
#include "menu.hpp"
#include "message.hpp"
#include "net.hpp"
#include "quest.hpp"
#include "random.hpp"
#include "save.hpp"
#include "shop.hpp"
#include "status_ailment.hpp"
#include "tcg.hpp"
#include "text.hpp"
#include "ui.hpp"
#include "variables.hpp"



namespace elona
{

namespace
{

int dbg_freemove;
int r3 = 0;
int noeffect = 0;
int inumbk = 0;



template <typename F>
bool any_of_characters_around_you(F predicate, bool ignore_pc = true)
{
    for (int dx = -1; dx <= 1; ++dx)
    {
        for (int dy = -1; dy <= 1; ++dy)
        {
            if (ignore_pc && dx == 0 && dy == 0)
            {
                continue;
            }
            const auto x = cdata.player().position.x + dx;
            const auto y = cdata.player().position.y + dy;
            const auto chara = cell_data.at(x, y).chara_index_plus_one - 1;
            if (chara != -1 && predicate(cdata[chara]))
            {
                return true;
            }
        }
    }

    return false;
}



void _search_for_crystal()
{
    p = 9999;
    for (const auto& item : inv.ground())
    {
        if (item.number() == 0)
        {
            continue;
        }
        if (item.own_state != 5)
        {
            continue;
        }
        if (item.id != ItemId::summoning_crystal)
        {
            continue;
        }
        if (p > dist(
                    item.position.x,
                    item.position.y,
                    cdata.player().position.x,
                    cdata.player().position.y))
        {
            p = dist(
                item.position.x,
                item.position.y,
                cdata.player().position.x,
                cdata.player().position.y);
        }
    }
    if (p != 9999)
    {
        while (1)
        {
            if (p <= 3)
            {
                txt(i18n::s.get("core.action.search.crystal.close"));
            }
            if (p <= 9)
            {
                txt(i18n::s.get("core.action.search.crystal.normal"));
                break;
            }
            if (p <= 16)
            {
                txt(i18n::s.get("core.action.search.crystal.far"));
                break;
            }
            txt(i18n::s.get("core.action.search.crystal.sense"));
            break;
        }
    }
}



void _try_to_reveal_small_coin()
{
    if (cdata[cc].position.x == x && cdata[cc].position.y == y)
    {
        snd("core.ding2");
        txt(i18n::s.get("core.action.search.small_coin.find"));
        cell_data.at(x, y).feats = 0;
        flt();
        itemcreate_extra_inv(622, x, y, 0);
    }
    else
    {
        if (dist(cdata[cc].position.x, cdata[cc].position.y, x, y) > 2)
        {
            txt(i18n::s.get("core.action.search.small_coin.far"));
        }
        else
        {
            txt(i18n::s.get("core.action.search.small_coin.close"));
        }
    }
}



void _search_for_map_feats()
{
    cell_featread(x, y);
    refx = x;
    refy = y;
    if (std::abs(cdata[cc].position.y - y) <= 1 &&
        std::abs(cdata[cc].position.x - x) <= 1)
    {
        if (feat(1) == 14)
        {
            if (feat(0) == 0)
            {
                int stat = try_to_reveal();
                if (stat == 1)
                {
                    discover_trap();
                    txt(i18n::s.get("core.action.search.discover.trap"));
                }
            }
        }
        if (feat(1) == 22)
        {
            int stat = try_to_reveal();
            if (stat == 1 || 0)
            {
                discover_hidden_path();
                txt(i18n::s.get("core.action.search.discover.hidden_path"));
            }
        }
    }
    if (feat(1) == 32)
    {
        if (game_data.current_map != mdata_t::MapId::show_house)
        {
            _try_to_reveal_small_coin();
        }
    }
}



void _search_surroundings()
{
    for (int cnt = 0; cnt < 11; ++cnt)
    {
        y = cdata[cc].position.y + cnt - 5;
        if (y < 0 || y >= map_data.height)
        {
            continue;
        }
        for (int cnt = 0; cnt < 11; ++cnt)
        {
            x = cdata[cc].position.x + cnt - 5;
            if (x < 0 || x >= map_data.width)
            {
                continue;
            }
            if (cell_data.at(x, y).feats != 0)
            {
                _search_for_map_feats();
            }
        }
    }
}



void _proc_manis_disassembly(Character& chara)
{
    if (feat(1) == 14 && feat(0) == tile_trap && chara.index == 0 &&
        chara.god_id == core_god::mani)
    {
        disarm_trap(chara, chara.position.x, chara.position.y);
    }
}



void _dig_material_spot()
{
    rowactre(0) = 1;
    rowactre(1) = cdata[cc].position.x;
    rowactre(2) = cdata[cc].position.y;
    if (feat(1) == 24)
    {
        spot_digging();
    }
    if (feat(1) == 27)
    {
        spot_digging();
    }
    if (feat(1) == 26)
    {
        spot_fishing();
    }
    if (feat(1) == 25)
    {
        spot_mining_or_wall();
    }
    if (feat(1) == 28)
    {
        spot_material();
    }
}



TurnResult _pre_proc_movement_event()
{
    if (map_data.type == mdata_t::MapType::world_map)
    {
        if (264 <= cell_data
                       .at(cdata[cc].next_position.x, cdata[cc].next_position.y)
                       .chip_id_actual &&
            cell_data.at(cdata[cc].next_position.x, cdata[cc].next_position.y)
                    .chip_id_actual < 363)
        {
            return TurnResult::pc_turn_user_error;
        }
    }
    return proc_movement_event();
}



TurnResult _bump_into_character()
{
    tc = cellchara;
    if (cdata[tc].relationship >= 10 ||
        (cdata[tc].relationship == -1 && !g_config.attack_neutral_npcs()) ||
        (cdata[tc].relationship == 0 &&
         (area_data[game_data.current_map].is_museum_or_shop() ||
          is_modifier_pressed(snail::ModKey::shift))))
    {
        if (cdata[tc].is_hung_on_sand_bag() == 0)
        {
            if (map_data.type == mdata_t::MapType::world_map)
            {
                return _pre_proc_movement_event();
            }
            if (g_config.scroll())
            {
                cdata.player().next_position.x = cdata[tc].position.x;
                cdata.player().next_position.y = cdata[tc].position.y;
                ui_scroll_screen();
            }
            cell_swap(cc, tc);
            txt(i18n::s.get("core.action.move.displace.text", cdata[tc]));
            if (cdata[tc].id == CharaId::rogue)
            {
                if (rnd(5) == 0)
                {
                    if (cdata[tc].sleep == 0)
                    {
                        p = rnd(clamp(cdata[cc].gold, 0, 20) + 1);
                        if (cdata[cc].is_protected_from_thieves())
                        {
                            p = 0;
                        }
                        if (p != 0)
                        {
                            snd("core.getgold1");
                            cdata[cc].gold -= p;
                            earn_gold(cdata[tc], p);
                            txt(i18n::s.get(
                                "core.action.move.displace.dialog"));
                        }
                    }
                }
            }
            if (cdata[tc].activity.type == Activity::Type::eat)
            {
                if (cdata[tc].activity.turn > 0)
                {
                    txt(i18n::s.get("core.action.move.interrupt", cdata[tc]));
                    cdata[tc].activity.type = Activity::Type::none;
                    cdata[tc].activity.turn = 0;
                }
            }
            sense_map_feats_on_move();
            return TurnResult::turn_end;
        }
    }
    if (running)
    {
        if (cdata[tc].relationship >= -2 || keybd_wait >= 40)
        {
            return TurnResult::pc_turn_user_error;
        }
    }
    if (cdata[tc].relationship <= -1)
    {
        cdata.player().enemy_id = tc;
        if (cdata[tc].is_invisible() == 1)
        {
            if (cdata.player().can_see_invisible() == 0)
            {
                if (cdata[tc].wet == 0)
                {
                    cdata.player().enemy_id = 0;
                }
            }
        }
        if (keybd_attacking == 0)
        {
            keybd_wait = 1;
            keybd_attacking = 1;
        }
        try_to_melee_attack();
        return TurnResult::turn_end;
    }
    talk_to_npc();
    if (chatteleport == 1)
    {
        chatteleport = 0;
        return TurnResult::exit_map;
    }
    return TurnResult::turn_end;
}

} // namespace



// TODO organize by order in pc_turn()



elona_vector1<int> fsetbarrel;
elona_vector1<int> isetgiftminor;
elona_vector1<int> isetgiftmajor;
elona_vector1<int> isetgiftgrand;


int refdiff = 0;



// see attack.cpp
extern int tglocx;
extern int tglocy;



TurnResult do_give_command()
{
    txt(i18n::s.get("core.action.which_direction.default"));
    update_screen();
    int stat = ask_direction();
    if (stat == 0)
    {
        txt(i18n::s.get("core.ui.invalid_target"));
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    tc = cell_data.at(x, y).chara_index_plus_one;
    if (tc == 0)
    {
        txt(i18n::s.get("core.ui.invalid_target"));
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    tc -= 1;
    if (tc == 0)
    {
        if (game_data.mount != 0)
        {
            tc = game_data.mount;
        }
    }
    if (tc != 0)
    {
        if (tc < 16)
        {
            if (!cdata[tc].is_escorted() &&
                !cdata[tc].is_escorted_in_sub_quest())
            {
                return try_interact_with_npc();
            }
        }
        update_screen();
        invctrl = 10;
        snd("core.inv");
        MenuResult mr = ctrl_inventory();
        assert(mr.turn_result != TurnResult::none);
        return mr.turn_result;
    }
    txt(i18n::s.get("core.ui.invalid_target"));
    update_screen();
    return TurnResult::pc_turn_user_error;
}



TurnResult do_interact_command()
{
    txt(i18n::s.get("core.action.interact.choose"));
    int stat = ask_direction();
    if (stat == 0)
    {
        txt(i18n::s.get("core.ui.invalid_target"));
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    tc = cell_data.at(x, y).chara_index_plus_one;
    if (tc == 0)
    {
        txt(i18n::s.get("core.ui.invalid_target"));
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    tc -= 1;
    txt(i18n::s.get("core.action.interact.prompt", cdata[tc]));
    p = 0;

    Prompt prompt("core.action.interact.choices");
    if (tc != 0)
    {
        if (cdata.player().confused == 0)
        {
            prompt.append("talk", 0);
            prompt.append("attack", 1);
        }
        if (cdata[tc].is_escorted() == 0)
        {
            if (cdata[tc].is_escorted_in_sub_quest() == 0)
            {
                if (tc < 16)
                {
                    prompt.append("inventory", 4);
                }
                else
                {
                    prompt.append("give", 2);
                }
                if (cdata[tc].is_livestock() == 1)
                {
                    prompt.append("bring_out", 5);
                }
                if (tc < 16)
                {
                    prompt.append("appearance", 8);
                }
            }
        }
        prompt.append("teach_words", 7);
        prompt.append("change_tone", 10);
        if (game_data.current_map != mdata_t::MapId::show_house)
        {
            if (cdata[tc].is_hung_on_sand_bag())
            {
                prompt.append("release", 9);
            }
        }
    }
    prompt.append("name", 3);
    if (0 || game_data.wizard)
    {
        prompt.append("info", 6);
    }
    {
        int stat = prompt.query(promptx, prompty, 200);
        if (stat == -1)
        {
            update_screen();
            return TurnResult::pc_turn_user_error;
        }
        rtval = stat;
    }
    screenupdate = -1;
    p = rtval;
    if (p == 0)
    {
        update_screen();
        talk_to_npc();
        if (chatteleport == 1)
        {
            chatteleport = 0;
            return TurnResult::exit_map;
        }
        else
        {
            return TurnResult::turn_end;
        }
    }
    if (p == 1)
    {
        update_screen();
        try_to_melee_attack();
        return TurnResult::turn_end;
    }
    if (p == 2)
    {
        update_screen();
        invctrl = 10;
        snd("core.inv");
        MenuResult mr = ctrl_inventory();
        assert(mr.turn_result != TurnResult::none);
        return mr.turn_result;
    }
    if (p == 3)
    {
        update_screen();
        return call_npc();
    }
    if (p == 4)
    {
        return try_interact_with_npc();
    }
    if (p == 5)
    {
        rc = tc;
        new_ally_joins();
        update_screen();
        return TurnResult::turn_end;
    }
    if (p == 6)
    {
        snd("core.pop2");
        cc = tc;
        menu_character_sheet_investigate();
        cc = 0;
        return TurnResult::pc_turn_user_error;
    }
    if (p == 7)
    {
        txt(i18n::s.get("core.action.interact.change_tone.prompt", cdata[tc]));
        inputlog = "";
        input_text_dialog((windoww - 360) / 2 + inf_screenx, winposy(90), 20);
        cdata[tc].has_custom_talk() = false;
        if (inputlog == ""s)
        {
            cdatan(4, tc) = "";
        }
        else
        {
            cdatan(4, tc) = inputlog;
            txt(""s + cdatan(4, tc), Message::color{ColorIndex::cyan});
        }
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    if (p == 8)
    {
        gsel(0);
        menu_change_appearance(cdata[tc]);
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    if (p == 9)
    {
        snd("core.build1");
        cdata[tc].is_hung_on_sand_bag() = false;
        txt(i18n::s.get("core.action.interact.release", cdata[tc]));
        flt();
        itemcreate_extra_inv(733, cdata[tc].position, 0);
    }
    if (p == 10)
    {
        change_npc_tone();
    }
    update_screen();
    return TurnResult::pc_turn_user_error;
}



TurnResult call_npc()
{
    txt(i18n::s.get("core.action.interact.name.prompt", cdata[tc]));
    inputlog = "";
    input_text_dialog((windoww - 220) / 2 + inf_screenx, winposy(90), 12);
    if (inputlog == ""s)
    {
        txt(i18n::s.get("core.action.interact.name.cancel"));
    }
    else
    {
        cdatan(0, tc) = ""s + inputlog;
        cdata[tc].has_own_name() = true;
        txt(i18n::s.get("core.action.interact.name.you_named", cdata[tc]));
    }
    gmode(2);
    update_screen();
    return TurnResult::pc_turn_user_error;
}



TurnResult do_bash_command()
{
    txt(i18n::s.get("core.action.bash.prompt"));
    int stat = ask_direction();
    if (stat == 0)
    {
        txt(i18n::s.get("core.common.it_is_impossible"));
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    return do_bash();
}



TurnResult do_dig_command()
{
    txt(i18n::s.get("core.action.dig.prompt"));
    int stat = ask_direction();
    if (stat == 0)
    {
        txt(i18n::s.get("core.common.it_is_impossible"));
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    refx = x;
    refy = y;
    tlocx = x;
    tlocy = y;
    if (tlocx == cdata.player().position.x)
    {
        if (tlocy == cdata.player().position.y)
        {
            rowactre = 0;
            spot_digging();
            return TurnResult::turn_end;
        }
    }
    if ((chip_data.for_cell(x, y).effect & 4) == 0 ||
        chip_data.for_cell(x, y).kind == 3 ||
        map_data.type == mdata_t::MapType::world_map)
    {
        txt(i18n::s.get("core.common.it_is_impossible"));
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    screenupdate = -1;
    update_screen();
    return do_dig_after_sp_check(cdata.player());
}



TurnResult do_search_command()
{
    txt(i18n::s.get("core.action.search.execute"), Message::only_once{true});
    if (game_data.current_map == mdata_t::MapId::show_house)
    {
        _search_for_crystal();
    }

    _search_surroundings();

    cell_featread(cdata[cc].position.x, cdata[cc].position.y);

    _proc_manis_disassembly(cdata[cc]);

    if (feat(1) >= 24 && feat(1) <= 28)
    {
        _dig_material_spot();
    }
    return TurnResult::turn_end;
}



TurnResult do_pray_command()
{
    if (const auto altar = item_find(60002))
    {
        ci = altar->index;
        int god_id_int = altar->param1;
        if (core_god::int2godid(god_id_int) != cdata.player().god_id)
        {
            begin_to_believe_god(god_id_int);
            return TurnResult::turn_end;
        }
    }
    return do_pray();
}



TurnResult do_throw_command()
{
    int ccthrowpotion = 0;
    if (is_in_fov(cdata[cc]))
    {
        txt(i18n::s.get("core.action.throw.execute", cdata[cc], inv[ci]));
    }
    if (dist(cdata[cc].position.x, cdata[cc].position.y, tlocx, tlocy) * 4 >
            rnd_capped(sdata(111, cc) + 10) + sdata(111, cc) / 4 ||
        rnd(10) == 0)
    {
        x = tlocx + rnd(2) - rnd(2);
        y = tlocy + rnd(2) - rnd(2);
        if (x >= 0)
        {
            if (y >= 0)
            {
                if (x < map_data.width)
                {
                    if (y < map_data.height)
                    {
                        if ((chip_data.for_cell(x, y).effect & 4) == 0)
                        {
                            tlocx = x;
                            tlocy = y;
                        }
                    }
                }
            }
        }
    }
    ThrowingObjectAnimation(
        {tlocx, tlocy}, cdata[cc].position, inv[ci].image, inv[ci].color)
        .play();
    ti = inv_getfreeid(-1);
    if (inv[ci].id == ItemId::monster_ball && ti != -1)
    {
        item_copy(ci, ti);
        inv[ti].position.x = tlocx;
        inv[ti].position.y = tlocy;
        inv[ti].set_number(1);
        inv[ci].modify_number(-1);
        ci = ti;
    }
    else
    {
        inv[ci].modify_number(-1);
    }
    if (cc == 0)
    {
        refresh_burden_state();
    }
    x = tlocx;
    y = tlocy;
    BreakingAnimation({x, y}).play();
    if (inv[ci].id == ItemId::monster_ball || inv[ci].id == ItemId::little_ball)
    {
        snd("core.throw2");
        cell_refresh(inv[ci].position.x, inv[ci].position.y);
        if (cell_data.at(tlocx, tlocy).chara_index_plus_one != 0)
        {
            tc = cell_data.at(tlocx, tlocy).chara_index_plus_one - 1;
            txt(i18n::s.get("core.action.throw.hits", cdata[tc]));
            if (inv[ci].id == ItemId::monster_ball)
            {
                if (tc < ELONA_MAX_PARTY_CHARACTERS ||
                    cdata[tc].character_role != 0 ||
                    cdata[tc].quality == Quality::special ||
                    cdata[tc].is_lord_of_dungeon() == 1)
                {
                    txt(i18n::s.get(
                        "core.action.throw.monster_ball.cannot_be_captured"));
                    return TurnResult::turn_end;
                }
                if (cdata[tc].level > inv[ci].param2)
                {
                    txt(i18n::s.get(
                        "core.action.throw.monster_ball.not_enough_power"));
                    return TurnResult::turn_end;
                }
                if (cdata[tc].hp > cdata[tc].max_hp / 10)
                {
                    txt(i18n::s.get(
                        "core.action.throw.monster_ball.not_weak_enough"));
                    return TurnResult::turn_end;
                }
                txt(i18n::s.get(
                        "core.action.throw.monster_ball.capture", cdata[tc]),
                    Message::color{ColorIndex::green});
                animeload(8, tc);
                inv[ci].subname = charaid2int(cdata[tc].id);
                inv[ci].param3 = cdata[tc].level;
                inv[ci].weight = clamp(cdata[tc].weight, 10000, 100000);
                inv[ci].value = 1000;
            }
            else
            {
                if (cdata[tc].id != CharaId::little_sister || tc < 16)
                {
                    txt(i18n::s.get("core.common.nothing_happens"));
                    return TurnResult::turn_end;
                }
                if (map_prevents_monster_ball())
                {
                    txt(i18n::s.get(
                        "core.action.throw.monster_ball.does_not_work"));
                    return TurnResult::turn_end;
                }
                rc = tc;
                new_ally_joins();
            }
            chara_vanquish(tc);
            quest_check();
        }
        return TurnResult::turn_end;
    }
    if (the_item_db[itemid2int(inv[ci].id)]->category == ItemCategory::potion ||
        inv[ci].id == ItemId::tomato)
    {
        if (inv[ci].id != ItemId::empty_bottle)
        {
            if (is_in_fov({tlocx, tlocy}))
            {
                if (inv[ci].id == ItemId::handful_of_snow)
                {
                    snd("core.snow");
                }
                else
                {
                    snd("core.crush2");
                }
            }
            if (cell_data.at(tlocx, tlocy).chara_index_plus_one != 0)
            {
                tc = cell_data.at(tlocx, tlocy).chara_index_plus_one - 1;
                if (is_in_fov(cdata[tc]))
                {
                    txt(i18n::s.get("core.action.throw.hits", cdata[tc]));
                    wet(tc, 25);
                }
                rowact_check(cdata[tc]);
                if (inv[ci].id == ItemId::handful_of_snow)
                {
                    if (is_in_fov(cdata[tc]))
                    {
                        if (tc != 0)
                        {
                            txt(i18n::s.get("core.action.throw.snow.dialog"),
                                Message::color{ColorIndex::cyan});
                        }
                    }
                    return TurnResult::turn_end;
                }
                if (inv[ci].id == ItemId::tomato)
                {
                    if (is_in_fov(cdata[tc]))
                    {
                        txt(i18n::s.get("core.action.throw.tomato"),
                            Message::color{ColorIndex::blue});
                    }
                    if (inv[ci].param3 == -1)
                    {
                        if (is_in_fov(cdata[tc]))
                        {
                            txt(i18n::s.get(
                                    "core.damage.is_engulfed_in_fury",
                                    cdata[tc]),
                                Message::color{ColorIndex::blue});
                        }
                        cdata[tc].furious += rnd(10) + 5;
                    }
                    return TurnResult::turn_end;
                }
                if (tc >= 16)
                {
                    hostileaction(cc, tc);
                }
                ccthrowpotion = cc;
                potionthrow = 100;
                cc = tc;
                item_db_on_drink(inv[ci], itemid2int(inv[ci].id));
                cc = ccthrowpotion;
                return TurnResult::turn_end;
            }
            if (inv[ci].id == ItemId::handful_of_snow)
            {
                if (cell_data.at(tlocx, tlocy).item_appearances_actual != 0)
                {
                    cell_itemlist(tlocx, tlocy);
                    f = 0;
                    for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
                    {
                        p = list(0, cnt);
                        if (inv[p].id == ItemId::snow_man)
                        {
                            if (is_in_fov({tlocx, tlocy}))
                            {
                                txt(i18n::s.get(
                                    "core.action.throw.snow.hits_snowman",
                                    inv[p(0)]));
                            }
                            inv[p].modify_number(-1);
                            f = 1;
                            break;
                        }
                    }
                    if (f == 1)
                    {
                        cell_refresh(tlocx, tlocy);
                        return TurnResult::turn_end;
                    }
                }
            }
            if (inv[ci].id == ItemId::handful_of_snow)
            {
                if (chip_data.for_cell(tlocx, tlocy).kind == 4)
                {
                    return TurnResult::turn_end;
                }
                if (is_in_fov({tlocx, tlocy}))
                {
                    txt(i18n::s.get("core.action.throw.snow.melts"));
                }
            }
            else if (is_in_fov({tlocx, tlocy}))
            {
                txt(i18n::s.get("core.action.throw.shatters"));
            }
            if (inv[ci].id == ItemId::tomato)
            {
                if (is_in_fov({tlocx, tlocy}))
                {
                    txt(i18n::s.get("core.action.throw.tomato"),
                        Message::color{ColorIndex::blue});
                }
                return TurnResult::turn_end;
            }
            efp = 50 + sdata(111, cc) * 10;
            if (inv[ci].id == ItemId::bottle_of_sulfuric)
            {
                mef_add(tlocx, tlocy, 3, 19, rnd(15) + 5, efp, cc);
                return TurnResult::turn_end;
            }
            if (inv[ci].id == ItemId::molotov)
            {
                mef_add(tlocx, tlocy, 5, 24, rnd(15) + 25, efp, cc);
                mapitem_fire(tlocx, tlocy);
                return TurnResult::turn_end;
            }
            mef_add(
                tlocx,
                tlocy,
                6,
                27,
                -1,
                efp,
                cc,
                itemid2int(inv[ci].id),
                static_cast<int>(inv[ci].curse_state), // TODO
                inv[ci].color);
            return TurnResult::turn_end;
        }
    }
    if (is_in_fov({tlocx, tlocy}))
    {
        txt(i18n::s.get("core.action.throw.shatters"));
        snd("core.crush2");
    }
    if (inv[ci].id == ItemId::kitty_bank)
    {
        flt();
        itemcreate_extra_inv(54, tlocx, tlocy, inv[ci].param1);
    }
    return TurnResult::turn_end;
}



TurnResult do_close_command()
{
    int stat = ask_direction_to_close();
    if (stat == 0)
    {
        txt(i18n::s.get("core.common.it_is_impossible"));
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    cell_featread(x, y);
    if (feat(1) != 20)
    {
        txt(i18n::s.get("core.action.close.nothing_to_close"));
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    if (cell_data.at(x, y).chara_index_plus_one != 0)
    {
        txt(i18n::s.get("core.action.close.blocked"));
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    cell_featset(x, y, tile_doorclosed, 21, -1, -1);
    txt(i18n::s.get("core.action.close.execute", cdata[cc]));
    return TurnResult::turn_end;
}



TurnResult do_change_ammo_command()
{
    f = 0;
    for (int cnt = 0; cnt < 30; ++cnt)
    {
        body = 100 + cnt;
        if (cdata[cc].body_parts[cnt] % 10000 == 0)
        {
            continue;
        }
        if (cdata[cc].body_parts[cnt] / 10000 == 11)
        {
            ci = cdata[cc].body_parts[cnt] % 10000 - 1;
            f = 1;
            break;
        }
    }
    if (f == 0)
    {
        txt(i18n::s.get("core.action.ammo.need_to_equip"));
        return TurnResult::pc_turn_user_error;
    }
    listmax = 0;
    cs = -1;
    for (int cnt = 0; cnt < 15; ++cnt)
    {
        if (inv[ci].enchantments[cnt].id == 0)
        {
            break;
        }
        enc = inv[ci].enchantments[cnt].id;
        i = enc / 10000;
        if (i != 0)
        {
            enc = enc % 10000;
            if (i == 9)
            {
                if (inv[ci].count == cnt)
                {
                    cs = cnt;
                }
                list(0, listmax) = cnt;
                ++listmax;
                continue;
            }
        }
    }
    if (listmax == 0)
    {
        inv[ci].count = -1;
        txt(i18n::s.get("core.action.ammo.is_not_capable", inv[ci]));
        return TurnResult::pc_turn_user_error;
    }
    snd("core.ammo");
    ++cs;
    if (cs >= listmax)
    {
        inv[ci].count = -1;
    }
    else
    {
        inv[ci].count = list(0, cs);
    }
    Message::instance().linebreak();
    txt(i18n::s.get("core.action.ammo.current") + ":");
    for (int cnt = 0, cnt_end = (listmax + 1); cnt < cnt_end; ++cnt)
    {
        if (cnt == 0)
        {
            s(0) = i18n::s.get("core.action.ammo.normal");
            s(1) = i18n::s.get("core.action.ammo.unlimited");
        }
        else
        {
            p = list(0, cnt - 1);
            i(0) = inv[ci].enchantments[p].power % 1000;
            i(1) = inv[ci].enchantments[p].power / 1000;
            s(0) = ammoname(inv[ci].enchantments[p].id % 10000);
            s(1) = ""s + i + u8"/"s + i(1);
        }
        s = s + u8":"s + s(1);
        if (inv[ci].count == cnt - 1)
        {
            s = u8"["s + s + u8"]"s;
            Message::instance().txtef(ColorIndex::blue);
        }
        else
        {
            s = u8" "s + s + u8" "s;
        }
        txt(u8" "s + s);
    }
    return TurnResult::pc_turn_user_error;
}



TurnResult do_offer_command()
{
    if (cdata.player().god_id == core_god::eyth)
    {
        txt(i18n::s.get("core.action.offer.do_not_believe"));
        return TurnResult::turn_end;
    }
    rowact_item(inv[ci]);
    item_separate(ci);
    txt(i18n::s.get(
        "core.action.offer.execute", inv[ci], god_name(cdata.player().god_id)));
    snd("core.offer2");
    const auto tcbk = tc(0);
    tc = 0;
    BrightAuraAnimation(cdata[tc].position, BrightAuraAnimation::Type::offering)
        .play();
    tc = tcbk;
    if (const auto altar = item_find(60002))
    {
        ti = altar->index;
    }
    else
    {
        return TurnResult::turn_end;
    }
    if (inv[ci].id == ItemId::corpse)
    {
        i = clamp(inv[ci].weight / 200, 1, 50);
        if (inv[ci].param3 < 0)
        {
            i = 1;
        }
    }
    else
    {
        i = 25;
    }
    if (core_god::int2godid(inv[ti].param1) != cdata.player().god_id)
    {
        f = 0;
        if (inv[ti].param1 == 0)
        {
            f = 1;
            txt(i18n::s.get(
                "core.action.offer.claim", god_name(cdata.player().god_id)));
        }
        else
        {
            txt(i18n::s.get(
                "core.action.offer.take_over.attempt",
                god_name(cdata.player().god_id),
                god_name(inv[ti].param1)));
            if (rnd(17) <= i)
            {
                f = 1;
            }
            else
            {
                f = 0;
            }
        }
        if (f == 1)
        {
            god_modify_piety(i * 5);
            cdata.player().praying_point += i * 30;
            animode = 100;
            MiracleAnimation().play();
            snd("core.pray2");
            if (inv[ti].param1 != 0)
            {
                txt(i18n::s.get("core.action.offer.take_over.shadow"));
            }
            txt(i18n::s.get(
                    "core.action.offer.take_over.succeed",
                    god_name(cdata.player().god_id),
                    inv[ti]),
                Message::color{ColorIndex::orange});
            txtgod(cdata.player().god_id, 2);
            inv[ti].param1 = core_god::godid2int(cdata.player().god_id);
        }
        else
        {
            txt(i18n::s.get(
                "core.action.offer.take_over.fail", god_name(inv[ti].param1)));
            txtgod(core_god::int2godid(inv[ti].param1), 3);
            god_fail_to_take_over_penalty();
        }
    }
    else
    {
        if (i >= 15)
        {
            txt(i18n::s.get("core.action.offer.result.best", inv[ci]),
                Message::color{ColorIndex::green});
            txtgod(cdata.player().god_id, 4);
        }
        else if (i >= 10)
        {
            txt(i18n::s.get("core.action.offer.result.good", inv[ci]),
                Message::color{ColorIndex::green});
        }
        else if (i >= 5)
        {
            txt(i18n::s.get("core.action.offer.result.okay", inv[ci]),
                Message::color{ColorIndex::green});
        }
        else if (i >= 1)
        {
            txt(i18n::s.get("core.action.offer.result.poor", inv[ci]),
                Message::color{ColorIndex::green});
        }
        god_modify_piety(i);
        cdata.player().praying_point += i * 7;
    }
    inv[ci].modify_number((-inv[ci].number()));
    return TurnResult::turn_end;
}



TurnResult do_look_command()
{
    std::string action;
    page = 0;
    pagesize = 16;
    cs_bk = -1;
    build_target_list();
    if (listmax == 0)
    {
        txt(i18n::s.get("core.action.look.find_nothing"),
            Message::only_once{true});
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    cs = 0;
    for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
    {
        if (list(0, cnt) == cdata.player().enemy_id)
        {
            cs = cnt % pagesize;
            page = cnt / pagesize;
        }
    }

    bool init = true;
    while (true)
    {
        if (init)
        {
            init = false;
            cs_bk = -1;
            pagemax = (listmax - 1) / pagesize;
            if (page < 0)
            {
                page = pagemax;
            }
            else if (page > pagemax)
            {
                page = 0;
            }
        }

        if (cs != cs_bk)
        {
            screenupdate = -1;
            update_screen();
            keyrange = 0;
            font(20 - en * 2, snail::Font::Style::bold);
            for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
            {
                p = pagesize * page + cnt;
                if (p >= listmax)
                {
                    break;
                }
                key_list(cnt) = key_select(cnt);
                ++keyrange;
                x = list(1, p) - scx;
                y = list(2, p) - scy;
                if (cs == cnt)
                {
                    i = p;
                    get_route(
                        cdata[cc].position.x,
                        cdata[cc].position.y,
                        cdata[list(0, p)].position.x,
                        cdata[list(0, p)].position.y);
                    dx = (tlocx - scx) * inf_tiles + inf_screenx;
                    dy = (tlocy - scy) * inf_tiles + inf_screeny;
                    if (maxroute != 0)
                    {
                        dx = cdata[cc].position.x;
                        dy = cdata[cc].position.y;
                        for (int cnt = 0; cnt < 100; ++cnt)
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
                            sx = (dx - scx) * inf_tiles + inf_screenx;
                            sy = (dy - scy) * inf_tiles + inf_screeny;
                            if (sy + inf_tiles <= windowh - inf_verh)
                            {
                                snail::Application::instance()
                                    .get_renderer()
                                    .set_blend_mode(snail::BlendMode::blend);
                                snail::Application::instance()
                                    .get_renderer()
                                    .set_draw_color({255, 255, 255, 25});
                                snail::Application::instance()
                                    .get_renderer()
                                    .fill_rect(
                                        sx,
                                        sy * (sy > 0),
                                        inf_tiles -
                                            (sx + inf_tiles > windoww) *
                                                (sx + inf_tiles - windoww),
                                        inf_tiles + (sy < 0) * inf_screeny -
                                            (sy + inf_tiles >
                                             windowh - inf_verh) *
                                                (sy + inf_tiles - windowh +
                                                 inf_verh));
                            }
                        }
                    }
                    sx = x * inf_tiles + inf_screenx;
                    sy = y * inf_tiles + inf_screeny;
                    if (sy + inf_tiles <= windowh - inf_verh)
                    {
                        snail::Application::instance()
                            .get_renderer()
                            .set_blend_mode(snail::BlendMode::blend);
                        snail::Application::instance()
                            .get_renderer()
                            .set_draw_color({127, 127, 255, 50});
                        snail::Application::instance().get_renderer().fill_rect(
                            sx,
                            sy * (sy > 0),
                            inf_tiles,
                            inf_tiles + (sy < 0) * inf_screeny -
                                (sy + inf_tiles > windowh - inf_verh) *
                                    (sy + inf_tiles - windowh + inf_verh));
                    }
                }
                display_key(
                    x * inf_tiles + inf_screenx - 12,
                    y * inf_tiles + inf_screeny - 12,
                    cnt);
            }
            txttargetnpc(
                cdata[list(0, i)].position.x, cdata[list(0, i)].position.y);
            cs_bk = cs;
            render_hud();
            redraw();
        }
        if (action == "target")
        {
            // TODO will not be detected since input is in "menu" mode
            action = "select_"s + (cs + 1);
        }
        action = get_selected_item(p(0));
        if (p != -1)
        {
            cdata.player().enemy_id = p;
            snd("core.ok1");
            txt(i18n::s.get("core.action.look.target", cdata[p(0)]));
            update_screen();
            return TurnResult::pc_turn_user_error;
        }
        if (action == "next_page")
        {
            if (pagemax != 0)
            {
                snd("core.pop1");
                ++page;
                init = true;
                continue;
            }
        }
        if (action == "previous_page")
        {
            if (pagemax != 0)
            {
                snd("core.pop1");
                --page;
                init = true;
                continue;
            }
        }
        if (action == "cancel")
        {
            update_screen();
            return TurnResult::pc_turn_user_error;
        }
    }
}



TurnResult do_dip_command()
{
    if (inv[cidip].id == ItemId::bait)
    {
        item_separate(ci);
        inv[cidip].modify_number(-1);
        snd("core.equip1");
        txt(i18n::s.get(
            "core.action.dip.result.bait_attachment", inv[ci], inv[cidip]));
        if (inv[ci].param4 == inv[cidip].param1)
        {
            inv[ci].count += rnd(10) + 15;
        }
        else
        {
            inv[ci].count = rnd(10) + 15;
            inv[ci].param4 = inv[cidip].param1;
        }
        return TurnResult::turn_end;
    }
    snd("core.drink1");
    if (the_item_db[itemid2int(inv[cidip].id)]->category ==
        ItemCategory::potion)
    {
        if (the_item_db[itemid2int(inv[ci].id)]->subcategory == 60001)
        {
            item_separate(ci);
            inv[cidip].modify_number(-1);
            if (inv[cidip].id != ItemId::empty_bottle)
            {
                txt(i18n::s.get(
                    "core.action.dip.execute", inv[ci], inv[cidip]));
                if (inv[ci].id == ItemId::holy_well)
                {
                    txt(i18n::s.get(
                        "core.action.dip.result.holy_well_polluted"));
                    return TurnResult::turn_end;
                }
                if (inv[ci].param3 >= 20)
                {
                    txt(i18n::s.get(
                        "core.action.dip.result.well_dry", inv[ci]));
                    return TurnResult::turn_end;
                }
                txt(i18n::s.get(
                    "core.action.dip.result.well_refilled", inv[ci]));
                if (inv[cidip].id == ItemId::handful_of_snow)
                {
                    txt(i18n::s.get("core.action.dip.result.snow_melts.dip"));
                }
                else
                {
                    inv[ci].param1 += rnd(3);
                }
                return TurnResult::turn_end;
            }
            else
            {
                if (inv[ci].param1 < -5 || inv[ci].param3 >= 20 ||
                    (inv[ci].id == ItemId::holy_well &&
                     game_data.holy_well_count <= 0))
                {
                    txt(i18n::s.get(
                        "core.action.dip.result.natural_potion_dry", inv[ci]));
                    txt(i18n::s.get(
                        "core.action.dip.result.natural_potion_drop"));
                    return TurnResult::turn_end;
                }
                if (inv_getfreeid(0) == -1)
                {
                    txt(i18n::s.get("core.ui.inv.common.inventory_is_full"));
                    return TurnResult::turn_end;
                }
                if (inv[ci].id == ItemId::holy_well)
                {
                    --game_data.holy_well_count;
                    flt();
                    if (const auto item = itemcreate_player_inv(516, 0))
                    {
                        item->curse_state = CurseState::blessed;
                    }
                }
                else
                {
                    inv[ci].param1 -= 3;
                    flt(20);
                    flttypemajor = 52000;
                    itemcreate_player_inv(0, 0);
                }
                txt(i18n::s.get("core.action.dip.result.natural_potion"));
                txt(i18n::s.get("core.action.dip.you_get", inv[ci]));
                item_stack(0, inv[ci], true);
                return TurnResult::turn_end;
            }
        }
    }
    if (inv[cidip].id == ItemId::poison)
    {
        if (the_item_db[itemid2int(inv[ci].id)]->category == ItemCategory::food)
        {
            inv[cidip].modify_number(-1);
            item_separate(ci);
            txt(i18n::s.get(
                    "core.action.dip.result.love_food.made",
                    inv[ci],
                    inv[cidip]) +
                i18n::s.get("core.action.dip.result.love_food.grin"));
            if (is_cursed(inv[cidip].curse_state))
            {
                dipcursed(ci);
            }
            inv[ci].is_poisoned() = true;
            return TurnResult::turn_end;
        }
    }
    if (inv[cidip].id == ItemId::love_potion)
    {
        if (the_item_db[itemid2int(inv[ci].id)]->category == ItemCategory::food)
        {
            inv[cidip].modify_number(-1);
            item_separate(ci);
            txt(i18n::s.get(
                    "core.action.dip.result.love_food.made",
                    inv[ci],
                    inv[cidip]) +
                i18n::s.get("core.action.dip.result.love_food.guilty"));
            if (is_cursed(inv[cidip].curse_state))
            {
                dipcursed(ci);
            }
            inv[ci].is_aphrodisiac() = true;
            return TurnResult::turn_end;
        }
    }
    if (inv[cidip].id == ItemId::bottle_of_dye)
    {
        if (inv[cidip].curse_state == CurseState::blessed)
        {
            in = inv[cidip].number();
        }
        else
        {
            in = 1;
            item_separate(ci);
        }
        inv[cidip].modify_number(-1);
        inv[ci].color = inv[cidip].color;
        txt(i18n::s.get("core.action.dip.result.dyeing", inv[ci]));
        if (inv_getowner(ci) == -1)
        {
            cell_refresh(inv[ci].position.x, inv[ci].position.y);
        }
        if (inv[ci].body_part != 0)
        {
            create_pcpic(cdata[cc]);
        }
        return TurnResult::turn_end;
    }
    if (inv[cidip].id == ItemId::acidproof_liquid)
    {
        if (inv[cidip].curse_state == CurseState::blessed)
        {
            in = inv[cidip].number();
        }
        else
        {
            in = 1;
            item_separate(ci);
        }
        txt(i18n::s.get("core.action.dip.result.put_on", inv[ci], inv[cidip]));
        if (is_cursed(inv[cidip].curse_state))
        {
            dipcursed(ci);
        }
        else
        {
            inv[ci].is_acidproof() = true;
            txt(i18n::s.get("core.action.dip.result.gains_acidproof", inv[ci]));
        }
        inv[cidip].modify_number(-1);
        return TurnResult::turn_end;
    }
    if (inv[cidip].id == ItemId::fireproof_liquid)
    {
        if (inv[cidip].curse_state == CurseState::blessed)
        {
            in = inv[cidip].number();
        }
        else
        {
            in = 1;
            item_separate(ci);
        }
        txt(i18n::s.get("core.action.dip.result.put_on", inv[ci], inv[cidip]));
        if (is_cursed(inv[cidip].curse_state))
        {
            dipcursed(ci);
        }
        else if (inv[ci].id == ItemId::fireproof_blanket)
        {
            txt(i18n::s.get("core.action.dip.result.good_idea_but"));
        }
        else
        {
            inv[ci].is_fireproof() = true;
            txt(i18n::s.get("core.action.dip.result.gains_fireproof", inv[ci]));
        }
        inv[cidip].modify_number(-1);
        return TurnResult::turn_end;
    }
    if (inv[cidip].id == ItemId::bottle_of_water)
    {
        inv[cidip].modify_number(-1);
        if (inv[cidip].curse_state == CurseState::blessed)
        {
            txt(i18n::s.get("core.action.dip.result.becomes_blessed", inv[ci]),
                Message::color{ColorIndex::green});
            inv[ci].curse_state = CurseState::blessed;
            chara_refresh(cc);
            return TurnResult::turn_end;
        }
        if (is_cursed(inv[cidip].curse_state))
        {
            txt(i18n::s.get("core.action.dip.result.becomes_cursed", inv[ci]),
                Message::color{ColorIndex::purple});
            inv[ci].curse_state = CurseState::cursed;
            chara_refresh(cc);
            return TurnResult::turn_end;
        }
    }
    txt(i18n::s.get("core.common.nothing_happens"));
    return TurnResult::turn_end;
}



TurnResult do_use_command()
{
    screenupdate = -1;
    update_screen();
    tc = cc;
    tlocx = cdata[cc].position.x;
    tlocy = cdata[cc].position.y;
    auto item_data = the_item_db[itemid2int(inv[ci].id)];

    if (item_data->on_use_callback)
    {
        bool success = lua::call_with_result(
            *item_data->on_use_callback,
            false,
            lua::handle(inv[ci]),
            lua::handle(cdata[cc]));

        if (success)
        {
            return TurnResult::turn_end;
        }
        else
        {
            update_screen();
            return TurnResult::pc_turn_user_error;
        }
    }

    if (inv[ci].has_cooldown_time())
    {
        if (game_data.date.hours() < inv[ci].count)
        {
            txt(i18n::s.get(
                "core.action.use.useable_again_at", cnvdate(inv[ci].count)));
            update_screen();
            return TurnResult::pc_turn_user_error;
        }
        item_separate(ci);
        inv[ci].count = game_data.date.hours() + inv[ci].param3;
    }
    if (inv[ci].has_charge())
    {
        if (inv[ci].count <= 0)
        {
            txt(i18n::s.get("core.action.use.out_of_charge"));
            update_screen();
            return TurnResult::pc_turn_user_error;
        }
        item_separate(ci);
        --inv[ci].count;
    }
    if (item_data->subcategory == 58500)
    {
        return do_plant();
    }
    if (item_data->subcategory == 59500)
    {
        return blending_menu();
    }
    if (item_data->subcategory == 60004)
    {
        if (game_data.continuous_active_hours < 15)
        {
            txt(i18n::s.get("core.action.use.not_sleepy"));
            update_screen();
            return TurnResult::pc_turn_user_error;
        }
        game_data.activity_about_to_start = 100;
        activity_others(cdata[cc]);
        return TurnResult::turn_end;
    }
    if (inv[ci].id == ItemId::red_treasure_machine ||
        inv[ci].id == ItemId::blue_treasure_machine)
    {
        return do_gatcha(inv[ci]);
    }
    if (inv[ci].id == ItemId::pachisuro_machine ||
        inv[ci].id == ItemId::casino_table ||
        inv[ci].id == ItemId::slot_machine || inv[ci].id == ItemId::darts_board)
    {
        casino_dealer();
        return TurnResult::turn_end;
    }
    if (inv[ci].function == 1 || inv[ci].function == 2 ||
        inv[ci].function == 3 || inv[ci].function == 4)
    {
        prodtype = inv[ci].function;
        snd("core.pop2");
        invctrl = 0;
        crafting_menu();
        return TurnResult::turn_end;
    }
    if (inv[ci].is_alive())
    {
        if (inv[ci].param2 < calcexpalive(inv[ci].param1))
        {
            txt(i18n::s.get("core.action.use.living.needs_more_blood"));
        }
        else
        {
            Message::instance().linebreak();
            txt(i18n::s.get("core.action.use.living.ready_to_grow", inv[ci]));
            randomize(inv[ci].subname);
            if (inv[ci].param1 >= 4 + rnd(12))
            {
                txt(i18n::s.get("core.action.use.living.weird"));
            }
            txt(i18n::s.get("core.action.use.living.it"));
            reftype = (int)item_data->category;
            listmax = 0;

            Prompt prompt;
            for (int cnt = 0; cnt < 3; ++cnt)
            {
                randomize(inv[ci].subname + inv[ci].param1 * 10 + cnt);
                if (enchantment_add(
                        inv[ci],
                        enchantment_generate(enchantment_gen_level(4)),
                        enchantment_gen_p(),
                        0,
                        0,
                        1))
                {
                    if (rtval == 34)
                    {
                        if (rnd(3))
                        {
                            continue;
                        }
                    }
                    list(0, listmax) = rtval;
                    list(1, listmax) = rtval(1);
                    get_enchantment_description(
                        list(0, listmax),
                        list(1, listmax),
                        ItemCategory::unidentified);

                    prompt.append(s);

                    ++listmax;
                }
            }
            list(0, listmax) = -1;
            ++listmax;
            s = i18n::s.get("core.action.use.living.bonus");
            prompt.append(s);
            rtval = prompt.query(promptx, prompty, 400);
            Message::instance().linebreak();
            if (rtval == -1)
            {
                txt(i18n::s.get("core.action.use.living.displeased", inv[ci]));
            }
            else
            {
                if (list(0, rtval) == -1)
                {
                    ++inv[ci].enhancement;
                }
                else
                {
                    enchantment_add(
                        inv[ci], list(0, rtval), list(1, rtval), 0, 1);
                }
                txt(i18n::s.get("core.action.use.living.pleased", inv[ci]),
                    Message::color{ColorIndex::green});
                randomize(inv[ci].subname);
                if (inv[ci].param1 >= 4 + rnd(12))
                {
                    txt(i18n::s.get(
                        "core.action.use.living.becoming_a_threat"));
                    if (!enchantment_add(inv[ci], 45, 50))
                    {
                        inv[ci].enchantments[14].id = 0;
                        txt(i18n::s.get(
                            "core.action.use.living.removes_enchantment",
                            inv[ci]));
                    }
                }
                inv[ci].param2 = 0;
                ++inv[ci].param1;
            }
            randomize();
        }
        chara_refresh(cc);
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    switch (inv[ci].function)
    {
    case 24:
        x = cdata[cc].position.x;
        y = cdata[cc].position.y;
        if (map_data.type == mdata_t::MapType::world_map)
        {
            txt(i18n::s.get("core.action.use.mine.cannot_use_here"));
            update_screen();
            return TurnResult::pc_turn_user_error;
        }
        if (cell_data.at(x, y).feats != 0)
        {
            txt(i18n::s.get("core.action.use.mine.cannot_place_here"));
            return TurnResult::pc_turn_user_error;
        }
        inv[ci].modify_number(-1);
        cell_featset(x, y, 0, 14, 7, cc);
        txt(i18n::s.get("core.action.use.mine.you_set_up"));
        snd("core.build1");
        break;
    case 44:
        if (inv_getowner(ci) != -1)
        {
            txt(i18n::s.get("core.action.use.chair.needs_place_on_ground"));
            update_screen();
            return TurnResult::pc_turn_user_error;
        }
        {
            txt(i18n::s.get("core.action.use.chair.you_sit_on", inv[ci]));

            Prompt prompt("core.action.use.chair.choices");
            prompt.append("relax", 0);
            if (inv[ci].param1 != 1)
            {
                prompt.append("my_chair", 1);
            }
            if (inv[ci].param1 != 2)
            {
                prompt.append("guest_chair", 2);
            }
            if (inv[ci].param1 != 0)
            {
                prompt.append("free_chair", 3);
            }
            {
                int stat = prompt.query(promptx, prompty, 260);
                if (stat == -1)
                {
                    break;
                }
                rtval = stat;
            }
        }
        if (rtval == 0)
        {
            txt(i18n::s.get("core.action.use.chair.relax"));
            break;
        }
        if (rtval == 1)
        {
            txt(i18n::s.get("core.action.use.chair.my_chair", inv[ci]));
            inv[ci].param1 = 1;
            break;
        }
        if (rtval == 2)
        {
            txt(i18n::s.get("core.action.use.chair.guest_chair", inv[ci]));
            inv[ci].param1 = 2;
            break;
        }
        if (rtval == 3)
        {
            txt(i18n::s.get("core.action.use.chair.free_chair", inv[ci]));
            inv[ci].param1 = 0;
            break;
        }
        break;
    case 8:
        if (map_data.type != mdata_t::MapType::player_owned)
        {
            txt(i18n::s.get("core.action.use.house_board.cannot_use_it_here"));
            update_screen();
            return TurnResult::pc_turn_user_error;
        }
        screenupdate = -1;
        update_screen();
        return TurnResult::show_house_board;
    case 19: {
        int chara = -1;
        // Are there any of your pets around you?
        const auto alone = !any_of_characters_around_you(
            [](const auto& chara) { return chara.index < 16; });
        if (alone)
        {
            chara = 0;
        }
        else
        {
            txt(i18n::s.get("core.action.use.dresser.prompt"));
            int stat = ask_direction();
            if (stat != 0)
            {
                const auto cc = cell_data.at(x, y).chara_index_plus_one - 1;
                if (cc != -1 && cc < 16)
                {
                    chara = cc;
                }
            }
        }
        if (chara != -1)
        {
            tc = chara;
            screenupdate = -1;
            update_screen();
            change_appearance_equipment(cdata[tc]);
        }
        else
        {
            txt(i18n::s.get("core.common.it_is_impossible"));
        }
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    case 15:
        efid = 184;
        magic();
        break;
    case 16:
        efid = 185;
        magic();
        break;
    case 17:
        efid = 183;
        magic();
        break;
    case 14:
        if (cc == 0)
        {
            if (inv[ci].number() < 5)
            {
                txt(i18n::s.get("core.action.use.snow.need_more"));
                update_screen();
                return TurnResult::pc_turn_user_error;
            }
            inv[ci].modify_number(-5);
        }
        flt();
        itemcreate_extra_inv(541, cdata.player().position, 0);
        if (is_in_fov(cdata[cc]))
        {
            snd("core.snow");
            txt(i18n::s.get("core.action.use.snow.make_snowman", cdata[cc]));
        }
        break;
    case 13:
        snd("core.fire1");
        if (game_data.torch == 0)
        {
            game_data.torch = 1;
            txt(i18n::s.get("core.action.use.torch.light"));
        }
        else
        {
            game_data.torch = 0;
            txt(i18n::s.get("core.action.use.torch.put_out"));
        }
        chara_refresh(0);
        break;
    case 9: {
        if (read_textbook(inv[ci]))
        {
            return TurnResult::turn_end;
        }
        else
        {
            update_screen();
            return TurnResult::pc_turn_user_error;
        }
    }
    break;
    case 5:
        txt(i18n::s.get("core.action.use.stethoscope.prompt"));
        update_screen();
        {
            int stat = ask_direction();
            if (stat == 0)
            {
                txt(i18n::s.get("core.common.it_is_impossible"));
                update_screen();
                return TurnResult::pc_turn_user_error;
            }
        }
        tc = cell_data.at(x, y).chara_index_plus_one - 1;
        if (tc == 0)
        {
            txt(i18n::s.get("core.action.use.stethoscope.self"));
            game_data.chara_last_attacked_by_player = 0;
            return TurnResult::turn_end;
        }
        if (tc > 0 && tc < 16)
        {
            if (cdata[tc].state() == Character::State::alive)
            {
                game_data.chara_last_attacked_by_player = 0;
                if (cdata[tc].has_been_used_stethoscope() == 1)
                {
                    cdata[tc].has_been_used_stethoscope() = false;
                    txt(i18n::s.get(
                        "core.action.use.stethoscope.other.stop", cdata[tc]));
                    return TurnResult::turn_end;
                }
                txt(i18n::s.get(
                    "core.action.use.stethoscope.other.start.text", cdata[tc]));
                if (cdata[tc].sex == 1)
                {
                    txt(i18n::s.get(
                        "core.action.use.stethoscope.other.start.female.text",
                        cdata[tc]));
                    txt(i18n::s.get(
                            "core.action.use.stethoscope.other.start.female.dialog",
                            cdata[tc]),
                        Message::color{ColorIndex::blue});
                }
                cdata[tc].has_been_used_stethoscope() = true;
                return TurnResult::turn_end;
            }
        }
        txt(i18n::s.get("core.common.it_is_impossible"));
        update_screen();
        return TurnResult::pc_turn_user_error;
        break;
    case 23:
        txt(i18n::s.get("core.action.use.leash.prompt"));
        update_screen();
        {
            int stat = ask_direction();
            f = 0;
            if (stat != 0)
            {
                if (cell_data.at(x, y).chara_index_plus_one > 0)
                {
                    tc = cell_data.at(x, y).chara_index_plus_one - 1;
                    if (tc == 0)
                    {
                        txt(i18n::s.get("core.action.use.leash.self"));
                    }
                    else if (cdata[tc].is_leashed() == 0)
                    {
                        if (tc >= 16)
                        {
                            if (rnd(5) == 0)
                            {
                                txt(i18n::s.get(
                                    "core.action.use.leash.other.start.resists",
                                    cdata[tc]));
                                inv[ci].modify_number(-1);
                                cell_refresh(
                                    inv[ci].position.x, inv[ci].position.y);
                                refresh_burden_state();
                                break;
                            }
                        }
                        cdata[tc].is_leashed() = true;
                        txt(i18n::s.get(
                            "core.action.use.leash.other.start.text",
                            cdata[tc]));
                        txt(i18n::s.get(
                                "core.action.use.leash.other.start.dialog",
                                cdata[tc]),
                            Message::color{ColorIndex::cyan});
                    }
                    else
                    {
                        cdata[tc].is_leashed() = false;
                        txt(i18n::s.get(
                            "core.action.use.leash.other.stop.text",
                            cdata[tc]));
                        txt(i18n::s.get(
                                "core.action.use.leash.other.stop.dialog",
                                cdata[tc]),
                            Message::color{ColorIndex::cyan});
                    }
                    animeload(8, tc);
                    f = 1;
                }
            }
        }
        if (f == 0)
        {
            txt(i18n::s.get("core.common.it_is_impossible"));
        }
        break;
    case 45:
        if (game_data.current_map == mdata_t::MapId::show_house)
        {
            txt(i18n::s.get("core.action.use.sandbag.cannot_use_here"));
            update_screen();
            return TurnResult::pc_turn_user_error;
        }
        txt(i18n::s.get("core.action.use.sandbag.prompt"));
        update_screen();
        {
            int stat = ask_direction();
            f = 0;
            if (stat != 0)
            {
                if (cell_data.at(x, y).chara_index_plus_one > 0)
                {
                    tc = cell_data.at(x, y).chara_index_plus_one - 1;
                    if (cdata[tc].hp >= cdata[tc].max_hp / 5)
                    {
                        txt(i18n::s.get(
                            "core.action.use.sandbag.not_weak_enough"));
                        return TurnResult::pc_turn_user_error;
                    }
                    if (tc != 0)
                    {
                        if (tc < 16)
                        {
                            txt(i18n::s.get("core.action.use.sandbag.ally"));
                            return TurnResult::pc_turn_user_error;
                        }
                    }
                    if (cdata[tc].is_hung_on_sand_bag())
                    {
                        txt(i18n::s.get("core.action.use.sandbag.already"));
                        return TurnResult::pc_turn_user_error;
                    }
                    if (tc == 0)
                    {
                        txt(i18n::s.get("core.action.use.sandbag.self"));
                    }
                    else
                    {
                        snd("core.build1");
                        cdata[tc].is_hung_on_sand_bag() = true;
                        txt(i18n::s.get(
                            "core.action.use.sandbag.start", cdata[tc]));
                        txt(i18n::s.get(
                            "core.action.use.leash.other.start.dialog",
                            cdata[tc]));
                        animeload(8, tc);
                        inv[ci].modify_number(-1);
                        cell_refresh(inv[ci].position.x, inv[ci].position.y);
                        refresh_burden_state();
                    }
                    f = 1;
                }
            }
        }
        if (f == 0)
        {
            txt(i18n::s.get("core.common.it_is_impossible"));
        }
        break;
    case 6: {
        txt(i18n::s.get("core.action.use.music_disc.play", inv[ci]));
        auto music = inv[ci].param1 + 50 + 1;
        if (music > 97)
        {
            music = 97;
        }
        map_data.bgm = music;

        auto music_id = the_music_db.get_id_from_legacy(music);
        assert(music_id);
        if (!music_id)
        {
            break;
        }
        play_music(*music_id);
    }
    break;
    case 10:
        screenupdate = -1;
        update_screen();
        return TurnResult::play_scene;
    case 7:
        if (inv[ci].own_state != 3)
        {
            if (map_prevents_building_shelter())
            {
                if (game_data.current_map == mdata_t::MapId::fields)
                {
                    txt(i18n::s.get(
                        "core.action.use.shelter.only_in_world_map"));
                }
                else
                {
                    txt(i18n::s.get(
                        "core.action.use.shelter.cannot_build_it_here"));
                }
                update_screen();
                return TurnResult::pc_turn_user_error;
            }
            game_data.activity_about_to_start = 101;
            activity_others(cdata[cc]);
            return TurnResult::turn_end;
        }
        if (area_data[game_data.current_map].id ==
            mdata_t::MapId::random_dungeon)
        {
            if (game_data.current_dungeon_level ==
                area_data[game_data.current_map].deepest_level)
            {
                if (area_data[game_data.current_map].has_been_conquered != -1)
                {
                    txt(i18n::s.get("core.action.use.shelter.during_quest"));
                    if (!yes_no())
                    {
                        update_screen();
                        return TurnResult::pc_turn_user_error;
                    }
                }
            }
        }
        game_data.activity_about_to_start = 102;
        activity_others(cdata[cc]);
        break;
    case 11:
        if (moneybox(inv[ci].param2) > cdata.player().gold)
        {
            txt(i18n::s.get("core.action.use.money_box.not_enough_gold"));
            update_screen();
            return TurnResult::pc_turn_user_error;
        }
        if (inv[ci].param1 >= 1000000000)
        {
            txt(i18n::s.get("core.action.use.money_box.full"));
            update_screen();
            return TurnResult::pc_turn_user_error;
        }
        item_separate(ci);
        snd("core.paygold1");
        cdata.player().gold -= moneybox(inv[ci].param2);
        inv[ci].param1 += moneybox(inv[ci].param2);
        inv[ci].weight += 100;
        break;
    case 20:
        efid = 458;
        efp = 400;
        magic();
        break;
    case 47: txt(i18n::s.get("core.action.use.summoning_crystal.use")); break;
    case 22:
        snd("core.enc");
        if (map_data.type != mdata_t::MapType::town &&
            map_data.type != mdata_t::MapType::guild)
        {
            txt(i18n::s.get("core.action.use.rune.only_in_town"));
            break;
        }
        inv[ci].modify_number(-1);
        cell_refresh(inv[ci].position.x, inv[ci].position.y);
        txt(i18n::s.get("core.action.use.rune.use"));
        // Showroom is not supported now.
        break;
    case 49:
        txt(i18n::s.get("core.action.use.hammer.use", inv[ci]));
        snd("core.build1");
        efid = 49;
        efp = 100;
        magic();
        break;
    case 21:
        txt(i18n::s.get("core.action.use.hammer.use", inv[ci]));
        snd("core.build1");
        inv[ci].modify_number(-1);
        fixmaterial = inv[ci].material;
        efid = 21;
        efp = 500;
        magic();
        break;
    case 25:
        txt(i18n::s.get("core.action.use.unicorn_horn.use", inv[ci]));
        inv[ci].modify_number(-1);
        efid = 637;
        efp = 500;
        magic();
        break;
    case 26:
        txt(i18n::s.get("core.action.use.statue.activate", inv[ci]));
        game_data.diastrophism_flag = 1;
        snd("core.pray1");
        txt(i18n::s.get("core.action.use.statue.opatos"),
            Message::color{ColorIndex::orange});
        break;
    case 34:
        txt(i18n::s.get("core.action.use.statue.activate", inv[ci]));
        txt(i18n::s.get("core.action.use.statue.jure"),
            Message::color{ColorIndex::orange});
        efid = 637;
        efp = 5000;
        magic();
        break;
    case 43:
        txt(i18n::s.get("core.action.use.statue.activate", inv[ci]));
        snd("core.pray1");
        txt(i18n::s.get("core.action.use.statue.ehekatl"),
            Message::color{ColorIndex::orange});
        buff_add(cdata[tc], "core.luck", 77, 2500);
        break;
    case 27:
        txt(i18n::s.get("core.action.use.statue.activate", inv[ci]));
        snd("core.pray1");
        if (game_data.weather == 1)
        {
            txt(i18n::s.get("core.action.use.statue.lulwy.during_etherwind"),
                Message::color{ColorIndex::orange});
            break;
        }
        p = game_data.weather;
        while (1)
        {
            if (rnd(10) == 0)
            {
                game_data.weather = 0;
            }
            if (rnd(10) == 0)
            {
                game_data.weather = 3;
            }
            if (rnd(15) == 0)
            {
                game_data.weather = 4;
            }
            if (rnd(20) == 0)
            {
                game_data.weather = 2;
            }
            if (game_data.weather != p)
            {
                break;
            }
        }
        txt(i18n::s.get("core.action.use.statue.lulwy.normal"),
            Message::color{ColorIndex::orange});
        txt(i18n::s.get("core.action.weather.changes"));
        sound_play_environmental();
        break;
    case 28:
        if (map_data.type == mdata_t::MapType::world_map)
        {
            txt(i18n::s.get("core.action.use.nuke.cannot_place_here"));
            update_screen();
            return TurnResult::pc_turn_user_error;
        }
        if (cdata.player().position.x != 33 || cdata.player().position.y != 16)
        {
            if (game_data.quest_flags.red_blossom_in_palmia == 1)
            {
                txt(i18n::s.get("core.action.use.nuke.not_quest_goal"));
                if (!yes_no())
                {
                    update_screen();
                    return TurnResult::pc_turn_user_error;
                }
            }
        }
        inv[ci].modify_number(-1);
        cell_refresh(inv[ci].position.x, inv[ci].position.y);
        txt(i18n::s.get("core.action.use.nuke.set_up"));
        snd("core.build1");
        mef_add(
            cdata[cc].position.x, cdata[cc].position.y, 7, 632, 10, 100, cc);
        break;
    case 48:
        if (game_data.current_map != mdata_t::MapId::show_house ||
            usermapid == 0)
        {
            txt(i18n::s.get("core.action.use.statue.creator.normal"));
            break;
        }
        txt(i18n::s.get("core.action.use.statue.creator.in_usermap"));
        break;
    case 29:
        trait(inv[ci].param1) = 1;
        if (inv[ci].param1 == 169)
        {
            trait(162) = 0;
        }
        if (inv[ci].param1 == 162)
        {
            trait(169) = 0;
        }
        inv[ci].modify_number(-1);
        txt(i18n::s.get("core.action.use.secret_treasure.use"));
        animeload(10, 0);
        chara_refresh(cc);
        break;
    case 30:
        txt(i18n::s.get("core.action.use.statue.activate", inv[ci]));
        efid = inv[ci].param1;
        efp = inv[ci].param2;
        tc = cc;
        efstatus = CurseState::none;
        magic();
        break;
    case 41:
        if (game_data
                .next_level_minus_one_kumiromis_experience_becomes_available >
            cdata.player().level)
        {
            txt(i18n::s.get(
                "core.action.use.secret_experience.kumiromi.not_enough_exp"));
            update_screen();
            return TurnResult::pc_turn_user_error;
        }
        snd("core.pray1");
        game_data.next_level_minus_one_kumiromis_experience_becomes_available +=
            10;
        inv[ci].modify_number(-1);
        ++game_data.acquirable_feat_count;
        txt(i18n::s.get(
            "core.action.use.secret_experience.kumiromi.use.dialog"));
        txt(i18n::s.get("core.action.use.secret_experience.kumiromi.use.text"),
            Message::color{ColorIndex::orange});
        break;
    case 42:
        snd("core.curse1");
        txt(i18n::s.get("core.action.use.secret_experience.lomias"),
            Message::color{ColorIndex::purple});
        break;
    case 46:
        Message::instance().linebreak();
        txt(i18n::s.get("core.action.use.rope.prompt"));
        if (!yes_no())
        {
            return TurnResult::turn_end;
        }
        damage_hp(cdata.player(), 99999, -20);
        break;
    case 33:
        if (inv[ci].subname == 0)
        {
            txt(i18n::s.get("core.action.use.monster_ball.empty"));
            break;
        }
        if (chara_get_free_slot_ally() == 0)
        {
            txt(i18n::s.get("core.action.use.monster_ball.party_is_full"));
            break;
        }
        txt(i18n::s.get("core.action.use.monster_ball.use", inv[ci]));
        inv[ci].modify_number(-1);
        flt();
        novoidlv = 1;
        chara_create(56, inv[ci].subname, -3, 0);
        rc = 56;
        new_ally_joins();
        break;
    case 31:
        x = cdata[cc].position.x;
        y = cdata[cc].position.y;
        cell_featread(x, y);
        if (feat(1) != 29)
        {
            txt(i18n::s.get("core.action.use.gem_stone.kumiromi.no_plant"));
            break;
        }
        if (feat == tile_plant + 2)
        {
            txt(i18n::s.get(
                "core.action.use.gem_stone.kumiromi.already_grown"));
            break;
        }
        if (feat == tile_plant + 3)
        {
            feat = tile_plant + 1;
            try_to_grow_plant();
            txt(i18n::s.get("core.action.use.gem_stone.kumiromi.revives"));
        }
        else
        {
            ++feat;
            txt(i18n::s.get("core.action.use.gem_stone.kumiromi.grows"));
        }
        cell_featset(x, y, feat, feat(1), feat(2), feat(3));
        animeload(8, 0);
        break;
    case 32:
        Message::instance().linebreak();
        txt(i18n::s.get("core.action.use.gene_machine.choose_original"));
        rc = 0;
        {
            int stat = ctrl_ally(ControlAllyOperation::gene_engineer);
            if (stat == -1)
            {
                return TurnResult::turn_end;
            }
            rc = stat;
        }
        Message::instance().linebreak();
        txt(i18n::s.get("core.action.use.gene_machine.choose_subject"));
        {
            int chara;
            while (true)
            {
                chara = ctrl_ally(ControlAllyOperation::gene_engineer);
                if (chara == -1)
                {
                    break;
                }
                if (cdata[chara].has_been_used_stethoscope())
                {
                    txt(i18n::s.get(
                        "core.action.use.gene_machine.precious_ally",
                        cdata[chara]));
                    continue;
                }
                break;
            }
            if (chara == -1)
            {
                return TurnResult::turn_end;
            }
            tc = chara;
        }
        update_screen();
        Message::instance().linebreak();
        txt(i18n::s.get(
            "core.action.use.gene_machine.prompt", cdata[tc], cdata[rc]));
        if (!yes_no())
        {
            return TurnResult::turn_end;
        }
        Message::instance().linebreak();
        txt(i18n::s.get(
                "core.action.use.gene_machine.has_inherited",
                cdata[rc],
                cdata[tc]),
            Message::color{ColorIndex::orange});
        GeneEngineeringAnimation(cdata[rc].position).play();
        {
            int stat = transplant_body_parts();
            if (stat != -1)
            {
                cdata[rc].body_parts[stat - 100] = rtval * 10000;
                txt(i18n::s.get(
                        "core.action.use.gene_machine.gains.body_part",
                        cdata[rc],
                        i18n::s.get_enum("core.ui.body_part", rtval)),
                    Message::color{ColorIndex::green});
                refresh_speed_correction_value(cdata[rc]);
            }
        }
        {
            int stat = gain_skills_by_geen_engineering();
            if (stat != 0)
            {
                for (int cnt = 0; cnt < 2; ++cnt)
                {
                    if (rtval(cnt) == -1)
                    {
                        break;
                    }
                    chara_gain_skill(cdata[rc], rtval(cnt), 1);
                    txt(i18n::s.get(
                            "core.action.use.gene_machine.gains.ability",
                            cdata[rc],
                            i18n::s.get_m(
                                "ability",
                                the_ability_db.get_id_from_legacy(rtval(cnt))
                                    ->get(),
                                "name")),
                        Message::color{ColorIndex::green});
                }
            }
        }
        if (cdata[tc].level > cdata[rc].level)
        {
            lv = (cdata[tc].level - cdata[rc].level) / 2 + 1;
            for (int cnt = 0, cnt_end = (lv); cnt < cnt_end; ++cnt)
            {
                r2 = 1;
                gain_level(cdata[rc]);
            }
            txt(i18n::s.get(
                    "core.action.use.gene_machine.gains.level",
                    cdata[rc],
                    cdata[rc].level),
                Message::color{ColorIndex::green});
            listmax = 0;
            for (int cnt = 10; cnt < 18; ++cnt)
            {
                list(0, listmax) = cnt;
                list(1, listmax) = sdata.get(cnt, tc).original_level;
                ++listmax;
            }
            sort_list_by_column1();
            for (int cnt = 0; cnt < 3; ++cnt)
            {
                p = listmax - cnt - 1;
                i = list(0, p);
                if (list(1, p) > sdata.get(i, rc).original_level)
                {
                    p = (list(1, p) - sdata.get(i, rc).original_level) * 500;
                    p = clamp(p * 10 / clamp(lv, 2, 10), 1000, 10000);
                    chara_gain_fixed_skill_exp(cdata[rc], i, p);
                }
            }
        }
        chara_vanquish(tc);
        save_set_autosave();
        chara_gain_skill_exp(cdata.player(), 151, 1200);
        randomize();
        screenupdate = -1;
        update_screen();
        cc = rc;
        snd("core.pop2");
        menu_character_sheet_investigate();
        cc = 0;
        break;
    case 35:
        txt(i18n::s.get("core.action.use.iron_maiden.use"));
        txt(i18n::s.get("core.action.use.iron_maiden.interesting"),
            Message::color{ColorIndex::cyan});
        txt(i18n::s.get("core.action.use.iron_maiden.someone_activates"));
        txt(i18n::s.get("core.action.use.iron_maiden.grin"),
            Message::color{ColorIndex::cyan});
        damage_hp(cdata.player(), 9999, -18);
        break;
    case 36:
        txt(i18n::s.get("core.action.use.guillotine.use"));
        txt(i18n::s.get("core.action.use.iron_maiden.interesting"),
            Message::color{ColorIndex::cyan});
        txt(i18n::s.get("core.action.use.guillotine.someone_activates"));
        txt(i18n::s.get("core.action.use.iron_maiden.grin"),
            Message::color{ColorIndex::cyan});
        damage_hp(cdata.player(), 9999, -19);
        break;
    case 39:
        txt(i18n::s.get("core.action.use.whistle.use"),
            Message::color{ColorIndex::cyan});
        make_sound(cdata[cc].position.x, cdata[cc].position.y, 10, 1, 1, cc);
        break;
    case 37:
        tcgdeck();
        draw_prepare_map_chips();
        update_entire_screen();
        Message::instance().linebreak();
        txt(i18n::s.get("core.action.use.deck.put_away"));
        break;
    case 38:
        if (inv_find(701, 0) == -1)
        {
            txt(i18n::s.get("core.action.use.deck.no_deck"));
            update_screen();
            return TurnResult::pc_turn_user_error;
        }
        snd("core.card1");
        inv[ci].modify_number(-1);
        cell_refresh(inv[ci].position.x, inv[ci].position.y);
        txt(i18n::s.get("core.action.use.deck.add_card", inv[ci]));
        ++card(0, inv[ci].subname);
        break;
    }

    refresh_burden_state();
    return TurnResult::turn_end;
}



TurnResult do_open_command(bool play_sound)
{
    const auto snd_ = [play_sound](data::InstanceId id) {
        if (play_sound)
        {
            snd(id);
        }
    };

    int refweight = 0;
    if (inv[ci].id == ItemId::shopkeepers_trunk)
    {
        modify_karma(cdata.player(), -10);
        invctrl(0) = 22;
        invctrl(1) = 0;
        invfile = inv[ci].param1;
        snd_("core.chest1");
        shop_sell_item();
        screenupdate = -1;
        update_screen();
        return TurnResult::turn_end;
    }
    if (inv[ci].id == ItemId::masters_delivery_chest)
    {
        invctrl(0) = 24;
        invctrl(1) = 0;
        snd_("core.inv");
        MenuResult mr = ctrl_inventory();
        assert(mr.turn_result != TurnResult::none);
        return mr.turn_result;
    }
    if (inv[ci].id == ItemId::tax_masters_tax_box)
    {
        invctrl(0) = 24;
        invctrl(1) = 2;
        snd_("core.inv");
        MenuResult mr = ctrl_inventory();
        assert(mr.turn_result != TurnResult::none);
        return mr.turn_result;
    }
    if (inv[ci].id == ItemId::giants_shackle)
    {
        snd_("core.locked1");
        txt(i18n::s.get("core.action.open.shackle.text"));
        if (game_data.current_map == mdata_t::MapId::noyel)
        {
            if (game_data.current_dungeon_level == 1)
            {
                if (game_data.released_fire_giant == 0)
                {
                    if (cdata[game_data.fire_giant].state() ==
                        Character::State::alive)
                    {
                        tc = chara_find("core.moyer");
                        if (tc != 0 &&
                            cdata[tc].state() == Character::State::alive)
                        {
                            txt(i18n::s.get("core.action.open.shackle.dialog"),
                                Message::color{ColorIndex::cyan});
                            cdata[game_data.fire_giant].enemy_id = tc;
                            cdata[game_data.fire_giant].hate = 1000;
                        }
                        game_data.released_fire_giant = 1;
                        net_send_news("fire");
                    }
                }
            }
        }
        return TurnResult::turn_end;
    }
    if (inv[ci].count != 0)
    {
        invfile = inv[ci].count;
        invcontainer(1) = itemid2int(inv[ci].id);
        const auto container_ci = ci;
        if (inv[ci].id == ItemId::cooler_box)
        {
            refweight = -1;
        }
        else
        {
            refweight = 0;
        }
        if (inv[ci].count == 3 || inv[ci].count == 4 || inv[ci].count == 6)
        {
            if (game_data.current_map != mdata_t::MapId::your_home)
            {
                txt(i18n::s.get("core.action.open.only_in_home"));
                update_screen();
                return TurnResult::pc_turn_user_error;
            }
        }
        if (inv[ci].count == 5)
        {
            if (area_data[game_data.current_map].id != mdata_t::MapId::shop)
            {
                txt(i18n::s.get("core.action.open.only_in_shop"));
                update_screen();
                return TurnResult::pc_turn_user_error;
            }
        }
        ctrl_file(FileOperation2::map_items_write, u8"shoptmp.s2");
        tmpload(filepathutil::u8path(u8"shop"s + invfile + u8".s2"));
        if (fs::exists(
                filesystem::dirs::tmp() / (u8"shop"s + invfile + u8".s2")))
        {
            ctrl_file(
                FileOperation2::map_items_read, u8"shop"s + invfile + u8".s2");
        }
        else
        {
            for (auto&& item : inv.ground())
            {
                item.remove();
            }
        }
        shoptrade = 0;
        invsubroutine = 1;
        invctrl(0) = 22;
        invctrl(1) = 2;
        if (invfile == 3)
        {
            txt(i18n::s.get(
                "core.ui.inv.take.can_claim_more",
                game_data.rights_to_succeed_to));
            invctrl(1) = 1;
        }
        if (invfile == 6 || invcontainer(1) == 641)
        {
            if (invfile == 6)
            {
                invcontainer = 15;
            }
            else
            {
                invcontainer = 4;
            }
            menucycle = 1;
            invctrl(1) = 3;
        }
        mode = 6;
        snd_("core.inv");
        ctrl_inventory();
        invcontainer = 0;
        if (refweight == -1)
        {
            refweight = inv_weight(-1) + 2500;
        }
        ctrl_file(
            FileOperation2::map_items_write, u8"shop"s + invfile + u8".s2");
        ctrl_file(FileOperation2::map_items_read, u8"shoptmp.s2");
        if (refweight != 0)
        {
            inv[container_ci].weight = refweight;
            refresh_burden_state();
        }
        update_screen();
        mode = 0;
        return TurnResult::turn_end;
    }
    item_separate(ci);
    if (inv[ci].param1 != 0)
    {
        if (inv[ci].param2 != 0)
        {
            int stat = unlock_box(inv[ci].param2);
            if (stat == 0)
            {
                screenupdate = -1;
                update_screen();
                return TurnResult::turn_end;
            }
        }
    }
    if (inv[ci].param1 == 0)
    {
        txt(i18n::s.get("core.action.open.empty"));
    }
    else
    {
        if (inv[ci].id == ItemId::new_years_gift)
        {
            ri = ci;
            open_new_year_gift(inv[ri]);
        }
        else
        {
            ri = ci;
            open_box(inv[ri]);
        }
        item_stack(cc, inv[ri]);
    }
    screenupdate = -1;
    update_screen();
    return TurnResult::turn_end;
}



TurnResult do_use_stairs_command(int val0)
{
    int movelevelbystairs = 0;
    if (dbg_freemove)
    {
        txt(i18n::s.get("core.action.use_stairs.cannot_during_debug"));
        return TurnResult::pc_turn_user_error;
    }
    if (const auto moon_gate = item_find(631, 3, ItemFindLocation::ground))
    {
        if (map_is_town_or_guild())
        {
            ci = moon_gate->index;
            return step_into_gate(*moon_gate);
        }
    }
    cell_featread(cdata[cc].position.x, cdata[cc].position.y);
    movelevelbystairs = 0;
    if (val0 == 1)
    {
        if (mapitemfind(cdata[cc].position.x, cdata[cc].position.y, 753) != -1)
        {
            txt(i18n::s.get("core.action.use_stairs.kotatsu.prompt"));
            if (!yes_no())
            {
                update_screen();
                return TurnResult::pc_turn_user_error;
            }
            txt(i18n::s.get("core.action.use_stairs.kotatsu.use"));
            cdata.player().blind += 2;
            return TurnResult::turn_end;
        }
    }
    if (game_data.current_map == mdata_t::MapId::your_home)
    {
        if (val0 == 1)
        {
            if (mapitemfind(cdata[cc].position.x, cdata[cc].position.y, 751) !=
                -1)
            {
                if (game_data.current_dungeon_level >=
                    area_data[game_data.current_map].deepest_level)
                {
                    txt(i18n::s.get("core.action.use_stairs.cannot_go.down"));
                    return TurnResult::pc_turn_user_error;
                }
                else
                {
                    movelevelbystairs = 1;
                }
            }
        }
        if (val0 == 2)
        {
            if (mapitemfind(cdata[cc].position.x, cdata[cc].position.y, 750) !=
                -1)
            {
                if (game_data.current_dungeon_level <=
                    area_data[game_data.current_map].danger_level)
                {
                    txt(i18n::s.get("core.action.use_stairs.cannot_go.up"));
                    return TurnResult::pc_turn_user_error;
                }
                else
                {
                    movelevelbystairs = 1;
                }
            }
        }
    }
    if (movelevelbystairs == 0)
    {
        if (map_data.type != mdata_t::MapType::world_map)
        {
            if (val0 == 1)
            {
                if (feat(1) != 11)
                {
                    txt(i18n::s.get("core.action.use_stairs.no.downstairs"));
                    update_screen();
                    return TurnResult::pc_turn_user_error;
                }
                else
                {
                    movelevelbystairs = 1;
                    if (game_data.current_map == mdata_t::MapId::the_void &&
                        game_data.current_dungeon_level >=
                            game_data.void_next_lord_floor)
                    {
                        txt(i18n::s.get(
                            "core.action.use_stairs.blocked_by_barrier"));
                        return TurnResult::pc_turn_user_error;
                    }
                }
            }
            if (val0 == 2)
            {
                if (feat(1) != 10)
                {
                    txt(i18n::s.get("core.action.use_stairs.no.upstairs"));
                    update_screen();
                    return TurnResult::pc_turn_user_error;
                }
                else
                {
                    movelevelbystairs = 1;
                }
            }
        }
    }
    if (feat == tile_downlocked)
    {
        f = 0;
        if (game_data.current_dungeon_level == 3)
        {
            if (game_data.quest_flags.main_quest >= 65)
            {
                f = 1;
            }
        }
        if (game_data.current_dungeon_level == 17)
        {
            if (game_data.quest_flags.main_quest >= 115)
            {
                f = 1;
            }
        }
        if (game_data.current_dungeon_level == 25)
        {
            if (game_data.quest_flags.main_quest >= 125)
            {
                f = 1;
            }
        }
        if (game_data.current_dungeon_level == 44)
        {
            if (game_data.quest_flags.main_quest >= 125)
            {
                f = 1;
            }
        }
        if (f == 1)
        {
            if (game_data.current_dungeon_level == 44)
            {
                txt(i18n::s.get("core.action.use_stairs.unlock.stones"));
            }
            else
            {
                txt(i18n::s.get("core.action.use_stairs.unlock.normal"));
            }
            snd("core.chest1");
            cell_featset(
                cdata[cc].position.x,
                cdata[cc].position.y,
                tile_downstairs,
                11);
            return TurnResult::turn_end;
        }
        snd("core.locked1");
        txt(i18n::s.get("core.action.use_stairs.locked"));
        return TurnResult::turn_end;
    }
    if (area_data[game_data.current_map].id == mdata_t::MapId::random_dungeon)
    {
        if (game_data.current_dungeon_level ==
            area_data[game_data.current_map].deepest_level)
        {
            if (area_data[game_data.current_map].has_been_conquered != -1)
            {
                txt(i18n::s.get("core.action.use_stairs.prompt_give_up_quest"));
                if (!yes_no())
                {
                    update_screen();
                    return TurnResult::pc_turn_user_error;
                }
            }
        }
    }
    if (movelevelbystairs == 1)
    {
        bool ok = action_sp(cdata.player(), 15);
        if (!ok || cdata.player().inventory_weight_type >= 3)
        {
            if (!ok || rnd(5 - cdata.player().inventory_weight_type) == 0)
            {
                txt(i18n::s.get("core.action.use_stairs.lost_balance"));
                damage_hp(
                    cdata[cc],
                    cdata[cc].max_hp *
                            (cdata.player().inventory_weight * 10 /
                                 cdata.player().max_inventory_weight +
                             10) /
                            100 +
                        1,
                    -7);
                msg_halt();
            }
            if (cdata.player().state() == Character::State::empty)
            {
                return TurnResult::turn_begin;
            }
        }
    }
    if (feat(1) == 15)
    {
        if (feat(2) + feat(3) * 100 == 35)
        {
            // Showroom is not supported now.
            return TurnResult::pc_turn_user_error;
        }
    }
    snd("core.exitmap1");
    levelexitby = 4;
    return TurnResult::exit_map;
}



TurnResult do_movement_command()
{
    f = 0;
    if (cdata[cc].dimmed != 0)
    {
        if (cdata[cc].dimmed + 10 > rnd(60))
        {
            f = 1;
        }
    }
    if (cdata[cc].drunk != 0)
    {
        if (rnd(5) == 0)
        {
            txt(i18n::s.get("core.action.move.drunk"),
                Message::color{ColorIndex::cyan});
            f = 1;
        }
    }
    if (cdata[cc].confused != 0 || f == 1)
    {
        cdata[cc].next_position.x = cdata[cc].position.x + rnd(3) - 1;
        cdata[cc].next_position.y = cdata[cc].position.y + rnd(3) - 1;
    }
    if (game_data.mount != 0)
    {
        if (cdata[game_data.mount].activity)
        {
            if (cdata[game_data.mount].activity.turn > 0)
            {
                txt(i18n::s.get(
                    "core.action.move.interrupt", cdata[game_data.mount]));
                cdata[game_data.mount].activity.type = Activity::Type::none;
                cdata[game_data.mount].activity.turn = 0;
            }
        }
    }
    cell_check(cdata[cc].next_position.x, cdata[cc].next_position.y);
    if (cdata.player().inventory_weight_type >= 4)
    {
        txt(i18n::s.get("core.action.move.carry_too_much"),
            Message::only_once{true});
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    if (cellchara != -1 && cellchara != 0)
    {
        return _bump_into_character();
    }
    else
    {
        keybd_attacking = 0;
    }
    if (map_data.type == mdata_t::MapType::world_map)
    {
        if (dbg_freemove)
        {
            x = cdata.player().next_position.x;
            y = cdata.player().next_position.y;
            if (x >= 0 && x < map_data.width && y >= 0 && y < map_data.height)
            {
                if (cell_data.at(x, y).chara_index_plus_one == 0)
                {
                    cellaccess = 1;
                }
            }
        }
    }
    if (cellaccess == 1)
    {
        return _pre_proc_movement_event();
    }
    if (map_data.type == mdata_t::MapType::shelter ||
        (game_data.current_dungeon_level == 1 &&
         map_data.type != mdata_t::MapType::world_map &&
         !mdata_t::is_nefia(map_data.type)))
    {
        if (cdata[cc].next_position.x < 0 ||
            cdata[cc].next_position.x > map_data.width - 1 ||
            cdata[cc].next_position.y < 0 ||
            cdata[cc].next_position.y > map_data.height - 1)
        {
            txt(i18n::s.get("core.action.move.leave.prompt", mdatan(0)));
            if (map_data.type == mdata_t::MapType::temporary)
            {
                if (game_data.executing_immediate_quest_status != 3)
                {
                    txt(i18n::s.get("core.action.move.leave.abandoning_quest"));
                }
            }
            const auto yesno_result = yes_no();
            update_screen();
            if (yesno_result)
            {
                game_data.player_x_on_map_leave = cdata.player().position.x;
                game_data.player_y_on_map_leave = cdata.player().position.y;
                snd("core.exitmap1");
                --game_data.current_dungeon_level;
                levelexitby = 4;
                return TurnResult::exit_map;
            }
            return TurnResult::pc_turn_user_error;
        }
    }
    if (cellfeat != -1)
    {
        if (cellfeat == 21)
        {
            return proc_movement_event();
        }
        input_halt_input(HaltInput::force);
        if (cellfeat == 23)
        {
            snd("core.chat");
            return TurnResult::show_quest_board;
        }
        if (cellfeat == 31)
        {
            snd("core.chat");
            menu_voting_box();
            return TurnResult::turn_end;
        }
        if (cellfeat == 33)
        {
            menucycle = 1;
            show_city_chart();
            return TurnResult::pc_turn_user_error;
        }
    }
    if (cdata.player().confused != 0)
    {
        txt(i18n::s.get("core.action.move.confused"), Message::only_once{true});
        update_screen();
    }
    return TurnResult::pc_turn_user_error;
}



TurnResult do_read_command()
{
    if (inv[ci].id == ItemId::recipe)
    {
        if (inv[ci].subname == 0)
        {
            txt(i18n::s.get("core.action.read.recipe.info"));
            return TurnResult::turn_end;
        }
    }
    efid = 0;
    item_db_on_read(inv[ci], itemid2int(inv[ci].id));
    if (efid == 1115)
    {
        return build_new_building();
    }
    return TurnResult::turn_end;
}



TurnResult do_eat_command()
{
    if (cc == 0)
    {
        if (!cargocheck(inv[ci]))
        {
            update_screen();
            return TurnResult::pc_turn_user_error;
        }
        if (itemusingfind(inv[ci]) > 0)
        {
            txt(i18n::s.get("core.action.someone_else_is_using"));
            return TurnResult::pc_turn_user_error;
        }
    }
    else if (itemusingfind(inv[ci]) != -1)
    {
        tc = itemusingfind(inv[ci]);
        if (tc != cc)
        {
            cdata[tc].activity.finish();
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get(
                    "core.action.eat.snatches", cdata[cc], cdata[tc]));
            }
        }
    }
    cdata[cc].emotion_icon = 116;
    activity_eating(cdata[cc], inv[ci]);
    return TurnResult::turn_end;
}



TurnResult do_drink_command()
{
    item_db_on_drink(inv[ci], itemid2int(inv[ci].id));
    return TurnResult::turn_end;
}



TurnResult do_zap_command()
{
    item_db_on_zap(inv[ci], itemid2int(inv[ci].id));
    int stat = do_zap();
    if (stat == 0)
    {
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    return TurnResult::turn_end;
}



TurnResult do_rest_command()
{
    do_rest();
    return TurnResult::turn_end;
}



TurnResult do_fire_command()
{
    cc = 0;
    int stat = find_enemy_target();
    if (stat == 0)
    {
        return TurnResult::pc_turn_user_error;
    }
    tc = cdata.player().enemy_id;
    if (cdata[tc].relationship >= 0)
    {
        int stat = prompt_really_attack();
        if (stat == 0)
        {
            return TurnResult::pc_turn_user_error;
        }
    }
    {
        int stat = can_do_ranged_attack();
        if (stat == -1)
        {
            txt(i18n::s.get("core.action.ranged.equip.need_weapon"),
                Message::only_once{true});
            update_screen();
            return TurnResult::pc_turn_user_error;
        }
        if (stat == -2)
        {
            txt(i18n::s.get("core.action.ranged.equip.need_ammo"),
                Message::only_once{true});
            update_screen();
            return TurnResult::pc_turn_user_error;
        }
        if (stat == -3)
        {
            txt(i18n::s.get("core.action.ranged.equip.wrong_ammo"),
                Message::only_once{true});
            update_screen();
            return TurnResult::pc_turn_user_error;
        }
    }
    do_ranged_attack();
    return TurnResult::turn_end;
}



TurnResult do_get_command()
{
    const auto item_info = cell_itemoncell(cdata.player().position);
    const auto number = item_info.first;
    const auto item = item_info.second;

    if (cell_data.at(cdata.player().position.x, cdata.player().position.y)
                .feats != 0 &&
        game_data.current_map != mdata_t::MapId::show_house && number == 0)
    {
        cell_featread(cdata.player().position.x, cdata.player().position.y);
        if (feat(1) == 29)
        {
            if (feat < tile_plant + 2)
            {
                txt(i18n::s.get("core.action.get.plant.young"));
                cell_data
                    .at(cdata.player().position.x, cdata.player().position.y)
                    .feats = 0;
                return TurnResult::turn_end;
            }
            if (feat == tile_plant + 3)
            {
                txt(i18n::s.get("core.action.get.plant.dead"));
                cell_data
                    .at(cdata.player().position.x, cdata.player().position.y)
                    .feats = 0;
                return TurnResult::turn_end;
            }
            if (!inv_getspace(0))
            {
                txt(i18n::s.get("core.ui.inv.common.inventory_is_full"));
                update_screen();
                return TurnResult::pc_turn_user_error;
            }
            create_harvested_item();
            harvest_plant(
                chip_data.for_cell(
                             cdata.player().position.x,
                             cdata.player().position.y)
                            .kind == 2
                    ? 1
                    : 0);
            if (feat(2) == 40)
            {
                save_set_autosave();
            }
            refresh_burden_state();
            return TurnResult::turn_end;
        }
        if (map_data.type == mdata_t::MapType::world_map && feat(1) == 15 &&
            feat(2) + feat(3) * 100 >= 300 && feat(2) + feat(3) * 100 < 450)
        {
            txt(i18n::s.get("core.action.get.building.prompt"));
            if (!yes_no())
            {
                update_screen();
                return TurnResult::pc_turn_user_error;
            }
            area = feat(2) + feat(3) * 100;
            cell_data.at(cdata.player().position.x, cdata.player().position.y)
                .feats = 0;
            area_data[area].id = static_cast<int>(mdata_t::MapId::none);
            removeworker(area);
            map_global_prepare();
            ctrl_file(FileOperation::temp_dir_delete_area);
            snd("core.build1");
            txt(i18n::s.get("core.action.get.building.remove"));
            return TurnResult::turn_end;
        }
    }

    if (number == 0)
    {
        if ((map_is_town_or_guild()) &&
            chip_data
                    .for_cell(
                        cdata.player().position.x, cdata.player().position.y)
                    .kind == 4)
        {
            snd("core.foot2a");
            txt(i18n::s.get("core.action.get.snow"));
            if (!action_sp(cdata.player(), 10))
            {
                txt(i18n::s.get("core.magic.common.too_exhausted"));
                return TurnResult::turn_end;
            }
            flt();
            {
                if (const auto item = itemcreate_player_inv(587, 0))
                {
                    item->curse_state = CurseState::none;
                    item->identify_state = IdentifyState::completely;
                    item_stack(0, *item, true);
                }
            }
            return TurnResult::turn_end;
        }
        txt(i18n::s.get("core.action.get.air"), Message::only_once{true});
        update_screen();
        return TurnResult::pc_turn_user_error;
    }

    ci = item;
    if (number > 1)
    {
        invctrl = 3;
        snd("core.inv");
        MenuResult mr = ctrl_inventory();
        assert(mr.turn_result != TurnResult::none);
        return mr.turn_result;
    }
    if ((inv[ci].own_state > 0 && inv[ci].own_state < 3) ||
        inv[ci].own_state == 5)
    {
        snd("core.fail1");
        if (inv[ci].own_state == 2)
        {
            txt(i18n::s.get("core.action.get.cannot_carry"),
                Message::only_once{true});
        }
        if (inv[ci].own_state == 1 || inv[ci].own_state == 5)
        {
            txt(i18n::s.get("core.action.get.not_owned"),
                Message::only_once{true});
        }
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    in = inv[ci].number();

    int stat = pick_up_item();
    if (stat == 1 || stat == -1)
    {
        return TurnResult::turn_end;
    }
    else
    {
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
}



TurnResult do_cast_command()
{
    tc = cc;
    int stat = do_cast_magic();
    if (stat == 0)
    {
        return TurnResult::pc_turn_user_error;
    }
    return TurnResult::turn_end;
}



TurnResult do_short_cut_command(int sc_)
{
    menucycle = 0;
    if (game_data.skill_shortcuts.at(sc_) == 0)
    {
        txt(i18n::s.get("core.action.shortcut.unassigned"),
            Message::only_once{true});
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    if (game_data.skill_shortcuts.at(sc_) >= 10000)
    {
        invsc = game_data.skill_shortcuts.at(sc_) % 10000;
        invctrl(0) = game_data.skill_shortcuts.at(sc_) / 10000;
        invctrl(1) = 0;
        MenuResult mr = ctrl_inventory();
        assert(mr.turn_result != TurnResult::none);
        return mr.turn_result;
    }
    efid = game_data.skill_shortcuts.at(sc_);
    if (efid >= 300 && efid < 400)
    {
        return do_use_magic();
    }
    if (efid >= 600)
    {
        if (map_data.type == mdata_t::MapType::world_map)
        {
            Message::instance().linebreak();
            txt(i18n::s.get("core.action.cannot_do_in_global"));
            redraw();
            return TurnResult::pc_turn_user_error;
        }
        if (efid < 661)
        {
            if (spact(efid - 600) == 0)
            {
                txt(i18n::s.get("core.action.shortcut.cannot_use_anymore"));
                update_screen();
                return TurnResult::pc_turn_user_error;
            }
        }
        return do_use_magic();
    }
    if (efid >= 400)
    {
        if (map_data.type == mdata_t::MapType::world_map)
        {
            Message::instance().linebreak();
            txt(i18n::s.get("core.action.cannot_do_in_global"));
            redraw();
            return TurnResult::pc_turn_user_error;
        }
        if (spell(efid - 400) <= 0)
        {
            txt(i18n::s.get("core.action.shortcut.cannot_use_spell_anymore"),
                Message::only_once{true});
            update_screen();
            return TurnResult::pc_turn_user_error;
        }
        return do_cast_command();
    }
    return TurnResult::pc_turn_user_error;
}



TurnResult do_exit_command()
{
    Message::instance().linebreak();
    if (game_data.current_map == mdata_t::MapId::show_house)
    {
        txt(i18n::s.get("core.action.exit.cannot_save_in_usermap"),
            Message::color{ColorIndex::red});
    }
    else
    {
        txt(i18n::s.get("core.action.exit.prompt"));
    }

    Prompt prompt("core.action.exit.choices");
    prompt.append("exit", snail::Key::key_a);
    prompt.append("cancel", snail::Key::key_b);
    prompt.append("game_setting", snail::Key::key_c);
    rtval = prompt.query(promptx, prompty, 190);

    if (rtval == 0)
    {
        if (game_data.current_map != mdata_t::MapId::show_house)
        {
            save_game(save_game_no_message);
            txt(i18n::s.get("core.action.exit.saved"));
            txt(i18n::s.get("core.action.exit.you_close_your_eyes", cdata[cc]));
            msg_halt();
            update_screen();
        }
        return TurnResult::finish_elona;
    }
    if (rtval == 2)
    {
        snd("core.ok1");
        show_option_menu();
    }
    update_screen();
    return TurnResult::pc_turn_user_error;
}



int ask_direction_to_close()
{
    int number_of_doors{};
    Position pos;
    for (int dy = -1; dy <= 1; ++dy)
    {
        for (int dx = -1; dx <= 1; ++dx)
        {
            if (dy == 0 && dx == 0)
                continue;

            int x = cdata.player().position.x + dx;
            int y = cdata.player().position.y + dy;
            cell_featread(x, y);
            if (feat(1) == 20 && cell_data.at(x, y).chara_index_plus_one == 0)
            {
                ++number_of_doors;
                pos = {x, y};
            }
        }
    }
    if (number_of_doors == 1)
    {
        x = pos.x;
        y = pos.y;
        return 1;
    }

    txt(i18n::s.get("core.action.which_direction.door"));
    update_screen();
    return ask_direction();
}



int try_to_cast_spell()
{
    int r4 = 0;
    f = 1;
    tc = cc;
    if (cdata[cc].blind != 0)
    {
        f = 0;
    }
    if (cdata[cc].confused != 0 || cdata[cc].dimmed != 0)
    {
        if (rnd(4) != 0)
        {
            f = 0;
        }
    }
    else
    {
        if (r3 == 0)
        {
            r4 = sdata(16, cc);
        }
        else
        {
            r4 = sdata(the_ability_db[r3]->related_basic_attribute, cc);
        }
        if (rnd_capped(sdata(150, cc) * r4 * 4 + 250) < rnd_capped(r2 + 1))
        {
            if (rnd(7) == 0)
            {
                f = 0;
            }
            if (r4 * 10 < r2)
            {
                if (rnd_capped(r4 * 10 + 1) < rnd_capped(r2 + 1))
                {
                    f = 0;
                }
            }
            if (r4 * 20 < r2)
            {
                if (rnd_capped(r4 * 20 + 1) < rnd_capped(r2 + 1))
                {
                    f = 0;
                }
            }
            if (r4 * 30 < r2)
            {
                if (rnd_capped(r4 * 30 + 1) < rnd_capped(r2 + 1))
                {
                    f = 0;
                }
            }
        }
    }
    if (f == 1)
    {
        return 1;
    }
    if (rnd(4) == 0)
    {
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get(
                "core.misc.fail_to_cast.mana_is_absorbed", cdata[cc]));
        }
        if (cc == 0)
        {
            damage_mp(cdata[cc], cdata[cc].max_mp);
        }
        else
        {
            damage_mp(cdata[cc], cdata[cc].max_mp / 3);
        }
        return 0;
    }
    if (rnd(4) == 0)
    {
        if (is_in_fov(cdata[cc]))
        {
            if (cdata[cc].confused != 0)
            {
                txt(i18n::s.get(
                    "core.misc.fail_to_cast.is_confused_more", cdata[cc]));
            }
            else
            {
                txt(i18n::s.get("core.misc.fail_to_cast.too_difficult"));
            }
        }
        status_ailment_damage(cdata[cc], StatusAilment::confused, 100);
        return 0;
    }
    if (rnd(4) == 0)
    {
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get("core.misc.fail_to_cast.creatures_are_summoned"));
        }
        for (int cnt = 0, cnt_end = (2 + rnd(3)); cnt < cnt_end; ++cnt)
        {
            flt(calcobjlv(cdata.player().level * 3 / 2 + 3),
                calcfixlv(Quality::bad));
            int stat =
                chara_create(-1, 0, cdata[cc].position.x, cdata[cc].position.y);
            if (stat != 0)
            {
                if (cdata[cc].relationship <= -3)
                {
                    cdata[rc].relationship = -1;
                    cdata[rc].original_relationship = -1;
                }
            }
        }
        return 0;
    }
    if (is_in_fov(cdata[cc]))
    {
        txt(i18n::s.get(
            "core.misc.fail_to_cast.dimension_door_opens", cdata[cc]));
    }
    tc = cc;
    efid = 408;
    magic();
    return 0;
}



int try_to_reveal()
{
    if (rnd_capped(sdata(159, cc) * 15 + 20 + sdata(13, cc)) >
        rnd_capped(game_data.current_dungeon_level * 8 + 60))
    {
        chara_gain_exp_detection(cdata[cc]);
        return 1;
    }
    return 0;
}



int can_evade_trap()
{
    if (feat(2) == 7)
    {
        return 0;
    }
    if (cc < 16)
    {
        if (rnd_capped(refdiff + 1) < sdata(13, cc) + sdata(159, cc) * 4)
        {
            return 1;
        }
    }
    else if (rnd(4) != 0)
    {
        return 1;
    }
    return 0;
}



int try_to_disarm_trap()
{
    if (rnd_capped(sdata(175, cc) * 15 + 20 + sdata(12, cc)) >
        rnd_capped(game_data.current_dungeon_level * 12 + 100))
    {
        chara_gain_exp_disarm_trap(cdata[cc]);
        return 1;
    }
    return 0;
}



int try_to_perceive_npc(int cc)
{
    int cv = 0;
    cv = 8;
    if (cdata[cc].position.x > cdata[r2].position.x - cv &&
        cdata[cc].position.x < cdata[r2].position.x + cv)
    {
        if (cdata[cc].position.y > cdata[r2].position.y - cv &&
            cdata[cc].position.y < cdata[r2].position.y + cv)
        {
            if (cdata[r2].hate > 0)
            {
                return 1;
            }
            p = dist(
                    cdata[cc].position.x,
                    cdata[cc].position.y,
                    cdata[r2].position.x,
                    cdata[r2].position.y) *
                    150 +
                (sdata(157, cc) * 100 + 150) + 1;
            if (rnd_capped(p(0)) < rnd_capped(sdata(13, r2) * 60 + 150))
            {
                return 1;
            }
        }
    }
    return 0;
}



TurnResult step_into_gate(Item& moon_gate)
{
    if (maybe_show_ex_help(17, true))
    {
        return TurnResult::pc_turn_user_error;
    }

    if (!game_data.wizard)
    {
        save_game();
    }
    txt(i18n::s.get("core.action.exit_map.gate.step_into"));
    moon_gate.modify_number(-1);
    txt(i18n::s.get("core.action.exit_map.gate.need_network"));
    update_screen();
    return TurnResult::pc_turn_user_error;
}



TurnResult do_use_magic()
{
    int stat = do_magic_attempt();
    if (stat == 0)
    {
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    return TurnResult::turn_end;
}



TurnResult try_interact_with_npc()
{
    if (cdata[tc].activity.turn != 0)
    {
        txt(i18n::s.get("core.action.npc.is_busy_now", cdata[tc]));
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    menucycle = 1;
    invally = 1;
    invctrl = 10;
    snd("core.inv");
    MenuResult mr = ctrl_inventory();
    assert(mr.turn_result != TurnResult::none);
    return mr.turn_result;
}



TurnResult do_gatcha(Item& gatcha_machine)
{
    screenupdate = -1;
    update_screen();
    const auto required_material =
        gatcha_machine.id == ItemId::red_treasure_machine ? 40 : 41;
    txt(i18n::s.get("core.action.gatcha.prompt", matname(required_material)));
    if (yes_no())
    {
        if (mat(required_material) > 0)
        {
            snd("core.gasha");
            matdelmain(required_material);
            const auto gatcha_ball_id =
                gatcha_machine.id == ItemId::red_treasure_machine ? 415 : 416;
            flt();
            if (const auto item =
                    itemcreate_extra_inv(gatcha_ball_id, cdata[cc].position, 0))
            {
                item->param2 = 0;
            }
            txt(i18n::s.get("core.common.something_is_put_on_the_ground"));
        }
        else
        {
            txt(i18n::s.get(
                "core.action.gatcha.do_not_have", matname(required_material)));
        }
    }
    return TurnResult::turn_end;
}



bool read_textbook(Item& textbook)
{
    if (textbook.id == ItemId::textbook)
    {
        if (sdata.get(textbook.param1, 0).original_level == 0)
        {
            txt(i18n::s.get("core.action.read.book.not_interested"));
            if (!yes_no())
            {
                return false;
            }
        }
    }
    game_data.activity_about_to_start = 104;
    activity_others(cdata[cc]);
    return true;
}



TurnResult do_enter_strange_gate()
{
    snd("core.exitmap1");
    map_prepare_for_travel_with_prev(
        static_cast<int>(mdata_t::MapId::show_house));
    return TurnResult::exit_map;
}



void disarm_trap(Character& chara, int x, int y)
{
    cell_featset(x, y, 0);
    if (chara.god_id == core_god::mani)
    {
        txt(i18n::s.get("core.action.move.trap.disarm.dismantle"));
        for (int _i = 0, n = rnd(3) + 1; _i < n; ++_i)
        {
            atxspot = 19;
            matgetmain(
                random_material(
                    game_data.current_dungeon_level,
                    game_data.current_dungeon_level / 5),
                1);
        }
    }
    else
    {
        txt(i18n::s.get("core.action.move.trap.disarm.succeed"));
    }
}



void do_rest()
{
    if (!cdata[cc].activity)
    {
        cdata[cc].activity.type = Activity::Type::sleep;
        cdata[cc].activity.turn = 50;
        txt(i18n::s.get("core.activity.rest.start"));
        update_screen();
        return;
    }
    if (cdata[cc].activity.turn > 0)
    {
        if (cdata[cc].activity.turn % 2 == 0)
        {
            heal_sp(cdata[cc], 1);
        }
        if (cdata[cc].activity.turn % 3 == 0)
        {
            heal_hp(cdata[cc], 1);
            heal_mp(cdata[cc], 1);
        }
        return;
    }
    if (game_data.continuous_active_hours >= 30)
    {
        f = 0;
        if (game_data.continuous_active_hours >= 50)
        {
            f = 1;
        }
        else if (rnd(2) == 0)
        {
            f = 1;
        }
        if (f == 1)
        {
            txt(i18n::s.get("core.activity.rest.drop_off_to_sleep"));
            cdata[cc].activity.item = -1;
            sleep_start();
            cdata[cc].activity.finish();
            return;
        }
    }
    txt(i18n::s.get("core.activity.rest.finish"));
    cdata[cc].activity.finish();
}



int decode_book()
{
    int cibkread = 0;
    if (!cdata[cc].activity)
    {
        if (inv[ci].id == ItemId::ancient_book)
        {
            if (inv[ci].param2 != 0)
            {
                txt(i18n::s.get("core.action.read.book.already_decoded"));
                return 0;
            }
        }
        if (cdata[cc].blind != 0)
        {
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get("core.action.read.cannot_see", cdata[cc]));
            }
            return 0;
        }
        cdata[cc].activity.type = Activity::Type::read;
        if (inv[ci].id == ItemId::recipe)
        {
            p = 50;
        }
        else if (inv[ci].id == ItemId::ancient_book)
        {
            p = 50 + inv[ci].param1 * 50 + inv[ci].param1 * inv[ci].param1 * 20;
        }
        else
        {
            p = the_ability_db[efid]->difficulty;
        }
        cdata[cc].activity.turn = p / (2 + sdata(150, 0)) + 1;
        cdata[cc].activity.item = ci;
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get("core.activity.read.start", cdata[cc], inv[ci]));
        }
        item_separate(ci);
        return 0;
    }
    if (cdata[cc].activity.turn > 0)
    {
        ci = cdata[cc].activity.item;
        cibkread = ci;
        chara_gain_exp_literacy(cdata.player());
        if (inv[ci].id == ItemId::recipe)
        {
            return 0;
        }
        if (inv[ci].id == ItemId::ancient_book)
        {
            r2 =
                50 + inv[ci].param1 * 50 + inv[ci].param1 * inv[ci].param1 * 20;
            r3 = 0;
        }
        else
        {
            r2 = the_ability_db[efid]->difficulty;
            r3 = efid;
        }
        if (inv[ci].curse_state == CurseState::blessed)
        {
            r2 = r2 * 100 / 120;
        }
        if (is_cursed(inv[ci].curse_state))
        {
            r2 = r2 * 150 / 100;
        }
        int stat = try_to_cast_spell();
        ci = cibkread;
        if (stat == 0)
        {
            cdata[cc].activity.finish();
            --inv[ci].count;
            if (inv[ci].count < 0)
            {
                inv[ci].count = 0;
            }
            if (inv[ci].count == 0)
            {
                inv[ci].modify_number(-1);
                if (is_in_fov(cdata[cc]))
                {
                    txt(i18n::s.get(
                        "core.action.read.book.falls_apart", inv[ci]));
                }
            }
        }
        return 0;
    }
    if (is_in_fov(cdata[cc]))
    {
        txt(i18n::s.get("core.activity.read.finish", cdata[cc], inv[ci]));
    }
    if (inv[ci].id == ItemId::recipe)
    {
        if (inv[ci].param1 == 0)
        {
            cdata[cc].activity.finish();
            return 1;
        }
        txt(i18n::s.get("core.action.read.recipe.learned", inv[ci]));
        ++recipememory(inv[ci].subname);
        item_identify(inv[ci], IdentifyState::partly);
        inv[ci].modify_number(-1);
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get("core.action.read.book.falls_apart", inv[ci]));
        }
        cdata[cc].activity.finish();
        return 1;
    }
    if (inv[ci].id == ItemId::ancient_book)
    {
        item_identify(inv[ci], IdentifyState::completely);
        txt(i18n::s.get("core.action.read.book.finished_decoding", inv[ci]));
        inv[ci].param2 = 1;
        inv[ci].count = 1;
        inv[ci].has_charge() = false;
        item_stack(0, inv[ci], true);
    }
    else
    {
        chara_gain_skill(
            cdata[cc],
            efid,
            1,
            (rnd(51) + 50) * (90 + sdata(165, cc) + (sdata(165, cc) > 0) * 20) /
                    clamp((100 + spell((efid - 400)) / 2), 50, 1000) +
                1);
        chara_gain_exp_memorization(cdata.player(), efid);
        if (itemmemory(2, itemid2int(inv[ci].id)) == 0)
        {
            itemmemory(2, itemid2int(inv[ci].id)) = 1;
        }
    }
    item_identify(inv[ci], IdentifyState::partly);
    if (inv[ci].id != ItemId::ancient_book)
    {
        --inv[ci].count;
        if (inv[ci].count < 0)
        {
            inv[ci].count = 0;
        }
        if (inv[ci].count == 0)
        {
            inv[ci].modify_number(-1);
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get("core.action.read.book.falls_apart", inv[ci]));
            }
        }
    }
    cdata[cc].activity.finish();
    return 1;
}



int read_normal_book()
{
    if (cdata[cc].blind != 0)
    {
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get("core.action.read.cannot_see", cdata[cc]));
        }
        return 0;
    }
    if (inv[ci].id == ItemId::license_of_the_void_explorer)
    {
        snd("core.book1");
        txt(i18n::s.get("core.action.read.book.void_permit"));
        return 1;
    }
    if (inv[ci].id == ItemId::textbook)
    {
        return read_textbook(inv[ci]);
    }
    if (inv[ci].id == ItemId::book_of_rachel)
    {
        snd("core.book1");
        txt(i18n::s.get("core.action.read.book.book_of_rachel"));
        return 1;
    }
    tc = cc;
    item_identify(inv[ci], IdentifyState::partly);
    show_book_window(inv[ci]);
    return 1;
}



int calcmagiccontrol(int caster_chara_index, int target_chara_index)
{
    if (sdata(188, caster_chara_index) != 0)
    {
        if (belong_to_same_team(
                cdata[caster_chara_index], cdata[target_chara_index]))
        {
            if (sdata(188, caster_chara_index) * 5 > rnd_capped(dmg + 1))
            {
                dmg = 0;
            }
            else
            {
                dmg = rnd_capped(
                    dmg * 100 / (100 + sdata(188, caster_chara_index) * 10) +
                    1);
            }
            if (dmg < 1)
            {
                if (is_in_fov(cdata[target_chara_index]))
                {
                    txt(i18n::s.get(
                        "core.misc.spell_passes_through",
                        cdata[target_chara_index]));
                }
                chara_gain_skill_exp(cdata[caster_chara_index], 188, 8, 4);
                return 1;
            }
            chara_gain_skill_exp(cdata[caster_chara_index], 188, 30, 2);
        }
    }
    return 0;
}



int do_cast_magic()
{
    int spellbk = 0;
    spellbk = efid;
    ccbk = cc;
    int stat = do_cast_magic_attempt();
    if (stat == 1)
    {
        cc = ccbk;
        chara_gain_exp_casting(cdata[cc], spellbk);
        return 1;
    }
    return 0;
}



int do_cast_magic_attempt()
{
    int mp = 0;
    efsource = 3;
    efstatus = CurseState::none;
    efp = calcspellpower(efid, cc);
    if (cc == 0)
    {
        if (calcspellcostmp(efid, cc) > cdata[cc].mp)
        {
            if (!g_config.skip_overcasting_warning())
            {
                txt(i18n::s.get("core.action.cast.overcast_warning"));
                if (!yes_no())
                {
                    update_screen();
                    efsource = 0;
                    return 0;
                }
            }
        }
        screenupdate = -1;
        update_screen();
    }
    int stat = prompt_magic_location();
    if (stat == 0)
    {
        efsource = 0;
        return 0;
    }
    if (cc != 0)
    {
        if (the_ability_db[efid]->ability_type == 7)
        {
            if (cdata[cc].relationship == 10 ||
                game_data.current_map == mdata_t::MapId::pet_arena)
            {
                efsource = 0;
                return 0;
            }
            if (game_data.play_turns % 10 > 4)
            {
                efsource = 0;
                return 0;
            }
        }
    }

    if (cc == 0)
    {
        spell(efid - 400) -= calcspellcoststock(efid, cc);
        if (spell(efid - 400) < 0)
        {
            spell(efid - 400) = 0;
        }
    }
    mp = calcspellcostmp(efid, cc);
    if (cc == 0)
    {
        if (cdata.player().god_id == core_god::ehekatl)
        {
            mp = rnd(mp * 140 / 100 + 1) + 1;
        }
    }
    damage_mp(cdata[cc], mp);
    if (cdata[cc].state() != Character::State::alive)
    {
        efsource = 0;
        return 1;
    }

    if (cdata[cc].confused != 0 || cdata[cc].dimmed != 0)
    {
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get("core.action.cast.confused", cdata[cc]));
        }
        const auto tcbk = tc(0);
        int stat = try_to_cast_spell();
        tc = tcbk;
        if (stat == 0)
        {
            efsource = 0;
            return 1;
        }
    }
    else if (is_in_fov(cdata[cc]))
    {
        if (cc == 0)
        {
            txt(i18n::s.get(
                "core.action.cast.self",
                cdata[cc],
                i18n::s.get_m(
                    "ability",
                    the_ability_db.get_id_from_legacy(efid)->get(),
                    "name"),
                i18n::s.get_enum(
                    "core.ui.cast_style", cdata[cc].special_attack_type)));
        }
        else
        {
            txt(i18n::s.get(
                "core.action.cast.other",
                cdata[cc],
                i18n::s.get_enum(
                    "core.ui.cast_style", cdata[cc].special_attack_type)));
        }
    }
    if (buff_has(cdata[cc], "core.mist_of_silence"))
    {
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get("core.action.cast.silenced"));
        }
        efsource = 0;
        return 1;
    }
    if (rnd(100) >= calcspellfail(efid, cc))
    {
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get("core.action.cast.fail", cdata[cc]));
            FailureToCastAnimation(cdata[cc].position).play();
        }
        efsource = 0;
        return 1;
    }
    if (noeffect == 1)
    {
        txt(i18n::s.get("core.common.nothing_happens"));
        efsource = 0;
        return 1;
    }
    efp = calcspellpower(efid, cc);
    if (const auto spell_enhancement = enchantment_find(cdata[cc], 34))
    {
        efp = efp * (100 + *spell_enhancement / 10) / 100;
    }
    rapidmagic = 0;
    if (cdata[cc].can_cast_rapid_magic() &&
        the_ability_db[efid]->ability_type == 2)
    {
        rapidmagic = 1 + (rnd(3) != 0) + (rnd(2) != 0);
    }
    if (rapidmagic)
    {
        for (int cnt = 0, cnt_end = (rapidmagic); cnt < cnt_end; ++cnt)
        {
            magic();
            if (cdata[tc].state() != Character::State::alive)
            {
                int stat = find_enemy_target();
                if (stat == 0)
                {
                    break;
                }
                else
                {
                    tc = cdata[cc].enemy_id;
                    if (relationbetween(cc, tc) != -3)
                    {
                        break;
                    }
                }
            }
        }
        rapidmagic = 0;
    }
    else
    {
        magic();
    }
    return 1;
}



int drink_potion()
{
    tc = cc;
    efsource = 4;
    if (potionspill || potionthrow)
    {
        if (potionthrow)
        {
            efp = efp * potionthrow / 100;
            efstatus = inv[ci].curse_state;
        }
    }
    else
    {
        efstatus = inv[ci].curse_state;
        if (is_in_fov(cdata[tc]))
        {
            snd_at("core.drink1", cdata[tc].position);
            txt(i18n::s.get("core.action.drink.potion", cdata[tc], inv[ci]));
        }
    }
    magic();
    if (potionspill || potionthrow)
    {
        potionspill = 0;
        potionthrow = 0;
    }
    else
    {
        if (obvious == 1)
        {
            if (tc == 0)
            {
                item_identify(inv[ci], IdentifyState::partly);
            }
        }
        inv[ci].modify_number(-1);
    }
    cdata[tc].nutrition += 150;
    if (tc < 16)
    {
        if (cdata[tc].nutrition > 12000)
        {
            if (rnd(5) == 0)
            {
                chara_vomit(cdata[tc]);
            }
        }
    }
    return 1;
}



int drink_well()
{
    if (inv[ci].param1 < -5 || inv[ci].param3 >= 20 ||
        (inv[ci].id == ItemId::holy_well && game_data.holy_well_count <= 0))
    {
        const auto valn = itemname(inv[ci]);
        txt(i18n::s.get("core.action.drink.well.is_dry", valn));
        return 1;
    }
    item_separate(ci);
    snd_at("core.drink1", cdata[cc].position);
    const auto valn = itemname(inv[ci]);
    txt(i18n::s.get("core.action.drink.well.draw", cdata[cc], valn));
    tc = cc;
    const auto cibk = ci;
    p = rnd(100);
    for (int cnt = 0; cnt < 1; ++cnt)
    {
        if (cc != 0)
        {
            if (rnd(15) == 0)
            {
                txt(i18n::s.get(
                    "core.action.drink.well.effect.falls.text", cdata[cc]));
                txt(i18n::s.get(
                        "core.action.drink.well.effect.falls.dialog",
                        cdata[cc]),
                    Message::color{ColorIndex::cyan});
                if (cdata[cc].is_floating() == 1 && cdata[cc].gravity == 0)
                {
                    txt(i18n::s.get(
                        "core.action.drink.well.effect.falls.floats",
                        cdata[cc]));
                }
                else
                {
                    damage_hp(cdata[cc], 9999, -1);
                }
                break;
            }
        }
        if (inv[ci].id == ItemId::holy_well)
        {
            if (rnd(2) == 0)
            {
                efid = 1113;
                magic();
                break;
            }
        }
        if (p > 70)
        {
            p = rnd(5);
            if (p == 0)
            {
                efid = 1112;
                efp = 100;
                magic();
                break;
            }
            if (p == 1)
            {
                efid = 1110;
                efp = 100;
                magic();
                break;
            }
            if (p == 2)
            {
                efid = 1111;
                efp = 100;
                magic();
                break;
            }
            if (p == 3)
            {
                efid = 1109;
                efp = 100;
                magic();
                break;
            }
            if (p == 4)
            {
                efid = 1108;
                efp = 100;
                magic();
                break;
            }
        }
        if (p > 55)
        {
            flt();
            itemcreate_extra_inv(
                54,
                cdata[cc].position,
                rnd_capped(sdata(159, cc) / 2 * 50 + 100) + 1);
            txt(i18n::s.get(
                "core.action.drink.well.effect.finds_gold", cdata[cc]));
            break;
        }
        if (p > 45)
        {
            p = rnd(8) + 10;
            if (rnd(5) > 2)
            {
                chara_gain_fixed_skill_exp(cdata[cc], p, 1000);
            }
            else
            {
                chara_gain_fixed_skill_exp(cdata[cc], p, -1000);
            }
            break;
        }
        if (p > 40)
        {
            if (cdata[cc].level < 5)
            {
                break;
            }
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get(
                    "core.action.drink.well.effect.pregnancy", cdata[cc]));
            }
            tc = cc;
            get_pregnant();
            break;
        }
        if (p > 35)
        {
            txt(i18n::s.get("core.action.drink.well.effect.monster"));
            for (int cnt = 0, cnt_end = (1 + rnd(3)); cnt < cnt_end; ++cnt)
            {
                flt(calcobjlv(cdata[cc].level * 3 / 2 + 3),
                    calcfixlv(Quality::bad));
                chara_create(-1, 0, cdata[cc].position.x, cdata[cc].position.y);
            }
            break;
        }
        if (p > 33)
        {
            efid = 1113;
            magic();
            break;
        }
        if (p > 20)
        {
            efid = 454;
            magic();
            break;
        }
        if (p == 0)
        {
            if (rnd(game_data.wish_count + 1))
            {
                txt(i18n::s.get(
                        "core.action.drink.well.effect.wish_too_frequent"),
                    Message::color{ColorIndex::orange});
                break;
            }
            ++game_data.wish_count;
            efid = 441;
            magic();
            break;
        }
        if (cc == 0)
        {
            txt(i18n::s.get("core.action.drink.well.effect.default"));
        }
    }
    ci = cibk;
    if (cc != 0)
    {
        cdata[cc].nutrition += 4000;
    }
    else
    {
        cdata[cc].nutrition += 500;
    }
    if (inv[ci].id == ItemId::holy_well)
    {
        --game_data.holy_well_count;
    }
    else
    {
        inv[ci].param1 -= rnd(3);
        inv[ci].param3 += rnd(3);
        if (inv[ci].param3 >= 20)
        {
            txt(i18n::s.get(
                "core.action.drink.well.completely_dried_up", inv[ci]));
            return 1;
        }
    }
    if (inv[ci].param1 < -5)
    {
        txt(i18n::s.get("core.action.drink.well.dried_up", inv[ci]));
    }
    return 1;
}



int read_scroll()
{
    tc = cc;
    tlocx = cdata[cc].position.x;
    tlocy = cdata[cc].position.y;
    efstatus = inv[ci].curse_state;
    efsource = 2;
    if (cdata[cc].blind != 0)
    {
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get("core.action.read.cannot_see", cdata[cc]));
        }
        efsource = 0;
        return 0;
    }
    if (cdata[cc].dimmed != 0 || cdata[cc].confused != 0)
    {
        if (rnd(4) != 0)
        {
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get(
                    "core.action.read.scroll.dimmed_or_confused", cdata[cc]));
            }
            efsource = 0;
            return 0;
        }
    }
    if (is_in_fov(cdata[cc]))
    {
        txt(i18n::s.get("core.action.read.scroll.execute", cdata[cc], inv[ci]));
    }
    if (inv[ci].id != ItemId::treasure_map)
    {
        inv[ci].modify_number(-1);
        chara_gain_skill_exp(cdata[cc], 150, 25, 2);
    }
    magic();
    if (cc == 0)
    {
        if (obvious == 1)
        {
            item_identify(inv[ci], IdentifyState::partly);
        }
    }
    return 1;
}



bool do_zap_internal(Character& doer, Item& rod)
{
    if (rod.count <= 0)
    {
        if (is_in_fov(doer))
        {
            txt(i18n::s.get("core.action.zap.execute", rod));
            txt(i18n::s.get("core.common.nothing_happens"));
        }
        return false;
    }

    efstatus = rod.curse_state;
    if (efstatus == CurseState::blessed)
    {
        efstatus = CurseState::none;
    }
    efsource = 1;

    int stat = prompt_magic_location();
    if (stat == 0)
    {
        efsource = 0;
        return false;
    }
    if (efid >= 400 && efid < 467)
    {
        if (noeffect == 1)
        {
            if (is_in_fov(doer))
            {
                txt(i18n::s.get("core.action.zap.execute", rod));
                txt(i18n::s.get("core.common.nothing_happens"));
            }
            return true;
        }
    }

    if (is_in_fov(doer))
    {
        txt(i18n::s.get("core.action.zap.execute", rod));
    }

    efp = efp *
        (100 + sdata(174, doer.index) * 10 + sdata(16, doer.index) / 2 +
         sdata(13, doer.index) / 2) /
        100;
    if (efid >= 400 && efid < 467)
    {
        f = 0;
        int skill = sdata(174, doer.index) * 20 + 100;
        if (rod.curse_state == CurseState::blessed)
        {
            skill = skill * 125 / 100;
        }
        if (is_cursed(rod.curse_state))
        {
            skill = skill * 50 / 100;
        }
        else if (rnd(2))
        {
            f = 1;
        }
        if (rnd((the_ability_db[efid]->difficulty + 1)) / 2 <= skill)
        {
            f = 1;
        }
    }
    else
    {
        f = 1;
    }

    if (rnd(30) == 0)
    {
        f = 0;
    }

    if (f == 1 || rod.id == ItemId::rod_of_wishing || doer.index != 0)
    {
        magic();
        if (doer.index == 0)
        {
            if (obvious == 1)
            {
                item_identify(rod, IdentifyState::partly);
            }
        }
        chara_gain_exp_magic_device(doer);
    }
    else if (is_in_fov(doer))
    {
        txt(i18n::s.get("core.action.zap.fail", doer));
    }

    return true;
}



int do_zap()
{
    const auto zapped = do_zap_internal(cdata[cc], inv[ci]);
    if (!zapped)
        return 0;

    efsource = 0;
    if (inv[ci].number() == 0)
    {
        if (ci >= ELONA_ITEM_ON_GROUND_INDEX)
        {
            cell_refresh(inv[ci].position.x, inv[ci].position.y);
            return 1;
        }
    }
    item_separate(ci);
    --inv[ci].count;
    return 1;
}



int do_magic_attempt()
{
    if (efid == 646)
    {
        if (cdata[tc].is_sentenced_daeth() == 1)
        {
            if (cdata[cc].relationship == -3)
            {
                for (int cnt = 0; cnt < ELONA_MAX_PARTY_CHARACTERS; ++cnt)
                {
                    if (cdata[cnt].state() == Character::State::alive)
                    {
                        if (cdata[cnt].relationship == 10)
                        {
                            cdata[cc].enemy_id = cnt;
                            break;
                        }
                    }
                }
            }
            return 0;
        }
    }
    {
        int stat = prompt_magic_location();
        if (stat == 0)
        {
            return 0;
        }
    }
    if (the_ability_db[efid]->range / 1000 * 1000 != 3000 &&
        the_ability_db[efid]->range / 1000 * 1000 != 10000)
    {
        if (cdata[cc].confused != 0 || cdata[cc].blind != 0)
        {
            if (rnd(5) == 0)
            {
                if (is_in_fov(cdata[cc]))
                {
                    txt(i18n::s.get("core.misc.shakes_head", cdata[cc]));
                }
                return 1;
            }
        }
    }
    if (efid >= 600)
    {
        if (cc == 0)
        {
            if (cdata.player().sp < 50)
            {
                if (cdata.player().sp < rnd(75))
                {
                    txt(i18n::s.get("core.magic.common.too_exhausted"));
                    damage_sp(
                        cdata.player(), the_ability_db[efid]->cost / 2 + 1);
                    return 1;
                }
            }
            damage_sp(
                cdata.player(),
                rnd(the_ability_db[efid]->cost / 2 + 1) +
                    the_ability_db[efid]->cost / 2 + 1);
            chara_gain_skill_exp(
                cdata[cc], the_ability_db[efid]->related_basic_attribute, 25);
        }
    }
    efp = calcspellpower(efid, cc);
    if (noeffect == 1)
    {
        if (efid != 300)
        {
            txt(i18n::s.get("core.common.nothing_happens"));
            return 1;
        }
    }
    {
        int stat = magic();
        if (stat == 0)
        {
            return 0;
        }
    }
    return 1;
}



int prompt_magic_location()
{
    noeffect = 0;
    if (efid > 661)
    {
        tc = cc;
        return 1;
    }
    tg = the_ability_db[efid]->range / 1000 * 1000;
    if (efsource == 1)
    {
        if (tg == 3000)
        {
            tg = 8000;
        }
    }
    if (the_ability_db[efid]->ability_type == 7)
    {
        if (cc == 0)
        {
            tc = 0;
            return 1;
        }
    }
    if (tg == 8000)
    {
        if (cc == 0)
        {
            tc = 0;
            txt(i18n::s.get("core.action.which_direction.ask"));
            update_screen();
            int stat = ask_direction();
            if (stat == 0)
            {
                return 0;
            }
            if (cell_data.at(tlocx, tlocy).chara_index_plus_one == 0)
            {
                noeffect = 1;
                obvious = 0;
                return 1;
            }
            tc = cell_data.at(tlocx, tlocy).chara_index_plus_one - 1;
        }
        else
        {
            if (dist(
                    cdata[tc].position.x,
                    cdata[tc].position.y,
                    cdata[cc].position.x,
                    cdata[cc].position.y) >
                the_ability_db[efid]->range % 1000 + 1)
            {
                return 0;
            }
            tlocx = cdata[tc].position.x;
            tlocy = cdata[tc].position.y;
        }
        return 1;
    }
    if (tg == 7000 || (tg == 9000 && tgloc == 1 && cc == 0))
    {
        if (cc == 0)
        {
            if (tg == 9000)
            {
                if (int stat = fov_los(
                                   cdata[cc].position.x,
                                   cdata[cc].position.y,
                                   tglocx,
                                   tglocy) == 0)
                {
                    if (stat == 0)
                    {
                        txt(i18n::s.get(
                            "core.action.which_direction.cannot_see_location"));
                        update_screen();
                    }
                    obvious = 0;
                    return 0;
                }
                tlocx = tglocx;
                tlocy = tglocy;
            }
            else
            {
                int stat = target_position();
                if (stat != 1)
                {
                    if (stat == 0)
                    {
                        txt(i18n::s.get(
                            "core.action.which_direction.cannot_see_location"));
                        update_screen();
                    }
                    obvious = 0;
                    return 0;
                }
            }
        }
        else
        {
            if (fov_los(
                    cdata[tc].position.x,
                    cdata[tc].position.y,
                    cdata[cc].position.x,
                    cdata[cc].position.y) == 0)
            {
                return 0;
            }
            tlocx = cdata[tc].position.x;
            tlocy = cdata[tc].position.y;
        }
        return 1;
    }
    if (tg == 3000 || tg == 10000)
    {
        if (cc != 0)
        {
            if (the_ability_db[efid]->ability_type == 3)
            {
                if (dist(
                        cdata[tc].position.x,
                        cdata[tc].position.y,
                        cdata[cc].position.x,
                        cdata[cc].position.y) >
                    the_ability_db[efid]->range % 1000 + 1)
                {
                    return 0;
                }
                if (fov_los(
                        cdata[cc].position.x,
                        cdata[cc].position.y,
                        cdata[tc].position.x,
                        cdata[tc].position.y) == 0)
                {
                    return 0;
                }
            }
        }
        tc = cc;
        tlocx = cdata[cc].position.x;
        tlocy = cdata[cc].position.y;
        return 1;
    }
    if (tg == 2000 || tg == 6000 || tg == 9000)
    {
        if (cc == 0)
        {
            int stat = find_enemy_target();
            if (stat == 0)
            {
                obvious = 0;
                return 0;
            }
            tc = cdata.player().enemy_id;
            if (cdata[tc].relationship >= 0)
            {
                int stat = prompt_really_attack();
                if (stat == 0)
                {
                    obvious = 0;
                    return 0;
                }
            }
        }
        if (dist(
                cdata[tc].position.x,
                cdata[tc].position.y,
                cdata[cc].position.x,
                cdata[cc].position.y) > the_ability_db[efid]->range % 1000 + 1)
        {
            if (cc == 0)
            {
                txt(i18n::s.get("core.action.which_direction.out_of_range"),
                    Message::only_once{true});
                update_screen();
            }
            return 0;
        }
        if (fov_los(
                cdata[cc].position.x,
                cdata[cc].position.y,
                cdata[tc].position.x,
                cdata[tc].position.y) == 0)
        {
            return 0;
        }
        tlocx = cdata[tc].position.x;
        tlocy = cdata[tc].position.y;
        return 1;
    }
    if (tg == 5000)
    {
        if (cc == 0)
        {
            if (efsource == 3)
            {
                txt(i18n::s.get("core.action.which_direction.spell"));
            }
            else
            {
                txt(i18n::s.get("core.action.which_direction.wand"));
            }
            update_screen();
            int stat = ask_direction();
            if (stat == 0)
            {
                txt(i18n::s.get("core.common.it_is_impossible"));
                obvious = 0;
                return 0;
            }
        }
    }
    return 1;
}



int pick_up_item(bool play_sound)
{
    const auto snd_ = [play_sound](data::InstanceId id) {
        if (play_sound)
        {
            snd(id);
        }
    };

    int sellgold = 0;
    if (cc != -1)
    {
        if (inv[ci].id == ItemId::gold_piece ||
            inv[ci].id == ItemId::platinum_coin)
        {
            snd_("core.getgold1");
            ti = ci;
            in = inv[ci].number();
            inv[ci].remove();
            txt(i18n::s.get(
                "core.action.pick_up.execute",
                cdata[cc],
                itemname(inv[ti], in)));
            cell_refresh(inv[ci].position.x, inv[ci].position.y);
            if (inv[ci].id == ItemId::gold_piece)
            {
                earn_gold(cdata[cc], in);
            }
            else
            {
                earn_platinum(cdata[cc], in);
            }
            return 1;
        }
    }
    if (cc == 0)
    {
        if (game_data.mount != 0)
        {
            if (cdata[game_data.mount].activity)
            {
                if (cdata[game_data.mount].activity.item == ci)
                {
                    txt(i18n::s.get(
                        "core.action.pick_up.used_by_mount",
                        cdata[game_data.mount]));
                    return 1;
                }
            }
        }
        if (the_item_db[itemid2int(inv[ci].id)]->category == ItemCategory::food)
        {
            if (inv[ci].own_state == 4)
            {
                if (!cdata.player().activity)
                {
                    if (!inv_getspace(0))
                    {
                        txt(i18n::s.get(
                            "core.ui.inv.common.inventory_is_full"));
                        return 0;
                    }
                    game_data.activity_about_to_start = 103;
                    activity_others(cdata[cc]);
                    return -1;
                }
            }
        }
        if (inv[ci].own_state == 3)
        {
            txt(i18n::s.get(
                "core.action.pick_up.do_you_want_to_remove", inv[ci]));
            if (yes_no())
            {
                snd_("core.build1");
                if (inv[ci].id == ItemId::shelter)
                {
                    std::string midbk = mid;
                    mid = ""s + 30 + u8"_"s + (100 + inv[ci].count);
                    tmpload(filepathutil::u8path(u8"mdata_"s + mid + u8".s2"));
                    if (fs::exists(
                            filesystem::dirs::tmp() /
                            (u8"mdata_"s + mid + u8".s2")))
                    {
                        ctrl_file(FileOperation::map_delete);
                    }
                    mid = midbk;
                    inv[ci].count = 0;
                    inv[ci].own_state = 0;
                }
            }
            else
            {
                return 0;
            }
        }
        if (inv_getfreeid(cc) == -1)
        {
            txt(i18n::s.get("core.action.pick_up.your_inventory_is_full"));
            return 0;
        }
    }
    inumbk = inv[ci].number() - in;
    inv[ci].set_number(in);
    if (cc == 0)
    {
        if (trait(215) != 0)
        {
            if (the_item_db[itemid2int(inv[ci].id)]->category ==
                ItemCategory::rod)
            {
                if (inv[ci].count > 0)
                {
                    item_db_on_zap(inv[ci], itemid2int(inv[ci].id));
                    txt(i18n::s.get(
                        "core.action.pick_up.you_absorb_magic", inv[ci]));
                    if (efid >= 400 && efid < 467)
                    {
                        spell(efid - 400) +=
                            inv[ci].count * 5 * inv[ci].number();
                    }
                    else
                    {
                        heal_mp(
                            cdata.player(),
                            inv[ci].count * 5 * inv[ci].number());
                    }
                    inv[ci].count = 0;
                }
            }
        }
        if (trait(216) != 0)
        {
            if (the_item_db[itemid2int(inv[ci].id)]->category ==
                ItemCategory::potion)
            {
                if (inv[ci].id != ItemId::poison &&
                    inv[ci].id != ItemId::potion_of_cure_corruption)
                {
                    if (rnd(5) == 0)
                    {
                        txt(i18n::s.get("core.action.pick_up.poison_drips"));
                        inv[ci].id = ItemId::poison;
                    }
                }
            }
        }
    }
    if (inv[ci].own_state < 0)
    {
        inv[ci].own_state = 0;
    }
    inv[ci].is_quest_target() = false;
    item_checkknown(inv[ci]);
    const auto stacked = item_stack(cc, inv[ci]);
    if (!stacked)
    {
        ti = inv_getfreeid(cc);
        if (ti == -1)
        {
            inv[ci].set_number(inumbk + in);
            if (invctrl == 12)
            {
                txt(i18n::s.get(
                    "core.action.pick_up.shopkeepers_inventory_is_full"));
            }
            else
            {
                txt(i18n::s.get("core.action.pick_up.your_inventory_is_full"));
            }
            return 0;
        }
        item_copy(ci, ti);
        inv[ti].set_number(in);
    }
    inv[ci].set_number(inumbk);
    if (mode == 6)
    {
        if (the_item_db[itemid2int(inv[ti].id)]->category == ItemCategory::food)
        {
            if (invctrl == 11 || invctrl == 22)
            {
                if (invctrl == 22 && invctrl(1) == 3)
                {
                    if (inv[ti].param3 > 0)
                    {
                        inv[ti].param3 += game_data.date.hours();
                    }
                }
                else if (inv[ti].param3 != 0 && inv[ti].material == 35)
                {
                    inv[ti].param3 = game_data.date.hours() +
                        the_item_db[itemid2int(inv[ti].id)]->expiration_date;
                    if (inv[ti].param2 != 0)
                    {
                        inv[ti].param3 += 72;
                    }
                }
            }
            if (invctrl == 24 && invctrl(1) == 3)
            {
                if (inv[ti].param3 > 0)
                {
                    inv[ti].param3 = inv[ti].param3 - game_data.date.hours();
                }
            }
        }
        if (invctrl == 11)
        {
            txt(i18n::s.get(
                "core.action.pick_up.you_buy", itemname(inv[ti], in)));
            sellgold = calcitemvalue(inv[ti], 0) * in;
            snd_("core.paygold1");
            cdata.player().gold -= sellgold;
            earn_gold(cdata[tc], sellgold);
            if (the_item_db[itemid2int(inv[ti].id)]->category ==
                ItemCategory::cargo)
            {
                inv[ti].param2 = calcitemvalue(inv[ti], 0);
            }
        }
        if (invctrl == 12)
        {
            sellgold = calcitemvalue(inv[ci], 1) * in;
            if (!inv[ti].is_stolen())
            {
                txt(i18n::s.get(
                    "core.action.pick_up.you_sell", itemname(inv[ti], in)));
            }
            else
            {
                inv[ti].is_stolen() = false;
                txt(i18n::s.get(
                    "core.action.pick_up.you_sell_stolen",
                    itemname(inv[ti], in)));
                if (game_data.guild.thieves_guild_quota > 0)
                {
                    game_data.guild.thieves_guild_quota -= sellgold;
                    if (game_data.guild.thieves_guild_quota < 0)
                    {
                        game_data.guild.thieves_guild_quota = 0;
                    }
                    txt(i18n::s.get(
                        "core.action.pick_up.thieves_guild_quota",
                        game_data.guild.thieves_guild_quota));
                }
            }
            snd_("core.getgold1");
            earn_gold(cdata.player(), sellgold);
            cdata[tc].gold -= sellgold;
            if (cdata[tc].gold < 0)
            {
                cdata[tc].gold = 0;
            }
            inv[ti].identify_state = IdentifyState::completely;
        }
        if (invctrl == 22 || invctrl == 24)
        {
            sound_pick_up();
            if (invctrl == 22)
            {
                txt(i18n::s.get(
                    "core.action.pick_up.execute",
                    cdata[cc],
                    itemname(inv[ti], in)));
            }
            else
            {
                txt(i18n::s.get(
                    "core.action.pick_up.put_in_container",
                    itemname(inv[ti], in)));
            }
        }
        else
        {
            chara_gain_exp_negotiation(cdata.player(), sellgold);
        }
    }
    else
    {
        cell_refresh(inv[ci].position.x, inv[ci].position.y);
        cell_data.at(inv[ci].position.x, inv[ci].position.y)
            .item_appearances_memory =
            cell_data.at(inv[ci].position.x, inv[ci].position.y)
                .item_appearances_actual;
        sound_pick_up();
        txt(i18n::s.get(
            "core.action.pick_up.execute", cdata[cc], itemname(inv[ti], in)));
    }
    if (cc == 0)
    {
        if (inv[ti].id == ItemId::campfire)
        {
            if (map_data.play_campfire_sound == 1)
            {
                f = 0;
                for (const auto& item : inv.ground())
                {
                    if (item.number() == 0)
                    {
                        continue;
                    }
                    if (item.id == ItemId::campfire)
                    {
                        f = 1;
                        break;
                    }
                }
                if (f == 0)
                {
                    map_data.play_campfire_sound = 0;
                    play_music();
                }
            }
        }
        int stat = convertartifact(ti);
        ti = stat;
        if (area_data[game_data.current_map].id == mdata_t::MapId::museum)
        {
            if (mode == 0)
            {
                update_museum();
            }
        }
        if (game_data.current_map == mdata_t::MapId::your_home)
        {
            if (mode == 0)
            {
                calc_home_rank();
            }
        }
        refresh_burden_state();
    }
    if (cc == -1)
    {
        refresh_burden_state();
    }

    return 1;
}



TurnResult do_bash()
{
    if (cell_data.at(x, y).item_appearances_memory != 0)
    {
        if (mapitemfind(x, y, 526) != -1)
        {
            ci = mapitemfind(x, y, 526);
            item_separate(ci);
            snd("core.bash1");
            txt(i18n::s.get("core.action.bash.tree.execute", inv[ci]));
            if (inv[ci].own_state == 5 || inv[ci].param1 <= 0)
            {
                txt(i18n::s.get("core.action.bash.tree.no_fruits"));
                return TurnResult::turn_end;
            }
            --inv[ci].param1;
            if (inv[ci].param1 <= 0)
            {
                inv[ci].image = 592;
                cell_refresh(x, y);
            }
            if (y + 1 < map_data.height)
            {
                if ((chip_data.for_cell(x, y + 1).effect & 4) == 0)
                {
                    ++y;
                }
            }
            flt();
            itemcreate_extra_inv(inv[ci].param2, x, y, 0);
            txt(i18n::s.get("core.action.bash.tree.falls_down", inv[ci]));
            item_stack(-1, inv[ci]);
            return TurnResult::turn_end;
        }
    }
    if (cell_data.at(x, y).chara_index_plus_one != 0)
    {
        tc = cell_data.at(x, y).chara_index_plus_one - 1;
        if (cdata[tc].sleep == 0)
        {
            if (cc == 0)
            {
                if (cdata[tc].relationship >= 0)
                {
                    int stat = prompt_really_attack();
                    if (stat == 0)
                    {
                        return TurnResult::pc_turn_user_error;
                    }
                }
            }
            if (cdata[tc].choked)
            {
                snd("core.bash1");
                txt(i18n::s.get(
                    "core.action.bash.choked.execute", cdata[cc], cdata[tc]));
                damage_hp(cdata[tc], sdata(10, cc) * 5, cc);
                if (cdata[tc].state() == Character::State::alive)
                {
                    txt(i18n::s.get(
                        "core.action.bash.choked.spits", cdata[tc]));
                    txt(i18n::s.get("core.action.bash.choked.dialog"));
                    cdata[tc].choked = 0;
                    chara_modify_impression(cdata[tc], 10);
                }
            }
            else
            {
                snd("core.bash1");
                txt(i18n::s.get(
                    "core.action.bash.execute", cdata[cc], cdata[tc]));
                hostileaction(cc, tc);
            }
        }
        else
        {
            snd("core.bash1");
            txt(i18n::s.get("core.action.bash.execute", cdata[cc], cdata[tc]));
            txt(i18n::s.get(
                "core.action.bash.disturbs_sleep", cdata[cc], cdata[tc]));
            modify_karma(cdata[cc], -1);
            cdata[tc].emotion_icon = 418;
        }
        cdata[tc].sleep = 0;
        return TurnResult::turn_end;
    }
    if (cell_data.at(x, y).feats != 0)
    {
        cell_featread(x, y);
        if (feat(1) == 30)
        {
            cell_data.at(x, y).feats = 0;
            spillfrag(x, y, 2);
            flt(calcobjlv(
                    game_data.current_dungeon_level *
                    (game_data.current_map != mdata_t::MapId::shelter_)),
                calcfixlv(Quality::bad));
            flttypemajor = choice(fsetbarrel);
            itemcreate_extra_inv(0, x, y, 0);
            if (is_in_fov(cdata[cc]))
            {
                snd("core.bash1");
                txt(i18n::s.get("core.action.bash.shatters_pot", cdata[cc]));
                snd("core.crush1");
                BreakingAnimation({x, y}).play();
            }
            return TurnResult::turn_end;
        }
        if (feat(1) == 21)
        {
            snd("core.bash1");
            p = feat(2) * 3 + 30;
            if (game_data.current_map == mdata_t::MapId::jail)
            {
                p *= 20;
            }
            if (rnd_capped(p(0)) < sdata(10, cc) && rnd(2))
            {
                txt(i18n::s.get("core.action.bash.door.destroyed"));
                if (feat(2) > sdata(10, cc))
                {
                    chara_gain_skill_exp(
                        cdata[cc], 10, (feat(2) - sdata(10, cc)) * 15);
                }
                cell_featset(x, y, 0, 0, 0, 0);
                return TurnResult::turn_end;
            }
            else
            {
                txt(i18n::s.get("core.action.bash.door.execute"));
                if (game_data.current_map == mdata_t::MapId::jail)
                {
                    txt(i18n::s.get("core.action.bash.door.jail"));
                }
                if (rnd(4) == 0)
                {
                    tc = cc;
                    efid = 1109;
                    efp = 200;
                    magic();
                }
                if (rnd(3) == 0)
                {
                    tc = cc;
                    efid = 1110;
                    efp = 200;
                    magic();
                }
                if (rnd(3) == 0)
                {
                    if (cdata[cc].quality < Quality::miracle &&
                        !enchantment_find(cdata[cc], 60010))
                    {
                        --cdata[cc].attr_adjs[0];
                        chara_refresh(cc);
                        if (is_in_fov(cdata[cc]))
                        {
                            txt(i18n::s.get(
                                    "core.action.bash.door.hurt", cdata[cc]),
                                Message::color{ColorIndex::purple});
                        }
                    }
                }
                if (rnd(3) == 0)
                {
                    if (feat(2) > 0)
                    {
                        --feat(2);
                        cell_featset(x, y, feat(0), feat(1), feat(2), feat(3));
                        if (is_in_fov(cdata[cc]))
                        {
                            txt(i18n::s.get("core.action.bash.door.cracked"));
                        }
                    }
                }
                return TurnResult::turn_end;
            }
        }
    }
    txt(i18n::s.get("core.action.bash.air", cdata[cc]));
    snd("core.miss");
    return TurnResult::turn_end;
}



void proc_autopick()
{
    if (!g_config.autopick())
        return;
    if (is_modifier_pressed(snail::ModKey::ctrl))
        return;
    if (area_data[game_data.current_map].type ==
            mdata_t::MapType::player_owned &&
        area_data[game_data.current_map].id != mdata_t::MapId::shelter_ &&
        area_data[game_data.current_map].id != mdata_t::MapId::ranch)
        return;


    for (auto&& item : inv.ground())
    {
        if (item.number() == 0)
            continue;
        if (item.position != cdata.player().position)
            continue;
        if (item.own_state > 0)
            continue;

        item_checkknown(item);

        const auto x = cdata.player().position.x;
        const auto y = cdata.player().position.y;

        bool did_something = true;
        const auto op = Autopick::instance().get_operation(item);
        switch (op.type)
        {
        case Autopick::Operation::Type::do_nothing:
            did_something = false;
            break;
        case Autopick::Operation::Type::pick_up:
        case Autopick::Operation::Type::save:
        case Autopick::Operation::Type::no_drop:
        case Autopick::Operation::Type::save_and_no_drop:
            // FIXME: DRY
            if (op.show_prompt)
            {
                txt(i18n::s.get(
                    "core.ui.autopick.do_you_really_pick_up", item));
                if (!yes_no())
                {
                    did_something = false;
                    break;
                }
            }
            in = item.number();
            elona::ci = item.index;
            pick_up_item(!op.sound);
            if (int(op.type) & int(Autopick::Operation::Type::no_drop))
            {
                inv[ti].is_marked_as_no_drop() = true;
                txt(i18n::s.get("core.ui.inv.examine.no_drop.set", inv[ti]));
            }
            if (int(op.type) & int(Autopick::Operation::Type::save))
            {
                if (!game_data.wizard)
                {
                    save_game();
                }
            }
            break;
        case Autopick::Operation::Type::destroy:
            // FIXME: DRY
            if (op.show_prompt)
            {
                txt(i18n::s.get(
                    "core.ui.autopick.do_you_really_destroy", item));
                if (!yes_no())
                {
                    did_something = false;
                    break;
                }
            }
            if (!op.sound)
            {
                snd("core.crush1");
            }
            txt(i18n::s.get("core.ui.autopick.destroyed", item));
            item.remove();
            cell_refresh(x, y);
            cell_data.at(x, y).item_appearances_memory =
                cell_data.at(x, y).item_appearances_actual;
            break;
        case Autopick::Operation::Type::open:
            // FIXME: DRY
            if (op.show_prompt)
            {
                txt(i18n::s.get("core.ui.autopick.do_you_really_open", item));
                if (!yes_no())
                {
                    did_something = false;
                    break;
                }
            }
            elona::ci = item.index;
            (void)do_open_command(!op.sound); // Result is unused.
            break;
        }
        if (did_something && op.sound)
        {
            snd(*op.sound);
        }
    }
}



int unlock_box(int difficulty)
{
    if (const auto lockpick = item_find(636, 3))
    {
        ti = lockpick->index;
    }
    else
    {
        txt(i18n::s.get("core.action.unlock.do_not_have_lockpicks"));
        return 0;
    }

    txt(i18n::s.get("core.action.unlock.use_lockpick"));
    snd("core.locked1");
    {
        if (item_find(637, 3))
        {
            i = sdata(158, 0) * 150 / 100 + 5;
            txt(i18n::s.get("core.action.unlock.use_skeleton_key"));
        }
        else
        {
            i = sdata(158, 0);
        }
    }
    f = 0;
    if (i * 2 < difficulty)
    {
        txt(i18n::s.get("core.action.unlock.too_difficult"));
        f = 1;
    }
    if (debug::voldemort)
    {
        f = 0;
    }
    if (f == 0)
    {
        if (i / 2 >= difficulty)
        {
            txt(i18n::s.get("core.action.unlock.easy"));
        }
        else if (rnd(rnd_capped(i * 2) + 1) < difficulty)
        {
            txt(i18n::s.get("core.action.unlock.fail"));
            f = 1;
        }
    }
    if (f)
    {
        if (rnd(3) == 0)
        {
            inv[ti].modify_number(-1);
            txt(i18n::s.get("core.action.unlock.lockpick_breaks"));
        }
        Message::instance().linebreak();
        txt(i18n::s.get("core.action.unlock.try_again"));
        if (yes_no())
        {
            unlock_box(difficulty);
            return 0;
        }
        return 0;
    }
    txt(i18n::s.get("core.action.unlock.succeed"));
    chara_gain_exp_lock_picking(cdata[cc]);
    return 1;
}



void open_box(Item& box)
{
    snd("core.chest1");
    txt(i18n::s.get("core.action.open.text", box));
    msg_halt();
    if (box.id == ItemId::material_box)
    {
        tc = cc;
        efid = 1117;
        efp = 100 + box.param1 * 10;
        box.param1 = 0;
        magic();
        return;
    }
    p = 3 + rnd(5);
    if (box.id == ItemId::treasure_ball ||
        box.id == ItemId::rare_treasure_ball ||
        box.id == ItemId::small_gamble_chest)
    {
        p = 1;
    }
    randomize(box.param3);
    for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
    {
        int item_id = 0;
        Quality base_quality;
        if (cnt == 0)
        {
            base_quality = Quality::great;
        }
        else
        {
            base_quality = Quality::good;
        }
        if (box.id == ItemId::bejeweled_chest)
        {
            if (cnt == 0 && rnd(3) == 0)
            {
                base_quality = Quality::miracle;
            }
            else
            {
                base_quality = Quality::great;
            }
            if (rnd(60) == 0)
            {
                item_id = 559;
            }
        }
        flt(calcobjlv(box.param1), calcfixlv(base_quality));
        flttypemajor = choice(fsetchest);
        if (cnt > 0)
        {
            if (rnd(3) != 0)
            {
                if (rnd(3) != 0)
                {
                    flttypeminor = 0;
                    flttypemajor = 68000;
                }
                else
                {
                    flttypemajor = 0;
                    flttypeminor = 77001;
                }
            }
        }
        if (box.id == ItemId::safe)
        {
            if (rnd(3) != 0)
            {
                flttypeminor = 0;
                flttypemajor = 68000;
            }
            else
            {
                flttypemajor = 0;
                flttypeminor = 77001;
            }
        }
        if (box.id == ItemId::treasure_ball ||
            box.id == ItemId::rare_treasure_ball)
        {
            flttypeminor = 0;
            flttypemajor = choice(fsetwear);
            fixlv = Quality::great;
            if (box.id == ItemId::rare_treasure_ball)
            {
                fixlv = Quality::miracle;
            }
            if (rnd(30) == 0)
            {
                item_id = 559;
            }
        }
        in = 0;
        if (box.id == ItemId::small_gamble_chest)
        {
            item_id = 54;
            randomize();
            if (rnd(75) == 0)
            {
                in = 50 * inv[ci].value;
            }
            else
            {
                in = rnd_capped(inv[ci].value / 10 + 1) + 1;
            }
        }
        if (box.id == ItemId::wallet)
        {
            item_id = 54;
            in = rnd(1000) + 1;
            if (rnd(5) == 0)
            {
                in = rnd(9) + 1;
            }
            if (rnd(10) == 0)
            {
                in = rnd(5000) + 5000;
            }
            if (rnd(20) == 0)
            {
                in = rnd(20000) + 10000;
            }
        }
        itemcreate_extra_inv(item_id, cdata.player().position, in);
    }
    randomize();
    f = 0;
    if (box.id != ItemId::small_gamble_chest)
    {
        if (rnd(10) == 0)
        {
            f = 1;
        }
    }
    if (box.id == ItemId::bejeweled_chest || box.id == ItemId::chest)
    {
        if (rnd(5) == 0)
        {
            f = 1;
        }
    }
    if (f)
    {
        flt();
        itemcreate_extra_inv(622, cdata.player().position, 1);
    }
    snd("core.ding2");
    txt(i18n::s.get("core.action.open.goods", box));
    save_set_autosave();
    box.param1 = 0;
    if (box.id == ItemId::wallet)
    {
        modify_karma(cdata.player(), -4);
    }
    if (box.id == ItemId::suitcase)
    {
        modify_karma(cdata.player(), -8);
    }
}



void open_new_year_gift(Item& box)
{
    snd("core.chest1");
    txt(i18n::s.get("core.action.open.text", box));
    msg_halt();
    snd("core.ding2");
    randomize();
    cc = 0;
    box.param1 = 0;
    if (box.param3 < 100)
    {
        if (rnd(3) == 0)
        {
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get(
                    "core.action.open.new_year_gift.something_jumps_out"));
            }
            for (int cnt = 0, cnt_end = (3 + rnd(3)); cnt < cnt_end; ++cnt)
            {
                flt(calcobjlv(cdata.player().level * 3 / 2 + 3),
                    calcfixlv(Quality::bad));
                chara_create(-1, 0, cdata[cc].position.x, cdata[cc].position.y);
            }
            return;
        }
        if (rnd(3) == 0)
        {
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get("core.action.open.new_year_gift.trap"));
            }
            for (int cnt = 0; cnt < 6; ++cnt)
            {
                tlocx = cdata.player().position.x + rnd(3) - rnd(3);
                tlocy = cdata.player().position.y - rnd(3) + rnd(3);
                if (tlocx < 0 || tlocx >= map_data.width || tlocy < 0 ||
                    tlocy >= map_data.height)
                {
                    continue;
                }
                mef_add(tlocx, tlocy, 5, 24, rnd(15) + 20, 50, 0);
                mapitem_fire(tlocx, tlocy);
            }
            return;
        }
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get("core.action.open.new_year_gift.cursed_letter"));
        }
        efid = 1114;
        efp = 1000;
        tc = 0;
        magic();
        return;
    }
    if (box.param3 < 200)
    {
        if (rnd(4) == 0)
        {
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get("core.action.open.new_year_gift.ring"),
                    Message::color{ColorIndex::orange});
            }
            flt();
            int stat = chara_create(
                -1, 328 + rnd(2), cdata[cc].position.x, cdata[cc].position.y);
            if (stat != 0)
            {
                if (cdata[cc].relationship <= -3)
                {
                    cdata[rc].relationship = -1;
                    cdata[rc].original_relationship = -1;
                }
            }
            return;
        }
        if (rnd(5) == 0)
        {
            if (is_in_fov(cdata[cc]))
            {
                txt(i18n::s.get(
                    "core.action.open.new_year_gift.younger_sister"));
            }
            flt();
            int stat = chara_create(
                -1, 176, cdata[cc].position.x, cdata[cc].position.y);
            if (stat != 0)
            {
                cdata[rc].gold = 5000;
            }
            return;
        }
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get("core.action.open.new_year_gift.something_inside"));
        }
        flt();
        itemcreate_extra_inv(choice(isetgiftminor), cdata.player().position, 1);
        return;
    }
    if (rnd(3) == 0)
    {
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get("core.action.open.new_year_gift.ring"),
                Message::color{ColorIndex::orange});
        }
        for (int cnt = 0, cnt_end = (2 + rnd(3)); cnt < cnt_end; ++cnt)
        {
            flt();
            int stat = chara_create(
                -1, 328 + rnd(2), cdata[cc].position.x, cdata[cc].position.y);
            if (stat != 0)
            {
                if (cdata[cc].relationship <= -3)
                {
                    cdata[rc].relationship = -1;
                    cdata[rc].original_relationship = -1;
                }
            }
        }
        return;
    }
    if (rnd(50) == 0)
    {
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get("core.action.open.new_year_gift.wonderful"));
        }
        flt();
        itemcreate_extra_inv(choice(isetgiftgrand), cdata.player().position, 1);
        return;
    }
    if (is_in_fov(cdata[cc]))
    {
        txt(i18n::s.get("core.action.open.new_year_gift.something_inside"));
    }
    flt();
    itemcreate_extra_inv(choice(isetgiftmajor), cdata.player().position, 1);
}



TurnResult try_to_open_locked_door()
{
    cell_featread(dx, dy);
    if (feat == tile_doorclosed4 && feat(2) > 0)
    {
        if (cc == 0)
        {
            int stat = unlock_box(feat(2));
            if (stat == 0)
            {
                screenupdate = -1;
                update_screen();
                await(g_config.animation_wait() * 5);
                return TurnResult::turn_end;
            }
            feat(2) = 0;
        }
        else
        {
            return TurnResult::turn_end;
        }
    }
    if (feat(2) > 0)
    {
        f = 0;
        if (rnd(feat(2) * 20 + 150) < sdata(158, cc) * 20 + 20)
        {
            f = 1;
        }
    }
    else
    {
        f = 1;
    }
    if (debug::voldemort)
    {
        f = 1;
    }
    if (f)
    {
        if (feat(2) > 0)
        {
            chara_gain_exp_lock_picking(cdata[cc]);
        }
        cell_featset(dx, dy, tile_dooropen, 20, 0, -1);
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get("core.action.open.door.succeed", cdata[cc]));
            if (map_data.tileset == 8)
            {
                snd("core.door2");
            }
            else if (map_data.tileset == 9)
            {
                snd("core.card1");
            }
            else
            {
                snd("core.door1");
            }
        }
    }
    else
    {
        if (is_in_fov(cdata[cc]))
        {
            snd("core.locked1");
            txt(i18n::s.get("core.action.open.door.fail", cdata[cc]),
                Message::only_once{true});
        }
    }
    if (cc == 0)
    {
        await(g_config.animation_wait() * 5);
    }
    return TurnResult::turn_end;
}



void discover_trap()
{
    cell_featset(refx, refy, tile_trap, -1, -1);
}



void discover_hidden_path()
{
    cell_data.at(refx, refy).chip_id_actual = tile_tunnel;
    cell_featset(refx, refy, 0, 0);
}



TurnResult do_plant()
{
    screenupdate = -1;
    update_screen();
    if (map_data.type == mdata_t::MapType::world_map || map_is_town_or_guild())
    {
        txt(i18n::s.get("core.action.plant.cannot_plant_it_here"));
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    if (cell_data.at(cdata[cc].position.x, cdata[cc].position.y).feats != 0)
    {
        txt(i18n::s.get("core.action.plant.cannot_plant_it_here"));
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    int val0;
    if (chip_data.for_cell(cdata.player().position.x, cdata.player().position.y)
            .kind == 2)
    {
        val0 = 1;
    }
    else
    {
        val0 = 0;
    }
    feat(0) = tile_plant;
    feat(1) = 29;
    feat(2) = inv[ci].material;
    try_to_grow_plant(val0);
    if (val0)
    {
        s = i18n::s.get("core.action.plant.on_field", inv[ci]);
    }
    else
    {
        s = i18n::s.get("core.action.plant.execute", inv[ci]);
    }
    txt(s);
    snd("core.bush1");
    inv[ci].modify_number(-1);
    cell_featset(
        cdata[cc].position.x,
        cdata[cc].position.y,
        tile_plant,
        29,
        inv[ci].material,
        feat(3));
    chara_gain_skill_exp(cdata.player(), 180, 300);
    return TurnResult::turn_end;
}

} // namespace elona

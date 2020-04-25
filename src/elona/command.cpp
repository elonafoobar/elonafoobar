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
#include "data/types/type_music.hpp"
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
#include "talk.hpp"
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
    optional<int> d;
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
        const auto d_ = dist(
            item.position.x,
            item.position.y,
            cdata.player().position.x,
            cdata.player().position.y);
        if (!d || d_ < *d)
        {
            d = d_;
        }
    }
    if (d)
    {
        if (*d <= 3)
        {
            txt(i18n::s.get("core.action.search.crystal.close"));
        }
        else if (*d <= 9)
        {
            txt(i18n::s.get("core.action.search.crystal.normal"));
        }
        else if (*d <= 16)
        {
            txt(i18n::s.get("core.action.search.crystal.far"));
        }
        else
        {
            txt(i18n::s.get("core.action.search.crystal.sense"));
        }
    }
}



void _try_to_reveal_small_coin(Character& chara)
{
    if (chara.position.x == x && chara.position.y == y)
    {
        snd("core.ding2");
        txt(i18n::s.get("core.action.search.small_coin.find"));
        cell_data.at(x, y).feats = 0;
        flt();
        itemcreate_extra_inv(622, x, y, 0);
    }
    else
    {
        if (dist(chara.position.x, chara.position.y, x, y) > 2)
        {
            txt(i18n::s.get("core.action.search.small_coin.far"));
        }
        else
        {
            txt(i18n::s.get("core.action.search.small_coin.close"));
        }
    }
}



void _search_for_map_feats(Character& chara)
{
    cell_featread(x, y);
    refx = x;
    refy = y;
    if (std::abs(chara.position.y - y) <= 1 &&
        std::abs(chara.position.x - x) <= 1)
    {
        if (feat(1) == 14)
        {
            if (feat(0) == 0)
            {
                int stat = try_to_reveal(chara);
                if (stat == 1)
                {
                    discover_trap();
                    txt(i18n::s.get("core.action.search.discover.trap"));
                }
            }
        }
        if (feat(1) == 22)
        {
            int stat = try_to_reveal(chara);
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
            _try_to_reveal_small_coin(chara);
        }
    }
}



void _search_surroundings(Character& chara)
{
    for (int cnt = 0; cnt < 11; ++cnt)
    {
        y = chara.position.y + cnt - 5;
        if (y < 0 || y >= map_data.height)
        {
            continue;
        }
        for (int cnt = 0; cnt < 11; ++cnt)
        {
            x = chara.position.x + cnt - 5;
            if (x < 0 || x >= map_data.width)
            {
                continue;
            }
            if (cell_data.at(x, y).feats != 0)
            {
                _search_for_map_feats(chara);
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



void _dig_material_spot(Character& chara)
{
    rowactre(0) = 1;
    rowactre(1) = chara.position.x;
    rowactre(2) = chara.position.y;
    if (feat(1) == 24)
    {
        spot_digging(chara);
    }
    if (feat(1) == 27)
    {
        spot_digging(chara);
    }
    if (feat(1) == 26)
    {
        spot_fishing(chara, none);
    }
    if (feat(1) == 25)
    {
        spot_mining_or_wall(chara);
    }
    if (feat(1) == 28)
    {
        spot_material(chara);
    }
}



TurnResult _pre_proc_movement_event(Character& chara)
{
    if (map_data.type == mdata_t::MapType::world_map)
    {
        if (264 <= cell_data.at(chara.next_position.x, chara.next_position.y)
                       .chip_id_actual &&
            cell_data.at(chara.next_position.x, chara.next_position.y)
                    .chip_id_actual < 363)
        {
            return TurnResult::pc_turn_user_error;
        }
    }
    return proc_movement_event(chara);
}



TurnResult _bump_into_character(Character& chara)
{
    if (chara.relationship >= 10 ||
        (chara.relationship == -1 && !g_config.attack_neutral_npcs()) ||
        (chara.relationship == 0 &&
         (area_data[game_data.current_map].is_museum_or_shop() ||
          is_modifier_pressed(snail::ModKey::shift))))
    {
        if (chara.is_hung_on_sand_bag() == 0)
        {
            if (map_data.type == mdata_t::MapType::world_map)
            {
                return _pre_proc_movement_event(cdata.player());
            }
            if (g_config.scroll())
            {
                cdata.player().next_position.x = chara.position.x;
                cdata.player().next_position.y = chara.position.y;
                ui_scroll_screen();
            }
            cell_swap(cdata.player().index, chara.index);
            txt(i18n::s.get("core.action.move.displace.text", chara));
            if (chara.id == CharaId::rogue)
            {
                if (rnd(5) == 0)
                {
                    if (chara.sleep == 0)
                    {
                        p = rnd(clamp(cdata.player().gold, 0, 20) + 1);
                        if (cdata.player().is_protected_from_thieves())
                        {
                            p = 0;
                        }
                        if (p != 0)
                        {
                            snd("core.getgold1");
                            cdata.player().gold -= p;
                            earn_gold(chara, p);
                            txt(i18n::s.get(
                                "core.action.move.displace.dialog"));
                        }
                    }
                }
            }
            if (chara.activity.type == Activity::Type::eat)
            {
                if (chara.activity.turn > 0)
                {
                    txt(i18n::s.get("core.action.move.interrupt", chara));
                    chara.activity.type = Activity::Type::none;
                    chara.activity.turn = 0;
                }
            }
            sense_map_feats_on_move(cdata.player());
            return TurnResult::turn_end;
        }
    }
    if (running)
    {
        if (chara.relationship >= -2 || keybd_wait >= 40)
        {
            return TurnResult::pc_turn_user_error;
        }
    }
    if (chara.relationship <= -1)
    {
        cdata.player().enemy_id = chara.index;
        if (chara.is_invisible() == 1)
        {
            if (cdata.player().can_see_invisible() == 0)
            {
                if (chara.wet == 0)
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
        try_to_melee_attack(cdata.player(), chara);
        return TurnResult::turn_end;
    }
    talk_to_npc(chara);
    if (chatteleport == 1)
    {
        chatteleport = 0;
        return TurnResult::exit_map;
    }
    return TurnResult::turn_end;
}



optional<TurnResult> use_gene_machine()
{
    Message::instance().linebreak();
    txt(i18n::s.get("core.action.use.gene_machine.choose_original"));

    const auto original_character =
        ctrl_ally(ControlAllyOperation::gene_engineer);
    if (original_character == -1)
    {
        return TurnResult::turn_end;
    }

    Message::instance().linebreak();
    txt(i18n::s.get("core.action.use.gene_machine.choose_subject"));

    int gene_chara_index{};
    while (true)
    {
        gene_chara_index = ctrl_ally(
            ControlAllyOperation::gene_engineer, cdata[original_character]);
        if (gene_chara_index == -1)
        {
            break;
        }
        if (cdata[gene_chara_index].has_been_used_stethoscope())
        {
            txt(i18n::s.get(
                "core.action.use.gene_machine.precious_ally",
                cdata[gene_chara_index]));
            continue;
        }
        break;
    }
    if (gene_chara_index == -1)
    {
        return TurnResult::turn_end;
    }

    update_screen();

    Message::instance().linebreak();
    txt(i18n::s.get(
        "core.action.use.gene_machine.prompt",
        cdata[gene_chara_index],
        cdata[original_character]));
    if (!yes_no())
    {
        return TurnResult::turn_end;
    }

    Message::instance().linebreak();
    txt(i18n::s.get(
            "core.action.use.gene_machine.has_inherited",
            cdata[original_character],
            cdata[gene_chara_index]),
        Message::color{ColorIndex::orange});

    GeneEngineeringAnimation(cdata[original_character].position).play();

    {
        int stat = transplant_body_parts(
            cdata[original_character], cdata[gene_chara_index]);
        if (stat != -1)
        {
            cdata[original_character].body_parts[stat - 100] = rtval * 10000;
            txt(i18n::s.get(
                    "core.action.use.gene_machine.gains.body_part",
                    cdata[original_character],
                    i18n::s.get_enum("core.ui.body_part", rtval)),
                Message::color{ColorIndex::green});
            refresh_speed_correction_value(cdata[original_character]);
        }
    }

    {
        int stat = gain_skills_by_geen_engineering(
            cdata[original_character], cdata[gene_chara_index]);
        if (stat != 0)
        {
            for (int cnt = 0; cnt < 2; ++cnt)
            {
                if (rtval(cnt) == -1)
                {
                    break;
                }
                chara_gain_skill(cdata[original_character], rtval(cnt), 1);
                txt(i18n::s.get(
                        "core.action.use.gene_machine.gains.ability",
                        cdata[original_character],
                        i18n::s.get_m(
                            "ability",
                            the_ability_db.get_id_from_legacy(rtval(cnt))
                                ->get(),
                            "name")),
                    Message::color{ColorIndex::green});
            }
        }
    }

    if (cdata[gene_chara_index].level > cdata[original_character].level)
    {
        lv = (cdata[gene_chara_index].level - cdata[original_character].level) /
                2 +
            1;
        for (int cnt = 0, cnt_end = (lv); cnt < cnt_end; ++cnt)
        {
            r2 = 1;
            gain_level(cdata[original_character]);
        }
        txt(i18n::s.get(
                "core.action.use.gene_machine.gains.level",
                cdata[original_character],
                cdata[original_character].level),
            Message::color{ColorIndex::green});
        listmax = 0;
        for (int cnt = 10; cnt < 18; ++cnt)
        {
            list(0, listmax) = cnt;
            list(1, listmax) = sdata.get(cnt, gene_chara_index).original_level;
            ++listmax;
        }
        sort_list_by_column1();
        for (int cnt = 0; cnt < 3; ++cnt)
        {
            p = listmax - cnt - 1;
            i = list(0, p);
            if (list(1, p) > sdata.get(i, original_character).original_level)
            {
                p = (list(1, p) -
                     sdata.get(i, original_character).original_level) *
                    500;
                p = clamp(p * 10 / clamp(lv, 2, 10), 1000, 10000);
                chara_gain_fixed_skill_exp(cdata[original_character], i, p);
            }
        }
    }

    chara_vanquish(gene_chara_index);
    save_set_autosave();
    chara_gain_skill_exp(cdata.player(), 151, 1200);
    randomize();
    screenupdate = -1;
    update_screen();
    snd("core.pop2");
    menu_character_sheet_investigate(cdata[original_character]);

    return none;
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
    auto target_chara_index = cell_data.at(x, y).chara_index_plus_one - 1;
    if (target_chara_index == -1)
    {
        txt(i18n::s.get("core.ui.invalid_target"));
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    if (target_chara_index == 0)
    {
        if (game_data.mount != 0)
        {
            target_chara_index = game_data.mount;
        }
    }
    if (target_chara_index != 0)
    {
        if (target_chara_index < 16)
        {
            if (!cdata[target_chara_index].is_escorted() &&
                !cdata[target_chara_index].is_escorted_in_sub_quest())
            {
                return try_interact_with_npc(cdata[target_chara_index]);
            }
        }
        update_screen();
        invctrl = 10;
        snd("core.inv");
        MenuResult mr = ctrl_inventory(cdata[target_chara_index]).menu_result;
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
    const auto target_index = cell_data.at(x, y).chara_index_plus_one - 1;
    if (target_index == -1)
    {
        txt(i18n::s.get("core.ui.invalid_target"));
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    txt(i18n::s.get("core.action.interact.prompt", cdata[target_index]));
    p = 0;

    Prompt prompt("core.action.interact.choices");
    if (target_index != 0)
    {
        if (cdata.player().confused == 0)
        {
            prompt.append("talk", 0);
            prompt.append("attack", 1);
        }
        if (cdata[target_index].is_escorted() == 0)
        {
            if (cdata[target_index].is_escorted_in_sub_quest() == 0)
            {
                if (target_index < 16)
                {
                    prompt.append("inventory", 4);
                }
                else
                {
                    prompt.append("give", 2);
                }
                if (cdata[target_index].is_livestock() == 1)
                {
                    prompt.append("bring_out", 5);
                }
                if (target_index < 16)
                {
                    prompt.append("appearance", 8);
                }
            }
        }
        prompt.append("teach_words", 7);
        prompt.append("change_tone", 10);
        if (game_data.current_map != mdata_t::MapId::show_house)
        {
            if (cdata[target_index].is_hung_on_sand_bag())
            {
                prompt.append("release", 9);
            }
        }
    }
    prompt.append("name", 3);
    if (game_data.wizard)
    {
        prompt.append("info", 6);
        if (target_index != 0 && !cdata[target_index].is_hung_on_sand_bag())
        {
            prompt.append("hang", 11);
        }
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
        talk_to_npc(cdata[target_index]);
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
        try_to_melee_attack(cdata.player(), cdata[target_index]);
        return TurnResult::turn_end;
    }
    if (p == 2)
    {
        update_screen();
        invctrl = 10;
        snd("core.inv");
        MenuResult mr = ctrl_inventory(cdata[target_index]).menu_result;
        assert(mr.turn_result != TurnResult::none);
        return mr.turn_result;
    }
    if (p == 3)
    {
        update_screen();
        return call_npc(cdata[target_index]);
    }
    if (p == 4)
    {
        return try_interact_with_npc(cdata[target_index]);
    }
    if (p == 5)
    {
        new_ally_joins(cdata[target_index]);
        update_screen();
        return TurnResult::turn_end;
    }
    if (p == 6)
    {
        snd("core.pop2");
        menu_character_sheet_investigate(cdata[target_index]);
        return TurnResult::pc_turn_user_error;
    }
    if (p == 7)
    {
        txt(i18n::s.get(
            "core.action.interact.change_tone.prompt", cdata[target_index]));
        inputlog = "";
        input_text_dialog((windoww - 360) / 2 + inf_screenx, winposy(90), 20);
        cdata[target_index].has_custom_talk() = false;
        if (inputlog == ""s)
        {
            cdatan(4, target_index) = "";
        }
        else
        {
            cdatan(4, target_index) = inputlog;
            txt(""s + cdatan(4, target_index),
                Message::color{ColorIndex::cyan});
        }
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    if (p == 8)
    {
        gsel(0);
        menu_change_appearance(cdata[target_index]);
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    if (p == 9)
    {
        snd("core.build1");
        cdata[target_index].is_hung_on_sand_bag() = false;
        txt(i18n::s.get("core.action.interact.release", cdata[target_index]));
        flt();
        itemcreate_extra_inv(733, cdata[target_index].position, 0);
    }
    if (p == 10)
    {
        change_npc_tone(cdata[target_index]);
    }
    if (p == 11)
    {
        snd("core.build1");
        cdata[target_index].is_hung_on_sand_bag() = true;
        txt(i18n::s.get("core.action.use.sandbag.start", cdata[target_index]));
        txt(i18n::s.get(
            "core.action.use.leash.other.start.dialog", cdata[target_index]));
        animeload(8, cdata[target_index]);
    }
    update_screen();
    return TurnResult::pc_turn_user_error;
}



TurnResult call_npc(Character& chara)
{
    txt(i18n::s.get("core.action.interact.name.prompt", chara));
    inputlog = "";
    input_text_dialog((windoww - 220) / 2 + inf_screenx, winposy(90), 12);
    if (inputlog == ""s)
    {
        txt(i18n::s.get("core.action.interact.name.cancel"));
    }
    else
    {
        cdatan(0, chara.index) = ""s + inputlog;
        chara.has_own_name() = true;
        txt(i18n::s.get("core.action.interact.name.you_named", chara));
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
    return do_bash(cdata.player());
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
            spot_digging(cdata.player());
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

    _search_surroundings(cdata.player());

    cell_featread(cdata.player().position.x, cdata.player().position.y);

    _proc_manis_disassembly(cdata.player());

    if (feat(1) >= 24 && feat(1) <= 28)
    {
        _dig_material_spot(cdata.player());
    }
    return TurnResult::turn_end;
}



TurnResult do_pray_command()
{
    if (const auto altar = item_find(60002))
    {
        int god_id_int = altar->param1;
        if (core_god::int2godid(god_id_int) != cdata.player().god_id)
        {
            begin_to_believe_god(god_id_int);
            return TurnResult::turn_end;
        }
    }
    return do_pray();
}



TurnResult do_throw_command_internal(Character& thrower, Item& throw_item)
{
    if (thrower.index == 0)
    {
        refresh_burden_state();
    }
    x = tlocx;
    y = tlocy;
    BreakingAnimation({x, y}).play();
    if (throw_item.id == ItemId::monster_ball ||
        throw_item.id == ItemId::little_ball)
    {
        snd("core.throw2");
        cell_refresh(throw_item.position.x, throw_item.position.y);
        if (cell_data.at(tlocx, tlocy).chara_index_plus_one != 0)
        {
            const auto target_index =
                cell_data.at(tlocx, tlocy).chara_index_plus_one - 1;
            txt(i18n::s.get("core.action.throw.hits", cdata[target_index]));
            if (throw_item.id == ItemId::monster_ball)
            {
                if (target_index < ELONA_MAX_PARTY_CHARACTERS ||
                    cdata[target_index].role != Role::none ||
                    cdata[target_index].quality == Quality::special ||
                    cdata[target_index].is_lord_of_dungeon() == 1)
                {
                    txt(i18n::s.get(
                        "core.action.throw.monster_ball.cannot_be_captured"));
                    return TurnResult::turn_end;
                }
                if (cdata[target_index].level > throw_item.param2)
                {
                    txt(i18n::s.get(
                        "core.action.throw.monster_ball.not_enough_power"));
                    return TurnResult::turn_end;
                }
                if (cdata[target_index].hp > cdata[target_index].max_hp / 10)
                {
                    txt(i18n::s.get(
                        "core.action.throw.monster_ball.not_weak_enough"));
                    return TurnResult::turn_end;
                }
                txt(i18n::s.get(
                        "core.action.throw.monster_ball.capture",
                        cdata[target_index]),
                    Message::color{ColorIndex::green});
                animeload(8, cdata[target_index]);
                throw_item.subname = charaid2int(cdata[target_index].id);
                throw_item.param3 = cdata[target_index].level;
                throw_item.weight =
                    clamp(cdata[target_index].weight, 10000, 100000);
                throw_item.value = 1000;
            }
            else
            {
                if (cdata[target_index].id != CharaId::little_sister ||
                    target_index < 16)
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
                new_ally_joins(cdata[target_index]);
            }
            chara_vanquish(target_index);
            quest_check();
        }
        return TurnResult::turn_end;
    }
    if (the_item_db[itemid2int(throw_item.id)]->category ==
            ItemCategory::potion ||
        throw_item.id == ItemId::tomato)
    {
        if (throw_item.id != ItemId::empty_bottle)
        {
            if (is_in_fov({tlocx, tlocy}))
            {
                if (throw_item.id == ItemId::handful_of_snow)
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
                const auto target_index =
                    cell_data.at(tlocx, tlocy).chara_index_plus_one - 1;
                if (is_in_fov(cdata[target_index]))
                {
                    txt(i18n::s.get(
                        "core.action.throw.hits", cdata[target_index]));
                    wet(target_index, 25);
                }
                rowact_check(cdata[target_index]);
                if (throw_item.id == ItemId::handful_of_snow)
                {
                    if (is_in_fov(cdata[target_index]))
                    {
                        if (target_index != 0)
                        {
                            txt(i18n::s.get("core.action.throw.snow.dialog"),
                                Message::color{ColorIndex::cyan});
                        }
                    }
                    return TurnResult::turn_end;
                }
                if (throw_item.id == ItemId::tomato)
                {
                    if (is_in_fov(cdata[target_index]))
                    {
                        txt(i18n::s.get("core.action.throw.tomato"),
                            Message::color{ColorIndex::blue});
                    }
                    if (throw_item.param3 == -1)
                    {
                        if (is_in_fov(cdata[target_index]))
                        {
                            txt(i18n::s.get(
                                    "core.damage.is_engulfed_in_fury",
                                    cdata[target_index]),
                                Message::color{ColorIndex::blue});
                        }
                        cdata[target_index].furious += rnd(10) + 5;
                    }
                    return TurnResult::turn_end;
                }
                if (target_index >= 16)
                {
                    hostileaction(thrower.index, target_index);
                }
                potionthrow = 100;
                item_db_on_drink(
                    cdata[target_index], throw_item, itemid2int(throw_item.id));
                return TurnResult::turn_end;
            }
            if (throw_item.id == ItemId::handful_of_snow)
            {
                if (cell_data.at(tlocx, tlocy).item_appearances_actual != 0)
                {
                    if (const auto snowman =
                            mapitemfind({tlocx, tlocy}, ItemId::snow_man))
                    {
                        if (is_in_fov({tlocx, tlocy}))
                        {
                            txt(i18n::s.get(
                                "core.action.throw.snow.hits_snowman",
                                *snowman));
                        }
                        snowman->modify_number(-1);
                        cell_refresh(tlocx, tlocy);
                        return TurnResult::turn_end;
                    }
                }
            }
            if (throw_item.id == ItemId::handful_of_snow)
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
            if (throw_item.id == ItemId::tomato)
            {
                if (is_in_fov({tlocx, tlocy}))
                {
                    txt(i18n::s.get("core.action.throw.tomato"),
                        Message::color{ColorIndex::blue});
                }
                return TurnResult::turn_end;
            }
            efp = 50 + sdata(111, thrower.index) * 10;
            if (throw_item.id == ItemId::bottle_of_sulfuric)
            {
                mef_add(tlocx, tlocy, 3, 19, rnd(15) + 5, efp, thrower.index);
                return TurnResult::turn_end;
            }
            if (throw_item.id == ItemId::molotov)
            {
                mef_add(tlocx, tlocy, 5, 24, rnd(15) + 25, efp, thrower.index);
                mapitem_fire(thrower, tlocx, tlocy);
                return TurnResult::turn_end;
            }
            mef_add(
                tlocx,
                tlocy,
                6,
                27,
                -1,
                efp,
                thrower.index,
                itemid2int(throw_item.id),
                static_cast<int>(throw_item.curse_state), // TODO
                throw_item.color);
            return TurnResult::turn_end;
        }
    }
    if (is_in_fov({tlocx, tlocy}))
    {
        txt(i18n::s.get("core.action.throw.shatters"));
        snd("core.crush2");
    }
    if (throw_item.id == ItemId::kitty_bank)
    {
        flt();
        itemcreate_extra_inv(54, tlocx, tlocy, throw_item.param1);
    }
    return TurnResult::turn_end;
}



TurnResult do_throw_command(Character& thrower, Item& throw_item)
{
    if (is_in_fov(thrower))
    {
        txt(i18n::s.get("core.action.throw.execute", thrower, throw_item));
    }
    if (dist(thrower.position.x, thrower.position.y, tlocx, tlocy) * 4 >
            rnd_capped(sdata(111, thrower.index) + 10) +
                sdata(111, thrower.index) / 4 ||
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
        {tlocx, tlocy}, thrower.position, throw_item.image, throw_item.color)
        .play();

    if (throw_item.id == ItemId::monster_ball)
    {
        if (const auto slot = inv_get_free_slot(-1))
        {
            item_copy(throw_item, *slot);
            slot->position.x = tlocx;
            slot->position.y = tlocy;
            slot->set_number(1);
            throw_item.modify_number(-1);
            return do_throw_command_internal(thrower, *slot);
        }
        else
        {
            throw_item.modify_number(-1);
            return do_throw_command_internal(thrower, throw_item);
        }
    }
    else
    {
        throw_item.modify_number(-1);
        return do_throw_command_internal(thrower, throw_item);
    }
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
    txt(i18n::s.get("core.action.close.execute", cdata.player()));
    return TurnResult::turn_end;
}



TurnResult do_change_ammo_command()
{
    optional_ref<Item> ammo_opt;
    for (int cnt = 0; cnt < 30; ++cnt)
    {
        body = 100 + cnt;
        if (cdata.player().body_parts[cnt] % 10000 == 0)
        {
            continue;
        }
        if (cdata.player().body_parts[cnt] / 10000 == 11)
        {
            ammo_opt = inv[cdata.player().body_parts[cnt] % 10000 - 1];
            break;
        }
    }

    if (!ammo_opt)
    {
        txt(i18n::s.get("core.action.ammo.need_to_equip"));
        return TurnResult::pc_turn_user_error;
    }
    auto& ammo = *ammo_opt;

    listmax = 0;
    cs = -1;
    for (int cnt = 0; cnt < 15; ++cnt)
    {
        if (ammo.enchantments[cnt].id == 0)
        {
            break;
        }
        enc = ammo.enchantments[cnt].id;
        i = enc / 10000;
        if (i != 0)
        {
            enc = enc % 10000;
            if (i == 9)
            {
                if (ammo.count == cnt)
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
        ammo.count = -1;
        txt(i18n::s.get("core.action.ammo.is_not_capable", ammo));
        return TurnResult::pc_turn_user_error;
    }
    snd("core.ammo");
    ++cs;
    if (cs >= listmax)
    {
        ammo.count = -1;
    }
    else
    {
        ammo.count = list(0, cs);
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
            i(0) = ammo.enchantments[p].power % 1000;
            i(1) = ammo.enchantments[p].power / 1000;
            s(0) = ammoname(ammo.enchantments[p].id % 10000);
            s(1) = ""s + i + u8"/"s + i(1);
        }
        s = s + u8":"s + s(1);
        if (ammo.count == cnt - 1)
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



TurnResult do_offer_command(Item& offering)
{
    if (cdata.player().god_id == core_god::eyth)
    {
        txt(i18n::s.get("core.action.offer.do_not_believe"));
        return TurnResult::turn_end;
    }
    rowact_item(offering);
    item_separate(offering);
    txt(i18n::s.get(
        "core.action.offer.execute",
        offering,
        god_name(cdata.player().god_id)));
    snd("core.offer2");
    BrightAuraAnimation(
        cdata.player().position, BrightAuraAnimation::Type::offering)
        .play();

    const auto altar_opt = item_find(60002);
    if (!altar_opt)
    {
        return TurnResult::turn_end;
    }
    auto& altar = *altar_opt;

    if (offering.id == ItemId::corpse)
    {
        i = clamp(offering.weight / 200, 1, 50);
        if (offering.param3 < 0)
        {
            i = 1;
        }
    }
    else
    {
        i = 25;
    }

    if (core_god::int2godid(altar.param1) != cdata.player().god_id)
    {
        f = 0;
        if (altar.param1 == 0)
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
                god_name(altar.param1)));
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
            MiracleAnimation(MiracleAnimation::Mode::target_one, cdata.player())
                .play();
            snd("core.pray2");
            if (altar.param1 != 0)
            {
                txt(i18n::s.get("core.action.offer.take_over.shadow"));
            }
            txt(i18n::s.get(
                    "core.action.offer.take_over.succeed",
                    god_name(cdata.player().god_id),
                    altar),
                Message::color{ColorIndex::orange});
            txtgod(cdata.player().god_id, 2);
            altar.param1 = core_god::godid2int(cdata.player().god_id);
        }
        else
        {
            txt(i18n::s.get(
                "core.action.offer.take_over.fail", god_name(altar.param1)));
            txtgod(core_god::int2godid(altar.param1), 3);
            god_fail_to_take_over_penalty();
        }
    }
    else
    {
        if (i >= 15)
        {
            txt(i18n::s.get("core.action.offer.result.best", offering),
                Message::color{ColorIndex::green});
            txtgod(cdata.player().god_id, 4);
        }
        else if (i >= 10)
        {
            txt(i18n::s.get("core.action.offer.result.good", offering),
                Message::color{ColorIndex::green});
        }
        else if (i >= 5)
        {
            txt(i18n::s.get("core.action.offer.result.okay", offering),
                Message::color{ColorIndex::green});
        }
        else if (i >= 1)
        {
            txt(i18n::s.get("core.action.offer.result.poor", offering),
                Message::color{ColorIndex::green});
        }
        god_modify_piety(i);
        cdata.player().praying_point += i * 7;
    }
    offering.modify_number(-offering.number());
    return TurnResult::turn_end;
}



TurnResult do_look_command()
{
    std::string action;
    page = 0;
    pagesize = 16;
    cs_bk = -1;
    build_target_list(cdata.player());
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
                        cdata.player().position.x,
                        cdata.player().position.y,
                        cdata[list(0, p)].position.x,
                        cdata[list(0, p)].position.y);
                    dx = (tlocx - scx) * inf_tiles + inf_screenx;
                    dy = (tlocy - scy) * inf_tiles + inf_screeny;
                    if (maxroute != 0)
                    {
                        dx = cdata.player().position.x;
                        dy = cdata.player().position.y;
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



TurnResult do_dip_command(Item& mix_item, Item& mix_target)
{
    if (mix_item.id == ItemId::bait)
    {
        item_separate(mix_target);
        mix_item.modify_number(-1);
        snd("core.equip1");
        txt(i18n::s.get(
            "core.action.dip.result.bait_attachment", mix_target, mix_item));
        if (mix_target.param4 == mix_item.param1)
        {
            mix_target.count += rnd(10) + 15;
        }
        else
        {
            mix_target.count = rnd(10) + 15;
            mix_target.param4 = mix_item.param1;
        }
        return TurnResult::turn_end;
    }
    snd("core.drink1");
    if (the_item_db[itemid2int(mix_item.id)]->category == ItemCategory::potion)
    {
        if (the_item_db[itemid2int(mix_target.id)]->subcategory == 60001)
        {
            item_separate(mix_target);
            mix_item.modify_number(-1);
            if (mix_item.id != ItemId::empty_bottle)
            {
                txt(i18n::s.get(
                    "core.action.dip.execute", mix_target, mix_item));
                if (mix_target.id == ItemId::holy_well)
                {
                    txt(i18n::s.get(
                        "core.action.dip.result.holy_well_polluted"));
                    return TurnResult::turn_end;
                }
                if (mix_target.param3 >= 20)
                {
                    txt(i18n::s.get(
                        "core.action.dip.result.well_dry", mix_target));
                    return TurnResult::turn_end;
                }
                txt(i18n::s.get(
                    "core.action.dip.result.well_refilled", mix_target));
                if (mix_item.id == ItemId::handful_of_snow)
                {
                    txt(i18n::s.get("core.action.dip.result.snow_melts.dip"));
                }
                else
                {
                    mix_target.param1 += rnd(3);
                }
                return TurnResult::turn_end;
            }
            else
            {
                if (mix_target.param1 < -5 || mix_target.param3 >= 20 ||
                    (mix_target.id == ItemId::holy_well &&
                     game_data.holy_well_count <= 0))
                {
                    txt(i18n::s.get(
                        "core.action.dip.result.natural_potion_dry",
                        mix_target));
                    txt(i18n::s.get(
                        "core.action.dip.result.natural_potion_drop"));
                    return TurnResult::turn_end;
                }
                if (!inv_get_free_slot(0))
                {
                    txt(i18n::s.get("core.ui.inv.common.inventory_is_full"));
                    return TurnResult::turn_end;
                }
                optional_ref<Item> natural_potion;
                if (mix_target.id == ItemId::holy_well)
                {
                    --game_data.holy_well_count;
                    flt();
                    if ((natural_potion = itemcreate_player_inv(516, 0)))
                    {
                        natural_potion->curse_state = CurseState::blessed;
                    }
                }
                else
                {
                    mix_target.param1 -= 3;
                    flt(20);
                    flttypemajor = 52000;
                    natural_potion = itemcreate_player_inv(0, 0);
                }
                if (natural_potion)
                {
                    txt(i18n::s.get("core.action.dip.result.natural_potion"));
                    txt(i18n::s.get(
                        "core.action.dip.you_get", *natural_potion));
                    item_stack(0, *natural_potion, true);
                }
                return TurnResult::turn_end;
            }
        }
    }
    if (mix_item.id == ItemId::poison)
    {
        if (the_item_db[itemid2int(mix_target.id)]->category ==
            ItemCategory::food)
        {
            mix_item.modify_number(-1);
            item_separate(mix_target);
            txt(i18n::s.get(
                    "core.action.dip.result.love_food.made",
                    mix_target,
                    mix_item) +
                i18n::s.get("core.action.dip.result.love_food.grin"));
            if (is_cursed(mix_item.curse_state))
            {
                dipcursed(mix_target);
            }
            mix_target.is_poisoned() = true;
            return TurnResult::turn_end;
        }
    }
    if (mix_item.id == ItemId::love_potion)
    {
        if (the_item_db[itemid2int(mix_target.id)]->category ==
            ItemCategory::food)
        {
            mix_item.modify_number(-1);
            item_separate(mix_target);
            txt(i18n::s.get(
                    "core.action.dip.result.love_food.made",
                    mix_target,
                    mix_item) +
                i18n::s.get("core.action.dip.result.love_food.guilty"));
            if (is_cursed(mix_item.curse_state))
            {
                dipcursed(mix_target);
            }
            mix_target.is_aphrodisiac() = true;
            return TurnResult::turn_end;
        }
    }
    if (mix_item.id == ItemId::bottle_of_dye)
    {
        if (mix_item.curse_state == CurseState::blessed)
        {
            in = mix_item.number();
        }
        else
        {
            in = 1;
            item_separate(mix_target);
        }
        mix_item.modify_number(-1);
        mix_target.color = mix_item.color;
        txt(i18n::s.get("core.action.dip.result.dyeing", mix_target));
        if (inv_getowner(mix_target) == -1)
        {
            cell_refresh(mix_target.position.x, mix_target.position.y);
        }
        if (mix_target.body_part != 0)
        {
            create_pcpic(cdata.player());
        }
        return TurnResult::turn_end;
    }
    if (mix_item.id == ItemId::acidproof_liquid)
    {
        if (mix_item.curse_state == CurseState::blessed)
        {
            in = mix_item.number();
        }
        else
        {
            in = 1;
            item_separate(mix_target);
        }
        txt(i18n::s.get("core.action.dip.result.put_on", mix_target, mix_item));
        if (is_cursed(mix_item.curse_state))
        {
            dipcursed(mix_target);
        }
        else
        {
            mix_target.is_acidproof() = true;
            txt(i18n::s.get(
                "core.action.dip.result.gains_acidproof", mix_target));
        }
        mix_item.modify_number(-1);
        return TurnResult::turn_end;
    }
    if (mix_item.id == ItemId::fireproof_liquid)
    {
        if (mix_item.curse_state == CurseState::blessed)
        {
            in = mix_item.number();
        }
        else
        {
            in = 1;
            item_separate(mix_target);
        }
        txt(i18n::s.get("core.action.dip.result.put_on", mix_target, mix_item));
        if (is_cursed(mix_item.curse_state))
        {
            dipcursed(mix_target);
        }
        else if (mix_target.id == ItemId::fireproof_blanket)
        {
            txt(i18n::s.get("core.action.dip.result.good_idea_but"));
        }
        else
        {
            mix_target.is_fireproof() = true;
            txt(i18n::s.get(
                "core.action.dip.result.gains_fireproof", mix_target));
        }
        mix_item.modify_number(-1);
        return TurnResult::turn_end;
    }
    if (mix_item.id == ItemId::bottle_of_water)
    {
        mix_item.modify_number(-1);
        if (mix_item.curse_state == CurseState::blessed)
        {
            txt(i18n::s.get(
                    "core.action.dip.result.becomes_blessed", mix_target),
                Message::color{ColorIndex::green});
            mix_target.curse_state = CurseState::blessed;
            chara_refresh(cdata.player());
            return TurnResult::turn_end;
        }
        if (is_cursed(mix_item.curse_state))
        {
            txt(i18n::s.get(
                    "core.action.dip.result.becomes_cursed", mix_target),
                Message::color{ColorIndex::purple});
            mix_target.curse_state = CurseState::cursed;
            chara_refresh(cdata.player());
            return TurnResult::turn_end;
        }
    }
    txt(i18n::s.get("core.common.nothing_happens"));
    return TurnResult::turn_end;
}



TurnResult do_use_command(Item& use_item)
{
    screenupdate = -1;
    update_screen();
    tlocx = cdata.player().position.x;
    tlocy = cdata.player().position.y;
    auto item_data = the_item_db[itemid2int(use_item.id)];

    if (item_data->on_use_callback)
    {
        bool success = lua::call_with_result(
            *item_data->on_use_callback,
            false,
            lua::handle(use_item),
            lua::handle(cdata.player()));

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

    if (use_item.has_cooldown_time())
    {
        if (game_data.date.hours() < use_item.count)
        {
            txt(i18n::s.get(
                "core.action.use.useable_again_at", cnvdate(use_item.count)));
            update_screen();
            return TurnResult::pc_turn_user_error;
        }
        item_separate(use_item);
        use_item.count = game_data.date.hours() + use_item.param3;
    }
    if (use_item.has_charge())
    {
        if (use_item.count <= 0)
        {
            txt(i18n::s.get("core.action.use.out_of_charge"));
            update_screen();
            return TurnResult::pc_turn_user_error;
        }
        item_separate(use_item);
        --use_item.count;
    }
    if (item_data->subcategory == 58500)
    {
        return do_plant(use_item);
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
        activity_others(cdata.player(), use_item);
        return TurnResult::turn_end;
    }
    if (use_item.id == ItemId::red_treasure_machine ||
        use_item.id == ItemId::blue_treasure_machine)
    {
        return do_gatcha(use_item);
    }
    if (use_item.id == ItemId::pachisuro_machine ||
        use_item.id == ItemId::casino_table ||
        use_item.id == ItemId::slot_machine ||
        use_item.id == ItemId::darts_board)
    {
        casino_dealer();
        return TurnResult::turn_end;
    }
    if (use_item.function == 1 || use_item.function == 2 ||
        use_item.function == 3 || use_item.function == 4)
    {
        prodtype = use_item.function;
        snd("core.pop2");
        invctrl = 0;
        crafting_menu();
        return TurnResult::turn_end;
    }

    if (use_item.is_alive())
    {
        if (use_item.param2 < calcexpalive(use_item.param1))
        {
            txt(i18n::s.get("core.action.use.living.needs_more_blood"));
        }
        else
        {
            Message::instance().linebreak();
            txt(i18n::s.get("core.action.use.living.ready_to_grow", use_item));
            randomize(use_item.subname);
            if (use_item.param1 >= 4 + rnd(12))
            {
                txt(i18n::s.get("core.action.use.living.weird"));
            }
            txt(i18n::s.get("core.action.use.living.it"));
            reftype = (int)item_data->category;
            listmax = 0;

            Prompt prompt;
            for (int cnt = 0; cnt < 3; ++cnt)
            {
                randomize(use_item.subname + use_item.param1 * 10 + cnt);
                if (enchantment_add(
                        use_item,
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
                txt(i18n::s.get("core.action.use.living.displeased", use_item));
            }
            else
            {
                if (list(0, rtval) == -1)
                {
                    ++use_item.enhancement;
                }
                else
                {
                    enchantment_add(
                        use_item, list(0, rtval), list(1, rtval), 0, 1);
                }
                txt(i18n::s.get("core.action.use.living.pleased", use_item),
                    Message::color{ColorIndex::green});
                randomize(use_item.subname);
                if (use_item.param1 >= 4 + rnd(12))
                {
                    txt(i18n::s.get(
                        "core.action.use.living.becoming_a_threat"));
                    if (!enchantment_add(use_item, 45, 50))
                    {
                        use_item.enchantments[14].id = 0;
                        txt(i18n::s.get(
                            "core.action.use.living.removes_enchantment",
                            use_item));
                    }
                }
                use_item.param2 = 0;
                ++use_item.param1;
            }
            randomize();
        }
        chara_refresh(cdata.player());
        update_screen();
        return TurnResult::pc_turn_user_error;
    }

    switch (use_item.function)
    {
    case 24:
        x = cdata.player().position.x;
        y = cdata.player().position.y;
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
        use_item.modify_number(-1);
        cell_featset(x, y, 0, 14, 7, cdata.player().index);
        txt(i18n::s.get("core.action.use.mine.you_set_up"));
        snd("core.build1");
        break;
    case 44:
        if (inv_getowner(use_item) != -1)
        {
            txt(i18n::s.get("core.action.use.chair.needs_place_on_ground"));
            update_screen();
            return TurnResult::pc_turn_user_error;
        }
        {
            txt(i18n::s.get("core.action.use.chair.you_sit_on", use_item));

            Prompt prompt("core.action.use.chair.choices");
            prompt.append("relax", 0);
            if (use_item.param1 != 1)
            {
                prompt.append("my_chair", 1);
            }
            if (use_item.param1 != 2)
            {
                prompt.append("guest_chair", 2);
            }
            if (use_item.param1 != 0)
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
            txt(i18n::s.get("core.action.use.chair.my_chair", use_item));
            use_item.param1 = 1;
            break;
        }
        if (rtval == 2)
        {
            txt(i18n::s.get("core.action.use.chair.guest_chair", use_item));
            use_item.param1 = 2;
            break;
        }
        if (rtval == 3)
        {
            txt(i18n::s.get("core.action.use.chair.free_chair", use_item));
            use_item.param1 = 0;
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
                const auto chara_index =
                    cell_data.at(x, y).chara_index_plus_one - 1;
                if (chara_index != -1 && chara_index < 16)
                {
                    chara = chara_index;
                }
            }
        }
        if (chara != -1)
        {
            screenupdate = -1;
            update_screen();
            change_appearance_equipment(cdata[chara]);
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
        magic(cdata.player(), cdata.player(), use_item);
        break;
    case 16:
        efid = 185;
        magic(cdata.player(), cdata.player(), use_item);
        break;
    case 17:
        efid = 183;
        magic(cdata.player(), cdata.player(), use_item);
        break;
    case 14:
        if (cdata.player().index == 0)
        {
            if (use_item.number() < 5)
            {
                txt(i18n::s.get("core.action.use.snow.need_more"));
                update_screen();
                return TurnResult::pc_turn_user_error;
            }
            use_item.modify_number(-5);
        }
        flt();
        itemcreate_extra_inv(541, cdata.player().position, 0);
        if (is_in_fov(cdata.player()))
        {
            snd("core.snow");
            txt(i18n::s.get(
                "core.action.use.snow.make_snowman", cdata.player()));
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
        chara_refresh(cdata.player());
        break;
    case 9: {
        if (read_textbook(cdata.player(), use_item))
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
    case 5: {
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
        const auto target_chara_index =
            cell_data.at(x, y).chara_index_plus_one - 1;
        if (target_chara_index == 0)
        {
            txt(i18n::s.get("core.action.use.stethoscope.self"));
            game_data.chara_last_attacked_by_player = 0;
            return TurnResult::turn_end;
        }
        if (target_chara_index > 0 && target_chara_index < 16)
        {
            if (cdata[target_chara_index].state() == Character::State::alive)
            {
                game_data.chara_last_attacked_by_player = 0;
                if (cdata[target_chara_index].has_been_used_stethoscope() == 1)
                {
                    cdata[target_chara_index].has_been_used_stethoscope() =
                        false;
                    txt(i18n::s.get(
                        "core.action.use.stethoscope.other.stop",
                        cdata[target_chara_index]));
                    return TurnResult::turn_end;
                }
                txt(i18n::s.get(
                    "core.action.use.stethoscope.other.start.text",
                    cdata[target_chara_index]));
                if (cdata[target_chara_index].sex == 1)
                {
                    txt(i18n::s.get(
                        "core.action.use.stethoscope.other.start.female.text",
                        cdata[target_chara_index]));
                    txt(i18n::s.get(
                            "core.action.use.stethoscope.other.start.female.dialog",
                            cdata[target_chara_index]),
                        Message::color{ColorIndex::blue});
                }
                cdata[target_chara_index].has_been_used_stethoscope() = true;
                return TurnResult::turn_end;
            }
        }
        txt(i18n::s.get("core.common.it_is_impossible"));
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    case 23: {
        txt(i18n::s.get("core.action.use.leash.prompt"));
        update_screen();
        int stat = ask_direction();
        f = 0;
        if (stat != 0)
        {
            if (cell_data.at(x, y).chara_index_plus_one > 0)
            {
                const auto target_chara_index =
                    cell_data.at(x, y).chara_index_plus_one - 1;
                if (target_chara_index == 0)
                {
                    txt(i18n::s.get("core.action.use.leash.self"));
                }
                else if (cdata[target_chara_index].is_leashed() == 0)
                {
                    if (target_chara_index >= 16)
                    {
                        if (rnd(5) == 0)
                        {
                            txt(i18n::s.get(
                                "core.action.use.leash.other.start.resists",
                                cdata[target_chara_index]));
                            use_item.modify_number(-1);
                            cell_refresh(
                                use_item.position.x, use_item.position.y);
                            refresh_burden_state();
                            break;
                        }
                    }
                    cdata[target_chara_index].is_leashed() = true;
                    txt(i18n::s.get(
                        "core.action.use.leash.other.start.text",
                        cdata[target_chara_index]));
                    txt(i18n::s.get(
                            "core.action.use.leash.other.start.dialog",
                            cdata[target_chara_index]),
                        Message::color{ColorIndex::cyan});
                }
                else
                {
                    cdata[target_chara_index].is_leashed() = false;
                    txt(i18n::s.get(
                        "core.action.use.leash.other.stop.text",
                        cdata[target_chara_index]));
                    txt(i18n::s.get(
                            "core.action.use.leash.other.stop.dialog",
                            cdata[target_chara_index]),
                        Message::color{ColorIndex::cyan});
                }
                animeload(8, cdata[target_chara_index]);
                f = 1;
            }
        }
        if (f == 0)
        {
            txt(i18n::s.get("core.common.it_is_impossible"));
        }
        break;
    }
    case 45: {
        if (game_data.current_map == mdata_t::MapId::show_house)
        {
            txt(i18n::s.get("core.action.use.sandbag.cannot_use_here"));
            update_screen();
            return TurnResult::pc_turn_user_error;
        }
        txt(i18n::s.get("core.action.use.sandbag.prompt"));
        update_screen();
        int stat = ask_direction();
        f = 0;
        if (stat != 0)
        {
            if (cell_data.at(x, y).chara_index_plus_one > 0)
            {
                const auto target_chara_index =
                    cell_data.at(x, y).chara_index_plus_one - 1;
                if (cdata[target_chara_index].hp >=
                    cdata[target_chara_index].max_hp / 5)
                {
                    txt(i18n::s.get("core.action.use.sandbag.not_weak_enough"));
                    return TurnResult::pc_turn_user_error;
                }
                if (target_chara_index != 0)
                {
                    if (target_chara_index < 16)
                    {
                        txt(i18n::s.get("core.action.use.sandbag.ally"));
                        return TurnResult::pc_turn_user_error;
                    }
                }
                if (cdata[target_chara_index].is_hung_on_sand_bag())
                {
                    txt(i18n::s.get("core.action.use.sandbag.already"));
                    return TurnResult::pc_turn_user_error;
                }
                if (target_chara_index == 0)
                {
                    txt(i18n::s.get("core.action.use.sandbag.self"));
                }
                else
                {
                    snd("core.build1");
                    cdata[target_chara_index].is_hung_on_sand_bag() = true;
                    txt(i18n::s.get(
                        "core.action.use.sandbag.start",
                        cdata[target_chara_index]));
                    txt(i18n::s.get(
                        "core.action.use.leash.other.start.dialog",
                        cdata[target_chara_index]));
                    animeload(8, cdata[target_chara_index]);
                    use_item.modify_number(-1);
                    cell_refresh(use_item.position.x, use_item.position.y);
                    refresh_burden_state();
                }
                f = 1;
            }
        }
        if (f == 0)
        {
            txt(i18n::s.get("core.common.it_is_impossible"));
        }
        break;
    }
    case 6: {
        txt(i18n::s.get("core.action.use.music_disc.play", use_item));
        auto music = use_item.param1 + 50 + 1;
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
        if (use_item.own_state != 3)
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
            activity_others(cdata.player(), use_item);
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
        activity_others(cdata.player(), use_item);
        break;
    case 11:
        if (moneybox(use_item.param2) > cdata.player().gold)
        {
            txt(i18n::s.get("core.action.use.money_box.not_enough_gold"));
            update_screen();
            return TurnResult::pc_turn_user_error;
        }
        if (use_item.param1 >= 1000000000)
        {
            txt(i18n::s.get("core.action.use.money_box.full"));
            update_screen();
            return TurnResult::pc_turn_user_error;
        }
        item_separate(use_item);
        snd("core.paygold1");
        cdata.player().gold -= moneybox(use_item.param2);
        use_item.param1 += moneybox(use_item.param2);
        use_item.weight += 100;
        break;
    case 20:
        efid = 458;
        efp = 400;
        magic(cdata.player(), cdata.player());
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
        use_item.modify_number(-1);
        cell_refresh(use_item.position.x, use_item.position.y);
        txt(i18n::s.get("core.action.use.rune.use"));
        // Showroom is not supported now.
        break;
    case 49:
        txt(i18n::s.get("core.action.use.hammer.use", use_item));
        snd("core.build1");
        efid = 49;
        efp = 100;
        magic(cdata.player(), cdata.player(), use_item);
        break;
    case 21:
        txt(i18n::s.get("core.action.use.hammer.use", use_item));
        snd("core.build1");
        use_item.modify_number(-1);
        fixmaterial = use_item.material;
        efid = 21;
        efp = 500;
        magic(cdata.player(), cdata.player());
        break;
    case 25:
        txt(i18n::s.get("core.action.use.unicorn_horn.use", use_item));
        use_item.modify_number(-1);
        efid = 637;
        efp = 500;
        magic(cdata.player(), cdata.player());
        break;
    case 26:
        txt(i18n::s.get("core.action.use.statue.activate", use_item));
        game_data.diastrophism_flag = 1;
        snd("core.pray1");
        txt(i18n::s.get("core.action.use.statue.opatos"),
            Message::color{ColorIndex::orange});
        break;
    case 34:
        txt(i18n::s.get("core.action.use.statue.activate", use_item));
        txt(i18n::s.get("core.action.use.statue.jure"),
            Message::color{ColorIndex::orange});
        efid = 637;
        efp = 5000;
        magic(cdata.player(), cdata.player());
        break;
    case 43:
        txt(i18n::s.get("core.action.use.statue.activate", use_item));
        snd("core.pray1");
        txt(i18n::s.get("core.action.use.statue.ehekatl"),
            Message::color{ColorIndex::orange});
        buff_add(cdata.player(), "core.luck", 77, 2500);
        break;
    case 27:
        txt(i18n::s.get("core.action.use.statue.activate", use_item));
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
        use_item.modify_number(-1);
        cell_refresh(use_item.position.x, use_item.position.y);
        txt(i18n::s.get("core.action.use.nuke.set_up"));
        snd("core.build1");
        mef_add(
            cdata.player().position.x,
            cdata.player().position.y,
            7,
            632,
            10,
            100,
            cdata.player().index);
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
        trait(use_item.param1) = 1;
        if (use_item.param1 == 169)
        {
            trait(162) = 0;
        }
        if (use_item.param1 == 162)
        {
            trait(169) = 0;
        }
        use_item.modify_number(-1);
        txt(i18n::s.get("core.action.use.secret_treasure.use"));
        animeload(10, cdata.player());
        chara_refresh(cdata.player());
        break;
    case 30:
        txt(i18n::s.get("core.action.use.statue.activate", use_item));
        efid = use_item.param1;
        efp = use_item.param2;
        efstatus = CurseState::none;
        magic(cdata.player(), cdata.player());
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
        use_item.modify_number(-1);
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
        if (use_item.subname == 0)
        {
            txt(i18n::s.get("core.action.use.monster_ball.empty"));
            break;
        }
        if (chara_get_free_slot_ally() == 0)
        {
            txt(i18n::s.get("core.action.use.monster_ball.party_is_full"));
            break;
        }
        txt(i18n::s.get("core.action.use.monster_ball.use", use_item));
        use_item.modify_number(-1);
        flt();
        novoidlv = 1;
        chara_create(56, use_item.subname, -3, 0);
        new_ally_joins(cdata.tmp());
        break;
    case 31:
        x = cdata.player().position.x;
        y = cdata.player().position.y;
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
        animeload(8, cdata.player());
        break;
    case 32: {
        const auto turn_result = use_gene_machine();
        if (turn_result)
        {
            return *turn_result;
        }
        break;
    }
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
        make_sound(
            cdata.player().position.x,
            cdata.player().position.y,
            10,
            1,
            1,
            cdata.player().index);
        break;
    case 37:
        tcgdeck();
        draw_prepare_map_chips();
        update_entire_screen();
        Message::instance().linebreak();
        txt(i18n::s.get("core.action.use.deck.put_away"));
        break;
    case 38:
        if (!inv_find(ItemId::deck, 0))
        {
            txt(i18n::s.get("core.action.use.deck.no_deck"));
            update_screen();
            return TurnResult::pc_turn_user_error;
        }
        snd("core.card1");
        use_item.modify_number(-1);
        cell_refresh(use_item.position.x, use_item.position.y);
        txt(i18n::s.get("core.action.use.deck.add_card", use_item));
        ++card(0, use_item.subname);
        break;
    }

    refresh_burden_state();
    return TurnResult::turn_end;
}



TurnResult do_open_command(Item& box, bool play_sound)
{
    const auto snd_ = [play_sound](data::InstanceId id) {
        if (play_sound)
        {
            snd(id);
        }
    };

    int refweight = 0;
    if (box.id == ItemId::shopkeepers_trunk)
    {
        modify_karma(cdata.player(), -10);
        invctrl(0) = 22;
        invctrl(1) = 0;
        invfile = box.param1;
        snd_("core.chest1");
        shop_sell_item(none);
        screenupdate = -1;
        update_screen();
        return TurnResult::turn_end;
    }
    if (box.id == ItemId::masters_delivery_chest)
    {
        invctrl(0) = 24;
        invctrl(1) = 0;
        snd_("core.inv");
        MenuResult mr = ctrl_inventory().menu_result;
        assert(mr.turn_result != TurnResult::none);
        return mr.turn_result;
    }
    if (box.id == ItemId::tax_masters_tax_box)
    {
        invctrl(0) = 24;
        invctrl(1) = 2;
        snd_("core.inv");
        MenuResult mr = ctrl_inventory().menu_result;
        assert(mr.turn_result != TurnResult::none);
        return mr.turn_result;
    }
    if (box.id == ItemId::giants_shackle)
    {
        snd_("core.locked1");
        txt(i18n::s.get("core.action.open.shackle.text"));
        if (game_data.current_map == mdata_t::MapId::noyel &&
            game_data.current_dungeon_level == 1 &&
            game_data.released_fire_giant == 0)
        {
            if (cdata[game_data.fire_giant].state() == Character::State::alive)
            {
                if (const auto moyer = chara_find("core.moyer"))
                {
                    if (moyer->state() == Character::State::alive)
                    {
                        txt(i18n::s.get("core.action.open.shackle.dialog"),
                            Message::color{ColorIndex::cyan});
                        cdata[game_data.fire_giant].enemy_id = moyer->index;
                        cdata[game_data.fire_giant].hate = 1000;
                    }
                }
                game_data.released_fire_giant = 1;
                net_send_news("fire");
            }
        }
        return TurnResult::turn_end;
    }
    if (box.count != 0)
    {
        invfile = box.count;
        invcontainer(1) = itemid2int(box.id);
        if (box.id == ItemId::cooler_box)
        {
            refweight = -1;
        }
        else
        {
            refweight = 0;
        }
        if (box.count == 3 || box.count == 4 || box.count == 6)
        {
            if (game_data.current_map != mdata_t::MapId::your_home)
            {
                txt(i18n::s.get("core.action.open.only_in_home"));
                update_screen();
                return TurnResult::pc_turn_user_error;
            }
        }
        if (box.count == 5)
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
            box.weight = refweight;
            refresh_burden_state();
        }
        update_screen();
        mode = 0;
        return TurnResult::turn_end;
    }
    item_separate(box);
    if (box.param1 != 0)
    {
        if (box.param2 != 0)
        {
            int stat = unlock_box(box.param2);
            if (stat == 0)
            {
                screenupdate = -1;
                update_screen();
                return TurnResult::turn_end;
            }
        }
    }
    if (box.param1 == 0)
    {
        txt(i18n::s.get("core.action.open.empty"));
    }
    else
    {
        if (box.id == ItemId::new_years_gift)
        {
            open_new_year_gift(box);
        }
        else
        {
            open_box(box);
        }
        item_stack(cdata.player().index, box);
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
            return step_into_gate(*moon_gate);
        }
    }
    cell_featread(cdata.player().position.x, cdata.player().position.y);
    movelevelbystairs = 0;
    if (val0 == 1)
    {
        if (mapitemfind(cdata.player().position, ItemId::kotatsu))
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
            if (mapitemfind(cdata.player().position, ItemId::downstairs))
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
            if (mapitemfind(cdata.player().position, ItemId::upstairs))
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
                cdata.player().position.x,
                cdata.player().position.y,
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
                    cdata.player(),
                    cdata.player().max_hp *
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
    if (cdata.player().dimmed != 0)
    {
        if (cdata.player().dimmed + 10 > rnd(60))
        {
            f = 1;
        }
    }
    if (cdata.player().drunk != 0)
    {
        if (rnd(5) == 0)
        {
            txt(i18n::s.get("core.action.move.drunk"),
                Message::color{ColorIndex::cyan});
            f = 1;
        }
    }
    if (cdata.player().confused != 0 || f == 1)
    {
        cdata.player().next_position.x = cdata.player().position.x + rnd(3) - 1;
        cdata.player().next_position.y = cdata.player().position.y + rnd(3) - 1;
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
    cell_check(cdata.player().next_position.x, cdata.player().next_position.y);
    if (cdata.player().inventory_weight_type >= 4)
    {
        txt(i18n::s.get("core.action.move.carry_too_much"),
            Message::only_once{true});
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    if (cellchara != -1 && cellchara != 0)
    {
        return _bump_into_character(cdata[cellchara]);
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
        return _pre_proc_movement_event(cdata.player());
    }
    if (map_data.type == mdata_t::MapType::shelter ||
        (game_data.current_dungeon_level == 1 &&
         map_data.type != mdata_t::MapType::world_map &&
         !mdata_t::is_nefia(map_data.type)))
    {
        if (cdata.player().next_position.x < 0 ||
            cdata.player().next_position.x > map_data.width - 1 ||
            cdata.player().next_position.y < 0 ||
            cdata.player().next_position.y > map_data.height - 1)
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
            return proc_movement_event(cdata.player());
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



TurnResult do_read_command(Character& reader, Item& item)
{
    if (item.id == ItemId::recipe)
    {
        if (item.subname == 0)
        {
            txt(i18n::s.get("core.action.read.recipe.info"));
            return TurnResult::turn_end;
        }
    }
    efid = 0;
    item_db_on_read(reader, item, itemid2int(item.id));
    if (efid == 1115)
    {
        return build_new_building(item);
    }
    return TurnResult::turn_end;
}



TurnResult do_eat_command(Character& eater, Item& food)
{
    if (eater.index == 0)
    {
        if (!cargocheck(food))
        {
            update_screen();
            return TurnResult::pc_turn_user_error;
        }
        if (itemusingfind(food) > 0)
        {
            txt(i18n::s.get("core.action.someone_else_is_using"));
            return TurnResult::pc_turn_user_error;
        }
    }
    else if (itemusingfind(food) != -1)
    {
        const auto eating_chara_index = itemusingfind(food);
        if (eating_chara_index != eater.index)
        {
            cdata[eating_chara_index].activity.finish();
            if (is_in_fov(eater))
            {
                txt(i18n::s.get(
                    "core.action.eat.snatches",
                    eater,
                    cdata[eating_chara_index]));
            }
        }
    }
    eater.emotion_icon = 116;
    activity_eating(eater, food);
    return TurnResult::turn_end;
}



TurnResult do_drink_command(Character& chara, Item& potion)
{
    item_db_on_drink(chara, potion, itemid2int(potion.id));
    return TurnResult::turn_end;
}



TurnResult do_zap_command(Item& rod)
{
    item_db_on_zap(rod, itemid2int(rod.id));
    int stat = do_zap(cdata.player(), rod);
    if (stat == 0)
    {
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    return TurnResult::turn_end;
}



TurnResult do_rest_command()
{
    do_rest(cdata.player());
    return TurnResult::turn_end;
}



TurnResult do_fire_command()
{
    int stat = find_enemy_target(cdata.player());
    if (stat == 0)
    {
        return TurnResult::pc_turn_user_error;
    }
    const auto target_chara_index = cdata.player().enemy_id;
    if (cdata[target_chara_index].relationship >= 0)
    {
        int stat = prompt_really_attack(cdata[target_chara_index]);
        if (stat == 0)
        {
            return TurnResult::pc_turn_user_error;
        }
    }
    const auto result = can_do_ranged_attack(cdata.player());
    if (result.type == -1)
    {
        txt(i18n::s.get("core.action.ranged.equip.need_weapon"),
            Message::only_once{true});
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    if (result.type == -2)
    {
        txt(i18n::s.get("core.action.ranged.equip.need_ammo"),
            Message::only_once{true});
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    if (result.type == -3)
    {
        txt(i18n::s.get("core.action.ranged.equip.wrong_ammo"),
            Message::only_once{true});
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    do_ranged_attack(
        cdata.player(), cdata[target_chara_index], result.weapon, result.ammo);
    return TurnResult::turn_end;
}



TurnResult do_get_command()
{
    const auto item_info = cell_itemoncell(cdata.player().position);
    const auto number = item_info.first;
    const auto item_index = item_info.second;

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

    if (number > 1)
    {
        invctrl = 3;
        snd("core.inv");
        MenuResult mr = ctrl_inventory().menu_result;
        assert(mr.turn_result != TurnResult::none);
        return mr.turn_result;
    }

    if ((inv[item_index].own_state > 0 && inv[item_index].own_state < 3) ||
        inv[item_index].own_state == 5)
    {
        snd("core.fail1");
        if (inv[item_index].own_state == 2)
        {
            txt(i18n::s.get("core.action.get.cannot_carry"),
                Message::only_once{true});
        }
        if (inv[item_index].own_state == 1 || inv[item_index].own_state == 5)
        {
            txt(i18n::s.get("core.action.get.not_owned"),
                Message::only_once{true});
        }
        update_screen();
        return TurnResult::pc_turn_user_error;
    }

    in = inv[item_index].number();
    int stat = pick_up_item(cdata.player().index, inv[item_index], none).type;
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
    int enemy_index = cdata.player().index;
    int stat = do_cast_magic(cdata.player(), enemy_index);
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
        MenuResult mr = ctrl_inventory().menu_result;
        assert(mr.turn_result != TurnResult::none);
        return mr.turn_result;
    }
    efid = game_data.skill_shortcuts.at(sc_);
    if (efid >= 300 && efid < 400)
    {
        return do_spact_command();
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
        return do_spact_command();
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
            txt(i18n::s.get(
                "core.action.exit.you_close_your_eyes", cdata.player()));
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



// TODO:
// This function must not modify @a enemy_id.
// See also:
// https://elonafoobar.github.io/bugfixes/#x-%E4%BA%8B%E5%89%8D%E3%81%AB%E5%AF%BE%E8%B1%A1%E3%82%92%E6%8C%87%E5%AE%9A%E3%81%99%E3%82%8B%E3%82%BF%E3%82%A4%E3%83%97%E3%81%AE%E9%AD%94%E6%B3%95%E3%82%92%E6%B7%B7%E4%B9%B1%E6%99%82%E3%81%AB%E4%BD%BF%E3%81%A3%E3%81%9F%E3%81%A8%E3%81%8D%E5%AF%BE%E8%B1%A1%E3%81%8C%E4%BD%BF%E7%94%A8%E8%80%85%E8%87%AA%E8%BA%AB%E3%81%AB%E3%81%AA%E3%81%A3%E3%81%A6%E3%81%97%E3%81%BE%E3%81%86%E5%95%8F%E9%A1%8C
int try_to_cast_spell(Character& caster, int& enemy_index)
{
    int r4 = 0;
    f = 1;
    enemy_index = caster.index;
    if (caster.blind != 0)
    {
        f = 0;
    }
    if (caster.confused != 0 || caster.dimmed != 0)
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
            r4 = sdata(16, caster.index);
        }
        else
        {
            r4 = sdata(
                the_ability_db[r3]->related_basic_attribute, caster.index);
        }
        if (rnd_capped(sdata(150, caster.index) * r4 * 4 + 250) <
            rnd_capped(r2 + 1))
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
        if (is_in_fov(caster))
        {
            txt(i18n::s.get("core.misc.fail_to_cast.mana_is_absorbed", caster));
        }
        if (caster.index == 0)
        {
            damage_mp(caster, caster.max_mp);
        }
        else
        {
            damage_mp(caster, caster.max_mp / 3);
        }
        return 0;
    }
    if (rnd(4) == 0)
    {
        if (is_in_fov(caster))
        {
            if (caster.confused != 0)
            {
                txt(i18n::s.get(
                    "core.misc.fail_to_cast.is_confused_more", caster));
            }
            else
            {
                txt(i18n::s.get("core.misc.fail_to_cast.too_difficult"));
            }
        }
        status_ailment_damage(caster, StatusAilment::confused, 100);
        return 0;
    }
    if (rnd(4) == 0)
    {
        if (is_in_fov(caster))
        {
            txt(i18n::s.get("core.misc.fail_to_cast.creatures_are_summoned"));
        }
        for (int cnt = 0, cnt_end = (2 + rnd(3)); cnt < cnt_end; ++cnt)
        {
            flt(calcobjlv(cdata.player().level * 3 / 2 + 3),
                calcfixlv(Quality::bad));
            if (const auto chara =
                    chara_create(-1, 0, caster.position.x, caster.position.y))
            {
                if (caster.relationship <= -3)
                {
                    chara->relationship = -1;
                    chara->original_relationship = -1;
                }
            }
        }
        return 0;
    }
    if (is_in_fov(caster))
    {
        txt(i18n::s.get("core.misc.fail_to_cast.dimension_door_opens", caster));
    }
    enemy_index = caster.index;
    efid = 408;
    magic(caster, caster);
    return 0;
}



int try_to_reveal(Character& chara)
{
    if (rnd_capped(sdata(159, chara.index) * 15 + 20 + sdata(13, chara.index)) >
        rnd_capped(game_data.current_dungeon_level * 8 + 60))
    {
        chara_gain_exp_detection(chara);
        return 1;
    }
    return 0;
}



int can_evade_trap(Character& chara)
{
    if (feat(2) == 7)
    {
        return 0;
    }
    if (chara.index < 16)
    {
        if (rnd_capped(refdiff + 1) <
            sdata(13, chara.index) + sdata(159, chara.index) * 4)
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



int try_to_disarm_trap(Character& chara)
{
    if (rnd_capped(sdata(175, chara.index) * 15 + 20 + sdata(12, chara.index)) >
        rnd_capped(game_data.current_dungeon_level * 12 + 100))
    {
        chara_gain_exp_disarm_trap(chara);
        return 1;
    }
    return 0;
}



bool try_to_perceive_npc(const Character& chara, const Character& enemy)
{
    constexpr int view_range = 8;

    if (enemy.position.x > chara.position.x - view_range &&
        enemy.position.x < chara.position.x + view_range)
    {
        if (enemy.position.y > chara.position.y - view_range &&
            enemy.position.y < chara.position.y + view_range)
        {
            if (chara.hate > 0)
            {
                return true;
            }
            const auto d = dist(
                enemy.position.x,
                enemy.position.y,
                chara.position.x,
                chara.position.y);
            const auto p = d * 150 + (sdata(157, enemy.index) * 100 + 150) + 1;
            if (rnd_capped(p) < rnd_capped(sdata(13, chara.index) * 60 + 150))
            {
                return true;
            }
        }
    }
    return false;
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



TurnResult do_spact_command()
{
    int enemy_index = cdata.player().index;
    int stat = do_spact(cdata.player(), enemy_index);
    if (stat == 0)
    {
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    return TurnResult::turn_end;
}



TurnResult try_interact_with_npc(Character& chara)
{
    if (chara.activity.turn != 0)
    {
        txt(i18n::s.get("core.action.npc.is_busy_now", chara));
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    menucycle = 1;
    invally = 1;
    invctrl = 10;
    snd("core.inv");
    MenuResult mr = ctrl_inventory(chara).menu_result;
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
            if (const auto item = itemcreate_extra_inv(
                    gatcha_ball_id, cdata.player().position, 0))
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



bool read_textbook(Character& doer, Item& textbook)
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
    activity_others(doer, textbook);
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



void do_rest(Character& chara)
{
    if (!chara.activity)
    {
        chara.activity.type = Activity::Type::sleep;
        chara.activity.turn = 50;
        txt(i18n::s.get("core.activity.rest.start"));
        update_screen();
        return;
    }
    if (chara.activity.turn > 0)
    {
        if (chara.activity.turn % 2 == 0)
        {
            heal_sp(chara, 1);
        }
        if (chara.activity.turn % 3 == 0)
        {
            heal_hp(chara, 1);
            heal_mp(chara, 1);
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
            chara.activity.item = -1;
            sleep_start(none);
            chara.activity.finish();
            return;
        }
    }
    txt(i18n::s.get("core.activity.rest.finish"));
    chara.activity.finish();
}



int decode_book(Character& reader, Item& book)
{
    if (!reader.activity)
    {
        if (book.id == ItemId::ancient_book)
        {
            if (book.param2 != 0)
            {
                txt(i18n::s.get("core.action.read.book.already_decoded"));
                return 0;
            }
        }
        if (reader.blind != 0)
        {
            if (is_in_fov(reader))
            {
                txt(i18n::s.get("core.action.read.cannot_see", reader));
            }
            return 0;
        }
        reader.activity.type = Activity::Type::read;
        if (book.id == ItemId::recipe)
        {
            p = 50;
        }
        else if (book.id == ItemId::ancient_book)
        {
            p = 50 + book.param1 * 50 + book.param1 * book.param1 * 20;
        }
        else
        {
            p = the_ability_db[efid]->difficulty;
        }
        reader.activity.turn = p / (2 + sdata(150, 0)) + 1;
        reader.activity.item = book.index;
        if (is_in_fov(reader))
        {
            txt(i18n::s.get("core.activity.read.start", reader, book));
        }
        item_separate(book);
        return 0;
    }
    if (reader.activity.turn > 0)
    {
        chara_gain_exp_literacy(cdata.player());
        if (book.id == ItemId::recipe)
        {
            return 0;
        }
        if (book.id == ItemId::ancient_book)
        {
            r2 = 50 + book.param1 * 50 + book.param1 * book.param1 * 20;
            r3 = 0;
        }
        else
        {
            r2 = the_ability_db[efid]->difficulty;
            r3 = efid;
        }
        if (book.curse_state == CurseState::blessed)
        {
            r2 = r2 * 100 / 120;
        }
        if (is_cursed(book.curse_state))
        {
            r2 = r2 * 150 / 100;
        }
        int _dummy{};
        int stat = try_to_cast_spell(reader, _dummy);
        if (stat == 0)
        {
            reader.activity.finish();
            --book.count;
            if (book.count < 0)
            {
                book.count = 0;
            }
            if (book.count == 0)
            {
                book.modify_number(-1);
                if (is_in_fov(reader))
                {
                    txt(i18n::s.get("core.action.read.book.falls_apart", book));
                }
            }
        }
        return 0;
    }
    if (is_in_fov(reader))
    {
        txt(i18n::s.get("core.activity.read.finish", reader, book));
    }
    if (book.id == ItemId::recipe)
    {
        if (book.param1 == 0)
        {
            reader.activity.finish();
            return 1;
        }
        txt(i18n::s.get("core.action.read.recipe.learned", book));
        ++recipememory(book.subname);
        item_identify(book, IdentifyState::partly);
        book.modify_number(-1);
        if (is_in_fov(reader))
        {
            txt(i18n::s.get("core.action.read.book.falls_apart", book));
        }
        reader.activity.finish();
        return 1;
    }
    if (book.id == ItemId::ancient_book)
    {
        item_identify(book, IdentifyState::completely);
        txt(i18n::s.get("core.action.read.book.finished_decoding", book));
        book.param2 = 1;
        book.count = 1;
        book.has_charge() = false;
        item_stack(0, book, true);
    }
    else
    {
        chara_gain_skill(
            reader,
            efid,
            1,
            (rnd(51) + 50) *
                    (90 + sdata(165, reader.index) +
                     (sdata(165, reader.index) > 0) * 20) /
                    clamp((100 + spell((efid - 400)) / 2), 50, 1000) +
                1);
        chara_gain_exp_memorization(cdata.player(), efid);
        if (itemmemory(2, itemid2int(book.id)) == 0)
        {
            itemmemory(2, itemid2int(book.id)) = 1;
        }
    }
    item_identify(book, IdentifyState::partly);
    if (book.id != ItemId::ancient_book)
    {
        --book.count;
        if (book.count < 0)
        {
            book.count = 0;
        }
        if (book.count == 0)
        {
            book.modify_number(-1);
            if (is_in_fov(reader))
            {
                txt(i18n::s.get("core.action.read.book.falls_apart", book));
            }
        }
    }
    reader.activity.finish();
    return 1;
}



int read_normal_book(Character& reader, Item& book)
{
    if (reader.blind != 0)
    {
        if (is_in_fov(reader))
        {
            txt(i18n::s.get("core.action.read.cannot_see", reader));
        }
        return 0;
    }
    if (book.id == ItemId::license_of_the_void_explorer)
    {
        snd("core.book1");
        txt(i18n::s.get("core.action.read.book.void_permit"));
        return 1;
    }
    if (book.id == ItemId::textbook)
    {
        return read_textbook(reader, book);
    }
    if (book.id == ItemId::book_of_rachel)
    {
        snd("core.book1");
        txt(i18n::s.get("core.action.read.book.book_of_rachel"));
        return 1;
    }
    item_identify(book, IdentifyState::partly);
    show_book_window(book);
    return 1;
}



bool calc_magic_control(Character& caster, const Character& target)
{
    if (sdata(188, caster.index) != 0)
    {
        if (belong_to_same_team(caster, target))
        {
            if (sdata(188, caster.index) * 5 > rnd_capped(dmg + 1))
            {
                dmg = 0;
            }
            else
            {
                dmg = rnd_capped(
                    dmg * 100 / (100 + sdata(188, caster.index) * 10) + 1);
            }
            if (dmg < 1)
            {
                if (is_in_fov(target))
                {
                    txt(i18n::s.get("core.misc.spell_passes_through", target));
                }
                chara_gain_skill_exp(caster, 188, 8, 4);
                return true;
            }
            chara_gain_skill_exp(caster, 188, 30, 2);
        }
    }
    return false;
}



int do_cast_magic(Character& caster, int& enemy_index)
{
    int spellbk = 0;
    spellbk = efid;
    int stat = do_cast_magic_attempt(caster, enemy_index);
    if (stat == 1)
    {
        chara_gain_exp_casting(caster, spellbk);
        return 1;
    }
    return 0;
}



int do_cast_magic_attempt(Character& caster, int& enemy_index)
{
    int mp = 0;
    efsource = 3;
    efstatus = CurseState::none;
    efp = calc_spell_power(caster, efid);
    if (caster.index == 0)
    {
        if (calc_spell_cost_mp(caster, efid) > caster.mp)
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
    if (!prompt_magic_location(caster, enemy_index))
    {
        efsource = 0;
        return 0;
    }
    if (caster.index != 0)
    {
        if (the_ability_db[efid]->ability_type == 7)
        {
            if (caster.relationship == 10 ||
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

    if (caster.index == 0)
    {
        spell(efid - 400) -= calc_spell_cost_stock(caster, efid);
        if (spell(efid - 400) < 0)
        {
            spell(efid - 400) = 0;
        }
    }
    mp = calc_spell_cost_mp(caster, efid);
    if (caster.index == 0)
    {
        if (cdata.player().god_id == core_god::ehekatl)
        {
            mp = rnd(mp * 140 / 100 + 1) + 1;
        }
    }
    damage_mp(caster, mp);
    if (caster.state() != Character::State::alive)
    {
        efsource = 0;
        return 1;
    }

    if (caster.confused != 0 || caster.dimmed != 0)
    {
        if (is_in_fov(caster))
        {
            txt(i18n::s.get("core.action.cast.confused", caster));
        }
        int stat = try_to_cast_spell(caster, enemy_index);
        if (stat == 0)
        {
            efsource = 0;
            return 1;
        }
    }
    else if (is_in_fov(caster))
    {
        if (caster.index == 0)
        {
            txt(i18n::s.get(
                "core.action.cast.self",
                caster,
                i18n::s.get_m(
                    "ability",
                    the_ability_db.get_id_from_legacy(efid)->get(),
                    "name"),
                i18n::s.get_enum(
                    "core.ui.cast_style", caster.special_attack_type)));
        }
        else
        {
            txt(i18n::s.get(
                "core.action.cast.other",
                caster,
                i18n::s.get_enum(
                    "core.ui.cast_style", caster.special_attack_type)));
        }
    }
    if (buff_has(caster, "core.mist_of_silence"))
    {
        if (is_in_fov(caster))
        {
            txt(i18n::s.get("core.action.cast.silenced"));
        }
        efsource = 0;
        return 1;
    }
    if (rnd(100) >= calc_spell_success_rate(caster, efid))
    {
        if (is_in_fov(caster))
        {
            txt(i18n::s.get("core.action.cast.fail", caster));
            FailureToCastAnimation(caster.position).play();
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
    efp = calc_spell_power(caster, efid);
    if (const auto spell_enhancement = enchantment_find(caster, 34))
    {
        efp = efp * (100 + *spell_enhancement / 10) / 100;
    }
    rapidmagic = 0;
    if (caster.can_cast_rapid_magic() &&
        the_ability_db[efid]->ability_type == 2)
    {
        rapidmagic = 1 + (rnd(3) != 0) + (rnd(2) != 0);
    }
    if (rapidmagic)
    {
        for (int cnt = 0, cnt_end = (rapidmagic); cnt < cnt_end; ++cnt)
        {
            magic(caster, cdata[enemy_index]);
            if (cdata[enemy_index].state() != Character::State::alive)
            {
                int stat = find_enemy_target(caster);
                if (stat == 0)
                {
                    break;
                }
                else
                {
                    enemy_index = caster.enemy_id;
                    if (relationbetween(caster.index, enemy_index) != -3)
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
        magic(caster, cdata[enemy_index]);
    }
    return 1;
}



int drink_potion(Character& chara, optional_ref<Item> potion)
{
    assert(potionspill || potion);

    efsource = 4;
    if (potionspill || potionthrow)
    {
        if (potionthrow)
        {
            efp = efp * potionthrow / 100;
            efstatus = potion->curse_state;
        }
    }
    else
    {
        efstatus = potion->curse_state;
        if (is_in_fov(chara))
        {
            snd_at("core.drink1", chara.position);
            txt(i18n::s.get("core.action.drink.potion", chara, *potion));
        }
    }
    magic(chara, chara);
    if (potionspill || potionthrow)
    {
        potionspill = 0;
        potionthrow = 0;
    }
    else
    {
        if (obvious == 1)
        {
            if (chara.index == 0)
            {
                item_identify(*potion, IdentifyState::partly);
            }
        }
        potion->modify_number(-1);
    }
    chara.nutrition += 150;
    if (chara.index < 16)
    {
        if (chara.nutrition > 12000)
        {
            if (rnd(5) == 0)
            {
                chara_vomit(chara);
            }
        }
    }
    return 1;
}



int drink_well(Character& chara, Item& well)
{
    if (well.param1 < -5 || well.param3 >= 20 ||
        (well.id == ItemId::holy_well && game_data.holy_well_count <= 0))
    {
        const auto valn = itemname(well);
        txt(i18n::s.get("core.action.drink.well.is_dry", valn));
        return 1;
    }
    item_separate(well);
    snd_at("core.drink1", chara.position);
    const auto valn = itemname(well);
    txt(i18n::s.get("core.action.drink.well.draw", chara, valn));
    p = rnd(100);
    for (int cnt = 0; cnt < 1; ++cnt)
    {
        if (chara.index != 0)
        {
            if (rnd(15) == 0)
            {
                txt(i18n::s.get(
                    "core.action.drink.well.effect.falls.text", chara));
                txt(i18n::s.get(
                        "core.action.drink.well.effect.falls.dialog", chara),
                    Message::color{ColorIndex::cyan});
                if (chara.is_floating() == 1 && chara.gravity == 0)
                {
                    txt(i18n::s.get(
                        "core.action.drink.well.effect.falls.floats", chara));
                }
                else
                {
                    damage_hp(chara, 9999, -1);
                }
                break;
            }
        }
        if (well.id == ItemId::holy_well)
        {
            if (rnd(2) == 0)
            {
                efid = 1113;
                magic(chara, chara);
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
                magic(chara, chara);
                break;
            }
            if (p == 1)
            {
                efid = 1110;
                efp = 100;
                magic(chara, chara);
                break;
            }
            if (p == 2)
            {
                efid = 1111;
                efp = 100;
                magic(chara, chara);
                break;
            }
            if (p == 3)
            {
                efid = 1109;
                efp = 100;
                magic(chara, chara);
                break;
            }
            if (p == 4)
            {
                efid = 1108;
                efp = 100;
                magic(chara, chara);
                break;
            }
        }
        if (p > 55)
        {
            flt();
            itemcreate_extra_inv(
                54,
                chara.position,
                rnd_capped(sdata(159, chara.index) / 2 * 50 + 100) + 1);
            txt(i18n::s.get("core.action.drink.well.effect.finds_gold", chara));
            break;
        }
        if (p > 45)
        {
            p = rnd(8) + 10;
            if (rnd(5) > 2)
            {
                chara_gain_fixed_skill_exp(chara, p, 1000);
            }
            else
            {
                chara_gain_fixed_skill_exp(chara, p, -1000);
            }
            break;
        }
        if (p > 40)
        {
            if (chara.level < 5)
            {
                break;
            }
            if (is_in_fov(chara))
            {
                txt(i18n::s.get(
                    "core.action.drink.well.effect.pregnancy", chara));
            }
            get_pregnant(chara);
            break;
        }
        if (p > 35)
        {
            txt(i18n::s.get("core.action.drink.well.effect.monster"));
            for (int cnt = 0, cnt_end = (1 + rnd(3)); cnt < cnt_end; ++cnt)
            {
                flt(calcobjlv(chara.level * 3 / 2 + 3),
                    calcfixlv(Quality::bad));
                chara_create(-1, 0, chara.position.x, chara.position.y);
            }
            break;
        }
        if (p > 33)
        {
            efid = 1113;
            magic(chara, chara);
            break;
        }
        if (p > 20)
        {
            efid = 454;
            magic(chara, chara);
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
            magic(chara, chara);
            break;
        }
        if (chara.index == 0)
        {
            txt(i18n::s.get("core.action.drink.well.effect.default"));
        }
    }
    if (chara.index != 0)
    {
        chara.nutrition += 4000;
    }
    else
    {
        chara.nutrition += 500;
    }
    if (well.id == ItemId::holy_well)
    {
        --game_data.holy_well_count;
    }
    else
    {
        well.param1 -= rnd(3);
        well.param3 += rnd(3);
        if (well.param3 >= 20)
        {
            txt(i18n::s.get(
                "core.action.drink.well.completely_dried_up", well));
            return 1;
        }
    }
    if (well.param1 < -5)
    {
        txt(i18n::s.get("core.action.drink.well.dried_up", well));
    }
    return 1;
}



int read_scroll(Character& reader, Item& scroll)
{
    tlocx = reader.position.x;
    tlocy = reader.position.y;
    efstatus = scroll.curse_state;
    efsource = 2;
    if (reader.blind != 0)
    {
        if (is_in_fov(reader))
        {
            txt(i18n::s.get("core.action.read.cannot_see", reader));
        }
        efsource = 0;
        return 0;
    }
    if (reader.dimmed != 0 || reader.confused != 0)
    {
        if (rnd(4) != 0)
        {
            if (is_in_fov(reader))
            {
                txt(i18n::s.get(
                    "core.action.read.scroll.dimmed_or_confused", reader));
            }
            efsource = 0;
            return 0;
        }
    }
    if (is_in_fov(reader))
    {
        txt(i18n::s.get("core.action.read.scroll.execute", reader, scroll));
    }
    if (scroll.id != ItemId::treasure_map)
    {
        scroll.modify_number(-1);
        chara_gain_skill_exp(reader, 150, 25, 2);
    }
    magic(reader, reader, scroll);
    if (reader.index == 0)
    {
        if (obvious == 1)
        {
            item_identify(scroll, IdentifyState::partly);
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

    int enemy_index = doer.index;
    if (!prompt_magic_location(doer, enemy_index))
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
        magic(doer, cdata[enemy_index]);
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



int do_zap(Character& doer, Item& rod)
{
    const auto zapped = do_zap_internal(doer, rod);
    if (!zapped)
        return 0;

    efsource = 0;
    if (rod.number() == 0)
    {
        if (rod.index >= ELONA_ITEM_ON_GROUND_INDEX)
        {
            cell_refresh(rod.position.x, rod.position.y);
            return 1;
        }
    }
    item_separate(rod);
    --rod.count;
    return 1;
}



int do_spact(Character& doer, int& enemy_index)
{
    if (efid == 646)
    {
        if (cdata[enemy_index].is_sentenced_daeth() == 1)
        {
            if (doer.relationship == -3)
            {
                for (int cnt = 0; cnt < ELONA_MAX_PARTY_CHARACTERS; ++cnt)
                {
                    if (cdata[cnt].state() == Character::State::alive)
                    {
                        if (cdata[cnt].relationship == 10)
                        {
                            doer.enemy_id = cnt;
                            break;
                        }
                    }
                }
            }
            return 0;
        }
    }
    if (!prompt_magic_location(doer, enemy_index))
    {
        return 0;
    }
    if (the_ability_db[efid]->range / 1000 * 1000 != 3000 &&
        the_ability_db[efid]->range / 1000 * 1000 != 10000)
    {
        if (doer.confused != 0 || doer.blind != 0)
        {
            if (rnd(5) == 0)
            {
                if (is_in_fov(doer))
                {
                    txt(i18n::s.get("core.misc.shakes_head", doer));
                }
                return 1;
            }
        }
    }
    if (efid >= 600)
    {
        if (doer.index == 0)
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
                doer, the_ability_db[efid]->related_basic_attribute, 25);
        }
    }
    efp = calc_spell_power(doer, efid);
    if (noeffect == 1)
    {
        if (efid != 300)
        {
            txt(i18n::s.get("core.common.nothing_happens"));
            return 1;
        }
    }
    {
        int stat = magic(doer, cdata[enemy_index]);
        if (stat == 0)
        {
            return 0;
        }
    }
    return 1;
}



bool prompt_magic_location(Character& caster, int& enemy_index)
{
    noeffect = 0;
    if (efid > 661)
    {
        enemy_index = caster.index;
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
        if (caster.index == 0)
        {
            enemy_index = 0;
            return 1;
        }
    }
    if (tg == 8000)
    {
        if (caster.index == 0)
        {
            enemy_index = 0;
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
            enemy_index = cell_data.at(tlocx, tlocy).chara_index_plus_one - 1;
        }
        else
        {
            if (dist(
                    cdata[enemy_index].position.x,
                    cdata[enemy_index].position.y,
                    caster.position.x,
                    caster.position.y) > the_ability_db[efid]->range % 1000 + 1)
            {
                return 0;
            }
            tlocx = cdata[enemy_index].position.x;
            tlocy = cdata[enemy_index].position.y;
        }
        return 1;
    }
    if (tg == 7000 || (tg == 9000 && tgloc == 1 && caster.index == 0))
    {
        if (caster.index == 0)
        {
            if (tg == 9000)
            {
                if (int stat = fov_los(
                                   caster.position.x,
                                   caster.position.y,
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
                    cdata[enemy_index].position.x,
                    cdata[enemy_index].position.y,
                    caster.position.x,
                    caster.position.y) == 0)
            {
                return 0;
            }
            tlocx = cdata[enemy_index].position.x;
            tlocy = cdata[enemy_index].position.y;
        }
        return 1;
    }
    if (tg == 3000 || tg == 10000)
    {
        if (caster.index != 0)
        {
            if (the_ability_db[efid]->ability_type == 3)
            {
                if (dist(
                        cdata[enemy_index].position.x,
                        cdata[enemy_index].position.y,
                        caster.position.x,
                        caster.position.y) >
                    the_ability_db[efid]->range % 1000 + 1)
                {
                    return 0;
                }
                if (fov_los(
                        caster.position.x,
                        caster.position.y,
                        cdata[enemy_index].position.x,
                        cdata[enemy_index].position.y) == 0)
                {
                    return 0;
                }
            }
        }
        enemy_index = caster.index;
        tlocx = caster.position.x;
        tlocy = caster.position.y;
        return 1;
    }
    if (tg == 2000 || tg == 6000 || tg == 9000)
    {
        if (caster.index == 0)
        {
            int stat = find_enemy_target(caster);
            if (stat == 0)
            {
                obvious = 0;
                return 0;
            }
            enemy_index = cdata.player().enemy_id;
            if (cdata[enemy_index].relationship >= 0)
            {
                int stat = prompt_really_attack(cdata[enemy_index]);
                if (stat == 0)
                {
                    obvious = 0;
                    return 0;
                }
            }
        }
        if (dist(
                cdata[enemy_index].position.x,
                cdata[enemy_index].position.y,
                caster.position.x,
                caster.position.y) > the_ability_db[efid]->range % 1000 + 1)
        {
            if (caster.index == 0)
            {
                txt(i18n::s.get("core.action.which_direction.out_of_range"),
                    Message::only_once{true});
                update_screen();
            }
            return 0;
        }
        if (fov_los(
                caster.position.x,
                caster.position.y,
                cdata[enemy_index].position.x,
                cdata[enemy_index].position.y) == 0)
        {
            return 0;
        }
        tlocx = cdata[enemy_index].position.x;
        tlocy = cdata[enemy_index].position.y;
        return 1;
    }
    if (tg == 5000)
    {
        if (caster.index == 0)
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



PickUpItemResult pick_up_item(
    int inventory_id,
    Item& item,
    optional_ref<Character> shopkeeper,
    bool play_sound)
{
    if (invctrl == 11 || invctrl == 12)
    {
        assert(shopkeeper);
    }

    const auto snd_ = [play_sound](data::InstanceId id) {
        if (play_sound)
        {
            snd(id);
        }
    };

    int sellgold = 0;
    if (inventory_id != -1)
    {
        if (item.id == ItemId::gold_piece || item.id == ItemId::platinum_coin)
        {
            snd_("core.getgold1");
            txt(i18n::s.get(
                "core.action.pick_up.execute",
                cdata[inventory_id],
                itemname(item)));
            if (item.id == ItemId::gold_piece)
            {
                earn_gold(cdata[inventory_id], item.number());
            }
            else
            {
                earn_platinum(cdata[inventory_id], item.number());
            }
            in = item.number();
            item.remove();
            cell_refresh(item.position.x, item.position.y);
            return {1, none};
        }
    }
    if (inventory_id == 0)
    {
        if (game_data.mount != 0)
        {
            if (cdata[game_data.mount].activity)
            {
                if (cdata[game_data.mount].activity.item == item.index)
                {
                    txt(i18n::s.get(
                        "core.action.pick_up.used_by_mount",
                        cdata[game_data.mount]));
                    return {1, none};
                }
            }
        }
        if (the_item_db[itemid2int(item.id)]->category == ItemCategory::food)
        {
            if (item.own_state == 4)
            {
                if (!cdata.player().activity)
                {
                    if (!inv_getspace(0))
                    {
                        txt(i18n::s.get(
                            "core.ui.inv.common.inventory_is_full"));
                        return {0, none};
                    }
                    game_data.activity_about_to_start = 103;
                    activity_others(cdata[inventory_id], item);
                    return {-1, none};
                }
            }
        }
        if (item.own_state == 3)
        {
            txt(i18n::s.get("core.action.pick_up.do_you_want_to_remove", item));
            if (yes_no())
            {
                snd_("core.build1");
                if (item.id == ItemId::shelter)
                {
                    std::string midbk = mid;
                    mid = ""s + 30 + u8"_"s + (100 + item.count);
                    tmpload(filepathutil::u8path(u8"mdata_"s + mid + u8".s2"));
                    if (fs::exists(
                            filesystem::dirs::tmp() /
                            (u8"mdata_"s + mid + u8".s2")))
                    {
                        ctrl_file(FileOperation::map_delete);
                    }
                    mid = midbk;
                    item.count = 0;
                    item.own_state = 0;
                }
            }
            else
            {
                return {0, none};
            }
        }
        if (!inv_get_free_slot(inventory_id))
        {
            txt(i18n::s.get("core.action.pick_up.your_inventory_is_full"));
            return {0, none};
        }
    }
    inumbk = item.number() - in;
    item.set_number(in);
    if (inventory_id == 0)
    {
        if (trait(215) != 0)
        {
            if (the_item_db[itemid2int(item.id)]->category == ItemCategory::rod)
            {
                if (item.count > 0)
                {
                    item_db_on_zap(item, itemid2int(item.id));
                    txt(i18n::s.get(
                        "core.action.pick_up.you_absorb_magic", item));
                    if (efid >= 400 && efid < 467)
                    {
                        spell(efid - 400) += item.count * 5 * item.number();
                    }
                    else
                    {
                        heal_mp(cdata.player(), item.count * 5 * item.number());
                    }
                    item.count = 0;
                }
            }
        }
        if (trait(216) != 0)
        {
            if (the_item_db[itemid2int(item.id)]->category ==
                ItemCategory::potion)
            {
                if (item.id != ItemId::poison &&
                    item.id != ItemId::potion_of_cure_corruption)
                {
                    if (rnd(5) == 0)
                    {
                        txt(i18n::s.get("core.action.pick_up.poison_drips"));
                        item.id = ItemId::poison;
                    }
                }
            }
        }
    }
    if (item.own_state < 0)
    {
        item.own_state = 0;
    }
    item.is_quest_target() = false;
    item_checkknown(item);

    optional_ref<Item> picked_up_item;
    const auto item_stack_result = item_stack(inventory_id, item);
    if (item_stack_result.stacked)
    {
        picked_up_item = item_stack_result.stacked_item;
    }
    else
    {
        const auto slot = inv_get_free_slot(inventory_id);
        if (!slot)
        {
            item.set_number(inumbk + in);
            if (invctrl == 12)
            {
                txt(i18n::s.get(
                    "core.action.pick_up.shopkeepers_inventory_is_full"));
            }
            else
            {
                txt(i18n::s.get("core.action.pick_up.your_inventory_is_full"));
            }
            return {0, none};
        }
        item_copy(item, *slot);
        slot->set_number(in);
        picked_up_item = *slot;
    }
    assert(picked_up_item);

    item.set_number(inumbk);
    if (mode == 6)
    {
        if (the_item_db[itemid2int(picked_up_item->id)]->category ==
            ItemCategory::food)
        {
            if (invctrl == 11 || invctrl == 22)
            {
                if (invctrl == 22 && invctrl(1) == 3)
                {
                    if (picked_up_item->param3 > 0)
                    {
                        picked_up_item->param3 += game_data.date.hours();
                    }
                }
                else if (
                    picked_up_item->param3 != 0 &&
                    picked_up_item->material == 35)
                {
                    picked_up_item->param3 = game_data.date.hours() +
                        the_item_db[itemid2int(picked_up_item->id)]
                            ->expiration_date;
                    if (picked_up_item->param2 != 0)
                    {
                        picked_up_item->param3 += 72;
                    }
                }
            }
            if (invctrl == 24 && invctrl(1) == 3)
            {
                if (picked_up_item->param3 > 0)
                {
                    picked_up_item->param3 =
                        picked_up_item->param3 - game_data.date.hours();
                }
            }
        }
        if (invctrl == 11)
        {
            txt(i18n::s.get(
                "core.action.pick_up.you_buy", itemname(*picked_up_item, in)));
            sellgold = calcitemvalue(*picked_up_item, 0) * in;
            snd_("core.paygold1");
            cdata.player().gold -= sellgold;
            earn_gold(*shopkeeper, sellgold);
            if (the_item_db[itemid2int(picked_up_item->id)]->category ==
                ItemCategory::cargo)
            {
                picked_up_item->param2 = calcitemvalue(*picked_up_item, 0);
            }
        }
        if (invctrl == 12)
        {
            sellgold = calcitemvalue(item, 1) * in;
            if (!picked_up_item->is_stolen())
            {
                txt(i18n::s.get(
                    "core.action.pick_up.you_sell",
                    itemname(*picked_up_item, in)));
            }
            else
            {
                picked_up_item->is_stolen() = false;
                txt(i18n::s.get(
                    "core.action.pick_up.you_sell_stolen",
                    itemname(*picked_up_item, in)));
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
            shopkeeper->gold -= sellgold;
            if (shopkeeper->gold < 0)
            {
                shopkeeper->gold = 0;
            }
            picked_up_item->identify_state = IdentifyState::completely;
        }
        if (invctrl == 22 || invctrl == 24)
        {
            sound_pick_up();
            if (invctrl == 22)
            {
                txt(i18n::s.get(
                    "core.action.pick_up.execute",
                    cdata[inventory_id],
                    itemname(*picked_up_item, in)));
            }
            else
            {
                txt(i18n::s.get(
                    "core.action.pick_up.put_in_container",
                    itemname(*picked_up_item, in)));
            }
        }
        else
        {
            chara_gain_exp_negotiation(cdata.player(), sellgold);
        }
    }
    else
    {
        cell_refresh(item.position.x, item.position.y);
        cell_data.at(item.position.x, item.position.y).item_appearances_memory =
            cell_data.at(item.position.x, item.position.y)
                .item_appearances_actual;
        sound_pick_up();
        txt(i18n::s.get(
            "core.action.pick_up.execute",
            cdata[inventory_id],
            itemname(*picked_up_item, in)));
    }
    if (inventory_id == 0)
    {
        if (picked_up_item->id == ItemId::campfire)
        {
            if (map_data.play_campfire_sound == 1)
            {
                f = 0;
                for (const auto& item_ : inv.ground())
                {
                    if (item_.number() == 0)
                    {
                        continue;
                    }
                    if (item_.id == ItemId::campfire)
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
        picked_up_item = item_convert_artifact(*picked_up_item);
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
                building_update_home_rank();
            }
        }
        refresh_burden_state();
    }
    if (inventory_id == -1)
    {
        refresh_burden_state();
    }

    return {1, picked_up_item};
}



TurnResult do_bash(Character& chara)
{
    if (cell_data.at(x, y).item_appearances_memory != 0)
    {
        if (const auto tree_opt = mapitemfind({x, y}, ItemId::tree_of_fruits))
        {
            auto& tree = *tree_opt;
            item_separate(tree);
            snd("core.bash1");
            txt(i18n::s.get("core.action.bash.tree.execute", tree));
            if (tree.own_state == 5 || tree.param1 <= 0)
            {
                txt(i18n::s.get("core.action.bash.tree.no_fruits"));
                return TurnResult::turn_end;
            }
            --tree.param1;
            if (tree.param1 <= 0)
            {
                tree.image = 592;
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
            if (const auto fruit = itemcreate_extra_inv(tree.param2, x, y, 0))
            {
                txt(i18n::s.get("core.action.bash.tree.falls_down", *fruit));
                item_stack(-1, *fruit);
            }
            return TurnResult::turn_end;
        }
    }
    if (cell_data.at(x, y).chara_index_plus_one != 0)
    {
        const auto bash_target_index =
            cell_data.at(x, y).chara_index_plus_one - 1;
        if (cdata[bash_target_index].sleep == 0)
        {
            if (chara.index == 0)
            {
                if (cdata[bash_target_index].relationship >= 0)
                {
                    int stat = prompt_really_attack(cdata[bash_target_index]);
                    if (stat == 0)
                    {
                        return TurnResult::pc_turn_user_error;
                    }
                }
            }
            if (cdata[bash_target_index].choked)
            {
                snd("core.bash1");
                txt(i18n::s.get(
                    "core.action.bash.choked.execute",
                    chara,
                    cdata[bash_target_index]));
                damage_hp(
                    cdata[bash_target_index],
                    sdata(10, chara.index) * 5,
                    chara.index);
                if (cdata[bash_target_index].state() == Character::State::alive)
                {
                    txt(i18n::s.get(
                        "core.action.bash.choked.spits",
                        cdata[bash_target_index]));
                    txt(i18n::s.get("core.action.bash.choked.dialog"));
                    cdata[bash_target_index].choked = 0;
                    chara_modify_impression(cdata[bash_target_index], 10);
                }
            }
            else
            {
                snd("core.bash1");
                txt(i18n::s.get(
                    "core.action.bash.execute",
                    chara,
                    cdata[bash_target_index]));
                hostileaction(chara.index, bash_target_index);
            }
        }
        else
        {
            snd("core.bash1");
            txt(i18n::s.get(
                "core.action.bash.execute", chara, cdata[bash_target_index]));
            txt(i18n::s.get(
                "core.action.bash.disturbs_sleep",
                chara,
                cdata[bash_target_index]));
            modify_karma(chara, -1);
            cdata[bash_target_index].emotion_icon = 418;
        }
        cdata[bash_target_index].sleep = 0;
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
            if (is_in_fov(chara))
            {
                snd("core.bash1");
                txt(i18n::s.get("core.action.bash.shatters_pot", chara));
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
            if (rnd_capped(p(0)) < sdata(10, chara.index) && rnd(2))
            {
                txt(i18n::s.get("core.action.bash.door.destroyed"));
                if (feat(2) > sdata(10, chara.index))
                {
                    chara_gain_skill_exp(
                        chara, 10, (feat(2) - sdata(10, chara.index)) * 15);
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
                    efid = 1109;
                    efp = 200;
                    magic(chara, chara);
                }
                if (rnd(3) == 0)
                {
                    efid = 1110;
                    efp = 200;
                    magic(chara, chara);
                }
                if (rnd(3) == 0)
                {
                    if (chara.quality < Quality::miracle &&
                        !enchantment_find(chara, 60010))
                    {
                        --chara.attr_adjs[0];
                        chara_refresh(chara);
                        if (is_in_fov(chara))
                        {
                            txt(i18n::s.get(
                                    "core.action.bash.door.hurt", chara),
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
                        if (is_in_fov(chara))
                        {
                            txt(i18n::s.get("core.action.bash.door.cracked"));
                        }
                    }
                }
                return TurnResult::turn_end;
            }
        }
    }
    txt(i18n::s.get("core.action.bash.air", chara));
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
            {
                in = item.number();
                const auto pick_up_item_result =
                    pick_up_item(cdata.player().index, item, none, !op.sound);
                if (pick_up_item_result.type != 1)
                {
                    break;
                }
                if (int(op.type) & int(Autopick::Operation::Type::no_drop))
                {
                    if (const auto picked_up_item =
                            pick_up_item_result.picked_up_item)
                    {
                        picked_up_item->is_marked_as_no_drop() = true;
                        txt(i18n::s.get(
                            "core.ui.inv.examine.no_drop.set",
                            *picked_up_item));
                    }
                }
                if (int(op.type) & int(Autopick::Operation::Type::save))
                {
                    if (!game_data.wizard)
                    {
                        save_game();
                    }
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
            (void)do_open_command(item, !op.sound); // Result is unused.
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
    const auto lockpick_opt = item_find(636, 3);
    if (!lockpick_opt)
    {
        txt(i18n::s.get("core.action.unlock.do_not_have_lockpicks"));
        return 0;
    }
    auto& lockpick = *lockpick_opt;

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
            lockpick.modify_number(-1);
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
    chara_gain_exp_lock_picking(cdata.player());
    return 1;
}



void open_box(Item& box)
{
    snd("core.chest1");
    txt(i18n::s.get("core.action.open.text", box));
    msg_halt();
    if (box.id == ItemId::material_box)
    {
        efid = 1117;
        efp = 100 + box.param1 * 10;
        box.param1 = 0;
        magic(cdata.player(), cdata.player());
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
                in = 50 * box.value;
            }
            else
            {
                in = rnd_capped(box.value / 10 + 1) + 1;
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
    box.param1 = 0;
    if (box.param3 < 100)
    {
        if (rnd(3) == 0)
        {
            if (is_in_fov(cdata.player()))
            {
                txt(i18n::s.get(
                    "core.action.open.new_year_gift.something_jumps_out"));
            }
            for (int cnt = 0, cnt_end = (3 + rnd(3)); cnt < cnt_end; ++cnt)
            {
                flt(calcobjlv(cdata.player().level * 3 / 2 + 3),
                    calcfixlv(Quality::bad));
                chara_create(
                    -1,
                    0,
                    cdata.player().position.x,
                    cdata.player().position.y);
            }
            return;
        }
        if (rnd(3) == 0)
        {
            if (is_in_fov(cdata.player()))
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
                mapitem_fire(cdata.player(), tlocx, tlocy);
            }
            return;
        }
        if (is_in_fov(cdata.player()))
        {
            txt(i18n::s.get("core.action.open.new_year_gift.cursed_letter"));
        }
        efid = 1114;
        efp = 1000;
        magic(cdata.player(), cdata.player());
        return;
    }
    if (box.param3 < 200)
    {
        if (rnd(4) == 0)
        {
            if (is_in_fov(cdata.player()))
            {
                txt(i18n::s.get("core.action.open.new_year_gift.ring"),
                    Message::color{ColorIndex::orange});
            }
            flt();
            if (const auto chara = chara_create(
                    -1,
                    328 + rnd(2),
                    cdata.player().position.x,
                    cdata.player().position.y))
            {
                if (cdata.player().relationship <= -3)
                {
                    chara->relationship = -1;
                    chara->original_relationship = -1;
                }
            }
            return;
        }
        if (rnd(5) == 0)
        {
            if (is_in_fov(cdata.player()))
            {
                txt(i18n::s.get(
                    "core.action.open.new_year_gift.younger_sister"));
            }
            flt();
            if (const auto chara = chara_create(
                    -1,
                    176,
                    cdata.player().position.x,
                    cdata.player().position.y))
            {
                chara->gold = 5000;
            }
            return;
        }
        if (is_in_fov(cdata.player()))
        {
            txt(i18n::s.get("core.action.open.new_year_gift.something_inside"));
        }
        flt();
        itemcreate_extra_inv(choice(isetgiftminor), cdata.player().position, 1);
        return;
    }
    if (rnd(3) == 0)
    {
        if (is_in_fov(cdata.player()))
        {
            txt(i18n::s.get("core.action.open.new_year_gift.ring"),
                Message::color{ColorIndex::orange});
        }
        for (int cnt = 0, cnt_end = (2 + rnd(3)); cnt < cnt_end; ++cnt)
        {
            flt();
            if (const auto chara = chara_create(
                    -1,
                    328 + rnd(2),
                    cdata.player().position.x,
                    cdata.player().position.y))
            {
                if (cdata.player().relationship <= -3)
                {
                    chara->relationship = -1;
                    chara->original_relationship = -1;
                }
            }
        }
        return;
    }
    if (rnd(50) == 0)
    {
        if (is_in_fov(cdata.player()))
        {
            txt(i18n::s.get("core.action.open.new_year_gift.wonderful"));
        }
        flt();
        itemcreate_extra_inv(choice(isetgiftgrand), cdata.player().position, 1);
        return;
    }
    if (is_in_fov(cdata.player()))
    {
        txt(i18n::s.get("core.action.open.new_year_gift.something_inside"));
    }
    flt();
    itemcreate_extra_inv(choice(isetgiftmajor), cdata.player().position, 1);
}



TurnResult try_to_open_locked_door(Character& chara)
{
    cell_featread(dx, dy);
    if (feat == tile_doorclosed4 && feat(2) > 0)
    {
        if (chara.index == 0)
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
        if (rnd(feat(2) * 20 + 150) < sdata(158, chara.index) * 20 + 20)
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
            chara_gain_exp_lock_picking(chara);
        }
        cell_featset(dx, dy, tile_dooropen, 20, 0, -1);
        if (is_in_fov(chara))
        {
            txt(i18n::s.get("core.action.open.door.suchara.indexeed", chara));
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
        if (is_in_fov(chara))
        {
            snd("core.locked1");
            txt(i18n::s.get("core.action.open.door.fail", chara),
                Message::only_once{true});
        }
    }
    if (chara.index == 0)
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



TurnResult do_plant(Item& seed)
{
    screenupdate = -1;
    update_screen();
    if (map_data.type == mdata_t::MapType::world_map || map_is_town_or_guild())
    {
        txt(i18n::s.get("core.action.plant.cannot_plant_it_here"));
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    if (cell_data.at(cdata.player().position.x, cdata.player().position.y)
            .feats != 0)
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
    feat(2) = seed.material;
    try_to_grow_plant(val0);
    if (val0)
    {
        s = i18n::s.get("core.action.plant.on_field", seed);
    }
    else
    {
        s = i18n::s.get("core.action.plant.execute", seed);
    }
    txt(s);
    snd("core.bush1");
    seed.modify_number(-1);
    cell_featset(
        cdata.player().position.x,
        cdata.player().position.y,
        tile_plant,
        29,
        seed.material,
        feat(3));
    chara_gain_skill_exp(cdata.player(), 180, 300);
    return TurnResult::turn_end;
}

} // namespace elona

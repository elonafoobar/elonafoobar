#include <iostream>

#include "ability.hpp"
#include "area.hpp"
#include "audio.hpp"
#include "building.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "config.hpp"
#include "ctrl_file.hpp"
#include "data/types/type_map.hpp"
#include "deferred_event.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "food.hpp"
#include "i18n.hpp"
#include "initialize_map_types.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "lua_env/event_manager.hpp"
#include "lua_env/lua_env.hpp"
#include "lua_env/lua_event/lua_event_map_initialized.hpp"
#include "lua_env/mod_manager.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "mapgen.hpp"
#include "menu.hpp"
#include "message.hpp"
#include "quest.hpp"
#include "random.hpp"
#include "save_fs.hpp"
#include "scene.hpp"
#include "text.hpp"
#include "ui.hpp"
#include "variables.hpp"



namespace elona
{

namespace
{

int maxnpcbk = 0;
elona_vector2<int> rolebk;
int maxmedal = 0;
elona_vector2<int> medalbk;



void _update_dungeon_level()
{
    if (game_data.current_dungeon_level >
        area_data[game_data.current_map].deepest_level)
    {
        game_data.current_dungeon_level =
            area_data[game_data.current_map].deepest_level;
    }
    if (game_data.current_dungeon_level <
        area_data[game_data.current_map].danger_level)
    {
        game_data.current_dungeon_level =
            area_data[game_data.current_map].danger_level;
    }
    if (game_data.deepest_dungeon_level < game_data.current_dungeon_level)
    {
        if (game_data.current_map != mdata_t::MapId::shelter_)
        {
            game_data.deepest_dungeon_level = game_data.current_dungeon_level;
        }
    }
    if (area_data[game_data.current_map].visited_deepest_level <
        game_data.current_dungeon_level)
    {
        area_data[game_data.current_map].visited_deepest_level =
            game_data.current_dungeon_level;
    }
}



void _update_pets_moving_status()
{
    for (auto&& ally : cdata.allies())
    {
        if (ally.current_map != 0 && ally.current_map == game_data.current_map)
        {
            if (ally.state() == Character::State::pet_moving_to_map)
            {
                ally.set_state(Character::State::alive);
            }
        }
    }
}



void _prompt_initialize_map()
{
    if (save_fs_exists(fs::u8path(u8"mdata_"s + mid + u8".s2")))
    {
        int stat = dialog(i18n::s.get("core.map.prompt_initialize"), 3);
        if (stat == 6)
        {
            ctrl_file_map_delete();
        }
    }
}



void _clear_map_and_objects()
{
    map_data.next_regenerate_date = 0;
    for (auto&& cnt : cdata.others())
    {
        cnt.set_state(Character::State::empty);
    }
    for (auto&& inv : g_inv.map_local())
    {
        for (auto&& item : inv)
        {
            item->remove();
        }
    }

    map_data.clear();
}



void _init_map_data()
{
    map_data.current_dungeon_level = game_data.current_dungeon_level;
    map_data.atlas_number = area_data[game_data.current_map].tile_set;
    map_data.tileset = area_data[game_data.current_map].tile_type;
    map_data.type = area_data[game_data.current_map].type;
    map_data.turn_cost = area_data[game_data.current_map].turn_cost_base;
    map_data.refresh_type =
        area_data[game_data.current_map].is_generated_every_time ? 0 : 1;
    map_data.designated_spawns =
        area_data[game_data.current_map].default_ai_calm;
    map_data.indoors_flag = area_data[game_data.current_map].is_indoor ? 1 : 2;
}



void _reveal_map()
{
    for (int cnt = 0, cnt_end = (map_data.height); cnt < cnt_end; ++cnt)
    {
        y = cnt;
        for (int cnt = 0, cnt_end = (map_data.width); cnt < cnt_end; ++cnt)
        {
            cell_data.at(cnt, y).chip_id_memory =
                cell_data.at(cnt, y).chip_id_actual;
        }
    }
}



void _init_map_visibility()
{
    map_setfog();
    if (map_should_reveal_fog())
    {
        _reveal_map();
    }
}



void _relocate_overlapping_area(Area& area)
{
    for (int cnt = 0;; ++cnt)
    {
        dx = clamp(rnd(cnt / 4 + 1) + 1, 1, map_data.width);
        dy = clamp(rnd(cnt / 4 + 1) + 1, 1, map_data.height);
        x = area.position.x + rnd(dx(0)) - rnd(dx(0));
        y = area.position.y + rnd(dy) - rnd(dy);
        if (x < 0 || y < 0 || x >= map_data.width || y >= map_data.height)
        {
            continue;
        }
        if (33 <= cell_data.at(x, y).chip_id_actual &&
            cell_data.at(x, y).chip_id_actual < 66)
        {
            continue;
        }
        if (cell_data.at(x, y).chip_id_actual > 19)
        {
            continue;
        }
        i = 1;
        for (int cnt = 0, cnt_end = (300); cnt < cnt_end; ++cnt)
        {
            if (area_data[cnt].position.x == 0 ||
                area_data[cnt].position.y == 0 ||
                area_data[cnt].id == mdata_t::MapId::none)
            {
                continue;
            }
            if (x == area_data[cnt].position.x)
            {
                if (y == area_data[cnt].position.y)
                {
                    i = 0;
                    break;
                }
            }
        }
        if (i == 0)
        {
            continue;
        }
        dialog(i18n::s.get(
            "core.map.location_changed",
            mapname(p),
            area.position.x,
            area.position.y,
            x(0),
            y(0)));
        area.position.x = x;
        area.position.y = y;
        ++f;
        break;
    }
}



void _do_mapupdate_world_map()
{
    f = 0;
    i = 0;
    for (int cnt = 300; cnt < 500; ++cnt)
    {
        p = cnt;
        if (area_data[cnt].position.x == 0 || area_data[cnt].position.y == 0 ||
            area_data[cnt].id == mdata_t::MapId::none)
        {
            continue;
        }
        for (int cnt = 0; cnt < 300; ++cnt)
        {
            if (area_data[cnt].position.x == 0 ||
                area_data[cnt].position.y == 0 ||
                area_data[cnt].id == mdata_t::MapId::none)
            {
                continue;
            }
            if (area_data[p].position.x == area_data[cnt].position.x)
            {
                if (area_data[p].position.y == area_data[cnt].position.y)
                {
                    _relocate_overlapping_area(area_data[p]);
                }
            }
        }
    }
    map_global_prepare();
}



void _prepare_mapupdate()
{
    maxnpcbk = 0;
    DIM3(rolebk, 2, ELONA_MAX_CHARACTERS);
    for (auto&& cnt : cdata.all())
    {
        if (cnt.state() == Character::State::empty)
        {
            continue;
        }
        if (is_shopkeeper(cnt.role))
        {
            rolebk(0, maxnpcbk) = static_cast<int>(cnt.role);
            rolebk(1, maxnpcbk) = cnt.shop_rank;
            ++maxnpcbk;
        }
    }
    maxmedal = 0;
    DIM3(medalbk, 2, 30);
    for (int cnt = 0, cnt_end = (map_data.height); cnt < cnt_end; ++cnt)
    {
        y = cnt;
        for (int cnt = 0, cnt_end = (map_data.width); cnt < cnt_end; ++cnt)
        {
            x = cnt;
            if (cell_data.at(x, y).feats / 1000 % 100 == 32)
            {
                if (maxmedal < 30)
                {
                    medalbk(0, maxmedal) = x;
                    medalbk(1, maxmedal) = y;
                    ++maxmedal;
                }
            }
        }
    }
}



void _do_mapupdate()
{
    if (map_data.type == mdata_t::MapType::world_map)
    {
        _do_mapupdate_world_map();
    }
    mapupdate = 0;
    for (auto&& cnt : cdata.all())
    {
        if (cnt.state() == Character::State::empty)
        {
            continue;
        }
        if (is_shopkeeper(cnt.role))
        {
            int cnt2 = cnt.index;
            for (int cnt = 0, cnt_end = (maxnpcbk); cnt < cnt_end; ++cnt)
            {
                if (cdata[cnt2].role == static_cast<Role>(rolebk(0, cnt)))
                {
                    cdata[cnt2].shop_rank = rolebk(1, cnt);
                    rolebk(0, cnt) = 0;
                    rolebk(1, cnt) = 0;
                    break;
                }
            }
        }
    }
    for (int cnt = 0, cnt_end = (maxmedal); cnt < cnt_end; ++cnt)
    {
        cell_featset(medalbk(0, cnt), medalbk(1, cnt), tile_hidden, 32);
    }
}



void _proc_three_years_later()
{
    if (game_data.current_map == mdata_t::MapId::north_tyris)
    {
        if (game_data.quest_flags.main_quest == 180)
        {
            cdata.player().position = area_data[11].position;
            game_data.player_next_move_direction = 1;
            game_data.player_x_on_map_leave = -1;
            Message::instance().buffered_message_begin(
                "  " + i18n::s.get("core.scenario.three_years_later"));
        }
    }
}



void _update_adventurer(Character& adv)
{
    if (adv.state() != Character::State::adventurer_in_other_map)
    {
        return;
    }
    if (adv.is_contracting())
    {
        adv.relationship = 10;
        adv.current_map = game_data.current_map;
    }
    else
    {
        if (adv.current_map != game_data.current_map)
        {
            return;
        }
        if (map_data.type != mdata_t::MapType::town &&
            map_data.type != mdata_t::MapType::guild)
        {
            return;
        }
        if (game_data.current_dungeon_level != 1)
        {
            return;
        }
    }
    if (game_data.current_map == mdata_t::MapId::arena ||
        game_data.current_map == mdata_t::MapId::pet_arena)
    {
        return;
    }
    adv.set_state(Character::State::alive);
    if (adv.is_contracting() == 1)
    {
        cxinit = cdata.player().position.x;
        cyinit = cdata.player().position.y;
        chara_place(adv);
    }
    else
    {
        cxinit = -1;
        chara_place(adv);
        adv.hp = adv.max_hp;
        adv.mp = adv.max_mp;
    }
    chara_refresh(adv);
}



void _update_adventurers()
{
    for (auto&& adv : cdata.adventurers())
    {
        _update_adventurer(adv);
    }
}



bool _should_regenerate_map()
{
    return game_data.date.hours() >= map_data.next_regenerate_date &&
        map_data.should_regenerate == 0 && map_data.next_regenerate_date != 0 &&
        game_data.current_dungeon_level == 1;
}



void _regenerate_map()
{
    if (game_data.current_map == mdata_t::MapId::lumiest)
    {
        map_reload(u8"lumiest"s);
    }
    if (game_data.current_map == mdata_t::MapId::vernis)
    {
        map_reload(u8"vernis"s);
    }
    if (game_data.current_map == mdata_t::MapId::palmia)
    {
        map_reload(u8"palmia"s);
    }
    if (game_data.current_map == mdata_t::MapId::port_kapul)
    {
        map_reload(u8"kapul"s);
    }
    if (game_data.current_map == mdata_t::MapId::yowyn)
    {
        map_reload(u8"yowyn"s);
    }
    if (game_data.current_map == mdata_t::MapId::derphy)
    {
        map_reload(u8"rogueden"s);
    }
    if (game_data.current_map == mdata_t::MapId::noyel)
    {
        if (game_data.date.month == 12)
        {
            if (!area_data[game_data.current_map].christmas_festival)
            {
                area_data[game_data.current_map].christmas_festival = true;
                map_reload_noyel();
            }
            map_reload(u8"noyel_fest"s);
        }
        else
        {
            if (area_data[game_data.current_map].christmas_festival)
            {
                area_data[game_data.current_map].christmas_festival = false;
                map_reload_noyel();
            }
            map_reload(u8"noyel"s);
        }
        game_data.released_fire_giant = 0;
    }
}



void _relocate_character(Character& chara)
{
    for (int cnt = 0;; ++cnt)
    {
        x = chara.position.x + rnd((cnt / 2 + 2)) - rnd((cnt / 2 + 2));
        y = chara.position.y + rnd((cnt / 2 + 2)) - rnd((cnt / 2 + 2));
        if (cnt > 100)
        {
            // After 100 failed tries, try any position in the map.
            x = rnd(map_data.width);
            y = rnd(map_data.height);
        }
        if (cnt > 1000)
        {
            // Give up.
            break;
        }
        cell_check(x, y);
        if (cellaccess == 1)
        {
            chara.position.x = x;
            chara.position.y = y;
            break;
        }
    }
}



bool _position_blocked(Character& chara)
{
    cell_check(chara.position.x, chara.position.y);
    return cell_data.at(chara.position.x, chara.position.y)
               .chara_index_plus_one != 0 ||
        cellaccess != 1;
}



void _clear_chara_indices_in_map()
{
    for (int cnt = 0, cnt_end = (map_data.height); cnt < cnt_end; ++cnt)
    {
        y = cnt;
        for (int cnt = 0, cnt_end = (map_data.width); cnt < cnt_end; ++cnt)
        {
            cell_data.at(cnt, y).chara_index_plus_one = 0;
        }
    }
}



void _refresh_map_character_other(Character& chara)
{
    chara.hp = chara.max_hp;
    chara.mp = chara.max_mp;
    chara.insanity = 0;

    if (map_data.designated_spawns == 1)
    {
        chara.position = chara.initial_position;
    }
    if (chara.is_quest_target() == 0)
    {
        chara.hate = 0;
        chara.relationship = chara.original_relationship;
    }
    if (chara.role == Role::guard)
    {
        if (cdata.player().karma < -30)
        {
            if (cdata.player().is_incognito() == 0)
            {
                chara.hate = 200;
                chara.relationship = -3;
            }
        }
    }
    if (map_is_town_or_guild())
    {
        chara.sleep = 0;
        if (game_data.date.hour >= 22 || game_data.date.hour < 7)
        {
            if (rnd(6) == 0)
            {
                chara.sleep = rnd(400);
            }
        }
    }
}



void _level_up_if_guard(Character& chara)
{
    if (chara.role == Role::guard)
    {
        if (cdata.player().karma < -30)
        {
            if (cdata.player().level > chara.level)
            {
                r2 = 1;
                gain_level(chara);
            }
        }
    }
}



void _refresh_map_character(Character& cnt)
{
    cnt.was_passed_item_by_you_just_now() = false;

    if (cnt.is_global())
    {
        if (mode == 11)
        {
            return;
        }
    }
    if (cnt.state() == Character::State::villager_dead)
    {
        if (game_data.date.hours() >= cnt.time_to_revive)
        {
            revive_player(cnt);
        }
        else
        {
            return;
        }
    }
    if (cnt.state() != Character::State::alive)
    {
        return;
    }

    _level_up_if_guard(cnt);

    if (cnt.is_map_local())
    {
        _refresh_map_character_other(cnt);
    }
    if (cnt.is_player() || game_data.mount != cnt.index)
    {
        if (_position_blocked(cnt))
        {
            _relocate_character(cnt);
        }
    }
    if (cnt.is_ridden() == 0)
    {
        cell_data.at(cnt.position.x, cnt.position.y).chara_index_plus_one =
            cnt.index + 1;
    }
}



void _refresh_map_characters()
{
    for (auto&& cnt : cdata.all())
    {
        _refresh_map_character(cnt);
    }
}



void _adjust_spawns()
{
    for (auto&& cnt : cdata.all())
    {
        if (cnt.state() == Character::State::alive)
        {
            if (cnt.position.x < 0 || cnt.position.x >= map_data.width ||
                cnt.position.y < 0 || cnt.position.y >= map_data.height)
            {
                cnt.position.x = 0;
                cnt.position.y = 0;
            }
        }
    }
    if (map_data.type != mdata_t::MapType::player_owned)
    {
        if (map_data.max_item_count != 0)
        {
            map_data.max_item_count = 0;
        }
    }
    if (game_data.current_map == mdata_t::MapId::your_home)
    {
        area_data[game_data.current_map].danger_level = 0;
        area_data[game_data.current_map].deepest_level = 10;
        area_data[game_data.current_map].default_ai_calm = 1;
        map_data.designated_spawns = 1;
        event_add(17);
        calccosthire();
    }
}



void _update_quest_flags_any()
{
    if (game_data.quest_flags.main_quest == 9)
    {
        sceneid = 2;
        do_play_scene();
        game_data.quest_flags.main_quest = 10;
    }
    if (game_data.quest_flags.main_quest == 60)
    {
        sceneid = 5;
        do_play_scene();
        game_data.quest_flags.main_quest = 65;
    }
    if (game_data.quest_flags.main_quest == 110)
    {
        sceneid = 26;
        do_play_scene();
        game_data.quest_flags.main_quest = 115;
    }
    if (game_data.quest_flags.main_quest == 115)
    {
        if (game_data.quest_flags.magic_stone_of_fool +
                game_data.quest_flags.magic_stone_of_king +
                game_data.quest_flags.magic_stone_of_sage >=
            1)
        {
            sceneid = 28;
            do_play_scene();
            game_data.quest_flags.main_quest = 116;
        }
    }
    if (game_data.quest_flags.main_quest == 116)
    {
        if (game_data.quest_flags.magic_stone_of_fool +
                game_data.quest_flags.magic_stone_of_king +
                game_data.quest_flags.magic_stone_of_sage >=
            2)
        {
            sceneid = 29;
            do_play_scene();
            game_data.quest_flags.main_quest = 117;
        }
    }
    if (game_data.quest_flags.main_quest == 117)
    {
        if (game_data.quest_flags.magic_stone_of_fool +
                game_data.quest_flags.magic_stone_of_king +
                game_data.quest_flags.magic_stone_of_sage >=
            3)
        {
            sceneid = 30;
            do_play_scene();
            game_data.quest_flags.main_quest = 120;
        }
    }
}



void _update_quest_flags_lesimas()
{
    if (game_data.quest_flags.main_quest == 10)
    {
        sceneid = 3;
        do_play_scene();
        game_data.quest_flags.main_quest = 20;
    }
    if (game_data.current_dungeon_level == 4)
    {
        if (game_data.quest_flags.main_quest == 65)
        {
            sceneid = 7;
            do_play_scene();
            game_data.quest_flags.main_quest = 70;
        }
    }
    if (game_data.current_dungeon_level == 7)
    {
        if (game_data.quest_flags.main_quest == 70)
        {
            sceneid = 15;
            do_play_scene();
            game_data.quest_flags.main_quest = 75;
        }
    }
    if (game_data.current_dungeon_level == 10)
    {
        if (game_data.quest_flags.main_quest == 75)
        {
            sceneid = 16;
            do_play_scene();
            game_data.quest_flags.main_quest = 80;
        }
    }
    if (game_data.current_dungeon_level == 14)
    {
        if (game_data.quest_flags.main_quest == 80)
        {
            sceneid = 17;
            do_play_scene();
            game_data.quest_flags.main_quest = 85;
        }
    }
    if (game_data.current_dungeon_level == 16)
    {
        if (game_data.quest_flags.main_quest == 85)
        {
            sceneid = 24;
            do_play_scene();
            game_data.quest_flags.main_quest = 90;
        }
    }
    if (game_data.current_dungeon_level == 26)
    {
        if (game_data.quest_flags.main_quest == 125)
        {
            sceneid = 33;
            do_play_scene();
            game_data.quest_flags.main_quest = 130;
        }
    }
    if (game_data.current_dungeon_level == 28)
    {
        if (game_data.quest_flags.main_quest == 130)
        {
            sceneid = 35;
            do_play_scene();
            game_data.quest_flags.main_quest = 135;
        }
    }
    if (game_data.current_dungeon_level == 31)
    {
        if (game_data.quest_flags.main_quest == 135)
        {
            sceneid = 40;
            do_play_scene();
            game_data.quest_flags.main_quest = 140;
        }
    }
    if (game_data.current_dungeon_level == 35)
    {
        if (game_data.quest_flags.main_quest == 140)
        {
            sceneid = 60;
            do_play_scene();
            game_data.quest_flags.main_quest = 145;
        }
    }
    if (game_data.current_dungeon_level == 38)
    {
        if (game_data.quest_flags.main_quest == 145)
        {
            sceneid = 70;
            do_play_scene();
            game_data.quest_flags.main_quest = 150;
        }
    }
    if (game_data.current_dungeon_level == 42)
    {
        if (game_data.quest_flags.main_quest == 150)
        {
            sceneid = 90;
            do_play_scene();
            game_data.quest_flags.main_quest = 160;
        }
    }
}



void _update_paels_mom()
{
    if (const auto lily = chara_find("core.lily"))
    {
        if (game_data.quest_flags.pael_and_her_mom >= 10)
        {
            lily->image = 360;
            lily->portrait = "";
        }
    }
}



void _proc_guild_entry_events()
{
    if (area_data[game_data.current_map].id == mdata_t::MapId::lumiest)
    {
        if (game_data.current_dungeon_level == 3)
        {
            event_add(22, game_data.guild.belongs_to_mages_guild);
        }
    }
    if (area_data[game_data.current_map].id == mdata_t::MapId::derphy)
    {
        if (game_data.current_dungeon_level == 3)
        {
            event_add(22, game_data.guild.belongs_to_thieves_guild);
        }
    }
    if (area_data[game_data.current_map].id == mdata_t::MapId::port_kapul)
    {
        if (game_data.current_dungeon_level == 3)
        {
            event_add(22, game_data.guild.belongs_to_fighters_guild);
        }
    }
}



void _update_quest_flags_vernis()
{
    if (game_data.quest_flags.main_quest == 0)
    {
        sceneid = 1;
        do_play_scene();
        game_data.quest_flags.main_quest = 9;
    }
    if (game_data.has_not_been_to_vernis == 0)
    {
        game_data.has_not_been_to_vernis = 1;
        event_add(12);
    }
}



void _update_quest_flags_palmia()
{
    if (game_data.quest_flags.main_quest == 30)
    {
        sceneid = 4;
        do_play_scene();
        game_data.quest_flags.main_quest = 40;
    }
    if (game_data.quest_flags.main_quest == 100)
    {
        sceneid = 25;
        do_play_scene();
        game_data.quest_flags.main_quest = 105;
    }
}



void _update_quest_flags_north_tyris()
{
    if (game_data.quest_flags.main_quest == 180)
    {
        sceneid = 100;
        do_play_scene();
        game_data.quest_flags.main_quest = 200;
        game_data.date.year += 3;
    }
}



void _proc_no_dungeon_master()
{
    if (game_data.current_dungeon_level ==
        area_data[game_data.current_map].deepest_level)
    {
        if (area_data[game_data.current_map].has_been_conquered == -1)
        {
            Message::instance().buffered_message_append(i18n::s.get(
                "core.map.no_dungeon_master", mapname(game_data.current_map)));
        }
    }
}



void _proc_map_hooks_1()
{
    _update_quest_flags_any();

    if (game_data.current_map == mdata_t::MapId::lesimas)
    {
        _update_quest_flags_lesimas();
    }
    if (area_data[game_data.current_map].id == mdata_t::MapId::noyel)
    {
        _update_paels_mom();
    }
    _proc_guild_entry_events();
    if (game_data.current_map == mdata_t::MapId::vernis)
    {
        _update_quest_flags_vernis();
    }
    if (game_data.current_map == mdata_t::MapId::palmia)
    {
        _update_quest_flags_palmia();
    }
    if (game_data.current_map == mdata_t::MapId::north_tyris)
    {
        _update_quest_flags_north_tyris();
    }
    if (area_data[game_data.current_map].id == mdata_t::MapId::random_dungeon)
    {
        _proc_no_dungeon_master();
    }

    // Work-around: shop's `cell_data` should be fixed before `cell_draw()` is
    // called.
    if (area_data[game_data.current_map].id == mdata_t::MapId::shop)
    {
        update_shop();
    }
}



void _notify_distance_traveled()
{
    p = game_data.date.hours() - game_data.departure_date;
    txt(i18n::s.get(
        "core.map.since_leaving.time_passed",
        p / 24,
        p % 24,
        mapname(game_data.left_town_map),
        cnvdate(game_data.departure_date, false)));
    p = 0;
    exp = cdata.player().level * game_data.distance_between_town *
            cdata.player().get_skill(182).level / 100 +
        1;
    for (auto&& chara : cdata.player_and_allies())
    {
        if (chara.state() != Character::State::alive)
        {
            continue;
        }
        if (!chara.is_player() && chara.current_map)
        {
            continue;
        }
        ++p;
        chara.experience += exp;
    }
    if (p == 1)
    {
        txt(i18n::s.get(
            "core.map.since_leaving.walked.you",
            game_data.distance_between_town));
    }
    else
    {
        txt(i18n::s.get(
            "core.map.since_leaving.walked.you_and_allies",
            game_data.distance_between_town));
    }
    chara_gain_skill_exp(
        cdata.player(),
        182,
        25 + game_data.distance_between_town * 2 / 3,
        0,
        1000);
    game_data.distance_between_town = 0;
}



void _remove_lomias_and_larnneire()
{
    if (const auto larnneire = chara_find("core.larnneire"))
    {
        chara_vanquish(*larnneire);
    }
    if (const auto lomias = chara_find("core.lomias"))
    {
        chara_vanquish(*lomias);
    }
}



void _remove_xabi()
{
    if (const auto xabi = chara_find("core.xabi"))
    {
        chara_vanquish(*xabi);
    }
}



void _update_quest_escort(int cnt2)
{
    for (auto&& ally : cdata.allies())
    {
        if (ally.state() == Character::State::alive)
        {
            if (ally.is_escorted() &&
                ally.id == int2charaid(quest_data[cnt2].extra_info_2) &&
                quest_data[cnt2].extra_info_1 == game_data.current_map)
            {
                event_add(16, cnt2, ally.index);
                ally.is_escorted() = false;
                break;
            }
        }
    }
}



void _spawn_museum_or_shop_crowds()
{
    for (int cnt = 0; cnt < 5; ++cnt)
    {
        monster_respawn();
    }
}



void _update_quest_escorts()
{
    for (int cnt = 0, cnt_end = (game_data.number_of_existing_quests);
         cnt < cnt_end;
         ++cnt)
    {
        if (quest_data[cnt].id == 1007 && quest_data[cnt].progress == 1)
        {
            _update_quest_escort(cnt);
        }
    }
}



void _set_livestock_relations()
{
    for (auto&& cnt : cdata.all())
    {
        if (cnt.is_livestock() == 1)
        {
            cnt.hate = 0;
            cnt.relationship = -1;
            cnt.original_relationship = -1;
        }
    }
}



void _proc_map_hooks_2()
{
    if (game_data.current_map == mdata_t::MapId::your_home)
    {
        if (game_data.quest_flags.main_quest != 0)
        {
            _remove_lomias_and_larnneire();
        }
    }
    if (game_data.current_map == mdata_t::MapId::palmia)
    {
        if (game_data.quest_flags.main_quest >= 90)
        {
            _remove_xabi();
        }
    }
    if (map_data.type == mdata_t::MapType::town)
    {
        _update_quest_escorts();
    }
    if (area_data[game_data.current_map].is_museum_or_shop())
    {
        _spawn_museum_or_shop_crowds();
    }
    if (map_data.refresh_type == 1)
    {
        foods_get_rotten();
    }
    if (area_data[game_data.current_map].id == mdata_t::MapId::museum)
    {
        update_museum();
    }
    if (game_data.current_map == mdata_t::MapId::your_home)
    {
        building_update_home_rank();
    }
    if (area_data[game_data.current_map].id == mdata_t::MapId::ranch)
    {
        _set_livestock_relations();
    }
    if (map_data.type == mdata_t::MapType::world_map)
    {
        maybe_show_ex_help(2);
    }
    if (map_data.type == mdata_t::MapType::town)
    {
        maybe_show_ex_help(3);
    }
    if (game_data.current_map == mdata_t::MapId::shelter_)
    {
        maybe_show_ex_help(14);
    }
    if (map_is_town_or_guild() ||
        game_data.current_map == mdata_t::MapId::your_home)
    {
        if (game_data.distance_between_town >= 16)
        {
            _notify_distance_traveled();
        }
    }
    if (game_data.current_map == mdata_t::MapId::quest)
    {
        quest_enter_map();
    }
}



void _update_aggro_and_crowd_density()
{
    game_data.crowd_density = 0;
    for (auto&& cnt : cdata.all())
    {
        cnt.turn_cost = 0;
        if (cnt.id == CharaId::user) // cnpc
        {
            // Vanilla-compatible CNPC is not supported now.
        }
        if (noaggrorefresh == 0)
        {
            cnt.enemy_id = 0;
            cnt.hate = 0;
        }
        cnt.vision_flag = 0;
        if (cnt.state() != Character::State::empty)
        {
            modify_crowd_density(cnt.index, 1);
        }
    }
}



void _init_tileset_minimap_and_scroll()
{
    scx = cdata.player().position.x;
    scy = cdata.player().position.y;
    msync = 1;
    draw_prepare_map_chips();
    ui_initialize_minimap();
    update_scrolling_info();
}



void _initialize_map_local_handles()
{
    lua::lua->get_mod_manager().clear_map_local_stores();
    lua::lua->get_handle_manager().clear_map_local_handles();
}



void _generate_new_map()
{
    noaggrorefresh = 0;

    if (mapupdate == 1)
    {
        // Backup character roles/shop ranks/medal locations before initializing
        // map from a template.
        _prepare_mapupdate();
    }

    // Since a new map is about to be created, clear any Lua handles left over
    // from the previous map. If the map were loaded from a save file, they
    // would have been already cleared by ctrl_file.
    _initialize_map_local_handles();

    _clear_map_and_objects();
    _init_map_data();

    if (mapupdate)
    {
        randomize(
            game_data.random_seed + game_data.current_map * 1000 +
            game_data.current_dungeon_level);
    }

    // Initialize map-specific features.
    initialize_map_from_map_type();

    _init_map_visibility();

    if (mapupdate == 1)
    {
        // Restore character roles/shop ranks/medal locations.
        _do_mapupdate();
        mapupdate = 0;
    }

    randomize();

    map_data.regenerate_count = game_data.map_regenerate_count;
    map_data.mefs_loaded_flag = 1;
}



void _proc_map_refresh()
{
    _proc_three_years_later();

    _update_adventurers();

    if (map_data.refresh_type == 1)
    {
        if (_should_regenerate_map())
        {
            _regenerate_map();
        }

        _clear_chara_indices_in_map();

        _refresh_map_characters();
    }
}



int initialize_map_pregenerate()
{
    clear_damage_popups();

    mapupdate = 0;

    _update_dungeon_level();

    _update_pets_moving_status();

    mid = ""s + game_data.current_map + u8"_"s +
        (100 + game_data.current_dungeon_level);

    if (mode == 3)
    {
        ctrl_file_map_read();
        ctrl_file_map_items_read(fs::u8path(u8"inv_"s + mid + u8".s2"));
        return 2;
    }

    if (getkey(snail::Key::backspace))
    {
        _prompt_initialize_map();
    }

    if (save_fs_exists(fs::u8path(u8"mdata_"s + mid + u8".s2")))
    {
        ctrl_file_map_read();
        if (map_data.refresh_type == 0)
        {
            return 0;
        }
        if (map_data.regenerate_count != game_data.map_regenerate_count ||
            (game_data.reset_world_map_in_diastrophism_flag == 1 &&
             map_data.type == mdata_t::MapType::world_map))
        {
            if (map_data.type == mdata_t::MapType::town ||
                map_data.type == mdata_t::MapType::guild ||
                map_data.type == mdata_t::MapType::shelter ||
                map_data.type == mdata_t::MapType::world_map)
            {
                mapupdate = 1;
                return 0;
            }
        }
        ctrl_file_map_items_read(fs::u8path(u8"inv_"s + mid + u8".s2"));
        if (mode == 2)
        {
            map_placeplayer();
        }
        return 1;
    }

    return 0;
}



// @see _update_save_data_16() in save_update.cpp
void migrate_old_save_v17()
{
    for (int y = 0; y < map_data.height; ++y)
    {
        for (int x = 0; x < map_data.width; ++x)
        {
            if (cell_data.at(x, y).item_info_actual.stack_count() != -4 ||
                cell_data.at(x, y).item_info_memory.stack_count() != -4)
            {
                return; // It's new format.
            }
        }
    }

    // Update old format.
    for (int y = 0; y < map_data.height; ++y)
    {
        for (int x = 0; x < map_data.width; ++x)
        {
            cell_data.at(x, y).item_info_actual.clear();
            cell_data.at(x, y).item_info_memory.clear();
        }
    }
    for (const auto& item : g_inv.ground())
    {
        cell_refresh(item->position().x, item->position().y);
    }
    for (int y = 0; y < map_data.height; ++y)
    {
        for (int x = 0; x < map_data.width; ++x)
        {
            cell_data.at(x, y).item_info_memory =
                cell_data.at(x, y).item_info_actual;
        }
    }
}

} // namespace



TurnResult initialize_map()
{
    bool was_generated = false;

    const auto stat = initialize_map_pregenerate();

    migrate_old_save_v17();

    if (stat == 0)
    {
        _generate_new_map();
        was_generated = true;
    }
    if (stat == 0 || stat == 1)
    {
        _proc_map_refresh();
    }

    DIM4(efmap, 4, map_data.width, map_data.height);
    if (map_data.width == 0 || map_data.height == 0)
    {
        throw std::runtime_error{"failed to load map"};
    }
    map_proc_regen_and_update();

    _update_aggro_and_crowd_density();

    cdata.player().current_map = game_data.current_map;
    cdata.player().current_dungeon_level = game_data.current_dungeon_level;

    _init_tileset_minimap_and_scroll();

    if (map_data.type == mdata_t::MapType::town)
    {
        quest_refresh_list();
    }

    auto legacy_id = area_data[game_data.current_map].id;
    auto map_id =
        the_mapdef_db.get_id_from_legacy(legacy_id).value_or("").get();
    auto event =
        lua::MapInitializedEvent(was_generated, map_id, game_data.current_map);

    if (mode == 11)
    {
        // This result will be ignored by the caller.
        lua::lua->get_event_manager().trigger(event);
        return TurnResult::turn_begin;
    }

    // Check for main quest flags, guild entry, or no dungeon master.
    _proc_map_hooks_1();

    play_music();
    _adjust_spawns();
    noaggrorefresh = 0;
    if (area_data[game_data.current_map].type == mdata_t::MapType::world_map)
    {
        // initialize_cloud_data();
        map_global_proc_diastrophism();
    }
    if (mode == 3)
    {
        mode = 0;
        if (mapsubroutine == 0)
        {
            screenupdate = -1;
            update_entire_screen();
            Message::instance().buffered_message_end();
            screenupdate = -1;
            update_screen();
            lua::lua->get_event_manager().trigger(event);
            if (event_has_pending_events())
            {
                return TurnResult::turn_begin;
            }
            else
            {
                return TurnResult::pc_turn_user_error;
            }
        }
        else
        {
            mapsubroutine = 0;
            lua::lua->get_event_manager().trigger(event);
            // This result will be ignored by the caller.
            return TurnResult::turn_begin;
        }
    }
    wake_up();
    pcattacker = 0;
    cdata.player().enemy_id = 0;
    game_data.chara_last_attacked_by_player = 0;
    mode = 0;
    screenupdate = -1;
    update_entire_screen();
    Message::instance().buffered_message_end();

    // Check more main quest flags and run map-specific behaviors.
    _proc_map_hooks_2();

    lua::lua->get_event_manager().trigger(event);

    return TurnResult::turn_begin;
}

} // namespace elona

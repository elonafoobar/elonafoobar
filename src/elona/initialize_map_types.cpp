#include "area.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "ctrl_file.hpp"
#include "data/types/type_map.hpp"
#include "event.hpp"
#include "gdata.hpp"
#include "i18n.hpp"
#include "itemgen.hpp"
#include "lua_env/lua_class/lua_class_map_generator.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "mapgen.hpp"
#include "quest.hpp"
#include "text.hpp"
#include "variables.hpp"

namespace elona
{

static void _init_map_shelter()
{
}

static void _init_map_nefia()
{
    if (game_data.current_dungeon_level ==
        area_data[game_data.current_map].deepest_level)
    {
        event_add(4);
    }
}

static void _init_map_museum()
{
}

static void _init_map_shop()
{
}

static void _init_map_crop()
{
}

static void _init_map_ranch()
{
}

static void _init_map_your_dungeon()
{
}

static void _init_map_storage_house()
{
}

static void _init_map_test_site()
{
}

static void _init_map_lumiest_graveyard()
{
}

static void _init_map_jail()
{
}

static void _init_map_truce_ground()
{
}

static void _init_map_embassy()
{
}

static void _init_map_test_world_north_border()
{
}

static void _init_map_tyris_border()
{
}

static void _init_map_the_smoke_and_pipe()
{
}

static void _init_map_miral_and_garoks_workshop()
{
}

static void _init_map_mansion_of_younger_sister()
{
}

static void _init_map_cyber_dome()
{
}

static void _init_map_larna()
{
}

static void _init_map_arena()
{
    for (int cnt = 0; cnt < 16; ++cnt)
    {
        if (cdata[cnt].state() == Character::State::alive)
        {
            if (cdata[cnt].relationship == 10)
            {
                if (cnt != 0)
                {
                    cell_data.at(cdata[cnt].position.x, cdata[cnt].position.y)
                        .chara_index_plus_one = 0;
                    cdata[cnt].set_state(Character::State::pet_in_other_map);
                }
            }
        }
    }
    if (arenaop == 0)
    {
        fixlv = static_cast<Quality>(arenaop(2));
        chara_create(
            -1,
            arenaop(1),
            cdata.player().position.x - 1,
            cdata.player().position.y - 4);
        cdata[rc].hate = 30;
        cdata[rc].relationship = -3;
        cdata[rc].relationship = -3;
        cdata[rc].original_relationship = -3;
        cdata[rc].is_lord_of_dungeon() = true;
    }
    if (arenaop == 1)
    {
        for (int cnt = 0, cnt_end = (3 + rnd(4)); cnt < cnt_end; ++cnt)
        {
            flt(arenaop(1), Quality::good);
            chara_create(
                -1,
                0,
                cdata.player().position.x - 1,
                cdata.player().position.y - 5);
            cdata[rc].relationship = -3;
            cdata[rc].original_relationship = -3;
            cdata[rc].hate = 30;
            cdata[rc].relationship = -3;
            cdata[rc].is_lord_of_dungeon() = true;
            if (cdata[rc].level > arenaop(1) || cdata[rc].relationship != -3)
            {
                chara_vanquish(rc);
                --cnt;
                continue;
            }
        }
    }
}

static void _init_map_pet_arena()
{
    for (int cnt = 0; cnt < 16; ++cnt)
    {
        if (cnt == 0 || cnt == 56)
        {
            continue;
        }
        if (followerin(cnt) == 0)
        {
            cdata[cnt].set_state(Character::State::pet_dead);
            cdata[cnt].position.x = 0;
            cdata[cnt].position.y = 0;
        }
        else
        {
            cdata[cnt].set_state(Character::State::alive);
        }
    }
    // map_placeplayer();
    petarenawin = 0;
    for (int cnt = 0, cnt_end = (arenaop(1)); cnt < cnt_end; ++cnt)
    {
        flt(arenaop(2), calcfixlv(Quality::good));
        chara_create(-1, 0, -3, 0);
        cell_data.at(cdata[rc].position.x, cdata[rc].position.y)
            .chara_index_plus_one = 0;
        f = 1;
        if (arenaop == 0)
        {
            if (cdata[rc].level < arenaop(2) / 2)
            {
                f = 0;
            }
        }
        if (cdata[rc].relationship != -3)
        {
            f = 0;
        }
        if (f == 0)
        {
            chara_vanquish(rc);
            --cnt;
            continue;
        }
        map_placearena(rc, true);
        if (cnt == 0)
        {
            enemyteam = rc;
        }
    }
    for (auto&& cnt : cdata.others())
    {
        if (cnt.relationship == -3)
        {
            cnt.has_been_used_stethoscope() = true;
        }
    }
}

static void _init_map_fort_of_chaos_beast()
{
}

static void _init_map_fort_of_chaos_machine()
{
}

static void _init_map_fort_of_chaos_collapsed()
{
}

static void _initialize_home_mdata()
{
    switch (game_data.home_scale)
    {
    case 0: game_data.basic_point_of_home_rank = 1000; break;
    case 1: game_data.basic_point_of_home_rank = 3000; break;
    case 2: game_data.basic_point_of_home_rank = 5000; break;
    case 3: game_data.basic_point_of_home_rank = 7000; break;
    case 4: game_data.basic_point_of_home_rank = 8000; break;
    case 5: game_data.basic_point_of_home_rank = 10000; break;
    }
}

static void _init_map_your_home()
{
    map_initcustom(u8"home"s + game_data.home_scale);
    map_data.bgm = 68;
    game_data.entrance_type = 4;
    map_placeplayer();
    map_data.user_map_flag = 0;
    map_data.tileset = 3;
    if (game_data.current_dungeon_level == 1)
    {
        if (game_data.home_scale != 0)
        {
            // Move existing characters/items to the center of the
            // map if the home was upgraded.
            ctrl_file(
                FileOperation2::map_items_read, u8"inv_"s + mid + u8".s2");
            for (const auto& cnt : items(-1))
            {
                if (inv[cnt].number() == 0)
                {
                    continue;
                }
                inv[cnt].position.x = map_data.width / 2;
                inv[cnt].position.y = map_data.height / 2;
                cell_refresh(inv[cnt].position.x, inv[cnt].position.y);
            }
            ctrl_file(FileOperation::map_home_upgrade);
            for (auto&& cnt : cdata.others())
            {
                cnt.position.x = map_data.width / 2;
                cnt.position.y = map_data.height / 2;
                cnt.initial_position.x = map_data.width / 2;
                cnt.initial_position.y = map_data.height / 2;
            }
        }
    }

    _initialize_home_mdata();
}

static void _init_map_north_tyris()
{
}

static void _init_map_south_tyris()
{
}

static void _init_map_test_world()
{
}

static void _init_map_derphy()
{
}

static void _init_map_palmia()
{
    if (game_data.quest_flags.mias_dream == 1000)
    {
        flt();
        chara_create(-1, 246, 42, 11);
        cdata[rc].character_role = 3;
    }
}

static void _init_map_lumiest_town()
{
    if (game_data.quest_flags.sewer_sweeping)
    {
        cell_featset(18, 45, tile_downstairs, 11, 20);
    }
}

static void _init_map_lumiest()
{
    if (game_data.current_dungeon_level == 1)
    {
        _init_map_lumiest_town();
    }
}

static void _init_map_yowyn_town()
{
    if (game_data.quest_flags.cat_house)
    {
        cell_featset(23, 22, tile_downstairs, 11, 3);
    }
}

static void _init_map_yowyn()
{
    if (game_data.current_dungeon_level == 1)
    {
        _init_map_yowyn_town();
    }
}

static void _init_map_noyel()
{
    flt();
    chara_create(-1, 202, 46, 18);
    game_data.fire_giant = rc;
    cdata[rc].character_role = 3;

    if (game_data.quest_flags.pael_and_her_mom != 1001)
    {
        flt();
        chara_create(-1, 222, 19, 2);
        cdata[rc].character_role = 3;
    }
}

static void _init_map_port_kapul_doom_ground()
{
    game_data.quest_flags.duration_of_kamikaze_attack = 0;
}

static void _init_map_port_kapul()
{
    if (game_data.current_dungeon_level == 25)
    {
        _init_map_port_kapul_doom_ground();
    }
}

static void _init_map_vernis_town()
{
    if (game_data.quest_flags.thieves_hideout)
    {
        cell_featset(48, 5, tile_downstairs, 11, 4);
    }

    if (game_data.quest_flags.puppys_cave == 1000)
    {
        flt();
        chara_create(-1, 225, 31, 4);
        cdata[rc].character_role = 3;
    }
}

static void _init_map_vernis()
{
    if (game_data.current_dungeon_level == 1)
    {
        _init_map_vernis_town();
    }
}

static void _init_map_fields_maybe_generate_encounter()
{
    if (encounter == 0)
    {
        for (int cnt = 0, cnt_end = (map_data.max_crowd_density + 1);
             cnt < cnt_end;
             ++cnt)
        {
            map_set_chara_generation_filter();
            flt();
            chara_create(-1, 0, -3, 0);
        }
    }
    if (encounter == 4)
    {
        map_data.max_crowd_density = 0;
        flt();
        initlv = encounterlv;
        chara_create(
            -1, 302, cdata.player().position.x, cdata.player().position.y);
        for (int cnt = 0, cnt_end = (6 + rnd(6)); cnt < cnt_end; ++cnt)
        {
            flt();
            initlv = encounterlv + rnd(10);
            chara_create(-1, 303 + rnd(3), 14, 11);
            cdatan(0, rc) += u8" Lv"s + cdata[rc].level;
        }
        gdatan(1) = random_title(RandomTitleType::party);
        event_add(23);
    }
    if (encounter == 3)
    {
        map_data.max_crowd_density = 0;
        map_data.type = static_cast<int>(mdata_t::MapType::temporary);
        rq = encounterref;
        game_data.executing_immediate_quest_type = 1007;
        game_data.executing_immediate_quest_show_hunt_remain = 1;
        game_data.executing_immediate_quest = rq;
        game_data.executing_immediate_quest_status = 1;
        p = rnd(3) + 5;
        for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
        {
            flt(quest_data[rq].difficulty, Quality::great);
            int stat = chara_create(
                -1, 0, cdata.player().position.x, cdata.player().position.y);
            if (stat != 0)
            {
                cdata[rc].hate = 30;
                cdata[rc].relationship = -3;
                cdata[rc].original_relationship = -3;
            }
        }
    }
    if (encounter == 2)
    {
        flt();
        chara_create(-1, 1, 10, 11);
        cdata[rc].character_role = 1010;
        cdata[rc].shop_rank = encounterlv;
        cdatan(0, rc) = i18n::s.get(
            "core.locale.chara.job.wandering_vendor", cdatan(0, rc));
        generatemoney(rc);
        for (int cnt = 0, cnt_end = (encounterlv / 2 + 1); cnt < cnt_end; ++cnt)
        {
            r2 = 1;
            gain_level(cdata[rc]);
        }
        event_add(11);
        for (int cnt = 0, cnt_end = (6 + rnd(6)); cnt < cnt_end; ++cnt)
        {
            flt();
            initlv = encounterlv + rnd(10);
            chara_create(-1, 159 + rnd(3), 14, 11);
            cdata[rc].character_role = 16;
            cdatan(0, rc) += u8" Lv"s + cdata[rc].level;
        }
    }
    if (encounter == 1)
    {
        p = rnd(9);
        if (cdata.player().level <= 5)
        {
            p = rnd(3);
        }
        for (int cnt = 0, cnt_end = (2 + p); cnt < cnt_end; ++cnt)
        {
            flt(calcobjlv(encounterlv), calcfixlv(Quality::bad));
            if (game_data.weather == 1)
            {
                if ((33 > game_data.stood_world_map_tile ||
                     game_data.stood_world_map_tile >= 66) &&
                    rnd(3) == 0)
                {
                    fixlv = Quality::godly;
                }
            }
            if (cnt < 4)
            {
                chara_create(
                    -1,
                    0,
                    cdata.player().position.x,
                    cdata.player().position.y);
            }
            else
            {
                chara_create(-1, 0, -3, 0);
            }
            cdata[rc].hate = 30;
        }
    }
    encounter = 0;
}

static void _init_map_fields()
{
    _init_map_fields_maybe_generate_encounter();
}

static void _init_map_the_void()
{
    if (game_data.void_next_lord_floor == 0)
    {
        game_data.void_next_lord_floor =
            area_data[game_data.current_map].danger_level + 4;
    }
    if (game_data.void_next_lord_floor <= game_data.current_dungeon_level)
    {
        event_add(29);
    }
    else
    {
        area_data[game_data.current_map].has_been_conquered = 0;
    }
}

static void _init_map_lesimas()
{
    if (game_data.current_dungeon_level ==
        area_data[game_data.current_map].deepest_level)
    {
        map_initcustom(u8"lesimas_1"s);
        map_data.max_crowd_density = 0;
        map_data.refresh_type = 0;
        map_data.bgm = 66;
        mdatan(0) =
            i18n::s.get_enum_property("core.locale.map.unique", "the_depth", 3);
        if (game_data.quest_flags.main_quest < 170)
        {
            event_add(3);
        }
        x = 16;
        y = 13;
        cell_featset(x, y, tile_upstairs, 10);
        map_data.stair_up_pos = y * 1000 + x;
        map_placeplayer();
        if (npcmemory(0, 2) == 0)
        {
            flt();
            chara_create(-1, 2, 16, 6);
        }
        else if (npcmemory(0, 23) == 0)
        {
            flt();
            chara_create(-1, 23, 16, 6);
        }
    }
}

static void _init_map_tower_of_fire()
{
}

static void _init_map_crypt_of_the_damned()
{
}

static void _init_map_ancient_castle()
{
}

static void _init_map_dragons_nest()
{
}

static void _init_map_puppy_cave()
{
    if (game_data.current_dungeon_level ==
        area_data[game_data.current_map].deepest_level)
    {
        if (game_data.quest_flags.puppys_cave < 2)
        {
            if (chara_find_ally(225) == -1)
            {
                flt();
                chara_create(-1, 225, -3, 0);
                cdata[rc].is_not_attacked_by_enemy() = true;
            }
        }
    }
}

static void _init_map_minotaurs_nest()
{
    if (game_data.current_dungeon_level ==
        area_data[game_data.current_map].deepest_level)
    {
        if (game_data.quest_flags.minotaur_king < 2)
        {
            flt();
            chara_create(-1, 300, -3, 0);
        }
    }
}

static void _init_map_yeeks_nest()
{
    if (game_data.current_dungeon_level ==
        area_data[game_data.current_map].deepest_level)
    {
        if (game_data.quest_flags.novice_knight < 2)
        {
            flt();
            chara_create(-1, 242, -3, 0);
            tc = rc;
            for (int cnt = 0; cnt < 5; ++cnt)
            {
                flt();
                chara_create(
                    -1, 240, cdata[tc].position.x, cdata[tc].position.y);
            }
            for (int cnt = 0; cnt < 10; ++cnt)
            {
                flt();
                chara_create(
                    -1, 238, cdata[tc].position.x, cdata[tc].position.y);
                flt();
                chara_create(
                    -1, 237, cdata[tc].position.x, cdata[tc].position.y);
            }
        }
    }
}

static void _init_map_pyramid()
{
}


static void _generate_map_from_lua(const MapDefData& map)
{
    lua::MapGenerator generator{};

    map.generator.call(generator);
}

void initialize_map_from_map_type()
{
    using namespace mdata_t;
    if (game_data.current_map == MapId::your_home)
    {
        if (mdatan(0) == ""s ||
            mdatan(0) ==
                i18n::s.get_enum_property("core.locale.map.unique", "name", 4))
        {
            mdatan(0) =
                i18n::s.get_enum_property("core.locale.map.unique", "name", 7);
        }
    }
    else
    {
        mdatan(0) = mapname(game_data.current_map);
    }
    // In most cases the area's map ID will be the same as
    // game_data.current_map. However, multiple player-owned areas can share
    // the same map ID.

    int map_id = area_data[game_data.current_map].id;
    auto map = the_mapdef_db[map_id];

    if (!map)
    {
        txt("Could not find map with ID "s + map_id);
        return;
    }

    _generate_map_from_lua(**map);

    MapId map_id_b =
        static_cast<mdata_t::MapId>(area_data[game_data.current_map].id);

    switch (map_id_b)
    {
        // clang-format off
    case mdata_t::MapId::shelter_:                   _init_map_shelter();                   break;
    case mdata_t::MapId::random_dungeon:             _init_map_nefia();                     break;
    case mdata_t::MapId::museum:                     _init_map_museum();                    break;
    case mdata_t::MapId::shop:                       _init_map_shop();                      break;
    case mdata_t::MapId::crop:                       _init_map_crop();                      break;
    case mdata_t::MapId::ranch:                      _init_map_ranch();                     break;
    case mdata_t::MapId::your_dungeon:               _init_map_your_dungeon();              break;
    case mdata_t::MapId::storage_house:              _init_map_storage_house();             break;

    case mdata_t::MapId::quest:                      generate_random_nefia();               break;
    case mdata_t::MapId::test_site:                  _init_map_test_site();                 break;
    case mdata_t::MapId::lumiest_graveyard:          _init_map_lumiest_graveyard();         break;
    case mdata_t::MapId::jail:                       _init_map_jail();                      break;
    case mdata_t::MapId::truce_ground:               _init_map_truce_ground();              break;
    case mdata_t::MapId::embassy:                    _init_map_embassy();                   break;
    case mdata_t::MapId::test_world_north_border:    _init_map_test_world_north_border();   break;
    case mdata_t::MapId::north_tyris_south_border:
    case mdata_t::MapId::south_tyris_north_border:
        _init_map_tyris_border();
        break;
    case mdata_t::MapId::the_smoke_and_pipe:         _init_map_the_smoke_and_pipe();        break;
    case mdata_t::MapId::miral_and_garoks_workshop:  _init_map_miral_and_garoks_workshop(); break;
    case mdata_t::MapId::mansion_of_younger_sister:  _init_map_mansion_of_younger_sister(); break;
    case mdata_t::MapId::cyber_dome:                 _init_map_cyber_dome();                break;
    case mdata_t::MapId::larna:                      _init_map_larna();                     break;
    case mdata_t::MapId::arena:                      _init_map_arena();                     break;
    case mdata_t::MapId::pet_arena:                  _init_map_pet_arena();                 break;
    case mdata_t::MapId::fort_of_chaos_beast:        _init_map_fort_of_chaos_beast();       break;
    case mdata_t::MapId::fort_of_chaos_machine:      _init_map_fort_of_chaos_machine();     break;
    case mdata_t::MapId::fort_of_chaos_collapsed:    _init_map_fort_of_chaos_collapsed();   break;
    case mdata_t::MapId::your_home:                  _init_map_your_home();                 break;
    case mdata_t::MapId::north_tyris:                _init_map_north_tyris();               break;
    case mdata_t::MapId::south_tyris:                _init_map_south_tyris();               break;
    case mdata_t::MapId::test_world:                 _init_map_test_world();                break;
    case mdata_t::MapId::derphy:                     _init_map_derphy();                    break;
    case mdata_t::MapId::palmia:                     _init_map_palmia();                    break;
    case mdata_t::MapId::lumiest:                    _init_map_lumiest();                   break;
    case mdata_t::MapId::yowyn:                      _init_map_yowyn();                     break;
    case mdata_t::MapId::noyel:                      _init_map_noyel();                     break;
    case mdata_t::MapId::port_kapul:                 _init_map_port_kapul();                break;
    case mdata_t::MapId::vernis:                     _init_map_vernis();                    break;
    case mdata_t::MapId::debug_map:                  generate_debug_map();                  break;
    case mdata_t::MapId::fields:                     _init_map_fields();                    break;
    case mdata_t::MapId::the_void:                   _init_map_the_void();                  break;
    case mdata_t::MapId::lesimas:                    _init_map_lesimas();                   break;
    case mdata_t::MapId::tower_of_fire:              _init_map_tower_of_fire();             break;
    case mdata_t::MapId::crypt_of_the_damned:        _init_map_crypt_of_the_damned();       break;
    case mdata_t::MapId::ancient_castle:             _init_map_ancient_castle();            break;
    case mdata_t::MapId::dragons_nest:               _init_map_dragons_nest();              break;
    case mdata_t::MapId::puppy_cave:                 _init_map_puppy_cave();                break;
    case mdata_t::MapId::minotaurs_nest:             _init_map_minotaurs_nest();            break;
    case mdata_t::MapId::yeeks_nest:                 _init_map_yeeks_nest();                break;
    case mdata_t::MapId::pyramid:                    _init_map_pyramid();                   break;
    case mdata_t::MapId::mountain_pass:              generate_random_nefia();               break;
    case mdata_t::MapId::show_house:
    case mdata_t::MapId::none:
    default: break;
        // clang-format on
    }
}

} // namespace elona

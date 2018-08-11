#include <iostream>
#include "ability.hpp"
#include "audio.hpp"
#include "building.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "config.hpp"
#include "ctrl_file.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "event.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "lua_env/event_manager.hpp"
#include "lua_env/lua_env.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "mapgen.hpp"
#include "quest.hpp"
#include "random.hpp"
#include "ui.hpp"
#include "variables.hpp"


namespace elona
{

turn_result_t initialize_map()
{
    int maxnpcbk = 0;
    elona_vector2<int> rolebk;
    int maxmedal = 0;
    elona_vector2<int> medalbk;
    int noaggrorefresh = 0;
    bool loaded_from_file = true;

    clear_damage_popups();

label_17401:
    mapupdate = 0;
    if (gdata_current_dungeon_level > adata(10, gdata_current_map))
    {
        gdata_current_dungeon_level = adata(10, gdata_current_map);
    }
    if (gdata_current_dungeon_level < adata(17, gdata_current_map))
    {
        gdata_current_dungeon_level = adata(17, gdata_current_map);
    }
    if (gdata_deepest_dungeon_level < gdata_current_dungeon_level)
    {
        if (gdata_current_map != mdata_t::map_id_t::shelter_)
        {
            gdata_deepest_dungeon_level = gdata_current_dungeon_level;
        }
    }
    if (adata(6, gdata_current_map) < gdata_current_dungeon_level)
    {
        adata(6, gdata_current_map) = gdata_current_dungeon_level;
    }
    for (int cnt = 0; cnt < 16; ++cnt)
    {
        if (cnt == 0)
        {
            continue;
        }
        if (cdata[cnt].current_map != 0)
        {
            if (cdata[cnt].current_map == gdata_current_map)
            {
                if (cdata[cnt].state() == character::state_t::pet_moving_to_map)
                {
                    cdata[cnt].set_state(character::state_t::alive);
                }
            }
        }
    }
    mid =
        ""s + gdata_current_map + u8"_"s + (100 + gdata_current_dungeon_level);
    if (mode == 3)
    {
        lua::lua->get_handle_manager().clear_map_local_handles();
        ctrl_file(file_operation_t::_1);
        ctrl_file(file_operation2_t::_3, u8"inv_"s + mid + u8".s2");
        goto label_1744_internal;
    }
    if (getkey(snail::key::backspace))
    {
        tmpload(filesystem::u8path(u8"mdata_"s + mid + u8".s2"));
        if (fs::exists(filesystem::dir::tmp() / (u8"mdata_"s + mid + u8".s2")))
        {
            int stat =
                dialog(i18n::s.get("core.locale.map.prompt_initialize"), 3);
            if (stat == 6)
            {
                ctrl_file(file_operation_t::_11);
            }
        }
    }
    tmpload(filesystem::u8path(u8"mdata_"s + mid + u8".s2"));
    if (fs::exists(filesystem::dir::tmp() / (u8"mdata_"s + mid + u8".s2")))
    {
        lua::lua->get_handle_manager().clear_map_local_handles();
        ctrl_file(file_operation_t::_1);
        if (mdata_map_refresh_type == 0)
        {
            goto label_1741_internal;
        }
        if (mdata_map_regenerate_count != gdata(184)
            || (gdata(79) == 1
                && mdata_map_type == mdata_t::map_type_t::world_map))
        {
            if (mdata_map_type == mdata_t::map_type_t::town
                || mdata_map_type == mdata_t::map_type_t::guild
                || mdata_map_type == mdata_t::map_type_t::shelter
                || mdata_map_type == mdata_t::map_type_t::world_map)
            {
                mapupdate = 1;
                goto label_1741_internal;
            }
        }
        ctrl_file(file_operation2_t::_3, u8"inv_"s + mid + u8".s2");
        if (mode == 2)
        {
            map_placeplayer();
        }
        goto label_1742_internal;
    }
label_1741_internal:
    if (mapupdate == 1)
    {
        maxnpcbk = 0;
        DIM3(rolebk, 2, ELONA_MAX_CHARACTERS);
        for (auto&& cnt : cdata.all())
        {
            if (cnt.state() == character::state_t::empty)
            {
                continue;
            }
            if ((cnt.character_role >= 1000 && cnt.character_role < 2000)
                || cnt.character_role == 2003)
            {
                rolebk(0, maxnpcbk) = cnt.character_role;
                rolebk(1, maxnpcbk) = cnt.shop_rank;
                ++maxnpcbk;
            }
        }
        maxmedal = 0;
        DIM3(medalbk, 2, 30);
        for (int cnt = 0, cnt_end = (mdata_map_height); cnt < cnt_end; ++cnt)
        {
            y = cnt;
            for (int cnt = 0, cnt_end = (mdata_map_width); cnt < cnt_end; ++cnt)
            {
                x = cnt;
                if (map(x, y, 6) / 1000 % 100 == 32)
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
    mdata_map_next_regenerate_date = 0;
    for (auto&& cnt : cdata.others())
    {
        cnt.set_state(character::state_t::empty);
    }
    for (int cnt = 1320; cnt < 5480; ++cnt)
    {
        inv[cnt].remove();
    }
    DIM2(mdata, 100);
    mdata_map_current_dungeon_level = gdata_current_dungeon_level;
    mdata_map_atlas_number = adata(4, gdata_current_map);
    mdata_map_tileset = adata(18, gdata_current_map);
    mdata_map_type = adata(0, gdata_current_map);
    mdata_map_turn_cost = adata(9, gdata_current_map);
    mdata_map_refresh_type = adata(11, gdata_current_map);
    mdata_map_designated_spawns = adata(12, gdata_current_map);
    mdata_map_indoors_flag = adata(21, gdata_current_map);
    if (mapupdate)
    {
        randomize(
            gdata_random_seed + gdata_current_map * 1000
            + gdata_current_dungeon_level);
    }
    if (gdata_current_map == mdata_t::map_id_t::your_home)
    {
        if (mdatan(0) == ""s
            || mdatan(0)
                == i18n::s.get_enum_property(
                       "core.locale.map.unique", "name", 4))
        {
            mdatan(0) =
                i18n::s.get_enum_property("core.locale.map.unique", "name", 7);
        }
    }
    else
    {
        mdatan(0) = mapname(gdata_current_map);
    }
    if (gdata_current_map == mdata_t::map_id_t::shelter_)
    {
        if (gdata_current_dungeon_level == 1)
        {
            map_initcustom(u8"shelter_2"s);
            mdata_map_refresh_type = 0;
            mdata_map_type = mdata_t::map_type_t::shelter;
        }
        else
        {
            map_initcustom(u8"shelter_1"s);
            mdata_map_user_map_flag = 0;
        }
        mdata_map_max_crowd_density = 0;
        mdata_map_max_item_count = 5;
        map_placeplayer();
        mdata_map_bgm = 68;
    }
    if (adata(16, gdata_current_map) == mdata_t::map_id_t::random_dungeon)
    {
        generate_random_nefia();
        if (gdata_current_dungeon_level == adata(10, gdata_current_map))
        {
            event_add(4);
        }
    }
    if (adata(16, gdata_current_map) == mdata_t::map_id_t::museum)
    {
        map_initcustom(u8"museum_1"s);
        mdata_map_bgm = 53;
        map_placeplayer();
        mdata_map_user_map_flag = 0;
        flt();
        itemcreate(-1, 24, 15, 17, 0);
        inv[ci].param1 = 4;
    }
    if (adata(16, gdata_current_map) == mdata_t::map_id_t::shop)
    {
        map_initcustom(u8"shop_1"s);
        mdata_map_bgm = 53;
        mdata_map_max_item_count = 10;
        map_placeplayer();
        mdata_map_user_map_flag = 0;
        flt();
        itemcreate(-1, 24, 17, 14, 0);
        inv[ci].param1 = 8;
        flt();
        itemcreate(-1, 561, 19, 10, 0);
        inv[ci].count = 5;
        flt();
        itemcreate(-1, 562, 17, 11, 0);
    }
    if (adata(16, gdata_current_map) == mdata_t::map_id_t::crop)
    {
        map_initcustom(u8"crop_1"s);
        mdata_map_bgm = 68;
        map_placeplayer();
        mdata_map_max_item_count = 80;
        mdata_map_user_map_flag = 0;
        flt();
        itemcreate(-1, 24, 14, 5, 0);
        inv[ci].param1 = 9;
    }
    if (adata(16, gdata_current_map) == mdata_t::map_id_t::ranch)
    {
        map_initcustom(u8"ranch_1"s);
        mdata_map_bgm = 68;
        map_placeplayer();
        mdata_map_max_item_count = 80;
        mdata_map_user_map_flag = 0;
        flt();
        itemcreate(-1, 24, 23, 8, 0);
        inv[ci].param1 = 11;
        flt();
        itemcreate(-1, 562, 22, 6, 0);
    }
    if (adata(16, gdata_current_map) == mdata_t::map_id_t::your_dungeon)
    {
        map_initcustom(u8"dungeon1"s);
        mdata_map_bgm = 68;
        map_placeplayer();
        mdata_map_max_item_count = 350;
        mdata_map_user_map_flag = 0;
        flt();
        itemcreate(-1, 24, 39, 54, 0);
        inv[ci].param1 = 15;
    }
    if (adata(16, gdata_current_map) == mdata_t::map_id_t::storage_house)
    {
        map_initcustom(u8"storage_1"s);
        mdata_map_bgm = 68;
        map_placeplayer();
        mdata_map_max_item_count = 200;
        mdata_map_user_map_flag = 0;
    }
    if (gdata_current_map == mdata_t::map_id_t::quest)
    {
        generate_random_nefia();
    }
    if (gdata_current_map == mdata_t::map_id_t::test_site)
    {
        mdata_map_width = 16;
        mdata_map_height = 16;
        mdata_map_max_crowd_density = 0;
        map_initialize();
        for (int cnt = 0, cnt_end = (mdata_map_height); cnt < cnt_end; ++cnt)
        {
            p = cnt;
            for (int cnt = 0, cnt_end = (mdata_map_width); cnt < cnt_end; ++cnt)
            {
                map(cnt, p, 0) = tile_default
                    + (rnd(tile_default(2)) == 0) * rnd(tile_default(1));
            }
        }
        map_placeplayer();
        for (int cnt = 0; cnt < 0; ++cnt)
        {
            flt();
            chara_create(
                -1,
                0,
                cdata.player().position.x,
                cdata.player().position.y + 5);
        }
        for (int cnt = 0; cnt < 100; ++cnt)
        {
            x = rnd(mdata_map_width);
            y = rnd(mdata_map_height);
        }
        flt();
        chara_create(
            -1, 41, cdata.player().position.x, cdata.player().position.y);
        cdata[rc].character_role = 22;
        cdata[rc].is_livestock() = true;
    }
    if (gdata_current_map == mdata_t::map_id_t::lumiest_graveyard)
    {
        map_initcustom(u8"grave_1"s);
        mdata_map_max_crowd_density = 7;
        mdata_map_bgm = 79;
        map_placeplayer();
        for (int cnt = 0, cnt_end = (mdata_map_max_crowd_density / 2);
             cnt < cnt_end;
             ++cnt)
        {
            chara_set_generation_filter();
            chara_create(-1, 0, -3, 0);
        }
    }
    if (gdata_current_map == mdata_t::map_id_t::jail)
    {
        map_initcustom(u8"jail1"s);
        mdata_map_max_crowd_density = 0;
        mdata_map_bgm = 79;
        map_placeplayer();
    }
    if (gdata_current_map == mdata_t::map_id_t::truce_ground)
    {
        map_initcustom(u8"shrine_1"s);
        mdata_map_max_crowd_density = 10;
        flt();
        itemcreate(-1, 171, 10, 8, 0);
        inv[ci].param1 = 1;
        inv[ci].own_state = 1;
        flt();
        itemcreate(-1, 171, 13, 8, 0);
        inv[ci].param1 = 2;
        inv[ci].own_state = 1;
        flt();
        itemcreate(-1, 171, 10, 13, 0);
        inv[ci].param1 = 5;
        inv[ci].own_state = 1;
        flt();
        itemcreate(-1, 171, 13, 13, 0);
        inv[ci].param1 = 4;
        inv[ci].own_state = 1;
        flt();
        itemcreate(-1, 171, 20, 8, 0);
        inv[ci].param1 = 3;
        inv[ci].own_state = 1;
        flt();
        itemcreate(-1, 171, 23, 8, 0);
        inv[ci].param1 = 7;
        inv[ci].own_state = 1;
        flt();
        itemcreate(-1, 171, 20, 13, 0);
        inv[ci].param1 = 6;
        inv[ci].own_state = 1;
        flt();
        itemcreate(-1, 171, 23, 13, 0);
        inv[ci].own_state = 1;
        mdata_map_bgm = 79;
        map_placeplayer();
        for (int cnt = 0, cnt_end = (mdata_map_max_crowd_density / 2);
             cnt < cnt_end;
             ++cnt)
        {
            chara_set_generation_filter();
            chara_create(-1, 0, -3, 0);
        }
    }
    if (gdata_current_map == mdata_t::map_id_t::embassy)
    {
        map_initcustom(u8"office_1"s);
        mdata_map_max_crowd_density = 0;
        flt();
        chara_create(-1, 173, 9, 2);
        cdata[rc].character_role = 1012;
        cdata[rc].shop_rank = 10;
        flt();
        chara_create(-1, 173, 15, 2);
        cdata[rc].character_role = 1012;
        cdata[rc].shop_rank = 10;
        flt();
        chara_create(-1, 173, 21, 2);
        cdata[rc].character_role = 1013;
        cdata[rc].shop_rank = 10;
        flt();
        chara_create(-1, 173, 3, 2);
        cdata[rc].character_role = 1013;
        cdata[rc].shop_rank = 10;
        for (int cnt = 0; cnt < 3; ++cnt)
        {
            flt();
            chara_create(-1, 16, -3, 0);
            cdata[rc].character_role = 4;
            flt();
            chara_create(-1, 39, -3, 0);
            cdata[rc].character_role = 4;
        }
        for (int cnt = 0; cnt < 4; ++cnt)
        {
            flt();
            chara_create(-1, 77, 3 + cnt * 6, 9);
            cdata[rc].character_role = 14;
        }
        mdata_map_bgm = 79;
        map_placeplayer();
    }
    if (gdata_current_map == mdata_t::map_id_t::test_world_north_border)
    {
        map_initcustom(u8"test2"s);
        mdata_map_max_crowd_density = 0;
        flt();
        chara_create(-1, 1, 7, 23);
        cdata[rc].character_role = 1006;
        cdata[rc].shop_rank = 10;
        cdatan(0, rc) = sngeneral(cdatan(0, rc));
        cdata[rc].ai_calm = 3;
        flt();
        chara_create(-1, 1, 5, 17);
        cdata[rc].character_role = 1009;
        cdata[rc].shop_rank = 12;
        cdatan(0, rc) = sntrade(cdatan(0, rc));
        cdata[rc].ai_calm = 3;
        flt();
        chara_create(-1, 1, 16, 19);
        cdata[rc].character_role = 1005;
        cdata[rc].shop_rank = 8;
        cdatan(0, rc) = sninn(cdatan(0, rc));
        flt();
        chara_create(-1, 70, 17, 13);
        cdata[rc].character_role = 9;
        flt();
        chara_create(-1, 353, 7, 3);
        cdata[rc].character_role = 23;
        for (int cnt = 0; cnt < 2; ++cnt)
        {
            flt();
            chara_create(-1, 9, -3, 0);
            flt();
            chara_create(-1, 159, -3, 0);
            cdata[rc].relationship = -1;
            cdata[rc].original_relationship = -1;
            flt();
            chara_create(-1, 160, -3, 0);
            cdata[rc].relationship = -1;
            cdata[rc].original_relationship = -1;
            flt();
            chara_create(-1, 161, -3, 0);
            cdata[rc].relationship = -1;
            cdata[rc].original_relationship = -1;
        }
        flt();
        chara_create(-1, 77, 5, 7);
        cdata[rc].character_role = 14;
        cdata[rc].ai_calm = 3;
        flt();
        chara_create(-1, 77, 8, 7);
        cdata[rc].character_role = 14;
        cdata[rc].ai_calm = 3;
        mdata_map_bgm = 79;
        map_placeplayer();
        event_add(30);
    }
    if (gdata_current_map == mdata_t::map_id_t::north_tyris_south_border
        || gdata_current_map == mdata_t::map_id_t::south_tyris_north_border)
    {
        map_initcustom(u8"station-nt1"s);
        mdata_map_max_crowd_density = 0;
        flt();
        chara_create(-1, 1, 7, 23);
        cdata[rc].character_role = 1006;
        cdata[rc].shop_rank = 10;
        cdatan(0, rc) = sngeneral(cdatan(0, rc));
        cdata[rc].ai_calm = 3;
        flt();
        chara_create(-1, 1, 5, 17);
        cdata[rc].character_role = 1009;
        cdata[rc].shop_rank = 12;
        cdatan(0, rc) = sntrade(cdatan(0, rc));
        cdata[rc].ai_calm = 3;
        flt();
        chara_create(-1, 1, 16, 19);
        cdata[rc].character_role = 1005;
        cdata[rc].shop_rank = 8;
        cdatan(0, rc) = sninn(cdatan(0, rc));
        flt();
        chara_create(-1, 70, 17, 13);
        cdata[rc].character_role = 9;
        flt();
        chara_create(-1, 353, 7, 3);
        cdata[rc].character_role = 23;
        for (int cnt = 0; cnt < 2; ++cnt)
        {
            flt();
            chara_create(-1, 9, -3, 0);
            flt();
            chara_create(-1, 159, -3, 0);
            cdata[rc].relationship = -1;
            cdata[rc].original_relationship = -1;
            flt();
            chara_create(-1, 160, -3, 0);
            cdata[rc].relationship = -1;
            cdata[rc].original_relationship = -1;
            flt();
            chara_create(-1, 161, -3, 0);
            cdata[rc].relationship = -1;
            cdata[rc].original_relationship = -1;
        }
        flt();
        chara_create(-1, 77, 5, 7);
        cdata[rc].character_role = 14;
        cdata[rc].ai_calm = 3;
        flt();
        chara_create(-1, 77, 8, 7);
        cdata[rc].character_role = 14;
        cdata[rc].ai_calm = 3;
        mdata_map_bgm = 79;
        map_placeplayer();
    }
    if (gdata_current_map == mdata_t::map_id_t::the_smoke_and_pipe)
    {
        map_initcustom(u8"inn1"s);
        mdata_map_max_crowd_density = 0;
        flt();
        chara_create(-1, 1, 19, 10);
        cdata[rc].character_role = 1005;
        cdata[rc].shop_rank = 8;
        cdatan(0, rc) = sninn(cdatan(0, rc));
        flt();
        chara_create(-1, 351, 26, 16);
        cdata[rc].character_role = 3;
        cdata[rc].ai_calm = 3;
        flt();
        chara_create(-1, 35, 25, 15);
        cdata[rc].ai_calm = 3;
        flt();
        chara_create(-1, 35, 25, 17);
        cdata[rc].ai_calm = 3;
        flt();
        chara_create(-1, 35, 27, 18);
        cdata[rc].ai_calm = 3;
        flt();
        chara_create(-1, 35, 27, 16);
        cdata[rc].ai_calm = 3;
        flt();
        chara_create(-1, 35, 26, 17);
        cdata[rc].ai_calm = 3;
        flt();
        chara_create(-1, 352, 4, 3);
        cdata[rc].character_role = 3;
        flt();
        chara_create(-1, 271, 4, 2);
        flt();
        chara_create(-1, 269, 3, 3);
        flt();
        chara_create(-1, 272, 4, 4);
        flt();
        chara_create(-1, 274, 5, 4);
        flt();
        chara_create(-1, 239, 24, 3);
        flt();
        chara_create(-1, 239, 26, 4);
        flt();
        chara_create(-1, 239, 25, 5);
        flt();
        chara_create(-1, 239, 25, 9);
        flt();
        chara_create(-1, 326, 12, 9);
        for (int cnt = 0; cnt < 2; ++cnt)
        {
            flt();
            chara_create(-1, 9, -3, 0);
            flt();
            chara_create(-1, 159, -3, 0);
            cdata[rc].relationship = -1;
            cdata[rc].original_relationship = -1;
            flt();
            chara_create(-1, 36, -3, 0);
            cdata[rc].relationship = -1;
            cdata[rc].original_relationship = -1;
            flt();
            chara_create(-1, 8, -3, 0);
            flt();
            chara_create(-1, 185, -3, 0);
        }
        mdata_map_bgm = 79;
        map_placeplayer();
    }
    if (gdata_current_map == mdata_t::map_id_t::miral_and_garoks_workshop)
    {
        map_initcustom(u8"smith0"s);
        mdata_map_max_crowd_density = 0;
        flt();
        chara_create(-1, 208, 17, 11);
        cdata[rc].character_role = 3;
        flt();
        chara_create(-1, 209, 8, 16);
        cdata[rc].character_role = 1016;
        cdata[rc].shop_rank = 100;
        for (int cnt = 0; cnt < 5; ++cnt)
        {
            flt();
            chara_create(-1, 164, -3, 0);
            cdata[rc].character_role = 3;
        }
        mdata_map_bgm = 79;
        map_placeplayer();
    }
    if (gdata_current_map == mdata_t::map_id_t::mansion_of_younger_sister)
    {
        map_initcustom(u8"sister"s);
        mdata_map_max_crowd_density = 0;
        mdata_map_bgm = 79;
        if (mapupdate == 0)
        {
            flt();
            itemcreate(-1, 668, 12, 8, 0);
            inv[ci].param2 = 4;
        }
        flt();
        chara_create(-1, 249, 12, 6);
        cdata[rc].character_role = 1019;
        for (int cnt = 0; cnt < 6; ++cnt)
        {
            flt();
            chara_create(-1, 211, -3, 0);
            cdata[rc].character_role = 3;
        }
        for (int cnt = 0; cnt < 8; ++cnt)
        {
            flt();
            chara_create(-1, 246, -3, 0);
            cdata[rc].character_role = 3;
        }
        map_placeplayer();
    }
    if (gdata_current_map == mdata_t::map_id_t::cyber_dome)
    {
        map_initcustom(u8"cyberdome"s);
        mdata_map_max_crowd_density = 10;
        flt();
        itemcreate(-1, 171, 19, 5, 0);
        inv[ci].param1 = 1;
        inv[ci].own_state = 1;
        flt();
        chara_create(-1, 173, 9, 16);
        cdata[rc].character_role = 1011;
        cdata[rc].shop_rank = 10;
        flt();
        chara_create(-1, 173, 9, 8);
        cdata[rc].character_role = 1011;
        cdata[rc].shop_rank = 10;
        flt();
        chara_create(-1, 322, 28, 7);
        cdata[rc].character_role = 3;
        for (int cnt = 0; cnt < 4; ++cnt)
        {
            flt();
            chara_create(-1, 171, -3, 0);
            cdata[rc].character_role = 4;
            flt();
            chara_create(-1, 172, -3, 0);
            cdata[rc].character_role = 4;
        }
        for (int cnt = 0, cnt_end = (mdata_map_max_crowd_density / 2);
             cnt < cnt_end;
             ++cnt)
        {
            chara_set_generation_filter();
            chara_create(-1, 0, -3, 0);
        }
        mdata_map_bgm = 79;
        map_placeplayer();
    }
    if (gdata_current_map == mdata_t::map_id_t::larna)
    {
        map_initcustom(u8"highmountain"s);
        mdata_map_max_crowd_density = 20;
        flt();
        chara_create(-1, 41, 21, 23);
        cdata[rc].character_role = 21;
        flt();
        chara_create(-1, 1, 9, 44);
        cdata[rc].character_role = 1017;
        cdata[rc].shop_rank = 5;
        cdatan(0, rc) =
            i18n::s.get("core.locale.chara.job.dye_vendor", cdatan(0, rc));
        flt();
        chara_create(-1, 1, 13, 37);
        cdata[rc].character_role = 1018;
        cdata[rc].shop_rank = 30;
        cdatan(0, rc) =
            i18n::s.get("core.locale.chara.job.souvenir_vendor", cdatan(0, rc));
        flt();
        chara_create(-1, 70, 24, 48);
        cdata[rc].character_role = 9;
        flt();
        chara_create(-1, 239, 7, 36);
        flt();
        chara_create(-1, 239, 9, 38);
        flt();
        chara_create(-1, 239, 6, 33);
        flt();
        chara_create(-1, 239, 3, 33);
        flt();
        chara_create(-1, 239, 8, 31);
        flt();
        chara_create(-1, 239, 4, 36);
        for (int cnt = 0; cnt < 7; ++cnt)
        {
            flt();
            chara_create(-1, 16, -3, 0);
            cdata[rc].character_role = 4;
            flt();
            chara_create(-1, 39, -3, 0);
            cdata[rc].character_role = 4;
            flt();
            chara_create(-1, 239, -3, 0);
        }
        for (int cnt = 0; cnt < 15; ++cnt)
        {
            flt();
            chara_create(-1, 239, -3, 0);
        }
        for (int cnt = 0, cnt_end = (mdata_map_max_crowd_density / 2);
             cnt < cnt_end;
             ++cnt)
        {
            chara_set_generation_filter();
            chara_create(-1, 0, -3, 0);
        }
        mdata_map_bgm = 79;
        map_placeplayer();
    }
    if (gdata_current_map == mdata_t::map_id_t::arena)
    {
        map_initcustom(u8"arena_1"s);
        map_placeplayer();
        for (int cnt = 0; cnt < 16; ++cnt)
        {
            if (cdata[cnt].state() == character::state_t::alive)
            {
                if (cdata[cnt].relationship == 10)
                {
                    if (cnt != 0)
                    {
                        map(cdata[cnt].position.x, cdata[cnt].position.y, 1) =
                            0;
                        cdata[cnt].set_state(
                            character::state_t::pet_in_other_map);
                    }
                }
            }
        }
        if (arenaop == 0)
        {
            fixlv = arenaop(2);
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
                flt(arenaop(1), 2);
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
                if (cdata[rc].level > arenaop(1)
                    || cdata[rc].relationship != -3)
                {
                    chara_vanquish(rc);
                    --cnt;
                    continue;
                }
            }
        }
    }
    if (gdata_current_map == mdata_t::map_id_t::pet_arena)
    {
        map_initcustom(u8"arena_2"s);
        mdata_map_max_crowd_density = 0;
        mdata_map_bgm = 81;
        for (int cnt = 0; cnt < 16; ++cnt)
        {
            if (cnt == 0 || cnt == 56)
            {
                continue;
            }
            if (followerin(cnt) == 0)
            {
                cdata[cnt].set_state(character::state_t::pet_dead);
                cdata[cnt].position.x = 0;
                cdata[cnt].position.y = 0;
            }
            else
            {
                cdata[cnt].set_state(character::state_t::alive);
            }
        }
        map_placeplayer();
        petarenawin = 0;
        for (int cnt = 0, cnt_end = (arenaop(1)); cnt < cnt_end; ++cnt)
        {
            flt(arenaop(2), calcfixlv(3));
            chara_create(-1, 0, -3, 0);
            map(cdata[rc].position.x, cdata[rc].position.y, 1) = 0;
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
            map_placearena(rc, 1);
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
    if (gdata_current_map == mdata_t::map_id_t::fort_of_chaos_beast)
    {
        map_initcustom(u8"god"s);
        mdata_map_max_crowd_density = 0;
        mdata_map_bgm = 63;
        flt();
        chara_create(-1, 175, 12, 14);
        map_placeplayer();
    }
    if (gdata_current_map == mdata_t::map_id_t::fort_of_chaos_machine)
    {
        map_initcustom(u8"god"s);
        mdata_map_max_crowd_density = 0;
        mdata_map_bgm = 63;
        flt();
        chara_create(-1, 177, 12, 14);
        map_placeplayer();
    }
    if (gdata_current_map == mdata_t::map_id_t::fort_of_chaos_collapsed)
    {
        map_initcustom(u8"god"s);
        mdata_map_bgm = 63;
        mdata_map_max_crowd_density = 0;
        flt();
        chara_create(-1, 178, 12, 14);
        map_placeplayer();
    }
    if (gdata_current_map == mdata_t::map_id_t::your_home)
    {
        map_initcustom(u8"home"s + gdata_home_scale);
        mdata_map_bgm = 68;
        gdata_entrance_type = 4;
        map_placeplayer();
        mdata_map_user_map_flag = 0;
        mdata_map_tileset = 3;
        if (gdata_current_dungeon_level == 1)
        {
            if (gdata_home_scale == 0)
            {
                mdata_map_play_campfire_sound = 1;
                flt();
                chara_create(-1, 33, 18, 10);
                cdata[rc].character_role = 3;
                flt();
                chara_create(-1, 34, 16, 11);
                cdata[rc].character_role = 3;
                flt();
                itemcreate(-1, 510, 6, 10, 0);
                inv[ci].count = 3;
                flt();
                itemcreate(-1, 547, 15, 19, 0);
                inv[ci].count = 4;
                flt();
                itemcreate(-1, 579, 9, 8, 0);
                inv[ci].count = 6;
                flt();
                itemcreate(-1, 24, 18, 19, 0);
                inv[ci].param1 = 1;
            }
            else
            {
                // Move existing characters/items to the middle of the
                // map if the home was upgraded.
                ctrl_file(file_operation2_t::_3, u8"inv_"s + mid + u8".s2");
                for (const auto& cnt : items(-1))
                {
                    if (inv[cnt].number() == 0)
                    {
                        continue;
                    }
                    inv[cnt].position.x = mdata_map_width / 2;
                    inv[cnt].position.y = mdata_map_height / 2;
                    cell_refresh(inv[cnt].position.x, inv[cnt].position.y);
                }
                ctrl_file(file_operation_t::_17);
                for (auto&& cnt : cdata.others())
                {
                    cnt.position.x = mdata_map_width / 2;
                    cnt.position.y = mdata_map_height / 2;
                    cnt.initial_position.x = mdata_map_width / 2;
                    cnt.initial_position.y = mdata_map_height / 2;
                }
            }
            if (gdata_home_scale == 5)
            {
                flt();
                chara_create(-1, 1, 31, 20);
                cdata[rc].character_role = 1006;
                cdata[rc].shop_rank = 10;
                cdatan(0, rc) = sngeneral(cdatan(0, rc));
                flt();
                chara_create(-1, 1, 9, 20);
                cdata[rc].character_role = 1001;
                cdata[rc].shop_rank = 12;
                cdatan(0, rc) = snarmor(cdatan(0, rc));
                flt();
                chara_create(-1, 1, 4, 20);
                cdata[rc].character_role = 1008;
                cdata[rc].shop_rank = 10;
                cdatan(0, rc) = sngoods(cdatan(0, rc));
                flt();
                chara_create(-1, 41, 4, 11);
                cdata[rc].character_role = 5;
                flt();
                chara_create(-1, 70, 30, 11);
                cdata[rc].character_role = 9;
                flt();
                chara_create(-1, 74, 30, 4);
                cdata[rc].character_role = 12;
                flt();
                chara_create(-1, 41, 4, 4);
                cdata[rc].character_role = 1004;
                cdata[rc].shop_rank = 11;
                cdatan(0, rc) = snmagic(cdatan(0, rc));
            }
        }
        else
        {
            flt();
            itemcreate(
                -1,
                219,
                cdata.player().position.x,
                cdata.player().position.y,
                0);
        }
        initialize_home_mdata();
    }
    if (gdata_current_map == mdata_t::map_id_t::north_tyris)
    {
        map_initcustom(u8"ntyris"s);
        initialize_world_map();
        map_placeplayer();
    }
    if (gdata_current_map == mdata_t::map_id_t::south_tyris)
    {
        map_initcustom(u8"styris"s);
        initialize_world_map();
        map_placeplayer();
    }
    if (gdata_current_map == mdata_t::map_id_t::test_world)
    {
        map_initcustom(u8"test"s);
        initialize_world_map();
        map_placeplayer();
    }
    if (gdata_current_map == mdata_t::map_id_t::derphy)
    {
        if (gdata_current_dungeon_level == 1)
        {
            mdata_map_max_crowd_density = 35;
            map_initcustom(u8"rogueden"s);
            map_placeplayer();
            mdata_map_user_map_flag = 0;
            flt();
            chara_create(-1, 253, 23, 14);
            cdata[rc].character_role = 3;
            flt();
            chara_create(-1, 259, 13, 18);
            cdata[rc].character_role = 3;
            flt();
            chara_create(-1, 294, 16, 17);
            cdata[rc].character_role = 3;
            flt();
            chara_create(-1, 1, 10, 17);
            cdata[rc].character_role = 1009;
            cdata[rc].shop_rank = 12;
            cdatan(0, rc) = sntrade(cdatan(0, rc));
            flt();
            chara_create(-1, 70, 15, 15);
            cdata[rc].character_role = 9;
            flt();
            chara_create(-1, 1, 13, 3);
            cdata[rc].character_role = 1006;
            cdata[rc].shop_rank = 10;
            cdatan(0, rc) = sngeneral(cdatan(0, rc));
            flt();
            chara_create(-1, 1, 29, 23);
            cdata[rc].character_role = 1005;
            cdata[rc].shop_rank = 8;
            cdatan(0, rc) = sninn(cdatan(0, rc));
            flt();
            chara_create(-1, 1, 26, 7);
            cdata[rc].character_role = 1008;
            cdata[rc].shop_rank = 10;
            cdatan(0, rc) = sngoods(cdatan(0, rc));
            flt();
            chara_create(-1, 1, 30, 4);
            cdata[rc].character_role = 1007;
            cdata[rc].shop_rank = 10;
            cdatan(0, rc) = snblack(cdatan(0, rc));
            flt();
            chara_create(-1, 1, 29, 4);
            cdata[rc].character_role = 17;
            cdatan(0, rc) = i18n::s.get("core.locale.chara.job.slave_master");
            flt();
            chara_create(-1, 1, 10, 6);
            cdata[rc].character_role = 1001;
            cdata[rc].shop_rank = 12;
            cdatan(0, rc) = snarmor(cdatan(0, rc));
            flt();
            chara_create(-1, 73, 7, 15);
            cdata[rc].character_role = 10;
            flt();
            chara_create(-1, 38, 9, 18);
            cdata[rc].character_role = 6;
            cdatan(0, rc) =
                i18n::s.get("core.locale.chara.job.of_derphy", cdatan(0, rc));
            flt();
            chara_create(-1, 40, 13, 18);
            cdata[rc].character_role = 7;
            cdatan(0, rc) = sntrainer(cdatan(0, rc));
            flt();
            chara_create(-1, 41, 5, 26);
            cdata[rc].character_role = 5;
            flt();
            chara_create(-1, 69, 3, 28);
            cdata[rc].character_role = 8;
            for (int cnt = 0; cnt < 4; ++cnt)
            {
                flt();
                chara_create(-1, 16, -3, 0);
                cdata[rc].character_role = 4;
                flt();
                chara_create(-1, 39, -3, 0);
                cdata[rc].character_role = 4;
            }
            quest_on_map_initialize();
            for (int cnt = 0; cnt < 20; ++cnt)
            {
                dbid = 0;
                chara_set_generation_filter();
                chara_create(-1, dbid, -3, 0);
            }
        }
        if (gdata_current_dungeon_level == 3)
        {
            mdata_map_tileset = 0;
            map_initcustom(u8"thiefguild"s);
            mdata_map_indoors_flag = 1;
            mdata_map_type = mdata_t::map_type_t::guild;
            mdata_map_max_crowd_density = 25;
            mdata_map_bgm = 79;
            mdata_map_should_regenerate = 0;
            mdatan(0) =
                i18n::s.get("core.locale.map.unique.thieves_guild.name");
            map_placeplayer();
            flt();
            chara_create(-1, 292, 21, 9);
            cdata[rc].character_role = 3;
            flt();
            chara_create(-1, 40, 3, 6);
            cdata[rc].character_role = 7;
            cdatan(0, rc) = sntrainer(cdatan(0, rc));
            flt();
            chara_create(-1, 41, 3, 12);
            cdata[rc].character_role = 5;
            flt();
            chara_create(-1, 1, 5, 18);
            cdata[rc].character_role = 1007;
            cdata[rc].shop_rank = 10;
            cdatan(0, rc) = snblack(cdatan(0, rc));
            flt();
            chara_create(-1, 1, 27, 13);
            cdata[rc].character_role = 1007;
            cdata[rc].shop_rank = 10;
            cdatan(0, rc) = snblack(cdatan(0, rc));
            flt();
            chara_create(-1, 1, 21, 19);
            cdata[rc].character_role = 1021;
            cdata[rc].shop_rank = 10;
            cdatan(0, rc) =
                i18n::s.get("core.locale.chara.job.fence", cdatan(0, rc));
            for (int cnt = 0; cnt < 16; ++cnt)
            {
                flt();
                chara_create(-1, 293, -3, 0);
            }
        }
    }
    if (gdata_current_map == mdata_t::map_id_t::palmia)
    {
        mdata_map_max_crowd_density = 45;
        map_initcustom(u8"palmia"s);
        map_placeplayer();
        mdata_map_user_map_flag = 0;
        flt();
        chara_create(-1, 70, 42, 27);
        cdata[rc].character_role = 9;
        flt();
        chara_create(-1, 74, 34, 3);
        cdata[rc].character_role = 12;
        flt();
        chara_create(-1, 73, 22, 31);
        cdata[rc].character_role = 10;
        flt();
        chara_create(-1, 142, 5, 15);
        cdata[rc].character_role = 3;
        flt();
        chara_create(-1, 247, 41, 11);
        cdata[rc].character_role = 3;
        flt();
        chara_create(-1, 301, 5, 6);
        cdata[rc].character_role = 3;
        flt();
        chara_create(-1, 320, 24, 6);
        cdata[rc].character_role = 3;
        flt();
        chara_create(-1, 320, 15, 22);
        cdata[rc].character_role = 3;
        flt();
        chara_create(-1, 326, 15, 22);
        cdata[rc].character_role = 3;
        if (gdata_mias_dream == 1000)
        {
            flt();
            chara_create(-1, 246, 42, 11);
            cdata[rc].character_role = 3;
        }
        flt();
        chara_create(-1, 1, 48, 18);
        cdata[rc].character_role = 1006;
        cdata[rc].shop_rank = 10;
        cdatan(0, rc) = sngeneral(cdatan(0, rc));
        flt();
        chara_create(-1, 1, 30, 17);
        cdata[rc].character_role = 1005;
        cdata[rc].shop_rank = 8;
        cdatan(0, rc) = sninn(cdatan(0, rc));
        flt();
        chara_create(-1, 1, 48, 3);
        cdata[rc].character_role = 1008;
        cdata[rc].shop_rank = 8;
        cdatan(0, rc) = sngoods(cdatan(0, rc));
        flt();
        chara_create(-1, 1, 42, 17);
        cdata[rc].character_role = 1001;
        cdata[rc].shop_rank = 12;
        cdatan(0, rc) = snarmor(cdatan(0, rc));
        flt();
        chara_create(-1, 1, 11, 14);
        cdata[rc].character_role = 1003;
        cdata[rc].shop_rank = 9;
        cdatan(0, rc) = snbakery(cdatan(0, rc));
        cdata[rc].image = 138;
        flt();
        chara_create(-1, 41, 41, 3);
        cdata[rc].character_role = 1004;
        cdata[rc].shop_rank = 11;
        cdatan(0, rc) = snmagic(cdatan(0, rc));
        flt();
        chara_create(-1, 1, 41, 28);
        cdata[rc].character_role = 1009;
        cdata[rc].shop_rank = 12;
        cdatan(0, rc) = sntrade(cdatan(0, rc));
        flt();
        chara_create(-1, 79, 7, 2);
        cdata[rc].character_role = 15;
        cdata[rc].ai_calm = 3;
        flt();
        chara_create(-1, 80, 6, 2);
        cdata[rc].character_role = 15;
        cdata[rc].ai_calm = 3;
        flt();
        chara_create(-1, 38, 49, 11);
        cdata[rc].character_role = 6;
        cdatan(0, rc) =
            i18n::s.get("core.locale.chara.job.of_palmia", cdatan(0, rc));
        flt();
        chara_create(-1, 40, 30, 27);
        cdata[rc].character_role = 7;
        cdatan(0, rc) = sntrainer(cdatan(0, rc));
        flt();
        chara_create(-1, 41, 32, 27);
        cdata[rc].character_role = 5;
        flt();
        chara_create(-1, 69, 29, 28);
        cdata[rc].character_role = 8;
        flt();
        chara_create(-1, 77, 16, 5);
        cdata[rc].character_role = 14;
        cdata[rc].ai_calm = 3;
        flt();
        chara_create(-1, 77, 16, 9);
        cdata[rc].character_role = 14;
        cdata[rc].ai_calm = 3;
        flt();
        chara_create(-1, 77, 5, 3);
        cdata[rc].character_role = 14;
        cdata[rc].ai_calm = 3;
        flt();
        chara_create(-1, 77, 8, 3);
        cdata[rc].character_role = 14;
        cdata[rc].ai_calm = 3;
        flt();
        chara_create(-1, 77, 35, 14);
        cdata[rc].character_role = 14;
        cdata[rc].ai_calm = 3;
        flt();
        chara_create(-1, 77, 38, 14);
        cdata[rc].character_role = 14;
        cdata[rc].ai_calm = 3;
        flt();
        chara_create(-1, 77, 29, 2);
        cdata[rc].character_role = 14;
        cdata[rc].ai_calm = 3;
        flt();
        chara_create(-1, 77, 19, 18);
        cdata[rc].character_role = 14;
        cdata[rc].ai_calm = 3;
        flt();
        chara_create(-1, 77, 22, 18);
        cdata[rc].character_role = 14;
        cdata[rc].ai_calm = 3;
        for (int cnt = 0; cnt < 5; ++cnt)
        {
            flt();
            chara_create(-1, 16, -3, 0);
            cdata[rc].character_role = 4;
            flt();
            chara_create(-1, 39, -3, 0);
            cdata[rc].character_role = 4;
        }
        for (int cnt = 0; cnt < 4; ++cnt)
        {
            flt();
            chara_create(-1, 77, -3, 0);
            cdata[rc].character_role = 14;
        }
        quest_on_map_initialize();
        for (int cnt = 0; cnt < 25; ++cnt)
        {
            dbid = 0;
            chara_set_generation_filter();
            chara_create(-1, dbid, -3, 0);
        }
    }
    if (gdata_current_map == mdata_t::map_id_t::lumiest)
    {
        if (gdata_current_dungeon_level == 1)
        {
            mdata_map_max_crowd_density = 40;
            map_initcustom(u8"lumiest"s);
            map_placeplayer();
            mdata_map_user_map_flag = 0;
            if (gdata_sewer_sweeping)
            {
                cell_featset(18, 45, tile_downstairs, 11, 20);
            }
            flt();
            chara_create(-1, 252, 12, 24);
            cdata[rc].character_role = 3;
            flt();
            chara_create(-1, 280, 21, 3);
            cdata[rc].character_role = 3;
            flt();
            chara_create(-1, 290, 5, 20);
            cdata[rc].character_role = 3;
            flt();
            chara_create(-1, 320, 28, 29);
            cdata[rc].character_role = 3;
            flt();
            chara_create(-1, 326, 41, 19);
            cdata[rc].character_role = 3;
            flt();
            chara_create(-1, 326, 32, 43);
            cdata[rc].character_role = 3;
            flt();
            chara_create(-1, 326, 29, 28);
            cdata[rc].character_role = 3;
            flt();
            chara_create(-1, 326, 16, 45);
            cdata[rc].character_role = 3;
            flt();
            chara_create(-1, 326, 13, 24);
            cdata[rc].character_role = 3;
            flt();
            chara_create(-1, 70, 41, 42);
            cdata[rc].character_role = 9;
            flt();
            chara_create(-1, 74, 10, 16);
            cdata[rc].character_role = 12;
            flt();
            chara_create(-1, 1, 47, 30);
            cdata[rc].character_role = 1006;
            cdata[rc].shop_rank = 10;
            cdatan(0, rc) = sngeneral(cdatan(0, rc));
            flt();
            chara_create(-1, 1, 24, 47);
            cdata[rc].character_role = 1005;
            cdata[rc].shop_rank = 8;
            cdatan(0, rc) = sninn(cdatan(0, rc));
            flt();
            chara_create(-1, 1, 37, 30);
            cdata[rc].character_role = 1001;
            cdata[rc].shop_rank = 12;
            cdatan(0, rc) = snarmor(cdatan(0, rc));
            flt();
            chara_create(-1, 1, 37, 12);
            cdata[rc].character_role = 1003;
            cdata[rc].shop_rank = 9;
            cdatan(0, rc) = snbakery(cdatan(0, rc));
            cdata[rc].image = 138;
            flt();
            chara_create(-1, 41, 6, 15);
            cdata[rc].character_role = 1004;
            cdata[rc].shop_rank = 11;
            cdatan(0, rc) = snmagic(cdatan(0, rc));
            flt();
            chara_create(-1, 1, 33, 43);
            cdata[rc].character_role = 1009;
            cdata[rc].shop_rank = 12;
            cdatan(0, rc) = sntrade(cdatan(0, rc));
            flt();
            chara_create(-1, 1, 47, 12);
            cdata[rc].character_role = 1014;
            cdata[rc].shop_rank = 5;
            cdatan(0, rc) = snfish(cdatan(0, rc));
            flt();
            chara_create(-1, 38, 3, 38);
            cdata[rc].character_role = 6;
            cdatan(0, rc) =
                i18n::s.get("core.locale.chara.job.of_lumiest", cdatan(0, rc));
            flt();
            chara_create(-1, 40, 21, 28);
            cdata[rc].character_role = 7;
            cdatan(0, rc) = sntrainer(cdatan(0, rc));
            flt();
            chara_create(-1, 41, 21, 30);
            cdata[rc].character_role = 5;
            flt();
            chara_create(-1, 69, 23, 38);
            cdata[rc].character_role = 8;
            for (int cnt = 0; cnt < 6; ++cnt)
            {
                flt();
                chara_create(-1, 16, -3, 0);
                cdata[rc].character_role = 4;
                flt();
                chara_create(-1, 39, -3, 0);
                cdata[rc].character_role = 4;
            }
            for (int cnt = 0; cnt < 7; ++cnt)
            {
                flt();
                chara_create(-1, 77, -3, 0);
                cdata[rc].character_role = 14;
            }
            quest_on_map_initialize();
            for (int cnt = 0; cnt < 25; ++cnt)
            {
                dbid = 0;
                chara_set_generation_filter();
                chara_create(-1, dbid, -3, 0);
            }
        }
        if (gdata_current_dungeon_level == 3)
        {
            mdata_map_tileset = 0;
            map_initcustom(u8"mageguild"s);
            mdata_map_indoors_flag = 1;
            mdata_map_type = mdata_t::map_type_t::guild;
            mdata_map_max_crowd_density = 25;
            mdata_map_bgm = 79;
            mdata_map_should_regenerate = 0;
            mdatan(0) = i18n::s.get("core.locale.map.unique.mages_guild.name");
            map_placeplayer();
            flt();
            chara_create(-1, 288, 24, 3);
            cdata[rc].character_role = 3;
            flt();
            chara_create(-1, 41, 27, 8);
            cdata[rc].character_role = 1020;
            cdatan(0, rc) = i18n::s.get(
                "core.locale.chara.job.spell_writer", cdatan(0, rc));
            flt();
            chara_create(-1, 41, 22, 8);
            cdata[rc].character_role = 1004;
            cdata[rc].shop_rank = 11;
            cdatan(0, rc) = snmagic(cdatan(0, rc));
            flt();
            chara_create(-1, 74, 3, 9);
            cdata[rc].character_role = 12;
            flt();
            chara_create(-1, 40, 12, 6);
            cdata[rc].character_role = 7;
            cdatan(0, rc) = sntrainer(cdatan(0, rc));
            flt();
            chara_create(-1, 41, 3, 3);
            cdata[rc].character_role = 5;
            for (int cnt = 0; cnt < 16; ++cnt)
            {
                flt();
                chara_create(-1, 289, -3, 0);
            }
        }
        if (gdata_current_dungeon_level == 20)
        {
            mdata_map_tileset = 0;
            map_initcustom(u8"sqSewer"s);
            mdata_map_indoors_flag = 1;
            mdata_map_type = mdata_t::map_type_t::dungeon;
            mdata_map_max_crowd_density = 0;
            mdata_map_bgm = 61;
            mdata_map_should_regenerate = 1;
            mdatan(0) = i18n::s.get("core.locale.map.unique.the_sewer.name");
            quest_place_target();
            gdata_entrance_type = 1;
            map_placeplayer();
        }
    }
    if (gdata_current_map == mdata_t::map_id_t::yowyn)
    {
        if (gdata_current_dungeon_level == 1)
        {
            mdata_map_max_crowd_density = 35;
            map_initcustom(u8"yowyn"s);
            map_placeplayer();
            mdata_map_user_map_flag = 0;
            if (gdata_cat_house)
            {
                cell_featset(23, 22, tile_downstairs, 11, 3);
            }
            flt();
            chara_create(-1, 224, 3, 17);
            cdata[rc].character_role = 3;
            flt();
            chara_create(-1, 227, 26, 11);
            cdata[rc].character_role = 3;
            flt();
            chara_create(-1, 231, 14, 20);
            cdata[rc].character_role = 3;
            flt();
            chara_create(-1, 1, 11, 5);
            cdata[rc].character_role = 1006;
            cdata[rc].shop_rank = 10;
            cdatan(0, rc) = sngeneral(cdatan(0, rc));
            flt();
            chara_create(-1, 1, 25, 8);
            cdata[rc].character_role = 1005;
            cdata[rc].shop_rank = 8;
            cdatan(0, rc) = sninn(cdatan(0, rc));
            flt();
            chara_create(-1, 1, 7, 8);
            cdata[rc].character_role = 1008;
            cdata[rc].shop_rank = 8;
            cdatan(0, rc) = sngoods(cdatan(0, rc));
            flt();
            chara_create(-1, 1, 14, 14);
            cdata[rc].character_role = 1009;
            cdata[rc].shop_rank = 12;
            cdatan(0, rc) = sntrade(cdatan(0, rc));
            flt();
            chara_create(-1, 1, 35, 18);
            cdata[rc].character_role = 22;
            cdatan(0, rc) = i18n::s.get(
                "core.locale.chara.job.horse_master", cdatan(0, rc));
            flt();
            chara_create(-1, 267, 33, 16);
            cdata[rc].character_role = 3;
            flt();
            chara_create(-1, 267, 37, 19);
            cdata[rc].character_role = 3;
            flt();
            chara_create(-1, 268, 34, 19);
            cdata[rc].character_role = 3;
            flt();
            chara_create(-1, 268, 38, 16);
            cdata[rc].character_role = 3;
            flt();
            chara_create(-1, 38, 3, 4);
            cdata[rc].character_role = 6;
            cdatan(0, rc) =
                i18n::s.get("core.locale.chara.job.of_yowyn", cdatan(0, rc));
            flt();
            chara_create(-1, 40, 20, 14);
            cdata[rc].character_role = 7;
            cdatan(0, rc) = sntrainer(cdatan(0, rc));
            flt();
            chara_create(-1, 41, 24, 16);
            cdata[rc].character_role = 5;
            flt();
            chara_create(-1, 69, 26, 16);
            cdata[rc].character_role = 8;
            flt();
            chara_create(-1, 213, 14, 12);
            cdata[rc].character_role = 3;
            for (int cnt = 0; cnt < 2; ++cnt)
            {
                flt();
                chara_create(-1, 16, -3, 0);
                cdata[rc].character_role = 4;
                flt();
                chara_create(-1, 39, -3, 0);
                cdata[rc].character_role = 4;
            }
            for (int cnt = 0; cnt < 3; ++cnt)
            {
                flt();
                chara_create(-1, 77, -3, 0);
                cdata[rc].character_role = 14;
            }
            quest_on_map_initialize();
            for (int cnt = 0; cnt < 15; ++cnt)
            {
                dbid = 0;
                chara_set_generation_filter();
                chara_create(-1, dbid, -3, 0);
            }
        }
        if (gdata_current_dungeon_level == 3)
        {
            mdata_map_tileset = 0;
            map_initcustom(u8"sqcat"s);
            mdata_map_indoors_flag = 1;
            mdata_map_type = mdata_t::map_type_t::dungeon;
            mdata_map_max_crowd_density = 0;
            mdata_map_bgm = 61;
            mdata_map_should_regenerate = 1;
            mdatan(0) = i18n::s.get("core.locale.map.unique.cat_mansion.name");
            quest_place_target();
            map_placeplayer();
        }
        if (gdata_current_dungeon_level == 4)
        {
            mdata_map_tileset = 0;
            map_initcustom(u8"sqwar"s);
            mdata_map_indoors_flag = 2;
            mdata_map_type = mdata_t::map_type_t::dungeon;
            mdata_map_max_crowd_density = 0;
            mdata_map_bgm = 61;
            mdata_map_should_regenerate = 1;
            mdata_map_refresh_type = 0;
            mdatan(0) = i18n::s.get("core.locale.map.unique.battle_field.name");
            quest_place_target();
            gdata_entrance_type = 8;
            map_placeplayer();
            listmax = 0;
            for (auto&& cnt : cdata.others())
            {
                if (cnt.state() == character::state_t::alive)
                {
                    if (cnt.is_quest_target() == 1)
                    {
                        list(0, listmax) = cnt.index;
                        ++listmax;
                    }
                }
            }
            for (int cnt = 0; cnt < 30; ++cnt)
            {
                flt();
                chara_create(-1, 233 + 2 * (cnt > 22), 11, 16);
                cdata[rc].relationship = 10;
                cdata[rc].original_relationship = 10;
                cdata[rc].hate = 100;
                p = list(0, rnd(listmax));
                cdata[rc].enemy_id = p;
                cdata[p].hate = 100;
                cdata[p].enemy_id = rc;
            }
            noaggrorefresh = 1;
        }
    }
    if (gdata_current_map == mdata_t::map_id_t::noyel)
    {
        mdata_map_max_crowd_density = 35;
        map_initcustom(u8"noyel"s);
        map_placeplayer();
        mdata_map_user_map_flag = 0;
        flt();
        chara_create(-1, 202, 46, 18);
        gdata_fire_giant = rc;
        cdata[rc].character_role = 3;
        flt();
        chara_create(-1, 203, 47, 18);
        cdata[rc].character_role = 1015;
        flt();
        chara_create(-1, 35, 47, 20);
        cdata[rc].character_role = 3;
        flt();
        chara_create(-1, 35, 45, 19);
        cdata[rc].character_role = 3;
        flt();
        chara_create(-1, 35, 49, 20);
        cdata[rc].character_role = 3;
        flt();
        chara_create(-1, 326, 28, 22);
        cdata[rc].character_role = 3;
        flt();
        chara_create(-1, 221, 19, 3);
        cdata[rc].character_role = 3;
        if (gdata_pael_and_her_mom != 1001)
        {
            flt();
            chara_create(-1, 222, 19, 2);
            cdata[rc].character_role = 3;
        }
        flt();
        chara_create(-1, 70, 40, 33);
        cdata[rc].character_role = 9;
        flt();
        chara_create(-1, 74, 44, 6);
        cdata[rc].character_role = 12;
        flt();
        chara_create(-1, 206, 44, 3);
        cdata[rc].character_role = 19;
        flt();
        chara_create(-1, 1, 19, 31);
        cdata[rc].character_role = 1001;
        cdata[rc].shop_rank = 12;
        cdatan(0, rc) = snarmor(cdatan(0, rc));
        flt();
        chara_create(-1, 1, 11, 31);
        cdata[rc].character_role = 1006;
        cdata[rc].shop_rank = 10;
        cdatan(0, rc) = sngeneral(cdatan(0, rc));
        flt();
        chara_create(-1, 1, 38, 34);
        cdata[rc].character_role = 1005;
        cdata[rc].shop_rank = 8;
        cdatan(0, rc) = sninn(cdatan(0, rc));
        flt();
        chara_create(-1, 1, 5, 27);
        cdata[rc].character_role = 1003;
        cdata[rc].shop_rank = 9;
        cdatan(0, rc) = snbakery(cdatan(0, rc));
        cdata[rc].image = 138;
        flt();
        chara_create(-1, 41, 56, 5);
        cdata[rc].character_role = 1004;
        cdata[rc].shop_rank = 11;
        cdatan(0, rc) = snmagic(cdatan(0, rc));
        flt();
        chara_create(-1, 1, 39, 35);
        cdata[rc].character_role = 1009;
        cdata[rc].shop_rank = 12;
        cdatan(0, rc) = sntrade(cdatan(0, rc));
        flt();
        chara_create(-1, 38, 5, 18);
        cdata[rc].character_role = 6;
        cdatan(0, rc) =
            i18n::s.get("core.locale.chara.job.of_noyel", cdatan(0, rc));
        flt();
        chara_create(-1, 40, 18, 20);
        cdata[rc].character_role = 7;
        cdatan(0, rc) = sntrainer(cdatan(0, rc));
        flt();
        chara_create(-1, 41, 4, 33);
        cdata[rc].character_role = 5;
        flt();
        chara_create(-1, 69, 6, 33);
        cdata[rc].character_role = 8;
        for (int cnt = 0; cnt < 3; ++cnt)
        {
            flt();
            chara_create(-1, 16, rnd(32), rnd(mdata_map_height));
            cdata[rc].character_role = 4;
            flt();
            chara_create(-1, 39, rnd(32), rnd(mdata_map_height));
            cdata[rc].character_role = 4;
        }
        for (int cnt = 0; cnt < 3; ++cnt)
        {
            flt();
            chara_create(-1, 77, rnd(32), rnd(mdata_map_height));
            cdata[rc].character_role = 14;
        }
        quest_on_map_initialize();
        for (int cnt = 0; cnt < 8; ++cnt)
        {
            chara_set_generation_filter();
            chara_create(-1, 35, rnd(11) + 25, rnd(5) + 15);
            cdata[rc].character_role = 3;
        }
        for (int cnt = 0; cnt < 20; ++cnt)
        {
            dbid = 0;
            chara_set_generation_filter();
            chara_create(-1, dbid, rnd(55), rnd(mdata_map_height));
        }
    }
    if (gdata_current_map == mdata_t::map_id_t::port_kapul)
    {
        if (gdata_current_dungeon_level == 1)
        {
            mdata_map_max_crowd_density = 40;
            map_initcustom(u8"kapul"s);
            map_placeplayer();
            mdata_map_user_map_flag = 0;
            flt();
            chara_create(-1, 223, 15, 18);
            cdata[rc].character_role = 3;
            flt();
            chara_create(-1, 243, 36, 27);
            cdata[rc].character_role = 3;
            flt();
            chara_create(-1, 279, 5, 26);
            cdata[rc].character_role = 3;
            flt();
            chara_create(-1, 297, 29, 3);
            cdata[rc].character_role = 3;
            flt();
            chara_create(-1, 320, 24, 21);
            cdata[rc].character_role = 3;
            flt();
            chara_create(-1, 320, 12, 26);
            cdata[rc].character_role = 3;
            flt();
            chara_create(-1, 320, 8, 11);
            cdata[rc].character_role = 3;
            flt();
            chara_create(-1, 326, 8, 14);
            cdata[rc].character_role = 3;
            flt();
            chara_create(-1, 1, 16, 17);
            cdata[rc].character_role = 1009;
            cdata[rc].shop_rank = 12;
            cdatan(0, rc) = sntrade(cdatan(0, rc));
            flt();
            chara_create(-1, 1, 23, 7);
            cdata[rc].character_role = 1001;
            cdata[rc].shop_rank = 12;
            cdatan(0, rc) = snarmor(cdatan(0, rc));
            flt();
            chara_create(-1, 1, 32, 14);
            cdata[rc].character_role = 1006;
            cdata[rc].shop_rank = 10;
            cdatan(0, rc) = sngeneral(cdatan(0, rc));
            flt();
            chara_create(-1, 1, 22, 14);
            cdata[rc].character_role = 1008;
            cdata[rc].shop_rank = 10;
            cdatan(0, rc) = sngoods(cdatan(0, rc));
            flt();
            chara_create(-1, 1, 16, 25);
            cdata[rc].character_role = 1007;
            cdata[rc].shop_rank = 10;
            cdatan(0, rc) = snblack(cdatan(0, rc));
            flt();
            chara_create(-1, 1, 17, 28);
            cdata[rc].character_role = 1002;
            cdata[rc].shop_rank = 10;
            cdatan(0, rc) = snfood(cdatan(0, rc));
            flt();
            chara_create(-1, 41, 22, 22);
            cdata[rc].character_role = 1004;
            cdata[rc].shop_rank = 11;
            cdatan(0, rc) = snmagic(cdatan(0, rc));
            flt();
            chara_create(-1, 1, 35, 3);
            cdata[rc].character_role = 1005;
            cdata[rc].shop_rank = 8;
            cdatan(0, rc) = sninn(cdatan(0, rc));
            flt();
            chara_create(-1, 70, 15, 15);
            cdata[rc].character_role = 9;
            flt();
            chara_create(-1, 73, 26, 3);
            cdata[rc].character_role = 10;
            flt();
            chara_create(-1, 179, 25, 4);
            cdata[rc].character_role = 11;
            flt();
            chara_create(-1, 38, 8, 12);
            cdata[rc].character_role = 6;
            cdatan(0, rc) = i18n::s.get(
                "core.locale.chara.job.of_port_kapul", cdatan(0, rc));
            flt();
            chara_create(-1, 40, 16, 4);
            cdata[rc].character_role = 7;
            cdatan(0, rc) = sntrainer(cdatan(0, rc));
            flt();
            chara_create(-1, 41, 14, 4);
            cdata[rc].character_role = 5;
            flt();
            chara_create(-1, 69, 17, 5);
            cdata[rc].character_role = 8;
            flt();
            chara_create(-1, 74, 27, 11);
            cdata[rc].character_role = 12;
            for (int cnt = 0; cnt < 2; ++cnt)
            {
                flt();
                chara_create(-1, 16, -3, 0);
                cdata[rc].character_role = 4;
                flt();
                chara_create(-1, 39, -3, 0);
                cdata[rc].character_role = 4;
            }
            for (int cnt = 0; cnt < 4; ++cnt)
            {
                flt();
                chara_create(-1, 71, -3, 0);
                cdata[rc].character_role = 4;
            }
            for (int cnt = 0; cnt < 5; ++cnt)
            {
                flt();
                chara_create(-1, 76, -3, 0);
                cdata[rc].character_role = 14;
            }
            flt();
            chara_create(-1, 72, 7, 6);
            cdata[rc].character_role = 4;
            quest_on_map_initialize();
            for (int cnt = 0; cnt < 20; ++cnt)
            {
                chara_set_generation_filter();
                chara_create(-1, 0, -3, 0);
            }
        }
        if (gdata_current_dungeon_level == 3)
        {
            mdata_map_tileset = 0;
            map_initcustom(u8"fighterguild"s);
            mdata_map_indoors_flag = 1;
            mdata_map_type = mdata_t::map_type_t::guild;
            mdata_map_max_crowd_density = 25;
            mdata_map_bgm = 79;
            mdata_map_should_regenerate = 0;
            mdatan(0) =
                i18n::s.get("core.locale.map.unique.fighters_guild.name");
            map_placeplayer();
            flt();
            chara_create(-1, 291, 27, 4);
            cdata[rc].character_role = 3;
            flt();
            chara_create(-1, 74, 28, 10);
            cdata[rc].character_role = 12;
            flt();
            chara_create(-1, 40, 15, 10);
            cdata[rc].character_role = 7;
            cdatan(0, rc) = sntrainer(cdatan(0, rc));
            flt();
            chara_create(-1, 41, 14, 18);
            cdata[rc].character_role = 5;
            flt();
            chara_create(-1, 1, 29, 15);
            cdata[rc].character_role = 1001;
            cdata[rc].shop_rank = 12;
            cdatan(0, rc) = snarmor(cdatan(0, rc));
            for (int cnt = 0; cnt < 16; ++cnt)
            {
                flt();
                chara_create(-1, 295, -3, 0);
            }
        }
        if (gdata_current_dungeon_level == 25)
        {
            mdata_map_tileset = 0;
            map_initcustom(u8"sqkamikaze"s);
            mdata_map_indoors_flag = 2;
            mdata_map_type = mdata_t::map_type_t::dungeon;
            mdata_map_max_crowd_density = 0;
            mdata_map_bgm = 61;
            mdata_map_should_regenerate = 1;
            mdata_map_refresh_type = 0;
            mdatan(0) = i18n::s.get("core.locale.map.unique.doom_ground.name");
            gdata_entrance_type = 4;
            gdata_duration_of_kamikaze_attack = 0;
            map_placeplayer();
            for (int cnt = 0; cnt < 10; ++cnt)
            {
                flt();
                chara_create(
                    -1,
                    204,
                    cdata.player().position.x,
                    cdata.player().position.y);
                cdata[rc].relationship = 10;
                cdata[rc].original_relationship = 10;
            }
            noaggrorefresh = 1;
        }
    }
    if (gdata_current_map == mdata_t::map_id_t::vernis)
    {
        if (gdata_current_dungeon_level == 1)
        {
            mdata_map_max_crowd_density = 40;
            map_initcustom(u8"vernis"s);
            map_placeplayer();
            mdata_map_user_map_flag = 0;
            if (gdata_thieves_hideout)
            {
                cell_featset(48, 5, tile_downstairs, 11, 4);
            }
            flt();
            chara_create(-1, 28, 39, 3);
            flt();
            chara_create(-1, 29, 42, 23);
            cdata[rc].character_role = 3;
            flt();
            chara_create(-1, 30, 24, 5);
            cdata[rc].character_role = 3;
            flt();
            chara_create(-1, 31, 40, 24);
            cdata[rc].character_role = 3;
            flt();
            chara_create(-1, 32, 40, 25);
            cdata[rc].character_role = 3;
            flt();
            chara_create(-1, 226, 30, 5);
            cdata[rc].character_role = 3;
            flt();
            chara_create(-1, 326, 42, 24);
            cdata[rc].character_role = 3;
            if (gdata_puppys_cave == 1000)
            {
                flt();
                chara_create(-1, 225, 31, 4);
                cdata[rc].character_role = 3;
            }
            flt();
            chara_create(-1, 1, 47, 9);
            cdata[rc].character_role = 1014;
            cdata[rc].shop_rank = 5;
            cdatan(0, rc) = snfish(cdatan(0, rc));
            flt();
            chara_create(-1, 1, 14, 12);
            cdata[rc].character_role = 1001;
            cdata[rc].shop_rank = 12;
            cdatan(0, rc) = snarmor(cdatan(0, rc));
            flt();
            chara_create(-1, 1, 39, 27);
            cdata[rc].character_role = 1009;
            cdata[rc].shop_rank = 12;
            cdatan(0, rc) = sntrade(cdatan(0, rc));
            flt();
            chara_create(-1, 1, 10, 15);
            cdata[rc].character_role = 1006;
            cdata[rc].shop_rank = 10;
            cdatan(0, rc) = sngeneral(cdatan(0, rc));
            flt();
            chara_create(-1, 41, 7, 26);
            cdata[rc].character_role = 1004;
            cdata[rc].shop_rank = 11;
            cdatan(0, rc) = snmagic(cdatan(0, rc));
            flt();
            chara_create(-1, 1, 14, 25);
            cdata[rc].character_role = 1005;
            cdata[rc].shop_rank = 8;
            cdatan(0, rc) = sninn(cdatan(0, rc));
            flt();
            chara_create(-1, 1, 22, 26);
            cdata[rc].character_role = 1003;
            cdata[rc].shop_rank = 9;
            cdatan(0, rc) = snbakery(cdatan(0, rc));
            cdata[rc].image = 138;
            flt();
            chara_create(-1, 41, 28, 16);
            cdata[rc].character_role = 5;
            flt();
            chara_create(-1, 70, 38, 27);
            cdata[rc].character_role = 9;
            flt();
            chara_create(-1, 74, 6, 25);
            cdata[rc].character_role = 12;
            flt();
            chara_create(-1, 38, 10, 7);
            cdata[rc].character_role = 6;
            cdatan(0, rc) =
                i18n::s.get("core.locale.chara.job.of_vernis", cdatan(0, rc));
            flt();
            chara_create(-1, 40, 27, 16);
            cdata[rc].character_role = 7;
            cdatan(0, rc) = sntrainer(cdatan(0, rc));
            flt();
            chara_create(-1, 69, 25, 16);
            cdata[rc].character_role = 8;
            for (int cnt = 0; cnt < 4; ++cnt)
            {
                flt();
                chara_create(-1, 16, -3, 0);
                cdata[rc].character_role = 4;
                flt();
                chara_create(-1, 39, -3, 0);
                cdata[rc].character_role = 4;
            }
            for (int cnt = 0; cnt < 4; ++cnt)
            {
                flt();
                chara_create(-1, 77, -3, 0);
                cdata[rc].character_role = 14;
            }
            quest_on_map_initialize();
            for (int cnt = 0; cnt < 25; ++cnt)
            {
                dbid = 0;
                chara_set_generation_filter();
                chara_create(-1, dbid, -3, 0);
            }
        }
        if (gdata_current_dungeon_level == 3)
        {
            mdata_map_tileset = 0;
            map_initcustom(u8"puti"s);
            mdata_map_indoors_flag = 1;
            mdata_map_type = mdata_t::map_type_t::dungeon;
            mdata_map_max_crowd_density = 0;
            mdata_map_bgm = 61;
            mdata_map_should_regenerate = 1;
            mdatan(0) = i18n::s.get("core.locale.map.unique.the_mine.name");
            quest_place_target();
            map_placeplayer();
        }
        if (gdata_current_dungeon_level == 4)
        {
            mdata_map_tileset = 0;
            map_initcustom(u8"sqrogue"s);
            mdata_map_indoors_flag = 1;
            mdata_map_type = mdata_t::map_type_t::dungeon;
            mdata_map_max_crowd_density = 0;
            mdata_map_bgm = 61;
            mdata_map_should_regenerate = 1;
            mdatan(0) =
                i18n::s.get("core.locale.map.unique.robbers_hideout.name");
            quest_place_target();
            map_placeplayer();
        }
        if (gdata_current_dungeon_level == 5)
        {
            mdata_map_tileset = 0;
            map_initcustom(u8"sqNightmare"s);
            mdata_map_indoors_flag = 1;
            mdata_map_type = mdata_t::map_type_t::dungeon;
            mdata_map_max_crowd_density = 0;
            mdata_map_bgm = 61;
            mdata_map_should_regenerate = 1;
            mdatan(0) = i18n::s.get("core.locale.map.unique.test_site.name");
            quest_place_target();
            gdata_entrance_type = 7;
            mapstartx = 6;
            mapstarty = 27;
            map_placeplayer();
        }
    }
    if (gdata_current_map == mdata_t::map_id_t::debug_map)
    {
        generate_debug_map();
    }
    if (gdata_current_map == mdata_t::map_id_t::fields)
    {
        mdata_map_width = 34;
        mdata_map_height = 22;
        mdata_map_max_crowd_density = 4;
        mdata_map_user_map_flag = 0;
        map_initialize();
        for (int cnt = 0, cnt_end = (mdata_map_height); cnt < cnt_end; ++cnt)
        {
            p = cnt;
            for (int cnt = 0, cnt_end = (mdata_map_width); cnt < cnt_end; ++cnt)
            {
                map(cnt, p, 0) = tile_default
                    + (rnd(tile_default(2)) == 0) * rnd(tile_default(1));
            }
        }
        mdatan(0) = "";
        if (4 <= gdata(62) && gdata(62) < 9)
        {
            mdatan(0) = i18n::s.get_enum_property(
                "core.locale.map.unique", "forest", 2);
            map_randomtile(8, 25);
            map_randomtile(0, 10);
            map_randomtile(1, 4);
            map_randomtile(4, 2);
            for (int cnt = 0, cnt_end = (20 + rnd(20)); cnt < cnt_end; ++cnt)
            {
                flt();
                flttypemajor = 80000;
                itemcreate(-1, 0, -1, -1, 0);
                inv[ci].own_state = 1;
                map(inv[ci].position.x, inv[ci].position.y, 0) = 0;
            }
        }
        if (264 <= gdata(62) && gdata(62) < 363)
        {
            mdatan(0) =
                i18n::s.get_enum_property("core.locale.map.unique", "sea", 2);
        }
        if (9 <= gdata(62) && gdata(62) < 13)
        {
            mdatan(0) = i18n::s.get_enum_property(
                "core.locale.map.unique", "grassland", 2);
            map_randomtile(9, 10);
            map_randomtile(10, 10);
            map_randomtile(0, 30);
            map_randomtile(1, 4);
            map_randomtile(4, 2);
            map_randomtile(3, 2);
            map_randomtile(4, 2);
            map_randomtile(5, 2);
            for (int cnt = 0, cnt_end = (10 + rnd(10)); cnt < cnt_end; ++cnt)
            {
                flt();
                flttypemajor = 80000;
                itemcreate(-1, 0, -1, -1, 0);
                inv[ci].own_state = 1;
            }
        }
        if (13 <= gdata(62) && gdata(62) < 17)
        {
            mdatan(0) = i18n::s.get_enum_property(
                "core.locale.map.unique", "desert", 2);
            map_randomtile(18, 25);
            map_randomtile(17, 10);
            map_randomtile(19, 2);
            map_randomtile(20, 4);
            map_randomtile(21, 2);
            for (int cnt = 0, cnt_end = (4 + rnd(4)); cnt < cnt_end; ++cnt)
            {
                flt();
                itemcreate(-1, 527, -1, -1, 0);
                inv[ci].own_state = 1;
            }
        }
        if (chipm(0, gdata(62)) == 4)
        {
            mdatan(0) = i18n::s.get_enum_property(
                "core.locale.map.unique", "snow_field", 2);
            map_randomtile(57, 4);
            map_randomtile(56, 4);
            map_randomtile(49, 2);
            map_randomtile(46, 1);
            map_randomtile(47, 1);
            map_randomtile(48, 1);
            map_randomtile(51, 1);
            for (int cnt = 0, cnt_end = (3 + rnd(5)); cnt < cnt_end; ++cnt)
            {
                flt();
                flttypemajor = 80000;
                fltselect = 8;
                itemcreate(-1, 0, -1, -1, 0);
                inv[ci].own_state = 1;
            }
        }
        if (mdatan(0) == ""s)
        {
            mdatan(0) = i18n::s.get_enum_property(
                "core.locale.map.unique", "plain_field", 2);
            map_randomtile(1, 10);
            map_randomtile(2, 2);
            map_randomtile(3, 2);
            map_randomtile(4, 2);
            map_randomtile(5, 2);
            map_randomtile(6, 2);
            for (int cnt = 0, cnt_end = (5 + rnd(5)); cnt < cnt_end; ++cnt)
            {
                flt();
                flttypemajor = 80000;
                itemcreate(-1, 0, -1, -1, 0);
                inv[ci].own_state = 1;
            }
        }
        map_placeplayer();
        if (264 > gdata(62) || gdata(62) >= 363)
        {
            for (int cnt = 0, cnt_end = (4 + rnd(5)); cnt < cnt_end; ++cnt)
            {
                flt();
                flttypeminor = 64000;
                itemcreate(-1, 0, -1, -1, 0);
            }
        }
        if (encounter == 0)
        {
            for (int cnt = 0, cnt_end = (mdata_map_max_crowd_density + 1);
                 cnt < cnt_end;
                 ++cnt)
            {
                chara_set_generation_filter();
                flt();
                chara_create(-1, 0, -3, 0);
            }
        }
        if (encounter == 4)
        {
            mdata_map_max_crowd_density = 0;
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
            gdatan(1) = random_title(2);
            event_add(23);
        }
        if (encounter == 3)
        {
            mdata_map_max_crowd_density = 0;
            mdata_map_type = mdata_t::map_type_t::temporary;
            rq = encounterref;
            gdata_executing_immediate_quest_type = 1007;
            gdata(71) = 1;
            gdata_executing_immediate_quest = rq;
            gdata(73) = 1;
            p = rnd(3) + 5;
            for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
            {
                flt(qdata(5, rq), 3);
                int stat = chara_create(
                    -1,
                    0,
                    cdata.player().position.x,
                    cdata.player().position.y);
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
            for (int cnt = 0, cnt_end = (encounterlv / 2 + 1); cnt < cnt_end;
                 ++cnt)
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
                flt(calcobjlv(encounterlv), calcfixlv(2));
                if (gdata_weather == 1)
                {
                    if ((33 > gdata(62) || gdata(62) >= 66) && rnd(3) == 0)
                    {
                        fixlv = 5;
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
    if (gdata_current_map == mdata_t::map_id_t::the_void)
    {
        generate_random_nefia();
        if (gdata(186) == 0)
        {
            gdata(186) = adata(17, gdata_current_map) + 4;
        }
        if (gdata(186) <= gdata_current_dungeon_level)
        {
            event_add(29);
        }
        else
        {
            adata(20, gdata_current_map) = 0;
        }
    }
    if (gdata_current_map == mdata_t::map_id_t::lesimas)
    {
        map_tileset(mdata_map_tileset);
        for (int cnt = 0; cnt < 1; ++cnt)
        {
            if (gdata_current_dungeon_level == adata(10, gdata_current_map))
            {
                map_initcustom(u8"lesimas_1"s);
                mdata_map_max_crowd_density = 0;
                mdata_map_refresh_type = 0;
                mdata_map_bgm = 66;
                mdatan(0) = i18n::s.get_enum_property(
                    "core.locale.map.unique", "the_depth", 3);
                if (gdata_main_quest_flag < 170)
                {
                    event_add(3);
                }
                x = 16;
                y = 13;
                cell_featset(x, y, tile_upstairs, 10);
                mdata_map_stair_up_pos = y * 1000 + x;
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
                break;
            }
            generate_random_nefia();
            break;
        }
        if (gdata_current_dungeon_level == 3)
        {
            chara_create(
                -1, 139, cdata.player().position.x, cdata.player().position.y);
            cdata[rc].character_role = 3;
            cdata[rc].ai_calm = 3;
        }
        if (gdata_current_dungeon_level == 17)
        {
            chara_create(
                -1, 146, cdata.player().position.x, cdata.player().position.y);
            cdata[rc].character_role = 3;
            cdata[rc].ai_calm = 3;
        }
    }
    if (gdata_current_map == mdata_t::map_id_t::tower_of_fire)
    {
        if (gdata_current_dungeon_level == adata(10, gdata_current_map))
        {
            map_initcustom(u8"firet1"s);
            mdata_map_max_crowd_density = 0;
            mdata_map_bgm = 66;
            map_placeplayer();
        }
        else
        {
            generate_random_nefia();
        }
    }
    if (gdata_current_map == mdata_t::map_id_t::crypt_of_the_damned)
    {
        if (gdata_current_dungeon_level == adata(10, gdata_current_map))
        {
            map_initcustom(u8"undeadt1"s);
            mdata_map_max_crowd_density = 0;
            mdata_map_bgm = 66;
            map_placeplayer();
        }
        else
        {
            generate_random_nefia();
        }
    }
    if (gdata_current_map == mdata_t::map_id_t::ancient_castle)
    {
        if (gdata_current_dungeon_level == adata(10, gdata_current_map))
        {
            map_initcustom(u8"roguet1"s);
            mdata_map_max_crowd_density = 0;
            mdata_map_bgm = 66;
            map_placeplayer();
        }
        else
        {
            generate_random_nefia();
        }
    }
    if (gdata_current_map == mdata_t::map_id_t::dragons_nest)
    {
        if (gdata_current_dungeon_level == adata(10, gdata_current_map))
        {
            map_initcustom(u8"d_1"s);
            mdata_map_max_crowd_density = 0;
            mdata_map_bgm = 66;
            map_placeplayer();
        }
        else
        {
            generate_random_nefia();
        }
    }
    if (gdata_current_map == mdata_t::map_id_t::puppy_cave)
    {
        generate_random_nefia();
        if (gdata_current_dungeon_level == adata(10, gdata_current_map))
        {
            if (gdata_puppys_cave < 2)
            {
                if (chara_find_ally(225) == -1)
                {
                    flt();
                    chara_create(-1, 225, -3, 0);
                    cdata[rc].does_not_search_enemy() = true;
                }
            }
        }
    }
    if (gdata_current_map == mdata_t::map_id_t::minotaurs_nest)
    {
        generate_random_nefia();
        if (gdata_current_dungeon_level == adata(10, gdata_current_map))
        {
            if (gdata_minotaur_king < 2)
            {
                flt();
                chara_create(-1, 300, -3, 0);
            }
        }
    }
    if (gdata_current_map == mdata_t::map_id_t::yeeks_nest)
    {
        generate_random_nefia();
        if (gdata_current_dungeon_level == adata(10, gdata_current_map))
        {
            if (gdata_novice_knight < 2)
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
    if (gdata_current_map == mdata_t::map_id_t::pyramid)
    {
        if (gdata_current_dungeon_level == 20)
        {
            map_initcustom(u8"sqPyramid"s);
            mdata_map_max_crowd_density = 40;
            mdata_map_bgm = 61;
            map_placeplayer();
            for (int cnt = 0, cnt_end = (mdata_map_max_crowd_density + 1);
                 cnt < cnt_end;
                 ++cnt)
            {
                chara_set_generation_filter();
                chara_create(-1, 0, -3, 0);
            }
        }
        if (gdata_current_dungeon_level == 21)
        {
            map_initcustom(u8"sqPyramid2"s);
            mdata_map_max_crowd_density = 0;
            mdata_map_bgm = 61;
            map_placeplayer();
        }
    }
    if (gdata_current_map == mdata_t::map_id_t::mountain_pass)
    {
        generate_random_nefia();
    }
    map_setfog();
    if (gdata_current_map == mdata_t::map_id_t::pet_arena
        || gdata_current_map == mdata_t::map_id_t::arena || dbg_revealmap
        || mdata_map_type == mdata_t::map_type_t::town
        || mdata_map_type == mdata_t::map_type_t::world_map
        || mdata_map_type == mdata_t::map_type_t::player_owned
        || mdata_map_type == mdata_t::map_type_t::guild
        || gdata_current_map == mdata_t::map_id_t::shelter_
        || gdata_current_map == mdata_t::map_id_t::embassy
        || gdata_current_map == mdata_t::map_id_t::miral_and_garoks_workshop
        || gdata_current_map == mdata_t::map_id_t::show_house
        || (gdata_current_map == mdata_t::map_id_t::quest
            && gdata_executing_immediate_quest_type == 1009))
    {
        for (int cnt = 0, cnt_end = (mdata_map_height); cnt < cnt_end; ++cnt)
        {
            y = cnt;
            for (int cnt = 0, cnt_end = (mdata_map_width); cnt < cnt_end; ++cnt)
            {
                map(cnt, y, 2) = map(cnt, y, 0);
            }
        }
    }
    if (mapupdate == 1)
    {
        if (mdata_map_type == mdata_t::map_type_t::world_map)
        {
            f = 0;
            i = 0;
            for (int cnt = 300; cnt < 500; ++cnt)
            {
                p = cnt;
                if (adata(1, cnt) == 0 || adata(2, cnt) == 0
                    || adata(16, cnt) == mdata_t::map_id_t::none)
                {
                    continue;
                }
                for (int cnt = 0; cnt < 300; ++cnt)
                {
                    if (adata(1, cnt) == 0 || adata(2, cnt) == 0
                        || adata(16, cnt) == mdata_t::map_id_t::none)
                    {
                        continue;
                    }
                    if (adata(1, p) == adata(1, cnt))
                    {
                        if (adata(2, p) == adata(2, cnt))
                        {
                            for (int cnt = 0;; ++cnt)
                            {
                                dx = clamp(
                                    rnd(cnt / 4 + 1) + 1, 1, mdata_map_width);
                                dy = clamp(
                                    rnd(cnt / 4 + 1) + 1, 1, mdata_map_height);
                                x = adata(1, p) + rnd(dx) - rnd(dx);
                                y = adata(2, p) + rnd(dy) - rnd(dy);
                                if (x < 0 || y < 0 || x >= mdata_map_width
                                    || y >= mdata_map_height)
                                {
                                    continue;
                                }
                                if (33 <= map(x, y, 0) && map(x, y, 0) < 66)
                                {
                                    continue;
                                }
                                if (map(x, y, 0) > 19)
                                {
                                    continue;
                                }
                                i = 1;
                                for (int cnt = 0, cnt_end = (300);
                                     cnt < cnt_end;
                                     ++cnt)
                                {
                                    if (adata(1, cnt) == 0 || adata(2, cnt) == 0
                                        || adata(16, cnt)
                                            == mdata_t::map_id_t::none)
                                    {
                                        continue;
                                    }
                                    if (x == adata(1, cnt))
                                    {
                                        if (y == adata(2, cnt))
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
                                    "core.locale.map.location_changed",
                                    mapname(p),
                                    adata(1, p),
                                    adata(2, p),
                                    x(0),
                                    y(0)));
                                adata(1, p) = x;
                                adata(2, p) = y;
                                ++f;
                                break;
                            }
                        }
                    }
                }
            }
            map_global_prepare();
        }
        mapupdate = 0;
        for (auto&& cnt : cdata.all())
        {
            if (cnt.state() == character::state_t::empty)
            {
                continue;
            }
            if ((cnt.character_role >= 1000 && cnt.character_role < 2000)
                || cnt.character_role == 2003)
            {
                int cnt2 = cnt.index;
                for (int cnt = 0, cnt_end = (maxnpcbk); cnt < cnt_end; ++cnt)
                {
                    if (cdata[cnt2].character_role == rolebk(0, cnt))
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
    randomize();
    mdata_map_regenerate_count = gdata(184);
    mdata_map_mefs_loaded_flag = 1;
    lua::lua->get_event_manager()
        .run_callbacks<lua::event_kind_t::map_created>();
    loaded_from_file = false;
label_1742_internal:
    if (gdata_current_map == mdata_t::map_id_t::north_tyris)
    {
        if (gdata_main_quest_flag == 180)
        {
            cdata.player().position.x = adata(1, 11);
            cdata.player().position.y = adata(2, 11);
            gdata(35) = 1;
            gdata(60) = -1;
            msg_newline();
            msgtemp =
                "  " + i18n::s.get("core.locale.scenario.three_years_later");
        }
    }
    for (int cnt = 16; cnt < 55; ++cnt)
    {
        if (cdata[cnt].state() != character::state_t::adventurer_in_other_map)
        {
            continue;
        }
        if (cdata[cnt].is_contracting())
        {
            cdata[cnt].relationship = 10;
            cdata[cnt].current_map = gdata_current_map;
            goto label_1743_internal;
        }
        if (cdata[cnt].current_map != gdata_current_map)
        {
            continue;
        }
        if (mdata_map_type != mdata_t::map_type_t::town
            && mdata_map_type != mdata_t::map_type_t::guild)
        {
            continue;
        }
        if (gdata_current_dungeon_level != 1)
        {
            continue;
        }
    label_1743_internal:
        if (gdata_current_map == mdata_t::map_id_t::arena
            || gdata_current_map == mdata_t::map_id_t::pet_arena)
        {
            continue;
        }
        rc = cnt;
        cdata[rc].set_state(character::state_t::alive);
        if (cdata[cnt].is_contracting() == 1)
        {
            cxinit = cdata.player().position.x;
            cyinit = cdata.player().position.y;
            chara_place();
        }
        else
        {
            cxinit = -1;
            chara_place();
            cdata[rc].hp = cdata[rc].max_hp;
            cdata[rc].mp = cdata[rc].max_mp;
        }
        chara_refresh(cnt);
    }
    if (mdata_map_refresh_type == 1)
    {
        if (gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
                + gdata_year * 24 * 30 * 12
            >= mdata_map_next_regenerate_date)
        {
            if (mdata_map_should_regenerate == 0)
            {
                if (mdata_map_next_regenerate_date != 0)
                {
                    if (gdata_current_dungeon_level == 1)
                    {
                        if (gdata_current_map == mdata_t::map_id_t::lumiest)
                        {
                            map_reload(u8"lumiest"s);
                        }
                        if (gdata_current_map == mdata_t::map_id_t::vernis)
                        {
                            map_reload(u8"vernis"s);
                        }
                        if (gdata_current_map == mdata_t::map_id_t::palmia)
                        {
                            map_reload(u8"palmia"s);
                        }
                        if (gdata_current_map == mdata_t::map_id_t::port_kapul)
                        {
                            map_reload(u8"kapul"s);
                        }
                        if (gdata_current_map == mdata_t::map_id_t::yowyn)
                        {
                            map_reload(u8"yowyn"s);
                        }
                        if (gdata_current_map == mdata_t::map_id_t::derphy)
                        {
                            map_reload(u8"rogueden"s);
                        }
                        if (gdata_current_map == mdata_t::map_id_t::noyel)
                        {
                            if (gdata_month == 12)
                            {
                                if (adata(29, gdata_current_map) == 0)
                                {
                                    adata(29, gdata_current_map) = 1;
                                    map_reload_noyel();
                                }
                                map_reload(u8"noyel_fest"s);
                            }
                            else
                            {
                                if (adata(29, gdata_current_map) == 1)
                                {
                                    adata(29, gdata_current_map) = 0;
                                    map_reload_noyel();
                                }
                                map_reload(u8"noyel"s);
                            }
                            gdata_released_fire_giant = 0;
                        }
                    }
                }
            }
        }
        for (int cnt = 0, cnt_end = (mdata_map_height); cnt < cnt_end; ++cnt)
        {
            y = cnt;
            for (int cnt = 0, cnt_end = (mdata_map_width); cnt < cnt_end; ++cnt)
            {
                map(cnt, y, 1) = 0;
            }
        }
        for (auto&& cnt : cdata.all())
        {
            rc = cnt.index;
            cdata[rc].was_passed_item_by_you_just_now() = false;
            if (rc < 57)
            {
                if (mode == 11)
                {
                    continue;
                }
            }
            if (cdata[rc].state() == character::state_t::villager_dead)
            {
                if (gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
                        + gdata_year * 24 * 30 * 12
                    >= cdata[rc].time_to_revive)
                {
                    revive_player();
                }
                else
                {
                    continue;
                }
            }
            if (cdata[rc].state() != character::state_t::alive)
            {
                continue;
            }
            if (cdata[rc].character_role == 14)
            {
                if (cdata.player().karma < -30)
                {
                    if (cdata.player().level > cdata[rc].level)
                    {
                        r2 = 1;
                        gain_level(cdata[rc]);
                    }
                }
            }
            if (rc >= 57)
            {
                cdata[rc].hp = cdata[rc].max_hp;
                cdata[rc].mp = cdata[rc].max_mp;
                cdata[rc].insanity = 0;
            }
            if (rc >= 57)
            {
                if (mdata_map_designated_spawns == 1)
                {
                    cdata[rc].position.x = cdata[rc].initial_position.x;
                    cdata[rc].position.y = cdata[rc].initial_position.y;
                }
                if (cdata[rc].is_quest_target() == 0)
                {
                    cdata[rc].hate = 0;
                    cdata[rc].relationship = cdata[rc].original_relationship;
                }
                if (cdata[rc].character_role == 14)
                {
                    if (cdata.player().karma < -30)
                    {
                        if (cdata.player().is_incognito() == 0)
                        {
                            cdata[rc].hate = 200;
                            cdata[rc].relationship = -3;
                        }
                    }
                }
                if (mdata_map_type == mdata_t::map_type_t::town
                    || mdata_map_type == mdata_t::map_type_t::guild)
                {
                    cdata[rc].sleep = 0;
                    if (gdata_hour >= 22 || gdata_hour < 7)
                    {
                        if (rnd(6) == 0)
                        {
                            cdata[rc].sleep = rnd(400);
                        }
                    }
                }
            }
            if (rc == 0 || gdata_mount != rc)
            {
                cell_check(cdata[rc].position.x, cdata[rc].position.y);
                if (map(cdata[rc].position.x, cdata[rc].position.y, 1) != 0
                    || cellaccess != 1)
                {
                    for (int cnt = 0;; ++cnt)
                    {
                        x = cdata[rc].position.x + rnd((cnt / 2 + 2))
                            - rnd((cnt / 2 + 2));
                        y = cdata[rc].position.y + rnd((cnt / 2 + 2))
                            - rnd((cnt / 2 + 2));
                        if (cnt > 100)
                        {
                            x = rnd(mdata_map_width);
                            y = rnd(mdata_map_height);
                        }
                        if (cnt > 1000)
                        {
                            break;
                        }
                        cell_check(x, y);
                        if (cellaccess == 1)
                        {
                            cdata[rc].position.x = x;
                            cdata[rc].position.y = y;
                            break;
                        }
                    }
                }
            }
            if (cdata[rc].is_ridden() == 0)
            {
                map(cdata[rc].position.x, cdata[rc].position.y, 1) = rc + 1;
            }
        }
    }
label_1744_internal:
    DIM4(efmap, 4, mdata_map_width, mdata_map_height);
    if (mdata_map_width == 0 || mdata_map_height == 0)
    {
        if (medit == 0)
        {
            dialog(i18n::s.get("core.locale.map.loading_failed"));
            mode = 2;
            gdata_current_map = 7;
            gdata_current_dungeon_level = 1;
            gdata_pc_x_in_world_map = adata(1, 7);
            gdata_pc_y_in_world_map = adata(2, 7);
            gdata_previous_map = 2;
            levelexitby = 4;
            goto label_17401;
        }
    }
    map_proc_regen_and_update();
    gdata_crowd_density = 0;
    for (auto&& cnt : cdata.all())
    {
        cnt.turn_cost = 0;
        if (cnt.id == 343)
        {
            getunid(cnt.index);
            chara_refresh(cnt.index);
        }
        if (noaggrorefresh == 0)
        {
            cnt.enemy_id = 0;
            cnt.hate = 0;
        }
        cnt.vision_flag = 0;
        if (cnt.state() != character::state_t::empty)
        {
            modify_crowd_density(cnt.index, 1);
        }
    }
    cdata.player().current_map = gdata_current_map;
    cdata.player().current_dungeon_level = gdata_current_dungeon_level;
    raderx = -1;
    radery = -1;
    raderw = 120 / mdata_map_width + 2;
    raderh = 84 / mdata_map_height + 2;
    scx = cdata.player().position.x;
    scy = cdata.player().position.y;
    msync = 1;
    map_prepare_tileset_atlas();
    ui_initialize_minimap();
    update_scrolling_info();

    if (mdata_map_type == mdata_t::map_type_t::town)
    {
        quest_refresh_list();
    }
    if (mode == 11)
    {
        // This result will be ignored by the caller.
        return turn_result_t::turn_begin;
    }
    if (gdata_main_quest_flag == 9)
    {
        sceneid = 2;
        do_play_scene();
        gdata_main_quest_flag = 10;
    }
    if (gdata_main_quest_flag == 60)
    {
        sceneid = 5;
        do_play_scene();
        gdata_main_quest_flag = 65;
    }
    if (gdata_main_quest_flag == 110)
    {
        sceneid = 26;
        do_play_scene();
        gdata_main_quest_flag = 115;
    }
    if (gdata_main_quest_flag == 115)
    {
        if (gdata_magic_stone_of_fool + gdata_magic_stone_of_king
                + gdata_magic_stone_of_sage
            >= 1)
        {
            sceneid = 28;
            do_play_scene();
            gdata_main_quest_flag = 116;
        }
    }
    if (gdata_main_quest_flag == 116)
    {
        if (gdata_magic_stone_of_fool + gdata_magic_stone_of_king
                + gdata_magic_stone_of_sage
            >= 2)
        {
            sceneid = 29;
            do_play_scene();
            gdata_main_quest_flag = 117;
        }
    }
    if (gdata_main_quest_flag == 117)
    {
        if (gdata_magic_stone_of_fool + gdata_magic_stone_of_king
                + gdata_magic_stone_of_sage
            >= 3)
        {
            sceneid = 30;
            do_play_scene();
            gdata_main_quest_flag = 120;
        }
    }
    if (gdata_current_map == mdata_t::map_id_t::lesimas)
    {
        if (gdata_main_quest_flag == 10)
        {
            sceneid = 3;
            do_play_scene();
            gdata_main_quest_flag = 20;
        }
        if (gdata_current_dungeon_level == 4)
        {
            if (gdata_main_quest_flag == 65)
            {
                sceneid = 7;
                do_play_scene();
                gdata_main_quest_flag = 70;
            }
        }
        if (gdata_current_dungeon_level == 7)
        {
            if (gdata_main_quest_flag == 70)
            {
                sceneid = 15;
                do_play_scene();
                gdata_main_quest_flag = 75;
            }
        }
        if (gdata_current_dungeon_level == 10)
        {
            if (gdata_main_quest_flag == 75)
            {
                sceneid = 16;
                do_play_scene();
                gdata_main_quest_flag = 80;
            }
        }
        if (gdata_current_dungeon_level == 14)
        {
            if (gdata_main_quest_flag == 80)
            {
                sceneid = 17;
                do_play_scene();
                gdata_main_quest_flag = 85;
            }
        }
        if (gdata_current_dungeon_level == 16)
        {
            if (gdata_main_quest_flag == 85)
            {
                sceneid = 24;
                do_play_scene();
                gdata_main_quest_flag = 90;
            }
        }
        if (gdata_current_dungeon_level == 26)
        {
            if (gdata_main_quest_flag == 125)
            {
                sceneid = 33;
                do_play_scene();
                gdata_main_quest_flag = 130;
            }
        }
        if (gdata_current_dungeon_level == 28)
        {
            if (gdata_main_quest_flag == 130)
            {
                sceneid = 35;
                do_play_scene();
                gdata_main_quest_flag = 135;
            }
        }
        if (gdata_current_dungeon_level == 31)
        {
            if (gdata_main_quest_flag == 135)
            {
                sceneid = 40;
                do_play_scene();
                gdata_main_quest_flag = 140;
            }
        }
        if (gdata_current_dungeon_level == 35)
        {
            if (gdata_main_quest_flag == 140)
            {
                sceneid = 60;
                do_play_scene();
                gdata_main_quest_flag = 145;
            }
        }
        if (gdata_current_dungeon_level == 38)
        {
            if (gdata_main_quest_flag == 145)
            {
                sceneid = 70;
                do_play_scene();
                gdata_main_quest_flag = 150;
            }
        }
        if (gdata_current_dungeon_level == 42)
        {
            if (gdata_main_quest_flag == 150)
            {
                sceneid = 90;
                do_play_scene();
                gdata_main_quest_flag = 160;
            }
        }
    }
    if (adata(16, gdata_current_map) == mdata_t::map_id_t::noyel)
    {
        tc = chara_find(222);
        if (tc != 0)
        {
            if (gdata_pael_and_her_mom >= 10)
            {
                cdata[tc].image = 360;
                cdata[tc].portrait = -1;
            }
        }
    }
    if (adata(16, gdata_current_map) == mdata_t::map_id_t::lumiest)
    {
        if (gdata_current_dungeon_level == 3)
        {
            event_add(22, gdata_belongs_to_mages_guild);
        }
    }
    if (adata(16, gdata_current_map) == mdata_t::map_id_t::derphy)
    {
        if (gdata_current_dungeon_level == 3)
        {
            event_add(22, gdata_belongs_to_thieves_guild);
        }
    }
    if (adata(16, gdata_current_map) == mdata_t::map_id_t::port_kapul)
    {
        if (gdata_current_dungeon_level == 3)
        {
            event_add(22, gdata_belongs_to_fighters_guild);
        }
    }
    if (gdata_current_map == mdata_t::map_id_t::vernis)
    {
        if (gdata_main_quest_flag == 0)
        {
            sceneid = 1;
            do_play_scene();
            gdata_main_quest_flag = 9;
        }
        if (gdata_has_not_been_to_vernis == 0)
        {
            gdata_has_not_been_to_vernis = 1;
            event_add(12);
        }
    }
    if (gdata_current_map == mdata_t::map_id_t::palmia)
    {
        if (gdata_main_quest_flag == 30)
        {
            sceneid = 4;
            do_play_scene();
            gdata_main_quest_flag = 40;
        }
        if (gdata_main_quest_flag == 100)
        {
            sceneid = 25;
            do_play_scene();
            gdata_main_quest_flag = 105;
        }
    }
    if (gdata_current_map == mdata_t::map_id_t::north_tyris)
    {
        if (gdata_main_quest_flag == 180)
        {
            sceneid = 100;
            do_play_scene();
            gdata_main_quest_flag = 200;
            gdata_year += 3;
        }
    }
    if (adata(16, gdata_current_map) == mdata_t::map_id_t::random_dungeon)
    {
        if (gdata_current_dungeon_level == adata(10, gdata_current_map))
        {
            if (adata(20, gdata_current_map) == -1)
            {
                msgtemp += i18n::s.get(
                    "core.locale.map.no_dungeon_master",
                    mapname(gdata_current_map));
            }
        }
    }
    play_music();
    initialize_map_adjust_spawns();
    noaggrorefresh = 0;
    if (adata(0, gdata_current_map) == mdata_t::map_type_t::world_map)
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
            txt_conv();
            screenupdate = -1;
            update_screen();
            if (evnum == 0)
            {
                return turn_result_t::pc_turn_user_error;
            }
            else
            {
                return turn_result_t::turn_begin;
            }
        }
        else
        {
            mapsubroutine = 0;
            // This result will be ignored by the caller.
            return turn_result_t::turn_begin;
        }
    }
    wake_up();
    pcattacker = 0;
    cdata.player().enemy_id = 0;
    gdata(94) = 0;
    mode = 0;
    screenupdate = -1;
    update_entire_screen();
    txt_conv();
    if (gdata_current_map == mdata_t::map_id_t::your_home)
    {
        if (gdata_main_quest_flag != 0)
        {
            if (chara_find(33) != 0)
            {
                chara_vanquish(chara_find(33));
            }
            if (chara_find(34) != 0)
            {
                chara_vanquish(chara_find(34));
            }
        }
    }
    if (gdata_current_map == mdata_t::map_id_t::palmia)
    {
        if (gdata_main_quest_flag >= 90)
        {
            if (chara_find(80) != 0)
            {
                chara_vanquish(chara_find(80));
            }
        }
    }
    if (mdata_map_type == mdata_t::map_type_t::town)
    {
        for (int cnt = 0, cnt_end = (gdata_number_of_existing_quests);
             cnt < cnt_end;
             ++cnt)
        {
            if (qdata(3, cnt) == 1007)
            {
                if (qdata(8, cnt) == 1)
                {
                    int cnt2 = cnt;
                    for (int cnt = 0; cnt < 16; ++cnt)
                    {
                        if (cdata[cnt].is_escorted() == 1)
                        {
                            if (cdata[cnt].state() == character::state_t::alive)
                            {
                                if (cdata[cnt].id == qdata(13, cnt2))
                                {
                                    if (qdata(12, cnt2) == gdata_current_map)
                                    {
                                        event_add(16, cnt2, cnt);
                                        cdata[cnt].is_escorted() = false;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (adata(16, gdata_current_map) == mdata_t::map_id_t::museum
        || adata(16, gdata_current_map) == mdata_t::map_id_t::shop)
    {
        for (int cnt = 0; cnt < 5; ++cnt)
        {
            monster_respawn();
        }
    }
    if (mdata_map_refresh_type == 1)
    {
        food_gets_rotten();
    }
    if (adata(16, gdata_current_map) == mdata_t::map_id_t::shop)
    {
        update_shop();
    }
    if (adata(16, gdata_current_map) == mdata_t::map_id_t::museum)
    {
        update_museum();
    }
    if (gdata_current_map == mdata_t::map_id_t::your_home)
    {
        calc_home_rank();
    }
    if (adata(16, gdata_current_map) == mdata_t::map_id_t::ranch)
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
    if (mdata_map_type == mdata_t::map_type_t::world_map)
    {
        if (config::instance().extrahelp)
        {
            if (gdata(202) == 0)
            {
                if (mode == 0)
                {
                    if (cdata.player().continuous_action_turn == 0)
                    {
                        gdata(202) = 1;
                        ghelp = 2;
                        show_ex_help();
                    }
                }
            }
        }
    }
    if (mdata_map_type == mdata_t::map_type_t::town)
    {
        if (config::instance().extrahelp)
        {
            if (gdata(203) == 0)
            {
                if (mode == 0)
                {
                    if (cdata.player().continuous_action_turn == 0)
                    {
                        gdata(203) = 1;
                        ghelp = 3;
                        show_ex_help();
                    }
                }
            }
        }
    }
    if (gdata_current_map == mdata_t::map_id_t::shelter_)
    {
        if (config::instance().extrahelp)
        {
            if (gdata(214) == 0)
            {
                if (mode == 0)
                {
                    if (cdata.player().continuous_action_turn == 0)
                    {
                        gdata(214) = 1;
                        ghelp = 14;
                        show_ex_help();
                    }
                }
            }
        }
    }
    if (mdata_map_type == mdata_t::map_type_t::town
        || gdata_current_map == mdata_t::map_id_t::your_home
        || mdata_map_type == mdata_t::map_type_t::guild)
    {
        if (gdata_distance_between_town >= 16)
        {
            p = gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
                + gdata_year * 24 * 30 * 12 - gdata_departure_date;
            txt(i18n::s.get(
                "core.locale.map.since_leaving.time_passed",
                p / 24,
                p % 24,
                mapname(gdata_left_town_map),
                cnvdate(gdata_departure_date, false)));
            p = 0;
            exp = cdata.player().level * gdata_distance_between_town
                    * sdata(182, 0) / 100
                + 1;
            for (int cnt = 0; cnt < 16; ++cnt)
            {
                if (cdata[cnt].state() != character::state_t::alive)
                {
                    continue;
                }
                if (cnt != 0 && cdata[cnt].current_map)
                {
                    continue;
                }
                ++p;
                cdata[cnt].experience += exp;
            }
            if (p == 1)
            {
                txt(i18n::s.get(
                    "core.locale.map.since_leaving.walked.you",
                    gdata_distance_between_town));
            }
            else
            {
                txt(i18n::s.get(
                    "core.locale.map.since_leaving.walked.you_and_allies",
                    gdata_distance_between_town));
            }
            chara_gain_skill_exp(
                cdata.player(),
                182,
                25 + gdata_distance_between_town * 2 / 3,
                0,
                1000);
            gdata_distance_between_town = 0;
        }
    }
    if (gdata_current_map == mdata_t::map_id_t::quest)
    {
        if (gdata_executing_immediate_quest_type == 1009)
        {
            txtef(9);
            txt(i18n::s.get(
                "core.locale.map.quest.on_enter.party",
                gdata_left_minutes_of_executing_quest,
                qdata(12, gdata_executing_immediate_quest)));
        }
        if (gdata_executing_immediate_quest_type == 1006)
        {
            if (qdata(12, gdata_executing_immediate_quest) <= 0)
            {
                qdata(12, gdata_executing_immediate_quest) = 15000;
                qdata(6, gdata_executing_immediate_quest) = 400;
            }
            txtef(9);
            txt(i18n::s.get(
                "core.locale.map.quest.on_enter.harvest",
                cnvweight(qdata(12, gdata_executing_immediate_quest)),
                gdata_left_minutes_of_executing_quest));
        }
        if (gdata_executing_immediate_quest_type == 1008)
        {
            txtef(9);
            txt(i18n::s.get(
                "core.locale.map.quest.on_enter.conquer",
                chara_refstr(qdata(12, gdata_executing_immediate_quest), 2),
                gdata_left_minutes_of_executing_quest));
        }
    }

    if (loaded_from_file)
    {
        lua::lua->get_event_manager()
            .run_callbacks<lua::event_kind_t::map_loaded>();
    }

    lua::lua->get_event_manager()
        .run_callbacks<lua::event_kind_t::map_initialized>();

    return turn_result_t::turn_begin;
}



} // namespace elona

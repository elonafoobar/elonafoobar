#include "mapgen.hpp"
#include "area.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "ctrl_file.hpp"
#include "elona.hpp"
#include "enums.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "mef.hpp"
#include "quest.hpp"
#include "random.hpp"
#include "variables.hpp"

namespace elona
{

elona_vector2<int> cellobjdata;
int i_at_m68;
int tx_at_m168 = 0;
int ty_at_m168 = 0;
int dir_at_m168 = 0;
int dest_at_m168 = 0;
int dir2_at_m168 = 0;
int tile_pot = 0;
int rdroomnum = 0;
elona_vector1<int> roomexist;
int rdsize = 0;
int rdsecond = 0;
int rdhiddenpath = 0;
int rdpos = 0;
elona_vector1<int> roomwidth;
int cr = 0;
elona_vector1<int> roomheight;
elona_vector1<int> roomx;
elona_vector1<int> roomy;
int roomdoor = 0;
int roomsum = 0;
int rdroomsizemax = 0;
int rdroomsizemin = 0;
int rdroomupstair = 0;
int rdroomdownstair = 0;
int dx_at_m170 = 0;
int dy_at_m170 = 0;
int p_at_m170 = 0;
int tmp_at_m172;
int rdroomentrance = 0;
elona_vector1<int> rdval;
int rdtunnel = 0;
int rdextraroom = 0;
int _mclass = 0;
int _bold = 0;
int rx = 0;
int rw = 0;
int ry = 0;
int rh = 0;

void map_initialize()
{
    if (rdroomnum >= 30)
    {
        rdroomnum = 30;
    }
    for (int cnt = 0; cnt < 30; ++cnt)
    {
        roomexist(cnt) = 0;
    }
    cell_data.init(map_data.width, map_data.height);
    DIM3(mapsync, map_data.width, map_data.height);
    DIM3(mef, 9, MEF_MAX);
    map_tileset(map_data.tileset);
}


void initialize_cell_object_data()
{
    int tile_doorclosed2 = 0;
    int tile_doorclosed3 = 0;
    elona_vector1<std::string> cellobjname;
    int maxobjid = 0;
    tile_trap = 234;
    tile_doorclosed = 726;
    tile_doorclosed2 = 728;
    tile_doorclosed3 = 730;
    tile_doorclosed4 = 733;
    tile_dooropen = 236;
    tile_downstairs = 231;
    tile_upstairs = 232;
    tile_hidden = 0;
    tile_downlocked = 237;
    tile_re = 238;
    tile_plant = 247;
    tile_board = 727;
    tile_votebox = 729;
    tile_townboard = 732;
    DIM3(cellobjdata, 5, 50);
    SDIM3(cellobjname, 20, 50);
    maxobjid = 0;
    cellobjdata(0, maxobjid) = 21;
    cellobjdata(1, maxobjid) = tile_doorclosed;
    cellobjdata(2, maxobjid) = 99;
    cellobjdata(3, maxobjid) = tile_doorclosed;
    cellobjname(maxobjid) = u8"dummy"s;
    ++maxobjid;
    cellobjdata(0, maxobjid) = 21;
    cellobjdata(1, maxobjid) = tile_doorclosed;
    cellobjdata(2, maxobjid) = 99;
    cellobjdata(3, maxobjid) = tile_doorclosed;
    cellobjname(maxobjid) = u8"扉99"s;
    ++maxobjid;
    cellobjdata(0, maxobjid) = 21;
    cellobjdata(1, maxobjid) = tile_doorclosed;
    cellobjdata(2, maxobjid) = 0;
    cellobjdata(3, maxobjid) = tile_doorclosed;
    cellobjname(maxobjid) = u8"扉0"s;
    ++maxobjid;
    cellobjdata(0, maxobjid) = 14;
    cellobjdata(1, maxobjid) = tile_trap;
    cellobjdata(2, maxobjid) = 100;
    cellobjdata(3, maxobjid) = 0;
    cellobjname(maxobjid) = u8"罠"s;
    ++maxobjid;
    cellobjdata(0, maxobjid) = 14;
    cellobjdata(1, maxobjid) = tile_trap;
    cellobjdata(2, maxobjid) = 100;
    cellobjdata(3, maxobjid) = 0;
    cellobjname(maxobjid) = u8"罠"s;
    ++maxobjid;
    cellobjdata(0, maxobjid) = 10;
    cellobjdata(1, maxobjid) = tile_upstairs;
    cellobjdata(2, maxobjid) = 0;
    cellobjdata(3, maxobjid) = tile_upstairs;
    cellobjname(maxobjid) = u8"昇り階段"s;
    ++maxobjid;
    cellobjdata(0, maxobjid) = 11;
    cellobjdata(1, maxobjid) = tile_downstairs;
    cellobjdata(2, maxobjid) = 0;
    cellobjdata(3, maxobjid) = tile_downstairs;
    cellobjname(maxobjid) = u8"降り階段"s;
    ++maxobjid;
    cellobjdata(0, maxobjid) = 21;
    cellobjdata(1, maxobjid) = tile_doorclosed2;
    cellobjdata(2, maxobjid) = 0;
    cellobjdata(3, maxobjid) = tile_doorclosed2;
    cellobjname(maxobjid) = u8"扉SF"s;
    ++maxobjid;
    cellobjdata(0, maxobjid) = 23;
    cellobjdata(1, maxobjid) = tile_board;
    cellobjdata(2, maxobjid) = 0;
    cellobjdata(3, maxobjid) = tile_board;
    cellobjname(maxobjid) = u8"掲示板"s;
    ++maxobjid;
    cellobjdata(0, maxobjid) = 31;
    cellobjdata(1, maxobjid) = tile_votebox;
    cellobjdata(2, maxobjid) = 0;
    cellobjdata(3, maxobjid) = tile_votebox;
    cellobjname(maxobjid) = u8"投票箱"s;
    ++maxobjid;
    cellobjdata(0, maxobjid) = 32;
    cellobjdata(1, maxobjid) = tile_trap;
    cellobjdata(2, maxobjid) = 0;
    cellobjdata(3, maxobjid) = 0;
    cellobjname(maxobjid) = u8"メダル"s;
    ++maxobjid;
    cellobjdata(0, maxobjid) = 21;
    cellobjdata(1, maxobjid) = tile_doorclosed3;
    cellobjdata(2, maxobjid) = 0;
    cellobjdata(3, maxobjid) = tile_doorclosed3;
    cellobjname(maxobjid) = u8"扉JP"s;
    ++maxobjid;
    cellobjdata(0, maxobjid) = 33;
    cellobjdata(1, maxobjid) = tile_townboard;
    cellobjdata(2, maxobjid) = 0;
    cellobjdata(3, maxobjid) = tile_townboard;
    cellobjname(maxobjid) = u8"街掲示板"s;
    ++maxobjid;
    cellobjdata(0, maxobjid) = 21;
    cellobjdata(1, maxobjid) = tile_doorclosed4;
    cellobjdata(2, maxobjid) = 0;
    cellobjdata(3, maxobjid) = tile_doorclosed4;
    cellobjname(maxobjid) = u8"扉JAIL"s;
    ++maxobjid;
}



void map_converttile()
{
    for (int cnt = 0, cnt_end = (map_data.height); cnt < cnt_end; ++cnt)
    {
        y = cnt;
        for (int cnt = 0, cnt_end = (map_data.width); cnt < cnt_end; ++cnt)
        {
            x = cnt;
            if (cell_data.at(x, y).chip_id_actual == 0)
            {
                cell_data.at(x, y).chip_id_actual = tile_default
                    + (rnd(tile_default(2)) == 0) * rnd(tile_default(1));
                continue;
            }
            if (cell_data.at(x, y).chip_id_actual >= 100)
            {
                cell_data.at(x, y).chip_id_actual = tile_tunnel
                    + (rnd(tile_tunnel(2)) == 0) * rnd(tile_tunnel(1));
                continue;
            }
            if (cell_data.at(x, y).chip_id_actual == 1)
            {
                cell_data.at(x, y).chip_id_actual =
                    tile_wall + (rnd(tile_wall(2)) == 0) * rnd(tile_wall(1));
                continue;
            }
            if (cell_data.at(x, y).chip_id_actual == 3)
            {
                cell_data.at(x, y).chip_id_actual =
                    tile_room + (rnd(tile_room(2)) == 0) * rnd(tile_room(1));
                continue;
            }
            if (cell_data.at(x, y).chip_id_actual == 4)
            {
                cell_data.at(x, y).chip_id_actual = tile_default
                    + (rnd(tile_default(2)) == 0) * rnd(tile_default(1));
                continue;
            }
        }
    }
}


int dist_town()
{
    int p_at_m165 = 0;
    int y_at_m165 = 0;
    int x_at_m165 = 0;
    int i_at_m165 = 0;
    p_at_m165 = 1000;
    for (int cnt = 0, cnt_end = (map_data.height); cnt < cnt_end; ++cnt)
    {
        y_at_m165 = cnt;
        for (int cnt = 0, cnt_end = (map_data.width); cnt < cnt_end; ++cnt)
        {
            x_at_m165 = cnt;
            cell_featread(x_at_m165, y_at_m165);
            if (area_data[feat(2)].type == mdata_t::MapType::town)
            {
                i_at_m165 = dist(
                    cdata.player().position.x,
                    cdata.player().position.y,
                    x_at_m165,
                    y_at_m165);
                if (i_at_m165 < p_at_m165)
                {
                    p_at_m165 = i_at_m165;
                }
            }
        }
    }
    return p_at_m165;
}



void map_placecharaonentrance(int prm_936, int prm_937, int prm_938)
{
    int x_at_m167 = 0;
    int y_at_m167 = 0;
    if (prm_937 == 1)
    {
        x_at_m167 = map_data.stair_up_pos % 1000;
        if (prm_938 != 0)
        {
            x_at_m167 += rnd(prm_938) - rnd(prm_938);
        }
        y_at_m167 = map_data.stair_up_pos / 1000;
        if (prm_938 != 0)
        {
            y_at_m167 += rnd(prm_938) - rnd(prm_938);
        }
    }
    if (prm_937 == 2)
    {
        x_at_m167 = map_data.stair_down_pos % 1000;
        if (prm_938 != 0)
        {
            x_at_m167 += rnd(prm_938) - rnd(prm_938);
        }
        y_at_m167 = map_data.stair_down_pos / 1000;
        if (prm_938 != 0)
        {
            y_at_m167 += rnd(prm_938) - rnd(prm_938);
        }
    }
    if (prm_937 == 3)
    {
        if (game_data.player_next_move_direction == 1)
        {
            x_at_m167 = map_data.width - 2;
            y_at_m167 = map_data.height / 2;
            if (game_data.current_map == mdata_t::MapId::palmia)
            {
                y_at_m167 = 22;
            }
            if (game_data.current_map == mdata_t::MapId::lumiest)
            {
                x_at_m167 = 58;
                y_at_m167 = 21;
            }
        }
        if (game_data.player_next_move_direction == 2)
        {
            x_at_m167 = 1;
            y_at_m167 = map_data.height / 2;
            if (game_data.current_map == mdata_t::MapId::noyel)
            {
                y_at_m167 = 3;
            }
            if (game_data.current_map == mdata_t::MapId::lumiest)
            {
                x_at_m167 = 25;
                y_at_m167 = 1;
            }
        }
        if (game_data.player_next_move_direction == 3)
        {
            x_at_m167 = map_data.width / 2;
            y_at_m167 = map_data.height - 2;
            if (game_data.current_map == mdata_t::MapId::palmia)
            {
                x_at_m167 = 30;
            }
            if (game_data.current_map == mdata_t::MapId::noyel)
            {
                x_at_m167 = 28;
            }
            if (game_data.current_map == mdata_t::MapId::lumiest)
            {
                x_at_m167 = 58;
                y_at_m167 = 21;
            }
        }
        if (game_data.player_next_move_direction == 0)
        {
            x_at_m167 = map_data.width / 2;
            y_at_m167 = 1;
            if (game_data.current_map == mdata_t::MapId::noyel)
            {
                x_at_m167 = 5;
            }
            if (game_data.current_map == mdata_t::MapId::lumiest)
            {
                x_at_m167 = 25;
                y_at_m167 = 1;
            }
        }
        if (game_data.current_map == mdata_t::MapId::larna)
        {
            x_at_m167 = 1;
            y_at_m167 = 14;
        }
        if (game_data.player_x_on_map_leave != -1)
        {
            x_at_m167 = game_data.player_x_on_map_leave;
            y_at_m167 = game_data.player_y_on_map_leave;
        }
    }
    if (prm_937 == 4)
    {
        x_at_m167 = map_data.width / 2;
        y_at_m167 = map_data.height / 2;
    }
    if (prm_937 == 8)
    {
        x_at_m167 = map_data.width / 2;
        y_at_m167 = map_data.height - 2;
    }
    if (prm_937 == 5)
    {
        x_at_m167 = rnd(map_data.width - 5) + 2;
        y_at_m167 = rnd(map_data.height - 5) + 2;
    }
    if (prm_937 == 6)
    {
        x_at_m167 = game_data.pc_x_in_world_map + rnd((prm_936 / 5 + 1));
        y_at_m167 = game_data.pc_y_in_world_map + rnd((prm_936 / 5 + 1));
    }
    if (prm_937 == 7)
    {
        x_at_m167 = mapstartx;
        y_at_m167 = mapstarty;
    }
    cxinit = x_at_m167;
    cyinit = y_at_m167;
    rc = prm_936;
    chara_place();
}



void map_placearena(int prm_939, int prm_940)
{
    while (1)
    {
        x = rnd(7) + 5;
        y = rnd(6) + 6;
        if (prm_940 == 0)
        {
            x += 8;
        }
        cxinit = x;
        cyinit = y;
        rc = prm_939;
        chara_place();
        if (prm_940 == 0)
        {
            if (cdata[prm_939].position.x >= 13
                && cdata[prm_939].position.y >= 6
                && cdata[prm_939].position.x < 20
                && cdata[prm_939].position.y < 12)
            {
                break;
            }
        }
        else if (
            cdata[prm_939].position.x >= 5 && cdata[prm_939].position.y >= 6
            && cdata[prm_939].position.x < 12 && cdata[prm_939].position.y < 12)
        {
            break;
        }
        cell_data.at(cdata[prm_939].position.x, cdata[prm_939].position.y)
            .chara_index_plus_one = 0;
    }
}



void map_placeplayer()
{
    if (mode == 11)
    {
        return;
    }
    camera = 0;
    for (int cnt = 0; cnt < 16; ++cnt)
    {
        if (cdata[cnt].state() != Character::State::alive)
        {
            continue;
        }
        if (cnt != 0)
        {
            if (game_data.mount == cnt)
            {
                cdata[game_data.mount].position.x = cdata.player().position.x;
                cdata[game_data.mount].position.y = cdata.player().position.y;
                continue;
            }
        }
        if (game_data.current_map == mdata_t::MapId::pet_arena)
        {
            if (followerin(cnt) == 1)
            {
                if (camera == 0)
                {
                    camera = cnt;
                }
                map_placearena(cnt, 0);
                continue;
            }
        }
        if (cdata[cnt].current_map == game_data.current_map)
        {
            if (cnt != 0)
            {
                cxinit = cdata[cnt].initial_position.x;
                cyinit = cdata[cnt].initial_position.y;
                rc = cnt;
                chara_place();
                continue;
            }
        }
        map_placecharaonentrance(cnt, game_data.entrance_type);
    }
}



void map_randomtile(int prm_941, int prm_942)
{
    for (int cnt = 0,
             cnt_end = (map_data.width * map_data.height * prm_942 / 100 + 1);
         cnt < cnt_end;
         ++cnt)
    {
        cell_data.at(rnd(map_data.width), rnd(map_data.height)).chip_id_actual =
            prm_941;
    }
}



int map_digcheck(int prm_953, int prm_954)
{
    if (prm_953 < 1 || prm_954 < 1 || prm_953 > map_data.width - 2
        || prm_954 > map_data.height - 2)
    {
        return 0;
    }
    if (cell_data.at(prm_953, prm_954).chip_id_actual == 100)
    {
        return 100;
    }
    return cell_data.at(prm_953, prm_954).chip_id_actual == 0;
}



void map_nextdir1(int prm_955, int prm_956)
{
    if (tx_at_m168 >= prm_955 - 4 && tx_at_m168 <= prm_955 + 4)
    {
        if (ty_at_m168 >= prm_956 - 4 && ty_at_m168 <= prm_956 + 4)
        {
            if (tx_at_m168 < prm_955)
            {
                dir_at_m168 = 2;
                if (ty_at_m168 > prm_956)
                {
                    dest_at_m168 = 3;
                }
                else
                {
                    dest_at_m168 = 0;
                }
            }
            if (tx_at_m168 > prm_955)
            {
                dir_at_m168 = 1;
                if (ty_at_m168 > prm_956)
                {
                    dest_at_m168 = 3;
                }
                else
                {
                    dest_at_m168 = 0;
                }
            }
            if (ty_at_m168 < prm_956)
            {
                dir_at_m168 = 0;
                if (tx_at_m168 > prm_955)
                {
                    dest_at_m168 = 1;
                }
                else
                {
                    dest_at_m168 = 2;
                }
            }
            if (ty_at_m168 > prm_956)
            {
                dir_at_m168 = 3;
                if (tx_at_m168 > prm_955)
                {
                    dest_at_m168 = 1;
                }
                else
                {
                    dest_at_m168 = 2;
                }
            }
            return;
        }
    }
    if (dir_at_m168 == 1 || dir_at_m168 == 2)
    {
        if (ty_at_m168 > prm_956)
        {
            dir_at_m168 = 3;
        }
        else
        {
            dir_at_m168 = 0;
        }
        if (tx_at_m168 > prm_955)
        {
            dest_at_m168 = 1;
        }
        else
        {
            dest_at_m168 = 2;
        }
        return;
    }
    else
    {
        if (tx_at_m168 > prm_955)
        {
            dir_at_m168 = 1;
        }
        else
        {
            dir_at_m168 = 2;
        }
        if (ty_at_m168 > prm_956)
        {
            dest_at_m168 = 3;
        }
        else
        {
            dest_at_m168 = 0;
        }
        return;
    }
}



void map_nextdir2(int prm_957, int prm_958)
{
    int p_at_m168 = 0;
    if (dir2_at_m168 != -1)
    {
        if (dir2_at_m168 == 1)
        {
            if (map_digcheck(tx_at_m168 - 1, ty_at_m168))
            {
                if (tx_at_m168 == prm_957)
                {
                    p_at_m168 = dir2_at_m168;
                    dir2_at_m168 = dir_at_m168;
                    dir_at_m168 = p_at_m168;
                }
                else
                {
                    dir_at_m168 = dir2_at_m168;
                    dir2_at_m168 = -1;
                }
            }
        }
        if (dir2_at_m168 == 2)
        {
            if (map_digcheck(tx_at_m168 + 1, ty_at_m168))
            {
                if (tx_at_m168 == prm_957)
                {
                    p_at_m168 = dir2_at_m168;
                    dir2_at_m168 = dir_at_m168;
                    dir_at_m168 = p_at_m168;
                }
                else
                {
                    dir_at_m168 = dir2_at_m168;
                    dir2_at_m168 = -1;
                }
            }
        }
        if (dir2_at_m168 == 3)
        {
            if (map_digcheck(tx_at_m168, ty_at_m168 - 1))
            {
                if (ty_at_m168 == prm_958)
                {
                    p_at_m168 = dir2_at_m168;
                    dir2_at_m168 = dir_at_m168;
                    dir_at_m168 = p_at_m168;
                }
                else
                {
                    dir_at_m168 = dir2_at_m168;
                    dir2_at_m168 = -1;
                }
            }
        }
        if (dir2_at_m168 == 0)
        {
            if (map_digcheck(tx_at_m168, ty_at_m168 + 1))
            {
                if (ty_at_m168 == prm_958)
                {
                    p_at_m168 = dir2_at_m168;
                    dir2_at_m168 = dir_at_m168;
                    dir_at_m168 = p_at_m168;
                }
                else
                {
                    dir_at_m168 = dir2_at_m168;
                    dir2_at_m168 = -1;
                }
            }
        }
    }
    if (dir_at_m168 == 1 || dir_at_m168 == 2)
    {
        if (tx_at_m168 == prm_957)
        {
            if (ty_at_m168 > prm_958)
            {
                if (map_digcheck(tx_at_m168, ty_at_m168 - 1))
                {
                    dir2_at_m168 = dir_at_m168;
                    dir_at_m168 = 3;
                }
            }
            if (ty_at_m168 < prm_958)
            {
                if (map_digcheck(tx_at_m168, ty_at_m168 + 1))
                {
                    dir2_at_m168 = dir_at_m168;
                    dir_at_m168 = 0;
                }
            }
        }
        return;
    }
    else
    {
        if (ty_at_m168 == prm_958)
        {
            if (tx_at_m168 > prm_957)
            {
                if (map_digcheck(tx_at_m168 - 1, ty_at_m168))
                {
                    dir2_at_m168 = dir_at_m168;
                    dir_at_m168 = 1;
                }
            }
            if (tx_at_m168 < prm_957)
            {
                if (map_digcheck(tx_at_m168 + 1, ty_at_m168))
                {
                    dir2_at_m168 = dir_at_m168;
                    dir_at_m168 = 2;
                }
            }
        }
        return;
    }
}



int map_digtoentrance1(
    int prm_959,
    int prm_960,
    int prm_961,
    int prm_962,
    int prm_963)
{
    int f_at_m168 = 0;
    int dx_at_m168 = 0;
    int dy_at_m168 = 0;
    tx_at_m168 = prm_959;
    ty_at_m168 = prm_960;
    dest_at_m168 = -1;
    f_at_m168 = 0;
    if (prm_963 == 1)
    {
        dir2_at_m168 = -1;
        map_nextdir1(prm_961, prm_962);
    }
    for (int cnt = 0; cnt < 2000; ++cnt)
    {
        if (tx_at_m168 == prm_961)
        {
            if (ty_at_m168 + 1 == prm_962 || ty_at_m168 - 1 == prm_962)
            {
                f_at_m168 = 1;
                break;
            }
        }
        if (ty_at_m168 == prm_962)
        {
            if (tx_at_m168 + 1 == prm_961 || tx_at_m168 - 1 == prm_961)
            {
                f_at_m168 = 1;
                break;
            }
        }
        if (prm_963 == 1)
        {
            map_nextdir2(prm_961, prm_962);
        }
        dx_at_m168 = tx_at_m168;
        dy_at_m168 = ty_at_m168;
        if (dir_at_m168 == 1)
        {
            --dx_at_m168;
        }
        if (dir_at_m168 == 2)
        {
            ++dx_at_m168;
        }
        if (dir_at_m168 == 3)
        {
            --dy_at_m168;
        }
        if (dir_at_m168 == 0)
        {
            ++dy_at_m168;
        }
        if (map_digcheck(dx_at_m168, dy_at_m168))
        {
            tx_at_m168 = dx_at_m168;
            ty_at_m168 = dy_at_m168;
            cell_data.at(dx_at_m168, dy_at_m168).chip_id_actual = 100;
            if (rnd(200) < rdhiddenpath)
            {
                cell_data.at(dx_at_m168, dy_at_m168).chip_id_actual = 4;
                cell_featset(dx_at_m168, dy_at_m168, 0, 22);
            }
            if (prm_963 == 0)
            {
                if (rnd(4) == 0)
                {
                    map_nextdir1(prm_961, prm_962);
                }
            }
        }
        else
        {
            if (dest_at_m168 == 1)
            {
                if (map_digcheck(tx_at_m168 - 1, ty_at_m168))
                {
                    dir_at_m168 = 1;
                    dest_at_m168 = -2;
                }
            }
            if (dest_at_m168 == 2)
            {
                if (map_digcheck(tx_at_m168 + 1, ty_at_m168))
                {
                    dir_at_m168 = 2;
                    dest_at_m168 = -2;
                }
            }
            if (dest_at_m168 == 3)
            {
                if (map_digcheck(tx_at_m168, ty_at_m168 - 1))
                {
                    dir_at_m168 = 3;
                    dest_at_m168 = -2;
                }
            }
            if (dest_at_m168 == 0)
            {
                if (map_digcheck(tx_at_m168, ty_at_m168 + 1))
                {
                    dir_at_m168 = 0;
                    dest_at_m168 = -2;
                }
            }
            if (dest_at_m168 == -2)
            {
                dest_at_m168 = -1;
                continue;
            }
            if (prm_963 == 0)
            {
                map_nextdir1(prm_961, prm_962);
            }
            if (prm_963 == 1)
            {
                map_nextdir1(prm_961, prm_962);
            }
        }
    }
    return f_at_m168;
}



void map_setfog(int, int)
{
    for (int cnt = 0, cnt_end = (map_data.height); cnt < cnt_end; ++cnt)
    {
        y = cnt;
        for (int cnt = 0, cnt_end = (map_data.width); cnt < cnt_end; ++cnt)
        {
            x = cnt;
            cell_data.at(x, y).chip_id_memory =
                tile_fog + (rnd(tile_fog(2)) == 0) * rnd(tile_fog(1));
        }
    }
}

void rndshuffle(elona_vector1<int>& prm_534)
{
    int p_at_m68 = 0;
    int r_at_m68 = 0;
    p_at_m68 = prm_534.size();
    for (int cnt = 0, cnt_end = (p_at_m68); cnt < cnt_end; ++cnt)
    {
        r_at_m68 = rnd(p_at_m68);
        --p_at_m68;
        i_at_m68 = prm_534(r_at_m68);
        prm_534(r_at_m68) = prm_534(p_at_m68);
        prm_534(p_at_m68) = i_at_m68;
    }
}

void map_createroomdoor()
{
    elona_vector1<int> rddoorpos;
    if (rdpos == 3 || rdpos == 0)
    {
        p = roomwidth(cr);
    }
    else
    {
        p = roomheight(cr);
    }
    DIM1(rddoorpos);
    for (int cnt = 0, cnt_end = (p - 2); cnt < cnt_end; ++cnt)
    {
        rddoorpos(cnt) = cnt;
    }
    rndshuffle(rddoorpos);
    for (int cnt = 0, cnt_end = (p - 2); cnt < cnt_end; ++cnt)
    {
        if (rdpos == 3)
        {
            x = rddoorpos(cnt) + roomx(cr) + 1;
            y = roomy(cr) + roomheight(cr) - 1;
            p(0) = 0;
            p(1) = 0;
            p(2) = -1;
            p(3) = 1;
        }
        if (rdpos == 0)
        {
            x = rddoorpos(cnt) + roomx(cr) + 1;
            y = roomy(cr);
            p(0) = 0;
            p(1) = 0;
            p(2) = -1;
            p(3) = 1;
        }
        if (rdpos == 1)
        {
            y = rddoorpos(cnt) + roomy(cr) + 1;
            x = roomx(cr) + roomwidth(cr) - 1;
            p(0) = -1;
            p(1) = 1;
            p(2) = 0;
            p(3) = 0;
        }
        if (rdpos == 2)
        {
            y = rddoorpos(cnt) + roomy(cr) + 1;
            x = roomx(cr);
            p(0) = -1;
            p(1) = 1;
            p(2) = 0;
            p(3) = 0;
        }
        f = 1;
        for (int cnt = 0; cnt < 2; ++cnt)
        {
            dx = x + p(cnt);
            dy = y + p((cnt + 2));
            if ((dx >= 0 && dy >= 0 && dx < map_data.width
                 && dy < map_data.height)
                == 0)
            {
                f = 0;
                break;
            }
            if (cell_data.at(dx, dy).chip_id_actual == 1)
            {
                f = 0;
                break;
            }
        }
        if (f == 1)
        {
            cell_data.at(x, y).chip_id_actual = 3;
            if (roomdoor != 3)
            {
                cell_featset(
                    x,
                    y,
                    tile_doorclosed,
                    21,
                    rnd(std::abs(game_data.current_dungeon_level * 3 / 2) + 1));
            }
            break;
        }
    }
}



int map_createroom(int prm_966)
{
    int roompos = 0;
    int roomwall = 0;
    if (roomsum >= 30)
    {
        return 0;
    }
    if (prm_966 == 0)
    {
        roompos = 0;
        roomwall = 0;
        roomdoor = 0;
    }
    if (prm_966 == 1)
    {
        roompos = 1;
        roomwall = 1;
        roomdoor = 0;
    }
    if (prm_966 == 2)
    {
        roompos = 2;
        roomwall = 1;
        roomdoor = 1;
    }
    if (prm_966 == 3)
    {
        roompos = 3;
        roomwall = 2;
        roomdoor = 3;
    }
    if (prm_966 == 4)
    {
        roompos = 4;
        roomwall = 3;
        roomdoor = 0;
    }
    cr = roomsum;
    f = 0;
    for (int cnt = 0; cnt < 100; ++cnt)
    {
        if (roompos == 0)
        {
            roomwidth(cr) = rnd(rdroomsizemax) + rdroomsizemin;
            roomheight(cr) = rnd(rdroomsizemax) + rdroomsizemin;
            roomx(cr) = rnd(map_data.width) + 2;
            roomy(cr) = rnd(map_data.height) + 2;
        }
        if (roompos == 1)
        {
            roomwidth(cr) = (rnd(rdroomsizemax) + rdroomsizemin) / 3 * 3 + 5;
            roomheight(cr) = (rnd(rdroomsizemax) + rdroomsizemin) / 3 * 3 + 5;
            roomx(cr) = rnd(map_data.width) / 3 * 3 + 2;
            roomy(cr) = rnd(map_data.height) / 3 * 3 + 2;
        }
        if (roompos == 2)
        {
            rdpos = rnd(4);
            if (rdpos == 3 || rdpos == 0)
            {
                roomx(cr) = rnd(map_data.width - rdroomsizemin * 3 / 2 - 2)
                    + rdroomsizemin / 2;
                roomwidth(cr) = rnd(rdroomsizemin) + rdroomsizemin / 2 + 3;
                roomheight(cr) = rdroomsizemin;
                if (rdpos == 3)
                {
                    roomy(cr) = 0;
                }
                else
                {
                    roomy(cr) = map_data.height - roomheight(cr);
                }
            }
            if (rdpos == 1 || rdpos == 2)
            {
                roomy(cr) = rnd(map_data.height - rdroomsizemin * 3 / 2 - 2)
                    + rdroomsizemin / 2;
                roomwidth(cr) = rdroomsizemin;
                roomheight(cr) = rnd(rdroomsizemin) + rdroomsizemin / 2 + 3;
                if (rdpos == 1)
                {
                    roomx(cr) = 0;
                }
                else
                {
                    roomx(cr) = map_data.width - roomwidth(cr);
                }
            }
        }
        if (roompos == 3)
        {
            roomwidth(cr) = 3;
            roomheight(cr) = 3;
            x = map_data.width - rdroomsizemin * 2 - roomwidth(cr) - 2 + 1;
            if (x < 1)
            {
                break;
            }
            y = map_data.height - rdroomsizemin * 2 - roomheight(cr) - 2 + 1;
            if (y < 1)
            {
                break;
            }
            roomx(cr) = rdroomsizemin + 1 + rnd(x(0));
            roomy(cr) = rdroomsizemin + 1 + rnd(y(0));
        }
        if (roompos == 4)
        {
            roomwidth(cr) = rnd(rdroomsizemax) + rdroomsizemin;
            roomheight(cr) = rnd(rdroomsizemax) + rdroomsizemin;
            roomx(cr) = rnd(map_data.width - rdroomsizemax - 8) + 3;
            roomy(cr) = rnd(map_data.height - rdroomsizemax - 8) + 3;
        }
        x = roomx(cr) + roomwidth(cr) - 1;
        y = roomy(cr) + roomheight(cr) - 1;
        if (x >= map_data.width)
        {
            continue;
        }
        if (y >= map_data.height)
        {
            continue;
        }
        if (roompos == 1)
        {
            if (x + 1 >= map_data.width)
            {
                continue;
            }
            if (y + 1 >= map_data.height)
            {
                continue;
            }
        }
        if (roompos == 0)
        {
            if (cell_data.at(x, y).chip_id_actual != 3)
            {
                continue;
            }
        }
        bool do_continue{};
        for (p = 0; p < roomsum; ++p)
        {
            if (p == cr)
            {
                continue;
            }
            x1 = roomx(p) - 1 - roomx(cr);
            x2 = -roomwidth(p) - 2 < x1 && x1 < roomwidth(cr);
            y1 = roomy(p) - 1 - roomy(cr);
            y2 = -roomheight(p) - 2 < y1 && y1 < roomheight(cr);
            if (x2 && y2)
            {
                do_continue = true;
                break;
            }
        }
        if (do_continue)
        {
            continue;
        }
        ++roomsum;
        f = 1;
        break;
    }
    if (f == 0)
    {
        return 0;
    }
    if (rnd(2) == 0)
    {
        tile(1) = 1 + rnd(2);
    }
    else
    {
        tile(1) = 0;
    }
    if (rnd(2) == 0)
    {
        tile(2) = 1 + rnd(2);
    }
    else
    {
        tile(2) = 0;
    }
    for (int cnt = 0, cnt_end = (roomheight(cr)); cnt < cnt_end; ++cnt)
    {
        y = roomy(cr) + cnt;
        int cnt2 = cnt;
        for (int cnt = 0, cnt_end = (roomwidth(cr)); cnt < cnt_end; ++cnt)
        {
            x = roomx(cr) + cnt;
            tile = 3;
            if (roomwall != 0)
            {
                if (cnt == 0 || cnt2 == 0 || cnt == roomwidth(cr) - 1
                    || cnt2 == roomheight(cr) - 1)
                {
                    if (roomwall == 1)
                    {
                        tile = 1;
                    }
                    if (roomwall == 2)
                    {
                        tile = 4;
                    }
                    if (roomwall == 3)
                    {
                        tile = 3;
                        if (tile(1) == 1)
                        {
                            if (cnt == 0)
                            {
                                tile = 1;
                            }
                        }
                        if (tile(2) == 1)
                        {
                            if (cnt2 == 0)
                            {
                                if (cnt != 0 && cnt != roomwidth(cr) - 1)
                                {
                                    if (rnd(3))
                                    {
                                        flt();
                                        p(0) = 296;
                                        p(1) = 300;
                                        p(2) = 312;
                                        p(3) = 604;
                                        itemcreate(-1, p(rnd(4)), x, y + 1, 0);
                                    }
                                    else if (cnt % 2 == 1)
                                    {
                                        flt();
                                        itemcreate(-1, 584, x, y + 1, 0);
                                    }
                                }
                                tile = 1;
                            }
                        }
                        if (tile(1) == 2)
                        {
                            if (cnt == roomwidth(cr) - 1)
                            {
                                tile = 1;
                            }
                        }
                        if (tile(2) == 2)
                        {
                            if (cnt2 == roomheight(cr) - 1)
                            {
                                if (rnd(3))
                                {
                                    flt();
                                    p(0) = 296;
                                    p(1) = 300;
                                    p(2) = 312;
                                    p(3) = 604;
                                    itemcreate(-1, p(rnd(4)), x, y + 1, 0);
                                }
                                else if (cnt % 2 == 1)
                                {
                                    flt();
                                    itemcreate(-1, 584, x, y + 1, 0);
                                }
                                tile = 1;
                            }
                        }
                    }
                }
            }
            cell_data.at(x, y).chip_id_actual = tile;
        }
    }
    if (roomdoor == 1)
    {
        map_createroomdoor();
    }
    if (roomdoor == 2 || roomdoor == 3)
    {
        for (int cnt = 0; cnt < 4; ++cnt)
        {
            rdpos = cnt;
            map_createroomdoor();
        }
    }
    return 1;
}



int map_placeupstairs(int prm_967, int prm_968)
{
    int found_x;
    int found_y;
    if (prm_967 == 0)
    {
        found_x = rnd(roomwidth(cr) - 2) + roomx(cr) + 1;
        found_y = rnd(roomheight(cr) - 2) + roomy(cr) + 1;
    }
    else
    {
        found_x = prm_967;
        found_y = prm_968;
    }
    cell_featset(found_x, found_y, tile_upstairs, 10);
    map_data.stair_up_pos = found_y * 1000 + found_x;
    rdroomupstair = cr;
    return 1;
}



int map_placedownstairs(int prm_969, int prm_970)
{
    int found_x;
    int found_y;

    if (game_data.current_dungeon_level
        >= area_data[game_data.current_map].deepest_level)
    {
        return 0;
    }
    if (prm_969 == 0)
    {
        found_x = rnd(roomwidth(cr) - 2) + roomx(cr) + 1;
        found_y = rnd(roomheight(cr) - 2) + roomy(cr) + 1;
    }
    else
    {
        found_x = prm_969;
        found_y = prm_970;
    }
    cell_featset(found_x, found_y, tile_downstairs, 11);
    map_data.stair_down_pos = found_y * 1000 + found_x;
    rdroomdownstair = cr;
    return 1;
}



int map_trap(int prm_973, int prm_974, int, int prm_976)
{
    int trap_at_m170 = 0;
    dx_at_m170 = prm_973;
    dy_at_m170 = prm_974;
    p_at_m170 = 0;
    while (1)
    {
        if (p_at_m170 >= 3)
        {
            return 0;
        }
        if (prm_973 == 0)
        {
            dx_at_m170 = rnd(map_data.width - 5) + 2;
            dy_at_m170 = rnd(map_data.height - 5) + 2;
        }
        else
        {
            dx_at_m170 = prm_973;
            dy_at_m170 = prm_974;
        }
        if ((chipm(7, cell_data.at(dx_at_m170, dy_at_m170).chip_id_actual) & 4)
            == 0)
        {
            if (cell_data.at(dx_at_m170, dy_at_m170).feats == 0)
            {
                if (prm_976 == 0)
                {
                    trap_at_m170 = rnd(8);
                }
                else
                {
                    trap_at_m170 = prm_976;
                }
                if (game_data.current_dungeon_level <= 5)
                {
                    if (trap_at_m170 == 6)
                    {
                        return 0;
                    }
                    if (trap_at_m170 == 1)
                    {
                        return 0;
                    }
                    if (trap_at_m170 == 5)
                    {
                        return 0;
                    }
                }
                if (game_data.current_dungeon_level <= 25)
                {
                    if (trap_at_m170 == 7)
                    {
                        return 0;
                    }
                }
                cell_featset(dx_at_m170, dy_at_m170, 0, 14, trap_at_m170);
                return 1;
            }
        }
        p_at_m170 += 1;
    }
}



int map_web(int prm_977, int prm_978, int prm_979)
{
    dx_at_m170 = prm_977;
    dy_at_m170 = prm_978;
    p_at_m170 = 0;

    while (1)
    {
        if (p_at_m170 >= 3)
        {
            return 0;
        }
        if (prm_977 == 0)
        {
            dx_at_m170 = rnd(map_data.width - 5) + 2;
            dy_at_m170 = rnd(map_data.height - 5) + 2;
        }
        else
        {
            dx_at_m170 = prm_977;
            dy_at_m170 = prm_978;
        }
        if ((chipm(7, cell_data.at(dx_at_m170, dy_at_m170).chip_id_actual) & 4)
            == 0)
        {
            if (cell_data.at(dx_at_m170, dy_at_m170).feats == 0)
            {
                mef_add(dx_at_m170, dy_at_m170, 1, 11, -1, prm_979);
                return 1;
            }
        }
        p_at_m170 += 1;
    }
}



int map_barrel(int prm_980, int prm_981)
{
    dx_at_m170 = prm_980;
    dy_at_m170 = prm_981;
    p_at_m170 = 0;

    while (1)
    {
        if (p_at_m170 >= 3)
        {
            return 0;
        }
        if (prm_980 == 0)
        {
            dx_at_m170 = rnd(map_data.width - 5) + 2;
            dy_at_m170 = rnd(map_data.height - 5) + 2;
        }
        else
        {
            dx_at_m170 = prm_980;
            dy_at_m170 = prm_981;
        }
        if ((chipm(7, cell_data.at(dx_at_m170, dy_at_m170).chip_id_actual) & 4)
            == 0)
        {
            if (cell_data.at(dx_at_m170, dy_at_m170).feats == 0)
            {
                cell_featset(dx_at_m170, dy_at_m170, tile_pot, 30);
                return 1;
            }
        }
        p_at_m170 += 1;
    }
}



int map_connectroom()
{
    cr = 0;
    while (cr < roomsum - 1)
    {
        bool ok = false;
        for (int i = 0; i < rnd(rdroomentrance + 1) + 1; ++i)
        {
            for (int j = cr; j < cr + 2; ++j)
            {
                while (1)
                {
                    dir = rnd(4);
                    x = dirxy(0, dir);
                    y = dirxy(1, dir);
                    if (dir == 1)
                    {
                        dx = roomx(j);
                        dy = roomy(j) + rnd(roomheight(j) - 2) + 1;
                    }
                    if (dir == 2)
                    {
                        dx = roomx(j) + roomwidth(j) - 1;
                        dy = roomy(j) + rnd(roomheight(j) - 2) + 1;
                    }
                    if (dir == 3)
                    {
                        dx = roomx(j) + rnd(roomwidth(j) - 2) + 1;
                        dy = roomy(j);
                    }
                    if (dir == 0)
                    {
                        dx = roomx(j) + rnd(roomwidth(j) - 2) + 1;
                        dy = roomy(j) + roomheight(j) - 1;
                    }
                    if (x != 0)
                    {
                        if (cell_data.at(dx, dy - 1).chip_id_actual == 3
                            || cell_data.at(dx, dy + 1).chip_id_actual == 3)
                        {
                            continue;
                        }
                    }
                    if (y != 0)
                    {
                        if (cell_data.at(dx - 1, dy).chip_id_actual == 3
                            || cell_data.at(dx + 1, dy).chip_id_actual == 3)
                        {
                            continue;
                        }
                    }
                    break;
                }
                cell_data.at(dx, dy).chip_id_actual = 3;
                roomexist(j) = 1;
                dx += x;
                dy += y;
                cell_data.at(dx, dy).chip_id_actual = 100;
                if (j == cr)
                {
                    tx = dx;
                    ty = dy;
                }
            }
            ok = map_digtoentrance1(tx, ty, dx, dy, 1);
        }
        if (!ok)
        {
            roomexist(cr) = 0;
            roomexist(cr + 1) = 0;
            return 0;
        }
        ++cr;
    }
    return 1;
}



void map_makedoor()
{
    for (cr = 0; cr < roomsum; ++cr)
    {
        tx = 0;
        ty = 0;
        for (int cnt = 0, cnt_end = (roomheight(cr) * 2 + roomwidth(cr) * 2);
             cnt < cnt_end;
             ++cnt)
        {
            if (tx == 0)
            {
                if (cnt != 0)
                {
                    --ty;
                }
            }
            if (ty == roomheight(cr) - 1)
            {
                --tx;
            }
            if (tx == roomwidth(cr) - 1)
            {
                ++ty;
            }
            if (ty == 0)
            {
                ++tx;
            }
            dx = tx + roomx(cr);
            dy = ty + roomy(cr);
            if (cell_data.at(dx, dy).chip_id_actual == 1)
            {
                continue;
            }
            cell_featset(
                dx,
                dy,
                tile_doorclosed,
                21,
                rnd(std::abs(game_data.current_dungeon_level * 3 / 2) + 1));
        }
    }
}


void generate_debug_map()
{
    map_data.width = 50;
    map_data.height = 50;
    map_data.atlas_number = 1;
    map_data.turn_cost = 10000;
    map_data.max_crowd_density = map_data.width * map_data.height / 100;
    map_data.tileset = 3;
    map_data.user_map_flag = 0;
    map_initialize();

    for (int y = 0; y < map_data.height; ++y)
    {
        for (int x = 0; x < map_data.width; ++x)
        {
            cell_data.at(x, y).chip_id_actual = 3;
        }
    }

    mdatan(0) =
        i18n::s.get_enum_property("core.locale.map.unique", "name", 499);
    map_converttile();

    mapstartx = 25;
    mapstarty = 25;
    map_placeplayer();
}

static optional<int> _setup_map_generation_parameters()
{
    int rdtype = 1;

    if (rnd(30) == 0)
    {
        rdtype = 3;
    }
    if (area_data[game_data.current_map].type == mdata_t::MapType::dungeon)
    {
        rdtype = 2;
        if (rnd(4) == 0)
        {
            rdtype = 1;
        }
        if (rnd(6) == 0)
        {
            rdtype = 10;
        }
        if (rnd(10) == 0)
        {
            rdtype = 4;
        }
        if (rnd(25) == 0)
        {
            rdtype = 8;
        }
        if (rnd(20) == 0)
        {
            map_data.tileset = 10;
        }
    }
    if (area_data[game_data.current_map].type
        == mdata_t::MapType::dungeon_forest)
    {
        rdtype = 2;
        if (rnd(6) == 0)
        {
            rdtype = 1;
        }
        if (rnd(6) == 0)
        {
            rdtype = 10;
        }
        if (rnd(25) == 0)
        {
            rdtype = 8;
        }
        if (rnd(20) == 0)
        {
            rdtype = 4;
        }
    }
    if (area_data[game_data.current_map].type
        == mdata_t::MapType::dungeon_tower)
    {
        rdtype = 1;
        if (rnd(5) == 0)
        {
            rdtype = 4;
        }
        if (rnd(10) == 0)
        {
            rdtype = 3;
        }
        if (rnd(25) == 0)
        {
            rdtype = 2;
        }
        if (rnd(40) == 0)
        {
            map_data.tileset = 10;
        }
    }
    if (area_data[game_data.current_map].type
        == mdata_t::MapType::dungeon_castle)
    {
        rdtype = 1;
        if (rnd(5) == 0)
        {
            rdtype = 4;
        }
        if (rnd(6) == 0)
        {
            rdtype = 5;
        }
        if (rnd(7) == 0)
        {
            rdtype = 2;
        }
        if (rnd(40) == 0)
        {
            map_data.tileset = 10;
        }
    }
    if (area_data[game_data.current_map].id == mdata_t::MapId::lesimas)
    {
        map_data.max_crowd_density += game_data.current_dungeon_level / 2;
        map_data.tileset = 101;
        if (rnd(20) == 0)
        {
            map_data.tileset = 10;
        }
        if (game_data.current_dungeon_level < 35)
        {
            map_data.tileset = 0;
        }
        if (game_data.current_dungeon_level < 20)
        {
            map_data.tileset = 100;
        }
        if (game_data.current_dungeon_level < 10)
        {
            map_data.tileset = 200;
        }
        if (game_data.current_dungeon_level < 5)
        {
            map_data.tileset = 0;
        }
        rdtype = 1;
        for (int cnt = 0; cnt < 1; ++cnt)
        {
            if (game_data.current_dungeon_level == 1)
            {
                rdtype = 2;
                break;
            }
            if (game_data.current_dungeon_level == 5)
            {
                rdtype = 5;
                break;
            }
            if (game_data.current_dungeon_level == 10)
            {
                rdtype = 3;
                break;
            }
            if (game_data.current_dungeon_level == 15)
            {
                rdtype = 5;
                break;
            }
            if (game_data.current_dungeon_level == 20)
            {
                rdtype = 3;
                break;
            }
            if (game_data.current_dungeon_level == 25)
            {
                rdtype = 5;
                break;
            }
            if (game_data.current_dungeon_level == 30)
            {
                rdtype = 3;
                break;
            }
            if (game_data.current_dungeon_level < 30)
            {
                if (rnd(4) == 0)
                {
                    rdtype = 2;
                }
            }
            if (rnd(5) == 0)
            {
                rdtype = 4;
            }
            if (rnd(20) == 0)
            {
                rdtype = 8;
            }
            if (rnd(6) == 0)
            {
                rdtype = 10;
            }
        }
    }
    if (area_data[game_data.current_map].id == mdata_t::MapId::tower_of_fire)
    {
        map_data.max_crowd_density += game_data.current_dungeon_level / 2;
        map_data.tileset = 7;
        rdtype = 1;
    }
    if (area_data[game_data.current_map].id
        == mdata_t::MapId::crypt_of_the_damned)
    {
        map_data.max_crowd_density += game_data.current_dungeon_level / 2;
        map_data.tileset = 0;
        rdtype = 1;
    }
    if (area_data[game_data.current_map].id == mdata_t::MapId::ancient_castle)
    {
        map_data.max_crowd_density += game_data.current_dungeon_level / 2;
        map_data.tileset = 200;
        rdtype = 1;
    }
    if (area_data[game_data.current_map].id == mdata_t::MapId::mountain_pass)
    {
        rdtype = 8;
    }
    if (area_data[game_data.current_map].id == mdata_t::MapId::puppy_cave)
    {
        rdtype = 10;
    }
    if (area_data[game_data.current_map].id == mdata_t::MapId::minotaurs_nest)
    {
        rdtype = 9;
    }
    if (area_data[game_data.current_map].id == mdata_t::MapId::quest)
    {
        if (game_data.executing_immediate_quest_type == 1001)
        {
            map_data.tileset = 300;
            map_data.width = 28 + rnd(6);
            map_data.height = 20 + rnd(6);
            rdtype = 6;
        }
        if (game_data.executing_immediate_quest_type == 1009)
        {
            initialize_quest_map_party();
            return none;
        }
        if (game_data.executing_immediate_quest_type == 1006)
        {
            initialize_quest_map_crop();
            return none;
        }
        if (game_data.executing_immediate_quest_type == 1008)
        {
            initialize_quest_map_town();
            return none;
        }
        if (game_data.executing_immediate_quest_type == 1010)
        {
            initialize_quest_map_town();
            return none;
        }
    }

    return rdtype;
}

void generate_random_nefia()
{
    int rdtype = 0;
    int rdmonsterhouse = 0;
    int rdcreaturepack = 0;
    int rdy3 = 0;
    int rdx3 = 0;
    int mobdensity = 0;
    int itemdensity = 0;

    while (1)
    {
        randomize();
        ++rdtry;
        map_data.user_map_flag = 0;
        map_data.width = 34 + rnd(15);
        map_data.height = 22 + rnd(15);
        map_data.max_crowd_density = map_data.width * map_data.height / 100;
        roomsum = 0;
        rdroomnum = map_data.width * map_data.height / 70;
        rdroomsizemin = 3;
        rdroomsizemax = 4;
        rdroomentrance = 1;
        rdhiddenpath = 20;
        rdval(2) = 2;
        rdtunnel = map_data.width * map_data.height;
        rdextraroom = 10;

        auto rdtype_opt = _setup_map_generation_parameters();
        if (!rdtype_opt)
        {
            // Quest maps can have special generation routines.
            return;
        }

        rdtype = *rdtype_opt;

        int stat = 1;
        if (rdtype == 2)
        {
            initialize_random_nefia_rdtype2();
        }
        if (rdtype == 1)
        {
            stat = initialize_random_nefia_rdtype1();
        }
        if (rdtype == 4)
        {
            initialize_random_nefia_rdtype4();
        }
        if (rdtype == 5)
        {
            initialize_random_nefia_rdtype5();
        }
        if (rdtype == 3)
        {
            initialize_random_nefia_rdtype3();
        }
        if (rdtype == 6)
        {
            map_data.indoors_flag = 2;
            initialize_random_nefia_rdtype6();
            return;
        }
        if (rdtype == 8)
        {
            initialize_random_nefia_rdtype8();
        }
        if (rdtype == 10)
        {
            _mclass = 5 + rnd(4);
            _bold = 2;
            initialize_random_nefia_rdtype10();
        }
        if (rdtype == 9)
        {
            _mclass = 12;
            _bold = 2;
            initialize_random_nefia_rdtype9();
        }
        if (stat != 0)
        {
            break;
        }
    }
    map_converttile();
    map_placeplayer();
    rdmonsterhouse = 0;
    rdcreaturepack = 0;
    for (int cnt = 0, cnt_end = (roomsum); cnt < cnt_end; ++cnt)
    {
        rx = roomx(cnt) + 1;
        rw = roomwidth(cnt) - 2;
        ry = roomy(cnt) + 1;
        rh = roomheight(cnt) - 2;
        rdsize = rw * rh;
        for (int cnt = 0, cnt_end = (rnd(rdsize / 8 + 2)); cnt < cnt_end; ++cnt)
        {
            if (rnd(2) == 0)
            {
                flt(calcobjlv(game_data.current_dungeon_level),
                    calcfixlv(Quality::bad));
                flttypemajor = fltsetdungeon();
                itemcreate(-1, 0, rnd(rw) + rx, rnd(rh) + ry, 0);
            }
            map_set_chara_generation_filter();
            int stat = chara_create(-1, 0, rnd(rw) + rx, rnd(rh) + ry);
            if (stat == 1)
            {
                if (game_data.current_dungeon_level > 3)
                {
                    if (creaturepack != 0)
                    {
                        if (rnd(rdcreaturepack * 5 + 5) == 0)
                        {
                            ++rdcreaturepack;
                            for (int cnt = 0, cnt_end = (10 + rnd(20));
                                 cnt < cnt_end;
                                 ++cnt)
                            {
                                flt(cdata[rc].level, calcfixlv(Quality::bad));
                                flttypemajor = creaturepack;
                                chara_create(-1, 0, rnd(rw) + rx, rnd(rh) + ry);
                            }
                            break;
                        }
                    }
                }
            }
        }
        if (cnt == rdroomdownstair)
        {
            continue;
        }
        if (cnt == rdroomupstair)
        {
            continue;
        }
        if (rdmonsterhouse == 0 || rdtype == 2)
        {
            if (rnd(8) == 0)
            {
                if (rw * rh < 40)
                {
                    ++rdmonsterhouse;
                    for (int cnt = ry, cnt_end = cnt + (rh); cnt < cnt_end;
                         ++cnt)
                    {
                        rdy3 = cnt;
                        for (int cnt = rx, cnt_end = cnt + (rw); cnt < cnt_end;
                             ++cnt)
                        {
                            rdx3 = cnt;
                            map_set_chara_generation_filter();
                            chara_create(-1, 0, rdx3, rdy3);
                        }
                    }
                    if (rdtype != 2)
                    {
                        for (int cnt = 0, cnt_end = (rnd(3) + 1); cnt < cnt_end;
                             ++cnt)
                        {
                            flt();
                            flttypemajor = 72000;
                            itemcreate(-1, 0, rnd(rw) + rx, rnd(rh) + ry, 0);
                        }
                    }
                }
            }
        }
    }
    mobdensity = map_data.max_crowd_density / 4;
    itemdensity = map_data.max_crowd_density / 4;
    if (rdtype == 3)
    {
        flt();
        flttypemajor = choice(fsetwear);
        fixlv = Quality::miracle;
        itemcreate(-1, 0, -1, -1, 0);
        mobdensity = map_data.max_crowd_density / 2;
        itemdensity = map_data.max_crowd_density / 3;
    }
    if (rdtype == 8)
    {
        mobdensity = map_data.max_crowd_density / 4;
        itemdensity = map_data.max_crowd_density / 10;
    }
    if (rdtype == 10)
    {
        mobdensity = map_data.max_crowd_density / 3;
        itemdensity = map_data.max_crowd_density / 6;
    }
    if (rdtype == 9)
    {
        mobdensity = map_data.max_crowd_density / 3;
        itemdensity = map_data.max_crowd_density / 10;
    }
    for (int cnt = 0, cnt_end = (mobdensity); cnt < cnt_end; ++cnt)
    {
        map_set_chara_generation_filter();
        chara_create(-1, 0, -3, 0);
    }
    for (int cnt = 0, cnt_end = (itemdensity); cnt < cnt_end; ++cnt)
    {
        flt(calcobjlv(game_data.current_dungeon_level),
            calcfixlv(Quality::bad));
        flttypemajor = fltsetdungeon();
        itemcreate(-1, 0, -1, -1, 0);
    }
    for (int cnt = 0, cnt_end = (rnd(map_data.width * map_data.height / 80));
         cnt < cnt_end;
         ++cnt)
    {
        map_trap(0, 0, game_data.current_dungeon_level);
    }
    if (rnd(5) == 0)
    {
        p = rnd(map_data.width * map_data.height / 40);
        if (rnd(5) == 0)
        {
            p = rnd(map_data.width * map_data.height / 5);
        }
        for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
        {
            map_web(0, 0, game_data.current_dungeon_level * 10 + 100);
        }
    }
    if (rnd(4) == 0)
    {
        p = clamp(rnd(map_data.width * map_data.height / 500 + 1) + 1, 3, 15);
        for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
        {
            map_barrel(0, 0);
        }
    }
    if (map_data.refresh_type == 1)
    {
        if (rnd(15 + game_data.quest_flags.kill_count_of_little_sister * 2)
            == 0)
        {
            flt();
            chara_create(-1, 318, -3, 0);
        }
    }
    if (area_data[game_data.current_map].id == mdata_t::MapId::lesimas)
    {
        if (game_data.current_dungeon_level == 3
            || game_data.current_dungeon_level == 17
            || game_data.current_dungeon_level == 25
            || game_data.current_dungeon_level == 44)
        {
            x = map_data.stair_down_pos % 1000;
            y = map_data.stair_down_pos / 1000;
            cell_featset(x, y, tile_downlocked, 11);
        }
    }
}



void initialize_random_nefia_rdtype6()
{
    map_initialize();
    for (int cnt = 0, cnt_end = (map_data.height); cnt < cnt_end; ++cnt)
    {
        p = cnt;
        for (int cnt = 0, cnt_end = (map_data.width); cnt < cnt_end; ++cnt)
        {
            cell_data.at(cnt, p).chip_id_actual = 3;
        }
    }
    for (int cnt = 0, cnt_end = (rnd(map_data.width * map_data.height / 30));
         cnt < cnt_end;
         ++cnt)
    {
        x = rnd(map_data.width);
        y = rnd(map_data.height);
        cell_data.at(x, y).chip_id_actual = 1;
    }
    if (game_data.previous_map2 == 33)
    {
        tile_room(0) = 45;
        tile_room(1) = 6;
    }
    map_converttile();
    map_placeplayer();
    map_data.max_crowd_density = 0;
    for (int cnt = 0, cnt_end = (10 + rnd(6)); cnt < cnt_end; ++cnt)
    {
        map_set_chara_generation_filter();
        int stat = chara_create(-1, 0, -3, 0);
        if (stat != 0)
        {
            cdata[rc].relationship = -3;
            cdata[rc].original_relationship = -3;
        }
    }
    for (int cnt = 0, cnt_end = (10 + rnd(10)); cnt < cnt_end; ++cnt)
    {
        flt();
        flttypemajor = 80000;
        itemcreate(-1, 0, -1, -1, 0);
        inv[ci].own_state = 1;
    }
}



int initialize_quest_map_crop()
{
    game_data.left_minutes_of_executing_quest = 120;
    game_data.executing_immediate_quest_time_left_display_period = 9999;
    map_data.indoors_flag = 2;
    map_data.tileset = 4;
    map_data.width = 58 + rnd(16);
    map_data.height = 50 + rnd(16);
    map_initialize();
    for (int cnt = 0, cnt_end = (map_data.height); cnt < cnt_end; ++cnt)
    {
        p = cnt;
        for (int cnt = 0, cnt_end = (map_data.width); cnt < cnt_end; ++cnt)
        {
            cell_data.at(cnt, p).chip_id_actual = tile_default
                + (rnd(tile_default(2)) == 0) * rnd(tile_default(1));
        }
    }
    mdatan(0) = u8"街周辺の畑"s;
    map_randomtile(9, 10);
    map_randomtile(10, 10);
    map_randomtile(0, 30);
    map_randomtile(1, 4);
    map_randomtile(4, 2);
    map_randomtile(3, 2);
    map_randomtile(4, 2);
    map_randomtile(5, 2);
    for (int cnt = 0; cnt < 30; ++cnt)
    {
        int w = rnd(5) + 5;
        int h = rnd(4) + 4;
        dx = rnd(map_data.width);
        dy = rnd(map_data.height);
        if (rnd(2))
        {
            tile = 30;
        }
        else
        {
            tile = 31;
        }
        size = clamp(
            dist(dx, dy, map_data.width / 2, map_data.height / 2) / 8, 0, 8);
        crop = choice(isetcrop);
        for (int cnt = dy, cnt_end = cnt + (h); cnt < cnt_end; ++cnt)
        {
            y = cnt;
            if (y >= map_data.height)
            {
                break;
            }
            for (int cnt = dx, cnt_end = cnt + (w); cnt < cnt_end; ++cnt)
            {
                x = cnt;
                if (x >= map_data.width)
                {
                    break;
                }
                cell_data.at(x, y).chip_id_actual = tile;
                if (rnd(10) != 0
                    || cell_data.at(x, y).item_appearances_actual != 0)
                {
                    continue;
                }
                if (rnd(4))
                {
                    dbid = crop;
                }
                else
                {
                    dbid = choice(isetcrop);
                }
                flt();
                itemcreate(-1, dbid, x, y, 0);
                inv[ci].own_state = 4;
                p = clamp(size + rnd((rnd(4) + 1)), 0, 9);
                inv[ci].weight = inv[ci].weight * (80 + p * p * 100) / 100;
                inv[ci].subname = p;
            }
        }
    }
    game_data.entrance_type = 7;
    mapstartx = rnd(map_data.width / 3) + map_data.width / 3;
    mapstarty = rnd(map_data.height / 3) + map_data.height / 3;
    map_placeplayer();
    flt();
    itemcreate(
        -1, 560, cdata.player().position.x + 1, cdata.player().position.y, 0);
    inv[ci].own_state = 1;
    for (int cnt = 0, cnt_end = (70 + rnd(20)); cnt < cnt_end; ++cnt)
    {
        x = rnd(map_data.width);
        y = rnd(map_data.height);
        if (cell_data.at(x, y).chip_id_actual != 30
            && cell_data.at(x, y).chip_id_actual != 31)
        {
            if (cell_data.at(x, y).item_appearances_actual == 0)
            {
                if (rnd(8))
                {
                    flt();
                    flttypemajor = 80000;
                    itemcreate(-1, 0, x, y, 0);
                    inv[ci].own_state = 1;
                }
                else
                {
                    cell_featset(x, y, tile_pot, 30);
                }
            }
        }
    }
    map_data.max_crowd_density = 15;
    for (int cnt = 0; cnt < 30; ++cnt)
    {
        map_set_chara_generation_filter();
        chara_create(-1, 0, -3, 0);
    }
    return 1;
}



int initialize_random_nefia_rdtype1()
{
    map_initialize();
    int stat = map_createroom(1);
    if (stat == 0)
    {
        return 0;
    }
    map_placeupstairs();
    {
        int stat = map_createroom(1);
        if (stat == 0)
        {
            return 0;
        }
    }
    map_placedownstairs();
    for (int cnt = 0, cnt_end = (rdroomnum); cnt < cnt_end; ++cnt)
    {
        map_createroom(1);
    }
    {
        int stat = map_connectroom();
        if (stat == 0)
        {
            return 0;
        }
    }
    map_makedoor();
    return 1;
}



int initialize_random_nefia_rdtype4()
{
    rdroomsizemin = 8;
    map_initialize();
    p = rdroomsizemin - 1;
    for (int cnt = 0, cnt_end = (map_data.height); cnt < cnt_end; ++cnt)
    {
        y = cnt;
        for (int cnt = 0, cnt_end = (map_data.width); cnt < cnt_end; ++cnt)
        {
            x = cnt;
            cell_data.at(x, y).chip_id_actual = 1;
            if (x > p && y > p && x + 1 < map_data.width - p
                && y + 1 < map_data.height - p)
            {
                cell_data.at(x, y).chip_id_actual = 100;
            }
        }
    }
    int stat = map_createroom(2);
    if (stat == 0)
    {
        return 0;
    }
    map_placeupstairs();
    {
        int stat = map_createroom(2);
        if (stat == 0)
        {
            return 0;
        }
    }
    map_placedownstairs();
    for (int cnt = 0, cnt_end = (rdroomnum); cnt < cnt_end; ++cnt)
    {
        map_createroom(2);
    }
    if (rnd(2) == 0)
    {
        for (int cnt = 0, cnt_end = (rdroomnum / 4 + 1); cnt < cnt_end; ++cnt)
        {
            map_createroom(3);
        }
    }
    else
    {
        p = rdroomsizemin + 1 + rnd(3);
        for (int cnt = 0, cnt_end = (map_data.height - p * 2); cnt < cnt_end;
             ++cnt)
        {
            y = p + cnt;
            for (int cnt = 0, cnt_end = (map_data.width - p * 2); cnt < cnt_end;
                 ++cnt)
            {
                x = p + cnt;
                cell_data.at(x, y).chip_id_actual = 1;
            }
        }
    }
    return 1;
}



int initialize_random_nefia_rdtype5()
{
    rdroomsizemin = 8;
    map_data.width = 48 + rnd(20);
    map_data.height = 22;
    map_data.max_crowd_density = map_data.width * map_data.height / 20;
    map_initialize();
    p = rdroomsizemin - 1;
    for (int cnt = 0, cnt_end = (map_data.height); cnt < cnt_end; ++cnt)
    {
        y = cnt;
        for (int cnt = 0, cnt_end = (map_data.width); cnt < cnt_end; ++cnt)
        {
            x = cnt;
            cell_data.at(x, y).chip_id_actual = 1;
            if (x > p && y > p && x + 1 < map_data.width - p
                && y + 1 < map_data.height - p)
            {
                cell_data.at(x, y).chip_id_actual = 100;
            }
        }
    }
    int stat = map_createroom(2);
    if (stat == 0)
    {
        return 0;
    }
    map_placeupstairs();
    {
        int stat = map_createroom(2);
        if (stat == 0)
        {
            return 0;
        }
    }
    map_placedownstairs();
    for (int cnt = 0, cnt_end = (rdroomnum); cnt < cnt_end; ++cnt)
    {
        map_createroom(2);
    }
    if (rnd(2) == 0)
    {
        for (int cnt = 0, cnt_end = (rdroomnum / 4 + 1); cnt < cnt_end; ++cnt)
        {
            map_createroom(3);
        }
    }
    else
    {
        p = rdroomsizemin + 1 + rnd(3);
        for (int cnt = 0, cnt_end = (map_data.height - p * 2); cnt < cnt_end;
             ++cnt)
        {
            y = p + cnt;
            for (int cnt = 0, cnt_end = (map_data.width - p * 2); cnt < cnt_end;
                 ++cnt)
            {
                x = p + cnt;
                cell_data.at(x, y).chip_id_actual = 1;
            }
        }
    }
    return 1;
}



int initialize_random_nefia_rdtype2()
{
    rdroomsizemax = 3;
    map_initialize();
    dx = map_data.width / 2;
    dy = map_data.height / 2;
    cell_data.at(dx, dy).chip_id_actual = 3;
    p = 0;
    for (int cnt = 0, cnt_end = (rdtunnel); cnt < cnt_end; ++cnt)
    {
        if (rnd(rdval(2)) == 0)
        {
            p = rnd(4);
        }
        if (p == 2)
        {
            ++dx;
            if (dx > map_data.width - 2)
            {
                p = 0;
                dx = map_data.width - 2;
            }
        }
        if (p == 1)
        {
            --dx;
            if (dx < 1)
            {
                p = 3;
                dx = 1;
            }
        }
        if (p == 0)
        {
            ++dy;
            if (dy > map_data.height - 2)
            {
                p = 1;
                dy = map_data.height - 2;
            }
        }
        if (p == 3)
        {
            --dy;
            if (dy < 1)
            {
                p = 2;
                dy = 1;
            }
        }
        cell_data.at(dx, dy).chip_id_actual = 3;
    }
    int stat = map_createroom();
    if (stat == 0)
    {
        return 0;
    }
    map_placeupstairs();
    {
        int stat = map_createroom();
        if (stat == 0)
        {
            return 0;
        }
    }
    map_placedownstairs();
    for (int cnt = 0, cnt_end = (rdroomnum); cnt < cnt_end; ++cnt)
    {
        map_createroom(0);
    }
    for (int cnt = 0, cnt_end = (rdextraroom); cnt < cnt_end; ++cnt)
    {
        p = 0;
        for (int cnt = 0; cnt < 100; ++cnt)
        {
            x = rnd(map_data.width);
            y = rnd(map_data.height);
            if (cell_data.at(x, y).chip_id_actual == 3)
            {
                dx = rnd(rdroomsizemax) + rdroomsizemin;
                dy = rnd(rdroomsizemax) + rdroomsizemin;
                rx = rnd(dx(0));
                ry = rnd(dy);
                if (x > 1 && y > 1 && x + dx < map_data.width - 2
                    && y + dy < map_data.height - 2)
                {
                    p = 1;
                    break;
                }
            }
        }
        if (p == 0)
        {
            continue;
        }
        dy = y;
        for (int cnt = 0, cnt_end = (ry); cnt < cnt_end; ++cnt)
        {
            dx = x;
            for (int cnt = 0, cnt_end = (rx); cnt < cnt_end; ++cnt)
            {
                cell_data.at(dx, dy).chip_id_actual = 3;
                ++dx;
            }
            ++dy;
        }
    }
    return 1;
}



int initialize_random_nefia_rdtype3()
{
    map_data.width = 48 + rnd(20);
    map_data.height = 22;
    map_data.max_crowd_density = map_data.width * map_data.height / 20;
    map_initialize();
    for (int cnt = 0, cnt_end = (map_data.height); cnt < cnt_end; ++cnt)
    {
        y = cnt;
        for (int cnt = 0, cnt_end = (map_data.width); cnt < cnt_end; ++cnt)
        {
            x = cnt;
            if (x == 0 || y == 0 || x + 1 == map_data.width
                || y + 1 == map_data.height)
            {
                continue;
            }
            cell_data.at(x, y).chip_id_actual = 3;
        }
    }
    p(0) = rnd(map_data.width / 2) + 2;
    p(1) = rnd(map_data.width / 2) + map_data.width / 2 - 2;
    if (rnd(2) == 0)
    {
        p(2) = p;
        p = p(1);
        p(1) = p(2);
    }
    map_placeupstairs(p, rnd(map_data.height - 4) + 2);
    map_placedownstairs(p(1), rnd(map_data.height - 4) + 2);
    return 1;
}



int initialize_quest_map_party()
{
    int roomdiff = 0;
    game_data.left_minutes_of_executing_quest = 60;
    game_data.executing_immediate_quest_time_left_display_period = 9999;
    rdroomsizemin = 5;
    mdatan(0) = i18n::s.get("core.locale.map.quest.party_room");
    map_data.indoors_flag = 1;
    map_data.tileset = 11;
    map_data.width = 38;
    map_data.height = 28;
    map_initialize();
    rdroomnum = 80;
    for (int cnt = 0, cnt_end = (map_data.height); cnt < cnt_end; ++cnt)
    {
        y = cnt;
        for (int cnt = 0, cnt_end = (map_data.width); cnt < cnt_end; ++cnt)
        {
            x = cnt;
            if (x == 0 || y == 0 || x + 1 == map_data.width
                || y + 1 == map_data.height)
            {
                continue;
            }
            cell_data.at(x, y).chip_id_actual = 100;
        }
    }
    for (int cnt = 0, cnt_end = (rdroomnum); cnt < cnt_end; ++cnt)
    {
        map_createroom(4);
    }
    map_converttile();
    for (int cnt = 0; cnt < 500; ++cnt)
    {
        dx = rnd(map_data.width - 5);
        dy = rnd(map_data.height - 5);
        p(0) = 1;
        p(1) = 1;
        for (int cnt = 0; cnt < 4; ++cnt)
        {
            y = dy + cnt;
            for (int cnt = 0; cnt < 4; ++cnt)
            {
                x = dx + cnt;
                if (cell_data.at(x, y).chip_id_actual != tile_tunnel
                    || cell_data.at(x, y).item_appearances_actual != 0)
                {
                    p(0) = 0;
                }
                if (cell_data.at(x, y).chip_id_actual != tile_room
                    || cell_data.at(x, y).item_appearances_actual != 0)
                {
                    p(1) = 0;
                }
            }
        }
        if (p(0) == 1)
        {
            int n = rnd(5);
            for (int cnt = 0; cnt < 4; ++cnt)
            {
                y = dy + cnt;
                int cnt2 = cnt;
                for (int cnt = 0; cnt < 4; ++cnt)
                {
                    x = dx + cnt;
                    if (n < 2)
                    {
                        if (cnt != 0 && cnt != 3 && cnt2 != 0 && cnt2 != 3)
                        {
                            cell_data.at(x, y).chip_id_actual = 473;
                        }
                    }
                    if (n == 2)
                    {
                        if (cnt == 3 || cnt2 == 3)
                        {
                            break;
                        }
                        if (cnt == 1 && cnt2 == 1)
                        {
                            cell_data.at(x, y).chip_id_actual = 664;
                        }
                        else
                        {
                            cell_data.at(x, y).chip_id_actual = 206;
                            flt();
                            itemcreate(-1, 91, x, y, 0);
                        }
                    }
                    if (n == 3)
                    {
                        if (cnt == 1 && cnt2 == 1)
                        {
                            cell_data.at(x, y).chip_id_actual = 204;
                            flt();
                            itemcreate(-1, 585, x, y, 0);
                        }
                    }
                    if (n == 4)
                    {
                        if (cnt == 1 && cnt2 == 1)
                        {
                            flt();
                            cell_data.at(x, y).chip_id_actual = 69;
                            itemcreate(-1, 138, x, y, 0);
                        }
                    }
                }
            }
        }
        if (p(1) == 1)
        {
            flt();
            itemcreate(-1, 83, dx + 1, dy + 1, 0);
            if (rnd(2))
            {
                flt();
                itemcreate(-1, 92, dx + 1, dy, 0);
            }
            if (rnd(2))
            {
                flt();
                itemcreate(-1, 92, dx + 1, dy + 2, 0);
            }
            if (rnd(2))
            {
                flt();
                itemcreate(-1, 92, dx, dy + 1, 0);
            }
            if (rnd(2))
            {
                flt();
                itemcreate(-1, 92, dx + 2, dy + 1, 0);
            }
        }
    }
    list(0, 0) = 171;
    list(1, 0) = 9;
    list(2, 0) = 36;
    list(0, 1) = 269;
    list(1, 1) = 273;
    list(2, 1) = 35;
    list(0, 2) = 269;
    list(1, 2) = 174;
    list(2, 2) = 8;
    list(0, 3) = 174;
    list(1, 3) = 16;
    list(2, 3) = 239;
    list(0, 4) = 16;
    list(1, 4) = 185;
    list(2, 4) = 41;
    list(0, 5) = 185;
    list(1, 5) = 274;
    list(2, 5) = 184;
    list(0, 6) = 274;
    list(1, 6) = 272;
    list(2, 6) = 70;
    list(0, 7) = 272;
    list(1, 7) = 38;
    list(2, 7) = 1;
    list(0, 8) = 38;
    list(1, 8) = 206;
    list(2, 8) = 72;
    list(0, 9) = 206;
    list(1, 9) = 73;
    list(2, 9) = 69;
    for (int cnt = 0, cnt_end = (roomsum); cnt < cnt_end; ++cnt)
    {
        rx = roomx(cnt) + 1;
        rw = roomwidth(cnt) - 2;
        ry = roomy(cnt) + 1;
        rh = roomheight(cnt) - 2;
        rdsize = rw * rh;
        roomdiff = clamp(rnd(quest_data.immediate().difficulty / 3 + 3), 0, 9);
        if (rnd(2) == 0)
        {
            x = rnd(rw) + rx;
            y = rnd(rh) + ry;
            if (cell_data.at(x, y).item_appearances_actual == 0)
            {
                flt();
                itemcreate(-1, 88, x, y, 0);
            }
        }
        if (rnd(3) == 0)
        {
            x = rnd(rw) + rx;
            y = rnd(rh) + ry;
            if (cell_data.at(x, y).item_appearances_actual == 0)
            {
                flt();
                itemcreate(-1, 313, x, y, 0);
            }
        }
        if (rnd(2) == 0)
        {
            x = rnd(rw) + rx;
            y = rnd(rh) + ry;
            if (cell_data.at(x, y).item_appearances_actual == 0)
            {
                flt();
                itemcreate(-1, 156, x, y, 0);
            }
        }
        if (rnd(3) == 0)
        {
            x = rnd(rw) + rx;
            y = rnd(rh) + ry;
            if (cell_data.at(x, y).item_appearances_actual == 0)
            {
                flt();
                itemcreate(-1, 606, x, y, 0);
            }
        }
        for (int cnt = 0,
                 cnt_end = cnt + (rnd(rdsize / 5 + 2) + rdsize / 5 + 3);
             cnt < cnt_end;
             ++cnt)
        {
            flt(roomdiff * 5, calcfixlv(Quality::bad));
            initlv = roomdiff * 7 + rnd(5);
            dbid = list(rnd(3), roomdiff);
            chara_create(-1, dbid, rnd(rw) + rx, rnd(rh) + ry);
            cdata[rc].character_role = 3;
            cdata[rc].relationship = -1;
            cdata[rc].original_relationship = -1;
            cdata[rc].gold = cdata[rc].level * (20 + rnd(20));
        }
    }
    game_data.entrance_type = 7;
    mapstartx = rnd(map_data.width / 3) + map_data.width / 3;
    mapstarty = rnd(map_data.height / 3) + map_data.height / 3;
    map_placeplayer();
    map_data.max_crowd_density = 0;
    for (int cnt = 0, cnt_end = (25 + rnd(10)); cnt < cnt_end; ++cnt)
    {
        x = rnd(map_data.width);
        y = rnd(map_data.height);
        if (cell_data.at(x, y).item_appearances_actual != 0
            || chipm(7, cell_data.at(x, y).chip_id_actual) & 4)
        {
            continue;
        }
        flt();
        p(0) = 217;
        p(1) = 218;
        p(2) = 216;
        p(3) = 215;
        p(4) = 215;
        p(5) = 152;
        p(6) = 152;
        p(7) = 91;
        p(8) = 189;
        itemcreate(-1, p(rnd(9)), x, y, 0);
    }
    flt();
    chara_create(-1, 29, -3, 0);
    cdata[rc].character_role = 3;
    cdata[rc].relationship = -1;
    cdata[rc].original_relationship = -1;
    flt();
    chara_create(-1, 231, -3, 0);
    cdata[rc].character_role = 3;
    cdata[rc].relationship = -1;
    cdata[rc].original_relationship = -1;
    flt();
    chara_create(-1, 31, -3, 0);
    cdata[rc].character_role = 3;
    cdata[rc].relationship = -1;
    cdata[rc].original_relationship = -1;
    flt();
    chara_create(-1, 247, -3, 0);
    cdata[rc].character_role = 3;
    cdata[rc].relationship = -1;
    cdata[rc].original_relationship = -1;
    if (rnd(10) == 0)
    {
        flt();
        chara_create(-1, 34, -3, 0);
        cdata[rc].character_role = 3;
        cdata[rc].relationship = -1;
        cdata[rc].original_relationship = -1;
    }
    if (rnd(10) == 0)
    {
        flt();
        chara_create(-1, 28, -3, 0);
        cdata[rc].character_role = 3;
        cdata[rc].relationship = -1;
        cdata[rc].original_relationship = -1;
    }
    if (rnd(10) == 0)
    {
        flt();
        chara_create(-1, 223, -3, 0);
        cdata[rc].character_role = 3;
        cdata[rc].relationship = -1;
        cdata[rc].original_relationship = -1;
    }
    if (rnd(10) == 0)
    {
        flt();
        chara_create(-1, 252, -3, 0);
        cdata[rc].character_role = 3;
        cdata[rc].relationship = -1;
        cdata[rc].original_relationship = -1;
    }
    if (rnd(10) == 0)
    {
        flt();
        chara_create(-1, 322, -3, 0);
        cdata[rc].character_role = 3;
        cdata[rc].relationship = -1;
        cdata[rc].original_relationship = -1;
    }
    for (const auto& cnt : items(-1))
    {
        if (inv[cnt].number() > 0)
        {
            inv[cnt].own_state = 1;
        }
    }
    return 1;
}



void initialize_quest_map_town()
{
    map_data.max_crowd_density = 0;
    map_data.indoors_flag = 2;
    map_initcustom(map_get_custom_map_name(game_data.previous_map2));
    mdatan(0) = i18n::s.get("core.locale.map.quest.urban_area");
    randomize();
    game_data.entrance_type = 5;
    map_placeplayer();
    map_data.user_map_flag = 0;
    if (game_data.executing_immediate_quest_type == 1008)
    {
        game_data.left_minutes_of_executing_quest = 720;
        game_data.executing_immediate_quest_time_left_display_period = 9999;
        flt();
        initlv = quest_data.immediate().difficulty;
        fixlv = Quality::godly;
        chara_create(-1, quest_data.immediate().extra_info_1, -3, 0);
        cdata[rc].relationship = -3;
        cdata[rc].original_relationship = -3;
        quest_data.immediate().extra_info_2 = rc;
    }
    if (game_data.executing_immediate_quest_type == 1010)
    {
        for (int cnt = 0, cnt_end = (6 + rnd(4)); cnt < cnt_end; ++cnt)
        {
            flt();
            initlv = quest_data.immediate().difficulty * 3 / 2;
            fixlv = Quality::bad;
            chara_create(-1, quest_data.immediate().extra_info_1, -3, 0);
            cdata[rc].relationship = -3;
            cdata[rc].original_relationship = -3;
        }
    }
    for (const auto& cnt : items(-1))
    {
        if (inv[cnt].number() == 0)
        {
            continue;
        }
        f = 0;
        if (inv[cnt].id == 109 || inv[cnt].id == 173)
        {
            inv[cnt].param1 = -10;
        }
        if (inv[cnt].id == 241)
        {
            inv[cnt].param1 = 0;
        }
    }
    for (int cnt = 0, cnt_end = (map_data.height); cnt < cnt_end; ++cnt)
    {
        y = cnt;
        for (int cnt = 0, cnt_end = (map_data.width); cnt < cnt_end; ++cnt)
        {
            x = cnt;
            cell_data.at(x, y).feats = 0;
        }
    }
}



void initialize_random_nefia_rdtype8()
{
    map_data.width = 30;
    map_data.height = 60 + rnd(60);
    map_data.max_crowd_density = map_data.width * map_data.height / 20;
    map_initialize();
    int w = 6;
    dx = map_data.width / 2 - w / 2;
    p = 0;
    for (int cnt = 0, cnt_end = (map_data.height - 4); cnt < cnt_end; ++cnt)
    {
        y = 2 + cnt;
        for (int cnt = 0, cnt_end = (w); cnt < cnt_end; ++cnt)
        {
            x = cnt + dx;
            cell_data.at(x, y).chip_id_actual = 100;
        }
        if (p <= 0)
        {
            if (rnd(2))
            {
                p = rnd(12);
            }
        }
        if (rnd(2))
        {
            if (w > 4)
            {
                w -= rnd(2);
            }
        }
        if (p > 0)
        {
            if (p < 5)
            {
                if (w > 3)
                {
                    w -= rnd(2);
                    --p;
                }
            }
            if (p > 4)
            {
                if (w < 10)
                {
                    ++w;
                    --p;
                }
            }
        }
        if (dx > 1)
        {
            dx -= rnd(2);
        }
        if (dx + w < map_data.width - 1)
        {
            dx += rnd(2);
        }
        if (dx + w > map_data.width)
        {
            w = map_data.width - dx;
        }
    }
    while (1)
    {
        x = rnd(map_data.width);
        y = rnd(15);
        if (cell_data.at(x, y).chip_id_actual == 100)
        {
            map_placeupstairs(x, y);
            break;
        }
    }
    while (1)
    {
        x = rnd(map_data.width);
        y = map_data.height - rnd(15) - 1;
        if (cell_data.at(x, y).chip_id_actual == 100)
        {
            map_placedownstairs(x, y);
            break;
        }
    }
}



void dimmix(elona_vector1<int>& prm_983)
{
    int mx_at_m172 = 0;
    int r_at_m172 = 0;
    mx_at_m172 = prm_983.size();
    for (int cnt = 0, cnt_end = (mx_at_m172); cnt < cnt_end; ++cnt)
    {
        r_at_m172 = cnt + rnd((mx_at_m172 - cnt));
        tmp_at_m172 = prm_983(r_at_m172);
        prm_983(r_at_m172) = prm_983(cnt);
        prm_983(cnt) = tmp_at_m172;
    }
}



void initialize_random_nefia_rdtype9()
{
    map_data.width = _mclass * (_bold * 2) - _bold + 8;
    map_data.height = map_data.width;
    map_data.max_crowd_density = map_data.width * map_data.height / 12;
    map_initialize();
    mapgen_dig_maze();
    rdsecond = 1;
    mapgen_dig_maze();
    rdsecond = 0;
}



void mapgen_dig_maze()
{
    elona_vector1<int> maze;
    int mdig = 0;
    int _hole = 0;
    int sdigx = 0;
    int sdigy = 0;
    int digno = 0;
    int pmdig = 0;
    DIM2(maze, _mclass * _mclass);
    mdig = 0;
    _hole = 0;
    sdigx = _bold;
    sdigy = _bold;
    maze(mdig) = 7;
    elona_vector1<int> way;
    DIM2(way, 4);
    for (int cnt = 0; cnt < 4; ++cnt)
    {
        way(cnt) = cnt;
    }
    i = 0;
    while (1)
    {
        dimmix(way);
        digno = 0;
        for (int cnt = 0; cnt < 4; ++cnt)
        {
            pmdig = mdig;
            if (way(cnt) == 0)
            {
                if (pmdig / _mclass == 0)
                {
                    continue;
                }
                else
                {
                    mdig -= _mclass;
                }
            }
            if (way(cnt) == 1)
            {
                if (pmdig % _mclass == _mclass - 1)
                {
                    continue;
                }
                else
                {
                    ++mdig;
                }
            }
            if (way(cnt) == 2)
            {
                if (pmdig / _mclass == _mclass - 1)
                {
                    continue;
                }
                else
                {
                    mdig += _mclass;
                }
            }
            if (way(cnt) == 3)
            {
                if (pmdig % _mclass == 0)
                {
                    continue;
                }
                else
                {
                    --mdig;
                }
            }
            if (maze(mdig) != _hole)
            {
                mdig = pmdig;
                continue;
            }
            ++i;
            sdigx = pmdig % _mclass * _bold * 2 + _bold;
            sdigy = pmdig / _mclass * _bold * 2 + _bold;
            if (way(cnt) == 0)
            {
                maze(mdig) = 3;
                for (int cnt = 0, cnt_end = (_bold * 2); cnt < cnt_end; ++cnt)
                {
                    y = sdigy - _bold * 2 + cnt - _bold + 4;
                    for (int cnt = 0, cnt_end = (_bold - 1); cnt < cnt_end;
                         ++cnt)
                    {
                        x = sdigx + cnt - _bold + 4;
                        cell_data.at(x, y).chip_id_actual = 100;
                    }
                }
            }
            if (way(cnt) == 1)
            {
                maze(mdig) = 4;
                for (int cnt = 0, cnt_end = (_bold - 1); cnt < cnt_end; ++cnt)
                {
                    y = sdigy + cnt - _bold + 4;
                    for (int cnt = 0, cnt_end = (_bold * 3 - 1); cnt < cnt_end;
                         ++cnt)
                    {
                        x = sdigx + cnt - _bold + 4;
                        cell_data.at(x, y).chip_id_actual = 100;
                    }
                }
            }
            if (way(cnt) == 2)
            {
                maze(mdig) = 1;
                for (int cnt = 0, cnt_end = (_bold * 3 - 1); cnt < cnt_end;
                     ++cnt)
                {
                    y = sdigy + cnt - _bold + 4;
                    for (int cnt = 0, cnt_end = (_bold - 1); cnt < cnt_end;
                         ++cnt)
                    {
                        x = sdigx + cnt - _bold + 4;
                        cell_data.at(x, y).chip_id_actual = 100;
                    }
                }
            }
            if (way(cnt) == 3)
            {
                maze(mdig) = 2;
                for (int cnt = 0, cnt_end = (_bold - 1); cnt < cnt_end; ++cnt)
                {
                    y = sdigy + cnt - _bold + 4;
                    for (int cnt = 0, cnt_end = (_bold * 2); cnt < cnt_end;
                         ++cnt)
                    {
                        x = sdigx + cnt - _bold * 2 - _bold + 4;
                        cell_data.at(x, y).chip_id_actual = 100;
                    }
                }
            }
            digno = 1;
            break;
        }
        if (digno == 1)
        {
            continue;
        }
        if (maze(mdig) == 7)
        {
            break;
        }
        if (maze(mdig) == 1)
        {
            mdig -= _mclass;
            continue;
        }
        if (maze(mdig) == 2)
        {
            ++mdig;
            continue;
        }
        if (maze(mdig) == 3)
        {
            mdig += _mclass;
            continue;
        }
        if (maze(mdig) == 4)
        {
            --mdig;
        }
    }
    if (rdsecond)
    {
        return;
    }
    for (int cnt = 0;; ++cnt)
    {
        x = rnd(map_data.width);
        y = rnd(map_data.height);
        if (cell_data.at(x, y).chip_id_actual != 100)
        {
            continue;
        }
        dx = rnd(map_data.width);
        dy = rnd(map_data.height);
        if (cell_data.at(dx, dy).chip_id_actual != 100)
        {
            continue;
        }
        if (dist(x, y, dx, dy) < 10)
        {
            if (cnt < 1000)
            {
                continue;
            }
        }
        map_placeupstairs(x, y);
        map_placedownstairs(dx, dy);
        break;
    }
}



void initialize_random_nefia_rdtype10()
{
    map_data.width = _mclass * (_bold * 2) - _bold + 8;
    map_data.height = map_data.width;
    map_data.max_crowd_density = map_data.width * map_data.height / 12;
    map_initialize();
    mapgen_dig_maze();
    for (int cnt = 0; cnt < 50; ++cnt)
    {
        int cnt2 = cnt;
        t = 100 + cnt2 + 1;
        while (1)
        {
            x = rnd(map_data.width);
            y = rnd(map_data.height);
            if (cell_data.at(x, y).chip_id_actual != 100)
            {
                continue;
            }
            int w = 10 + rnd(4);
            for (int cnt = 0, cnt_end = (w); cnt < cnt_end; ++cnt)
            {
                dy = cnt + y - w / 2;
                for (int cnt = 0, cnt_end = (w); cnt < cnt_end; ++cnt)
                {
                    dx = cnt + x - w / 2;
                    if (dx < 1 || dy < 1 || dx >= map_data.width - 1
                        || dy >= map_data.height - 1)
                    {
                        continue;
                    }
                    if (dist(x, y, dx, dy) >= w / 2)
                    {
                        continue;
                    }
                    tx = dx - 1;
                    ty = dy;
                    if (cell_data.at(tx, ty).chip_id_actual != t)
                    {
                        if (cell_data.at(tx, ty).chip_id_actual != 0)
                        {
                            if (cell_data.at(tx, ty).chip_id_actual != 100)
                            {
                                continue;
                            }
                        }
                    }
                    tx = dx + 1;
                    ty = dy;
                    if (cell_data.at(tx, ty).chip_id_actual != t)
                    {
                        if (cell_data.at(tx, ty).chip_id_actual != 0)
                        {
                            if (cell_data.at(tx, ty).chip_id_actual != 100)
                            {
                                continue;
                            }
                        }
                    }
                    tx = dx;
                    ty = dy - 1;
                    if (cell_data.at(tx, ty).chip_id_actual != t)
                    {
                        if (cell_data.at(tx, ty).chip_id_actual != 0)
                        {
                            if (cell_data.at(tx, ty).chip_id_actual != 100)
                            {
                                continue;
                            }
                        }
                    }
                    tx = dx;
                    ty = dy + 1;
                    if (cell_data.at(tx, ty).chip_id_actual != t)
                    {
                        if (cell_data.at(tx, ty).chip_id_actual != 0)
                        {
                            if (cell_data.at(tx, ty).chip_id_actual != 100)
                            {
                                continue;
                            }
                        }
                    }
                    tx = dx - 1;
                    ty = dy - 1;
                    if (cell_data.at(tx, ty).chip_id_actual != t)
                    {
                        if (cell_data.at(tx, ty).chip_id_actual != 0)
                        {
                            if (cell_data.at(tx, ty).chip_id_actual != 100)
                            {
                                continue;
                            }
                        }
                    }
                    tx = dx + 1;
                    ty = dy - 1;
                    if (cell_data.at(tx, ty).chip_id_actual != t)
                    {
                        if (cell_data.at(tx, ty).chip_id_actual != 0)
                        {
                            if (cell_data.at(tx, ty).chip_id_actual != 100)
                            {
                                continue;
                            }
                        }
                    }
                    tx = dx - 1;
                    ty = dy + 1;
                    if (cell_data.at(tx, ty).chip_id_actual != t)
                    {
                        if (cell_data.at(tx, ty).chip_id_actual != 0)
                        {
                            if (cell_data.at(tx, ty).chip_id_actual != 100)
                            {
                                continue;
                            }
                        }
                    }
                    tx = dx + 1;
                    ty = dy + 1;
                    if (cell_data.at(tx, ty).chip_id_actual != t)
                    {
                        if (cell_data.at(tx, ty).chip_id_actual != 0)
                        {
                            if (cell_data.at(tx, ty).chip_id_actual != 100)
                            {
                                continue;
                            }
                        }
                    }
                    cell_data.at(dx, dy).chip_id_actual = t;
                }
            }
            break;
        }
    }
    for (int cnt = 0, cnt_end = (map_data.height / 2 - 2); cnt < cnt_end; ++cnt)
    {
        y = cnt * 2;
        for (int cnt = 0, cnt_end = (map_data.width / 2 - 2); cnt < cnt_end;
             ++cnt)
        {
            x = cnt * 2;
            if (cell_data.at(x, y).chip_id_actual < 100)
            {
                continue;
            }
            if (cell_data.at(x, y).feats != 0)
            {
                continue;
            }
            if (cell_data.at(x - 1, y).chip_id_actual >= 100)
            {
                if (cell_data.at(x + 1, y).chip_id_actual >= 100)
                {
                    if (cell_data.at(x, y - 1).chip_id_actual == 0)
                    {
                        if (cell_data.at(x, y + 1).chip_id_actual == 0)
                        {
                            cell_featset(
                                x,
                                y,
                                tile_doorclosed,
                                21,
                                rnd(std::abs(
                                        game_data.current_dungeon_level * 3 / 2)
                                    + 1));
                        }
                    }
                    continue;
                }
            }
            if (cell_data.at(x, y - 1).chip_id_actual >= 100)
            {
                if (cell_data.at(x, y + 1).chip_id_actual >= 100)
                {
                    if (cell_data.at(x - 1, y).chip_id_actual == 0)
                    {
                        if (cell_data.at(x + 1, y).chip_id_actual == 0)
                        {
                            cell_featset(
                                x,
                                y,
                                tile_doorclosed,
                                21,
                                rnd(std::abs(
                                        game_data.current_dungeon_level * 3 / 2)
                                    + 1));
                        }
                    }
                    continue;
                }
            }
        }
    }
}

void map_tileset(int prm_933)
{
    tile_doorclosed = 726;
    tile_dooropen = 236;
    tile_default(0) = 396;
    tile_default(1) = 1;
    tile_default(2) = 1;
    tile_fog(0) = 531;
    tile_fog(1) = 1;
    tile_fog(2) = 1;
    tile_wall(0) = 462;
    tile_wall(1) = 1;
    tile_wall(2) = 1;
    tile_room(0) = 13;
    tile_room(1) = 1;
    tile_room(2) = 1;
    tile_board = 727;
    tile_votebox = 729;
    tile_townboard = 732;
    tile_tunnel(0) = 33;
    tile_tunnel(1) = 1;
    tile_tunnel(2) = 1;
    tile_pot = 242;
    if (prm_933 == 12)
    {
        tile_doorclosed = 733;
        tile_dooropen = 265;
    }
    if (prm_933 == 8)
    {
        tile_doorclosed = 728;
        tile_dooropen = 241;
    }
    if (prm_933 == 9)
    {
        tile_doorclosed = 730;
        tile_dooropen = 264;
    }
    if (prm_933 == 3)
    {
        tile_room = 41;
        tile_tunnel = 41;
        tile_wall = 469;
        tile_fog = tile_wall + 66;
    }
    if (prm_933 == 2)
    {
        tile_wall = 462;
        tile_fog = 529;
    }
    if (prm_933 == 10)
    {
        tile_room = 165;
        tile_tunnel(0) = 33;
        tile_tunnel(1) = 4;
        tile_tunnel(2) = 2;
        tile_wall = 469;
        tile_default = 469;
    }
    if (prm_933 == 11)
    {
        tile_default = 465;
        tile_fog = 530;
        tile_tunnel = 212;
        tile_wall = 467;
        tile_room = 203;
    }
    if (prm_933 == 0)
    {
        tile_default = 469;
        tile_fog = 529;
        tile_tunnel(0) = 33;
        tile_tunnel(1) = 4;
        tile_tunnel(2) = 2;
        tile_wall = 469;
        tile_room(0) = 33;
        tile_room(1) = 4;
        tile_room(2) = 2;
    }
    if (prm_933 == 6)
    {
        tile_default = 469;
        tile_fog = 529;
        tile_tunnel(0) = 45;
        tile_tunnel(1) = 3;
        tile_tunnel(2) = 2;
        tile_wall = 469;
        tile_room(0) = 33;
        tile_room(1) = 6;
        tile_room(2) = 3;
    }
    if (prm_933 == 7)
    {
        tile_default = 474;
        tile_fog = 530;
        tile_tunnel = 68;
        tile_wall = 474;
        tile_room(0) = 66;
        tile_room(1) = 2;
        tile_room(2) = 2;
    }
    if (prm_933 == 300)
    {
        tile_default = 475;
        tile_fog = 528;
        tile_tunnel = 0;
        tile_wall = 475;
        tile_room(0) = 0;
        tile_room(1) = 6;
        tile_room(2) = 6;
    }
    if (prm_933 == 100)
    {
        tile_default = 472;
        tile_fog = 530;
        tile_tunnel = 103;
        tile_wall = 473;
        tile_room(0) = 132;
        tile_room(1) = 3;
        tile_room(2) = 2;
    }
    if (prm_933 == 101)
    {
        tile_default = 477;
        tile_fog = 530;
        tile_tunnel = 100;
        tile_wall = 477;
        tile_room = 99;
    }
    if (prm_933 == 200)
    {
        tile_default = 468;
        tile_fog = 531;
        tile_tunnel(0) = 33;
        tile_tunnel(1) = 4;
        tile_tunnel(2) = 2;
        tile_wall = 462;
        tile_room(0) = 119;
        tile_room(1) = 4;
        tile_room(2) = 2;
    }
    if (prm_933 == 1)
    {
        tile_wall = -1;
        tile_fog(0) = 396;
        tile_fog(1) = 4;
        tile_fog(2) = 2;
    }
    if (prm_933 == 4)
    {
        tile_default = 0;
        tile_fog = 528;
        if (4 <= game_data.stood_world_map_tile
            && game_data.stood_world_map_tile < 9)
        {
            tile_default = 7;
            tile_fog = 528;
        }
        if (264 <= game_data.stood_world_map_tile
            && game_data.stood_world_map_tile < 363)
        {
            tile_default = 12;
        }
        if (9 <= game_data.stood_world_map_tile
            && game_data.stood_world_map_tile < 13)
        {
            tile_fog = 528;
            tile_default = 3;
        }
        if (13 <= game_data.stood_world_map_tile
            && game_data.stood_world_map_tile < 17)
        {
            tile_fog = 531;
            tile_default = 19;
        }
        if (chipm(0, game_data.stood_world_map_tile) == 4)
        {
            tile_fog = 532;
            tile_default = 45;
        }
    }
}

void initialize_home_mdata()
{
    if (game_data.home_scale == 0)
    {
        map_data.max_item_count = 100;
        game_data.basic_point_of_home_rank = 1000;
    }
    if (game_data.home_scale == 1)
    {
        map_data.max_item_count = 150;
        game_data.basic_point_of_home_rank = 3000;
    }
    if (game_data.home_scale == 2)
    {
        map_data.max_item_count = 200;
        game_data.basic_point_of_home_rank = 5000;
    }
    if (game_data.home_scale == 3)
    {
        map_data.max_item_count = 300;
        game_data.basic_point_of_home_rank = 7000;
    }
    if (game_data.home_scale == 4)
    {
        map_data.max_item_count = 350;
        game_data.basic_point_of_home_rank = 8000;
        map_data.tileset = 8;
    }
    if (game_data.home_scale == 5)
    {
        map_data.max_item_count = 400;
        game_data.basic_point_of_home_rank = 10000;
    }
}

void map_initcustom(const std::string& prm_934)
{
    fmapfile = (filesystem::dir::map() / prm_934).generic_string();
    ctrl_file(FileOperation::custom_map_read);
    map_tileset(map_data.tileset);
    nooracle = 1;
    for (int cnt = 0; cnt < 400; ++cnt)
    {
        if (cmapdata(0, cnt) == 0)
        {
            continue;
        }
        if (cmapdata(4, cnt) == 0)
        {
            flt();
            int stat = itemcreate(
                -1, cmapdata(0, cnt), cmapdata(1, cnt), cmapdata(2, cnt), 0);
            if (stat != 0)
            {
                inv[ci].own_state = cmapdata(3, cnt);
            }
        }
        if (cmapdata(4, cnt) == 1)
        {
            flt();
            chara_create(
                -1, cmapdata(0, cnt), cmapdata(1, cnt), cmapdata(2, cnt));
        }
        if (cmapdata(4, cnt) == 2)
        {
            if (mapupdate)
            {
                if (cellobjdata(0, cmapdata(0, cnt)) == 32)
                {
                    continue;
                }
            }
            cell_featset(
                cmapdata(1, cnt),
                cmapdata(2, cnt),
                cellobjdata(3, cmapdata(0, cnt)),
                cellobjdata(0, cmapdata(0, cnt)),
                cmapdata(3, cnt) % 1000,
                cmapdata(3, cnt) / 1000);
            if (cellobjdata(0, cmapdata(0, cnt)) == 10)
            {
                map_data.stair_up_pos =
                    cmapdata(2, cnt) * 1000 + cmapdata(1, cnt);
            }
            if (cellobjdata(0, cmapdata(0, cnt)) == 11)
            {
                map_data.stair_down_pos =
                    cmapdata(2, cnt) * 1000 + cmapdata(1, cnt);
            }
        }
    }
    nooracle = 0;
    map_data.user_map_flag = 1;
}



} // namespace elona

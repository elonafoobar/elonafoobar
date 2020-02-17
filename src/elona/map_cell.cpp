#include "map_cell.hpp"

#include "character.hpp"
#include "elona.hpp"
#include "item.hpp"
#include "map.hpp"
#include "variables.hpp"

namespace elona
{

int tc_at_m81 = 0;



void cell_featset(int x, int y, int info1, int info2, int info3, int info4)
{
    elona_vector1<int> feat_at_m80;
    if (info1 != -1)
    {
        feat_at_m80 = info1;
    }
    else
    {
        feat_at_m80 = cell_data.at(x, y).feats % 1000;
    }
    if (info2 != -1)
    {
        feat_at_m80(1) = info2;
    }
    else
    {
        feat_at_m80(1) = cell_data.at(x, y).feats / 1000 % 100;
    }
    if (info3 != -1)
    {
        feat_at_m80(2) = info3;
    }
    else
    {
        feat_at_m80(2) = cell_data.at(x, y).feats / 100000 % 100;
    }
    if (info4 != -1)
    {
        feat_at_m80(3) = info4;
    }
    else
    {
        feat_at_m80(3) = cell_data.at(x, y).feats / 10000000;
    }
    cell_data.at(x, y).feats = feat_at_m80 + feat_at_m80(1) * 1000 +
        feat_at_m80(2) * 100000 + feat_at_m80(3) * 10000000;
}



void cell_featread(int x, int y)
{
    feat(0) = cell_data.at(x, y).feats % 1000;
    feat(1) = cell_data.at(x, y).feats / 1000 % 100;
    feat(2) = cell_data.at(x, y).feats / 100000 % 100;
    feat(3) = cell_data.at(x, y).feats / 10000000;
}



void cell_featclear(int x, int y)
{
    cell_data.at(x, y).feats = 0;
}



void cell_check(int x, int y)
{
    cellaccess = 1;
    cellchara = -1;
    cellfeat = -1;
    if (x < 0 || x >= map_data.width || y < 0 || y >= map_data.height)
    {
        cellaccess = 0;
        return;
    }
    if (cell_data.at(x, y).chara_index_plus_one != 0)
    {
        cellchara = cell_data.at(x, y).chara_index_plus_one - 1;
        cellaccess = 0;
    }
    if (cell_data.at(x, y).feats != 0)
    {
        cellfeat = cell_data.at(x, y).feats / 1000 % 100;
        if (chip_data.for_feat(x, y).effect & 4)
        {
            cellaccess = 0;
        }
    }
    if (chip_data.for_cell(x, y).effect & 4)
    {
        cellaccess = 0;
    }
}



bool cell_swap(int chara_index_a, int chara_index_b, int x, int y)
{
    int x2_at_m81 = 0;
    int y2_at_m81 = 0;
    if (game_data.mount != 0)
    {
        if (game_data.mount == chara_index_a ||
            game_data.mount == chara_index_b)
        {
            return false;
        }
    }
    tc_at_m81 = chara_index_b;
    if (tc_at_m81 == -1)
    {
        if (cell_data.at(x, y).chara_index_plus_one != 0)
        {
            tc_at_m81 = cell_data.at(x, y).chara_index_plus_one - 1;
        }
    }
    if (tc_at_m81 != -1)
    {
        cell_data
            .at(cdata[chara_index_a].position.x,
                cdata[chara_index_a].position.y)
            .chara_index_plus_one = tc_at_m81 + 1;
        x2_at_m81 = cdata[tc_at_m81].position.x;
        y2_at_m81 = cdata[tc_at_m81].position.y;
        cdata[tc_at_m81].position.x = cdata[chara_index_a].position.x;
        cdata[tc_at_m81].position.y = cdata[chara_index_a].position.y;
    }
    else
    {
        cell_data
            .at(cdata[chara_index_a].position.x,
                cdata[chara_index_a].position.y)
            .chara_index_plus_one = 0;
        x2_at_m81 = x;
        y2_at_m81 = y;
    }
    cell_data.at(x2_at_m81, y2_at_m81).chara_index_plus_one = chara_index_a + 1;
    cdata[chara_index_a].position.x = x2_at_m81;
    cdata[chara_index_a].position.y = y2_at_m81;
    if (chara_index_a == 0 || tc_at_m81 == 0)
    {
        if (game_data.mount)
        {
            cdata[game_data.mount].position.x = cdata.player().position.x;
            cdata[game_data.mount].position.y = cdata.player().position.y;
        }
    }
    return true;
}



void cell_movechara(int cc, int x, int y)
{
    if (cell_data.at(x, y).chara_index_plus_one != 0)
    {
        if (cell_data.at(x, y).chara_index_plus_one - 1 == cc)
        {
            return;
        }
        cell_swap(cc, tc_at_m81);
    }
    else
    {
        cell_data.at(cdata[cc].position.x, cdata[cc].position.y)
            .chara_index_plus_one = 0;
        cdata[cc].position = {x, y};
        cell_data.at(x, y).chara_index_plus_one = cc + 1;
    }
}



int cell_itemlist(int x, int y)
{
    listmax = 0;
    for (const auto& item : inv.ground())
    {
        if (item.number() > 0)
        {
            if (item.position.x == x && item.position.y == y)
            {
                list(0, listmax) = item.index;
                ++listmax;
            }
        }
    }
    return rtval;
}



// Returns pair of number of items and the last item on the cell.
std::pair<int, int> cell_itemoncell(const Position& pos)
{
    int number{};
    int item_{};

    for (const auto& item : inv.ground())
    {
        if (item.number() > 0 && item.position == pos)
        {
            ++number;
            item_ = item.index;
        }
    }

    return std::make_pair(number, item_);
}



void cell_setchara(int cc, int x, int y)
{
    cell_data.at(x, y).chara_index_plus_one = cc + 1;
    cdata[cc].position = Position{x, y};
}



void cell_removechara(int x, int y)
{
    cell_data.at(x, y).chara_index_plus_one = 0;
}



int cell_findspace(int base_x, int base_y, int range)
{
    int f_at_m130 = 0;
    int dy_at_m130 = 0;
    int dx_at_m130 = 0;
    f_at_m130 = 0;
    for (int cnt = 0, cnt_end = (range * 2 + 1); cnt < cnt_end; ++cnt)
    {
        dy_at_m130 = base_y + cnt - 1;
        if (dy_at_m130 < 0 || dy_at_m130 >= map_data.height)
        {
            continue;
        }
        for (int cnt = 0, cnt_end = (range * 2 + 1); cnt < cnt_end; ++cnt)
        {
            dx_at_m130 = base_x + cnt - 1;
            if (dx_at_m130 < 0 || dx_at_m130 >= map_data.width)
            {
                continue;
            }
            if (cell_data.at(dx_at_m130, dy_at_m130).chara_index_plus_one != 0)
            {
                continue;
            }
            if (chip_data.for_cell(dx_at_m130, dy_at_m130).effect & 4)
            {
                continue;
            }
            if (chip_data.for_feat(dx_at_m130, dy_at_m130).effect & 4)
            {
                continue;
            }
            rtval(0) = dx_at_m130;
            rtval(1) = dy_at_m130;
            f_at_m130 = 1;
        }
        if (f_at_m130)
        {
            break;
        }
    }
    return f_at_m130;
}



static int _random_tile(elona_vector1<int> tile)
{
    if (tile(1) == 0 || tile(2) == 0)
    {
        return tile(0);
    }
    return tile(0) + (rnd(tile(2)) == 0) * rnd(tile(1));
}

int cell_get_type(TileKind type)
{
    // TODO dedup from map_converttile?
    elona_vector1<int> tile;
    switch (type)
    {
    case TileKind::normal: tile = tile_default; break;
    case TileKind::wall: tile = tile_wall; break;
    case TileKind::tunnel: tile = tile_tunnel; break;
    case TileKind::room: tile = tile_room; break;
    case TileKind::fog: tile = tile_fog; break;
    default: assert(0);
    }

    return _random_tile(tile);
}

} // namespace elona

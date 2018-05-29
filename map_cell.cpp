#include "map_cell.hpp"
#include "character.hpp"
#include "elona.hpp"
#include "item.hpp"
#include "map.hpp"
#include "variables.hpp"

namespace elona
{

int tc_at_m81 = 0;

void cell_featset(
    int prm_592,
    int prm_593,
    int prm_594,
    int prm_595,
    int prm_596,
    int prm_597)
{
    elona_vector1<int> feat_at_m80;
    if (prm_594 != -1)
    {
        feat_at_m80 = prm_594;
    }
    else
    {
        feat_at_m80 = map(prm_592, prm_593, 6) % 1000;
    }
    if (prm_595 != -1)
    {
        feat_at_m80(1) = prm_595;
    }
    else
    {
        feat_at_m80(1) = map(prm_592, prm_593, 6) / 1000 % 100;
    }
    if (prm_596 != -1)
    {
        feat_at_m80(2) = prm_596;
    }
    else
    {
        feat_at_m80(2) = map(prm_592, prm_593, 6) / 100000 % 100;
    }
    if (prm_597 != -1)
    {
        feat_at_m80(3) = prm_597;
    }
    else
    {
        feat_at_m80(3) = map(prm_592, prm_593, 6) / 10000000;
    }
    map(prm_592, prm_593, 6) = feat_at_m80 + feat_at_m80(1) * 1000
        + feat_at_m80(2) * 100000 + feat_at_m80(3) * 10000000;
    return;
}



int cell_featread(int prm_598, int prm_599, int)
{
    feat(0) = map(prm_598, prm_599, 6) % 1000;
    feat(1) = map(prm_598, prm_599, 6) / 1000 % 100;
    feat(2) = map(prm_598, prm_599, 6) / 100000 % 100;
    feat(3) = map(prm_598, prm_599, 6) / 10000000;
    return 0;
}



void cell_featclear(int prm_601, int prm_602)
{
    map(prm_601, prm_602, 6) = 0;
    return;
}



void cell_check(int prm_603, int prm_604)
{
    cellaccess = 1;
    cellchara = -1;
    cellfeat = -1;
    if (prm_603 < 0 || prm_603 >= mdata(0) || prm_604 < 0
        || prm_604 >= mdata(1))
    {
        cellaccess = 0;
        return;
    }
    if (map(prm_603, prm_604, 1) != 0)
    {
        cellchara = map(prm_603, prm_604, 1) - 1;
        cellaccess = 0;
    }
    if (map(prm_603, prm_604, 6) != 0)
    {
        cellfeat = map(prm_603, prm_604, 6) / 1000 % 100;
        if (chipm(7, map(prm_603, prm_604, 6) % 1000) & 4)
        {
            cellaccess = 0;
        }
    }
    if (chipm(7, map(prm_603, prm_604, 0)) & 4)
    {
        cellaccess = 0;
    }
    return;
}



void cell_swap(int prm_605, int prm_606, int prm_607, int prm_608)
{
    int x2_at_m81 = 0;
    int y2_at_m81 = 0;
    if (gdata_mount != 0)
    {
        if (gdata_mount == prm_605 || gdata_mount == prm_606)
        {
            return;
        }
    }
    tc_at_m81 = prm_606;
    if (tc_at_m81 == -1)
    {
        if (map(prm_607, prm_608, 1) != 0)
        {
            tc_at_m81 = map(prm_607, prm_608, 1) - 1;
        }
    }
    if (tc_at_m81 != -1)
    {
        map(cdata[prm_605].position.x, cdata[prm_605].position.y, 1) =
            tc_at_m81 + 1;
        x2_at_m81 = cdata[tc_at_m81].position.x;
        y2_at_m81 = cdata[tc_at_m81].position.y;
        cdata[tc_at_m81].position.x = cdata[prm_605].position.x;
        cdata[tc_at_m81].position.y = cdata[prm_605].position.y;
    }
    else
    {
        map(cdata[prm_605].position.x, cdata[prm_605].position.y, 1) = 0;
        x2_at_m81 = prm_607;
        y2_at_m81 = prm_608;
    }
    map(x2_at_m81, y2_at_m81, 1) = prm_605 + 1;
    cdata[prm_605].position.x = x2_at_m81;
    cdata[prm_605].position.y = y2_at_m81;
    if (prm_605 == 0 || tc_at_m81 == 0)
    {
        if (gdata_mount)
        {
            cdata[gdata_mount].position.x = cdata[0].position.x;
            cdata[gdata_mount].position.y = cdata[0].position.y;
        }
    }
    return;
}



void cell_movechara(int cc, int x, int y)
{
    if (map(x, y, 1) != 0)
    {
        if (map(x, y, 1) - 1 == cc)
        {
            return;
        }
        cell_swap(cc, tc_at_m81);
    }
    else
    {
        map(cdata[cc].position.x, cdata[cc].position.y, 1) = 0;
        cdata[cc].position = {x, y};
        map(x, y, 1) = cc + 1;
    }
}

int cell_itemlist(int prm_625, int prm_626)
{
    listmax = 0;
    for (const auto& cnt : items(-1))
    {
        if (inv[cnt].number > 0)
        {
            if (inv[cnt].position.x == prm_625
                && inv[cnt].position.y == prm_626)
            {
                list(0, listmax) = cnt;
                ++listmax;
            }
        }
    }
    return rtval;
}

// Returns pair of number of items and the last item on the cell.
std::pair<int, int> cell_itemoncell(const position_t& pos)
{
    int number{};
    int item{};

    for (const auto& ci : items(-1))
    {
        if (inv[ci].number > 0 && inv[ci].position == pos)
        {
            ++number;
            item = ci;
        }
    }

    return std::make_pair(number, item);
}

void cell_setchara(int cc, int x, int y)
{
    map(x, y, 1) = cc + 1;
    cdata[cc].position = position_t{x, y};
}



void cell_removechara(int x, int y)
{
    map(x, y, 1) = 0;
}



int cell_findspace(int prm_796, int prm_797, int prm_798)
{
    int f_at_m130 = 0;
    int dy_at_m130 = 0;
    int dx_at_m130 = 0;
    f_at_m130 = 0;
    for (int cnt = 0, cnt_end = (prm_798 * 2 + 1); cnt < cnt_end; ++cnt)
    {
        dy_at_m130 = prm_797 + cnt - 1;
        if (dy_at_m130 < 0 || dy_at_m130 >= mdata(1))
        {
            continue;
        }
        for (int cnt = 0, cnt_end = (prm_798 * 2 + 1); cnt < cnt_end; ++cnt)
        {
            dx_at_m130 = prm_796 + cnt - 1;
            if (dx_at_m130 < 0 || dx_at_m130 >= mdata(0))
            {
                continue;
            }
            if (map(dx_at_m130, dy_at_m130, 1) != 0)
            {
                continue;
            }
            if (chipm(7, map(dx_at_m130, dy_at_m130, 0)) & 4)
            {
                continue;
            }
            if (chipm(7, map(dx_at_m130, dy_at_m130, 6) % 1000) & 4)
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
    return tile(0) + (rnd(tile(2)) == 0) * rnd(tile(1));
}

int cell_get_type(tile_kind_t type)
{
    // TODO dedup from map_converttile?
    elona_vector1<int> tile;
    switch(type)
    {
    case tile_kind_t::normal:
        tile = tile_default;
        break;
    case tile_kind_t::wall:
        tile = tile_wall;
        break;
    case tile_kind_t::tunnel:
        tile = tile_tunnel;
        break;
    case tile_kind_t::room:
        tile = tile_room;
        break;
    case tile_kind_t::fog:
        tile = tile_fog;
        break;
    default:
        assert(0);
    }

    return _random_tile(tile);
}

} // namespace elona

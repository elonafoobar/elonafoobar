#include "map_cell.hpp"

#include "character.hpp"
#include "elona.hpp"
#include "item.hpp"
#include "map.hpp"
#include "variables.hpp"

namespace elona
{

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



bool cell_swap(Character& chara, const Position& pos)
{
    if (const auto chara_b_index_plus_one =
            cell_data.at(pos.x, pos.y).chara_index_plus_one)
    {
        return cell_swap(chara, cdata[chara_b_index_plus_one - 1]);
    }

    if (game_data.mount != 0)
    {
        if (game_data.mount == chara.index)
        {
            return false;
        }
    }

    cell_data.at(chara.position.x, chara.position.y).chara_index_plus_one = 0;
    chara.position = pos;
    cell_data.at(pos.x, pos.y).chara_index_plus_one = chara.index + 1;

    if (chara.is_player())
    {
        if (game_data.mount)
        {
            cdata[game_data.mount].position = cdata.player().position;
        }
    }
    return true;
}



bool cell_swap(Character& chara_a, Character& chara_b)
{
    if (game_data.mount != 0)
    {
        if (game_data.mount == chara_a.index ||
            game_data.mount == chara_b.index)
        {
            return false;
        }
    }

    std::swap(chara_a.position, chara_b.position);
    cell_data.at(chara_a.position.x, chara_a.position.y).chara_index_plus_one =
        chara_a.index + 1;
    cell_data.at(chara_b.position.x, chara_b.position.y).chara_index_plus_one =
        chara_b.index + 1;

    if (chara_a.is_player() || chara_b.is_player())
    {
        if (game_data.mount)
        {
            cdata[game_data.mount].position = cdata.player().position;
        }
    }
    return true;
}



void cell_movechara(Character& chara, int x, int y)
{
    if (const auto chara_b_index_plus_one =
            cell_data.at(x, y).chara_index_plus_one)
    {
        if (chara_b_index_plus_one - 1 == chara.index)
        {
            return;
        }
        cell_swap(chara, cdata[chara_b_index_plus_one - 1]);
    }
    else
    {
        cell_data.at(chara.position.x, chara.position.y).chara_index_plus_one =
            0;
        chara.position = {x, y};
        cell_data.at(x, y).chara_index_plus_one = chara.index + 1;
    }
}



void cell_setchara(Character& chara, int x, int y)
{
    cell_data.at(x, y).chara_index_plus_one = chara.index + 1;
    chara.position = {x, y};
}



void cell_removechara(const Position& pos)
{
    cell_data.at(pos.x, pos.y).chara_index_plus_one = 0;
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



int cell_count_exact_item_stacks(const Position& pos)
{
    int ret{};
    for (const auto& item : *g_inv.ground())
    {
        if (item->number() > 0 && item->position() == pos)
        {
            ++ret;
        }
    }
    return ret;
}



OptionalItemRef cell_get_item_if_only_one(const Position& pos)
{
    const auto& item_info_actual = cell_data.at(pos.x, pos.y).item_info_actual;
    if (item_info_actual.stack_count() != 1)
    {
        return nullptr;
    }
    else
    {
        const auto index = item_info_actual.item_indice()[0];
        return g_inv.ground()->at(static_cast<InventorySlot>(index - 1));
    }
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

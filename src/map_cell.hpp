#pragma once

#include <unordered_map>

namespace elona
{

struct position_t;

// Maps from an enumeration to an ID in the current tileset.
enum class tile_kind_t : int
{
    normal = 0,
    wall = 1,
    tunnel = 2,
    room = 3,
    fog = 4
};

std::pair<int, int> cell_itemoncell(const position_t& pos);
int cell_featread(int = 0, int = 0, int = 0);
int cell_findspace(int = 0, int = 0, int = 0);
int cell_itemlist(int = 0, int = 0);
void cell_check(int = 0, int = 0);
void cell_featclear(int = 0, int = 0);
void cell_featset(int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);
void cell_movechara(int = 0, int = 0, int = 0);
void cell_refresh(int = 0, int = 0);
void cell_removechara(int = 0, int = 0);
void cell_setchara(int = 0, int = 0, int = 0);
bool cell_swap(int = 0, int = 0, int = 0, int = 0);

/**
 * \param type tile type to generate
 * \return a random tile ID of the provided type
 *
 * Generates a random tile ID to be placed in the current map.
 * The ID is only valid until the tileset is changed.
 * Tilesets can have multiple variations for the same tile type.
 */
int cell_get_type(tile_kind_t type);

} // namespace elona

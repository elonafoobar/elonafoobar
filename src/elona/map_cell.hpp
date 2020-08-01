#pragma once

#include <utility>

#include "eobject/forward.hpp"
#include "optional.hpp"



namespace elona
{

struct Item;
struct Position;
struct Character;



// Maps from an enumeration to an ID in the current tileset.
enum class TileKind : int
{
    normal = 0,
    wall = 1,
    tunnel = 2,
    room = 3,
    fog = 4
};

void cell_featread(int x, int y);
int cell_findspace(int = 0, int = 0, int = 0);
void cell_check(int = 0, int = 0);
void cell_featclear(int = 0, int = 0);
void cell_featset(int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);
void cell_movechara(int = 0, int = 0, int = 0);
void cell_refresh(int = 0, int = 0);
void cell_removechara(int = 0, int = 0);
void cell_setchara(int = 0, int = 0, int = 0);
bool cell_swap(Character& chara, const Position& pos);
bool cell_swap(Character& chara_a, Character& chara_b);


/**
 * Count the exact number of item stacks at @a pos.
 *
 * @param The position to query.
 * @return The exact number of item stacks.
 */
int cell_count_exact_item_stacks(const Position& pos);


/**
 * Get an item at @a pos if there is only one item.
 *
 * @param The position to query.
 * @return The item placed at @a pos.
 */
OptionalItemRef cell_get_item_if_only_one(const Position& pos);


/**
 * \param type tile type to generate
 * \return a random tile ID of the provided type
 *
 * Generates a random tile ID to be placed in the current map.
 * The ID is only valid until the tileset is changed.
 * Tilesets can have multiple variations for the same tile type.
 */
int cell_get_type(TileKind type);

} // namespace elona

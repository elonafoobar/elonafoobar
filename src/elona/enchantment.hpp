#pragma once

#include <string>
#include "optional.hpp"



namespace elona
{

struct Character;
struct Item;



bool enchantment_add(
    Item& item,
    int type,
    int power,
    int flip_percentage = 0,
    bool not_halve = false,
    bool only_check = false,
    bool force = false);



/**
 * Removes the enchantment or reduces its power from the item.
 *
 * @param item The item
 * @param id The enchantment ID
 * @param power The enchantment's power will be reduced by @a power.
 */
void enchantment_remove(Item& item, int id, int power);



/**
 * Find enchantments from chara's equipments.
 *
 * @param chara The character
 * @param id The enchantment ID
 * @return The strongest power of the enchantment if found; otherwise, returns
 *         none.
 */
optional<int> enchantment_find(const Character& chara, int id);



/**
 * Find enchantments from the item.
 *
 * @param item The item
 * @param id The enchantment ID
 * @return The power of the enchantment if found; otherwise, returns none.
 */
optional<int> enchantment_find(const Item& item, int id);

int enchantment_generate(int rank);
int enchantment_gen_level(int base_level);

/**
 * Calculate power of random enchantment.
 *
 * @param multiplier The multiplier of the power (%)
 */
int enchantment_gen_p(int multiplier = 100);



std::string enchantment_print_level(int level);
void get_enchantment_description(int, int, int, bool = false);
void add_enchantments(Item& item);

void initialize_ego_data();



/**
 * Initialize enchantment data. It called from init.cpp only once.
 */
void enchantment_init();

} // namespace elona

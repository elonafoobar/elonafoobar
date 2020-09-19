#pragma once

#include <string>
#include <vector>

#include "../util/range.hpp"
#include "enums.hpp"
#include "eobject/forward.hpp"
#include "optional.hpp"
#include "serialization/concepts.hpp"



namespace elona
{

struct Character;
struct Item;



struct Enchantment
{
    int id = 0;
    int power = 0;



    bool operator==(const Enchantment& other) const noexcept
    {
        return id == other.id && power == other.power;
    }



    template <typename Archive>
    void serialize(Archive& ar)
    {
        /* clang-format off */
        ar(id);
        ar(power);
        /* clang-format on */
    }
};



// Enchantments are sorted by ID (descending order).
struct EnchantmentList
{
    using storage_type = std::vector<Enchantment>;
    using iterator = storage_type::iterator;
    using const_iterator = storage_type::const_iterator;



    EnchantmentList() = default;



    Enchantment& operator[](size_t index)
    {
        return _enchantments.at(index);
    }


    const Enchantment& operator[](size_t index) const
    {
        return _enchantments.at(index);
    }


    size_t size() const noexcept
    {
        return _enchantments.size();
    }


    bool empty() const noexcept
    {
        return _enchantments.empty();
    }


    void clear() noexcept
    {
        _enchantments.clear();
    }


    void add(int id, int power)
    {
        if (id == 0)
            return;

        for (size_t i = 0; i < size(); ++i)
        {
            auto& enc = _enchantments[i];
            if (enc.id == id)
            {
                enc.power += power;
                return;
            }
        }

        _enchantments.push_back(Enchantment{id, power});
        sort();
    }


    void remove(int id, int power)
    {
        if (id == 0)
            return;

        for (size_t i = 0; i < size(); ++i)
        {
            auto& enc = _enchantments[i];
            if (enc.id == id)
            {
                enc.power -= power;
                if (enc.power == 0)
                {
                    // Remove the enchantment
                    _enchantments.erase(_enchantments.begin() + i);
                }
                break;
            }
        }
    }


    void remove_last()
    {
        if (empty())
            return;

        _enchantments.pop_back();
    }



    bool has(int id) const noexcept
    {
        for (const auto& enc : _enchantments)
        {
            if (enc.id == id)
                return true;
        }
        return false;
    }



    void sort()
    {
        range::sort(_enchantments, [](const auto& e1, const auto& e2) {
            return e1.id > e2.id; // descending
        });
    }



    // Range interface

    iterator begin() noexcept
    {
        return _enchantments.begin();
    }

    iterator end() noexcept
    {
        return _enchantments.end();
    }

    const_iterator begin() const noexcept
    {
        return _enchantments.begin();
    }

    const_iterator end() const noexcept
    {
        return _enchantments.end();
    }

    const_iterator cbegin() const noexcept
    {
        return _enchantments.cbegin();
    }

    const_iterator cend() const noexcept
    {
        return _enchantments.cend();
    }



    template <typename Archive>
    void serialize(Archive& ar)
    {
        /* clang-format off */
        ar(_enchantments);
        /* clang-format on */
    }



private:
    storage_type _enchantments;
};



bool enchantment_add(
    const ItemRef& item,
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
void enchantment_remove(const ItemRef& item, int id, int power);



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
optional<int> enchantment_find(const ItemRef& item, int id);

int enchantment_generate(int rank);
int enchantment_gen_level(int base_level);

/**
 * Calculate power of random enchantment.
 *
 * @param multiplier The multiplier of the power (%)
 */
int enchantment_gen_p(int multiplier = 100);



std::string enchantment_print_level(int level);
void get_enchantment_description(int, int, ItemCategory, bool = false);
void add_enchantments(const ItemRef& item);

void initialize_ego_data();



/**
 * Initialize enchantment data. It called from init.cpp only once.
 */
void enchantment_init();

} // namespace elona

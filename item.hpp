#pragma once

#include <memory>
#include <vector>
#include "enums.hpp"
#include "position.hpp"
#include "range.hpp"


namespace elona
{


// FIXME
struct enc_t
{
    int id = 0;
    int power = 0;

    bool operator==(const enc_t& other) const noexcept
    {
        return id == other.id && power == other.power;
    }


    template <typename Archive>
    void serialize(Archive& ar)
    {
        ar(id);
        ar(power);
    }
};


struct item
{
    item();


    int number = 0;
    int value = 0;
    int image = 0;
    int id = 0;
    int quality = 0;
    position_t position;
    int weight = 0;
    identification_state_t identification_state =
        identification_state_t::unidentified;
    int count = 0;
    int dice_x = 0;
    int dice_y = 0;
    int damage_bonus = 0;
    int hit_bonus = 0;
    int dv = 0;
    int pv = 0;
    int skill = 0;
    curse_state_t curse_state = curse_state_t::none;
    int body_part = 0;
    int function = 0;
    int enhancement = 0;
    int own_state = 0;
    int color = 0;
    int subname = 0;
    int material = 0;
    int param1 = 0;
    int param2 = 0;
    int param3 = 0;
    int param4 = 0;
    int difficulty_of_identification = 0;
    int turn = 0;

    int flags = 0;

    std::vector<enc_t> enchantments;


    void clear();

    bool almost_equals(const item& other, bool ignore_position);


    template <typename Archive>
    void serialize(Archive& ar)
    {
        ar(number);
        ar(value);
        ar(image);
        ar(id);
        ar(quality);
        ar(position);
        ar(weight);
        ar(identification_state);
        ar(count);
        ar(dice_x);
        ar(dice_y);
        ar(damage_bonus);
        ar(hit_bonus);
        ar(dv);
        ar(pv);
        ar(skill);
        ar(curse_state);
        ar(body_part);
        ar(function);
        ar(enhancement);
        ar(own_state);
        ar(color);
        ar(subname);
        ar(material);
        ar(param1);
        ar(param2);
        ar(param3);
        ar(param4);
        ar(difficulty_of_identification);
        ar(turn);
        ar(flags);
        range::for_each(
            enchantments, [&](auto&& enchantment) { ar(enchantment); });
    }
};



struct inventory
{
    inventory();


    item& operator()(int index)
    {
        return storage[index];
    }


    item& operator[](int index)
    {
        return storage[index];
    }


private:
    std::vector<item> storage;
};


extern inventory inv;



int ibit(size_t type, int ci);
void ibitmod(size_t type, int ci, int on);


identification_state_t item_identify(item& ci, identification_state_t level);
identification_state_t item_identify(item& ci, int power);


range::iota<int> items(int owner);
int get_random_inv(int owner);


} // namespace elona

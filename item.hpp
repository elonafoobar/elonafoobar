#pragma once

#include <array>
#include <memory>
#include "position.hpp"


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
};


struct item
{
    int number = 0;
    int value = 0;
    int image = 0;
    int id = 0;
    int quality = 0;
    position_t position;
    int weight = 0;
    int identification_state = 0;
    int count = 0;
    int dice_x = 0;
    int dice_y = 0;
    int damage_bonus = 0;
    int hit_bonus = 0;
    int dv = 0;
    int pv = 0;
    int skill = 0;
    int curse_state = 0;
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

    std::array<enc_t, 15> enchantments;


    void clear();

    bool almost_euqals(const item& other, bool ignore_position);
};



struct inventory
{
    item& operator()(int index)
    {
        return storage[index];
    }


    std::unique_ptr<char[]> serialize(int offset = 0) const;

    void
    deserialize(std::unique_ptr<char[]> raw_data, int size, int offset = 0);


private:
    std::array<item, 5480> storage;
};


inline inventory inv;



int ibit(int type, int ci);
void ibitmod(int type, int ci, int on);


} // namespace elona



#include "macro_inv.hpp"

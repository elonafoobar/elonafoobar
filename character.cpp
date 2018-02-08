#include "character.hpp"
#include <cassert>
#include <iostream>
#include <type_traits>
#include "elona.hpp"
#include "range.hpp"
#include "variables.hpp"



namespace elona
{


character::character()
    : growth_buffs(10)
    , body_parts(30)
    , act(10)
    , buffs(16)
    , attr_adjs(10)
    , flags(31)
{
}


void character::clear()
{
    character tmp{};
    using std::swap;
    swap(*this, tmp);
}


void character::clear_flags()
{
    range::fill(flags, 0);
}


character_data::character_data()
    : storage(245)
{
}



int cbit(int type, int cc)
{
    assert(type < sizeof(int) * 8 * 50);
    return cdata(cc).flags[type / 32] & (1 << (type % 32)) ? 1 : 0;
}



void cbitmod(int type, int cc, int on)
{
    assert(type < sizeof(int) * 8 * 50);
    if (on)
    {
        cdata(cc).flags[type / 32] |= 1 << (type % 32);
    }
    else
    {
        cdata(cc).flags[type / 32] &= ~(1 << (type % 32));
    }
}


} // namespace elona

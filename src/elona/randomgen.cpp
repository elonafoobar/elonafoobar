#include "randomgen.hpp"

#include "calc.hpp"
#include "game.hpp"
#include "variables.hpp"



namespace elona
{

elona_vector1<int> fsetrare;



void flt(int level, Quality quality)
{
    filtermax = 0;
    fltselect = 0;
    flttypemajor = 0;
    flttypeminor = 0;
    fltnrace = "";
    objlv = level == 0 ? calcobjlv(game_data.current_dungeon_level) : level;
    fixlv = quality == Quality::none ? calcfixlv(Quality::bad) : quality;
}



void fltn(const std::string& filter)
{
    std::string s2_at_m44;
    int p_at_m44 = 0;
    s2_at_m44 = filter;
    p_at_m44 = 0;
    for (int cnt = 0; cnt < 5; ++cnt)
    {
        getstr(filtern(cnt), s2_at_m44, p_at_m44, 47);
        if (strsize == 0)
        {
            break;
        }
        filtern(cnt) = u8"/"s + filtern(cnt) + u8"/"s;
        p_at_m44 += strsize;
        ++filtermax;
    }
}



int fltsetdungeon()
{
    if (rnd(20) == 0)
    {
        return choice(fsetrare);
    }
    if (rnd(3) == 0)
    {
        return choice(fsetwear);
    }
    return choice(fsetitem);
}

} // namespace elona

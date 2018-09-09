#include "gdata.hpp"
#include "variables.hpp"



namespace elona
{


GameData game_data;
FoobarData foobar_data;

#define GDATA_PACK(x, ident) gdata(x) = ident;

#define GDATA_UNPACK(x, ident) ident = gdata(x);

void GameData::pack_to(elona_vector1<int>& gdata)
{
    GDATA_PACK(0, death_count);
    GDATA_PACK(1, deepest_dungeon_level);
    GDATA_PACK(2, kill_count);
    GDATA_PACK(3, crowd_density);
}

void GameData::unpack_from(elona_vector1<int>& gdata)
{
    GDATA_UNPACK(0, death_count);
    GDATA_UNPACK(1, deepest_dungeon_level);
    GDATA_UNPACK(2, kill_count);
    GDATA_UNPACK(3, crowd_density);
}


void modify_crowd_density(int cc, int delta)
{
    if (cc >= 57)
    {
        game_data.crowd_density += delta;
        if (game_data.crowd_density < 0)
            game_data.crowd_density = 0;
    }
}



} // namespace elona

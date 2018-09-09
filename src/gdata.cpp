#include "gdata.hpp"
#include "variables.hpp"



namespace elona
{


GameData game_data;
FoobarData foobar_data;

#define GDATA_PACK(x, ident) gdata(x) = ident;

#define GDATA_UNPACK(x, ident) ident = gdata(x);

#define SERIALIZE_ALL() \
    SERIALIZE(0, death_count); \
    SERIALIZE(1, deepest_dungeon_level); \
    SERIALIZE(2, kill_count); \
    SERIALIZE(3, crowd_density); \
    SERIALIZE(4, play_turns); \
    SERIALIZE(5, pc_x_in_world_map); \
    SERIALIZE(6, pc_y_in_world_map); \
    SERIALIZE(7, play_days); \
    SERIALIZE(8, random_seed); \
\
    SERIALIZE(16, next_inventory_serial_id); \
    SERIALIZE(17, weather); \
    SERIALIZE(18, hours_until_weather_changes); \
\
    SERIALIZE(24, home_scale); \
    SERIALIZE(25, charge_power); \
    SERIALIZE(26, entrance_type);

#define SERIALIZE GDATA_PACK
void GameData::pack_to(elona_vector1<int>& gdata)
{
    SERIALIZE_ALL();
}
#undef SERIALIZE

#define SERIALIZE GDATA_UNPACK
void GameData::unpack_from(elona_vector1<int>& gdata)
{
    SERIALIZE_ALL();
}
#undef SERIALIZE


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

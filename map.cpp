#include "map.hpp"
#include "character.hpp"
#include "elona.hpp"
#include "position.hpp"
#include "variables.hpp"



bool is_in_fov(const position_t& pos)
{
    return mapsync(pos.x, pos.y) == msync;
}



bool is_in_fov(int cc)
{
    return cdata[cc].vision_flag == msync || cc == gdata_mount;
}

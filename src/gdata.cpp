#include "gdata.hpp"
#include "variables.hpp"



namespace elona
{


foobar_save_t foobar_save;


void foobar_save_t::initialize()
{
    version = latest_version;
}



void modify_crowd_density(int cc, int delta)
{
    if (cc >= 57)
    {
        gdata_crowd_density += delta;
        if (gdata_crowd_density < 0)
            gdata_crowd_density = 0;
    }
}



} // namespace elona

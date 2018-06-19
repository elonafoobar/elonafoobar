#include "gdata.hpp"
#include "variables.hpp"



namespace elona
{


foobar_data_t foobar_data;


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

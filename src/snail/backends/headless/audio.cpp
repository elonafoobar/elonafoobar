#include "../../audio.hpp"



namespace elona
{
namespace snail
{
namespace audio
{


void set_position(int, short, unsigned char)
{
}


int DSINIT()
{
    return 1;
}



void DSLOADFNAME(const std::string&, int)
{
}



void DSPLAY(int, bool)
{
}



void DSSTOP(int)
{
}



void DSSETVOLUME(int, int)
{
}



bool CHECKPLAY(int)
{
    return false;
}



int DMINIT()
{
    return 1;
}



void DMLOADFNAME(const std::string&, int)
{
}



void DMPLAY(int, int)
{
}



void DMSTOP()
{
}

} // namespace audio
} // namespace snail
} // namespace elona

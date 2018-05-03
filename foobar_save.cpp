#include "foobar_save.hpp"



namespace elona
{


foobar_save_t foobar_save;


void foobar_save_t::initialize()
{
    version = latest_version;
}


} // namespace elona

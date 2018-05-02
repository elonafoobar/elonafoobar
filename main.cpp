#include <stdexcept>
#include <SDL.h>
#include "log.hpp"
#include "version.hpp"


namespace elona
{
int run();
}



int main(int argc, char** argv)
{
    using namespace elona;
    (void)argc, (void)argv;

    log::initialize();

    ELONA_LOG(latest_version.long_string());

    try
    {
        return run();
    }
    catch (std::exception& e)
    {
        ELONA_LOG(e.what());
    }
    catch (...)
    {
        ELONA_LOG(u8"Error occurred for some reason.");
    }
}

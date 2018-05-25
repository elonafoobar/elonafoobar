#include <iostream>
#include <stdexcept>
#include <SDL.h>
#include "defines.hpp"
#include "init.hpp"
#include "log.hpp"
#include "version.hpp"
#if defined(ELONA_OS_WINDOWS)
#include <windows.h> // OutputDebugStringA
#endif

namespace elona
{

void report_error(const char* what)
{
#if defined(ELONA_OS_WINDOWS)
    OutputDebugStringA(what);
    MessageBoxA(NULL, what, "Error", MB_OK | MB_ICONSTOP);
#endif
    ELONA_LOG("Error: " << what);
}
} // namespace elona



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
        report_error(e.what());
        throw e;
    }
    catch (...)
    {
        report_error(u8"Error occurred for some reason.");
    }
}

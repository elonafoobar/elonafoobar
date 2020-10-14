#include "elona/main.hpp"

#include <iostream>
#include <stdexcept>

#include <SDL.h>

#include "elona/defines.hpp"
#include "elona/filesystem.hpp"
#include "elona/log.hpp"
#include "snail/application.hpp"
#include "spider/http/core.hpp"
#include "util/backtrace.hpp"
#include "version.hpp"

#if defined(ELONA_OS_WINDOWS)
#include <windows.h> // OutputDebugStringA
#endif


namespace
{

void report_error(const char* what)
{
#if defined(ELONA_OS_WINDOWS)
    OutputDebugStringA(what);
    MessageBoxA(NULL, what, "Error", MB_OK | MB_ICONSTOP);
#endif

    ELONA_ERROR(what);
}

} // namespace



int main(int argc, char** argv)
{
    using namespace elona;

    lib::setup_backtrace();

    log::init(filesystem::dirs::log(), log::LogLevel::info);
    ELONA_LOG(latest_version.long_string());

    spider::http::init();

    // If user press X button at the top of the game window, snail immediately
    // calls std::exit(). The function, std::exit(), does not call destructors
    // of auto storage variables. The destructors of function-local static
    // variables (in this case, snail::Application's instance), however, should
    // be called by std::exit(). We have to register finalizer here to make sure
    // that the spider's loop thread where asynchronous network IO is performed
    // finish. Or, the std::thread's destructors calls std::terminate() and
    // Elona foobar crashes.
    snail::Application::instance().register_finalizer(&spider::http::finalize);

#if DEBUG
    return run(argc, argv);
#else
    try
    {
        return run(argc, argv);
    }
    catch (std::exception& e)
    {
        report_error(e.what());
    }
#endif

    return 0;
}

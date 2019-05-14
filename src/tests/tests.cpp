#define CATCH_CONFIG_RUNNER
#include "../elona/testing.hpp"
#include "../thirdparty/catch2/catch.hpp"
#include "../util/backtrace.hpp"

#ifdef ELONA_OS_WINDOWS
#include <crtdbg.h>

#include <windows>
// Prevent assertion dialogs from appearing on Windows, hanging CI test runs
int WindowsCrtReportHook(int reportType, char* message, int* returnValue)
{
    std::cerr << message << std::endl;
    *returnValue = 0;
    return true;
}
#endif

int main(int argc, char* argv[])
{
#ifdef ELONA_OS_WINDOWS
    // Don't pop up Windows Error Reporting dialog when app crashes. This
    // prevents AppVeyor from hanging.
    _CrtSetReportHook(WindowsCrtReportHook);
    DWORD dwMode = SetErrorMode(SEM_NOGPFAULTERRORBOX);
    SetErrorMode(dwMode | SEM_NOGPFAULTERRORBOX);
#endif

    lib::setup_backtrace();

    srand(static_cast<unsigned int>(std::time(0)));

    elona::testing::pre_init();

    int result = Catch::Session().run(argc, argv);

    elona::testing::post_run();

    return result;
}

#define CATCH_CONFIG_RUNNER
#include "../thirdparty/catch2/catch.hpp"
#include "../testing.hpp"

int main(int argc, char* argv[])
{
    srand(static_cast<unsigned int>(std::time(0)));

    elona::testing::pre_init();

    int result = Catch::Session().run(argc, argv);

    elona::testing::post_run();

    return result;
}

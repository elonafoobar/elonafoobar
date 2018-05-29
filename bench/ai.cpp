#include "../thirdparty/hayai/hayai.hpp"

#include "../testing.hpp"
#include "../debug.hpp"
#include "../event.hpp"
#include "../turn_sequence.hpp"

using namespace elona;

class ElonaFixture
    :   public ::hayai::Fixture
{
public:
    virtual void SetUp()
    {
        testing::pre_init();
        testing::start_in_debug_map();
        debug::voldemort = true;
        event_add(18, 0);
        event_start_proc();
    }

    virtual void TearDown()
    {
        testing::post_run();
    }
};

BENCHMARK_F(ElonaFixture, BenchRagnarok, 2, 20)
{
    turn_begin();
    pass_turns(true);
    turn_end();
}

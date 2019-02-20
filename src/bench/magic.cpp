#include "../thirdparty/hayai/hayai.hpp"

#include <cassert>
#include "../elona/ability.hpp"
#include "../elona/character.hpp"
#include "../elona/debug.hpp"
#include "../elona/testing.hpp"
#include "../elona/variables.hpp"
#include "util.hpp"

using namespace elona;

class MagicChainBombFixture : public ::hayai::Fixture
{
public:
    virtual void SetUp()
    {
        testing::pre_init();
        testing::start_in_debug_map();
        debug::voldemort = true;
        AddBombs(64);
    }

    virtual void TearDown()
    {
        for (int i = 1; i < 10; i++)
        {
            chara_delete(i);
            cdata[i].set_state(Character::State::empty);
        }
        testing::post_run();
    }

    void AddBombs(int amount)
    {
        sdata(17, 0) = 9999;
        for (int i = 1; i < 10; i++)
        {
            int x = i % 50;
            int y = i / 50;
            assert(chara_create(-1, 328, x, y));
            assert(new_ally_joins() == 1);
            cdata[rc].will_explode_soon() = true;
        }

        for (int i = 10; i < amount; i++)
        {
            int x = i % 50;
            int y = i / 50;
            assert(chara_create(-1, 245, x, y));
            cdata[rc].will_explode_soon() = true;
        }
    }
};

BENCHMARK_F(MagicChainBombFixture, BenchMagicChainBomb64, 5, 50)
{
    run_npc_turns();
}

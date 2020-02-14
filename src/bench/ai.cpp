#include <cassert>

#include "../elona/ability.hpp"
#include "../elona/character.hpp"
#include "../elona/debug.hpp"
#include "../elona/event.hpp"
#include "../elona/testing.hpp"
#include "../elona/variables.hpp"
#include "../thirdparty/hayai/hayai.hpp"
#include "util.hpp"

using namespace elona;

class AiFightFixture : public ::hayai::Fixture
{
public:
    virtual void SetUp()
    {
        testing::pre_init();
        testing::start_in_debug_map();
        debug::voldemort = true;
        AddCharas(64);
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

    void AddCharas(int amount)
    {
        sdata(17, 0) = 9999;
        for (int i = 0; i < 10; i++)
        {
            chara_create(-1, 328, i % 50, i / 50);
            new_ally_joins();
        }

        for (int i = 10; i < amount; i++)
        {
            chara_create(-1, 328, i % 50, i / 50);
        }
    }
};

BENCHMARK_F(AiFightFixture, BenchAiFight64, 5, 50)
{
    run_npc_turns();
}


class AiMagicFixture : public ::hayai::Fixture
{
public:
    virtual void SetUp()
    {
        testing::pre_init();
        testing::start_in_debug_map();
        debug::voldemort = true;
        AddCharas(64);
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

    void AddCharas(int amount)
    {
        sdata(17, 0) = 9999;
        for (int i = 1; i < 10; i++)
        {
            chara_create(-1, 60, i % 50, i / 50);
            new_ally_joins();
        }

        for (int i = 10; i < amount; i++)
        {
            chara_create(-1, 60, i % 50, i / 50);
        }
    }
};

BENCHMARK_F(AiMagicFixture, BenchAiMagic64, 5, 50)
{
    run_npc_turns();
}


class AiRagnarokFixture : public ::hayai::Fixture
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

BENCHMARK_F(AiRagnarokFixture, BenchAiRagnarok, 5, 50)
{
    run_npc_turns();
}

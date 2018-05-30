#include "../thirdparty/hayai/hayai.hpp"

#include "util.hpp"
#include "../testing.hpp"
#include "../ability.hpp"
#include "../character.hpp"
#include "../debug.hpp"
#include "../lua_env/lua_env.hpp"
#include "../variables.hpp"
#include <cassert>

class LuaCallbacksWanderFixture
    :   public ::hayai::Fixture
{
public:
    virtual void SetUp()
    {
        testing::pre_init();
        testing::start_in_debug_map();
        debug::voldemort = true;
        AddCharas(64);
        AddCallbacks(1000);
    }

    virtual void TearDown()
    {
        testing::post_run();
    }

    void AddCharas(int amount)
    {
        for (int i = 0; i < amount; i++)
        {
            int x = i % 50;
            int y = i / 50;
            assert(chara_create(-1, 328, x, y));
        }
    }

    void AddCallbacks(int amount)
    {
        for (int i = 0; i < amount; i++)
        {
            elona::lua::lua.run_in_mod("core", R"(
local Event = Elona.require("Event")
local GUI = Elona.require("GUI")
local function my_func()
  for i=1, 100 do
    GUI.txt(tostring(chara))
  end
end

Event.register(Event.CharaMoved, my_func)
)");

        }
    }
};

BENCHMARK_F(LuaCallbacksWanderFixture, BenchLuaCallbacksWander250, 5, 50)
{
    run_npc_turns();
}

class LuaCallbacksWanderNoneFixture
    :   public ::hayai::Fixture
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
        testing::post_run();
    }

    void AddCharas(int amount)
    {
        for (int i = 0; i < amount; i++)
        {
            int x = i % 50;
            int y = i / 50;
            assert(chara_create(-1, 328, x, y));
        }
    }
};

BENCHMARK_F(LuaCallbacksWanderNoneFixture, BenchLuaCallbacksWanderNone, 5, 50)
{
    run_npc_turns();
}

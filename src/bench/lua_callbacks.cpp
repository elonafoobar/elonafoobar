#include "../thirdparty/hayai/hayai.hpp"

#include <cassert>
#include "../ability.hpp"
#include "../character.hpp"
#include "../debug.hpp"
#include "../lua_env/lua_env.hpp"
#include "../testing.hpp"
#include "../variables.hpp"
#include "util.hpp"

class LuaCallbacksWanderFixture : public ::hayai::Fixture
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
        elona::lua::lua->get_mod_manager().load_mod_from_script("bench", "");
        for (int i = 0; i < amount; i++)
        {
            elona::lua::lua->get_mod_manager().run_in_mod("bench", R"(
local GUI = Elona.require("GUI")
local Event = Elona.require("Event")

local function my_func(chara)
  for i=1, 100 do
    GUI.txt(chara.name)
  end
end
Event.register(Event.CharaMoved, my_func)
)");
        }
    }
};

BENCHMARK_F(LuaCallbacksWanderFixture, BenchLuaCallbacksWander1000, 5, 50)
{
    run_npc_turns();
}

class LuaCallbacksWanderNoneFixture : public ::hayai::Fixture
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

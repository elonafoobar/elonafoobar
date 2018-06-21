#include "../thirdparty/catch2/catch.hpp"
#include "../thirdparty/sol2/sol.hpp"

#include "tests.hpp"
#include "../character.hpp"
#include "../dmgheal.hpp"
#include "../filesystem.hpp"
#include "../item.hpp"
#include "../itemgen.hpp"
#include "../lua_env/lua_env.hpp"
#include "../testing.hpp"
#include "../variables.hpp"

using namespace elona::testing;

TEST_CASE("Test that _MOD_NAME is defined", "[Lua: Mods]")
{
    elona::lua::lua_env lua;
    lua.reload();

    REQUIRE_NOTHROW(lua.load_mod_from_script("my_mod", ""));

    REQUIRE_NOTHROW(lua.run_in_mod("my_mod", R"(assert(_MOD_NAME == "my_mod"))"));
}

TEST_CASE("Test that sandboxing removes unsafe functions", "[Lua: Mods]")
{
    elona::lua::lua_env lua;
    lua.reload();

    REQUIRE_NOTHROW(lua.load_mod_from_script("my_mod", ""));

    REQUIRE_THROWS(lua.run_in_mod("my_mod", R"(rawset(_G, "assert", nil))"));
    REQUIRE_THROWS(lua.run_in_mod("my_mod", R"(rawget(_G, "assert"))"));
    REQUIRE_THROWS(lua.run_in_mod("my_mod", R"(rawequal(1, 1))"));
    REQUIRE_THROWS(lua.run_in_mod("my_mod", R"(rawlen({}))"));
    REQUIRE_THROWS(lua.run_in_mod("my_mod", R"(require "mods/core/init")"));
    REQUIRE_THROWS(lua.run_in_mod("my_mod", R"(collectgarbage())"));
    REQUIRE_THROWS(lua.run_in_mod("my_mod", R"(loadstring("i = 1"))"));
    REQUIRE_THROWS(lua.run_in_mod("my_mod", R"(dofile("tests/lua/item.lua"))"));
    REQUIRE_THROWS(lua.run_in_mod("my_mod", R"(loadfile("tests/lua/item.lua"))"));
    REQUIRE_THROWS(lua.run_in_mod("my_mod", R"(load("return function(a,b) return a+b end"))"));
    REQUIRE_THROWS(lua.run_in_mod("my_mod", R"(setmetatable(_G, {}))"));
    REQUIRE_THROWS(lua.run_in_mod("my_mod", R"(getmetatable(_G))"));
    REQUIRE_THROWS(lua.run_in_mod("my_mod", R"(module(..., package.seeall))"));
    REQUIRE_THROWS(lua.run_in_mod("my_mod", R"(setfenv(print, {}))"));
    REQUIRE_THROWS(lua.run_in_mod("my_mod", R"(getfenv(print))"));
    REQUIRE_NOTHROW(lua.run_in_mod("my_mod", R"(assert(package == nil))"));
    REQUIRE_THROWS(lua.run_in_mod("my_mod", R"(package.loadlib("LibSDL2.dll", "main")())"));

    REQUIRE_THROWS(lua.run_in_mod("my_mod", R"(rawlen = nil; rawlen({}))"));
}

TEST_CASE("Test no access to os/io", "[Lua: Mods]")
{
    elona::lua::lua_env lua;
    lua.reload();

    REQUIRE_NOTHROW(lua.load_mod_from_script("my_mod", ""));

    REQUIRE_NOTHROW(lua.run_in_mod("my_mod", R"(assert(os == nil))"));
    REQUIRE_NOTHROW(lua.run_in_mod("my_mod", R"(assert(io == nil))"));
}

TEST_CASE("Test usage of store in mod", "[Lua: Mods]")
{
    elona::lua::lua_env lua;
    lua.reload();

    REQUIRE_NOTHROW(lua.load_mod_from_script("test", "Store.thing = 1"));

    REQUIRE_NOTHROW(lua.run_in_mod("test", "assert(Store.thing == 1)"));
    sol::state_view view(*lua.get_state());
    int thing = lua.get_mod("test")->store->get("thing", view).as<int>();
    assert(thing == 1);
}

TEST_CASE("Test invalid usage of store in main state", "[Lua: Mods]")
{
    elona::lua::lua_env lua;
    lua.reload();

    REQUIRE_NOTHROW(lua.load_mod_from_script("test", "Store.thing = 1"));

    // Accessed from main state, not the mod's environment
    sol::object obj = (*lua.get_state())["Store"]["thing"];
    REQUIRE(obj == sol::lua_nil);
}

TEST_CASE("Test modification of store inside callback", "[Lua: Mods]")
{
    elona::lua::lua_env lua;
    lua.reload();

    REQUIRE_NOTHROW(lua.load_mod_from_script("test", R"(
local Event = Elona.require("Event")

function my_turn_handler()
  Store.thing = Store.thing + 1
end

Store.thing = 1

Event.register(Event.EventKind.AllTurnsFinished, my_turn_handler)
)"));

    REQUIRE_NOTHROW(lua.run_in_mod("test", "assert(Store.thing == 1)"));

    lua.get_event_manager().run_callbacks<elona::lua::event_kind_t::all_turns_finished>();
    REQUIRE_NOTHROW(lua.run_in_mod("test", "assert(Store.thing == 2)"));

    lua.get_event_manager().run_callbacks<elona::lua::event_kind_t::all_turns_finished>();
    lua.get_event_manager().run_callbacks<elona::lua::event_kind_t::all_turns_finished>();
    REQUIRE_NOTHROW(lua.run_in_mod("test", "assert(Store.thing == 4)"));
}

TEST_CASE("Test isolation of mod environments", "[Lua: Mods]")
{
    elona::lua::lua_env lua;
    lua.reload();

    REQUIRE_NOTHROW(lua.load_mod_from_script("first", R"(Store.thing = 42)"));
    REQUIRE_NOTHROW(lua.load_mod_from_script("second", R"(Store.thing = "dood")"));

    REQUIRE_NOTHROW(lua.run_in_mod("first", R"(assert(Store.thing == 42))"));
    REQUIRE_NOTHROW(lua.run_in_mod("second", R"(assert(Store.thing == "dood"))"));

    REQUIRE_NOTHROW(lua.run_in_mod("second", R"(Store.thing = false)"));

    REQUIRE_NOTHROW(lua.run_in_mod("first", R"(assert(Store.thing == 42))"));
    REQUIRE_NOTHROW(lua.run_in_mod("second", R"(assert(Store.thing == false))"));
}


TEST_CASE("Test complex nested table assignment", "[Lua: Mods]")
{
    elona::lua::lua_env lua;
    lua.reload();

    REQUIRE_NOTHROW(lua.load_mod_from_script("test", R"(
local Event = Elona.require("Event")

function my_turn_handler()
   for x = 1, 20 do
      for y = 1, 20 do
         Store.grid[x][y] = 1
      end
   end
end

local grid = {}
for i = 1, 20 do
   grid[i] = {}

   for j = 1, 20 do
      grid[i][j] = 0
   end
end

Store.grid = grid

Event.register(Event.EventKind.AllTurnsFinished, my_turn_handler)
)"));

    REQUIRE_NOTHROW(lua.run_in_mod("test", "assert(Store.grid[1][1] == 0)"));

    lua.get_event_manager().run_callbacks<elona::lua::event_kind_t::all_turns_finished>();
    REQUIRE_NOTHROW(lua.run_in_mod("test", "assert(Store.grid[1][1] == 1)"));
}

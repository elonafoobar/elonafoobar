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

TEST_CASE("Test registering of callback", "[Lua: Events]")
{
    REQUIRE(false);
}

TEST_CASE("Test registering of callback multiple times", "[Lua: Events]")
{

}

TEST_CASE("Test unregistering of callback", "[Lua: Events]")
{

}

TEST_CASE("Test unregistering of callback multiple times", "[Lua: Events]")
{

}

TEST_CASE("Test unregistering of callback without registering", "[Lua: Events]")
{

}

TEST_CASE("Test unregistering of callback inside callback", "[Lua: Events]")
{

}

TEST_CASE("Test unregistering of callback following multiple registries", "[Lua: Events]")
{

}

TEST_CASE("Test clearing of single callback type", "[Lua: Events]")
{

}

TEST_CASE("Test clearing of all callback types", "[Lua: Events]")
{

}

TEST_CASE("Test triggering of callback inside another callback", "[Lua: Events]")
{

}

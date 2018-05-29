#include "../thirdparty/catch2/catch.hpp"
#include "../thirdparty/sol2/sol.hpp"

#include "tests.hpp"
#include "../character.hpp"
#include "../filesystem.hpp"
#include "../item.hpp"
#include "../itemgen.hpp"
#include "../lua_env/lua_env.hpp"
#include "../testing.hpp"
#include "../variables.hpp"

using namespace elona::testing;

TEST_CASE("Test that store can be reset", "[Lua: Serialization]")
{
    elona::lua::lua_env lua;
    lua.scan_all_mods(elona::filesystem::dir::mods());
    lua.load_core_mod(elona::filesystem::dir::mods());

    REQUIRE_NOTHROW(lua.load_mod_from_script("test", "Store.thing = 1"));

    lua.clear_mod_stores();

    REQUIRE_NOTHROW(lua.run_in_mod("test", "assert(Store.thing == nil)"));
}

TEST_CASE("Test that store can be reset across mods", "[Lua: Serialization]")
{
    elona::lua::lua_env lua;
    lua.scan_all_mods(elona::filesystem::dir::mods());
    lua.load_core_mod(elona::filesystem::dir::mods());

    REQUIRE_NOTHROW(lua.load_mod_from_script("test1", "Store.mine = false; Store.thing = 1"));
    REQUIRE_NOTHROW(lua.load_mod_from_script("test2", "Store.theirs = true; Store.thing = 2"));

    lua.clear_mod_stores();

    REQUIRE_NOTHROW(lua.run_in_mod("test1", "assert(Store.thing == nil)"));
    REQUIRE_NOTHROW(lua.run_in_mod("test1", "assert(Store.mine == nil)"));
    REQUIRE_NOTHROW(lua.run_in_mod("test2", "assert(Store.thing == nil)"));
    REQUIRE_NOTHROW(lua.run_in_mod("test2", "assert(Store.theirs == nil)"));
}

TEST_CASE("Test that API tables aren't reset", "[Lua: Serialization]")
{
    elona::lua::lua_env lua;
    lua.scan_all_mods(elona::filesystem::dir::mods());
    lua.load_core_mod(elona::filesystem::dir::mods());

    REQUIRE_NOTHROW(lua.load_mod_from_script("test", R"(Rand = Elona.require("Rand"))"));
    REQUIRE_NOTHROW(lua.run_in_mod("test", "assert(Rand ~= nil)"));

    lua.clear_mod_stores();

    REQUIRE_NOTHROW(lua.run_in_mod("test", "assert(Rand ~= nil)"));
}

TEST_CASE("Test that globals aren't reset", "[Lua: Serialization]")
{
    elona::lua::lua_env lua;
    lua.scan_all_mods(elona::filesystem::dir::mods());
    lua.load_core_mod(elona::filesystem::dir::mods());

    REQUIRE_NOTHROW(lua.load_mod_from_script("test", ""));
    REQUIRE_NOTHROW(lua.run_in_mod("test", R"(assert(_MOD_NAME == "test"))"));

    lua.clear_mod_stores();

    REQUIRE_NOTHROW(lua.run_in_mod("test", R"(assert(_MOD_NAME == "test"))"));
}

TEST_CASE("Test that store can be reset and map init hooks re-run", "[Lua: Serialization]")
{
    elona::lua::lua_env lua;
    lua.scan_all_mods(elona::filesystem::dir::mods());
    lua.load_core_mod(elona::filesystem::dir::mods());

    REQUIRE_NOTHROW(lua.load_mod_from_script("test", R"(
local Event = Elona.require("Event")

function my_map_init_hook()
   Store.val = 42
end

Event.register(Event.EventKind.MapInitialized, my_map_init_hook)
)"));

    lua.get_event_manager().run_callbacks<elona::lua::event_kind_t::map_initialized>();
    REQUIRE_NOTHROW(lua.run_in_mod("test", "assert(Store.val == 42)"));

    lua.clear_mod_stores();

    REQUIRE_NOTHROW(lua.run_in_mod("test", "assert(Store.thing == nil)"));

    lua.get_event_manager().run_callbacks<elona::lua::event_kind_t::map_initialized>();
    REQUIRE_NOTHROW(lua.run_in_mod("test", "assert(Store.val == 42)"));
}

// TEST_CASE("Test that map init hooks are re-run on map change", "[Lua: Serialization]")
// {
//     REQUIRE(0);
// }
//
// TEST_CASE("Test that character init hooks are re-run on map change", "[Lua: Serialization]")
// {
//     REQUIRE(0);
// }
//
// TEST_CASE("Test that item init hooks are re-run on map change", "[Lua: Serialization]")
// {
//     REQUIRE(0);
// }

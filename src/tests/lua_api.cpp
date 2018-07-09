#include "../thirdparty/catch2/catch.hpp"

#include "../filesystem.hpp"
#include "../lua_env/lua_env.hpp"
#include "../testing.hpp"
#include "../variables.hpp"

using namespace std::literals::string_literals;
using namespace elona;

void lua_testcase(const std::string& filename)
{
    elona::testing::reset_state();
    elona::fixlv = 0;
    elona::lua::lua->get_state()->open_libraries(sol::lib::io, sol::lib::os);
    elona::lua::lua->get_api_manager().set_on(*elona::lua::lua);
    REQUIRE_NOTHROW(elona::lua::lua->get_state()->safe_script_file(
        "tests/lua/"s + filename));
    REQUIRE_NOTHROW(elona::lua::lua->get_state()->safe_script(R"(assert(lresults()))"));
}

TEST_CASE("test Elona.require", "[Lua: API]")
{
    elona::lua::lua_env lua;
    lua.scan_all_mods(filesystem::dir::mods());
    lua.load_core_mod(filesystem::dir::mods());

    REQUIRE_NOTHROW(lua.load_mod_from_script("test", R"(
local Rand = Elona.require("Rand")
assert(Rand ~= nil)
assert(type(Rand.coinflip) == "function")
)"));
}

TEST_CASE("test loading of non-ASCII filepaths", "[Lua: Misc]")
{
    lua_testcase(u8"Windowsファイル名.lua");
}

TEST_CASE("test that core API tables are read-only", "[Lua: API]")
{
    lua_testcase("readonly.lua");
}


TEST_CASE("Core API: Chara", "[Lua: API]")
{
    lua_testcase("chara.lua");
}

TEST_CASE("Core API: FOV", "[Lua: API]")
{
    lua_testcase("fov.lua");
}

TEST_CASE("Core API: Item", "[Lua: API]")
{
    lua_testcase("item.lua");
}

TEST_CASE("Core API: Map", "[Lua: API]")
{
    lua_testcase("map.lua");
}

TEST_CASE("Core API: I18N", "[Lua: API]")
{
    lua_testcase("i18n.lua");
}

TEST_CASE("Core API: Trait", "[Lua: API]")
{
    lua_testcase("trait.lua");
}

TEST_CASE("Core API: Input", "[Lua: API]")
{
    lua_testcase("input.lua");
}


TEST_CASE("Core API: LuaCharacter", "[Lua: API]")
{
    lua_testcase("classes/LuaCharacter.lua");
}

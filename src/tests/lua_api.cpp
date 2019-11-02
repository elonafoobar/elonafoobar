#include "../thirdparty/catch2/catch.hpp"

#include "../elona/filesystem.hpp"
#include "../elona/lua_env/api_manager.hpp"
#include "../elona/lua_env/lua_env.hpp"
#include "../elona/lua_env/mod_manager.hpp"
#include "../elona/testing.hpp"
#include "../elona/variables.hpp"
#include "util.hpp"

using namespace std::literals::string_literals;
using namespace elona;

void lua_testcase(const std::string& filename)
{
    std::cout << "TEST FILE: " << filename << std::endl;
    elona::testing::reset_state();
    testing::set_english();
    elona::fixlv = Quality::none;

    elona::lua::lua->get_state()->open_libraries(sol::lib::os);
    elona::lua::lua->get_api_manager().set_on(*elona::lua::lua);
    REQUIRE_NOTHROW(elona::lua::lua->get_state()->safe_script_file(
        "tests/lua/"s + filename));
    REQUIRE_NOTHROW(
        elona::lua::lua->get_state()->safe_script(R"(assert(lresults()))"));
}

TEST_CASE("test require", "[Lua: API]")
{
    elona::lua::LuaEnv lua;
    lua.get_mod_manager().load_mods(filesystem::dirs::mod());

    REQUIRE_NOTHROW(lua.get_mod_manager().load_mod_from_script("test", R"(
local Rand = require("game.Rand")
assert(Rand ~= nil)
assert(type(Rand.coinflip) == "function")
)"));
}

TEST_CASE("test require from other mods", "[Lua: API]")
{
    elona::lua::LuaEnv lua;
    lua.get_mod_manager().load_mods(
        filesystem::dirs::mod(),
        {filesystem::dirs::exe() / u8"tests/data/mods/test_require"});

    REQUIRE_NOTHROW(
        lua.get_mod_manager().load_mod_from_script("test_require_from_mods", R"(
local Hello = require("test_require.Hello")
assert(Hello ~= nil)
assert(type(Hello.hello) == "function")
assert(Hello.hello() == "Hello!")
)"));
}

TEST_CASE("test loading of non-ASCII filepaths", "[Lua: Misc]")
{
    lua_testcase(u8"Windowsファイル名.lua");
}

TEST_CASE("Core API: Chara", "[Lua: API]")
{
    lua_testcase("chara.lua");
}

TEST_CASE("Core API: Env", "[Lua: API]")
{
    const auto foobar_ver = latest_version.short_string();

    elona::lua::LuaEnv lua;
    lua.get_mod_manager().load_mods(filesystem::dirs::mod());
    REQUIRE_NOTHROW(lua.get_mod_manager().load_mod_from_script(
        "test_env",
        "local foobar_ver = '" + foobar_ver + "'\n" +
            R"(
local Env = require("game.Env")

assert(Env.LUA_VERSION, "5.3") -- _VERSION is not available.
assert(Env.ELONA_VERSION, "1.22")
assert(Env.ELONA_FOOBAR_VERSION, foobar_ver)
assert(Env.MOD_API_VERSION, "0.1")
)"));
}

TEST_CASE("Core API: Config", "[Lua: API]")
{
    lua_testcase("config.lua");
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

TEST_CASE("Core API: LuaCharacter", "[Lua: API]")
{
    lua_testcase("classes/LuaCharacter.lua");
}

TEST_CASE("Core API: tostring()", "[Lua: API]")
{
    lua_testcase("tostring.lua");
}

TEST_CASE("Exports: eating_effect", "[Lua: Exports]")
{
    lua_testcase("exports/eating_effect.lua");
}

#include "../elona/filesystem.hpp"
#include "../elona/game.hpp"
#include "../elona/lua_env/api_manager.hpp"
#include "../elona/lua_env/lua_env.hpp"
#include "../elona/lua_env/mod_manager.hpp"
#include "../elona/testing.hpp"
#include "../elona/variables.hpp"
#include "../thirdparty/catch2/catch.hpp"
#include "util.hpp"

using namespace std::literals::string_literals;
using namespace elona;

void do_nothing()
{
}

template <typename F = decltype(do_nothing)>
void lua_testcase(const std::string& filename, F extra_setup = do_nothing)
{
    std::cout << "TEST FILE: " << filename << std::endl;
    elona::testing::reset_state();
    testing::set_english();
    elona::fixlv = Quality::none;

    elona::lua::lua->get_state()->open_libraries(sol::lib::os);
    elona::lua::lua->get_api_manager().set_on(*elona::lua::lua);
    extra_setup();
    REQUIRE_NOTHROW(elona::lua::lua->get_state()->safe_script_file(
        "tests/lua/"s + filename));
    REQUIRE_NOTHROW(
        elona::lua::lua->get_state()->safe_script(R"(assert(lresults()))"));
}

TEST_CASE("test require", "[Lua: API]")
{
    elona::lua::LuaEnv lua;
    lua.load_mods();

    REQUIRE_NOTHROW(
        lua.get_mod_manager().load_testing_mod_from_script("test", R"(
local Rand = ELONA.require("core.Rand")
assert(Rand ~= nil)
assert(type(Rand.coinflip) == "function")
)"));
}

TEST_CASE("test require from other mods", "[Lua: API]")
{
    elona::lua::LuaEnv lua;
    lua.load_mods();
    lua.get_mod_manager().load_testing_mod_from_file(
        filesystem::dirs::exe() / u8"tests/data/mods/test_require");
    lua.get_api_manager().init_from_mods();

    REQUIRE_NOTHROW(lua.get_mod_manager().load_testing_mod_from_script(
        "test_require_from_mods", R"(
local Hello = ELONA.require("test_require.Hello")
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
    lua.load_mods();
    REQUIRE_NOTHROW(lua.get_mod_manager().load_testing_mod_from_script(
        "test_env",
        "local foobar_ver = '" + foobar_ver + "'\n" +
            R"(
local Env = ELONA.require("core.Env")

assert(Env.LUA_VERSION, "5.3") -- _VERSION is not available.
assert(Env.ELONA_VERSION, "1.22")
assert(Env.ELONA_FOOBAR_VERSION, foobar_ver)
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
    lua_testcase("map.lua", []() {
        auto& mod_mgr = lua::lua->get_mod_manager();
        REQUIRE_NOTHROW(mod_mgr.load_testing_mod_from_script("test", ""));
    });
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
    lua::lua->get_api_manager().init_from_mods();
    lua_testcase("exports/eating_effect.lua");
}

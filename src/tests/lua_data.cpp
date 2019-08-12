#include "../thirdparty/catch2/catch.hpp"

#include "../elona/filesystem.hpp"
#include "../elona/lua_env/data_manager.hpp"
#include "../elona/lua_env/export_manager.hpp"
#include "../elona/lua_env/lua_env.hpp"
#include "../elona/lua_env/mod_manager.hpp"
#include "../elona/testing.hpp"
#include "../elona/variables.hpp"
#include "tests.hpp"

TEST_CASE("test reading invalid HCL file", "[Lua: Data]")
{
    const auto base_path = testing::get_test_data_path() / "registry";

    elona::lua::LuaEnv lua;
    lua.get_mod_manager().load_mods(
        filesystem::dirs::mod(), {base_path / "invalid"});

    REQUIRE_THROWS(lua.get_data_manager().init_from_mods());
}

TEST_CASE("test declaring and loading datatype", "[Lua: Data]")
{
    const auto base_path = testing::get_test_data_path() / "registry";

    elona::lua::LuaEnv lua;
    lua.get_mod_manager().load_mods(
        filesystem::dirs::mod(), {base_path / "putit"});

    REQUIRE_NOTHROW(lua.get_data_manager().init_from_mods());

    auto& table = lua.get_data_manager().get();

    auto normal = table.raw("putit.putit", "putit.normal");
    REQUIRE_SOME(normal);
    REQUIRE((*normal)["display_name"].get<std::string>() == "putit");
    REQUIRE((*normal)["legacy_id"].get<int>() == 3);

    auto red = table.raw("putit.putit", "putit.red");
    REQUIRE_SOME(red);
    REQUIRE((*red)["display_name"].get<std::string>() == "red putit");
    REQUIRE((*red)["legacy_id"].get<int>() == 4);
}

// NOTE: requires dependencies on mods to be implemented.
// TEST_CASE("test loading datatype originating from other mod", "[Lua: Data]")
// {
//     const auto base_path = testing::get_test_data_path() / "registry";
//
//     elona::lua::LuaEnv lua;
//     lua.get_mod_manager().load_mods(
//         filesystem::dirs::mod(), {base_path / "putit", base_path /
//         "putit_b"});
//
//     REQUIRE_NOTHROW(lua.get_data_manager().init_from_mods());
//
//     auto& table = lua.get_data_manager().get();
//
//     auto green = table.raw("putit.putit", "putit_b.green");
//     REQUIRE_SOME(green);
//     REQUIRE((*green)["display_name"].get<std::string>() == "green putit");
//     REQUIRE((*green)["legacy_id"].get<int>() == 5);
// }

TEST_CASE(
    "test verification that Exports table only have string keys",
    "[Lua: Data]")
{
    elona::lua::LuaEnv lua;
    REQUIRE_THROWS(lua.get_mod_manager().load_mods(
        filesystem::dirs::mod(),
        {testing::get_test_data_path() / "mods" / "test_export_keys"}));
}

TEST_CASE("test order of script execution", "[Lua: Data]")
{
    const auto base_path = testing::get_test_data_path() / "registry";

    elona::lua::LuaEnv lua;
    lua.get_mod_manager().load_mods(
        filesystem::dirs::mod(), {base_path / "load_order"});

    REQUIRE_NOTHROW(lua.get_data_manager().init_from_mods());

    auto& table = lua.get_data_manager().get();

    auto spell = table.raw("core.ability", "load_order.expecto_patronum");
    REQUIRE_SOME(spell);
    REQUIRE((*spell)["related_basic_attribute"].get<int>() == 17);
    REQUIRE((*spell)["cost"].get<int>() == 100);
}

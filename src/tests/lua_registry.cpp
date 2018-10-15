#include "../thirdparty/catch2/catch.hpp"

// #include "../filesystem.hpp"
// #include "../lua_env/lua_env.hpp"
// #include "../testing.hpp"
// #include "../variables.hpp"
// #include "tests.hpp"
//
// TEST_CASE("test reading invalid HCL file", "[Lua: Registry]")
// {
//     const auto base_path = testing::get_test_data_path() / "registry";
//
//     elona::lua::LuaEnv lua;
//     lua.get_mod_manager().load_mods(filesystem::dir::mods());
//
//     REQUIRE_THROWS(lua.get_registry_manager().load_mod_data(
//         {{base_path / "invalid" / "data.hcl", "test"}}));
// }
//
// TEST_CASE("test declaring and loading datatype", "[Lua: Registry]")
// {
//     const auto base_path = testing::get_test_data_path() / "registry";
//
//     elona::lua::LuaEnv lua;
//     lua.get_mod_manager().load_mods(filesystem::dir::mods());
//
//     REQUIRE_NOTHROW(lua.get_registry_manager().load_mod_data(
//         {{base_path / "putit" / "data.hcl", "test"}}));
//
//     auto table = lua.get_registry_manager().get_table("test", "putit");
//     REQUIRE(table != sol::nullopt);
//
//     sol::table normal = (*table)["test"]["normal"];
//     REQUIRE(normal["name"].get<std::string>() == "putit");
//     REQUIRE(normal["id"].get<int>() == 3);
//     REQUIRE(normal["_id"].get<std::string>() == "test.normal");
//     REQUIRE(normal["_full_id"].get<std::string>() ==
//     "test.putit:test.normal"); REQUIRE(normal["_mod"].get<std::string>() ==
//     "test");
//
//     sol::table red = (*table)["test"]["red"];
//     REQUIRE(red["name"].get<std::string>() == "red putit");
//     REQUIRE(red["id"].get<int>() == 4);
//     REQUIRE(red["_id"].get<std::string>() == "test.red");
//     REQUIRE(red["_full_id"].get<std::string>() == "test.putit:test.red");
//     REQUIRE(red["_mod"].get<std::string>() == "test");
// }
//
// TEST_CASE("test loading datatype originating from other mod", "[Lua:
// Registry]")
// {
//     const auto base_path = testing::get_test_data_path() / "registry";
//
//     elona::lua::LuaEnv lua;
//     lua.get_mod_manager().load_mods(filesystem::dir::mods());
//
//     REQUIRE_NOTHROW(lua.get_registry_manager().load_mod_data(
//         {{base_path / "putit" / "data.hcl", "test"}}));
//     REQUIRE_NOTHROW(lua.get_registry_manager().load_mod_data(
//         {{base_path / "putit_b" / "data.hcl", "putit_b"}}));
//
//     auto table = lua.get_registry_manager().get_table("test", "putit");
//     REQUIRE(table != sol::nullopt);
//
//     sol::table normal = (*table)["putit_b"]["normal"];
//     REQUIRE(normal["name"].get<std::string>() == "putit");
//     REQUIRE(normal["id"].get<int>() == 3);
//     REQUIRE(normal["_id"].get<std::string>() == "putit_b.normal");
//     REQUIRE(
//         normal["_full_id"].get<std::string>() ==
//         "test.putit:putit_b.normal");
//     REQUIRE(normal["_mod"].get<std::string>() == "putit_b");
//
//     sol::table red = (*table)["putit_b"]["red"];
//     REQUIRE(red["name"].get<std::string>() == "red putit");
//     REQUIRE(red["id"].get<int>() == 4);
//     REQUIRE(red["_id"].get<std::string>() == "putit_b.red");
//     REQUIRE(red["_full_id"].get<std::string>() == "test.putit:putit_b.red");
//     REQUIRE(red["_mod"].get<std::string>() == "putit_b");
// }
//
// TEST_CASE(
//     "test verification that API tables only have string keys",
//     "[Lua: Registry]")
// {
//     elona::lua::LuaEnv lua;
//     REQUIRE_THROWS(lua.get_mod_manager().load_mods(
//         filesystem::dir::mods(),
//         {filesystem::dir::exe() / u8"tests/data/mods/test_export_keys"}));
// }

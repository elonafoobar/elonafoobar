#include "../elona/data/types/type_item.hpp"
#include "../elona/filesystem.hpp"
#include "../elona/item.hpp"
#include "../elona/lua_env/data_manager.hpp"
#include "../elona/lua_env/lua_env.hpp"
#include "../elona/lua_env/mod_manager.hpp"
#include "../elona/testing.hpp"
#include "../elona/variables.hpp"
#include "../thirdparty/catch2/catch.hpp"
#include "tests.hpp"

static lua::DataTable load(elona::lua::LuaEnv& lua, const std::string& name)
{
    const auto base_path = testing::get_test_data_path() / "registry";

    lua.load_mods();
    lua.get_mod_manager().load_testing_mod_from_file(base_path / name);

    REQUIRE_NOTHROW(lua.get_data_manager().init_from_mods());

    return lua.get_data_manager().get();
}

TEST_CASE("test registering item", "[Lua: Data]")
{
    elona::lua::LuaEnv lua;
    auto table = load(lua, "item");

    ItemDB db;
    db.initialize(lua.get_data_manager().get());

    auto data = db["item.putitoro"];

    REQUIRE(data);
    REQUIRE(data->legacy_id == 9999);
    REQUIRE(data->image == 695);
    REQUIRE(data->value == 2000);
    REQUIRE(data->weight == 200);
    REQUIRE(data->is_cargo == true);
    REQUIRE(data->filter == "/noshop/nodownload/");
    REQUIRE(data->rffilter == "/fish/");
}

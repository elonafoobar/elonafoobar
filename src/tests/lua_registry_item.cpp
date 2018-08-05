#include "../thirdparty/catch2/catch.hpp"

#include "../db_item.hpp"
#include "../filesystem.hpp"
#include "../item.hpp"
#include "../lua_env/lua_env.hpp"
#include "../testing.hpp"
#include "../variables.hpp"
#include "tests.hpp"

static sol::table load(elona::lua::lua_env& lua, const std::string& name)
{
    const auto base_path = testing::get_test_data_path() / "registry";

    lua.get_mod_manager().load_mods(filesystem::dir::mods());

    REQUIRE_NOTHROW(lua.get_registry_manager().register_native_datatype(
        "item", [](sol::table) {}));
    REQUIRE_NOTHROW(lua.get_registry_manager().load_mod_data(
        {{base_path / name / "data.hcl", name}}));

    auto table = lua.get_registry_manager().get_table("core", "item");
    REQUIRE(table);
    return *table;
}

TEST_CASE("test registering item", "[Lua: Registry]")
{
    elona::lua::lua_env lua;
    auto table = load(lua, "item");

    item_db_ex db;
    db.initialize(table, lua);

    auto data = db["core.item:item.putitoro"];

    REQUIRE(data);
    REQUIRE(data->id == 792);
    REQUIRE(data->image == 695);
    REQUIRE(data->value == 2000);
    REQUIRE(data->weight == 200);
    REQUIRE(data->is_cargo == true);
    REQUIRE(data->filter == "/noshop/nodownload/");
    REQUIRE(data->rffilter == "/fish/");
}

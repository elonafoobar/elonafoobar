#include "../thirdparty/catch2/catch.hpp"

#include "../elona/character.hpp"
#include "../elona/enums.hpp"
#include "../elona/filesystem.hpp"
#include "../elona/lua_env/data_manager.hpp"
#include "../elona/lua_env/lua_env.hpp"
#include "../elona/lua_env/mod_manager.hpp"
#include "../elona/testing.hpp"
#include "../elona/variables.hpp"
#include "tests.hpp"

static lua::DataTable load(elona::lua::LuaEnv& lua, const std::string& name)
{
    const auto base_path = testing::get_test_data_path() / "registry";

    lua.get_mod_manager().load_mods(
        filesystem::dir::mods(), {base_path / name});

    REQUIRE_NOTHROW(lua.get_data_manager().init_from_mods());

    return lua.get_data_manager().get();
}

TEST_CASE("test reading invalid enum", "[Lua: Data]")
{
    elona::lua::LuaEnv lua;
    auto table = load(lua, "chara_invalid_enum");

    CharacterDB db;
    db.initialize(lua.get_data_manager().get());

    auto data = db["chara_invalid_enum.putit"];
    REQUIRE_NONE(data);
    REQUIRE(
        *db.error(SharedId("chara_invalid_enum.putit")) ==
        "Enum value Whatever for Color not found.");
}

TEST_CASE("test reading duplicate keys", "[Lua: Data]")
{
    const auto base_path = testing::get_test_data_path() / "registry";

    elona::lua::LuaEnv lua;
    lua.get_mod_manager().load_mods(
        filesystem::dir::mods(), {base_path / "chara_duplicate_key"});

    REQUIRE_THROWS(lua.get_data_manager().init_from_mods());
}

TEST_CASE("test registering character", "[Lua: Data]")
{
    elona::lua::LuaEnv lua;
    auto table = load(lua, "chara");

    CharacterDB db;
    db.initialize(lua.get_data_manager().get());

    auto data = db["chara.spiral_putit"];

    REQUIRE(data);
    REQUIRE(data->id == 9999);
    REQUIRE(data->item_type == 2);
    REQUIRE(data->filter == "/slime/ether/");
    REQUIRE(data->level == 2);
    REQUIRE(data->portrait_male == "core.zeome");
    REQUIRE(data->portrait_female == "core.zeome");
    REQUIRE(data->image == 430);
    REQUIRE(data->female_image == 431);
    REQUIRE(data->male_image == 432);
    REQUIRE(data->race == "slime");
    REQUIRE(data->class_ == "wizard");

    {
        std::vector<int> expected = {417, 434, 415, 454};
        REQUIRE(data->normal_actions == expected);
    }
    {
        std::vector<int> expected = {636};
        REQUIRE(data->special_actions == expected);
    }
    {
        std::unordered_map<int, int> expected = {{54, 500}};
        REQUIRE(data->resistances == expected);
    }

    REQUIRE(data->color == ColorIndex::blue);
    REQUIRE(data->sex == 1);
    REQUIRE(data->original_relationship == -3);
    REQUIRE(data->_flags[22] == true);
    REQUIRE(data->_flags[27] == true);
}

TEST_CASE("test character's portrait", "[Lua: Data]")
{
    elona::lua::LuaEnv lua;
    auto table = load(lua, "chara_portrait");

    CharacterDB db;
    db.initialize(lua.get_data_manager().get());

    {
        auto data = db["chara_portrait.no_portrait"];
        REQUIRE(data->portrait_male == "");
        REQUIRE(data->portrait_female == "");
    }
    {
        auto data = db["chara_portrait.random_portrait"];
        REQUIRE(data->portrait_male == "__random__");
        REQUIRE(data->portrait_female == "__random__");
    }
    {
        // The portrait resource named "john_doe" will not be defined, but the
        // ID that refers to is accepted.
        auto data = db["chara_portrait.undefined_portrait"];
        REQUIRE(data->portrait_male == "john_doe");
        REQUIRE(data->portrait_female == "john_doe");
    }
    {
        auto data = db["chara_portrait.loyter_portrait"];
        REQUIRE(data->portrait_male == "core.loyter");
        REQUIRE(data->portrait_female == "core.loyter");
    }
    {
        auto data = db["chara_portrait.male_portrait_only"];
        REQUIRE(data->portrait_male == "male_portrait_only");
        REQUIRE(data->portrait_female == "");
    }
    {
        auto data = db["chara_portrait.female_portrait_only"];
        REQUIRE(data->portrait_male == "");
        REQUIRE(data->portrait_female == "female_portrait_only");
    }
    {
        auto data = db["chara_portrait.both_portrait"];
        REQUIRE(data->portrait_male == "male_portrait");
        REQUIRE(data->portrait_female == "female_portrait");
    }
}

TEST_CASE("test registering character with all defaults", "[Lua: Data]")
{
    elona::lua::LuaEnv lua;
    auto table = load(lua, "chara_defaults");

    CharacterDB db;
    db.initialize(lua.get_data_manager().get());

    auto data = db["chara_defaults.nothing"];

    REQUIRE(data);
    REQUIRE(data->id == 9999);
    REQUIRE(data->item_type == 0);
    REQUIRE(data->filter == "");
    REQUIRE(data->level == 0);
    REQUIRE(data->portrait_male == "");
    REQUIRE(data->portrait_female == "");
    REQUIRE(data->image == 0);
    REQUIRE(data->race == "");
    REQUIRE(data->class_ == "");

    {
        std::vector<int> expected = {-1};
        REQUIRE(data->normal_actions == expected);
    }
    {
        std::vector<int> expected = {};
        REQUIRE(data->special_actions == expected);
    }
    {
        std::unordered_map<int, int> expected = {};
        REQUIRE(data->resistances == expected);
    }

    REQUIRE(data->color == ColorIndex::none);
    REQUIRE(data->sex == -1);
    REQUIRE(data->original_relationship == 0);
    REQUIRE(data->_flags[22] == false);
    REQUIRE(data->_flags[27] == false);
}

TEST_CASE("test character flags", "[Lua: Data]")
{
    elona::lua::LuaEnv lua;
    auto table = load(lua, "chara_defaults");

    CharacterDB db;
    db.initialize(lua.get_data_manager().get());

    auto data = db["chara_defaults.nothing"];

    REQUIRE(data);
    for (size_t i = 0; i < 32 * 30; ++i)
    {
        REQUIRE(data->_flags[i] == false);
    }
}

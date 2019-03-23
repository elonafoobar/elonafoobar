#include "../thirdparty/catch2/catch.hpp"
#include "../thirdparty/sol2/sol.hpp"

#include "../elona/character.hpp"
#include "../elona/filesystem.hpp"
#include "../elona/item.hpp"
#include "../elona/itemgen.hpp"
#include "../elona/lua_env/event_manager.hpp"
#include "../elona/lua_env/lua_env.hpp"
#include "../elona/lua_env/lua_event/base_event.hpp"
#include "../elona/lua_env/lua_event/lua_event_map_initialized.hpp"
#include "../elona/lua_env/mod_manager.hpp"
#include "../elona/testing.hpp"
#include "../elona/variables.hpp"
#include "tests.hpp"

using namespace elona::testing;

TEST_CASE("Test that store can be reset", "[Lua: Serialization]")
{
    elona::lua::LuaEnv lua;
    lua.get_mod_manager().load_mods(filesystem::dir::mod());

    REQUIRE_NOTHROW(lua.get_mod_manager().load_mod_from_script(
        "test", "Store.global.thing = 1"));

    lua.get_mod_manager().clear_mod_stores();

    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test", "assert(Store.global.thing == nil)"));
}

TEST_CASE("Test that store can be reset across mods", "[Lua: Serialization]")
{
    elona::lua::LuaEnv lua;
    lua.get_mod_manager().load_mods(filesystem::dir::mod());

    REQUIRE_NOTHROW(lua.get_mod_manager().load_mod_from_script(
        "test1", "Store.global.mine = false; Store.global.thing = 1"));
    REQUIRE_NOTHROW(lua.get_mod_manager().load_mod_from_script(
        "test2", "Store.global.theirs = true; Store.global.thing = 2"));

    lua.get_mod_manager().clear_mod_stores();

    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test1", "assert(Store.global.thing == nil)"));
    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test1", "assert(Store.global.mine == nil)"));
    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test2", "assert(Store.global.thing == nil)"));
    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test2", "assert(Store.global.theirs == nil)"));
}

TEST_CASE("Test that API tables aren't reset", "[Lua: Serialization]")
{
    elona::lua::LuaEnv lua;
    lua.get_mod_manager().load_mods(filesystem::dir::mod());

    REQUIRE_NOTHROW(lua.get_mod_manager().load_mod_from_script("test", ""));
    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test", R"(Rand = Elona.require("Rand"); assert(Rand ~= nil))"));

    lua.get_mod_manager().clear_mod_stores();

    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test", R"(Rand = Elona.require("Rand"); assert(Rand ~= nil))"));
}

TEST_CASE("Test that globals aren't reset", "[Lua: Serialization]")
{
    elona::lua::LuaEnv lua;
    lua.get_mod_manager().load_mods(filesystem::dir::mod());

    REQUIRE_NOTHROW(lua.get_mod_manager().load_mod_from_script("test", ""));
    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test", R"(assert(_MOD_NAME == "test"))"));

    lua.get_mod_manager().clear_mod_stores();

    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test", R"(assert(_MOD_NAME == "test"))"));
}

TEST_CASE(
    "Test that store can be reset and map init hooks re-run",
    "[Lua: Serialization]")
{
    elona::lua::LuaEnv lua;
    lua.get_mod_manager().load_mods(filesystem::dir::mod());

    REQUIRE_NOTHROW(lua.get_mod_manager().load_mod_from_script("test", R"(
local Event = Elona.require("Event")

local function my_map_init_hook()
   Store.global.val = 42
end

Event.register("core.map_initialized", my_map_init_hook)
)"));

    lua.get_event_manager().trigger(
        elona::lua::MapInitializedEvent(true, "", 0));
    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test", "assert(Store.global.val == 42)"));

    lua.get_mod_manager().clear_mod_stores();

    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test", "assert(Store.global.thing == nil)"));

    lua.get_event_manager().trigger(
        elona::lua::MapInitializedEvent(true, "", 0));
    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test", "assert(Store.global.val == 42)"));
}

TEST_CASE("Test preservation of global data", "[Lua: Serialization]")
{
    start_in_debug_map();

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().load_mod_from_script(
        "test_serial_global", R"(
Store.global.val = 42
)"));

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_global", "assert(Store.global.val == 42)"));

    run_in_temporary_map(6, 1, []() {
        REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
            "test_serial_global", "assert(Store.global.val == 42)"));
    });

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_global", "assert(Store.global.val == 42)"));
}


TEST_CASE("Test preservation of map local data", "[Lua: Serialization]")
{
    start_in_debug_map();

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().load_mod_from_script(
        "test_serial_map", R"(
Store.map.val = 42
)"));

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_map", "assert(Store.map.val == 42)"));

    run_in_temporary_map(6, 1, []() {
        REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
            "test_serial_map", "assert(Store.map.val == nil)"));
    });

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_map", "assert(Store.map.val == 42)"));
}


TEST_CASE("Test preservation of data across reloads", "[Lua: Serialization]")
{
    start_in_debug_map();

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().load_mod_from_script(
        "test_serial_reload", R"(
Store.global.val = 42
Store.map.val = "hoge"
)"));

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_reload", "assert(Store.global.val == 42)"));
    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_reload", "assert(Store.map.val == \"hoge\")"));

    save_and_reload();

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_reload", "assert(Store.global.val == 42)"));
    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_reload", "assert(Store.map.val == \"hoge\")"));
}


TEST_CASE("Test preservation of handles across reloads", "[Lua: Serialization]")
{
    start_in_debug_map();

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().load_mod_from_script(
        "test_serial_handle_reload", R"(
local Chara = Elona.require("Chara")
local Item = Elona.require("Item")

Store.global.chara = Chara.create(4, 8, "core.putit")
Store.global.item = Item.create(4, 8, "core.putitoro", 0)
Store.map.chara = Chara.create(4, 8, "core.putit")
Store.map.item = Item.create(4, 8, "core.putitoro", 0)
)"));

    auto mod =
        elona::lua::lua->get_mod_manager().get_mod("test_serial_handle_reload");
    std::string uuid_chara_global = mod->get_store(
        elona::lua::ModInfo::StoreType::global)["chara"]["__uuid"];
    std::string uuid_item_global = mod->get_store(
        elona::lua::ModInfo::StoreType::global)["item"]["__uuid"];
    std::string uuid_chara_map =
        mod->get_store(elona::lua::ModInfo::StoreType::map)["chara"]["__uuid"];
    std::string uuid_item_map =
        mod->get_store(elona::lua::ModInfo::StoreType::map)["item"]["__uuid"];

    save_and_reload();

    mod->env.set("uuid_chara_global", uuid_chara_global);
    mod->env.set("uuid_item_global", uuid_item_global);
    mod->env.set("uuid_chara_map", uuid_chara_map);
    mod->env.set("uuid_item_map", uuid_item_map);

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_handle_reload", R"(
assert(Store.global.chara.__uuid == uuid_chara_global)
assert(Store.global.item.__uuid == uuid_item_global)
assert(Store.map.chara.__uuid == uuid_chara_map)
assert(Store.map.item.__uuid == uuid_item_map)
        )"));

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_handle_reload", R"(
assert(Store.global.chara:is_valid())
assert(Store.global.item:is_valid())
assert(Store.map.chara:is_valid())
assert(Store.map.item:is_valid())
        )"));
}


TEST_CASE(
    "Test preservation of handles across map changes",
    "[Lua: Serialization]")
{
    start_in_debug_map();

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().load_mod_from_script(
        "test_serial_handle_map_change", R"(
local Chara = Elona.require("Chara")

Store.global.chara = Chara.create(4, 8, "core.putit")
Store.global.chara_local = Chara.create(4, 8, "core.putit")

Store.global.chara:recruit_as_ally()
)"));

    auto mod = elona::lua::lua->get_mod_manager().get_mod(
        "test_serial_handle_map_change");
    auto store = mod->get_store(elona::lua::ModInfo::StoreType::global);
    std::string uuid_chara = store["chara"]["__uuid"];
    std::string uuid_chara_local = store["chara_local"]["__uuid"];

    mod->env.set("uuid_chara", uuid_chara);
    mod->env.set("uuid_chara_local", uuid_chara_local);

    run_in_temporary_map(6, 1, [&mod, uuid_chara]() {
        REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
            "test_serial_handle_map_change", R"(
assert(Store.global.chara.__uuid == uuid_chara)
assert(Store.global.chara_local.__uuid == uuid_chara_local)
            )"));
        REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
            "test_serial_handle_map_change", R"(
assert(Store.global.chara:is_valid())
assert(not Store.global.chara_local:is_valid())
            )"));
    });

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_handle_map_change", R"(
assert(Store.global.chara.__uuid == uuid_chara)
assert(Store.global.chara_local.__uuid == uuid_chara_local)
            )"));
    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_handle_map_change", R"(
assert(Store.global.chara:is_valid())
assert(not Store.global.chara_local:is_valid())
            )"));
}


TEST_CASE(
    "Test preservation of map local handles across map changes",
    "[Lua: Serialization]")
{
    start_in_debug_map();

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().load_mod_from_script(
        "test_serial_handle_map_change_local", R"(
local Chara = Elona.require("Chara")
local Item = Elona.require("Item")

Store.map.chara = Chara.create(4, 8, "core.putit")
Store.map.item = Item.create(4, 8, "core.putitoro", 0)
)"));

    auto mod = elona::lua::lua->get_mod_manager().get_mod(
        "test_serial_handle_map_change_local");
    auto store = mod->get_store(elona::lua::ModInfo::StoreType::map);
    std::string uuid_chara = store["chara"]["__uuid"];
    std::string uuid_item = store["item"]["__uuid"];

    run_in_temporary_map(6, 1, [&mod, uuid_chara, uuid_item]() {
        REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
            "test_serial_handle_map_change_local", R"(
assert(Store.map.chara == nil)
assert(Store.map.item == nil)
            )"));
    });

    mod->env.set("uuid_chara", uuid_chara);
    mod->env.set("uuid_item", uuid_item);

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_handle_map_change_local", R"(
assert(Store.map.chara.__uuid == uuid_chara)
assert(Store.map.item.__uuid == uuid_item)
            )"));
    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_handle_map_change_local", R"(
assert(Store.map.chara:is_valid())
assert(Store.map.item:is_valid())
            )"));
}

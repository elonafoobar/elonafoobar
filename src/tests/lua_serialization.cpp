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
#include "../thirdparty/catch2/catch.hpp"
#include "../thirdparty/sol2/sol.hpp"
#include "tests.hpp"

using namespace elona::testing;

TEST_CASE("Test that store can be reset", "[Lua: Serialization]")
{
#if 0
    elona::lua::LuaEnv lua;
    lua.load_mods();

    REQUIRE_NOTHROW(lua.get_mod_manager().load_testing_mod_from_script(
        "test", "mod.store.global.thing = 1"));

    lua.get_mod_manager().clear_mod_stores();

    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test", "assert(mod.store.global.thing == nil)"));
#endif
}

TEST_CASE("Test that store can be assigned", "[Lua: Serialization]")
{
#if 0
    elona::lua::LuaEnv lua;
    lua.load_mods();

    REQUIRE_NOTHROW(
        lua.get_mod_manager().load_testing_mod_from_script("test", R"(
mod.store.global.thing = 1
assert(mod.store.global.thing == 1)
)"));

    REQUIRE_NOTHROW(
        lua.get_mod_manager().run_in_mod("test", R"(mod.store.global = {})"));

    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod("test", R"(
mod.store.global = true
assert(mod.store.global == true)
)"));
#endif
}

TEST_CASE("Test that store cannot have new fields", "[Lua: Serialization]")
{
#if 0
    elona::lua::LuaEnv lua;
    lua.load_mods();

    REQUIRE_THROWS(
        lua.get_mod_manager().load_testing_mod_from_script("test", R"(
mod.store.test = {}
)"));
#endif
}

TEST_CASE("Test that store can be reset across mods", "[Lua: Serialization]")
{
#if 0
    elona::lua::LuaEnv lua;
    lua.load_mods();

    REQUIRE_NOTHROW(lua.get_mod_manager().load_testing_mod_from_script(
        "test1", "mod.store.global.mine = false; mod.store.global.thing = 1"));
    REQUIRE_NOTHROW(lua.get_mod_manager().load_testing_mod_from_script(
        "test2", "mod.store.global.theirs = true; mod.store.global.thing = 2"));

    lua.get_mod_manager().clear_mod_stores();

    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test1", "assert(mod.store.global.thing == nil)"));
    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test1", "assert(mod.store.global.mine == nil)"));
    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test2", "assert(mod.store.global.thing == nil)"));
    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test2", "assert(mod.store.global.theirs == nil)"));
#endif
}

TEST_CASE("Test that API tables aren't reset", "[Lua: Serialization]")
{
#if 0
    elona::lua::LuaEnv lua;
    lua.load_mods();

    REQUIRE_NOTHROW(
        lua.get_mod_manager().load_testing_mod_from_script("test", ""));
    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test",
        R"(local Rand = ELONA.require("core.Rand"); assert(Rand ~= nil))"));

    lua.get_mod_manager().clear_mod_stores();

    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test",
        R"(local Rand = ELONA.require("core.Rand"); assert(Rand ~= nil))"));
#endif
}

TEST_CASE("Test that globals aren't reset", "[Lua: Serialization]")
{
#if 0
    elona::lua::LuaEnv lua;
    lua.load_mods();

    REQUIRE_NOTHROW(
        lua.get_mod_manager().load_testing_mod_from_script("test", ""));
    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test", R"(assert(_MOD_ID == "test"))"));

    lua.get_mod_manager().clear_mod_stores();

    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test", R"(assert(_MOD_ID == "test"))"));
#endif
}

TEST_CASE(
    "Test that store can be reset and map init hooks re-run",
    "[Lua: Serialization]")
{
#if 0
    elona::lua::LuaEnv lua;
    lua.load_mods();

    REQUIRE_NOTHROW(
        lua.get_mod_manager().load_testing_mod_from_script("test", R"(
local Event = ELONA.require("core.Event")

local function my_map_init_hook()
   mod.store.global.val = 42
end

Event.register("core.map_initialized", my_map_init_hook)
)"));

    lua.get_event_manager().trigger(
        elona::lua::MapInitializedEvent(true, "", 0));
    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test", "assert(mod.store.global.val == 42)"));

    lua.get_mod_manager().clear_mod_stores();

    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test", "assert(mod.store.global.thing == nil)"));

    lua.get_event_manager().trigger(
        elona::lua::MapInitializedEvent(true, "", 0));
    REQUIRE_NOTHROW(lua.get_mod_manager().run_in_mod(
        "test", "assert(mod.store.global.val == 42)"));
#endif
}

TEST_CASE("Test preservation of global data", "[Lua: Serialization]")
{
#if 0
    start_in_debug_map();

    REQUIRE_NOTHROW(
        elona::lua::lua->get_mod_manager().load_testing_mod_from_script(
            "test_serial_global", R"(
mod.store.global.val = 42
)"));

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_global", "assert(mod.store.global.val == 42)"));

    run_in_temporary_map(6, 1, []() {
        REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
            "test_serial_global", "assert(mod.store.global.val == 42)"));
    });

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_global", "assert(mod.store.global.val == 42)"));
#endif
}


TEST_CASE("Test preservation of map local data", "[Lua: Serialization]")
{
#if 0
    start_in_debug_map();

    REQUIRE_NOTHROW(
        elona::lua::lua->get_mod_manager().load_testing_mod_from_script(
            "test_serial_map", R"(
mod.store.map.val = 42
)"));

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_map", "assert(mod.store.map.val == 42)"));

    run_in_temporary_map(6, 1, []() {
        REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
            "test_serial_map", "assert(mod.store.map.val == nil)"));
    });

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_map", "assert(mod.store.map.val == 42)"));
#endif
}


TEST_CASE("Test preservation of data across reloads", "[Lua: Serialization]")
{
#if 0
    start_in_debug_map();

    REQUIRE_NOTHROW(
        elona::lua::lua->get_mod_manager().load_testing_mod_from_script(
            "test_serial_reload", R"(
mod.store.global.val = 42
mod.store.map.val = "hoge"
)"));

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_reload", "assert(mod.store.global.val == 42)"));
    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_reload", "assert(mod.store.map.val == \"hoge\")"));

    save();

    REQUIRE_NOTHROW(
        elona::lua::lua->get_mod_manager().run_in_mod("test_serial_reload", R"(
mod.store.global.val = 0
mod.store.map.val = ""
)"));

    load();

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_reload", "assert(mod.store.global.val == 42)"));
    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_reload", "assert(mod.store.map.val == \"hoge\")"));
#endif
}


TEST_CASE("Test preservation of handles across reloads", "[Lua: Serialization]")
{
#if 0
    REQUIRE_NOTHROW(
        elona::lua::lua->get_mod_manager().load_testing_mod_from_script(
            "test_serial_handle_reload", ""));

    start_in_debug_map();

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_handle_reload", R"(
local Chara = ELONA.require("core.Chara")
local Item = ELONA.require("core.Item")

mod.store.global.chara = Chara.create(4, 8, "core.putit")
-- TODO mod.store.global.item = Item.create(4, 8, "core.putitoro", 0)
mod.store.map.chara = Chara.create(4, 8, "core.putit")
-- TODO mod.store.map.item = Item.create(4, 8, "core.putitoro", 0)
        )"));

    auto mod =
        elona::lua::lua->get_mod_manager().get_mod("test_serial_handle_reload");
    auto global =
        mod->get_store(elona::lua::ModEnv::StoreType::global).as<sol::table>();
    auto map =
        mod->get_store(elona::lua::ModEnv::StoreType::map).as<sol::table>();
    std::string uuid_chara_global = global["chara"]["__uuid"];
    // std::string uuid_item_global = global["item"]["__uuid"];
    std::string uuid_chara_map = map["chara"]["__uuid"];
    // std::string uuid_item_map = map["item"]["__uuid"];

    save();

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_handle_reload", R"(
mod.store.global.chara = 0
-- TODO mod.store.global.item = 0
mod.store.map.chara = 0
-- TODO mod.store.map.item = 0
        )"));

    load();

    mod->env.raw_set("uuid_chara_global", uuid_chara_global);
    // mod->env.raw_set("uuid_item_global", uuid_item_global);
    mod->env.raw_set("uuid_chara_map", uuid_chara_map);
    // mod->env.raw_set("uuid_item_map", uuid_item_map);

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_handle_reload", R"(
assert(mod.store.global.chara.__uuid == uuid_chara_global)
-- TODO assert(mod.store.global.item.__uuid == uuid_item_global)
assert(mod.store.map.chara.__uuid == uuid_chara_map)
-- TODO assert(mod.store.map.item.__uuid == uuid_item_map)
        )"));

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_handle_reload", R"(
assert(mod.store.global.chara:is_valid())
-- TODO assert(mod.store.global.item:is_valid())
assert(mod.store.map.chara:is_valid())
-- TODO assert(mod.store.map.item:is_valid())
        )"));
#endif
}


TEST_CASE(
    "Test preservation of handles across map changes",
    "[Lua: Serialization]")
{
#if 0
    REQUIRE_NOTHROW(
        elona::lua::lua->get_mod_manager().load_testing_mod_from_script(
            "test_serial_handle_map_change", ""));

    start_in_debug_map();

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_handle_map_change", R"(
local Chara = ELONA.require("core.Chara")

mod.store.global.chara = Chara.create(4, 8, "core.putit")
mod.store.global.chara_local = Chara.create(4, 8, "core.putit")

mod.store.global.chara:recruit_as_ally()
mod.store.global.it = 0
)"));

    auto mod = elona::lua::lua->get_mod_manager().get_mod(
        "test_serial_handle_map_change");
    auto store =
        mod->get_store(elona::lua::ModEnv::StoreType::global).as<sol::table>();
    std::string uuid_chara = store["chara"]["__uuid"];
    std::string uuid_chara_local = store["chara_local"]["__uuid"];

    mod->env.raw_set("uuid_chara", uuid_chara);
    mod->env.raw_set("uuid_chara_local", uuid_chara_local);

    run_in_temporary_map(6, 1, [uuid_chara]() {
        REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
            "test_serial_handle_map_change", R"(
assert(mod.store.global.chara.__uuid == uuid_chara)
assert(mod.store.global.chara_local.__uuid == uuid_chara_local)
)"));
        REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
            "test_serial_handle_map_change", R"(
assert(mod.store.global.chara:is_valid())
assert(not mod.store.global.chara_local:is_valid())
)"));
    });

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_handle_map_change", R"(
assert(mod.store.global.chara.__uuid == uuid_chara)
assert(mod.store.global.chara_local.__uuid == uuid_chara_local)
)"));
    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_handle_map_change", R"(
assert(mod.store.global.chara:is_valid())
assert(mod.store.global.chara_local:is_valid())
)"));
#endif
}


TEST_CASE(
    "Test preservation of map local handles across map changes",
    "[Lua: Serialization]")
{
#if 0
    REQUIRE_NOTHROW(
        elona::lua::lua->get_mod_manager().load_testing_mod_from_script(
            "test_serial_handle_map_change_local", ""));

    start_in_debug_map();

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_handle_map_change_local", R"(
local Chara = ELONA.require("core.Chara")
local Item = ELONA.require("core.Item")

mod.store.map.chara = Chara.create(4, 8, "core.putit")
-- TODO mod.store.map.item = Item.create(4, 8, "core.putitoro", 0)
)"));

    auto mod = elona::lua::lua->get_mod_manager().get_mod(
        "test_serial_handle_map_change_local");
    auto store =
        mod->get_store(elona::lua::ModEnv::StoreType::map).as<sol::table>();
    std::string uuid_chara = store["chara"]["__uuid"];
    // std::string uuid_item = store["item"]["__uuid"];

    run_in_temporary_map(6, 1, [uuid_chara /* , uuid_item */]() {
        REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
            "test_serial_handle_map_change_local", R"(
assert(mod.store.map.chara == nil)
-- TODO assert(mod.store.map.item == nil)
)"));
    });

    mod->env.raw_set("uuid_chara", uuid_chara);
    // mod->env.raw_set("uuid_item", uuid_item);

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_handle_map_change_local", R"(
assert(mod.store.map.chara.__uuid == uuid_chara)
-- TODO assert(mod.store.map.item.__uuid == uuid_item)
)"));
    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_handle_map_change_local", R"(
assert(mod.store.map.chara:is_valid())
-- TODO assert(mod.store.map.item:is_valid())
)"));
#endif
}


TEST_CASE("Test serialization of recursive table", "[Lua: Serialization]")
{
#if 0
    start_in_debug_map();

    REQUIRE_NOTHROW(
        elona::lua::lua->get_mod_manager().load_testing_mod_from_script(
            "test_serial_recursive", R"(
local t = {}
t[1] = t

mod.store.global.t = t
)"));

    save();

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_recursive", R"(
mod.store.global.t = {}
)"));

    load();

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_recursive", R"(
assert(type(mod.store.global.t) == "table")
assert(type(mod.store.global.t[1]) == "table")
)"));
#endif
}


TEST_CASE("Test serialization of plain value", "[Lua: Serialization]")
{
#if 0
    start_in_debug_map();

    REQUIRE_NOTHROW(
        elona::lua::lua->get_mod_manager().load_testing_mod_from_script(
            "test_serial_plain", R"(
mod.store.global = 42
)"));

    save();

    REQUIRE_NOTHROW(
        elona::lua::lua->get_mod_manager().run_in_mod("test_serial_plain", R"(
mod.store.global = 0
)"));

    load();

    REQUIRE_NOTHROW(
        elona::lua::lua->get_mod_manager().run_in_mod("test_serial_plain", R"(
assert(mod.store.global == 42)
)"));
#endif
}


TEST_CASE("Test serialization of single handle", "[Lua: Serialization]")
{
#if 0
    REQUIRE_NOTHROW(
        elona::lua::lua->get_mod_manager().load_testing_mod_from_script(
            "test_serial_handle", ""));

    start_in_debug_map();

    REQUIRE_NOTHROW(
        elona::lua::lua->get_mod_manager().run_in_mod("test_serial_handle", R"(
local Chara = ELONA.require("core.Chara")

mod.store.global.cute_creature = Chara.create(4, 8, "core.putit")
assert(mod.store.global.cute_creature.__handle == true)
assert(mod.store.global.cute_creature.position.x == 4)
)"));

    save();

    REQUIRE_NOTHROW(
        elona::lua::lua->get_mod_manager().run_in_mod("test_serial_handle", R"(
mod.store.global = {}
)"));

    load();

    REQUIRE_NOTHROW(
        elona::lua::lua->get_mod_manager().run_in_mod("test_serial_handle", R"(
assert(mod.store.global.cute_creature.__handle == true)
assert(mod.store.global.cute_creature.position.x == 4)
)"));
#endif
}


TEST_CASE("Test that disabled mods are not serialized", "[Lua: Serialization]")
{
#if 0 // To enable/disable mods has not been implemented yet.
    start_in_debug_map();

    REQUIRE_NOTHROW(
        elona::lua::lua->get_mod_manager().load_testing_mod_from_script(
            "test_serial_disabled", R"(
mod.store.global.val = 42
)"));

    save();

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_disabled", R"(
mod.store.global.val = 0
)"));

    elona::lua::lua->get_mod_manager().disable_mod("test_serial_disabled");

    load();

    REQUIRE_NOTHROW(
        elona::lua::lua->get_mod_manager().load_testing_mod_from_script(
            "test_serial_disabled", ""));

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_serial_disabled", R"(
assert(mod.store.global.val == nil)
)"));
#endif
}


TEST_CASE("Test private fields are not serialized", "[Lua: Serialization]")
{
#if 0
    start_in_debug_map();

    REQUIRE_NOTHROW(
        elona::lua::lua->get_mod_manager().load_testing_mod_from_script(
            "test_serial_private", R"(
mod.store.global.public = true
mod.store.global.public2 = {
   public = true,
   public2 = {
      public = true,
      _private = true,
   },
   _private = true,
   _private2 = {
      public = true,
      _private = true,
   },
}
mod.store.global._private = true
mod.store.global._private2 = {
   public = true,
   public2 = {
      public = true,
      _private = true,
   },
   _private = true,
   _private2 = {
      public = true,
      _private = true,
   },
}
)"));

    save();

    REQUIRE_NOTHROW(
        elona::lua::lua->get_mod_manager().run_in_mod("test_serial_private", R"(
-- Private fields are skipped on serialization, but they are not removed from
-- the mod.store table.
assert(mod.store.global.public)
assert(mod.store.global.public2)
assert(mod.store.global.public2.public)
assert(mod.store.global.public2.public2)
assert(mod.store.global.public2.public2.public)
assert(mod.store.global.public2.public2._private)
assert(mod.store.global.public2._private)
assert(mod.store.global.public2._private2)
assert(mod.store.global.public2._private2.public)
assert(mod.store.global.public2._private2._private)

assert(mod.store.global._private)
assert(mod.store.global._private2)
assert(mod.store.global._private2.public)
assert(mod.store.global._private2.public2)
assert(mod.store.global._private2.public2.public)
assert(mod.store.global._private2.public2._private)
assert(mod.store.global._private2._private)
assert(mod.store.global._private2._private2)
assert(mod.store.global._private2._private2.public)
assert(mod.store.global._private2._private2._private)

mod.store.global = {} -- clear store
)"));

    load();

    REQUIRE_NOTHROW(
        elona::lua::lua->get_mod_manager().run_in_mod("test_serial_private", R"(
-- Non-private fields are restored.
assert(mod.store.global.public)
assert(mod.store.global.public2)
assert(mod.store.global.public2.public)
assert(mod.store.global.public2.public2)
assert(mod.store.global.public2.public2.public)

-- Non-top-level private fields are restored.
assert(mod.store.global.public2.public2._private)
assert(mod.store.global.public2._private)
assert(mod.store.global.public2._private2)
assert(mod.store.global.public2._private2.public)
assert(mod.store.global.public2._private2._private)

-- Top-level private fields are NOT restored.
assert(not mod.store.global._private)
assert(not mod.store.global._private2)
)"));
#endif
}

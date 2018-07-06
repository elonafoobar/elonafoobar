#include "../thirdparty/catch2/catch.hpp"
#include "../thirdparty/sol2/sol.hpp"

#include "../character.hpp"
#include "../dmgheal.hpp"
#include "../filesystem.hpp"
#include "../item.hpp"
#include "../itemgen.hpp"
#include "../lua_env/lua_env.hpp"
#include "../testing.hpp"
#include "../variables.hpp"
#include "tests.hpp"

using namespace elona::testing;

TEST_CASE("Test character created callback", "[Lua: Callbacks]")
{
    start_in_debug_map();

    REQUIRE_NOTHROW(
        elona::lua::lua.load_mod_from_script("test_chara_created", R"(
local Event = Elona.require("Event")

local function my_chara_created_handler(chara)
   Store.global.charas[chara.index] = chara
end

Store.global.charas = {}

Event.register(Event.EventKind.CharaCreated, my_chara_created_handler)
)"));

    REQUIRE(elona::chara_create(-1, PUTIT_PROTO_ID, 4, 8));
    int idx = elona::rc;
    REQUIRE(idx != -1);
    elona::character& chara = elona::cdata[idx];
    elona::lua::lua.get_mod("test_chara_created")->env.set("idx", idx);

    REQUIRE_NOTHROW(elona::lua::lua.run_in_mod(
        "test_chara_created", R"(assert(Store.global.charas[idx].index == idx))"));
}

TEST_CASE("Test character hurt callback", "[Lua: Callbacks]")
{
    start_in_debug_map();

    REQUIRE_NOTHROW(
        elona::lua::lua.load_mod_from_script("test_chara_hurt", R"(
local Event = Elona.require("Event")

local function my_chara_hurt_handler(chara, amount)
   Store.global.hurt_idx = chara.index
   Store.global.hurt_amount = amount
end

Store.global.hurt_idx = -1
Store.global.hurt_amount = -1

Event.register(Event.EventKind.CharaDamaged, my_chara_hurt_handler)
)"));

    REQUIRE(elona::chara_create(-1, PUTIT_PROTO_ID, 4, 8));
    int idx = elona::rc;
    elona::character& chara = elona::cdata[idx];
    elona::lua::lua.get_mod("test_chara_hurt")->env.set("idx", idx);

    elona::dmghp(idx, 4, -1);
    elona::healhp(idx, 45);

    REQUIRE_NOTHROW(elona::lua::lua.run_in_mod(
        "test_chara_hurt", R"(assert(Store.global.hurt_idx == idx))"));
    REQUIRE_NOTHROW(elona::lua::lua.run_in_mod(
        "test_chara_hurt", R"(assert(Store.global.hurt_amount == 4))"));
}

TEST_CASE("Test character removed callback", "[Lua: Callbacks]")
{
    start_in_debug_map();

    REQUIRE_NOTHROW(
        elona::lua::lua.load_mod_from_script("test_chara_removed", R"(
local Event = Elona.require("Event")

local function my_chara_removed_handler(chara)
   Store.global.removed_idx = chara.index
end

Store.global.removed_idx = -1

Event.register(Event.EventKind.CharaRemoved, my_chara_removed_handler)
)"));

    REQUIRE(elona::chara_create(-1, PUTIT_PROTO_ID, 4, 8));
    int idx = elona::rc;
    elona::character& chara = elona::cdata[idx];
    elona::lua::lua.get_mod("test_chara_removed")->env.set("idx", idx);

    elona::chara_delete(idx);

    REQUIRE_NOTHROW(elona::lua::lua.run_in_mod(
        "test_chara_removed", R"(assert(Store.global.removed_idx == idx))"));
}

TEST_CASE("Test character killed callback", "[Lua: Callbacks]")
{
    start_in_debug_map();

    REQUIRE_NOTHROW(
        elona::lua::lua.load_mod_from_script("test_chara_killed", R"(
local Event = Elona.require("Event")

local function my_chara_killed_handler(chara)
   Store.global.killed_idx = chara.index
end

Store.global.killed_idx = -1

Event.register(Event.EventKind.CharaKilled, my_chara_killed_handler)
)"));

    REQUIRE(elona::chara_create(-1, PUTIT_PROTO_ID, 4, 8));
    int idx = elona::rc;
    elona::character& chara = elona::cdata[idx];
    elona::lua::lua.get_mod("test_chara_killed")->env.set("idx", idx);

    elona::dmghp(idx, chara.max_hp + 1, -11);

    REQUIRE_NOTHROW(elona::lua::lua.run_in_mod(
        "test_chara_killed", R"(assert(Store.global.killed_idx == idx))"));
}

TEST_CASE(
    "Test that killed event is fired for townsfolk but not removed event",
    "[Lua: Callbacks]")
{
    start_in_debug_map();

    REQUIRE_NOTHROW(
        elona::lua::lua.load_mod_from_script("test_townsperson_killed", R"(
local Event = Elona.require("Event")

local function my_chara_removed_handler(chara)
   Store.global.removed_idx = chara.index
end

local function my_chara_killed_handler(chara)
   Store.global.killed_idx = chara.index
end

Store.global.removed_idx = -1
Store.global.killed_idx = -1

Event.register(Event.EventKind.CharaKilled, my_chara_killed_handler)
Event.register(Event.EventKind.CharaRemoved, my_chara_removed_handler)
)"));

    REQUIRE(elona::chara_create(-1, PUTIT_PROTO_ID, 4, 8));
    int idx = elona::rc;
    elona::character& chara = elona::cdata[idx];
    elona::lua::lua.get_mod("test_townsperson_killed")->env.set("idx", idx);

    // Make this character a townsperson.
    chara.character_role = 13;

    elona::dmghp(idx, chara.max_hp + 1, -11);

    REQUIRE_NOTHROW(elona::lua::lua.run_in_mod(
        "test_townsperson_killed", R"(assert(Store.global.killed_idx == idx))"));
    REQUIRE_NOTHROW(elona::lua::lua.run_in_mod(
        "test_townsperson_killed", R"(assert(Store.global.removed_idx == -1))"));
}

TEST_CASE(
    "Test that killed event is fired for special characters but not removed "
    "event",
    "[Lua: Callbacks]")
{
    start_in_debug_map();

    REQUIRE_NOTHROW(
        elona::lua::lua.load_mod_from_script("test_special_chara_killed", R"(
local Event = Elona.require("Event")

local function my_chara_removed_handler(chara)
   Store.global.removed_idx = chara.index
end

local function my_chara_killed_handler(chara)
   Store.global.killed_idx = chara.index
end

Store.global.removed_idx = -1
Store.global.killed_idx = -1

Event.register(Event.EventKind.CharaKilled, my_chara_killed_handler)
Event.register(Event.EventKind.CharaRemoved, my_chara_removed_handler)
)"));

    REQUIRE(elona::chara_create(-1, PUTIT_PROTO_ID, 4, 8));
    int idx = elona::rc;
    elona::character& chara = elona::cdata[idx];
    elona::lua::lua.get_mod("test_special_chara_killed")->env.set("idx", idx);

    // Give this character a role besides a townsperson.
    chara.character_role = 2002;

    elona::dmghp(idx, chara.max_hp + 1, -11);

    REQUIRE_NOTHROW(elona::lua::lua.run_in_mod(
        "test_special_chara_killed", R"(assert(Store.global.killed_idx == idx))"));
    REQUIRE_NOTHROW(elona::lua::lua.run_in_mod(
        "test_special_chara_killed", R"(assert(Store.global.removed_idx == -1))"));
}


TEST_CASE("Test item created callback", "[Lua: Callbacks]")
{
    start_in_debug_map();

    REQUIRE_NOTHROW(
        elona::lua::lua.load_mod_from_script("test_item_created", R"(
local Event = Elona.require("Event")

local function my_item_created_handler(item)
   Store.global.items[item.index] = item
end

Store.global.items = {}

Event.register(Event.EventKind.ItemCreated, my_item_created_handler)
)"));

    REQUIRE(elona::itemcreate(-1, PUTITORO_PROTO_ID, 4, 8, 3));
    int idx = elona::ci;
    REQUIRE(idx != -1);
    elona::item& item = elona::inv[idx];
    elona::lua::lua.get_mod("test_item_created")->env.set("idx", idx);

    REQUIRE_NOTHROW(elona::lua::lua.run_in_mod(
        "test_item_created", R"(assert(Store.global.items[idx].index == idx))"));
}

TEST_CASE("Test map unloading callback", "[Lua: Callbacks]")
{
    start_in_debug_map();

    REQUIRE_NOTHROW(
        elona::lua::lua.load_mod_from_script("test_map_unloading", R"(
local Event = Elona.require("Event")

local function my_map_unloading_handler()
   Store.global.map_unloaded = true
end

Store.global.map_unloaded = false

Event.register(Event.EventKind.MapUnloading, my_map_unloading_handler)
)"));

    run_in_temporary_map(6, 1,
                         []() {
                             REQUIRE_NOTHROW(elona::lua::lua.run_in_mod(
                                                 "test_map_unloading", R"(assert(Store.global.map_unloaded))"));
                                 });
}

TEST_CASE("Test map-local characters becoming unloaded in global state on map transition", "[Lua: Callbacks]")
{
    start_in_debug_map();

    REQUIRE_NOTHROW(
        elona::lua::lua.load_mod_from_script("test_map_local_chara", R"(
local Chara = Elona.require("Chara")

Store.global.chara = Chara.create(24, 24, 3)
Store.global.player = Chara.player()
Store.global.ally = Chara.create(24, 24, 3)
Store.global.ally:recruit_as_ally()
)"));

    REQUIRE_NOTHROW(elona::lua::lua.run_in_mod(
                        "test_map_local_chara", R"(assert(Store.global.chara.is_valid == true))"));

    run_in_temporary_map(6, 1,
                         []() {
                             REQUIRE_NOTHROW(elona::lua::lua.run_in_mod(
                                                 "test_map_local_chara", R"(assert(Store.global.chara.is_valid == false))"));
                             REQUIRE_NOTHROW(elona::lua::lua.run_in_mod(
                                                 "test_map_local_chara", R"(assert(Store.global.player.is_valid == true))"));
                             REQUIRE_NOTHROW(elona::lua::lua.run_in_mod(
                                                 "test_map_local_chara", R"(assert(Store.global.ally.is_valid == true))"));
                                 });
}

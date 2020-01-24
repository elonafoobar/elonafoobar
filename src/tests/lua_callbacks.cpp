#include "../elona/character.hpp"
#include "../elona/dmgheal.hpp"
#include "../elona/filesystem.hpp"
#include "../elona/item.hpp"
#include "../elona/itemgen.hpp"
#include "../elona/lua_env/lua_env.hpp"
#include "../elona/lua_env/mod_manager.hpp"
#include "../elona/testing.hpp"
#include "../elona/variables.hpp"
#include "../thirdparty/catch2/catch.hpp"
#include "../thirdparty/sol2/sol.hpp"
#include "tests.hpp"

using namespace elona::testing;

TEST_CASE("Test character created callback", "[Lua: Callbacks]")
{
    start_in_debug_map();

    REQUIRE_NOTHROW(
        elona::lua::lua->get_mod_manager().load_testing_mod_from_script(
            "test_chara_created", R"(
local Event = require("game.Event")

local function my_chara_created_handler(e)
   mod.store.global.charas[e.chara.index] = e.chara
end

mod.store.global.charas = {}

Event.register("core.character_created", my_chara_created_handler)
)"));

    REQUIRE(elona::chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 8));
    int idx = elona::rc;
    REQUIRE(idx != -1);
    elona::lua::lua->get_mod_manager()
        .get_enabled_mod("test_chara_created")
        ->env.set("idx", idx);

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_chara_created",
        R"(assert(mod.store.global.charas[idx].index == idx))"));
}

TEST_CASE("Test character hurt callback", "[Lua: Callbacks]")
{
    start_in_debug_map();

    REQUIRE_NOTHROW(
        elona::lua::lua->get_mod_manager().load_testing_mod_from_script(
            "test_chara_hurt", R"(
local Event = require("game.Event")

local function my_chara_hurt_handler(e)
   mod.store.global.hurt_idx = e.chara.index
   mod.store.global.hurt_amount = e.damage
end

mod.store.global.hurt_idx = -1
mod.store.global.hurt_amount = -1

Event.register("core.character_damaged", my_chara_hurt_handler)
)"));

    REQUIRE(elona::chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 8));
    int idx = elona::rc;
    elona::lua::lua->get_mod_manager()
        .get_enabled_mod("test_chara_hurt")
        ->env.set("idx", idx);

    elona::damage_hp(cdata[idx], 4, -1);
    elona::heal_hp(cdata[idx], 45);

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_chara_hurt", R"(assert(mod.store.global.hurt_idx == idx))"));
    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_chara_hurt", R"(assert(mod.store.global.hurt_amount == 4))"));
}

TEST_CASE("Test character removed callback", "[Lua: Callbacks]")
{
    start_in_debug_map();

    REQUIRE_NOTHROW(
        elona::lua::lua->get_mod_manager().load_testing_mod_from_script(
            "test_chara_removed", R"(
local Event = require("game.Event")

local function my_chara_removed_handler(e)
   mod.store.global.removed_idx = e.chara.index
end

mod.store.global.removed_idx = -1

Event.register("core.character_removed", my_chara_removed_handler)
)"));

    REQUIRE(elona::chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 8));
    int idx = elona::rc;
    elona::lua::lua->get_mod_manager()
        .get_enabled_mod("test_chara_removed")
        ->env.set("idx", idx);

    testing::invalidate_chara(cdata[idx]);

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_chara_removed",
        R"(assert(mod.store.global.removed_idx == idx))"));
}

TEST_CASE("Test character killed callback", "[Lua: Callbacks]")
{
    start_in_debug_map();

    REQUIRE_NOTHROW(
        elona::lua::lua->get_mod_manager().load_testing_mod_from_script(
            "test_chara_killed", R"(
local Event = require("game.Event")

local function my_chara_killed_handler(e)
   mod.store.global.killed_idx = e.chara.index
end

mod.store.global.killed_idx = -1

Event.register("core.character_killed", my_chara_killed_handler)
)"));

    REQUIRE(elona::chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 8));
    int idx = elona::rc;
    elona::Character& chara = elona::cdata[idx];
    elona::lua::lua->get_mod_manager()
        .get_enabled_mod("test_chara_killed")
        ->env.set("idx", idx);

    elona::damage_hp(cdata[idx], chara.max_hp + 1, -11);

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_chara_killed", R"(assert(mod.store.global.killed_idx == idx))"));
}

TEST_CASE(
    "Test that killed event is fired for townsfolk but not removed event",
    "[Lua: Callbacks]")
{
    start_in_debug_map();

    REQUIRE_NOTHROW(
        elona::lua::lua->get_mod_manager().load_testing_mod_from_script(
            "test_townsperson_killed", R"(
local Chara = require("game.Chara")
local Event = require("game.Event")

mod.store.global.townsperson = Chara.create(0, 0, "core.putit")
mod.store.global.townsperson.role = 14
mod.store.global.idx = mod.store.global.townsperson.index

local function my_chara_removed_handler(e)
   mod.store.global.removed_idx = e.chara.index
end

local function my_chara_killed_handler(e)
   mod.store.global.killed_idx = e.chara.index
end

mod.store.global.removed_idx = -1
mod.store.global.killed_idx = -1

Event.register("core.character_killed", my_chara_killed_handler)
Event.register("core.character_removed", my_chara_removed_handler)
)"));


    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_townsperson_killed",
        R"(mod.store.global.townsperson:damage_hp(mod.store.global.townsperson.max_hp + 1))"));

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_townsperson_killed",
        R"(assert(mod.store.global.killed_idx == mod.store.global.idx))"));
    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_townsperson_killed",
        R"(assert(mod.store.global.removed_idx == -1))"));
}

TEST_CASE(
    "Test that killed event is fired for special characters but not removed "
    "event",
    "[Lua: Callbacks]")
{
    start_in_debug_map();

    REQUIRE_NOTHROW(
        elona::lua::lua->get_mod_manager().load_testing_mod_from_script(
            "test_special_chara_killed", R"(
local Event = require("game.Event")

local function my_chara_removed_handler(e)
   mod.store.global.removed_idx = e.chara.index
end

local function my_chara_killed_handler(e)
   mod.store.global.killed_idx = e.chara.index
end

mod.store.global.removed_idx = -1
mod.store.global.killed_idx = -1

Event.register("core.character_killed", my_chara_killed_handler)
Event.register("core.character_removed", my_chara_removed_handler)
)"));

    REQUIRE(elona::chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 8));
    int idx = elona::rc;
    elona::Character& chara = elona::cdata[idx];
    elona::lua::lua->get_mod_manager()
        .get_enabled_mod("test_special_chara_killed")
        ->env.set("idx", idx);

    // Give this character a role besides a townsperson.
    chara.character_role = 2002;

    elona::damage_hp(cdata[idx], chara.max_hp + 1, -11);

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_special_chara_killed",
        R"(assert(mod.store.global.killed_idx == idx))"));
    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_special_chara_killed",
        R"(assert(mod.store.global.removed_idx == -1))"));
}


TEST_CASE("Test character refreshed callback", "[Lua: Callbacks]")
{
    start_in_debug_map();

    REQUIRE_NOTHROW(
        elona::lua::lua->get_mod_manager().load_testing_mod_from_script(
            "test_chara_refreshed", R"(
local Event = require("game.Event")

local function my_chara_refreshed_handler(e)
   mod.store.global.idx = e.chara.index
end

Event.register("core.character_refreshed", my_chara_refreshed_handler)
)"));

    REQUIRE(elona::chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 8));
    int idx = elona::rc;
    elona::lua::lua->get_mod_manager()
        .get_enabled_mod("test_chara_refreshed")
        ->env.set("idx", idx);

    elona::chara_refresh(idx);

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_chara_refreshed", R"(assert(mod.store.global.idx == idx))"));
}


TEST_CASE("Test item created callback", "[Lua: Callbacks]")
{
    start_in_debug_map();

    REQUIRE_NOTHROW(
        elona::lua::lua->get_mod_manager().load_testing_mod_from_script(
            "test_item_created", R"(
local Event = require("game.Event")

local function my_item_created_handler(e)
   mod.store.global.items[e.item.index] = e.item
end

mod.store.global.items = {}

Event.register("core.item_created", my_item_created_handler)
)"));

    REQUIRE_SOME(
        elona::itemcreate_extra_inv(itemid2int(PUTITORO_PROTO_ID), 4, 8, 3));
    int idx = elona::ci;
    REQUIRE(idx != -1);
    elona::lua::lua->get_mod_manager()
        .get_enabled_mod("test_item_created")
        ->env.set("idx", idx);

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_item_created",
        R"(assert(mod.store.global.items[idx].index == idx))"));
}

TEST_CASE("Test map unloading callback", "[Lua: Callbacks]")
{
    start_in_debug_map();

    REQUIRE_NOTHROW(
        elona::lua::lua->get_mod_manager().load_testing_mod_from_script(
            "test_map_unloading", R"(
local Event = require("game.Event")

local function my_map_unloading_handler()
   mod.store.global.map_unloaded = true
end

mod.store.global.map_unloaded = false

Event.register("core.before_map_unload", my_map_unloading_handler)
)"));

    run_in_temporary_map(6, 1, []() {
        REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
            "test_map_unloading", R"(assert(mod.store.global.map_unloaded))"));
    });
}

TEST_CASE(
    "Test map-local characters becoming unloaded in global state on map "
    "transition",
    "[Lua: Callbacks]")
{
    start_in_debug_map();

    REQUIRE_NOTHROW(
        elona::lua::lua->get_mod_manager().load_testing_mod_from_script(
            "test_map_local_chara", R"(
local Chara = require("game.Chara")

mod.store.global.chara = Chara.create(24, 24, "core.putit")
mod.store.global.player = Chara.player()
mod.store.global.ally = Chara.create(24, 24, "core.putit")
mod.store.global.ally:recruit_as_ally()
)"));

    REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
        "test_map_local_chara",
        R"(assert(mod.store.global.chara:is_valid() == true))"));

    run_in_temporary_map(6, 1, []() {
        REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
            "test_map_local_chara",
            R"(assert(mod.store.global.chara:is_valid() == false))"));
        REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
            "test_map_local_chara",
            R"(assert(mod.store.global.player:is_valid() == true))"));
        REQUIRE_NOTHROW(elona::lua::lua->get_mod_manager().run_in_mod(
            "test_map_local_chara",
            R"(assert(mod.store.global.ally:is_valid() == true))"));
    });
}

#include "../thirdparty/catch2/catch.hpp"
#include "../thirdparty/sol2/sol.hpp"

#include "../character.hpp"
#include "../item.hpp"
#include "../itemgen.hpp"
#include "../lua_env/lua_env.hpp"
#include "../testing.hpp"
#include "../variables.hpp"
#include "tests.hpp"

using namespace elona::testing;
using namespace std::literals::string_literals;

TEST_CASE("Test that handle properties can be read", "[Lua: Handles]")
{
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();

    SECTION("Characters")
    {
        REQUIRE(chara_create(-1, PUTIT_PROTO_ID, 4, 8));
        int idx = elona::rc;
        character& chara = elona::cdata[idx];
        auto handle = handle_mgr.get_handle(chara);
        elona::lua::lua->get_state()->set("chara", handle);
        elona::lua::lua->get_state()->set("idx", idx);
        REQUIRE_NOTHROW(elona::lua::lua->get_state()->safe_script(
            R"(assert(chara.index == idx))"));
        REQUIRE_NOTHROW(elona::lua::lua->get_state()->safe_script(
            R"(assert(chara.position.x == 4))"));
        REQUIRE_NOTHROW(elona::lua::lua->get_state()->safe_script(
            R"(assert(chara.position.y == 8))"));
    }
    SECTION("Items")
    {
        REQUIRE(itemcreate(-1, PUTITORO_PROTO_ID, 4, 8, 3));
        int idx = elona::ci;
        item& item = elona::inv[idx];
        auto handle = handle_mgr.get_handle(item);
        elona::lua::lua->get_state()->set("item", handle);
        elona::lua::lua->get_state()->set("idx", idx);
        REQUIRE_NOTHROW(elona::lua::lua->get_state()->safe_script(
            R"(assert(item.index == idx))"));
        REQUIRE_NOTHROW(elona::lua::lua->get_state()->safe_script(
            R"(assert(item.position.x == 4))"));
        REQUIRE_NOTHROW(elona::lua::lua->get_state()->safe_script(
            R"(assert(item.position.y == 8))"));
        REQUIRE_NOTHROW(elona::lua::lua->get_state()->safe_script(
            R"(assert(item.number == 3))"));
    }
}

TEST_CASE("Test that handle properties can be written", "[Lua: Handles]")
{
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();

    SECTION("Characters")
    {
        character& chara = elona::cdata[0];
        auto handle = handle_mgr.get_handle(chara);
        elona::lua::lua->get_state()->set("chara", handle);
        REQUIRE_NOTHROW(elona::lua::lua->get_state()->safe_script(
            R"(chara.shop_rank = 50)"));
        REQUIRE_NOTHROW(elona::lua::lua->get_state()->safe_script(
            R"(chara.position.x = 4)"));
        REQUIRE_NOTHROW(elona::lua::lua->get_state()->safe_script(
            R"(chara.position.y = 8)"));

        REQUIRE(chara.shop_rank == 50);
        REQUIRE(chara.position.x == 4);
        REQUIRE(chara.position.y == 8);
    }
    SECTION("Items")
    {
        REQUIRE(itemcreate(-1, PUTITORO_PROTO_ID, 0, 0, 1));
        item& item = elona::inv[elona::ci];
        auto handle = handle_mgr.get_handle(item);
        elona::lua::lua->get_state()->set("item", handle);

        REQUIRE_NOTHROW(
            elona::lua::lua->get_state()->safe_script(R"(item.number = 3)"));
        REQUIRE_NOTHROW(
            elona::lua::lua->get_state()->safe_script(R"(item.position.x = 4)"));
        REQUIRE_NOTHROW(
            elona::lua::lua->get_state()->safe_script(R"(item.position.y = 8)"));

        REQUIRE(item.number == 3);
        REQUIRE(item.position.x == 4);
        REQUIRE(item.position.y == 8);
    }
}

TEST_CASE("Test that handle methods can be called", "[Lua: Handles]")
{
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();

    {
        REQUIRE(chara_create(-1, PUTIT_PROTO_ID, 4, 8));
        character& chara = elona::cdata[elona::rc];
        auto handle = handle_mgr.get_handle(chara);
        elona::lua::lua->get_state()->set("chara", handle);

        int hp_before = chara.hp;

        REQUIRE_NOTHROW(
            elona::lua::lua->get_state()->safe_script(R"(chara:damage_hp(7))"));

        REQUIRE(chara.hp == (hp_before - 7));
    }
}

TEST_CASE("Test that handles go invalid", "[Lua: Handles]")
{
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();

    SECTION("Characters")
    {
        REQUIRE(chara_create(-1, PUTIT_PROTO_ID, 4, 8));
        character& chara = elona::cdata[elona::rc];
        auto handle =
            handle_mgr.get_handle(chara);
        elona::lua::lua->get_state()->set("chara", handle);

        std::cout<<"BEGIN"<<std::endl;
        chara_delete(chara.index);
        std::cout<<"END"<<std::endl;

        {
            auto result = elona::lua::lua->get_state()->safe_script(
                R"(print(require("inspect").inspect(chara));print(chara.index))", &sol::script_pass_on_error);
            REQUIRE(!result.valid());
        }
        {
            auto result = elona::lua::lua->get_state()->safe_script(
                R"(chara.position.x = 2)", &sol::script_pass_on_error);
            REQUIRE(!result.valid());
        }
        {
            auto result = elona::lua::lua->get_state()->safe_script(
                R"(chara:damage_hp(1))", &sol::script_pass_on_error);
            REQUIRE(!result.valid());
        }
    }
    SECTION("Items")
    {
        REQUIRE(itemcreate(-1, PUTITORO_PROTO_ID, 4, 8, 3));
        item& item = elona::inv[elona::ci];
        auto handle =
            handle_mgr.get_handle(item);
        elona::lua::lua->get_state()->set("item", handle);

        item_delete(item.index);

        {
            auto result = elona::lua::lua->get_state()->safe_script(
                R"(print(item.number))", &sol::script_pass_on_error);
            REQUIRE(!result.valid());
        }
        {
            auto result = elona::lua::lua->get_state()->safe_script(
                R"(item.position.x = 2)", &sol::script_pass_on_error);
            REQUIRE(!result.valid());
        }
    }
}

TEST_CASE("Test invalid references to handles in store table", "[Lua: Handles]")
{
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();
    auto& mod_mgr = elona::lua::lua->get_mod_manager();

    SECTION("Characters")
    {
        REQUIRE(chara_create(-1, PUTIT_PROTO_ID, 4, 8));
        character& chara = elona::cdata[elona::rc];
        auto handle =
            handle_mgr.get_handle(chara);

        REQUIRE_NOTHROW(mod_mgr.load_mod_from_script("test", ""));

        mod_mgr.get_mod("test")->env.set("chara", handle);
        REQUIRE_NOTHROW(
            mod_mgr.run_in_mod("test", "Store.global.charas = {[0]=chara}"));

        chara_delete(chara.index);

        REQUIRE_THROWS(
            mod_mgr.run_in_mod("test", "print(Store.global.charas[0].index)"));
    }
    SECTION("Items")
    {
        REQUIRE(itemcreate(-1, PUTITORO_PROTO_ID, 4, 8, 3));
        item& item = elona::inv[elona::ci];
        auto handle =
            handle_mgr.get_handle(item);

        REQUIRE_NOTHROW(mod_mgr.load_mod_from_script("test2", ""));

        mod_mgr.get_mod("test2")->env.set("item", handle);
        REQUIRE_NOTHROW(
            mod_mgr.run_in_mod("test2", "Store.global.items = {[0]=item}"));

        item_delete(item.index);

        REQUIRE_THROWS(
            mod_mgr.run_in_mod("test2", "print(Store.global.items[0].index)"));
    }
}

TEST_CASE("Test invalid references to handles from Lua side", "[Lua: Handles]")
{
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();
    auto& mod_mgr = elona::lua::lua->get_mod_manager();

    SECTION("Characters")
    {
        REQUIRE_NOTHROW(
            mod_mgr.load_mod_from_script("test_invalid_chara", R"(
local Chara = Elona.require("Chara")
local chara = Chara.create(0, 0, 3)
idx = chara.index
Store.global.charas = {[0]=chara}
)"));
        int idx = mod_mgr.get_mod("test_invalid_chara")->env["idx"];

        chara_delete(idx);

        REQUIRE_THROWS(mod_mgr.run_in_mod(
            "test_invalid_chara", "print(Store.global.charas[0].index)"));
    }
    SECTION("Items")
    {
        REQUIRE_NOTHROW(
            mod_mgr.load_mod_from_script("test_invalid_item", R"(
local Item = Elona.require("Item")
local item = Item.create(0, 0, 792, 3)
idx = item.index
Store.global.items = {[0]=items}
)"));
        int idx = mod_mgr.get_mod("test_invalid_item")->env["idx"];

        item_delete(idx);

        REQUIRE_THROWS(mod_mgr.run_in_mod(
            "test_invalid_item", "print(Store.global.items[0].index)"));
    }
}

TEST_CASE("Test calling C++ functions taking handles as arguments", "[Lua: Handles]")
{
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();
    auto& mod_mgr = elona::lua::lua->get_mod_manager();

    SECTION("Characters")
    {
        REQUIRE(chara_create(-1, PUTIT_PROTO_ID, 4, 8));
        character& chara = elona::cdata[elona::rc];
        auto handle = handle_mgr.get_handle(chara);

        REQUIRE_NOTHROW(mod_mgr.load_mod_from_script(
            "test_chara_arg", "Store.global.charas = {}"));
        mod_mgr.get_mod("test_chara_arg")->env.set("chara", handle);

        REQUIRE_NOTHROW(mod_mgr.run_in_mod("test_chara_arg", R"(
Store.global.charas[0] = chara
local Chara = Elona.require("Chara")
print(Chara.is_ally(Store.global.charas[0]))
)"));

        chara_delete(chara.index);

        REQUIRE_THROWS(mod_mgr.run_in_mod("test_chara_arg", R"(
local Chara = Elona.require("Chara")
print(Chara.is_ally(Store.global.charas[0]))
)"));
    }
    SECTION("Items")
    {
        REQUIRE(itemcreate(-1, PUTITORO_PROTO_ID, 4, 8, 3));
        item& item = elona::inv[elona::ci];
        auto handle = handle_mgr.get_handle(item);

        REQUIRE_NOTHROW(mod_mgr.load_mod_from_script(
            "test_item_arg", "Store.global.items = {}"));
        mod_mgr.get_mod("test_item_arg")->env.set("item", handle);

        REQUIRE_NOTHROW(mod_mgr.run_in_mod("test_item_arg", R"(
Store.global.items[0] = item
local Item = Elona.require("Item")
Item.has_enchantment(Store.global.items[0], 20)
)"));

        item_delete(item.index);

        REQUIRE_THROWS(mod_mgr.run_in_mod("test_item_arg", R"(
local Item = Elona.require("Item")
Item.has_enchantment(Store.global.items[0], 20)
)"));
    }
}

TEST_CASE("Test uniqueness of handle after original handle has been replaced", "[Lua: Handles]")
{
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();
    auto& mod_mgr = elona::lua::lua->get_mod_manager();

    {
        REQUIRE(chara_create(-1, PUTIT_PROTO_ID, 4, 8));
        character& chara = elona::cdata[elona::rc];
        auto handle = handle_mgr.get_handle(chara);
        elona::lua::lua->get_state()->set("chara", handle);

        REQUIRE(chara_create(-1, PUTIT_PROTO_ID, 4, 9));
        character& chara2 = elona::cdata[elona::rc];
        auto handle2 = handle_mgr.get_handle(chara2);
        elona::lua::lua->get_state()->set("chara2", handle2);

        REQUIRE_NOTHROW(
            elona::lua::lua->get_state()->safe_script(R"(assert(chara == chara))"));
        REQUIRE_NOTHROW(
            elona::lua::lua->get_state()->safe_script(R"(assert(chara ~= chara2))"));

        chara_delete(chara.index);

        REQUIRE_NOTHROW(
            elona::lua::lua->get_state()->safe_script(R"(assert(chara ~= nil))"));
        REQUIRE_NOTHROW(
            elona::lua::lua->get_state()->safe_script(R"(assert(chara ~= chara2))"));

        REQUIRE(chara_create(-1, PUTIT_PROTO_ID, 4, 8));
        character& chara3 = elona::cdata[elona::rc];
        auto handle3 = handle_mgr.get_handle(chara3);
        elona::lua::lua->get_state()->set("chara3", handle3);

        REQUIRE_NOTHROW(
            elona::lua::lua->get_state()->safe_script(R"(assert(chara ~= chara3))"));
    }
}

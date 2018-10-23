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
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();

    SECTION("Characters")
    {
        REQUIRE(chara_create(-1, PUTIT_PROTO_ID, 4, 8));
        int idx = elona::rc;
        Character& chara = elona::cdata[idx];
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
        Item& item = elona::inv[idx];
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
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();

    SECTION("Characters")
    {
        Character& chara = elona::cdata.player();
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
        Item& item = elona::inv[elona::ci];
        auto handle = handle_mgr.get_handle(item);
        elona::lua::lua->get_state()->set("item", handle);

        REQUIRE_NOTHROW(
            elona::lua::lua->get_state()->safe_script(R"(item.number = 3)"));
        REQUIRE_NOTHROW(elona::lua::lua->get_state()->safe_script(
            R"(item.position.x = 4)"));
        REQUIRE_NOTHROW(elona::lua::lua->get_state()->safe_script(
            R"(item.position.y = 8)"));

        REQUIRE(item.number() == 3);
        REQUIRE(item.position.x == 4);
        REQUIRE(item.position.y == 8);
    }
}

TEST_CASE("Test that handle methods can be called", "[Lua: Handles]")
{
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();

    {
        REQUIRE(chara_create(-1, PUTIT_PROTO_ID, 4, 8));
        Character& chara = elona::cdata[elona::rc];
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
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();

    SECTION("Characters")
    {
        REQUIRE(chara_create(-1, PUTIT_PROTO_ID, 4, 8));
        Character& chara = elona::cdata[elona::rc];
        auto handle = handle_mgr.get_handle(chara);
        elona::lua::lua->get_state()->set("chara", handle);

        chara_delete(chara.index);

        {
            auto result = elona::lua::lua->get_state()->safe_script(
                R"(print(chara.index))", &sol::script_pass_on_error);
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
        Item& item = elona::inv[elona::ci];
        auto handle = handle_mgr.get_handle(item);
        elona::lua::lua->get_state()->set("item", handle);

        item_delete(item.index);

        {
            auto result = elona::lua::lua->get_state()->safe_script(
                R"(print(item.number()))", &sol::script_pass_on_error);
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
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();
    auto& mod_mgr = elona::lua::lua->get_mod_manager();

    SECTION("Characters")
    {
        REQUIRE(chara_create(-1, PUTIT_PROTO_ID, 4, 8));
        Character& chara = elona::cdata[elona::rc];
        auto handle = handle_mgr.get_handle(chara);

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
        Item& item = elona::inv[elona::ci];
        auto handle = handle_mgr.get_handle(item);

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
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();
    auto& mod_mgr = elona::lua::lua->get_mod_manager();

    SECTION("Characters")
    {
        REQUIRE_NOTHROW(mod_mgr.load_mod_from_script("test_invalid_chara", R"(
local Chara = Elona.require("Chara")
local chara = Chara.create(0, 0, "core.putit")
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
        REQUIRE_NOTHROW(mod_mgr.load_mod_from_script("test_invalid_item", R"(
local Item = Elona.require("Item")
local item = Item.create(0, 0, "core.putitoro", 3)
idx = item.index
Store.global.items = {[0]=items}
)"));
        int idx = mod_mgr.get_mod("test_invalid_item")->env["idx"];

        item_delete(idx);

        REQUIRE_THROWS(mod_mgr.run_in_mod(
            "test_invalid_item", "print(Store.global.items[0].index)"));
    }
}

TEST_CASE(
    "Test calling C++ functions taking handles as arguments",
    "[Lua: Handles]")
{
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();
    auto& mod_mgr = elona::lua::lua->get_mod_manager();

    SECTION("Characters")
    {
        REQUIRE(chara_create(-1, PUTIT_PROTO_ID, 4, 8));
        Character& chara = elona::cdata[elona::rc];
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
        Item& item = elona::inv[elona::ci];
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

TEST_CASE(
    "Test uniqueness of handle after original handle has been replaced",
    "[Lua: Handles]")
{
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();
    auto& mod_mgr = elona::lua::lua->get_mod_manager();

    {
        REQUIRE(chara_create(-1, PUTIT_PROTO_ID, 4, 8));
        Character& chara = elona::cdata[elona::rc];
        auto handle = handle_mgr.get_handle(chara);
        elona::lua::lua->get_state()->set("chara", handle);

        REQUIRE(chara_create(-1, PUTIT_PROTO_ID, 4, 9));
        Character& chara2 = elona::cdata[elona::rc];
        auto handle2 = handle_mgr.get_handle(chara2);
        elona::lua::lua->get_state()->set("chara2", handle2);

        REQUIRE_NOTHROW(elona::lua::lua->get_state()->safe_script(
            R"(assert(chara == chara))"));
        REQUIRE_NOTHROW(elona::lua::lua->get_state()->safe_script(
            R"(assert(chara ~= chara2))"));

        chara_delete(chara.index);

        REQUIRE_NOTHROW(elona::lua::lua->get_state()->safe_script(
            R"(assert(chara ~= nil))"));
        REQUIRE_NOTHROW(elona::lua::lua->get_state()->safe_script(
            R"(assert(chara ~= chara2))"));

        REQUIRE(chara_create(-1, PUTIT_PROTO_ID, 4, 8));
        Character& chara3 = elona::cdata[elona::rc];
        auto handle3 = handle_mgr.get_handle(chara3);
        elona::lua::lua->get_state()->set("chara3", handle3);

        REQUIRE_NOTHROW(elona::lua::lua->get_state()->safe_script(
            R"(assert(chara ~= chara3))"));
    }
}

TEST_CASE(
    "Test validity of handles for items that are picked up",
    "[Lua: Handles]")
{
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();

    REQUIRE(itemcreate(-1, PUTITORO_PROTO_ID, 4, 8, 1));
    elona::cc = 0;
    elona::in = inv[elona::ci].number();

    REQUIRE(handle_mgr.get_handle(inv[elona::ci]) != sol::lua_nil);
    REQUIRE(pick_up_item() == 1);
    REQUIRE(handle_mgr.get_handle(inv[elona::ci]) == sol::lua_nil);
    REQUIRE(handle_mgr.get_handle(inv[elona::ti]) != sol::lua_nil);
}

TEST_CASE("Test relocation of character handle", "[Lua: Handles]")
{
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();

    REQUIRE(chara_create(-1, PUTIT_PROTO_ID, 4, 8));
    Character& chara = elona::cdata[elona::rc];
    auto handle = handle_mgr.get_handle(chara);

    int first_index = elona::rc;
    std::string uuid = handle["__uuid"];
    REQUIRE(handle["__index"].get<int>() == first_index);

    new_ally_joins();

    REQUIRE(handle_mgr.handle_is_valid(handle) == true);
    REQUIRE(elona::rc != first_index);
    REQUIRE(handle["__index"].get<int>() == elona::rc);
    REQUIRE(handle["__uuid"].get<std::string>() == uuid);
    REQUIRE(handle["__index"].get<int>() == handle["index"].get<int>());
}

TEST_CASE(
    "Test relocation of character handle caused by in-place change",
    "[Lua: Handles]")
{
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();
    REQUIRE(chara_create(-1, PUTIT_PROTO_ID, 4, 8));
    Character& chara = elona::cdata[elona::rc];
    auto handle = handle_mgr.get_handle(chara);

    int first_index = elona::rc;
    std::string uuid = handle["__uuid"];
    REQUIRE(handle["__index"].get<int>() == first_index);

    int tc = elona::rc;
    flt(20, Quality::good);
    REQUIRE(chara_create(56, 0, -3, 0));
    chara_relocate(cdata.tmp(), tc, CharaRelocationMode::change);

    REQUIRE(handle_mgr.handle_is_valid(handle) == true);
    REQUIRE(handle["__index"].get<int>() == elona::rc);
    REQUIRE(handle["__uuid"].get<std::string>() == uuid);
}

TEST_CASE("Test copying of character handles", "[Lua: Handles]")
{
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();

    REQUIRE(chara_create(-1, PUTIT_PROTO_ID, 4, 8));
    Character& chara = elona::cdata[elona::rc];
    auto handle = handle_mgr.get_handle(chara);

    int tc = chara_copy(chara);
    Character& copy = elona::cdata[tc];
    sol::table handle_copy = handle_mgr.get_handle(copy);

    REQUIRE(handle_mgr.handle_is_valid(handle) == true);
    REQUIRE(handle_mgr.handle_is_valid(handle_copy) == true);

    // Copying will create a handle with a unique UUID if no item
    // existed before at the new index.
    REQUIRE(
        handle["__uuid"].get<std::string>()
        != handle_copy["__uuid"].get<std::string>());

    // Assert that copying to an existing character will not try to
    // overwrite the existing handle.
    REQUIRE_NOTHROW(elona::Character::copy(chara, copy));
}

TEST_CASE("Test deletion of character causing handle removal", "[Lua: Handles]")
{
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();

    REQUIRE(chara_create(-1, PUTIT_PROTO_ID, 4, 8));
    Character& chara = elona::cdata[elona::rc];
    auto handle = handle_mgr.get_handle(chara);

    chara_delete(chara.index);

    REQUIRE(handle_mgr.handle_is_valid(handle) == false);
}

TEST_CASE(
    "Test state change of character causing handle removal",
    "[Lua: Handles]")
{
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();

    REQUIRE(chara_create(-1, PUTIT_PROTO_ID, 4, 8));
    Character& chara = elona::cdata[elona::rc];
    auto handle = handle_mgr.get_handle(chara);

    REQUIRE(handle_mgr.handle_is_valid(handle) == true);

    // State is set to empty.
    chara.set_state(Character::State::empty);
    REQUIRE(handle_mgr.handle_is_valid(handle) == false);

    // State becomes non-empty again. Character counts as recreated.
    chara.set_state(Character::State::alive);
    REQUIRE(handle_mgr.handle_is_valid(handle) == false);

    // The handle has been replaced, so retrieve it again.
    handle = handle_mgr.get_handle(chara);
    REQUIRE(handle_mgr.handle_is_valid(handle) == true);
}

TEST_CASE(
    "Test setting of item amount causing handle deletion",
    "[Lua: Handles]")
{
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();
    int amount = 2;

    REQUIRE(itemcreate(-1, PUTITORO_PROTO_ID, 4, 8, amount));
    Item& i = elona::inv[elona::ci];
    auto handle = handle_mgr.get_handle(i);

    REQUIRE(handle_mgr.handle_is_valid(handle) == true);

    // Amount becomes 1.
    i.set_number(1);
    REQUIRE(handle_mgr.handle_is_valid(handle) == true);

    // Amount becomes 0.
    i.set_number(-5);
    REQUIRE(handle_mgr.handle_is_valid(handle) == false);

    // Amount becomes 1 again. Item counts as recreated.
    i.set_number(1);
    REQUIRE(handle_mgr.handle_is_valid(handle) == false);

    // The handle has been replaced, so retrieve it again.
    handle = handle_mgr.get_handle(i);
    REQUIRE(handle_mgr.handle_is_valid(handle) == true);
}

TEST_CASE(
    "Test modifying of item amount causing handle deletion",
    "[Lua: Handles]")
{
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();
    int amount = 2;

    REQUIRE(itemcreate(-1, PUTITORO_PROTO_ID, 4, 8, amount));
    Item& i = elona::inv[elona::ci];
    auto handle = handle_mgr.get_handle(i);

    REQUIRE(handle_mgr.handle_is_valid(handle) == true);

    // Amount becomes 1.
    i.modify_number(-1);
    REQUIRE(handle_mgr.handle_is_valid(handle) == true);

    // Amount becomes 0.
    i.modify_number(-5);
    REQUIRE(handle_mgr.handle_is_valid(handle) == false);

    // Amount becomes 1 again. Item counts as recreated.
    i.modify_number(1);
    REQUIRE(handle_mgr.handle_is_valid(handle) == false);

    // The handle has been replaced, so retrieve it again.
    handle = handle_mgr.get_handle(i);
    REQUIRE(handle_mgr.handle_is_valid(handle) == true);
}

TEST_CASE("Test separation of item handles", "[Lua: Handles]")
{
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();
    int amount = 3;

    REQUIRE(itemcreate(-1, PUTITORO_PROTO_ID, 4, 8, amount));
    Item& i = elona::inv[elona::ci];
    sol::table handle = handle_mgr.get_handle(i);

    elona::item_separate(elona::ci);
    Item& item_sep = elona::inv[elona::ci];
    sol::table handle_sep = handle_mgr.get_handle(item_sep);

    REQUIRE(handle_mgr.handle_is_valid(handle) == true);
    REQUIRE(handle_mgr.handle_is_valid(handle_sep) == true);

    elona::item_separate(elona::ci);
    REQUIRE(handle_mgr.handle_is_valid(handle) == true);
    REQUIRE(handle_mgr.handle_is_valid(handle_sep) == true);
}

TEST_CASE("Test copying of item handles", "[Lua: Handles]")
{
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();
    int amount = 1;

    REQUIRE(itemcreate(-1, PUTITORO_PROTO_ID, 4, 8, amount));
    Item& i = elona::inv[elona::ci];
    sol::table handle = handle_mgr.get_handle(i);

    int ti = elona::inv_getfreeid(-1);
    REQUIRE(handle_mgr.get_handle(elona::inv[ti]) == sol::lua_nil);

    elona::item_copy(elona::ci, ti);
    Item& copy = elona::inv[ti];
    sol::table handle_copy = handle_mgr.get_handle(copy);

    REQUIRE(handle_mgr.handle_is_valid(handle) == true);
    REQUIRE(handle_mgr.handle_is_valid(handle_copy) == true);

    // Copying will create a handle with a unique UUID if no item
    // existed before at the new index.
    REQUIRE(
        handle["__uuid"].get<std::string>()
        != handle_copy["__uuid"].get<std::string>());

    // Assert that copying to an existing item will not try to
    // overwrite the existing handle.
    REQUIRE_NOTHROW(elona::item_copy(elona::ci, ti));
}

TEST_CASE("Test swapping of item handles", "[Lua: Handles]")
{
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();

    REQUIRE(itemcreate(-1, PUTITORO_PROTO_ID, 4, 8, 1));
    Item& item_a = elona::inv[elona::ci];
    sol::table handle_a = handle_mgr.get_handle(item_a);

    REQUIRE(itemcreate(-1, PUTITORO_PROTO_ID, 4, 9, 1));
    Item& item_b = elona::inv[elona::ci];
    sol::table handle_b = handle_mgr.get_handle(item_b);

    std::string uuid_a = handle_a["__uuid"];
    std::string uuid_b = handle_b["__uuid"];

    elona::item_exchange(item_a.index, item_b.index);

    // Handle indices should reflect the swapped item indices.
    REQUIRE(handle_a["__index"].get<int>() == item_b.index);
    REQUIRE(handle_b["__index"].get<int>() == item_a.index);

    // UUIDs should still be the same as before.
    REQUIRE(handle_a["__uuid"].get<std::string>() == uuid_a);
    REQUIRE(handle_b["__uuid"].get<std::string>() == uuid_b);
}

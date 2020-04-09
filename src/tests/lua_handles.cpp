#include "../elona/character.hpp"
#include "../elona/command.hpp"
#include "../elona/item.hpp"
#include "../elona/itemgen.hpp"
#include "../elona/lua_env/handle_manager.hpp"
#include "../elona/lua_env/lua_env.hpp"
#include "../elona/lua_env/mod_manager.hpp"
#include "../elona/testing.hpp"
#include "../elona/variables.hpp"
#include "../thirdparty/catch2/catch.hpp"
#include "../thirdparty/sol2/sol.hpp"
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
        REQUIRE(chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 8));
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
        const auto item_opt =
            itemcreate_extra_inv(itemid2int(PUTITORO_PROTO_ID), 4, 8, 3);
        REQUIRE_SOME(item_opt);
        int idx = item_opt->index;
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
        const auto item_opt =
            itemcreate_extra_inv(itemid2int(PUTITORO_PROTO_ID), 0, 0, 1);
        REQUIRE_SOME(item_opt);
        Item& item = *item_opt;
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
        REQUIRE(chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 8));
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
        REQUIRE(chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 8));
        Character& chara = elona::cdata[elona::rc];
        auto handle = handle_mgr.get_handle(chara);
        elona::lua::lua->get_state()->set("chara", handle);

        testing::invalidate_chara(chara);

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
        const auto item_opt =
            itemcreate_extra_inv(itemid2int(PUTITORO_PROTO_ID), 4, 8, 3);
        REQUIRE_SOME(item_opt);
        Item& item = *item_opt;
        auto handle = handle_mgr.get_handle(item);
        elona::lua::lua->get_state()->set("item", handle);

        testing::invalidate_item(item);

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
        REQUIRE(chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 8));
        Character& chara = elona::cdata[elona::rc];
        auto handle = handle_mgr.get_handle(chara);

        REQUIRE_NOTHROW(mod_mgr.load_testing_mod_from_script("test", ""));

        mod_mgr.get_mod("test")->env.raw_set("chara", handle);
        REQUIRE_NOTHROW(mod_mgr.run_in_mod(
            "test", "mod.store.global.charas = {[0]=chara}"));

        testing::invalidate_chara(chara);

        REQUIRE_THROWS(mod_mgr.run_in_mod(
            "test", "print(mod.store.global.charas[0].index)"));
    }
    SECTION("Items")
    {
        const auto item_opt =
            itemcreate_extra_inv(itemid2int(PUTITORO_PROTO_ID), 4, 8, 3);
        REQUIRE_SOME(item_opt);
        Item& item = *item_opt;
        auto handle = handle_mgr.get_handle(item);

        REQUIRE_NOTHROW(mod_mgr.load_testing_mod_from_script("test2", ""));

        mod_mgr.get_mod("test2")->env.raw_set("item", handle);
        REQUIRE_NOTHROW(
            mod_mgr.run_in_mod("test2", "mod.store.global.items = {[0]=item}"));

        testing::invalidate_item(item);

        REQUIRE_THROWS(mod_mgr.run_in_mod(
            "test2", "print(mod.store.global.items[0].index)"));
    }
}

TEST_CASE("Test invalid references to handles from Lua side", "[Lua: Handles]")
{
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();
    (void)handle_mgr;
    auto& mod_mgr = elona::lua::lua->get_mod_manager();

    SECTION("Characters")
    {
        REQUIRE_NOTHROW(
            mod_mgr.load_testing_mod_from_script("test_invalid_chara", R"(
local Chara = ELONA.require("core.Chara")
local chara = Chara.create(0, 0, "core.putit")
mod.store.global.idx = chara.index
mod.store.global.charas = {[0]=chara}
)"));
        int idx = mod_mgr.get_mod("test_invalid_chara")
                      ->env.get<int>(std::tie("mod", "store", "global", "idx"));

        testing::invalidate_chara(elona::cdata[idx]);

        REQUIRE_THROWS(mod_mgr.run_in_mod(
            "test_invalid_chara", "print(mod.store.global.charas[0].index)"));
    }
    SECTION("Items")
    {
        REQUIRE_NOTHROW(
            mod_mgr.load_testing_mod_from_script("test_invalid_item", R"(
local Item = ELONA.require("core.Item")
local item = Item.create(0, 0, "core.putitoro", 3)
mod.store.global.idx = item.index
mod.store.global.items = {[0]=items}
)"));
        int idx = mod_mgr.get_mod("test_invalid_item")
                      ->env.get<int>(std::tie("mod", "store", "global", "idx"));

        testing::invalidate_item(elona::inv[idx]);

        REQUIRE_THROWS(mod_mgr.run_in_mod(
            "test_invalid_item", "print(mod.store.global.items[0].index)"));
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
        REQUIRE(chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 8));
        Character& chara = elona::cdata[elona::rc];
        auto handle = handle_mgr.get_handle(chara);

        REQUIRE_NOTHROW(mod_mgr.load_testing_mod_from_script(
            "test_chara_arg", "mod.store.global.charas = {}"));
        mod_mgr.get_mod("test_chara_arg")->env.raw_set("chara", handle);

        REQUIRE_NOTHROW(mod_mgr.run_in_mod("test_chara_arg", R"(
mod.store.global.charas[0] = chara
local Chara = ELONA.require("core.Chara")
print(Chara.is_ally(mod.store.global.charas[0]))
)"));

        testing::invalidate_chara(chara);

        REQUIRE_THROWS(mod_mgr.run_in_mod("test_chara_arg", R"(
local Chara = ELONA.require("core.Chara")
print(Chara.is_ally(mod.store.global.charas[0]))
)"));
    }
    SECTION("Items")
    {
        const auto item_opt =
            itemcreate_extra_inv(itemid2int(PUTITORO_PROTO_ID), 4, 8, 3);
        REQUIRE_SOME(item_opt);
        Item& item = *item_opt;
        auto handle = handle_mgr.get_handle(item);

        REQUIRE_NOTHROW(mod_mgr.load_testing_mod_from_script(
            "test_item_arg", "mod.store.global.items = {}"));
        mod_mgr.get_mod("test_item_arg")->env.raw_set("item", handle);

        REQUIRE_NOTHROW(mod_mgr.run_in_mod("test_item_arg", R"(
mod.store.global.items[0] = item
local Item = ELONA.require("core.Item")
Item.has_enchantment(mod.store.global.items[0], 20)
)"));

        testing::invalidate_item(item);

        REQUIRE_THROWS(mod_mgr.run_in_mod("test_item_arg", R"(
local Item = ELONA.require("core.Item")
Item.has_enchantment(mod.store.global.items[0], 20)
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
    (void)handle_mgr;
    auto& mod_mgr = elona::lua::lua->get_mod_manager();

    {
        REQUIRE(chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 8));
        Character& chara = elona::cdata[elona::rc];
        auto handle = handle_mgr.get_handle(chara);
        elona::lua::lua->get_state()->set("chara", handle);

        REQUIRE(chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 9));
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

        REQUIRE(chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 8));
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

    const auto item =
        itemcreate_extra_inv(itemid2int(PUTITORO_PROTO_ID), 4, 8, 1);
    REQUIRE_SOME(item);
    elona::cc = 0;
    elona::in = item->number();

    REQUIRE(handle_mgr.get_handle(*item) != sol::lua_nil);
    const auto pick_up_item_result = pick_up_item(*item);
    REQUIRE(pick_up_item_result.type == 1);
    REQUIRE_SOME(pick_up_item_result.picked_up_item);
    REQUIRE(
        handle_mgr.get_handle(*pick_up_item_result.picked_up_item) !=
        sol::lua_nil);

    // Removal of handle is deferred.
    REQUIRE(handle_mgr.get_handle(*item) != sol::lua_nil);
}

TEST_CASE("Test relocation of character handle", "[Lua: Handles]")
{
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();

    REQUIRE(chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 8));
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
    REQUIRE(chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 8));
    Character& chara = elona::cdata[elona::rc];
    auto handle = handle_mgr.get_handle(chara);

    int first_index = elona::rc;
    std::string uuid = handle["__uuid"];
    REQUIRE(handle["__index"].get<int>() == first_index);

    int tc = elona::rc;
    flt(20, Quality::good);
    REQUIRE(chara_create(56, 0, -3, 0));
    auto temporary_handle = handle_mgr.get_handle(cdata.tmp());
    chara_relocate(cdata.tmp(), tc, CharaRelocationMode::change);

    REQUIRE(handle_mgr.handle_is_valid(handle) == true);
    REQUIRE(handle["__index"].get<int>() == elona::rc);
    REQUIRE(handle["__uuid"].get<std::string>() == uuid);
    REQUIRE(handle_mgr.handle_is_valid(temporary_handle) == false);
}

TEST_CASE("Test copying of character handles", "[Lua: Handles]")
{
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();

    REQUIRE(chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 8));
    Character& chara = elona::cdata[elona::rc];
    auto handle = handle_mgr.get_handle(chara);

    int tc = elona::chara_copy(chara);
    Character& copy = elona::cdata[tc];
    sol::table handle_copy = handle_mgr.get_handle(copy);

    REQUIRE(handle_mgr.handle_is_valid(handle) == true);
    REQUIRE(handle_mgr.handle_is_valid(handle_copy) == true);

    // Copying will create a handle with a unique UUID if no item
    // existed before at the new index.
    REQUIRE(
        handle["__uuid"].get<std::string>() !=
        handle_copy["__uuid"].get<std::string>());

    // Assert that copying to an existing character will not try to
    // overwrite the existing handle (it would cause an exception).
    REQUIRE_NOTHROW(elona::Character::copy(chara, copy));
}

TEST_CASE("Test copying of character handles after removal", "[Lua: Handles]")
{
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();

    REQUIRE(chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 8));
    Character& a = elona::cdata[elona::rc];

    REQUIRE(chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 9));
    Character& b = elona::cdata[elona::rc];

    // Mark the handle in b's slot as invalid.
    b.set_state(Character::State::empty);

    // chara_copy should clean up the handle in b's slot.
    REQUIRE_NOTHROW(elona::chara_copy(a));
}

TEST_CASE(
    "Test deletion of character causing handle to remain",
    "[Lua: Handles]")
{
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();

    REQUIRE(chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 8));
    Character& chara = elona::cdata[elona::rc];
    auto handle = handle_mgr.get_handle(chara);

    chara_delete(chara.index);

    // Invalidation is deferred until the handle is recreated in the same slot.
    REQUIRE(handle_mgr.handle_is_valid(handle) == true);
}

TEST_CASE(
    "Test state change of character causing handle recreation",
    "[Lua: Handles]")
{
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();

    REQUIRE(chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 8));
    Character& chara = elona::cdata[elona::rc];
    auto handle = handle_mgr.get_handle(chara);
    auto old_uuid = handle["__uuid"].get<std::string>();

    REQUIRE(handle_mgr.handle_is_valid(handle) == true);

    // State is set to empty.
    chara.set_state(Character::State::empty);
    REQUIRE(handle_mgr.handle_is_valid(handle) == true);

    // State becomes non-empty again. Character counts as recreated.
    chara.set_state(Character::State::alive);
    REQUIRE(handle_mgr.handle_is_valid(handle) == false);

    // The handle has been replaced, so retrieve it again.
    handle = handle_mgr.get_handle(chara);
    REQUIRE(handle_mgr.handle_is_valid(handle) == true);

    REQUIRE(handle["__uuid"].get<std::string>() != old_uuid);
}

TEST_CASE(
    "Test setting of item amount causing handle recreation",
    "[Lua: Handles]")
{
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();
    int amount = 2;

    const auto item_opt =
        itemcreate_extra_inv(itemid2int(PUTITORO_PROTO_ID), 4, 8, amount);
    REQUIRE_SOME(item_opt);
    Item& i = *item_opt;
    auto handle = handle_mgr.get_handle(i);
    auto old_uuid = handle["__uuid"].get<std::string>();

    REQUIRE(handle_mgr.handle_is_valid(handle) == true);

    // Amount becomes 1.
    i.set_number(1);
    REQUIRE(handle_mgr.handle_is_valid(handle) == true);

    // Amount becomes 0.
    i.set_number(-5);
    REQUIRE(handle_mgr.handle_is_valid(handle) == true);

    // Amount becomes 1 again. Item counts as recreated.
    i.set_number(1);
    REQUIRE(handle_mgr.handle_is_valid(handle) == false);

    // The handle has been replaced, so retrieve it again.
    handle = handle_mgr.get_handle(i);
    REQUIRE(handle_mgr.handle_is_valid(handle) == true);

    REQUIRE(handle["__uuid"].get<std::string>() != old_uuid);
}

TEST_CASE("Test separation of item handles", "[Lua: Handles]")
{
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();
    int amount = 3;

    const auto i_opt =
        itemcreate_extra_inv(itemid2int(PUTITORO_PROTO_ID), 4, 8, amount);
    REQUIRE_SOME(i_opt);
    Item& i = *i_opt;
    sol::table handle = handle_mgr.get_handle(i);

    elona::item_separate(i.index);
    Item& item_sep = i;
    sol::table handle_sep = handle_mgr.get_handle(item_sep);

    REQUIRE(handle_mgr.handle_is_valid(handle) == true);
    REQUIRE(handle_mgr.handle_is_valid(handle_sep) == true);

    elona::item_separate(i.index);
    REQUIRE(handle_mgr.handle_is_valid(handle) == true);
    REQUIRE(handle_mgr.handle_is_valid(handle_sep) == true);
}

TEST_CASE("Test copying of item handles", "[Lua: Handles]")
{
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();
    int amount = 1;

    const auto i_opt =
        itemcreate_extra_inv(itemid2int(PUTITORO_PROTO_ID), 4, 8, amount);
    REQUIRE_SOME(i_opt);
    Item& i = *i_opt;
    sol::table handle = handle_mgr.get_handle(i);

    int ti = elona::inv_getfreeid(-1);
    REQUIRE(handle_mgr.get_handle(elona::inv[ti]) == sol::lua_nil);

    elona::item_copy(i, slot);
    Item& copy = slot;
    sol::table handle_copy = handle_mgr.get_handle(copy);

    REQUIRE(handle_mgr.handle_is_valid(handle) == true);
    REQUIRE(handle_mgr.handle_is_valid(handle_copy) == true);

    // Copying will create a handle with a unique UUID if no item
    // existed before at the new index.
    REQUIRE(
        handle["__uuid"].get<std::string>() !=
        handle_copy["__uuid"].get<std::string>());

    // Assert that copying to an existing item will not try to
    // overwrite the existing handle.
    REQUIRE_NOTHROW(elona::item_copy(i, slot));
}

TEST_CASE("Test copying of item handles after removal", "[Lua: Handles]")
{
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();
    int amount = 1;

    const auto a_opt =
        itemcreate_extra_inv(itemid2int(PUTITORO_PROTO_ID), 4, 8, amount);
    REQUIRE_SOME(a_opt);
    Item& a = *a_opt;

    const auto b_opt =
        itemcreate_extra_inv(itemid2int(PUTITORO_PROTO_ID), 4, 9, amount);
    REQUIRE_SOME(b_opt);
    Item& b = *b_opt;

    // Mark the handle in b's slot as invalid.
    b.set_number(0);

    // item_copy should clean up the handle in b's slot.
    REQUIRE_NOTHROW(elona::item_copy(a, b));
}

TEST_CASE("Test swapping of item handles", "[Lua: Handles]")
{
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();

    const auto item_a_opt =
        itemcreate_extra_inv(itemid2int(PUTITORO_PROTO_ID), 4, 8, 1);
    REQUIRE_SOME(item_a_opt);
    Item& item_a = *item_a_opt;
    sol::table handle_a = handle_mgr.get_handle(item_a);

    const auto item_b_opt =
        itemcreate_extra_inv(itemid2int(PUTITORO_PROTO_ID), 4, 9, 1);
    REQUIRE_SOME(item_b_opt);
    Item& item_b = *item_b_opt;
    sol::table handle_b = handle_mgr.get_handle(item_b);

    std::string uuid_a = handle_a["__uuid"];
    std::string uuid_b = handle_b["__uuid"];

    elona::item_exchange(item_a.index, item_b.index);

    // Disabled temporarily.
    // TODO: rethink how should swapping behave.
    // // Handle indices should reflect the swapped item indices.
    // REQUIRE(handle_a["__index"].get<int>() == item_b.index);
    // REQUIRE(handle_b["__index"].get<int>() == item_a.index);

    // // UUIDs should still be the same as before.
    // REQUIRE(handle_a["__uuid"].get<std::string>() == uuid_a);
    // REQUIRE(handle_b["__uuid"].get<std::string>() == uuid_b);
}

TEST_CASE("Test validity check of lua reference userdata", "[Lua: Handles]")
{
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();
    auto& mod_mgr = elona::lua::lua->get_mod_manager();

    REQUIRE_NOTHROW(mod_mgr.load_testing_mod_from_script("test_lua_ref", R"(
local Chara = ELONA.require("core.Chara")
local chara = Chara.create(0, 0, "core.putit")
local skill = chara:get_skill("core.attribute_strength")
assert(skill.original_level > 0)

local old_index = chara.index
chara:damage_hp(chara.max_hp + 1)
local chara = Chara.create(0, 0, "core.putit")
assert(chara.index == old_index)

assert(skill.original_level == 0)
)"));
}

TEST_CASE(
    "Test new handles are created when a map is generated",
    "[Lua: Handles]")
{
    start_in_debug_map();

    // fields
    run_in_temporary_map(2, 0, []() {
        REQUIRE(
            elona::lua::lua->get_handle_manager().get_handle(
                57, Character::lua_type()) != sol::lua_nil);
    });
}

TEST_CASE(
    "Test new handles are created when a map is loaded from a custom file",
    "[Lua: Handles]")
{
    start_in_debug_map();

    // vernis
    run_in_temporary_map(5, 1, []() {
        REQUIRE(
            elona::lua::lua->get_handle_manager().get_handle(
                57, Character::lua_type()) != sol::lua_nil);
    });
}

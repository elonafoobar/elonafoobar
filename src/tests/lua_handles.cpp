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
        const auto chara_opt =
            chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 8);
        REQUIRE_SOME(chara_opt);
        int idx = chara_opt->index;
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
        const auto item_opt = itemcreate_map_inv(PUTITORO_PROTO_ID, 4, 8, 3);
        REQUIRE_SOME(item_opt);
        const auto item = item_opt.unwrap();
        elona::lua::lua->get_state()->set("item", item);
        REQUIRE_NOTHROW(elona::lua::lua->get_state()->safe_script(
            R"(assert(item.pos.x == 4))"));
        REQUIRE_NOTHROW(elona::lua::lua->get_state()->safe_script(
            R"(assert(item.pos.y == 8))"));
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
        const auto item_opt = itemcreate_map_inv(PUTITORO_PROTO_ID, 0, 0, 1);
        REQUIRE_SOME(item_opt);
        const auto item = item_opt.unwrap();
        elona::lua::lua->get_state()->set("item", item);

        REQUIRE_NOTHROW(
            elona::lua::lua->get_state()->safe_script(R"(item.number = 3)"));
#if 0 // TODO
        REQUIRE_NOTHROW(
            elona::lua::lua->get_state()->safe_script(R"(item.pos.x = 4)"));
        REQUIRE_NOTHROW(
            elona::lua::lua->get_state()->safe_script(R"(item.pos.y = 8)"));
#endif
        REQUIRE_NOTHROW(elona::lua::lua->get_state()->safe_script(
            R"(item.pos = LuaPosition.new(4, 8))"));

        REQUIRE(item->number() == 3);
        REQUIRE(item->pos().x == 4);
        REQUIRE(item->pos().y == 8);
    }
}

TEST_CASE("Test that handle methods can be called", "[Lua: Handles]")
{
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();

    {
        const auto chara_opt =
            chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 8);
        REQUIRE_SOME(chara_opt);
        Character& chara = *chara_opt;
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
        const auto chara_opt =
            chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 8);
        REQUIRE_SOME(chara_opt);
        Character& chara = *chara_opt;
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
#if 0
        const auto item_opt =
            itemcreate_map_inv(PUTITORO_PROTO_ID, 4, 8, 3);
        REQUIRE_SOME(item_opt);
        const auto item = item_opt.unwrap();
        elona::lua::lua->get_state()->set("item", item);

        testing::invalidate_item(item);

        {
            auto result = elona::lua::lua->get_state()->safe_script(
                R"(print(item.number()))", &sol::script_pass_on_error);
            REQUIRE(!result.valid());
        }
        {
            auto result = elona::lua::lua->get_state()->safe_script(
                R"(item.pos.x = 2)", &sol::script_pass_on_error);
            REQUIRE(!result.valid());
        }
#endif
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
        const auto chara_opt =
            chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 8);
        REQUIRE_SOME(chara_opt);
        Character& chara = *chara_opt;
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
#if 0
        const auto item_opt =
            itemcreate_map_inv(PUTITORO_PROTO_ID, 4, 8, 3);
        REQUIRE_SOME(item_opt);
        const auto item = item_opt.unwrap();

        REQUIRE_NOTHROW(mod_mgr.load_testing_mod_from_script("test2", ""));

        mod_mgr.get_mod("test2")->env.raw_set("item", item);
        REQUIRE_NOTHROW(
            mod_mgr.run_in_mod("test2", "mod.store.global.items = {[0]=item}"));

        testing::invalidate_item(item);

        REQUIRE_THROWS(
            mod_mgr.run_in_mod("test2", "print(mod.store.global.items[0].id)"));
#endif
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
#if 0
        REQUIRE_NOTHROW(
            mod_mgr.load_testing_mod_from_script("test_invalid_item", R"(
local Chara = ELONA.require("core.Chara")
local Item = ELONA.require("core.Item")
local item = Item.create(Chara.player().position, "core.putitoro", 3)
mod.store.global.items = {[0]=item}
)"));

        const auto item = item_find(
            itemid2int("core.putitoro"), 3, ItemFindLocation::ground);
        REQUIRE_SOME(item);
        testing::invalidate_item(item.unwrap());

        REQUIRE_THROWS(mod_mgr.run_in_mod(
            "test_invalid_item", "print(mod.store.global.items[0].id)"));
#endif
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
        const auto chara_opt =
            chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 8);
        REQUIRE_SOME(chara_opt);
        Character& chara = *chara_opt;
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
#if 0
        const auto item_opt =
            itemcreate_map_inv(PUTITORO_PROTO_ID, 4, 8, 3);
        REQUIRE_SOME(item_opt);
        const auto item = item_opt.unwrap();

        REQUIRE_NOTHROW(mod_mgr.load_testing_mod_from_script(
            "test_item_arg", "mod.store.global.items = {}"));
        mod_mgr.get_mod("test_item_arg")->env.raw_set("item", item);

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
#endif
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
        const auto chara_opt =
            chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 8);
        REQUIRE_SOME(chara_opt);
        Character& chara = *chara_opt;
        auto handle = handle_mgr.get_handle(chara);
        elona::lua::lua->get_state()->set("chara", handle);

        const auto chara2_opt =
            chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 9);
        REQUIRE_SOME(chara2_opt);
        Character& chara2 = *chara2_opt;
        auto handle2 = handle_mgr.get_handle(chara2);
        elona::lua::lua->get_state()->set("chara2", handle2);

        REQUIRE_NOTHROW(elona::lua::lua->get_state()->safe_script(
            R"(assert(chara == chara))"));
        REQUIRE_NOTHROW(elona::lua::lua->get_state()->safe_script(
            R"(assert(chara ~= chara2))"));

        chara_delete(chara);

        REQUIRE_NOTHROW(elona::lua::lua->get_state()->safe_script(
            R"(assert(chara ~= nil))"));
        REQUIRE_NOTHROW(elona::lua::lua->get_state()->safe_script(
            R"(assert(chara ~= chara2))"));

        const auto chara3_opt =
            chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 8);
        REQUIRE_SOME(chara3_opt);
        Character& chara3 = *chara3_opt;
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
#if 0
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();

    const auto item =
        itemcreate_map_inv(PUTITORO_PROTO_ID, 4, 8, 1);
    REQUIRE_SOME(item);
    elona::in = item->number();

    REQUIRE(
        handle_mgr.get_handle(*item.unwrap().get_raw_ptr()) != sol::lua_nil);
    const auto pick_up_item_result = pick_up_item(0, item.unwrap(), none);
    REQUIRE(pick_up_item_result.type == 1);
    REQUIRE_SOME(pick_up_item_result.picked_up_item);
    REQUIRE(
        handle_mgr.get_handle(
            *pick_up_item_result.picked_up_item.unwrap().get_raw_ptr()) !=
        sol::lua_nil);

    // Removal of handle is deferred.
    REQUIRE(
        handle_mgr.get_handle(*item.unwrap().get_raw_ptr()) != sol::lua_nil);
#endif
}

TEST_CASE("Test relocation of character handle", "[Lua: Handles]")
{
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();

    const auto chara_opt = chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 8);
    REQUIRE_SOME(chara_opt);
    Character& chara = *chara_opt;
    auto handle = handle_mgr.get_handle(chara);

    int first_index = chara_opt->index;
    std::string uuid = handle["__uuid"];

    const auto ally = new_ally_joins(chara);
    REQUIRE_SOME(ally);

    REQUIRE(handle_mgr.handle_is_valid(handle) == true);
    REQUIRE(ally->index != first_index);
    REQUIRE(handle["__uuid"].get<std::string>() == uuid);
}

TEST_CASE(
    "Test relocation of character handle caused by in-place change",
    "[Lua: Handles]")
{
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();
    const auto chara_opt = chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 8);
    REQUIRE_SOME(chara_opt);
    Character& chara = *chara_opt;
    auto handle = handle_mgr.get_handle(chara);

    int first_index = chara_opt->index;
    std::string uuid = handle["__uuid"];

    int tc = chara_opt->index;
    flt(20, Quality::good);
    const auto chara2_opt = chara_create(56, 0, -3, 0);
    REQUIRE_SOME(chara2_opt);
    auto temporary_handle = handle_mgr.get_handle(cdata.tmp());
    chara_relocate(cdata.tmp(), cdata[tc], CharaRelocationMode::change);

    REQUIRE(handle_mgr.handle_is_valid(handle) == true);
    REQUIRE(handle["__uuid"].get<std::string>() == uuid);
    REQUIRE(handle_mgr.handle_is_valid(temporary_handle) == false);
}

TEST_CASE("Test copying of character handles", "[Lua: Handles]")
{
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();

    const auto chara_opt = chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 8);
    REQUIRE_SOME(chara_opt);
    Character& chara = *chara_opt;
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

    const auto a_opt = chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 8);
    REQUIRE_SOME(a_opt);
    Character& a = *a_opt;

    const auto b_opt = chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 9);
    REQUIRE_SOME(b_opt);
    Character& b = *b_opt;

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

    const auto chara_opt = chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 8);
    REQUIRE_SOME(chara_opt);
    Character& chara = *chara_opt;
    auto handle = handle_mgr.get_handle(chara);

    chara_delete(chara);

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

    const auto chara_opt = chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 8);
    REQUIRE_SOME(chara_opt);
    Character& chara = *chara_opt;
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
#if 0
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();
    int amount = 2;

    const auto item_opt =
        itemcreate_map_inv(PUTITORO_PROTO_ID, 4, 8, amount);
    REQUIRE_SOME(item_opt);
    const auto i = item_opt.unwrap();
    auto handle = handle_mgr.get_handle(*i.get_raw_ptr());
    auto old_uuid = handle["__uuid"].get<std::string>();

    REQUIRE(handle_mgr.handle_is_valid(handle) == true);

    // Amount becomes 1.
    i->set_number(1);
    REQUIRE(handle_mgr.handle_is_valid(handle) == true);

    // Amount becomes 0.
    i->set_number(-5);
    REQUIRE(handle_mgr.handle_is_valid(handle) == true);

    // Amount becomes 1 again. Item counts as recreated.
    i->set_number(1);
    REQUIRE(handle_mgr.handle_is_valid(handle) == false);

    // The handle has been replaced, so retrieve it again.
    handle = handle_mgr.get_handle(*i.get_raw_ptr());
    REQUIRE(handle_mgr.handle_is_valid(handle) == true);

    REQUIRE(handle["__uuid"].get<std::string>() != old_uuid);
#endif
}

TEST_CASE("Test separation of item handles", "[Lua: Handles]")
{
#if 0
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();
    int amount = 3;

    const auto i_opt =
        itemcreate_map_inv(PUTITORO_PROTO_ID, 4, 8, amount);
    REQUIRE_SOME(i_opt);
    const auto i = i_opt.unwrap();
    sol::table handle = handle_mgr.get_handle(*i.get_raw_ptr());

    elona::item_separate(i);
    const auto item_sep = i;
    sol::table handle_sep = handle_mgr.get_handle(*item_sep.get_raw_ptr());

    REQUIRE(handle_mgr.handle_is_valid(handle) == true);
    REQUIRE(handle_mgr.handle_is_valid(handle_sep) == true);

    elona::item_separate(i);
    REQUIRE(handle_mgr.handle_is_valid(handle) == true);
    REQUIRE(handle_mgr.handle_is_valid(handle_sep) == true);
#endif
}

TEST_CASE("Test copying of item handles", "[Lua: Handles]")
{
#if 0
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();
    int amount = 1;

    const auto i_opt =
        itemcreate_map_inv(PUTITORO_PROTO_ID, 4, 8, amount);
    REQUIRE_SOME(i_opt);
    const auto i = i_opt.unwrap();
    sol::table handle = handle_mgr.get_handle(*i.get_raw_ptr());

    const auto slot_opt = elona::inv_get_free_slot(-1);
    REQUIRE_SOME(slot_opt);
    const auto slot = *slot_opt;
    REQUIRE(handle_mgr.get_handle(*slot.get_raw_ptr()) == sol::lua_nil);

    elona::item_copy(i, slot);
    const auto copy = slot;
    sol::table handle_copy = handle_mgr.get_handle(*copy.get_raw_ptr());

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
#endif
}

TEST_CASE("Test copying of item handles after removal", "[Lua: Handles]")
{
#if 0
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();
    int amount = 1;

    const auto a_opt =
        itemcreate_map_inv(PUTITORO_PROTO_ID, 4, 8, amount);
    REQUIRE_SOME(a_opt);
    const auto a = a_opt.unwrap();

    const auto b_opt =
        itemcreate_map_inv(PUTITORO_PROTO_ID, 4, 9, amount);
    REQUIRE_SOME(b_opt);
    const auto b = b_opt.unwrap();

    // Mark the handle in b's slot as invalid.
    b->set_number(0);

    // item_copy should clean up the handle in b's slot.
    REQUIRE_NOTHROW(elona::item_copy(a, b));
#endif
}

TEST_CASE("Test swapping of item handles", "[Lua: Handles]")
{
#if 0
    reset_state();
    start_in_debug_map();
    auto& handle_mgr = elona::lua::lua->get_handle_manager();

    const auto item_a_opt =
        itemcreate_map_inv(PUTITORO_PROTO_ID, 4, 8, 1);
    REQUIRE_SOME(item_a_opt);
    const auto item_a = item_a_opt.unwrap();
    sol::table handle_a = handle_mgr.get_handle(*item_a.get_raw_ptr());

    const auto item_b_opt =
        itemcreate_map_inv(PUTITORO_PROTO_ID, 4, 9, 1);
    REQUIRE_SOME(item_b_opt);
    const auto item_b = item_b_opt.unwrap();
    sol::table handle_b = handle_mgr.get_handle(*item_b.get_raw_ptr());

    std::string uuid_a = handle_a["__uuid"];
    std::string uuid_b = handle_b["__uuid"];

    elona::item_exchange(item_a, item_b);

    // Disabled temporarily.
    // // UUIDs should still be the same as before.
    // REQUIRE(handle_a["__uuid"].get<std::string>() == uuid_a);
    // REQUIRE(handle_b["__uuid"].get<std::string>() == uuid_b);
#endif
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
assert(skill.base_level > 0)

local old_index = chara.index
chara:damage_hp(chara.max_hp + 1)
local chara = Chara.create(0, 0, "core.putit")
assert(chara.index == old_index)

assert(skill.base_level == 0)
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
                elona::cdata[57]) != sol::lua_nil);
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
                elona::cdata[57]) != sol::lua_nil);
    });
}

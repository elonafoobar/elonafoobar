#include "../elona/ability.hpp"
#include "../elona/character.hpp"
#include "../elona/enums.hpp"
#include "../elona/filesystem.hpp"
#include "../elona/gdata.hpp"
#include "../elona/init.hpp"
#include "../elona/item.hpp"
#include "../elona/itemgen.hpp"
#include "../elona/testing.hpp"
#include "../elona/variables.hpp"
#include "../thirdparty/catch2/catch.hpp"
#include "tests.hpp"

using namespace Catch;
using namespace elona::testing;

TEST_CASE("Test character saving and reloading", "[C++: Serialization]")
{
    start_in_debug_map();
    REQUIRE(chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 8));
    int index = elona::rc;
    cdata[index].is_floating() = true;

    save_and_reload();

    REQUIRE(elona::cdata[index].state() != Character::State::empty);
    REQUIRE(elona::cdata[index].position.x == 4);
    REQUIRE(elona::cdata[index].position.y == 8);
    REQUIRE(elona::cdata[index].id == PUTIT_PROTO_ID);
    REQUIRE(elona::cdata[index].is_floating() == true);
}

TEST_CASE("Test item saving and reloading", "[C++: Serialization]")
{
    start_in_debug_map();
    int x = 4;
    int y = 8;
    int number = 3;
    REQUIRE_SOME(
        itemcreate_extra_inv(itemid2int(PUTITORO_PROTO_ID), x, y, number));
    int index = elona::ci;
    elona::inv[index].is_aphrodisiac() = true;
    elona::inv[index].curse_state = CurseState::blessed;

    save_and_reload();

    REQUIRE(elona::inv[index].number() == 3);
    REQUIRE(elona::inv[index].id == PUTITORO_PROTO_ID);
    REQUIRE(elona::inv[index].position.x == 4);
    REQUIRE(elona::inv[index].position.y == 8);
    REQUIRE(elona::inv[index].curse_state == CurseState::blessed);
    REQUIRE(elona::inv[index].is_aphrodisiac());
    REQUIRE(itemname(inv[index]) == u8"3個のプチトロ(媚薬混入)");
}

TEST_CASE("Test party character index preservation", "[C++: Serialization]")
{
    start_in_debug_map();
    REQUIRE(chara_create(-1, charaid2int(PUTIT_PROTO_ID), 0, 0));
    REQUIRE(new_ally_joins());
    int index = elona::rc;

    save_and_reload();

    REQUIRE(elona::cdata[index].index == index);
}

TEST_CASE("Test other character index preservation", "[C++: Serialization]")
{
    start_in_debug_map();
    REQUIRE(chara_create(-1, charaid2int(PUTIT_PROTO_ID), 0, 0));
    int index = elona::rc;

    save_and_reload();

    REQUIRE(elona::cdata[index].index == index);
}

TEST_CASE("Test item index preservation", "[C++: Serialization]")
{
    start_in_debug_map();
    REQUIRE_SOME(itemcreate_extra_inv(itemid2int(PUTITORO_PROTO_ID), 0, 0, 0));
    int index = elona::ci;

    save_and_reload();

    REQUIRE(elona::inv[index].index == index);
}

TEST_CASE("Test character data compatibility", "[C++: Serialization]")
{
    int player_idx = 0;
    load_previous_savefile();
    REQUIRE(elona::cdata[player_idx].index == player_idx);
    REQUIRE(elona::cdatan(0, player_idx) == u8"foobar_test");
}

TEST_CASE("Test other character data compatibility", "[C++: Serialization]")
{
    int chara_idx = 57;
    load_previous_savefile();
    REQUIRE(elona::cdata[chara_idx].index == chara_idx);
    REQUIRE(elona::cdatan(0, chara_idx) == u8"風を聴く者『ラーネイレ』");
}

TEST_CASE("Test item data compatibility (in inventory)", "[C++: Serialization]")
{
    int item_idx = 0;
    load_previous_savefile();
    REQUIRE(elona::inv[item_idx].index == item_idx);
    REQUIRE(elona::itemname(inv[item_idx]) == u8"ブロンズの兜 [0,1]");
}

TEST_CASE("Test item data compatibility (on ground)", "[C++: Serialization]")
{
    int item_idx = 5080;
    load_previous_savefile();
    REQUIRE(elona::inv[item_idx].index == item_idx);
    REQUIRE(elona::itemname(inv[item_idx]) == u8"割れたつぼ");
}

TEST_CASE("Test ability data compatibility", "[C++: Serialization]")
{
    int ability_idx = 170; // Medium Armor
    int chara_idx = 57;
    load_previous_savefile();
    REQUIRE(elona::sdata.get(ability_idx, chara_idx).current_level == 28);
    REQUIRE(elona::sdata.get(ability_idx, chara_idx).original_level == 28);
    REQUIRE(elona::sdata.get(ability_idx, chara_idx).experience == 0);
    REQUIRE(elona::sdata.get(ability_idx, chara_idx).potential == 22);
}

TEST_CASE("Test foobar save data compatibility", "[C++: Serialization]")
{
    load_previous_savefile();
    REQUIRE(elona::foobar_data.is_autodig_enabled == 0);
}

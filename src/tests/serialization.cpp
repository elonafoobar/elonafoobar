#include "../thirdparty/catch2/catch.hpp"

#include "../ability.hpp"
#include "../character.hpp"
#include "../enums.hpp"
#include "../filesystem.hpp"
#include "../gdata.hpp"
#include "../init.hpp"
#include "../item.hpp"
#include "../itemgen.hpp"
#include "../testing.hpp"
#include "../variables.hpp"
#include "../log.hpp"
#include "tests.hpp"

using namespace Catch;
using namespace elona::testing;

TEST_CASE("Test character saving and reloading", "[C++: Serialization]")
{
    start_in_debug_map();
    REQUIRE(chara_create(-1, PUTIT_PROTO_ID, 4, 8));
    int index = elona::rc;
    cdata[index].is_floating() = true;

    save_and_reload();

    REQUIRE(elona::cdata(index).state != 0);
    REQUIRE(elona::cdata(index).position.x == 4);
    REQUIRE(elona::cdata(index).position.y == 8);
    REQUIRE(elona::cdata(index).id == 3);
    REQUIRE(elona::cdata(index).is_floating() == true);
}

TEST_CASE("Test item saving and reloading", "[C++: Serialization]")
{
    start_in_debug_map();
    int x = 4;
    int y = 8;
    int number = 3;
    REQUIRE(itemcreate(-1, PUTITORO_PROTO_ID, x, y, number));
    int index = elona::ci;
    ibitmod(6, index, 1);
    elona::inv(index).curse_state = curse_state_t::blessed;

    save_and_reload();

    REQUIRE(elona::inv(index).number == 3);
    REQUIRE(elona::inv(index).id == PUTITORO_PROTO_ID);
    REQUIRE(elona::inv(index).position.x == 4);
    REQUIRE(elona::inv(index).position.y == 8);
    REQUIRE(elona::inv(index).curse_state == curse_state_t::blessed);
    REQUIRE(elona::ibit(6, index) == 1);
    REQUIRE(itemname(index) == u8"3個のプチトロ(媚薬混入)");
}

TEST_CASE("Test party character index preservation", "[C++: Serialization]")
{
    start_in_debug_map();
    REQUIRE(chara_create(-1, PUTIT_PROTO_ID, 0, 0));
    REQUIRE(new_ally_joins());
    int index = elona::rc;

    save_and_reload();

    REQUIRE(elona::cdata(index).index == index);
}

TEST_CASE("Test other character index preservation", "[C++: Serialization]")
{
    start_in_debug_map();
    REQUIRE(chara_create(-1, PUTIT_PROTO_ID, 0, 0));
    int index = elona::rc;

    save_and_reload();

    REQUIRE(elona::cdata(index).index == index);
}

TEST_CASE("Test item index preservation", "[C++: Serialization]")
{
    start_in_debug_map();
    REQUIRE(itemcreate(-1, PUTITORO_PROTO_ID, 0, 0, 0));
    int index = elona::ci;

    save_and_reload();

    REQUIRE(elona::inv(index).index == index);
}

TEST_CASE("Test character data compatibility", "[C++: Serialization]")
{
    int player_idx = 0;
    ELONA_LOG("test begin");
    load_previous_savefile();
    ELONA_LOG("test end");
    REQUIRE(elona::cdata(player_idx).index == player_idx);
    REQUIRE(elona::cdatan(0, player_idx) == u8"foobar_test");
}

TEST_CASE("Test other character data compatibility", "[C++: Serialization]")
{
    int chara_idx = 57;
    ELONA_LOG("test begin2");
    load_previous_savefile();
    ELONA_LOG("test end2");
    REQUIRE(elona::cdata(chara_idx).index == chara_idx);
    REQUIRE(elona::cdatan(0, chara_idx) == u8"風を聴く者『ラーネイレ』");
}

TEST_CASE("Test item data compatibility (in inventory)", "[C++: Serialization]")
{
    int item_idx = 0;
    ELONA_LOG("test begin3");
    load_previous_savefile();
    ELONA_LOG("test end3");
    REQUIRE(elona::inv(item_idx).index == item_idx);
    REQUIRE(elona::itemname(item_idx) == u8"ブロンズの兜 [0,1]");
}

TEST_CASE("Test item data compatibility (on ground)", "[C++: Serialization]")
{
    int item_idx = 5080;
    ELONA_LOG("test begin4");
    load_previous_savefile();
    ELONA_LOG("test end4");
    REQUIRE(elona::inv(item_idx).index == item_idx);
    REQUIRE(elona::itemname(item_idx) == u8"割れたつぼ");
}

TEST_CASE("Test ability data compatibility", "[C++: Serialization]")
{
    int ability_idx = 170; // Medium Armor
    int chara_idx = 57;
    ELONA_LOG("test begin5");
    load_previous_savefile();
    ELONA_LOG("test end5");
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

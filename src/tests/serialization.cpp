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
    const auto chara = chara_create(-1, charaid2int(PUTIT_PROTO_ID), 4, 8);
    REQUIRE_SOME(chara);
    chara->is_floating() = true;

    save_and_reload();

    REQUIRE(chara->state() != Character::State::empty);
    REQUIRE(chara->position.x == 4);
    REQUIRE(chara->position.y == 8);
    REQUIRE(chara->id == PUTIT_PROTO_ID);
    REQUIRE(chara->is_floating() == true);
}

TEST_CASE("Test item saving and reloading", "[C++: Serialization]")
{
    start_in_debug_map();
    int index;
    {
        int x = 4;
        int y = 8;
        int number = 3;
        const auto item = itemcreate_map_inv(PUTITORO_PROTO_ID, x, y, number);
        REQUIRE_SOME(item);
        item->is_aphrodisiac() = true;
        item->curse_state = CurseState::blessed;
        item->identify_state = IdentifyState::partly;
        index = item->global_index();
    }

    save_and_reload();

    REQUIRE(elona::g_inv[index]->number() == 3);
    REQUIRE(
        the_item_db[elona::g_inv[index]->id]->legacy_id == PUTITORO_PROTO_ID);
    REQUIRE(elona::g_inv[index]->position().x == 4);
    REQUIRE(elona::g_inv[index]->position().y == 8);
    REQUIRE(elona::g_inv[index]->curse_state == CurseState::blessed);
    REQUIRE(elona::g_inv[index]->is_aphrodisiac());
    REQUIRE(itemname(g_inv[index]) == u8"3個のプチトロ(媚薬混入)");
}

TEST_CASE("Test party character index preservation", "[C++: Serialization]")
{
    start_in_debug_map();
    const auto chara = chara_create(-1, charaid2int(PUTIT_PROTO_ID), 0, 0);
    REQUIRE_SOME(chara);
    const auto ally = new_ally_joins(*chara);
    REQUIRE_SOME(ally);
    int index = ally->index;

    save_and_reload();

    REQUIRE(elona::cdata[index].index == index);
}

TEST_CASE("Test other character index preservation", "[C++: Serialization]")
{
    start_in_debug_map();
    const auto chara = chara_create(-1, charaid2int(PUTIT_PROTO_ID), 0, 0);
    REQUIRE_SOME(chara);
    int index = chara->index;

    save_and_reload();

    REQUIRE(elona::cdata[index].index == index);
}

TEST_CASE("Test character data compatibility", "[C++: Serialization]")
{
    int player_idx = 0;
    load_previous_savefile();
    REQUIRE(elona::cdata[player_idx].index == player_idx);
    REQUIRE(elona::cdata[player_idx].name == u8"foobar_test");
}

TEST_CASE("Test other character data compatibility", "[C++: Serialization]")
{
    int chara_idx = 57;
    load_previous_savefile();
    REQUIRE(elona::cdata[chara_idx].index == chara_idx);
    REQUIRE(elona::cdata[chara_idx].name == u8"風を聴く者『ラーネイレ』");
}

TEST_CASE("Test item data compatibility (in inventory)", "[C++: Serialization]")
{
    load_previous_savefile();
    REQUIRE(elona::itemname(g_inv[1 << 18]) == u8"ブロンズの兜 [0,1]");
}

TEST_CASE("Test item data compatibility (on ground)", "[C++: Serialization]")
{
    load_previous_savefile();
    REQUIRE(elona::itemname(g_inv[0]) == u8"割れたつぼ");
}

TEST_CASE("Test ability data compatibility", "[C++: Serialization]")
{
    int ability_idx = 170; // Medium Armor
    int chara_idx = 57;
    load_previous_savefile();
    REQUIRE(elona::cdata[chara_idx].get_skill(ability_idx).level == 28);
    REQUIRE(elona::cdata[chara_idx].get_skill(ability_idx).base_level == 28);
    REQUIRE(elona::cdata[chara_idx].get_skill(ability_idx).experience == 0);
    REQUIRE(elona::cdata[chara_idx].get_skill(ability_idx).potential == 22);
}

TEST_CASE("Test foobar save data compatibility", "[C++: Serialization]")
{
    load_previous_savefile();
    REQUIRE(elona::foobar_data.is_autodig_enabled == 0);
}

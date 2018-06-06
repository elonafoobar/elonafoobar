#include "../thirdparty/catch2/catch.hpp"

#include "tests.hpp"
#include "../testing.hpp"
#include "../character.hpp"
#include "../enums.hpp"
#include "../i18n.hpp"
#include "../item.hpp"
#include "../itemgen.hpp"
#include "../variables.hpp"
#include <sstream>

using namespace std::literals::string_literals;
using namespace elona;

TEST_CASE("test itemname: counters", "[I18N: Regressions]")
{
    testing::start_in_debug_map();
    REQUIRE(testing::test_itemname(792, 1) == u8"プチトロ");
    REQUIRE(testing::test_itemname(792, 3) == u8"3個のプチトロ");
    REQUIRE(testing::test_itemname(444, 3) == u8"3着の鉛の防弾服");
    REQUIRE(testing::test_itemname(434, 3) == u8"3冊の自己変容の魔法書(残り1回)");
    REQUIRE(testing::test_itemname(4, 3) == u8"3本の鉛の棍棒");
    REQUIRE(testing::test_itemname(771, 3) == u8"3服のブルーカプセルドラッグ");
    REQUIRE(testing::test_itemname(742, 3) == u8"★3巻のすくつ探索許可証");
    REQUIRE(testing::test_itemname(448, 3) == u8"3対の鉛の合成篭手");
    REQUIRE(testing::test_itemname(12, 3) == u8"3対の鉛の合成靴");
    REQUIRE(testing::test_itemname(54, 3) == u8"3枚の金貨");
    REQUIRE(testing::test_itemname(55, 3) == u8"3枚のプラチナ硬貨");
}

TEST_CASE("test itemname: curse state", "[I18N: Regressions]")
{
    testing::start_in_debug_map();
    item& i = testing::create_item(792, 1);
    i.identification_state = identification_state_t::completely_identified;

    SECTION("Blessed")
    {
        i.curse_state = curse_state_t::blessed;
        REQUIRE(itemname(i.index) == u8"祝福されたプチトロ");
        i.number = 3;
        REQUIRE(itemname(i.index) == u8"3個の祝福されたプチトロ");
    }
    SECTION("None")
    {
        i.curse_state = curse_state_t::none;
        REQUIRE(itemname(i.index) == u8"プチトロ");
        i.number = 3;
        REQUIRE(itemname(i.index) == u8"3個のプチトロ");
    }
    SECTION("Cursed")
    {
        i.curse_state = curse_state_t::cursed;
        REQUIRE(itemname(i.index) == u8"呪われたプチトロ");
        i.number = 3;
        REQUIRE(itemname(i.index) == u8"3個の呪われたプチトロ");
    }
    SECTION("Doomed")
    {
        i.curse_state = curse_state_t::doomed;
        REQUIRE(itemname(i.index) == u8"堕落したプチトロ");
        i.number = 3;
        REQUIRE(itemname(i.index) == u8"3個の堕落したプチトロ");
    }
    SECTION("Unidentified")
    {
        i.identification_state = identification_state_t::almost_identified;
        i.curse_state = curse_state_t::blessed;
        REQUIRE(itemname(i.index) == u8"プチトロ");
        i.number = 3;
        REQUIRE(itemname(i.index) == u8"3個のプチトロ");
    }
}

TEST_CASE("test itemname: rotten", "[I18N: Regressions]")
{
    testing::start_in_debug_map();
    item& i = testing::create_item(197, 1);
    i.material = 35;
    i.identification_state = identification_state_t::completely_identified;

    REQUIRE(itemname(i.index) == u8"レモン");
    i.param3 = -100;
    REQUIRE(itemname(i.index) == u8"腐ったレモン");
    i.number = 3;
    REQUIRE(itemname(i.index) == u8"3個の腐ったレモン");
}

TEST_CASE("test itemname: material kit", "[I18N: Regressions]")
{
    testing::start_in_debug_map();
    item& i = testing::create_item(630, 3);
    i.identification_state = identification_state_t::completely_identified;

    i.material = 22;
    REQUIRE(itemname(i.index) == u8"3個の真珠製の素材槌");
    i.material = 7;
    REQUIRE(itemname(i.index) == u8"3個のミスリル製の素材槌");
}

TEST_CASE("test itemname: furniture", "[I18N: Regressions]")
{
    testing::start_in_debug_map();
    item& i = testing::create_item(778, 3);
    i.identification_state = identification_state_t::completely_identified;

    i.material = 0;
    REQUIRE(itemname(i.index) == u8"3個の高級ソファー");
    i.material = 22;
    REQUIRE(itemname(i.index) == u8"3個の真珠細工の高級ソファー");
}

TEST_CASE("test itemname: gift", "[I18N: Regressions]")
{
    testing::start_in_debug_map();
    item& i = testing::create_item(729, 3);
    i.identification_state = identification_state_t::completely_identified;

    i.param4 = 0;
    i.material = 0;
    REQUIRE(itemname(i.index) == u8"3個のつまらないおみやげ");
    i.material = 22;
    REQUIRE(itemname(i.index) == u8"3個の真珠細工のつまらないおみやげ");
    i.param4 = 1;
    REQUIRE(itemname(i.index) == u8"3個の真珠細工の普通のおみやげ");
}

TEST_CASE("test itemname: eternal force", "[I18N: Regressions]")
{
    testing::start_in_debug_map();
    item& i = testing::create_item(4, 3);
    i.identification_state = identification_state_t::completely_identified;
    i.subname = 10000;

    ibitmod(15, i.index, 1);
    REQUIRE(itemname(i.index) == u8"3本のエターナルフォースクラブ");
    i.identification_state = identification_state_t::almost_identified;
    REQUIRE(itemname(i.index) == u8"3本の棍棒 (粗悪)[鉛製]");
}

TEST_CASE("test itemname: enchantment name", "[I18N: Regressions]")
{
    testing::start_in_debug_map();
    item& i = testing::create_item(4, 3);
    i.identification_state = identification_state_t::completely_identified;

    i.subname = 10000;
    REQUIRE(itemname(i.index) == u8"3本の烈火の鉛の棍棒");
    i.identification_state = identification_state_t::almost_identified;
    REQUIRE(itemname(i.index) == u8"3本の棍棒 (粗悪)[鉛製]");
    i.identification_state = identification_state_t::completely_identified;
    i.subname = 20000;
    REQUIRE(itemname(i.index) == u8"3本の唄う鉛の棍棒");
    i.identification_state = identification_state_t::almost_identified;
    REQUIRE(itemname(i.index) == u8"3本の棍棒 (粗悪)[鉛製]");
}

TEST_CASE("test itemname: quality", "[I18N: Regressions]")
{
    testing::start_in_debug_map();
    item& i = testing::create_item(4, 3);
    i.identification_state = identification_state_t::completely_identified;
    i.material = 15;

    SECTION("Normal")
    {
        i.quality = 3;
        REQUIRE(itemname(i.index) == u8"3本のルビナスの棍棒");
        i.identification_state = identification_state_t::almost_identified;
        REQUIRE(itemname(i.index) == u8"3本の棍棒 (高品質)[ルビナス製]");
    }
    SECTION("Rare")
    {
        i.quality = 4;
        REQUIRE(itemname(i.index) == u8"☆3本の赤く染まった棍棒");
        i.identification_state = identification_state_t::almost_identified;
        REQUIRE(itemname(i.index) == u8"3本の棍棒 (奇跡)[ルビナス製]");
    }
    SECTION("Special")
    {
        i.quality = 6;
        REQUIRE(itemname(i.index) == u8"★3本の棍棒");
        i.identification_state = identification_state_t::almost_identified;
        REQUIRE(itemname(i.index) == u8"3本の棍棒 (特別)[ルビナス製]");
    }
}

TEST_CASE("test itemname: known/original name", "[I18N: Regressions]")
{
    testing::start_in_debug_map();
    item& i = testing::create_item(4, 1);

    SECTION("Unidentified")
    {
        i.identification_state = identification_state_t::unidentified;
        REQUIRE(itemname(i.index) == u8"棍棒");
    }
    SECTION("Not completely identified")
    {
        i.quality = 4;
        i.identification_state = identification_state_t::almost_identified;
        REQUIRE(itemname(i.index) == u8"棍棒 (奇跡)[鉛製]");
    }
    SECTION("Not completely identified and normal quality")
    {
        i.quality = 3;
        i.identification_state = identification_state_t::almost_identified;
        REQUIRE(itemname(i.index) == u8"棍棒 (高品質)[鉛製]");
    }
    SECTION("Not completely identified and of high category")
    {
        i = testing::create_item(252, 1);
        i.quality = 4;
        i.identification_state = identification_state_t::almost_identified;
        REQUIRE(itemname(i.index) == u8"ジュアの癒しの魔法書(残り1回)");
    }
    SECTION("Completely identified")
    {
        i.identification_state = identification_state_t::completely_identified;
        REQUIRE(itemname(i.index) == u8"鉛の棍棒");
    }
    SECTION("Completely identified and ibit 5")
    {
        ibitmod(5, i.index, 1);
        i.identification_state = identification_state_t::completely_identified;
        REQUIRE(itemname(i.index) == u8"★鉛の棍棒");
    }
    SECTION("Completely identified and unique")
    {
        i.quality = 6;
        i.identification_state = identification_state_t::completely_identified;
        REQUIRE(itemname(i.index) == u8"★棍棒");
    }
    SECTION("Completely identified and rare")
    {
        i.quality = 4;
        i.identification_state = identification_state_t::completely_identified;
        REQUIRE(itemname(i.index) == u8"☆重き棍棒");
    }
    SECTION("Completely identified and subname")
    {
        i.quality = 3;
        i.subname = 40000;
        i.identification_state = identification_state_t::completely_identified;
        REQUIRE(itemname(i.index) == u8"鉛の棍棒《サンダーコマンダー》");
    }
    SECTION("Completely identified and rare subname")
    {
        i.quality = 4;
        i.subname = 40000;
        i.identification_state = identification_state_t::completely_identified;
        REQUIRE(itemname(i.index) == u8"☆重き棍棒『サンダーコマンダー』");
    }
}

TEST_CASE("test itemname: books", "[I18N: Regressions]")
{
    testing::start_in_debug_map();

    SECTION("Textbooks")
    {
        item& i = testing::create_item(563, 3);
        i.param1 = 106;
        REQUIRE(itemname(i.index) == u8"3冊の《格闘》という題名の学習書");
        i.param1 = 107;
        REQUIRE(itemname(i.index) == u8"3冊の《鎌》という題名の学習書");
    }

    SECTION("Books")
    {
        item& i = testing::create_item(24, 3);
        i.param1 = 1;
        REQUIRE(itemname(i.index) == u8"3冊の《迷子の兵士に送るマニュアル》という題名の本");
        i.param1 = 3;
        REQUIRE(itemname(i.index) == u8"3冊の《見るな》という題名の本");
    }

    SECTION("Books of Rachel")
    {
        item& i = testing::create_item(668, 3);
        i.param2 = 1;
        REQUIRE(itemname(i.index) == u8"3冊の第1巻目のレイチェルの絵本");
        i.param2 = 2;
        REQUIRE(itemname(i.index) == u8"3冊の第2巻目のレイチェルの絵本");
    }

    SECTION("Spellbooks")
    {
        item& i = testing::create_item(22, 3);
        i.identification_state = identification_state_t::completely_identified;
        i.quality = 1;
        i.count = 2;
        REQUIRE(itemname(i.index) == u8"3冊の解呪の魔法書(残り2回)");
        i.count = 4;
        REQUIRE(itemname(i.index) == u8"3冊の解呪の魔法書(残り4回)");
    }
}

TEST_CASE("test itemname: counters special cases", "[I18N: Regressions]")
{
    testing::start_in_debug_map();
    REQUIRE(testing::test_itemname(622, 3) == u8"★3枚の小さなメダル");
    REQUIRE(testing::test_itemname(730, 3) == u8"★3枚の友情の証");
    REQUIRE(testing::test_itemname(724, 3) == u8"★3枚の音楽チケット");

    {
        item& i = testing::create_item(783, 3);
        i.param1 = 1;
        i.subname = 0;
        REQUIRE(itemname(i.index) == u8"3枚のカスタムレシピ");
    }
}

TEST_CASE("test itemname: recipe", "[I18N: Regressions]")
{
    testing::start_in_debug_map();

    SECTION("Custom")
    {
        item& i = testing::create_item(783, 1);
        i.param1 = 1;
        i.subname = 0;
        REQUIRE(itemname(i.index) == u8"カスタムレシピ");
    }

    SECTION("Named")
    {
        item& i = testing::create_item(783, 1);
        i.param1 = 1;
        i.subname = 792 + 400;
        REQUIRE(itemname(i.index) == u8"《プチトロ》のレシピ");
    }
}


TEST_CASE("test itemname: counters (english)", "[I18N: Regressions]")
{
    testing::start_in_debug_map();
    testing::set_english();

    REQUIRE(testing::test_itemname(792, 1) == u8"putitoro");
    REQUIRE(testing::test_itemname(792, 3) == u8"3 putitoros");
}

TEST_CASE("test itemname: prefixes (english)", "[I18N: Regressions]")
{
    testing::start_in_debug_map();
    testing::set_english();

    REQUIRE(testing::test_itemname(792, 1, true) == u8"a putitoro");
    REQUIRE(testing::test_itemname(792, 3, true) == u8"3 putitoros");
    REQUIRE(testing::test_itemname(180, 1, true) == u8"an apple");
}

TEST_CASE("test itemname: prefixes and curse state", "[I18N: Regressions]")
{
    testing::start_in_debug_map();
    testing::set_english();

    item& i = testing::create_item(4, 1);
    i.quality = 4;
    i.identification_state = identification_state_t::completely_identified;
    i.curse_state = curse_state_t::cursed;

    REQUIRE(itemname(i.index, 1, 0) == "the cursed heavy club");
}

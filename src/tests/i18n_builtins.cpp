#include <sstream>

#include "../elona/character.hpp"
#include "../elona/i18n.hpp"
#include "../elona/item.hpp"
#include "../elona/itemgen.hpp"
#include "../elona/testing.hpp"
#include "../elona/ui.hpp"
#include "../elona/variables.hpp"
#include "../thirdparty/catch2/catch.hpp"
#include "tests.hpp"

using namespace std::literals::string_literals;
using namespace elona;



TEST_CASE("test i18n builtin: characters", "[I18N: Builtins]")
{
    testing::reset_state();
    testing::start_in_debug_map();

    Character& you = elona::cdata.player();
    you.name = "Orville";
    you.sex = 0;

    Character& out_of_fov =
        testing::create_chara(charaid2int(PUTIT_PROTO_ID), 0, 0);

    SECTION("Japanese")
    {
        testing::set_japanese();
        Character& chara =
            testing::create_chara(charaid2int(PUTIT_PROTO_ID), 23, 23);
        chara.sex = 1;
        update_slight();

        REQUIRE(i18n::s.format("{he($1, true)}", you) == "彼");
        REQUIRE(i18n::s.format("{he($1, true)}", chara) == "彼女");

        REQUIRE(i18n::s.format("{his($1, true)}", you) == "あなたの");
        REQUIRE(i18n::s.format("{his($1, true)}", chara) == "彼女の");

        REQUIRE(i18n::s.format("{him($1, true)}", you) == "彼");
        REQUIRE(i18n::s.format("{him($1, true)}", chara) == "彼女");

        REQUIRE(i18n::s.format("{kare_wa($1)}", you) == "");
        REQUIRE(i18n::s.format("{kare_wa($1)}", chara) == "プチは");
        REQUIRE(i18n::s.format("{kare_wa($1)}", out_of_fov) == "それは");
    }
    SECTION("English")
    {
        testing::set_english();
        Character& chara =
            testing::create_chara(charaid2int(PUTIT_PROTO_ID), 23, 23);
        chara.sex = 1;
        update_slight();

        REQUIRE(i18n::s.format("{he($1, true)}", you) == "he");
        REQUIRE(i18n::s.format("{he($1, true)}", chara) == "she");
        REQUIRE(i18n::s.format("{he($1)}", you) == "you");
        REQUIRE(i18n::s.format("{he($1)}", chara) == "she");
        REQUIRE(i18n::s.format("{he($1)}", out_of_fov) == "it");

        REQUIRE(i18n::s.format("{his($1, true)}", you) == "your");
        REQUIRE(i18n::s.format("{his($1, true)}", chara) == "her");
        REQUIRE(i18n::s.format("{his($1)}", you) == "your");
        REQUIRE(i18n::s.format("{his($1)}", chara) == "her");
        REQUIRE(i18n::s.format("{his($1)}", out_of_fov) == "its");

        REQUIRE(i18n::s.format("{him($1, true)}", you) == "him");
        REQUIRE(i18n::s.format("{him($1, true)}", chara) == "her");
        REQUIRE(i18n::s.format("{him($1)}", you) == "yourself");
        REQUIRE(i18n::s.format("{him($1)}", chara) == "her");
        REQUIRE(i18n::s.format("{him($1)}", out_of_fov) == "it");

        REQUIRE(i18n::s.format("{name($1)}", you) == "you");
        REQUIRE(i18n::s.format("{name($1)}", chara) == "the putit");
        REQUIRE(i18n::s.format("{name($1)}", out_of_fov) == "something");

        REQUIRE(i18n::s.format("{basename($1)}", you) == "Orville");
        REQUIRE(i18n::s.format("{basename($1)}", chara) == "putit");

        REQUIRE(
            i18n::s.format("you {is($1)} killed.", you) == "you are killed.");
        REQUIRE(
            i18n::s.format("something {is($1)} killed.", chara) ==
            "something is killed.");
        REQUIRE(
            i18n::s.format("you {is(true)} killed.", you) == "you are killed.");
        REQUIRE(
            i18n::s.format("something {is(false)} killed.", chara) ==
            "something is killed.");

        REQUIRE(i18n::s.format("{have($1)}", you) == "have");
        REQUIRE(i18n::s.format("{have($1)}", chara) == "has");

        REQUIRE(i18n::s.format("{himself($1)}", you) == "yourself");
        REQUIRE(i18n::s.format("{himself($1)}", chara) == "herself");

        REQUIRE(i18n::s.format("you{his_owned($1)}", you) == "your");
        REQUIRE(
            i18n::s.format("the putit{his_owned($1)}", chara) == "the putit's");

        REQUIRE(
            i18n::s.format("something go{s($1)} to hell.", chara) ==
            "something gos to hell.");
        REQUIRE(
            i18n::s.format("something go{s($1, true)} to hell.", chara) ==
            "something goes to hell.");

        chara.name = "Putit the mochi vendor";
        REQUIRE(i18n::s.format("{name_nojob($1)}", chara) == "Putit ");
    }
}

TEST_CASE("test i18n builtin: items", "[I18N: Builtins]")
{
    testing::reset_state();
    testing::start_in_debug_map();
    testing::set_english();
    const auto item = testing::create_item(PUTITORO_PROTO_ID, 1);
    update_slight();

    REQUIRE(i18n::s.format("{itemname($1)}", item) == "a putitoro");
    REQUIRE(i18n::s.format("{itemname($1, 1)}", item) == "a putitoro");
    REQUIRE(i18n::s.format("{itemname($1, 2)}", item) == "2 putitoros");
    REQUIRE(i18n::s.format("{itemname($1, 1, false)}", item) == "putitoro");
    REQUIRE(i18n::s.format("{itemname($1, 2, false)}", item) == "2 putitoros");
    REQUIRE(i18n::s.format("{itemname($1, 1, true)}", item) == "a putitoro");
    REQUIRE(i18n::s.format("{itemname($1, 2, true)}", item) == "2 putitoros");

    REQUIRE(i18n::s.format("{itembasename($1)}", item) == "putitoro");
    REQUIRE(i18n::s.format("{$1} stone{s($1)}", 0) == "0 stones");
    REQUIRE(i18n::s.format("{$1} stone{s($1)}", 1) == "1 stone");
    REQUIRE(i18n::s.format("{$1} stone{s($1)}", 2) == "2 stones");
    REQUIRE(i18n::s.format("{$1} stone{s($1)}", 10) == "10 stones");
}

TEST_CASE("test i18n builtin: misc.", "[I18N: Builtins]")
{
    testing::reset_state();
    testing::start_in_debug_map();

    SECTION("Japanese")
    {
        testing::set_japanese();
        REQUIRE(i18n::s.format("{you()}") == "あなた");
        REQUIRE(
            i18n::s.format("うわああ！{you()}は階段から足を踏み外した。") ==
            "うわああ！あなたは階段から足を踏み外した。");
    }

    SECTION("English")
    {
        testing::set_english();
        REQUIRE(i18n::s.format("{you()}") == "you");

        REQUIRE(i18n::s.format("{capitalize($1)}", "") == "");
        REQUIRE(i18n::s.format("{capitalize($1)}", "test") == "Test");
        REQUIRE(i18n::s.format("{capitalize($1)}", "TEST") == "TEST");

        REQUIRE(i18n::s.format("{ordinal($1)}", 1) == "1st");
        REQUIRE(i18n::s.format("{ordinal($1)}", 2) == "2nd");
        REQUIRE(i18n::s.format("{ordinal($1)}", 3) == "3rd");
        REQUIRE(i18n::s.format("{ordinal($1)}", 11) == "11th");
        REQUIRE(i18n::s.format("{ordinal($1)}", 12) == "12th");
        REQUIRE(i18n::s.format("{ordinal($1)}", 13) == "13th");
        REQUIRE(i18n::s.format("{ordinal($1)}", 14) == "14th");
        REQUIRE(i18n::s.format("{ordinal($1)}", 21) == "21st");
        REQUIRE(i18n::s.format("{ordinal($1)}", 22) == "22nd");
        REQUIRE(i18n::s.format("{ordinal($1)}", 23) == "23rd");
        REQUIRE(i18n::s.format("{ordinal($1)}", 24) == "24th");
    }
}

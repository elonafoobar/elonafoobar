#include "../thirdparty/catch2/catch.hpp"

#include <sstream>
#include "../elona/character.hpp"
#include "../elona/i18n.hpp"
#include "../elona/item.hpp"
#include "../elona/itemgen.hpp"
#include "../elona/testing.hpp"
#include "../elona/ui.hpp"
#include "../elona/variables.hpp"
#include "tests.hpp"

using namespace std::literals::string_literals;
using namespace elona;

TEST_CASE("test i18n builtin: characters", "[I18N: Builtins]")
{
    testing::reset_state();
    testing::start_in_debug_map();

    Character& you = elona::cdata.player();
    elona::cdatan(0, you.index) = u8"Orville";
    you.sex = 0;

    Character& out_of_fov = testing::create_chara(PUTIT_PROTO_ID, 0, 0);

    SECTION("Japanese")
    {
        testing::set_japanese();
        Character& chara = testing::create_chara(PUTIT_PROTO_ID, 23, 23);
        chara.sex = 1;
        update_slight();

        REQUIRE(i18n::fmt_hil("${he(_1, true)}", you) == u8"彼");
        REQUIRE(i18n::fmt_hil("${he(_1, true)}", chara) == u8"彼女");

        REQUIRE(i18n::fmt_hil("${his(_1, true)}", you) == u8"あなたの");
        REQUIRE(i18n::fmt_hil("${his(_1, true)}", chara) == u8"彼女の");

        REQUIRE(i18n::fmt_hil("${him(_1, true)}", you) == u8"彼");
        REQUIRE(i18n::fmt_hil("${him(_1, true)}", chara) == u8"彼女");

        REQUIRE(i18n::fmt_hil("${kare_wa(_1)}", you) == u8"");
        REQUIRE(i18n::fmt_hil("${kare_wa(_1)}", chara) == u8"プチは");
        REQUIRE(i18n::fmt_hil("${kare_wa(_1)}", out_of_fov) == u8"それは");
    }
    SECTION("English")
    {
        testing::set_english();
        Character& chara = testing::create_chara(PUTIT_PROTO_ID, 23, 23);
        chara.sex = 1;
        update_slight();

        REQUIRE(i18n::fmt_hil("${he(_1, true)}", you) == u8"he");
        REQUIRE(i18n::fmt_hil("${he(_1, true)}", chara) == u8"she");
        REQUIRE(i18n::fmt_hil("${he(_1)}", you) == u8"you");
        REQUIRE(i18n::fmt_hil("${he(_1)}", chara) == u8"she");
        REQUIRE(i18n::fmt_hil("${he(_1)}", out_of_fov) == u8"it");

        REQUIRE(i18n::fmt_hil("${his(_1, true)}", you) == u8"your");
        REQUIRE(i18n::fmt_hil("${his(_1, true)}", chara) == u8"her");
        REQUIRE(i18n::fmt_hil("${his(_1)}", you) == u8"your");
        REQUIRE(i18n::fmt_hil("${his(_1)}", chara) == u8"her");
        REQUIRE(i18n::fmt_hil("${his(_1)}", out_of_fov) == u8"its");

        REQUIRE(i18n::fmt_hil("${him(_1, true)}", you) == u8"him");
        REQUIRE(i18n::fmt_hil("${him(_1, true)}", chara) == u8"her");
        REQUIRE(i18n::fmt_hil("${him(_1)}", you) == u8"yourself");
        REQUIRE(i18n::fmt_hil("${him(_1)}", chara) == u8"her");
        REQUIRE(i18n::fmt_hil("${him(_1)}", out_of_fov) == u8"it");

        REQUIRE(i18n::fmt_hil("${name(_1)}", you) == u8"you");
        REQUIRE(i18n::fmt_hil("${name(_1)}", chara) == u8"the putit");
        REQUIRE(i18n::fmt_hil("${name(_1)}", out_of_fov) == u8"something");

        REQUIRE(i18n::fmt_hil("${basename(_1)}", you) == u8"Orville");
        REQUIRE(i18n::fmt_hil("${basename(_1)}", chara) == u8"putit");

        REQUIRE(
            i18n::fmt_hil("you ${is(_1)} killed.", you) == u8"you are killed.");
        REQUIRE(
            i18n::fmt_hil("something ${is(_1)} killed.", chara) ==
            u8"something is killed.");
        REQUIRE(
            i18n::fmt_hil("you ${is(true)} killed.", you) ==
            u8"you are killed.");
        REQUIRE(
            i18n::fmt_hil("something ${is(false)} killed.", chara) ==
            u8"something is killed.");

        REQUIRE(i18n::fmt_hil("${have(_1)}", you) == u8"have");
        REQUIRE(i18n::fmt_hil("${have(_1)}", chara) == u8"has");

        REQUIRE(i18n::fmt_hil("${himself(_1)}", you) == u8"yourself");
        REQUIRE(i18n::fmt_hil("${himself(_1)}", chara) == u8"herself");

        REQUIRE(i18n::fmt_hil("you${his_owned(_1)}", you) == u8"your");
        REQUIRE(
            i18n::fmt_hil("the putit${his_owned(_1)}", chara) ==
            u8"the putit's");

        REQUIRE(
            i18n::fmt_hil("something go${s(_1)} to hell.", chara) ==
            u8"something gos to hell.");
        REQUIRE(
            i18n::fmt_hil("something go${s(_1, true)} to hell.", chara) ==
            u8"something goes to hell.");

        elona::cdatan(0, chara.index) = u8"Putit the mochi vendor";
        REQUIRE(i18n::fmt_hil("${name_nojob(_1)}", chara) == u8"Putit ");
    }
}

TEST_CASE("test i18n builtin: items", "[I18N: Builtins]")
{
    testing::reset_state();
    testing::start_in_debug_map();
    testing::set_english();
    Item& item = testing::create_item(PUTITORO_PROTO_ID, 1);
    update_slight();

    REQUIRE(i18n::fmt_hil("${itemname(_1)}", item) == u8"a putitoro");
    REQUIRE(i18n::fmt_hil("${itemname(_1, 1)}", item) == u8"a putitoro");
    REQUIRE(i18n::fmt_hil("${itemname(_1, 2)}", item) == u8"2 putitoros");
    REQUIRE(i18n::fmt_hil("${itemname(_1, 1, false)}", item) == u8"putitoro");
    REQUIRE(
        i18n::fmt_hil("${itemname(_1, 2, false)}", item) == u8"2 putitoros");
    REQUIRE(i18n::fmt_hil("${itemname(_1, 1, true)}", item) == u8"a putitoro");
    REQUIRE(i18n::fmt_hil("${itemname(_1, 2, true)}", item) == u8"2 putitoros");

    REQUIRE(i18n::fmt_hil("${itembasename(_1)}", item) == u8"putitoro");
    REQUIRE(i18n::fmt_hil("${_1} stone${s(_1)}", 0) == u8"0 stones");
    REQUIRE(i18n::fmt_hil("${_1} stone${s(_1)}", 1) == u8"1 stone");
    REQUIRE(i18n::fmt_hil("${_1} stone${s(_1)}", 2) == u8"2 stones");
    REQUIRE(i18n::fmt_hil("${_1} stone${s(_1)}", 10) == u8"10 stones");
}

TEST_CASE("test i18n builtin: misc.", "[I18N: Builtins]")
{
    testing::reset_state();
    testing::start_in_debug_map();

    SECTION("Japanese")
    {
        testing::set_japanese();
        REQUIRE(i18n::fmt_hil("${you()}") == u8"あなた");
        REQUIRE(
            i18n::fmt_hil(u8"うわああ！${you()}は階段から足を踏み外した。") ==
            u8"うわああ！あなたは階段から足を踏み外した。");
    }

    SECTION("English")
    {
        testing::set_english();
        REQUIRE(i18n::fmt_hil("${you()}") == u8"you");

        REQUIRE(i18n::fmt_hil("${capitalize(_1)}", "") == u8"");
        REQUIRE(i18n::fmt_hil("${capitalize(_1)}", "test") == u8"Test");
        REQUIRE(i18n::fmt_hil("${capitalize(_1)}", "TEST") == u8"TEST");

        REQUIRE(i18n::fmt_hil("${ordinal(_1)}", 1) == u8"1st");
        REQUIRE(i18n::fmt_hil("${ordinal(_1)}", 2) == u8"2nd");
        REQUIRE(i18n::fmt_hil("${ordinal(_1)}", 3) == u8"3rd");
        REQUIRE(i18n::fmt_hil("${ordinal(_1)}", 11) == u8"11th");
        REQUIRE(i18n::fmt_hil("${ordinal(_1)}", 12) == u8"12th");
        REQUIRE(i18n::fmt_hil("${ordinal(_1)}", 13) == u8"13th");
        REQUIRE(i18n::fmt_hil("${ordinal(_1)}", 14) == u8"14th");
        REQUIRE(i18n::fmt_hil("${ordinal(_1)}", 21) == u8"21st");
        REQUIRE(i18n::fmt_hil("${ordinal(_1)}", 22) == u8"22nd");
        REQUIRE(i18n::fmt_hil("${ordinal(_1)}", 23) == u8"23rd");
        REQUIRE(i18n::fmt_hil("${ordinal(_1)}", 24) == u8"24th");
    }
}

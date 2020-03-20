#include "../elona/testing.hpp"
#include "../elona/text.hpp"
#include "../elona/variables.hpp"
#include "../thirdparty/catch2/catch.hpp"
#include "tests.hpp"

using namespace Catch;
using namespace elona::testing;
using namespace std::literals::string_literals;

TEST_CASE("Test cutname", "[C++: Misc.]")
{
    auto cutname = [](std::string str, int max_char_length) {
        elona::cutname(str, max_char_length);
        return str;
    };

    REQUIRE(cutname(u8"", 0) == u8"");
    REQUIRE(cutname(u8"", 99) == u8"");

    REQUIRE(cutname(u8"タイム・デューク シュハード", 0) == u8"");
    REQUIRE(
        cutname(u8"タイム・デューク シュハード", 99) ==
        u8"タイム・デューク シュハード");

    REQUIRE(cutname(u8"タイム・デューク シュハード", 1) == u8"");
    REQUIRE(cutname(u8"タイム・デューク シュハード", 6) == u8"タイム");
    REQUIRE(cutname(u8"タイム・デューク シュハード", 7) == u8"タイム");
    REQUIRE(cutname(u8"タイム・デューク シュハード", 8) == u8"タイム・");
    REQUIRE(cutname(u8"タイム・デューク シュハード", 9) == u8"タイム・");
    REQUIRE(cutname(u8"タイム・デューク シュハード", 10) == u8"タイム・デ");
    REQUIRE(
        cutname(u8"タイム・デューク シュハード", 16) == u8"タイム・デューク");
    REQUIRE(
        cutname(u8"タイム・デューク シュハード", 17) == u8"タイム・デューク ");
    REQUIRE(
        cutname(u8"タイム・デューク シュハード", 18) == u8"タイム・デューク ");
    REQUIRE(
        cutname(u8"タイム・デューク シュハード", 19) ==
        u8"タイム・デューク シ");
    REQUIRE(
        cutname(u8"タイム・デューク シュハード", 25) ==
        u8"タイム・デューク シュハー");
    REQUIRE(
        cutname(u8"タイム・デューク シュハード", 26) ==
        u8"タイム・デューク シュハー");
    REQUIRE(
        cutname(u8"タイム・デューク シュハード", 27) ==
        u8"タイム・デューク シュハード");
    REQUIRE(
        cutname(u8"タイム・デューク シュハード", 28) ==
        u8"タイム・デューク シュハード");
    REQUIRE(
        cutname(u8"タイム・デューク シュハード", 29) ==
        u8"タイム・デューク シュハード");

    REQUIRE(cutname(u8"Gentleness of Immortality Sonya", 1) == u8"G");
    REQUIRE(cutname(u8"Gentleness of Immortality Sonya", 2) == u8"Ge");
    REQUIRE(
        cutname(u8"Gentleness of Immortality Sonya", 30) ==
        u8"Gentleness of Immortality Sony");
    REQUIRE(
        cutname(u8"Gentleness of Immortality Sonya", 31) ==
        u8"Gentleness of Immortality Sonya");
    REQUIRE(
        cutname(u8"Gentleness of Immortality Sonya", 32) ==
        u8"Gentleness of Immortality Sonya");
}

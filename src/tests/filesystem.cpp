#include "../thirdparty/catch2/catch.hpp"

#include "../elona/filesystem.hpp"

using namespace elona;

TEST_CASE("Test resolve_path_for_mod", "[C++: Filesystem]")
{
    REQUIRE(
        filesystem::resolve_path_for_mod("__BUILTIN__/dood") ==
        filesystem::dirs::exe() / "dood");
    REQUIRE(
        filesystem::resolve_path_for_mod("__test__/dood") ==
        filesystem::dirs::for_mod("test") / "dood");
    REQUIRE(
        filesystem::resolve_path_for_mod("__test__/__dood__/file.txt") ==
        filesystem::dirs::for_mod("test") / "__dood__" / "file.txt");

    REQUIRE_THROWS(filesystem::resolve_path_for_mod("file.txt"));
    REQUIRE_THROWS(filesystem::resolve_path_for_mod("____"));
    REQUIRE_THROWS(filesystem::resolve_path_for_mod("__$__/file.txt"));
}

#include "../thirdparty/catch2/catch.hpp"

#include "../elona/filesystem.hpp"

using namespace elona;

TEST_CASE("Test resolve_path_for_mod", "[C++: Filesystem]")
{
    REQUIRE(
        filesystem::resolve_path_for_mod("<_builtin_>/dood") ==
        filesystem::dirs::exe() / "dood");
    REQUIRE(
        filesystem::resolve_path_for_mod("<test>/dood") ==
        filesystem::dirs::for_mod("test") / "dood");
    REQUIRE(
        filesystem::resolve_path_for_mod("<test>/<dood>/file.txt") ==
        filesystem::dirs::for_mod("test") / "<dood>" / "file.txt");

    REQUIRE_THROWS(filesystem::resolve_path_for_mod("file.txt"));
    REQUIRE_THROWS(filesystem::resolve_path_for_mod("<>"));
    REQUIRE_THROWS(filesystem::resolve_path_for_mod("<$>/file.txt"));
}

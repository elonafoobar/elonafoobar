#include "../thirdparty/catch2/catch.hpp"

#include "../elona/filesystem.hpp"

using namespace elona;

TEST_CASE("Test resolve_path_for_mod", "[C++: Filesystem]")
{
    using namespace filesystem;

    REQUIRE(resolve_path_for_mod("<_builtin_>/dood") == dirs::exe() / "dood");
    REQUIRE(
        resolve_path_for_mod("<test>/dood") == dirs::for_mod("test") / "dood");
    REQUIRE(
        resolve_path_for_mod("<test>/<dood>/file.txt") ==
        dirs::for_mod("test") / "<dood>" / "file.txt");
    REQUIRE(
        resolve_path_for_mod("<test>/file-<LANGUAGE>.txt") ==
        dirs::for_mod("test") / "file-jp.txt");
    REQUIRE(
        resolve_path_for_mod("<test>/<LANGUAGE>/file-<LANGUAGE>.txt") ==
        dirs::for_mod("test") / "jp" / "file-jp.txt");

    REQUIRE_THROWS(resolve_path_for_mod("file.txt"));
    REQUIRE_THROWS(resolve_path_for_mod("<>"));
    REQUIRE_THROWS(resolve_path_for_mod("<$>/file.txt"));
}

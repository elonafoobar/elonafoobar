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



TEST_CASE("Test is_portable_path", "[C++: Filesystem]")
{
    const auto is_portable_path = [](const char* path) {
        return filepathutil::is_portable_path(filepathutil::u8path(path));
    };

    CHECK(is_portable_path("."));
    CHECK(is_portable_path(".."));
    CHECK(is_portable_path("no-extension"));
    CHECK(is_portable_path("README.md"));

    CHECK_FALSE(is_portable_path(""));
    CHECK_FALSE(is_portable_path("con"));
    CHECK_FALSE(is_portable_path("nul.txt"));
    CHECK_FALSE(is_portable_path("<>"));
    CHECK_FALSE(is_portable_path(";"));
    CHECK_FALSE(is_portable_path("foo "));
    CHECK_FALSE(is_portable_path("foo."));
    CHECK_FALSE(is_portable_path(".vimrc"));
    CHECK_FALSE(is_portable_path("abc/xyz"));
    CHECK_FALSE(is_portable_path("/usr"));
    CHECK_FALSE(is_portable_path("C:\\Program Files"));
}

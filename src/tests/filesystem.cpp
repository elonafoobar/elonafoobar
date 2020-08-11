#include "../elona/filesystem.hpp"

#include "../thirdparty/catch2/catch.hpp"

using namespace elona;



TEST_CASE("Test is_portable_path", "[C++: Filesystem]")
{
    const auto is_portable_path = [](const char* path) {
        return fs::is_portable_path(fs::u8path(path));
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

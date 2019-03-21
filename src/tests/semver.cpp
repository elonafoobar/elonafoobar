#include "../thirdparty/catch2/catch.hpp"

#include "../elona/semver.hpp"

#include "tests.hpp"

using SemVer = elona::semver::Version;
using SemVerRequirement = elona::semver::VersionRequirement;



TEST_CASE("Test valid version", "[SemVer]")
{
    REQUIRE_SOME(SemVer::parse("0.1.0"));
    REQUIRE_SOME(SemVer::parse("1.0.0"));
    REQUIRE_SOME(SemVer::parse("10.99.42"));
}



TEST_CASE("Test invalid version", "[SemVer]")
{
    REQUIRE_NONE(SemVer::parse(""));
    REQUIRE_NONE(SemVer::parse("lomias"));
    REQUIRE_NONE(SemVer::parse("0.0.0"));
    REQUIRE_NONE(SemVer::parse("-2.0.0"));
    REQUIRE_NONE(SemVer::parse("1.0"));
    REQUIRE_NONE(SemVer::parse("1"));
    REQUIRE_NONE(SemVer::parse("100.0.0"));
    REQUIRE_NONE(SemVer::parse("1000.0.0"));
    REQUIRE_NONE(SemVer::parse("1000000000000000000000000"));
}



TEST_CASE("Test SemVer::to_string()", "[SemVer]")
{
    REQUIRE(SemVer(1, 2, 3).to_string() == "1.2.3");
    REQUIRE(SemVer(99, 88, 77).to_string() == "99.88.77");
}



TEST_CASE("Test SemVer::to_integer()", "[SemVer]")
{
    REQUIRE(SemVer(1, 2, 3).to_integer() == 10203);
    REQUIRE(SemVer(99, 88, 77).to_integer() == 998877);
}



TEST_CASE("Test version comparison", "[SemVer]")
{
    REQUIRE(SemVer(1, 2, 3) == SemVer(1, 2, 3));
    REQUIRE(SemVer(1, 2, 3) != SemVer(0, 2, 3));
    REQUIRE(SemVer(1, 2, 3) != SemVer(1, 0, 3));
    REQUIRE(SemVer(1, 2, 3) != SemVer(1, 2, 0));
    REQUIRE(SemVer(1, 2, 3) > SemVer(1, 2, 2));
    REQUIRE(SemVer(1, 2, 3) > SemVer(1, 1, 4));
    REQUIRE(SemVer(1, 2, 3) > SemVer(0, 3, 4));
    REQUIRE(SemVer(1, 2, 3) >= SemVer(1, 2, 3));
    REQUIRE(SemVer(1, 2, 3) >= SemVer(1, 2, 2));
    REQUIRE(SemVer(1, 2, 3) >= SemVer(1, 1, 4));
    REQUIRE(SemVer(1, 2, 3) >= SemVer(0, 3, 4));
}



TEST_CASE("Test valid version requirement", "[SemVer]")
{
    REQUIRE_SOME(SemVerRequirement::parse(""));
    REQUIRE_SOME(SemVerRequirement::parse(" "));
    REQUIRE_SOME(SemVerRequirement::parse("*"));
    REQUIRE_SOME(SemVerRequirement::parse("=0.1.0"));
    REQUIRE_SOME(SemVerRequirement::parse("0.1.0"));
    REQUIRE_SOME(SemVerRequirement::parse("=0.1"));
    REQUIRE_SOME(SemVerRequirement::parse("0.1"));
    REQUIRE_SOME(SemVerRequirement::parse("=0"));
    REQUIRE_SOME(SemVerRequirement::parse("0"));
    REQUIRE_SOME(SemVerRequirement::parse("==   99.10"));
    REQUIRE_SOME(SemVerRequirement::parse("  !=   1.0.10  "));
    REQUIRE_SOME(SemVerRequirement::parse("> 1.2.3"));
    REQUIRE_SOME(SemVerRequirement::parse(">= 1.2.3"));
    REQUIRE_SOME(SemVerRequirement::parse("< 1.2.3"));
    REQUIRE_SOME(SemVerRequirement::parse("<= 1.2.3"));
    REQUIRE_SOME(SemVerRequirement::parse(">= 1.2, < 1.3"));
    REQUIRE_SOME(SemVerRequirement::parse(">= 1.2, < 1.3, != 1.2.4"));
    REQUIRE_SOME(SemVerRequirement::parse(",,,,,"));
}



TEST_CASE("Test invalid version requirement", "[SemVer]")
{
    REQUIRE_NONE(SemVerRequirement::parse("larnneire"));
    REQUIRE_NONE(SemVerRequirement::parse("\t\n"));
    REQUIRE_NONE(SemVerRequirement::parse("0.0.0"));
    REQUIRE_NONE(SemVerRequirement::parse("@ 1.2.3"));
    REQUIRE_NONE(SemVerRequirement::parse("~ 1.2.3"));
    REQUIRE_NONE(SemVerRequirement::parse("+ 1.2.3"));
    REQUIRE_NONE(SemVerRequirement::parse("> 100.999.1000"));
    REQUIRE_NONE(SemVerRequirement::parse("1.0.0, xxx"));
    REQUIRE_NONE(SemVerRequirement::parse("1000000000000000000000000"));
}



TEST_CASE("Test SemVerRequirement::to_string()", "[SemVer]")
{
#define REQUIRE_(lhs, rhs) \
    REQUIRE(SemVerRequirement::parse(lhs).right().to_string() == rhs)

    REQUIRE_("", "*");
    REQUIRE_(" ", "*");
    REQUIRE_("*", "*");
    REQUIRE_("=0.1.0", "= 0.1.0");
    REQUIRE_("0.1.0", "= 0.1.0");
    REQUIRE_("=0.1", "= 0.1");
    REQUIRE_("0.1", "= 0.1");
    REQUIRE_("=0", "= 0");
    REQUIRE_("0", "= 0");
    REQUIRE_("==   99.10", "= 99.10");
    REQUIRE_("  !=   1.0.10  ", "!= 1.0.10");
    REQUIRE_("> 1.2.3", "> 1.2.3");
    REQUIRE_(">= 1.2.3", ">= 1.2.3");
    REQUIRE_("< 1.2.3", "< 1.2.3");
    REQUIRE_("<= 1.2.3", "<= 1.2.3");
    REQUIRE_(">= 1.2, < 1.3", ">= 1.2, < 1.3");
    REQUIRE_(">= 1.2, < 1.3, != 1.2.4", ">= 1.2, < 1.3, != 1.2.4");
    REQUIRE_(",,,,,", "*, *, *, *, *, *");

#undef REQUIRE_
}



TEST_CASE("Test SemVerRequirement::is_satisfied()", "[SemVer]")
{
#define REQUIRE_(req_str, ver_str) \
    REQUIRE(SemVerRequirement::parse(req_str).right().is_satisfied( \
        SemVer::parse(ver_str).right()))
#define REQUIRE_FALSE_(req_str, ver_str) \
    REQUIRE_FALSE(SemVerRequirement::parse(req_str).right().is_satisfied( \
        SemVer::parse(ver_str).right()))

    REQUIRE_("*", "0.0.1");
    REQUIRE_("*", "1.2.3");
    REQUIRE_("*", "10.0.0");
    REQUIRE_("= 0.1.0", "0.1.0");
    REQUIRE_FALSE_("= 0.1.0", "0.1.1");

    REQUIRE_("= 0.1", "0.1.0");
    REQUIRE_("= 0.1", "0.1.99");
    REQUIRE_FALSE_("= 0.1", "0.2.0");

    REQUIRE_("= 0", "0.0.1");
    REQUIRE_("= 0", "0.99.0");
    REQUIRE_FALSE_("= 0", "1.0.0");

    REQUIRE_("!= 1.0.10", "1.0.11");
    REQUIRE_FALSE_("!= 1.0.10", "1.0.10");

    REQUIRE_("> 1.2.3", "1.2.4");
    REQUIRE_("> 1.2.3", "1.3.2");
    REQUIRE_("> 1.2.3", "1.3.2");
    REQUIRE_FALSE_("> 1.2.3", "1.2.3");
    REQUIRE_FALSE_("> 1.2.3", "1.1.3");

    REQUIRE_(">= 1.2.3", "1.2.4");
    REQUIRE_(">= 1.2.3", "1.3.2");
    REQUIRE_(">= 1.2.3", "1.3.2");
    REQUIRE_(">= 1.2.3", "1.2.3");
    REQUIRE_FALSE_(">= 1.2.3", "1.1.3");

    REQUIRE_("< 1.2", "1.1.0");
    REQUIRE_("< 1.2", "1.1.55");
    REQUIRE_FALSE_("< 1.2", "1.2.0");
    REQUIRE_FALSE_("< 1.2", "1.2.10");
    REQUIRE_FALSE_("< 1.2", "1.3.0");
    REQUIRE_FALSE_("< 1.2", "2.0.0");

    REQUIRE_("<= 1.2", "1.1.0");
    REQUIRE_("<= 1.2", "1.1.55");
    REQUIRE_("<= 1.2", "1.2.0");
    REQUIRE_("<= 1.2", "1.2.10");
    REQUIRE_FALSE_("<= 1.2", "1.3.0");
    REQUIRE_FALSE_("<= 1.2", "2.0.0");

    REQUIRE_(">= 1.2, < 1.3", "1.2.10");
    REQUIRE_FALSE_(">= 1.2, < 1.3", "1.3.0");

    REQUIRE_(">= 1.2, < 1.3, != 1.2.4", "1.2.0");
    REQUIRE_(">= 1.2, < 1.3, != 1.2.4", "1.2.7");
    REQUIRE_FALSE_(">= 1.2, < 1.3, != 1.2.4", "1.2.4");
    REQUIRE_FALSE_(">= 1.2, < 1.3, != 1.2.4", "1.3.0");
    REQUIRE_FALSE_(">= 1.2, < 1.3, != 1.2.4", "3.0.0");

    REQUIRE_("= 1.0.0, *", "1.0.0");
    REQUIRE_FALSE_("= 1.0.0, *", "1.2.3");

#undef REQUIRE_
#undef REQUIRE_FALSE_
}

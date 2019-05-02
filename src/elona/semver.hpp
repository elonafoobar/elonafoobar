#pragma once

#include <cassert>

#include <regex>
#include <stdexcept>
#include <string>
#include <vector>

#include "../util/either.hpp"
#include "../util/range.hpp"
#include "../util/strutil.hpp"

// A GNU system header defines these two macro named "major" and "minor". To
// avoid breackage of semver::Version's fields, save and undefine the two here.
// cf.
// https://stackoverflow.com/questions/22240973/major-and-minor-macros-defined-in-sys-sysmacros-h-pulled-in-by-iterator
#if defined(major) || defined(minor)
#define ELONA_MAJOR_AND_MINOR_MACRO_DEFINED // for restoring
// Both Clang and GCC support this pragma
#pragma push_macro("major")
#pragma push_macro("minor")
#undef major
#undef minor
#endif



namespace elona
{

// This module is named "SemVer", but it does not follow The Semantic Versioning
// strictly.
namespace semver
{

struct VersionRequirement;



/// @putit
struct Version
{
    static constexpr int unspecified = -1;



    /// @putit
    int major;

    /// @putit
    int minor;

    /// @putit
    int patch;



    constexpr Version()
        : Version(0, 1, 0)
    {
    }



    // Constructor without validation.
    explicit constexpr Version(int major, int minor, int patch)
        : major(major)
        , minor(minor)
        , patch(patch)
    {
    }



    static either::either<std::string, Version> parse(const std::string& str)
    {
        if (const auto result = _parse_internal(str))
        {
            if (result.right()._is_incomplete())
            {
                return either::either<std::string, Version>::left_of(
                    u8"Minor and patch version must be specified: " + str);
            }
            else
            {
                return result;
            }
        }
        else
        {
            return result;
        }
    }



    // E.g., "1.2.3"
    std::string to_string() const
    {
        auto ret = std::to_string(major);
        if (minor != unspecified)
        {
            ret += "." + std::to_string(minor);
        }
        if (patch != unspecified)
        {
            ret += "." + std::to_string(patch);
        }
        return ret;
    }



    // E.g., 1.2.3 => 10203
    constexpr int to_integer() const
    {
        return major * 100 * 100 + minor * 100 + patch;
    }



    constexpr Version next_major() const
    {
        return Version{major + 1, 0, 0};
    }



    constexpr Version next_minor() const
    {
        return Version{major, minor + 1, 0};
    }



    constexpr Version next_patch() const
    {
        return Version{major, minor, patch + 1};
    }



#define ELONA_SEMVER_DEFINE_COMPARATOR(op) \
    constexpr bool operator op(const Version& other) const \
    { \
        return to_integer() op other.to_integer(); \
    }

    ELONA_SEMVER_DEFINE_COMPARATOR(==)
    ELONA_SEMVER_DEFINE_COMPARATOR(!=)
    ELONA_SEMVER_DEFINE_COMPARATOR(<)
    ELONA_SEMVER_DEFINE_COMPARATOR(<=)
    ELONA_SEMVER_DEFINE_COMPARATOR(>)
    ELONA_SEMVER_DEFINE_COMPARATOR(>=)

#undef ELONA_SEMVER_DEFINE_COMPARATOR


#include "_putit/version.hpp"


private:
    friend VersionRequirement;



    // Factory method with validation. This method allows incomplete version.
    static either::either<std::string, Version> _parse_internal(
        const std::string& str)
    {
        using Result = either::either<std::string, Version>;

        std::regex pattern{u8R"(([0-9]+)(?:\.([0-9]+)(?:\.([0-9]+))?)?)"};
        std::smatch match;
        if (const auto matched = std::regex_match(str, match, pattern))
        {
            (void)matched;
            int major, minor, patch;
            try
            {
                major = std::stoi(match[1]);
                minor = match[2].matched ? std::stoi(match[2]) : unspecified;
                patch = match[3].matched ? std::stoi(match[3]) : unspecified;
            }
            catch (std::out_of_range&)
            {
                return Result::left_of(u8"Too large number: " + str);
            }

            if (major == 0 && minor == 0 && patch == 0)
            {
                return Result::left_of(u8"Version '0.0.0' is invalid.");
            }
            // For the upper limit, see to_integer().
            if (100 <= major || 100 <= minor || 100 <= patch)
            {
                return Result::left_of(
                    u8"Each number must be less than 100: " + str);
            }

            return Result::right_of(Version{major, minor, patch});
        }
        else
        {
            return Result::left_of(u8"Invalid format: " + str);
        }
    }



    constexpr bool _is_complete() const
    {
        return minor != unspecified && patch != unspecified;
    }


    constexpr bool _is_incomplete() const
    {
        return !_is_complete();
    }
};



struct VersionRequirement
{
private:
    struct OneVersionRequirement
    {
        enum class Operator
        {
            match_any,
            equal,
            not_equal,
            less_than,
            less_than_or_equal,
            greater_than,
            greater_than_or_equal,
        };



        static either::either<std::string, OneVersionRequirement> parse(
            std::string str)
        {
            using Result = either::either<std::string, OneVersionRequirement>;

            range::remove_erase(str, ' ');

            if (str.empty() || str == "*")
            {
                return Result::right_of(
                    OneVersionRequirement{Operator::match_any, Version{}});
            }

            std::string version_str;
            Operator op;
            if (strutil::starts_with(str, u8"!="))
            {
                version_str = str.substr(2);
                op = Operator::not_equal;
            }
            else if (strutil::starts_with(str, u8"=="))
            {
                version_str = str.substr(2);
                op = Operator::equal;
            }
            else if (strutil::starts_with(str, u8"="))
            {
                version_str = str.substr(1);
                op = Operator::equal;
            }
            else if (strutil::starts_with(str, u8"<="))
            {
                version_str = str.substr(2);
                op = Operator::less_than_or_equal;
            }
            else if (strutil::starts_with(str, u8"<"))
            {
                version_str = str.substr(1);
                op = Operator::less_than;
            }
            else if (strutil::starts_with(str, u8">="))
            {
                version_str = str.substr(2);
                op = Operator::greater_than_or_equal;
            }
            else if (strutil::starts_with(str, u8">"))
            {
                version_str = str.substr(1);
                op = Operator::greater_than;
            }
            else
            {
                version_str = str;
                op = Operator::equal;
            }

            // Call Version::_parse_internal() instead of Version::parse() to
            // allow incomplete version.
            if (const auto version = Version::_parse_internal(version_str))
            {
                return Result::right_of(
                    OneVersionRequirement{op, version.right()});
            }
            else
            {
                return Result::left_of(version.left());
            }
        }



        bool is_satisfied(const Version& lhs) const
        {
            assert(lhs._is_complete());

            switch (_operator)
            {
            case Operator::match_any: return true;
            case Operator::equal: return _equal(lhs, _rhs);
            case Operator::not_equal: return !_equal(lhs, _rhs);
            case Operator::less_than: return _less_than(lhs, _rhs);
            case Operator::less_than_or_equal:
                return _less_than(lhs, _rhs) || _equal(lhs, _rhs);
            case Operator::greater_than:
                return !_less_than(lhs, _rhs) && !_equal(lhs, _rhs);
            case Operator::greater_than_or_equal: return !_less_than(lhs, _rhs);
            default: assert(0); return false;
            }
        }



        std::string to_string() const
        {
            switch (_operator)
            {
            case Operator::match_any: return "*";
            case Operator::equal: return "= " + _rhs.to_string();
            case Operator::not_equal: return "!= " + _rhs.to_string();
            case Operator::less_than: return "< " + _rhs.to_string();
            case Operator::less_than_or_equal: return "<= " + _rhs.to_string();
            case Operator::greater_than: return "> " + _rhs.to_string();
            case Operator::greater_than_or_equal:
                return ">= " + _rhs.to_string();
            default: assert(0); return "";
            }
        }



    private:
        Operator _operator;
        Version _rhs;



        OneVersionRequirement(Operator op, const Version& version)
            : _operator(op)
            , _rhs(version)
        {
        }



        static bool _equal(const Version& lhs, const Version& rhs)
        {
            if (lhs.major != rhs.major)
                return false;
            if (rhs.minor != Version::unspecified && lhs.minor != rhs.minor)
                return false;
            if (rhs.patch != Version::unspecified && lhs.patch != rhs.patch)
                return false;
            return true;
        }



        static bool _less_than(const Version& lhs, const Version& rhs)
        {
            if (lhs.major < rhs.major)
                return true;
            if (lhs.major > rhs.major)
                return false;
            if (rhs.minor == Version::unspecified)
                return false;
            if (lhs.minor < rhs.minor)
                return true;
            if (lhs.minor > rhs.minor)
                return false;
            if (rhs.patch == Version::unspecified)
                return false;
            return lhs.patch < rhs.patch;
        }
    };



public:
    explicit VersionRequirement(
        const std::vector<OneVersionRequirement>& requirements)
        : _requirements(requirements)
    {
    }



    static either::either<std::string, VersionRequirement> parse(
        const std::string& str)
    {
        using Result = either::either<std::string, VersionRequirement>;

        std::vector<OneVersionRequirement> requirements;
        for (const auto& req_str : strutil::split(str, ','))
        {
            if (const auto req = OneVersionRequirement::parse(req_str))
            {
                requirements.push_back(req.right());
            }
            else
            {
                return Result::left_of(req.left());
            }
        }

        return Result::right_of(VersionRequirement{requirements});
    }



    bool is_satisfied(const Version& version) const
    {
        return std::all_of(
            std::begin(_requirements),
            std::end(_requirements),
            [&](const auto& req) { return req.is_satisfied(version); });
    }



    std::string to_string() const
    {
        std::string result;
        for (const auto& r : _requirements)
        {
            if (result.empty())
            {
                result += r.to_string();
            }
            else
            {
                result += ", " + r.to_string();
            }
        }
        return result;
    }



private:
    std::vector<OneVersionRequirement> _requirements;
};

} // namespace semver
} // namespace elona


#ifdef ELONA_MAJOR_AND_MINOR_MACRO_DEFINED
// Restore undefined macros. See also the top of this file.
#pragma pop_macro("major")
#pragma pop_macro("minor")
#undef ELONA_MAJOR_AND_MINOR_MACRO_DEFINED
#endif

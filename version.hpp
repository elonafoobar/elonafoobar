#pragma once

#include <string>


namespace elona
{


/* clang-format off */


struct version_t
{
    int major;
    int minor;
    int patch;
    std::string revision;
    std::string timestamp;
    std::string platform;

    // Like 10203
    int id() const
    {
        return major * 100 * 100 + minor * 100 + patch;
    }

    // Like "1.2.3".
    std::string short_string() const
    {
        return std::to_string(major) + '.' + std::to_string(minor) + '.' + std::to_string(patch);
    }

    // Like "Elona Foobar version 1.2.3 (14db8cb), compiled on Darwin-17.4.0 at 2018-04-15T14:07:28Z"
    std::string long_string() const
    {
        return u8"Elona Foobar version " + short_string() + " (" + revision + "), compiled on " + platform + " at " + timestamp;
    }


    template <typename Archive>
    void serialize(Archive& ar)
    {
        ar(major);
        ar(minor);
        ar(patch);
        ar(revision);
        ar(timestamp);
        ar(platform);
    }
};


/* clang-format on */


extern const version_t latest_version;


} // namespace elona

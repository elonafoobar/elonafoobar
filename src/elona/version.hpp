#pragma once

#include <string>



namespace elona
{


/* clang-format off */


struct Version
{
    // NOTE: Don't add new fields unless you add them to serialization, which
    // will break save compatibility.
    int major;
    int minor;
    int patch;
    int serial_id;
    std::string revision;
    std::string timestamp;
    std::string platform;

    // E.g., 10203
    int id() const
    {
        return major * 100 * 100 + minor * 100 + patch;
    }

    // E.g., "1.2.3".
    std::string short_string() const
    {
        return std::to_string(major) + '.' + std::to_string(minor) + '.' + std::to_string(patch);
    }

    // E.g., "Elona foobar version 1.2.3 (14db8cb), compiled on Darwin-17.4.0 at 2018-04-15T14:07:28Z"
    std::string long_string() const
    {
        return u8"Elona foobar version " + short_string() + " (" + revision + "), compiled on " + platform + " at " + timestamp;
    }

    // E.g., "Elona_foobar/1.2.3+14db8cb (Darwin-17.4.0)"
    std::string user_agent() const
    {
        return u8"Elona_foobar/" + short_string() + "+" + revision + " (" + platform + ")";
    }
};


/* clang-format on */


extern const Version latest_version;

} // namespace elona

#pragma once


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
    int id;

    // Like "1.2.3".
    const char* short_string;

    // Like "Elona Foobar version 1.2.3 (14db8cb), compiled on Darwin-17.4.0 at 2018-04-15T14:07:28Z"
    const char* long_string;


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
>>>>>>> 57de873... TMP
};


/* clang-format on */


extern const version_t latest_version;


} // namespace elona

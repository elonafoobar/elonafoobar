#pragma once


namespace elona
{
namespace version
{


/* clang-format off */

extern const int major;
extern const int minor;
extern const int patch;
extern const char* revision;
extern const char* timestamp;
extern const char* platform;

// Like 10203
extern const int id;

// Like "1.2.3".
extern const char* short_string;

// Like "Elona Foobar version 1.2.3 (14db8cb), compiled on Darwin-17.4.0 at 2018-04-15T14:07:28Z"
extern const char* long_string;

/* clang-format on */


} // namespace version
} // namespace elona

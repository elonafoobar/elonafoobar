#pragma once
#include <string>
#include "android/defines.hpp"

namespace elona
{
namespace snail
{
namespace android
{

enum orientation
{
    landscape = SCREEN_ORIENTATION_LANDSCAPE,
    portrait = SCREEN_ORIENTATION_PORTRAIT,
    reverse_landscape = SCREEN_ORIENTATION_REVERSE_LANDSCAPE,
    reverse_portrait = SCREEN_ORIENTATION_REVERSE_PORTRAIT,
    sensor_landscape = SCREEN_ORIENTATION_SENSOR_LANDSCAPE,
    sensor_portrait = SCREEN_ORIENTATION_SENSOR_PORTRAIT,
    sensor = SCREEN_ORIENTATION_SENSOR
};

enum toast_length
{
    short_length = TOAST_LENGTH_SHORT,
    long_length = TOAST_LENGTH_LONG
};

void set_requested_orientation(orientation);
void set_navigation_bar_visibility(bool);
void toast(std::string, toast_length);
void vibrate(int);
void vibrate_pulse();

} // namespace android
} // namespace snail
} // namespace elona

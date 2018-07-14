#pragma once
#include "android/defines.hpp"

namespace elona
{
namespace snail
{
namespace android
{

enum orientation
{
    landscape          = SCREEN_ORIENTATION_LANDSCAPE,
    portrait           = SCREEN_ORIENTATION_PORTRAIT,
    reverse_landscape  = SCREEN_ORIENTATION_REVERSE_LANDSCAPE,
    reverse_portrait   = SCREEN_ORIENTATION_REVERSE_PORTRAIT,
    sensor_landscape   = SCREEN_ORIENTATION_SENSOR_LANDSCAPE,
    sensor_portrait    = SCREEN_ORIENTATION_SENSOR_PORTRAIT,
    sensor             = SCREEN_ORIENTATION_SENSOR
};

void set_requested_orientation(orientation);

}
}
}


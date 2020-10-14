#pragma once

#include "../util/enumutil.hpp"
#include "time.hpp"



namespace elona
{

enum class GameAdvanceClockEvents
{
    none = 0,
    on_minute_changed = 1,
    on_hour_changed = 2,
    all = on_minute_changed & on_hour_changed,
};

ENUMUTIL_DEFINE_BITWISE_OPERATORS(GameAdvanceClockEvents);



void game_advance_clock(
    time::Duration elapsed_time,
    GameAdvanceClockEvents triggered_events);

} // namespace elona

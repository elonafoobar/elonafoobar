#pragma once

#include "typedefs.hpp"



/**
 * Time, date, clock and calendar in game.
 *
 * After some code changes, I finally figured out that pluggable date, time,
 * calendar system is totally horrible. To simplify all the things, in Elona,
 *
 * + No time zone. All wall clocks show the same time everywhere,
 * + No daylight saving time,
 * + No calendar other than Ylva's. I.e., a month is 30 days, a year is 12
 *   months without exception,
 * + No "backward time travel", and
 * + No "change of calendar era" (for real-world example, "改元" in Japanese
 *   Calendar).
 *
 * There is only one customization point for modders:
 *
 * + You can set the starting date and time when your adventurer starts. By
 *   default, it is 517/8/12 16:10. Note that the starting time was changed in
 *   foobar.
 */
namespace elona::time
{

/**
 * Represents a "duration" between two time points *in the game world*. It is
 * internally represented in milliseconds, so the minimum value is one
 * millisecond. The largest unit of durations is a yaer, which is different from
 * common "Duration" class in other languages. It is because there is only one
 * calendar system in the game. See the above comment of `elona::time`
 * namespace.
 */
struct Duration
{
    using value_type = lua_int; // in milliseconds



    /// Ratio of one millisecond against its internal representation
    static constexpr value_type ratio_millisecond = 1;

    /// Ratio of one second against its internal representation
    static constexpr value_type ratio_second = 1000;

    /// Ratio of one minute against its internal representation
    static constexpr value_type ratio_minute = ratio_second * 60;

    /// Ratio of one hour against its internal representation
    static constexpr value_type ratio_hour = ratio_minute * 60;

    /// Ratio of one day against its internal representation
    static constexpr value_type ratio_day = ratio_hour * 24;

    /// Ratio of one month against its internal representation
    static constexpr value_type ratio_month = ratio_day * 30;

    /// Ratio of one year against its internal representation
    static constexpr value_type ratio_year = ratio_month * 12;



    /**
     * Default constructor. It is equivalent to `Duration::zero()`.
     *
     * @return A zero-length duration.
     */
    constexpr Duration() noexcept
        : _milliseconds(0)
    {
    }



    /**
     * Create a duration with the given internal representation.
     */
    constexpr explicit Duration(value_type inner) noexcept
        : _milliseconds(inner)
    {
    }



    /**
     * Create a zero-length duration.
     *
     * @return A zero-length duration.
     */
    static constexpr Duration zero() noexcept
    {
        return Duration{};
    }



    /**
     * Create a duration with the given years.
     *
     * @param t_years The number of years
     * @return @a t_years years
     */
    static constexpr Duration from_years(value_type t_years) noexcept
    {
        return Duration{ratio_year * t_years};
    }



    /**
     * Create a duration with the given months.
     *
     * @param t_months The number of months
     * @return @a t_months months
     */
    static constexpr Duration from_months(value_type t_months) noexcept
    {
        return Duration{ratio_month * t_months};
    }



    /**
     * Create a duration with the given days.
     *
     * @param t_days The number of days
     * @return @a t_days days
     */
    static constexpr Duration from_days(value_type t_days) noexcept
    {
        return Duration{ratio_day * t_days};
    }



    /**
     * Create a duration with the given hours.
     *
     * @param t_hours The number of hours
     * @return @a t_hours hours
     */
    static constexpr Duration from_hours(value_type t_hours) noexcept
    {
        return Duration{ratio_hour * t_hours};
    }



    /**
     * Create a duration with the given minutes.
     *
     * @param t_minutes The number of minutes
     * @return @a t_minutes minutes
     */
    static constexpr Duration from_minutes(value_type t_minutes) noexcept
    {
        return Duration{ratio_minute * t_minutes};
    }



    /**
     * Create a duration with the given seconds.
     *
     * @param t_seconds The number of seconds
     * @return @a t_seconds seconds
     */
    static constexpr Duration from_seconds(value_type t_seconds) noexcept
    {
        return Duration{ratio_second * t_seconds};
    }



    /**
     * Create a duration with the given milliseconds.
     *
     * @param t_milliseconds The number of milliseconds
     * @return @a t_milliseconds milliseconds
     */
    static constexpr Duration from_milliseconds(
        value_type t_milliseconds) noexcept
    {
        return Duration{t_milliseconds};
    }



    /**
     * Gets the number of years which the duration holds.
     */
    constexpr value_type years() const noexcept
    {
        return _milliseconds / ratio_year;
    }



    /**
     * Gets the number of months which the duration holds.
     */
    constexpr value_type months() const noexcept
    {
        return _milliseconds / ratio_month;
    }



    /**
     * Gets the number of days which the duration holds.
     */
    constexpr value_type days() const noexcept
    {
        return _milliseconds / ratio_day;
    }



    /**
     * Gets the number of hours which the duration holds.
     */
    constexpr value_type hours() const noexcept
    {
        return _milliseconds / ratio_hour;
    }



    /**
     * Gets the number of minutes which the duration holds.
     */
    constexpr value_type minutes() const noexcept
    {
        return _milliseconds / ratio_minute;
    }



    /**
     * Gets the number of seconds which the duration holds.
     */
    constexpr value_type seconds() const noexcept
    {
        return _milliseconds / ratio_second;
    }



    /**
     * Gets the number of milliseconds which the duration holds.
     */
    constexpr value_type milliseconds() const noexcept
    {
        return _milliseconds;
    }



    /**
     * Gets the internal representation.
     */
    constexpr value_type inner() const noexcept
    {
        return milliseconds();
    }



    /**
     * True if the duration is zero.
     */
    constexpr bool is_zero() const noexcept
    {
        return _milliseconds == 0;
    }



    /* clang-format off */
    constexpr Duration& operator+=(Duration other) noexcept { return (*this = *this + other); }
    constexpr Duration& operator-=(Duration other) noexcept { return (*this = *this - other); }
    constexpr Duration& operator*=(value_type n) noexcept { return (*this = *this * n); }
    constexpr Duration& operator/=(value_type n) noexcept { return (*this = *this / n); }

    constexpr Duration operator+(Duration other) const noexcept { return Duration{_milliseconds + other._milliseconds}; }
    constexpr Duration operator-(Duration other) const noexcept { return Duration{_milliseconds - other._milliseconds}; }
    constexpr Duration operator*(value_type n) const noexcept { return Duration{_milliseconds * n}; }
    constexpr Duration operator/(value_type n) const noexcept { return Duration{_milliseconds / n}; }

    constexpr bool operator==(Duration other) const noexcept { return _milliseconds == other._milliseconds; }
    constexpr bool operator!=(Duration other) const noexcept { return _milliseconds != other._milliseconds; }
    constexpr bool operator<(Duration other) const noexcept { return _milliseconds < other._milliseconds; }
    constexpr bool operator<=(Duration other) const noexcept { return _milliseconds <= other._milliseconds; }
    constexpr bool operator>(Duration other) const noexcept { return _milliseconds > other._milliseconds; }
    constexpr bool operator>=(Duration other) const noexcept { return _milliseconds >= other._milliseconds; }
    /* clang-format on */



private:
    value_type _milliseconds;
};



inline namespace literals
{

/* clang-format off */
inline constexpr Duration operator"" _year         (unsigned long long t) { return Duration::from_years(t);        }
inline constexpr Duration operator"" _years        (unsigned long long t) { return Duration::from_years(t);        }
inline constexpr Duration operator"" _month        (unsigned long long t) { return Duration::from_months(t);       }
inline constexpr Duration operator"" _months       (unsigned long long t) { return Duration::from_months(t);       }
inline constexpr Duration operator"" _day          (unsigned long long t) { return Duration::from_days(t);         }
inline constexpr Duration operator"" _days         (unsigned long long t) { return Duration::from_days(t);         }
inline constexpr Duration operator"" _hour         (unsigned long long t) { return Duration::from_hours(t);        }
inline constexpr Duration operator"" _hours        (unsigned long long t) { return Duration::from_hours(t);        }
inline constexpr Duration operator"" _minute       (unsigned long long t) { return Duration::from_minutes(t);      }
inline constexpr Duration operator"" _minutes      (unsigned long long t) { return Duration::from_minutes(t);      }
inline constexpr Duration operator"" _second       (unsigned long long t) { return Duration::from_seconds(t);      }
inline constexpr Duration operator"" _seconds      (unsigned long long t) { return Duration::from_seconds(t);      }
inline constexpr Duration operator"" _millisecond  (unsigned long long t) { return Duration::from_milliseconds(t); }
inline constexpr Duration operator"" _milliseconds (unsigned long long t) { return Duration::from_milliseconds(t); }
/* clang-format on */

} // namespace literals



/**
 * Represents a certain "instant time point" *in the game world*. It is
 * internally represented by a duration from "The Epoch Time". The Epoch Time is
 * New Year Day, midnight in `Game::epoch_year`.
 *
 * TODO: negative Instant (time before Epoch) support
 */
struct Instant
{
    constexpr Instant() noexcept = default;



    static constexpr Instant epoch() noexcept
    {
        return Instant{};
    }



    constexpr Instant& operator+=(Duration delta) noexcept
    {
        return (*this = *this + delta);
    }



    constexpr Instant& operator-=(Duration delta) noexcept
    {
        return (*this = *this - delta);
    }



    constexpr Instant operator+(Duration delta) const noexcept
    {
        return Instant{_from_epoch + delta};
    }



    constexpr Instant operator-(Duration delta) const noexcept
    {
        return Instant{_from_epoch - delta};
    }



    constexpr Duration operator-(Instant other) const noexcept
    {
        return _from_epoch - other._from_epoch;
    }



    constexpr Duration from_epoch() const noexcept
    {
        return _from_epoch;
    }



    constexpr bool is_epoch() const noexcept
    {
        return _from_epoch.is_zero();
    }



    /* clang-format off */
    constexpr bool operator==(Instant other) const noexcept { return _from_epoch == other._from_epoch; }
    constexpr bool operator!=(Instant other) const noexcept { return _from_epoch != other._from_epoch; }
    constexpr bool operator< (Instant other) const noexcept { return _from_epoch <  other._from_epoch; }
    constexpr bool operator<=(Instant other) const noexcept { return _from_epoch <= other._from_epoch; }
    constexpr bool operator> (Instant other) const noexcept { return _from_epoch >  other._from_epoch; }
    constexpr bool operator>=(Instant other) const noexcept { return _from_epoch >= other._from_epoch; }
    /* clang-format on */



private:
    Duration _from_epoch{};



    constexpr explicit Instant(Duration from_epoch) noexcept
        : _from_epoch(from_epoch)
    {
    }
};



/**
 * Controls the time *in the game world*.
 */
struct Clock
{
    /**
     * Query "now".
     *
     * @return The time point pointing to now
     */
    constexpr Instant now() const noexcept
    {
        return _now;
    }



    /**
     * Advance the clock by @a delta.
     */
    constexpr void advance(Duration delta) noexcept
    {
        // FIXME: potential overflow
        _now += delta;
    }



    /**
     * Turn the clock back by @a delta.
     */
    constexpr void turn_back(Duration delta) noexcept
    {
        // FIXME: potential overflow
        _now -= delta;
    }



    /**
     * Set the clock's time to @a new_time.
     */
    constexpr void travel(Instant new_time) noexcept
    {
        _now = new_time;
    }



private:
    Instant _now{Instant::epoch()};
};



struct Date
{
    constexpr explicit Date(lua_int year, uint8_t month, uint8_t day) noexcept
        : _year(year)
        , _month(month)
        , _day(day)
    {
        assert(1 <= month && month <= 12);
        assert(1 <= day && day <= 30);
    }



    constexpr lua_int year() const noexcept
    {
        return _year;
    }



    // [1, 12]
    constexpr uint8_t month() const noexcept
    {
        return _month;
    }



    // [1, 30]
    constexpr uint8_t day() const noexcept
    {
        return _day;
    }



private:
    lua_int _year;
    uint8_t _month;
    uint8_t _day;
};



struct Time
{
    constexpr explicit Time(Duration from_midnight) noexcept
        : _from_midnight(from_midnight)
    {
        assert(Duration::zero() <= from_midnight && from_midnight < 1_day);
    }



    static constexpr Time from_instant(Instant t) noexcept
    {
        return Time{Duration{t.from_epoch().inner() % Duration::ratio_day}};
    }



    // [0, 23]
    constexpr uint8_t hour() const noexcept
    {
        return _from_midnight.hours();
    }



    // [0, 59]
    constexpr uint8_t minute() const noexcept
    {
        return (_from_midnight.inner() % Duration::ratio_hour) /
            Duration::ratio_minute;
    }



    // [0, 59]
    constexpr uint8_t second() const noexcept
    {
        return (_from_midnight.inner() % Duration::ratio_minute) /
            Duration::ratio_second;
    }



    // [0, 999]
    constexpr uint16_t millisecond() const noexcept
    {
        return (_from_midnight.inner() % Duration::ratio_second) /
            Duration::ratio_millisecond;
    }



private:
    Duration _from_midnight;
};



struct DateTime
{
    constexpr explicit DateTime(Date date, Time time) noexcept
        : _date(date)
        , _time(time)
    {
    }



    constexpr auto year() const noexcept
    {
        return _date.year();
    }

    constexpr auto month() const noexcept
    {
        return _date.month();
    }

    constexpr auto day() const noexcept
    {
        return _date.day();
    }

    constexpr auto hour() const noexcept
    {
        return _time.hour();
    }

    constexpr auto minute() const noexcept
    {
        return _time.minute();
    }

    constexpr auto second() const noexcept
    {
        return _time.second();
    }

    constexpr auto millisecond() const noexcept
    {
        return _time.millisecond();
    }



private:
    Date _date;
    Time _time;
};

} // namespace elona::time



namespace elona
{

using namespace time::literals;

}

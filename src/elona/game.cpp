#include "game.hpp"

#include "variables.hpp"



namespace elona
{

const std::unique_ptr<Game>& game()
{
    static const auto the_instance = std::make_unique<Game>();
    return the_instance;
}



void modify_crowd_density(int chara_index, int delta)
{
    if (chara_index >= 57)
    {
        game()->crowd_density += delta;
        if (game()->crowd_density < 0)
            game()->crowd_density = 0;
    }
}



time::Instant game_now()
{
    return game()->universal_clock.now();
}



time::Date game_date(optional<time::Instant> instant)
{
    const auto n = (instant.value_or(game_now())).from_epoch().inner();

    lua_int y = game()->epoch_year + (n / time::Duration::ratio_year);
    uint8_t m =
        (n % time::Duration::ratio_year) / time::Duration::ratio_month + 1;
    uint8_t d =
        (n % time::Duration::ratio_month) / time::Duration::ratio_day + 1;
    return time::Date{y, m, d};
}



time::Time game_time(optional<time::Instant> instant)
{
    return time::Time::from_instant(instant.value_or(game_now()));
}



time::DateTime game_date_time(optional<time::Instant> instant)
{
    return time::DateTime{game_date(instant), game_time(instant)};
}

} // namespace elona

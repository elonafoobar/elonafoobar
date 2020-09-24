#include "time.hpp"



namespace elona::time::utils
{

inline bool is_same_month(time::Instant t1, time::Instant t2)
{
    const auto date1 = game_date(t1);
    const auto date2 = game_date(t2);
    const auto y1 = date1.year();
    const auto m1 = date1.month();
    const auto y2 = date2.year();
    const auto m2 = date2.month();
    return y1 == y2 && m1 == m2;
}

} // namespace elona::time::utils

#include "game.hpp"

#include <iomanip>
#include <sstream>

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



std::string DateTime::to_string() const
{
    std::stringstream ss;
    // clang-format off
    ss << std::setfill('0') << year << '/'
       << std::setw(2) << month << '/'
       << std::setw(2) << day << ' '
       << std::setw(2) << hour << ':'
       << std::setw(2) << minute << ':'
       << std::setw(2) << second;
    // clang-format on
    return ss.str();
}

} // namespace elona

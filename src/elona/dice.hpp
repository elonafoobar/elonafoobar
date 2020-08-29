#pragma once

#include <string>

#include "typedefs.hpp"



namespace elona
{

/// Dice
/// "XdY+Z" means "to roll a Y-face dice X times, then add Z."
struct Dice
{
    /// Number of rolls.
    lua_int rolls;

    /// Number of faces.
    lua_int faces;

    /// Bonus to be added to the dice result.
    lua_int bonus;



    constexpr Dice() noexcept
        : rolls(0)
        , faces(0)
        , bonus(0)
    {
    }



    constexpr explicit Dice(
        lua_int rolls,
        lua_int faces,
        lua_int bonus = 0) noexcept
        : rolls(rolls)
        , faces(faces)
        , bonus(bonus)
    {
    }



    constexpr bool operator==(const Dice& other) const noexcept
    {
        return rolls == other.rolls && faces == other.faces &&
            bonus == other.bonus;
    }



    constexpr bool operator!=(const Dice& other) const noexcept
    {
        return !(*this == other);
    }



    std::string to_string() const
    {
        const auto xdy = std::to_string(rolls) + "d" + std::to_string(faces);
        if (bonus == 0)
            return xdy;
        else if (bonus > 0)
            return xdy + "+" + std::to_string(bonus);
        else
            return xdy + std::to_string(bonus);
    }



    template <typename Archive>
    void serialize(Archive& ar)
    {
        /* clang-format off */
        ar(rolls);
        ar(faces);
        ar(bonus);
        /* clang-format on */
    }
};

} // namespace elona

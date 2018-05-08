#pragma once



namespace elona
{

enum class curse_state_t
{
    doomed,
    cursed,
    none,
    blessed,
};


inline bool is_cursed(curse_state_t s)
{
    return s <= curse_state_t::cursed;
}


enum class identification_state_t
{
    unidentified,
    partly_identified,
    almost_identified,
    completely_identified,
};


enum class element_t : int
{
    none = 0,
    burning = 50,
    icy = 51,
    electric = 52,
    gloomy = 53,
    psychic = 54,
    poisonous = 55,
    infernal = 56,
    shivering = 57,
    numb = 58,
    chaotic = 59,
    magic = 60,
    cut = 61,
    ether = 62,
    acid = 63,
    vorpal = 658,
};

} // namespace elona

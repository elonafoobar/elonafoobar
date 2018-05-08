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
    psychic = 54,
    numb = 58,
    shivering = 57,
    poisonous = 55,
    infernal = 56,
    chaotic = 59,
    gloomy = 53,
    cut = 61,
    ether = 62,
    acid = 63,
    vorpal = 658,
};

} // namespace elona

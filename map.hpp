#pragma once

#include "elona.hpp"
#include <string>


namespace elona
{


struct position_t;

// Returns wheather the PC can see  the position or the character.
bool is_in_fov(const position_t&);
bool is_in_fov(int cc);

void map_reload(const std::string&);

} // namespace elona

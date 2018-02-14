#pragma once


namespace elona
{


class position_t;


// Returns wheather the PC can see  the position or the character.
bool is_in_fov(const position_t&);
bool is_in_fov(int cc);


} // namespace elona

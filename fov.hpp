#pragma once

namespace elona
{

struct position_t;

// Returns wheather the PC can see  the position or the character.
bool is_in_fov(const position_t&);
bool is_in_fov(int cc);
int fov_los(int = 0, int = 0, int = 0, int = 0);
int get_route(int = 0, int = 0, int = 0, int = 0);

} // namespace elona

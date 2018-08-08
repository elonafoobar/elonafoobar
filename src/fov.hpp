#pragma once

#include <array>



namespace elona
{

struct position_t;
struct character;

constexpr int fov_max = 15; // in diameter

extern std::array<std::array<int, 2>, fov_max + 2> fovlist;

// Returns wheather the PC can see  the position or the character.
bool is_in_fov(const position_t&);
bool is_in_fov(const character& cc);
int fov_los(int = 0, int = 0, int = 0, int = 0);
int get_route(int = 0, int = 0, int = 0, int = 0);
void init_fovlist();

} // namespace elona

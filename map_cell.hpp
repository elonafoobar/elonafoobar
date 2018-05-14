#pragma once

#include <unordered_map>

namespace elona
{

struct position_t;

std::pair<int, int> cell_itemoncell(const position_t& pos);
int cell_featread(int = 0, int = 0, int = 0);
int cell_findspace(int = 0, int = 0, int = 0);
int cell_itemlist(int = 0, int = 0);
void cell_check(int = 0, int = 0);
void cell_featclear(int = 0, int = 0);
void cell_featset(int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);
void cell_movechara(int = 0, int = 0, int = 0);
void cell_refresh(int = 0, int = 0);
void cell_removechara(int = 0, int = 0);
void cell_setchara(int = 0, int = 0, int = 0);
void cell_swap(int = 0, int = 0, int = 0, int = 0);

} // namespace elona

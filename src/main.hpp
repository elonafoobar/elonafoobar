#pragma once

#include <iostream>
#include "enums.hpp"

namespace elona
{



void update_screen();
void show_race_or_class_info(int, int);

extern int prm_518;

extern elona_vector1<int> inhlist;

extern int i_at_m68;
extern double r_at_m133;


inline int _fdialog(
    std::string&,
    int,
    std::string&,
    const std::string&,
    const std::string&)
{
    return 0;
}


} // namespace elona

#define CNT cnt

#pragma once

#include <iostream>
#include "enums.hpp"

namespace elona
{



void update_screen();
void show_race_or_class_info(int, int);

extern int prm_518;
extern int prm_853;

extern int tmp_at_m172;

extern elona_vector1<int> inhlist_at_m184;
extern elona_vector1<int> inhlist;

extern int i_at_m68;
extern double r_at_m133;


#define window_recipe(a, b, c, d, e, f) window_recipe_(b, c, d, e, f)



main_menu_result_t character_making_select_sex(bool = true);
main_menu_result_t character_making_select_class(bool = true);
main_menu_result_t character_making_role_attributes(bool = true);
main_menu_result_t character_making_select_feats_and_alias(bool = true);
turn_result_t pc_turn(bool = true);
turn_result_t pass_one_turn(bool = true);

int access_character_info();


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

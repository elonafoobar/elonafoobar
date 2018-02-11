#pragma once

#include <iostream>


namespace elona
{


std::string calcage(int);

void update_screen();
void show_race_or_class_info(int);

inline int prm_518;
inline int prm_818;
inline int prm_820;
inline int prm_853;

inline int tmp_at_m172;

inline elona_vector2<std::string> invn;
inline elona_vector1<int> inhlist_at_m184;
inline elona_vector1<int> inhlist;

inline int i_at_m68;
inline double r_at_m133;


#define window_recipe(a, b, c, d, e, f) window_recipe_(b, c, d, e, f)



void character_making_select_sex(bool = true);
void character_making_select_class(bool = true);
void character_making_role_attributes(bool = true);
void character_making_select_feats_and_alias(bool = true);
void pc_turn(bool = true);
void pass_one_turn(bool = true);

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



struct elona_turn_sequence
{
};


} // namespace elona

#define CNT cnt

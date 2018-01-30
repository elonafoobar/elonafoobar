#pragma once

#include <iostream>
#include "dup.hpp"


namespace elona
{
std::string calcage(int);

void label_0481();
void label_1419();
void label_1567(int);

int prm_409;
int prm_518;
int prm_818;
int prm_820;
int prm_853;

int tmp_at_m172;

elona_vector2<std::string> invn;
elona_vector1<int> inhlist_at_m184;
elona_vector1<int> inhlist;

int i_at_m68;
double r_at_m133;


#define window_recipe(a, b, c, d, e, f) window_recipe_(b, c, d, e, f)



void label_1547(bool = true);
void label_1550(bool = true);
void label_1553(bool = true);
void label_1557(bool = true);
void label_2743(bool = true);
void label_2737(bool = true);

int label_2654();


void _fdialog(
    std::string& prm_710,
    int prm_711,
    std::string& prm_712,
    const std::string& prm_713,
    const std::string& prm_714)
{
    (void)prm_710;
    (void)prm_711;
    (void)prm_712;
    (void)prm_713;
    (void)prm_714;
}



struct elona_turn_sequence
{
};


} // namespace elona

#define CNT cnt

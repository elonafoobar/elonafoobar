#pragma once

#include <string>


namespace elona
{


int calc_buff_duration(int id, int power);
std::string get_buff_description(int id, int power);
void apply_buff(int cc, int id, int power);
int calcskill(int = 0, int = 0, int = 0);
int calcobjlv(int = 0);
int calcfixlv(int = 0);
int calcfame(int = 0, int = 0);
int decfame(int = 0, int = 0);
int calcshopreform();
int calcweaponfix(int = 0);
std::string calcage(int);
int calcexpalive(int = 0);
int calcattackhit(int = 0);
int calcattackdmg(int = 0);
int calcmedalvalue(int = 0);
int calcitemvalue(int = 0, int = 0);
int calcinvestvalue(int = 0);
int calcguiltvalue(int = 0);
int calchireadv(int = 0);
int calchirecost(int = 0);
void generatemoney(int = 0);
void calccosthire();
int calccostbuilding();
int calccosttax();
int calcmealvalue();
int calccostreload(int = 0, int = 0);
int calccargoupdate();
int calccargoupdatecost();
int calcidentifyvalue(int = 0);
int calctraincost(int = 0, int = 0, int = 0);
int calclearncost(int = 0, int = 0, int = 0);
int calcresurrectvalue(int = 0);
int calcslavevalue(int = 0);
int calcrestorecost();
int calcinitgold(int = 0);
int calcspellpower(int = 0, int = 0);
int calcspellfail(int = 0, int = 0);
int calcspellcostmp(int = 0, int = 0);
int calcspellcoststock(int = 0, int = 0);
int calcscore();
void calcpartyscore();
void calcpartyscore2();


} // namespace elona

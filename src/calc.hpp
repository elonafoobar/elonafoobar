#pragma once

#include <string>
#include "enums.hpp"
#include "optional.hpp"


namespace elona
{


int calc_buff_duration(int id, int power);
std::string get_buff_description(int id, int power);
void apply_buff(int cc, int id, int power);

struct SkillDamage
{
    int dice_x;
    int dice_y;
    int damage_bonus;
    int element;
    int element_power;
};
optional<SkillDamage> calc_skill_damage(int, int, int);
int calcobjlv(int = 0);
int calcfixlv(int = 0);
int calcfame(int = 0, int = 0);
int decfame(int = 0, int = 0);
int calcshopreform();
int calc_rate_to_pierce(int);
std::string calcage(int);
int calcexpalive(int = 0);
int calc_evasion(int cc);
int calc_accuracy(bool consider_distance);
int calcattackhit();
int calcattackdmg(int = 0);
int calcmedalvalue(int = 0);
int calcitemvalue(int = 0, int = 0);
int calcinvestvalue();
int calcguiltvalue();
int calchireadv(int = 0);
int calchirecost(int = 0);
void generatemoney(int = 0);
void calccosthire();
int calccostbuilding();
int calccosttax();
int calcmealvalue();
int calccostreload(int, bool = false);
int calccargoupdate();
int calccargoupdatecost();
int calcidentifyvalue(int);
int calctraincost(int, int, bool = false);
int calclearncost(int, int, bool = false);
int calcresurrectvalue(int = 0);
int calcslavevalue(int = 0);
int calcrestorecost();
int calcinitgold(int);
int calcspellpower(int = 0, int = 0);
int calcspellfail(int = 0, int = 0);
int calcspellcostmp(int = 0, int = 0);
int calcspellcoststock(int = 0, int = 0);
int calcscore();
void calcpartyscore();
void calcpartyscore2();

int generate_color(ColorIndex index, int id);


} // namespace elona

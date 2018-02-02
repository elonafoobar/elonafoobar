#pragma once

#include <string>


namespace elona
{


int calc_buff_duration(int id, int power);
std::string get_buff_description(int id, int power);
void apply_buff(int cc, int id, int power);


} // namespace elona

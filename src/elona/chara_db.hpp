#pragma once

#include <string>

#include "data/id.hpp"



namespace elona
{

struct Character;



void chara_db_set_stats(Character& chara, data::InstanceId id);
int chara_db_get_item_type(data::InstanceId id);
std::string chara_db_get_filter(data::InstanceId id);
std::string chara_db_get_name(data::InstanceId id);
void chara_db_invoke_eating_effect(Character& eater, data::InstanceId id);
void chara_db_get_special_equipments(data::InstanceId id);
void chara_db_get_talk(data::InstanceId id, int talk_type);

} // namespace elona

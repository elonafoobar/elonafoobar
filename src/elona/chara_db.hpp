#pragma once

#include <string>



namespace elona
{

enum class CharaId;



void chara_db_set_stats(CharaId chara_id);
int chara_db_get_item_type(CharaId chara_id);
std::string chara_db_get_filter(CharaId chara_id);
std::string chara_db_get_name(CharaId chara_id);
void chara_db_invoke_eating_effect(CharaId chara_id);
void chara_db_get_special_equipments(CharaId chara_id);
void chara_db_get_talk(CharaId chara_id, int talk_type);

} // namespace elona

#pragma once

namespace elona
{

enum class main_menu_result_t;

main_menu_result_t character_making_select_race();
main_menu_result_t character_making_select_class(bool = true);
main_menu_result_t character_making_select_sex(bool = true);
main_menu_result_t character_making_role_attributes(bool = true);
main_menu_result_t character_making_select_feats_and_alias(bool = true);
main_menu_result_t character_making_final_phase();

void show_race_or_class_info(int, int);

} // namespace elona

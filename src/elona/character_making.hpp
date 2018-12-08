#pragma once
#include <string>

namespace elona
{

enum class MainMenuResult;

MainMenuResult character_making_select_race();
MainMenuResult character_making_select_class(bool = true);
MainMenuResult character_making_select_sex(bool = true);
MainMenuResult character_making_role_attributes(bool = true);
MainMenuResult character_making_select_feats();
MainMenuResult character_making_select_alias(bool = true);
MainMenuResult character_making_customize_appearance();
MainMenuResult character_making_final_phase();

void character_making_draw_background(const std::string& key);
void draw_race_or_class_info();

} // namespace elona

#pragma once

namespace elona
{

enum class MainMenuResult
{
    main_title_menu,
    main_menu_new_game,
    main_menu_continue,
    main_menu_incarnate,
    character_making_select_race,
    character_making_select_sex,
    character_making_select_sex_looped,
    character_making_select_class,
    character_making_select_class_looped,
    character_making_role_attributes,
    character_making_role_attributes_looped,
    character_making_select_feats,
    character_making_select_alias,
    character_making_select_alias_looped,
    character_making_customize_appearance,
    character_making_final_phase,
    initialize_game,
    finish_elona,
};

MainMenuResult main_menu_wrapper();
MainMenuResult main_menu_new_game();
MainMenuResult main_title_menu();
MainMenuResult main_menu_continue();
MainMenuResult main_menu_incarnate();

} // namespace elona

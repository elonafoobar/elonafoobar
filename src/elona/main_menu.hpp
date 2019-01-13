#pragma once

namespace elona
{

enum class MainMenuResult
{
    main_title_menu,
    main_menu_new_game,
    main_menu_continue,
    main_menu_incarnate,
    main_menu_about,
    main_menu_about_changelogs,
    main_menu_about_license,
    main_menu_about_credits,
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
MainMenuResult main_menu_about();
MainMenuResult main_menu_about_changelogs();
MainMenuResult main_menu_about_license();
MainMenuResult main_menu_about_credits();

} // namespace elona

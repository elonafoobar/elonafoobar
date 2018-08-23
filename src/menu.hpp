#pragma once

#include <string>
#include "optional.hpp"

namespace elona
{

enum class turn_result_t;

struct menu_result
{
    bool succeeded; // true if stat was 1, false if it was 0
    bool pressed_f1; // true if f1 was pressed in feats menu
    turn_result_t turn_result;
};

enum class ctrl_ally_operation
{
    call_back,
    sell,
    pet_arena,
    staying,
    investigate,
    gene_engineer,
};

enum class hire_operation
{
    move,
    hire,
    revive,
};

enum class character_sheet_operation
{
    normal,
    train_skill,
    learn_skill,
    character_making,
    investigate_ally,
};


void text_set();
int cnvjkey(const std::string&);
void show_quick_menu();
void show_ex_help();
void show_game_help();
turn_result_t show_chat_history();
turn_result_t show_message_log();
void load_showroom_user_info();
void set_option();
turn_result_t play_scene();

turn_result_t show_spell_list();
turn_result_t show_skill_list();
void draw_spell_power_entry(int skill_id);
int change_appearance();
menu_result menu_feats();
menu_result menu_materials();

menu_result menu_character_sheet_normal();
bool menu_character_sheet_character_making();
optional<int> menu_character_sheet_trainer(bool is_training);
void menu_character_sheet_investigate();

int select_alias(int);
menu_result menu_feats();
menu_result menu_feats_character_making();
void deco_traits_menu();
turn_result_t show_journal();
turn_result_t show_quest_board();
void list_adventurers();
turn_result_t blending_menu();
menu_result menu_equipment();
int show_hire_menu(hire_operation);
int show_spell_writer_menu();
void showeconomy(int, int, const std::string&, int = 0, int = 0);
void show_city_chart();
void show_economy_window();
void show_politics_window();
void begin_to_believe_god(int);
void screen_analyze_self();
int ctrl_ally(ctrl_ally_operation);
void show_book_window();
int change_npc_tone();
void item_show_description();

menu_result ctrl_inventory();

} // namespace elona

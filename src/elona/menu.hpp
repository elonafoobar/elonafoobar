#pragma once

#include <string>

#include "optional.hpp"



namespace elona
{

enum class TurnResult;
struct Character;
struct Item;



struct MenuResult
{
    bool succeeded; // true if stat was 1, false if it was 0
    bool pressed_f1; // true if f1 was pressed in feats menu
    TurnResult turn_result;
};

enum class ControlAllyOperation
{
    call_back,
    sell,
    pet_arena,
    staying,
    investigate,
    gene_engineer,
};

enum class HireOperation
{
    move,
    hire,
    revive,
};

enum class CharacterSheetOperation
{
    normal,
    train_skill,
    learn_skill,
    character_making,
    investigate_ally,
};


void text_set();
std::string show_quick_menu();
bool maybe_show_ex_help(int id, bool should_update_screen = false);
void show_ex_help(int id);
void show_game_help();
TurnResult show_chat_history();
TurnResult show_message_log();
void show_option_menu();
TurnResult play_scene();

TurnResult show_spell_list();
TurnResult show_skill_list();
std::string make_spell_description(int skill_id);


enum class ChangeAppearanceResult
{
    proceed,
    canceled,
    show_help,
};

ChangeAppearanceResult menu_change_appearance(Character& chara);
void change_appearance_equipment(Character& chara);


MenuResult menu_feats();
MenuResult menu_materials();

MenuResult menu_character_sheet_normal();
bool menu_character_sheet_character_making();
optional<int> menu_character_sheet_trainer(bool is_training);
void menu_character_sheet_investigate(Character& ally);

int select_alias(int);
MenuResult menu_feats();
MenuResult menu_feats_character_making();
void deco_traits_menu();
TurnResult show_journal();
TurnResult show_quest_board();
void list_adventurers();
TurnResult blending_menu();
MenuResult menu_equipment();
int show_hire_menu(HireOperation);
int show_spell_writer_menu();
void showeconomy(int, int, const std::string&, int = 0, int = 0);
void show_city_chart();
void begin_to_believe_god(int);
void screen_analyze_self();
int ctrl_ally(
    ControlAllyOperation,
    optional_ref<Character> gene_engineering_original_character = none);
void show_book_window(const Item& book);
int change_npc_tone();
void item_show_description(Item& item);


struct CtrlInventoryResult
{
    MenuResult menu_result;
    optional_ref<Item> selected_item;
};

CtrlInventoryResult ctrl_inventory();


void menu_chat_dialog();
void menu_voting_box();

void append_accuracy_info(const Character& chara, int);
void show_weapon_dice(
    const Character& chara,
    optional_ref<Item> weapon,
    optional_ref<Item> ammo,
    int val0);
void house_board_update_screen();

} // namespace elona

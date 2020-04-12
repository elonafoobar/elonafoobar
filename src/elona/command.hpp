#pragma once

#include "optional.hpp"



namespace elona
{

enum class TurnResult;
struct Item;
struct Character;



TurnResult do_look_command();
TurnResult do_dig_command();
TurnResult do_bash_command();
TurnResult do_give_command();
TurnResult do_interact_command();
TurnResult do_cast_command();
TurnResult do_get_command();
TurnResult do_fire_command();
TurnResult do_rest_command();
TurnResult do_exit_command();
TurnResult do_change_ammo_command();
TurnResult do_pray_command();
TurnResult do_movement_command();
TurnResult do_close_command();
TurnResult do_search_command();
TurnResult do_short_cut_command(int sc_);

// These are nested inside ctrl_inventory().
TurnResult do_dip_command(Item& mix_item, Item& mix_target);
TurnResult do_use_command(Item& use_item);
TurnResult do_throw_command(Item& throw_item);
TurnResult do_eat_command(Item& food);
TurnResult do_read_command(Item& item);
TurnResult do_drink_command(Item& potion);
TurnResult do_zap_command(Item& rod);
TurnResult do_open_command(Item& box, bool play_sound = true);
TurnResult do_offer_command(Item& offering);

int ask_direction_to_close();

TurnResult step_into_gate(Item& moon_gate);
TurnResult do_bash();
TurnResult do_enter_strange_gate();
TurnResult do_gatcha(Item& gatcha_machine);
TurnResult do_use_magic();
TurnResult do_use_stairs_command(int);
TurnResult try_interact_with_npc();
TurnResult try_to_open_locked_door();
int drink_potion(optional_ref<Item> potion);
int drink_well(Item& well);
int do_zap(Item& rod);
int do_magic_attempt();

struct PickUpItemResult
{
    int type;
    optional_ref<Item> picked_up_item;
};
PickUpItemResult pick_up_item(Item& item, bool play_sound = true);

int unlock_box(int);
int try_to_cast_spell();
int read_scroll(Item& scroll);
bool read_textbook(Item& textbook);
int try_to_reveal();
int can_evade_trap();
int try_to_disarm_trap();
void disarm_trap(Character& chara, int x, int y);
void discover_trap();
void discover_hidden_path();
int decode_book(Item& book);
int read_normal_book(Item& book);
int do_cast_magic();
int do_cast_magic_attempt();
void proc_autopick();

int calcmagiccontrol(int = 0, int = 0);
int prompt_magic_location();
TurnResult do_plant(Item& seed);
void do_rest();
void open_box(Item& box);
void open_new_year_gift(Item& box);
TurnResult call_npc();

} // namespace elona

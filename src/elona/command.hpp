#pragma once

#include "eobject/eobject.hpp"
#include "optional.hpp"



namespace elona
{

enum class TurnResult;
struct Inventory;
using InventoryRef = Inventory*;
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
TurnResult do_dip_command(const ItemRef& mix_item, const ItemRef& mix_target);
TurnResult do_use_command(ItemRef use_item);
TurnResult do_throw_command(Character& thrower, const ItemRef& throw_item);
TurnResult do_eat_command(Character& eater, const ItemRef& food);
TurnResult do_read_command(Character& reader, const ItemRef& item);
TurnResult do_drink_command(Character& chara, ItemRef potion);
TurnResult do_zap_command(const ItemRef& rod);
TurnResult do_open_command(const ItemRef& box, bool play_sound = true);
TurnResult do_offer_command(const ItemRef& offering);

int ask_direction_to_close();

TurnResult step_into_gate(const ItemRef& moon_gate);
TurnResult do_bash(Character& chara);
TurnResult do_enter_strange_gate();
TurnResult do_gatcha(const ItemRef& gatcha_machine);
TurnResult do_spact_command();
TurnResult do_use_stairs_command(int);
TurnResult try_interact_with_npc(Character& chara);
TurnResult try_to_open_locked_door(Character& chara);
int drink_potion(Character& chara, const OptionalItemRef& potion);
int drink_well(Character& chara, const ItemRef& well);
int do_zap(Character& doer, const ItemRef& rod);
int do_spact(Character& doer, int& enemy_index);

struct PickUpItemResult
{
    int type;
    OptionalItemRef picked_up_item;
};
PickUpItemResult pick_up_item(
    const InventoryRef& inv,
    const ItemRef& item,
    optional_ref<Character> shopkeeper,
    bool play_sound = true);


/**
 * Try unlocking lock of box, chest or jail door.
 *
 * @param difficulty The lock difficulty
 * @return True on success; false on failure.
 */
bool try_unlock(int difficulty);

int try_to_cast_spell(Character& caster, int& enemy_index);
int read_scroll(Character& reader, const ItemRef& scroll);
bool read_textbook(Character& doer, ItemRef textbook);
int try_to_reveal(Character& chara);
int can_evade_trap(Character& chara);
int try_to_disarm_trap(Character& chara);
void disarm_trap(Character& chara, int x, int y);
void discover_trap();
void discover_hidden_path();
int decode_book(Character& reader, const ItemRef& book);
int read_normal_book(Character& reader, ItemRef book);
int do_cast_magic(Character& caster, int& enemy_index);
int do_cast_magic_attempt(Character& caster, int& enemy_index);
void proc_autopick();

bool calc_magic_control(Character& caster, const Character& target);
bool prompt_magic_location(Character& caster, int& enemy_index);
TurnResult do_plant(const ItemRef& seed);
void do_rest(Character& chara);
void open_box(const ItemRef& box);
void open_new_year_gift(const ItemRef& box);
TurnResult call_npc(Character& chara);

} // namespace elona

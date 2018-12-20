#pragma once

namespace elona
{

enum class TurnResult;

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
TurnResult do_dip_command();
TurnResult do_use_command();
TurnResult do_throw_command();
TurnResult do_eat_command();
TurnResult do_read_command();
TurnResult do_drink_command();
TurnResult do_zap_command();
TurnResult do_open_command(bool play_sound = true);
TurnResult do_offer_command();

int ask_direction_to_close();

} // namespace elona

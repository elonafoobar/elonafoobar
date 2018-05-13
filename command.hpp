#pragma once

namespace elona
{

enum class turn_result_t;

turn_result_t do_look_command();
turn_result_t do_dig_command();
turn_result_t do_bash_command();
turn_result_t do_give_command();
turn_result_t do_interact_command();
turn_result_t do_cast_command();
turn_result_t do_get_command();
turn_result_t do_fire_command();
turn_result_t do_rest_command();
turn_result_t do_exit_command();
turn_result_t do_change_ammo_command();
turn_result_t do_pray_command();
turn_result_t do_movement_command();
turn_result_t do_close_command();
turn_result_t do_search_command();

// These are nested inside ctrl_inventory().
turn_result_t do_dip_command();
turn_result_t do_use_command();
turn_result_t do_throw_command();
turn_result_t do_eat_command();
turn_result_t do_read_command();
turn_result_t do_drink_command();
turn_result_t do_zap_command();
turn_result_t do_open_command();
turn_result_t do_offer_command();

int ask_direction_to_close();

} // namespace elona

/**
 * High-level save/load operations.
 */
#pragma once



namespace elona
{

/**
 * Save the current game data.
 */
constexpr bool save_game_silent = true;
constexpr bool save_game_no_message = true;
void save_save_game(bool no_message = false, bool silent = false);


/**
 * Load a game data.
 */
void save_load_game();


/**
 * TODO
 */
void save_save_map_local_data();


/**
 * Save a gene data.
 */
void save_save_gene();


/**
 * Load a gene data.
 */
void save_load_gene();


/**
 * TODO
 */
void save_get_inheritance();


/**
 * Dump the player's information.
 */
void save_dump_player_info();


/**
 * Trigger auto-saving in the next player's turn.
 */
void save_trigger_autosaving();


/**
 * Auto-save if @ref save_trigger_autosaving was called.
 */
void save_autosave_if_triggered();

} // namespace elona

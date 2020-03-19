#pragma once



namespace elona
{

void load_save_data();


constexpr bool save_game_silent = true;
constexpr bool save_game_no_message = true;

void save_game(bool no_message = false, bool silent = false);


// Will autosave in the next PC's turn.
void save_set_autosave();
// Autosave if save_set_autosave() was called.
void save_autosave_if_needed();


void load_gene_files();
void save_gene();
void save_map_local_data();
void get_inheritance();

} // namespace elona

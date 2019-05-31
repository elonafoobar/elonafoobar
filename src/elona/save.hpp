#pragma once



namespace elona
{

void load_save_data();
void do_save_game();
void save_game();

// Will autosave in the next PC's turn.
void save_set_autosave();
// Autosave if save_set_autosave() was called.
void save_autosave_if_needed();

} // namespace elona

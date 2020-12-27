#pragma once



namespace elona
{

enum class InitializeGameMode
{
    continue_,
    new_,
    quickstart,
};

void init();
void initialize_i18n();
void initialize_lua();
void initialize_elona();
void init_fovlist();
void initialize_game(InitializeGameMode start_mode);
void initialize_debug_globals();
void initialize_picfood();
void initialize_post_data();
void initialize_set_of_random_generation();

void finish_elona();

} // namespace elona

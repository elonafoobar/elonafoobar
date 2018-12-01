#pragma once

#include "filesystem.hpp"

namespace elona
{

void initialize_config(const fs::path&);
void initialize_i18n();
void initialize_lua();
void initialize_elona();
void init_fovlist();
void initialize_game();
void initialize_debug_globals();
int run();

} // namespace elona

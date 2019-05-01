#pragma once

#include "filesystem.hpp"

namespace elona
{

void init();
void initialize_config();
void initialize_i18n();
void initialize_lua();
void initialize_elona();
void init_fovlist();
void initialize_game();
void initialize_debug_globals();
void initialize_config_defs();

} // namespace elona

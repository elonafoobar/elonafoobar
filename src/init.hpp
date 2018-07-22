#pragma once

#include "filesystem.hpp"
#include "thirdparty/sol2/sol.hpp"

namespace elona
{

void initialize_config(const fs::path&);
sol::table initialize_single_lion_db(const std::string&, const fs::path&);
void initialize_cat_db();
void initialize_lion_db();
void initialize_elona();
void init_fovlist();
void initialize_game();
void initialize_debug_globals();
int run();

} // namespace elona

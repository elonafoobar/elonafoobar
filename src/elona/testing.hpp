#pragma once
#include <functional>
#include "filesystem.hpp"

namespace elona
{
namespace testing
{

fs::path get_test_data_path();
fs::path get_mods_path();

void pre_init();
void post_run();

/***
 * Sets world state to a clean base for testing:
 * - Resets Lua mod state and reloads the core mod.
 * - Wipes and reinitializes everything.
 * - Runs game initialization.
 */
void reset_state();

void save_and_reload();

/***
 * Loads a pre-prepared savefile to test save breakages between
 * versions.
 */
void load_previous_savefile();

/***
 * Wipes state and starts in a 50x50 debug map.
 */
void start_in_debug_map();

void start_in_map(int, int);
void run_in_temporary_map(int, int, std::function<void()>);

} // namespace testing
} // namespace elona

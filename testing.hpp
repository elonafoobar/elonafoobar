#pragma once

namespace elona
{
namespace testing
{

void pre_init();
void post_run();

/***
 * Sets world state to a clean base for testing:
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

}
}

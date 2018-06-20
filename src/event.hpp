#pragma once

namespace elona
{

enum class turn_result_t;

int event_id();
bool event_was_set();
void event_add(int = 0, int = 0, int = 0);
int event_find(int = 0);
turn_result_t event_start_proc();

void proc_event();

} // namespace elona

#pragma once

namespace elona
{

enum class TurnResult;

int event_id();
bool event_was_set();
void event_add(int = 0, int = 0, int = 0);
int event_find(int = 0);
TurnResult event_start_proc();

void proc_event();

} // namespace elona

#pragma once

#include "filesystem.hpp"



namespace elona
{

enum class TurnResult;

int event_processing_event();
bool event_has_pending_events();
void event_add(int event_type, int param1 = 0, int param2 = 0);
bool event_find(int event_type);
TurnResult event_start_proc();

void event_load(const fs::path& path);
void event_save(const fs::path& path);

} // namespace elona

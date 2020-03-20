#pragma once



namespace elona
{

void weather_changes_by_location(bool output_immediately = true);
void weather_changes();
void initialize_building_data();
void initialize_economy();
int initialize_world_map();
void modrank(int = 0, int = 0, int = 0);

} // namespace elona

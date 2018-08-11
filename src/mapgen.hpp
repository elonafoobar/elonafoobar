#pragma once
#include <string>

namespace elona
{

void map_initialize();
void map_initcustom(const std::string&);
void map_tileset(int = 0);
void map_converttile();
void map_createroomdoor();
void map_makedoor();
void map_nextdir1(int = 0, int = 0);
void map_nextdir2(int = 0, int = 0);
void map_placearena(int = 0, int = 0);
void map_placecharaonentrance(int = 0, int = 0, int = 0);
int dist_town();
void map_placeplayer();
void map_randomtile(int = 0, int = 0);
void map_randsite(int = 0, int = 0);
void map_setfog(int = 0, int = 0);

void generate_debug_map();
void generate_random_nefia();
int initialize_quest_map_crop();
int initialize_random_nefia_rdtype1();
int initialize_random_nefia_rdtype4();
int initialize_random_nefia_rdtype5();
int initialize_random_nefia_rdtype2();
int initialize_random_nefia_rdtype3();
int initialize_quest_map_party();

} // namespace elona
